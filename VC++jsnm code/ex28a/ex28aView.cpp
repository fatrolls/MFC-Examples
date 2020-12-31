// ex28aView.cpp : implementation of the CEx28aView class
//

#include "stdafx.h"
#include "ex28a.h"
#include "ex28aSet.h"
#include "ex28aDoc.h"
#include "ex28aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28aView

IMPLEMENT_DYNCREATE(CEx28aView, CScrollView)

BEGIN_MESSAGE_MAP(CEx28aView, CScrollView)
	//{{AFX_MSG_MAP(CEx28aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28aView construction/destruction

CEx28aView::CEx28aView()
{
	// TODO: add construction code here

}

CEx28aView::~CEx28aView()
{
}

BOOL CEx28aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx28aView drawing

void CEx28aView::OnDraw(CDC* pDC)
{
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight=tm.tmHeight+tm.tmExternalLeading;
	CPoint pText(0,0);

	int y = 0;
    CString str;
    if (m_pSet->IsBOF()) { // detects empty recordset
      return;
    }
    m_pSet->MoveFirst();   // fails if recordset is empty
    while (!m_pSet->IsEOF()) {
	  str.Format("%ld", m_pSet->m_StudentID);
      pDC->TextOut(pText.x, pText.y, str);
      pDC->TextOut(pText.x+1000, pText.y, m_pSet->m_Name);
      str.Format("%d", m_pSet->m_GradYear);
      pDC->TextOut(pText.x+4000, pText.y, str);
	  pDC->TextOut(pText.x+5000, pText.y, m_pSet->m_CourseID);
      m_pSet->MoveNext();
	  pText.y -= nLineHeight;

    }
}

void CEx28aView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal(8000, 10500);

    SetScrollSizes(MM_HIENGLISH, sizeTotal);
    
    m_pSet = &GetDocument()->m_ex28aSet;
	// Remember that documents/views are reused in SDI applications!
	m_pSet->m_strFilter="[Student].[StudentID]=[Enrollment].[StudentID]";
    
    if (m_pSet->IsOpen()) {
		m_pSet->Close();
    }
    m_pSet->Open();
}

/////////////////////////////////////////////////////////////////////////////
// CEx28aView printing

BOOL CEx28aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx28aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx28aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx28aView diagnostics

#ifdef _DEBUG
void CEx28aView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx28aView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx28aDoc* CEx28aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx28aDoc)));
	return (CEx28aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28aView message handlers
