// LBTabCtrl.cpp : implementation file
//
// Copyright © 2000 Oleg Lobach, All Rights Reserved.
//
// mailto:oleglb@mail.ru
//or
// mailto:oleg@alexen.ru
//
//
// This source file may be redistributed unmodified by any means PROVIDING 
// it is NOT sold for profit without the authors expressed written 
// consent, and providing that this notice and the authors name and all 
// copyright notices remain intact. This software is by no means to be 
// included as part of any third party components library, or as part any
// development solution that offers MFC extensions that are sold for profit. 
// 
// If the source code is used in any commercial applications then a statement 
// along the lines of:
// 
// "Portions Copyright © 1999 Oleg Lobach" must be included in the "Startup 
// Banner", "About Box" or "Printed Documentation". This software is provided 
// "as is" without express or implied warranty. The author accepts no 
// liability for any damage/loss of business that this  product may cause.
//
/////////////////////////////////////////////////////////////////////////////
//****************************************************************************

#include "stdafx.h"
#include "LBTabCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLBTabCtrl

CLBTabCtrl::CLBTabCtrl():m_nPrevPointedItem(-1),m_bOverTab(false),
						m_nActiveItem(-1),m_bFloatPaint(false),
						m_rectUpDn(0,0,0,0),m_rctPage(0,0,0,0),
						m_bAutoRaising(true),m_bHasFocus(false)
{
}

CLBTabCtrl::~CLBTabCtrl()
{
}
BEGIN_MESSAGE_MAP(CLBTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CLBTabCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_HSCROLL()
	ON_NOTIFY_REFLECT_EX(TCN_SELCHANGE, OnSelchange)
	ON_NOTIFY_REFLECT_EX(TCN_SELCHANGING, OnSelchanging)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave) 
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////


void CLBTabCtrl::PreSubclassWindow() 
{
	CTabCtrl::PreSubclassWindow();

	// Get default menu font.
	// We shall use it to draw tab's text.
	//
	// If somebody don't like this font
	// he or she always can use  the AfxGetPropSheetFont implementation
	// from "ccdata.cpp", located with MFC source files.

	NONCLIENTMETRICS nclim;
	nclim.cbSize=sizeof(NONCLIENTMETRICS);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
							sizeof(NONCLIENTMETRICS),
							&nclim,0);
	m_hMenuFont= ::CreateFontIndirect(&nclim.lfMenuFont);
	
	//Create pens for drawing CLBTabCtrl
	COLORREF clr = ::GetSysColor(COLOR_3DHILIGHT);	
	m_hPenLight = ::CreatePen(PS_SOLID,1,clr);
	clr=::GetSysColor(COLOR_3DDKSHADOW);
	m_hPenShadow = ::CreatePen(PS_SOLID,1,clr);
	clr=::GetSysColor(COLOR_3DSHADOW);
	m_hPenItemShadow = ::CreatePen(PS_SOLID,1,clr);

	//Look for msctls_updown32 control and if it is present, modify its size,
	//position and subclass it to CLBSpinButtonCtrl, which have autodisabling
	//arrow buttons.
	//The msctls_updown32 control exists when CLBTabCtrl is not in stacked mode.
	CWnd* pWnd = GetWindow(GW_CHILD);
	while(pWnd)
	{
		char buf[]="msctls_updown32";
		int nRet=::GetClassName(pWnd->m_hWnd,buf,sizeof(buf)/sizeof (buf[0]));
		if(nRet && strcmp(buf,"msctls_updown32"))
		{
			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}
		else
		{
			//The msctls_updown32 control is found.
			//
			pWnd->GetWindowRect(&m_rectUpDn);
			ScreenToClient(&m_rectUpDn);

			//Update size and position of msctls_updown32 control
			m_rectUpDn.DeflateRect(3,2);
			m_rectUpDn.OffsetRect(3,5);
			pWnd->MoveWindow(&m_rectUpDn);
			
			//Subclass common msctls_updown32 control to
			//my CLBSpinButtonCtrl, which have autodisabling arrow buttons.
			m_Spin.SubclassWindow(pWnd->m_hWnd);

			pWnd=0;
		}
	}
	m_nActiveItem=GetCurSel();
	CRect rctItem;
	GetItemRect(0,&rctItem);
	GetClientRect(&m_rctPage);
	m_rctPage.top=rctItem.bottom;
}

LRESULT CLBTabCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//This handler is called when mouse leaves CLBTabCtrl
	m_bOverTab=false;
	if(m_nPrevPointedItem>=0)
	{
		if (m_nPrevPointedItem!=m_nActiveItem)
		{
			//If we are here,then mouse leaved the raised item, so
			//we have to redraw it as normal (unraised).

			CRect rectItem;
			GetItemRect(m_nPrevPointedItem,&rectItem);
			rectItem.top-=FLOAT_ITEM_HEIGHT_SHIFT;


			//If the right side of item overlaps the up-down control,
			//we have to exclude the up-down control from update region
			//to reduce flickering
			if(!m_rectUpDn.IsRectEmpty() && rectItem.right >= m_rectUpDn.left)
				rectItem.right = m_rectUpDn.left;

			InvalidateRect(&rectItem);
			UpdateWindow();
		}
		m_nPrevPointedItem=-1;
	}
return 0;
}

void CLBTabCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bAutoRaising)
	{
		if(!m_bOverTab )
		{
		//	We are here if the mouse  just entered the CLBTabCtrl
		//
		//	Let's use _TrackMouseEvent API to be notified when the mouse leaves.
		//	This API tries to use the window manager's
		//	implementation of TrackMouseEvent if it is present,
		//	otherwise it emulates.

			m_bOverTab=true;
			TRACKMOUSEEVENT stTRACKMOUSEEVENT;
			stTRACKMOUSEEVENT.cbSize = sizeof(stTRACKMOUSEEVENT);
			stTRACKMOUSEEVENT.hwndTrack=m_hWnd;
			stTRACKMOUSEEVENT.dwFlags=TME_LEAVE;
			_TrackMouseEvent(&stTRACKMOUSEEVENT);
		}
		CRect rectItem(0,0,0,0);

		//	Here we shall get mouse position for the last dispatched message and
		//	test if mouse is over any tab item.
		TCHITTESTINFO thi;
		thi.pt=point;
		int nItem=HitTest(&thi);
		if(nItem>=0)
		{
			if(nItem!=m_nPrevPointedItem )
			{
			//	Mouse is over new inactive item.
				if(m_nPrevPointedItem>=0 && m_nPrevPointedItem!=m_nActiveItem)
				{
				//	Redraw the item, over which mouse was on the previous step.
				//	We redraw it as normal (unraised).
					  
					GetItemRect(m_nPrevPointedItem,&rectItem);
					rectItem.top-=FLOAT_ITEM_HEIGHT_SHIFT;


					// If the right side of item overlaps the up-down control,
					// we have to exclude the up-down control from update region
					// to reduce flickering.
					if(!m_rectUpDn.IsRectEmpty() && rectItem.right >= m_rectUpDn.left)
						rectItem.right= m_rectUpDn.left;

					InvalidateRect(&rectItem);
					UpdateWindow();
				}
				 if(nItem!=m_nActiveItem)
				 {
				 //Redraw the item, over which mouse is now.
				 //We redraw it as raised.
					GetClientRect(&rectItem);
					ValidateRect(&rectItem);
					GetItemRect(nItem,&rectItem);
					m_bFloatPaint=true;
					rectItem.top-=FLOAT_ITEM_HEIGHT_SHIFT;


					// If the right side of item overlaps the up-down control,
					// we have to exclude the up-down control from update region
					// to reduce flickering
					if(!m_rectUpDn.IsRectEmpty() && rectItem.right >= m_rectUpDn.left)
						rectItem.right= m_rectUpDn.left;

					InvalidateRect(&rectItem);
					UpdateWindow();
				 }
				m_nPrevPointedItem=nItem;
			}
		}
	}
  CTabCtrl::OnMouseMove(nFlags, point);
}

BOOL CLBTabCtrl::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//	After CLBTabCtrl control (or its parent) handles TCN_SELCHANGING message,  
	//	the system will  send to it WM_PAINT/WM_ERASEBKGND messages.
	//	Since at that moment we still don't know which item has become active,
	//	and can not properly draw items, we have to avoid these 
	//	WM_PAINT/WM_ERASEBKGND messages to get rid of flickering.
	//
	//	Since up-down control do not receive WM_PAINT/WM_ERASEBKGND messages 
	//	if it is invisible, so we temporary  set the appropriate visible bits off
    //	and the control thinks it is visible even though it is not.
	//	We will set visible bits back on in TCN_SELCHANGE handler, when
	//	it is good time to redraw CLBTabCtrl.

	CRect rctUpdate;
	GetClientRect(&rctUpdate);
	ValidateRect(&rctUpdate); //Clean-up any pending WM_PAINTs
	
	DWORD dwStyle = ::GetWindowLong(m_hWnd,GWL_STYLE);
	if (dwStyle & WS_VISIBLE)
     ::SetWindowLong(m_hWnd, GWL_STYLE, (dwStyle & ~ WS_VISIBLE));//switch off WS_VISIBLE

	*pResult = 0;
	return FALSE;
}

BOOL CLBTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_nPrevPointedItem=-1;
	*pResult = 0;

	CRect rctUpdate;
	GetClientRect(&rctUpdate);

	//	We will set visible bits back on here (see comments in OnSelchanging),
	//	since now we know which item became active and can redraw CLBTabCtrl.
	ValidateRect(&rctUpdate);//Clean-up any pending WM_PAINTs
	DWORD dwStyle = ::GetWindowLong(m_hWnd,GWL_STYLE);
	if ((dwStyle & WS_VISIBLE) == 0)
        ::SetWindowLong(m_hWnd, GWL_STYLE, (dwStyle | WS_VISIBLE));//switch on WS_VISIBLE
	
	m_nActiveItem=GetCurSel();
	if(::IsWindow(m_Spin.m_hWnd))
	{
		//As so the CLBSpinButtonCtrl lives within CLBTabCtrl,we have to
		// update its (CLBSpinButtonCtrl) state when tab order has changed
		UINT nLeftItem=FindLeftDownItem();
		NMUPDOWN nmUpDn;
		nmUpDn.iDelta=0;
		nmUpDn.iPos=nLeftItem;
		nmUpDn.hdr.code=UDN_DELTAPOS;
		nmUpDn.hdr.hwndFrom=m_Spin.m_hWnd;
		nmUpDn.hdr.idFrom=::GetDlgCtrlID(m_Spin.m_hWnd);

		::SendMessage(::GetParent(m_Spin.m_hWnd),
							WM_NOTIFY,(WPARAM)nmUpDn.hdr.idFrom,
							(LPARAM)&nmUpDn);
	}


	rctUpdate.bottom=m_rctPage.top+2;
	rctUpdate.top=0;

	// If the right side of update region overlaps the up-down control,
	// we have to exclude the up-down control from update region
	// to reduce flickering
	if(!m_rectUpDn.IsRectEmpty())
	{
		rctUpdate.right= m_rectUpDn.left;
	}
	//Let's repaint tabs,since the active tab has changed
	InvalidateRect(&rctUpdate,FALSE);
	UpdateWindow();

	return FALSE;
}

void CLBTabCtrl::OnPaint() 
{
	CRect rcPnt,rcItem,rcActive,rectCli;
	CDC dc;
	CBitmap bmp;
	GetClientRect(&rectCli);
	CPaintDC dcReal(this); // device context for painting


	//To reduce flickering we are drawing to memory DC,
	//and then BitBlting result to the screen.
	//So we have to create compatible memory DC and select bitmap into it.
	dc.CreateCompatibleDC(&dcReal);
	bmp.CreateCompatibleBitmap(&dcReal,rectCli.Width(),rectCli.Height());
	CBitmap *pOldBitmap;
	pOldBitmap=dc.SelectObject(&bmp);

	//Copy update rect to rcPnt 
	rcPnt=dcReal.m_ps.rcPaint;
	COLORREF clrFill=::GetSysColor(COLOR_3DFACE);

	//As so I bypassed WM_ERASEBCKGND, do its job here 
	dc.FillSolidRect(&rcPnt,clrFill);

	HPEN hOldPen;
	DRAWITEMSTRUCT drawItemStruct;

	hOldPen = (HPEN)::GetCurrentObject(dc.m_hDC,OBJ_PEN);
	
	//Active item should be wider then other items.
	//So here we calculate and apply the width difference.
	GetItemRect(m_nActiveItem,&rcActive);
	if(m_nActiveItem!=(int)FindLeftDownItem()) // if acive item is not leftmost,
		rcActive.left-=3;					   // then move to the left its left side.
	TCHITTESTINFO thi;
	thi.pt=CPoint(rcActive.right+5,rcActive.bottom-4);
	int nPos = HitTest(&thi);
	if(nPos>=0)				// if acive item is not rightmost,
		rcActive.right+=3;	// then move to the right its left side.

	//Active item should be higher then other items.
	//So here we  apply the height difference.
	rcActive.top-=ACTIVE_ITEM_HEIGHT_SHIFT;

	if (m_bFloatPaint )
	{	
		//
		//The mouse is  moving over inactive item - raise it
		//
		m_bFloatPaint=false;
		//Get the mouse position for the last dispatched message and
		// find index of item, over which the mouse is(was).
		TCHITTESTINFO tci;
		tci.pt=CPoint(::GetMessagePos());
		ScreenToClient(&tci.pt);
		int nItemFloat=HitTest(&tci);
		if(nItemFloat>=0)
		{
			GetItemRect(nItemFloat,&rcItem);
			rcItem.DeflateRect(ITEM_DEFLATE,0);
			rcItem.top-=FLOAT_ITEM_HEIGHT_SHIFT;
		
			//Draw item's text,bitmap,...
			drawItemStruct.rcItem=rcItem;
			drawItemStruct.hDC=dc.GetSafeHdc();
			drawItemStruct.itemID=nItemFloat;
			DrawItem(&drawItemStruct);

			//Draw item's rect
			//HINT_ACTIVATE_RIGHT_SIDE is a flag indicating, that the
			//right side of rect should be drawn as for active item (darker).
			DrawItemRect(dc,rcItem,HINT_ACTIVATE_RIGHT_SIDE);
		}
	}
	else
	{
		//If we are here, then  complex repaint is required.
		CRect rectTemp;
		if(rectTemp.IntersectRect(m_rctPage,rcPnt) && rcActive.bottom == m_rctPage.top)
		{
			//Let's draw Property Page bounding rectangle as 3D.

			rectTemp=m_rctPage;
			::SelectObject(dc.m_hDC,m_hPenLight);
			dc.MoveTo(rectTemp.left,rectTemp.bottom+1);
			dc.LineTo(rectTemp.left,rectTemp.top+1);

			if(rcActive.left>=0)
			{
				dc.LineTo(rcActive.left,rcActive.bottom+1);
				if(m_rectUpDn.IsRectEmpty())
				{
					dc.MoveTo(rcActive.right,rcActive.bottom+1);
				}
				else
				{
					if(rcActive.right >= m_rectUpDn.left)
					{
						dc.MoveTo(m_rectUpDn.left-SHIFT_FROM_CUT_TO_SPIN+2,
							rcActive.bottom+1);
					}
					else
					{
						dc.MoveTo(rcActive.right,rcActive.bottom+1);

					}
				}
				dc.LineTo(rectTemp.right-2,rcActive.bottom+1);
			}
			else
			{
				CRect rectItemLeftmost;
				UINT nItemLeftmost=FindLeftDownItem();
				GetItemRect(nItemLeftmost,&rectItemLeftmost);
				dc.LineTo(rectTemp.right-2,rcActive.bottom+1);
			}
			::SelectObject(dc.m_hDC,m_hPenItemShadow);
			dc.LineTo(rectTemp.right-2,rectTemp.bottom-2);
			dc.LineTo(rectTemp.left,rectTemp.bottom-2);

			::SelectObject(dc.m_hDC,m_hPenShadow);
			dc.MoveTo(rectTemp.right-1,rcActive.bottom+1);
			dc.LineTo(rectTemp.right-1,rectTemp.bottom-1);
			dc.LineTo(rectTemp.left-2,rectTemp.bottom-1);

		}

		int nCount = GetItemCount();

		for(int i=0;i< nCount;i++)
		{
			if(i!=m_nActiveItem)
			{
				//Let's draw all inactive  items which intersects invalidated
				//rect (rcPaint).
				GetItemRect(i,&rcItem);
				if (rectTemp.IntersectRect(&rcItem,&rcPnt))
				{
					rcItem.DeflateRect(ITEM_DEFLATE,0);

					//Draw item's text,bitmap,...
					drawItemStruct.rcItem=rcItem;
					drawItemStruct.hDC=dc.GetSafeHdc();
					drawItemStruct.itemID=i;
					DrawItem(&drawItemStruct);
					DrawItemRect(dc,rcItem);
				}
			}
		}

	}
	if (rcPnt.IntersectRect(&rcActive,&rcPnt) && rcActive.left > 0)
	{
		//Current update region intersects the active item,
		// so we should repaint it.
		rcItem=rcActive;
		dc.FillSolidRect(&rcItem,clrFill);

		//Draw item's text,bitmap,...
		drawItemStruct.rcItem=rcItem;
		drawItemStruct.hDC=dc.GetSafeHdc();
		drawItemStruct.itemID=m_nActiveItem;
		DrawItem(&drawItemStruct);

		DrawItemRect(dc,rcItem,HINT_ACTIVATE_RIGHT_SIDE|HINT_ACTIVE_ITEM);
		if(m_bHasFocus)
			DrawFocus(dc);


	}

	//Copy drawing from memory device context to the screen.
	dcReal.BitBlt(0,0,rectCli.Width(),rectCli.Height(),&dc,0,0,SRCCOPY);

	//Restore device context defaults.
	::SelectObject(dc.m_hDC,hOldPen);
	dc.SelectObject(pOldBitmap);
}

void CLBTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//Let's draw items text

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	//Set current font equal to default menu font.
	dc.SelectObject(m_hMenuFont);
	char buf[255];
	int nCurItem = lpDrawItemStruct->itemID;

	TCITEM tcitem;
	//Get text of item.
	tcitem.mask=TCIF_TEXT;
	tcitem.pszText =buf;
	tcitem.cchTextMax=sizeof(buf);
	GetItem(nCurItem,&tcitem);
	
	CRect rect=lpDrawItemStruct->rcItem;
	rect.OffsetRect(1,4);

	// Draw Item text.
	if(!m_rectUpDn.IsRectEmpty() && 
			lpDrawItemStruct->rcItem.right >= m_rectUpDn.left)
	{ 
		//The current item is cut on the right side.
		if(nCurItem == m_nActiveItem)
		{
			//If current item is active, then we should decrease its width
			//as so, the length of the visible text should be the same as when
			//this tab will be inactive. 
			if(m_nActiveItem!=(int)FindLeftDownItem())
					rect.left+=3;
			TCHITTESTINFO thi;
			thi.pt=CPoint(lpDrawItemStruct->rcItem.right+5,
						  lpDrawItemStruct->rcItem.bottom-4);
			int nPos = HitTest(&thi);
			if(nPos>=0)
				rect.right-=3;
		}

		//Decrease the length of the visible text, since
		//the right side is cut.
		rect.right=m_rectUpDn.left-SHIFT_FROM_CUT_TO_SPIN-1;
		rect.left+=4;
		::DrawText(lpDrawItemStruct->hDC,buf,-1,&rect,DT_LEFT);
	}
	else
	{
		::DrawText(lpDrawItemStruct->hDC,buf,-1,&rect,DT_CENTER);
	}	
	dc.Detach();
}

void CLBTabCtrl::DrawItemRect(CDC &dc, CRect &rcItem,int nHint)
{
	//Let's draw items rect.
	rcItem.bottom-=1;
	if(rcItem.left>0)
	{
		bool bDoNotCut=true;

		::SelectObject(dc.m_hDC,m_hPenLight);
		
		if(nHint & HINT_ACTIVE_ITEM)
			dc.MoveTo(rcItem.left,rcItem.bottom+2);
		else
			dc.MoveTo(rcItem.left,rcItem.bottom);
		
		dc.LineTo(rcItem.left,rcItem.top+2);
		dc.LineTo(rcItem.left+2,rcItem.top);
		if(!m_rectUpDn.IsRectEmpty() && rcItem.right >= m_rectUpDn.left)
		{
			//	CLBTabCtrl is not in stacked mode and current item overlaps
			//	msctls_updown32 control. So let's decrease current item's  
			//	width.
			rcItem.right=m_rectUpDn.left-SHIFT_FROM_CUT_TO_SPIN;
			dc.LineTo(rcItem.right,rcItem.top);
			bDoNotCut=false;
		}
		else
			dc.LineTo(rcItem.right-2,rcItem.top);
		
		if(!nHint)
			::SelectObject(dc.m_hDC,m_hPenItemShadow);
		else
		{
			if(nHint & HINT_ACTIVATE_RIGHT_SIDE)
			{
				::SelectObject(dc.m_hDC,m_hPenShadow);
			}
		}
		if(bDoNotCut)
		{
			if(nHint & HINT_ACTIVE_ITEM)
			{
				dc.LineTo(rcItem.right,rcItem.top+2);
				dc.LineTo(rcItem.right,rcItem.bottom+2);
			}
			else
			{
				dc.LineTo(rcItem.right,rcItem.top+2);
				dc.LineTo(rcItem.right,rcItem.bottom+1);
			}
		}
		else
		{
			//	CLBTabCtrl is not in stacked mode and current item overlaps
			//	msctls_updown32 control. So let's draw current item's rect 
			//	as cut.
			int nYPos=rcItem.top+2;

			nYPos+=rcItem.Height()/5;
			rcItem.right+=1;
			if(nYPos < rcItem.bottom)
				dc.LineTo(rcItem.right,nYPos);

			nYPos+=rcItem.Height()/3;
			rcItem.right-=2;
			if(nYPos < rcItem.bottom)
				dc.LineTo(rcItem.right,nYPos);

			nYPos+=rcItem.Height()/5;
			rcItem.right+=1;
			if(nYPos < rcItem.bottom)
				dc.LineTo(rcItem.right,nYPos);

			nYPos+=rcItem.Height()/5;
			rcItem.right+=1;
			if(nYPos < rcItem.bottom)
				dc.LineTo(rcItem.right,nYPos);
			if(nHint & HINT_ACTIVE_ITEM)
			{
				dc.LineTo(rcItem.right,rcItem.bottom+2);
			}
			else
				dc.LineTo(rcItem.right,rcItem.bottom+1);

		}
	}
}

BOOL CLBTabCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE; //Let's get rid of flickering
}

void CLBTabCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	//	This handler used only when CLBTabCtrl is in scrolling mode.
	//
	//
	if(nSBCode == SB_THUMBPOSITION)
	{
		CTabCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
		//	If the current position of CLBSpinButtonCtrl has changed,
		//	we have to repaint area near it, since it could have
		//	traces of rightmost item.
		CRect rctNearSpin;
		GetClientRect(&rctNearSpin);
		rctNearSpin.right = m_rectUpDn.left;
		rctNearSpin.bottom = m_rectUpDn.bottom+2;
		rctNearSpin.left=m_rectUpDn.left-2*SHIFT_FROM_CUT_TO_SPIN;

		InvalidateRect(&rctNearSpin);
		UpdateWindow();
	}
}

UINT CLBTabCtrl::FindLeftDownItem() const
{
	//Helper function
	//Finds leftmost down item.

	CRect rctLeft(100000,0,0,0),rctCur;
	int nCount = GetItemCount()-1;
	UINT nItem=0;
	for(int i=0;i<nCount;i++)
	{
		GetItemRect(i,&rctCur);
		if(rctCur.left > 0 && rctCur.left <= rctLeft.left)
		{
			if(rctCur.bottom > rctLeft.bottom)
			{
				rctLeft=rctCur;
				nItem=i;	
			}
		}
	}
	return nItem;
}


LRESULT CLBTabCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message != TCM_SETCURSEL)
		return CTabCtrl::WindowProc(message, wParam, lParam);
	else
	{	//	We need to handle this message to alter CLBTabCtrl state,
		//	which may change due to user keyboard input ('Control-Tab')
		//	or because of direct SendMessage.
		//
		//	After CLBTabCtrl control handles TCM_SETCURSEL message,  
		//	the system will draw the tab control, by sending to it 
		//	WM_PAINT/WM_ERASEBKGND messages.
		//	Since we perform actual redraw in  TCN_SELCHANGE handler ,
		//	we have to avoid these WM_PAINT/WM_ERASEBKGND messages 
		//	to get rid of flickering.
		//
		//	Since up-down control do not receive WM_PAINT/WM_ERASEBKGND messages 
		//	if it is invisible, so we temporary  set the appropriate visible bits
		//	off and the control thinks it is visible even though it is not.
		//	We shall set visible bits back on in TCN_SELCHANGE handler, when
		//	it is good time to redraw CLBTabCtrl.

		DWORD dwStyle = ::GetWindowLong(m_hWnd,GWL_STYLE);
		if (dwStyle & WS_VISIBLE)
		    ::SetWindowLong(m_hWnd, GWL_STYLE, (dwStyle & ~ WS_VISIBLE));
	
		LRESULT nResult = CTabCtrl::WindowProc(message, wParam, lParam);
		
		//Now let's meet with TCN_SELCHANGE message
		NMHDR nmhdr;
		nmhdr.hwndFrom = m_hWnd;
		nmhdr.idFrom = ::GetDlgCtrlID(m_hWnd);
		nmhdr.code = TCN_SELCHANGE;

		::SendMessage(::GetParent(m_hWnd),WM_NOTIFY,
						WPARAM(nmhdr.idFrom),LPARAM(&nmhdr));
		return nResult;
	}
}

bool CLBTabCtrl::SetAutoRaising(bool bOn)
{
	// User should have an opportunity to swith on/off the 
	// autoraising feature of the CLBTabCtrl control.

	bool bPrev = m_bAutoRaising;
	m_bAutoRaising = bOn;
	return bPrev;
}
void CLBTabCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	//Remove focus rect from active item
	m_bHasFocus	= false;
	CTabCtrl::OnKillFocus(pNewWnd);
}

void CLBTabCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	//Set a focus rect over active item.
	m_bHasFocus	= true;
	CTabCtrl::OnSetFocus(pOldWnd);

}

void CLBTabCtrl::DrawFocus(CDC &dc)
{
	//	Helper function
	//	Draws a focus rect over active item

		CRect rctItem;
		GetItemRect(m_nActiveItem,&rctItem);
		if(rctItem.left >=0)
		{
			if(m_nActiveItem!=(int)FindLeftDownItem())
				rctItem.left-=3;
			TCHITTESTINFO thi;
			thi.pt=CPoint(rctItem.right+5,rctItem.bottom-4);
			int nPos = HitTest(&thi);
			if(nPos>=0)
				rctItem.right+=3;

			if(!m_rectUpDn.IsRectEmpty()&& rctItem.right >= m_rectUpDn.left)
			{
				rctItem.right = m_rectUpDn.left-SHIFT_FROM_CUT_TO_SPIN;
				rctItem.right-=2;
				rctItem.left+=3;
			}
			else
				rctItem.DeflateRect(3,0);

			rctItem.top+=1;
			dc.DrawFocusRect(&rctItem);
		}
}

