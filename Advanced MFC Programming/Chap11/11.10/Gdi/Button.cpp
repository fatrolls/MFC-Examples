#include "stdafx.h"
#include "GDI.h"
#include "Button.h"
#include "MainFrm.h"
#include "GDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CColorButton::CColorButton()
{
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CGDIDoc *pDoc;
	CDC *pDC;
	CPalette *pPal;
	CPalette *pPalOld;
	
	pDoc=(CGDIDoc *)((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	if(pDoc == NULL)return;
	pPal=pDoc->GetPalette();
	if(pPal->GetSafeHandle() == NULL)return;
	else
	{
		pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
		pPalOld=pDC->SelectPalette(pPal, FALSE);
		pDC->RealizePalette();
		pDC->FillSolidRect
		(
			&lpDrawItemStruct->rcItem,
			PALETTEINDEX(m_nPalIndex)
		);
		pDC->SelectPalette(pPalOld, FALSE);
	}
}

CFBButton::CFBButton()
{
}

CFBButton::~CFBButton()
{
}

BEGIN_MESSAGE_MAP(CFBButton, CButton)
	//{{AFX_MSG_MAP(CFBButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CFBButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CGDIDoc *pDoc;
	CDC *pDC;
	CPalette *pPal;
	CPalette *pPalOld;
	CBrush brush;
	CBrush *pBrOld;
	int nFgdIndex;
	int nBgdIndex;
	CRect rect;
	
	pDoc=(CGDIDoc *)((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument();
	if(pDoc == NULL)return;
	pPal=pDoc->GetPalette();
	if(pPal->GetSafeHandle() == NULL)return;
	else
	{
		nFgdIndex=pDoc->GetFgdIndex();
		nBgdIndex=pDoc->GetBgdIndex();
		pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
		pPalOld=pDC->SelectPalette(pPal, FALSE);
		pDC->RealizePalette();

		brush.CreateSolidBrush(PALETTEINDEX(nBgdIndex));
		rect=lpDrawItemStruct->rcItem;
		rect.InflateRect(-2, -2);
		rect.left+=rect.Width()/4;
		rect.top+=rect.Height()/4;
		pBrOld=pDC->SelectObject(&brush);
		pDC->Rectangle(rect);
		pDC->DrawEdge(rect, EDGE_SUNKEN, BF_RECT);
		pDC->SelectObject(pBrOld);

		brush.DeleteObject();

		brush.CreateSolidBrush(PALETTEINDEX(nFgdIndex));
		rect=lpDrawItemStruct->rcItem;
		rect.InflateRect(-2, -2);
		rect.right-=rect.Width()/4;
		rect.bottom-=rect.Height()/4;
		pBrOld=pDC->SelectObject(&brush);
		pDC->Rectangle(rect);
		pDC->DrawEdge(rect, EDGE_SUNKEN, BF_RECT);
		pDC->SelectObject(pBrOld);

		pDC->SelectPalette(pPalOld, FALSE);
	}
}
