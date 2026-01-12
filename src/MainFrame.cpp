/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * MainFrame.cpp - Main MDI parent frame implementation
 */

#include "MainFrame.h"
#include "ChildFrame.h"
#include "SettingsDialog.h"
#include <wx/artprov.h>
#include <wx/aui/auibook.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/toolbar.h>
#include <wx/treectrl.h>
#include <wx/xrc/xmlres.h>
#include <wx/fileconf.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    // File menu
    EVT_MENU(ID_NEW_MESSAGE, MainFrame::OnNewMessage)
        EVT_MENU(ID_OPEN, MainFrame::OnOpen)
            EVT_MENU(XRCID("ID_APP_EXIT"), MainFrame::OnExit)
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
        EVT_MENU(XRCID("ID_SETTINGS"), MainFrame::OnSettings)
            EVT_MENU(XRCID("ID_SPECIAL_SETTINGS"), MainFrame::OnSettings)
                EVT_MENU(wxID_PREFERENCES, MainFrame::OnSettings)
                    EVT_MENU(ID_EMPTY_TRASH, MainFrame::OnEmptyTrash)

    // Window menu
    EVT_MENU(ID_CASCADE, MainFrame::OnCascade)
        EVT_MENU(ID_TILE_HORIZONTAL, MainFrame::OnTileHorizontal)
            EVT_MENU(ID_TILE_VERTICAL, MainFrame::OnTileVertical)
                EVT_MENU(ID_CLOSE_ALL, MainFrame::OnCloseAll)

    // Help menu
    EVT_MENU(wxID_HELP, MainFrame::OnHelpContents)
        EVT_MENU(wxID_ABOUT, MainFrame::OnAbout) EVT_SIZE(MainFrame::OnSize)

    // Update UI
    EVT_UPDATE_UI(wxID_CUT, MainFrame::OnUpdateNeedSelection)
        EVT_UPDATE_UI(wxID_COPY, MainFrame::OnUpdateNeedSelection)
            EVT_UPDATE_UI(wxID_PASTE, MainFrame::OnUpdateNeedClipboard)
                wxEND_EVENT_TABLE()

                    MainFrame::MainFrame(const wxString &title)
    : m_splitter(nullptr), m_mailboxTree(nullptr), m_notebook(nullptr),
      m_statusBar(nullptr) {
  // Load the frame from XRC
  wxXmlResource::Get()->LoadFrame(this, nullptr, "MainFrame");
  SetMenuBar(wxXmlResource::Get()->LoadMenuBar("IDR_MAINFRAME"));
  SetTitle(title);

  // Get pointers to controls
  m_splitter = XRCCTRL(*this, "main_splitter", wxSplitterWindow);
  wxTreeCtrl *treeCtrl = XRCCTRL(*this, "mailbox_tree", wxTreeCtrl);
  wxPanel *notebookPanel = XRCCTRL(*this, "content_panel", wxPanel);

  // Create status bar
  m_statusBar = GetStatusBar();
  if (m_statusBar) {
    m_statusBar->SetFieldsCount(3);
    int widths[] = {-1, 150, 100};
    m_statusBar->SetStatusWidths(3, widths);
    SetStatusText("Ready", 0);
    SetStatusText("No messages", 1);
    SetStatusText("Offline", 2);
  }

  // Bind settings and exit events explicitly using XRC IDs
  Bind(wxEVT_MENU, &MainFrame::OnSettings, this, XRCID("ID_SETTINGS"));
  Bind(wxEVT_MENU, &MainFrame::OnExit, this, XRCID("ID_APP_EXIT"));
  Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
  // If we have a notebook panel from XRC, put the notebook in it
  if (notebookPanel) {
    m_notebook = new wxAuiNotebook(
        notebookPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE |
            wxAUI_NB_CLOSE_ON_ACTIVE_TAB);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_notebook, 1, wxEXPAND);
    notebookPanel->SetSizer(sizer);

    // Add a welcome page to the notebook
    wxPanel *welcomePanel = new wxPanel(m_notebook, wxID_ANY);
    welcomePanel->SetBackgroundColour(*wxWHITE);
    wxBoxSizer *welcomeSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *welcomeText =
        new wxStaticText(welcomePanel, wxID_ANY,
                         "Welcome to wxEudora (Phoenix UI)\n\n"
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
  }

  // Initialize mailbox tree
  if (m_splitter && treeCtrl && notebookPanel) {
    // Replace the generic wxTreeCtrl with our custom MailboxTree
    wxWindow *parent = treeCtrl->GetParent();
    m_mailboxTree = new MailboxTree(parent, wxID_ANY);
    m_splitter->ReplaceWindow(treeCtrl, m_mailboxTree);
    treeCtrl->Destroy();

    // Ensure splitter fills the entire client area
    m_splitter->SetSplitMode(wxSPLIT_VERTICAL);
    m_splitter->SetSashPosition(250);
    m_splitter->SetSize(GetClientSize());
  }
  // Setup AUI manager now so panes reserve space for toolbars
  m_auiManager = new wxAuiManager(this);

  // Make the main splitter the center pane so toolbars dock around it
  if (m_splitter) {
    m_auiManager->AddPane(m_splitter, wxAuiPaneInfo().CenterPane());
  }

  // Create main toolbar and try to load icons from resources/png
  m_toolBar = new wxAuiToolBar(this, wxID_ANY,
                               wxDefaultPosition, wxDefaultSize,
                               wxAUI_TB_HORZ_TEXT);
  // helper lambda to load a PNG and add tool (fallback to text)
  auto addToolWithPng = [this](int id, const wxString &label, const wxString &png, const wxString &tip) {
    wxBitmap bmp;
    if (wxFileExists(png)) bmp.LoadFile(png, wxBITMAP_TYPE_PNG);
    if (bmp.IsOk()) m_toolBar->AddTool(id, label, bmp, tip);
    else m_toolBar->AddTool(id, label, wxNullBitmap, tip);
  };

  addToolWithPng(ID_NEW_MESSAGE, "New", "resources/png/NEWFILE.png", "New Message");
  addToolWithPng(ID_REPLY, "Reply", "resources/png/REPLYING.png", "Reply");

  // If RTB1 is a sprite (many 16x16 icons in a row), extract sub-bitmaps
  auto addToolsFromSprite = [this](const wxString &png, int baseId, int tileW, int tileH, int maxCount) {
    if (!wxFileExists(png)) return 0;
    wxBitmap bmp;
    if (!bmp.LoadFile(png, wxBITMAP_TYPE_PNG) || !bmp.IsOk()) return 0;
    int cols = bmp.GetWidth() / tileW;
    if (cols <= 0) return 0;
    int yoff = 0;
    if (bmp.GetHeight() > tileH) yoff = (bmp.GetHeight() - tileH) / 2;
    int added = 0;
    for (int c = 0; c < cols && added < maxCount; ++c) {
      wxRect r(c * tileW, yoff, tileW, tileH);
      wxBitmap sub = bmp.GetSubBitmap(r);
      int id = baseId + added;
      m_toolBar->AddTool(id, wxEmptyString, sub);
      // bind this generated tool to a generic secondary handler
      Bind(wxEVT_TOOL, &MainFrame::OnSecondaryTool, this, id);
      ++added;
    }
    return added;
  };

  // Add sprite icons (17x17) from RTB1.png after Reply. Cap to 32 icons.
  int spriteAdded = addToolsFromSprite("resources/png/RTB1.png", ID_SEC_TOOL_BASE, 17, 17, 32);
  (void)spriteAdded; // silence unused in some builds

  addToolWithPng(ID_FORWARD, "Forward", "", "Forward");
  addToolWithPng(ID_DELETE_MESSAGE, "Delete", "resources/png/Remove.png", "Delete");

  m_toolBar->Realize();
  m_auiManager->AddPane(m_toolBar, wxAuiPaneInfo().Name("MainToolbar").ToolbarPane().Top());
  m_auiManager->Update();

  // Bind toolbar events to existing handlers
  Bind(wxEVT_TOOL, &MainFrame::OnNewMessage, this, ID_NEW_MESSAGE);
  Bind(wxEVT_TOOL, &MainFrame::OnReply, this, ID_REPLY);
  Bind(wxEVT_TOOL, &MainFrame::OnForward, this, ID_FORWARD);
  Bind(wxEVT_TOOL, &MainFrame::OnDelete, this, ID_DELETE_MESSAGE);

  // Set the frame size to ensure children have a size to calculate from
  SetSize(1200, 800);

  // Center and layout
  Layout();
  Centre();

  // Robust post-creation layout refresh
  CallAfter([this]() {
    if (m_splitter) {
      m_splitter->SetSize(GetClientSize());
      m_splitter->SetSashPosition(250);
      m_splitter->UpdateSize();
      Layout();
    }
  });
}

void MainFrame::OnSize(wxSizeEvent &event) {
  event.Skip();
  if (m_splitter) {
    m_splitter->SetSize(GetClientSize());
    m_splitter->UpdateSize();
  }
}

MainFrame::~MainFrame() {
  if (m_auiManager) {
    // Save perspective
    wxFileConfig config(wxEmptyString, wxEmptyString);
    wxString perspective = m_auiManager->SavePerspective();
    config.Write("ToolBar/Perspective", perspective);
    m_auiManager->UnInit();
    delete m_auiManager;
    m_auiManager = nullptr;
  }
}


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

void MainFrame::OnSecondaryTool(wxCommandEvent &event) {
  int idx = event.GetId() - ID_SEC_TOOL_BASE;
  wxString msg = wxString::Format("Secondary toolbar tool %d clicked", idx);
  SetStatusText(msg, 0);
}

// Special menu handlers
void MainFrame::OnSettings(wxCommandEvent &WXUNUSED(event)) {
  SettingsDialog dialog(this);
  dialog.ShowModal();
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
