// TabViewBar.cpp : implementation file
//
// Docktest demo of Dockable Views functionality

#include "stdafx.h"
#include "docktest.h"
#include "TabViewBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabViewBar
//

IMPLEMENT_DYNAMIC(CTabViewBar, COXSizeControlBar);

CTabViewBar::CTabViewBar() 
		: COXSizeControlBar( SZBARF_STDMOUSECLICKS | SZBARF_ALLOW_MDI_FLOAT)
{
}

CTabViewBar::~CTabViewBar()
{
}



BEGIN_MESSAGE_MAP(CTabViewBar, COXSizeControlBar)
	//{{AFX_MSG_MAP(CTabViewBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTabViewBar message handlers


//-------------------------------------------------------------------
void CTabViewBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	CRect rect;
	GetClientRect(rect);

//	rect.DeflateRect(2,2);
	
	m_TabViewContainer.MoveWindow(&rect);
}


//-------------------------------------------------------------------
int CTabViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//-------------------------------------------------------------------
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	
	if(!m_TabViewContainer.Create(this,rect))
		return -1;

	// edit control
	if(!edit.Create(WS_CHILD|ES_MULTILINE|ES_AUTOHSCROLL|
		ES_AUTOVSCROLL|WS_HSCROLL|WS_VSCROLL,CRect(0,0,0,0),
		&m_TabViewContainer,1))
		return -1;
	m_TabViewContainer.AddPage(&edit,_T("Edit"));

	// list box
	if(!listBox.Create(WS_CHILD|WS_HSCROLL|WS_VSCROLL,
		CRect(0,0,0,0),&m_TabViewContainer,2))
		return -1;

	int nIndex=0;
	for(nIndex=0; nIndex<20; nIndex++)
	{
		CString string;
		string.Format(_T("List box test string number %d"),nIndex);
		listBox.AddString(string);
	}
	m_TabViewContainer.AddPage(&listBox,_T("ListBox"));

	// list control
	if(!listCtrl.Create(WS_CHILD|LVS_REPORT,
		CRect(0,0,0,0),&m_TabViewContainer,3))
		return -1;
	if((listCtrl.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=200;
		lvc.pszText=_T("Column1");
		listCtrl.InsertColumn(0,&lvc);
	}
	for(nIndex=0; nIndex<20; nIndex++)
	{
		CString string;
		string.Format(_T("List control test string number %d"),nIndex);
		VERIFY(listCtrl.InsertItem(nIndex,string)!=-1);
	}
	m_TabViewContainer.AddPage(&listCtrl,_T("List"));

	// tree control
	if(!treeCtrl.Create(WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS,
		CRect(0,0,0,0),&m_TabViewContainer,4))
		return -1;
	HTREEITEM htiRoot=treeCtrl.InsertItem(_T("RootItem"));
	for(nIndex=0; nIndex<20; nIndex++)
	{
		CString string;
		string.Format(_T("Tree control test string number %d"),nIndex);
		VERIFY(treeCtrl.InsertItem(string,htiRoot)!=NULL);
	}
	m_TabViewContainer.AddPage(&treeCtrl,_T("Tree"));

	// rich edit control

	m_TabViewContainer.SetActivePageIndex(0);
	
	
	return 0;					
}


BOOL CTabViewBar::PreCreateWindow(CREATESTRUCT& cs) 
{
	return COXSizeControlBar::PreCreateWindow(cs);
}


BOOL CTabViewBar::Create(CWnd * pParentWnd, 
						 const CString& sTitle/*=_T("TabViewBar")*/,
						 const UINT nID/*=ID_TABVIEWBAR*/)
{
	// register a window class for the control bar
	static CString strWndClass;
	if (strWndClass.IsEmpty())
	{
		strWndClass = AfxRegisterWndClass(CS_DBLCLKS);
	}
	
	return COXSizeControlBar::Create(strWndClass, sTitle,
		WS_VISIBLE | WS_CHILD | CBRS_BOTTOM | WS_CLIPCHILDREN,
		CFrameWnd::rectDefault, pParentWnd, nID);
}



