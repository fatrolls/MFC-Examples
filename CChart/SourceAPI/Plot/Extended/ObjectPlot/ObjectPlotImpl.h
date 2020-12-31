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

#ifndef __OBJECTPLOTIMPL_H_122333444455555__
#define __OBJECTPLOTIMPL_H_122333444455555__

#include "ObjectPlot.h"
#include "../../Basics/XYPlotImpl.h"
#include "../../Basics//XYHandler.h"

class CObjectPlotImpl : public CObjectPlot, public CXYPlotImpl
{
public:
	CObjectPlotImpl();
	virtual ~CObjectPlotImpl();

public:
	void				OnDraw( HWND hWnd );
	void				OnDraw( HDC hDC, RECT destRect);

protected:
	void				DrawLine(HDC hDC, double x1, double y1, bool bData1, double x2, double y2, bool bData2, int linestyle, int linewidth, COLORREF color);
	void				DrawRectangle(HDC hDC, double x1, double y1, bool bData1, double x2, double y2, bool bData2, int linestyle, int linewidth, COLORREF linecolor, bool bFill, COLORREF fillcolor);
	void				DrawEllipse(HDC hDC, double ctx, double cty, bool bDataCT, double rx, bool bDataX, double ry, bool bDataY, int linestyle, int linewidth, COLORREF linecolor, bool bFill, COLORREF fillcolor);
	void				DrawCircle(HDC hDC, double ctx, double cty, bool bDataCT, double radius, bool bDataR, bool bDataRX, int linestyle, int linewidth, COLORREF linecolor, bool bFill, COLORREF fillcolor);

	void				DrawObjects(HDC hDC, RECT destRect);

protected:
	void				GetCoodinate(HDC hDC, POINT &point, double x, double y, bool bData);
	double				GetLength(HDC hDC, double val, bool bData, bool bDataX);
public:	
	bool				PtNearLine(POINT point, POINT point1, POINT point2);
	bool				PtNearObject(HDC hDC, POINT point, MetaObject object);
	int					GetNeareatObjectID(HDC hDC, POINT point);
};

template <typename ObjectPlotImplT>
class CObjectHandler : public CXYHandler<ObjectPlotImplT>
{
public:
	bool				OnMouseDown( HWND hWnd, POINT point );
	//bool				OnMouseUp( HWND hWnd, POINT point );
	//bool				OnMouseDblClk( HWND hWnd, POINT point );
	bool				OnMouseMove( HWND hWnd, POINT point );
	//bool				OnContextMenu( HMENU hMenu, HWND hWnd, POINT point );
};

class CObjectPlotImplI : public CObjectPlotImpl, public CObjectHandler<CObjectPlotImplI>
{

};
/*
class CObjectPlotImplI : public CObjectPlotImpl, public CXYHandler<CObjectPlotImplI>
{
public:
	bool				OnMouseDown( HWND hWnd, POINT point );
	//bool				OnMouseUp( HWND hWnd, POINT point );
	//bool				OnMouseDblClk( HWND hWnd, POINT point );
	bool				OnMouseMove( HWND hWnd, POINT point );
	//bool				OnContextMenu( HMENU hMenu, HWND hWnd, POINT point );
};
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

template <typename ObjectPlotImplT>
bool	CObjectHandler<ObjectPlotImplT>::OnMouseDown( HWND hWnd, POINT point )
{
	ObjectPlotImplT *pT=static_cast<ObjectPlotImplT*>(this);

	HDC hDC = GetDC( hWnd );
	for(int i = 0; i < (int)pT->GetMetaObjects().size(); i++)
	{
		if(pT->PtNearObject(hDC, point, pT->GetMetaObjects()[i]))
		{
			if(!pT->GetMetaObjects()[i].bSelected)
				pT->UnselectAllMetaObjects();
			pT->SelectMetaObject(i, !pT->GetMetaObjects()[i].bSelected);
			ReleaseDC(hWnd, hDC);
			return true;
		}
	}
	ReleaseDC(hWnd, hDC);

	pT->UnselectAllMetaObjects();
	return CXYHandler<ObjectPlotImplT>::OnMouseDown(hWnd, point);
}
/*
bool	CObjectPlotImplI::OnMouseUp( HWND hWnd, POINT point )
{
	return CXYHandler<CObjectPlotImpl>::OnMouseUp(hWnd, point);
}

bool	CObjectPlotImplI::OnMouseDblClk( HWND hWnd, POINT point )
{
	return CXYHandler<CObjectPlotImpl>::OnMouseDblClk(hWnd, point);
}
*/
template <typename ObjectPlotImplT>
bool	CObjectHandler<ObjectPlotImplT>::OnMouseMove( HWND hWnd, POINT point )
{
	ObjectPlotImplT *pT=static_cast<ObjectPlotImplT*>(this);

	static int ObjID_old = -1;
	int ObjID =-1;

	HDC hDC = GetDC(hWnd);
	for(int i = 0; i < (int)pT->m_vMetaObjects.size(); i++)
	{
		if(pT->PtNearObject(hDC, point, pT->GetMetaObjects()[i]))
		{
			if(!pT->GetMetaObjects()[i].bLighted)
				pT->UnlightAllMetaObjects();
			pT->LightMetaObject(i, !pT->GetMetaObjects()[i].bLighted);
			ObjID = i;

			ReleaseDC(hWnd, hDC);
			if(ObjID_old == ObjID)
			{
				return false;
			}
			else
			{
				ObjID_old = ObjID;
				return true;
			}
		}
	}

	ReleaseDC(hWnd, hDC);

	pT->UnlightAllMetaObjects();

	bool	bNeed1 = false, bNeed2 = false;
	if(ObjID_old >= 0)
	{
		ObjID_old = -1;
		bNeed1 = true;
	}
	bNeed2 = CXYHandler<ObjectPlotImplT>::OnMouseMove(hWnd, point);
	return bNeed1 || bNeed2;
}
/*
bool	CObjectPlotImplI::OnContextMenu( HMENU hMenu, HWND hWnd, POINT point )
{
	return CXYHandler<CObjectPlotImpl>::OnContextMenu(hMenu, hWnd, point);
}
*/

#endif