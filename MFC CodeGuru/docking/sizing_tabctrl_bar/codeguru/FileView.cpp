// FileView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "FileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

IMPLEMENT_DYNCREATE(CFileView, CTreeView)

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}


BEGIN_MESSAGE_MAP(CFileView, CTreeView)
	//{{AFX_MSG_MAP(CFileView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CFileView 

void CFileView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CFileView

#ifdef _DEBUG
void CFileView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CFileView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CFileView 

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetTreeCtrl().ModifyStyle(0, 
		TVS_HASBUTTONS|TVS_LINESATROOT|TVS_HASLINES|TVS_SHOWSELALWAYS);

	HTREEITEM hRootItem = GetTreeCtrl().InsertItem("Files",0,0);
	
	for (int i=0; i<5; i++)
	{
		CString strItem;
		strItem.Format("File %d", i);
		GetTreeCtrl().InsertItem(strItem,i,i,hRootItem);
	}
	
	GetTreeCtrl().SelectItem(hRootItem);
	GetTreeCtrl().Expand(hRootItem, TVE_EXPAND);
	
	return 0;
}
