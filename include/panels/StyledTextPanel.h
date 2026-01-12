#ifndef STYLEDTEXTPANEL_H
#define STYLEDTEXTPANEL_H

#include "panels/SettingsPanel.h"

class StyledTextPanel : public SettingsPanel
{
public:
    StyledTextPanel(wxWindow* parent);
    ~StyledTextPanel();
    
    void LoadSettings() override;
    void SaveSettings() override;

private:
    wxCheckBox* m_showFormattingToolbar;
    wxRadioButton* m_sendBothPlainStyled;
    wxRadioButton* m_sendStyledOnly;
    wxRadioButton* m_sendPlainOnly;
    wxCheckBox* m_askEachTime;
    wxCheckBox* m_sendStyledSig;
};

#endif
