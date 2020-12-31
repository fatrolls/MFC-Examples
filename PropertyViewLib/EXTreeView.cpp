// NaviPlotTreeView.cpp : implementation file
//

#include "stdafx.h"
//#include "naviplot.h"
//#include "NaviPlotDoc.h"
#include "TreeCtrlResource.h"

//#include "Eframe.h"
//#include "EBaseItem.h"
//#include "ITreeMember.h"
#include "EXTreeView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EXTreeView

IMPLEMENT_DYNCREATE(EXTreeView, CView)

EXTreeView::EXTreeView()
{
}

EXTreeView::~EXTreeView()
{
}


BEGIN_MESSAGE_MAP(EXTreeView, CView)
	//{{AFX_MSG_MAP(EXTreeView)
	ON_WM_CREATE()
	ON_WM_SIZE()
//	ON_COMMAND(ID_EDIT_MOVEUP, OnEditMoveup)
//	ON_COMMAND(ID_EDIT_MOVEDOWN, OnEditMovedown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EXTreeView drawing

void EXTreeView::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// EXTreeView diagnostics

#ifdef _DEBUG
void EXTreeView::AssertValid() const
{
	CView::AssertValid();
}

void EXTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// EXTreeView message handlers

int EXTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);
	m_tree.Create(WS_VISIBLE , rect, this, 100);

	return 0;
}

void EXTreeView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);
	m_tree.MoveWindow(&rect);
}


void EXTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	IXTreeItem* pTreeMember = (IXTreeItem*)pHint;

	m_tree.m_bDontSend = true;

	switch(lHint)
	{
	case WM_TREECTRL_SELCHANGED:
		{
			m_tree.SelectDataItem(pTreeMember);
		}
		break;
	case WM_TREECTRL_REFRESH:
		{
			m_tree.RefreshDataItem(pTreeMember);
		}
		break;
	}

	m_tree.m_bDontSend = false;

}

void EXTreeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	m_tree.InitTree(NULL,0);
}


