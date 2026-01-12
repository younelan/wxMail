/**
 * wxEudora - Settings Panel for Sending Mail
 * Ported from Eudora 7.1 IDD_SETTINGS_SENDING
 */

#include "panels/SendingMailPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

SendingMailPanel::SendingMailPanel(wxWindow *parent) : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "SendingMailPanel");

  m_emailAddress = XRCCTRL(*this, "m_emailAddress", wxTextCtrl);
  m_domainQualifier = XRCCTRL(*this, "m_domainQualifier", wxTextCtrl);
  m_smtpServer = XRCCTRL(*this, "m_smtpServer", wxTextCtrl);
  m_relayPersona = XRCCTRL(*this, "m_relayPersona", wxChoice);
  m_allowAuth = XRCCTRL(*this, "m_allowAuth", wxCheckBox);
  m_immediateSend = XRCCTRL(*this, "m_immediateSend", wxCheckBox);
  m_sendOnCheck = XRCCTRL(*this, "m_sendOnCheck", wxCheckBox);
  m_useSubmissionPort = XRCCTRL(*this, "m_useSubmissionPort", wxCheckBox);
  m_sslSend = XRCCTRL(*this, "m_sslSend", wxChoice);
}

SendingMailPanel::~SendingMailPanel() {}

void SendingMailPanel::LoadSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");

  m_emailAddress->SetValue(config.Read("/Settings/ReturnAddress", ""));
  m_domainQualifier->SetValue(config.Read("/Settings/DomainQualifier", ""));
  m_smtpServer->SetValue(config.Read("/Settings/SMTPServer", ""));
  m_allowAuth->SetValue(config.ReadBool("/Settings/SMTPAuthAllowed", false));
  m_immediateSend->SetValue(config.ReadBool("/Settings/ImmediateSend", false));
  m_sendOnCheck->SetValue(config.ReadBool("/Settings/SendOnCheck", false));
  m_useSubmissionPort->SetValue(
      config.ReadBool("/Settings/UseSubmissionPort", false));
  m_sslSend->SetSelection(config.ReadLong("/Settings/SSLSendUse", 0));
}

void SendingMailPanel::SaveSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");

  config.Write("/Settings/ReturnAddress", m_emailAddress->GetValue());
  config.Write("/Settings/DomainQualifier", m_domainQualifier->GetValue());
  config.Write("/Settings/SMTPServer", m_smtpServer->GetValue());
  config.Write("/Settings/SMTPAuthAllowed", m_allowAuth->GetValue());
  config.Write("/Settings/ImmediateSend", m_immediateSend->GetValue());
  config.Write("/Settings/SendOnCheck", m_sendOnCheck->GetValue());
  config.Write("/Settings/UseSubmissionPort", m_useSubmissionPort->GetValue());
  config.Write("/Settings/SSLSendUse", (long)m_sslSend->GetSelection());

  config.Flush();
}
