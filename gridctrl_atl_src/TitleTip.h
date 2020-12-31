// TitleTip.h: interface for the CTitleTip class.
//
//////////////////////////////////////////////////////////////////////
// Written by Mario Zucca 
//        mailto:mario@GenoaValley.org
//        http://www.GenoaValley.org
//
// Copyright (c) 2000.
//
// The code contained in this file is based on the original
// Grid control written by Chris Maunder,
//        mailto:chris@codeproject.com
//        http://www.codeproject.com

#if !defined(AFX_TITLETIP_H__16CEF8F6_CB28_11D3_9950_006097FEBF00__INCLUDED_)
#define AFX_TITLETIP_H__16CEF8F6_CB28_11D3_9950_006097FEBF00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTitleTip : public CWindowImpl<CTitleTip>  
{
public:
//	DECLARE_WND_CLASS_EX( "ZTitleTip", CS_SAVEBITS, (COLOR_INFOBK + 1) )
   DECLARE_WND_CLASS("ZTitleTip") 

	CWindow m_pParentWnd;
	void Hide();
	void Show(RECT rectTitle, LPCTSTR lpszTitleText, int xoffset =0, LPRECT lpHoverRect =NULL, LPLOGFONT lpLogFont =NULL);
	RECT m_rectTitle;
    RECT m_rectHover;
	BOOL Create(HWND hwnd);
	CTitleTip();
	virtual ~CTitleTip();
   BEGIN_MSG_MAP(CTitleTip)
      MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
      MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
      MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
   END_MSG_MAP()

   LRESULT OnMouseMove(UINT nMsg, WPARAM wParam, 
                   LPARAM lParam, BOOL& bHandled)
   {
//	   return DefWindowProc();
		POINT point;
		UINT nFlags = (UINT) wParam;
		point.x = (short) LOWORD(lParam); 
		point.y = (short) HIWORD(lParam); 
		RECT rect;
		GetClientRect(&rect);
		rect.bottom += 2;
		rect.right += 2;
		if (PtInRect(&rect,point)==0) 
		{
			Hide();
    
			// Forward the message
			ClientToScreen( &point );
			HWND hWnd;
			hWnd = WindowFromPoint( point );
			if ( hWnd == m_hWnd ) 
				hWnd = m_pParentWnd.m_hWnd;
    
			int hittest = (int)SendMessage(hWnd,WM_NCHITTEST,0,MAKELONG(point.x,point.y));
    
			if (hittest == HTCLIENT)
			{
				::ScreenToClient(hWnd, &point );
				::PostMessage(hWnd, WM_MOUSEMOVE, nFlags, MAKELONG(point.x,point.y) );
			} 
			else 
			{
				::PostMessage(hWnd, WM_NCMOUSEMOVE, hittest, MAKELONG(point.x,point.y) );
			}
		}
		return TRUE;
   }

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		Hide();
		return 0;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
};

#endif // !defined(AFX_TITLETIP_H__16CEF8F6_CB28_11D3_9950_006097FEBF00__INCLUDED_)
