// AutoChart.cpp : implementation file
//

#include "stdafx.h"
#include "AutoPie.h"
#include "AutoChart.h"
#include "AutoPieDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoChart

IMPLEMENT_DYNCREATE(CAutoChart, CCmdTarget)

CAutoChart::CAutoChart()
{
	EnableAutomation();
}

CAutoChart::~CAutoChart()
{
}


void CAutoChart::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CAutoChart, CCmdTarget)
	//{{AFX_MSG_MAP(CAutoChart)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoChart, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CAutoChart)
	DISP_FUNCTION(CAutoChart, "Save", Save, VT_BOOL, VTS_BSTR)
	DISP_PROPERTY_PARAM(CAutoChart, "Revenue", GetRevenue, SetRevenue, VT_I4, VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IAutoChart to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {3B5BA31D-3B72-11D2-AC82-006008A8274D}
static const IID IID_IAutoChart =
{ 0x3b5ba31d, 0x3b72, 0x11d2, { 0xac, 0x82, 0x0, 0x60, 0x8, 0xa8, 0x27, 0x4d } };

BEGIN_INTERFACE_MAP(CAutoChart, CCmdTarget)
	INTERFACE_PART(CAutoChart, IID_IAutoChart, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoChart message handlers

BOOL CAutoChart::Save(LPCTSTR pszPath) 
{
	CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
	CAutoPieDoc* pDoc = (CAutoPieDoc*) pFrame->GetActiveDocument ();
	return pDoc->OnSaveDocument (pszPath);
}

long CAutoChart::GetRevenue(short nQuarter) 
{
	long lResult = -1;
	
	if (nQuarter >= 1 && nQuarter <= 4) {
		CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
		CAutoPieDoc* pDoc = (CAutoPieDoc*) pFrame->GetActiveDocument ();
		lResult = (long) pDoc->GetRevenue (nQuarter - 1);
	}
	else {
		//
		// If the quarter number is out of range, fail the call
		// and let the caller know precisely why it failed.
		//
		AfxThrowOleDispatchException (ID_ERROR_OUTOFRANGE,
			_T ("Invalid parameter specified when reading Revenue"));
	}
	return lResult;
}

void CAutoChart::SetRevenue(short nQuarter, long nNewValue) 
{
	if (nQuarter >= 1 && nQuarter <= 4) {
		CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
		CAutoPieDoc* pDoc = (CAutoPieDoc*) pFrame->GetActiveDocument ();
		pDoc->SetRevenue (nQuarter - 1, nNewValue);
	}
	else {
		//
		// If the quarter number is out of range, fail the call
		// and let the caller know precisely why it failed.
		//
		AfxThrowOleDispatchException (ID_ERROR_OUTOFRANGE,
			_T ("Invalid parameter specified when setting Revenue"));
	}
}
