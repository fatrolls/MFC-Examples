///////////////////////////////////////////////////////////////////
//  Module  : JIGGLER.CPP
//
//  Purpose : Implementation of CJigglerApp and DLL registration.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-27-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Jiggler.h"

const GUID CDECL BASED_CODE _tlid =
{ 
   0x5cd2fc80, 0xe7bd, 0x11cf, 
   { 
      0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 0, 0 
   } 
};

const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

////////////////////////////////////////////////////////////////////////////
// CJigglerApp::InitInstance - DLL initialization

BOOL CJigglerApp::InitInstance()
{
   BOOL bInit = COleControlModule::InitInstance();

   if (bInit)
   {
      // You could add your own module initialization code here.
   }

   return bInit;
}

///////////////////////////////////////////////////////////////////
// CJigglerApp::ExitInstance - DLL termination

int CJigglerApp::ExitInstance()
{
   // TODO: Add your own module termination code here.

   return COleControlModule::ExitInstance();
}

///////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
   AFX_MANAGE_STATE(_afxModuleAddrThis);

   if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
      return ResultFromScode(SELFREG_E_TYPELIB);

   if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
      return ResultFromScode(SELFREG_E_CLASS);

   return NOERROR;
}

///////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
   AFX_MANAGE_STATE(_afxModuleAddrThis);

   if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
      return ResultFromScode(SELFREG_E_TYPELIB);

   if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
      return ResultFromScode(SELFREG_E_CLASS);

   return NOERROR;
}

///////////////////////////////////////////////////////////////////
// The sole application (DLL) object

CJigglerApp MyActiveXControl;

///////////////////////////////////////////////////////////////////







