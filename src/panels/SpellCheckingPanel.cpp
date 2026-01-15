#include "panels/SpellCheckingPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

SpellCheckingPanel::SpellCheckingPanel(wxWindow *parent)
    : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "SpellCheckingPanel");
}

SpellCheckingPanel::~SpellCheckingPanel() {}

void SpellCheckingPanel::LoadSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");
  // Load settings - placeholder
}

void SpellCheckingPanel::SaveSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");
  // Save settings - placeholder
  config.Flush();
}
