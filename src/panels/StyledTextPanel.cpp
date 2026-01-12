#include "panels/StyledTextPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

StyledTextPanel::StyledTextPanel(wxWindow* parent)
    : SettingsPanel(parent)
{
    wxXmlResource::Get()->LoadPanel(this, parent, "StyledTextPanel");
    
    m_showFormattingToolbar = XRCCTRL(*this, "m_showFormattingToolbar", wxCheckBox);
    m_sendBothPlainStyled = XRCCTRL(*this, "m_sendBothPlainStyled", wxRadioButton);
    m_sendStyledOnly = XRCCTRL(*this, "m_sendStyledOnly", wxRadioButton);
    m_sendPlainOnly = XRCCTRL(*this, "m_sendPlainOnly", wxRadioButton);
    m_askEachTime = XRCCTRL(*this, "m_askEachTime", wxCheckBox);
    m_sendStyledSig = XRCCTRL(*this, "m_sendStyledSig", wxCheckBox);
}

StyledTextPanel::~StyledTextPanel()
{
}

void StyledTextPanel::LoadSettings()
{
    wxFileConfig config("wxEudora", "", "eudora.ini");
    
    m_showFormattingToolbar->SetValue(config.ReadBool("/Settings/ShowStyledTextToolbar", true));
    
    bool sendBoth = config.ReadBool("/Settings/SendPlainAndStyled", true);
    bool sendStyled = config.ReadBool("/Settings/SendStyledOnly", false);
    
    if (sendBoth)
        m_sendBothPlainStyled->SetValue(true);
    else if (sendStyled)
        m_sendStyledOnly->SetValue(true);
    else
        m_sendPlainOnly->SetValue(true);
    
    m_askEachTime->SetValue(config.ReadBool("/Settings/WarnQueueStyledText", false));
    m_sendStyledSig->SetValue(config.ReadBool("/Settings/SendStyledSig", true));
}

void StyledTextPanel::SaveSettings()
{
    wxFileConfig config("wxEudora", "", "eudora.ini");
    
    config.Write("/Settings/ShowStyledTextToolbar", m_showFormattingToolbar->GetValue());
    config.Write("/Settings/SendPlainAndStyled", m_sendBothPlainStyled->GetValue());
    config.Write("/Settings/SendStyledOnly", m_sendStyledOnly->GetValue());
    config.Write("/Settings/WarnQueueStyledText", m_askEachTime->GetValue());
    config.Write("/Settings/SendStyledSig", m_sendStyledSig->GetValue());
    
    config.Flush();
}
