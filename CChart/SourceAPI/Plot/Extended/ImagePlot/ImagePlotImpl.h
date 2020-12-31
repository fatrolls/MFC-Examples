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

#ifndef __IMAGEPLOTIMPL_H_122333444455555__
#define __IMAGEPLOTIMPL_H_122333444455555__

#include "../../Basics/PlotImpl.h"
#include "../../Basics/XYHandler.h"
#include "ImagePlot.h"
#include "ImageLegendImpl.h"

// usage step by step
// SetFieldFcn(double f(double, double));
// SetRanges(double x[2], double y[2]);
// CreateMemDC(HWND);
// CreateImage();

class CImagePlotImpl: public CImagePlot, public CPlotImpl
{
public:
	CImagePlotImpl();
	virtual ~CImagePlotImpl();

	void		OnDraw( HWND hWnd );
	void		OnDraw(HDC hDC, RECT clientRect);
public:
	virtual	int	GetDataSetCount( void ) { return ((CImageLegendImpl *)m_pLegend)->GetLegends(); }
	string		GetAbsoluteDataTitle( int which );
	inline	void	SetXRange( double low, double high ) {m_fXRange[0] = low; m_fXRange[1] = high; CPlot::SetXRange(low, high);}
	inline	void	SetYRange( double low, double high ) {m_fYRange[0] = low; m_fYRange[1] = high; CPlot::SetYRange(low, high);}
	inline	bool	IsEmpty(){return m_pFieldFcn==0;}

private:
	CLegend		*NewLegend(){CImageLegendImpl *pLegend = new CImageLegendImpl(this); return pLegend;}
	void		GetPlotRange( double *xRange, double *yRange );
};

template<typename ImagePlotImplT>
class CImageHandler : public CHandler<ImagePlotImplT>
{
public:
	bool		OnMouseDown( HWND hWnd, POINT point );
	bool		OnMouseUp( HWND hWnd, POINT point );
	bool		OnMouseDblClk( HWND hWnd, POINT point );
	bool		OnMouseMove( HWND hWnd, POINT point );
	bool		OnContextMenu( HMENU hMenu, HWND hWnd, POINT point );
	void		Interactive(HWND hWnd, UINT message, POINT point);
	void		Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

class CImagePlotImplI : public CImagePlotImpl, public CImageHandler<CImagePlotImplI>
{
};

///////////////////////////////////////////////////////////////////////////////////
//

template<typename ImagePlotImplT>
bool	CImageHandler<ImagePlotImplT>::OnMouseDown( HWND hWnd, POINT point )
{
	ImagePlotImplT *pT=static_cast<ImagePlotImplT *>(this);
	if(pT->IsEmpty()) return false;
	
	HDC hDC = GetDC( hWnd );

	// Capture
	SetCapture(hWnd);
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	ClientToScreen(hWnd,(LPPOINT)&clientRect);
	ClientToScreen(hWnd,(LPPOINT)&clientRect+1);
	ClipCursor(&clientRect);
	// end

	bool needUpdate = false;
	
	DPtoLP( hDC, &point,1);
	
	//Set Drag mode
	int which = ((CLegendImpl *)(pT->GetLegend()))->RegionIdentify(hDC,point);
	if(which>=0)
	{
		pT->GetLegend()->SetDragMode(true,point);

		ReleaseDC(hWnd, hDC);
		return true;
	}
	
	ReleaseDC(hWnd, hDC);
	return false;
}

template<typename ImagePlotImplT>
bool	CImageHandler<ImagePlotImplT>::OnMouseUp( HWND hWnd, POINT point )
{
	ImagePlotImplT *pT=static_cast<ImagePlotImplT *>(this);
	if(pT->GetLegend()->IsDragMode())pT->GetLegend()->SetDragMode(false,point);
	if(GetCapture())ReleaseCapture();
	ClipCursor(NULL);

	return false;
}

template<typename ImagePlotImplT>
bool	CImageHandler<ImagePlotImplT>::OnMouseDblClk( HWND hWnd, POINT point )
{
	return false;
}

template<typename ImagePlotImplT>
bool	CImageHandler<ImagePlotImplT>::OnMouseMove( HWND hWnd, POINT point )
{
	ImagePlotImplT *pT=static_cast<ImagePlotImplT *>(this);
	if(pT->IsEmpty()) return false;

	HDC hDC = GetDC( hWnd );

	static int loc0=-1;
	static bool light_title0=false;
	static bool light_dataregion0=false;

	bool needUpdate = false;

	if(pT->IsEmpty()) goto mousemove_return;
	
	DPtoLP( hDC, &point,1);

	if(pT->GetLegend()->IsDragMode())
	{
		pT->GetLegend()->SetCurrentPoint(point);
		needUpdate = true;
		goto mousemove_return;
	}

	int which;

	CAxis *axis;
	int location;
	bool light_title,light_dataregion;
	int region;
	region=pT->RegionIdentify(hDC,point);
	switch(region)
	{
	case kXYRegionData:
		if(pT->AxisLighted())
		{
			pT->UnlightAllAxis();
			if(loc0>=0)
			{
				needUpdate = true;
			}
			loc0=-1;
		}
		//如果处于legend区域
		which=((CLegendImpl *)(pT->GetLegend()))->RegionIdentify(hDC,point);
		if(which>=0)
		{
			pT->GetLegend()->SetCurrent(true);
		}
		else
		{
			pT->GetLegend()->SetCurrent(false);
		}
		break;
	
	case kXYRegionBottom:
		location=kLocationBottom;
		goto LightAxis;
	case kXYRegionTop:
		location=kLocationTop;
		goto LightAxis;
	case kXYRegionLeft:
		location=kLocationLeft;
		goto LightAxis;
	case kXYRegionRight:
		location=kLocationRight;
LightAxis:
		axis=pT->GetAxisByLocation(location);
		if(axis)
		{
			pT->UnlightAllAxis();
			axis->SetCurrent(true);
			if(location!=loc0)
			{
				needUpdate = true;
			}
			loc0=location;
		}
		break;
	default:
		// unlignt axis
		if(pT->AxisLighted())
		{
			pT->UnlightAllAxis();
			if(loc0>=0)
			{
				needUpdate = true;
			}
			loc0=-1;
		}
		break;
	}

	if(region == kXYRegionTitle)
	{		
		light_title=true;
		if(light_title != light_title0)
		{
			pT->SetLightTitle(true);
			needUpdate = true;
		}
		light_title0=light_title;
	}
	else
	{
		// unlight title
		if(pT->IsLightTitle())
		{
			pT->SetLightTitle(false);
			if(light_title0)
			{
				needUpdate = true;
			}
			light_title0=false;
		}
	}

	if(region == kXYRegionData)
	{		
		light_dataregion=true;
		if(light_dataregion != light_dataregion0)
		{
			pT->SetLightDataRegion(true);
			needUpdate = true;
		}
		light_dataregion0=light_dataregion;
	}
	else
	{
		// unlight data region
		if(pT->IsLightDataRegion())
		{
			pT->SetLightDataRegion(false);
			if(light_dataregion0)
			{
				needUpdate = true;
			}
			light_dataregion0=false;
		}
	}

mousemove_return:
	ReleaseDC(hWnd,hDC);
	return needUpdate;
}

template<typename ImagePlotImplT>
bool	CImageHandler<ImagePlotImplT>::OnContextMenu(HMENU hMenu, HWND hWnd, POINT point  )
{
	return false;
}

template<typename ImagePlotImplT>
void	CImageHandler<ImagePlotImplT>::Interactive(HWND hWnd, UINT message, POINT point)
{
	ImagePlotImplT *pT=static_cast<ImagePlotImplT*>(this);
	
	switch(message)
	{
	case WM_LBUTTONDOWN:
		if(OnMouseDown(hWnd,point))pT->OnDraw(hWnd);
		break;
	case WM_LBUTTONUP:
		if(OnMouseUp(hWnd,point))pT->OnDraw(hWnd);
		break;
	case WM_LBUTTONDBLCLK:
		if(OnMouseDblClk(hWnd,point))pT->OnDraw(hWnd);
		break;
	case WM_MOUSEMOVE:
		if(OnMouseMove(hWnd,point))pT->OnDraw(hWnd);
		break;
	case WM_CONTEXTMENU:
		if(OnContextMenu(NULL, hWnd, point))pT->OnDraw(hWnd);
		break;
	case WM_SIZE:
		pT->OnDraw(hWnd);
	case WM_ERASEBKGND:
	default:
		return;
	}
}

template<typename ImagePlotImplT>
void	CImageHandler<ImagePlotImplT>::Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ImagePlotImplT *pT=static_cast<ImagePlotImplT*>(this);
	POINT	point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	Interactive(hWnd, message, point);
}

#endif