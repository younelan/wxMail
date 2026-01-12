#include "panels/GettingAttentionPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

GettingAttentionPanel::GettingAttentionPanel(wxWindow *parent)
    : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "GettingAttentionPanel");
}

GettingAttentionPanel::~GettingAttentionPanel() {}

void GettingAttentionPanel::LoadSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");
  // Load settings - placeholder
}

void GettingAttentionPanel::SaveSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");
  // Save settings - placeholder
  config.Flush();
}
