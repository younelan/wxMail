/**
 * wxEudora - Settings Panel for Getting Started
 * Ported from Eudora 7.1 IDD_SETTINGS_GET_START
 */

#ifndef GETTINGSTARTEDPANEL_H
#define GETTINGSTARTEDPANEL_H

#include "panels/SettingsPanel.h"

class GettingStartedPanel : public SettingsPanel {
public:
  GettingStartedPanel(wxWindow *parent);
  virtual ~GettingStartedPanel();

  virtual void LoadSettings() override;
  virtual void SaveSettings() override;

private:
  wxTextCtrl *m_realName;
  wxTextCtrl *m_emailAddress;
  wxTextCtrl *m_popServer;
  wxTextCtrl *m_loginName;
  wxTextCtrl *m_smtpServer;
  wxCheckBox *m_allowAuth;
};

#endif // GETTINGSTARTEDPANEL_H
