// TriangleButton.cpp : implementation file
//

#include "stdafx.h"
#include "math.h"
#include "TriangleButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTriangleButton

CTriangleButton::CTriangleButton()
{
	PointDirection = POINT_RIGHT;
}

CTriangleButton::~CTriangleButton()
{
}

BEGIN_MESSAGE_MAP(CTriangleButton, CButton)
	//{{AFX_MSG_MAP(CRoundButton)
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CTriangleButton::SetDirection(POINTDIRECTION Direction)
{
	PointDirection = Direction;
	PreSubclassWindow();
}

CTriangleButton::POINTDIRECTION CTriangleButton::GetDirection()
{
	return PointDirection;
}



BOOL CTriangleButton::SetWindowPos(const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags)
{
	//Size must be dividable by two (else triangle will look strange when drawn)
	cx -= cx % 2; cy -= cy % 2;
	//TRACE("x=%i   y=%i\n", cx, cy);
	return CButton::SetWindowPos(pWndInsertAfter, x, y, cx, cy, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CRoundButton message handlers

void CTriangleButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();

	//get client rectangle
	CRect rect;
	GetClientRect(rect);
	rect.bottom = rect.right = min(rect.bottom,rect.right);	//make it square
	rect.bottom -= rect.bottom % 2; rect.right -= rect.right % 2;

	SetWindowPos(NULL, 0, 0, rect.right, rect.bottom, SWP_NOMOVE | SWP_NOZORDER);

	CPoint Head, RightLeg, LeftLeg;

	switch (PointDirection) {
		case POINT_UP :
			Head.x = rect.right / 2; Head.y = 0;
			RightLeg.x = rect.right; RightLeg.y = rect.bottom;
			LeftLeg.x = 0; LeftLeg.y = rect.bottom;
			break;
		case POINT_DOWN :
			Head.x = rect.right / 2; Head.y = rect.bottom;
			RightLeg.x = 0; RightLeg.y = 0;
			LeftLeg.x = rect.right; LeftLeg.y = 0;
			break;
		case POINT_LEFT :
			Head.x = 0; Head.y = rect.bottom / 2;
			RightLeg.x = rect.right; RightLeg.y = 0;
			LeftLeg.x = rect.right; LeftLeg.y = rect.bottom;
			break;
		case POINT_RIGHT :
			Head.x = rect.right; Head.y = rect.bottom / 2;
			RightLeg.x = 0; RightLeg.y = rect.bottom;
			LeftLeg.x = 0; LeftLeg.y = 0;
			break;
		default :
			ASSERT(FALSE);
	}//switch
							
	CPoint points[3];
	points[0] = Head; points[1] = RightLeg; points[2] = LeftLeg;
	
	SetWindowRgn(NULL, FALSE);

	CurrentRegion.DeleteObject();
	CurrentRegion.CreatePolygonRgn(points, 3, ALTERNATE);

	SetWindowRgn(CurrentRegion, TRUE);
		
	ModifyStyle(0, BS_OWNERDRAW);
}


void CTriangleButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct != NULL);
	CRect rect = lpDrawItemStruct->rcItem;
	CDC* pDC   = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT state = lpDrawItemStruct->itemState;
	UINT nStyle = GetStyle();

	int nSavedDC = pDC->SaveDC();

	//make the rect a square
	rect.bottom = rect.right = min(rect.bottom, rect.right);
	pDC->FillSolidRect(rect, ::GetSysColor(COLOR_BTNFACE));
	
	rect.right -= 1; rect.bottom -= 1;	//avoid drawing outside area

	//make some pens
	CPen HighlightPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DHIGHLIGHT));
	CPen DarkShadowPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DDKSHADOW));
	CPen ShadowPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
	CPen BlackPen(PS_SOLID, 1, RGB(0,0,0));
	//NOTE: If U use this class for NT apps only, use the implementation of FocusPen below 
	//			instead, as WIN95 doesn't support this yet (though the doc says **dang ms-fools**)
	//			(WIN98 might also support this)
	//LOGBRUSH logbrush; logbrush.lbStyle = BS_SOLID; logbrush.lbColor = RGB(0,0,0); logbrush.lbHatch = NULL;
	//CPen FocusPen(PS_COSMETIC | PS_ALTERNATE, 1, &logbrush);
	CPen FocusPen(PS_DOT, 0, RGB(0,0,0));
 	

	//Draw button
	switch (PointDirection) {
		case POINT_UP : {
			//Draw the raised/sunken edges of the button (unless flat)
			if (nStyle & BS_FLAT) {					//style is flat
				pDC->SelectObject(BlackPen);
				pDC->MoveTo(rect.right / 2, 0);
				pDC->LineTo(0, rect.bottom);
				pDC->LineTo(rect.right, rect.bottom);
				pDC->LineTo(rect.right / 2, 0);
				pDC->SelectObject(HighlightPen);
				pDC->MoveTo(rect.right / 2, 2);
				pDC->LineTo(2, rect.bottom - 1);
				pDC->LineTo(rect.right - 2, rect.bottom - 1);
				pDC->LineTo(rect.right / 2, 2);
			}	else {												//style not flat
				if ((state & ODS_SELECTED))	{	//Button is down	
					pDC->SelectObject(HighlightPen);
					pDC->MoveTo(0, rect.bottom);
					pDC->LineTo(rect.right - 1, rect.bottom);
					pDC->LineTo(rect.right / 2, 0);

					pDC->SelectObject(ShadowPen);
					pDC->LineTo(0, rect.bottom);			
					
					pDC->SelectObject(DarkShadowPen);
					pDC->MoveTo(rect.right / 2 - 1, 4);
					pDC->LineTo(1, rect.bottom);
				} else {											//Button is not down
					pDC->SelectObject(HighlightPen);
					pDC->MoveTo(rect.right /2, 0);
					pDC->LineTo(0, rect.bottom - 1);
					
					pDC->SelectObject(ShadowPen);
					pDC->LineTo(rect.right - 1, rect.bottom - 1);
					pDC->LineTo(rect.right / 2, 0);

					pDC->SelectObject(DarkShadowPen);
					pDC->MoveTo(rect.right / 2 + 2, 3);
					pDC->LineTo(rect.right + 1, rect.bottom + 1);
					
					pDC->MoveTo(rect.right - 1, rect.bottom);
					pDC->LineTo(1, rect.bottom);
				}//else|if
			}//else|if	
			break;
		}//case
	
		case POINT_DOWN : {
			//Draw the raised/sunken edges of the button (unless flat)
			if (nStyle & BS_FLAT) {					//style is flat
				pDC->SelectObject(BlackPen);
				pDC->MoveTo(rect.right / 2, rect.bottom);
				pDC->LineTo(0, 0);
				pDC->LineTo(rect.right, 0);
				pDC->LineTo(rect.right / 2, rect.bottom);
				
				pDC->SelectObject(HighlightPen);
				pDC->MoveTo(rect.right / 2, rect.bottom - 2);
				pDC->LineTo(2, 1);
				pDC->LineTo(rect.right - 2, 1);
				pDC->LineTo(rect.right / 2, rect.bottom - 2);
			}	else {												//style not flat
				if ((state & ODS_SELECTED))	{	//Button is down	
					pDC->SelectObject(ShadowPen);
					pDC->MoveTo(rect.right, 1);
					pDC->LineTo(1, 1);
					pDC->LineTo(rect.right / 2, rect.bottom - 1);
					
					pDC->SelectObject(BlackPen);
					pDC->MoveTo(rect.right - 2, 2);
					pDC->LineTo(1, 2);
					
					pDC->SelectObject(HighlightPen);
					pDC->MoveTo(rect.right + 1, 0);
					pDC->LineTo(rect.right / 2 + 1, rect.bottom + 1);

				} else {											//Button is not down
					pDC->SelectObject(ShadowPen);
					pDC->MoveTo(0, 0);
					pDC->LineTo(rect.right / 2, rect.bottom);
					pDC->LineTo(rect.right, 0);
					pDC->MoveTo(1, 1);
					pDC->LineTo(rect.right / 2 + 1, rect.bottom);
					
					pDC->SelectObject(DarkShadowPen);
					pDC->MoveTo(rect.right, 2);
					pDC->LineTo(rect.right / 2 + 1, rect.bottom + 1);
					
					pDC->SelectObject(HighlightPen);
					pDC->MoveTo(0, 0);
					pDC->LineTo(rect.right, 0);
				
				}
			}//else|if
			break;
		}//case

		case POINT_LEFT : {
			if (nStyle & BS_FLAT) {					//style is flat
				pDC->SelectObject(BlackPen);
				pDC->MoveTo(rect.right, 0);
				pDC->LineTo(0, rect.bottom / 2);
				pDC->LineTo(rect.right, rect.bottom);
				pDC->LineTo(rect.right, 0);
				
				pDC->SelectObject(HighlightPen);
				pDC->MoveTo(rect.right - 1, 2);
				pDC->LineTo(3, rect.bottom / 2);
				pDC->LineTo(rect.right - 1, rect.bottom - 2);
				pDC->LineTo(rect.right - 1, 2);
			}	else {												//style not flat
				if ((state & ODS_SELECTED))	{	//Button is down	
					pDC->SelectObject(ShadowPen);
					pDC->MoveTo(rect.right, 0);
					pDC->LineTo(0, rect.bottom / 2);

					pDC->SelectObject(DarkShadowPen);
					pDC->MoveTo(rect.right, 1);
					pDC->LineTo(2, rect.bottom / 2);
					
					pDC->SelectObject(HighlightPen);
					pDC->MoveTo(rect.right, 0);
					pDC->LineTo(rect.right, rect.bottom);
					pDC->LineTo(0, rect.bottom / 2);
				} else {											//Button is not down
					pDC->SelectObject(ShadowPen);
					pDC->MoveTo(rect.right - 1, 0);
					pDC->LineTo(rect.right - 1, rect.bottom - 1);
					pDC->LineTo(0, rect.bottom / 2);
					pDC->MoveTo(1, rect.bottom / 2 + 1);
					pDC->LineTo(6, rect.bottom / 2 + 4);

					pDC->SelectObject(DarkShadowPen);
					pDC->MoveTo(rect.right, 1);
					pDC->LineTo(rect.right, rect.bottom);
					pDC->LineTo(2, rect.bottom / 2 + 2);
					
					pDC->SelectObject(HighlightPen);
					pDC->MoveTo(0, rect.bottom / 2);
					pDC->LineTo(rect.right, 0);
				}
			}//else|if
			break;
		}//case

		case POINT_RIGHT : {
			if (nStyle & BS_FLAT) {					//style is flat
				pDC->SelectObject(BlackPen);
				pDC->MoveTo(0, 0);
				pDC->LineTo(rect.right, rect.bottom / 2);
				pDC->LineTo(0, rect.bottom);
				pDC->LineTo(0, 0);
				
				pDC->SelectObject(HighlightPen);
				pDC->MoveTo(1, 2);
				pDC->LineTo(rect.right - 2, rect.bottom / 2);
				pDC->LineTo(1, rect.bottom - 2);
				pDC->LineTo(1, 2);
			}	else {												//style not flat
				if ((state & ODS_SELECTED))	{	//Button is down	
					pDC->SelectObject(ShadowPen);
					pDC->MoveTo(0, rect.bottom);
					pDC->LineTo(0, 0);
					pDC->LineTo(rect.right, rect.bottom / 2);

					pDC->SelectObject(DarkShadowPen);
					pDC->MoveTo(1, rect.bottom - 2);
					pDC->LineTo(1, 1);
					pDC->MoveTo(rect.right - 3, rect.bottom / 2);
					pDC->LineTo(0, 1);
					
					pDC->SelectObject(HighlightPen);
					pDC->MoveTo(0, rect.bottom);
					pDC->LineTo(rect.right, rect.bottom / 2);
					
				} else {											//Button is not down
					pDC->SelectObject(ShadowPen);
					pDC->MoveTo(0, rect.bottom);
					pDC->LineTo(rect.right, rect.bottom / 2);

					pDC->SelectObject(DarkShadowPen);
					pDC->MoveTo(0, rect.bottom + 1);
					pDC->LineTo(rect.right, rect.bottom / 2 + 1);
					
					pDC->SelectObject(HighlightPen);
					pDC->MoveTo(0, rect.bottom);
					pDC->LineTo(0, 0);
					pDC->LineTo(rect.right, rect.bottom / 2);
				}
			}//else|if

			break;
		}//case

		default :
			ASSERT(FALSE);
	}//switch


	//Draw text	if any
	CString strText;
	GetWindowText(strText);
	if (!strText.IsEmpty()) {
		CSize TextExtent = pDC->GetTextExtent(strText);
		CPoint TextPos;
		pDC->SetBkMode(TRANSPARENT);

		switch (PointDirection) {
			case POINT_UP : {
				TextPos = CPoint((int)(rect.right / 2.0 - TextExtent.cx / 2.0),
											 rect.bottom - (int)(rect.bottom / 5.0 + TextExtent.cy));

				int iXLimit = (int)((rect.bottom / 5.0 + TextExtent.cy) * 4.0 / 7.0);

				CRgn rgn; rgn.CreateRectRgn(iXLimit, TextPos.y, rect.right - iXLimit, rect.bottom - 2);
				pDC->SelectClipRgn(&rgn);
				
				break;
			}//case
			case POINT_DOWN : {
				TextPos = CPoint((int)(rect.right / 2.0 - TextExtent.cx / 2.0),
											 (int)(rect.bottom / 5.0));

				int iXLimit = (int)((rect.bottom / 5.0 + TextExtent.cy) * 4.0 / 7.0);

				CRgn rgn; rgn.CreateRectRgn(iXLimit, (int)(rect.bottom / 5.0), rect.right - iXLimit, (int)(rect.bottom / 5.0) + TextExtent.cy + 2);
				pDC->SelectClipRgn(&rgn);
				
				break;
			}
			
			case POINT_LEFT : {
				TextPos = CPoint((int)((rect.right / 2.0 - TextExtent.cx / 2.0) + (rect.right / 8.0)),
											   (int)(rect.bottom / 2.0 - TextExtent.cy / 2.0) );

				int iXLimitLeft = (int)(TextExtent.cy / 2.0 * 7.0 / 4.0) + 4;
				int iXLimitRight = rect.right - 4;
			
				CRgn rgn; rgn.CreateRectRgn(iXLimitLeft, (int)(rect.bottom / 2.0 - TextExtent.cy / 2.0),
																		iXLimitRight, (int)(rect.bottom / 2.0 + TextExtent.cy / 2.0) );
				pDC->SelectClipRgn(&rgn);

				break;
			}//case

			case POINT_RIGHT : {
				TextPos = CPoint((int)((rect.right / 2.0 - TextExtent.cx / 2.0) - (rect.right / 8.0)),
											   (int)(rect.bottom / 2.0 - TextExtent.cy / 2.0) );

				int iXLimitLeft = 4;
				int iXLimitRight = rect.right - (int)(TextExtent.cy / 2.0 * 7.0 / 4.0) - 4;
					
				CRgn rgn; rgn.CreateRectRgn(iXLimitLeft, (int)(rect.bottom / 2.0 - TextExtent.cy / 2.0),
																		iXLimitRight, (int)(rect.bottom / 2.0 + TextExtent.cy / 2.0) );
				pDC->SelectClipRgn(&rgn);

				break;
			}//case

			default :
				ASSERT(FALSE);
		}//switch

		//common for all directions
		if (state & ODS_SELECTED) TextPos.Offset(1,1);

		if (state & ODS_DISABLED) {
			pDC->DrawState(TextPos, TextExtent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		} else {
			pDC->TextOut(TextPos.x, TextPos.y, strText);
		}

	}//if			


	//Draw the focus triangle on the inside of the button if we have focus
	if ((state & ODS_FOCUS)) {
		CRgn rgn; rgn.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
		pDC->SelectClipRgn(&rgn);
		pDC->SelectObject(FocusPen);
		switch (PointDirection) {
			case POINT_UP : {
				pDC->MoveTo(rect.right / 2, 12);
				pDC->LineTo(9, rect.bottom - 6);
				pDC->LineTo(rect.right - 9, rect.bottom - 6);
				pDC->LineTo(rect.right / 2, 12);
				break;
			}
			case POINT_DOWN : {
				pDC->MoveTo(rect.right / 2 + 1, rect.bottom - 13);
				pDC->LineTo(10, 6);
				pDC->LineTo(rect.right - 9, 6);
				pDC->LineTo(rect.right / 2 + 1, rect.bottom - 13);
				break;
			}
			case POINT_LEFT : {
				pDC->MoveTo(12, rect.bottom / 2);
				pDC->LineTo(rect.right - 6, 9);
				pDC->LineTo(rect.right - 6, rect.bottom - 9);
				pDC->LineTo(12, rect.bottom / 2);
				break;
			}//case
			case POINT_RIGHT : {
				pDC->MoveTo(6, 9);
				pDC->LineTo(rect.right - 12, rect.bottom / 2);
				pDC->LineTo(6, rect.bottom - 9);
				pDC->LineTo(6, 9);
				break;
			}//case

			default :
				ASSERT(FALSE);
		}//switch
	}//if

	pDC->RestoreDC(nSavedDC);

}

/*  I'm not sure what this function is supposed to do, but it was in the
CRoundButton class i used to make this class, so I have implemented it, though
I don't know what the function should do ! (if it is nescessary just remove comments) 
UINT CTriangleButton::OnNcHitTest(CPoint point) 
{
	ScreenToClient(&point);
	if (CurrentRegion.PtInRegion(point)) {
		//TRACE("HTCLIENT: %i, %i\n", point.x, point.y);
		return HTCLIENT;
	}
	else {
		//TRACE("HTNOWHERE: %i, %i\n", point.x, point.y);
		return HTNOWHERE;
	}
}
*/


