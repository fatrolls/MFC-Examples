// NumericEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExtendedEditControls.h"
#include "NumericEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumericEditDlg dialog

CNumericEditDlg::CNumericEditDlg():CPropertyPage(CNumericEditDlg::IDD)
{
	//{{AFX_DATA_INIT(CNumericEditDlg)
	m_bLeadingZero = FALSE;
	m_bIndefiniteDecimalDigitCount = FALSE;
	m_bNoDiditInGroup = FALSE;
	m_sDecimalSeparator = _T("");
	m_sGroupSeparator = _T("");
	m_sNegativeValueFormat = _T("");
	m_nDecimalDigitCount = -1;
	m_nFractionalDigitCount = -1;
	m_nGroupLength = -1;
	m_sMask = _T("");
	//}}AFX_DATA_INIT
}

void CNumericEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNumericEditDlg)
	DDX_Control(pDX, IDC_STATIC_BOTTOM, m_sepBottom);
	DDX_Control(pDX, IDC_COMBO_NEGATIVE_VALUE_FORMAT, m_comboNegativeFormat);
	DDX_Control(pDX, IDC_COMBO_GROUP_SEPARATOR, m_comboGroupSeparator);
	DDX_Control(pDX, IDC_COMBO_DECIMAL_SEPARATOR, m_comboDecimalSeparator);
	DDX_Control(pDX, IDC_COMBO_MASK, m_comboMask);
	DDX_Control(pDX, IDC_COMBO_GROUP_LENGTH, m_comboGroupLength);
	DDX_Control(pDX, IDC_COMBO_DECIMAL_DIGIT_COUNT, m_comboDecimalCount);
	DDX_Control(pDX, IDC_STATIC_NUMERIC_EDIT, m_sepNumericEdit);
	DDX_Control(pDX, IDC_STATIC_NUMERIC_EDIT_SETTINGS, m_sepNumericEditSettings);
	DDX_Control(pDX, IDC_STATIC_CONTROL_APPEARANCE, m_sepControlAppearance);
	DDX_Control(pDX, IDC_BUTTON_TEXTCOLOR_NEGATIVE, m_btnTextColorNegative);
	DDX_Control(pDX, IDC_BUTTON_FONT, m_btnFont);
	DDX_Control(pDX, IDC_EDIT_TEST, m_edit);
	DDX_Control(pDX, IDC_BUTTON_TEXTCOLOR, m_btnTextColor);
	DDX_Control(pDX, IDC_BUTTON_BACKCOLOR, m_btnBackColor);
	DDX_Check(pDX, IDC_CHECK_LEADING_ZERO, m_bLeadingZero);
	DDX_Check(pDX, IDC_CHECK_DECIMAL_DIGIT_COUNT_INDEFINITE, m_bIndefiniteDecimalDigitCount);
	DDX_Check(pDX, IDC_CHECK_NO_GROUP, m_bNoDiditInGroup);
	DDX_CBString(pDX, IDC_COMBO_DECIMAL_SEPARATOR, m_sDecimalSeparator);
	DDV_MaxChars(pDX, m_sDecimalSeparator, 1);
	DDX_CBString(pDX, IDC_COMBO_GROUP_SEPARATOR, m_sGroupSeparator);
	DDV_MaxChars(pDX, m_sGroupSeparator, 1);
	DDX_CBString(pDX, IDC_COMBO_NEGATIVE_VALUE_FORMAT, m_sNegativeValueFormat);
	DDX_CBIndex(pDX, IDC_COMBO_DECIMAL_DIGIT_COUNT, m_nDecimalDigitCount);
	DDX_CBIndex(pDX, IDC_COMBO_FRACTIONAL_DIGIT_COUNT, m_nFractionalDigitCount);
	DDX_CBIndex(pDX, IDC_COMBO_GROUP_LENGTH, m_nGroupLength);
	DDX_CBString(pDX, IDC_COMBO_MASK, m_sMask);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_BACKCOLOR, m_clrBack);
	DDX_ColorPicker(pDX, IDC_BUTTON_TEXTCOLOR, m_clrText);
	DDX_ColorPicker(pDX, IDC_BUTTON_TEXTCOLOR_NEGATIVE, m_clrTextNegative);
	DDX_FontPickerFont(pDX, IDC_BUTTON_FONT, &m_font);
}

BEGIN_MESSAGE_MAP(CNumericEditDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CNumericEditDlg)
	ON_BN_CLICKED(IDC_BUTTON_BACKCOLOR, OnButtonBackcolor)
	ON_BN_CLICKED(IDC_BUTTON_TEXTCOLOR, OnButtonTextcolor)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	ON_BN_CLICKED(IDC_BUTTON_TEXTCOLOR_NEGATIVE, OnButtonTextcolorNegative)
	ON_BN_CLICKED(IDC_CHECK_DECIMAL_DIGIT_COUNT_INDEFINITE, OnCheckDecimalDigitCountIndefinite)
	ON_BN_CLICKED(IDC_CHECK_NO_GROUP, OnCheckNoGroup)
	ON_CBN_EDITCHANGE(IDC_COMBO_MASK, OnEditchangeComboMask)
	ON_CBN_SELCHANGE(IDC_COMBO_MASK, OnSelchangeComboMask)
	ON_BN_CLICKED(IDC_CHECK_LEADING_ZERO, OnCheckLeadingZero)
	ON_CBN_SELCHANGE(IDC_COMBO_DECIMAL_DIGIT_COUNT, OnSelchangeComboDecimalDigitCount)
	ON_CBN_EDITCHANGE(IDC_COMBO_DECIMAL_SEPARATOR, OnEditchangeComboDecimalSeparator)
	ON_CBN_SELCHANGE(IDC_COMBO_DECIMAL_SEPARATOR, OnSelchangeComboDecimalSeparator)
	ON_CBN_SELCHANGE(IDC_COMBO_FRACTIONAL_DIGIT_COUNT, OnSelchangeComboFractionalDigitCount)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP_LENGTH, OnSelchangeComboGroupLength)
	ON_CBN_EDITCHANGE(IDC_COMBO_GROUP_SEPARATOR, OnEditchangeComboGroupSeparator)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP_SEPARATOR, OnSelchangeComboGroupSeparator)
	ON_CBN_EDITCHANGE(IDC_COMBO_NEGATIVE_VALUE_FORMAT, OnEditchangeComboNegativeValueFormat)
	ON_CBN_SELCHANGE(IDC_COMBO_NEGATIVE_VALUE_FORMAT, OnSelchangeComboNegativeValueFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumericEditDlg message handlers

BOOL CNumericEditDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_clrBack=m_edit.GetBkColor();
	m_clrText=m_edit.GetTextColor();
	m_clrTextNegative=m_edit.GetNegativeTextColor();

	m_edit.SetToolTipText(_T("EditControl"));
//	VERIFY(m_edit.SetMask(_T("Length: # m")));
//	VERIFY(m_edit.SetInputData(_T("234.567")));
	m_sMask=m_edit.GetMask();
	m_bLeadingZero=m_edit.GetShowLeadingZero();
	m_nDecimalDigitCount=m_edit.GetDecimalDigitCount();
	m_bIndefiniteDecimalDigitCount=(m_nDecimalDigitCount==-1 ? TRUE : FALSE);
	m_comboDecimalCount.EnableWindow(!m_bIndefiniteDecimalDigitCount);
	m_sDecimalSeparator=m_edit.GetDecimalSeparator();
	m_nFractionalDigitCount=m_edit.GetFractionalDigitCount();
	m_nGroupLength=m_edit.GetGroupLength();
	m_bNoDiditInGroup=(m_nGroupLength==0 ? TRUE : FALSE);
	m_comboGroupLength.EnableWindow(!m_bNoDiditInGroup);
	m_nGroupLength--;
	m_sGroupSeparator=m_edit.GetGroupSeparator();
	m_sNegativeValueFormat=m_edit.GetNegativeFormat();

	m_btnBackColor.SetToolTip(TRUE);
	m_btnTextColor.SetToolTip(TRUE);
	m_btnTextColorNegative.SetToolTip(TRUE);

	m_btnFont.SetBuddy(IDC_STATIC_FONT);
	LOGFONT lf;
	CFont* pFont=m_edit.GetFont();
	if(pFont==NULL)
	{
		CClientDC dc(&m_edit);
		pFont=dc.GetCurrentFont();
	}
	ASSERT(pFont!=NULL);
	VERIFY(pFont->GetLogFont(&lf));
	VERIFY(m_font.CreateFontIndirect(&lf));

	// separators
	COLORREF clr=::GetSysColor(COLOR_BTNTEXT);
	m_sepNumericEdit.SetTextColor(clr);
	m_sepNumericEditSettings.SetTextColor(clr);
	m_sepControlAppearance.SetTextColor(clr);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNumericEditDlg::OnButtonBackcolor() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
	m_edit.SetBkColor(m_clrBack);
}

void CNumericEditDlg::OnButtonTextcolor() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetTextColor(m_clrText);
}

void CNumericEditDlg::OnButtonTextcolorNegative() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetNegativeTextColor(m_clrTextNegative);
}

void CNumericEditDlg::OnButtonFont() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_edit.SetFont(&m_font);
}

void CNumericEditDlg::OnCheckDecimalDigitCountIndefinite() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
	m_comboDecimalCount.EnableWindow(!m_bIndefiniteDecimalDigitCount);
	if(m_bIndefiniteDecimalDigitCount)
		m_edit.SetDecimalDigitCount(-1);
	else
		m_edit.SetDecimalDigitCount(m_nDecimalDigitCount);
}

void CNumericEditDlg::OnCheckNoGroup() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_comboGroupLength.EnableWindow(!m_bNoDiditInGroup);
	if(m_bNoDiditInGroup)
		m_edit.SetGroupLength(0);
	else
		m_edit.SetGroupLength(m_nGroupLength+1);
}

void CNumericEditDlg::OnEditchangeComboMask() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	if(!m_edit.SetMask(m_sMask))
	{
		AfxMessageBox(_T("Invalid mask has been specified.\nMake sure you use '#' symbol in your mask!"));
		m_sMask=m_edit.GetMask();
		UpdateData(FALSE);
	}
}


void CNumericEditDlg::OnSelchangeComboMask() 
{
	// TODO: Add your control notification handler code here
		
	m_comboMask.GetLBText(m_comboMask.GetCurSel(),m_sMask);
	if(!m_edit.SetMask(m_sMask))
	{
		AfxMessageBox(_T("Invalid mask has been specified.\nMake sure you use '#' symbol in your mask!"));
		m_sMask=m_edit.GetMask();
		UpdateData(FALSE);
	}
}

void CNumericEditDlg::OnCheckLeadingZero() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetShowLeadingZero(m_bLeadingZero);
}

void CNumericEditDlg::OnSelchangeComboDecimalDigitCount() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetDecimalDigitCount(m_nDecimalDigitCount);
}

void CNumericEditDlg::OnEditchangeComboDecimalSeparator() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetDecimalSeparator(m_sDecimalSeparator[0]);
}

void CNumericEditDlg::OnSelchangeComboDecimalSeparator() 
{
	// TODO: Add your control notification handler code here
	
	m_comboDecimalSeparator.GetLBText(m_comboDecimalSeparator.GetCurSel(),
		m_sDecimalSeparator);
	m_edit.SetDecimalSeparator(m_sDecimalSeparator[0]);
}

void CNumericEditDlg::OnSelchangeComboFractionalDigitCount() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetFractionalDigitCount(m_nFractionalDigitCount);
}

void CNumericEditDlg::OnSelchangeComboGroupLength() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetGroupLength(m_nGroupLength+1);
}

void CNumericEditDlg::OnEditchangeComboGroupSeparator() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetGroupSeparator(m_sGroupSeparator[0]);
}

void CNumericEditDlg::OnSelchangeComboGroupSeparator() 
{
	// TODO: Add your control notification handler code here
	
	m_comboGroupSeparator.GetLBText(m_comboGroupSeparator.GetCurSel(),
		m_sGroupSeparator);
	m_edit.SetGroupSeparator(m_sGroupSeparator[0]);
}

void CNumericEditDlg::OnEditchangeComboNegativeValueFormat() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetNegativeFormat(m_sNegativeValueFormat);
}

void CNumericEditDlg::OnSelchangeComboNegativeValueFormat() 
{
	// TODO: Add your control notification handler code here
	
	m_comboNegativeFormat.GetLBText(m_comboNegativeFormat.GetCurSel(),
		m_sNegativeValueFormat);
	m_edit.SetNegativeFormat(m_sNegativeValueFormat);
}
