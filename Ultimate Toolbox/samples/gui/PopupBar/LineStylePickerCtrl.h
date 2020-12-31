#if !defined(_LINESTYLEPICKERCTRL_H_)
#define _LINESTYLEPICKERCTRL_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXPopupBarCtrl.h"
#include "Resource.h"


// LineStylePickerCtrl.h : header file
//

// line styles
#define ID_LINE_1PX						0
#define ID_LINE_2PX						1
#define ID_LINE_3PX						2
#define ID_LINE_4PX						3
#define ID_LINE_6PX						4
#define ID_LINE_3PX_2LINES				5
#define ID_LINE_4PX_2LINES				6
#define ID_LINE_4PX_2LINES_REVERSE		7
#define ID_LINE_7PX_3LINES				8

// the number of predefined tooltiptext
#define LINESTYLEPICK_DEFINEDSTYLES		9

/////////////////////////////////////////////////////////////////////////////
// CLineStylePickerCtrl window

class CLineStylePickerCtrl : public COXPopupBarCtrl
{
// Construction
public:
	CLineStylePickerCtrl(UINT nButtons=LINESTYLEPICK_DEFINEDSTYLES, 
		UINT nRows=LINESTYLEPICK_DEFINEDSTYLES, DWORD dwDefault=ID_LINE_1PX,
		CSize sizeButton=CSize(120,18),	int nIDDefault=IDS_DEFAULT,
		int nIDCustom=IDS_CUSTOM);

// Data
protected:
	static DWORD m_defaultLineStyles[];
	static LPCTSTR m_defaultArrToolTipText[];

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

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineStylePickerCtrl)
	//}}AFX_VIRTUAL
public:
	virtual ~CLineStylePickerCtrl() {} ;

// implementation
protected:
	virtual void DrawButton(CDC* pDC, UINT nIndex);

// Generated message map functions
protected:
	//{{AFX_MSG(CLineStylePickerCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_LINESTYLEPICKERCTRL_H_)
