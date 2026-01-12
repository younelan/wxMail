/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * SettingsDialog.h - Main settings dialog
 */

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "panels/SettingsPanel.h"
#include <wx/listbox.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/wx.h>

class SettingsDialog : public wxDialog {
public:
  SettingsDialog(wxWindow *parent);
  virtual ~SettingsDialog();

private:
  void CreateControls();
  void PopulateCategories();
  void OnCategorySelected(wxCommandEvent &event);
  void OnTreeSelectionChanged(wxTreeEvent &event);
  void OnOK(wxCommandEvent &event);
  void OnCancel(wxCommandEvent &event);
  void OnApply(wxCommandEvent &event);

  void ShowPanel(int index);
  void SaveCurrentPanel();

  wxSplitterWindow *m_splitter;
  wxListBox *m_categoryList;
  wxTreeCtrl *m_treeCtrl;
  wxPanel *m_panelContainer;
  wxSizer *m_panelSizer;

  std::vector<SettingsPanel *> m_panels;
  int m_currentPanel;

  wxDECLARE_EVENT_TABLE();
};

#endif // SETTINGSDIALOG_H
