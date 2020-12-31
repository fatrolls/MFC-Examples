// CategTbl.cpp : implementation of the CCategoriesTable class
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoBmp.h"
#include "DaoSet.h"
#include "CategSet.h"
#include "DaoDoc.h"
#include "TblView.h"
#include "CategTbl.h"
#include "CategVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCategoriesTable

IMPLEMENT_DYNCREATE(CCategoriesTable, CDaoTableView)

BEGIN_MESSAGE_MAP(CCategoriesTable, CDaoTableView)
	//{{AFX_MSG_MAP(CCategoriesTable)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCategoriesTable construction/destruction

CCategoriesTable::CCategoriesTable()
{
	m_pCategoriesSet = NULL;
}

CCategoriesTable::~CCategoriesTable()
{
}

BOOL CCategoriesTable::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CDaoTableView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCategoriesTable drawing

void CCategoriesTable::OnDraw(CDC* pDC)
{
	CMSDIDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CCategoriesTable::OnInitialUpdate()
{
	CMSDIDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_pCategoriesSet = pDoc->OpenCategories();
	CDaoTableView::OnInitialUpdate();
}

void CCategoriesTable::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CDaoTableView::OnUpdate(pSender, lHint, pHint);
}

CDaoRecordset *CCategoriesTable::OnGetRecordset()
{
	return (CDaoRecordset*)m_pCategoriesSet;
}

long CCategoriesTable::GetRecordCount()
{
	ASSERT(m_pCategoriesSet != NULL);
	return m_pCategoriesSet->GetRecordCount();
}

/////////////////////////////////////////////////////////////////////////////
// CCategoriesTable printing

void CCategoriesTable::GetPrintTitle(CString& strTitle)
{
  strTitle = "Categories";
}

BOOL CCategoriesTable::OnPreparePrinting(CPrintInfo* pInfo)
{
  return CDaoTableView::OnPreparePrinting(pInfo);
}

void CCategoriesTable::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
  CDaoTableView::OnBeginPrinting(pDC, pInfo);
}

void CCategoriesTable::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
  CDaoTableView::OnPrint(pDC, pInfo);
}

void CCategoriesTable::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
  CDaoTableView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CCategoriesTable diagnostics

#ifdef _DEBUG
void CCategoriesTable::AssertValid() const
{
	CDaoTableView::AssertValid();
}

void CCategoriesTable::Dump(CDumpContext& dc) const
{
	CDaoTableView::Dump(dc);
}

CMSDIDaoDoc* CCategoriesTable::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSDIDaoDoc)));
	return (CMSDIDaoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCategoriesTable message handlers

void CCategoriesTable::OnDestroy()
{
	CMSDIDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (m_pCategoriesSet) pDoc->CloseCategories();
	CDaoTableView::OnDestroy();
}

void CCategoriesTable::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMSDIDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDaoTableView::OnDblclk(pNMHDR, pResult);
	theApp.CreateOrActivateFrame(RUNTIME_CLASS(CCategoriesView), pDoc);
}

void CCategoriesTable::OnReturn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMSDIDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDaoTableView::OnReturn(pNMHDR, pResult);
	theApp.CreateOrActivateFrame(RUNTIME_CLASS(CCategoriesView), pDoc);
}
