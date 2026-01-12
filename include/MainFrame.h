/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * MainFrame.h - Main MDI parent frame window
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "MailboxTree.h"
#include <wx/aui/auibook.h>
#include <wx/splitter.h>
#include <wx/wx.h>

class wxAuiManager;
class wxAuiToolBar;

/**
 * Main application frame with notebook-based document interface
 */
class MainFrame : public wxFrame {
public:
  MainFrame(const wxString &title);
  virtual ~MainFrame();

private:
  // Menu creation
  void CreateMenuBar();

  // Event handlers - File menu
  void OnNewMessage(wxCommandEvent &event);
  void OnOpen(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);

  // Event handlers - Edit menu
  void OnUndo(wxCommandEvent &event);
  void OnRedo(wxCommandEvent &event);
  void OnCut(wxCommandEvent &event);
  void OnCopy(wxCommandEvent &event);
  void OnPaste(wxCommandEvent &event);
  void OnSelectAll(wxCommandEvent &event);
  void OnFind(wxCommandEvent &event);

  // Event handlers - Message menu
  void OnReply(wxCommandEvent &event);
  void OnReplyAll(wxCommandEvent &event);
  void OnForward(wxCommandEvent &event);
  void OnDelete(wxCommandEvent &event);

  // Handler for secondary toolbar tools extracted from sprite
  void OnSecondaryTool(wxCommandEvent &event);

  // Event handlers - Special menu
  void OnSettings(wxCommandEvent &event);
  void OnEmptyTrash(wxCommandEvent &event);

  // Event handlers - Window menu
  void OnCascade(wxCommandEvent &event);
  void OnTileHorizontal(wxCommandEvent &event);
  void OnTileVertical(wxCommandEvent &event);
  void OnCloseAll(wxCommandEvent &event);

  // Event handlers - Help menu
  void OnHelpContents(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnSize(wxSizeEvent &event);

  // Update UI handlers
  void OnUpdateNeedSelection(wxUpdateUIEvent &event);
  void OnUpdateNeedClipboard(wxUpdateUIEvent &event);

  // Components
  wxSplitterWindow *m_splitter;
  MailboxTree *m_mailboxTree;
  wxAuiNotebook *m_notebook;
  wxStatusBar *m_statusBar;
  // AUI manager and main toolbar
  wxAuiManager *m_auiManager = nullptr;
  wxAuiToolBar *m_toolBar = nullptr;

  wxDECLARE_EVENT_TABLE();
};

// Menu IDs
enum {
  // File menu
  ID_NEW_MESSAGE = wxID_HIGHEST + 1,
  ID_OPEN,

  // Edit menu
  ID_FIND,

  // Mailbox menu
  ID_NEW_MAILBOX,
  ID_RENAME_MAILBOX,
  ID_DELETE_MAILBOX,

  // Message menu
  ID_REPLY,
  ID_REPLY_ALL,
  ID_FORWARD,
  ID_REDIRECT,
  ID_DELETE_MESSAGE,

  // Transfer menu
  ID_TRANSFER,

  // Special menu
  ID_SETTINGS,
  ID_EMPTY_TRASH,
  ID_COMPACT_MAILBOXES,
  ID_FILTERS,

  // Tools menu
  ID_ADDRESS_BOOK,
  ID_PLUGINS,

  // Window menu
  ID_CASCADE,
  ID_TILE_HORIZONTAL,
  ID_TILE_VERTICAL,
  ID_CLOSE_ALL
  ,
  // Base for toolbar sprite-generated tool IDs
  ID_SEC_TOOL_BASE = wxID_HIGHEST + 1000
};

#endif // MAINFRAME_H
