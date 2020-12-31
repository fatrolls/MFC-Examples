// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "FileExplorer.h"

#include "FileExplorerDoc.h"
#include "LeftView.h"

#include "MainFrm.h"
#include "FileExplorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

BEGIN_MESSAGE_MAP(CLeftView, CView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED,IDC_FOLDERTREE,OnSelectFolder)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_VIEW_PROPERTY, OnViewProperties)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTY, OnUpdateViewProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
	m_nCurrentItemInHistory=-1;
	m_bPopulateList=TRUE;
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CFileExplorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	UNREFERENCED_PARAMETER(pDC);
}


void CLeftView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	ASSERT(::IsWindow(m_folderTree.GetSafeHwnd()));

	m_folderTree.SetEnableContextMenu(TRUE);
	m_folderTree.SetOnlyFileSystemFolders(FALSE);
	m_folderTree.SetNotifyError(TRUE);

	m_folderTree.InitializeTree();

	m_folderTree.SelectItem(m_folderTree.GetNextItem(TVI_ROOT,TVGN_CHILD));
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFileExplorerDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileExplorerDoc)));
	return (CFileExplorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if(!m_folderTree.Create(WS_VISIBLE|WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|
		TVS_HASBUTTONS|TVS_EDITLABELS|TVS_SHOWSELALWAYS,CRect(0,0,0,0),this,
		IDC_FOLDERTREE))
	{
		return -1;
	}

	return 0;
}

void CLeftView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(::IsWindow(m_folderTree.GetSafeHwnd()))
		m_folderTree.MoveWindow(0,0,cx,cy);
}

BOOL CLeftView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	UNREFERENCED_PARAMETER(pDC);
	
	return TRUE;
}

void CLeftView::OnSelectFolder(NMHDR* pNotifyStruct, LRESULT* result)
{
	*result=0;

	LPNMTREEVIEW pnmtv=(LPNMTREEVIEW)pNotifyStruct;

	if(pnmtv->itemNew.hItem==NULL)
		return;

	// Get folder info  associated with item
	LPNAMESPACEOBJECT lpNameSpaceObject=
		(LPNAMESPACEOBJECT)m_folderTree.GetItemData(pnmtv->itemNew.hItem);
	ASSERT(lpNameSpaceObject!=NULL || m_folderTree.GetShowDesktopItem());

	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	ASSERT(pMainFrame!=NULL);

	// get shell folder object from saved PIDLs
	if(m_bPopulateList)
	{
		if(lpNameSpaceObject!=NULL)
		{
			COXShellNamespaceNavigator navigator;
			LPSHELLFOLDER lpsfSelected=navigator.
				GetShellFolder(lpNameSpaceObject->lpsfParent,
				lpNameSpaceObject->lpRelativeIDL);
			if(lpsfSelected!=NULL)
			{
				CFileExplorerView* pListView=pMainFrame->GetRightPane();
				pListView->m_filesList.PopulateList(lpsfSelected,
					lpNameSpaceObject->lpFullIDL);
				lpsfSelected->Release();
			}
		}
		else
		{
			CFileExplorerView* pListView=pMainFrame->GetRightPane();
			pListView->m_filesList.PopulateList();
		}
	}

	BOOL bExistInHistory=FALSE;
	if(m_arrHistory.GetSize()>m_nCurrentItemInHistory && m_nCurrentItemInHistory>=0)
	{
		if(lpNameSpaceObject==NULL)
			bExistInHistory=(m_arrHistory.GetAt(m_nCurrentItemInHistory)==NULL);
		else
			bExistInHistory=(m_arrHistory.GetAt(m_nCurrentItemInHistory)==
				lpNameSpaceObject->lpFullIDL);
		if(!bExistInHistory)
		{
			m_arrHistory.RemoveAt(m_nCurrentItemInHistory+1,
				m_arrHistory.GetSize()-m_nCurrentItemInHistory-1);
		}
	}
	if(!bExistInHistory)
	{
		m_nCurrentItemInHistory++;
		// ??? IDL might be deleted in the future, probably have to copy it
		if(lpNameSpaceObject==NULL)
			m_arrHistory.SetAtGrow(m_nCurrentItemInHistory,NULL);
		else
			m_arrHistory.SetAtGrow(m_nCurrentItemInHistory,lpNameSpaceObject->lpFullIDL);
	}
}


void CLeftView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	HTREEITEM hItem=m_folderTree.GetSelectedItem();
	ASSERT(hItem!=NULL);
	LPNAMESPACEOBJECT lpNameSpaceObject=
		(LPNAMESPACEOBJECT)m_folderTree.GetItemData(hItem);
	ASSERT(lpNameSpaceObject!=NULL);
	ASSERT((lpNameSpaceObject->dwFlags&SFGAO_FOLDER)==SFGAO_FOLDER);
	m_folderTree.InvokeCommand(hItem,IDCMD_PASTE);
}

void CLeftView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	HTREEITEM hItem=m_folderTree.GetSelectedItem();
	ASSERT(hItem!=NULL);
	m_folderTree.InvokeCommand(hItem,IDCMD_COPY);
}

void CLeftView::OnEditCut() 
{
	// TODO: Add your command handler code here
	HTREEITEM hItem=m_folderTree.GetSelectedItem();
	ASSERT(hItem!=NULL);
	m_folderTree.InvokeCommand(hItem,IDCMD_CUT);
}

void CLeftView::OnEditDelete() 
{
	// TODO: Add your command handler code here
	HTREEITEM hItem=m_folderTree.GetSelectedItem();
	ASSERT(hItem!=NULL);
	m_folderTree.InvokeCommand(hItem,IDCMD_DELETE);
}

void CLeftView::OnViewProperties() 
{
	// TODO: Add your command handler code here
	HTREEITEM hItem=m_folderTree.GetSelectedItem();
	ASSERT(hItem!=NULL);
	m_folderTree.InvokeCommand(hItem,IDCMD_PROPERTIES);
}


void CLeftView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_EDIT_PASTE);
}

void CLeftView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_EDIT_COPY);
}

void CLeftView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_EDIT_CUT);
}

void CLeftView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_EDIT_DELETE);
}

void CLeftView::OnUpdateViewProperties(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_VIEW_PROPERTY);
}

void CLeftView::OnUpdate(CCmdUI* pCmdUI, UINT nID)
{
	HTREEITEM hItem=m_folderTree.GetSelectedItem();
	if(hItem==NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	// Get folder info  associated with item
	LPNAMESPACEOBJECT lpNameSpaceObject=
		(LPNAMESPACEOBJECT)m_folderTree.GetItemData(hItem);
	if(lpNameSpaceObject==NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	switch(nID)
	{
	case ID_EDIT_PASTE:
		pCmdUI->Enable(lpNameSpaceObject->dwFlags&SFGAO_FOLDER);
		break;
	case ID_EDIT_COPY:
		pCmdUI->Enable(lpNameSpaceObject->dwFlags&SFGAO_CANCOPY);
		break;
	case ID_EDIT_CUT:
		pCmdUI->Enable((lpNameSpaceObject->dwFlags&SFGAO_CANCOPY)!=0 && 
			(lpNameSpaceObject->dwFlags&SFGAO_CANDELETE)!=0);
		break;
	case ID_EDIT_DELETE:
		pCmdUI->Enable(lpNameSpaceObject->dwFlags&SFGAO_CANDELETE);
		break;
	case ID_VIEW_PROPERTY:
		pCmdUI->Enable(lpNameSpaceObject->dwFlags&SFGAO_HASPROPSHEET);
		break;
	default:
		ASSERT(FALSE);
	}
}

void CLeftView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	m_folderTree.SetFocus();
}
