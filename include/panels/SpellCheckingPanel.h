#ifndef SPELLCHECKINGPANEL_H
#define SPELLCHECKINGPANEL_H

#include "panels/SettingsPanel.h"

class SpellCheckingPanel : public SettingsPanel {
public:
  SpellCheckingPanel(wxWindow *parent);
  ~SpellCheckingPanel();

  void LoadSettings() override;
  void SaveSettings() override;
};

#endif
