#include "stdafx.h"
#include "DDECli.h"
#include "DDEDlg.h"

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


TCHAR CDDECliDlg::m_szService[]=TEXT("PROGMAN");
DWORD CDDECliDlg::m_dwInst=0;
HSZ CDDECliDlg::m_hszServiceName=0;
HCONV CDDECliDlg::m_hConvClient=0;

CDDECliDlg::CDDECliDlg(CWnd* pParent):CDialog(CDDECliDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDDECliDlg)
	m_szCommand = _T("");
	//}}AFX_DATA_INIT
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_szFormats[0]="[CreateGroup(%s)]";
	m_szFormats[1]="[ShowGroup(%s,1)]";
	m_szFormats[2]="[DeleteGroup(%s)]";
	m_szFormats[3]="[AddItem(%s,%s)]";
	m_szFormats[4]="[DeleteItem(%s)]";
}

void CDDECliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDDECliDlg)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbType);
	DDX_Control(pDX, IDC_BUTTON_COMMAND, m_btnCommand);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_EDIT, m_ecMsg);
	DDX_Text(pDX, IDC_EDIT_COMMAND, m_szCommand);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDDECliDlg, CDialog)
	//{{AFX_MSG_MAP(CDDECliDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_COMMAND, OnButtonCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDDECliDlg::OnInitDialog()
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
	
	InitializeDDE();

	m_btnCommand.EnableWindow(FALSE);

	return TRUE;
}

void CDDECliDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDDECliDlg::OnPaint() 
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

HCURSOR CDDECliDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

HDDEDATA CALLBACK CDDECliDlg::DdeCallback
(
	UINT wType,
	UINT wFormat,
	HCONV hConv,
	HSZ hszTopic,
	HSZ hszItem,
	HDDEDATA hData,
	DWORD lData1,
	DWORD lData2
)
{
	switch(wType)
	{
	    case XTYP_REGISTER: 
        case XTYP_UNREGISTER:
		case XTYP_ADVSTART:
		case XTYP_ADVDATA:
		case XTYP_ADVREQ:
		case XTYP_ADVSTOP:
		case XTYP_XACT_COMPLETE:
		case XTYP_CONNECT:
		{
			return (HDDEDATA)NULL;
		}
        case XTYP_DISCONNECT:
		{
			m_hConvClient=0;
			((CDDECliDlg *)(AfxGetApp()->m_pMainWnd))->m_btnConnect.SetWindowText("Connect");
			Printf("Disconnected by the server.\r\n");
			((CDDECliDlg *)(AfxGetApp()->m_pMainWnd))->m_btnCommand.EnableWindow(FALSE);
			return (HDDEDATA)NULL;
		}
		case XTYP_CONNECT_CONFIRM:
		{
			return (HDDEDATA)NULL; 
		}
        default:
		{
			return (HDDEDATA)NULL; 
		}
	}
}

void CDDECliDlg::InitializeDDE()
{
	UINT uDdeInit;
	CString szRlt;

	uDdeInit=::DdeInitialize
	(
		&m_dwInst,
		(PFNCALLBACK)DdeCallback,
		APPCMD_FILTERINITS, 
		0L
	);

	switch(uDdeInit)
	{
		case DMLERR_NO_ERROR:
		{
			m_hszServiceName=ObtainHsz(m_szService);
			szRlt="DDE initialized successfully!";
			break;
		}
		case DMLERR_DLL_USAGE:
		{
			szRlt="Fail to initialize DDE: Dll usage error!";
			break;
		}
		case DMLERR_INVALIDPARAMETER:
		{
			szRlt="Fail to initialize DDE: Invalid parameter!";
			break;
		}
		case DMLERR_SYS_ERROR:
		{
			szRlt="Fail to initialize DDE: System error!";
			break;
		}
	}
	
	Printf((LPCSTR)szRlt);
	Printf("\r\n");
}

HSZ CDDECliDlg::ObtainHsz(CString szStr)
{
	HSZ hsz=0;

	if(m_dwInst != 0)
	{
		hsz=::DdeCreateStringHandle(m_dwInst, szStr, NULL);
	}

	return hsz;
}

void CDDECliDlg::UnobtainHsz(HSZ hsz)
{
	if(m_dwInst != 0)
	{
		::DdeFreeStringHandle(m_dwInst, hsz);
	}
}

void CDDECliDlg::Printf(const char *fmt, ...)
{
	char buff[1024];

	va_list argp;
	va_start(argp, fmt);
	vsprintf(buff, fmt, argp);
	va_end(argp);
	((CDDECliDlg *)(AfxGetApp()->m_pMainWnd))->m_ecMsg.ReplaceSel(buff);
}

void CDDECliDlg::OnButtonConnect() 
{
	if(m_hConvClient == 0)
	{
		m_hConvClient=::DdeConnect
		(
			m_dwInst, m_hszServiceName, 0L, (PCONVCONTEXT)NULL
		);
		if(m_hConvClient == FALSE)
		{
			Printf("Unable to connect server!\r\n");
		}
		else 
		{
			m_btnCommand.EnableWindow();
			Printf("Connected to server!\r\n");
		}
		m_btnConnect.SetWindowText("Disconnect");
	}
	else
	{
		::DdeDisconnect(m_hConvClient);
		m_hConvClient=0;
		m_btnConnect.SetWindowText("Connect");
		Printf("Disconnected by the client!\r\n");
		m_btnCommand.EnableWindow(FALSE);
	}
}

void CDDECliDlg::OnClose() 
{
	if(m_hConvClient != 0)
	{
		::DdeDisconnect(m_hConvClient);
	}
	
	::DdeNameService(m_dwInst, NULL, NULL, DNS_UNREGISTER);
	UnobtainHsz(m_hszServiceName);
	::DdeUninitialize(m_dwInst);

	CDialog::OnClose();
}

BOOL CDDECliDlg::PreTranslateMessage(MSG *pMsg) 
{
	if
	(
		pMsg->hwnd == m_ecMsg.m_hWnd && 
		(
			pMsg->message == WM_LBUTTONDOWN ||
			pMsg->message == WM_RBUTTONDOWN ||
			pMsg->message == WM_MOUSEMOVE
		)
	)return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CDDECliDlg::OnButtonCommand() 
{
	CString szCommand;
	CString szFile;
	CFileDialog dlg(TRUE);
	int nSel;

	UpdateData();
	if(m_szCommand.IsEmpty())
	{
		AfxMessageBox("Please input a string first!");
	}
	else
	{
		nSel=m_cbType.GetCurSel();
		szCommand.Empty();
		if(nSel != CB_ERR)
		{
			if(nSel == 3)
			{
				if(dlg.DoModal() == IDOK)
				{
					szFile=dlg.GetPathName();
					szCommand.Format(m_szFormats[nSel], szFile, m_szCommand);
				}
				else return;
			}
			else
			{
				szCommand.Format(m_szFormats[nSel], m_szCommand);
				szCommand+='\0';
			}
			if
			(
				::DdeClientTransaction
				(
					(LPBYTE)(LPCSTR)szCommand,
					szCommand.GetLength(),
					m_hConvClient,
					0,
					0,
					XTYP_EXECUTE,
					5000,
					NULL
				)
			)
			{
				Printf("Command  %s  executed!\r\n", (LPCSTR)szCommand);
			}
			else Printf("Command  %s  failed!\r\n", (LPCSTR)szCommand);
		}
		else
		{
			AfxMessageBox("Make a selection!");
		}
	}
}
