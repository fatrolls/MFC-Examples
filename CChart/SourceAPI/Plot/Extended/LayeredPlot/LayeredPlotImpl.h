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

#ifndef __LAYEREDPLOTIMPL_H_122333444455555__
#define __LAYEREDPLOTIMPL_H_122333444455555__

#include "../../Basics/XYPlotImpl.h"
#include "../../Basics/XYHandler.h"
#include "LayeredPlot.h"
#include "PlotLayerImpl.h"
#include "LayeredLegendImpl.h"

class CLayeredPlotImpl : public CLayeredPlot, public CXYPlotImpl
{
public:
	CLayeredPlotImpl();
	virtual ~CLayeredPlotImpl();

	bool		IsEmpty();
	bool		NeedDrawing();

	int			AddCurve(double *pX, double *pY, int nLen, int nLayerIdx);
	//int			AddLayer(CPlotLayerImpl *layer);
	int			AddLayer();
	
	void		ClearLayers(int nIndex);
	void		ClearLayers();
	int			GetNumOfLayers(){return m_vpLayers.size();}
	int			SetNumOfLayers( int num );
	void		DeleteAllData( void );

	void		GetPlotRange( double xRange[2], double yRange[2] );

	int			GetDataSetCount( void );
	CPlotData<DataPoint2D>	*GetAbsoluteDataSet( int which );

	CAxis		*AddAxis( int nLayerIdx, int location );
	CAxis		*GetAxis( int nLayerIdx, int location );

public:
	void		OnDraw( HWND hWnd );
	void		OnDraw( HDC hDC, RECT destRect);
	
	SIZE		GetAxisSize( HDC hDC, int location );
	SIZE		GetAxisPaddingSize( HDC hDC , int location );
	SIZE		GetTitleSize( HDC hDC );
	RECT		GetPlotRect( HDC hDC, RECT clientRect);
	RECT		GetTitleRect( HDC hDC, RECT clientRect, RECT chartRect );

public:
	int			GetLocalIdx(int which, int &idxOfLayer, int &idxInLayer);

	int			RegionIdentify(HDC hDC,POINT point);

	bool		IsLighted(){for(int i=0;i<GetNumOfLayers();i++)if(((CPlotLayerImpl *)m_vpLayers[i])->IsLighted())return true;return false;}
	void		UnlightAllDataSets(){for(int i=0;i<GetNumOfLayers();i++)((CPlotLayerImpl *)m_vpLayers[i])->UnlightAllDataSets();}
	void		SelectAllDataSets(bool bSel){for(int i=0;i<GetNumOfLayers();i++)((CPlotLayerImpl *)m_vpLayers[i])->SelectAllDataSets(bSel);}
	
	bool		AxisLighted();
	void		UnlightAllAxis();
	
	int			LightByPoint( HDC hDC, POINT point, int &idxOfLayer, int &idxInLayer );
	int			SelectByPoint( HDC hDC, POINT point, int &idxOfLayer, int &idxInLayer );
	
	int			GetNeareastDataSet( HDC hDC, POINT point, int &idxOfLayer, int &idxInLayer );
		
	RECT		GetLayerAxisRect( int idxOfLayer, int location, HDC hDC, RECT plotRect );
	int			GetIdxOfLayerByPointInAxisRegion(HDC hDC, RECT plotRect, POINT point);


};

template <typename LayeredPlotImplT>
class CLayeredHandler : public CHandler<LayeredPlotImplT>
{
public:
	CLayeredHandler();
protected:
	FcnDataSettings		*m_pFcnDS;
	FcnAxisSettings		*m_pFcnAS;
	FcnPlotSettings		*m_pFcnPS;
	FcnShowPopupMenu	*m_pFcnPM;
public:
	bool		OnMouseDown( HWND hWnd, POINT point );
	bool		OnMouseUp( HWND hWnd, POINT point );
	bool		OnMouseDblClk( HWND hWnd, POINT point );
	bool		OnMouseMove( HWND hWnd, POINT point );
	bool		OnContextMenu( HMENU hMenu, HWND hWnd, POINT point );
	
	void		Interactive(HWND hWnd, UINT message, POINT point);
	void		Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

class CLayeredPlotImplI : public CLayeredPlotImpl, public CLayeredHandler<CLayeredPlotImplI>
{
	
};
/*
class CLayeredPlotImplI : public CLayeredPlotImpl, public CHandler<CLayeredPlotImplI>
{
public:
	CLayeredPlotImplI();
protected:
	FcnDataSettings		*m_pFcnDS;
	FcnAxisSettings		*m_pFcnAS;
	FcnPlotSettings		*m_pFcnPS;
	FcnShowPopupMenu	*m_pFcnPM;
public:
	bool		OnMouseDown( HWND hWnd, POINT point );
	bool		OnMouseUp( HWND hWnd, POINT point );
	bool		OnMouseDblClk( HWND hWnd, POINT point );
	bool		OnMouseMove( HWND hWnd, POINT point );
	
	void		Interactive(HWND hWnd, UINT message, POINT point);
	void		Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

template <typename LayeredPlotImplT>
CLayeredHandler<LayeredPlotImplT>::CLayeredHandler()
{
	m_pFcnDS = DefDataSettings;
	m_pFcnAS = DefAxisSettings;
	m_pFcnPS = DefPlotSettings;
	m_pFcnPM = DefContextMenu;
}

template <typename LayeredPlotImplT>
bool	CLayeredHandler<LayeredPlotImplT>::OnMouseDown( HWND hWnd, POINT point )
{
	LayeredPlotImplT *pT=static_cast<LayeredPlotImplT *>(this);
	if(pT->IsEmpty()) return false;

	CPlotLayerImpl *pLayer=0;
	
	HDC hDC = GetDC( hWnd );

	// Capture
	SetCapture(hWnd);
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	ClientToScreen(hWnd,(LPPOINT)&clientRect);
	ClientToScreen(hWnd,(LPPOINT)&clientRect+1);
	ClipCursor(&clientRect);
	// End Capture

	static int curve_id0=-1;
	bool needUpdate = false;
	int idxOfLayer,idxInLayer;
	
	DPtoLP( hDC, &point,1);
	
	//Set Drag mode
	int curve_id, which = ((CLayeredLegendImpl *)(pT->GetLegend()))->RegionIdentify(hDC,point);
	if(which>=0)
	{
		pT->GetLegend()->SetDragMode(true,point);
		if(which == pT->GetDataSetCount())goto UnselectCurve;//in drag region
		curve_id=pT->GetLocalIdx(which,idxOfLayer,idxInLayer);
		pLayer=pT->GetLayer(idxOfLayer);
		if(!pLayer)
		{
			needUpdate=false;
			goto lbuttondown_return;
		}
		pLayer->SetSelected(pLayer->GetDataID(curve_id),!pLayer->IsSelected(pLayer->GetDataID(curve_id)));
		goto SelectCurve;
	}
	
	int region;
	region=pT->RegionIdentify(hDC,point);
	switch(region)
	{
	case kXYRegionData:
		//curve_id=CLayeredPlotImpl::SelectByPoint(hDC, point, idxOfLayer, idxInLayer);
		curve_id=pT->SelectByPoint(hDC, point, idxOfLayer, idxInLayer);
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
	
	LPtoDP( hDC, &point,1);
	
lbuttondown_return:
	ReleaseDC(hWnd,hDC);

	return needUpdate;
}

template <typename LayeredPlotImplT>
bool	CLayeredHandler<LayeredPlotImplT>::OnMouseUp( HWND hWnd, POINT point )
{
	LayeredPlotImplT *pT=static_cast<LayeredPlotImplT *>(this);
	
	if((((CLayeredLegendImpl *)pT->GetLegend()))->IsDragMode()) (((CLayeredLegendImpl *)pT->GetLegend()))->SetDragMode(false,point);
	if(GetCapture())ReleaseCapture();
	ClipCursor(NULL);
		
	return false;
}

template <typename LayeredPlotImplT>
bool	CLayeredHandler<LayeredPlotImplT>::OnMouseDblClk( HWND hWnd, POINT point )
{
	LayeredPlotImplT *pT=static_cast<LayeredPlotImplT *>(this);
	if(pT->IsEmpty()) return false;

	CPlotLayerImpl *pLayer;

	if( m_pFcnAS==NULL || m_pFcnDS==NULL || m_pFcnPS==NULL ) return false;

	HDC hDC = GetDC( hWnd );

	bool needUpdate = false;

	if(pT->IsEmpty()) goto lbuttondblclk_return;

	DPtoLP( hDC, &point,1);

	int which,curve_id;
	int idxOfLayer,idxInLayer;
	
	which=(((CLegendImpl *)pT->GetLegend()))->RegionIdentify(hDC,point);
	if(which >= 0)
	{
		if(which == pT->GetDataSetCount())goto lbuttondblclk_return;
		
		curve_id=pT->GetLocalIdx(which,idxOfLayer,idxInLayer);
		if(curve_id>=0)
		{
			pLayer = pT->GetLayer(idxOfLayer);
			if(!pLayer)
			{
				needUpdate = false;
				goto lbuttondblclk_return;
			}
			pLayer->SetSelected(curve_id,!pLayer->IsSelected(curve_id));
		}
		goto CurveProperty;
	}

	int location,region;
	region=pT->RegionIdentify(hDC,point);
	switch(region)
	{
	case kXYRegionData:
		curve_id=pT->GetNeareastDataSet(hDC,point,idxOfLayer,idxInLayer);

CurveProperty:
		if(curve_id>=0)
		{
			pLayer = pT->GetLayer(idxOfLayer);
			if(!pLayer)
			{
				needUpdate = false;
				goto lbuttondblclk_return;
			}
			which=pLayer->GetIndex(curve_id);
			if(pLayer->m_pFcnDS(static_cast<LayeredPlotImplT *>(this),hWnd,which))
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
		goto SetAxisTB;
	case kXYRegionTop:
		location=kLocationTop;
SetAxisTB:
		if((*m_pFcnAS)(static_cast<LayeredPlotImplT *>(this),hWnd,location))
		{
			needUpdate = true;
		}
		break;
	case kXYRegionLeft:
		location=kLocationLeft;
		goto SetAxisLR;
	case kXYRegionRight:
		location=kLocationRight;
SetAxisLR:
		idxOfLayer = pT->GetIdxOfLayerByPointInAxisRegion( hDC, pT->GetPlotRect(hDC,pT->GetLastClientRect()),point);
		pLayer = pT->GetLayer(idxOfLayer);
		if(!pLayer)
		{
			needUpdate = false;
			goto lbuttondblclk_return;
		}
		if(idxOfLayer>=0 && pLayer->m_pFcnAS(static_cast<LayeredPlotImplT *>(this),hWnd,location))
		{
			needUpdate = true;
		}
		break;
	default:

PlotProperty:
		if((*m_pFcnPS)(static_cast<LayeredPlotImplT *>(this),hWnd))
		{
			needUpdate = true;
		}
		break;
	}

	LPtoDP( hDC, &point,1);

lbuttondblclk_return:

	ReleaseDC(hWnd,hDC);

	return needUpdate;
}

template <typename LayeredPlotImplT>
bool	CLayeredHandler<LayeredPlotImplT>::OnMouseMove( HWND hWnd, POINT point )
{
	LayeredPlotImplT *pT=static_cast<LayeredPlotImplT *>(this);
	if(pT->IsEmpty()) return false;

	CPlotLayerImpl *pLayer;

	HDC hDC = GetDC( hWnd );

	static int curve_id0=-1,layer_idx0_cv=-1;
	static int loc0,layer_idx0_ax=-1;
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
	int idxOfLayer,idxInLayer;

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
			if(loc0>=0 || layer_idx0_ax>=0)
			{
				needUpdate = true;
			}
			loc0=-1;
			layer_idx0_ax=-1;
		}
		//如果处于legend区域
		which=((CLegendImpl *)(pT->GetLegend()))->RegionIdentify(hDC,point);
		if(which>=0)
		{
			if(which<pT->GetDataSetCount())
			{
				curve_id=pT->GetLocalIdx(which,idxOfLayer,idxInLayer);
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
			//curve_id=CLayeredPlotImpl::LightByPoint(hDC,point,idxOfLayer,idxInLayer);
			curve_id=pT->LightByPoint(hDC,point,idxOfLayer,idxInLayer);
			if(pT->GetLegend()->IsCurrent())needUpdate=true;//考虑Drag区域
			pT->GetLegend()->SetCurrent(false);
		}

		if(curve_id>=0)
		{
			if(curve_id!=curve_id0 || idxOfLayer!=layer_idx0_cv)
			{
				pT->UnlightAllDataSets();
				pLayer = pT->GetLayer(idxOfLayer);
				if(!pLayer)
				{
					needUpdate = false;
					goto mousemove_return;
				}
				pLayer->SetLighted(curve_id,true);
				needUpdate = true;
			}
		}
		else
		{
			goto SameAsOutRegion;
		}
		curve_id0=curve_id;
		layer_idx0_cv=idxOfLayer;
		break;
	case kXYRegionBottom:
		location=kLocationBottom;
		goto LightAxisTB;
	case kXYRegionTop:
		location=kLocationTop;		
LightAxisTB:
		axis=pT->GetAxisByLocation(location);
		if(axis)
		{
			axis->SetCurrent(true);
			if(location!=loc0)
			{
				needUpdate = true;
			}
			loc0=location;
		}
		break;
	case kXYRegionLeft:
		location=kLocationLeft;
		goto LightAxisLR;
	case kXYRegionRight:
		location=kLocationRight;
LightAxisLR:
		idxOfLayer=pT->GetIdxOfLayerByPointInAxisRegion(hDC, pT->GetPlotRect(hDC,pT->GetLastClientRect()),point);
		if(idxOfLayer<0)
		{
			needUpdate = false;
			goto mousemove_return;
		}
		pLayer = pT->GetLayer(idxOfLayer);
		if(!pLayer)
		{
			needUpdate = false;
			goto mousemove_return;
		}
		axis=pLayer->GetAxisByLocation(location);
		if(axis)
		{
			pT->UnlightAllAxis();
			axis->SetCurrent(true);
			if(location!=loc0 || idxOfLayer!=layer_idx0_ax )
			{
				needUpdate = true;
			}
			loc0=location;
			layer_idx0_ax=idxOfLayer;
		}
		break;
	default:
		// unlight axis
		if(pT->AxisLighted())
		{
			pT->UnlightAllAxis();
			if( loc0>=0 || layer_idx0_ax>=0 )
			{
				needUpdate = true;
			}
			loc0=-1;
			layer_idx0_ax=-1;
		}
SameAsOutRegion:
		pT->UnlightAllDataSets();
		if(curve_id0>=0 || layer_idx0_cv>=0)
		{
			needUpdate = true;
		}
		
		curve_id0=-1;
		layer_idx0_cv=-1;
		layer_idx0_ax=-1;
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

	double data[2];
	pT->LPToData( hDC, &point, data);
	//SetCursor(data);
	//needUpdate = true;

	LPtoDP( hDC, &point,1);

mousemove_return:

	ReleaseDC(hWnd,hDC);
	return needUpdate;
}

template <typename LayeredPlotImplT>
bool	CLayeredHandler<LayeredPlotImplT>::OnContextMenu( HMENU hMenu, HWND hWnd, POINT point )
{
	LayeredPlotImplT *pT=static_cast<LayeredPlotImplT *>(this);
		
	return false;
}

template <typename LayeredPlotImplT>
void	CLayeredHandler<LayeredPlotImplT>::Interactive(HWND hWnd, UINT message, POINT point)
{
	LayeredPlotImplT *pT=static_cast<LayeredPlotImplT *>(this);

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
	case WM_SIZE:
		pT->OnDraw(hWnd);
	case WM_ERASEBKGND:
		return;
	default:
		return;
	}
}

template <typename LayeredPlotImplT>
void	CLayeredHandler<LayeredPlotImplT>::Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT	point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	Interactive(hWnd, message, point);
}


#endif