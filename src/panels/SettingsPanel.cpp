/**
 * wxMail - A wxWidgets port of the Eudora email client
 *
 * SettingsPanel.cpp - Base class implementation
 */

#include "panels/SettingsPanel.h"

SettingsPanel::SettingsPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {
  SetBackgroundColour(*wxWHITE);
}

SettingsPanel::~SettingsPanel() {}

wxStaticText *SettingsPanel::CreateLabel(const wxString &text, wxSizer *sizer) {
  wxStaticText *label = new wxStaticText(this, wxID_ANY, text);
  if (sizer) {
    sizer->Add(label, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
  }
  return label;
}

wxTextCtrl *SettingsPanel::CreateTextCtrl(const wxString &value,
                                          wxSizer *sizer) {
  wxTextCtrl *textCtrl = new wxTextCtrl(this, wxID_ANY, value);
  if (sizer) {
    sizer->Add(textCtrl, 1, wxALL | wxEXPAND, 5);
  }
  return textCtrl;
}

wxCheckBox *SettingsPanel::CreateCheckBox(const wxString &label, bool checked,
                                          wxSizer *sizer) {
  wxCheckBox *checkBox = new wxCheckBox(this, wxID_ANY, label);
  checkBox->SetValue(checked);
  if (sizer) {
    sizer->Add(checkBox, 0, wxALL, 5);
  }
  return checkBox;
}

wxChoice *SettingsPanel::CreateChoice(const wxArrayString &choices,
                                      int selection, wxSizer *sizer) {
  wxChoice *choice =
      new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
  if (selection >= 0 && selection < (int)choices.GetCount()) {
    choice->SetSelection(selection);
  }
  if (sizer) {
    sizer->Add(choice, 0, wxALL, 5);
  }
  return choice;
}
