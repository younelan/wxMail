/**
 * wxMail - A wxWidgets port of the Eudora email client
 *
 * SettingsPanel.h - Base class for all settings panels
 */

#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <wx/wx.h>

/**
 * Base class for all settings panels
 * Each category in the settings dialog derives from this
 */
class SettingsPanel : public wxPanel {
public:
  SettingsPanel(wxWindow *parent, wxWindowID id = wxID_ANY);
  virtual ~SettingsPanel();

  // Override these in derived classes
  virtual void LoadSettings() = 0;
  virtual void SaveSettings() = 0;
  virtual bool ValidateSettings() { return true; }

protected:
  // Helper methods for creating common controls
  wxStaticText *CreateLabel(const wxString &text, wxSizer *sizer = nullptr);
  wxTextCtrl *CreateTextCtrl(const wxString &value, wxSizer *sizer = nullptr);
  wxCheckBox *CreateCheckBox(const wxString &label, bool checked,
                             wxSizer *sizer = nullptr);
  wxChoice *CreateChoice(const wxArrayString &choices, int selection,
                         wxSizer *sizer = nullptr);
};

#endif // SETTINGSPANEL_H
