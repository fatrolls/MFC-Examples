#include "stdafx.h"
#include "CCtl.h"
#include "CCtlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCCtlDlg::CCCtlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCCtlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCCtlDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCCtlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCCtlDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCCtlDlg, CDialog)
	//{{AFX_MSG_MAP(CCCtlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_STR, OnDeltaposSpinStr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCCtlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	(
		(CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_VER)
	)->SetBuddy(GetDlgItem(IDC_EDIT_VER));
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_VER))->SetRange(0, 200);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_VER))->SetBase(16);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_VER))->SetPos(100);
	(
		(CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_HOR)
	)->SetBuddy(GetDlgItem(IDC_EDIT_HOR));
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_HOR))->SetRange(50, 0);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_HOR))->SetBase(10);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_HOR))->SetPos(25);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_STR))->SetRange(0, 9);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_STR))->SetPos(0);
	GetDlgItem(IDC_EDIT_STR)->SetWindowText("Zero");
	
	return TRUE;
}

void CCCtlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CCCtlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CCCtlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCCtlDlg::OnDeltaposSpinStr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nNewPos;
	char szNumber[][16]=
	{
		"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"
	};
	NM_UPDOWN *pNMUpDown=(NM_UPDOWN*)pNMHDR;
	
	nNewPos=pNMUpDown->iPos+pNMUpDown->iDelta;
	if(nNewPos >= 0 && nNewPos <= 9)
	{
		GetDlgItem(IDC_EDIT_STR)->SetWindowText(szNumber[nNewPos]);
	}
	*pResult=0;
}
