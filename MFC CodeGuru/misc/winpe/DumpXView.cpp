// winpeView.cpp : implementation of the CDumpXView class
//

#include "stdafx.h"
#include "winpe.h"

#include "winpeDoc.h"
#include "dumpxview.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define PRINTMARGIN 2

/////////////////////////////////////////////////////////////////////////////
// CDumpXView

IMPLEMENT_DYNCREATE(CDumpXView, CScrollView)

BEGIN_MESSAGE_MAP(CDumpXView, CScrollView)
	//{{AFX_MSG_MAP(CDumpXView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpXView construction/destruction

CDumpXView::CDumpXView()
{
	// TODO: add construction code here

}

CDumpXView::~CDumpXView()
{
}

BOOL CDumpXView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDumpXView drawing

void CDumpXView::OnDraw(CDC* pDC)
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//
	// my code.
	//

	if (m_nLinesTotal != 0)
	{
		CRect rect;
		pDC->GetClipBox(&rect);
		CFont * pOldFont = pDC->SelectObject(pDoc->m_screenFont);

		CSize size = pDC->GetTextExtent("Fg",2);
		INT nStart = rect.top / size.cy;
		INT nEnd = min (m_nLinesTotal -1,
						 (rect.bottom + size.cy - 1) /
						 size.cy);
		CString string;
		
		for (INT i = nStart; i <= nEnd; i++)
		{
			FormatLine(i,string);
			pDC->TextOut(2,((i*size.cy) +2),string);
		}
		pDC->SelectObject(pOldFont);
	}

	
}

/////////////////////////////////////////////////////////////////////////////
// CDumpXView printing

BOOL CDumpXView::OnPreparePrinting(CPrintInfo* pInfo)
{
	
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDumpXView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{

	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->SetMapMode(MM_LOENGLISH);
	
    CFont* pOldFont = pDC->SelectObject (pDoc->m_printerFont);
    
    CSize size = pDC->GetTextExtent ("---------1---------2---------" \
        "3---------4---------5---------6---------7---------8-", 81);

    pDC->SelectObject (pOldFont);
	//
	// Get height and width then convert to logical
	//
	CSize vsz;	// vertres horzres
	vsz.cy = pDC->GetDeviceCaps(VERTRES);
	vsz.cx = pDC->GetDeviceCaps(HORZRES);
	pDC->DPtoLP(&vsz);
	m_cyPrinter = size.cy;
	m_cxOffset = (vsz.cx - size.cx) / 2;
    m_cxWidth = size.cx;
	//
    //
	//
    m_nLinesPerPage = (vsz.cy -
        (m_cyPrinter * (3 + (2 * PRINTMARGIN)))) / m_cyPrinter;
    UINT nMaxPage = max (1, (m_nLinesTotal + (m_nLinesPerPage - 1)) /
        m_nLinesPerPage);

	if (m_nLinesTotal + (m_nLinesPerPage - 1) % m_nLinesPerPage)
		nMaxPage++;
    pInfo->SetMaxPage (nMaxPage);

    
	
}

void CDumpXView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDumpXView diagnostics

#ifdef _DEBUG
void CDumpXView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDumpXView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinpeDoc* CDumpXView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinpeDoc)));
	return (CWinpeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDumpXView message handlers


int CDumpXView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CDumpXView::OnInitialUpdate() 
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	pDoc->TurnChecksOff();
	pDoc->m_Dump_Checked = TRUE;
	DWORD nDocLength = pDoc->GetDocumentLength();

	// + plus 15 to ensure even number division
	m_nLinesTotal = (nDocLength + 15) / 16;

	//
	CClientDC dc(this);
	TEXTMETRIC tm;
	CFont* pOldFont = dc.SelectObject(pDoc->m_screenFont);
	dc.GetTextMetrics (&tm);
	m_cyScreen = tm.tmHeight + tm.tmExternalLeading;
	dc.SelectObject(pOldFont);
	//
	SetScrollSizes (MM_TEXT,
					CSize(0,m_nLinesTotal * m_cyScreen),
					CSize(0,m_cyScreen * 100),
					CSize (0,m_cyScreen));

	ScrollToPosition(CPoint (0,0));

	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}

void CDumpXView::FormatLine(UINT nLine,CString& string)
{
	BYTE b[17];
	::FillMemory(b,16,32);
	UINT nCount = GetDocument()->GetBytes(nLine * 16,16,b);

	string.Format(
	 "%0.8X    %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X " \
	 "- %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X     ",
	 nLine * 16,
		b[0], b[1],b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9], 
		b[10], b[11], b[12], b[13], b[14], b[15]);
	
	for (UINT i=0;i<nCount;i++)
	{
		if (!::IsCharAlphaNumeric(b[i]))
			b[i] = 0x2E;
	}

	b[nCount] = 0;
	string += b;

	if (nCount < 16)
	{
		UINT pos1 = 59;
		UINT pos2 = 60;
		UINT j = 16 - nCount;

		for (i=0;i<j;i++)
		{
			string.SetAt(pos1,' ');
			string.SetAt(pos2,' ');
			pos1 -= 3;
			pos2 -= 3;
			if (pos1 == 35)
			{
				string.SetAt(35,' ');
				string.SetAt(36,' ');
				pos1 = 33;
				pos2 = 34;
			}
		}
	}


}


void CDumpXView::PrintPageHeader(CDC* pDC, UINT nPageNumber)
{

	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString strHeader = GetDocument ()->GetPathName ();
    if (strHeader.GetLength () > 68)
        strHeader = GetDocument ()->GetTitle ();

    CString strPageNumber;
    strPageNumber.Format ("Page %d", nPageNumber);

    UINT nSpaces = 81 - strPageNumber.GetLength () -
        strHeader.GetLength ();
    for (UINT i=0; i<nSpaces; i++)
        strHeader += ' ';
    strHeader += strPageNumber;

    INT y = m_cyPrinter * PRINTMARGIN;
    CFont* pOldFont = pDC->SelectObject (pDoc->m_printerFont);
    //pDC->TextOut (m_cxOffset, -y, strHeader);
	pDC->TextOut (0, -y, strHeader);

    y += (m_cyPrinter * 3) / 2;
    //pDC->MoveTo (m_cxOffset, -y);
	pDC->MoveTo (0, -y);
    pDC->LineTo (m_cxWidth, -y);
	//pDC->LineTo (0, -y);

    pDC->SelectObject (pOldFont);
}

void CDumpXView::PrintPage(CDC* pDC, UINT nPageNumber)
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_nLinesTotal != 0) {
        INT nStart = (nPageNumber - 1) * m_nLinesPerPage;
        INT nEnd = min (m_nLinesTotal - 1, nStart + m_nLinesPerPage - 1);

        CString string;
        CFont* pOldFont = pDC->SelectObject (pDoc->m_printerFont);

        INT y;
        for (INT i=nStart; i<=nEnd; i++) {
            FormatLine (i, string);
            y = ((i - nStart) + PRINTMARGIN + 3) * m_cyPrinter;
            //pDC->TextOut (m_cxOffset, -y, string);
			pDC->TextOut (0, -y, string);
        }
        pDC->SelectObject (pOldFont);
    }

}

void CDumpXView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	PrintPageHeader (pDC, pInfo->m_nCurPage);
    PrintPage (pDC, pInfo->m_nCurPage);

}

void CDumpXView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CScrollView::OnPrepareDC(pDC, pInfo);
	
	if (pInfo)
	{
		pDC->SetMapMode(MM_LOENGLISH);
		pDC->SelectObject(pDoc->m_printerFont);
		
	}

}

void CDumpXView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClientDC dc(this);
	TEXTMETRIC tm;
	CFont* pOldFont = dc.SelectObject(pDoc->m_screenFont);
	dc.GetTextMetrics (&tm);
	m_cyScreen = tm.tmHeight + tm.tmExternalLeading;
	dc.SelectObject(pOldFont);
	//
	SetScrollSizes (MM_TEXT,
					CSize(0,m_nLinesTotal * m_cyScreen),
					CSize(0,m_cyScreen * 100),
					CSize (0,m_cyScreen));

	ScrollToPosition(CPoint (0,0));
	CRect rect;
	dc.GetClipBox(&rect);
	InvalidateRect(&rect);
	
}
