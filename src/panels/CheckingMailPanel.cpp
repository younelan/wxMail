/**
 * wxEudora - Settings Panel for Checking Mail
 * Ported from Eudora 7.1 IDD_SETTINGS_CHECKING
 */

#include "panels/CheckingMailPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

CheckingMailPanel::CheckingMailPanel(wxWindow *parent) : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "CheckingMailPanel");

  m_mailServer = XRCCTRL(*this, "m_mailServer", wxTextCtrl);
  m_userName = XRCCTRL(*this, "m_userName", wxTextCtrl);
  m_checkInterval = XRCCTRL(*this, "m_checkInterval", wxTextCtrl);
  m_dontCheckUnconnected = XRCCTRL(*this, "m_dontCheckUnconnected", wxCheckBox);
  m_dontCheckBattery = XRCCTRL(*this, "m_dontCheckBattery", wxCheckBox);
  m_sendOnCheck = XRCCTRL(*this, "m_sendOnCheck", wxCheckBox);
  m_sslReceive = XRCCTRL(*this, "m_sslReceive", wxChoice);

  // Get the Last SSL Info button (optional - may not need to store it)
  wxButton *sslButton = XRCCTRL(*this, "m_lastSSLInfo", wxButton);
  if (sslButton) {
    // TODO: Connect button event handler when implementing SSL info dialog
  }
}

CheckingMailPanel::~CheckingMailPanel() {}

void CheckingMailPanel::LoadSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");

  m_mailServer->SetValue(config.Read("/Settings/POPServer", ""));
  m_userName->SetValue(config.Read("/Settings/LoginName", ""));
  m_checkInterval->SetValue(
      wxString::Format("%ld", config.ReadLong("/Settings/CheckForMail", 30)));
  m_dontCheckUnconnected->SetValue(
      config.ReadBool("/Settings/DontCheckUnconnected", false));
  m_dontCheckBattery->SetValue(
      config.ReadBool("/Settings/DontCheckBattery", false));
  m_sendOnCheck->SetValue(config.ReadBool("/Settings/SendOnCheck", false));
  m_sslReceive->SetSelection(config.ReadLong("/Settings/SSLReceiveUse", 0));
}

void CheckingMailPanel::SaveSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");

  config.Write("/Settings/POPServer", m_mailServer->GetValue());
  config.Write("/Settings/LoginName", m_userName->GetValue());

  long interval;
  if (m_checkInterval->GetValue().ToLong(&interval))
    config.Write("/Settings/CheckForMail", interval);

  config.Write("/Settings/DontCheckUnconnected",
               m_dontCheckUnconnected->GetValue());
  config.Write("/Settings/DontCheckBattery", m_dontCheckBattery->GetValue());
  config.Write("/Settings/SendOnCheck", m_sendOnCheck->GetValue());
  config.Write("/Settings/SSLReceiveUse", (long)m_sslReceive->GetSelection());

  config.Flush();
}
