// PizzaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Pizza.h"
#include "PizzaDlg.h"

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
// CPizzaDlg dialog

CPizzaDlg::CPizzaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPizzaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPizzaDlg)
	m_SurName = _T("");
	m_SecondName = _T("");
	m_Address = _T("");
	m_AddrNo = _T("");
	m_Phone = _T("");
	m_id = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPizzaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPizzaDlg)
	DDX_Text(pDX, IDC_EDIT2, m_SurName);
	DDX_Text(pDX, IDC_EDIT3, m_SecondName);
	DDX_Text(pDX, IDC_EDIT4, m_Address);
	DDX_Text(pDX, IDC_EDIT5, m_AddrNo);
	DDX_Text(pDX, IDC_EDIT6, m_Phone);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPizzaDlg, CDialog)
	//{{AFX_MSG_MAP(CPizzaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnAddNew)
	ON_BN_CLICKED(IDC_BUTTON4, OnDelete)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, OnFind)
	ON_BN_CLICKED(IDC_BUTTON3, OnChange)
	ON_BN_CLICKED(IDC_BUTTON5, OnClear)
	//}}AFX_MSG_MAP
	ON_LBN_DBLCLK(IDC_CLIENTLB, OnDblclkClientsLB)
	ON_LBN_SELCHANGE(IDC_CLIENTLB, OnSelchange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPizzaDlg message handlers

BOOL CPizzaDlg::OnInitDialog()
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

	RECT tmpRect;
	RECT tmpRect2;
	GetDlgItem( IDC_EDIT1 )->GetWindowRect( &tmpRect );
	ScreenToClient( &tmpRect );
	tmpRect2.left = tmpRect.left;
	tmpRect2.top = tmpRect.bottom + 2;
	GetDlgItem( IDC_EDIT6 )->GetWindowRect( &tmpRect );
	ScreenToClient( &tmpRect );
	tmpRect2.right = tmpRect.right + 20;
	GetDlgItem( IDC_BUTTON1 )->GetWindowRect( &tmpRect );
	ScreenToClient( &tmpRect );
	tmpRect2.bottom = tmpRect.top - 20;
	
	ClientsLB.Init( 20, tmpRect2, this, IDC_CLIENTLB );
	
	GetDlgItem( IDC_EDIT1 )->GetWindowRect( &tmpRect );
	short left = (short)tmpRect.left;
	ClientsLB.SetTabStop( 0, 2 );
	GetDlgItem( IDC_EDIT2 )->GetWindowRect( &tmpRect );
	ClientsLB.SetTabStop( 1, tmpRect.left - left );
	GetDlgItem( IDC_EDIT3 )->GetWindowRect( &tmpRect );
	ClientsLB.SetTabStop( 2, tmpRect.left - left );
	GetDlgItem( IDC_EDIT4 )->GetWindowRect( &tmpRect );
	ClientsLB.SetTabStop( 3, tmpRect.left - left );
	GetDlgItem( IDC_EDIT5 )->GetWindowRect( &tmpRect );
	ClientsLB.SetTabStop( 4, tmpRect.left - left );
	GetDlgItem( IDC_EDIT6 )->GetWindowRect( &tmpRect );
	ClientsLB.SetTabStop( 5, tmpRect.left - left );

	Clients.Open();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPizzaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPizzaDlg::OnPaint() 
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
HCURSOR CPizzaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPizzaDlg::PopulateLB()
{
	CString tmpString;

	ClientsLB.ResetContent();

	if( Clients.GetRecordCount() != 0 )
	{
		Clients.MoveFirst();
		
		if( !( Clients.IsBOF() || Clients.IsEOF() ) )
		{
			while( !Clients.IsEOF() )
			{
				tmpString.Format( "%ld", Clients.m_id );
				ClientsLB.AddString( tmpString + "#" +
									 Clients.m_SurName + "#" +
									 Clients.m_SecondName + "#" +
									 Clients.m_Address + "#" +
									 Clients.m_AddrNo + "#" +
									 Clients.m_Phone );
				Clients.MoveNext();
			}
		}
	}
}

void CPizzaDlg::OnAddNew() 
{
	// TODO: Add your control notification handler code her
	UpdateData( TRUE );
	
	Clients.AddNew();
		
	Clients.m_SurName = m_SurName; 
	Clients.m_SecondName = m_SecondName;
	Clients.m_Address = m_Address;
	Clients.m_AddrNo = m_AddrNo;
	Clients.m_Phone = m_Phone;

	Clients.Update();

	Clients.SetBookmark( Clients.GetLastModifiedBookmark() );

	ClientsLB.ResetContent();
	CString tmpString;
	tmpString.Format( "%ld", Clients.m_id );
	ClientsLB.AddString( tmpString + "#" +
						 Clients.m_SurName + "#" +
						 Clients.m_SecondName + "#" +
						 Clients.m_Address + "#" +
						 Clients.m_AddrNo + "#" +
						 Clients.m_Phone );
	ClientsLB.SetCurSel( 0 );
	OnSelchange();
}

void CPizzaDlg::OnOK()
{
	CWnd *FocusWin = GetFocus();
	if( ( FocusWin == GetDlgItem( IDC_EDIT1 ) ) ||
		( FocusWin == GetDlgItem( IDC_EDIT2 ) ) ||
		( FocusWin == GetDlgItem( IDC_EDIT3 ) ) ||
		( FocusWin == GetDlgItem( IDC_EDIT4 ) ) ||
		( FocusWin == GetDlgItem( IDC_EDIT5 ) ) ||
		( FocusWin == GetDlgItem( IDC_EDIT6 ) ) )
		OnFind();
	else if( FocusWin == GetDlgItem( IDC_CLIENTLB ) )
		DoDelivery();
}

void CPizzaDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	CString tmpString;
	
	tmpString = ClientsLB.GetCurrentID();
	if( tmpString != "NS" )
	{
		Clients.m_pDatabase->Execute(
			CString( "DELETE FROM Clients WHERE id = " ) + tmpString );
		ClientsLB.DeleteString( ClientsLB.GetCurSel() );
		m_SurName = _T("");
		m_SecondName = _T("");
		m_Address = _T("");
		m_AddrNo = _T("");
		m_Phone = _T("");
		m_id = _T("");
		UpdateData( FALSE );
	}
}

void CPizzaDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	Clients.Close();
	CDialog::OnClose();
}

void CPizzaDlg::OnFind() 
{
	// TODO: Add your control notification handler code here
	UpdateData( TRUE );
	if( m_id == "" )
	{
		Clients.m_strFilter = "SurName LIKE '" + m_SurName + "*' " +
			"AND SecondName LIKE '" + m_SecondName + "*' " +
			"AND Address LIKE '" + m_Address + "*' " +
			"AND AddrNo LIKE '" + m_AddrNo + "*' " +
			"AND Phone LIKE '" + m_Phone + "*'";
			
		Clients.Close();
		Clients.Open();
		PopulateLB();
		if( ClientsLB.GetCount() != 0 )
		{
			ClientsLB.SetCurSel( 0 );
			ClientsLB.SetFocus();
			OnSelchange();
		}
		else
			GetDlgItem( IDC_EDIT1 )->SetFocus();
	}
	else
	{
		Clients.m_strFilter = CString( "id = " ) + m_id;
		Clients.Close();
		Clients.Open();
		PopulateLB();
		if( ClientsLB.GetCount() != 0 )
		{
			ClientsLB.SetCurSel( 0 );
			ClientsLB.SetFocus();
			OnSelchange();
		}
		else
			GetDlgItem( IDC_EDIT1 )->SetFocus();
	}
}

void CPizzaDlg::OnChange() 
{
	// TODO: Add your control notification handler code here
	CString tmpString;
	CString tmpString2;
	
	UpdateData( TRUE );
	tmpString = ClientsLB.GetCurrentID();
	if( tmpString != "NS" )
	{
		tmpString2 = "UPDATE Clients SET SurName = '" + m_SurName +
			"', SecondName = '" + m_SecondName + "', Address = '" +
			m_Address + "', AddrNo = '" + m_AddrNo + "', Phone = '" + m_Phone +
			"' WHERE id = " + tmpString;

		Clients.m_pDatabase->Execute( tmpString2 );
		Clients.m_strFilter = "";
		Clients.Close();
		Clients.Open();
		PopulateLB();
	}	
}

void CPizzaDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	m_SurName = _T("");
	m_SecondName = _T("");
	m_Address = _T("");
	m_AddrNo = _T("");
	m_Phone = _T("");
	m_id = _T("");
	UpdateData( FALSE );
	ClientsLB.ResetContent();
}

void CPizzaDlg::OnSelchange() 
{
	// TODO: Add your control notification handler code here

	CString tmpString;
	ClientsLB.GetText( ClientsLB.GetCurSel(), tmpString );
	ClientsLB.ExtractString( CMD_RESET, tmpString );
	ClientsLB.ExtractString( CMD_NEXT, tmpString );
	m_id = tmpString;
	ClientsLB.ExtractString( CMD_NEXT, tmpString );
	m_SurName = tmpString;
	ClientsLB.ExtractString( CMD_NEXT, tmpString );
	m_SecondName = tmpString;
	ClientsLB.ExtractString( CMD_NEXT, tmpString );
	m_Address = tmpString;
	ClientsLB.ExtractString( CMD_NEXT, tmpString );
	m_AddrNo = tmpString;
	ClientsLB.ExtractString( CMD_NEXT, tmpString );
	m_Phone = tmpString;
	UpdateData( FALSE );
}

void CPizzaDlg::DoDelivery()
{
	MessageBox( "Do Something here" );
}

void CPizzaDlg::OnDblclkClientsLB() 
{
	// TODO: Add your control notification handler code here
	DoDelivery();
}
