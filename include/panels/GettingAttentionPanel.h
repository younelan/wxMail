#ifndef GETTINGATTENTIONPANEL_H
#define GETTINGATTENTIONPANEL_H

#include "panels/SettingsPanel.h"

class GettingAttentionPanel : public SettingsPanel {
public:
  GettingAttentionPanel(wxWindow *parent);
  ~GettingAttentionPanel();

  void LoadSettings() override;
  void SaveSettings() override;
};

#endif
