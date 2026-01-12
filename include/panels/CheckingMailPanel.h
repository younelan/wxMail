/**
 * wxEudora - Settings Panel for Checking Mail
 * Ported from Eudora 7.1 IDD_SETTINGS_CHECKING
 */

#ifndef CHECKINGMAILPANEL_H
#define CHECKINGMAILPANEL_H

#include "panels/SettingsPanel.h"

class CheckingMailPanel : public SettingsPanel {
public:
  CheckingMailPanel(wxWindow *parent);
  virtual ~CheckingMailPanel();

  virtual void LoadSettings() override;
  virtual void SaveSettings() override;

private:
  wxTextCtrl *m_mailServer;
  wxTextCtrl *m_userName;
  wxTextCtrl *m_checkInterval;
  wxCheckBox *m_dontCheckUnconnected;
  wxCheckBox *m_dontCheckBattery;
  wxCheckBox *m_sendOnCheck;
  wxChoice *m_sslReceive;
};

#endif // CHECKINGMAILPANEL_H
