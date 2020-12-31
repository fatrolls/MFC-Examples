// MFCATL_OCXCtl.cpp : Implementation of the CMFCATL_OCXCtrl ActiveX Control class.

#include "stdafx.h"
#include "MFCATL_OCX.h"
#include "MFCATL_OCXCtl.h"
#include "MFCATL_OCXPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMFCATL_OCXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMFCATL_OCXCtrl, COleControl)
	//{{AFX_MSG_MAP(CMFCATL_OCXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMFCATL_OCXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMFCATL_OCXCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CMFCATL_OCXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMFCATL_OCXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CMFCATL_OCXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMFCATL_OCXCtrl, 1)
	PROPPAGEID(CMFCATL_OCXPropPage::guid)
END_PROPPAGEIDS(CMFCATL_OCXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMFCATL_OCXCtrl, "MFCATLOCX.MFCATLOCXCtrl.1",
	0xa9ee6e84, 0x5f04, 0x11d1, 0x93, 0x4c, 0xe4, 0xcf, 0xda, 0, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMFCATL_OCXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMFCATL_OCX =
		{ 0xa9ee6e82, 0x5f04, 0x11d1, { 0x93, 0x4c, 0xe4, 0xcf, 0xda, 0, 0, 0 } };
const IID BASED_CODE IID_DMFCATL_OCXEvents =
		{ 0xa9ee6e83, 0x5f04, 0x11d1, { 0x93, 0x4c, 0xe4, 0xcf, 0xda, 0, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwMFCATL_OCXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMFCATL_OCXCtrl, IDS_MFCATL_OCX, _dwMFCATL_OCXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXCtrl::CMFCATL_OCXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMFCATL_OCXCtrl

BOOL CMFCATL_OCXCtrl::CMFCATL_OCXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MFCATL_OCX,
			IDB_MFCATL_OCX,
			afxRegApartmentThreading,
			_dwMFCATL_OCXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXCtrl::CMFCATL_OCXCtrl - Constructor

CMFCATL_OCXCtrl::CMFCATL_OCXCtrl()
{
	InitializeIIDs(&IID_DMFCATL_OCX, &IID_DMFCATL_OCXEvents);

   ::MessageBox(NULL,"ctor CMFCATL_OCXCtrl","MFCATL",MB_OK);
}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXCtrl::~CMFCATL_OCXCtrl - Destructor

CMFCATL_OCXCtrl::~CMFCATL_OCXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXCtrl::OnDraw - Drawing function

void CMFCATL_OCXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXCtrl::DoPropExchange - Persistence support

void CMFCATL_OCXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXCtrl::OnResetState - Reset control to default state

void CMFCATL_OCXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXCtrl::AboutBox - Display an "About" box to the user

void CMFCATL_OCXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MFCATL_OCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXCtrl message handlers
