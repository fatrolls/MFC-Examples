// SlcPage.cpp : implementation file
//

#include "stdafx.h"
#include "SctPage.h"

#define SECTION_APPLY_TIMER_ID	15
#define SECTION_APPLY_TIME		800


extern long ISU;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSlicePage dialog


CSectionPage::CSectionPage() : 
	COXDockPropertyPage(IDS_SECTION)
{
	m_nID = CSectionPage::IDD;
	//{{AFX_DATA_INIT(CSectionPage)
	m_fPosValue = 1.0f;
	m_nSection = 0;
	//}}AFX_DATA_INIT
}


void CSectionPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSectionPage)
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Text(pDX, IDC_CUTVALUE, m_fPosValue);
	DDX_Radio(pDX, IDC_X, m_nSection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSectionPage, CDialog)
	//{{AFX_MSG_MAP(CSectionPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlicePage message handlers

BOOL CSectionPage::OnInitDialog() 
{
	COXDockPropertyPage::OnInitDialog();
	
	m_slider.ClearTics();
	m_slider.SetRange(0,100); 
	m_slider.SetLineSize(1); 
	m_slider.SetPageSize(10); 

	return TRUE;  // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CSectionPage::OnSetActive( )
{
	return COXDockPropertyPage::OnSetActive();

}

BOOL CSectionPage::OnKillActive( )
{
	return COXDockPropertyPage::OnKillActive();;

}
