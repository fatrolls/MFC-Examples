#include "stdafx.h"
#include "Explorer.h"
#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CExplorerDoc, CDocument)

BEGIN_MESSAGE_MAP(CExplorerDoc, CDocument)
	//{{AFX_MSG_MAP(CExplorerDoc)
	ON_COMMAND(ID_VIEW_LARGEICONS, OnViewLargeIcons)
	ON_COMMAND(ID_VIEW_LIST, OnViewList)
	ON_COMMAND(ID_VIEW_SMALLICONS, OnViewSmallIcons)
	ON_COMMAND(ID_VIEW_DETAILS, OnViewDetails)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DETAILS, OnUpdateViewDetails)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGEICONS, OnUpdateViewLargeIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, OnUpdateViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALLICONS, OnUpdateViewSmallIcons)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CExplorerDoc::CExplorerDoc()
{
	m_uStyle=STYLE_ICON;
}

CExplorerDoc::~CExplorerDoc()
{
}

BOOL CExplorerDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())return FALSE;

	return TRUE;
}

void CExplorerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CExplorerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExplorerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

void CExplorerDoc::OnViewLargeIcons() 
{
	CExplorerView *pView;
	LONG lStyle;

	pView=GetCExplorerView();
	lStyle=::GetWindowLong(pView->GetListCtrl().GetSafeHwnd(), GWL_STYLE);
	lStyle&=~(LVS_TYPEMASK);
	lStyle|=LVS_ICON;
	SetWindowLong(pView->GetListCtrl().GetSafeHwnd(), GWL_STYLE, lStyle);
	m_uStyle=STYLE_ICON;
}

void CExplorerDoc::OnViewList() 
{
	CExplorerView *pView;
	LONG lStyle;

	pView=GetCExplorerView();
	lStyle=::GetWindowLong(pView->GetListCtrl().GetSafeHwnd(), GWL_STYLE);
	lStyle&=~(LVS_TYPEMASK);
	lStyle|=LVS_LIST;
	SetWindowLong(pView->GetListCtrl().GetSafeHwnd(), GWL_STYLE, lStyle);
	m_uStyle=STYLE_LIST;
}

void CExplorerDoc::OnViewSmallIcons() 
{
	CExplorerView *pView;
	LONG lStyle;

	pView=GetCExplorerView();
	lStyle=::GetWindowLong(pView->GetListCtrl().GetSafeHwnd(), GWL_STYLE);
	lStyle&=~(LVS_TYPEMASK);
	lStyle|=LVS_SMALLICON;
	SetWindowLong(pView->GetListCtrl().GetSafeHwnd(), GWL_STYLE, lStyle);
	m_uStyle=STYLE_SMALLICON;
}

void CExplorerDoc::OnViewDetails() 
{
	CExplorerView *pView;
	LONG lStyle;

	pView=GetCExplorerView();
	lStyle=::GetWindowLong(pView->GetListCtrl().GetSafeHwnd(), GWL_STYLE);
	lStyle&=~(LVS_TYPEMASK);
	lStyle|=LVS_REPORT;
	SetWindowLong(pView->GetListCtrl().GetSafeHwnd(), GWL_STYLE, lStyle);
	m_uStyle=STYLE_REPORT;
}

CExplorerView *CExplorerDoc::GetCExplorerView()
{
	CExplorerView *pView;
	POSITION posi;

	posi=GetFirstViewPosition();
	while(posi != NULL)
	{
		pView=(CExplorerView *)GetNextView(posi);
		if(pView->IsKindOf(RUNTIME_CLASS(CExplorerView)))break;
	}

	return pView;
}

void CExplorerDoc::OnUpdateViewDetails(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_uStyle == STYLE_REPORT);	
}

void CExplorerDoc::OnUpdateViewLargeIcons(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_uStyle == STYLE_ICON);
}

void CExplorerDoc::OnUpdateViewList(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_uStyle == STYLE_LIST);
}

void CExplorerDoc::OnUpdateViewSmallIcons(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_uStyle == STYLE_SMALLICON);
}
