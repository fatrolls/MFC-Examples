// AgTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AgTest.h"
#include "AgTestDlg.h"
#include "AgTestDll.h"

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
// CAgTestDlg dialog

CAgTestDlg::CAgTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAgTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAgTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAgTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAgTestDlg)
	DDX_Control(pDX, IDC_BUTTON2, StopT);
	DDX_Control(pDX, IDC_BUTTON1, StartT);
	DDX_Control(pDX, IDC_EDIT1, Edit);
	DDX_Control(pDX, IDC_CHECK2, Check2);
	DDX_Control(pDX, IDC_CHECK1, Check1);
	DDX_Control(pDX, IDC_RADIO1, Radio1);
	DDX_Control(pDX, IDC_RADIO2, Radio2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAgTestDlg, CDialog)
	//{{AFX_MSG_MAP(CAgTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillFocusEdit1)
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetFocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnStartThread)
	ON_BN_CLICKED(IDC_BUTTON2, OnStopThread)
	ON_BN_CLICKED(IDC_BUTTON3, OnThreadAction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAgTestDlg message handlers

BOOL CAgTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAgTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAgTestDlg::OnPaint() 
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

HCURSOR CAgTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAgTestDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
  AGENT(MT_CHECKBOX,"User clicked on checkbox 1",0);	
}

void CAgTestDlg::OnCheck2() 
{
	// TODO: Add your control notification handler code here
  AGENT(MT_CHECKBOX,"User clicked on checkbox 2",0);		
}

void CAgTestDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
  AGENT(MT_RADIO,"User clicked on radio button 1",0);	
}

void CAgTestDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
  AGENT(MT_RADIO,"User clicked on radio button 2",0);	
}

void CAgTestDlg::OnKillFocusEdit1() 
{
	// TODO: Add your control notification handler code here
  CString str,edstr;
  Edit.GetWindowText(edstr);
  str.Format("Editbox lost focus [%s]", edstr);
  AGENT(MT_EDIT,str,0);
  TestFunction();
}

void CAgTestDlg::OnSetFocusEdit1() 
{
	// TODO: Add your control notification handler code here
  CString str,edstr;
  Edit.GetWindowText(edstr);
  str.Format("Editbox received focus [%s]", edstr);
  AGENT(MT_EDIT,str,0);		
}

void CAgTestDlg::OnStartThread() 
{
	// TODO: Add your control notification handler code here
  AGENT(MT_THREAD,"Background worker thread started",0);
  Thread.Create();
  StartT.EnableWindow(FALSE);
  StopT.EnableWindow(TRUE);
}

void CAgTestDlg::OnStopThread() 
{
	// TODO: Add your control notification handler code here
  Thread.Destroy();
  StartT.EnableWindow(TRUE);
  StopT.EnableWindow(FALSE);
  AGENT(MT_THREAD,"Background worker thread stopped",0);
}

void CAgTestDlg::OnThreadAction() 
{
	// TODO: Add your control notification handler code here
  AGENT(MT_THREAD,"Triggered a background thread action",0);
}

///////////////////////////////////////////////////////////////////////////////
// class TTestThread
//

TTestThread::TTestThread()
{
  Thread = NULL;
}

TTestThread::~TTestThread()
{
  DWORD exitCode;
  if (Thread != NULL && 
      ::GetExitCodeThread(Thread->m_hThread, &exitCode) &&
      exitCode == STILL_ACTIVE)
  {
    Destroy();
  }
}

// Thread handler
UINT TTestThread::ThreadFunc(LPVOID arg)
{
  TTestThread *thread = (TTestThread*)arg;
  thread->Execute();    // Virtual so derived function will be called
  return 0;
}

void TTestThread::Create(void)
{
  if (!Thread) {
    // Auto reset, initially reset
    EKillThread = ::CreateEvent(NULL,FALSE,FALSE,NULL);
    EThreadIsDead = ::CreateEvent(NULL,FALSE,FALSE,NULL);
    // Create the thread. Set the private flag to indicate success
    Thread = ::AfxBeginThread(ThreadFunc,this,THREAD_PRIORITY_NORMAL);
  }
}

void TTestThread::Destroy(void)
{
  if (Thread) {
    ::SetEvent(EKillThread);
    ::WaitForSingleObject(EThreadIsDead,INFINITE);
    ::Sleep(100);
    Thread = NULL;
  }
}

//
// Main Interface thread function.
//
void TTestThread::Execute(void)
{
  DWORD retcode;
  while (TRUE) {
    retcode = ::WaitForSingleObject(EKillThread,5000);
    AGENT(MT_THREAD,"TTestThread::WaitForSingleObject",retcode);
    if (retcode == WAIT_OBJECT_0)
      break;
    // Do something
    ::Beep(5000,20);
    AGENT(MT_THREAD,"Do something in a thread",0);
  }
  ::SetEvent(EThreadIsDead);
}

#ifdef _DEBUG
void TTestThread::AssertValid() const
{
	CObject::AssertValid();
}

void TTestThread::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
  dc << "TTestThread\n";
}
#endif //_DEBUG

