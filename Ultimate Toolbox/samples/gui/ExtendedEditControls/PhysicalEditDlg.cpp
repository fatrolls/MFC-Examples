// PhysicalEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExtendedEditControls.h"
#include "PhysicalEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPhysicalEditDlg dialog

CPhysicalEditDlg::CPhysicalEditDlg():CPropertyPage(CPhysicalEditDlg::IDD)
{
	//{{AFX_DATA_INIT(CPhysicalEditDlg)
	m_bShowUnit = FALSE;
	m_bShowDropdownButton = TRUE;
	m_bDropdownLeftAligned = FALSE;
	//}}AFX_DATA_INIT
	m_dConvAngle = 0.0;
	m_dConvLength = 0.0;
	m_dConvTemp = 0.0;
	m_dConvTime = 0.0;
}

void CPhysicalEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhysicalEditDlg)
	DDX_Control(pDX, IDC_STATIC_VALUE, m_sepValue);
	DDX_Control(pDX, IDC_STATIC_BOTTOM, m_sepBottom);
	DDX_Control(pDX, IDC_STATIC_CONTROL_APPEARANCE, m_sepControlAppearance);
	DDX_Control(pDX, IDC_BUTTON_TEXTCOLOR_NEGATIVE, m_btnTextColorNegative);
	DDX_Control(pDX, IDC_BUTTON_FONT, m_btnFont);
	DDX_Control(pDX, IDC_BUTTON_TEXTCOLOR, m_btnTextColor);
	DDX_Control(pDX, IDC_BUTTON_BACKCOLOR, m_btnBackColor);
	DDX_Control(pDX, IDC_TEMPERATURE, m_wndTemp);
	DDX_Control(pDX, IDC_TIME, m_wndTime);
	DDX_Control(pDX, IDC_LENGTH, m_wndLength);
	DDX_Control(pDX, IDC_ANGLE, m_wndAngle);
	DDX_Check(pDX, IDC_CHECK_SHOW_UNIT, m_bShowUnit);
	DDX_Check(pDX, IDC_CHECK_SHOW_DROPDOWN, m_bShowDropdownButton);
	DDX_Check(pDX, IDC_CHECK_LEFTALIGNED, m_bDropdownLeftAligned);
	//}}AFX_DATA_MAP
	// We only want to retrieve data from the control (not put new data in it)
	DDX_ColorPicker(pDX, IDC_BUTTON_BACKCOLOR, m_clrBack);
	DDX_ColorPicker(pDX, IDC_BUTTON_TEXTCOLOR, m_clrText);
	DDX_ColorPicker(pDX, IDC_BUTTON_TEXTCOLOR_NEGATIVE, m_clrTextNegative);
	DDX_FontPickerFont(pDX, IDC_BUTTON_FONT, &m_font);
}

BEGIN_MESSAGE_MAP(CPhysicalEditDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CPhysicalEditDlg)
	ON_BN_CLICKED(IDC_BUTTON_BACKCOLOR, OnButtonBackcolor)
	ON_BN_CLICKED(IDC_BUTTON_TEXTCOLOR, OnButtonTextcolor)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	ON_BN_CLICKED(IDC_BUTTON_TEXTCOLOR_NEGATIVE, OnButtonTextcolorNegative)
	ON_BN_CLICKED(IDC_CHECK_SHOW_UNIT, OnCheckShowUnit)
	ON_BN_CLICKED(IDC_CHECK_SHOW_DROPDOWN, OnCheckShowDropdown)
	ON_BN_CLICKED(IDC_CHECK_LEFTALIGNED, OnCheckLeftaligned)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhysicalEditDlg message handlers

BOOL CPhysicalEditDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	
	m_wndTemp.SetMask(_T("Temperature: #"));
	m_wndTemp.SetTextColor(RGB(0,0,255));
	m_wndTemp.SetNegativeFormat(_T("-1.1"));
	m_wndTemp.SetPositiveFormat(_T("+1.1"));
	
	m_wndTime.SetMask(_T("Time: #"));
	m_wndTime.SetTextColor(RGB(0,0,255));
	
	m_wndLength.SetMask(_T("Length: #"));
	m_wndLength.SetTextColor(RGB(0,0,255));
	
	m_wndAngle.SetMask(_T("Angle: #"));
	m_wndAngle.SetTextColor(RGB(0,0,255));

	m_btnBackColor.SetToolTip(TRUE);
	m_btnTextColor.SetToolTip(TRUE);
	m_btnTextColorNegative.SetToolTip(TRUE);

	m_clrBack=m_wndLength.GetBkColor();
	m_clrText=m_wndLength.GetTextColor();
	m_clrTextNegative=m_wndLength.GetNegativeTextColor();
	m_bShowUnit=m_wndLength.GetShowUnit();

	m_btnFont.SetBuddy(IDC_STATIC_FONT);
	LOGFONT lf;
	CFont* pFont=m_wndLength.GetFont();
	if(pFont==NULL)
	{
		CClientDC dc(&m_wndLength);
		pFont=dc.GetCurrentFont();
	}
	ASSERT(pFont!=NULL);
	VERIFY(pFont->GetLogFont(&lf));
	VERIFY(m_font.CreateFontIndirect(&lf));

	// separators
	COLORREF clr=::GetSysColor(COLOR_BTNTEXT);
	m_sepControlAppearance.SetTextColor(clr);
	m_sepValue.SetTextColor(clr);

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPhysicalEditDlg::OnButtonBackcolor() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
	m_wndTemp.SetBkColor(m_clrBack);
	m_wndTime.SetBkColor(m_clrBack);
	m_wndLength.SetBkColor(m_clrBack);
	m_wndAngle.SetBkColor(m_clrBack);
}

void CPhysicalEditDlg::OnButtonTextcolor() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_wndTemp.SetTextColor(m_clrText);
	m_wndTime.SetTextColor(m_clrText);
	m_wndLength.SetTextColor(m_clrText);
	m_wndAngle.SetTextColor(m_clrText);
}

void CPhysicalEditDlg::OnButtonTextcolorNegative() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_wndTemp.SetNegativeTextColor(m_clrTextNegative);
	m_wndTime.SetNegativeTextColor(m_clrTextNegative);
	m_wndLength.SetNegativeTextColor(m_clrTextNegative);
	m_wndAngle.SetNegativeTextColor(m_clrTextNegative);
}

void CPhysicalEditDlg::OnButtonFont() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_wndTemp.SetFont(&m_font);
	m_wndTime.SetFont(&m_font);
	m_wndLength.SetFont(&m_font);
	m_wndAngle.SetFont(&m_font);
}


void CPhysicalEditDlg::OnCheckShowUnit() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_wndTemp.ShowUnit(m_bShowUnit);
	m_wndTime.ShowUnit(m_bShowUnit);
	m_wndLength.ShowUnit(m_bShowUnit);
	m_wndAngle.ShowUnit(m_bShowUnit);
}

void CPhysicalEditDlg::OnCheckShowDropdown() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_wndTemp.ShowButton(m_bShowDropdownButton);
	m_wndTime.ShowButton(m_bShowDropdownButton);
	m_wndLength.ShowButton(m_bShowDropdownButton);
	m_wndAngle.ShowButton(m_bShowDropdownButton);
}

void CPhysicalEditDlg::OnCheckLeftaligned() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int nAlignment=(m_bDropdownLeftAligned ? OXDROPEDIT_BUTTONLEFT : 
		OXDROPEDIT_BUTTONRIGHT);
	m_wndTemp.SetButtonAlignment(nAlignment);
	m_wndTime.SetButtonAlignment(nAlignment);
	m_wndLength.SetButtonAlignment(nAlignment);
	m_wndAngle.SetButtonAlignment(nAlignment);
}
