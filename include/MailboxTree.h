/**
 * wxEudora - A wxWidgets port of the Eudora email client
 *
 * MailboxTree.h - Tree control for mailbox hierarchy
 */

#ifndef MAILBOXTREE_H
#define MAILBOXTREE_H

#include <wx/imaglist.h>
#include <wx/treectrl.h>
#include <wx/wx.h>

/**
 * Mailbox item types (based on QCMailboxTreeCtrl::ItemType)
 */
enum class MailboxItemType {
  ROOT = 0,
  IN_MBOX,
  OUT_MBOX,
  TRASH_MBOX,
  JUNK_MBOX,
  FOLDER,
  USER_MBOX
};

/**
 * Custom data for tree items
 */
class MailboxItemData : public wxTreeItemData {
public:
  MailboxItemData(MailboxItemType type, const wxString &path = wxEmptyString)
      : m_type(type), m_path(path) {}

  MailboxItemType GetType() const { return m_type; }
  wxString GetPath() const { return m_path; }

private:
  MailboxItemType m_type;
  wxString m_path;
};

/**
 * Tree control for displaying mailbox hierarchy
 */
class MailboxTree : public wxTreeCtrl {
public:
  MailboxTree(wxWindow *parent, wxWindowID id = wxID_ANY);
  virtual ~MailboxTree();

  void InitializeMailboxes();

private:
  void CreateImageList();
  wxTreeItemId AddMailbox(const wxTreeItemId &parent, const wxString &name,
                          MailboxItemType type, int imageIndex);

  void OnItemActivated(wxTreeEvent &event);
  void OnItemRightClick(wxTreeEvent &event);
  void OnSelectionChanged(wxTreeEvent &event);

  wxImageList *m_imageList;
  wxTreeItemId m_rootItem;

  wxDECLARE_EVENT_TABLE();
};

#endif // MAILBOXTREE_H
