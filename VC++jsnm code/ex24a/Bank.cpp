// Bank.cpp : implementation file
//

#include "stdafx.h"
#include "ex24a.h"
#include "Bank.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBank

IMPLEMENT_DYNCREATE(CBank, CCmdTarget)

CBank::CBank()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
    m_dBalance = 0.0;
}

CBank::~CBank()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CBank::OnFinalRelease()
{
	// When the last reference for an automation object is released,
	//  OnFinalRelease is called.  This implementation deletes the 
	//  object.  Add additional cleanup required for your object before
	//  deleting it from memory.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CBank, CCmdTarget)
	//{{AFX_MSG_MAP(CBank)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBank, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CBank)
	DISP_PROPERTY_EX(CBank, "Balance", GetBalance, SetBalance, VT_R8)
	DISP_FUNCTION(CBank, "Withdrawal", Withdrawal, VT_R8, VTS_R8)
	DISP_FUNCTION(CBank, "Deposit", Deposit, VT_EMPTY, VTS_R8)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IBank to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {A9515AB6-5B85-11D0-848F-00400526305B}
static const IID IID_IBank =
{ 0xa9515ab6, 0x5b85, 0x11d0, { 0x84, 0x8f, 0x0, 0x40, 0x5, 0x26, 
    0x30, 0x5b } };

BEGIN_INTERFACE_MAP(CBank, CCmdTarget)
	INTERFACE_PART(CBank, IID_IBank, Dispatch)
END_INTERFACE_MAP()

// {632B1E4C-F287-11CE-B5E3-00AA005B1574}
IMPLEMENT_OLECREATE2(CBank, "ex24a.Bank", 0x632b1e4c, 0xf287, 0x11ce, 
	0xb5, 0xe3, 0x0, 0xaa, 0x0, 0x5b, 0x15, 0x74)

/////////////////////////////////////////////////////////////////////////////
// CBank message handlers

double CBank::Withdrawal(double dAmount) 
{
    if (dAmount < 0.0) {
      return 0.0;
    }
    if (dAmount <= m_dBalance) {
      m_dBalance -= dAmount;
      return dAmount;
    }
    double dTemp = m_dBalance;
    m_dBalance = 0.0;
    return dTemp;
}

void CBank::Deposit(double dAmount) 
{
    if (dAmount < 0.0) {
      return;
    }
    m_dBalance += dAmount;
}

double CBank::GetBalance() 
{
    return m_dBalance;
}

void CBank::SetBalance(double newValue) 
{
    TRACE("Sorry, Dave, I can't do that!\n");
}
