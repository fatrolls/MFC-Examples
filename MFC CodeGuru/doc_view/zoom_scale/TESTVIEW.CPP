// testview.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "mainfrm.h"
#include "zoomview.h"	// For CZoomView class
#include "test.h"
#include "afxpriv.h"    // For WM_SETMESSAGESTRING
#include "testdoc.h"
#include "testview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Define some colors to make the boxes better looking
#define NUM_COLORS 9
#define COLOR_YELLOW  RGB(255, 255,   0)
#define COLOR_PURPLE  RGB(255,   0, 255)
#define COLOR_BLACK   RGB(  0,   0,   0)
#define COLOR_RED     RGB(255,   0,   0)
#define COLOR_GREEN   RGB(  0, 255,   0)
#define COLOR_DKGREEN RGB(  0, 128,   0)
#define COLOR_BLUE    RGB(  0,   0, 255)
#define COLOR_AQUA    RGB(  0, 255, 255)
#define COLOR_GRAY    RGB(192, 192, 192)
COLORREF colors[NUM_COLORS] = {COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_DKGREEN, 
	COLOR_BLUE, COLOR_AQUA, COLOR_YELLOW, COLOR_PURPLE, COLOR_GRAY};

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CZoomView)

BEGIN_MESSAGE_MAP(CTestView, CZoomView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomout)
	ON_COMMAND(ID_VIEW_ZOOMFULL, OnViewZoomfull)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CZoomView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CZoomView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
}

CTestView::~CTestView()
{
	// Clean up
	if (m_font) delete m_font;
}

void CTestView::OnInitialUpdate()
{
	CZoomView::OnInitialUpdate();
	CTestDoc* pDoc = GetDocument();

	// Initialize the CZoomView class
	SetZoomSizes(pDoc->GetDocSize());

	// Create the LOGICAL font to draw with (only once!)
	int height = (m_totalLog.cy / 10) / 5;  // 1/5 of box size
	m_font = new CFont();
   m_font->CreateFont(height, 0, 0, 0,
         FW_NORMAL, FALSE, FALSE,
         FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
         DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, "Arial");
} // OnInitialUpdate

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing
void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc *pDoc = GetDocument();
	CPen     *oldPen;
	CFont    *oldFont;
	char     buf[12];

	// Draw border
	CRect rect(1, 1, m_totalLog.cx - 1, m_totalLog.cy - 1);
	pDC->Rectangle(&rect);

	// Draw a 10x10 grid of boxes of boxs - alternating color
	// Notice I am drawing completely in LOGICAL units!
	oldFont = pDC->SelectObject(m_font);
	int color  = 0;
	int width  = m_totalLog.cx / 10;
	int height = m_totalLog.cy / 10;
	int widthPad  = width  / 10;
	int heightPad = height / 10;
	int textX, textY;
	CSize size;
	for (int row = 0; row < 10; row++) {
		for (int col = 0; col < 10; col++) {
			rect.SetRect(col * width  + widthPad, row * height + heightPad,
							 col * width  + width  - widthPad, 
							 row * height + height - heightPad);
			CPen newPen(PS_SOLID, 0, colors[color]); // 0 width = 1 device unit
			oldPen = pDC->SelectObject(&newPen);
			pDC->Rectangle(&rect);
			pDC->SelectObject(oldPen);
			// Rotate colors
			if (++color > NUM_COLORS - 1) {
				color = 0;
			}
			// Draw the row/col text
			wsprintf(buf, "row %d", row);
			size  = pDC->GetTextExtent(buf, strlen(buf));
			textX = rect.left + (rect.Width()/2  - size.cx/2);
			textY = rect.top  + (rect.Height()/2 - size.cy);  // 2 texts
			pDC->TextOut(textX, textY, buf, strlen(buf));
			wsprintf(buf, "col %d", col);
			textY += size.cy;
			pDC->TextOut(textX, textY, buf, strlen(buf));
		}
	}
	pDC->SelectObject(oldFont);
} // OnDraw

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
} // OnPreparePrinting

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
} // OnBeginPrinting

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
} // OnEndPrinting



/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CZoomView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CZoomView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*) m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers
//
/*---------------------------------------------------------------------------
   FUNCTION: OnViewZoomin
   PURPOSE : User pressed the ZOOM IN toolbutton or menu
---------------------------------------------------------------------------*/
void CTestView::OnViewZoomin()
{
	// Toggle zoomin mode
	CWnd *pWin = ((CWinApp *) AfxGetApp())->m_pMainWnd;
	if (GetZoomMode() == MODE_ZOOMIN) {
		SetZoomMode(MODE_ZOOMOFF);
		// Clear the statusbar
		pWin->SendMessage(WM_SETMESSAGESTRING, 0, 
			(LPARAM)(LPCSTR)"");
	} else {
		SetZoomMode(MODE_ZOOMIN);
		// Give instructions in the statusbar
		pWin->SendMessage(WM_SETMESSAGESTRING, 0, 
			(LPARAM)(LPCSTR)"Click to zoom in on point or drag a zoom box.");
	}
} // OnViewZoomin

/*---------------------------------------------------------------------------
   FUNCTION: OnViewZoomout
   PURPOSE : User pressed the ZOOM OUT toolbutton or menu
---------------------------------------------------------------------------*/
void CTestView::OnViewZoomout()
{
	// Toggle zoomout mode
	CWnd *pWin = ((CWinApp *) AfxGetApp())->m_pMainWnd;
	if (GetZoomMode() == MODE_ZOOMOUT) {
		SetZoomMode(MODE_ZOOMOFF);
		// Clear the statusbar
		pWin->SendMessage(WM_SETMESSAGESTRING, 0, 
			(LPARAM)(LPCSTR)"");
	} else {
		SetZoomMode(MODE_ZOOMOUT);
		// Give instructions in the statusbar
		pWin->SendMessage(WM_SETMESSAGESTRING, 0, 
			(LPARAM)(LPCSTR)"Click to zoom out on point.");
	}
} // OnViewZoomout

/*---------------------------------------------------------------------------
   FUNCTION: OnViewZoomfull
   PURPOSE : User pressed the ZOOM FULL toolbutton or menu
---------------------------------------------------------------------------*/
void CTestView::OnViewZoomfull()
{
	DoZoomFull();  // Call CZoomView member to zoom full scale
} // OnViewZoomfull

/*---------------------------------------------------------------------------
   FUNCTION: OnUpdateViewZoomin
   PURPOSE : Tell MFC whether to depress the button or check the menu
---------------------------------------------------------------------------*/
void CTestView::OnUpdateViewZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetZoomMode() == MODE_ZOOMIN);
} // OnUpdateViewZoomin

/*---------------------------------------------------------------------------
   FUNCTION: OnUpdateViewZoomout
   PURPOSE : Tell MFC whether to depress the button or check the menu
---------------------------------------------------------------------------*/
void CTestView::OnUpdateViewZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetZoomMode() == MODE_ZOOMOUT);
} // OnUpdateViewZoomout
