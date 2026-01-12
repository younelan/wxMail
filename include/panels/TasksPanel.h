#ifndef TASKSPANEL_H
#define TASKSPANEL_H

#include "panels/SettingsPanel.h"

class TasksPanel : public SettingsPanel {
public:
  TasksPanel(wxWindow *parent);
  ~TasksPanel();

  void LoadSettings() override;
  void SaveSettings() override;
};

#endif
