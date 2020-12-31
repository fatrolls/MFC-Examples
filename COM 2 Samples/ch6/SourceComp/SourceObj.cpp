// SourceObj.cpp : implementation file
//

#include "stdafx.h"
#include "SourceComp.h"
#include "SourceObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSourceObj

IMPLEMENT_DYNCREATE(CSourceObj, CCmdTarget)

CSourceObj::CSourceObj()
{
	EnableAutomation();
	EnableConnections();
}

CSourceObj::~CSourceObj()
{
}


void CSourceObj::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSourceObj, CCmdTarget)
	//{{AFX_MSG_MAP(CSourceObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSourceObj, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CSourceObj)
	DISP_PROPERTY_EX(CSourceObj, "MyProperty", GetMyProperty, SetMyProperty, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISourceObj to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {B77C2984-56DD-11CF-B355-00104B08CC22}
static const IID IID_ISourceObj =
{ 0xb77c2984, 0x56dd, 0x11cf, { 0xb3, 0x55, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 } };
// {B77C2985-56DD-11CF-B355-00104B08CC22}
static const IID IID_IEventSet =
{ 0xb77c2985, 0x56dd, 0x11cf, { 0xb3, 0x55, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 } };

IMPLEMENT_OLECREATE(CSourceObj, "SourceComp.SourceObj",
	0xb77c2986, 0x56dd, 0x11cf, 0xb3, 0x55, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 )

BEGIN_INTERFACE_MAP(CSourceObj, CCmdTarget)
	INTERFACE_PART(CSourceObj, IID_ISourceObj, Dispatch)
	INTERFACE_PART(CSourceObj, IID_IConnectionPointContainer, ConnPtContainer)
END_INTERFACE_MAP()

BEGIN_CONNECTION_MAP(CSourceObj, CCmdTarget)
	CONNECTION_PART(CSourceObj, IID_IEventSet, EventSetConnPt)
END_CONNECTION_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSourceObj message handlers
void CSourceObj::FirePropChanged (long nInt)
{
	COleDispatchDriver driver;

	POSITION pos = m_xEventSetConnPt.GetStartPosition();
	LPDISPATCH pDispatch;
	while (pos != NULL)
	{
		pDispatch = (LPDISPATCH) m_xEventSetConnPt.GetNextConnection(pos);
		ASSERT(pDispatch != NULL);
		driver.AttachDispatch(pDispatch, FALSE);
		TRY
			driver.InvokeHelper(0/*eventidPropChanged*/, DISPATCH_METHOD, VT_EMPTY, NULL,
				(BYTE *)(VTS_I4), nInt);
		END_TRY
		driver.DetachDispatch();
	}
}

REFIID CSourceObj::XEventSetConnPt::GetIID(void)
{
	return IID_IEventSet;
}

long CSourceObj::GetMyProperty() 
{
	// TODO: Add your property handler here

	return mProperty;
}

void CSourceObj::SetMyProperty(long nNewValue) 
{
	mProperty = nNewValue;
	FirePropChanged (mProperty);
}
