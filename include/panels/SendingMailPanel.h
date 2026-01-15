/**
 * wxMail - Settings Panel for Sending Mail
 * Ported from Eudora 7.1 IDD_SETTINGS_SENDING
 */

#ifndef SENDINGMAILPANEL_H
#define SENDINGMAILPANEL_H

#include "panels/SettingsPanel.h"

class SendingMailPanel : public SettingsPanel {
public:
  SendingMailPanel(wxWindow *parent);
  virtual ~SendingMailPanel();

  virtual void LoadSettings() override;
  virtual void SaveSettings() override;

private:
  wxTextCtrl *m_emailAddress;
  wxTextCtrl *m_domainQualifier;
  wxTextCtrl *m_smtpServer;
  wxChoice *m_relayPersona;
  wxCheckBox *m_allowAuth;
  wxCheckBox *m_immediateSend;
  wxCheckBox *m_sendOnCheck;
  wxCheckBox *m_useSubmissionPort;
  wxChoice *m_sslSend;
};

#endif // SENDINGMAILPANEL_H
