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

#ifndef __XYHANDLER_H_122333444455555__
#define __XYHANDLER_H_122333444455555__

//#include "XYPlotImpl.h"
#include "LegendImpl.h"
#include "AxisImpl.h"
#include "PlotUtility.h"
#include "DefHandlers/DefHandlers.h"
#include "DefHandlers/ColorControl.h"

typedef bool	(FcnDataSettings)( CXYPlotImpl *plot, HWND hWnd, int whichDataSet );
typedef bool	(FcnAxisSettings)( CXYPlotImpl *plot, HWND hWnd, int location );
typedef bool	(FcnPlotSettings)( CXYPlotImpl *plot, HWND hWnd );
typedef int		(FcnShowPopupMenu)( CXYPlotImpl *plot, HMENU hMenu, HWND hWnd, POINT point );

//The base class for handlers, do nothing here
template <typename PlotImplT>
class CHandler
{
public:
	CHandler(){};
	virtual ~CHandler(){};
public:
	virtual bool		OnMouseDown( HWND hWnd, POINT point )=0;
	virtual bool		OnMouseUp( HWND hWnd, POINT point )=0;
	virtual bool		OnMouseDblClk( HWND hWnd, POINT point )=0;
	virtual bool		OnMouseMove( HWND hWnd, POINT point )=0;
	virtual bool		OnContextMenu( HMENU hMenu, HWND hWnd, POINT point )=0;
	
	virtual void		Interactive(HWND hWnd, UINT message, POINT point)=0;
	virtual void		Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)=0;
};

//The handler class for XYPlotImpl and its children classes
template <typename XYPlotImplT>
class CXYHandler : public CHandler<XYPlotImplT>
{
public:
	CXYHandler();
	virtual ~CXYHandler();

	FcnDataSettings		*m_pFcnDS;
	FcnAxisSettings		*m_pFcnAS;
	FcnPlotSettings		*m_pFcnPS;
	FcnShowPopupMenu	*m_pFcnPM;

public:

	virtual	bool		OnMouseDown( HWND hWnd, POINT point );
	virtual	bool		OnMouseUp( HWND hWnd, POINT point );
	virtual	bool		OnMouseDblClk( HWND hWnd, POINT point );
	virtual	bool		OnMouseMove( HWND hWnd, POINT point );
	virtual	bool		OnContextMenu( HMENU hMenu, HWND hWnd, POINT point );

	virtual	void		Interactive(HWND hWnd, UINT message, POINT point);
	virtual	void		Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	inline	void		SetFcnPlotSettings( FcnPlotSettings fcn ){ m_pFcnPS = fcn; }
	inline	void		SetFcnAxisSettings( FcnAxisSettings fcn ){ m_pFcnAS = fcn; }
	inline	void		SetFcnDataSettings( FcnDataSettings fcn ){ m_pFcnDS = fcn; }
	inline	void		SetFcnShowPopupMenu( FcnShowPopupMenu fcn ){ m_pFcnPM = fcn; }

/*	
	inline	bool		IsNewInteractive(){return m_bNewInteractive;}
	inline	void		SetNewInteractive(bool ni){m_bNewInteractive = ni;}

private:
	bool				m_bNewInteractive;
*/
};

template <typename XYPlotImplT>
CXYHandler<XYPlotImplT>::CXYHandler()
{
	m_pFcnDS = DefDataSettings;
	m_pFcnAS = DefAxisSettings;
	m_pFcnPS = DefPlotSettings;
	m_pFcnPM = DefContextMenu;

	//m_bRedraw = false;
}

template <typename XYPlotImplT>
CXYHandler<XYPlotImplT>::~CXYHandler()
{
	
}

template <typename XYPlotImplT>
bool	CXYHandler<XYPlotImplT>::OnMouseDown( HWND hWnd, POINT point )
{
	XYPlotImplT *pT=static_cast<XYPlotImplT*>(this);

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

	static int curve_id0=-1;
	bool needUpdate = false;
	
	DPtoLP( hDC, &point,1);
	
	//Set Drag mode
	int curve_id, which = ((CLegendImpl *)pT->GetLegend())->RegionIdentify(hDC,point);
	if(which>=0)
	{
		pT->GetLegend()->SetDragMode(true,point);
		if(which == pT->GetDataSetCount())goto UnselectCurve;//in drag region
		pT->SetSelected(pT->GetDataID(which),!pT->IsSelected(pT->GetDataID(which)));
		curve_id=pT->GetDataID(which);
		goto SelectCurve;
	}
	int region;
	region=pT->RegionIdentify(hDC,point);
	switch(region)
	{
	case kXYRegionData:
		curve_id=pT->SelectByPoint(hDC,point);
SelectCurve:
		if(curve_id>=0 && curve_id != curve_id0)
		{
			curve_id0 = curve_id0;
			needUpdate = true;
		}
		else
		{
			goto UnselectCurve;
		}
		break;
	default:
UnselectCurve:
		pT->SelectAllDataSets(false);
		needUpdate = true;
	}
	
//lbuttondown_return:
	ReleaseDC(hWnd,hDC);

	//if(m_bRedraw && needUpdate)pT->OnDraw(hWnd);
	return needUpdate;
}

template <typename XYPlotImplT>
bool	CXYHandler<XYPlotImplT>::OnMouseUp( HWND hWnd, POINT point )
{
	XYPlotImplT *pT=static_cast<XYPlotImplT*>(this);

	if(pT->GetLegend()->IsDragMode())pT->GetLegend()->SetDragMode(false,point);
	if(GetCapture())ReleaseCapture();
	ClipCursor(NULL);
	//SendMessage(hWnd,WM_PAINT,0,0);

	return false;
}

template <typename XYPlotImplT>
bool	CXYHandler<XYPlotImplT>::OnMouseDblClk( HWND hWnd, POINT point )
{
	XYPlotImplT *pT=static_cast<XYPlotImplT*>(this);

	if(pT->IsEmpty()) return false;
	if( m_pFcnAS==NULL || m_pFcnDS==NULL || m_pFcnPS==NULL ) return false;

	HDC hDC = GetDC( hWnd );

	bool needUpdate = false;

	if(pT->IsEmpty()) goto lbuttondblclk_return;

	DPtoLP( hDC, &point,1);

	int which;
	which=((CLegendImpl *)pT->GetLegend())->RegionIdentify(hDC,point);
	if(which>=0)
	{
		if(which == pT->GetDataSetCount())goto lbuttondblclk_return;
		goto CurveProperty;
	}

	int location,region;
	region=pT->RegionIdentify(hDC,point);
	switch(region)
	{
	case kXYRegionData:
		which=pT->GetIndex(pT->GetNeareastDataSet(hDC,point));

CurveProperty:
		if(which>=0)
		{
			if((*m_pFcnDS)(pT,hWnd,which))
			{
				needUpdate = true;
			}
		}
		else
		{
			goto PlotProperty;
		}
		break;
	case kXYRegionBottom:
		location=kLocationBottom;
		goto SetAxis;
	case kXYRegionTop:
		location=kLocationTop;
		goto SetAxis;
	case kXYRegionLeft:
		location=kLocationLeft;
		goto SetAxis;
	case kXYRegionRight:
		location=kLocationRight;
SetAxis:
		if((*m_pFcnAS)(pT,hWnd,location))
		{
			needUpdate = true;
		}
		break;
	default:

PlotProperty:
		if((*m_pFcnPS)(pT,hWnd))
		{
			needUpdate = true;
		}
		break;
	}

	LPtoDP( hDC, &point,1);

lbuttondblclk_return:

	ReleaseDC(hWnd,hDC);

	//if(m_bRedraw && needUpdate)pT->OnDraw(hWnd);
	return needUpdate;
}

template <typename XYPlotImplT>
bool	CXYHandler<XYPlotImplT>::OnMouseMove( HWND hWnd, POINT point )
{
	XYPlotImplT *pT=static_cast<XYPlotImplT*>(this);

	if(pT->IsEmpty()) return false;

	HDC hDC = GetDC( hWnd );

	static int curve_id0=-1;
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

	int which,curve_id;

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
		which=((CLegendImpl *)pT->GetLegend())->RegionIdentify(hDC,point);
		if(which>=0)
		{
			if(which<pT->GetDataSetCount())
			{
				curve_id=pT->GetDataID(which);
			}
			else//处于Drag区域
			{
				curve_id=-1;
				needUpdate=true;
			}
			pT->GetLegend()->SetCurrent(true);
		}
		else
		{
			curve_id=pT->GetNeareastDataSet(hDC,point);
			if(pT->GetLegend()->IsCurrent())needUpdate=true;//考虑Drag区域
			pT->GetLegend()->SetCurrent(false);
		}

		if(curve_id>=0)
		{
			if(curve_id!=curve_id0)
			{
				pT->SetLighted(curve_id,true);
				needUpdate = true;
			}
		}
		else
		{
			goto SameAsOutRegion;
		}
		curve_id0=curve_id;
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
SameAsOutRegion:
		if(pT->IsLighted())
		{
			pT->UnlightAllDataSets();
			if(curve_id0>=0)
			{
				needUpdate = true;
			}
		}
		curve_id0=-1;
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

	//if(m_bRedraw && needUpdate)pT->OnDraw(hWnd);
	return needUpdate;
}

template <typename XYPlotImplT>
bool	CXYHandler<XYPlotImplT>::OnContextMenu(HMENU hMenu, HWND hWnd, POINT point  )
{
	XYPlotImplT *pT=static_cast<XYPlotImplT*>(this);

	if( m_pFcnPM == NULL ) return false;

	//ClientToScreen( hWnd, &point );
	if( (*m_pFcnPM)( pT, hMenu, hWnd, point )==kPopupUpdate )
	{
		//if(m_bRedraw )pT->OnDraw(hWnd);
		return true ;
	}
	else
		return false;
}

template <typename XYPlotImplT>
void CXYHandler<XYPlotImplT>::Interactive(HWND hWnd, UINT message, POINT point)
{
	XYPlotImplT *pT=static_cast<XYPlotImplT*>(this);

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

template <typename XYPlotImplT>
void	CXYHandler<XYPlotImplT>::Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	XYPlotImplT *pT=static_cast<XYPlotImplT*>(this);
	POINT	point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	Interactive(hWnd, message, point);
}

#endif