// RoundedButtonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoundedButton.h"
#include "RoundedButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoundedButtonDlg dialog

CRoundedButtonDlg::CRoundedButtonDlg():CPropertyPage(CRoundedButtonDlg::IDD)
{
	//{{AFX_DATA_INIT(CRoundedButtonDlg)
	m_fAmbient = 0.0f;
	m_fDiffuse = 0.0f;
	m_fLightIntensityCoef = 0.0f;
	m_fMirror = 0.0f;
	m_fPhi = 0.0f;
	m_nPhong = 0;
	m_nSphereExtRadius = 0;
	m_nSphereIntRadius = 0;
	m_fThetta = 0.0f;
	//}}AFX_DATA_INIT
}

void CRoundedButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoundedButtonDlg)
	DDX_Control(pDX, IDC_SPIN_THETTA, m_spinThetta);
	DDX_Control(pDX, IDC_SPIN_RADIUS_INT, m_spinIntRadius);
	DDX_Control(pDX, IDC_SPIN_RADIUS_EXT, m_spinExtRadius);
	DDX_Control(pDX, IDC_SPIN_PHONG, m_spinPhong);
	DDX_Control(pDX, IDC_SPIN_PHI, m_spinPhi);
	DDX_Control(pDX, IDC_SPIN_MIRROR, m_spinMirror);
	DDX_Control(pDX, IDC_SPIN_LIGHT_INTENSITY, m_spinLightIntensity);
	DDX_Control(pDX, IDC_SPIN_DIFFUSE, m_spinDiffuse);
	DDX_Control(pDX, IDC_SPIN_AMBIENT, m_spinAmbient);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR, m_separator);
	DDX_Control(pDX, IDC_STATIC_SURFACE_SETTINGS, m_sepSurfaceSettings);
	DDX_Control(pDX, IDC_STATIC_LIGHTSOURCE_SETTINGS, m_sepLightSourceSettings);
	DDX_Control(pDX, IDC_STATIC_BUTTON_SETTINGS, m_sepButtonSettings);
	DDX_Control(pDX, IDC_LIGHT_COLOR, m_btnLightColor);
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_btnButtonColor);
	DDX_Control(pDX, IDC_BUTTON_ROUND, m_btnRound);
	DDX_Text(pDX, IDC_EDIT_AMBIENT, m_fAmbient);
	DDX_Text(pDX, IDC_EDIT_DIFFUSE, m_fDiffuse);
	DDX_Text(pDX, IDC_EDIT_LIGHT_INTENSITY, m_fLightIntensityCoef);
	DDX_Text(pDX, IDC_EDIT_MIRROR, m_fMirror);
	DDX_Text(pDX, IDC_EDIT_PHI, m_fPhi);
	DDX_Text(pDX, IDC_EDIT_PHONG, m_nPhong);
	DDX_Text(pDX, IDC_EDIT_RADIUS_EXT, m_nSphereExtRadius);
	DDX_Text(pDX, IDC_EDIT_RADIUS_INT, m_nSphereIntRadius);
	DDX_Text(pDX, IDC_EDIT_THETTA, m_fThetta);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_COLOR, m_clrButton);
	DDX_ColorPicker(pDX, IDC_LIGHT_COLOR, m_clrLight);
}

BEGIN_MESSAGE_MAP(CRoundedButtonDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CRoundedButtonDlg)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnUpdate)
	ON_EN_CHANGE(IDC_EDIT_AMBIENT, OnUpdate)
	ON_EN_CHANGE(IDC_EDIT_DIFFUSE, OnUpdate)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_INTENSITY, OnUpdate)
	ON_EN_CHANGE(IDC_EDIT_MIRROR, OnUpdate)
	ON_EN_CHANGE(IDC_EDIT_PHI, OnUpdate)
	ON_EN_CHANGE(IDC_EDIT_PHONG, OnUpdate)
	ON_EN_CHANGE(IDC_EDIT_RADIUS_EXT, OnUpdate)
	ON_EN_CHANGE(IDC_EDIT_RADIUS_INT, OnUpdate)
	ON_EN_CHANGE(IDC_EDIT_THETTA, OnUpdate)
	ON_BN_CLICKED(IDC_LIGHT_COLOR, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoundedButtonDlg message handlers

BOOL CRoundedButtonDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	
	VERIFY(m_btnRound.LoadIcon(IDR_MAINFRAME,FALSE,16,16));

	static CFont fontVertEnabled;
	VERIFY(fontVertEnabled.CreatePointFont(120,_T("Times New Roman")));
	m_sepButtonSettings.SetTextColor(RGB(128,0,0));
	m_sepButtonSettings.SetVertOriented();
	m_sepButtonSettings.SetFont(&fontVertEnabled);
	m_sepSurfaceSettings.SetTextColor(RGB(128,0,0));
	m_sepSurfaceSettings.SetVertOriented();
	m_sepSurfaceSettings.SetFont(&fontVertEnabled);
	m_sepLightSourceSettings.SetTextColor(RGB(128,0,0));
	m_sepLightSourceSettings.SetVertOriented();
	m_sepLightSourceSettings.SetFont(&fontVertEnabled);

	m_spinThetta.SetRange(-360,360);
	m_spinPhi.SetRange(-360,360);
	m_spinIntRadius.SetRange(0,100);
	m_spinExtRadius.SetRange(0,100);
	m_spinPhong.SetRange(0,100);
	m_spinMirror.SetRange(0,100);
	m_spinLightIntensity.SetRange(0,100);
	m_spinDiffuse.SetRange(0,100);
	m_spinAmbient.SetRange(0,100);

	GetVars();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRoundedButtonDlg::GetVars()
{
	m_fAmbient=m_btnRound.GetAmbientCoef()*10;
	m_fDiffuse=m_btnRound.GetDiffuseCoef()*10;
	m_fLightIntensityCoef=m_btnRound.GetLightIntensityCoef()*10;
	m_fMirror=m_btnRound.GetMirrorCoef()*10;
	m_fPhi=m_btnRound.GetPhi();
	m_nPhong=m_btnRound.GetPhong();
	m_nSphereExtRadius=m_btnRound.GetSphereExternalRadius();
	m_nSphereIntRadius=m_btnRound.GetSphereInternalRadius();
	m_fThetta=m_btnRound.GetThetta();
	m_clrButton=m_btnRound.GetButtonColor();
	m_clrLight=m_btnRound.GetLightColor();

	UpdateData(FALSE);
}

void CRoundedButtonDlg::SetVars()
{
	if(!::IsWindow(m_btnRound.GetSafeHwnd()))
		return;

	if(!UpdateData())
		return;

	m_btnRound.SetAmbientCoef(m_fAmbient/10,FALSE);
	m_btnRound.SetDiffuseCoef(m_fDiffuse/10,FALSE);
	m_btnRound.SetLightIntensityCoef(m_fLightIntensityCoef/10,FALSE);
	m_btnRound.SetMirrorCoef(m_fMirror/10,FALSE);
	m_btnRound.SetPhi(m_fPhi,FALSE);
	m_btnRound.SetPhong(m_nPhong,FALSE);
	m_btnRound.SetSphereExternalRadius(m_nSphereExtRadius,FALSE);
	m_btnRound.SetSphereInternalRadius(m_nSphereIntRadius,FALSE);
	m_btnRound.SetThetta(m_fThetta,FALSE);
	m_btnRound.SetButtonColor(m_clrButton,FALSE);
	m_btnRound.SetLightColor(m_clrLight,FALSE);

	m_btnRound.RedrawWindow();
}



void CRoundedButtonDlg::OnUpdate() 
{
	// TODO: Add your control notification handler code here
	SetVars();
}
