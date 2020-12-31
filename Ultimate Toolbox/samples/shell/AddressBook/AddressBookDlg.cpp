// AddressBookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddressBook.h"
#include "AddressBookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddressBookDlg dialog

CAddressBookDlg::CAddressBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddressBookDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddressBookDlg)
	m_sLDAP = _T("ldap://ldap.itd.umich.edu/o=University%20of%20Michigan,c=US");
	m_nSearchBy = 0;
	m_sEmail = _T("");
	m_sName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAddressBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddressBookDlg)
	DDX_Control(pDX, IDC_LIST_RESULTS, m_lstResults);
	DDX_Text(pDX, IDC_EDIT_LDAP, m_sLDAP);
	DDX_CBIndex(pDX, IDC_COMBO_SEARCHBY, m_nSearchBy);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_sEmail);
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAddressBookDlg, CDialog)
	//{{AFX_MSG_MAP(CAddressBookDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, OnButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_FINDDIALOG, OnButtonFinddialog)
	ON_BN_CLICKED(IDC_BUTTON_LDAP, OnButtonLdap)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_ADDRESS, OnButtonAddress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddressBookDlg message handlers

BOOL CAddressBookDlg::OnInitDialog()
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
	
	if (!m_ABook.Init())
	{
		TRACE0("Unable to initialize the address book.\r\n Quit.");
		PostMessage(WM_QUIT);
	}
	else
		m_ABook.SetParent(this->m_hWnd);

	CRect rect;
	m_lstResults.GetClientRect(&rect);
	m_lstResults.InsertColumn(0,_T("Property"),LVCFMT_LEFT,100);
	m_lstResults.InsertColumn(1,_T("Value"),LVCFMT_LEFT,100);
	m_lstResults.InsertColumn(2,_T("To "),LVCFMT_LEFT,rect.Width()-200);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAddressBookDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAddressBookDlg::OnPaint() 
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
HCURSOR CAddressBookDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAddressBookDlg::OnButtonFind() 
{
	UpdateData();
	PopulateList(NULL);

	COXMailUser* pUser=GetUser();
	if (!pUser)
		return;
	
	PopulateList(pUser);
	AfxMessageBox(_T("The user has been found."));

	if (pUser)
		delete pUser;
}

void CAddressBookDlg::PopulateList(COXMailUser *pUser, BOOL bList)
{

	m_lstResults.DeleteAllItems();
	if (!pUser)
		return;

	CRect rect;
	m_lstResults.GetClientRect(&rect);

	if (!bList)
	{
		FillUserProperties(pUser);
	}
	else
	{
		ADRLIST* pList=(ADRLIST*) pUser;
		ASSERT(pList);

		for (UINT n=0;n<pList->cEntries;n++)
		{

			ULONG ulType=NULL;
			
			// find PR_RECIPIENT_TYPE property
			UINT k=0;
			for (k=0;k<pList->aEntries[n].cValues;k++)
			{

				if (pList->aEntries[n].rgPropVals[k].ulPropTag==PR_RECIPIENT_TYPE)
				{
					ulType=pList->aEntries[n].rgPropVals[k].Value.l;
				}

			}	

			for (k=0;k<pList->aEntries[n].cValues;k++)
			{

				if (pList->aEntries[n].rgPropVals[k].ulPropTag==PR_ENTRYID)
				{
					COXMailUser* pUser=m_ABook.GetUserFromID(
						pList->aEntries[n].rgPropVals[k].Value.bin.cb,
						(ENTRYID*) pList->aEntries[n].rgPropVals[k].Value.bin.lpb);
					if (pUser)
					{
						UINT nStart=m_lstResults.GetItemCount();
						FillUserProperties(pUser);
						CString sType;
						if (ulType == MAPI_TO)
							sType=_T("To ");
						if (ulType == MAPI_CC)
							sType=_T("Cc ");
						if (ulType == MAPI_BCC)
							sType=_T("Bcc ");
						m_lstResults.SetItemText(nStart,2,(LPCTSTR) sType);
						delete pUser;

					}

				}
			}
		}
	}
}


void CAddressBookDlg::OnButtonCreate() 
{
	
	PopulateList(NULL);

	COXMailUser* pUser=m_ABook.CreateUser();
	
	if (pUser)
		AfxMessageBox(_T("The user has been created successfully."));
	else
	{
		AfxMessageBox(_T("The user has not been created."));
		return;
	}

	PopulateList(pUser);
	delete pUser;
}

void CAddressBookDlg::OnButtonEdit() 
{

	UpdateData();
	PopulateList(NULL);

	COXMailUser* pUser=GetUser();
	if (!pUser)
		return;

	BOOL bRet=m_ABook.EditUser(pUser);

	if (bRet)
		AfxMessageBox(_T("The properties of the user has been edited successfully."));
	else
		AfxMessageBox(_T("The properties of the user has not been edited successfully."));

	if (pUser)
		delete pUser;
}

void CAddressBookDlg::OnButtonFinddialog() 
{
	PopulateList(NULL);
	m_ABook.ShowFindDialog();
}

void CAddressBookDlg::OnButtonLdap() 
{
	UpdateData(TRUE);
	PopulateList(NULL);
	
	LPTSTR lpszLDAP =m_sLDAP.GetBuffer(m_sLDAP.GetLength());
	COXMailUser* pUser=m_ABook.SearchLDAP(lpszLDAP,WABOBJECT_LDAPURL_RETURN_MAILUSER);
	
	m_sLDAP.ReleaseBuffer();

	if (pUser)
	{
		PopulateList(pUser);
		delete pUser;
	}

	

}

void CAddressBookDlg::OnButtonDelete() 
{
	UpdateData();
	PopulateList(NULL);

	COXMailUser* pUser=GetUser();
	if (!pUser)
		return;

	BOOL	bRet=m_ABook.DeleteUser(pUser);

	if (bRet && !m_ABook.GetLastError())
		AfxMessageBox(_T("The user has been successfully deleted."));
	else
		AfxMessageBox(_T("Error to delete the user."));
	if (pUser)
 		delete pUser;
}

void CAddressBookDlg::OnButtonAddress() 
{

	PopulateList(NULL);

	if (m_dlgOpt.DoModal()==IDOK)
	{
		ADRLIST* pList=m_ABook.SelectUser(&m_dlgOpt.m_options);
		if (pList)
		{
			PopulateList((COXMailUser*) pList, TRUE);
		}
		else
			TRACE1("COXAddressBook::returned %d\r\n",m_ABook.GetLastError());
	}
}

COXMailUser* CAddressBookDlg::GetUser()
{
	COXMailUser* pUser=NULL;

	switch (m_nSearchBy)
	{
	case E_EMAIL:
		pUser=m_ABook.FindUserByEMail(m_sEmail, TRUE, NULL, MAPI_MODIFY);	
		break;
	case E_NAME:
		pUser=m_ABook.FindUserByName(m_sName, TRUE, NULL, MAPI_MODIFY);	
		break;
	default:
		ASSERT(FALSE);
	}
	if (!pUser)
	{
		AfxMessageBox(_T("Error to find the user."));
		return NULL;
	}
	else
		return pUser;

}

BOOL CAddressBookDlg::FillUserProperties(COXMailUser *pUser)
{
	ULONG nNumber=NULL;

	COXPropValue* pProps=pUser->GetProperties(NULL,&nNumber);
	if (!pProps)
	{
		return FALSE;
	}

	for (UINT n=0;n<nNumber;n++)
	{

		CString sText=COXPropValue::GetPropertyNameFromTag((pProps+n)->ulPropTag);
		if (sText.IsEmpty())
			continue;
		m_lstResults.InsertItem(m_lstResults.GetItemCount(),(LPCTSTR) sText);
		sText =(pProps+n)->GetStringProperty();
		if (!sText.IsEmpty())
			m_lstResults.SetItemText(m_lstResults.GetItemCount()-1,
				1,(LPCTSTR) sText);
	}
	delete [] pProps;

	return TRUE;
}
