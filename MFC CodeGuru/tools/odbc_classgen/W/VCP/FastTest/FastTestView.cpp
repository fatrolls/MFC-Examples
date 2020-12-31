// FastTestView.cpp : implementation of the CFastTestView class
//

#include "stdafx.h"
#include "FastTest.h"

#include "FastTestDoc.h"
#include "FastTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFastTestView

IMPLEMENT_DYNCREATE(CFastTestView, CListView)

BEGIN_MESSAGE_MAP(CFastTestView, CListView)
	//{{AFX_MSG_MAP(CFastTestView)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFastTestView construction/destruction

CFastTestView::CFastTestView()
{
	// TODO: add construction code here
    m_pLocationsSet = NULL;

}

CFastTestView::~CFastTestView()
{
    if  (m_pLocationsSet)
        delete m_pLocationsSet;
}

BOOL CFastTestView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.lpszName = WC_LISTVIEW;
	cs.style    &= ~LVS_TYPEMASK;
	cs.style    |= LVS_REPORT;
	cs.style    |= LVS_OWNERDATA;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFastTestView drawing

void CFastTestView::OnDraw(CDC* pDC)
{
	CFastTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CFastTestView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

    m_pLocationsSet = new CLocationsSet(&theApp.m_DB);

    int nCount = m_pLocationsSet->Load();

	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

	GetListCtrl().SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));
	
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

    GetListCtrl().SendMessage(LVM_SETITEMCOUNT, (WPARAM)nCount , (LPARAM)LVSICF_NOINVALIDATEALL);

}
/////////////////////////////////////////////////////////////////////////////
// CFastTestView diagnostics

#ifdef _DEBUG
void CFastTestView::AssertValid() const
{
	CListView::AssertValid();
}

void CFastTestView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFastTestDoc* CFastTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFastTestDoc)));
	return (CFastTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFastTestView message handlers

void CFastTestView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    *pResult = 0;
    char    strBuffer[20];

    int nIndex = pDispInfo->item.iItem;

    if  (!m_pLocationsSet)
        return;

    if  (0 == m_pLocationsSet->m_aData.GetSize())
        return;


    pDB_LOCATIONS_FIELDS    pData = m_pLocationsSet->m_aData.GetAt(nIndex);



    if  ( pDispInfo->item.mask & LVIF_TEXT)
    {
	    switch  (pDispInfo->item.iSubItem)
        {
        case 0: // Main Item
            sprintf(strBuffer,"%d", nIndex +1);
            lstrcpy(pDispInfo->item.pszText, strBuffer);
            break;
        case 1:
            lstrcpy(pDispInfo->item.pszText, pData->m_Code);
            break;
        case 2:
            lstrcpy(pDispInfo->item.pszText, pData->m_Name);
            break;
        }
    }
}
