// PropertyPageNewControls.cpp : implementation file
//

#include "stdafx.h"
#include "CoolControls.h"
#include "PropertyPageNewControls.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if _MSC_VER > 0x0421

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageNewControls property page

IMPLEMENT_DYNCREATE(CPropertyPageNewControls, CPropertyPage)

CPropertyPageNewControls::CPropertyPageNewControls() : CPropertyPage(CPropertyPageNewControls::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPageNewControls)
	m_bDisable = FALSE;
	//}}AFX_DATA_INIT
}

CPropertyPageNewControls::~CPropertyPageNewControls()
{
}

void CPropertyPageNewControls::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageNewControls)
	DDX_Control(pDX, IDC_IPADDRESS, m_ipAddress);
	DDX_Control(pDX, IDC_MONTHCALENDAR, m_monthCal);
	DDX_Control(pDX, IDC_DATETIMEPICKER_UPDOWN, m_dtpUpDown);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DROPDOWN, m_dtpDropDown);
	DDX_Control(pDX, IDC_CHECK_DISABLE_ALL, m_btnDisable);
	DDX_Check(pDX, IDC_CHECK_DISABLE_ALL, m_bDisable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageNewControls, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageNewControls)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_ALL, OnCheckDisableAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageNewControls message handlers

void CPropertyPageNewControls::OnCheckDisableAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CWnd* pChildWnd=GetWindow(GW_CHILD);
	while(pChildWnd!=NULL)
	{
		if(pChildWnd!=&m_btnDisable)
			pChildWnd->EnableWindow(!m_bDisable);
		pChildWnd=pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}

BOOL CPropertyPageNewControls::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#endif // _MSC_VER > 0x0421
