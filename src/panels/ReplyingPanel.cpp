/**
 * wxEudora - Settings Panel for Replying
 * Ported from Eudora 7.1 IDD_SETTINGS_REPLYING
 */

#include "panels/ReplyingPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

ReplyingPanel::ReplyingPanel(wxWindow *parent) : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "ReplyingPanel");

  m_replyToAll = XRCCTRL(*this, "m_replyToAll", wxCheckBox);
  m_copyPriority = XRCCTRL(*this, "m_copyPriority", wxCheckBox);
  m_autoFcc = XRCCTRL(*this, "m_autoFcc", wxCheckBox);
  m_includeSig = XRCCTRL(*this, "m_includeSig", wxCheckBox);
  m_quoteSelection = XRCCTRL(*this, "m_quoteSelection", wxCheckBox);
  m_multipleReplies = XRCCTRL(*this, "m_multipleReplies", wxCheckBox);
  m_includeSelf = XRCCTRL(*this, "m_includeSelf", wxCheckBox);
  m_putToInCc = XRCCTRL(*this, "m_putToInCc", wxCheckBox);
}

ReplyingPanel::~ReplyingPanel() {}

void ReplyingPanel::LoadSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");

  m_replyToAll->SetValue(config.ReadBool("/Settings/ReplyToAll", false));
  m_copyPriority->SetValue(config.ReadBool("/Settings/CopyPriority", false));
  m_autoFcc->SetValue(config.ReadBool("/Settings/ReplyAutoFcc", false));
  m_includeSig->SetValue(config.ReadBool("/Settings/IncludeSigReply", false));
  m_quoteSelection->SetValue(
      config.ReadBool("/Settings/ReplySelection", false));
  m_multipleReplies->SetValue(
      config.ReadBool("/Settings/MultRepliesForMultSel", false));
  m_includeSelf->SetValue(config.ReadBool("/Settings/IncludeSelf", false));
  m_putToInCc->SetValue(config.ReadBool("/Settings/ReplyToToCc", false));
}

void ReplyingPanel::SaveSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");

  config.Write("/Settings/ReplyToAll", m_replyToAll->GetValue());
  config.Write("/Settings/CopyPriority", m_copyPriority->GetValue());
  config.Write("/Settings/ReplyAutoFcc", m_autoFcc->GetValue());
  config.Write("/Settings/IncludeSigReply", m_includeSig->GetValue());
  config.Write("/Settings/ReplySelection", m_quoteSelection->GetValue());
  config.Write("/Settings/MultRepliesForMultSel",
               m_multipleReplies->GetValue());
  config.Write("/Settings/IncludeSelf", m_includeSelf->GetValue());
  config.Write("/Settings/ReplyToToCc", m_putToInCc->GetValue());

  config.Flush();
}
