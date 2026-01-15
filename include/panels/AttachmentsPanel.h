/**
 * wxMail - Settings Panel for Attachments
 * Ported from Eudora 7.1 IDD_SETTINGS_ATTACH
 */

#ifndef ATTACHMENTSPANEL_H
#define ATTACHMENTSPANEL_H

#include "panels/SettingsPanel.h"

class AttachmentsPanel : public SettingsPanel {
public:
  AttachmentsPanel(wxWindow *parent);
  virtual ~AttachmentsPanel();

  virtual void LoadSettings() override;
  virtual void SaveSettings() override;

private:
  wxRadioButton *m_encodeMime;
  wxRadioButton *m_encodeBinhex;
  wxRadioButton *m_encodeUuencode;
  wxCheckBox *m_putTextInBody;
  wxCheckBox *m_digestAsMailbox;
  wxCheckBox *m_deleteOnTrash;
  wxRadioButton *m_autoDeleteNever;
  wxRadioButton *m_autoDeleteSend;
  wxRadioButton *m_autoDeleteTrash;
};

#endif // ATTACHMENTSPANEL_H
