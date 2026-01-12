/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * MainApp.cpp - Main application implementation
 */

#include "MainApp.h"
#include "MainFrame.h"
#include <wx/xrc/xmlres.h>

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit() {
  SetVendorName("Eudora");
  SetAppName("wxEudora");

  if (!wxApp::OnInit())
    return false;

  // Initialize XRC resource system
  wxXmlResource::Get()->InitAllHandlers();

  if (!wxXmlResource::Get()->Load("resources/eudora.xrc")) {
    wxLogWarning("Failed to load resources/eudora.xrc");
  }

  // Load individual settings XRCs
  const char *settings_files[] = {"resources/settings_attachments.xrc",
                                  "resources/settings_checking_mail.xrc",
                                  "resources/settings_date_display.xrc",
                                  "resources/settings_display.xrc",
                                  "resources/settings_extra_warnings.xrc",
                                  "resources/settings_getting_attention.xrc",
                                  "resources/settings_getting_started.xrc",
                                  "resources/settings_mailboxes.xrc",
                                  "resources/settings_miscellaneous.xrc",
                                  "resources/settings_network.xrc",
                                  "resources/settings_replying.xrc",
                                  "resources/settings_sending_mail.xrc",
                                  "resources/settings_spell_checking.xrc",
                                  "resources/settings_styled_text.xrc",
                                  "resources/settings_tasks.xrc",
                                  "resources/settings_viewing_mail.xrc"};

  for (const char *file : settings_files) {
    if (!wxXmlResource::Get()->Load(file)) {
      wxLogWarning("Failed to load %s", file);
    }
  }

  // Create and show the main frame
  MainFrame *frame = new MainFrame("wxEudora");
  frame->Show(true);

  return true;
}
