/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * ChildFrame.cpp - MDI child window implementation
 */

#include "ChildFrame.h"

wxBEGIN_EVENT_TABLE(ChildFrame, wxMDIChildFrame) EVT_CLOSE(ChildFrame::OnClose)
    wxEND_EVENT_TABLE()

        ChildFrame::ChildFrame(wxMDIParentFrame *parent, const wxString &title)
    : wxMDIChildFrame(parent, wxID_ANY, title, wxDefaultPosition,
                      wxSize(600, 400)) {
  // Create a text control for now (placeholder for message content)
  m_textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                              wxDefaultSize,
                              wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);

  // Set some sample content
  m_textCtrl->SetValue("This is a placeholder for mailbox/message content.\n\n"
                       "In a full implementation, this would display:\n"
                       "- Message list (for mailbox windows)\n"
                       "- Message content (for message windows)\n"
                       "- Composition interface (for new messages)\n");

  // Create status bar for this child window
  CreateStatusBar();
  SetStatusText("Ready");
}

ChildFrame::~ChildFrame() {}

void ChildFrame::OnClose(wxCloseEvent &event) {
  // TODO: Check if content needs to be saved
  event.Skip();
}
