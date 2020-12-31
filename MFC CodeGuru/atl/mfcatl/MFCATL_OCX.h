#if !defined(AFX_MFCATL_OCX_H__A9EE6E8A_5F04_11D1_934C_E4CFDA000000__INCLUDED_)
#define AFX_MFCATL_OCX_H__A9EE6E8A_5F04_11D1_934C_E4CFDA000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MFCATL_OCX.h : main header file for MFCATL_OCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXApp : See MFCATL_OCX.cpp for implementation.

class CMFCATL_OCXApp : public COleControlModule
{
   typedef COleControlModule super;
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCATL_OCX_H__A9EE6E8A_5F04_11D1_934C_E4CFDA000000__INCLUDED)
