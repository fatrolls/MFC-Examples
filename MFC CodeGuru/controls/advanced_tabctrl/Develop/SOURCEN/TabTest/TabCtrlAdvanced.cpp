// TabCtrlAdvanced.cpp : implementation file
//

#include "stdafx.h"
#include "TabTest.h"
#include "TabCtrlAdvanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabItemInfo
IMPLEMENT_DYNCREATE(CTabItemInfo, CObject)

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlAdvanced

CTabCtrlAdvanced::CTabCtrlAdvanced()
{
}

CTabCtrlAdvanced::~CTabCtrlAdvanced()
{
}


BEGIN_MESSAGE_MAP(CTabCtrlAdvanced, CTabCtrl)
	//{{AFX_MSG_MAP(CTabCtrlAdvanced)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlAdvanced message handlers

int CTabCtrlAdvanced::GetItemRow(int nItem)
{
	CRect rcItem;
	GetItemRect(nItem,&rcItem);
	return GetItemRow(rcItem);
}
int CTabCtrlAdvanced::GetItemRow(LPRECT pItemRec)
{
	int Row = ( pItemRec->top / (pItemRec->bottom - pItemRec->top) ) + 1;
	return GetRowCount() - Row;
}

void CTabCtrlAdvanced::GetDisplayRect( LPRECT lpRect )
// --- Returns the Rectangle of the Display-Area
{
	// --- this returns nearly(!!) the right size
	GetClientRect (lpRect);
	// --- adjust it to the TabCtrl position and size
	AdjustRect(FALSE,lpRect);	

	
	// --- Now we want to keep a little Border
	lpRect -> top	+= 2;
	lpRect -> left	 = 2;
	lpRect -> right += 2;
	lpRect -> bottom+= 2;
}

BOOL CTabCtrlAdvanced::getItemRgn( int nItem, CRgn& outerRgn, CRgn& innerRgn )
{
	CRect rcItem;
	if ( GetItemRect( nItem, rcItem ) )
	{
		if ( nItem == GetCurSel() )
			rcItem .InflateRect(2,2);
		
		CRgn round1Out, round1In;
		
		if(outerRgn.m_hObject)
			outerRgn .DeleteObject();
		if(innerRgn.m_hObject)
			innerRgn .DeleteObject();
		
		outerRgn.CreateRoundRectRgn( rcItem .left,
									   rcItem .top,
									   rcItem .right,
									   rcItem .bottom + rcItem.Height(),
									   32,
									   32);
						
		innerRgn .CreateRoundRectRgn( rcItem .left+2,
									  rcItem .top+2,
									  rcItem .right-2,
									  rcItem .bottom-2+ rcItem.Height(),
									  32,
									  32);
	}
	else
		return FALSE;

	return TRUE;
}

BOOL CTabCtrlAdvanced::OnEraseBkgnd(CDC* pDC) 
{
	// --- Get the current Clipping Region
	CRgn* pRgnOrgClip;
	HRGN hrgnOrgClip;
	::GetClipRgn( pDC->GetSafeHdc(), hrgnOrgClip );
	pRgnOrgClip = CRgn::FromHandle( hrgnOrgClip );

	// --- Clip out the Item Region
	CRgn rgnOut;
	CRgn rgnIn;
	CRgn result;
	result. CreateRectRgn( 0, 0, 1, 1 );
	// Create a Region with all Items
	for( int ix = 0; ix < GetItemCount(); ix++ )
	{
		getItemRgn( ix, rgnOut, rgnIn );
		result. CombineRgn( &result, &rgnOut, RGN_OR );
		rgnOut. DeleteObject();
		rgnIn.  DeleteObject();
	}
	CRect rcClient;
	GetClientRect(rcClient);
	CRgn clip;
	clip. CreateRectRgnIndirect(rcClient);
	// The Reverse Region is our Clipping Region
	clip. CombineRgn(&clip, &result, RGN_XOR);
	pDC-> SelectClipRgn(&clip);
	result. DeleteObject();
	clip.   DeleteObject();

	// --- Fill the Display Area
	CRect rcDisplay;
	GetDisplayRect(rcDisplay);
	// inflate by Display Border size
	rcDisplay. InflateRect(2,2);
	CRgn rgnDisplay;
	rgnDisplay. CreateRectRgnIndirect( rcDisplay );

	// --- Clip out the Display Region
	pDC-> SelectClipRgn( &rgnDisplay, RGN_DIFF );

	// --- Fill the remaining Region with the Background Brush
	CRgn rgnBkgnd;
	rgnBkgnd. CreateRectRgnIndirect(rcClient);

	CBrush* pBkgnd1 = (CBrush*)SendMessage(WM_CTLCOLOR_BKGND,(WPARAM)pDC,(LPARAM)pDC->GetWindow());
	pDC-> FillRgn(&rgnBkgnd, pBkgnd1 );

	// --- Restore the original Clipping Region
	pDC-> SelectClipRgn( pRgnOrgClip, RGN_COPY );
	if( pRgnOrgClip )
		pRgnOrgClip ->DeleteObject();

	return TRUE;
}

void CTabCtrlAdvanced::OnPaint() 
{
	// Do not call CTabCtrl::OnPaint() for painting messages
	CPaintDC dc(this); // device context for painting

	// --- Get Current Clipping Region
	CRgn* pRgnOrgClip1;
	HRGN hrgnOrgClip;
	::GetClipRgn( dc. GetSafeHdc(), hrgnOrgClip );
	pRgnOrgClip1 = CRgn::FromHandle( hrgnOrgClip );

	dc. SelectClipRgn(NULL);
	// --- minimize the drawable Area
	// - complete Client Region
	CRect rcClient;
	GetClientRect( &rcClient );
	CRgn rgnTotalClient;
	rgnTotalClient .CreateRectRgnIndirect( rcClient );
	// - Display Region
	CRect rcDisplay;
	GetDisplayRect( &rcDisplay );
	CRgn rgnDisplay;
	rgnDisplay .CreateRectRgnIndirect( rcDisplay );
	CBrush* pBrDisplayBkgnd = (CBrush*)SendMessage( WM_CTLCOLOR_DISPLAY,
													(WPARAM)&dc, 
													(LPARAM)dc. GetWindow() );
	dc. FillRgn( &rgnDisplay, pBrDisplayBkgnd );
	// - remaining Draw Region
	CRgn rgnMyArea;
	rgnMyArea .CreateRectRgn( 0, 0, 1, 1 );
	rgnMyArea .CombineRgn( &rgnTotalClient, &rgnDisplay , RGN_DIFF );
	dc .SelectClipRgn (&rgnMyArea, RGN_COPY );

	// - General Datas
	int selected = GetCurSel();
	int count = GetItemCount();
	CRect rcItem;
	// TabCtrl Structure
	DRAWITEMSTRUCT drwItStr1;
		drwItStr1 .CtlType	= 101;		//??	WHY EVER
		drwItStr1 .CtlID		= 59648;	//??	WHY EVER
	TC_ITEM item1;
		item1. mask			= 0;
		item1. cchTextMax	= 0;

	// --- Draw the selected Item
	GetItem( selected, &item1 );
	drwItStr1. itemID	= selected;

	drwItStr1. itemAction= ODA_SELECT;
	drwItStr1. itemState = ODS_SELECTED;
	drwItStr1. hDC		= dc. GetSafeHdc();
	drwItStr1. itemData	= 0;

	// get the rectangle
	GetItemRect( selected, rcItem );
	rcItem. InflateRect( 2, 2 );
	drwItStr1. rcItem	= rcItem;
	DrawItem( &dc, rgnMyArea, &drwItStr1 );

	// --- Draw the Border of the Display
	CRect rcDisplayBorder(rcDisplay);
	rcDisplayBorder .InflateRect(1,1);
	
	CPen* pOldPen;
	CPen light,dark;
	light.CreatePen(PS_SOLID,2,GetSysColor(COLOR_3DLIGHT));
	dark. CreatePen(PS_SOLID,2,GetSysColor(COLOR_3DSHADOW));

	pOldPen = dc.SelectObject(&light);
	dc. MoveTo(rcDisplayBorder.right,rcDisplayBorder.top);
	dc. LineTo(rcDisplayBorder.left,rcDisplayBorder.top);
	dc. LineTo(rcDisplayBorder.left,rcDisplayBorder.bottom);
	
	dc.SelectObject(&dark);
	dc. LineTo(rcDisplayBorder.right,rcDisplayBorder.bottom);
	dc. LineTo(rcDisplayBorder.right,rcDisplayBorder.top);
	
	dc. SelectObject(pOldPen);
	light. DeleteObject();
	dark. DeleteObject();

	CRgn rgnDisplayBorder;
	rgnDisplayBorder. CreateRectRgnIndirect( rcDisplayBorder );
	rgnMyArea .CombineRgn( &rgnMyArea, &rgnDisplayBorder, RGN_XOR );
	dc .SelectClipRgn(&rgnMyArea,RGN_AND);
	
	// --- Draw the remaining Items
		for (int r = 0; r < GetRowCount(); r++)							
	{																
		for (int ix = 0 ; ix < count ; ix ++)
		{
			GetItemRect(ix,rcItem);										
			if (GetItemRow(rcItem) == r)								
			{															
				// Der Selektierte wurde ja schon gemalt
				if ( ix != selected )
				{
					GetItem(ix,&item1);
					drwItStr1.itemID=ix;
					//Status setzten
					drwItStr1.itemAction=ODA_SELECT;
					drwItStr1.itemState = UINT( ~ODS_SELECTED );
					drwItStr1.hDC=dc.GetSafeHdc();
					drwItStr1.rcItem=rcItem;
					drwItStr1.itemData=0;			
					DrawItem(&dc, rgnMyArea, &drwItStr1);
				}
			}
		}
	}

	// --- Restore the old Clipping Area
	dc.SelectClipRgn(pRgnOrgClip1);
	if( pRgnOrgClip1 )
		pRgnOrgClip1-> DeleteObject();

	return;
}

void CTabCtrlAdvanced::DrawItem(CDC* pDC, CRgn& region, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// retrieve Informations
	TC_ITEM info;
	info.mask = 0;
	info.cchTextMax = 0;
	GetItem(lpDrawItemStruct->itemID,&info);
	
	// Get the Color by a Call to our OnCtlColor
	CBrush* pBk = (CBrush*)SendMessage( WM_CTLCOLOR_TABITEM, 
										(LPARAM)pDC, 
										(WPARAM)pDC->GetWindow() );
	CBrush* pOldBr = pDC->SelectObject(pBk);
	// old Colour for restoring at End
	COLORREF nOldColor;

	if ((lpDrawItemStruct-> itemState) == ODS_SELECTED)
	{
		// The Selected Item print out its Text in RED
		nOldColor	= pDC ->SetTextColor( RGB(255, 0, 0) );
	}
	else
	{
		// all normal Item print out their Text in BLACK
		nOldColor	= pDC ->SetTextColor( RGB(0, 0, 0) );
	}

	// ----
	CRgn usedRegion;		// Outer Border of Item to add to Clipping Region
	
	// --- Item Background and Border
	drawItemBackground( pDC,					// The DC
						lpDrawItemStruct,		// DrawInfo
						usedRegion);			// the drawn Region
	// --- Item Text
	drawItemText( pDC,							// The DC
				  lpDrawItemStruct );			// DrawInfo

// - retrieve old clipping Area
	region .CombineRgn( &region, &usedRegion, RGN_XOR );	//cut out overlapped Regions
	pDC ->SelectClipRgn( &region, RGN_AND );			// clip out visible Region of the Item

	//
	// release GDI-Objekte
	usedRegion .DeleteObject();

	// reset old Colour & Brush
	pDC -> SetTextColor( nOldColor );
	pDC->SelectObject(pOldBr);
	
	
}

// --- Background and Border draw function
void CTabCtrlAdvanced::drawItemBackground( CDC* pDC, 
								  LPDRAWITEMSTRUCT lpDrawItemStruct,
								  CRgn& usedRegion)
{
	// --- get the Inner & Outer Region of the Item
	CRgn inner;
	CRgn outer;
	getItemRgn( lpDrawItemStruct->itemID, outer, inner );

	// --- retrieve the Bounding Box of the Border Region, this is
	//			used later on for drawing the Shadows
	CRect rcBorder;
	outer.GetRgnBox(rcBorder);

	// --- Draw on a MemDC to avoid flickering
	CDC memDC;
	memDC .CreateCompatibleDC( pDC );

	CBitmap memBMP;
	memBMP .CreateCompatibleBitmap(pDC, rcBorder .Width(), rcBorder .Height() );
	CBitmap* pOldBmp = memDC .SelectObject(&memBMP);

	// --- offset of item einbeziehen
	memDC.SetWindowOrg(rcBorder.left,rcBorder.top);

	// --- copy current Screen to MemDC
	memDC .BitBlt(rcBorder.left,rcBorder.top,rcBorder.Width(),rcBorder.Height(),
				pDC,rcBorder.left,rcBorder.top, SRCCOPY);

	CGdiObject gdiLight;
	CGdiObject gdiDark;

	// --- The Shadows are SOLID_BURSHES, get Colors from System
	((CBrush*)&gdiLight) ->CreateSolidBrush( GetSysColor( COLOR_3DHILIGHT ) );
	((CBrush*)&gdiDark ) ->CreateSolidBrush( GetSysColor( COLOR_3DSHADOW  ) );

	// --- Make a Region out of the Bounding Item Rectangle
	//			eine Region umwandeln
	CRgn alles;
	alles .CreateRectRgnIndirect(rcBorder);

	// --- every thing about a diagonal from the left-Bottom to the
	//			right-Top must be drawn in the Light-Color
	CRgn tstTLRgn;
	CPoint ptTest[3];
	ptTest[0] = CPoint(rcBorder.left,rcBorder.top);
	ptTest[1] = CPoint(rcBorder.right,rcBorder.top);
	ptTest[2] = CPoint(rcBorder.left,rcBorder.bottom);
	tstTLRgn.CreatePolygonRgn(ptTest,3,WINDING);

	// --- The Border Region is exactly the small difference between
	//			outer and inner Region
	CRgn borderRgn;
	borderRgn.CreateRectRgn(0,0,1,1);
	borderRgn.CombineRgn(&outer,&inner,RGN_DIFF);

	// --- The combination of our Triangle-Top-Left-Region and the
	//		the Border region must be drawn with the Light-Color
	CRgn drawBorder;
	drawBorder.CreateRectRgn(0,0,0,1);
	drawBorder.CombineRgn(&borderRgn,&tstTLRgn,RGN_AND);
	memDC .FillRgn(&drawBorder,(CBrush*)&gdiLight);

	//		... the Rest must be drawn with the dark Color
	drawBorder.CombineRgn(&borderRgn,&tstTLRgn,RGN_DIFF);
	memDC .FillRgn(&drawBorder,(CBrush*)&gdiDark);

	CBrush* pItemBkgndBrush = NULL;
	// --- Get the Item Background Brush by calling our OnCtlColor
	pItemBkgndBrush = (CBrush*)SendMessage( WM_CTLCOLOR_TABITEM, 
											(LPARAM)pDC, 
											(WPARAM)lpDrawItemStruct );
	ASSERT(pItemBkgndBrush);

	CWnd* pWndScr = pDC ->GetWindow();
	CWnd* pWndMem = memDC.GetWindow();

	// --- If we are working with Textures later-on, we have to change
	//		our Brush Origines so that the Texture for the Item, and
	//		and the Display Area fit together, without any breaks.
	CRect rcDisplay;
	GetDisplayRect(rcDisplay);
	CPoint ptM(rcDisplay.left, rcDisplay.top);
	memDC .LPtoDP(&ptM);

	memDC .SetBrushOrg(ptM);

	memDC .FillRgn(&inner,(CBrush*)pItemBkgndBrush);

	// --- Now, after we have done all the work, and every thing looks
	//			beautiful, we will present our result on the real Screen
	pDC ->BitBlt(rcBorder.left,rcBorder.top,rcBorder.Width(),rcBorder.Height(),
				&memDC,rcBorder.left,rcBorder.top, SRCCOPY);

	memDC .SelectObject(pOldBmp);
	memBMP .DeleteObject();

	usedRegion .DeleteObject();
	usedRegion .CreateRectRgn(0,0,1,1);
	usedRegion .CopyRgn(&outer);
	
	// release GDI-Objekte
	tstTLRgn .DeleteObject();
	inner .DeleteObject();
	outer .DeleteObject();
}

// --- If you need more than the standard variable, you can work
//			with additional information in the lParam of the
//			TC_ITEM-Structure. 
void CTabCtrlAdvanced::drawItemText( CDC* pDC, LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	if ( UINT( GetItemCount() ) > (lpDrawItemStruct -> itemID))
	{
		CRect rcItem = lpDrawItemStruct->rcItem;
		rcItem . DeflateRect( 2, 2);
		pDC->SetBkMode(TRANSPARENT);
		TC_ITEM item;
		item.mask = TCIF_PARAM;

		GetItem(lpDrawItemStruct ->itemID,&item);
		CTabItemInfo* pData = (CTabItemInfo*)item. lParam;
		ASSERT( pData-> IsKindOf(RUNTIME_CLASS(CTabItemInfo)) );

		pDC->TextOut(rcItem.left+2,rcItem.top+2,pData->m_strText);

		delete[]item.pszText;
	}
}

LRESULT CTabCtrlAdvanced::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT lRes;
	if( (WM_CTLCOLOR_FIRST <= message) && (message <= WM_CTLCOLOR_LAST) )
	{
		lRes = (LRESULT)OnCtlColor( (CDC*)wParam, 
									(LPDRAWITEMSTRUCT)lParam, 
									message );
		return lRes;
	}

	return CTabCtrl::WindowProc(message, wParam, lParam);
}

HBRUSH CTabCtrlAdvanced::OnCtlColor(CDC* pDC, 
									 LPDRAWITEMSTRUCT lpDrawItemStruct, 
									 UINT nCtlColor) 
{
	static CBrush brDefault;
	if(!brDefault.m_hObject)
		brDefault.CreateSolidBrush( GetSysColor(COLOR_3DFACE) );
	
	static CBrush brTabItem;
	static CBrush brDisplay;
	static CBrush brBackground;

	if ( nCtlColor == WM_CTLCOLOR_TABITEM )
	{
		if(brTabItem.m_hObject)
			brTabItem. DeleteObject();

		TC_ITEM item;
		item.mask = TCIF_PARAM;
		GetItem( lpDrawItemStruct->itemID, &item );
		CTabItemInfo* pData = (CTabItemInfo*)item.lParam;
		ASSERT( pData->IsKindOf(RUNTIME_CLASS(CTabItemInfo)) );
		if (!brTabItem.m_hObject)
		{
			brTabItem. CreateSolidBrush(pData->m_Color);
		}

		return (HBRUSH)&brTabItem;
	}
	if( nCtlColor == WM_CTLCOLOR_DISPLAY )
	{
		if (!brDisplay.m_hObject)
		{
			brDisplay. CreateSolidBrush(RGB(0,200,200));
		}

		return (HBRUSH)&brDisplay;
	}
	if( nCtlColor == WM_CTLCOLOR_BKGND )
	{
		if (!brBackground.m_hObject)
		{
			brBackground. CreateSolidBrush(RGB(200,0,200));
		}

		return (HBRUSH)&brBackground;
	}

	return (HBRUSH)&brDefault;
}
