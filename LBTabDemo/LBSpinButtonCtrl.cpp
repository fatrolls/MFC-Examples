// LBSpinButtonCtrl.cpp : implementation file
//
// Copyright © 1999 Oleg Lobach, All Rights Reserved.
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
// liability for any damage/loss of business that this product may cause.
//
/////////////////////////////////////////////////////////////////////////////
//****************************************************************************

#include "stdafx.h"
#include "LBSpinButtonCtrl.h"

#pragma warning(disable:4786)
#include <map>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;
typedef map <HWND,HWND> HWNDMAP;
static HWNDMAP gHandleMap;


static LRESULT CALLBACK FilterBuddyMsgProc(int code,WPARAM wParam,  LPARAM lParam );
static HHOOK ghHook=NULL;

/////////////////////////////////////////////////////////////////////////////
// CLBSpinButtonCtrl

CLBSpinButtonCtrl::CLBSpinButtonCtrl():m_hWndBuddy(NULL),
				   m_bVertical(true),m_nSpinAlign(Outside),
				   m_bDefaultDirection(true),m_bBuddyIsEdit(false),
				   m_rctIsPressed(0,0,0,0),m_bActiveSpinPressed(false),
				   m_bAutoDisable(true)
{
	
}

CLBSpinButtonCtrl::~CLBSpinButtonCtrl()
{
}


BEGIN_MESSAGE_MAP(CLBSpinButtonCtrl, CSpinButtonCtrl)
	//{{AFX_MSG_MAP(CLBSpinButtonCtrl)
	ON_NOTIFY_REFLECT_EX(UDN_DELTAPOS, OnDeltapos)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLBSpinButtonCtrl message handlers

void CLBSpinButtonCtrl::PreSubclassWindow() 
{
	//I need custom pens to draw up_down control

	COLORREF clr=::GetSysColor(COLOR_3DDKSHADOW);
	m_penDarkShadow=::CreatePen(PS_SOLID,0,clr);	

	clr=::GetSysColor(COLOR_BTNSHADOW);
	m_penShadow=::CreatePen(PS_SOLID,0,clr);

	clr=::GetSysColor(COLOR_3DHILIGHT);
	m_penLight=::CreatePen(PS_SOLID,0,clr);

	clr=::GetSysColor(COLOR_3DLIGHT);
	m_penLightShadow=::CreatePen(PS_SOLID,0,clr);

	clr=::GetSysColor(COLOR_BTNFACE);
	m_penButtonFace=::CreatePen(PS_SOLID,0,clr);


	Init();
	CSpinButtonCtrl::PreSubclassWindow();
}

void CLBSpinButtonCtrl::OnPaint() 
{
	if(m_bAutoDisable)
	{
		//Draw control by hands

		CPaintDC RealDC(this); // device context

		CRect rctPaint=m_rctClient;
		CRect rcPaintUp,rcPaintDown;

		//To get rid of flickering we are drawing to memory DC (dc),
		//and then BitBlting it to the screen.
		//So we have to create compatible memory DC and select bitmap into it.

		CDC dc;
		CBitmap bmpMem,*pOldMemBmp;
		dc.CreateCompatibleDC(&RealDC);
		bmpMem.CreateCompatibleBitmap(&RealDC,rctPaint.Width(),rctPaint.Height());
		pOldMemBmp=dc.SelectObject(&bmpMem);

		//As so I bypassed WM_ERASEBCKGND, do its job here 
		dc.FillSolidRect(&rctPaint,::GetSysColor(COLOR_BTNFACE));


		if(::IsWindow(m_hWndBuddy) && m_nSpinAlign!=Outside )
		{
			rctPaint.top+=2;
			rctPaint.bottom-=2;
			if(m_nSpinAlign == OnRightInside)
				rctPaint.right-=2;
			else
				rctPaint.left+=2;
		}

		rcPaintUp= rctPaint;

		//Draw control, depending on it alignment and orientation
		if(m_bVertical)
		{
			rcPaintUp.bottom=rcPaintUp.top+rcPaintUp.Height()/2;
			rcPaintDown=rctPaint;
			rcPaintDown.top=rcPaintDown.bottom-rcPaintUp.Height();

			dc.DrawFrameControl(&rcPaintUp,DFC_SCROLL,DFCS_SCROLLUP);
			dc.DrawFrameControl(&rcPaintDown,DFC_SCROLL,DFCS_SCROLLDOWN);

		}
		else
		{
			rcPaintUp.right=rcPaintUp.left+rcPaintUp.Width()/2;
			rcPaintDown=rctPaint;
			rcPaintDown.left=rcPaintDown.right-rcPaintUp.Width();

			dc.DrawFrameControl(&rcPaintUp,DFC_SCROLL,DFCS_SCROLLLEFT);
			dc.DrawFrameControl(&rcPaintDown,DFC_SCROLL,DFCS_SCROLLRIGHT);
		
		}
		
		if(::IsWindow(m_hWndBuddy) && m_nSpinAlign!=Outside )
		{
			//We are inside buddy,so have to draw buddy's border around
			//CLBSpinButtonCtrl
			
			//We use m_rctClient as so rctPaint may have been already modified.
			if(m_nSpinAlign == OnRightInside)
			{
				::SelectObject(dc.m_hDC,m_penShadow);
				dc.MoveTo(m_rctClient.left,m_rctClient.top);
				dc.LineTo(m_rctClient.right,m_rctClient.top);

				::SelectObject(dc.m_hDC,m_penDarkShadow);
				dc.MoveTo(m_rctClient.left,m_rctClient.top+1);
				dc.LineTo(m_rctClient.right-1,m_rctClient.top+1);

				::SelectObject(dc.m_hDC,m_penLight);
				dc.LineTo(m_rctClient.right-1,m_rctClient.bottom-1);
				dc.LineTo(m_rctClient.left-1,m_rctClient.bottom-1);
			}
			else
			{
				::SelectObject(dc.m_hDC,m_penShadow);
				dc.MoveTo(m_rctClient.right,m_rctClient.top);
				dc.LineTo(m_rctClient.left,m_rctClient.top);
				dc.LineTo(m_rctClient.left,m_rctClient.bottom);

				::SelectObject(dc.m_hDC,m_penDarkShadow);
				dc.MoveTo(m_rctClient.right,m_rctClient.top+1);
				dc.LineTo(m_rctClient.left+1,m_rctClient.top+1);
				dc.LineTo(m_rctClient.left+1,m_rctClient.top+1);
				dc.LineTo(m_rctClient.left+1,m_rctClient.bottom-1);

				::SelectObject(dc.m_hDC,m_penLight);
				dc.LineTo(m_rctClient.right+1,m_rctClient.bottom-1);
			}

		}
		//If the position reached the limit, draw corresponding
		//part of control as disabled
		switch (m_nSpinState)
		{
			case DisableRight:
								if(m_bDefaultDirection)
								{
									if(m_bVertical)
										DisableRect(dc,rcPaintDown);
									else
										DisableRect(dc,rcPaintUp);
								}
								else
								{
									if(m_bVertical)
										DisableRect(dc,rcPaintUp);
									else
										DisableRect(dc,rcPaintDown);
								}

								break;
			case DisableLeft:
								if(m_bDefaultDirection)
								{
									if(m_bVertical)
										DisableRect(dc,rcPaintUp);
									else
										DisableRect(dc,rcPaintDown);
								
								}
								else
								{
									if(m_bVertical)
										DisableRect(dc,rcPaintDown); 
									else
										DisableRect(dc,rcPaintUp);

								}
								break;
		}

		if(m_bActiveSpinPressed)
		{
			//The control's position has changed, so we have to
			//draw corresponding part as pressed
			if(m_rctIsPressed.IsRectEmpty())
			{
				CPoint pt=::GetMessagePos();
				ScreenToClient(&pt);
				if(rcPaintUp.PtInRect(pt))
				{
					m_rctIsPressed = rcPaintUp;
				}
				else
				{
					if(rcPaintDown.PtInRect(pt))
					{
						m_rctIsPressed = rcPaintDown; 
					}
				}

			}
			DrawPressedRect(dc,m_rctIsPressed);
			m_bActiveSpinPressed=false;

		}
		//Copy drawing from memory device context to the screen
		RealDC.BitBlt(m_rctClient.left,m_rctClient.top,m_rctClient.Width(),
			m_rctClient.Height(),&dc,m_rctClient.left,m_rctClient.top,SRCCOPY);

		dc.SelectObject(pOldMemBmp);
	}
	else
	{
		//Let the Windows do it's work 
		Default();
		return;
	}

}
void CLBSpinButtonCtrl::DisableRect(CDC &dc, const CRect &rectDisable) const
{
	CBitmap bmpMask,*pBmpBeforeMask;
	CBrush	brushMask,*pOldBrush;
	COLORREF clrOldBack,clrOldText;
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	
	CRect rctClient;
	CRect rectToDisable=rectDisable;
	GetClientRect(&rctClient);

	//Create MONO bitmap
	bmpMask.CreateBitmap(rctClient.Width(),rctClient.Height(),1,1,NULL);
	pBmpBeforeMask=memDC.SelectObject(&bmpMask);

	CDC dcSrc;
	dcSrc.CreateCompatibleDC(&dc);
	CBitmap bmpSrc,*pBmpBeforeSrc;
	
	bmpSrc.CreateCompatibleBitmap(&dc,rctClient.Width(),rctClient.Height());
	pBmpBeforeSrc=dcSrc.SelectObject(&bmpSrc);

	clrOldBack=dc.SetBkColor(RGB(0,0,0)); //Suppose arrows are black

	//Create mask into memDC (the pixels which in dc were black  - become white in memDC,
	//all others pixels in memDC become black)
	memDC.BitBlt(rectToDisable.left,rectToDisable.top,
		rectToDisable.Width(),rectToDisable.Height(),&dc,
		rectToDisable.left,rectToDisable.top,SRCCOPY);

	//Copy bitmap from screen to memory DC
	dcSrc.BitBlt(rectToDisable.left,rectToDisable.top,
		rectToDisable.Width(),rectToDisable.Height(),&dc,
		rectToDisable.left,rectToDisable.top,SRCCOPY);

	CBrush brushSrc;
	rectToDisable.DeflateRect(1,1);

	//Apply DSPxax ROP code to memory dc . As result black arrow become
	// of COLOR_3DSHADOW
	brushSrc.CreateSolidBrush(::GetSysColor(COLOR_3DSHADOW));
	dcSrc.SelectObject(&brushSrc);
	dcSrc.SetBkColor(RGB(255,255,255));
	dcSrc.SetTextColor(RGB(0,0,0));
	dcSrc.BitBlt(rectToDisable.left,rectToDisable.top,
		rectToDisable.Width(),rectToDisable.Height(),&memDC,
		rectToDisable.left,rectToDisable.top,0x00E20746L);

	//Apply DSPxax ROP code to screen dc and shift result one pixel left and bottom.
	//As result black arrow become shifted and of COLOR_3DLIGHT.
	brushMask.CreateSolidBrush(::GetSysColor(COLOR_3DHILIGHT));
	pOldBrush = dc.SelectObject(&brushMask);
	dc.SetBkColor(RGB(255,255,255));
	clrOldText=dc.SetTextColor(RGB(0,0,0));
	dc.BitBlt(rectToDisable.left+1,rectToDisable.top+1,
		rectToDisable.Width()-1,rectToDisable.Height()-1,&memDC,
		rectToDisable.left,rectToDisable.top,0x00E20746L);


	// Draw memory dc (dcSrc) transparently over device dc.
	//As result only arrow of color COLOR_3DSHADOW will be drawn over device dc
	//-------------------------------------------------------------------------

	//Create mask into memDC (the pixels which in dc were COLOR_BTNFACE
	//- become white in memDC,all others pixels in memDC become black)
	dcSrc.SetBkColor(GetSysColor(COLOR_BTNFACE));
	memDC.BitBlt(rectToDisable.left,rectToDisable.top,
		rectToDisable.Width(),rectToDisable.Height(),&dcSrc,
		rectToDisable.left,rectToDisable.top,SRCCOPY);

	dc.BitBlt(rectToDisable.left,rectToDisable.top,
		rectToDisable.Width(),rectToDisable.Height(),&dcSrc,
		rectToDisable.left,rectToDisable.top,SRCINVERT);

	dc.BitBlt(rectToDisable.left,rectToDisable.top,
		rectToDisable.Width(),rectToDisable.Height(),&memDC,
		rectToDisable.left,rectToDisable.top,SRCAND);
	dc.BitBlt(rectToDisable.left,rectToDisable.top,
		rectToDisable.Width(),rectToDisable.Height(),&dcSrc,
		rectToDisable.left,rectToDisable.top,SRCINVERT);
	//-------------------------------------------------------------------------

	//Restore resourses
	memDC.SelectObject(pBmpBeforeMask);
	dcSrc.SelectObject(pBmpBeforeSrc);

	dc.SetBkColor(clrOldBack);
	dc.SetTextColor(clrOldText);
	dc.SelectObject(pOldBrush);
}

void CLBSpinButtonCtrl::DrawPressedRect(CDC &dc, const CRect &rctToDown) const
{

	CRect 	rctDown=rctToDown;
	HPEN hOldPen;
	
		//Offset bitmap one pixel left and down
	
		dc.BitBlt(rctDown.left+1,rctDown.top+1,
		rctDown.Width()-1,rctDown.Height()-1,&dc,
		rctDown.left,rctDown.top,SRCCOPY);

		// Draw the border of pressed button
		rctDown.bottom-=1;

		hOldPen = (HPEN)SelectObject(dc.m_hDC,m_penShadow);
		dc.MoveTo(rctDown.left,rctDown.bottom-1);
		dc.LineTo(rctDown.left,rctDown.top);
		dc.LineTo(rctDown.right-1,rctDown.top);
		
		SelectObject(dc.m_hDC,m_penLight);
		dc.LineTo(rctDown.right-1,rctDown.bottom);
		dc.LineTo(rctDown.left-1,rctDown.bottom);


		SelectObject(dc.m_hDC,m_penDarkShadow);
		dc.MoveTo(rctDown.left+1,rctDown.bottom-2);
		dc.LineTo(rctDown.left+1,rctDown.top+1);
		dc.LineTo(rctDown.right-2,rctDown.top+1);

		SelectObject(dc.m_hDC,m_penLightShadow);
		dc.LineTo(rctDown.right-2,rctDown.bottom-1);
		dc.LineTo(rctDown.left,rctDown.bottom-1);

		SelectObject(dc.m_hDC,m_penButtonFace);
		dc.MoveTo(rctDown.left+2,rctDown.bottom-2);
		dc.LineTo(rctDown.left+2,rctDown.top+2);
		dc.LineTo(rctDown.right-2,rctDown.top+2);

		
		
		SelectObject(dc.m_hDC,hOldPen);


}

void CLBSpinButtonCtrl::Init()
{ 
	//We need to know m_hWndBuddy even if UDS_WRAP style applied, to fix bug
	// with possible incorrect Z-order of buddy/spin
	m_hWndBuddy=(HWND)::SendMessage(m_hWnd, UDM_GETBUDDY, 0, 0l);

	DWORD dwStyle=::GetWindowLong(m_hWnd,GWL_STYLE);
	if(dwStyle & UDS_WRAP)
		m_bAutoDisable=false; //if the UDS_WRAP style was applied, we can't disable arrows
	
	// The m_bAutoDisable can also  be set from outside using SetAutoDisable method;
	if(m_bAutoDisable) 
	{
		//Determine the orientation and alignment of this CLBSpinButtonCtrl
		if(dwStyle & UDS_ALIGNRIGHT )
			m_nSpinAlign=OnRightInside;
		else
		{
			if(dwStyle & UDS_ALIGNLEFT)
			{
				m_nSpinAlign=OnLeftInside;
			
			}
		}
		if(dwStyle & UDS_HORZ)
			m_bVertical=false;


		//Determine the control's limits and direction of increasing of it's position
		GetRange32(m_nMinPos,m_nMaxPos);	
		if( m_nMinPos < m_nMaxPos)
			m_bDefaultDirection =false;
		else
		{
			int nTemp = m_nMinPos;
			m_nMinPos = m_nMaxPos;
			m_nMaxPos=nTemp;
		}

		GetClientRect(&m_rctClient);

		m_nPrevPos = GetPos();

		//This is done special for up-down control which lives in CTabCtrl,
		//as so its initial value is out of range.
		if(m_nPrevPos < m_nMinPos || m_nPrevPos > m_nMaxPos)
			m_nPrevPos=m_nMinPos;

		//Determine the control's initial enable/disable state
		m_nSpinState = BothEnable;
		if(m_nPrevPos == m_nMinPos)
				m_nSpinState = DisableLeft;
		else
		{
			if(m_nPrevPos == m_nMaxPos)
				m_nSpinState = DisableRight;

		}

		if(::IsWindow(m_hWndBuddy))
		{
			char buf[5];
			::GetClassName(m_hWndBuddy,buf,sizeof(buf)/sizeof(buf[0]));
			
			if(!strcmp(buf,"Edit"))
			{
				//The class  of buddy is Edit
				m_bBuddyIsEdit=true;

				//I need to update the enabled/disabled state of CLBSpinButtonCtrl
				//when contents of buddy window is changing.
				//For instance, if user enters into buddy window the value greater
				//than upper possible limit - it is obvious that the increasing 
				//arrow should switch to disable state.
				//The best way to do it is to create WH_CALLWNDPROC hook 
				//and test within it if EN_UPDATE message came from buddy window
				//Another posibility- keyboard hook, but then the user can foolish 
				//the control, using clipboard Copy/Cut/Paste functions.
						
				//Test if WH_CALLWNDPROC hook already was installed.
				// If no, set up it.
				if(ghHook==NULL)
					ghHook=SetWindowsHookEx(WH_CALLWNDPROC,FilterBuddyMsgProc,NULL, //WH_GETMESSAGE
											GetCurrentThreadId());
				//As so I use a single WH_CALLWNDPROC hook for all existing in
				//an application CLBSpinButtonCtrl controls, I need to distinguish
				// between these controls in the static FilterBuddyMsgProc.
				//For this purpose I use static std:map<HWND,HWND> gHandleMap
				
				//Try to find m_hWndBuddy in the gHandleMap
				HWNDMAP::iterator iterHwnd=gHandleMap.find(m_hWndBuddy);
				if(iterHwnd != gHandleMap.end())
				{
					if((*iterHwnd).second != m_hWnd)
					{
						//If in the gHandleMap already defined  another CLBSpinButtonCtrl
						//for that buddy (m_hWndBuddy), then redefine it .
						gHandleMap.erase(iterHwnd);	
						gHandleMap.insert(HWNDMAP::value_type(m_hWndBuddy,m_hWnd));
					}
				}
				else
					//If the CLBSpinButtonCtrl assosiated with
					//m_hWndBuddy is not found in the gHandleMap, then add it.
					gHandleMap.insert(HWNDMAP::value_type(m_hWndBuddy,m_hWnd));
			}
		}
		Invalidate(FALSE);
	}
}

BOOL CLBSpinButtonCtrl::OnDeltapos(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_bAutoDisable)
	{
		NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

		int nNextPos=pNMUpDown->iPos+pNMUpDown->iDelta;

		//Determine the enable/disable state of CLBSpinButtonCtrl
		if(nNextPos > m_nMaxPos)
			nNextPos = m_nMaxPos;
		else
		{
			if(nNextPos < m_nMinPos)
				nNextPos = m_nMinPos;
		}
	
		if(m_nPrevPos!=nNextPos)
		{
			if(pNMUpDown->iDelta)
				m_bActiveSpinPressed=true;

			if(nNextPos  <m_nMaxPos && nNextPos >m_nMinPos)
			{
				m_nSpinState = BothEnable;
			}
			else
			{
				if(nNextPos == m_nMaxPos)
				{
					if(m_nMaxPos != m_nMinPos)
					{
						m_nSpinState=DisableRight;
						m_bActiveSpinPressed=false;
					}
					else
					{
						m_nSpinState = BothDisable;
						m_bActiveSpinPressed=false;
					}
				}
				else
				{
					if(nNextPos == m_nMinPos)
					{
						m_nSpinState=DisableLeft;
						m_bActiveSpinPressed=false;
					}
				}
			}
			m_nPrevPos=nNextPos;
			Invalidate(FALSE);

			//Let the Windows process UDN_DELTAPOS too
			*pResult = 0;
			return FALSE;
		}
		else
		{
			//If the next position of control is the same as current,
			//what can happen when user clicked the disable arrow,
			//then eat UDN_DELTAPOS
			*pResult = 1;
			return TRUE;
		}
	}
	else
	{ 
		//Let the Windows process UDN_DELTAPOS
		*pResult = 0;
		return FALSE;
	}
}


LRESULT CLBSpinButtonCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	//Let the Windows do it's work 
	LRESULT nRet = CSpinButtonCtrl::WindowProc(message, wParam, lParam);

	switch(message)
	{
		case UDM_SETRANGE32:
		case UDM_SETRANGE: 
							//Need to reinit CLBSpinButtonCtrl, as so the
							//limits probably changed
							Init();
							break;


		case UDM_SETBUDDY :
							//Need to reinit CLBSpinButtonCtrl, as so the
							//buddy changed
							CleanUpHook();
							Init();
							//If buddy window(m_hWndBuddy) is placed after this 
							//CLBSpinButtonCtrl in Z-order , then m_hWndBuddywindow will 
							//get WM_PAINT message after  this CLBSpinButtonCtrl control 
							//and in case CLBSpinButtonCtrl is attached to buddy,
							// it will be overpainted by buddy's border
							//This undocumented bug persist for CSpinButtonCtrl as well.
							//
							//To reproduce it create on dialog template attached
							//CSpinButtonCtrl control and CEdit control and make
							//tab order so, that for CSpinButtonCtrl tab position 
							//was less then for CEdit;
							//Then in OnInitDiaolg call SetBuddy(pointerToEdit) function 
							//of CSpinButtonCtrl.
							//
							//
							//To work around this simply place CSpinButtonCtrl
							//after it's buddy in Z-order. 
							if(::IsWindow(m_hWndBuddy))
								::SetWindowPos(m_hWnd,m_hWndBuddy,0,0,0,0,
									           SWP_NOMOVE|SWP_NOSIZE);

							break;
	}
	return nRet;

}

void CLBSpinButtonCtrl::CleanUpHook() const
{
	if(m_bBuddyIsEdit)
	{
		//If the buddy is edit, then try to find out if
		//it was added to gHandleMap.
		HWNDMAP::iterator iterHwnd=gHandleMap.find(m_hWndBuddy);
		if(iterHwnd != gHandleMap.end() && (*iterHwnd).second == m_hWnd)
		{
			//If m_hWndBuddy found and is assosiated with current window,
			//then delete it from gHandleMap.
			iterHwnd = gHandleMap.erase(iterHwnd);
			if(!gHandleMap.size() && ghHook!=NULL)
			{
				//If just deleted from the gHandleMap m_hWndBuddy was
				//the last for current application,
				//then remove a hook procedure. 
				UnhookWindowsHookEx( ghHook);
				ghHook=NULL;
			}
		}
	}
}

void CLBSpinButtonCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_rctIsPressed.SetRectEmpty();
	CSpinButtonCtrl::OnLButtonDown(nFlags, point);
}

BOOL CLBSpinButtonCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE	; //Get rid of flickering

}

void CLBSpinButtonCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	Invalidate();	
	UpdateWindow();
	CSpinButtonCtrl::OnLButtonUp(nFlags, point);
}

bool CLBSpinButtonCtrl::SetAutoDisable(bool bSetOn)
{
	// User should have an opportunity to swith on/off the custom
	//behavior of  the CLBSpinButtonCtrl control.
	
	bool bPrev = m_bAutoDisable;
	m_bAutoDisable = bSetOn;
	Init();

	return bPrev;
}

LRESULT CALLBACK FilterBuddyMsgProc(  int code,  WPARAM wParam,  LPARAM lParam )
{
	CWPSTRUCT* pData=reinterpret_cast<CWPSTRUCT*>(lParam);
	if(WM_COMMAND==pData->message && EN_UPDATE==HIWORD(pData->wParam))
	{
		//If the incoming message is EN_UPDATE
		HWNDMAP::iterator iterHwnd=gHandleMap.find(reinterpret_cast<HWND>(pData->lParam));
		if(iterHwnd != gHandleMap.end())
		{
			//The incoming EN_UPDATE message has been sent
			//to the edit control, defined in the gHandleMap.

			//So get the value, entered into the edit control
			//and send it to the CLBSpinButtonCtrl, assosiated
			//with the edit control.
			CString strText;
			int nLen=::GetWindowTextLength((*iterHwnd).first);
			::GetWindowText((*iterHwnd).first,strText.GetBufferSetLength(nLen),nLen+1);
			strText.ReleaseBuffer();

			//In case UDS_NOTHOUSANDS style not applied
			//we have to delete thousands delimiter from string
			strText.Remove((TCHAR)0xA0);

			NMUPDOWN nmUpDn;
			nmUpDn.iDelta=0;
			nmUpDn.iPos=atoi(strText);
			nmUpDn.hdr.code=UDN_DELTAPOS;
			nmUpDn.hdr.hwndFrom=(*iterHwnd).second;
			nmUpDn.hdr.idFrom=::GetDlgCtrlID((*iterHwnd).second);

			///HWND hWndSpinParent=::GetParent((*iterHwnd).second);!!! watermark
			::SendMessage(::GetParent((*iterHwnd).second),
							WM_NOTIFY,(WPARAM)nmUpDn.hdr.idFrom,
							(LPARAM)&nmUpDn);
		}
	}
	return CallNextHookEx(ghHook,code,wParam,lParam);
}

void CLBSpinButtonCtrl::OnDestroy() 
{
	//Remove current CLBSpinButtonCtrl control from the gHandleMap and
	//if it is the last control, defined in the gHandleMap
	//then remove a hook procedure. 
	CleanUpHook();

	CSpinButtonCtrl::OnDestroy();
}
