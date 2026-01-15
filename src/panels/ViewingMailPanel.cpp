#include "panels/ViewingMailPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

ViewingMailPanel::ViewingMailPanel(wxWindow *parent) : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "ViewingMailPanel");
}

ViewingMailPanel::~ViewingMailPanel() {}

void ViewingMailPanel::LoadSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");
  // Load settings from eudora.ini
}

void ViewingMailPanel::SaveSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");
  // Save settings to eudora.ini
  config.Flush();
}
