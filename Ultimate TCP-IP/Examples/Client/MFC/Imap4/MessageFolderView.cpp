// MessageFolderView.cpp : implementation file
//

#include "stdafx.h"
#include "IMAPClient.h"
#include "IMAPClientDoc.h"
#include "MainFrame.h"
#include "MessageListView.h"
#include "MessageFolderView.h"
#include "CreateFolderDlg.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define FOLDER_DELETE       1001
#define FOLDER_INSERT       1002
    
const LPCTSTR
CMessageFolderView::m_lpFoldersName = _T("Folders");

/////////////////////////////////////////////////////////////////////////////
// CMessageFolderView

IMPLEMENT_DYNCREATE(CMessageFolderView, CTreeView)

CMessageFolderView::CMessageFolderView()
	: m_hRootItem(NULL)
{
}

CMessageFolderView::~CMessageFolderView()
{
}

BEGIN_MESSAGE_MAP(CMessageFolderView, CTreeView)
	//{{AFX_MSG_MAP(CMessageFolderView)
	ON_NOTIFY_REFLECT(NM_CLICK, OnSingleClickItem)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageFolderView drawing

void CMessageFolderView::OnDraw(CDC* /* pDC */)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMessageFolderView diagnostics

#ifdef _DEBUG
void CMessageFolderView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMessageFolderView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMessageFolderView message handlers

void CMessageFolderView::BuildFolderList()
{
	CWaitCursor w;
	CUT_IMAP4Client& imapc = GetAppFrameWnd()->m_imapClient;
	CTreeCtrl& tree = GetTreeCtrl();

	imapc.MailBoxList("", "*");
	AddChildFolders(m_hRootItem);

	tree.Expand(m_hRootItem, TVE_EXPAND);
}

void CMessageFolderView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	GetTreeCtrl().ModifyStyle(NULL, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_EDITLABELS | TVS_SHOWSELALWAYS);
	m_hRootItem = GetTreeCtrl().InsertItem(CMessageFolderView::m_lpFoldersName);
}

void CMessageFolderView::CreateFolder(LPCSTR lpFolder)
{
	// Tree folder insertion algorithm
	// -------------------------------
	// Creates the specified folder only if does not already exist.
	// This function accepts folders with sub-folders. Sub-folders
	// must be delimited with the "." character.
	//
	// e.g.
	//
	// lpFolder = "Inbox"
	// effect: adds the folder "Inbox" to the tree if it doesn't already 
	//         exist
	//
	// lpFolder = "Inbox.Old.Sue"
	// effect: adds the folder "Inbox" (if it doesn't exist), then adds
	//         "Old" as a sub-folder of "Inbox" (if it doesn't exist) and 
	//         finally adds "Sue" as a sub-folder of "Old" (if it doesn't
	//         exist).
	//
	// Note: it is assumed that all items exist as sub-items of the
	//       one and only root item named "Folders"

	static const LPCTSTR lpDelimiter = _T(".");

	CTreeCtrl& tree = GetTreeCtrl();
	
	CString sFolder = lpFolder;
	CString sSub = _tcstok(sFolder.GetBuffer(sFolder.GetLength()), lpDelimiter);

	HTREEITEM hFirstItem = tree.GetChildItem(m_hRootItem);
	HTREEITEM hSuperItem = m_hRootItem; // super item of the current item

	if (hFirstItem == NULL) {

		// safe to add all nodes since the tree is empty 
		// (degenerate case #1)

		while (!sSub.IsEmpty()) {

			hSuperItem = tree.InsertItem(sSub, hSuperItem);
			sSub = _tcstok(NULL, lpDelimiter);
		}
	}
	else {
	
		bool bAlreadyExists;
			
		while (!sSub.IsEmpty()) {

			bAlreadyExists = false;

			// Look for an item in the tree (at the current depth)
			// with the same name. If such an item already exists,
			// we do not need to reinsert it
			while (hFirstItem != NULL) {

				// Does this item have the same name as the folder?
				if (tree.GetItemText(hFirstItem).CompareNoCase(sSub) == 0) {
					bAlreadyExists = true;
					break;
				}
				else
					hFirstItem = tree.GetNextSiblingItem(hFirstItem);
			}

			if (!bAlreadyExists) {

				// Since this item does not already exist, none of its child
				// items can exist (at any level below it). Thus, it is safe
				// to add this item and all its sub-items at once
				// (degenerate case #2)

				while (!sSub.IsEmpty()) {

					hSuperItem = tree.InsertItem(sSub, hSuperItem);
					sSub = _tcstok(NULL, lpDelimiter);
				}
			}
			else {

				// A folder with the same name already exists. We don't
				// add a new folder; rather, we move into this new folder
				// and try inserting the next sub-string
				hSuperItem = hFirstItem;
				hFirstItem = tree.GetChildItem(hFirstItem);

				// Get the next sub-string in the folder
				sSub = _tcstok(NULL, lpDelimiter);
			}
		}
	}
	sFolder.ReleaseBuffer();
}

void CMessageFolderView::AddChildFolders(HTREEITEM /* hParentItem */)
{
	// Adds all folders into the tree	
	CUT_IMAP4Client& imapc = GetAppFrameWnd()->m_imapClient;

	CString sFolder;
    for(int i=0; i<imapc.GetMailBoxListSize(); i++) {
        LPCSTR   ptrName, ptrDelimiter;
        int     nAttrib;
        if(imapc.GetMailBoxListItem(i, ptrName, ptrDelimiter, nAttrib) == UTE_SUCCESS)
            CreateFolder(ptrName);
        }
}

void CMessageFolderView::OnSingleClickItem(NMHDR* /* pNMHDR */, LRESULT* pResult) 
{
	// Relay the message to the message list view
	TVHITTESTINFO tvhti;
	GetCursorPos(&tvhti.pt);
	ScreenToClient(&tvhti.pt);

	// Only update the view if the user clicked on an item and
	// the currently selected folder is not the "Folders" folder
	HTREEITEM hItem = GetTreeCtrl().HitTest(&tvhti);
	if (hItem != NULL && tvhti.flags & TVHT_ONITEM) {

		BuildSelectedFolderString(hItem);
		if (m_sSelectedFolder != CMessageFolderView::m_lpFoldersName)
			GetDocument()->UpdateAllViews(this, IDN_UPDATE_MESSAGE_LIST);
	}

	*pResult = 0;
}


void CMessageFolderView::BuildSelectedFolderString(HTREEITEM hItem)
{
	if (hItem == m_hRootItem)
		m_sSelectedFolder = CMessageFolderView::m_lpFoldersName;
	else {
	
		m_sSelectedFolder.Empty();
		do {
		
			m_sSelectedFolder = GetTreeCtrl().GetItemText(hItem) + m_sSelectedFolder;

			hItem = GetTreeCtrl().GetParentItem(hItem);
			if (hItem != m_hRootItem)
				m_sSelectedFolder = "." + m_sSelectedFolder;
		}
		while (hItem != m_hRootItem);
	}
}

void CMessageFolderView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    CMenu   menu;
    CPoint  pt = point;
    
    ClientToScreen( &pt ); 
    BOOL result = menu.CreatePopupMenu( );
	if(result) {
		menu.AppendMenu(MF_STRING, FOLDER_DELETE, _T("Delete")); 
		menu.AppendMenu(MF_STRING, FOLDER_INSERT, _T("Insert")); 
		menu.TrackPopupMenu( TPM_LEFTALIGN, pt.x, pt.y, this);
		menu.DestroyMenu();
	}	
	CTreeView::OnRButtonDown(nFlags, point);
}

BOOL CMessageFolderView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    CTreeCtrl&  tree = GetTreeCtrl();
    CUT_IMAP4Client& imapc = GetAppFrameWnd()->m_imapClient;

	// TODO: Add your specialized code here and/or call the base class
    switch(wParam) {
        case(FOLDER_DELETE): {
            HTREEITEM   item = tree.GetSelectedItem( );
            CString     itemText = "";

            // Get full item text
            if(item != NULL ){
                do {
                    itemText = tree.GetItemText(item) + itemText;
                    itemText = "." + itemText;
                } while ((item = tree.GetParentItem( item )) != NULL);
                
                if(itemText.GetLength() > lstrlen(CMessageFolderView::m_lpFoldersName) + 2)
                    itemText = itemText.Mid(lstrlen(CMessageFolderView::m_lpFoldersName) + 2);
            }

            imapc.MailBoxDelete(itemText);
            tree.DeleteAllItems();
            m_hRootItem = tree.InsertItem(CMessageFolderView::m_lpFoldersName);
            BuildFolderList();
            }
            break;

        case(FOLDER_INSERT):
            CCreateFolderDlg    dlg(GetAppFrameWnd());
            if(dlg.DoModal() == IDOK) {
                imapc.MailBoxCreate(dlg.m_strFolderName);
                tree.DeleteAllItems();
                m_hRootItem = tree.InsertItem(CMessageFolderView::m_lpFoldersName);
                BuildFolderList();
            }
            break;
    }
	

    return CTreeView::OnCommand(wParam, lParam);
}

#pragma warning ( pop )