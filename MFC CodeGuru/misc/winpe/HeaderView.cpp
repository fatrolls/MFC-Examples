// winpeView.cpp : implementation of the CHeaderView class
//

#include "stdafx.h"
#include "winpe.h"
//#include "pefile.h"
#include "winpeDoc.h"
#include "HeaderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct 
{
WORD    flag;
PSTR    name;
}WORD_FLAG_DESCRIPTIONS;

WORD_FLAG_DESCRIPTIONS ImageFileHeaderCharacteristics[] = 
{
{ IMAGE_FILE_RELOCS_STRIPPED, "RELOCS_STRIPPED" },
{ IMAGE_FILE_EXECUTABLE_IMAGE, "EXECUTABLE_IMAGE" },
{ IMAGE_FILE_LINE_NUMS_STRIPPED, "LINE_NUMS_STRIPPED" },
{ IMAGE_FILE_LOCAL_SYMS_STRIPPED, "LOCAL_SYMS_STRIPPED" },
{ IMAGE_FILE_BYTES_REVERSED_LO, "BYTES_REVERSED_LO" },
{ IMAGE_FILE_32BIT_MACHINE, "32BIT_MACHINE" },
{ IMAGE_FILE_DEBUG_STRIPPED, "DEBUG_STRIPPED" },
{ IMAGE_FILE_SYSTEM, "SYSTEM" },
{ IMAGE_FILE_DLL, "DLL" },
{ IMAGE_FILE_BYTES_REVERSED_HI, "BYTES_REVERSED_HI" }
};

#define NUMBER_IMAGE_HEADER_FLAGS \
	(sizeof(ImageFileHeaderCharacteristics) / sizeof(WORD_FLAG_DESCRIPTIONS))
//
// Names of the data directory elements that are defined
char *ImageDirectoryNames[] = {
    "EXPORT", "IMPORT", "RESOURCE", "EXCEPTION", "SECURITY", "BASERELOC",
    "DEBUG", "COPYRIGHT", "GLOBALPTR", "TLS", "LOAD_CONFIG",
    "BOUND_IMPORT", "IAT" };    // These last two entries added for NT 3.51

#define NUMBER_IMAGE_DIRECTORY_ENTRYS \
    (sizeof(ImageDirectoryNames)/sizeof(char *))

/////////////////////////////////////////////////////////////////////////////
// CHeaderView

IMPLEMENT_DYNCREATE(CHeaderView, CScrollView)

BEGIN_MESSAGE_MAP(CHeaderView, CScrollView)
	//{{AFX_MSG_MAP(CHeaderView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderView construction/destruction

CHeaderView::CHeaderView()
{
	// TODO: add construction code here

}

CHeaderView::~CHeaderView()
{
}

BOOL CHeaderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHeaderView drawing

void CHeaderView::OnDraw(CDC* pDC)
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
		//INT nStart = rect.top / pDoc->m_cyScreen;
		//INT nEnd = min(m_nLinesTotal - 1,
		//				 (rect.bottom + pDoc->m_cyScreen - 1) /
		//				 pDoc->m_cyScreen);


	
		CFont * pOldFont = pDC->SelectObject(pDoc->m_screenFont);

	
		for (INT i = nStart; i <= nEnd; i++)
		{
			

			pDC->TextOut(2,(i * size.cy) +2,m_DisplayData[i]);
		}

		
		pDC->SelectObject(pOldFont);

		
	}


	
}

/////////////////////////////////////////////////////////////////////////////
// CHeaderView printing

BOOL CHeaderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHeaderView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
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

void CHeaderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHeaderView diagnostics

#ifdef _DEBUG
void CHeaderView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CHeaderView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinpeDoc* CHeaderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinpeDoc)));
	return (CWinpeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHeaderView message handlers


int CHeaderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CHeaderView::OnInitialUpdate() 
{

	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->TurnChecksOff();
	pDoc->m_Headers_Checked = TRUE;
	DWORD nDocLength = pDoc->GetDocumentLength();

	if (nDocLength == 0)
	{
		m_nLinesTotal = 0;
		
	}
	else
	{
		m_nLinesTotal = GetFileHdrOptions();
		m_nLinesTotal = GetOptnlHdrOptions();
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


INT CHeaderView::GetFileHdrOptions()
{

	CHAR szmachine[10];
	BYTE * pfile;
	CString string;
	PIMAGE_FILE_HEADER pfh;
	PIMAGE_NT_HEADERS pNTHeader;
	PIMAGE_DOS_HEADER pDosHeader;
	CHAR line[128];
	CHAR *pLine;
	CWinpeDoc* pDoc;

	pDoc = GetDocument();
	pfile = pDoc->GetDocumentDataP();

	pDosHeader = (PIMAGE_DOS_HEADER)pfile;

	pNTHeader = MakePtr(PIMAGE_NT_HEADERS,
						pDosHeader,
						pDosHeader->e_lfanew);

	//GetPEFileHeader(pfile,&fh);
	pfh = &pNTHeader->FileHeader;

		 
    string = "File Header";
	m_DisplayData.Add(string);

	
    switch( pfh->Machine )
    {
        case IMAGE_FILE_MACHINE_I386:
			strcpy(szmachine,"i386");
			break;
        
        case IMAGE_FILE_MACHINE_R3000:
			    strcpy(szmachine,"R3000");
				break;

        case IMAGE_FILE_MACHINE_R4000:
			strcpy(szmachine,"R4000"); 
			break;

        case IMAGE_FILE_MACHINE_ALPHA:
			strcpy(szmachine,"alpha");
			break;
        default:
			strcpy(szmachine,"unknown");
			break;
    }

    wsprintf(line,
		     "  %s%04X (%s)","Machine:", 
                pfh->Machine, szmachine);

	pLine = string.GetBuffer(sizeof(line));
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

		
    wsprintf(line,"  %s%04X","Number of Sections:",
                pfh->NumberOfSections);
	pLine = string.GetBuffer(sizeof(line));
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);


    wsprintf(line,"  %s%08X","TimeDateStamp:",
                pfh->TimeDateStamp);
	pLine = string.GetBuffer(sizeof(line));
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

	
    wsprintf(line,"  %s%08X","PointerToSymbolTable:",
                pfh->PointerToSymbolTable);
	pLine = string.GetBuffer(sizeof(line));
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);


    wsprintf(line,"  %s%08X","NumberOfSymbols:",
                pfh->NumberOfSymbols);
	pLine = string.GetBuffer(sizeof(line));
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);


    wsprintf(line,"  %s%04X","SizeOfOptionalHeader:",
                pfh->SizeOfOptionalHeader);
	pLine = string.GetBuffer(sizeof(line));
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

	
    wsprintf(line,"  %s%04X","Characteristics:",
                pfh->Characteristics);
	pLine = string.GetBuffer(sizeof(line));
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);


	//
	// print a line for each bit that's on in the flag 
	//

	
    for (int x=0; x < NUMBER_IMAGE_HEADER_FLAGS; x++ )
    {
        if ( pfh->Characteristics & 
             ImageFileHeaderCharacteristics[x].flag )
		{
            wsprintf(line,"    %s", ImageFileHeaderCharacteristics[x].name );
			pLine = string.GetBuffer(sizeof(line));
			strcpy(pLine,line);
			string.ReleaseBuffer();
			m_DisplayData.Add(string);

		}

    }

	string = "  ";
	m_DisplayData.Add(string);
	return m_DisplayData.GetSize(); 

}


INT CHeaderView::GetOptnlHdrOptions()
{
	CHAR szsubsys[10];
	BYTE * pfile;
	CString string;
	PIMAGE_OPTIONAL_HEADER poh;
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNTHeader;
	CHAR line[128];
	CHAR *pLine;
	CWinpeDoc* pDoc;
	UINT i;


	pDoc = GetDocument();
	pfile = pDoc->GetDocumentDataP();
	pDosHeader = (PIMAGE_DOS_HEADER)pfile;

	pNTHeader = MakePtr(PIMAGE_NT_HEADERS,
						pDosHeader,
						pDosHeader->e_lfanew);

	
	
	//GetPEOptionalHeader(pfile,&optionalHeader);
	poh = &pNTHeader->OptionalHeader;

    strcpy(line,"Optional Header");
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    
    wsprintf(line,"  %s%04X","Magic:", poh->Magic);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
	

    wsprintf(line,"  %s%u.%02u","linker version:",
        poh->MajorLinkerVersion,
        poh->MinorLinkerVersion);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","size of code:", poh->SizeOfCode);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","size of initialized data:",
        poh->SizeOfInitializedData);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","size of uninitialized data:",
        poh->SizeOfUninitializedData);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","entrypoint RVA:",
        poh->AddressOfEntryPoint);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","base of code:", poh->BaseOfCode);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","base of data:", poh->BaseOfData);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","image base:", poh->ImageBase);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    wsprintf(line,"  %s%X","section align:",
        poh->SectionAlignment);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","file align:", poh->FileAlignment);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%u.%02u","required OS version:",
        poh->MajorOperatingSystemVersion,
        poh->MinorOperatingSystemVersion);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%u.%02u","image version:",
        poh->MajorImageVersion,
        poh->MinorImageVersion);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%u.%02u","subsystem version:",
        poh->MajorSubsystemVersion,
        poh->MinorSubsystemVersion);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    
    wsprintf(line,"  %s%X","size of image:", poh->SizeOfImage);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","size of headers:",
            poh->SizeOfHeaders);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  %s%X","checksum:", poh->CheckSum);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    switch( poh->Subsystem )
    {
        case IMAGE_SUBSYSTEM_NATIVE: 
			strcpy(szsubsys,"Native");
			break;
        case IMAGE_SUBSYSTEM_WINDOWS_GUI:
			strcpy(szsubsys,"Windows GUI");
			break;
        case IMAGE_SUBSYSTEM_WINDOWS_CUI:
			strcpy(szsubsys,"Windows character");
			break;
        case IMAGE_SUBSYSTEM_OS2_CUI:
			strcpy(szsubsys,"OS/2 character");
			break;
        case IMAGE_SUBSYSTEM_POSIX_CUI: 
			strcpy(szsubsys,"Posix character"); 
			break;
        default: strcpy(szsubsys,"unknown");
    }
    wsprintf(line,"  %s%04X (%s)","Subsystem:",
            poh->Subsystem, szsubsys);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    wsprintf(line,"  %s%X","stack reserve size:",					
        poh->SizeOfStackReserve);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    wsprintf(line,"  %s%X","stack commit size:",
        poh->SizeOfStackCommit);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    wsprintf(line,"  %s%X","heap reserve size:",
        poh->SizeOfHeapReserve);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    wsprintf(line,"  %s%X","heap commit size:",
        poh->SizeOfHeapCommit);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);


    wsprintf(line,"  %s%X","RVAs & sizes:",
        poh->NumberOfRvaAndSizes);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);


    wsprintf(line,"Data Directory:");
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    for ( i=0; i < poh->NumberOfRvaAndSizes; i++)
    {
        wsprintf(line,"  %-12s rva: %08X  size: %08X",
            (i >= NUMBER_IMAGE_DIRECTORY_ENTRYS)
                ? "Unused" : ImageDirectoryNames[i], 
            poh->DataDirectory[i].VirtualAddress,
            poh->DataDirectory[i].Size);
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);

    }

	string = "  ";
	m_DisplayData.Add(string);
	return m_DisplayData.GetSize(); 

}

void CHeaderView::PrintPageHeader (CDC* pDC, UINT nPageNumber)
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

void CHeaderView::PrintPage(CDC* pDC, UINT nPageNumber)
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

void CHeaderView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
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

void CHeaderView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//CScrollView::OnPrint(pDC, pInfo);
	PrintPageHeader (pDC, pInfo->m_nCurPage);
    PrintPage (pDC, pInfo->m_nCurPage);
}

void CHeaderView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
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
