/**
 * wxMail - A wxWidgets port of the Eudora email client
 *
 * SettingsDialog.cpp - Settings dialog implementation
 */

#include "SettingsDialog.h"
#include "panels/AttachmentsPanel.h"
#include "panels/CheckingMailPanel.h"
#include "panels/DateDisplayPanel.h"
#include "panels/DisplayPanel.h"
#include "panels/ExtraWarningsPanel.h"
#include "panels/GettingAttentionPanel.h"
#include "panels/GettingStartedPanel.h"
#include "panels/MailboxesPanel.h"
#include "panels/MiscellaneousPanel.h"
#include "panels/NetworkPanel.h"
#include "panels/ReplyingPanel.h"
#include "panels/SendingMailPanel.h"
#include "panels/SpellCheckingPanel.h"
#include "panels/StyledTextPanel.h"
#include "panels/TasksPanel.h"
#include "panels/ViewingMailPanel.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
    EVT_TREE_SEL_CHANGED(XRCID("settings_tree"),
                         SettingsDialog::OnTreeSelectionChanged)
        EVT_BUTTON(wxID_OK, SettingsDialog::OnOK)
            EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
                EVT_BUTTON(wxID_APPLY, SettingsDialog::OnApply)
                    wxEND_EVENT_TABLE()

                        SettingsDialog::SettingsDialog(wxWindow *parent)
    : m_splitter(nullptr), m_categoryList(nullptr), m_treeCtrl(nullptr),
      m_panelContainer(nullptr), m_panelSizer(nullptr), m_currentPanel(-1) {
  // Load from XRC
  wxXmlResource::Get()->LoadDialog(this, parent, "SettingsDialog");

  // Get controls
  m_categoryList = XRCCTRL(*this, "category_list", wxListBox);
  m_treeCtrl = XRCCTRL(*this, "settings_tree", wxTreeCtrl);
  m_panelContainer = XRCCTRL(*this, "settings_content_panel", wxPanel);

  // Force larger size for settings
  SetSize(wxSize(950, 750));
  CentreOnParent();

  if (m_panelContainer) {
    m_panelSizer = m_panelContainer->GetSizer();
    if (!m_panelSizer) {
      m_panelSizer = new wxBoxSizer(wxVERTICAL);
      m_panelContainer->SetSizer(m_panelSizer);
    }
  }

  PopulateCategories();

  // Show first panel by default
  if (!m_panels.empty()) {
    ShowPanel(0);
    if (m_treeCtrl) {
      wxTreeItemId root = m_treeCtrl->GetRootItem();
      if (root.IsOk()) {
        wxTreeItemIdValue cookie;
        wxTreeItemId first = m_treeCtrl->GetFirstChild(root, cookie);
        if (first.IsOk())
          m_treeCtrl->SelectItem(first);
      }
    }
  }

  Centre();
}

SettingsDialog::~SettingsDialog() {
  // Panels will be deleted by wxWidgets parent-child relationship
}

void SettingsDialog::CreateControls() {
  // Logic now handled by XRC
}

void SettingsDialog::PopulateCategories() {
  if (!m_treeCtrl)
    return;

  wxTreeItemId root = m_treeCtrl->AddRoot("Settings");

  // Add all 16 Eudora categories
  struct Category {
    const char *name;
    SettingsPanel *panel;
  };

  std::vector<Category> categories = {
      {"Getting Started", new GettingStartedPanel(m_panelContainer)},
      {"Checking Mail", new CheckingMailPanel(m_panelContainer)},
      {"Sending Mail", new SendingMailPanel(m_panelContainer)},
      {"Replying", new ReplyingPanel(m_panelContainer)},
      {"Attachments", new AttachmentsPanel(m_panelContainer)},
      {"Display", new DisplayPanel(m_panelContainer)},
      {"Viewing Mail", new ViewingMailPanel(m_panelContainer)},
      {"Mailboxes", new MailboxesPanel(m_panelContainer)},
      {"Extra Warnings", new ExtraWarningsPanel(m_panelContainer)},
      {"Miscellaneous", new MiscellaneousPanel(m_panelContainer)},
      {"Network", new NetworkPanel(m_panelContainer)},
      {"Date Display", new DateDisplayPanel(m_panelContainer)},
      {"Styled Text", new StyledTextPanel(m_panelContainer)},
      {"Getting Attention", new GettingAttentionPanel(m_panelContainer)},
      {"Spell Checking", new SpellCheckingPanel(m_panelContainer)},
      {"Tasks", new TasksPanel(m_panelContainer)}};

  for (auto &cat : categories) {
    m_treeCtrl->AppendItem(root, cat.name);
    m_panels.push_back(cat.panel);
    cat.panel->Hide();
  }

  m_treeCtrl->ExpandAll();
}

void SettingsDialog::ShowPanel(int index) {
  if (index < 0 || index >= (int)m_panels.size())
    return;

  // Save current panel if any
  SaveCurrentPanel();

  // Hide current panel
  if (m_currentPanel >= 0 && m_currentPanel < (int)m_panels.size()) {
    m_panelSizer->Detach(m_panels[m_currentPanel]);
    m_panels[m_currentPanel]->Hide();
  }

  // Show new panel
  m_currentPanel = index;
  m_panels[index]->LoadSettings();
  m_panelSizer->Add(m_panels[index], 1, wxEXPAND);
  m_panels[index]->Show();
  m_panelContainer->Layout();
}

void SettingsDialog::SaveCurrentPanel() {
  if (m_currentPanel >= 0 && m_currentPanel < (int)m_panels.size()) {
    if (m_panels[m_currentPanel]->ValidateSettings()) {
      m_panels[m_currentPanel]->SaveSettings();
    }
  }
}

void SettingsDialog::OnCategorySelected(wxCommandEvent &event) {
  // This is for ListBox, we now use Tree Selection
}

void SettingsDialog::OnTreeSelectionChanged(wxTreeEvent &event) {
  wxTreeItemId item = event.GetItem();
  if (!item.IsOk() || item == m_treeCtrl->GetRootItem())
    return;

  // Find index of chosen item
  wxTreeItemId root = m_treeCtrl->GetRootItem();
  wxTreeItemIdValue cookie;
  wxTreeItemId child = m_treeCtrl->GetFirstChild(root, cookie);
  int index = 0;
  while (child.IsOk()) {
    if (child == item) {
      ShowPanel(index);
      break;
    }
    child = m_treeCtrl->GetNextChild(root, cookie);
    index++;
  }
}

void SettingsDialog::OnOK(wxCommandEvent &WXUNUSED(event)) {
  SaveCurrentPanel();
  EndModal(wxID_OK);
}

void SettingsDialog::OnCancel(wxCommandEvent &WXUNUSED(event)) {
  EndModal(wxID_CANCEL);
}

void SettingsDialog::OnApply(wxCommandEvent &WXUNUSED(event)) {
  SaveCurrentPanel();
}
