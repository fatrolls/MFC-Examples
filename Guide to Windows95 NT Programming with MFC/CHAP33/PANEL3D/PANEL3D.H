///////////////////////////////////////////////////////////////////
//  Module  : PANEL3D.H
//
//  Purpose : Main header for PANEL3D.DLL
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-10-96
///////////////////////////////////////////////////////////////////

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////
// CPanel3dApp - Application (DLL) class

class CPanel3dApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

///////////////////////////////////////////////////////////////////
