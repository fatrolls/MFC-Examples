// winpeView.cpp : implementation of the CSymbolView class
//

#include "stdafx.h"
#include "winpe.h"
//#include "pefile.h"
#include "winpeDoc.h"
#include "SymbolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSymbolView

IMPLEMENT_DYNCREATE(CSymbolView, CScrollView)

BEGIN_MESSAGE_MAP(CSymbolView, CScrollView)
	//{{AFX_MSG_MAP(CSymbolView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSymbolView construction/destruction

CSymbolView::CSymbolView()
{
	// TODO: add construction code here

}

CSymbolView::~CSymbolView()
{
}

BOOL CSymbolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSymbolView drawing

void CSymbolView::OnDraw(CDC* pDC)
{
	CWinpeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	
	if (m_nLinesTotal != 0)
	{
		
		CRect rect;
		pDC->GetClipBox(&rect);

		UINT nStart = rect.top / m_cyScreen;
		UINT nEnd = min(m_nLinesTotal - 1,
						 (rect.bottom + m_cyScreen - 1) /
						 m_cyScreen);


	
		CFont * pOldFont = pDC->SelectObject(&m_screenFont);

	
		for (UINT i = nStart; i <= nEnd; i++)
		{
			

			pDC->TextOut(2,(i * m_cyScreen) +2,m_DisplayData[i]);
		}

		
		pDC->SelectObject(pOldFont);

		
	}


	
}

/////////////////////////////////////////////////////////////////////////////
// CSymbolView printing

BOOL CSymbolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSymbolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSymbolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSymbolView diagnostics

#ifdef _DEBUG
void CSymbolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSymbolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWinpeDoc* CSymbolView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinpeDoc)));
	return (CWinpeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSymbolView message handlers


int CSymbolView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CClientDC dc (this);
	int nHeight = -((dc.GetDeviceCaps (LOGPIXELSY) * 10 ) / 72);

	m_screenFont.CreateFont(nHeight,
							0,0,0,
							FW_NORMAL,
							0,0,0,
							DEFAULT_CHARSET,
							OUT_CHARACTER_PRECIS,
							CLIP_CHARACTER_PRECIS,
							DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_DONTCARE,
							"Courier New");

	TEXTMETRIC tm;
	CFont * pOldFont = dc.SelectObject(&m_screenFont);
	dc.GetTextMetrics (&tm);
	m_cyScreen = tm.tmHeight + tm.tmExternalLeading;
	dc.SelectObject(pOldFont);
	return 0;
}

void CSymbolView::OnInitialUpdate() 
{

	DWORD nDocLength = GetDocument()->GetDocumentLength();

	if (nDocLength == 0)
	{
		m_nLinesTotal = 0;
		
	}
	else
	{
		m_nLinesTotal = GetSymbols();
		
	}



	SetScrollSizes (MM_TEXT,
					CSize(0,m_nLinesTotal * m_cyScreen), //tot size
					CSize(0,m_cyScreen * 10),			 //screen size 
					CSize (0,m_cyScreen));				//line size

	ScrollToPosition(CPoint (0,0));

	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}




INT CSymbolView::GetSymbols()
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

	PIMAGE_SYMBOL PCOFFSymbolTable;
    DWORD COFFSymbolCount;
    PIMAGE_COFF_SYMBOLS_HEADER PCOFFDebugInfo;
	


	pDoc = GetDocument();
	pfile = pDoc->GetDocumentDataP();

	pDosHdr = (PIMAGE_DOS_HEADER)pfile;
	base = (DWORD)pfile;
	
	pNTHeader = MakePtr(PIMAGE_NT_HEADERS,
						pfile,pDosHdr->e_lfanew);

	if (pNTHeader->FileHeader.PointerToSymbolTable == 0)
	{
		string = "No Symbol Table:";
		m_DisplayData.Add(string);
		return m_DisplayData.GetSize(); 
	}

    PCOFFSymbolTable = MakePtr(PIMAGE_SYMBOL, base,
                        pNTHeader->FileHeader.PointerToSymbolTable);
    COFFSymbolCount = pNTHeader->FileHeader.NumberOfSymbols;

    
    DumpCOFFHeader( PCOFFDebugInfo );
   
    
    
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


void CSymbolView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
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
