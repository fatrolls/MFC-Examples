#if !defined(_OXSSTATICMENUITEM_H__)
#define _OXSSTATICMENUITEM_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

// OXStaticMenuItem.h : header file
//

#include "OXHookWnd.h"
#include "OXStaticText.h"
#include "OXMainRes.h"


/////////////////////////////////////////////////////////////////////////////
// COXStaticMenuItem window

class OX_CLASS_DECL COXStaticMenuItem : public COXStaticText
{
// Construction
public:
	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructs the object
	COXStaticMenuItem();

// Attributes
public:

protected:
	// flag specifies whether the mouse button is currently pressed in 
	BOOL m_bPressedDown;
	// color of the text when item is active
	COLORREF m_clrActive;
	// color of the text when item is inactive
	COLORREF m_clrNormalText;

	// helper object to spy for mouse entering and leaving events
	COXHookWnd m_MouseSpy;

// Operations
public:

	// --- In  :	clrText			-	text color in the inactive (normal) state
	//				clrBack			-	background color
	//				clrActive		-	text color in the active state
	//				nFontHeight		-	text font height
	//				nFontWeight		-	text font weight
	//				sFontName		-	text font name
	//				bEmboss			-	if TRUE then font will be drawn 
	//									with 3D effect
	//				nHorzAlignment	-	horizontal alignment of the text 
	//									in the control
	//				nVertAlignment	-	vertical alignment of the text 
	//									in the control
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructs the object
	void SetProperties(COLORREF clrText=::GetSysColor(COLOR_BTNTEXT), 
		COLORREF clrBack=::GetSysColor(COLOR_BTNFACE), 
		COLORREF clrActive=RGB(192,0,0), int nFontHeight=12, 
		int nFontWeight=FW_NORMAL, CString sFontName=_T("MS Sans Serif"), 
		BOOL bEmboss=TRUE, int nHorzAlignment=OX_ALIGNHORZ_LEFT, 
		int nVertAlignment=OX_ALIGNVERT_CENTER);

	
	inline void SetActiveColor(COLORREF clrActive, BOOL bPrepareNow=FALSE) 
	{
		m_clrActive=clrActive;
		if(m_MouseSpy.IsMouseOver())
			PrepareBitmap(bPrepareNow);
	}

	inline COLORREF GetActiveColor() const { return m_clrActive; }


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXStaticMenuItem)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COXStaticMenuItem();

	// Generated message map functions
protected:

	// helper to notify parent about COXStaticMenuItem events
	void NotifyParent(int nEventID);

	//{{AFX_MSG(COXStaticMenuItem)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LONG OnMouseEnter(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_OXSSTATICMENUITEM_H__)
