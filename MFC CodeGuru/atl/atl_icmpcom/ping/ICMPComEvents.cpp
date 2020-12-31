// ICMPComEvents.cpp : implementation file
//

#include "stdafx.h"
#include "..\\icmpcom_i.c"
#include "ping.h"
#include "ICMPComEvents.h"
#include "pingdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ICMPComEvents

IMPLEMENT_DYNCREATE(ICMPComEvents, CCmdTarget)

ICMPComEvents::ICMPComEvents(CPingDlg* pParent) :m_pParent(pParent)
{
	ASSERT(m_pParent);
	EnableAutomation();  // needed to sink events
}

ICMPComEvents::~ICMPComEvents()
{
}


BEGIN_MESSAGE_MAP(ICMPComEvents, CCmdTarget)
	//{{AFX_MSG_MAP(ICMPComEvents)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(ICMPComEvents,CCmdTarget)
	DISP_FUNCTION_ID(ICMPComEvents,
						"PingMsgEvent",
						0x1,
						OnPingMsgEvent,
						VT_EMPTY,VTS_BSTR)
	DISP_FUNCTION_ID(ICMPComEvents,
						"PingDoneEvent",
						0x2,
						OnPingDone,
						VT_EMPTY,VTS_NONE)
	DISP_FUNCTION_ID(ICMPComEvents,
						"PingTerminated",
						0x3,
						OnPingTerminated,
						VT_EMPTY,VTS_NONE)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(ICMPComEvents,CCmdTarget)
	INTERFACE_PART(ICMPComEvents,DIID_DICMPComEvent,Dispatch)
END_INTERFACE_MAP()



/////////////////////////////////////////////////////////////////////////////
// ICMPComEvents message handlers
void ICMPComEvents::OnPingMsgEvent(LPCTSTR lpmsg)
{

	m_pParent->m_pingoutlb.InsertString(-1,lpmsg);
	return;
}

void ICMPComEvents::OnPingDone()
{
	m_pParent->m_pingoutlb.InsertString(-1,"Ping Done!");
	return;

}

void ICMPComEvents::OnPingTerminated()
{
	m_pParent->m_pingoutlb.InsertString(-1,"Ping Terminated!");

	return;

}