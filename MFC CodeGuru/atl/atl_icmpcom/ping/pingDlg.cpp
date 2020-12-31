// pingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\\icmpcom_i.c"
#include <afxctl.h>
#include <comdef.h>
#include "ping.h"
#include "pingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
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

/////////////////////////////////////////////////////////////////////////////
// CPingDlg dialog

CPingDlg::CPingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPingDlg)
	m_hostname = _T("127.0.0.1");
	m_interrupt = FALSE;
	m_nofrag = FALSE;
	m_numpackets = 10;
	m_numstamps = 0;
	m_packetlen = 64;
	m_resolve = FALSE;
	m_rrnum = 0;
	m_timeout = 5;
	m_tos = 0;
	m_tracert = FALSE;
	m_ttl = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ICMPComEvents = new ICMPComEvents(this);
	m_ICMPCom = NULL;
	m_dwCookie = 0;

}

CPingDlg::~CPingDlg()	
{
	
	if (m_dwCookie)
	{
		BOOL adv = AfxConnectionUnadvise(m_ICMPCom,
									DIID_DICMPComEvent,
									m_ICMPComEvents->GetInterface(&IID_IUnknown),
									TRUE,
									m_dwCookie);
	}

	if (m_ICMPCom)
	{
		m_ICMPCom->Release();
	}

	delete m_ICMPComEvents;
	CoUninitialize();

}

void CPingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPingDlg)
	DDX_Control(pDX, IDC_PINGOUTLB, m_pingoutlb);
	DDX_Text(pDX, IDC_HOSTNAME, m_hostname);
	DDX_Check(pDX, IDC_INTERRUPT, m_interrupt);
	DDX_Check(pDX, IDC_NOFRAG, m_nofrag);
	DDX_Text(pDX, IDC_NUMPACKETS, m_numpackets);
	DDX_Text(pDX, IDC_NUMSTAMPS, m_numstamps);
	DDX_Text(pDX, IDC_PACKETLEN, m_packetlen);
	DDX_Check(pDX, IDC_RESOLVE, m_resolve);
	DDX_Text(pDX, IDC_RRNUM, m_rrnum);
	DDX_Text(pDX, IDC_TIMEOUT, m_timeout);
	DDX_Text(pDX, IDC_TOS, m_tos);
	DDX_Check(pDX, IDC_TRACERT, m_tracert);
	DDX_Text(pDX, IDC_TTL, m_ttl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPingDlg, CDialog)
	//{{AFX_MSG_MAP(CPingDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTICMP, OnStarticmp)
	ON_BN_CLICKED(IDC_STOPICMP, OnStopicmp)
	ON_BN_CLICKED(IDC_STOPPING, OnStopping)
	ON_BN_CLICKED(IDC_RUNPING, OnRunping)
	ON_BN_CLICKED(IDC_SETVARS, OnSetvars)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPingDlg message handlers

BOOL CPingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	CoInitialize(FALSE);
//	m_ICMPCom.CreateDispatch(IID_ICMPCom);

	if (m_ICMPCom == NULL)
	{
		HRESULT hr = CoCreateInstance(CLSID_CICMPCom,NULL,
										CLSCTX_INPROC_SERVER,
										IID_ICMPCom,
										(void**)&m_ICMPCom);
		if (SUCCEEDED(hr))
		{
			BOOL adv = AfxConnectionAdvise(m_ICMPCom,
									DIID_DICMPComEvent,
									m_ICMPComEvents->GetInterface(&IID_IUnknown),
									TRUE,
									&m_dwCookie);
		}
	}

	
									
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPingDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPingDlg::OnStarticmp() 
{
	// TODO: Add your control notification handler code here
	m_ICMPCom->StartICMP();
	
}

void CPingDlg::OnStopicmp() 
{
	// TODO: Add your control notification handler code here
	
	m_ICMPCom->StopICMP();
	
}

void CPingDlg::OnStopping() 
{
	// TODO: Add your control notification handler code here
	m_ICMPCom->StopPing();
	
}

void CPingDlg::OnRunping() 
{
	// TODO: Add your control notification handler code here
	m_ICMPCom->RunPing();
	
}

void CPingDlg::OnSetvars() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);  // get current info from dlg

	_bstr_t bstring(m_hostname);

	m_ICMPCom->SetPingVariables(bstring,
					 m_tracert,
					 m_resolve,
					 m_nofrag,
					 m_interrupt,
					 m_ttl,
					 m_packetlen,
					 m_numpackets,
					 m_rrnum,
					 m_numstamps,
					 m_tos,
					 m_timeout);

	
}


