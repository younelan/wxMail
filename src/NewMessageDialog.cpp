#include "NewMessageDialog.h"
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>

CNewMessageDialog::CNewMessageDialog(wxWindow* parent)
  : wxDialog()
{
    // Load the dialog from XRC into this object
    wxXmlResource::Get()->LoadDialog(this, parent, "NewMessageDialog");

    // The XRC may not have a richtext handler available, so we create the
    // wxRichTextCtrl at runtime inside a placeholder panel called
    // "body_placeholder".
    m_toolBar = XRCCTRL(*this, "NewMsgToolBar", wxToolBar);
    wxPanel* bodyPlace = XRCCTRL(*this, "body_placeholder", wxPanel);
    if (bodyPlace) {
        wxBoxSizer* s = new wxBoxSizer(wxVERTICAL);
        m_body = new wxRichTextCtrl(bodyPlace, wxID_ANY, wxEmptyString,
                                    wxDefaultPosition, wxDefaultSize,
                                    wxTE_MULTILINE | wxVSCROLL | wxHSCROLL);
        s->Add(m_body, 1, wxEXPAND);
        bodyPlace->SetSizer(s);
    } else {
        m_body = nullptr;
    }

    if (m_toolBar) {
        m_toolBar->Bind(wxEVT_TOOL, &CNewMessageDialog::OnSend, this, XRCID("ID_NM_SEND"));
        m_toolBar->Bind(wxEVT_TOOL, &CNewMessageDialog::OnAttach, this, XRCID("ID_NM_ATTACH"));
        m_toolBar->Bind(wxEVT_TOOL, &CNewMessageDialog::OnFormatStub, this, XRCID("ID_NM_BOLD"));
        m_toolBar->Bind(wxEVT_TOOL, &CNewMessageDialog::OnFormatStub, this, XRCID("ID_NM_ITALIC"));
        m_toolBar->Bind(wxEVT_TOOL, &CNewMessageDialog::OnFormatStub, this, XRCID("ID_NM_UNDER"));
    }
}

void CNewMessageDialog::OnSend(wxCommandEvent& WXUNUSED(evt)) {
    // Simple behavior: close dialog with OK — actual send logic happens elsewhere
    EndModal(wxID_OK);
}

void CNewMessageDialog::OnAttach(wxCommandEvent& WXUNUSED(evt)) {
    wxFileDialog dlg(this, "Attach file", wxEmptyString, wxEmptyString, "All files|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK) {
        wxString path = dlg.GetPath();
        if (m_body) {
            m_body->WriteText(path + "\n");
        }
    }
}

void CNewMessageDialog::OnFormatStub(wxCommandEvent& WXUNUSED(evt)) {
    wxMessageBox("Formatting shortcuts not implemented yet.", "Info", wxOK | wxICON_INFORMATION, this);
}
