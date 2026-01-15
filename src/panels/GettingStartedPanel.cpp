/**
 * wxMail - Settings Panel for Getting Started
 * Ported from Eudora 7.1 IDD_SETTINGS_GET_START
 */

#include "panels/GettingStartedPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

GettingStartedPanel::GettingStartedPanel(wxWindow *parent)
    : SettingsPanel(parent) {
  // Load UI from XRC resource
  wxXmlResource::Get()->LoadPanel(this, parent, "GettingStartedPanel");

  // Get control pointers
  m_realName = XRCCTRL(*this, "m_realName", wxTextCtrl);
  m_emailAddress = XRCCTRL(*this, "m_emailAddress", wxTextCtrl);
  m_popServer = XRCCTRL(*this, "m_popServer", wxTextCtrl);
  m_loginName = XRCCTRL(*this, "m_loginName", wxTextCtrl);
  m_smtpServer = XRCCTRL(*this, "m_smtpServer", wxTextCtrl);
  m_allowAuth = XRCCTRL(*this, "m_allowAuth", wxCheckBox);
}

GettingStartedPanel::~GettingStartedPanel() {}

void GettingStartedPanel::LoadSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");

  m_realName->SetValue(config.Read("/Settings/RealName", ""));
  m_emailAddress->SetValue(config.Read("/Settings/ReturnAddress", ""));
  m_popServer->SetValue(config.Read("/Settings/POPServer", ""));
  m_loginName->SetValue(config.Read("/Settings/LoginName", ""));
  m_smtpServer->SetValue(config.Read("/Settings/SMTPServer", ""));
  m_allowAuth->SetValue(config.ReadBool("/Settings/SMTPAuthAllowed", false));
}

void GettingStartedPanel::SaveSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");

  config.Write("/Settings/RealName", m_realName->GetValue());
  config.Write("/Settings/ReturnAddress", m_emailAddress->GetValue());
  config.Write("/Settings/POPServer", m_popServer->GetValue());
  config.Write("/Settings/LoginName", m_loginName->GetValue());
  config.Write("/Settings/SMTPServer", m_smtpServer->GetValue());
  config.Write("/Settings/SMTPAuthAllowed", m_allowAuth->GetValue());

  config.Flush();
}
