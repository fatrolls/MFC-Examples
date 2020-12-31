// TestPageGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "TestPageGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPageGeneral property page

IMPLEMENT_DYNCREATE(CTestPageGeneral, CPropertyPage)

CTestPageGeneral::CTestPageGeneral() : CPropertyPage(CTestPageGeneral::IDD)
{
	//{{AFX_DATA_INIT(CTestPageGeneral)
	m_tooltip_string = _T("<table>\r\n<tr><td>\r\n<ilst idres=159 cx=32 cy=32 mask width=200% height=200% speed=1></td>\r\n<td><center><h2>Dynamic Tooltip</h2></center><br>\r\n<hr color=green><br>\r\n<font color=red size=12pt style=b>NEW :</font><br>\r\n<t>· more styles;<br>\r\n<t>· all styles in CSS format;<br>\r\n<t>· support hyperlinks;<br>\r\n<t>· support tables;<br>\r\n<t>· support image efffects (grayed, darked, lighted);<br>\r\n<t>· support a gradient shadow;<br>\r\n<t>· support multiple monitors;<br>\r\n<t>· support hot areas;<br>\r\n<t>· support debug mode;<br>\r\n<t>· support fade-in and fade-out;<br>\r\n<t>... and more\r\n</td></tr>\r\n</table>");
	m_disable_look = FALSE;
	m_enable_escape = FALSE;
	//}}AFX_DATA_INIT
}

CTestPageGeneral::~CTestPageGeneral()
{
}

void CTestPageGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPageGeneral)
	DDX_Text(pDX, IDC_TOOLTIP_STRING, m_tooltip_string);
	DDX_Check(pDX, IDC_DISABLE_LOOK_BTN, m_disable_look);
	DDX_Check(pDX, IDC_CHECK1, m_enable_escape);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestPageGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CTestPageGeneral)
	ON_BN_CLICKED(IDC_DISABLE_LOOK_BTN, OnDisableLookButton)
	ON_EN_CHANGE(IDC_TOOLTIP_STRING, OnChangeTooltipString)
	ON_BN_CLICKED(IDC_BUTTON1, OnShowHelp)
	ON_BN_CLICKED(IDC_BUTTON2, OnShowHelp2)
	ON_BN_CLICKED(IDC_CHECK1, OnEnableSequences)
	//}}AFX_MSG_MAP
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPageGeneral message handlers

BOOL CTestPageGeneral::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

		//Create Tooltip
	m_tooltip.Create(this);

	//Adding tools
	m_tooltip.AddTool(GetDlgItem(IDC_LOOK_TOOLTIP), m_tooltip_string);
	//m_tooltip.AddTool(GetDlgItem(IDC_DISABLE_LOOK_BTN), _T("Test"), IDR_CPPTOOTYPE, CSize(0, 0));
	m_tooltip.AddTool(GetDlgItem(IDC_DISABLE_LOOK_BTN), _T("<center><h2>Disables a button</h2></center><br><hr color=green><br>Checks to disables a button!!!"), IDI_ICON_INFORMATION, CSize(32, 32));
	m_tooltip.SetNotify();
	m_tooltip.SetColorBk(RGB(255, 0, 0));
	m_tooltip.SetMaxTipWidth(0);
	m_tooltip.SetImageList(IDB_SMILES, 16, 16, 22);
//	m_tooltip.EnableTextWrap();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	OnEnableSequences();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTestPageGeneral::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CTestPageGeneral::OnDisableLookButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDlgItem(IDC_LOOK_TOOLTIP)->EnableWindow(!m_disable_look);
}

void CTestPageGeneral::OnChangeTooltipString() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CTestPageGeneral::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;
	
	if (NULL == pNotify->hwndTool)
	{
		//Order to update a tooltip for a current Tooltip Help
		//He has not a handle of the window
		//If you want change tooltip's parameter than make it's here
	}
	else
	{
		//Order to update a tooltip for a specified window as tooltip's tool

		//Gets a ID of the window if needed
		UINT nID = CWnd::FromHandle(pNotify->hwndTool)->GetDlgCtrlID();
		
		//Change a tooltip's parameters for a current window (control)
		switch (nID)
		{
		case IDC_LOOK_TOOLTIP:
			pNotify->ti->sTooltip = m_tooltip_string;
			break;
		} //switch
	} //if
} //End NotifyDisplayTooltip

void CTestPageGeneral::OnShowHelp() 
{
	CRect rect;
	GetDlgItem(IDC_BUTTON1)->GetWindowRect(&rect);
	CPoint pt = rect.CenterPoint();
	m_tooltip.ShowHelpTooltip(&pt, _T("This is a help tooltip 1"));
}

void CTestPageGeneral::OnShowHelp2() 
{
	CRect rect;
	GetDlgItem(IDC_BUTTON2)->GetWindowRect(&rect);
	CPoint pt = rect.CenterPoint();
	m_tooltip.ShowHelpTooltip(&pt, _T("This is a help tooltip 2"));
}

void CTestPageGeneral::OnEnableSequences() 
{
	UpdateData();
	m_tooltip.EnableEscapeSequences(m_enable_escape);
}

BOOL CTestPageGeneral::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_tooltip.HideTooltip();
	return CPropertyPage::OnKillActive();
}
