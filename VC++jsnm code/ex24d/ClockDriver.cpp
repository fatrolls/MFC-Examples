// Machine generated IDispatch wrapper class(es) created with ClassWizard
// ClockDriver.cpp

#include "stdafx.h"
#include "clockDriver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IEx24c properties

DATE IEx24c::GetTime()
{
	DATE result;
	GetProperty(0x1, VT_DATE, (void*)&result);
	return result;
}

void IEx24c::SetTime(DATE propVal)
{
	SetProperty(0x1, VT_DATE, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IEx24c operations

VARIANT IEx24c::GetFigure(short n)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		n);
	return result;
}

void IEx24c::SetFigure(short n, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 n, &newValue);
}

void IEx24c::ShowWin()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IEx24c::CreateAlarm(DATE Time)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Time);
	return result;
}

void IEx24c::RefreshWin()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAlarm properties

DATE IAlarm::GetTime()
{
	DATE result;
	GetProperty(0x1, VT_DATE, (void*)&result);
	return result;
}

void IAlarm::SetTime(DATE propVal)
{
	SetProperty(0x1, VT_DATE, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IAlarm operations
