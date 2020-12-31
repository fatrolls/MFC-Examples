// ResourceView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "ResourceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceView

IMPLEMENT_DYNCREATE(CResourceView, CTreeView)

CResourceView::CResourceView()
{
}

CResourceView::~CResourceView()
{
}


BEGIN_MESSAGE_MAP(CResourceView, CTreeView)
	//{{AFX_MSG_MAP(CResourceView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CResourceView 

void CResourceView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CResourceView

#ifdef _DEBUG
void CResourceView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CResourceView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CResourceView 

int CResourceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetTreeCtrl().ModifyStyle(0, 
		TVS_HASBUTTONS|TVS_LINESATROOT|TVS_HASLINES|TVS_SHOWSELALWAYS);

	HTREEITEM hRootItem = GetTreeCtrl().InsertItem("Resources",0,0);
	
	for (int i=0; i<15; i++)
	{
		CString strItem;
		strItem.Format("Resource %d", i);
		GetTreeCtrl().InsertItem(strItem,i,i,hRootItem);
	}
	
	GetTreeCtrl().SelectItem(hRootItem);
	GetTreeCtrl().Expand(hRootItem, TVE_EXPAND);
	
	return 0;
}
