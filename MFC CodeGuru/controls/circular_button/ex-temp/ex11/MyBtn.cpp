// MyBtn.cpp : implementation file
//

#include "stdafx.h"
#include "MyBtn.h"

#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBtn

CMyBtn::CMyBtn()
{
}

CMyBtn::~CMyBtn()
{
}


BEGIN_MESSAGE_MAP(CMyBtn, CButton)
	//{{AFX_MSG_MAP(CMyBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyBtn message handlers

void CMyBtn::SetRound(void)
{
	HRGN rgn;
	CRect wrect;
	GetClientRect(&wrect);
    SetWindowRgn( NULL, FALSE );
	rgn = CreateEllipticRgn( wrect.left, wrect.top,
								wrect.right, wrect.bottom );

	SetWindowRgn(rgn, TRUE);	
}

void CMyBtn::GradientFill (CDC* pDC, CRect* pRect)
{
    CBrush* pBrush[64];

    for (int i=0; i<64; i++) 
	{
		pBrush[i] = new CBrush (RGB (0, 0, 255 - (i * 4)));
    }

    int nWidth = pRect->Width ();
    int nHeight = pRect->Height ();
    CRect rect;

    for (i=0; i<nHeight; i++) 
	{
        rect.SetRect (0, i, nWidth, i + 1);
        pDC->FillRect (&rect, pBrush[(i * 63) / nHeight]);
    }

    for (i=0; i<64; i++)
        delete pBrush[i];
}

void CMyBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CRect Rect = lpDrawItemStruct->rcItem;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRgn rgn;
	CRect rect;

	rect = Rect;

	UINT state = lpDrawItemStruct->itemState;

	CMemDC	*pMemDC = new CMemDC( pDC, Rect);
	CBrush hbr;
	hbr.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
	//pDC->FillRect( &Rect, &hbr);
	pMemDC->FillRect( &Rect, &hbr);
	hbr.DeleteObject();
	
	if( !(state & ODS_DISABLED) )
	{
		if (state & ODS_SELECTED)
		{
			CPen pen( PS_SOLID, 2, GetSysColor( COLOR_3DHILIGHT ) );
			CPen *pPen;
			CPoint start, end;

			start.x = rect.left;
			start.y = rect.bottom;		
			end.x = rect.right;
			end.y = rect.top;

			rect.left += 2;
			rect.top += 2;
			rect.right -= 2;
			rect.bottom -= 2;

			pPen = pMemDC->SelectObject( &pen );
			pMemDC->Arc( &rect, start, end );
			pMemDC->SelectObject( pPen );
			pen.DeleteObject();
		}
	}

	rgn.CreateEllipticRgn( rect.left, rect.top, 
							rect.right, rect.bottom );
	
	pMemDC->SelectClipRgn( &rgn );	
	GradientFill( pMemDC, &Rect );

	SetRound();

	CString title;
	GetWindowText( title );
	if( title.GetLength() != 0 )
	{
		DrawWhiteText( pMemDC, &Rect, title );
		title.ReleaseBuffer();
	}

	delete pMemDC;
}

void CMyBtn::DrawWhiteText(CDC* pDC, CRect* pRect, CString& text )
{
    CFont font;
    int nHeight = -16;

    font.CreateFont (nHeight, 0, 0, 0, FW_BOLD,
        TRUE, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
        CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
        FF_DONTCARE, "Times New Roman");

    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(RGB (255, 255, 255));

    CFont* pOldFont = pDC->SelectObject (&font);
    pDC->DrawText (text, -1, pRect, DT_SINGLELINE | DT_CENTER |
					    DT_VCENTER);

    pDC->SelectObject (pOldFont);
}
