// TestCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestCtrl.h"
#include "TestCtrlDlg.h"

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
// CTestCtrlDlg dialog

CTestCtrlDlg::CTestCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestCtrlDlg)
	m_Property = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDispatch = NULL;
	m_dwCookie = 0;
}

CTestCtrlDlg::~CTestCtrlDlg()
{
	if (m_pDispatch != NULL) {
		if (m_dwCookie != 0)
			Disconnection();
		m_pDispatch->Release();
	}
}

void CTestCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestCtrlDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Property);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CTestCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECTION, OnConnection)
	ON_BN_CLICKED(IDC_DISCONNECTION, OnDisconnection)
	ON_BN_CLICKED(IDC_SETPROPERTY, OnSetproperty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCtrlDlg message handlers

BOOL CTestCtrlDlg::OnInitDialog()
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
	
	GUID sourceobjCLSID;

	HRESULT hResult = ::CLSIDFromProgID(L"SourceComp.SourceObj", &sourceobjCLSID);
	if (FAILED(hResult)) 
	{
		return FALSE;
	}
	
	hResult = CoCreateInstance(sourceobjCLSID, NULL, 
		CLSCTX_INPROC_SERVER, IID_IDispatch, (void **)&m_pDispatch);
	if (FAILED(hResult)) 
	{
		return FALSE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestCtrlDlg::OnPaint() 
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
HCURSOR CTestCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// {B77C2985-56DD-11CF-B355-00104B08CC22}
static const IID IID_IEventSet =
{ 0xb77c2985, 0x56dd, 0x11cf, { 0xb3, 0x55, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 } };

int CTestCtrlDlg::Connection() 
{
	BOOL RetValue = 0;
	if (m_dwCookie != 0) {
		return 2;
	}
	LPCONNECTIONPOINTCONTAINER pConnPtCont;

	if ((m_pDispatch != NULL) &&
		SUCCEEDED(m_pDispatch->QueryInterface(IID_IConnectionPointContainer,
			(LPVOID*)&pConnPtCont)))
	{
		ASSERT(pConnPtCont != NULL);
		LPCONNECTIONPOINT pConnPt = NULL;
		DWORD dwCookie = 0;

		if (SUCCEEDED(pConnPtCont->FindConnectionPoint(IID_IEventSet, &pConnPt)))
		{
			ASSERT(pConnPt != NULL);
			pConnPt->Advise(&m_xEventSink, &dwCookie);
			m_dwCookie = dwCookie;
			RetValue = 1;
			pConnPt->Release();
		}

		pConnPtCont->Release();
		m_dwCookie = dwCookie;
	}
	return RetValue;
}

int CTestCtrlDlg::Disconnection() 
{
	BOOL RetValue = 0;
	if (m_dwCookie == 0) {
		return 2;
	}
	LPCONNECTIONPOINTCONTAINER pConnPtCont;

	if ((m_pDispatch != NULL) &&
		SUCCEEDED(m_pDispatch->QueryInterface(IID_IConnectionPointContainer,
			(LPVOID*)&pConnPtCont)))
	{
		ASSERT(pConnPtCont != NULL);
		LPCONNECTIONPOINT pConnPt = NULL;

		if (SUCCEEDED(pConnPtCont->FindConnectionPoint(IID_IEventSet, &pConnPt)))
		{
			ASSERT(pConnPt != NULL);
			pConnPt->Unadvise(m_dwCookie);
			pConnPt->Release();
			m_dwCookie = 0;
			RetValue = 1;
		}

		pConnPtCont->Release();
	}
	return RetValue;
}

void CTestCtrlDlg::OnConnection() 
{
	BOOL RetValue = Connection();
	if (RetValue == 0) {
		AfxMessageBox("Connecting Failed!");
	} else if (RetValue == 1) {
		AfxMessageBox("Connecting Successful!");
		GetDlgItem(IDC_STATIC1)->SetWindowText("连接：建立！");
	} else if (RetValue == 2) {
		AfxMessageBox("You have a Connection!");
	}
	return ;
}

void CTestCtrlDlg::OnDisconnection() 
{
	BOOL RetValue = Disconnection();
	if (RetValue == 0) {
		AfxMessageBox("Disconnecting Failed!");
	} else if (RetValue == 1) {
		AfxMessageBox("Disconnecting Successful!");
		GetDlgItem(IDC_STATIC1)->SetWindowText("连接：未建立！");
	} else if (RetValue == 2) {
		AfxMessageBox("You have not a Connection!");
	}
	return ;
}

void CTestCtrlDlg::OnSetproperty() 
{
	if (!UpdateData(TRUE))
	{
		TRACE0("UpdateData failed during dialog termination.\n");
		// the UpdateData routine will set focus to correct item
		return;
	}
	COleDispatchDriver driver;

	driver.AttachDispatch(m_pDispatch, FALSE);
	TRY
		driver.SetProperty(0x1, VT_I4, m_Property);
	END_TRY
	driver.DetachDispatch();
}
/////////////////////////////////////////////////////////////////////////////
// CTestCtrlDlg::XEventSink

STDMETHODIMP_(ULONG) CTestCtrlDlg::XEventSink::AddRef()
{
	return 1;
}

STDMETHODIMP_(ULONG) CTestCtrlDlg::XEventSink::Release()
{
	return 0;
}

STDMETHODIMP CTestCtrlDlg::XEventSink::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CTestCtrlDlg, EventSink)

	if (IsEqualIID(iid, IID_IUnknown) ||
		IsEqualIID(iid, IID_IDispatch) ||
		IsEqualIID(iid, IID_IEventSet))
	{
		*ppvObj = this;
		AddRef();
		return S_OK;
	}
	else
	{
		return E_NOINTERFACE;
	}
}

STDMETHODIMP CTestCtrlDlg::XEventSink::GetTypeInfoCount(
	unsigned int*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTestCtrlDlg::XEventSink::GetTypeInfo(
	unsigned int, LCID, ITypeInfo**)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTestCtrlDlg::XEventSink::GetIDsOfNames(
	REFIID, LPOLESTR*, unsigned int, LCID, DISPID*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTestCtrlDlg::XEventSink::Invoke(
	DISPID dispid, REFIID, LCID, unsigned short wFlags,
	DISPPARAMS* pDispParams, VARIANT* pvarResult,
	EXCEPINFO* pExcepInfo, unsigned int* puArgError)
{
	if (dispid == 0) {
		AfxMessageBox("The Property has been changed!");
	} else {
		AfxMessageBox("I don't known the event!");
	}
	return S_OK;
}

