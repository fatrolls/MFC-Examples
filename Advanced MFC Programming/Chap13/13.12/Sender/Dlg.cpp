#include "stdafx.h"
#include "Sender.h"
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

UINT g_uMsgSendStr=0;
UINT g_uMsgReceived=0;

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSenderDlg::CSenderDlg(CWnd* pParent /*=NULL*/) : CDialog(CSenderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSenderDlg)
	m_nCount = 0;
	m_szText = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSenderDlg)
	DDX_Text(pDX, IDC_EDIT_COUNT, m_nCount);
	DDX_Text(pDX, IDC_EDIT_SEND, m_szText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSenderDlg, CDialog)
	//{{AFX_MSG_MAP(CSenderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(g_uMsgReceived, OnReceive)
END_MESSAGE_MAP()

BOOL CSenderDlg::OnInitDialog()
{
	g_uMsgSendStr=::RegisterWindowMessage(MSG_SENDSTRING);
	g_uMsgReceived=::RegisterWindowMessage(MSG_RECEIVED);

	m_hMapFile=::CreateFileMapping
	(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		BUFFER_SIZE,
		MAPPING_PROJECT
	);
 
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

void CSenderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSenderDlg::OnPaint() 
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

HCURSOR CSenderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSenderDlg::OnButtonSend() 
{
	CWnd *pWnd;
	LPSTR lpMapAddress;

	UpdateData(TRUE);
	
	lpMapAddress=(LPSTR)MapViewOfFile
	(
		m_hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0
	);
 
	if(lpMapAddress != NULL)
	{ 
		memcpy(lpMapAddress, m_szText, max(m_szText.GetLength(), BUFFER_SIZE));
	} 
	pWnd=CWnd::FindWindow(CLASS_NAME_RECIEVER, NULL);
	if(pWnd != NULL && ::IsWindow(pWnd->m_hWnd))
	{
		pWnd->PostMessage(g_uMsgSendStr, (WPARAM)GetSafeHwnd(), (LPARAM)NULL);
	}
}

LONG CSenderDlg::OnReceive(UINT wParam, LONG lParam)
{
	m_nCount++;
	UpdateData(FALSE);

	return (LONG)TRUE;
}
