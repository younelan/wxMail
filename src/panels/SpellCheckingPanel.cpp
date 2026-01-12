#include "panels/SpellCheckingPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

SpellCheckingPanel::SpellCheckingPanel(wxWindow *parent)
    : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "SpellCheckingPanel");
}

SpellCheckingPanel::~SpellCheckingPanel() {}

void SpellCheckingPanel::LoadSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");
  // Load settings - placeholder
}

void SpellCheckingPanel::SaveSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");
  // Save settings - placeholder
  config.Flush();
}
