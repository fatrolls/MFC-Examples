// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "cgitooledrv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CCgiDispatchDrv properties

/////////////////////////////////////////////////////////////////////////////
// CCgiDispatchDrv operations

void CCgiDispatchDrv::SetOutput(LPCTSTR sOutput)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 sOutput);
}

CString CCgiDispatchDrv::GetInput(const VARIANT& vIndex)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		&vIndex);
	return result;
}

CString CCgiDispatchDrv::GetPathInfo()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CCgiDispatchDrv::GetScriptName()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CCgiDispatchDrv::GetAccepted()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CCgiDispatchDrv::GetRemoteAddress()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CCgiDispatchDrv::GetClientInfo(LPCTSTR sInfoKey)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		sInfoKey);
	return result;
}

CString CCgiDispatchDrv::GetServerName()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

short CCgiDispatchDrv::GetServerPort()
{
	short result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

CString CCgiDispatchDrv::GetServerProtocol()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CCgiDispatchDrv::GetServerSoftware()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}
