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

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

const VTX_RECT				= 0;
const VTX_DIAMOND			= 1;
const VTX_CIRCLE			= 2;
const VTX_STRETCHEDCIRCLE	= 3;

///////////////////////////////////////////////////////////////////////////////////////////
// CVertex object
//
// An alternate for CPoint which is derived from CObject, allowing it to be used in a 
// CObArray. It contains the minimum number of functions to achieve the desired 
// functionality.
//

class CVertex : public CObject
{
// Construction
public:
	CVertex();
	CVertex(const CPoint& pt);
	CVertex(const int& nX, const int& nY);
	CVertex(const CVertex& vtx);

// Attributes
public:
	int x; // Wouldn't it be counter-productive to call this m_nX?
	int y;

// Operations
public:
	operator CPoint()
	{
		return CPoint(x, y);
	}
	operator!=(const CVertex& right)
	{
		if (x == right.x && y == right.y)
			return FALSE;
		return TRUE;
	}

// Implementation
public:
	virtual ~CVertex();
};

///////////////////////////////////////////////////////////////////////////////////////////
// CVtxPolygons object
//
// A container class specifically designed for use in a CVtxButton. It contains an array of 
// four CObArray's. Each CObArray is a list of CVertex's which define a polygon.
// 

class CVtxPolygons : public CObject
{
// Construction
public:
	CVtxPolygons();

// Attributes
private:
	CObArray m_oaPolygons[4];

// Operations
public:
	// Removes all the CVertex's from all the CObArray's:
	void RemoveAll();

	// Functions that are specific to the nPolygon CObArray:
	int GetSize(const int& nPolygon);
	CVertex *GetAt(const int& nPolygon, const int& nVertex);
	void SetAt(const int& nPolygon, const int& nVertex, const CVertex& vtx);
	void InsertAt(const int& nPolygon, const int& nVertex, const CVertex& vtx);
	void Add(const int& nPolygon, const CVertex& vtx);
	void RemoveAt(const int& nPolygon, const int& nVertex);

	// Returns true if each CObArray contains at least one CVertex and 
	// contains the same number of CVertex's as each of the other CObArray's:
	BOOL ValidPolygons();
	// If the last CVertex in a CObArray is not the same as the first,
	// this function will add a CVertex to the end that is the same:
	void ClosePolygons();

	// Create standard shape functions:
	void Create(const CRect& rect, const int& nType = VTX_RECT);
	void CreateRect(const CRect& rect);
	void CreateDiamond(const CRect& rect);
	void CreateCircle(const CRect& rect, const int& nSegments = 0);
	void CreateStretchedCircle(const CRect& rect, const int& nSegments = 0);

	// Create a CRgn from the nPolygon CObArray:
	void CreatePolygonRgn(CRgn *rgn, const int& nPolygon);

	void Copy(const CVtxPolygons& vtxBtnPolygons)
	{
		RemoveAll();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < vtxBtnPolygons.m_oaPolygons[i].GetSize(); j++)
				Add(i, *(CVertex*)vtxBtnPolygons.m_oaPolygons[i].GetAt(j));
	}

// Implementation
public:
	virtual ~CVtxPolygons();
};

///////////////////////////////////////////////////////////////////////////////////////////