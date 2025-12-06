/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * MailboxTree.cpp - Tree control implementation
 */

#include "MailboxTree.h"
#include <wx/artprov.h>

wxBEGIN_EVENT_TABLE(MailboxTree, wxTreeCtrl)
    EVT_TREE_ITEM_ACTIVATED(wxID_ANY, MailboxTree::OnItemActivated)
        EVT_TREE_ITEM_RIGHT_CLICK(wxID_ANY, MailboxTree::OnItemRightClick)
            EVT_TREE_SEL_CHANGED(wxID_ANY, MailboxTree::OnSelectionChanged)
                wxEND_EVENT_TABLE()

                    MailboxTree::MailboxTree(wxWindow *parent, wxWindowID id)
    : wxTreeCtrl(parent, id, wxDefaultPosition, wxDefaultSize,
                 wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_SINGLE),
      m_imageList(nullptr) {
  CreateImageList();
  InitializeMailboxes();
}

MailboxTree::~MailboxTree() {
  if (m_imageList) {
    delete m_imageList;
  }
}

void MailboxTree::CreateImageList() {
  // Create image list with 16x16 icons
  m_imageList = new wxImageList(16, 16);

  // Add icons for different mailbox types
  // Using wxArtProvider for standard icons
  wxBitmap folderIcon =
      wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16, 16));
  wxBitmap folderOpenIcon =
      wxArtProvider::GetBitmap(wxART_FOLDER_OPEN, wxART_OTHER, wxSize(16, 16));
  wxBitmap fileIcon =
      wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));

  m_imageList->Add(folderIcon);     // 0 - Folder/Root
  m_imageList->Add(folderOpenIcon); // 1 - Open folder
  m_imageList->Add(fileIcon);       // 2 - Mailbox

  SetImageList(m_imageList);
}

void MailboxTree::InitializeMailboxes() {
  // Create root item
  m_rootItem =
      AddRoot("Mailboxes", 0, 0, new MailboxItemData(MailboxItemType::ROOT));

  // Add default mailboxes (based on Eudora structure)
  AddMailbox(m_rootItem, "In", MailboxItemType::IN_MBOX, 2);
  AddMailbox(m_rootItem, "Out", MailboxItemType::OUT_MBOX, 2);
  AddMailbox(m_rootItem, "Trash", MailboxItemType::TRASH_MBOX, 2);
  AddMailbox(m_rootItem, "Junk", MailboxItemType::JUNK_MBOX, 2);

  // Add a sample folder with user mailboxes
  wxTreeItemId userFolder =
      AddMailbox(m_rootItem, "Personal", MailboxItemType::FOLDER, 0);
  AddMailbox(userFolder, "Work", MailboxItemType::USER_MBOX, 2);
  AddMailbox(userFolder, "Family", MailboxItemType::USER_MBOX, 2);
  AddMailbox(userFolder, "Friends", MailboxItemType::USER_MBOX, 2);

  // Expand root
  Expand(m_rootItem);
}

wxTreeItemId MailboxTree::AddMailbox(const wxTreeItemId &parent,
                                     const wxString &name, MailboxItemType type,
                                     int imageIndex) {
  wxString path = name;
  if (parent != m_rootItem) {
    MailboxItemData *parentData =
        dynamic_cast<MailboxItemData *>(GetItemData(parent));
    if (parentData) {
      path = parentData->GetPath() + "/" + name;
    }
  }

  return AppendItem(parent, name, imageIndex, imageIndex,
                    new MailboxItemData(type, path));
}

void MailboxTree::OnItemActivated(wxTreeEvent &event) {
  wxTreeItemId itemId = event.GetItem();
  MailboxItemData *data = dynamic_cast<MailboxItemData *>(GetItemData(itemId));

  if (data) {
    wxString msg =
        wxString::Format("Activated mailbox: %s (Type: %d)", data->GetPath(),
                         static_cast<int>(data->GetType()));
    wxLogStatus(msg);

    // TODO: Open mailbox in MDI child window
  }
}

void MailboxTree::OnItemRightClick(wxTreeEvent &event) {
  wxTreeItemId itemId = event.GetItem();
  SelectItem(itemId);

  MailboxItemData *data = dynamic_cast<MailboxItemData *>(GetItemData(itemId));
  if (!data)
    return;

  // Create context menu
  wxMenu menu;

  if (data->GetType() == MailboxItemType::FOLDER) {
    menu.Append(wxID_ANY, "New Mailbox...");
    menu.Append(wxID_ANY, "New Folder...");
    menu.AppendSeparator();
  }

  if (data->GetType() != MailboxItemType::ROOT) {
    menu.Append(wxID_ANY, "Rename...");
    menu.Append(wxID_ANY, "Delete");
    menu.AppendSeparator();
  }

  menu.Append(wxID_ANY, "Properties...");

  PopupMenu(&menu);
}

void MailboxTree::OnSelectionChanged(wxTreeEvent &event) {
  wxTreeItemId itemId = event.GetItem();
  MailboxItemData *data = dynamic_cast<MailboxItemData *>(GetItemData(itemId));

  if (data) {
    wxLogStatus("Selected: %s", data->GetPath());
  }
}
