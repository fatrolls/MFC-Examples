// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "icmpcom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// ICMPCom properties

/////////////////////////////////////////////////////////////////////////////
// ICMPCom operations

void ICMPCom::StartICMP()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICMPCom::StopICMP()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICMPCom::SetPingVariables(LPCTSTR hostname, long opttrcrt, long optresolve, long optnofrag, long optruntointerupt, long optttl, long optpacketlen, long optnumpackets, long optrroutenum, long opttimestamp, long opttos, long opttimeout)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hostname, opttrcrt, optresolve, optnofrag, optruntointerupt, optttl, optpacketlen, optnumpackets, optrroutenum, opttimestamp, opttos, opttimeout);
}

void ICMPCom::RunPing()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICMPCom::StopPing()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
