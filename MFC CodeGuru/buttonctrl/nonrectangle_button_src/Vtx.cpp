// Vtx.h: header file
//
// CVertex and CVtxPolygons
//
// Copyright © 1998 Hilton Campbell. All rights reserved.
// 
// Revisions: 
// 30 June 1998		Initial release		Hilton Campbell (hiltonc@softhome.net)
//
// This code may be used in compiled form in any way you desire. This file may be 
// redistributed unmodified by any means PROVIDING it is not sold for profit without the 
// author's written consent, and providing that this notice and the authors name is 
// included. If the source code in this file is used in any distributed application, please
// let me know by e-mail so that I can feel special. 
//
// No warrantee of any kind, express or implied, is included with this software; use at 
// your own risk, responsibility for damages (if any) to anyone resulting from the use of 
// this software rests entirely with the user.
//
///////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vtx.h"
#include <math.h>

// There is no excuse for inaccuracy in this area =)
#define PI			3.1415926535897932384626433832795028841971693993751058209
// A very convenient way to properly convert double's to int's:
#define round(x)	(int)(x + 0.5)

///////////////////////////////////////////////////////////////////////////////////////////
// CVertex object

CVertex::CVertex()
{
	x = 0;
	y = 0;
}

CVertex::CVertex(const CPoint& pt)
{
	x = pt.x;
	y = pt.y;
}

CVertex::CVertex(const int& nX, const int& nY)
{
	x = nX;
	y = nY;
}

//
CVertex::CVertex(const CVertex& vtx)
{
	x = vtx.x;
	y = vtx.y;
}

CVertex::~CVertex()
{
}

///////////////////////////////////////////////////////////////////////////////////////////
// CVtxPolygons object

CVtxPolygons::CVtxPolygons()
{
}

CVtxPolygons::~CVtxPolygons()
{
	RemoveAll();
}

void CVtxPolygons::RemoveAll()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < m_oaPolygons[i].GetSize(); j++)
		{
			if (m_oaPolygons[i].GetAt(j) != NULL)
				delete m_oaPolygons[i].GetAt(j);
		}
	}
}

int CVtxPolygons::GetSize(const int& nPolygon)
{
	return m_oaPolygons[nPolygon].GetSize();
}

CVertex *CVtxPolygons::GetAt(const int& nPolygon, const int& nVertex)
{
	return (CVertex*)m_oaPolygons[nPolygon].GetAt(nVertex);
}

void CVtxPolygons::SetAt(const int& nPolygon, const int& nVertex, const CVertex& vtx)
{
	m_oaPolygons[nPolygon].SetAt(nVertex, new CVertex(vtx));
}
	
void CVtxPolygons::InsertAt(const int& nPolygon, const int& nVertex, const CVertex& vtx)
{
	m_oaPolygons[nPolygon].InsertAt(nVertex, new CVertex(vtx));
}

void CVtxPolygons::Add(const int& nPolygon, const CVertex& vtx)
{
	m_oaPolygons[nPolygon].Add(new CVertex(vtx));
}

void CVtxPolygons::RemoveAt(const int& nPolygon, const int& nVertex)
{
	m_oaPolygons[nPolygon].RemoveAt(nVertex);
}

BOOL CVtxPolygons::ValidPolygons()
{
	int nSize = GetSize(0);
	if (nSize == 0)
		return FALSE;
	if (nSize != GetSize(1))
		return FALSE;
	if (nSize != GetSize(2))
		return FALSE;
	if (nSize != GetSize(3))
		return FALSE;
	return TRUE;
}

void CVtxPolygons::ClosePolygons()
{
	for (int i = 0; i < 4; i++)
		if (*GetAt(i, GetSize(i) - 1) != *GetAt(i, 0))
			Add(i, *GetAt(i, 0));
}

void CVtxPolygons::Create(const CRect& rect, const int& nType)
{
	switch (nType)
	{
		case VTX_RECT:
			CreateRect(rect);
			break;
		case VTX_DIAMOND:
			CreateDiamond(rect);
			break;
		case VTX_CIRCLE:
			CreateCircle(rect);
			break;
		case VTX_STRETCHEDCIRCLE:
			CreateStretchedCircle(rect);
			break;
	}
}

void CVtxPolygons::CreateRect(const CRect& rect)
{
	RemoveAll();

	CRect offset[4] = {CRect(0, 0, 0, 0), CRect(1, 1, -1, -1), 
		CRect(2, 2, -2, -2), CRect(4, 4, -4, -4)};

	CRect realRect = *rect;
	realRect.right--;
	realRect.bottom--;

	for (int i = 0; i < 4; i++)
	{ 
		m_oaPolygons[i].Add(new CVertex(realRect.left + offset[i].left, 
			realRect.top + offset[i].top));
		m_oaPolygons[i].Add(new CVertex(realRect.right + offset[i].right, 
			realRect.top + offset[i].top));
		m_oaPolygons[i].Add(new CVertex(realRect.right + offset[i].right, 
			realRect.bottom + offset[i].bottom));
		m_oaPolygons[i].Add(new CVertex(realRect.left + offset[i].left, 
			realRect.bottom + offset[i].bottom));

	}

	ClosePolygons();
}

void CVtxPolygons::CreateDiamond(const CRect& rect)
{
	RemoveAll();

	CRect offset[4] = {CRect(0, 0, 0, 0), CRect(1, 1, -1, -1), 
		CRect(2, 2, -2, -2), CRect(4, 4, -4, -4)};

	CRect realRect = *rect;
	realRect.right--;
	realRect.bottom--;

	UINT side;
	if (realRect.right > realRect.bottom)
	{
		side = realRect.bottom;
		realRect.left = round((realRect.right - side) / 2);
		realRect.right = realRect.left + side;
	}
	else
	{
		side = realRect.right;
		realRect.top = round((realRect.bottom - side) / 2);
		realRect.bottom = realRect.top + side;
	}

	for (UINT i = 0; i < 4; i++)
	{
		m_oaPolygons[i].Add(new CVertex(realRect.left + offset[i].left, 
			round(realRect.top + realRect.Height() / 2)));
		m_oaPolygons[i].Add(new CVertex(round(realRect.left + realRect.Width() / 2), 
			realRect.top + offset[i].top));
		m_oaPolygons[i].Add(new CVertex(realRect.right + offset[i].right, 
			round(realRect.top + realRect.Height() / 2)));
		m_oaPolygons[i].Add(new CVertex(round(realRect.left + realRect.Width() / 2), 
			realRect.bottom + offset[i].bottom));
	}

	ClosePolygons();
}

void CVtxPolygons::CreateCircle(const CRect& rect, const int& nSegments)
{
	RemoveAll();

	CRect realRect = *rect;
	realRect.right--;
	realRect.bottom--;

	double dCenterX = realRect.left + realRect.Width() / 2;
	double dCenterY = realRect.top + realRect.Height() / 2;

	UINT nSide;
	double dRadius;
	if (realRect.right > realRect.bottom)
	{
		nSide = realRect.bottom;
		realRect.left = round((realRect.right - nSide) / 2);
		realRect.right = realRect.left + nSide;
		dRadius = dCenterY;
	}
	else
	{
		nSide = realRect.right;
		realRect.top = round((realRect.bottom - nSide) / 2);
		realRect.bottom = realRect.top + nSide;
		dRadius = dCenterX;
	}

	double dLayers[4] = {dRadius, dRadius - 1, dRadius - 2, dRadius - 4};
	int segments = (nSegments < 2 ? round(dRadius) : nSegments);

	double dAngle;
	for (int i = 0; i < 4; i++)
	{
		m_oaPolygons[i].RemoveAll();
		for (int j = 0; j < segments; j++)
		{
			dAngle = 2.0 * PI * j / segments;
			m_oaPolygons[i].Add(new CVertex(round(dCenterX + cos(dAngle) * dLayers[i]), 
				round(dCenterY + sin(dAngle) * dLayers[i])));
		}
	}

	ClosePolygons();
}

void CVtxPolygons::CreateStretchedCircle(const CRect& rect, const int& nSegments)
{
	RemoveAll();

	CRect realRect = *rect;
	realRect.right--;
	realRect.bottom--;

	double dRadius;
	double dRightX, dRightY;
	double dStartAngle;
	BOOL bHorizontal = realRect.right > realRect.bottom;
	if (bHorizontal)
	{
		dRadius = realRect.top + realRect.Height() / 2;
		dRightX = realRect.right - dRadius;
		dRightY = dRadius;
		dStartAngle = 3 * PI / 2;
	}
	else
	{
		dRadius = realRect.left + realRect.Width() / 2;
		dRightX = dRadius;
		dRightY = realRect.bottom - dRadius;
		dStartAngle = 0;
	}

	double dLeftX = dRadius;
	double dLeftY = dRadius;
	
	double dRadiusLayers[4] = {dRadius, dRadius - 1, dRadius - 2, dRadius - 4};
	int segments = (nSegments < 1 ? round(dRadius) : nSegments);

	double dAngle;
	for (int i = 0; i < 4; i++)
	{
		m_oaPolygons[i].RemoveAll();
		for (int j = 0; j < round(segments / 2 + 1); j++)
		{
			dAngle = dStartAngle + 2 * PI * j / segments;
			m_oaPolygons[i].Add(new CVertex(round(dRightX + cos(dAngle) *
				dRadiusLayers[i]), round(dRightY + sin(dAngle) * dRadiusLayers[i])));
		}

		for (j = round(segments / 2); j < segments + 1; j++)
		{ 
			dAngle = dStartAngle + 2 * PI * j / segments;
			m_oaPolygons[i].Add(new CVertex(round(dLeftX + cos(dAngle) * 
				dRadiusLayers[i]), round(dLeftY + sin(dAngle)  *dRadiusLayers[i])));
		}
	}

	ClosePolygons();
}

void CVtxPolygons::CreatePolygonRgn(CRgn *rgn, const int& nPolygon)
{
	ASSERT(ValidPolygons());

	ClosePolygons();
	
	CPoint pts[1024];
	for (int i = 0; i < m_oaPolygons[nPolygon].GetSize(); i++)
		pts[i] = (CPoint)(*(CVertex*)m_oaPolygons[nPolygon].GetAt(i));

	rgn->CreatePolygonRgn(pts, m_oaPolygons[nPolygon].GetSize(), ALTERNATE);	
}

///////////////////////////////////////////////////////////////////////////////////////////