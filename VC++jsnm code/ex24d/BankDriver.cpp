// Machine generated IDispatch wrapper class(es) created with ClassWizard
// BankDriver.cpp

#include "stdafx.h"
#include "bankDriver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IBank properties

double IBank::GetBalance()
{
	double result;
	GetProperty(0x1, VT_R8, (void*)&result);
	return result;
}

void IBank::SetBalance(double propVal)
{
	SetProperty(0x1, VT_R8, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IBank operations

double IBank::Withdrawal(double dAmount)
{
	double result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		dAmount);
	return result;
}

void IBank::Deposit(double dAmount)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 dAmount);
}
