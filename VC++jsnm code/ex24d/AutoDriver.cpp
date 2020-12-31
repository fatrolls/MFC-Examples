// Machine generated IDispatch wrapper class(es) created with ClassWizard
// AutoDriver.cpp

#include "stdafx.h"
#include "autoDriver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IEx24bAuto properties

long IEx24bAuto::GetLongData()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void IEx24bAuto::SetLongData(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

VARIANT IEx24bAuto::GetTextData()
{
	VARIANT result;
	GetProperty(0x2, VT_VARIANT, (void*)&result);
	return result;
}

void IEx24bAuto::SetTextData(const VARIANT& propVal)
{
	SetProperty(0x2, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IEx24bAuto operations

BOOL IEx24bAuto::DisplayDialog()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}
