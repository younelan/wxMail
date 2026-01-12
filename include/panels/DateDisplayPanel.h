#ifndef DATEDISPLAYPANEL_H
#define DATEDISPLAYPANEL_H

#include "panels/SettingsPanel.h"

class DateDisplayPanel : public SettingsPanel
{
public:
    DateDisplayPanel(wxWindow* parent);
    ~DateDisplayPanel();
    
    void LoadSettings() override;
    void SaveSettings() override;

private:
    wxRadioButton* m_localTimezone;
    wxRadioButton* m_senderTimezone;
    wxRadioButton* m_fixedFormat;
    wxRadioButton* m_ageSensitive;
    wxTextCtrl* m_fixedDateFormat;
    wxTextCtrl* m_recentDateFormat;
    wxTextCtrl* m_oldDateHours;
    wxTextCtrl* m_oldDateFormat;
    wxTextCtrl* m_ancientDateHours;
    wxTextCtrl* m_ancientDateFormat;
};

#endif
