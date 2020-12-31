// PropertyPageSource.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ScreenGrabber.h"
#include "PropertyPageSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageSource property page

//IMPLEMENT_DYNCREATE(CPropertyPageSource, COXContextHelpPropertyPage)

// array of control IDs and corresponding help IDs
const DWORD CPropertyPageSource::m_nHelpIDs[] = 
{
	IDC_RADIO_CURRENT_WINDOW, IDH_RADIO_CURRENT_WINDOW,
	IDC_RADIO_CLIENT_WINDOW, IDH_RADIO_CLIENT_WINDOW,
	IDC_RADIO_FULL_SCREEN, IDH_RADIO_FULL_SCREEN,
	IDC_RADIO_RECT_AREA, IDH_RADIO_RECT_AREA,
	0, 0
};


CPropertyPageSource::CPropertyPageSource() : 
	COXContextHelpPropertyPage(CPropertyPageSource::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPageSource)
	m_nRadioCapturedArea = -1;
	//}}AFX_DATA_INIT
}

CPropertyPageSource::~CPropertyPageSource()
{
}

void CPropertyPageSource::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageSource)
	DDX_Control(pDX, IDC_RADIO_CURRENT_WINDOW, m_ctlRadioCurrentWindow);
	DDX_Radio(pDX, IDC_RADIO_CURRENT_WINDOW, m_nRadioCapturedArea);
	//}}AFX_DATA_MAP
	// check if all variables are correct
	CheckVars();
}


BEGIN_MESSAGE_MAP(CPropertyPageSource, COXContextHelpPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageSource)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageSource message handlers

BOOL CPropertyPageSource::AdjustToolTips()
{
	//Set up the Tooltip
	BOOL result;

	result=m_Tooltip.AddTool(&m_ctlRadioCurrentWindow,
		_T("Pick the capturing area"));
	ASSERT(result != 0) ;

	return result;
}



BOOL CPropertyPageSource::OnInitDialog() 
{
	COXContextHelpPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_LayoutManager.Attach(this);

	CRect rectDialog;
	GetWindowRect(&rectDialog);

	CRect rectItem;

	GetDlgItem(IDC_STATIC_AREA)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_STATIC_AREA, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_STATIC_AREA, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	// check if all variables are correct
	CheckVars();

	UpdateData(FALSE);

	ShowControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageSource::ShowControls() 
{
}

void CPropertyPageSource::CheckVars() 
{
	if(m_nRadioCapturedArea<0 || 
		m_nRadioCapturedArea>IDC_RADIO_RECT_AREA-IDC_RADIO_CURRENT_WINDOW)
	{
		m_nRadioCapturedArea=0;
	}
}
