#include "panels/NetworkPanel.h"
#include <wx/fileconf.h>
#include <wx/xrc/xmlres.h>

NetworkPanel::NetworkPanel(wxWindow *parent) : SettingsPanel(parent) {
  wxXmlResource::Get()->LoadPanel(this, parent, "NetworkPanel");

  m_networkOpenTimeout = XRCCTRL(*this, "m_networkOpenTimeout", wxTextCtrl);
  m_networkTimeout = XRCCTRL(*this, "m_networkTimeout", wxTextCtrl);
  m_networkBufferSize = XRCCTRL(*this, "m_networkBufferSize", wxTextCtrl);
  m_cacheNetworkInfo = XRCCTRL(*this, "m_cacheNetworkInfo", wxCheckBox);
  m_unloadWinsock = XRCCTRL(*this, "m_unloadWinsock", wxCheckBox);
}

NetworkPanel::~NetworkPanel() {}

void NetworkPanel::LoadSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");

  m_networkOpenTimeout->SetValue(wxString::Format(
      "%ld", config.ReadLong("/Settings/NetworkOpenTimeout", 60)));
  m_networkTimeout->SetValue(
      wxString::Format("%ld", config.ReadLong("/Settings/NetworkTimeout", 60)));
  m_networkBufferSize->SetValue(wxString::Format(
      "%ld", config.ReadLong("/Settings/NetworkBufferSize", 4096)));
  m_cacheNetworkInfo->SetValue(
      config.ReadBool("/Settings/NetworkCaching", true));
  m_unloadWinsock->SetValue(
      config.ReadBool("/Settings/NetImmediateClose", false));
}

void NetworkPanel::SaveSettings() {
  wxFileConfig config("wxMail", "", "eudora.ini");

  long openTimeout, timeout, bufferSize;
  if (m_networkOpenTimeout->GetValue().ToLong(&openTimeout))
    config.Write("/Settings/NetworkOpenTimeout", openTimeout);
  if (m_networkTimeout->GetValue().ToLong(&timeout))
    config.Write("/Settings/NetworkTimeout", timeout);
  if (m_networkBufferSize->GetValue().ToLong(&bufferSize))
    config.Write("/Settings/NetworkBufferSize", bufferSize);

  config.Write("/Settings/NetworkCaching", m_cacheNetworkInfo->GetValue());
  config.Write("/Settings/NetImmediateClose", m_unloadWinsock->GetValue());

  config.Flush();
}
