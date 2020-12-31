#if !defined(_DASHSTYLEPICKERCTRL_H_)
#define _DASHSTYLEPICKERCTRL_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXPopupBarCtrl.h"
#include "Resource.h"


// DashStylePickerCtrl.h : header file
//

// dash styles
#define ID_DASH_SOLID					0
#define ID_DASH_DASH					1
#define ID_DASH_DOT						2
#define ID_DASH_DASHDOT					3
#define ID_DASH_DASHDOTDOT				4

// the number of predefined tooltiptext
#define DASHSTYLEPICK_DEFINEDSTYLES		5

/////////////////////////////////////////////////////////////////////////////
// CDashStylePickerCtrl window

class CDashStylePickerCtrl : public COXPopupBarCtrl
{
// Construction
public:
	CDashStylePickerCtrl(UINT nButtons=DASHSTYLEPICK_DEFINEDSTYLES, 
		UINT nRows=DASHSTYLEPICK_DEFINEDSTYLES, DWORD dwDefault=ID_DASH_SOLID,
		CSize sizeButton=CSize(100,18), int nIDDefault=IDS_DEFAULT,
		int nIDCustom=IDS_CUSTOM);

// Data
protected:
	static DWORD m_defaultDashStyles[];

	static ButtonToolTipIDTable m_defaultArrToolTipText[];

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
	//{{AFX_VIRTUAL(CDashStylePickerCtrl)
	//}}AFX_VIRTUAL
public:
	virtual ~CDashStylePickerCtrl() {} ;

// implementation
protected:
	virtual void DrawButton(CDC* pDC, UINT nIndex);

// Generated message map functions
protected:
	//{{AFX_MSG(CDashStylePickerCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_DASHSTYLEPICKERCTRL_H_)
