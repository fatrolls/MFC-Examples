// winpeView.cpp : implementation of the CDebugDirView class
//

#include "stdafx.h"
#include "winpe.h"
//#include "pefile.h"
#include "winpeDoc.h"
#include "DebugDirView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDebugDirView

IMPLEMENT_DYNCREATE(CDebugDirView, CScrollView)

BEGIN_MESSAGE_MAP(CDebugDirView, CScrollView)
	//{{AFX_MSG_MAP(CDebugDirView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebugDirView construction/destruction

CDebugDirView::CDebugDirView()
{
	// TODO: add construction code here

}

CDebugDirView::~CDebugDirView()
{
}

BOOL CDebugDirView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDebugDirView drawing

void CDebugDirView::OnDraw(CDC* pDC)
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
// CDebugDirView printing

BOOL CDebugDirView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDebugDirView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
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

void CDebugDirView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDebugDirView diagnostics

#ifdef _DEBUG
void CDebugDirView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDebugDirView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinpeDoc* CDebugDirView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinpeDoc)));
	return (CWinpeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDebugDirView message handlers


int CDebugDirView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CDebugDirView::OnInitialUpdate() 
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->TurnChecksOff();
	pDoc->m_DebugDir_Checked = TRUE;
	DWORD nDocLength = pDoc->GetDocumentLength();

	if (nDocLength == 0)
	{
		m_nLinesTotal = 0;
	}
	else
	{
		m_nLinesTotal = GetDebugDir();
		m_nLinesTotal = GetSymbols();
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

INT CDebugDirView::GetSymbols()
{
	
	
	PIMAGE_NT_HEADERS pNTHeader;
	PIMAGE_DOS_HEADER pDosHdr;
	DWORD base;
	BYTE * pfile;
	CString string;
	CString stringapnd;
	CWinpeDoc* pDoc;

	pDoc = GetDocument();
	pfile = pDoc->GetDocumentDataP();

	pDosHdr = (PIMAGE_DOS_HEADER)pfile;
	base = (DWORD)pfile;
	
	pNTHeader = MakePtr(PIMAGE_NT_HEADERS,
						pfile,pDosHdr->e_lfanew);

	if (pNTHeader->FileHeader.PointerToSymbolTable == 0)
	{
		string = "No COFF Symbol Table:";
		m_DisplayData.Add(string);
		return m_DisplayData.GetSize(); 
	}

    PCOFFSymbolTable = MakePtr(PIMAGE_SYMBOL, base,
                        pNTHeader->FileHeader.PointerToSymbolTable);
    COFFSymbolCount = pNTHeader->FileHeader.NumberOfSymbols;

    
    DumpCOFFHeader();
   
    
    
    DumpLineNumbers( MakePtr(PIMAGE_LINENUMBER, PCOFFDebugInfo,
                        PCOFFDebugInfo->LvaToFirstLinenumber),
                        PCOFFDebugInfo->NumberOfLinenumbers);
   
    

    
    if ( pNTHeader->FileHeader.NumberOfSymbols) 
      
    {
        DumpSymbolTable(PCOFFSymbolTable, COFFSymbolCount);
       
    }

    string = "  ";
	m_DisplayData.Add(string);
	return m_DisplayData.GetSize(); 

}

INT CDebugDirView::GetDebugDir()
{

	
	PIMAGE_DEBUG_DIRECTORY debugDir;
	PIMAGE_SECTION_HEADER header;
	PIMAGE_NT_HEADERS pNTHeader;
	PIMAGE_DOS_HEADER pDosHdr;

	DWORD offsetInto_rdata;
	DWORD va_debug_dir;
	DWORD size;
	//BOOL found;
	DWORD cDebugFormats;
	LPTSTR szDebugFormat;
    UINT i;

	BYTE * pfile;
	CString string;
	CHAR line[128];
	CHAR *pLine;
	CWinpeDoc* pDoc;

	char *SzDebugFormats[] =
	{
		"UNKNOWN/BORLAND",
		"COFF",
		"CODEVIEW",
		"FPO",
		"MISC",
		"EXCEPTION",
		"FIXUP"
	};

	
	pDoc = GetDocument();
	pfile = pDoc->GetDocumentDataP();

	pDosHdr = (PIMAGE_DOS_HEADER)pfile;
	pNTHeader = MakePtr(PIMAGE_NT_HEADERS,pfile,pDosHdr->e_lfanew);

	// This line was so long that we had to break it up
    va_debug_dir = pNTHeader->OptionalHeader.
                        DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].
                        VirtualAddress;
    if ( va_debug_dir == 0 )  // no debug directory send msg.
	{
		string = "No Debug Directory";
		m_DisplayData.Add(string);
        return 1;
	}

    // If we found a .debug section, and the debug directory is at the
    // beginning of this section, it looks like a Borland file
    header = GetSectionHeader(".debug",pNTHeader);
    if ( header && (header->VirtualAddress == va_debug_dir) )
    {
        debugDir = (PIMAGE_DEBUG_DIRECTORY)(header->PointerToRawData+pfile);
        size = pNTHeader->OptionalHeader.
                DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size *
                sizeof(IMAGE_DEBUG_DIRECTORY);
    }
    else    // Look for microsoft debug directory in the .rdata section
    {
        header = GetSectionHeader(".rdata",pNTHeader);
        if ( !header )
		{ // no debug info send msg
			string = "No Debug Directory";
			m_DisplayData.Add(string);
			return 1;
            
		}

        size = pNTHeader->OptionalHeader.
                        DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size;
    
        offsetInto_rdata = va_debug_dir - header->VirtualAddress;
        debugDir = MakePtr(PIMAGE_DEBUG_DIRECTORY,pfile,
                   header->PointerToRawData + offsetInto_rdata);
    }

    

//
// Dump the debug directory array
//

    cDebugFormats = size / sizeof(IMAGE_DEBUG_DIRECTORY);
    
    
    if ( cDebugFormats == 0 )
	{
		string = "No Debug Directory";
		m_DisplayData.Add(string);
		return 1;
     
	}
    
	string = "Debug Formats";
	m_DisplayData.Add(string);

    string = 
    "  Type            Size     Address  FilePtr  Charactr TimeData Version";
	m_DisplayData.Add(string);
	string = 
    "  --------------- -------- -------- -------- -------- -------- --------";
    m_DisplayData.Add(string);
    
    for ( i=0; i < cDebugFormats; i++ )
    {
        szDebugFormat = (debugDir->Type <= 6)
                        ? SzDebugFormats[debugDir->Type] : "???";

        wsprintf(line,"  %-15s %08X %08X %08X %08X %08X %u.%02u",
            szDebugFormat, debugDir->SizeOfData, debugDir->AddressOfRawData,
            debugDir->PointerToRawData, debugDir->Characteristics,
            debugDir->TimeDateStamp, debugDir->MajorVersion,
            debugDir->MinorVersion);
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);
		//
		// set us up for symbol dump.
		//
		if (debugDir->Type == IMAGE_DEBUG_TYPE_COFF)
		{
			PCOFFDebugInfo = (PIMAGE_COFF_SYMBOLS_HEADER)
				((DWORD)pfile + debugDir->PointerToRawData);
		}
        debugDir++;
    }

	string = "  ";
	m_DisplayData.Add(string);
		        
    
    
    return m_DisplayData.GetSize(); 

}



void CDebugDirView::DumpCOFFHeader()
{
	CString string;
	CHAR *pLine;
	CHAR line[128];

	string = "COFF Debug Info Header:";


    wsprintf(line,"  NumberOfSymbols:      %08X", PCOFFDebugInfo->NumberOfSymbols);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    wsprintf(line,"  LvaToFirstSymbol:     %08X", PCOFFDebugInfo->LvaToFirstSymbol);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  NumberOfLinenumbers:  %08X", PCOFFDebugInfo->NumberOfLinenumbers);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  LvaToFirstLinenumber: %08X", PCOFFDebugInfo->LvaToFirstLinenumber);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  RvaToFirstByteOfCode: %08X", PCOFFDebugInfo->RvaToFirstByteOfCode);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  RvaToLastByteOfCode:  %08X", PCOFFDebugInfo->RvaToLastByteOfCode);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  RvaToFirstByteOfData: %08X", PCOFFDebugInfo->RvaToFirstByteOfData);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"  RvaToLastByteOfData:  %08X", PCOFFDebugInfo->RvaToLastByteOfData);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

	return;


}






void CDebugDirView::DumpLineNumbers(PIMAGE_LINENUMBER pln,DWORD count)
{
	char buffer[64];
    DWORD i;
	CString string;
	CHAR *pLine;
	CHAR line[128];
    
    string = "Line Numbers";
	m_DisplayData.Add(string);

    
    for (i=0; i < count; i++)
    {
        if ( pln->Linenumber == 0 ) // A symbol table index
        {
            buffer[0] = 0;
            LookupSymbolName(pln->Type.SymbolTableIndex, buffer,
                            sizeof(buffer));
            wsprintf(line,"SymIndex: %X (%s)", pln->Type.SymbolTableIndex,
                                             buffer);
			pLine = string.GetBuffer(strlen(line)+1);
			strcpy(pLine,line);
			string.ReleaseBuffer();
			m_DisplayData.Add(string);
        }
        else        // A regular line number
		{
            wsprintf(line," Addr: %05X  Line: %04X",
                pln->Type.VirtualAddress, pln->Linenumber);
			pLine = string.GetBuffer(strlen(line)+1);
			strcpy(pLine,line);
			string.ReleaseBuffer();
			m_DisplayData.Add(string);
		}
        pln++;
    }

}

BOOL CDebugDirView::LookupSymbolName(DWORD index,LPTSTR buffer,UINT length)
{
	LPTSTR stringTable;

    if ( index >= COFFSymbolCount )
        return FALSE;
    
    if ( PCOFFSymbolTable == 0 )
        return FALSE;
    
    if ( PCOFFSymbolTable[index].N.Name.Short != 0 )
    {
        strncpy(buffer, (LPCTSTR)PCOFFSymbolTable[index].N.ShortName, min(8,length));
        buffer[8] = 0;
    }
    else
    {
        stringTable = (LPTSTR)&PCOFFSymbolTable[COFFSymbolCount]; 
        strncpy(buffer,
                stringTable + PCOFFSymbolTable[index].N.Name.Long, length);
        buffer[length-1] = 0;
    }
    
    return TRUE;


}

void CDebugDirView::DumpSymbolTable(PIMAGE_SYMBOL pSymbolTable,UINT cSymbols)
{
	unsigned i;
    LPTSTR stringTable;
    char sectionName[10];
	CString string;
	CHAR *pLine;
	CHAR line[128];
    
    wsprintf(line,"Symbol Table - %X entries  (* = auxillary symbol)", cSymbols);
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
    wsprintf(line,"%s",
    "Indx Name                 Value    Section    cAux  Type    Storage");
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);
	wsprintf(line,"%s",
    "---- -------------------- -------- ---------- ----- ------- --------");
	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

    // The string table apparently starts right after the symbol table
    stringTable = (LPTSTR)&pSymbolTable[cSymbols]; 
        
    for ( i=0; i < cSymbols; i++ )
    {
        wsprintf(line,"%04X ", i);
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);
        
        if ( pSymbolTable->N.Name.Short != 0 )
		{
            wsprintf(line,"%-20.8s", pSymbolTable->N.ShortName);
		}
        else
		{
            wsprintf(line,"%-20s", stringTable + pSymbolTable->N.Name.Long);
		}
        pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);

        wsprintf(line," %08X", pSymbolTable->Value);
		pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);
    
        GetSectionName(pSymbolTable->SectionNumber, sectionName,
                        sizeof(sectionName));

        wsprintf(line," sect:%s aux:%X type:%02X st:%s",
                sectionName,
                pSymbolTable->NumberOfAuxSymbols,
                pSymbolTable->Type,
                GetSZStorageClass(pSymbolTable->StorageClass) );
        pLine = string.GetBuffer(strlen(line)+1);
		strcpy(pLine,line);
		string.ReleaseBuffer();
		m_DisplayData.Add(string);

        if ( pSymbolTable->NumberOfAuxSymbols )
            DumpAuxSymbols(pSymbolTable);

        // Take into account any aux symbols
        i += pSymbolTable->NumberOfAuxSymbols;
        pSymbolTable += pSymbolTable->NumberOfAuxSymbols;
        pSymbolTable++;
    }
}




void CDebugDirView::GetSectionName(WORD section,LPTSTR buffer,UINT cbBuffer)
{
	char tempbuffer[10];
    
    switch ( (SHORT)section )
    {
        case IMAGE_SYM_UNDEFINED: strcpy(tempbuffer, "UNDEF"); break;
        case IMAGE_SYM_ABSOLUTE:  strcpy(tempbuffer, "ABS  "); break;
        case IMAGE_SYM_DEBUG:     strcpy(tempbuffer, "DEBUG"); break;
        default: sprintf(tempbuffer, "%-5X", section);
    }
    
    strncpy(buffer, tempbuffer, cbBuffer-1);

}

LPTSTR CDebugDirView::GetSZStorageClass(BYTE storageClass)
{
	// The names of the first group of possible symbol table storage classes
char * SzStorageClass1[] = {
"NULL","AUTOMATIC","EXTERNAL","STATIC","REGISTER","EXTERNAL_DEF","LABEL",
"UNDEFINED_LABEL","MEMBER_OF_STRUCT","ARGUMENT","STRUCT_TAG",
"MEMBER_OF_UNION","UNION_TAG","TYPE_DEFINITION","UNDEFINED_STATIC",
"ENUM_TAG","MEMBER_OF_ENUM","REGISTER_PARAM","BIT_FIELD"
};

// The names of the second group of possible symbol table storage classes
char * SzStorageClass2[] = {
"BLOCK","FUNCTION","END_OF_STRUCT","FILE","SECTION","WEAK_EXTERNAL"
};

	if ( storageClass <= IMAGE_SYM_CLASS_BIT_FIELD )
        return SzStorageClass1[storageClass];
    else if ( (storageClass >= IMAGE_SYM_CLASS_BLOCK)
              && (storageClass <= IMAGE_SYM_CLASS_WEAK_EXTERNAL) )
        return SzStorageClass2[storageClass-IMAGE_SYM_CLASS_BLOCK];
    else
        return "???";

}

void CDebugDirView::DumpAuxSymbols(PIMAGE_SYMBOL pSymbolTable)
{
	CString string;
	CHAR *pLine;
	CHAR line[128];

	PIMAGE_AUX_SYMBOL auxSym;
    
    auxSym = (PIMAGE_AUX_SYMBOL)(pSymbolTable+1);
    
    if ( pSymbolTable->StorageClass == IMAGE_SYM_CLASS_FILE )
        wsprintf(line,"     * %s", auxSym);
    else 
		if ( (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) )
		{
			if ( (pSymbolTable->Type & 0xF0) == (IMAGE_SYM_DTYPE_FUNCTION << 4))
			{   
				wsprintf(line,"     * tag: %04X  size: %04X  Line #'s: %08X  next fn: %04X",
				auxSym->Sym.TagIndex, auxSym->Sym.Misc.TotalSize,
				auxSym->Sym.FcnAry.Function.PointerToLinenumber,
				auxSym->Sym.FcnAry.Function.PointerToNextFunction);
			}
		}
    else
		if ( (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_STATIC) )
		{
			wsprintf(line,
				"     * Section: %04X  Len: %05X  Relocs: %04X  LineNums: %04X",
				auxSym->Section.Number, auxSym->Section.Length,
				auxSym->Section.NumberOfRelocations,
				auxSym->Section.NumberOfLinenumbers);

		}

	pLine = string.GetBuffer(strlen(line)+1);
	strcpy(pLine,line);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);


}



PIMAGE_SECTION_HEADER CDebugDirView::GetSectionHeader(LPTSTR name,PIMAGE_NT_HEADERS pNTHeader)
{
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(pNTHeader);
    unsigned i;
    
    for ( i=0; i < pNTHeader->FileHeader.NumberOfSections; i++, section++ )
    {
        if ( strnicmp((LPCTSTR)section->Name, name, IMAGE_SIZEOF_SHORT_NAME) == 0 )
            return section;
    }
    
    return 0;

}

void CDebugDirView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
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

void CDebugDirView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//CScrollView::OnPrint(pDC, pInfo);
	PrintPageHeader (pDC, pInfo->m_nCurPage);
    PrintPage (pDC, pInfo->m_nCurPage);
}

void CDebugDirView::PrintPageHeader (CDC* pDC, UINT nPageNumber)
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

void CDebugDirView::PrintPage(CDC* pDC, UINT nPageNumber)
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

void CDebugDirView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
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
