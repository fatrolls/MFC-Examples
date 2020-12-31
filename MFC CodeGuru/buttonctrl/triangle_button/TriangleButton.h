// TriangleButton.h : header file
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1997 by Janus Kjempff
// All rights reserved

// class CTriangleButton shows a triangle button pointing in one of four 
// directions (UP, DOWN, LEFT, RIGHT), and works like the CButton MFC class
// Please distribute, but don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.


// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.


// Note: I copy/pasted the structure of this class from the class CRoundButton
//			 Thanx to Chris Maunder who made the CRoundButton class in the first place.
//			 The OnNCHitTest function was in the CRoundButton class, but though
//			 I have implemented it, I don't know what it should do (it is therefore
//			 outcommented at the moment, but feel free to "unlock" it if it is 
//			 anything useful)

// reach me at jak@sign-tronic.dk

// Preaching: Microsoft explorer is a fatal stupidity, remove it from windows 
//						again (no need not to learn by mistake)


#ifndef __TRIANGLEBUTTON_H__INCLUDED
#define __TRIANGLEBUTTON_H__INCLUDED



class CTriangleButton : public CButton
{
public:
	enum POINTDIRECTION {POINT_UP, POINT_DOWN, POINT_LEFT, POINT_RIGHT};
	
	// Construction
public:
	CTriangleButton();
	virtual ~CTriangleButton();

// Attributes
public:

protected:
	POINTDIRECTION PointDirection;
	CRgn CurrentRegion;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTriangleButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

public:
	//note: SetWindowPos decreases the cx, cy parameter to nearest number dividable by two
	BOOL SetWindowPos(const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags );

// Implementation
public:
	void SetDirection(POINTDIRECTION PointDirection);	//sets the direction of triangle
	POINTDIRECTION GetDirection();										//gets the direction of triangle

	// Generated message map functions
protected:
	//{{AFX_MSG(CTriangleButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#endif // __TRIANGLEBUTTON_H__INCLUDED
