/**
 * wxEudora - Settings Panel for Replying
 * Ported from Eudora 7.1 IDD_SETTINGS_REPLYING
 */

#ifndef REPLYINGPANEL_H
#define REPLYINGPANEL_H

#include "panels/SettingsPanel.h"

class ReplyingPanel : public SettingsPanel {
public:
  ReplyingPanel(wxWindow *parent);
  virtual ~ReplyingPanel();

  virtual void LoadSettings() override;
  virtual void SaveSettings() override;

private:
  wxCheckBox *m_replyToAll;
  wxCheckBox *m_copyPriority;
  wxCheckBox *m_autoFcc;
  wxCheckBox *m_includeSig;
  wxCheckBox *m_quoteSelection;
  wxCheckBox *m_multipleReplies;
  wxCheckBox *m_includeSelf;
  wxCheckBox *m_putToInCc;
};

#endif // REPLYINGPANEL_H
