#include "panels/DisplayPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

DisplayPanel::DisplayPanel(wxWindow* parent)
    : SettingsPanel(parent)
{
    wxXmlResource::Get()->LoadPanel(this, parent, "DisplayPanel");
    
    m_showToolbar = XRCCTRL(*this, "m_showToolbar", wxCheckBox);
    m_showTooltips = XRCCTRL(*this, "m_showTooltips", wxCheckBox);
    m_showCoolbar = XRCCTRL(*this, "m_showCoolbar", wxCheckBox);
    m_showLargeButtons = XRCCTRL(*this, "m_showLargeButtons", wxCheckBox);
    m_showStatusBar = XRCCTRL(*this, "m_showStatusBar", wxCheckBox);
    m_showCategoryIcons = XRCCTRL(*this, "m_showCategoryIcons", wxCheckBox);
    m_mdiTaskbar = XRCCTRL(*this, "m_mdiTaskbar", wxCheckBox);
    m_autoDownloadGraphics = XRCCTRL(*this, "m_autoDownloadGraphics", wxCheckBox);
    m_displayImagesInline = XRCCTRL(*this, "m_displayImagesInline", wxCheckBox);
    m_displayEmoticons = XRCCTRL(*this, "m_displayEmoticons", wxCheckBox);
    m_minimizeToTray = XRCCTRL(*this, "m_minimizeToTray", wxCheckBox);
    m_alwaysShowTrayIcon = XRCCTRL(*this, "m_alwaysShowTrayIcon", wxCheckBox);
}

DisplayPanel::~DisplayPanel()
{
}

void DisplayPanel::LoadSettings()
{
    wxFileConfig config("wxEudora", "", "eudora.ini");
    
    m_showToolbar->SetValue(config.ReadBool("/Settings/ShowToolbar", true));
    m_showTooltips->SetValue(config.ReadBool("/Settings/ShowTooltips", true));
    m_showCoolbar->SetValue(config.ReadBool("/Settings/ShowCoolbar", true));
    m_showLargeButtons->SetValue(config.ReadBool("/Settings/ShowLargeButtons", false));
    m_showStatusBar->SetValue(config.ReadBool("/Settings/ShowStatusBar", true));
    m_showCategoryIcons->SetValue(config.ReadBool("/Settings/ShowCategoryIcons", true));
    m_mdiTaskbar->SetValue(config.ReadBool("/Settings/MDITaskbar", true));
    m_autoDownloadGraphics->SetValue(config.ReadBool("/Settings/FetchInlineContent", false));
    m_displayImagesInline->SetValue(config.ReadBool("/Settings/DisplayImageAttachmentsInline", false));
    m_displayEmoticons->SetValue(config.ReadBool("/Settings/DisplayEmoticonAsPictures", false));
    m_minimizeToTray->SetValue(config.ReadBool("/Settings/ShowOnlyInTray", false));
    m_alwaysShowTrayIcon->SetValue(config.ReadBool("/Settings/AlwaysShowTrayIcon", false));
}

void DisplayPanel::SaveSettings()
{
    wxFileConfig config("wxEudora", "", "eudora.ini");
    
    config.Write("/Settings/ShowToolbar", m_showToolbar->GetValue());
    config.Write("/Settings/ShowTooltips", m_showTooltips->GetValue());
    config.Write("/Settings/ShowCoolbar", m_showCoolbar->GetValue());
    config.Write("/Settings/ShowLargeButtons", m_showLargeButtons->GetValue());
    config.Write("/Settings/ShowStatusBar", m_showStatusBar->GetValue());
    config.Write("/Settings/ShowCategoryIcons", m_showCategoryIcons->GetValue());
    config.Write("/Settings/MDITaskbar", m_mdiTaskbar->GetValue());
    config.Write("/Settings/FetchInlineContent", m_autoDownloadGraphics->GetValue());
    config.Write("/Settings/DisplayImageAttachmentsInline", m_displayImagesInline->GetValue());
    config.Write("/Settings/DisplayEmoticonAsPictures", m_displayEmoticons->GetValue());
    config.Write("/Settings/ShowOnlyInTray", m_minimizeToTray->GetValue());
    config.Write("/Settings/AlwaysShowTrayIcon", m_alwaysShowTrayIcon->GetValue());
    
    config.Flush();
}
