#if !defined(_BORDERPICKERCTRL_H_)
#define _BORDERPICKERCTRL_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXPopupBarCtrl.h"
#include "Resource.h"

// BorderPickerCtrl.h : header file
//

// border styles
#define ID_BORDER_NONE				0x00000000
#define ID_BORDER_TOP				0x00000001
#define ID_BORDER_BOTTOM			0x00000002
#define ID_BORDER_LEFT				0x00000004
#define ID_BORDER_RIGHT				0x00000008
#define ID_BORDER_OUTSIDE			ID_BORDER_TOP|ID_BORDER_BOTTOM|ID_BORDER_LEFT|ID_BORDER_RIGHT
#define ID_BORDER_HORZ_INSIDE		0x00010000
#define ID_BORDER_VERT_INSIDE		0x00020000
#define ID_BORDER_INSIDE			ID_BORDER_HORZ_INSIDE|ID_BORDER_VERT_INSIDE
#define ID_BORDER_ALL				ID_BORDER_OUTSIDE|ID_BORDER_INSIDE

// the number of predefined tooltiptext
#define BORDERPICK_DEFINEDSTYLES	10

/////////////////////////////////////////////////////////////////////////////
// CBorderPickerCtrl window

class CBorderPickerCtrl : public COXPopupBarCtrl
{
// Construction
public:
	CBorderPickerCtrl(UINT nButtons=BORDERPICK_DEFINEDSTYLES, UINT nRows=2, 
		DWORD dwDefault=ID_BORDER_ALL, CSize sizeButton=CSize(19,19),
		int nIDDefault=IDS_DEFAULT, int nIDCustom=IDS_CUSTOM);

// Data
protected:
	static DWORD m_defaultBorderStyles[];

	static ButtonToolTipIDTable m_defaultArrToolTipText[];

	CImageList m_ilStyles;

// data for inner use

// Attributes
public:

// Operations
public:
	virtual BOOL Pick(UINT nAlignment=ID_POPUPBAR_ALIGNBOTTOM, CRect* pParentRect=NULL, 
		CSize sizeOffset=CSize(0,0));

	// sets selected color
	inline void SetSelectedStyle(DWORD dwSelected) { SetSelectedData(dwSelected); }
	// returns selected color
	inline DWORD GetSelectedStyle() { return GetSelectedData(); }
	// sets default color
	inline void SetDefaultStyle(DWORD dwDefault) { SetDefaultData(dwDefault); }
	// returns default color
	inline DWORD GetDefaultStyle() { return GetDefaultData(); }

	inline BOOL SetStylesImages(UINT nBitmapID, int cx, int nGrow, COLORREF crMask) 
	{
		return SetStylesImages(MAKEINTRESOURCE(nBitmapID), cx, nGrow, crMask);
	}
	inline BOOL SetStylesImages(LPCTSTR lpszBitmapID, int cx, int nGrow, COLORREF crMask)
	{
		return m_ilStyles.Create(lpszBitmapID, cx, nGrow, crMask);
	}

	inline CImageList* GetStylesImages() { return &m_ilStyles; }

	static int FindImageIndexFromStyle(DWORD dwStyle);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBorderPickerCtrl)
	//}}AFX_VIRTUAL
public:
	virtual ~CBorderPickerCtrl() {} ;

// implementation
protected:
	virtual void DrawButton(CDC* pDC, UINT nIndex);

// Generated message map functions
protected:
	//{{AFX_MSG(CBorderPickerCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_BORDERPICKERCTRL_H_)
