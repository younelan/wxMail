/**
 * wxEudora - Settings Panel for Attachments
 * Ported from Eudora 7.1 IDD_SETTINGS_ATTACH
 */

#include "panels/AttachmentsPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

AttachmentsPanel::AttachmentsPanel(wxWindow *parent) : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "AttachmentsPanel");

  m_encodeMime = XRCCTRL(*this, "m_encodeMime", wxRadioButton);
  m_encodeBinhex = XRCCTRL(*this, "m_encodeBinhex", wxRadioButton);
  m_encodeUuencode = XRCCTRL(*this, "m_encodeUuencode", wxRadioButton);
  m_putTextInBody = XRCCTRL(*this, "m_putTextInBody", wxCheckBox);
  m_digestAsMailbox = XRCCTRL(*this, "m_digestAsMailbox", wxCheckBox);
  m_deleteOnTrash = XRCCTRL(*this, "m_deleteOnTrash", wxCheckBox);
  m_autoDeleteNever = XRCCTRL(*this, "m_autoDeleteNever", wxRadioButton);
  m_autoDeleteSend = XRCCTRL(*this, "m_autoDeleteSend", wxRadioButton);
  m_autoDeleteTrash = XRCCTRL(*this, "m_autoDeleteTrash", wxRadioButton);
}

AttachmentsPanel::~AttachmentsPanel() {}

void AttachmentsPanel::LoadSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");

  long encoding = config.ReadLong("/Settings/SendEncoding", 0);
  m_encodeMime->SetValue(encoding == 0);
  m_encodeBinhex->SetValue(encoding == 1);
  m_encodeUuencode->SetValue(encoding == 2);

  m_putTextInBody->SetValue(config.ReadBool("/Settings/AntiTextAsDoc", false));
  m_digestAsMailbox->SetValue(
      config.ReadBool("/Settings/ExplodeDigest", false));
  m_deleteOnTrash->SetValue(config.ReadBool("/Settings/TidyAttach", false));

  long autoDelete = config.ReadLong("/Settings/AutoAttachedDelete", 0);
  m_autoDeleteNever->SetValue(autoDelete == 0);
  m_autoDeleteSend->SetValue(autoDelete == 1);
  m_autoDeleteTrash->SetValue(autoDelete == 2);
}

void AttachmentsPanel::SaveSettings() {
  wxFileConfig config("wxEudora", "", "eudora.ini");

  long encoding =
      m_encodeMime->GetValue() ? 0 : (m_encodeBinhex->GetValue() ? 1 : 2);
  config.Write("/Settings/SendEncoding", encoding);

  config.Write("/Settings/AntiTextAsDoc", m_putTextInBody->GetValue());
  config.Write("/Settings/ExplodeDigest", m_digestAsMailbox->GetValue());
  config.Write("/Settings/TidyAttach", m_deleteOnTrash->GetValue());

  long autoDelete = m_autoDeleteNever->GetValue()
                        ? 0
                        : (m_autoDeleteSend->GetValue() ? 1 : 2);
  config.Write("/Settings/AutoAttachedDelete", autoDelete);

  config.Flush();
}
