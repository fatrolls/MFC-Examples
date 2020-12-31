// StatisticsView.cpp : implementation file
//

#include "stdafx.h"
#include "tabviews.h"

#include "TabViewsDoc.h"
#include "TabViewsView.h"
#include "StatisticsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatisticsView

IMPLEMENT_DYNCREATE(CStatisticsView, CListView)

CStatisticsView::CStatisticsView()
{
}

CStatisticsView::~CStatisticsView()
{
}


BEGIN_MESSAGE_MAP(CStatisticsView, CListView)
	//{{AFX_MSG_MAP(CStatisticsView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatisticsView drawing

void CStatisticsView::OnDraw(CDC* pDC)
{
	// TODO: add draw code here

	UNREFERENCED_PARAMETER(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CStatisticsView diagnostics

#ifdef _DEBUG
void CStatisticsView::AssertValid() const
{
	CListView::AssertValid();
}

void CStatisticsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CTabViewsDoc* CStatisticsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabViewsDoc)));
	return (CTabViewsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatisticsView message handlers

BOOL CStatisticsView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void CStatisticsView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(bActivate && pActivateView==this)
	{
		SetRedraw(FALSE);
		Populate();
		SetRedraw(TRUE);
		RedrawWindow();
	}

	CListView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CStatisticsView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	Populate(TRUE);
}

void CStatisticsView::Populate(BOOL bForFirstTime/*=FALSE*/)
{
	CTabViewsDoc* pDoc=(CTabViewsDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	CTabViewsView* pPrimaryView=(CTabViewsView*)pDoc->GetPrimaryView();
	ASSERT_VALID(pPrimaryView);

	if(!bForFirstTime && !pPrimaryView->GetEditCtrl().GetModify())
		return;

	GetListCtrl().DeleteAllItems();

	CMap<TCHAR, TCHAR&, int, int&> arrCharacters;
	UINT nMaxIndex=pPrimaryView->GetBufferLength();
	LPCTSTR pData=pPrimaryView->LockBuffer();
	ASSERT(pData!=NULL);

	int nIndex=0;
	for(nIndex=0; nIndex<(int)nMaxIndex; nIndex++)
	{
		if(_istprint(pData[nIndex]))
		{
			int nCount;
			if(!arrCharacters.Lookup((TCHAR)pData[nIndex],nCount))
				nCount=0;
			nCount++;
			arrCharacters.SetAt((TCHAR)pData[nIndex],nCount);
		}
	}

	nIndex=0;
	POSITION pos=arrCharacters.GetStartPosition();
	while(pos!=NULL)
	{
		int nCount;
		TCHAR chr;
		arrCharacters.GetNextAssoc(pos,chr,nCount);
		CString sChar=chr;
		if(chr==32)
		{
			sChar=_T("Space");
		}

		VERIFY(GetListCtrl().InsertItem(nIndex,sChar)!=-1);

		CString sCount;
		sCount.Format(_T("%u"),nCount);
		VERIFY(GetListCtrl().SetItemText(nIndex,1,sCount));

		nIndex++;
	}

	pPrimaryView->UnlockBuffer();
}

int CStatisticsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	LV_COLUMN lvc;
	lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
	lvc.fmt=LVCFMT_LEFT;
	lvc.iSubItem=0;
	lvc.cx=75;
	lvc.pszText=_T("Character");
	GetListCtrl().InsertColumn(0,&lvc);

	lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
	lvc.fmt=LVCFMT_CENTER;
	lvc.iSubItem=1;
	lvc.cx=50;
	lvc.pszText=_T("Count");
	GetListCtrl().InsertColumn(1,&lvc);

	return 0;
}
