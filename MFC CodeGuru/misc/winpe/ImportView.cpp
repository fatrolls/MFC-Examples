// winpeView.cpp : implementation of the CImportView class
//

#include "stdafx.h"
#include "winpe.h"
//#include "pefile.h"
#include "winpeDoc.h"
#include "ImportView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportView

IMPLEMENT_DYNCREATE(CImportView, CScrollView)

BEGIN_MESSAGE_MAP(CImportView, CScrollView)
	//{{AFX_MSG_MAP(CImportView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportView construction/destruction

CImportView::CImportView()
{
	// TODO: add construction code here
	
}

CImportView::~CImportView()
{
}

BOOL CImportView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImportView drawing

void CImportView::OnDraw(CDC* pDC)
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
// CImportView printing

BOOL CImportView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImportView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	
	m_keepprinting = TRUE;
	
    
}

void CImportView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImportView diagnostics

#ifdef _DEBUG
void CImportView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImportView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinpeDoc* CImportView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinpeDoc)));
	return (CWinpeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImportView message handlers


int CImportView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CImportView::OnInitialUpdate() 
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	pDoc->TurnChecksOff();
	pDoc->m_Imports_Checked = TRUE;
	DWORD nDocLength = pDoc->GetDocumentLength();

	if (nDocLength == 0)
	{
		m_nLinesTotal = 0;
		
	}
	else
	{
		m_nLinesTotal = GetImportsSection();
		
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




INT CImportView::GetImportsSection()
{
	
	BYTE * pfile;
	CString string;
	CString stringapnd;
	CHAR line[128];
	CHAR line2[128];
	CWinpeDoc* pDoc;
	PIMAGE_IMPORT_DESCRIPTOR importDesc;
	PIMAGE_DOS_HEADER pDosHdr;
	PIMAGE_NT_HEADERS pNTHeader;
    PIMAGE_SECTION_HEADER pSection;
    PIMAGE_THUNK_DATA thunk, thunkIAT=0;
    PIMAGE_IMPORT_BY_NAME pOrdinalName;
    DWORD importsStartRVA;
    INT delta = -1;



	pDoc = GetDocument();
	pfile = pDoc->GetDocumentDataP();

	pDosHdr = (PIMAGE_DOS_HEADER)pfile;

	
	pNTHeader = MakePtr(PIMAGE_NT_HEADERS,
						pfile,pDosHdr->e_lfanew);
	// Look up where the imports section is (normally in the .idata section)
    // but not necessarily so.  Therefore, grab the RVA from the data dir.
    importsStartRVA = pNTHeader->OptionalHeader.DataDirectory
                            [IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
    if ( !importsStartRVA )
	{
		string = "No Imports Table Found:";
		m_DisplayData.Add(string);		
        return m_DisplayData.GetSize(); 
	}
     

    // Get the IMAGE_SECTION_HEADER that contains the imports.  This is
    // usually the .idata section, but doesn't have to be.
    pSection = pDoc->GetEnclosingSectionHeader(importsStartRVA,
										 pNTHeader );
    if ( !pSection )
	{
		string = "No Imports Table Found:";
		m_DisplayData.Add(string);		
        return m_DisplayData.GetSize(); 
	}
    

    delta = (INT)(pSection->VirtualAddress-pSection->PointerToRawData);
    
    importDesc = (PIMAGE_IMPORT_DESCRIPTOR) (importsStartRVA - delta + (DWORD)pfile);
            
    string = "Imports Table:";
	m_DisplayData.Add(string);	
    
    while ( 1 )
    {
        // See if we've reached an empty IMAGE_IMPORT_DESCRIPTOR
        if ( (importDesc->TimeDateStamp==0 ) && (importDesc->Name==0) )
            break;
        
        wsprintf(line,"  %s", (PBYTE)(importDesc->Name) - delta + (DWORD)pfile);
		AttaLine(line);	
        wsprintf(line,"  Hint/Name Table: %08X", importDesc->Characteristics);
		AttaLine(line);	
        wsprintf(line,"  TimeDateStamp:   %08X", importDesc->TimeDateStamp);
		AttaLine(line);
        wsprintf(line,"  ForwarderChain:  %08X", importDesc->ForwarderChain);
		AttaLine(line);
        wsprintf(line,"  First thunk RVA: %08X", importDesc->FirstThunk);
		AttaLine(line);
    
        thunk = (PIMAGE_THUNK_DATA)importDesc->Characteristics;
        thunkIAT = (PIMAGE_THUNK_DATA)importDesc->FirstThunk;

        if ( thunk == 0 )   // No Characteristics field?
        {
            // Yes! Gotta have a non-zero FirstThunk field then.
            thunk = thunkIAT;
            
            if ( thunk == 0 )
			{                  // No FirstThunk field?  Ooops!!!
				string = "No First Thunk? Ooops! !";
				m_DisplayData.Add(string);		
				return m_DisplayData.GetSize();
			}
             
        }
        
        // Adjust the pointer to point where the tables are in the
        // mem mapped file.
        thunk = (PIMAGE_THUNK_DATA)( (PBYTE)thunk - delta + (DWORD)pfile);
        thunkIAT = (PIMAGE_THUNK_DATA)( (PBYTE)thunkIAT - delta + (DWORD)pfile);
    
        string = "  Ordn  Name";
        
        while ( 1 ) // Loop forever (or until we break out)
        {
            if ( thunk->u1.AddressOfData == 0 )
                break;

            if ( thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG )
            {
                wsprintf(line,"  %4u", IMAGE_ORDINAL(thunk->u1.Ordinal) );
				
				
            }
            else
            {
                pOrdinalName = thunk->u1.AddressOfData;
                pOrdinalName = (PIMAGE_IMPORT_BY_NAME)
                                ((PBYTE)pOrdinalName - delta + (DWORD)pfile);
                    
                wsprintf(line,"  %4u  %s", pOrdinalName->Hint, pOrdinalName->Name);
            }
            

            
            wsprintf(line2, " (IAT: %08X)", thunkIAT->u1.Function );
			strcat(line,line2);
			AttaLine(line);
           
            thunk++;            // Advance to next thunk
            thunkIAT++;         // advance to next thunk
        }

        importDesc++;   // advance to next IMAGE_IMPORT_DESCRIPTOR
		string = ":  ";
		m_DisplayData.Add(string);
        
    }
    
	string = ":  ";
	m_DisplayData.Add(string);
	return m_DisplayData.GetSize(); 

}


void CImportView::AttaLine(CHAR* pLine)
{
	CString string;
	CHAR *sLine;
	
	
	// set len back to 1 after testing
	sLine = string.GetBuffer(strlen(pLine)+1);
	strcpy(sLine,pLine);
	string.ReleaseBuffer();
	m_DisplayData.Add(string);

	
   

}


void CImportView::PrintPageHeader (CDC* pDC, UINT nPageNumber)
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

void CImportView::PrintPage(CDC* pDC, UINT nPageNumber)
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_nLinesTotal != 0) 
	{
        INT nStart = (nPageNumber - 1) * m_nLinesPerPage;
        INT nEnd = min (m_nLinesTotal - 1,
						nStart + m_nLinesPerPage - 1);

		
		nEnd = m_nLinesTotal - 1;
		//TRACE("End %d\n",nEnd);
		//TRACE("Start %d\n",nStart);
		//TRACE("pageno %d\n",nPageNumber);
        CString string;
        CFont* pOldFont = pDC->SelectObject (pDoc->m_printerFont);

        INT y;
        for (INT i=nStart; i<=nEnd; i++)
		{

            //FormatLine (i, string);
            y = ((i - nStart) + PRINTMARGIN + 3) * m_cyPrinter;
            pDC->TextOut (0, -y,m_DisplayData[i]);
			//TRACE("Data: %s\n",m_DisplayData[i]);
        }
        pDC->SelectObject (pOldFont);
		//TRACE("y %d\n",y);
    }

}

void CImportView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
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
		if (!pInfo->m_bPreview)
			pInfo->m_bContinuePrinting = m_keepprinting;
		
	}

}

void CImportView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CSize size = pDC->GetTextExtent(m_DisplayData[0]);
	m_cyPrinter = size.cy;

	INT vert = pInfo->m_rectDraw.Height();
	vert = abs(vert);
	vert -= m_cyPrinter * (3 + (2 * PRINTMARGIN));
	m_nLinesPerPage = abs(vert) / size.cy - 1;
	int maxpage = m_nLinesTotal / m_nLinesPerPage;
	if (m_nLinesTotal % m_nLinesPerPage)
		maxpage++;

	pInfo->SetMaxPage(maxpage);

	m_cxWidth = pInfo->m_rectDraw.Width();
	



	//CScrollView::OnPrint(pDC, pInfo);
	PrintPageHeader (pDC, pInfo->m_nCurPage);
    //PrintPage (pDC, pInfo->m_nCurPage);
	int i,x;
	INT marginlength = m_cyPrinter * (3 + (2 * PRINTMARGIN));
	for (i=0;i<m_nLinesPerPage;i++)
	{
		x = (pInfo->m_nCurPage -1) * m_nLinesPerPage + i;
		if (x >= m_nLinesTotal)
		{
			m_keepprinting = FALSE;
			break;
		}
		
		//pDC->TextOut (0, -i*(size.cy),m_DisplayData[x]);
		pDC->TextOut (0, (-i*(size.cy))-marginlength,
		
		m_DisplayData[x]);
	}


}

void CImportView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
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
