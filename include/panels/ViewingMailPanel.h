#ifndef VIEWINGMAILPANEL_H
#define VIEWINGMAILPANEL_H

#include "panels/SettingsPanel.h"

class ViewingMailPanel : public SettingsPanel {
public:
  ViewingMailPanel(wxWindow *parent);
  ~ViewingMailPanel();

  void LoadSettings() override;
  void SaveSettings() override;
};

#endif
