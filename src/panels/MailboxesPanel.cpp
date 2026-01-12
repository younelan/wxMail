#include "panels/MailboxesPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

MailboxesPanel::MailboxesPanel(wxWindow *parent) : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "MailboxesPanel");
}

MailboxesPanel::~MailboxesPanel() {}

void MailboxesPanel::LoadSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");
  // Load settings from eudora.ini
}

void MailboxesPanel::SaveSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");
  // Save settings to eudora.ini
  config.Flush();
}
