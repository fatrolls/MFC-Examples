// HexView.cpp : implementation of the CHexView class
//

#include "stdafx.h"
#include "HexDump.h"

#include "HexDoc.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PRINTMARGIN 2

/////////////////////////////////////////////////////////////////////////////
// CHexView

IMPLEMENT_DYNCREATE(CHexView, CScrollView)

BEGIN_MESSAGE_MAP(CHexView, CScrollView)
	//{{AFX_MSG_MAP(CHexView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexView construction/destruction

CHexView::CHexView()
{
}

CHexView::~CHexView()
{
}

BOOL CHexView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHexView drawing

void CHexView::OnDraw(CDC* pDC)
{
	CHexDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    if (m_nLinesTotal != 0) {
        CRect rect;
        pDC->GetClipBox (&rect);

        UINT nStart = rect.top / m_cyScreen;
        UINT nEnd = min (m_nLinesTotal - 1,
            (rect.bottom + m_cyScreen - 1) / m_cyScreen);

        CFont* pOldFont = pDC->SelectObject (&m_fontScreen);
        for (UINT i=nStart; i<=nEnd; i++) {
	        CString string;
            FormatLine (pDoc, i, string);
            pDC->TextOut (2, (i * m_cyScreen) + 2, string);
        }
        pDC->SelectObject (pOldFont);
    }
}

void CHexView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    UINT nDocLength = GetDocument ()->GetDocumentLength ();
    m_nLinesTotal = (nDocLength + 15) / 16;

    SetScrollSizes (MM_TEXT, CSize (0, m_nLinesTotal * m_cyScreen),
        CSize (0, m_cyScreen * 10), CSize (0, m_cyScreen));
    ScrollToPosition (CPoint (0, 0));
}

/////////////////////////////////////////////////////////////////////////////
// CHexView printing

BOOL CHexView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHexView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	//
	// Create a printer font.
	//
    m_fontPrinter.CreatePointFont (100, _T ("Courier New"), pDC);

	//
	// Compute the width and height of a line in the printer font.
	//
    TEXTMETRIC tm;
    CFont* pOldFont = pDC->SelectObject (&m_fontPrinter);
    pDC->GetTextMetrics (&tm);
    m_cyPrinter = tm.tmHeight + tm.tmExternalLeading;
    CSize size = pDC->GetTextExtent (_T ("---------1---------2---------" \
        "3---------4---------5---------6---------7---------8-"), 81);
    pDC->SelectObject (pOldFont);
    m_cxWidth = size.cx;

	//
	// Compute the page count.
	//
    m_nLinesPerPage = (pDC->GetDeviceCaps (VERTRES) -
        (m_cyPrinter * (3 + (2 * PRINTMARGIN)))) / m_cyPrinter;
    UINT nMaxPage = max (1, (m_nLinesTotal + (m_nLinesPerPage - 1)) /
        m_nLinesPerPage);
    pInfo->SetMaxPage (nMaxPage);

    //
    // Compute the horizontal offset required to center 
    // each line of output.
    //
    m_cxOffset = (pDC->GetDeviceCaps (HORZRES) - size.cx) / 2;
}

void CHexView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CHexDoc* pDoc = GetDocument ();
    PrintPageHeader (pDoc, pDC, pInfo->m_nCurPage);
    PrintPage (pDoc, pDC, pInfo->m_nCurPage);
}

void CHexView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    m_fontPrinter.DeleteObject ();
}

/////////////////////////////////////////////////////////////////////////////
// CHexView diagnostics

#ifdef _DEBUG
void CHexView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CHexDoc* CHexView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHexDoc)));
	return (CHexDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHexView message handlers

int CHexView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//
	// Create a screen font.
	//
    m_fontScreen.CreatePointFont (100, _T ("Courier New"));

	//
	// Compute the height of one line in the screen font.
	//
    CClientDC dc (this);
    TEXTMETRIC tm;
    CFont* pOldFont = dc.SelectObject (&m_fontScreen);
    dc.GetTextMetrics (&tm);
    m_cyScreen = tm.tmHeight + tm.tmExternalLeading;
    dc.SelectObject (pOldFont);
	return 0;
}

void CHexView::FormatLine(CHexDoc* pDoc, UINT nLine, CString& string)
{
	//
	// Get 16 bytes and format them for output.
	//
    BYTE b[17];
    ::FillMemory (b, 16, 32);
    UINT nCount = pDoc->GetBytes (nLine * 16, 16, b);

    string.Format (_T ("%0.8X    %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X " \
        "%0.2X %0.2X - %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X " \
        "%0.2X    "), nLine * 16,
        b[0], b[1],  b[2],  b[3],  b[4],  b[5],  b[6],  b[7],
        b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15]);

	//
	// Replace non-printable characters with periods.
	//
    for (UINT i=0; i<nCount; i++) {
        if (!::IsCharAlphaNumeric (b[i]))
            b[i] = 0x2E;
    }

	//
	// If less than 16 bytes were retrieved, erase to the end of the line.
	//
    b[nCount] = 0;
    string += b;

    if (nCount < 16) {
        UINT pos1 = 59;
        UINT pos2 = 60;
        UINT j = 16 - nCount;

        for (i=0; i<j; i++) {
            string.SetAt (pos1, _T (' '));
            string.SetAt (pos2, _T (' '));
            pos1 -= 3;
            pos2 -= 3;
            if (pos1 == 35) {
                string.SetAt (35, _T (' '));
                string.SetAt (36, _T (' '));
                pos1 = 33;
                pos2 = 34;
            }
        }
    }
}

void CHexView::PrintPageHeader(CHexDoc* pDoc, CDC* pDC, UINT nPageNumber)
{
	//
	// Formulate the text that appears at the top of page.
	//
    CString strHeader = pDoc->GetPathName ();
    if (strHeader.GetLength () > 68)
        strHeader = pDoc->GetTitle ();

    CString strPageNumber;
    strPageNumber.Format (_T ("Page %d"), nPageNumber);

    UINT nSpaces = 81 - strPageNumber.GetLength () - strHeader.GetLength ();
    for (UINT i=0; i<nSpaces; i++)
        strHeader += _T (' ');
    strHeader += strPageNumber;

	//
	// Output the text.
	//
    UINT y = m_cyPrinter * PRINTMARGIN;
    CFont* pOldFont = pDC->SelectObject (&m_fontPrinter);
    pDC->TextOut (m_cxOffset, y, strHeader);

	//
	// Draw a horizontal line underneath the line of text.
	//
    y += (m_cyPrinter * 3) / 2;
    pDC->MoveTo (m_cxOffset, y);
    pDC->LineTo (m_cxOffset + m_cxWidth, y);

    pDC->SelectObject (pOldFont);
}

void CHexView::PrintPage(CHexDoc* pDoc, CDC* pDC, UINT nPageNumber)
{
    if (m_nLinesTotal != 0) {
        UINT nStart = (nPageNumber - 1) * m_nLinesPerPage;
        UINT nEnd = min (m_nLinesTotal - 1, nStart + m_nLinesPerPage - 1);

        CFont* pOldFont = pDC->SelectObject (&m_fontPrinter);
        for (UINT i=nStart; i<=nEnd; i++) {
	        CString string;
            FormatLine (pDoc, i, string);
            UINT y = ((i - nStart) + PRINTMARGIN + 3) * m_cyPrinter;
            pDC->TextOut (m_cxOffset, y, string);
        }
        pDC->SelectObject (pOldFont);
    }
}
