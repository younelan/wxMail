#ifndef EXTRAWARNINGSPANEL_H
#define EXTRAWARNINGSPANEL_H

#include "panels/SettingsPanel.h"

class ExtraWarningsPanel : public SettingsPanel {
public:
  ExtraWarningsPanel(wxWindow *parent);
  ~ExtraWarningsPanel();

  void LoadSettings() override;
  void SaveSettings() override;
};

#endif
