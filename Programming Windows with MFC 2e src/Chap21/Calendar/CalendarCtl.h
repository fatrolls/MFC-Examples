#if !defined(AFX_CALENDARCTL_H__68932D29_CFE2_11D2_9282_00C04F8ECF0C__INCLUDED_)
#define AFX_CALENDARCTL_H__68932D29_CFE2_11D2_9282_00C04F8ECF0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CalendarCtl.h : Declaration of the CCalendarCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CCalendarCtrl : See CalendarCtl.cpp for implementation.

class CCalendarCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCalendarCtrl)

// Constructor
public:
	CCalendarCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL LeapYear(int nYear);
	static const int m_nDaysPerMonth[];
	int m_nDay;
	int m_nMonth;
	int m_nYear;
	~CCalendarCtrl();

	DECLARE_OLECREATE_EX(CCalendarCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CCalendarCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCalendarCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CCalendarCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CCalendarCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CCalendarCtrl)
	BOOL m_bRedSundays;
	afx_msg void OnRedSundaysChanged();
	afx_msg DATE GetDate();
	afx_msg BOOL SetDate(short nYear, short nMonth, short nDay);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CCalendarCtrl)
	void FireNewDay(short nDay)
		{FireEvent(eventidNewDay,EVENT_PARAM(VTS_I2), nDay);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CCalendarCtrl)
	dispidRedSundays = 1L,
	dispidGetDate = 2L,
	dispidSetDate = 3L,
	eventidNewDay = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARCTL_H__68932D29_CFE2_11D2_9282_00C04F8ECF0C__INCLUDED)
