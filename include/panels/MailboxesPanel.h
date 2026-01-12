#ifndef MAILBOXESPANEL_H
#define MAILBOXESPANEL_H

#include "panels/SettingsPanel.h"

class MailboxesPanel : public SettingsPanel {
public:
  MailboxesPanel(wxWindow *parent);
  ~MailboxesPanel();

  void LoadSettings() override;
  void SaveSettings() override;
};

#endif
