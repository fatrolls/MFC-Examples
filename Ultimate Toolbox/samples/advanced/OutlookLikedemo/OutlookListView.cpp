// OutlookListView.cpp : implementation file
//

#include "stdafx.h"
#include "Outlook.h"
#include "OutlookListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutlookListView

IMPLEMENT_DYNCREATE(COutlookListView, CListView)

COutlookListView::COutlookListView()
{
}

COutlookListView::~COutlookListView()
{
}


BEGIN_MESSAGE_MAP(COutlookListView, CListView)
	//{{AFX_MSG_MAP(COutlookListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookListView drawing

void COutlookListView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);

	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// COutlookListView diagnostics

#ifdef _DEBUG
void COutlookListView::AssertValid() const
{
	CListView::AssertValid();
}

void COutlookListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutlookListView message handlers

BOOL COutlookListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL | LVS_SORTASCENDING;
		
	return CListView::PreCreateWindow(cs);
}

void COutlookListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	static LPTSTR lpszColumns[3] = { _T("Name"), _T("City"), _T("Title") };

	m_ilList.Create(IDB_BITMAP4, 16, 1, RGB(255, 0, 255));
	GetListCtrl().SetImageList(&m_ilList, LVSIL_SMALL);
	
	LV_COLUMN lvc;
	ZeroMemory((void*) &lvc, sizeof(lvc));

	int i = 0;
	for (i = 0; i < 3; i++)
	{
		lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvc.fmt = LVCFMT_LEFT;
		lvc.pszText = lpszColumns[i];
		lvc.cx = i == 0 ? 200 : 100;
		lvc.cchTextMax = 30;

		GetListCtrl().InsertColumn(i, &lvc);
	}

	static const int nCount = 8;
	static LPCTSTR lpszNames[nCount] = 
	{ 
		_T("John McDonald"), 
		_T("Mary Bolten"), 
		_T("Bob Jackson"), 
		_T("Markus Brody"),
		_T("Elizabeth Sizeberg"),
		_T("Janna Stevens"), 
		_T("Martha Lenton"), 
		_T("Margaret Atwal") 
	};
	static LPCTSTR lpszCities[nCount] = 
	{ 
		_T("Toronto"), 
		_T("New York"),
		_T("Neice"), 
		_T("Mexico City"),
		_T("Berlin"), 
		_T("Zurich"), 
		_T("Rome"), 
		_T("Madrid")
	};
	static LPCTSTR lpszTitle[nCount] = 
	{
		_T("CEO"), 
		_T("Head Chef"), 
		_T("Computer Programmer"), 
		_T("Engineer"), 
		_T("Shipper"), 
		_T("Consultant"), 
		_T("Professional Athlete"), 
		_T("Singer") 
	};

	for (i = 0; i < nCount; i++)
	{
		int iItem = GetListCtrl().InsertItem(LVIF_TEXT | LVIF_IMAGE, i, lpszNames[i], NULL, NULL, 0, NULL);
		GetListCtrl().SetItem(iItem, 1, LVIF_TEXT, lpszCities[i], NULL, NULL, NULL, NULL);
		GetListCtrl().SetItem(iItem, 2, LVIF_TEXT, lpszTitle[i], NULL, NULL, NULL, NULL);
	}
}
