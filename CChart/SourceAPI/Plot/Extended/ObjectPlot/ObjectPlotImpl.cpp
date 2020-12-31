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

#include "StdAfx.h"
#include "ObjectPlotImpl.h"

CObjectPlotImpl::CObjectPlotImpl()
{

}

CObjectPlotImpl::~CObjectPlotImpl()
{

}

void	CObjectPlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CObjectPlotImpl::OnDraw(HDC hDC, RECT destRect)
{
	//if there is no data, doing nothing
	if(m_vXYDataInfo.size()<=0)
	{
		EraseBkgnd( hDC, destRect );
		return;
	}
	
	//////////////////////////////////////////////////////////////////
	double			xRange[] = {1e30, -1e30}, yRange[]={1e30,-1e30};

	// Make sure our ranges are set
	// Get ranges for plotting
	GetPlotRange( xRange, yRange );
	
	// Draw basics
	CXYPlotImpl::OnDraw(hDC,destRect);
	// Draw objects
	DrawObjects(hDC, destRect);
}

void	CObjectPlotImpl::DrawObjects(HDC hDC, RECT destRect)
{
	int linewidth;
	COLORREF linecolor, fillcolor;

	SetLastClientRect(destRect);
	for(int i = 0; i < (int)m_vMetaObjects.size(); i++)
	{
		linewidth = GetLineWidth(m_vMetaObjects[i].nLineWidth, m_vMetaObjects[i].bLighted, m_vMetaObjects[i].bSelected);
		linecolor = GetLineColor(m_vMetaObjects[i].crLineColor, m_vMetaObjects[i].bLighted, m_vMetaObjects[i].bSelected);
		fillcolor = GetLineColor(m_vMetaObjects[i].crFillColor, m_vMetaObjects[i].bLighted, m_vMetaObjects[i].bSelected);
		switch(m_vMetaObjects[i].nCode)
		{
		case 1:
			DrawLine(hDC, m_vMetaObjects[i].fX1, m_vMetaObjects[i].fY1, m_vMetaObjects[i].bData1, m_vMetaObjects[i].fX2, m_vMetaObjects[i].fY2, m_vMetaObjects[i].bData2, m_vMetaObjects[i].nLineStyle, linewidth, linecolor);
			break;
		case 2:
			DrawRectangle(hDC, m_vMetaObjects[i].fX1, m_vMetaObjects[i].fY1, m_vMetaObjects[i].bData1, m_vMetaObjects[i].fX2, m_vMetaObjects[i].fY2, m_vMetaObjects[i].bData2, m_vMetaObjects[i].nLineStyle, linewidth, linecolor, m_vMetaObjects[i].bFill, fillcolor);
			break;
		case 3:
			DrawEllipse(hDC, m_vMetaObjects[i].fCtX, m_vMetaObjects[i].fCtY, m_vMetaObjects[i].bDataCT, m_vMetaObjects[i].fRx, m_vMetaObjects[i].bDataX, m_vMetaObjects[i].fRy, m_vMetaObjects[i].bDataY, m_vMetaObjects[i].nLineStyle, linewidth, linecolor, m_vMetaObjects[i].bFill, fillcolor);
			break;
		case 4:
			DrawCircle(hDC, m_vMetaObjects[i].fCtX, m_vMetaObjects[i].fCtY, m_vMetaObjects[i].bDataCT, m_vMetaObjects[i].fRadius, m_vMetaObjects[i].bDataR, m_vMetaObjects[i].bDataRX, m_vMetaObjects[i].nLineStyle, linewidth, linecolor, m_vMetaObjects[i].bFill, fillcolor);
			break;
		default:
			break;
		}
	}
}

void	CObjectPlotImpl::DrawLine(HDC hDC, double x1, double y1, bool bData1, double x2, double y2, bool bData2, int linestyle, int linewidth, COLORREF linecolor )
{
	POINT point1, point2;

	GetCoodinate(hDC, point1, x1, y1, bData1);
	GetCoodinate(hDC, point2, x2, y2, bData2);

	HPEN hPen, hOldPen;
	hPen = CreatePen(linestyle, linewidth, linecolor);
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	MoveToEx(hDC, point1.x, point1.y, NULL);
	LineTo(hDC, point2.x, point2.y);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

void	CObjectPlotImpl::DrawRectangle(HDC hDC, double x1, double y1, bool bData1, double x2, double y2, bool bData2, int linestyle, int linewidth, COLORREF linecolor, bool bFill, COLORREF fillcolor)
{
	POINT point1, point2;
	
	GetCoodinate(hDC, point1, x1, y1, bData1);
	GetCoodinate(hDC, point2, x2, y2, bData2);
	
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	hPen = CreatePen(linestyle, linewidth, linecolor);
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	if(bFill)
	{
		hBrush = CreateSolidBrush(fillcolor);
	}
	else
	{
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	
	Rectangle(hDC, point1.x, point1.y, point2.x, point2.y);
	
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void	CObjectPlotImpl::DrawEllipse(HDC hDC, double ctx, double cty, bool bDataCT, double rx, bool bDataX, double ry, bool bDataY, int linestyle, int linewidth, COLORREF linecolor, bool bFill, COLORREF fillcolor)
{
	POINT center;

	GetCoodinate(hDC, center, ctx, cty, bDataCT);
	double Rx, Ry;
	Rx = GetLength(hDC, rx, bDataX, true);
	Ry = GetLength(hDC, ry, bDataY, false);

	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	hPen = CreatePen(linestyle, linewidth, linecolor);
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	if(bFill)
	{
		hBrush = CreateSolidBrush(fillcolor);
	}
	else
	{
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Ellipse(hDC, int(center.x-Rx), int(center.y+Ry), int(center.x+Rx), int(center.y-Ry));
	
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void	CObjectPlotImpl::DrawCircle(HDC hDC, double ctx, double cty, bool bDataCT, double radius, bool bDataR, bool bDataRX, int linestyle, int linewidth, COLORREF linecolor, bool bFill, COLORREF fillcolor)
{
	POINT center;
	
	GetCoodinate(hDC, center, ctx, cty, bDataCT);

	double Radius;
	Radius = GetLength(hDC, radius, bDataR, bDataRX);

	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	
	hPen = CreatePen(linestyle, linewidth, linecolor);
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	if(bFill)
	{
		hBrush = CreateSolidBrush(fillcolor);
	}
	else
	{
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Ellipse(hDC, int(center.x-Radius), int(center.y+Radius), int(center.x+Radius), int(center.y-Radius));
	
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void	CObjectPlotImpl::GetCoodinate(HDC hDC, POINT &point, double x, double y, bool bData)
{
	double data[2];
	RECT plotRect = GetPlotRect(hDC, GetLastClientRect());

	if(!bData)
	{
		point.x = plotRect.left + (long)x;
		point.y = plotRect.bottom - (long)y;
	}
	else
	{
		data[0] = x;
		data[1] = y;
		CXYPlotImpl::DataToLP(hDC, data, &point);
	}
}

double	CObjectPlotImpl::GetLength(HDC hDC, double val, bool bData, bool bDataX)
{
	double data[2];
	POINT point1, point2;

	if(!bData)
	{
		return val;
	}
	else
	{
		data[0] = 0;
		data[1] = 0;
		CXYPlotImpl::DataToLP(hDC, data, &point1);
		
		if(bDataX)
		{
			data[0] = val;
			data[1] = 0;
			CXYPlotImpl::DataToLP(hDC, data, &point2);
			return fabs(double(point2.x - point1.x));
		}
		else
		{
			data[0] = 0;
			data[1] = val;
			CXYPlotImpl::DataToLP(hDC, data, &point2);
			return fabs(double(point2.y - point1.y));
		}
	}
}

bool	CObjectPlotImpl::PtNearLine(POINT point, POINT point1, POINT point2)
{
	double dltM = 2.0;

	if(point1.x == point2.x && point1.y == point2.y) return false;

	if(point1.x == point2.x)
	{
		if(fabs(double(point.x - point1.x)) <= dltM && (point2.y - point.y)*(point.y - point1.y)>=0 )
			return true;
		else
			return false;
	}
	else
	{
		double y;
		y = point1.y + (point2.y - point1.y)*(point.x - point1.x)/(point2.x - point1.x);
		if(fabs(double(y - point.y)) <= dltM)
			return true;
		else
			return false;
	}
}

bool	CObjectPlotImpl::PtNearObject(HDC hDC, POINT point, MetaObject object)
{
	POINT point1, point2;

	double dltM = 2.0;
	POINT center;
	double Rx, Ry;
	double Radius;

	switch(object.nCode)
	{
	case 1:
		GetCoodinate(hDC, point1, object.fX1, object.fY1, object.bData1);
		GetCoodinate(hDC, point2, object.fX2, object.fY2, object.bData2);
		return PtNearLine(point, point1, point2);
	case 2:
		GetCoodinate(hDC, point1, object.fX1, object.fY1, object.bData1);
		GetCoodinate(hDC, point2, object.fX2, object.fY2, object.bData2);
		
		if(object.bFill)
		{
			RECT rect;
			rect.left = point1.x;
			rect.top = point1.y;
			rect.right = point2.x;
			rect.bottom = point2.y;
			if(PtInRect(&rect, point))
				return true;
			else
				return false;
		}
		else
		{
			POINT pt1, pt2;
			
			pt1.x = point1.x;
			pt1.y = point1.y;
			pt2.x = point2.x;
			pt2.y = point1.y;
			if(PtNearLine(point, pt1, pt2))
				return true;
			pt1.x = point2.x;
			pt1.y = point1.y;
			pt2.x = point2.x;
			pt2.y = point2.y;
			if(PtNearLine(point, pt1, pt2))
				return true;
			pt1.x = point2.x;
			pt1.y = point2.y;
			pt2.x = point1.x;
			pt2.y = point2.y;
			if(PtNearLine(point, pt1, pt2))
				return true;
			pt1.x = point1.x;
			pt1.y = point2.y;
			pt2.x = point1.x;
			pt2.y = point1.y;
			if(PtNearLine(point, pt1, pt2))
				return true;			
			return false;
		}
	case 3:
		GetCoodinate(hDC, center, object.fCtX, object.fCtY, object.bDataCT);
		Rx = GetLength(hDC, object.fRx, object.bDataX, true);
		Ry = GetLength(hDC, object.fRy, object.bDataY, false);
		if(object.bFill)
		{
			HRGN hRgn;
			hRgn = CreateEllipticRgn(int(center.x - Rx), int(center.y - Ry), int(center.x + Rx), int(center.y + Ry));
			if(PtInRegion(hRgn, point.x, point.y))
			{
				DeleteObject(hRgn);
				return true;
			}
			else
			{
				DeleteObject(hRgn);
				return false;
			}
		}
		else
		{
			if( point.x < center.x - Rx || point.x > center.x + Rx || point.y < center.y - Ry || point.y > center.y + Rx)
				return false;
			
			double y1, y2;
			y1 = center.y + sqrt( 1.0 - (point.x - center.x)*(point.x - center.x)/(Rx * Rx) ) * Ry;
			y2 = center.y - sqrt( 1.0 - (point.x - center.x)*(point.x - center.x)/(Rx * Rx) ) * Ry;
			
			if( fabs(point.y - y1) <= dltM || fabs(point.y - y2) <= dltM)
				return true;
			else
				return false;
		}
	case 4:
		GetCoodinate(hDC, center, object.fCtX, object.fCtY, object.bDataCT);
		Radius = GetLength(hDC, object.fRadius, object.bDataR, object.bDataRX);
		if(object.bFill)
		{
			HRGN hRgn;
			hRgn = CreateEllipticRgn(int(center.x - Radius), int(center.y - Radius), int(center.x + Radius), int(center.y + Radius));
			if(PtInRegion(hRgn, point.x, point.y))
			{
				DeleteObject(hRgn);
				return true;
			}
			else
			{
				DeleteObject(hRgn);
				return false;
			}
		}
		else
		{
			if( point.x < center.x - Radius || point.x > center.x + Radius || point.y < center.y - Radius || point.y > center.y + Radius)
				return false;
			
			double y1, y2;
			y1 = center.y + sqrt( Radius * Radius - (point.x - center.x)*(point.x - center.x) );
			y2 = center.y - sqrt( Radius * Radius - (point.x - center.x)*(point.x - center.x) );
			
			if( fabs(point.y - y1) <= dltM || fabs(point.y - y2) <= dltM)
				return true;
			else
				return false;
		}
	default:
		return false;
	}
}

int		CObjectPlotImpl::GetNeareatObjectID(HDC hDC, POINT point)
{
	for(int i = 0; i < (int)m_vMetaObjects.size(); i++)
	{
		if(PtNearObject(hDC, point, m_vMetaObjects[i]))
			return i;
	}
	return -1;
}
/*
bool	CObjectPlotImplI::OnMouseDown( HWND hWnd, POINT point )
{
	HDC hDC = GetDC( hWnd );
	for(int i = 0; i < m_vMetaObjects.size(); i++)
	{
		if(PtNearObject(hDC, point, m_vMetaObjects[i]))
		{
			if(!m_vMetaObjects[i].bSelected)
				UnselectAllMetaObjects();
			SelectMetaObject(i, !m_vMetaObjects[i].bSelected);
			ReleaseDC(hWnd, hDC);
			return true;
		}
	}
	ReleaseDC(hWnd, hDC);

	UnselectAllMetaObjects();
	return CXYHandler<CObjectPlotImplI>::OnMouseDown(hWnd, point);
}

bool	CObjectPlotImplI::OnMouseUp( HWND hWnd, POINT point )
{
	return CXYHandler<CObjectPlotImpl>::OnMouseUp(hWnd, point);
}

bool	CObjectPlotImplI::OnMouseDblClk( HWND hWnd, POINT point )
{
	return CXYHandler<CObjectPlotImpl>::OnMouseDblClk(hWnd, point);
}

bool	CObjectPlotImplI::OnMouseMove( HWND hWnd, POINT point )
{
	static int ObjID_old = -1;
	int ObjID =-1;

	HDC hDC = GetDC(hWnd);
	for(int i = 0; i < m_vMetaObjects.size(); i++)
	{
		if(PtNearObject(hDC, point, m_vMetaObjects[i]))
		{
			if(!m_vMetaObjects[i].bLighted)
				UnlightAllMetaObjects();
			LightMetaObject(i, !m_vMetaObjects[i].bLighted);
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

	UnlightAllMetaObjects();

	bool	bNeed1 = false, bNeed2 = false;
	if(ObjID_old >= 0)
	{
		ObjID_old = -1;
		bNeed1 = true;
	}
	bNeed2 = CXYHandler<CObjectPlotImplI>::OnMouseMove(hWnd, point);
	return bNeed1 || bNeed2;
}

bool	CObjectPlotImplI::OnContextMenu( HMENU hMenu, HWND hWnd, POINT point )
{
	return CXYHandler<CObjectPlotImpl>::OnContextMenu(hMenu, hWnd, point);
}
*/