// CustomizeCaptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "multipad.h"
#include "CustomizeCaptionDlg.h"

#include "OXColorPickerCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeCaptionDlg dialog


CCustomizeCaptionDlg::CCustomizeCaptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeCaptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeCaptionDlg)
	m_bGradient = FALSE;
	m_nGradientAlgorithm = -1;
	m_nGradientAlignment = -1;
	m_nCaptionState = -1;
	m_nEllipsis = -1;
	m_nHorizontalAlignment = -1;
	m_nVerticalAlignment = -1;
	m_sFont = _T("");
	m_nNumberShade = 0;
//	m_clrBackground = 0;
	//}}AFX_DATA_INIT
}


void CCustomizeCaptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeCaptionDlg)
	DDX_Control(pDX, IDC_EDIT_NUMBER_SHADE, m_ctlEditNumberShade);
	DDX_Control(pDX, IDC_COMBO_CAPTION, m_ctlComboCaptionState);
	DDX_Control(pDX, IDC_COMBO_GRADIENT_ALGORITHM, m_ctlComboGradientAlgorithm);
	DDX_Control(pDX, IDC_COMBO_GRADIENT_ALIGNMENT, m_ctlComboGradientAlignment);
	DDX_Control(pDX, IDC_BUTTON_TEXT_FONT, m_ctlButtonFont);
	DDX_Control(pDX, IDC_BUTTON_BACKGROUND_COLOR, m_ctlButtonBackground);
	DDX_Check(pDX, IDC_CHECK_GRADIENT, m_bGradient);
	DDX_CBIndex(pDX, IDC_COMBO_GRADIENT_ALGORITHM, m_nGradientAlgorithm);
	DDX_CBIndex(pDX, IDC_COMBO_GRADIENT_ALIGNMENT, m_nGradientAlignment);
	DDX_CBIndex(pDX, IDC_COMBO_CAPTION, m_nCaptionState);
	DDX_Radio(pDX, IDC_RADIO_ELLIPSIS_NONE, m_nEllipsis);
	DDX_Radio(pDX, IDC_RADIO_HORZ_LEFT, m_nHorizontalAlignment);
	DDX_Radio(pDX, IDC_RADIO_VERT_TOP, m_nVerticalAlignment);
	DDX_Text(pDX, IDC_EDIT_FONT, m_sFont);
	DDX_Text(pDX, IDC_EDIT_NUMBER_SHADE, m_nNumberShade);
//	DDX_Text(pDX, IDC_EDIT_BACKGROUND_COLOR, m_clrBackground);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_BACKGROUND_COLOR, m_clrBackground);
}


BEGIN_MESSAGE_MAP(CCustomizeCaptionDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomizeCaptionDlg)
	ON_BN_CLICKED(IDC_CHECK_GRADIENT, OnCheckGradient)
	ON_BN_CLICKED(IDC_BUTTON_TEXT_FONT, OnButtonTextFont)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTION, OnSelchangeComboCaption)
	ON_BN_CLICKED(IDC_BUTTON_BACKGROUND_COLOR, OnButtonBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeCaptionDlg message handlers

BOOL CCustomizeCaptionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Caption.Attach(this);

	CMainFrame* pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pFrame);
	COXCaptionPainter parentCaption;
	if(::SendMessage(pFrame->m_hWnd,COXCaptionPainter::m_nGetCaptionPainter,0,
		(LPARAM)&parentCaption))
	{
		SendMessage(COXCaptionPainter::m_nSetCaptionPainter,0,(LPARAM)&parentCaption);
	}

	SendMessage(WM_NCPAINT);

	m_ctlComboCaptionState.AddString(_T("Active"));
	m_ctlComboCaptionState.AddString(_T("Inactive"));

	m_ctlComboGradientAlignment.AddString(_T("Left"));
	m_ctlComboGradientAlignment.AddString(_T("Center"));
	m_ctlComboGradientAlignment.AddString(_T("Right"));

	m_ctlComboGradientAlgorithm.AddString(_T("Linear"));
	m_ctlComboGradientAlgorithm.AddString(_T("Square"));

	m_nCaptionState=0;
	m_nOldCaptionState=0;

	GetDlgItem(IDC_EDIT_BACKGROUND_COLOR)->ShowWindow(SW_HIDE);
//	m_ctlButtonBackground.SetStyleEx(OXBB_EX_DROPDOWN|OXBB_EX_DROPDOWNRIGHT);
//	m_ctlButtonBackground.SetText(_T(""));
//	m_ctlButtonBackground.SetDefaultColor(RGB(0,0,128));
//	m_ctlButtonBackground.SetColorBandHeight(8);
	m_ctlButtonBackground.SizeToContent();

	GetVars();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomizeCaptionDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	SetVars();
	
	CDialog::OnOK();
}

void CCustomizeCaptionDlg::OnCheckGradient() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}

void CCustomizeCaptionDlg::OnButtonTextFont() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	// Use font common dialog
	CFontDialog fontDlg(&arrCustomize[m_nCaptionState].m_lf);
	fontDlg.m_cf.rgbColors=arrCustomize[m_nCaptionState].m_clrText;
	if(fontDlg.DoModal()==IDOK)
	{
		arrCustomize[m_nCaptionState].m_clrText=fontDlg.GetColor();
		fontDlg.GetCurrentFont(&arrCustomize[m_nCaptionState].m_lf);
		m_sFont=arrCustomize[m_nCaptionState].m_lf.lfFaceName;
		UpdateData(FALSE);
	}
}

void CCustomizeCaptionDlg::OnSelchangeComboCaption() 
{
	// TODO: Add your control notification handler code here
	
	SetVars();
	GetVars();
}

void CCustomizeCaptionDlg::GetVars()
{
	m_bGradient=arrCustomize[m_nCaptionState].m_bGradient;
	m_nGradientAlgorithm=arrCustomize[m_nCaptionState].m_nGradientAlgorithm;
	m_nGradientAlignment=arrCustomize[m_nCaptionState].m_nGradientAlignment;
	m_nEllipsis=arrCustomize[m_nCaptionState].m_nEllipsis;
	m_nHorizontalAlignment=arrCustomize[m_nCaptionState].m_nHorizontalAlignment;
	m_nVerticalAlignment=arrCustomize[m_nCaptionState].m_nVerticalAlignment;
	m_clrBackground=arrCustomize[m_nCaptionState].m_clrBackground;
	m_nNumberShade=arrCustomize[m_nCaptionState].m_nNumberShade;

	m_sFont=arrCustomize[m_nCaptionState].m_lf.lfFaceName;

	UpdateData(FALSE);

	ShowControls();
}

void CCustomizeCaptionDlg::SetVars()
{
	UpdateData();

	arrCustomize[m_nOldCaptionState].m_bGradient=m_bGradient;
	arrCustomize[m_nOldCaptionState].m_nGradientAlgorithm=m_nGradientAlgorithm;
	arrCustomize[m_nOldCaptionState].m_nGradientAlignment=m_nGradientAlignment;
	arrCustomize[m_nOldCaptionState].m_nEllipsis=m_nEllipsis;
	arrCustomize[m_nOldCaptionState].m_nHorizontalAlignment=m_nHorizontalAlignment;
	arrCustomize[m_nOldCaptionState].m_nVerticalAlignment=m_nVerticalAlignment;
	arrCustomize[m_nOldCaptionState].m_clrBackground=m_clrBackground;
	arrCustomize[m_nOldCaptionState].m_nNumberShade=m_nNumberShade;

	m_nOldCaptionState=m_nCaptionState;

	ShowControls();
}

void CCustomizeCaptionDlg::ShowControls() 
{
	UpdateData(TRUE);

	m_ctlComboGradientAlignment.EnableWindow(m_bGradient);
	m_ctlComboGradientAlgorithm.EnableWindow(m_bGradient);
	m_ctlEditNumberShade.EnableWindow(m_bGradient);

	m_ctlButtonBackground.SetDefaultColor(m_nCaptionState==0 ? 
		RGB(0,0,128) : RGB(128, 128, 128));

	UpdateData(FALSE);
}


void CCustomizeCaptionDlg::OnButtonBackgroundColor() 
{
	// TODO: Add your control notification handler code here

/*	CColorDialog clrDlg(m_clrBackground);
	if(clrDlg.DoModal()==IDOK)
	{
		m_clrBackground=clrDlg.GetColor();
		UpdateData(FALSE);
	}*/
}
