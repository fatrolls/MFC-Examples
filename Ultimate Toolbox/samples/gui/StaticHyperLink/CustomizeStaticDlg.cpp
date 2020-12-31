// CustomizeStaticDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StaticHyperLink.h"
#include "CustomizeStaticDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeStaticDlg dialog


CCustomizeStaticDlg::CCustomizeStaticDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeStaticDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeStaticDlg)
	m_bFitToText = FALSE;
	m_bShowToolTip = FALSE;
	m_sToolTipText = _T("");
	m_clr = 0;
	m_sFontName = _T("");
	m_sWindowText = _T("");
	//}}AFX_DATA_INIT
}


void CCustomizeStaticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeStaticDlg)
	DDX_Control(pDX, IDC_EDIT_WINDOW_TEXT, m_ctlEditWindowText);
	DDX_Control(pDX, IDC_EDIT_TOOLTIP_TEXT, m_ctlEditToolTipText);
	DDX_Check(pDX, IDC_CHECK_FIT_TO_TEXT, m_bFitToText);
	DDX_Check(pDX, IDC_CHECK_SHOW_TOOLTIP, m_bShowToolTip);
	DDX_Text(pDX, IDC_EDIT_TOOLTIP_TEXT, m_sToolTipText);
	DDX_Text(pDX, IDC_EDIT_COLOR, m_clr);
	DDX_Text(pDX, IDC_EDIT_FONT_NAME, m_sFontName);
	DDX_Text(pDX, IDC_EDIT_WINDOW_TEXT, m_sWindowText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeStaticDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomizeStaticDlg)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	ON_BN_CLICKED(IDC_CHECK_SHOW_TOOLTIP, OnCheckShowTooltip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeStaticDlg message handlers
void CCustomizeStaticDlg::OnButtonColor() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	// Use color common dialog
	CColorDialog colorDlg(m_clr);
	if(colorDlg.DoModal()==IDOK)
	{
		m_clr=colorDlg.GetColor();
		UpdateData(FALSE);
	}
}

void CCustomizeStaticDlg::OnButtonFont() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	// Use font common dialog
	CFontDialog fontDlg(&m_lf);
	if(fontDlg.DoModal()==IDOK)
	{
		fontDlg.GetCurrentFont(&m_lf);
		m_sFontName=m_lf.lfFaceName;
		UpdateData(FALSE);
	}
}

void CCustomizeStaticDlg::OnCheckShowTooltip() 
{
	// TODO: Add your control notification handler code here

	ShowControls();
}

BOOL CCustomizeStaticDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if(m_pStatic->IsStaticText(m_pStatic))
	{
		CString sText;
		m_pStatic->GetWindowText(sText);
		if(!sText.IsEmpty())
		{
			sText=_T("Customize: ")+sText;
			SetWindowText(sText);
		}
	}

	GetVars();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomizeStaticDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	SetVars();

	CDialog::OnOK();
}

void CCustomizeStaticDlg::GetVars()
{
	m_bFitToText=m_pStatic->GetFitToText();
	m_bShowToolTip=m_pStatic->GetShowToolTip();
	m_sToolTipText=m_pStatic->GetToolTipText();
	m_clr=m_pStatic->GetTextColor();
	if(m_pStatic->GetTextLogFont(&m_lf))
	{
		m_sFontName=m_lf.lfFaceName;
	}
	else
	{
		m_sFontName.Empty();
	}

	if(m_pStatic->IsStaticText(m_pStatic))
	{
		m_pStatic->GetWindowText(m_sWindowText);
	}
	else
	{
		m_sWindowText.Empty();
	}

	UpdateData(FALSE);

	ShowControls();
}

void CCustomizeStaticDlg::SetVars()
{
	UpdateData();

	m_pStatic->SetFitToText(m_bFitToText);
	m_pStatic->SetShowToolTip(m_bShowToolTip);
	m_pStatic->SetToolTipText(m_sToolTipText);
	m_pStatic->SetTextColor(m_clr);

	if(!m_sFontName.IsEmpty())
	{
		m_pStatic->SetTextLogFont(&m_lf);
	}
	else
	{
		m_pStatic->SetTextLogFont(NULL);
	}

	if(m_pStatic->IsStaticText(m_pStatic))
	{
		m_pStatic->SetWindowText(m_sWindowText);
	}
}

void CCustomizeStaticDlg::ShowControls() 
{
	UpdateData(TRUE);

	m_ctlEditToolTipText.EnableWindow(m_bShowToolTip);
	m_ctlEditWindowText.EnableWindow(m_pStatic->
		IsStaticText(m_pStatic));
}



