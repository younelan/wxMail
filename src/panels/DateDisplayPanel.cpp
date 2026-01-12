#include "panels/DateDisplayPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

DateDisplayPanel::DateDisplayPanel(wxWindow* parent)
    : SettingsPanel(parent)
{
    wxXmlResource::Get()->LoadPanel(this, parent, "DateDisplayPanel");
    
    m_localTimezone = XRCCTRL(*this, "m_localTimezone", wxRadioButton);
    m_senderTimezone = XRCCTRL(*this, "m_senderTimezone", wxRadioButton);
    m_fixedFormat = XRCCTRL(*this, "m_fixedFormat", wxRadioButton);
    m_ageSensitive = XRCCTRL(*this, "m_ageSensitive", wxRadioButton);
    m_fixedDateFormat = XRCCTRL(*this, "m_fixedDateFormat", wxTextCtrl);
    m_recentDateFormat = XRCCTRL(*this, "m_recentDateFormat", wxTextCtrl);
    m_oldDateHours = XRCCTRL(*this, "m_oldDateHours", wxTextCtrl);
    m_oldDateFormat = XRCCTRL(*this, "m_oldDateFormat", wxTextCtrl);
    m_ancientDateHours = XRCCTRL(*this, "m_ancientDateHours", wxTextCtrl);
    m_ancientDateFormat = XRCCTRL(*this, "m_ancientDateFormat", wxTextCtrl);
}

DateDisplayPanel::~DateDisplayPanel()
{
}

void DateDisplayPanel::LoadSettings()
{
    wxFileConfig config("wxEudora", "", "eudora.ini");
    
    m_localTimezone->SetValue(config.ReadBool("/Settings/LocalTimeDisplay", true));
    m_senderTimezone->SetValue(config.ReadBool("/Settings/SenderTimeDisplay", false));
    m_fixedFormat->SetValue(config.ReadBool("/Settings/FixedDateDisplay", true));
    m_ageSensitive->SetValue(config.ReadBool("/Settings/AgeSensitiveDateDisplay", false));
    m_fixedDateFormat->SetValue(config.Read("/Settings/FixedDateFormat", "%1 %2"));
    m_recentDateFormat->SetValue(config.Read("/Settings/RecentDateFormat", "%1"));
    m_oldDateHours->SetValue(wxString::Format("%ld", config.ReadLong("/Settings/OldDateHours", 24)));
    m_oldDateFormat->SetValue(config.Read("/Settings/OldDateFormat", "%2"));
    m_ancientDateHours->SetValue(wxString::Format("%ld", config.ReadLong("/Settings/AncientDateHours", 168)));
    m_ancientDateFormat->SetValue(config.Read("/Settings/AncientDateFormat", "%2"));
}

void DateDisplayPanel::SaveSettings()
{
    wxFileConfig config("wxEudora", "", "eudora.ini");
    
    config.Write("/Settings/LocalTimeDisplay", m_localTimezone->GetValue());
    config.Write("/Settings/SenderTimeDisplay", m_senderTimezone->GetValue());
    config.Write("/Settings/FixedDateDisplay", m_fixedFormat->GetValue());
    config.Write("/Settings/AgeSensitiveDateDisplay", m_ageSensitive->GetValue());
    config.Write("/Settings/FixedDateFormat", m_fixedDateFormat->GetValue());
    config.Write("/Settings/RecentDateFormat", m_recentDateFormat->GetValue());
    
    long oldHours, ancientHours;
    if (m_oldDateHours->GetValue().ToLong(&oldHours))
        config.Write("/Settings/OldDateHours", oldHours);
    if (m_ancientDateHours->GetValue().ToLong(&ancientHours))
        config.Write("/Settings/AncientDateHours", ancientHours);
    
    config.Write("/Settings/OldDateFormat", m_oldDateFormat->GetValue());
    config.Write("/Settings/AncientDateFormat", m_ancientDateFormat->GetValue());
    
    config.Flush();
}
