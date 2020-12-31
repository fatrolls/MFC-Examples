#include "stdafx.h"
#include "DB.h"
#include "DBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_X_SIZE		150
#define MIN_Y_SIZE		110

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

CDBDlg::CDBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDBDlg, CDialog)
	//{{AFX_MSG_MAP(CDBDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDBDlg::OnInitDialog()
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
	
	RECT rect;

	rect.left=0;
	rect.top=0;
	rect.right=MIN_X_SIZE;
	rect.bottom=MIN_Y_SIZE;
	MapDialogRect(&rect);
	rect.right+=50;
	rect.bottom+=50;
	MoveWindow(&rect);
	CenterWindow();
	
	return TRUE;
}

void CDBDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDBDlg::OnPaint() 
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

HCURSOR CDBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDBDlg::OnGetMinMaxInfo(MINMAXINFO *lpMMI) 
{
	RECT rect;
	SIZE sizeScreen;

	rect.left=0;
	rect.top=0;
	rect.right=MIN_X_SIZE;
	rect.bottom=MIN_Y_SIZE;
	MapDialogRect(&rect);
	lpMMI->ptMinTrackSize.x=
	(
		rect.right+::GetSystemMetrics(SM_CXSIZEFRAME)*2
	);
	lpMMI->ptMinTrackSize.y=
	(
		rect.bottom+::GetSystemMetrics(SM_CYCAPTION)+
		::GetSystemMetrics(SM_CYSIZEFRAME)*2
	);
	lpMMI->ptMaxTrackSize.x=lpMMI->ptMinTrackSize.x+100;
	lpMMI->ptMaxTrackSize.y=lpMMI->ptMinTrackSize.y+100;
	sizeScreen.cx=::GetSystemMetrics(SM_CXFULLSCREEN);
	sizeScreen.cy=::GetSystemMetrics(SM_CYFULLSCREEN);
	lpMMI->ptMaxPosition.x=0;
	lpMMI->ptMaxPosition.y=0;
	lpMMI->ptMaxSize.x=sizeScreen.cx/2;
	lpMMI->ptMaxSize.y=sizeScreen.cy/2;
}
