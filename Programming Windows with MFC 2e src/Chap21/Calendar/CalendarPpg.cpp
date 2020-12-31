// CalendarPpg.cpp : Implementation of the CCalendarPropPage property page class.

#include "stdafx.h"
#include "Calendar.h"
#include "CalendarPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCalendarPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCalendarPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CCalendarPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCalendarPropPage, "CALENDAR.CalendarPropPage.1",
	0x68932d1c, 0xcfe2, 0x11d2, 0x92, 0x82, 0, 0xc0, 0x4f, 0x8e, 0xcf, 0xc)


/////////////////////////////////////////////////////////////////////////////
// CCalendarPropPage::CCalendarPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CCalendarPropPage

BOOL CCalendarPropPage::CCalendarPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CALENDAR_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CCalendarPropPage::CCalendarPropPage - Constructor

CCalendarPropPage::CCalendarPropPage() :
	COlePropertyPage(IDD, IDS_CALENDAR_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CCalendarPropPage)
	m_bRedSundays = FALSE;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CCalendarPropPage::DoDataExchange - Moves data between page and properties

void CCalendarPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CCalendarPropPage)
	DDP_Check(pDX, IDC_REDSUNDAYS, m_bRedSundays, _T("RedSundays") );
	DDX_Check(pDX, IDC_REDSUNDAYS, m_bRedSundays);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CCalendarPropPage message handlers
