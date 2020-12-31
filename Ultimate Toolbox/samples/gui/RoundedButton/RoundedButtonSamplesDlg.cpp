// RoundedButtonSamplesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoundedButton.h"
#include "RoundedButtonSamplesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoundedButtonSamplesDlg property page

IMPLEMENT_DYNCREATE(CRoundedButtonSamplesDlg, CPropertyPage)

CRoundedButtonSamplesDlg::CRoundedButtonSamplesDlg() : CPropertyPage(CRoundedButtonSamplesDlg::IDD)
{
	//{{AFX_DATA_INIT(CRoundedButtonSamplesDlg)
	//}}AFX_DATA_INIT
}

CRoundedButtonSamplesDlg::~CRoundedButtonSamplesDlg()
{
}

void CRoundedButtonSamplesDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoundedButtonSamplesDlg)
	DDX_Control(pDX, IDC_STATIC_BUTTONS_TOGGLE, m_sepToggleButtons);
	DDX_Control(pDX, IDC_BUTTON_TOGGLE_4, m_btnToggle4);
	DDX_Control(pDX, IDC_BUTTON_TOGGLE_3, m_btnToggle3);
	DDX_Control(pDX, IDC_BUTTON_TOGGLE_2, m_btnToggle2);
	DDX_Control(pDX, IDC_BUTTON_TOGGLE_1, m_btnToggle1);
	DDX_Control(pDX, IDC_BUTTON_WITH_IMAGE_7, m_btnWithImage7);
	DDX_Control(pDX, IDC_BUTTON_WITH_IMAGE_6, m_btnWithImage6);
	DDX_Control(pDX, IDC_BUTTON_WITH_IMAGE_5, m_btnWithImage5);
	DDX_Control(pDX, IDC_BUTTON_WITH_IMAGE_4, m_btnWithImage4);
	DDX_Control(pDX, IDC_BUTTON_WITH_IMAGE_3, m_btnWithImage3);
	DDX_Control(pDX, IDC_BUTTON_WITH_IMAGE_2, m_btnWithImage2);
	DDX_Control(pDX, IDC_BUTTON_WITH_IMAGE_1, m_btnWithImage1);
	DDX_Control(pDX, IDC_STATIC_BUTTONS_WITH_IMAGES, m_sepButtonsWithImages);
	DDX_Control(pDX, IDC_BUTTON_WITH_TEXT_MULTILINE_CUSTOM, m_btnWithTextMultilineCustom);
	DDX_Control(pDX, IDC_STATIC_BUTTONS_WITH_TEXT, m_sepButtonsWithText);
	DDX_Control(pDX, IDC_BUTTON_WITH_TEXT_3, m_btnWithText3);
	DDX_Control(pDX, IDC_BUTTON_WITH_TEXT_2, m_btnWithText2);
	DDX_Control(pDX, IDC_BUTTON_WITH_TEXT_1, m_btnWithText1);
	DDX_Control(pDX, IDC_BUTTON_ROUND_5, m_btnRound5);
	DDX_Control(pDX, IDC_BUTTON_ROUND_4, m_btnRound4);
	DDX_Control(pDX, IDC_BUTTON_ROUND_3, m_btnRound3);
	DDX_Control(pDX, IDC_BUTTON_ROUND_2, m_btnRound2);
	DDX_Control(pDX, IDC_BUTTON_ROUND_1, m_btnRound1);
	DDX_Control(pDX, IDC_STATIC_ROUND_BUTTONS, m_sepRoundButtons);
	//}}AFX_DATA_MAP
	DDX_Toggle(pDX, IDC_BUTTON_TOGGLE_1, m_bOption1);
	DDX_Toggle(pDX, IDC_BUTTON_TOGGLE_2, m_bOption2);
	DDX_Toggle(pDX, IDC_BUTTON_TOGGLE_3, m_bOption3);
	DDX_Toggle(pDX, IDC_BUTTON_TOGGLE_4, m_bOption4);
}


BEGIN_MESSAGE_MAP(CRoundedButtonSamplesDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CRoundedButtonSamplesDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY_RANGE(OXBBN_TOGGLE, IDC_BUTTON_TOGGLE_1, IDC_BUTTON_TOGGLE_4, OnToggle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoundedButtonSamplesDlg message handlers

BOOL CRoundedButtonSamplesDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here

	// separators
	m_sepRoundButtons.SetTextColor(RGB(128, 128, 128));
	m_sepButtonsWithText.SetTextColor(RGB(128, 128, 128));
	m_sepButtonsWithImages.SetTextColor(RGB(128, 128, 128));
	m_sepToggleButtons.SetTextColor(RGB(128, 128, 128));

	// setup round buttons
	SetupRoundButton(&m_btnRound1,RGB(0xB0, 0xB0, 0xB0));	// light grey
	SetupRoundButton(&m_btnRound2,RGB(0x00, 0x93, 0x00));	// green
	SetupRoundButton(&m_btnRound3,RGB(0xFF, 0x68, 0x20));	// orange
	SetupRoundButton(&m_btnRound4,RGB(0x7B, 0x7B, 0xC0));	// blue-grey
	SetupRoundButton(&m_btnRound5,RGB(0x8B, 0x8B, 0x00));	// dark yellow
	//
	//////////////////////////////

	// setup buttons with text
	m_btnWithText1.SetButtonColor(RGB(0x38, 0x8E, 0x8E));	// teal
	m_btnWithText2.SetButtonColor(RGB(0x38, 0x8E, 0x8E));	// teal
	m_btnWithText3.SetButtonColor(RGB(0x3C, 0xB3, 0x71));	// sea green

	m_btnWithTextMultilineCustom.SetButtonColor(RGB(0xFF, 0xAD, 0x5B));	// light orange
	m_btnWithTextMultilineCustom.SetTextColor(RGB(128,0,0));
	static CFont fontCustom;
	fontCustom.CreatePointFont(140,_T("Times New Roman"));
	m_btnWithTextMultilineCustom.SetTextFont(&fontCustom);
	//
	////////////////////////////////

	// setup buttons with images
	static CFont fontImage;
	fontImage.CreatePointFont(100,_T("Tahoma"));
	VERIFY(m_btnWithImage1.LoadIcon(IDI_ICON_EARTH,FALSE,32,32));
	m_btnWithImage1.SetButtonColor(RGB(0x68, 0x83, 0x8B));	// pale blue
	m_btnWithImage1.SetTextFont(&fontImage);
	VERIFY(m_btnWithImage2.LoadIcon(IDI_ICON_MOON,FALSE,32,32));
	m_btnWithImage2.SetButtonColor(RGB(0x68, 0x83, 0x8B));	// pale blue
	m_btnWithImage2.SetTextFont(&fontImage);
	VERIFY(m_btnWithImage3.LoadIcon(IDI_ICON_JUPITER,FALSE,32,32));
	m_btnWithImage3.SetButtonColor(RGB(0x68, 0x83, 0x8B));	// pale blue
	m_btnWithImage3.SetTextFont(&fontImage);

	SetupImageButton(&m_btnWithImage4,IDI_ICON_INFO);
	SetupImageButton(&m_btnWithImage5,IDI_ICON_QUESTION);
	SetupImageButton(&m_btnWithImage6,IDI_ICON_EXCLAMATION);
	SetupImageButton(&m_btnWithImage7,IDI_ICON_CHECK);
	//
	/////////////////////////////////////////

	// setup toggle buttons
	SetupToggleButton(&m_btnToggle1);
	SetupToggleButton(&m_btnToggle2);
	SetupToggleButton(&m_btnToggle3);
	SetupToggleButton(&m_btnToggle4);

	m_bOption1=TRUE;
	m_bOption2=FALSE;
	m_bOption3=FALSE;
	m_bOption4=FALSE;
	ResetImages(TRUE);
	//
	/////////////////////////////////////////

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CRoundedButtonSamplesDlg::SetupRoundButton(COXRoundedButton* pButton, 
												COLORREF clr)
{
	ASSERT(pButton!=NULL);
	ASSERT(::IsWindow(pButton->GetSafeHwnd()));

	pButton->SetButtonColor(clr);

	CRect rect;
	pButton->GetWindowRect(rect);
	int nRadius=rect.Width()/2;
	pButton->SetSphereExternalRadius(nRadius);
	pButton->SetSphereInternalRadius(nRadius-5);
}


void CRoundedButtonSamplesDlg::SetupImageButton(COXRoundedButton* pButton, 
												UINT nIconID)
{
	ASSERT(pButton!=NULL);
	ASSERT(::IsWindow(pButton->GetSafeHwnd()));

	VERIFY(pButton->LoadIcon(nIconID,FALSE,32,32));

	CRect rect;
	pButton->GetWindowRect(rect);
	int nRadius=rect.Width()/2;
	pButton->SetSphereExternalRadius(nRadius);
	pButton->SetSphereInternalRadius(nRadius-5);
}


void CRoundedButtonSamplesDlg::SetupToggleButton(COXRoundedButton* pButton)
{
	pButton->SetButtonColor(RGB(0xD2, 0xB4, 0x8C));	// tan
	pButton->SetStyleEx(OXBB_EX_TOGGLE);
	VERIFY(pButton->LoadIcon(IDI_ICON_OFF,FALSE,16,16));
}


void CRoundedButtonSamplesDlg::OnToggle(UINT id, NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	ResetImages(FALSE);

	m_bOption1=FALSE;
	m_bOption2=FALSE;
	m_bOption3=FALSE;
	m_bOption4=FALSE;

	switch(id)
	{
	case IDC_BUTTON_TOGGLE_1:
		m_bOption1=TRUE;
		break;
	case IDC_BUTTON_TOGGLE_2:
		m_bOption2=TRUE;
		break;
	case IDC_BUTTON_TOGGLE_3:
		m_bOption3=TRUE;
		break;
	case IDC_BUTTON_TOGGLE_4:
		m_bOption4=TRUE;
		break;
	default:
		ASSERT(FALSE);
	}
	ResetImages(TRUE);

	UpdateData(FALSE);

	*result=0;
}


void CRoundedButtonSamplesDlg::ResetImages(BOOL bSet)
{
	if(m_bOption1)
	{
		VERIFY(m_btnToggle1.LoadIcon((bSet ? IDI_ICON_ON : IDI_ICON_OFF),FALSE,16,16));
		m_btnToggle1.RedrawWindow();
	}
	else if(m_bOption2)
	{
		VERIFY(m_btnToggle2.LoadIcon((bSet ? IDI_ICON_ON : IDI_ICON_OFF),FALSE,16,16));
		m_btnToggle2.RedrawWindow();
	}
	else if(m_bOption3)
	{
		VERIFY(m_btnToggle3.LoadIcon((bSet ? IDI_ICON_ON : IDI_ICON_OFF),FALSE,16,16));
		m_btnToggle3.RedrawWindow();
	}
	else if(m_bOption4)
	{
		VERIFY(m_btnToggle4.LoadIcon((bSet ? IDI_ICON_ON : IDI_ICON_OFF),FALSE,16,16));
		m_btnToggle4.RedrawWindow();
	}
}
