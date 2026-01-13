#pragma once

#include "ChildFrame.h"
#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>

class CNewMessageFrame : public ChildFrame {
public:
    explicit CNewMessageFrame(wxMDIParentFrame* parent);
    wxRichTextCtrl* GetBody() { return m_body; }
    wxTextCtrl* GetFrom() { return m_from; }
    wxTextCtrl* GetTo() { return m_to; }
    wxTextCtrl* GetSubject() { return m_subject; }

private:
    void OnSend(wxCommandEvent& evt);
    void OnAttach(wxCommandEvent& evt);
    void OnFormatToggle(wxCommandEvent& evt);

    wxRichTextCtrl* m_body = nullptr;
    wxToolBar* m_toolBar = nullptr;
    wxTextCtrl* m_from = nullptr;
    wxTextCtrl* m_to = nullptr;
    wxTextCtrl* m_subject = nullptr;
};
