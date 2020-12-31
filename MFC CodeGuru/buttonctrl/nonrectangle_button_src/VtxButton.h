// VtxButton.h: header file
//
// CVtxButton
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

#include "Vtx.h"

///////////////////////////////////////////////////////////////////////////////////////////
// CVtxButton button
//
// A class derived from CButton that is drawn in the shape specified by 
// CVtxPolygons.
//

class CVtxButton : public CButton
{
// Construction
public:
	CVtxButton();

// Attributes
private:
	CVtxPolygons	m_vtxBtnPolygons;
	CDC				*m_pBitmapDC;
	CBitmap			*m_pBtn,
					*m_pBtnFocus,
					*m_pBtnSelected;
	DWORD			m_dwStyle;
	BOOL			m_bNeedToRegenerateBitmaps;

// Operations
public:
	// Select a custom CVtxPolygons shape:
	void SetVtxPolygons(CVtxPolygons *vtxBtnPolygons);
	// Select a standard CVtxPolygons shape:
	void SetVtx(const int& nType);

private:
	void GenerateBitmaps(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Overrides
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void PreSubclassWindow();

// Implementation
public:
	virtual ~CVtxButton();
};

///////////////////////////////////////////////////////////////////////////////////////////