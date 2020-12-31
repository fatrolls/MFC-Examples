#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIView, CView)

BEGIN_MESSAGE_MAP(CGDIView, CView)
	//{{AFX_MSG_MAP(CGDIView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC* pDC)
{
	CGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CGDIView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif

void CGDIView::OnInitialUpdate() 
{
	CClientDC dc(this);
	CString szStr;
	CString szBuf;
	int nRasterCaps;
	int nNumOfColors;
	int nNumOfReserved;
	int nColorRes;

	CView::OnInitialUpdate();
	
	szStr="My video device's ability:\n";
	nRasterCaps=dc.GetDeviceCaps(RASTERCAPS);
	if(nRasterCaps & RC_PALETTE)
	{
		szStr+="\tIt is a palette device\n";
		nNumOfColors=dc.GetDeviceCaps(SIZEPALETTE);
		szBuf.Format("\tThe device supports %d colors\n", nNumOfColors);
		szStr+=szBuf;
		szBuf.Empty();
		nNumOfReserved=dc.GetDeviceCaps(NUMRESERVED);
		szBuf.Format("\tThere are %d static colors\n", nNumOfReserved);
		szStr+=szBuf;
		nColorRes=dc.GetDeviceCaps(COLORRES);
		szBuf.Format("\tColor resolution is %d bits\n", nColorRes);
		szStr+=szBuf;
	}
	else
	{
		szStr+="\tIt is not a palette device\n";
	}
	szBuf.Empty();
	szBuf.Format
	(
		"\tHorizontal size is %d mm, %d pixels\n",
		dc.GetDeviceCaps(HORZSIZE),
		dc.GetDeviceCaps(HORZRES)
	);
	szStr+=szBuf;
	szBuf.Empty();
	szBuf.Format
	(
		"\tVertical size is %d mm, %d pixels\n",
		dc.GetDeviceCaps(VERTSIZE),
		dc.GetDeviceCaps(VERTRES)
	);
	szStr+=szBuf;
	AfxMessageBox(szStr);
}
