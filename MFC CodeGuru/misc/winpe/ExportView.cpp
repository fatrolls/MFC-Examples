// winpeView.cpp : implementation of the CExportView class
//

#include "stdafx.h"
#include "winpe.h"
//#include "pefile.h"
#include "winpeDoc.h"
#include "ExportView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportView

IMPLEMENT_DYNCREATE(CExportView, CScrollView)

BEGIN_MESSAGE_MAP(CExportView, CScrollView)
	//{{AFX_MSG_MAP(CExportView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportView construction/destruction

CExportView::CExportView()
{
	// TODO: add construction code here

}

CExportView::~CExportView()
{
}

BOOL CExportView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExportView drawing

void CExportView::OnDraw(CDC* pDC)
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	
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

		//UINT nStart = rect.top / pDoc->m_cyScreen;
		//UINT nEnd = min(m_nLinesTotal - 1,
		//				 (rect.bottom + pDoc->m_cyScreen - 1) /
		//				 pDoc->m_cyScreen);


	
		

	
		for (INT i = nStart; i <= nEnd; i++)
		{
			

			pDC->TextOut(2,(i * size.cy) +2,m_DisplayData[i]);
		}

		
		pDC->SelectObject(pOldFont);

		
	}


	
}

/////////////////////////////////////////////////////////////////////////////
// CExportView printing

BOOL CExportView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExportView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
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

void CExportView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExportView diagnostics

#ifdef _DEBUG
void CExportView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CExportView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinpeDoc* CExportView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinpeDoc)));
	return (CWinpeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExportView message handlers


int CExportView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CExportView::OnInitialUpdate() 
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	pDoc->TurnChecksOff();
	pDoc->m_Exports_Checked = TRUE;
	DWORD nDocLength = pDoc->GetDocumentLength();

	if (nDocLength == 0)
	{
		m_nLinesTotal = 0;
		
	}
	else
	{
		m_nLinesTotal = GetExportsSection();
		
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




INT CExportView::GetExportsSection()
{
	PIMAGE_EXPORT_DIRECTORY exportDir;
	PIMAGE_SECTION_HEADER header;
	PIMAGE_NT_HEADERS pNTHeader;
	PIMAGE_DOS_HEADER pDosHdr;
	INT delta;
	LPSTR filename;
	DWORD i;
	PDWORD functions;
	PWORD  ordinals;
	LPSTR *name;
	DWORD exportsStartRVA, exportsEndRVA;
	DWORD base;
	BYTE * pfile;
	CString string;
	CString stringapnd;
	CHAR line[128];
	CHAR *pLine;
	CWinpeDoc* pDoc;
	


	pDoc = GetDocument();
	pfile = pDoc->GetDocumentDataP();

	pDosHdr = (PIMAGE_DOS_HEADER)pfile;
	base = (DWORD)pfile;
	
	pNTHeader = MakePtr(PIMAGE_NT_HEADERS,
						pfile,pDosHdr->e_lfanew);

	exportsStartRVA = 
		pNTHeader->OptionalHeader.DataDirectory
		    [IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

		
	exportsEndRVA = exportsStartRVA + pNTHeader->OptionalHeader.DataDirectory
                            [IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

    // Get the IMAGE_SECTION_HEADER that contains the exports.  This is
    // usually the .edata section, but doesn't have to be.
    header = pDoc->GetEnclosingSectionHeader(exportsStartRVA,
											 pNTHeader);
    if ( !header )
	{
		string = "No Exports Table Found:";
		m_DisplayData.Add(string);		
        return m_DisplayData.GetSize(); 
	}

    delta = (INT)(header->VirtualAddress - header->PointerToRawData);
        
    exportDir = MakePtr(PIMAGE_EXPORT_DIRECTORY, base,
                         exportsStartRVA - delta);
        
    filename = (PSTR)(exportDir->Name - delta + base);

    string = "Exports Table:";
	m_DisplayData.Add(string);
        
    
    wsprintf(line,"  Name:            %s", filename);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    wsprintf(line,"  Characteristics: %08X", exportDir->Characteristics);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  TimeDateStamp:   %08X", exportDir->TimeDateStamp);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  Version:         %u.%02u", exportDir->MajorVersion,
            exportDir->MinorVersion);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  Ordinal base:    %08X", exportDir->Base);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  # of functions:  %08X", exportDir->NumberOfFunctions);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  # of Names:      %08X", exportDir->NumberOfNames);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    
    functions = (PDWORD)((DWORD)exportDir->AddressOfFunctions - delta + base);
    ordinals = (PWORD)((DWORD)exportDir->AddressOfNameOrdinals - delta + base);
    name = (PSTR *)((DWORD)exportDir->AddressOfNames - delta + base);

    wsprintf(line,"  Entry Pt  Ordn  Name");
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    for ( i=0; i < exportDir->NumberOfFunctions; i++ )
    {
        DWORD entryPointRVA = functions[i];
        DWORD j;

        if ( entryPointRVA == 0 )   // Skip over gaps in exported function
            continue;               // ordinals (the entrypoint is 0 for
                                    // these functions).

        wsprintf(line,"  %08X  %4u", entryPointRVA, i + exportDir->Base );
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		//m_DisplayData.Add(string);

        // See if this function has an associated name exported for it.
        for ( j=0; j < exportDir->NumberOfNames; j++ )
		{
            if ( ordinals[j] == i )
			{
                wsprintf(line,"  %s", name[j] - delta + base);
				pLine = stringapnd.GetBuffer(strlen(line)+1);
				strcpy(pLine,line);
				stringapnd.ReleaseBuffer();
				string += stringapnd;
				m_DisplayData.Add(string);
			}
		}

        // Is it a forwarder?  If so, the entry point RVA is inside the
        // .edata section, and is an RVA to the DllName.EntryPointName
        if ( (entryPointRVA >= exportsStartRVA)
             && (entryPointRVA <= exportsEndRVA) )
        {
            wsprintf(line," (forwarder -> %s)", entryPointRVA - delta + base );
			pLine = string.GetBuffer(strlen(line)+1);
			strcpy(pLine,line);
			string.ReleaseBuffer();
			m_DisplayData.Add(string);
        }
        
        
    }
    
    string = "  ";
	m_DisplayData.Add(string);
	return m_DisplayData.GetSize(); 

}

void CExportView::PrintPageHeader (CDC* pDC, UINT nPageNumber)
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
    
	pDC->TextOut (0, -y, strHeader);

    y += (m_cyPrinter * 3) / 2;
	pDC->MoveTo (0, -y);
    pDC->LineTo (m_cxWidth, -y);

    pDC->SelectObject (pOldFont);

}

void CExportView::PrintPage(CDC* pDC, UINT nPageNumber)
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
            pDC->TextOut (0, -y,m_DisplayData[i]);
        }
        pDC->SelectObject (pOldFont);
    }

}

void CExportView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
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

void CExportView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//CScrollView::OnPrint(pDC, pInfo);
	PrintPageHeader (pDC, pInfo->m_nCurPage);
    PrintPage (pDC, pInfo->m_nCurPage);
}

void CExportView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
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
