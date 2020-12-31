// StringView.cpp : implementation of the CStringView class
//

#include "stdafx.h"
#include "ex19c.h"

#include "PoemDoc.h"
#include "StringView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStringView

IMPLEMENT_DYNCREATE(CStringView, CLogScrollView)

BEGIN_MESSAGE_MAP(CStringView, CLogScrollView)
	//{{AFX_MSG_MAP(CStringView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CLogScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CLogScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CLogScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStringView construction/destruction

CStringView::CStringView() : m_rectPrint(0, 0, 11520, -15120)
{
}

CStringView::~CStringView()
{
}

BOOL CStringView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CLogScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStringView drawing

void CStringView::OnDraw(CDC* pDC)
{
	int        i, j, nHeight;
	CString    str;
	CFont      font;
	TEXTMETRIC tm;

	CPoemDoc* pDoc = GetDocument();
	// Draw a border, slightly smaller to avoid truncation
	pDC->Rectangle(m_rectPrint + CRect(0, 0, -20, 20));
	// Draw horizontal and vertical rulers
	j = m_rectPrint.Width() / 1440;
	for (i = 0; i <= j; i++) {
		str.Format("%02d", i);
		pDC->TextOut(i * 1440, 0, str);
	}
	j = - m_rectPrint.Height() / 1440;
	for (i = 0; i <= j; i++) {
		str.Format("%02d", i);
		pDC->TextOut(0, -i * 1440, str);
	}
	// Print the poem 0.5 inch down and over;
	//  use 10-point roman font
	font.CreateFont(-200, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET,
	                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	                DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
	                "Times New Roman");
	CFont* pOldFont = (CFont*) pDC->SelectObject(&font);
	pDC->GetTextMetrics(&tm);
	nHeight = tm.tmHeight + tm.tmExternalLeading;
	TRACE("font height = %d, internal leading = %d\n",
	      nHeight, tm.tmInternalLeading);
	j = pDoc->m_stringArray.GetSize();
	for (i = 0; i < j; i++) {
		pDC->TextOut(720, -i * nHeight - 720, pDoc->m_stringArray[i]);
	}
	pDC->SelectObject(pOldFont);
	TRACE("LOGPIXELSX = %d, LOGPIXELSY = %d\n",
	      pDC->GetDeviceCaps(LOGPIXELSX),
	      pDC->GetDeviceCaps(LOGPIXELSY));
	TRACE("HORZSIZE = %d, VERTSIZE = %d\n",
	      pDC->GetDeviceCaps(HORZSIZE),
	      pDC->GetDeviceCaps(VERTSIZE));
}

void CStringView::OnInitialUpdate()
{
	CLogScrollView::OnInitialUpdate();
	CSize sizeTotal(m_rectPrint.Width(), -m_rectPrint.Height());
	SetLogScrollSizes(sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CStringView printing

BOOL CStringView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
}

void CStringView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStringView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CStringView diagnostics

#ifdef _DEBUG
void CStringView::AssertValid() const
{
	CLogScrollView::AssertValid();
}

void CStringView::Dump(CDumpContext& dc) const
{
	CLogScrollView::Dump(dc);
}

CPoemDoc* CStringView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoemDoc)));
	return (CPoemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStringView message handlers

void CStringView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_rectPrint = pInfo->m_rectDraw;
	SetLogScrollSizes(CSize(m_rectPrint.Width(), -m_rectPrint.Height()));
	CLogScrollView::OnPrint(pDC, pInfo);
}
