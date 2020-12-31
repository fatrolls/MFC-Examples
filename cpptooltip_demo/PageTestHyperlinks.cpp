// PageTestHyperlinks.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageTestHyperlinks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTestHyperlinks property page

IMPLEMENT_DYNCREATE(CPageTestHyperlinks, CPropertyPage)

CPageTestHyperlinks::CPageTestHyperlinks() : CPropertyPage(CPageTestHyperlinks::IDD)
{
	//{{AFX_DATA_INIT(CPageTestHyperlinks)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageTestHyperlinks::~CPageTestHyperlinks()
{
}

void CPageTestHyperlinks::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTestHyperlinks)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageTestHyperlinks, CPropertyPage)
	//{{AFX_MSG_MAP(CPageTestHyperlinks)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UNM_HYPERLINK_CLICKED, NotifyHyperlinkClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTestHyperlinks message handlers

BOOL CPageTestHyperlinks::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_tooltip.Create(this);
	m_tooltip.SetBehaviour(PPTOOLTIP_NOCLOSE_OVER | PPTOOLTIP_CLOSE_LEAVEWND | PPTOOLTIP_DISABLE_AUTOPOP);
	m_tooltip.SetCallbackHyperlink(this->GetSafeHwnd(), UNM_HYPERLINK_CLICKED);

	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), _T("To open URL click <b><a href=\"http://www.codeproject.com\">link</a></b>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON2), _T("If you want mail to me,<br>please click <b><a href=\"mailto:pustovoyt@mail.ru\">link</a></b>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON3), _T("To notify a parent about user's click, please click follow:<br><t><b><a msg=\"1\">link 1</a></b><br><t><b><a msg=\"2\">link 2</a></b><br><t><b><a msg=\"3\">link 3</a></b>"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON4), _T("<b><i>Click image to: ...</i></b><br><right><b>go to <h2>CodeProject</h2> <a href=\"http://www.codeproject.com\"><bmp idres=138 mask hotstyle=s></a></b><br><b>mail to me<a href=\"mailto:pustovoyt@mail.ru\"><icon idres=146 style=g hotstyle=s width=32 height=32></a></b><br><b>notify a parent <a msg=\"3\"><icon idres=142 style=g hotstyle width=32 height=32></a></b></right>"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageTestHyperlinks::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

LRESULT CPageTestHyperlinks::NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str.Format(_T("You're click a link %s"), (LPCTSTR)wParam);
	AfxMessageBox(str);

    return TRUE;
}

BOOL CPageTestHyperlinks::OnKillActive() 
{
	m_tooltip.HideTooltip();
	
	return CPropertyPage::OnKillActive();
}
