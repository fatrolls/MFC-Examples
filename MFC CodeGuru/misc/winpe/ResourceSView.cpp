// winpeView.cpp : implementation of the CResourceSView class
//

#include "stdafx.h"
#include "winpe.h"
//#include "pefile.h"
#include "winpeDoc.h"
#include "resourcesview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CResourceSView

IMPLEMENT_DYNCREATE(CResourceSView, CScrollView)

BEGIN_MESSAGE_MAP(CResourceSView, CScrollView)
	//{{AFX_MSG_MAP(CResourceSView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceSView construction/destruction

CResourceSView::CResourceSView()
{
	// TODO: add construction code here

}

CResourceSView::~CResourceSView()
{
}

BOOL CResourceSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CResourceSView drawing

void CResourceSView::OnDraw(CDC* pDC)
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

		

	
		for (INT i = nStart; i <= nEnd; i++)
		{
			

			pDC->TextOut(2,(i * size.cy) +2,m_DisplayData[i]);
		}

		
		pDC->SelectObject(pOldFont);

		
	}


	
	
}

/////////////////////////////////////////////////////////////////////////////
// CResourceSView printing

BOOL CResourceSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CResourceSView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
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

void CResourceSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CResourceSView diagnostics

#ifdef _DEBUG
void CResourceSView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CResourceSView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinpeDoc* CResourceSView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinpeDoc)));
	return (CWinpeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResourceSView message handlers


int CResourceSView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CResourceSView::OnInitialUpdate() 
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	pDoc->TurnChecksOff();
	pDoc->m_Resources_Checked = TRUE;
	DWORD nDocLength = pDoc->GetDocumentLength();

	if (nDocLength == 0)
	{
		m_nLinesTotal = 0;
	
	}
	else
	{
		m_nLinesTotal = GetResourceSection();	
	}



	SetScrollSizes (MM_TEXT,
					CSize(0,m_nLinesTotal * pDoc->m_cyScreen), //tot size
					CSize(0,pDoc->m_cyScreen * 10),			 //screen size 
					CSize (0,pDoc->m_cyScreen));				//line size

	ScrollToPosition(CPoint (0,0));

	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}


INT CResourceSView::GetResourceSection()
{

	PIMAGE_RESOURCE_DIRECTORY prd;	
	PIMAGE_NT_HEADERS pNTHeader;
	PIMAGE_DOS_HEADER pDosHdr;
	
	BYTE * pfile;
	CString string;
	
	CWinpeDoc* pDoc;

	pDoc = GetDocument();
	pfile = pDoc->GetDocumentDataP();

	pDosHdr = (PIMAGE_DOS_HEADER)pfile;
	pNTHeader = MakePtr(PIMAGE_NT_HEADERS,pfile,pDosHdr->e_lfanew);

	//prd = (PIMAGE_RESOURCE_DIRECTORY)ImageDirectoryOffset(pfile,IMAGE_DIRECTORY_ENTRY_RESOURCE);
	prd = (PIMAGE_RESOURCE_DIRECTORY)GetSectionPtr(".rsrc",pNTHeader,(DWORD)pfile);
	if (prd == NULL)
	{
		string = "No Resources Found";
		m_DisplayData.Add(string);
		return 1;
	}
		        
    DumpResourceDirectory(prd,(DWORD)prd,0,0);
    
    return m_DisplayData.GetSize(); 

}



void CResourceSView::DumpResourceDirectory(PIMAGE_RESOURCE_DIRECTORY resDir,
										   DWORD resourceBase,
										   DWORD level,
										   DWORD resourceType)
{
	PIMAGE_RESOURCE_DIRECTORY_ENTRY resDirEntry;
    char szType[64];
    UINT i;
	CString string;
	CString indent;
	CHAR line[128];
	CHAR *pLine;

	indent.Empty();
    // Spit out the spacing for the level indentation
    for ( i=0; i < level; i++ )
	{
        indent += "    ";
		
	}

	m_DisplayData.Add(string);

    // Level 1 resources are the resource types
    if ( level == 1 && !(resourceType & IMAGE_RESOURCE_NAME_IS_STRING) )
    {
        GetResourceTypeName( resourceType, szType, sizeof(szType) );
    }
    else    // Just print out the regular id or name
    {
        GetResourceNameFromId( resourceType, resourceBase, szType,
                               sizeof(szType) );
    }
    
    wsprintf(line,
        "ResDir (%s) Named:%02X ID:%02X TimeDate:%08X Vers:%u.%02u Char:%X",
        szType, resDir->NumberOfNamedEntries, resDir->NumberOfIdEntries,
        resDir->TimeDateStamp, resDir->MajorVersion,
        resDir->MinorVersion,resDir->Characteristics);

	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	indent += string;
	m_DisplayData.Add(indent);

    resDirEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(resDir+1);
    
    for ( i=0; i < resDir->NumberOfNamedEntries; i++, resDirEntry++ )
        DumpResourceEntry(resDirEntry, resourceBase, level+1);

    for ( i=0; i < resDir->NumberOfIdEntries; i++, resDirEntry++ )
        DumpResourceEntry(resDirEntry, resourceBase, level+1);


}

void CResourceSView::GetResourceTypeName(DWORD type,
										 LPTSTR buffer,
										 UINT cBytes)
{
char *SzResourceTypes[] = 
{
	"???_0", "CURSOR", "BITMAP", "ICON", "MENU", "DIALOG", "STRING", "FONTDIR",
	"FONT", "ACCELERATORS", "RCDATA", "MESSAGETABLE", "GROUP_CURSOR",
	"???_13", "GROUP_ICON", "???_15", "VERSION"
};

// Get an ASCII string representing a resource type

    if ( type <= 16 )
        strncpy(buffer, SzResourceTypes[type], cBytes);
    else
        sprintf(buffer, "%X", type);



}

void CResourceSView::GetResourceNameFromId(DWORD id,
									   DWORD resourceBase,
									   LPTSTR buffer,
									   UINT cBytes)
{
	
	PIMAGE_RESOURCE_DIR_STRING_U prdsu;

    // If it's a regular ID, just format it.
    if ( !(id & IMAGE_RESOURCE_NAME_IS_STRING) )
    {
        sprintf(buffer, "%X", id);
        return;
    }
    
    id &= 0x7FFFFFFF;
    prdsu = (PIMAGE_RESOURCE_DIR_STRING_U)(resourceBase + id);

    // prdsu->Length is the number of unicode characters
    WideCharToMultiByte(CP_ACP, 0, prdsu->NameString, prdsu->Length,
                        buffer, cBytes, 0, 0);
    buffer[ min(cBytes-1,prdsu->Length) ] = 0;  // Null terminate it!!!

}

void CResourceSView::DumpResourceEntry(PIMAGE_RESOURCE_DIRECTORY_ENTRY resDirEntry, DWORD resourceBase,DWORD level)
{
	CHAR line[128];
	CHAR *pLine;
	CString string;
	CString indent;
	UINT i;
    char nameBuffer[128];
    PIMAGE_RESOURCE_DATA_ENTRY pResDataEntry;
    
    if ( resDirEntry->OffsetToData & IMAGE_RESOURCE_DATA_IS_DIRECTORY )
    {
        DumpResourceDirectory( (PIMAGE_RESOURCE_DIRECTORY)
            ((resDirEntry->OffsetToData & 0x7FFFFFFF) + resourceBase),
            resourceBase, level, resDirEntry->Name);
        return;
    }

    // Spit out the spacing for the level indentation
	indent.Empty();
    for ( i=0; i < level; i++ )
        indent += "   ";

    if ( resDirEntry->Name & IMAGE_RESOURCE_NAME_IS_STRING )
    {
        GetResourceNameFromId(resDirEntry->Name, resourceBase, nameBuffer,
                              sizeof(nameBuffer));
        wsprintf(line,"Name: %s  DataEntryOffs: %08X",
            nameBuffer, resDirEntry->OffsetToData);
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		indent += string;
		m_DisplayData.Add(indent);
    }
    else
    {
        wsprintf(line,"ID: %08X  DataEntryOffs: %08X",
                resDirEntry->Name, resDirEntry->OffsetToData);
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		indent += string;
		m_DisplayData.Add(indent);
    }
    
    // the resDirEntry->OffsetToData is a pointer to an
    // IMAGE_RESOURCE_DATA_ENTRY.  Go dump out that information.  First,
    // spit out the proper indentation
	indent.Empty();
    for ( i=0; i < level; i++ )
        indent += "    ";
    
    pResDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)
                    (resourceBase + resDirEntry->OffsetToData);
    wsprintf(line,"Offset: %05X  Size: %05X  CodePage: %X",
            pResDataEntry->OffsetToData, pResDataEntry->Size,
            pResDataEntry->CodePage);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	indent += string;
	m_DisplayData.Add(indent);
	m_DisplayData.Add(" ");


}

LPVOID CResourceSView::GetSectionPtr(LPTSTR name,PIMAGE_NT_HEADERS pNTHeader,DWORD imageBase)
{
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(pNTHeader);
    unsigned i;
    
    for ( i=0; i < pNTHeader->FileHeader.NumberOfSections; i++, section++ )
    {
        if ( strnicmp((LPCTSTR)section->Name, name, IMAGE_SIZEOF_SHORT_NAME) == 0 )
            return (LPVOID)(section->PointerToRawData + imageBase);
    }
    
    return 0;

}

void CResourceSView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
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

void CResourceSView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	PrintPageHeader (pDC, pInfo->m_nCurPage);
    PrintPage (pDC, pInfo->m_nCurPage);
	//CScrollView::OnPrint(pDC, pInfo);
}


void CResourceSView::PrintPageHeader(CDC* pDC, UINT nPageNumber)
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

void CResourceSView::PrintPage(CDC* pDC, UINT nPageNumber)
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
void CResourceSView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClientDC dc(this);
	TEXTMETRIC tm;
	CFont* pOldFont = dc.SelectObject(pDoc->m_screenFont);
	dc.GetTextMetrics (&tm);
	INT m_cyScreen = tm.tmHeight + tm.tmExternalLeading;
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
