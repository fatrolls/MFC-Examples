// 3DTabViewBar.cpp : implementation file
//

#include "stdafx.h"
#include "VisualStudioLikeDemo.h"
#include "3DTabViewBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DTabViewBar
//

IMPLEMENT_DYNAMIC(C3DTabViewBar, COXSizeControlBar);

C3DTabViewBar::C3DTabViewBar() 
	: COXSizeControlBar(
	SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
}

C3DTabViewBar::~C3DTabViewBar()
{
}



BEGIN_MESSAGE_MAP(C3DTabViewBar, COXSizeControlBar)
	//{{AFX_MSG_MAP(C3DTabViewBar)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// C3DTabViewBar message handlers

BOOL C3DTabViewBar::OnEraseBkgnd(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);
	return TRUE;
}


//-------------------------------------------------------------------
void C3DTabViewBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	CRect rect;
	GetClientRect(rect);

	m_TabViewContainer.MoveWindow(&rect);

}


//-------------------------------------------------------------------
int C3DTabViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//-------------------------------------------------------------------
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	
	if(!m_TabViewContainer.Create(this,rect))
		return -1;

	VERIFY(m_ilTabView.Create(IDB_IL_3DTABVIEW,16,0,RGB(192,192,192)));
	m_TabViewContainer.SetImageList(&m_ilTabView);

	// Class View
	if(!m_treeClass.Create(WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS,
		CRect(0,0,0,0),&m_TabViewContainer,1))
		return -1;
	VERIFY(m_ilClass.Create(IDB_IL_CLASSVIEW,16,0,RGB(192,192,192)));
	m_treeClass.SetImageList(&m_ilClass,TVSIL_NORMAL);
	HTREEITEM htiRoot=
		m_treeClass.InsertItem(_T("VisualStudioLikeDemo classes"),0,0);
	ASSERT(htiRoot!=NULL);
	m_treeClass.SetItemState(htiRoot,TVIS_BOLD,TVIS_BOLD);
	HTREEITEM htiSubroot=m_treeClass.InsertItem(_T("CAboutDlg"),1,1,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("CAboutDlg()"),2,2,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("DoDataExchange(CDataExchange* pDX)"),3,3,
		htiSubroot)!=NULL);
	htiSubroot=m_treeClass.InsertItem(_T("CMainFrame"),1,1,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("AssertValid()"),2,2,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("CMainFrame()"),2,2,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("~CMainFrame()"),2,2,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("Dump(CDumpContext& dc)"),2,2,
		htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("OnCreate(LPCREATESTRUCT lpCreateStruct)"),
		3,3,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("PreCreateWindow(CREATESTRUCT& cs)"),2,2,
		htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("m_3DTabViewBar"),5,5,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("m_tabViewBar"),5,5,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("m_wndStatusBar"),5,5,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("m_wndToolBar"),5,5,htiSubroot)!=NULL);
	htiSubroot=m_treeClass.InsertItem(_T("CVisualStudioLikeDemoApp"),1,1,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("CVisualStudioLikeDemoApp()"),2,2,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("InitInstance()"),2,2,htiSubroot)!=NULL);
	VERIFY(m_treeClass.InsertItem(_T("OnAppAbout()"),2,2,htiSubroot)!=NULL);
	m_TabViewContainer.AddPage(&m_treeClass,_T("ClassView"),0);

	// Resource View
	if(!m_treeResource.
		Create(WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS,
		CRect(0,0,0,0),&m_TabViewContainer,2))
		return -1;
	VERIFY(m_ilResource.Create(IDB_IL_RESOURCEVIEW,16,0,RGB(192,192,192)));
	m_treeResource.SetImageList(&m_ilResource,TVSIL_NORMAL);
	htiRoot=m_treeResource.InsertItem(_T("VisualStudioLikeDemo resources"),0,0);
	ASSERT(htiRoot!=NULL);
	m_treeResource.SetItemState(htiRoot,TVIS_BOLD,TVIS_BOLD);
	htiSubroot=m_treeResource.InsertItem(_T("Bitmap"),0,0,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeResource.InsertItem(_T("IDB_IL_3DTABVIEW"),2,2,
		htiSubroot)!=NULL);
	VERIFY(m_treeResource.InsertItem(_T("IDB_IL_CLASSVIEW"),2,2,
		htiSubroot)!=NULL);
	VERIFY(m_treeResource.InsertItem(_T("IDB_IL_RESOURCEVIEW"),2,2,
		htiSubroot)!=NULL);
	htiSubroot=m_treeResource.InsertItem(_T("Dialog"),0,0,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeResource.InsertItem(_T("IDD_ABOUTBOX"),3,3,
		htiSubroot)!=NULL);
	htiSubroot=m_treeResource.InsertItem(_T("Icon"),0,0,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeResource.InsertItem(_T("IDR_MAINFRAME"),4,4,
		htiSubroot)!=NULL);
	VERIFY(m_treeResource.InsertItem(_T("IDR_VISUALTYPE"),4,4,
		htiSubroot)!=NULL);
	htiSubroot=m_treeResource.InsertItem(_T("String Table"),0,0,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeResource.InsertItem(_T("String Table"),5,5,
		htiSubroot)!=NULL);
	m_TabViewContainer.AddPage(&m_treeResource,_T("ResourceView"),1);

	// File View
	if(!m_treeFile.Create(WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS,
		CRect(0,0,0,0),&m_TabViewContainer,3))
		return -1;
	VERIFY(m_ilFile.Create(IDB_IL_FILEVIEW,16,0,RGB(192,192,192)));
	m_treeFile.SetImageList(&m_ilFile,TVSIL_NORMAL);
	htiRoot=m_treeFile.
		InsertItem(_T("Workspace 'VisualStudioLikeDemo': 1 project(s)"),0,0);
	ASSERT(htiRoot!=NULL);
	htiRoot=m_treeFile.InsertItem(_T("VisualStudioLikeDemo files"),1,1);
	ASSERT(htiRoot!=NULL);
	m_treeFile.SetItemState(htiRoot,TVIS_BOLD,TVIS_BOLD);
	htiSubroot=m_treeFile.InsertItem(_T("Source Files"),2,2,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("3DTabViewBar.cpp"),4,4,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("ChildFrm.cpp"),4,4,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("MainFrm.cpp"),4,4,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("StdAfx.cpp"),4,4,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("TabViewBar.cpp"),4,4,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemo.cpp"),4,4,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemo.rc"),4,4,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemoDoc.cpp"),4,4,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemoView.cpp"),4,4,
		htiSubroot)!=NULL);
	htiSubroot=m_treeFile.InsertItem(_T("Header Files"),2,2,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("3DTabViewBar.h"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("ChildFrm.h"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("MainFrm.h"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("Resource.h"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("StdAfx.h"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("TabViewBar.h"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemo.rc"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemoDoc.h"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemoView.h"),5,5,
		htiSubroot)!=NULL);
	htiSubroot=m_treeFile.InsertItem(_T("Resource Files"),2,2,htiRoot);
	ASSERT(htiSubroot!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemo.ico"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemo.rc2"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("VisualStudioLikeDemoDoc.ico"),5,5,
		htiSubroot)!=NULL);
	VERIFY(m_treeFile.InsertItem(_T("ReadMe.txt"),5,5,htiRoot)!=NULL);
	m_TabViewContainer.AddPage(&m_treeFile,_T("FileView"),2);


	m_TabViewContainer.SetActivePageIndex(0);
	
	return 0;					
}


BOOL C3DTabViewBar::Create(CWnd * pParentWnd, 
						   const CString& sTitle/*=_T("3DTabViewBar")*/,
						   const UINT nID/*=ID_3DTABVIEWBAR*/)
{
	// register a window class for the control bar
	static CString strWndClass;
	if (strWndClass.IsEmpty())
	{
		strWndClass = AfxRegisterWndClass(CS_DBLCLKS);
	}
	
	return COXSizeControlBar::Create(strWndClass, sTitle,
		WS_VISIBLE | WS_CHILD | CBRS_BOTTOM | WS_CLIPSIBLINGS,
		CFrameWnd::rectDefault, pParentWnd, nID);
}




