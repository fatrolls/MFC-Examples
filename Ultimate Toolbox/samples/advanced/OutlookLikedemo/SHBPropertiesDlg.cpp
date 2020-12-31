// SHBPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Outlook.h"
#include "SHBPropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSHBPropertiesDlg dialog


CSHBPropertiesDlg::CSHBPropertiesDlg(COXShortcutBar* pShortcutBar, 
									 CWnd* pParent /*=NULL*/)
	: CDialog(CSHBPropertiesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSHBPropertiesDlg)
	m_bApplyOnlyToExpanded = TRUE;
	m_nBottomMargin = 0;
	m_nGroupMargin = 0;
	m_nRightMargin = 0;
	m_nLeftMargin = 0;
	m_nScrollBtnHeight = 0;
	m_nScrollBtnWidth = 0;
	m_nTopMargin = 0;
	m_sNameTextFont = _T("");
	m_sNameHeaderFont = _T("");
	m_nHeaderHeight = 0;
	//}}AFX_DATA_INIT

	ASSERT(pShortcutBar);
	m_pShortcutBar=pShortcutBar;
}


void CSHBPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSHBPropertiesDlg)
	DDX_Control(pDX, IDC_NAMETEXTFONT, m_ctlNameTextFont);
	DDX_Control(pDX, IDC_NAMEHDRFONT, m_ctlNameHeaderFont);
	DDX_Control(pDX, IDC_HDRCLRBACK, m_btnHeaderClrBack);
	DDX_Control(pDX, IDC_CLRBACK, m_btnClrBack);
	DDX_Check(pDX, IDC_CHECK_APPLYTOEXPANDED, m_bApplyOnlyToExpanded);
	DDX_Text(pDX, IDC_EDIT_BOTTOMMARGIN, m_nBottomMargin);
	DDX_Text(pDX, IDC_EDIT_GRPMARGIN, m_nGroupMargin);
	DDX_Text(pDX, IDC_EDIT_RIGHTMARGIN, m_nRightMargin);
	DDX_Text(pDX, IDC_EDIT_LEFTMARGIN, m_nLeftMargin);
	DDX_Text(pDX, IDC_EDIT_SCROLLBTNHEIGHT, m_nScrollBtnHeight);
	DDX_Text(pDX, IDC_EDIT_SCROLLBTNWIDTH, m_nScrollBtnWidth);
	DDX_Text(pDX, IDC_EDIT_TOPMARGIN, m_nTopMargin);
	DDX_Text(pDX, IDC_NAMETEXTFONT, m_sNameTextFont);
	DDX_Text(pDX, IDC_NAMEHDRFONT, m_sNameHeaderFont);
	DDX_Text(pDX, IDC_EDIT_HDRHEIGHT, m_nHeaderHeight);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_CLRBACK, m_clrBackground);
	DDX_ColorPicker(pDX, IDC_HDRCLRBACK, m_clrHeaderBackground);
}


BEGIN_MESSAGE_MAP(CSHBPropertiesDlg, CDialog)
	//{{AFX_MSG_MAP(CSHBPropertiesDlg)
	ON_BN_CLICKED(IDC_HDRFONT, OnHdrfont)
	ON_BN_CLICKED(IDC_TEXTFONT, OnTextfont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSHBPropertiesDlg message handlers

void CSHBPropertiesDlg::OnHdrfont() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData(TRUE))
		return;

	// Use font common dialog
	CFontDialog fontDlg(&m_lfHeader);
	fontDlg.m_cf.rgbColors=m_clrHeaderText;
	if(fontDlg.DoModal()==IDOK)
	{
		m_clrHeaderText=fontDlg.GetColor();
		fontDlg.GetCurrentFont(&m_lfHeader);
		m_sNameHeaderFont.Format(_T("%d pt, %s"),abs(m_lfHeader.lfHeight),
			m_lfHeader.lfFaceName);
		m_ctlNameHeaderFont.SetTextLogFont(&m_lfHeader);
		m_ctlNameHeaderFont.SetTextColor(m_clrHeaderText,TRUE);
		UpdateData(FALSE);
	}
}

void CSHBPropertiesDlg::OnTextfont() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData(TRUE))
		return;

	// Use font common dialog
	CFontDialog fontDlg(&m_lfText);
	fontDlg.m_cf.rgbColors=m_clrText;
	if(fontDlg.DoModal()==IDOK)
	{
		m_clrText=fontDlg.GetColor();
		fontDlg.GetCurrentFont(&m_lfText);
		m_sNameTextFont.Format(_T("%d pt, %s"),abs(m_lfText.lfHeight),
			m_lfText.lfFaceName);
		m_ctlNameTextFont.SetTextLogFont(&m_lfText);
		m_ctlNameTextFont.SetTextColor(m_clrText);
		UpdateData(FALSE);
	}
}

void CSHBPropertiesDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	SetVars();
	
	CDialog::OnOK();
}

BOOL CSHBPropertiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	GetVars();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSHBPropertiesDlg::GetVars()
{
	m_nLeftMargin=m_pShortcutBar->GetChildWndMargins().left;
	m_nTopMargin=m_pShortcutBar->GetChildWndMargins().top;
	m_nRightMargin=m_pShortcutBar->GetChildWndMargins().right;
	m_nBottomMargin=m_pShortcutBar->GetChildWndMargins().bottom;

	m_nGroupMargin=m_pShortcutBar->GetGroupMargin();

	m_nScrollBtnHeight=m_pShortcutBar->GetScrollButtonSize().cy;
	m_nScrollBtnWidth=m_pShortcutBar->GetScrollButtonSize().cx;

	HSHBGROUP hGroup=m_pShortcutBar->GetExpandedGroup();
	ASSERT(hGroup);

	m_nHeaderHeight=m_pShortcutBar->GetGroupHeaderHeight(hGroup);

	m_clrBackground=m_pShortcutBar->GetGroupBkColor(hGroup);
	m_clrHeaderBackground=m_pShortcutBar->GetGroupHeaderBkColor(hGroup);
	m_clrText=m_pShortcutBar->GetGroupTextColor(hGroup);
	m_clrHeaderText=m_pShortcutBar->GetGroupHeaderTextColor(hGroup);

	CFont font;
	LPLOGFONT plf=m_pShortcutBar->GetGroupTextFont(hGroup);
	ASSERT(plf);
	VERIFY(font.CreateFontIndirect(plf));
	VERIFY(font.GetLogFont(&m_lfText));

	plf=m_pShortcutBar->GetGroupHeaderTextFont(hGroup);
	ASSERT(plf);
	if((HFONT)font)
		font.DeleteObject();
	VERIFY(font.CreateFontIndirect(plf));
	VERIFY(font.GetLogFont(&m_lfHeader));

	m_sNameTextFont.Format(_T("%d pt, %s"),abs(m_lfText.lfHeight),m_lfText.lfFaceName);
	m_ctlNameTextFont.SetTextColor(m_clrText);
	m_ctlNameTextFont.SetTextLogFont(&m_lfText);

	m_sNameHeaderFont.Format(_T("%d pt, %s"),abs(m_lfHeader.lfHeight),
		m_lfHeader.lfFaceName);
	m_ctlNameHeaderFont.SetTextColor(m_clrHeaderText);
	m_ctlNameHeaderFont.SetTextLogFont(&m_lfHeader);

	m_btnHeaderClrBack.SetDefaultColor(::GetSysColor(COLOR_BTNFACE));
	m_btnClrBack.SetDefaultColor(::GetSysColor(COLOR_3DSHADOW));

	UpdateData(FALSE);

	ShowControls();
}

void CSHBPropertiesDlg::SetVars()
{
	UpdateData();

	m_pShortcutBar->SetChildWndMargins(CRect(m_nLeftMargin,m_nTopMargin,
		m_nRightMargin,m_nBottomMargin));
	m_pShortcutBar->SetGroupMargin(m_nGroupMargin);

	m_pShortcutBar->SetScrollButtonSize(CSize(m_nScrollBtnWidth,m_nScrollBtnHeight));

	HSHBGROUP hGroup=NULL;
	if(m_bApplyOnlyToExpanded)
	{
		hGroup=m_pShortcutBar->GetExpandedGroup();
		ASSERT(hGroup);
	}

	m_pShortcutBar->SetGroupHeaderHeight(hGroup,m_nHeaderHeight);

	m_pShortcutBar->SetGroupBkColor(hGroup,m_clrBackground);
	m_pShortcutBar->SetGroupHeaderBkColor(hGroup,m_clrHeaderBackground);
	m_pShortcutBar->SetGroupTextColor(hGroup,m_clrText);
	m_pShortcutBar->SetGroupHeaderTextColor(hGroup,m_clrHeaderText);

	m_pShortcutBar->SetGroupHeaderTextFont(hGroup,&m_lfHeader);
	m_pShortcutBar->SetGroupTextFont(hGroup,&m_lfText);

	m_pShortcutBar->RedrawBar();
}

void CSHBPropertiesDlg::ShowControls() 
{
}

