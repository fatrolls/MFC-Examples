// ex06aView.cpp : implementation of the CEx06aView class
//

#include "stdafx.h"
#include "ex06a.h"

#include "ex06aDoc.h"
#include "ex06aView.h"
#include "ex06aDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx06aView

IMPLEMENT_DYNCREATE(CEx06aView, CView)

BEGIN_MESSAGE_MAP(CEx06aView, CView)
	//{{AFX_MSG_MAP(CEx06aView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx06aView construction/destruction

CEx06aView::CEx06aView()
{
	// TODO: add construction code here

}

CEx06aView::~CEx06aView()
{
}

BOOL CEx06aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx06aView drawing

void CEx06aView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx06aView diagnostics

#ifdef _DEBUG
void CEx06aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx06aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx06aDoc* CEx06aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx06aDoc)));
	return (CEx06aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx06aView message handlers

void CEx06aView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CEx06aDialog dlg;
	dlg.m_strName  = "Shakespeare, Will";
	dlg.m_nSsn     = 307806636;
	dlg.m_nCat     = 1;  // 0 = hourly, 1 = salary
	dlg.m_strBio   = "This person is not a well-motivated tech writer";
	dlg.m_bInsLife = TRUE;
	dlg.m_bInsDis  = FALSE;
	dlg.m_bInsMed  = TRUE;
	dlg.m_strDept  = "Documentation";
	dlg.m_strSkill = "Writer";
	dlg.m_strLang  = "English";
	dlg.m_strEduc  = "College";
	dlg.m_nLoyal = dlg.m_nRely = 50;
	int ret = dlg.DoModal();
	TRACE("DoModal return = %d\n", ret);
	TRACE("name = %s, ssn = %d, cat = %d\n",
	      dlg.m_strName, dlg.m_nSsn, dlg.m_nCat);
	TRACE("dept = %s, skill = %s, lang = %s, educ = %s\n",
	      dlg.m_strDept, dlg.m_strSkill, dlg.m_strLang, dlg.m_strEduc);
	TRACE("life = %d, dis = %d, med = %d, bio = %s\n",
	      dlg.m_bInsLife, dlg.m_bInsDis, dlg.m_bInsMed, dlg.m_strBio);
	TRACE("loyalty = %d, reliability = %d\n",
	      dlg.m_nLoyal, dlg.m_nRely);
}
