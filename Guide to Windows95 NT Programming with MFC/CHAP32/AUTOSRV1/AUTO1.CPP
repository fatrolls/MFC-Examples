///////////////////////////////////////////////////////////////////
// Module  : AUTO1.CPP
//
// Purpose : Shows how to create a basic OLE Automation server
//           using MFC.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 07-06-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoSrv1.h"
#include "Auto1.h"

///////////////////////////////////////////////////////////////////
// CAuto1

IMPLEMENT_DYNCREATE(CAuto1, CCmdTarget)

CAuto1::CAuto1()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CAuto1::~CAuto1()
{
	// To terminate the application when all objects created with
	// OLE automation die, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CAuto1::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// delete the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

///////////////////////////////////////////////////////////////////
// Dispatch map for the class

BEGIN_DISPATCH_MAP(CAuto1, CCmdTarget)
	DISP_FUNCTION(CAuto1, "CalcGrossPay", CalcGrossPay, VT_R4, 
      VTS_R4 VTS_R4)
END_DISPATCH_MAP()

// Note: we add support for IID_IAuto1 to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {C8DD94E0-D803-11CF-A3BC-444553540000}
static const IID IID_IAuto1 =
{ 
   0xc8dd94e0, 0xd803, 0x11cf, 
   { 
      0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 
   } 
};

BEGIN_INTERFACE_MAP(CAuto1, CCmdTarget)
	INTERFACE_PART(CAuto1, IID_IAuto1, Dispatch)
END_INTERFACE_MAP()

// {C8DD94E1-D803-11CF-A3BC-444553540000}
IMPLEMENT_OLECREATE(CAuto1, "AUTOSRV1.AUTO1",  0xc8dd94e1, \
   0xd803, 0x11cf, 0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0)

///////////////////////////////////////////////////////////////////
// CAuto1::CalcGrossPay()

float CAuto1::CalcGrossPay(float fHourlyWage, float fHoursWorked) 
{
   return (fHourlyWage * fHoursWorked);
}
