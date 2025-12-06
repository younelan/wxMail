/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * MainApp.h - Main application class header
 */

#ifndef MAINAPP_H
#define MAINAPP_H

#include <wx/wx.h>

/**
 * Main application class for wxEudora
 */
class MainApp : public wxApp {
public:
  virtual bool OnInit() override;
};

#endif // MAINAPP_H
