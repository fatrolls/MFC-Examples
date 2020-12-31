// AutoWindow.cpp : implementation file
//

#include "stdafx.h"
#include "AutoPie.h"
#include "AutoWindow.h"
#include "AutoPieDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoWindow

IMPLEMENT_DYNCREATE(CAutoWindow, CCmdTarget)

CAutoWindow::CAutoWindow()
{
	EnableAutomation();
}

CAutoWindow::~CAutoWindow()
{
}


void CAutoWindow::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CAutoWindow, CCmdTarget)
	//{{AFX_MSG_MAP(CAutoWindow)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoWindow, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CAutoWindow)
	DISP_PROPERTY_EX(CAutoWindow, "Visible", GetVisible, SetVisible, VT_BOOL)
	DISP_FUNCTION(CAutoWindow, "Refresh", Refresh, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IAutoWindow to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {3B5BA320-3B72-11D2-AC82-006008A8274D}
static const IID IID_IAutoWindow =
{ 0x3b5ba320, 0x3b72, 0x11d2, { 0xac, 0x82, 0x0, 0x60, 0x8, 0xa8, 0x27, 0x4d } };

BEGIN_INTERFACE_MAP(CAutoWindow, CCmdTarget)
	INTERFACE_PART(CAutoWindow, IID_IAutoWindow, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoWindow message handlers

void CAutoWindow::Refresh() 
{
	CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
	CAutoPieDoc* pDoc = (CAutoPieDoc*) pFrame->GetActiveDocument ();
	pDoc->UpdateAllViews (NULL);
}

BOOL CAutoWindow::GetVisible() 
{
	return AfxGetMainWnd ()->IsWindowVisible ();
}

void CAutoWindow::SetVisible(BOOL bNewValue) 
{
	AfxGetMainWnd ()->ShowWindow (bNewValue ? SW_SHOW : SW_HIDE);
}
