// SlowView.cpp : implementation file
//

#include "stdafx.h"
#include "FastTest.h"
#include "SlowView.h"
#include "SlowSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlowView

IMPLEMENT_DYNCREATE(CSlowView, CListView)

CSlowView::CSlowView()
{
}

CSlowView::~CSlowView()
{
}


BEGIN_MESSAGE_MAP(CSlowView, CListView)
	//{{AFX_MSG_MAP(CSlowView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlowView drawing

void CSlowView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSlowView diagnostics

#ifdef _DEBUG
void CSlowView::AssertValid() const
{
	CListView::AssertValid();
}

void CSlowView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSlowView message handlers

void CSlowView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();

    GetParent()->SetWindowText("Slow View");
	
	LV_COLUMN lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvColumn.fmt = LVCFMT_LEFT;

	lvColumn.cx = 100;
    lvColumn.pszText = "Sl. #";
    lvColumn.cchTextMax  = strlen(lvColumn.pszText);

    GetListCtrl().InsertColumn(0, &lvColumn);

	lvColumn.cx = 120;
    lvColumn.pszText = "Code";
    lvColumn.cchTextMax  = strlen(lvColumn.pszText);

    GetListCtrl().InsertColumn(1, &lvColumn);

	lvColumn.cx = 500;
    lvColumn.pszText = "Name";
    lvColumn.cchTextMax  = strlen(lvColumn.pszText);

    GetListCtrl().InsertColumn(2, &lvColumn);


    CSlowSet    SlowSet(&theApp.m_DB);

    SlowSet.Open();

    int     nIndex = 0;
    char    strBuffer[20];
    while   (!SlowSet.IsEOF())
    {
        sprintf(strBuffer,"%d", nIndex + 1);
        nIndex = GetListCtrl().InsertItem(nIndex,strBuffer);
        GetListCtrl().SetItemText(nIndex,1,SlowSet.m_CODE);
        GetListCtrl().SetItemText(nIndex,2,SlowSet.m_NAME);
        nIndex++;

        SlowSet.MoveNext();
    }

    SlowSet.Close();
	
}

BOOL CSlowView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style    |= LVS_REPORT;
	
	return CListView::PreCreateWindow(cs);
}
