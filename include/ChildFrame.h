/**
 * wxMail - A wxWidgets port of the Eudora email client
 *
 * ChildFrame.h - MDI child window for messages and mailbox contents
 */

#ifndef CHILDFRAME_H
#define CHILDFRAME_H

#include <wx/mdi.h>
#include <wx/wx.h>

/**
 * MDI child window for displaying message or mailbox content
 */
class ChildFrame : public wxMDIChildFrame {
public:
  ChildFrame(wxMDIParentFrame *parent, const wxString &title);
  virtual ~ChildFrame();

private:
  void OnClose(wxCloseEvent &event);

  wxTextCtrl *m_textCtrl;

  wxDECLARE_EVENT_TABLE();
};

#endif // CHILDFRAME_H
