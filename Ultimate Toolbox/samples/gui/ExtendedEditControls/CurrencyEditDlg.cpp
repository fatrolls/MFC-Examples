// CurrencyEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExtendedEditControls.h"
#include "CurrencyEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurrencyEditDlg dialog

CCurrencyEditDlg::CCurrencyEditDlg():CPropertyPage(CCurrencyEditDlg::IDD)
{
	//{{AFX_DATA_INIT(CCurrencyEditDlg)
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
	m_sCurrency = _T("");
	m_sPositiveValueFormat = _T("");
	//}}AFX_DATA_INIT
}

void CCurrencyEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurrencyEditDlg)
	DDX_Control(pDX, IDC_COMBO_POSITIVE_VALUE_FORMAT, m_comboPositiveFormat);
	DDX_Control(pDX, IDC_COMBO_CURRENCY_NAME, m_comboCurrencyName);
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
	DDX_CBString(pDX, IDC_COMBO_CURRENCY_NAME, m_sCurrency);
	DDX_CBString(pDX, IDC_COMBO_POSITIVE_VALUE_FORMAT, m_sPositiveValueFormat);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_BACKCOLOR, m_clrBack);
	DDX_ColorPicker(pDX, IDC_BUTTON_TEXTCOLOR, m_clrText);
	DDX_ColorPicker(pDX, IDC_BUTTON_TEXTCOLOR_NEGATIVE, m_clrTextNegative);
	DDX_FontPickerFont(pDX, IDC_BUTTON_FONT, &m_font);
}

BEGIN_MESSAGE_MAP(CCurrencyEditDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CCurrencyEditDlg)
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
	ON_CBN_EDITCHANGE(IDC_COMBO_CURRENCY_NAME, OnEditchangeComboCurrencyName)
	ON_CBN_SELCHANGE(IDC_COMBO_CURRENCY_NAME, OnSelchangeComboCurrencyName)
	ON_CBN_EDITCHANGE(IDC_COMBO_POSITIVE_VALUE_FORMAT, OnEditchangeComboPositiveValueFormat)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITIVE_VALUE_FORMAT, OnSelchangeComboPositiveValueFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurrencyEditDlg message handlers

BOOL CCurrencyEditDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_clrBack=m_edit.GetBkColor();
	m_clrText=m_edit.GetTextColor();
	m_clrTextNegative=m_edit.GetNegativeTextColor();

	m_edit.SetToolTipText(_T("EditControl"));
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
	m_sPositiveValueFormat=m_edit.GetPositiveFormat();
	m_sCurrency=m_edit.GetCurrencyName();

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

void CCurrencyEditDlg::OnButtonBackcolor() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
	m_edit.SetBkColor(m_clrBack);
}

void CCurrencyEditDlg::OnButtonTextcolor() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetTextColor(m_clrText);
}

void CCurrencyEditDlg::OnButtonTextcolorNegative() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetNegativeTextColor(m_clrTextNegative);
}

void CCurrencyEditDlg::OnButtonFont() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_edit.SetFont(&m_font);
}

void CCurrencyEditDlg::OnCheckDecimalDigitCountIndefinite() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
	m_comboDecimalCount.EnableWindow(!m_bIndefiniteDecimalDigitCount);
	if(m_bIndefiniteDecimalDigitCount)
		m_edit.SetDecimalDigitCount(-1);
	else
		m_edit.SetDecimalDigitCount(m_nDecimalDigitCount);
}

void CCurrencyEditDlg::OnCheckNoGroup() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_comboGroupLength.EnableWindow(!m_bNoDiditInGroup);
	if(m_bNoDiditInGroup)
		m_edit.SetGroupLength(0);
	else
		m_edit.SetGroupLength(m_nGroupLength+1);
}

void CCurrencyEditDlg::OnEditchangeComboMask() 
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


void CCurrencyEditDlg::OnSelchangeComboMask() 
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

void CCurrencyEditDlg::OnCheckLeadingZero() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetShowLeadingZero(m_bLeadingZero);
}

void CCurrencyEditDlg::OnSelchangeComboDecimalDigitCount() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetDecimalDigitCount(m_nDecimalDigitCount);
}

void CCurrencyEditDlg::OnEditchangeComboDecimalSeparator() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetDecimalSeparator(m_sDecimalSeparator[0]);
}

void CCurrencyEditDlg::OnSelchangeComboDecimalSeparator() 
{
	// TODO: Add your control notification handler code here
	
	m_comboDecimalSeparator.GetLBText(m_comboDecimalSeparator.GetCurSel(),
		m_sDecimalSeparator);
	m_edit.SetDecimalSeparator(m_sDecimalSeparator[0]);
}

void CCurrencyEditDlg::OnSelchangeComboFractionalDigitCount() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetFractionalDigitCount(m_nFractionalDigitCount);
}

void CCurrencyEditDlg::OnSelchangeComboGroupLength() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetGroupLength(m_nGroupLength+1);
}

void CCurrencyEditDlg::OnEditchangeComboGroupSeparator() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetGroupSeparator(m_sGroupSeparator[0]);
}

void CCurrencyEditDlg::OnSelchangeComboGroupSeparator() 
{
	// TODO: Add your control notification handler code here
	
	m_comboGroupSeparator.GetLBText(m_comboGroupSeparator.GetCurSel(),
		m_sGroupSeparator);
	m_edit.SetGroupSeparator(m_sGroupSeparator[0]);
}

void CCurrencyEditDlg::OnEditchangeComboNegativeValueFormat() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetNegativeFormat(m_sNegativeValueFormat);
}

void CCurrencyEditDlg::OnSelchangeComboNegativeValueFormat() 
{
	// TODO: Add your control notification handler code here
	
	m_comboNegativeFormat.GetLBText(m_comboNegativeFormat.GetCurSel(),
		m_sNegativeValueFormat);
	m_edit.SetNegativeFormat(m_sNegativeValueFormat);
}

void CCurrencyEditDlg::OnEditchangeComboCurrencyName() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetCurrencyName(m_sCurrency);
}

void CCurrencyEditDlg::OnSelchangeComboCurrencyName() 
{
	// TODO: Add your control notification handler code here
	
	m_comboCurrencyName.GetLBText(m_comboCurrencyName.GetCurSel(),m_sCurrency);
	m_edit.SetCurrencyName(m_sCurrency);
}

void CCurrencyEditDlg::OnEditchangeComboPositiveValueFormat() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetPositiveFormat(m_sPositiveValueFormat);
}

void CCurrencyEditDlg::OnSelchangeComboPositiveValueFormat() 
{
	// TODO: Add your control notification handler code here
	
	m_comboPositiveFormat.GetLBText(m_comboPositiveFormat.GetCurSel(),
		m_sPositiveValueFormat);
	m_edit.SetPositiveFormat(m_sPositiveValueFormat);
}
