#include "panels/ExtraWarningsPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

ExtraWarningsPanel::ExtraWarningsPanel(wxWindow *parent)
    : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "ExtraWarningsPanel");
}

ExtraWarningsPanel::~ExtraWarningsPanel() {}

void ExtraWarningsPanel::LoadSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");
  // Load settings from eudora.ini
}

void ExtraWarningsPanel::SaveSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");
  // Save settings to eudora.ini
  config.Flush();
}
