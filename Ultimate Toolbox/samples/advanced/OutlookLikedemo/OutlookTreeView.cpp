// OutlookTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "Outlook.h"
#include "OutlookTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutlookTreeView

IMPLEMENT_DYNCREATE(COutlookTreeView, CTreeView)

COutlookTreeView::COutlookTreeView()
{
}

COutlookTreeView::~COutlookTreeView()
{
}


BEGIN_MESSAGE_MAP(COutlookTreeView, CTreeView)
	//{{AFX_MSG_MAP(COutlookTreeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookTreeView drawing

void COutlookTreeView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);

	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// COutlookTreeView diagnostics

#ifdef _DEBUG
void COutlookTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void COutlookTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutlookTreeView message handlers

void COutlookTreeView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	const COLORREF rgb = RGB(255, 0, 255);

	TV_INSERTSTRUCT	tvstruct;
	TCHAR rgszItems[][20] = { _T("Mail Box"), _T("Calendar"), _T("Deleted Items"), _T("Inbox"), _T("Journal"), _T("Notes"), _T("Outbox"), _T("Sent Items") };

	VERIFY(m_ilTree.Create(IDB_BITMAP3, 16, 8, rgb));
	GetTreeCtrl().SetImageList(&m_ilTree, TVSIL_NORMAL);

	HTREEITEM hParent = NULL;
	for (int nIndex = 0; nIndex < (sizeof(rgszItems) / sizeof(rgszItems[0])); nIndex++)
	{
		tvstruct.hParent = nIndex == 0 ? NULL : hParent;
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.iImage = nIndex;
		tvstruct.item.iSelectedImage = nIndex;
		tvstruct.item.pszText = rgszItems[nIndex];
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		HTREEITEM hItem = GetTreeCtrl().InsertItem(&tvstruct);
		hParent = hParent == NULL ? hItem : hParent;
	}

	GetTreeCtrl().Expand(GetTreeCtrl().GetRootItem(), TVE_EXPAND);
}

BOOL COutlookTreeView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_HASBUTTONS;
		
	return CTreeView::PreCreateWindow(cs);
}
