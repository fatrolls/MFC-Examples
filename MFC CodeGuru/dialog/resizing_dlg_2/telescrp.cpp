// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "telescrp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// ITeleSc properties

BOOL ITeleSc::GetFinished()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void ITeleSc::SetFinished(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

BOOL ITeleSc::GetServer()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void ITeleSc::SetServer(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL ITeleSc::GetAsciiOut()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void ITeleSc::SetAsciiOut(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

short ITeleSc::GetResultCode()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}

void ITeleSc::SetResultCode(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}

BOOL ITeleSc::GetTestMode()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}

void ITeleSc::SetTestMode(BOOL propVal)
{
	SetProperty(0x5, VT_BOOL, propVal);
}

BOOL ITeleSc::GetCallStarted()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void ITeleSc::SetCallStarted(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// ITeleSc operations

BOOL ITeleSc::ToScript(LPCTSTR FieldLabel, LPCTSTR Value)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		FieldLabel, Value);
	return result;
}

void ITeleSc::ShutDown()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL ITeleSc::OpenScript(LPCTSTR FullPath)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		FullPath);
	return result;
}

BOOL ITeleSc::FromScript(LPCTSTR Label, BSTR* Value)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_PBSTR;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Label, Value);
	return result;
}

BOOL ITeleSc::ResetScript()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT ITeleSc::GetValue(LPCTSTR FieldName)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		FieldName);
	return result;
}

void ITeleSc::AddResultCode(LPCTSTR Name, short Code, short Callback)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_I2;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, Code, Callback);
}

void ITeleSc::BringMainWindowToTop()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL ITeleSc::OutputValues(LPCTSTR szPath, LPCTSTR szOperator, short iResultCode, long lDuration, short iOutputMode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I2 VTS_I4 VTS_I2;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		szPath, szOperator, iResultCode, lDuration, iOutputMode);
	return result;
}

void ITeleSc::HideMainWindow()
{
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL ITeleSc::MakeDst(LPCTSTR szPath)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		szPath);
	return result;
}

CString ITeleSc::GetFirstFieldName()
{
	CString result;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ITeleSc::GetNextFieldName()
{
	CString result;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}
