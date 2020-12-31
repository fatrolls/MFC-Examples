///////////////////////////////////////////////////////////////////
//  Module  : JIGGLER.H
//
//  Purpose : Main header file for JIGGLER.OCX
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-27-96
///////////////////////////////////////////////////////////////////

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////
// The CJigglerApp class

class CJigglerApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

// Externals
extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

///////////////////////////////////////////////////////////////////

