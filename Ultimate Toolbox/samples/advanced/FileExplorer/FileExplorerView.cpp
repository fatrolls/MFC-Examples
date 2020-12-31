// FileExplorerView.cpp : implementation of the CFileExplorerView class
//

#include "stdafx.h"
#include "FileExplorer.h"

#include "FileExplorerDoc.h"
#include "FileExplorerView.h"

#include "MainFrm.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerView

IMPLEMENT_DYNCREATE(CFileExplorerView, CView)

BEGIN_MESSAGE_MAP(CFileExplorerView, CView)
	//{{AFX_MSG_MAP(CFileExplorerView)
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
	ON_NOTIFY(NM_DBLCLK,IDC_FILELIST,OnSelectFolder)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_VIEW_PROPERTY, OnViewProperties)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTY, OnUpdateViewProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerView construction/destruction

CFileExplorerView::CFileExplorerView()
{
	// TODO: add construction code here

}

CFileExplorerView::~CFileExplorerView()
{
}

BOOL CFileExplorerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerView drawing

void CFileExplorerView::OnDraw(CDC* pDC)
{
	CFileExplorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	UNREFERENCED_PARAMETER(pDC);
}

void CFileExplorerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().

	ASSERT(::IsWindow(m_filesList.GetSafeHwnd()));

	m_filesList.SetEnableContextMenu(TRUE);
	m_filesList.SetOnlyFileSystemItems(FALSE);
	m_filesList.SetNotifyError(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerView diagnostics

#ifdef _DEBUG
void CFileExplorerView::AssertValid() const
{
	CView::AssertValid();
}

void CFileExplorerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFileExplorerDoc* CFileExplorerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileExplorerDoc)));
	return (CFileExplorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileExplorerView message handlers
int CFileExplorerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if(!m_filesList.Create(WS_VISIBLE|WS_CHILD|LVS_REPORT|
		LVS_EDITLABELS|LVS_SHOWSELALWAYS,
		CRect(0,0,0,0),this,IDC_FILELIST))
	{
		return -1;
	}

	
	return 0;
}

void CFileExplorerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(::IsWindow(m_filesList.GetSafeHwnd()))
		m_filesList.MoveWindow(0,0,cx,cy);
}

BOOL CFileExplorerView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	UNREFERENCED_PARAMETER(pDC);
	
	return TRUE;
}

void CFileExplorerView::OnSelectFolder(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	*result=0;

	CPoint ptMouseCursor;
	::GetCursorPos(&ptMouseCursor);
	m_filesList.ScreenToClient(&ptMouseCursor);

	// Use HitTest function to define the list item by coordinate
	UINT nFlags=NULL;
	int nItem=m_filesList.HitTest(ptMouseCursor,&nFlags);

	if(nItem!=-1 && (nFlags&LVHT_ONITEM)!=0)
	{
		// Get folder info  associated with item
		LPNAMESPACEOBJECT lpNameSpaceObject=
			(LPNAMESPACEOBJECT)m_filesList.GetItemData(nItem);
		ASSERT(lpNameSpaceObject!=NULL);

		if(lpNameSpaceObject->dwFlags&SFGAO_HASSUBFOLDER || 
			lpNameSpaceObject->dwFlags&SFGAO_FOLDER)
		{
			COXShellNamespaceNavigator navigator;
			LPSHELLFOLDER lpsfSelected=
				navigator.GetShellFolder(lpNameSpaceObject->lpsfParent,
				lpNameSpaceObject->lpRelativeIDL);
			if(lpsfSelected!=NULL)
			{
				m_filesList.PopulateList(lpsfSelected,lpNameSpaceObject->lpFullIDL);

				CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
				ASSERT(pMainFrame!=NULL);
				CLeftView* pTreeView=pMainFrame->GetLeftPane();
				pTreeView->m_bPopulateList=FALSE;
				pTreeView->m_folderTree.OpenFolder(lpNameSpaceObject->lpFullIDL);
				pTreeView->m_bPopulateList=TRUE;
			}
		}
	}
}

void CFileExplorerView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	int nItem=m_filesList.GetNextItem(-1,LVNI_SELECTED);
	ASSERT(nItem!=-1);
	LPNAMESPACEOBJECT lpNameSpaceObject=
		(LPNAMESPACEOBJECT)m_filesList.GetItemData(nItem);
	ASSERT(lpNameSpaceObject!=NULL);
	ASSERT((lpNameSpaceObject->dwFlags&SFGAO_FOLDER)==SFGAO_FOLDER);
	m_filesList.InvokeCommand(nItem,IDCMD_PASTE);
}

void CFileExplorerView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	int nItem=m_filesList.GetNextItem(-1,LVNI_SELECTED);
	ASSERT(nItem!=-1);
	m_filesList.InvokeCommand(nItem,IDCMD_COPY);
}

void CFileExplorerView::OnEditCut() 
{
	// TODO: Add your command handler code here
	int nItem=m_filesList.GetNextItem(-1,LVNI_SELECTED);
	ASSERT(nItem!=-1);
	m_filesList.InvokeCommand(nItem,IDCMD_CUT);
}

void CFileExplorerView::OnEditDelete() 
{
	// TODO: Add your command handler code here
	int nItem=m_filesList.GetNextItem(-1,LVNI_SELECTED);
	ASSERT(nItem!=-1);
	m_filesList.InvokeCommand(nItem,IDCMD_DELETE);
}

void CFileExplorerView::OnViewProperties() 
{
	// TODO: Add your command handler code here
	int nItem=m_filesList.GetNextItem(-1,LVNI_SELECTED);
	ASSERT(nItem!=-1);
	m_filesList.InvokeCommand(nItem,IDCMD_PROPERTIES);
}


void CFileExplorerView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_EDIT_PASTE);
}

void CFileExplorerView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_EDIT_COPY);
}

void CFileExplorerView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_EDIT_CUT);
}

void CFileExplorerView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_EDIT_DELETE);
}

void CFileExplorerView::OnUpdateViewProperties(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdate(pCmdUI,ID_VIEW_PROPERTY);
}

void CFileExplorerView::OnUpdate(CCmdUI* pCmdUI, UINT nID)
{
	int nItem=m_filesList.GetNextItem(-1,LVNI_SELECTED);
	if(nItem==-1)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	// Get folder info  associated with item
	LPNAMESPACEOBJECT lpNameSpaceObject=
		(LPNAMESPACEOBJECT)m_filesList.GetItemData(nItem);
	ASSERT(lpNameSpaceObject!=NULL);

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

void CFileExplorerView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	m_filesList.SetFocus();
}
