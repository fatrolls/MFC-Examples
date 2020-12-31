#include "stdafx.h"
#include "CButtonST_Demo.h"
#include "CButtonST_DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDS_MAILADDR	_T("mailto:davide_calabro@yahoo.com")
#define IDS_WEBADDR		_T("http://www.softechsoftware.it")

CCButtonST_DemoDlg::CCButtonST_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCButtonST_DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCButtonST_DemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCButtonST_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCButtonST_DemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	// Make our buttons a CButtonST buttons
	DDX_Control(pDX, IDCANCEL, m_btnClose);

	DDX_Control(pDX, IDC_TAB, m_tabMyTabCtrl);
	DDX_Control(pDX, IDC_EMAILLINK, m_EMailLink);
	DDX_Control(pDX, IDC_HOMEPAGELINK, m_HomePageLink);
}

BEGIN_MESSAGE_MAP(CCButtonST_DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCButtonST_DemoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCButtonST_DemoDlg::OnInitDialog()
{
	short	shBtnColor = 30;

	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// Button close
	m_btnClose.SetIcon(IDI_NO3, (int)BTNST_AUTO_GRAY);
	m_btnClose.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnClose.SetTooltipText(_T("Close the application"));
#ifdef	BTNST_USE_SOUND
	//m_btnClose.SetSound(MAKEINTRESOURCE(IDR_WAVSTART), ::GetModuleHandle(NULL), TRUE, FALSE);
#endif

	m_tabMyTabCtrl.InsertItem(0, _T("Basic features"));
	m_tabMyTabCtrl.InsertItem(1, _T("Advanced features"));
	m_tabMyTabCtrl.InsertItem(2, _T("Transparent effect"));
	m_tabMyTabCtrl.InsertItem(3, _T("CShadeButtonST"));
	m_tabMyTabCtrl.InsertItem(4, _T("About"));
	m_tabMyTabCtrl.Init();

	// Set HyperLink for E-Mail
	m_EMailLink.SetURL(IDS_MAILADDR);
	m_EMailLink.SetUnderline(CHyperLink::ulAlways);

	// Set HyperLink for Home Page
	m_HomePageLink.SetURL(IDS_WEBADDR);
	m_HomePageLink.SetUnderline(CHyperLink::ulAlways);

	return TRUE;
} // End of OnInitDialog
