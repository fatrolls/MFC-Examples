// ExtendedEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExtendedEditControls.h"
#include "ExtendedEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendedEditDlg dialog

CExtendedEditDlg::CExtendedEditDlg():CPropertyPage(CExtendedEditDlg::IDD)
{
	//{{AFX_DATA_INIT(CExtendedEditDlg)
	m_sMask = _T("");
	m_sTooltipText = _T("");
	//}}AFX_DATA_INIT
}

void CExtendedEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtendedEditDlg)
	DDX_Control(pDX, IDC_STATIC_BOTTOM, m_sepBottom);
	DDX_Control(pDX, IDC_COMBO_MASK, m_comboMask);
	DDX_Control(pDX, IDC_STATIC_NUMERIC_EDIT, m_sepNumericEdit);
	DDX_Control(pDX, IDC_STATIC_CONTROL_APPEARANCE, m_sepControlAppearance);
	DDX_Control(pDX, IDC_BUTTON_FONT, m_btnFont);
	DDX_Control(pDX, IDC_EDIT_TEST, m_edit);
	DDX_Control(pDX, IDC_BUTTON_TEXTCOLOR, m_btnTextColor);
	DDX_Control(pDX, IDC_BUTTON_BACKCOLOR, m_btnBackColor);
	DDX_CBString(pDX, IDC_COMBO_MASK, m_sMask);
	DDX_Text(pDX, IDC_EDIT_TOOLTIP, m_sTooltipText);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_BACKCOLOR, m_clrBack);
	DDX_ColorPicker(pDX, IDC_BUTTON_TEXTCOLOR, m_clrText);
	DDX_FontPickerFont(pDX, IDC_BUTTON_FONT, &m_font);
}

BEGIN_MESSAGE_MAP(CExtendedEditDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CExtendedEditDlg)
	ON_BN_CLICKED(IDC_BUTTON_BACKCOLOR, OnButtonBackcolor)
	ON_BN_CLICKED(IDC_BUTTON_TEXTCOLOR, OnButtonTextcolor)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	ON_CBN_SELCHANGE(IDC_COMBO_MASK, OnSelchangeComboMask)
	ON_CBN_EDITCHANGE(IDC_COMBO_MASK, OnEditchangeComboMask)
	ON_EN_CHANGE(IDC_EDIT_TOOLTIP, OnChangeEditTooltip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendedEditDlg message handlers

BOOL CExtendedEditDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_clrBack=m_edit.GetBkColor();
	m_clrText=m_edit.GetTextColor();

	m_edit.SetToolTipText(_T("EditControl"));
	m_sMask=m_edit.GetMask();
	m_sTooltipText=m_edit.GetToolTipText();

	m_btnBackColor.SetToolTip(TRUE);
	m_btnTextColor.SetToolTip(TRUE);

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
	m_sepControlAppearance.SetTextColor(clr);


	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExtendedEditDlg::OnButtonBackcolor() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
	m_edit.SetBkColor(m_clrBack);
}

void CExtendedEditDlg::OnButtonTextcolor() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_edit.SetTextColor(m_clrText);
}

void CExtendedEditDlg::OnButtonFont() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_edit.SetFont(&m_font);
}

void CExtendedEditDlg::OnEditchangeComboMask() 
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


void CExtendedEditDlg::OnSelchangeComboMask() 
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


void CExtendedEditDlg::OnChangeEditTooltip() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_edit.SetToolTipText(m_sTooltipText);
}
