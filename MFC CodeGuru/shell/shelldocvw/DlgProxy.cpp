// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "shelldoc.h"
#include "DlgProxy.h"
#include "shelldocDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShelldocDlgAutoProxy

IMPLEMENT_DYNCREATE(CShelldocDlgAutoProxy, CCmdTarget)

CShelldocDlgAutoProxy::CShelldocDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CShelldocDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CShelldocDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CShelldocDlgAutoProxy::~CShelldocDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	AfxOleUnlockApp();
}

void CShelldocDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CShelldocDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CShelldocDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CShelldocDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CShelldocDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IShelldoc to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {A773FE74-4192-11D1-AE13-006097D60BAC}
static const IID IID_IShelldoc =
{ 0xa773fe74, 0x4192, 0x11d1, { 0xae, 0x13, 0x0, 0x60, 0x97, 0xd6, 0xb, 0xac } };

BEGIN_INTERFACE_MAP(CShelldocDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CShelldocDlgAutoProxy, IID_IShelldoc, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {A773FE72-4192-11D1-AE13-006097D60BAC}
IMPLEMENT_OLECREATE2(CShelldocDlgAutoProxy, "Shelldoc.Application", 0xa773fe72, 0x4192, 0x11d1, 0xae, 0x13, 0x0, 0x60, 0x97, 0xd6, 0xb, 0xac)

/////////////////////////////////////////////////////////////////////////////
// CShelldocDlgAutoProxy message handlers
