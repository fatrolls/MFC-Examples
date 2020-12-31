// IPAddressCheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPAddressCheck.h"
#include "IPAddressCheckDlg.h"
#include <winsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPAddressCheckDlg dialog
// DDX routine fo IP address translation
void WINAPI DDX_IPAddress(CDataExchange* pDX, int nIDC, UINT & value)
{
	// from dialog to class ?
	if( pDX->m_bSaveAndValidate)
	{
		CString Val;
		BOOL bValid = true;

		pDX->m_pDlgWnd->GetDlgItem(nIDC)->GetWindowText(Val);

		for( int i = 0; i < Val.GetLength(); i++)
		{
			// let's check if all entered char in entered
			// IP address are digits
			if(Val[i] == '.')
				continue;

			if(isdigit(Val[i]) == 0)
			{
				bValid = false;
				break;			
			}
		}

		if(bValid)
		{
			value = inet_addr(Val);
			if(value == INADDR_NONE)
			{
				pDX->m_pDlgWnd->MessageBox("The entered IP address is invalid.");
				pDX->PrepareEditCtrl(nIDC);
				pDX->Fail();
			}
		}
		else
		{
			pDX->m_pDlgWnd->MessageBox("IP address can only have digits and dots.");
			pDX->PrepareEditCtrl(nIDC);
			pDX->Fail();
		}
	}
	else
	{
		// if the value is a valid IP address store it in the child control
		in_addr IPaddress;
		memcpy(&IPaddress, &value, 4);
		CString Address = inet_ntoa(IPaddress);
		if(!Address.IsEmpty())
		{
			pDX->m_pDlgWnd->GetDlgItem(nIDC)->SetWindowText(Address);
		}
	}	
}

CIPAddressCheckDlg::CIPAddressCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPAddressCheckDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPAddressCheckDlg)
	m_IPAddress = 2711065280;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPAddressCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPAddressCheckDlg)
	DDX_IPAddress(pDX, IDC_IPADDRESS, m_IPAddress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIPAddressCheckDlg, CDialog)
	//{{AFX_MSG_MAP(CIPAddressCheckDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPAddressCheckDlg message handlers

BOOL CIPAddressCheckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIPAddressCheckDlg::OnPaint() 
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
HCURSOR CIPAddressCheckDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIPAddressCheckDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
