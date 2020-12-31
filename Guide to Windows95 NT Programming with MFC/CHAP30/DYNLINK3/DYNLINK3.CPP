///////////////////////////////////////////////////////////////////
//  Header  : DYNLINK3.CPP
//
//  Purpose : Implementation file for the DYNLINK3.DLL
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 06-02-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxdllx.h>

static AFX_EXTENSION_MODULE DynLink3DLL = { NULL, NULL };

// The DLL entry point
extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   if (dwReason == DLL_PROCESS_ATTACH)
   {
      TRACE0("DYNLINK3.DLL Initializing!\n");
      
      // Extension DLL one-time initialization
      AfxInitExtensionModule(DynLink3DLL, hInstance);

      // Insert this DLL into the resource chain
      new CDynLinkLibrary(DynLink3DLL);
   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      TRACE0("DYNLINK3.DLL Terminating!\n");
   }
   return 1;   // ok
}

///////////////////////////////////////////////////////////////////
