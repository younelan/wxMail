#ifndef NETWORKPANEL_H
#define NETWORKPANEL_H

#include "panels/SettingsPanel.h"

class NetworkPanel : public SettingsPanel {
public:
  NetworkPanel(wxWindow *parent);
  ~NetworkPanel();

  void LoadSettings() override;
  void SaveSettings() override;

private:
  wxTextCtrl *m_networkOpenTimeout;
  wxTextCtrl *m_networkTimeout;
  wxTextCtrl *m_networkBufferSize;
  wxCheckBox *m_cacheNetworkInfo;
  wxCheckBox *m_unloadWinsock;
};

#endif
