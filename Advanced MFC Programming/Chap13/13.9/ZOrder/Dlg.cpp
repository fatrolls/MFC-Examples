#include "stdafx.h"
#include "ZOrder.h"
#include "Dlg.h"

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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CZOrderDlg::CZOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZOrderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZOrderDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZOrderDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZOrderDlg, CDialog)
	//{{AFX_MSG_MAP(CZOrderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_BOTTOM, OnRadioBottom)
	ON_BN_CLICKED(IDC_RADIO_NOTOPMOST, OnRadioNotopmost)
	ON_BN_CLICKED(IDC_RADIO_TOP, OnRadioTop)
	ON_BN_CLICKED(IDC_RADIO_TOPMOST, OnRadioTopmost)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CZOrderDlg::OnInitDialog()
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
	
	return TRUE;
}

void CZOrderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CZOrderDlg::OnPaint() 
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

HCURSOR CZOrderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CZOrderDlg::OnRadioBottom() 
{
	SetWindowPos(&wndBottom, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE);
}

void CZOrderDlg::OnRadioNotopmost() 
{
	SetWindowPos(&wndNoTopMost, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE);
}

void CZOrderDlg::OnRadioTop() 
{
	SetWindowPos(&wndTop, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE);
}

void CZOrderDlg::OnRadioTopmost() 
{
	SetWindowPos(&wndTopMost, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE);
}
