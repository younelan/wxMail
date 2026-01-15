#include "panels/TasksPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

TasksPanel::TasksPanel(wxWindow *parent) : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "TasksPanel");
}

TasksPanel::~TasksPanel() {}

void TasksPanel::LoadSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");
  // Load settings - placeholder
}

void TasksPanel::SaveSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");
  // Save settings - placeholder
  config.Flush();
}
