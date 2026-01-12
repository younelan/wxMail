#ifndef DISPLAYPANEL_H
#define DISPLAYPANEL_H

#include "panels/SettingsPanel.h"

class DisplayPanel : public SettingsPanel
{
public:
    DisplayPanel(wxWindow* parent);
    ~DisplayPanel();
    
    void LoadSettings() override;
    void SaveSettings() override;

private:
    wxCheckBox* m_showToolbar;
    wxCheckBox* m_showTooltips;
    wxCheckBox* m_showCoolbar;
    wxCheckBox* m_showLargeButtons;
    wxCheckBox* m_showStatusBar;
    wxCheckBox* m_showCategoryIcons;
    wxCheckBox* m_mdiTaskbar;
    wxCheckBox* m_autoDownloadGraphics;
    wxCheckBox* m_displayImagesInline;
    wxCheckBox* m_displayEmoticons;
    wxCheckBox* m_minimizeToTray;
    wxCheckBox* m_alwaysShowTrayIcon;
};

#endif
