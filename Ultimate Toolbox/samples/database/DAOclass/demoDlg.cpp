// demoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "demoDlg.h"

#include "UTSampleAbout.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
	m_sBalance = _T("");
	m_sCompany = _T("");
	m_sCustnum = _T("");
	m_sDate = _T("");
	m_sEmail = _T("");
	m_sFirstName = _T("");
	m_sLastName = _T("");
	m_sPhone = _T("");
	m_bOldCustomer = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_add	= FALSE;
	m_isDirty = FALSE;

}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_PHONE, m_ctlEditPhone);
	DDX_Control(pDX, IDC_LASTNAME, m_ctlEditLastName);
	DDX_Control(pDX, IDC_FIRSTNAME, m_ctlEditFirstName);
	DDX_Control(pDX, IDC_EMAIL, m_ctlEditEmail);
	DDX_Control(pDX, IDC_DATE, m_ctlEditDate);
	DDX_Control(pDX, IDC_CUSTNUM, m_ctlEditCustnum);
	DDX_Control(pDX, IDC_COMPANY, m_ctlEditCompany);
	DDX_Control(pDX, IDC_BALANCE, m_ctlEditBalance);
	DDX_Text(pDX, IDC_BALANCE, m_sBalance);
	DDX_Text(pDX, IDC_COMPANY, m_sCompany);
	DDX_Text(pDX, IDC_CUSTNUM, m_sCustnum);
	DDX_Text(pDX, IDC_DATE, m_sDate);
	DDX_Text(pDX, IDC_EMAIL, m_sEmail);
	DDX_Text(pDX, IDC_FIRSTNAME, m_sFirstName);
	DDX_Text(pDX, IDC_LASTNAME, m_sLastName);
	DDX_Text(pDX, IDC_PHONE, m_sPhone);
	DDX_Check(pDX, IDC_CHECK_OLDCUSTOMER, m_bOldCustomer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_FIRST, OnFirst)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_LAST, OnLast)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_CONTROL_RANGE(EN_CHANGE,IDC_LASTNAME,IDC_BALANCE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
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
	CString string = GetAppDir();
	string += "\\customer.mdb";
	
	if(m_dao.Open(string,_T("info")) != TRUE){
		MessageBox(_T("Database Failed To Open, make sure that the database is in the program directory"),
			_T("Error"),MB_OK);
		EndDialog(0);
	}
	else{
		LoadRecord();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
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

void CDemoDlg::OnPaint() 
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
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	ClearDialog();

	m_dao.Add();
	m_add = TRUE;
}

void CDemoDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	m_dao.Delete();
	LoadRecord();
}

void CDemoDlg::OnFirst() 
{
	// TODO: Add your control notification handler code here
	m_dao.MoveFirst();
	LoadRecord();
}

void CDemoDlg::OnPrev() 
{
	// TODO: Add your control notification handler code here
	if(m_dao.IsBOF() == TRUE)
		return;

	m_dao.MovePrev();	
	LoadRecord();
}

void CDemoDlg::OnNext() 
{
	// TODO: Add your control notification handler code here
	if(m_dao.IsEOF() == TRUE)
		return;

	m_dao.MoveNext();	
	LoadRecord();
}

void CDemoDlg::OnLast() 
{
	// TODO: Add your control notification handler code here
	m_dao.MoveLast();	
	LoadRecord();
}

void CDemoDlg::ClearDialog()
{
	m_sCustnum.Empty();
	m_sDate.Empty();
	m_sLastName.Empty();
	m_sFirstName.Empty();
	m_sCompany.Empty();
	m_sPhone.Empty();
	m_sEmail.Empty();
	m_sBalance.Empty();

	UpdateData(FALSE);
}

void CDemoDlg::SaveRecord()
{

	CString string;
	COleDateTime dt;
	COleCurrency cy;

	VERIFY(UpdateData());

	if(m_add)
		m_dao.Add();
	else
		m_dao.Edit();

	GetDlgItemText(IDC_LASTNAME,string);
	m_dao.SetField(m_dao.GFN(_T("LastName")),(LPCTSTR)string);

	GetDlgItemText(IDC_FIRSTNAME,string);
	m_dao.SetField(m_dao.GFN(_T("FirstName")),(LPCTSTR)string);

	GetDlgItemText(IDC_COMPANY,string);
	m_dao.SetField(m_dao.GFN(_T("Company")),(LPCTSTR)string);

	GetDlgItemText(IDC_PHONE,string);
	m_dao.SetField(m_dao.GFN(_T("Phone")),(LPCTSTR)string);

	GetDlgItemText(IDC_EMAIL,string);
	m_dao.SetField(m_dao.GFN(_T("EMail")),(LPCTSTR)string);

	GetDlgItemText(IDC_BALANCE,string);
	cy.ParseCurrency(string);
	m_dao.SetField(m_dao.GFN(_T("Balance")),cy);

	m_dao.SetField(m_dao.GFN(_T("Old customer")),m_bOldCustomer);

	//get the current date
	if(m_add){
		dt = COleDateTime::GetCurrentTime();
		m_dao.SetField(m_dao.GFN(_T("Date")),dt);
	}

	m_dao.Update();

	m_add		= FALSE;
	m_isDirty	= FALSE;
}

void CDemoDlg::LoadRecord()
{
	//check to see if editing or adding was in progress
	if(m_isDirty){
		if(MessageBox(_T("Do you want to save your changes?"),
			_T("Save Changes"),MB_YESNO) == IDYES)
			SaveRecord();
	}

	CString string;
	COleDateTime dt;
	COleCurrency cy;

	if(m_dao.IsEOF() || m_dao.IsBOF()){
		ClearDialog();
		return;
	}


	m_dao.GetField(m_dao.GFN(_T("CustNum")),m_sCustnum);

//	m_dao.GetField(m_dao.GFN(_T("Date")),dt);
//	m_sDate=dt.Format();
	if(!m_dao.GetField(m_dao.GFN(_T("Date")),dt)/* && dt.m_status==COleDateTime::null*/)
	{
		m_sDate=_T("");
	}
	else
		m_sDate=dt.Format();

	m_dao.GetField(m_dao.GFN(_T("LastName")),m_sLastName);

	m_dao.GetField(m_dao.GFN(_T("FirstName")),m_sFirstName);

	m_dao.GetField(m_dao.GFN(_T("Company")),m_sCompany);

	m_dao.GetField(m_dao.GFN(_T("Phone")),m_sPhone);

	m_dao.GetField(m_dao.GFN(_T("EMail")),m_sEmail);

	m_dao.GetField(m_dao.GFN(_T("Balance")),cy);
	m_sBalance=cy.Format();

	m_dao.GetField(m_dao.GFN(_T("Old customer")),m_bOldCustomer);

	UpdateData(FALSE);

	m_isDirty = FALSE;
}

CString CDemoDlg::GetAppDir(){


	LPTSTR	clStr = GetCommandLine();
	LPTSTR	buf;
	CString string;
	int 	loop;

	//create the temp buffer
	buf = new TCHAR[ lstrlen(clStr) + 1 ];

	//copy the command line and check to see if the first character is a quote
	if(clStr[0] == '\"')
		lstrcpy(buf,&clStr[1]);
	else
		lstrcpy(buf,clStr);


	//check to see if the command line is empty
	loop = 0;
	if(lstrlen(buf) > 0){

		loop = lstrlen(buf);
		while(loop > 0){
			if(buf[loop]== _T('.')){
				  break;
			}
			loop --;
		}
		while(loop > 0){
			if(buf[loop]== _T('\\')){
				buf[loop] = 0;
				  break;
			}
			loop --;
		}
	}

	if(loop == 0){
		
		delete[] buf;

		//create the temp buffer
		buf = new TCHAR[MAX_PATH + 1];
		 
		_tgetcwd(buf,255);
	}

	string = buf;

	delete[] buf;

	return string;
}


void CDemoDlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	SaveRecord();
}

void CDemoDlg::OnChange(UINT nParam) 
{
	UNREFERENCED_PARAMETER(nParam);
	// TODO: Add your control notification handler code here
	m_isDirty = TRUE;
}
