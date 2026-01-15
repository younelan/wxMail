#include "NewMessageFrame.h"
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/toolbar.h>

CNewMessageFrame::CNewMessageFrame(wxMDIParentFrame* parent)
    : ChildFrame(parent, "New Message")
{
        // Build UI programmatically to ensure it's an MDI child with editable fields
        wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

        // Toolbar
        m_toolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                      wxTB_HORIZONTAL | wxTB_TEXT);
        // Use 32x32 toolbar icons from resources/png/
        m_toolBar->SetToolBitmapSize(wxSize(32, 32));
        wxBitmap bmpSend("resources/png/tbar32.png", wxBITMAP_TYPE_PNG);
        wxBitmap bmpAttach("resources/png/tbar32a.png", wxBITMAP_TYPE_PNG);
        wxBitmap bmpBold("resources/png/tbar32b.png", wxBITMAP_TYPE_PNG);
        // reuse existing bitmaps for italic/underline if separate icons not available
        wxBitmap bmpItalic = bmpBold;
        wxBitmap bmpUnder = bmpBold;

        m_toolBar->AddTool(XRCID("ID_NM_SEND"), "Send", bmpSend);
        m_toolBar->AddTool(XRCID("ID_NM_ATTACH"), "Attach", bmpAttach);
        m_toolBar->AddTool(XRCID("ID_NM_BOLD"), "B", bmpBold);
        m_toolBar->AddTool(XRCID("ID_NM_ITALIC"), "I", bmpItalic);
        m_toolBar->AddTool(XRCID("ID_NM_UNDER"), "U", bmpUnder);
        m_toolBar->Realize();
        Bind(wxEVT_TOOL, &CNewMessageFrame::OnSend, this, XRCID("ID_NM_SEND"));
        Bind(wxEVT_TOOL, &CNewMessageFrame::OnAttach, this, XRCID("ID_NM_ATTACH"));
        Bind(wxEVT_TOOL, &CNewMessageFrame::OnFormatToggle, this, XRCID("ID_NM_BOLD"));
        Bind(wxEVT_TOOL, &CNewMessageFrame::OnFormatToggle, this, XRCID("ID_NM_ITALIC"));
        Bind(wxEVT_TOOL, &CNewMessageFrame::OnFormatToggle, this, XRCID("ID_NM_UNDER"));

        topsizer->Add(m_toolBar, 0, wxEXPAND);

        // From/To/Subject fields
        wxFlexGridSizer* fg = new wxFlexGridSizer(3, 2, 4, 4);
        fg->AddGrowableCol(1, 1);
        fg->Add(new wxStaticText(this, wxID_ANY, "From:"), 0, wxALIGN_CENTER_VERTICAL);
        m_from = new wxTextCtrl(this, wxID_ANY);
        fg->Add(m_from, 1, wxEXPAND);
        fg->Add(new wxStaticText(this, wxID_ANY, "To:"), 0, wxALIGN_CENTER_VERTICAL);
        m_to = new wxTextCtrl(this, wxID_ANY);
        fg->Add(m_to, 1, wxEXPAND);
        fg->Add(new wxStaticText(this, wxID_ANY, "Subject:"), 0, wxALIGN_CENTER_VERTICAL);
        m_subject = new wxTextCtrl(this, wxID_ANY);
        fg->Add(m_subject, 1, wxEXPAND);

        topsizer->Add(fg, 0, wxEXPAND | wxALL, 6);

        // Rich text body
        m_body = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                                                                wxDefaultSize, wxTE_MULTILINE | wxVSCROLL | wxHSCROLL);
        topsizer->Add(m_body, 1, wxEXPAND | wxALL, 6);

        SetSizerAndFit(topsizer);
}

void CNewMessageFrame::OnSend(wxCommandEvent& WXUNUSED(evt)) {
    // placeholder: close the frame
    Close();
}

void CNewMessageFrame::OnAttach(wxCommandEvent& WXUNUSED(evt)) {
    wxFileDialog dlg(this, "Attach file", wxEmptyString, wxEmptyString, "All files|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK) {
        wxString path = dlg.GetPath();
        if (m_body) m_body->WriteText(path + "\n");
    }
}

void CNewMessageFrame::OnFormatToggle(wxCommandEvent& evt) {
    if (!m_body) return;
    int id = evt.GetId();
    wxTextAttrEx attr;
    if (id == XRCID("ID_NM_BOLD")) {
        attr.SetFontWeight(wxFONTWEIGHT_BOLD);
    } else if (id == XRCID("ID_NM_ITALIC")) {
        attr.SetFontStyle(wxFONTSTYLE_ITALIC);
    } else if (id == XRCID("ID_NM_UNDER")) {
        attr.SetFontUnderlined(true);
    }
    long from = m_body->GetSelectionRange().GetStart();
    long to = m_body->GetSelectionRange().GetEnd();
    if (from == to) {
        // toggle at caret: apply to next typing (simpler: show message)
        wxMessageBox("Select text to apply formatting.", "Format", wxOK | wxICON_INFORMATION, this);
    } else {
        m_body->SetStyle(from, to, attr);
    }
}
