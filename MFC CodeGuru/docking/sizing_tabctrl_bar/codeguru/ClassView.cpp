// ClassView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "ClassView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassView

IMPLEMENT_DYNCREATE(CClassView, CTreeView)

CClassView::CClassView()
{
}

CClassView::~CClassView()
{
}


BEGIN_MESSAGE_MAP(CClassView, CTreeView)
	//{{AFX_MSG_MAP(CClassView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CClassView 

void CClassView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CClassView

#ifdef _DEBUG
void CClassView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CClassView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CClassView 

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetTreeCtrl().ModifyStyle(0, 
		TVS_HASBUTTONS|TVS_LINESATROOT|TVS_HASLINES|TVS_SHOWSELALWAYS);

	HTREEITEM hRootItem = GetTreeCtrl().InsertItem("Classes",0,0);
	
	for (int i=0; i<10; i++)
	{
		CString strItem;
		strItem.Format("Class %d", i);
		GetTreeCtrl().InsertItem(strItem,i,i,hRootItem);
	}
	
	GetTreeCtrl().SelectItem(hRootItem);
	GetTreeCtrl().Expand(hRootItem, TVE_EXPAND);
	
	return 0;
}
