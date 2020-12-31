// MFCATL_OCXPpg.cpp : Implementation of the CMFCATL_OCXPropPage property page class.

#include "stdafx.h"
#include "MFCATL_OCX.h"
#include "MFCATL_OCXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMFCATL_OCXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMFCATL_OCXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMFCATL_OCXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMFCATL_OCXPropPage, "MFCATLOCX.MFCATLOCXPropPage.1",
	0xa9ee6e85, 0x5f04, 0x11d1, 0x93, 0x4c, 0xe4, 0xcf, 0xda, 0, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXPropPage::CMFCATL_OCXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMFCATL_OCXPropPage

BOOL CMFCATL_OCXPropPage::CMFCATL_OCXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MFCATL_OCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXPropPage::CMFCATL_OCXPropPage - Constructor

CMFCATL_OCXPropPage::CMFCATL_OCXPropPage() :
	COlePropertyPage(IDD, IDS_MFCATL_OCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMFCATL_OCXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXPropPage::DoDataExchange - Moves data between page and properties

void CMFCATL_OCXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMFCATL_OCXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXPropPage message handlers
