// CustTbl.cpp : implementation of the CCustomersTable class
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoSet.h"
#include "CustSet.h"
#include "DaoDoc.h"
#include "TblView.h"
#include "CustTbl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomersTable

IMPLEMENT_DYNCREATE(CCustomersTable, CDaoTableView)

BEGIN_MESSAGE_MAP(CCustomersTable, CDaoTableView)
	//{{AFX_MSG_MAP(CCustomersTable)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomersTable construction/destruction

CCustomersTable::CCustomersTable()
{
	m_pCustomersSet = NULL;
}

CCustomersTable::~CCustomersTable()
{
}

BOOL CCustomersTable::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CDaoTableView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomersTable drawing

void CCustomersTable::OnDraw(CDC* pDC)
{
	CMSDIDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CCustomersTable::OnInitialUpdate()
{
	CMSDIDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_pCustomersSet = pDoc->OpenCustomers();
	CDaoTableView::OnInitialUpdate();
}

void CCustomersTable::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CDaoTableView::OnUpdate(pSender, lHint, pHint);
}

CDaoRecordset *CCustomersTable::OnGetRecordset()
{
	return (CDaoRecordset*)m_pCustomersSet;
}

long CCustomersTable::GetRecordCount()
{
	ASSERT(m_pCustomersSet != NULL);
	return m_pCustomersSet->GetRecordCount();
}

/////////////////////////////////////////////////////////////////////////////
// CCustomersTable printing

void CCustomersTable::GetPrintTitle(CString& strTitle)
{
  strTitle = "Customers";
}

BOOL CCustomersTable::OnPreparePrinting(CPrintInfo* pInfo)
{
  return CDaoTableView::OnPreparePrinting(pInfo);
}

void CCustomersTable::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
  CDaoTableView::OnBeginPrinting(pDC, pInfo);
}

void CCustomersTable::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
  CDaoTableView::OnPrint(pDC, pInfo);
}

void CCustomersTable::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
  CDaoTableView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomersTable diagnostics

#ifdef _DEBUG
void CCustomersTable::AssertValid() const
{
	CDaoTableView::AssertValid();
}

void CCustomersTable::Dump(CDumpContext& dc) const
{
	CDaoTableView::Dump(dc);
}

CMSDIDaoDoc* CCustomersTable::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSDIDaoDoc)));
	return (CMSDIDaoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomersTable message handlers

void CCustomersTable::OnDestroy()
{
	CMSDIDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (m_pCustomersSet) pDoc->CloseCustomers();
	CDaoTableView::OnDestroy();
}
