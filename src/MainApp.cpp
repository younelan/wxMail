/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * MainApp.cpp - Main application implementation
 */

#include "MainApp.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit() {
  if (!wxApp::OnInit())
    return false;

  // Create and show the main frame
  MainFrame *frame = new MainFrame("wxEudora");
  frame->Show(true);

  return true;
}
