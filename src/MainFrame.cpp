/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * MainFrame.cpp - Main MDI parent frame implementation
 */

#include "MainFrame.h"
#include "ChildFrame.h"
#include <wx/artprov.h>
#include <wx/splitter.h>
#include <wx/toolbar.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    // File menu
    EVT_MENU(ID_NEW_MESSAGE, MainFrame::OnNewMessage)
        EVT_MENU(ID_OPEN, MainFrame::OnOpen)
            EVT_MENU(wxID_EXIT, MainFrame::OnExit)

    // Edit menu
    EVT_MENU(wxID_UNDO, MainFrame::OnUndo)
        EVT_MENU(wxID_REDO, MainFrame::OnRedo)
            EVT_MENU(wxID_CUT, MainFrame::OnCut)
                EVT_MENU(wxID_COPY, MainFrame::OnCopy)
                    EVT_MENU(wxID_PASTE, MainFrame::OnPaste)
                        EVT_MENU(wxID_SELECTALL, MainFrame::OnSelectAll)
                            EVT_MENU(ID_FIND, MainFrame::OnFind)

    // Message menu
    EVT_MENU(ID_REPLY, MainFrame::OnReply)
        EVT_MENU(ID_REPLY_ALL, MainFrame::OnReplyAll)
            EVT_MENU(ID_FORWARD, MainFrame::OnForward)
                EVT_MENU(ID_DELETE_MESSAGE, MainFrame::OnDelete)

    // Special menu
    EVT_MENU(ID_SETTINGS, MainFrame::OnSettings)
        EVT_MENU(ID_EMPTY_TRASH, MainFrame::OnEmptyTrash)

    // Window menu
    EVT_MENU(ID_CASCADE, MainFrame::OnCascade)
        EVT_MENU(ID_TILE_HORIZONTAL, MainFrame::OnTileHorizontal)
            EVT_MENU(ID_TILE_VERTICAL, MainFrame::OnTileVertical)
                EVT_MENU(ID_CLOSE_ALL, MainFrame::OnCloseAll)

    // Help menu
    EVT_MENU(wxID_HELP, MainFrame::OnHelpContents)
        EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)

    // Update UI
    EVT_UPDATE_UI(wxID_CUT, MainFrame::OnUpdateNeedSelection)
        EVT_UPDATE_UI(wxID_COPY, MainFrame::OnUpdateNeedSelection)
            EVT_UPDATE_UI(wxID_PASTE, MainFrame::OnUpdateNeedClipboard)
                wxEND_EVENT_TABLE()

                    MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 800)),
      m_splitter(nullptr), m_mailboxTree(nullptr), m_notebook(nullptr),
      m_statusBar(nullptr) {
  // Create menu bar
  CreateMenuBar();

  // Create toolbar
  wxToolBar *toolbar = CreateToolBar(wxTB_HORIZONTAL | wxTB_FLAT | wxTB_TEXT);
  toolbar->AddTool(ID_NEW_MESSAGE, "New",
                   wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR),
                   "New Message");
  toolbar->AddTool(ID_REPLY, "Reply",
                   wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR),
                   "Reply");
  toolbar->AddTool(ID_FORWARD, "Forward",
                   wxArtProvider::GetBitmap(wxART_REDO, wxART_TOOLBAR),
                   "Forward");
  toolbar->AddSeparator();
  toolbar->AddTool(ID_DELETE_MESSAGE, "Delete",
                   wxArtProvider::GetBitmap(wxART_DELETE, wxART_TOOLBAR),
                   "Delete");
  toolbar->AddSeparator();
  toolbar->AddTool(wxID_PRINT, "Print",
                   wxArtProvider::GetBitmap(wxART_PRINT, wxART_TOOLBAR),
                   "Print");
  toolbar->Realize();

  // Create status bar
  m_statusBar = CreateStatusBar(3);
  int widths[] = {-1, 150, 100};
  m_statusBar->SetStatusWidths(3, widths);
  SetStatusText("Ready", 0);
  SetStatusText("No messages", 1);
  SetStatusText("Offline", 2);

  // Create splitter window - THIS is the main content area
  m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition,
                                    wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE);

  // Create mailbox tree on the LEFT
  m_mailboxTree = new MailboxTree(m_splitter, wxID_ANY);

  // Create notebook on the RIGHT for document tabs
  m_notebook =
      new wxAuiNotebook(m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                        wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE |
                            wxAUI_NB_CLOSE_ON_ACTIVE_TAB);

  // Add a welcome page to the notebook
  wxPanel *welcomePanel = new wxPanel(m_notebook, wxID_ANY);
  welcomePanel->SetBackgroundColour(*wxWHITE);
  wxBoxSizer *welcomeSizer = new wxBoxSizer(wxVERTICAL);
  wxStaticText *welcomeText =
      new wxStaticText(welcomePanel, wxID_ANY,
                       "Welcome to wxEudora\n\n"
                       "• Use File → New Message to compose\n"
                       "• Click a mailbox to view messages\n"
                       "• Double-click a message to open it\n",
                       wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
  wxFont font = welcomeText->GetFont();
  font.SetPointSize(12);
  welcomeText->SetFont(font);
  welcomeSizer->AddStretchSpacer();
  welcomeSizer->Add(welcomeText, 0, wxALL | wxALIGN_CENTER, 20);
  welcomeSizer->AddStretchSpacer();
  welcomePanel->SetSizer(welcomeSizer);
  m_notebook->AddPage(welcomePanel, "Welcome", true);

  // Split vertically: tree on left (250px), notebook on right
  m_splitter->SplitVertically(m_mailboxTree, m_notebook, 250);
  m_splitter->SetMinimumPaneSize(150);

  // Center the window
  Centre();
}

MainFrame::~MainFrame() {}

void MainFrame::CreateMenuBar() {
  wxMenuBar *menuBar = new wxMenuBar;

  // File menu
  wxMenu *fileMenu = new wxMenu;
  fileMenu->Append(ID_NEW_MESSAGE, "&New Message\tCtrl-N",
                   "Create a new message");
  fileMenu->Append(ID_OPEN, "&Open...\tCtrl-O", "Open a file");
  fileMenu->AppendSeparator();
  fileMenu->Append(wxID_SAVE, "&Save\tCtrl-S", "Save current document");
  fileMenu->Append(wxID_SAVEAS, "Save &As...",
                   "Save current document with a new name");
  fileMenu->AppendSeparator();
  fileMenu->Append(wxID_PRINT, "&Print...\tCtrl-P", "Print current document");
  fileMenu->AppendSeparator();
  fileMenu->Append(wxID_EXIT, "E&xit\tAlt-F4", "Exit wxEudora");
  menuBar->Append(fileMenu, "&File");

  // Edit menu
  wxMenu *editMenu = new wxMenu;
  editMenu->Append(wxID_UNDO, "&Undo\tCtrl-Z", "Undo last action");
  editMenu->Append(wxID_REDO, "&Redo\tCtrl-Y", "Redo last undone action");
  editMenu->AppendSeparator();
  editMenu->Append(wxID_CUT, "Cu&t\tCtrl-X", "Cut selection to clipboard");
  editMenu->Append(wxID_COPY, "&Copy\tCtrl-C", "Copy selection to clipboard");
  editMenu->Append(wxID_PASTE, "&Paste\tCtrl-V", "Paste from clipboard");
  editMenu->Append(wxID_SELECTALL, "Select &All\tCtrl-A", "Select all text");
  editMenu->AppendSeparator();
  editMenu->Append(ID_FIND, "&Find...\tCtrl-F", "Find text");
  menuBar->Append(editMenu, "&Edit");

  // Mailbox menu
  wxMenu *mailboxMenu = new wxMenu;
  mailboxMenu->Append(ID_NEW_MAILBOX, "&New...", "Create a new mailbox");
  mailboxMenu->Append(ID_RENAME_MAILBOX, "&Rename...",
                      "Rename selected mailbox");
  mailboxMenu->Append(ID_DELETE_MAILBOX, "&Delete", "Delete selected mailbox");
  mailboxMenu->AppendSeparator();
  mailboxMenu->Append(wxID_ANY, "&In", "Open In mailbox");
  mailboxMenu->Append(wxID_ANY, "&Out", "Open Out mailbox");
  mailboxMenu->Append(wxID_ANY, "&Trash", "Open Trash mailbox");
  mailboxMenu->Append(wxID_ANY, "&Junk", "Open Junk mailbox");
  menuBar->Append(mailboxMenu, "&Mailbox");

  // Message menu
  wxMenu *messageMenu = new wxMenu;
  messageMenu->Append(ID_NEW_MESSAGE, "&New Message\tCtrl-N",
                      "Create a new message");
  messageMenu->AppendSeparator();
  messageMenu->Append(ID_REPLY, "&Reply\tCtrl-R", "Reply to sender");
  messageMenu->Append(ID_REPLY_ALL, "Reply to &All\tCtrl-Shift-R",
                      "Reply to all recipients");
  messageMenu->Append(ID_FORWARD, "&Forward\tCtrl-J", "Forward message");
  messageMenu->Append(ID_REDIRECT, "Re&direct", "Redirect message");
  messageMenu->AppendSeparator();
  messageMenu->Append(ID_DELETE_MESSAGE, "&Delete\tCtrl-D",
                      "Delete selected messages");
  messageMenu->AppendSeparator();
  messageMenu->Append(wxID_ANY, "&Send Immediately", "Send message now");
  menuBar->Append(messageMenu, "&Message");

  // Transfer menu
  wxMenu *transferMenu = new wxMenu;
  transferMenu->Append(ID_TRANSFER, "&Transfer",
                       "Transfer messages to another mailbox");
  transferMenu->AppendSeparator();
  transferMenu->Append(wxID_ANY, "&In", "Transfer to In");
  transferMenu->Append(wxID_ANY, "&Out", "Transfer to Out");
  transferMenu->Append(wxID_ANY, "&Trash", "Transfer to Trash");
  transferMenu->Append(wxID_ANY, "&Junk", "Transfer to Junk");
  menuBar->Append(transferMenu, "&Transfer");

  // Special menu
  wxMenu *specialMenu = new wxMenu;
  specialMenu->Append(ID_SETTINGS, "&Settings...", "Configure wxEudora");
  specialMenu->AppendSeparator();
  specialMenu->Append(ID_FILTERS, "&Filters...", "Manage mail filters");
  specialMenu->Append(ID_EMPTY_TRASH, "&Empty Trash",
                      "Permanently delete trash contents");
  specialMenu->Append(ID_COMPACT_MAILBOXES, "&Compact Mailboxes",
                      "Reclaim disk space");
  specialMenu->AppendSeparator();
  specialMenu->Append(wxID_ANY, "&Check Mail\tCtrl-M", "Check for new mail");
  menuBar->Append(specialMenu, "&Special");

  // Tools menu
  wxMenu *toolsMenu = new wxMenu;
  toolsMenu->Append(ID_ADDRESS_BOOK, "&Address Book", "Open address book");
  toolsMenu->Append(wxID_ANY, "&Nicknames", "Manage nicknames");
  toolsMenu->AppendSeparator();
  toolsMenu->Append(ID_PLUGINS, "&Plugins...", "Manage plugins");
  menuBar->Append(toolsMenu, "&Tools");

  // Window menu
  wxMenu *windowMenu = new wxMenu;
  windowMenu->Append(ID_CASCADE, "&Cascade", "Cascade all windows");
  windowMenu->Append(ID_TILE_HORIZONTAL, "Tile &Horizontally",
                     "Tile windows horizontally");
  windowMenu->Append(ID_TILE_VERTICAL, "Tile &Vertically",
                     "Tile windows vertically");
  windowMenu->AppendSeparator();
  windowMenu->Append(ID_CLOSE_ALL, "Close &All", "Close all windows");
  menuBar->Append(windowMenu, "&Window");

  // Help menu
  wxMenu *helpMenu = new wxMenu;
  helpMenu->Append(wxID_HELP, "&Help Contents\tF1", "Show help contents");
  helpMenu->AppendSeparator();
  helpMenu->Append(wxID_ABOUT, "&About wxEudora", "About this application");
  menuBar->Append(helpMenu, "&Help");

  SetMenuBar(menuBar);
}

// File menu handlers
void MainFrame::OnNewMessage(wxCommandEvent &WXUNUSED(event)) {
  // Create a new composition window as a notebook tab
  wxPanel *composePanel = new wxPanel(m_notebook, wxID_ANY);
  composePanel->SetBackgroundColour(*wxWHITE);

  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  wxTextCtrl *textCtrl =
      new wxTextCtrl(composePanel, wxID_ANY, "Compose your message here...",
                     wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
  sizer->Add(textCtrl, 1, wxEXPAND | wxALL, 5);
  composePanel->SetSizer(sizer);

  m_notebook->AddPage(composePanel, "New Message", true);
}

void MainFrame::OnOpen(wxCommandEvent &WXUNUSED(event)) {
  wxFileDialog dialog(this, "Open file", "", "", "All files (*.*)|*.*",
                      wxFD_OPEN | wxFD_FILE_MUST_EXIST);

  if (dialog.ShowModal() == wxID_OK) {
    wxString path = dialog.GetPath();
    SetStatusText("Opened: " + path, 0);
  }
}

void MainFrame::OnExit(wxCommandEvent &WXUNUSED(event)) { Close(true); }

// Edit menu handlers
void MainFrame::OnUndo(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Undo - Not yet implemented", 0);
}

void MainFrame::OnRedo(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Redo - Not yet implemented", 0);
}

void MainFrame::OnCut(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Cut - Not yet implemented", 0);
}

void MainFrame::OnCopy(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Copy - Not yet implemented", 0);
}

void MainFrame::OnPaste(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Paste - Not yet implemented", 0);
}

void MainFrame::OnSelectAll(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Select All - Not yet implemented", 0);
}

void MainFrame::OnFind(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Find - Not yet implemented", 0);
}

// Message menu handlers
void MainFrame::OnReply(wxCommandEvent &WXUNUSED(event)) {
  wxPanel *replyPanel = new wxPanel(m_notebook, wxID_ANY);
  replyPanel->SetBackgroundColour(*wxWHITE);
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  wxTextCtrl *textCtrl =
      new wxTextCtrl(replyPanel, wxID_ANY, "Reply message...",
                     wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
  sizer->Add(textCtrl, 1, wxEXPAND | wxALL, 5);
  replyPanel->SetSizer(sizer);
  m_notebook->AddPage(replyPanel, "Reply", true);
}

void MainFrame::OnReplyAll(wxCommandEvent &WXUNUSED(event)) {
  wxPanel *replyPanel = new wxPanel(m_notebook, wxID_ANY);
  replyPanel->SetBackgroundColour(*wxWHITE);
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  wxTextCtrl *textCtrl =
      new wxTextCtrl(replyPanel, wxID_ANY, "Reply to all...", wxDefaultPosition,
                     wxDefaultSize, wxTE_MULTILINE);
  sizer->Add(textCtrl, 1, wxEXPAND | wxALL, 5);
  replyPanel->SetSizer(sizer);
  m_notebook->AddPage(replyPanel, "Reply to All", true);
}

void MainFrame::OnForward(wxCommandEvent &WXUNUSED(event)) {
  wxPanel *forwardPanel = new wxPanel(m_notebook, wxID_ANY);
  forwardPanel->SetBackgroundColour(*wxWHITE);
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  wxTextCtrl *textCtrl =
      new wxTextCtrl(forwardPanel, wxID_ANY, "Forward message...",
                     wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
  sizer->Add(textCtrl, 1, wxEXPAND | wxALL, 5);
  forwardPanel->SetSizer(sizer);
  m_notebook->AddPage(forwardPanel, "Forward", true);
}

void MainFrame::OnDelete(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Delete - Not yet implemented", 0);
}

// Special menu handlers
void MainFrame::OnSettings(wxCommandEvent &WXUNUSED(event)) {
  wxMessageBox("Settings dialog would appear here.", "Settings",
               wxOK | wxICON_INFORMATION, this);
}

void MainFrame::OnEmptyTrash(wxCommandEvent &WXUNUSED(event)) {
  int answer = wxMessageBox("Are you sure you want to empty the Trash?",
                            "Empty Trash", wxYES_NO | wxICON_QUESTION, this);
  if (answer == wxYES) {
    SetStatusText("Trash emptied", 0);
  }
}

// Window menu handlers
void MainFrame::OnCascade(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Cascade - Not applicable for tabbed interface", 0);
}

void MainFrame::OnTileHorizontal(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Tile Horizontal - Not applicable for tabbed interface", 0);
}

void MainFrame::OnTileVertical(wxCommandEvent &WXUNUSED(event)) {
  SetStatusText("Tile Vertical - Not applicable for tabbed interface", 0);
}

void MainFrame::OnCloseAll(wxCommandEvent &WXUNUSED(event)) {
  // Close all notebook pages except the welcome page
  while (m_notebook->GetPageCount() > 1) {
    m_notebook->DeletePage(m_notebook->GetPageCount() - 1);
  }
}

// Help menu handlers
void MainFrame::OnHelpContents(wxCommandEvent &WXUNUSED(event)) {
  wxMessageBox("Help contents would appear here.", "Help",
               wxOK | wxICON_INFORMATION, this);
}

void MainFrame::OnAbout(wxCommandEvent &WXUNUSED(event)) {
  wxMessageBox("wxEudora - A wxWidgets Port\n\n"
               "Based on the public domain Eudora 7.1 source code.\n"
               "Ported to wxWidgets for cross-platform compatibility.\n\n"
               "Version: 0.2.0 (MDI Interface)",
               "About wxEudora", wxOK | wxICON_INFORMATION, this);
}

// Update UI handlers
void MainFrame::OnUpdateNeedSelection(wxUpdateUIEvent &event) {
  // TODO: Enable only when there's a selection
  event.Enable(false);
}

void MainFrame::OnUpdateNeedClipboard(wxUpdateUIEvent &event) {
  // TODO: Enable only when clipboard has content
  event.Enable(true);
}
