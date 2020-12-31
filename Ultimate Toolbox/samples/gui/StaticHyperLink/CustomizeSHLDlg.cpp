// CustomizeSHLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StaticHyperLink.h"
#include "CustomizeSHLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeSHLDlg dialog


CCustomizeSHLDlg::CCustomizeSHLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeSHLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeSHLDlg)
	m_sDefaultDirectory = _T("");
	m_bErrorNotify = FALSE;
	m_bFitToText = FALSE;
	m_bShowToolTip = FALSE;
	m_bUseWindowText = FALSE;
	m_sFile = _T("");
	m_sParameters = _T("");
	m_sToolTipText = _T("");
	m_clrUnvisited = 0;
	m_nActionID = -1;
	m_nCallbackMsgID = 0;
	m_clrVisited = 0;
	m_sFontName = _T("");
	m_sWindowText = _T("");
	m_bUseSpecialCursor = FALSE;
	//}}AFX_DATA_INIT
}


void CCustomizeSHLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeSHLDlg)
	DDX_Control(pDX, IDC_EDIT_WINDOW_TEXT, m_ctlEditWindowText);
	DDX_Control(pDX, IDC_COMBO_ACTION, m_ctlComboAction);
	DDX_Control(pDX, IDC_EDIT_TOOLTIP_TEXT, m_ctlEditToolTipText);
	DDX_Text(pDX, IDC_EDIT_DEFAULT_DIRECTORY, m_sDefaultDirectory);
	DDX_Check(pDX, IDC_CHECK_ERROR_NOTIFY, m_bErrorNotify);
	DDX_Check(pDX, IDC_CHECK_FIT_TO_TEXT, m_bFitToText);
	DDX_Check(pDX, IDC_CHECK_SHOW_TOOLTIP, m_bShowToolTip);
	DDX_Check(pDX, IDC_CHECK_USE_WINDOW_TEXT, m_bUseWindowText);
	DDX_Text(pDX, IDC_EDIT_FILE, m_sFile);
	DDX_Text(pDX, IDC_EDIT_PARAMETERS, m_sParameters);
	DDX_Text(pDX, IDC_EDIT_TOOLTIP_TEXT, m_sToolTipText);
	DDX_Text(pDX, IDC_EDIT_UNVISITED_COLOR, m_clrUnvisited);
	DDX_CBIndex(pDX, IDC_COMBO_ACTION, m_nActionID);
	DDX_Text(pDX, IDC_EDIT_CALLBACK_MESSAGE_ID, m_nCallbackMsgID);
	DDX_Text(pDX, IDC_EDIT_VISITED_COLOR, m_clrVisited);
	DDX_Text(pDX, IDC_EDIT_FONT_NAME, m_sFontName);
	DDX_Text(pDX, IDC_EDIT_WINDOW_TEXT, m_sWindowText);
	DDX_Check(pDX, IDC_CHECK_USE_SPECIAL_CURSOR, m_bUseSpecialCursor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeSHLDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomizeSHLDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLR_UNVISITED, OnButtonClrUnvisited)
	ON_BN_CLICKED(IDC_BUTTON_CLR_VISITED, OnButtonClrVisited)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	ON_BN_CLICKED(IDC_CHECK_SHOW_TOOLTIP, OnCheckShowTooltip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeSHLDlg message handlers

void CCustomizeSHLDlg::OnButtonClrUnvisited() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	// Use color common dialog
	CColorDialog colorDlg(m_clrUnvisited);
	if(colorDlg.DoModal()==IDOK)
	{
		m_clrUnvisited=colorDlg.GetColor();
		UpdateData(FALSE);
	}
}

void CCustomizeSHLDlg::OnButtonClrVisited() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	// Use color common dialog
	CColorDialog colorDlg(m_clrVisited);
	if(colorDlg.DoModal()==IDOK)
	{
		m_clrVisited=colorDlg.GetColor();
		UpdateData(FALSE);
	}
}

void CCustomizeSHLDlg::OnButtonFont() 
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

void CCustomizeSHLDlg::OnCheckShowTooltip() 
{
	// TODO: Add your control notification handler code here

	ShowControls();
}

BOOL CCustomizeSHLDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if(m_pStaticHyperLink->IsStaticText(m_pStaticHyperLink))
	{
		CString sText;
		m_pStaticHyperLink->GetWindowText(sText);
		if(!sText.IsEmpty())
		{
			sText=_T("Customize: ")+sText;
			SetWindowText(sText);
		}
	}

	for(int nIndex=0; nIndex<ID_HL_ACTIONNUMBER; nIndex++)
	{
		CString sAction;
		VERIFY(sAction.LoadString(m_szAction[nIndex]));
		m_ctlComboAction.AddString(sAction);
	}

	GetVars();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomizeSHLDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	SetVars();

	CDialog::OnOK();
}

void CCustomizeSHLDlg::GetVars()
{
	COXHyperLinkAction hla=m_pStaticHyperLink->GetAction();

	m_nActionID=hla.GetActionID();
	m_sFile=hla.GetFile();
	m_sParameters=hla.GetParameters();
	m_sDefaultDirectory=hla.GetDefaultDirectory();
	m_nCallbackMsgID=hla.GetCallbackMsg();

	m_bUseSpecialCursor=m_pStaticHyperLink->GetLinkCursor()==NULL ? FALSE : TRUE;
	m_bErrorNotify=m_pStaticHyperLink->GetErrorNotify();
	m_bFitToText=m_pStaticHyperLink->GetFitToText();
	m_bShowToolTip=m_pStaticHyperLink->GetShowToolTip();
	m_bUseWindowText=m_pStaticHyperLink->GetUseWindowText();
	m_sToolTipText=m_pStaticHyperLink->GetToolTipText();
	m_clrUnvisited=m_pStaticHyperLink->GetUnvisitedColor();
	m_clrVisited=m_pStaticHyperLink->GetVisitedColor();
	if(m_pStaticHyperLink->GetTextLogFont(&m_lf))
	{
		m_sFontName=m_lf.lfFaceName;
	}
	else
	{
		m_sFontName.Empty();
	}

	if(m_pStaticHyperLink->IsStaticText(m_pStaticHyperLink))
	{
		m_pStaticHyperLink->GetWindowText(m_sWindowText);
	}
	else
	{
		m_sWindowText.Empty();
	}

	UpdateData(FALSE);

	ShowControls();
}

void CCustomizeSHLDlg::SetVars()
{
	UpdateData();

	COXHyperLinkAction hla=m_pStaticHyperLink->GetAction();
	hla.SetActionID(m_nActionID);
	hla.SetFile(m_sFile);
	hla.SetParameters(m_sParameters);
	hla.SetDefaultDirectory(m_sDefaultDirectory);
	hla.SetCallbackMsg(m_nCallbackMsgID);
	m_pStaticHyperLink->SetAction(hla);

	if(m_bUseSpecialCursor)
	{
		m_pStaticHyperLink->SetDefaultLinkCursor();
	}
	else
	{
		m_pStaticHyperLink->SetLinkCursor(NULL);
	}
	m_pStaticHyperLink->SetErrorNotify(m_bErrorNotify);
	m_pStaticHyperLink->SetFitToText(m_bFitToText);
	m_pStaticHyperLink->SetShowToolTip(m_bShowToolTip);
	m_pStaticHyperLink->SetUseWindowText(m_bUseWindowText);
	m_pStaticHyperLink->SetToolTipText(m_sToolTipText);
	m_pStaticHyperLink->SetUnvisitedColor(m_clrUnvisited);
	m_pStaticHyperLink->SetVisitedColor(m_clrVisited);

	if(!m_sFontName.IsEmpty())
	{
		m_pStaticHyperLink->SetTextLogFont(&m_lf);
	}
	else
	{
		m_pStaticHyperLink->SetTextLogFont(NULL);
	}

	if(m_pStaticHyperLink->IsStaticText(m_pStaticHyperLink))
	{
		m_pStaticHyperLink->SetWindowText(m_sWindowText);
	}
}

void CCustomizeSHLDlg::ShowControls() 
{
	UpdateData(TRUE);

	m_ctlEditToolTipText.EnableWindow(m_bShowToolTip);
	m_ctlEditWindowText.EnableWindow(m_pStaticHyperLink->
		IsStaticText(m_pStaticHyperLink));
}











