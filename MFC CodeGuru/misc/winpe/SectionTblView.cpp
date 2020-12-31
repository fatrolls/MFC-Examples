// winpeView.cpp : implementation of the CSectionTblView class
//

#include "stdafx.h"
#include "winpe.h"
//#include "pefile.h"
#include "winpeDoc.h"
#include "SectionTblView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct
{
    DWORD   flag;
    PSTR    name;
} DWORD_FLAG_DESCRIPTIONS;


// Bitfield values and names for the IMAGE_SECTION_HEADER flags

DWORD_FLAG_DESCRIPTIONS SectionCharacteristics[] = 
{
{ IMAGE_SCN_CNT_CODE, "CODE" },
{ IMAGE_SCN_CNT_INITIALIZED_DATA, "INITIALIZED_DATA" },
{ IMAGE_SCN_CNT_UNINITIALIZED_DATA, "UNINITIALIZED_DATA" },
{ IMAGE_SCN_LNK_INFO, "LNK_INFO" },
// { IMAGE_SCN_LNK_OVERLAY, "LNK_OVERLAY" },
{ IMAGE_SCN_LNK_REMOVE, "LNK_REMOVE" },
{ IMAGE_SCN_LNK_COMDAT, "LNK_COMDAT" },
{ IMAGE_SCN_MEM_DISCARDABLE, "MEM_DISCARDABLE" },
{ IMAGE_SCN_MEM_NOT_CACHED, "MEM_NOT_CACHED" },
{ IMAGE_SCN_MEM_NOT_PAGED, "MEM_NOT_PAGED" },
{ IMAGE_SCN_MEM_SHARED, "MEM_SHARED" },
{ IMAGE_SCN_MEM_EXECUTE, "MEM_EXECUTE" },
{ IMAGE_SCN_MEM_READ, "MEM_READ" },
{ IMAGE_SCN_MEM_WRITE, "MEM_WRITE" },
};

#define NUMBER_SECTION_CHARACTERISTICS \
    (sizeof(SectionCharacteristics) / sizeof(DWORD_FLAG_DESCRIPTIONS))
/////////////////////////////////////////////////////////////////////////////
// CSectionTblView

IMPLEMENT_DYNCREATE(CSectionTblView, CScrollView)

BEGIN_MESSAGE_MAP(CSectionTblView, CScrollView)
	//{{AFX_MSG_MAP(CSectionTblView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSectionTblView construction/destruction

CSectionTblView::CSectionTblView()
{
	// TODO: add construction code here

}

CSectionTblView::~CSectionTblView()
{
}

BOOL CSectionTblView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSectionTblView drawing

void CSectionTblView::OnDraw(CDC* pDC)
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	
	if (m_nLinesTotal != 0)
	{
		
		CRect rect;
		pDC->GetClipBox(&rect);
		CSize size = pDC->GetTextExtent("Fg",2);
		INT nStart = rect.top / size.cy;
		INT nEnd = min (m_nLinesTotal -1,
						 (rect.bottom + size.cy - 1) /
						 size.cy);
		

	
		CFont * pOldFont = pDC->SelectObject(pDoc->m_screenFont);

	
		for (INT i = nStart; i <= nEnd; i++)
		{
			

			pDC->TextOut(2,(i * size.cy) +2,m_DisplayData[i]);
		}

		
		pDC->SelectObject(pOldFont);

		
	}


	
}

/////////////////////////////////////////////////////////////////////////////
// CSectionTblView printing

BOOL CSectionTblView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSectionTblView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
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

void CSectionTblView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSectionTblView diagnostics

#ifdef _DEBUG
void CSectionTblView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSectionTblView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinpeDoc* CSectionTblView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinpeDoc)));
	return (CWinpeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSectionTblView message handlers


int CSectionTblView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CSectionTblView::OnInitialUpdate() 
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->TurnChecksOff();
	pDoc->m_Sections_Checked = TRUE;

	DWORD nDocLength = pDoc->GetDocumentLength();

	if (nDocLength == 0)
	{
		m_nLinesTotal = 0;
		
	}
	else
	{
		m_nLinesTotal = GetSectionTable();
	}

	CClientDC dc(this);
	TEXTMETRIC tm;
	CFont* pOldFont = dc.SelectObject(pDoc->m_screenFont);
	dc.GetTextMetrics (&tm);
	m_cyScreen = tm.tmHeight + tm.tmExternalLeading;
	dc.SelectObject(pOldFont);

	SetScrollSizes (MM_TEXT,
					CSize(0,m_nLinesTotal * m_cyScreen), //tot size
					CSize(0,m_cyScreen * 10),			 //screen size 
					CSize (0,m_cyScreen));				//line size

	ScrollToPosition(CPoint (0,0));

	CScrollView::OnInitialUpdate();



	
	
	// TODO: Add your specialized code here and/or call the base class
	
}


INT CSectionTblView::GetSectionTable()
{

	
	PIMAGE_SECTION_HEADER pSections;
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNTHeader;
	INT nsections;

	BYTE * pfile;
	CString string;
	BOOL IsEXE;
	INT i, j; 
	
	CHAR line[128];
	CHAR *pLine;
	CWinpeDoc* pDoc;
	
	pDoc = GetDocument();
	pfile = pDoc->GetDocumentDataP();

	pDosHeader = (PIMAGE_DOS_HEADER)pfile;

	pNTHeader = MakePtr(PIMAGE_NT_HEADERS,
						pDosHeader,
						pDosHeader->e_lfanew);

	nsections = pNTHeader->FileHeader.NumberOfSections;

	//nsections = NumOfSections(pfile);

	INT tp = pDoc->GetOpenFileType();
	if (tp == FILETYPE_EXE)
		IsEXE = TRUE;
	else
		IsEXE = FALSE;

	pSections = IMAGE_FIRST_SECTION(pNTHeader);
	//pSections = (PIMAGE_SECTION_HEADER)SECHDROFFSET(pfile);

	

    string = "Section Table";
	m_DisplayData.Add(string);

	
	        
    for ( i=1; i <= nsections; i++, pSections++ )
    {
        wsprintf(line, "  %02X %-8.8s  %s: %08X  VirtAddr:  %08X",
                i, pSections->Name,
                IsEXE ? "VirtSize" : "PhysAddr",
                pSections->Misc.VirtualSize, pSections->VirtualAddress);

		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);

		
        wsprintf(line, "    raw data offs:   %08X  raw data size: %08X",
                pSections->PointerToRawData, pSections->SizeOfRawData );
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);

        wsprintf(line, "    relocation offs: %08X  relocations:   %08X",
                pSections->PointerToRelocations, pSections->NumberOfRelocations );
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);

        wsprintf(line, "    line # offs:     %08X  line #'s:      %08X",
                pSections->PointerToLinenumbers, pSections->NumberOfLinenumbers );
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);

        wsprintf(line, "    characteristics: %08X", pSections->Characteristics);
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);

        wsprintf(line,"    ");
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);

        for ( j=0; j < NUMBER_SECTION_CHARACTERISTICS; j++ )
        {
            if ( pSections->Characteristics & 
                SectionCharacteristics[j].flag )
			{
                wsprintf(line, "  %s", SectionCharacteristics[j].name );
				pLine = string.GetBuffer(strlen(line)+1);
				strcpy(pLine,line);
				string.ReleaseBuffer();
				m_DisplayData.Add(string);

			}

        }
		string = "  ";
		m_DisplayData.Add(string);
        
    }
    
    return m_DisplayData.GetSize(); 

}





void CSectionTblView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//CScrollView::OnPrepareDC(pDC, pInfo);
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CScrollView::OnPrepareDC(pDC, pInfo);
	
	if (pInfo)
	{
		pDC->SetMapMode(MM_LOENGLISH);
		pDC->SelectObject(pDoc->m_printerFont);
		
	}
}

void CSectionTblView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//CScrollView::OnPrint(pDC, pInfo);
	PrintPageHeader (pDC, pInfo->m_nCurPage);
    PrintPage (pDC, pInfo->m_nCurPage);
}

void CSectionTblView::PrintPageHeader(CDC* pDC, UINT nPageNumber)
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

void CSectionTblView::PrintPage(CDC* pDC, UINT nPageNumber)
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
            //FormatLine (i, string);
            y = ((i - nStart) + PRINTMARGIN + 3) * m_cyPrinter;
            //pDC->TextOut (m_cxOffset, -y, string);
			pDC->TextOut (0, -y, m_DisplayData[i]);
        }
        pDC->SelectObject (pOldFont);
    }

}
void CSectionTblView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
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
