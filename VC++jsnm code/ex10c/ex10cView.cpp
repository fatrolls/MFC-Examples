// ex10cView.cpp : implementation of the CEx10cView class
//

#include "stdafx.h"
#include "ex10c.h"

#include "ex10cDoc.h"
#include "ex10cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10cView

IMPLEMENT_DYNCREATE(CEx10cView, CScrollView)

BEGIN_MESSAGE_MAP(CEx10cView, CScrollView)
	//{{AFX_MSG_MAP(CEx10cView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10cView construction/destruction

CEx10cView::CEx10cView()
{
	// TODO: add construction code here

}

CEx10cView::~CEx10cView()
{
}

BOOL CEx10cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx10cView drawing

void CEx10cView::OnDraw(CDC* pDC)
{
	BeginWaitCursor();
	m_dibResource.UsePalette(pDC); // should be in palette
	m_dibFile.UsePalette(pDC);     //  message handlers, not here
	pDC->TextOut(0, 0,
		"Click the left mouse button here to load a file.");
	CSize sizeResourceDib = m_dibResource.GetDimensions();
	sizeResourceDib.cx *= 30;
	sizeResourceDib.cy *= -30;
	m_dibResource.Draw(pDC, CPoint(0, -800), sizeResourceDib);
	CSize sizeFileDib = m_dibFile.GetDimensions();
	sizeFileDib.cx *= 30;
	sizeFileDib.cy *= -30;
	m_dibFile.Draw(pDC, CPoint(1800, -800), sizeFileDib);
	EndWaitCursor();
}

void CEx10cView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal(30000, 40000); // 30-by-40 cm
	CSize sizeLine = CSize(sizeTotal.cx / 100, sizeTotal.cy / 100);
	SetScrollSizes(MM_HIMETRIC, sizeTotal, sizeTotal, sizeLine);

	LPVOID lpvResource = (LPVOID) ::LoadResource(NULL,
		::FindResource(NULL, MAKEINTRESOURCE(IDB_REDBLOCKS),
		RT_BITMAP));
	m_dibResource.AttachMemory(lpvResource); // no need for
	                                         //  ::LockResource
	CClientDC dc(this);
	TRACE("bits per pixel  = %d\n", dc.GetDeviceCaps(BITSPIXEL));
}

/////////////////////////////////////////////////////////////////////////////
// CEx10cView printing

BOOL CEx10cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx10cView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx10cView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx10cView diagnostics

#ifdef _DEBUG
void CEx10cView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx10cView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx10cDoc* CEx10cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx10cDoc)));
	return (CEx10cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10cView message handlers

#define MEMORY_MAPPED_FILES
void CEx10cView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CFileDialog dlg(TRUE, "bmp", "*.bmp");
	if (dlg.DoModal() != IDOK) {
		return;
	}
#ifdef MEMORY_MAPPED_FILES
	if (m_dibFile.AttachMapFile(dlg.GetPathName(),
			TRUE) == TRUE) { // share
		Invalidate();
	}
#else
	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	if (m_dibFile.Read(&file) == TRUE) {
		Invalidate();
	}
#endif // MEMORY_MAPPED_FILES
	CClientDC dc(this);
	m_dibFile.SetSystemPalette(&dc);
}
