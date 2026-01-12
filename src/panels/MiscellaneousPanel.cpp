#include "panels/MiscellaneousPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

MiscellaneousPanel::MiscellaneousPanel(wxWindow *parent)
    : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "MiscellaneousPanel");
}

MiscellaneousPanel::~MiscellaneousPanel() {}

void MiscellaneousPanel::LoadSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");
  // Load settings from eudora.ini
}

void MiscellaneousPanel::SaveSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");
  // Save settings to eudora.ini
  config.Flush();
}
