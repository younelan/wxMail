#pragma once

#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/richtext/richtextctrl.h>

class CNewMessageDialog : public wxDialog {
public:
    explicit CNewMessageDialog(wxWindow* parent);
    wxRichTextCtrl* GetBody() { return m_body; }
private:
    void OnSend(wxCommandEvent& evt);
    void OnAttach(wxCommandEvent& evt);
    void OnFormatStub(wxCommandEvent& evt);

    wxRichTextCtrl* m_body = nullptr;
    wxToolBar* m_toolBar = nullptr;
};

// Kept for compatibility but the application now opens `CNewMessageFrame`.
