// PopupBarView.cpp : implementation of the CPopupBarView class
//

#include "stdafx.h"
#include "PopupBar.h"

#include "MainFrm.h"
#include "PopupBarDoc.h"
#include "PopupBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupBarView

IMPLEMENT_DYNCREATE(CPopupBarView, CView)

BEGIN_MESSAGE_MAP(CPopupBarView, CView)
	//{{AFX_MSG_MAP(CPopupBarView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupBarView construction/destruction

CPopupBarView::CPopupBarView()
{
	// TODO: add construction code here

}

CPopupBarView::~CPopupBarView()
{
}

BOOL CPopupBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPopupBarView drawing

void CPopupBarView::OnDraw(CDC* pDC)
{
	CPopupBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	// fill square
	CBrush brush(pDoc->GetFillColor());
	CRect rectSquare=m_rectWholeSquare;
	rectSquare.InflateRect(0,0,1,1);
	pDC->FillRect(rectSquare,&brush);

	// draw borders
	int nBorderStyle=pDoc->GetBorderStyle();
	if(nBorderStyle!=ID_BORDER_NONE)
	{
		// set pen to draw borders
		COLORREF clrBorder=pDoc->GetBorderColor();
		CPen pen;
		switch(pDoc->GetDashStyle())
		{
		case ID_DASH_SOLID:
			{
				VERIFY(pen.CreatePen(PS_SOLID,1,clrBorder));
				break;
			}
		case ID_DASH_DASH:
			{
				VERIFY(pen.CreatePen(PS_DASH,1,clrBorder));
				break;
			}
		case ID_DASH_DOT:
			{
				VERIFY(pen.CreatePen(PS_DOT,1,clrBorder));
				break;
			}
		case ID_DASH_DASHDOT:
			{
				VERIFY(pen.CreatePen(PS_DASHDOT,1,clrBorder));
				break;
			}
		case ID_DASH_DASHDOTDOT:
			{
				VERIFY(pen.CreatePen(PS_DASHDOTDOT,1,clrBorder));
				break;
			}
		default:
			ASSERT(FALSE);
		}

		pDC->SelectObject(&pen);
		pDC->SetBkMode(TRANSPARENT);

		CRect rectBorder;
		int nLineStyle=pDoc->GetLineStyle();

		if(nBorderStyle&ID_BORDER_TOP)
		{
			rectBorder=m_rectWholeSquare;
			rectBorder.bottom=rectBorder.top;
			DrawBorder(pDC,rectBorder,ID_BORDER_TOP,nLineStyle);
		}
		if(nBorderStyle&ID_BORDER_BOTTOM)
		{
			rectBorder=m_rectWholeSquare;
			rectBorder.top=rectBorder.bottom;
			if(nBorderStyle&ID_BORDER_RIGHT)
			{
				rectBorder.right++;
			}
			DrawBorder(pDC,rectBorder,ID_BORDER_BOTTOM,nLineStyle);
		}
		if(nBorderStyle&ID_BORDER_LEFT)
		{
			rectBorder=m_rectWholeSquare;
			rectBorder.right=rectBorder.left;
			DrawBorder(pDC,rectBorder,ID_BORDER_LEFT,nLineStyle);
		}
		if(nBorderStyle&ID_BORDER_RIGHT)
		{
			rectBorder=m_rectWholeSquare;
			rectBorder.left=rectBorder.right;
			if(nBorderStyle&ID_BORDER_BOTTOM)
			{
				rectBorder.bottom++;
			}
			DrawBorder(pDC,rectBorder,ID_BORDER_RIGHT,nLineStyle);
		}
		if(nBorderStyle&ID_BORDER_HORZ_INSIDE)
		{
			rectBorder=m_rectWholeSquare;
			rectBorder.bottom=rectBorder.top+rectBorder.Height()/2;
			rectBorder.top=rectBorder.bottom;
			DrawBorder(pDC,rectBorder,ID_BORDER_HORZ_INSIDE,nLineStyle);
		}
		if(nBorderStyle&ID_BORDER_VERT_INSIDE)
		{
			rectBorder=m_rectWholeSquare;
			rectBorder.right=rectBorder.left+rectBorder.Width()/2;
			rectBorder.left=rectBorder.right;
			DrawBorder(pDC,rectBorder,ID_BORDER_VERT_INSIDE,nLineStyle);
		}
	}

	// draw text
	pDC->SetTextColor(pDoc->GetTextColor());

	pDC->DrawText(_T("First Quarter"),m_rectFirstSquare,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pDC->DrawText(_T("Second Quarter"),m_rectSecondSquare,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pDC->DrawText(_T("Third Quarter"),m_rectThirdSquare,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pDC->DrawText(_T("Fourth Quarter"),m_rectFourthSquare,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

/////////////////////////////////////////////////////////////////////////////
// CPopupBarView printing

BOOL CPopupBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPopupBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPopupBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPopupBarView diagnostics

#ifdef _DEBUG
void CPopupBarView::AssertValid() const
{
	CView::AssertValid();
}

void CPopupBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPopupBarDoc* CPopupBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPopupBarDoc)));
	return (CPopupBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPopupBarView message handlers


void CPopupBarView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	ASSERT(pFrame);
	pFrame->GetCustomizeToolBar()->Invalidate();

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CPopupBarView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	CalculateRects();
}


void CPopupBarView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	CalculateRects();
}


void CPopupBarView::CalculateRects()
{
	GetClientRect(m_rectWholeSquare);

	m_rectWholeSquare.DeflateRect(ID_EDGE_MARGIN,ID_EDGE_MARGIN);

	m_rectFirstSquare=m_rectWholeSquare;
	m_rectFirstSquare.right=m_rectFirstSquare.left+m_rectWholeSquare.Width()/2;
	m_rectFirstSquare.bottom=m_rectFirstSquare.top+m_rectWholeSquare.Height()/2;

	m_rectSecondSquare=m_rectFirstSquare;
	m_rectSecondSquare.left=m_rectFirstSquare.right;
	m_rectSecondSquare.right=m_rectWholeSquare.right;

	m_rectThirdSquare=m_rectFirstSquare;
	m_rectThirdSquare.top=m_rectFirstSquare.bottom;
	m_rectThirdSquare.bottom=m_rectWholeSquare.bottom;

	m_rectFourthSquare=m_rectSecondSquare;
	m_rectFourthSquare.top=m_rectSecondSquare.bottom;
	m_rectFourthSquare.bottom=m_rectWholeSquare.bottom;

	m_textSize.cx=m_rectFirstSquare.Width()-2*ID_TEXT_MARGIN-
		ID_BORDER_MARGIN-ID_BORDER_MARGIN/2;
	m_textSize.cy=m_rectFirstSquare.Height()-2*ID_TEXT_MARGIN-
		ID_BORDER_MARGIN-ID_BORDER_MARGIN/2;
}

void CPopupBarView::DrawBorder(CDC* pDC, CRect rect, int nBorderStyle, int nLineStyle)
{
	pDC->MoveTo(rect.left,rect.top);
	switch(nLineStyle)
	{
	case ID_LINE_1PX:
		{
			switch(nBorderStyle)
			{
			case ID_BORDER_TOP:
			case ID_BORDER_BOTTOM:
			case ID_BORDER_HORZ_INSIDE:
				{
					pDC->LineTo(rect.right,rect.top);
					break;
				}
			case ID_BORDER_LEFT:
			case ID_BORDER_RIGHT:
			case ID_BORDER_VERT_INSIDE:
				{
					pDC->LineTo(rect.left,rect.bottom);
					break;
				}
			}
			break;
		}
	case ID_LINE_2PX:
		{
			switch(nBorderStyle)
			{
			case ID_BORDER_TOP:
			case ID_BORDER_HORZ_INSIDE:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					break;
				}
			case ID_BORDER_BOTTOM:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					break;
				}
			case ID_BORDER_LEFT:
			case ID_BORDER_VERT_INSIDE:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					break;
				}
			case ID_BORDER_RIGHT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					break;
				}
			}
			break;
		}
	case ID_LINE_3PX:
		{
			switch(nBorderStyle)
			{
			case ID_BORDER_TOP:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top+2);
					pDC->LineTo(rect.right,rect.top+2);
					break;
				}
			case ID_BORDER_BOTTOM:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					break;
				}
			case ID_BORDER_LEFT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left+2,rect.top);
					pDC->LineTo(rect.left+2,rect.bottom);
					break;
				}
			case ID_BORDER_RIGHT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					break;
				}
			case ID_BORDER_HORZ_INSIDE:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					break;
				}
			case ID_BORDER_VERT_INSIDE:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					break;
				}
			}
			break;
		}
	case ID_LINE_4PX:
		{
			switch(nBorderStyle)
			{
			case ID_BORDER_TOP:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top+2);
					pDC->LineTo(rect.right,rect.top+2);
					pDC->MoveTo(rect.left,rect.top+3);
					pDC->LineTo(rect.right,rect.top+3);
					break;
				}
			case ID_BORDER_BOTTOM:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					pDC->MoveTo(rect.left,rect.top-3);
					pDC->LineTo(rect.right,rect.top-3);
					break;
				}
			case ID_BORDER_LEFT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left+2,rect.top);
					pDC->LineTo(rect.left+2,rect.bottom);
					pDC->MoveTo(rect.left+3,rect.top);
					pDC->LineTo(rect.left+3,rect.bottom);
					break;
				}
			case ID_BORDER_RIGHT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					pDC->MoveTo(rect.left-3,rect.top);
					pDC->LineTo(rect.left-3,rect.bottom);
					break;
				}
			case ID_BORDER_HORZ_INSIDE:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					break;
				}
			case ID_BORDER_VERT_INSIDE:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					break;
				}
			}
			break;
		}
	case ID_LINE_6PX:
		{
			switch(nBorderStyle)
			{
			case ID_BORDER_TOP:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top+2);
					pDC->LineTo(rect.right,rect.top+2);
					pDC->MoveTo(rect.left,rect.top+3);
					pDC->LineTo(rect.right,rect.top+3);
					pDC->MoveTo(rect.left,rect.top+4);
					pDC->LineTo(rect.right,rect.top+4);
					pDC->MoveTo(rect.left,rect.top+5);
					pDC->LineTo(rect.right,rect.top+5);
					break;
				}
			case ID_BORDER_BOTTOM:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					pDC->MoveTo(rect.left,rect.top-3);
					pDC->LineTo(rect.right,rect.top-3);
					pDC->MoveTo(rect.left,rect.top-4);
					pDC->LineTo(rect.right,rect.top-4);
					pDC->MoveTo(rect.left,rect.top-5);
					pDC->LineTo(rect.right,rect.top-5);
					break;
				}
			case ID_BORDER_LEFT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left+2,rect.top);
					pDC->LineTo(rect.left+2,rect.bottom);
					pDC->MoveTo(rect.left+3,rect.top);
					pDC->LineTo(rect.left+3,rect.bottom);
					pDC->MoveTo(rect.left+4,rect.top);
					pDC->LineTo(rect.left+4,rect.bottom);
					pDC->MoveTo(rect.left+5,rect.top);
					pDC->LineTo(rect.left+5,rect.bottom);
					break;
				}
			case ID_BORDER_RIGHT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					pDC->MoveTo(rect.left-3,rect.top);
					pDC->LineTo(rect.left-3,rect.bottom);
					pDC->MoveTo(rect.left-4,rect.top);
					pDC->LineTo(rect.left-4,rect.bottom);
					pDC->MoveTo(rect.left-5,rect.top);
					pDC->LineTo(rect.left-5,rect.bottom);
					break;
				}
			case ID_BORDER_HORZ_INSIDE:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					pDC->MoveTo(rect.left,rect.top+2);
					pDC->LineTo(rect.right,rect.top+2);
					pDC->MoveTo(rect.left,rect.top-3);
					pDC->LineTo(rect.right,rect.top-3);
					break;
				}
			case ID_BORDER_VERT_INSIDE:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					pDC->MoveTo(rect.left+2,rect.top);
					pDC->LineTo(rect.left+2,rect.bottom);
					pDC->MoveTo(rect.left-3,rect.top);
					pDC->LineTo(rect.left-3,rect.bottom);
					break;
				}
			}
			break;
		}
	case ID_LINE_3PX_2LINES:
		{
			switch(nBorderStyle)
			{
			case ID_BORDER_TOP:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+2);
					pDC->LineTo(rect.right,rect.top+2);
					break;
				}
			case ID_BORDER_BOTTOM:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					break;
				}
			case ID_BORDER_LEFT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+2,rect.top);
					pDC->LineTo(rect.left+2,rect.bottom);
					break;
				}
			case ID_BORDER_RIGHT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					break;
				}
			case ID_BORDER_HORZ_INSIDE:
				{
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					break;
				}
			case ID_BORDER_VERT_INSIDE:
				{
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					break;
				}
			}
			break;
		}
	case ID_LINE_4PX_2LINES:
		{
			switch(nBorderStyle)
			{
			case ID_BORDER_TOP:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+2);
					pDC->LineTo(rect.right,rect.top+2);
					pDC->MoveTo(rect.left,rect.top+3);
					pDC->LineTo(rect.right,rect.top+3);
					break;
				}
			case ID_BORDER_BOTTOM:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					pDC->MoveTo(rect.left,rect.top-3);
					pDC->LineTo(rect.right,rect.top-3);
					break;
				}
			case ID_BORDER_LEFT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+2,rect.top);
					pDC->LineTo(rect.left+2,rect.bottom);
					pDC->MoveTo(rect.left+3,rect.top);
					pDC->LineTo(rect.left+3,rect.bottom);
					break;
				}
			case ID_BORDER_RIGHT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					pDC->MoveTo(rect.left-3,rect.top);
					pDC->LineTo(rect.left-3,rect.bottom);
					break;
				}
			case ID_BORDER_HORZ_INSIDE:
				{
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					break;
				}
			case ID_BORDER_VERT_INSIDE:
				{
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					break;
				}
			}
			break;
		}
	case ID_LINE_4PX_2LINES_REVERSE:
		{
			switch(nBorderStyle)
			{
			case ID_BORDER_TOP:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top+3);
					pDC->LineTo(rect.right,rect.top+3);
					break;
				}
			case ID_BORDER_BOTTOM:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					pDC->MoveTo(rect.left,rect.top-3);
					pDC->LineTo(rect.right,rect.top-3);
					break;
				}
			case ID_BORDER_LEFT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left+3,rect.top);
					pDC->LineTo(rect.left+3,rect.bottom);
					break;
				}
			case ID_BORDER_RIGHT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					pDC->MoveTo(rect.left-3,rect.top);
					pDC->LineTo(rect.left-3,rect.bottom);
					break;
				}
			case ID_BORDER_HORZ_INSIDE:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					break;
				}
			case ID_BORDER_VERT_INSIDE:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					break;
				}
			}
			break;
		}
	case ID_LINE_7PX_3LINES:
		{
			switch(nBorderStyle)
			{
			case ID_BORDER_TOP:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top+1);
					pDC->LineTo(rect.right,rect.top+1);
					pDC->MoveTo(rect.left,rect.top+3);
					pDC->LineTo(rect.right,rect.top+3);
					pDC->MoveTo(rect.left,rect.top+5);
					pDC->LineTo(rect.right,rect.top+5);
					pDC->MoveTo(rect.left,rect.top+6);
					pDC->LineTo(rect.right,rect.top+6);
					break;
				}
			case ID_BORDER_BOTTOM:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top-1);
					pDC->LineTo(rect.right,rect.top-1);
					pDC->MoveTo(rect.left,rect.top-3);
					pDC->LineTo(rect.right,rect.top-3);
					pDC->MoveTo(rect.left,rect.top-5);
					pDC->LineTo(rect.right,rect.top-5);
					pDC->MoveTo(rect.left,rect.top-6);
					pDC->LineTo(rect.right,rect.top-6);
					break;
				}
			case ID_BORDER_LEFT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left+1,rect.top);
					pDC->LineTo(rect.left+1,rect.bottom);
					pDC->MoveTo(rect.left+3,rect.top);
					pDC->LineTo(rect.left+3,rect.bottom);
					pDC->MoveTo(rect.left+5,rect.top);
					pDC->LineTo(rect.left+5,rect.bottom);
					pDC->MoveTo(rect.left+6,rect.top);
					pDC->LineTo(rect.left+6,rect.bottom);
					break;
				}
			case ID_BORDER_RIGHT:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left-1,rect.top);
					pDC->LineTo(rect.left-1,rect.bottom);
					pDC->MoveTo(rect.left-3,rect.top);
					pDC->LineTo(rect.left-3,rect.bottom);
					pDC->MoveTo(rect.left-5,rect.top);
					pDC->LineTo(rect.left-5,rect.bottom);
					pDC->MoveTo(rect.left-6,rect.top);
					pDC->LineTo(rect.left-6,rect.bottom);
					break;
				}
			case ID_BORDER_HORZ_INSIDE:
				{
					pDC->LineTo(rect.right,rect.top);
					pDC->MoveTo(rect.left,rect.top-2);
					pDC->LineTo(rect.right,rect.top-2);
					pDC->MoveTo(rect.left,rect.top+2);
					pDC->LineTo(rect.right,rect.top+2);
					pDC->MoveTo(rect.left,rect.top-3);
					pDC->LineTo(rect.right,rect.top-3);
					pDC->MoveTo(rect.left,rect.top+3);
					pDC->LineTo(rect.right,rect.top+3);
					break;
				}
			case ID_BORDER_VERT_INSIDE:
				{
					pDC->LineTo(rect.left,rect.bottom);
					pDC->MoveTo(rect.left-2,rect.top);
					pDC->LineTo(rect.left-2,rect.bottom);
					pDC->MoveTo(rect.left+2,rect.top);
					pDC->LineTo(rect.left+2,rect.bottom);
					pDC->MoveTo(rect.left-3,rect.top);
					pDC->LineTo(rect.left-3,rect.bottom);
					pDC->MoveTo(rect.left+3,rect.top);
					pDC->LineTo(rect.left+3,rect.bottom);
					break;
				}
			}
			break;
		}
	default:
		ASSERT(FALSE);
	}
}
