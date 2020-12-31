// NGTLB10.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE NGTLB10DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("NGTLB10.DLL Initializing!\n");
		
		if (!AfxInitExtensionModule(NGTLB10DLL, hInstance))
			return 0;

		new CDynLinkLibrary(NGTLB10DLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("NGTLB10.DLL Terminating!\n");
		AfxTermExtensionModule(NGTLB10DLL);
	}
	return 1;
}
