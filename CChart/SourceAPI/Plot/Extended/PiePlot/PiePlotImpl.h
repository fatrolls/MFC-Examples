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

#ifndef __PIEPLOTIMPL_H_122333444455555__
#define __PIEPLOTIMPL_H_122333444455555__

#include "../../Basics/XYPlotImpl.h"
#include "../../Basics/XYHandler.h"
#include "PiePlot.h"

class	CPiePlotImpl : public CPiePlot, public CXYPlotImpl
{
public:
	CPiePlotImpl();
	virtual ~CPiePlotImpl();
public:
	POINT	m_ptOrigin,m_ptCurr;
	SIZE	m_sizeOffsetOrigin;

public:
	void	Reset();
	int		AddPie(double value);
	int		AddPie(double value, COLORREF color, string title, double scale);

	void	GetPlotRange( double *xRange, double *yRange );
public:
	void	OnDraw( HWND hWnd );
	void	OnDraw( HDC hDC, RECT destRect );

	int		GetNeareastDataSet( HDC hDC, POINT point );

	bool	IsPieDragMode(int dataID) { int i = GetIndex(dataID); if(i<0)return false; return m_vXYDataInfo[i].bSpecialFlag;  }
	bool	IsPieDragMode(){ for(int i=0; i<GetDataSetCount(); i++)if(m_vXYDataInfo[i].bSpecialFlag)return true; return false; }
	int		GetPieDragMode(){ for(int i=0; i<GetDataSetCount(); i++)if(m_vXYDataInfo[i].bSpecialFlag)return i; return -1; }
	void	SetPieDragMode(int dataID, bool drag) { int i = GetIndex(dataID); if(i<0)return; m_vXYDataInfo[i].bSpecialFlag = drag;  }
	void	UnsetPieDragMode() { for(int i=0; i<GetDataSetCount(); i++)m_vXYDataInfo[i].bSpecialFlag = false; }

public:
	void	DrawPies( HDC hDC, RECT	plotRect );

	RECT	GetPieTitleRect( HDC hDC, RECT plotRect, int which, double ctx, double cty, double a1, double b1, double curr, double ratio, int &fontheight );
	RECT	GetPieTitleRect( HDC hDC, RECT plotRect, int which );

	bool	PtInPieArea( HDC hDC, POINT point, RECT plotRect );
	bool	PtInPieArea( int which, HDC hDC, POINT point, RECT plotRect, bool withTitle );
	bool	PtInPieArea( int which, HDC hDC, POINT point, RECT plotRect, bool withTitle, double ctx, double cty, double a1, double b1, double curr, double ratio);
	bool	PtInPieTitleArea(  int which, HDC hDC, POINT point, RECT plotRect );
	HRGN	GetPieRegion( int which, HDC hDC, RECT plotRect, double ctx, double cty, double a1, double b1, double curr, double ratio );

	bool	GetFreqPara( RECT plotRect, double &ctx, double &cty, double &a, double &b, double &total );
	bool	GetFreqPara( RECT plotRect, int which, double &ctx, double &cty, double &a, double &b, double &a1, double &b1, double &curr, double &ratio, double &total );
};

template<typename CPiePlotImpl>
class CPieHandler : public CXYHandler<CPiePlotImpl>
{
public:
	virtual	bool		OnMouseDown( HWND hWnd, POINT point );
	virtual	bool		OnMouseUp( HWND hWnd, POINT point );
//	virtual	bool		OnMouseDblClk( HWND hWnd, POINT point );
	virtual	bool		OnMouseMove( HWND hWnd, POINT point );
//	virtual	bool		OnContextMenu( HMENU hMenu, HWND hWnd, POINT point );
	
//	virtual	void		Interactive(HWND hWnd, UINT message, POINT point);
//	virtual	void		Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

class CPiePlotImplI : public CPiePlotImpl, public CPieHandler<CPiePlotImplI>
{

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

template<typename CPiePlotImpl>
bool	CPieHandler<CPiePlotImpl>::OnMouseDown( HWND hWnd, POINT point )
{
	CPiePlotImpl *pT=static_cast<CPiePlotImpl*>(this);

	HDC hDC = GetDC( hWnd );
	int i;
	
	// Capture
	SetCapture(hWnd);
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	ClientToScreen(hWnd,(LPPOINT)&clientRect);
	ClientToScreen(hWnd,(LPPOINT)&clientRect+1);
	ClipCursor(&clientRect);
	// End
	
	RECT plotRect = pT->GetPlotRect(hDC, pT->GetLastClientRect());
	RECT PieTitleRect;
	for(i=0; i<pT->GetDataSetCount(); i++ )
	{
		PieTitleRect = pT->GetPieTitleRect( hDC, plotRect, i );
		if( PtInRect( &PieTitleRect, point ) )
		{
			// Select
			if(!pT->IsMultiSelect() && pT->IsSelected(pT->GetDataID(i)))
			{
				pT->SelectAllDataSets(false);
			}
			else
			{
				pT->SetSelected(pT->GetDataID(i), !pT->IsSelected(pT->GetDataID(i)));
			}
			
			// drag
			pT->UnsetPieDragMode();
			
			pT->SetPieDragMode(pT->GetDataID(i), true);
			pT->m_ptOrigin = pT->m_ptCurr = point;
			pT->m_sizeOffsetOrigin = pT->GetXYDataInfo()[i].sizeTitleOffset;
			
			ReleaseDC(hWnd, hDC);
			return true;
		}
	}
	
	if(pT->PtInPieArea(hDC, point, plotRect))
	{
		pT->SetDragMode(true);
		
		pT->m_ptOrigin = pT->m_ptCurr = point;
		pT->m_sizeOffsetOrigin = pT->m_sizeOffset;
	}
	
	ReleaseDC(hWnd, hDC);
	//return	true;
	return	CXYHandler<CPiePlotImpl>::OnMouseDown(hWnd, point);
}

template<typename CPiePlotImpl>
bool	CPieHandler<CPiePlotImpl>::OnMouseUp( HWND hWnd, POINT point )
{
	CPiePlotImpl *pT=static_cast<CPiePlotImpl*>(this);

	pT->SetDragMode(false);
	pT->UnsetPieDragMode();
	if(GetCapture())ReleaseCapture();
	ClipCursor(NULL);
	
	//return true;
	return	CXYHandler<CPiePlotImpl>::OnMouseUp(hWnd, point);
}

template<typename CPiePlotImpl>
bool	CPieHandler<CPiePlotImpl>::OnMouseMove( HWND hWnd, POINT point )
{
	CPiePlotImpl *pT=static_cast<CPiePlotImpl*>(this);

	int title_idx = pT->GetPieDragMode();
	if(title_idx >= 0)
	{
		pT->m_ptCurr = point;
		
		SIZE offset = pT->m_sizeOffsetOrigin;
		offset.cx+=(pT->m_ptCurr.x-pT->m_ptOrigin.x);
		offset.cy+=(pT->m_ptCurr.y-pT->m_ptOrigin.y);
		pT->GetXYDataInfo()[title_idx].sizeTitleOffset = offset;
		
		return true;
	}
	
	if(pT->IsDragMode())
	{
		pT->m_ptCurr = point;
		
		SIZE offset = pT->m_sizeOffsetOrigin;
		offset.cx+=(pT->m_ptCurr.x-pT->m_ptOrigin.x);
		offset.cy+=(pT->m_ptCurr.y-pT->m_ptOrigin.y);
		pT->m_sizeOffset = offset;
		
		return true;
	}
	
	//return true;
	return CXYHandler<CPiePlotImpl>::OnMouseMove(hWnd, point);
}

#endif




















