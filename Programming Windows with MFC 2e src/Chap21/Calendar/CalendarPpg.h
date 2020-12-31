#if !defined(AFX_CALENDARPPG_H__68932D2B_CFE2_11D2_9282_00C04F8ECF0C__INCLUDED_)
#define AFX_CALENDARPPG_H__68932D2B_CFE2_11D2_9282_00C04F8ECF0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CalendarPpg.h : Declaration of the CCalendarPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CCalendarPropPage : See CalendarPpg.cpp.cpp for implementation.

class CCalendarPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCalendarPropPage)
	DECLARE_OLECREATE_EX(CCalendarPropPage)

// Constructor
public:
	CCalendarPropPage();

// Dialog Data
	//{{AFX_DATA(CCalendarPropPage)
	enum { IDD = IDD_PROPPAGE_CALENDAR };
	BOOL	m_bRedSundays;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CCalendarPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARPPG_H__68932D2B_CFE2_11D2_9282_00C04F8ECF0C__INCLUDED)
