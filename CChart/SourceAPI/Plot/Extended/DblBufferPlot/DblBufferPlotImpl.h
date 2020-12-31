/*============================================================================*/
/*                                                                            */
/*                            C O P Y R I G H T                               */
/*                                                                            */
/*                          (C) Copyright 2011 by                             */
/*                              Yang Guojun                                   */
/*                           All Rights Reserved                              */
/*                                                                            */
/*      The author assumes no responsibility for the use or reliability of    */
/*      his software.                                                         */
/*                                                                            */
/*============================================================================*/

/* ############################################################################################################################## */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is a templated class 

#ifndef __DBLBUFFERPLOTIMPL_H_122333444455555__
#define __DBLBUFFERPLOTIMPL_H_122333444455555__

#include "DblBufferPlot.h"
#include "../../Basics/XYHandler.h"

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

template <typename XYPlotImplT>
class CDblBufferPlotImpl : public CDblBufferPlot, public XYPlotImplT
{
public:
	CDblBufferPlotImpl(){m_hWnd=0;}
	CDblBufferPlotImpl(HWND hWnd):m_hWnd(hWnd){CreateVirtualWindow();}
	virtual ~CDblBufferPlotImpl(){ReleaseVirtualWindow();}
	void SetWindow(HWND hWnd){ReleaseVirtualWindow();m_hWnd = hWnd;CreateVirtualWindow();}
public:
	void OnDraw(HWND hWnd)
	{
		if(m_hWnd==0)
		{
			m_hWnd=hWnd;
			CreateVirtualWindow();
		}
		if (m_bUpdate)OnUpdate();
		
		HDC hDC = GetDC(m_hWnd);
		StretchBlt(hDC, 0, 0, m_maxX, m_maxY, m_hMemDC, 0, 0, m_maxX, m_maxY, SRCCOPY);
		ReleaseDC(m_hWnd, hDC);
	}
	void OnUpdate()
	{
		HDC hDC = m_hMemDC;
		RECT destRect;
		GetClientRect(m_hWnd, &destRect);
		
		if (XYPlotImplT::GetDataSetCount() <= 0)
		{
			XYPlotImplT::EraseBkgnd(hDC, destRect);
			return;
		}
		SetLastClientRect(destRect);
		
		XYPlotImplT::OnDraw(hDC, destRect);
		m_bUpdate = false;
	}
};

//Since the CHandler can not be used as a templated class, here c-style define is used like MFC
#define Declare_CDblBufferPlotImplI( CDblBufferPlotImplI, XYPlotImplT, CHandlerT ) \
\
	template < typename XYPlotImplT > \
	class CDblBufferPlotImplI : public CDblBufferPlotImpl< XYPlotImplT >, public CHandlerT< CDblBufferPlotImplI<XYPlotImplT> > \
	{ \
	public:\
		CDblBufferPlotImplI(){}\
		CDblBufferPlotImplI(HWND hWnd){m_hWnd = hWnd;CreateVirtualWindow();}\
		virtual ~CDblBufferPlotImplI(){}\
	public:\
		bool OnMouseDown(HWND hWnd, POINT point){return m_bUpdate = CHandlerT<CDblBufferPlotImplI>::OnMouseDown(hWnd, point);}\
		bool OnMouseUp(HWND hWnd, POINT point){return m_bUpdate = CHandlerT<CDblBufferPlotImplI>::OnMouseUp(hWnd, point);}\
		bool OnMouseDblClk(HWND hWnd, POINT point){return m_bUpdate = CHandlerT<CDblBufferPlotImplI>::OnMouseDblClk(hWnd, point);}\
		bool OnMouseMove(HWND hWnd, POINT point){return m_bUpdate = CHandlerT<CDblBufferPlotImplI>::OnMouseMove(hWnd, point);}\
		bool OnContextMenu( HMENU hMenu, HWND hWnd, POINT point ){return m_bUpdate = CHandlerT<CDblBufferPlotImplI>::OnContextMenu(hMenu, hWnd, point);}\
		void Interactive(HWND hWnd, UINT message, POINT point)\
		{\
			switch(message)\
			{\
			case WM_LBUTTONDOWN:	if(OnMouseDown(hWnd,point))OnDraw(hWnd);break;\
			case WM_LBUTTONUP:		if(OnMouseUp(hWnd,point))OnDraw(hWnd);break;\
			case WM_LBUTTONDBLCLK:	if(OnMouseDblClk(hWnd,point))OnDraw(hWnd);break;\
			case WM_MOUSEMOVE:		if(OnMouseMove(hWnd,point))OnDraw(hWnd);break;\
			case WM_CONTEXTMENU:	if(OnContextMenu(NULL, hWnd, point))OnDraw(hWnd);break;\
			case WM_SIZE:			m_bUpdate = true;OnDraw(hWnd);break;\
			case WM_ERASEBKGND:		return;\
			default:				return;\
			}\
		}\
		void Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)\
		{\
			POINT	point;\
			point.x = LOWORD(lParam);\
			point.y = HIWORD(lParam);\
			Interactive(hWnd, message, point);\
		}\
	};\
\

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#endif