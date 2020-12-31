#if !defined(AFX_CALENDAR_H__68932D21_CFE2_11D2_9282_00C04F8ECF0C__INCLUDED_)
#define AFX_CALENDAR_H__68932D21_CFE2_11D2_9282_00C04F8ECF0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Calendar.h : main header file for CALENDAR.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalendarApp : See Calendar.cpp for implementation.

class CCalendarApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDAR_H__68932D21_CFE2_11D2_9282_00C04F8ECF0C__INCLUDED)
