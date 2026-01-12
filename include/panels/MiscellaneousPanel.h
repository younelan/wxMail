#ifndef MISCELLANEOUSPANEL_H
#define MISCELLANEOUSPANEL_H

#include "panels/SettingsPanel.h"

class MiscellaneousPanel : public SettingsPanel {
public:
  MiscellaneousPanel(wxWindow *parent);
  ~MiscellaneousPanel();

  void LoadSettings() override;
  void SaveSettings() override;
};

#endif
