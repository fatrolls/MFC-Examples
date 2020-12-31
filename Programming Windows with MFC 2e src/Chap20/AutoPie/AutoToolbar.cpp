// AutoToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "AutoPie.h"
#include "AutoToolbar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoToolbar

IMPLEMENT_DYNCREATE(CAutoToolbar, CCmdTarget)

CAutoToolbar::CAutoToolbar()
{
	EnableAutomation();
}

CAutoToolbar::~CAutoToolbar()
{
}


void CAutoToolbar::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CAutoToolbar, CCmdTarget)
	//{{AFX_MSG_MAP(CAutoToolbar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoToolbar, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CAutoToolbar)
	DISP_PROPERTY_EX(CAutoToolbar, "Visible", GetVisible, SetVisible, VT_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IAutoToolbar to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {3B5BA323-3B72-11D2-AC82-006008A8274D}
static const IID IID_IAutoToolbar =
{ 0x3b5ba323, 0x3b72, 0x11d2, { 0xac, 0x82, 0x0, 0x60, 0x8, 0xa8, 0x27, 0x4d } };

BEGIN_INTERFACE_MAP(CAutoToolbar, CCmdTarget)
	INTERFACE_PART(CAutoToolbar, IID_IAutoToolbar, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoToolbar message handlers

BOOL CAutoToolbar::GetVisible() 
{
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd ();
	return (pFrame->m_wndToolBar.GetStyle () & WS_VISIBLE) ?
		TRUE : FALSE;
}

void CAutoToolbar::SetVisible(BOOL bNewValue) 
{
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd ();
	pFrame->ShowControlBar (&pFrame->m_wndToolBar, bNewValue, FALSE);
}
