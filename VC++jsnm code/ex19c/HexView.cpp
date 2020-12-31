// HexView.cpp : implementation of the CHexView class
//

#include "stdafx.h"
#include "ex19c.h"

#include "PoemDoc.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexView

IMPLEMENT_DYNCREATE(CHexView, CLogScrollView)

BEGIN_MESSAGE_MAP(CHexView, CLogScrollView)
	//{{AFX_MSG_MAP(CHexView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CLogScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CLogScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CLogScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexView construction/destruction

CHexView::CHexView() : m_rectPrint(0, 0, 11520, -15120)
{
}

CHexView::~CHexView()
{
}

BOOL CHexView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CLogScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHexView drawing

void CHexView::OnDraw(CDC* pDC)
{
	// hex dump of document strings
	int        i, j, k, l, n, nHeight;
	CString    outputLine, str;
	CFont      font;
	TEXTMETRIC tm;

	CPoemDoc* pDoc = GetDocument();
	font.CreateFont(-160, 80, 0, 0, 400, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
	CFont* pOldFont = pDC->SelectObject(&font);
	pDC->GetTextMetrics(&tm);
	nHeight = tm.tmHeight + tm.tmExternalLeading;

	j = pDoc->m_stringArray.GetSize();
	for (i = 0; i < j; i++) {
		outputLine.Format("%02x   ", i);
		l = pDoc->m_stringArray[i].GetLength();
		for (k = 0; k < l; k++) {
			n = pDoc->m_stringArray[i][k] & 0x00ff;
			str.Format("%02x ", n);
			outputLine += str;
		}
		pDC->TextOut(720, -i * nHeight - 720, outputLine);
	}
	pDC->SelectObject(pOldFont);
}

void CHexView::OnInitialUpdate()
{
	CLogScrollView::OnInitialUpdate();
	CSize sizeTotal(m_rectPrint.Width(), -m_rectPrint.Height());
	SetLogScrollSizes(sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CHexView printing

BOOL CHexView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
}

void CHexView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHexView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHexView diagnostics

#ifdef _DEBUG
void CHexView::AssertValid() const
{
	CLogScrollView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
	CLogScrollView::Dump(dc);
}

CPoemDoc* CHexView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoemDoc)));
	return (CPoemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHexView message handlers

void CHexView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_rectPrint = pInfo->m_rectDraw;
	SetLogScrollSizes(CSize(m_rectPrint.Width(), -m_rectPrint.Height()));
	CLogScrollView::OnPrint(pDC, pInfo);
}
