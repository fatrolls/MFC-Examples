#pragma once
// popupcalendar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPopupCalendar window

#include "ListCtrlCellWnd.h"
#include "MCCtrl.h"

class CCellDateCtrl;
class CMCCtrl;
class CPopupCalendar : public CListCtrlCellWnd
{
	friend class CMCCtrl;
// Construction
public:
	CPopupCalendar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupCalendar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPopupCalendar();
	void Create(HWND hParentWnd, CCellDateCtrl *pCellDateCtrl);
	void GetBoundingRect(const RECT &rcCellBounding, RECT &rcBounding, BOOL Downwards = TRUE);
	void OpenDropDown(const LPSYSTEMTIME pDateTime);
	void OnThemeChanged();
protected:
	CMCCtrl m_MonthCalCtrl;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CPopupCalendar)
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnMCSelect(NMHDR* pNMHDR, LRESULT* pResult);
	void OnMCSelchange(NMHDR* pNMHDR, LRESULT* pResult);
};