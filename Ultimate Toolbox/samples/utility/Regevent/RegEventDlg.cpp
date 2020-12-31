// RegEventDlg.cpp : implementation file
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#include "stdafx.h"
#include "utsampleabout.h"
#include "RegEvent.h"
#include "RegEventDlg.h"
#include "OXRegistryWatcher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRegEventDlg dialog

CRegEventDlg::CRegEventDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegEventDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegEventDlg)
	m_HkeyStr = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegEventDlg)
	DDX_Control(pDX, IDOK, m_AddBttn);
	DDX_Control(pDX, IDC_CLRBTTN, m_ClrBttn);
	DDX_Control(pDX, IDC_REMBTTN, m_RemBttn);
	DDX_Control(pDX, IDC_REMALLBTTN, m_RemAllBttn);
	DDX_Control(pDX, IDC_CHANGELIST, m_ChangeList);
	DDX_Control(pDX, IDC_KEYLIST, m_KeyList);
	DDX_Text(pDX, IDC_HKEY, m_HkeyStr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegEventDlg, CDialog)
	//{{AFX_MSG_MAP(CRegEventDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_KEYLIST, OnClickKeylist)
	ON_NOTIFY(NM_KILLFOCUS, IDC_KEYLIST, OnKillfocusKeylist)
	ON_BN_CLICKED(IDC_REMBTTN, OnRembttn)
	ON_BN_CLICKED(IDC_REMALLBTTN, OnRemallbttn)
	ON_BN_CLICKED(IDC_CLRBTTN, OnClrbttn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegEventDlg message handlers

BOOL CRegEventDlg::OnInitDialog()
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

	// Set columns od lists.
	CRect rect;
	m_KeyList.GetWindowRect(rect);
	m_KeyList.InsertColumn(0, _T("Watched Keys List"), LVCFMT_LEFT, rect.Width()-20);
	m_ChangeList.GetWindowRect(rect);
	m_ChangeList.InsertColumn(0, _T("Registry Changes List"), LVCFMT_LEFT, rect.Width()-20);

	// Initial settings for Radio & Check Buttons: HKEY_CURRENT_USER key is default,
	// "Name" and "Value" buttons have a check mark.
	CheckRadioButton(IDC_HKEY_CURRENT_USER_RADIO, IDC_HKEY_LOCAL_MACHINE_RADIO, IDC_HKEY_CURRENT_USER_RADIO);
	CheckDlgButton(IDC_NAMECHANGE, 1);
	CheckDlgButton(IDC_VALCHANGE, 1);

	// Check whether Registry key watching is supported.
	if ( !m_RegWatch.IsWatchingSupported() )
		{
		m_AddBttn.EnableWindow(FALSE);
		AfxMessageBox(_T("Registry key watching isn't supported on your system.\nPlease run this program on Windows NT 4.0."), MB_OK|MB_ICONSTOP);
		}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRegEventDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRegEventDlg::OnPaint() 
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
HCURSOR CRegEventDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CRegEventDlg::PreTranslateMessage(MSG* pMsg)
{
	// Translate message from COXRegistryWatcher class when Registry key is changed.
	if ( pMsg->message == WM_OX_REGISTRY_NOTIFY )
		{
		::Beep(2000, 200);
		TCHAR szBuffer[_MAX_PATH];
		VERIFY(!::RegEnumKey((HKEY) pMsg->lParam,0,(LPTSTR) &szBuffer,
			_MAX_PATH));
		CString	sKey((LPCTSTR) &szBuffer);
		CString sMess;
		DWORD	dwKey = (DWORD)pMsg->wParam;
		if ( m_MesMap.Lookup(dwKey, sMess) )
			{
			m_ChangeList.InsertItem(m_ChangeList.GetItemCount(), sKey);
			m_ClrBttn.EnableWindow();
			}
		}

	return CDialog::PreTranslateMessage(pMsg);
}

void CRegEventDlg::OnOK()
// Called when the user clicks the "Add Watch" button (this button has ID = IDOK).
// Adds Registry Key watch to "watch queue".
// Standard CDialog::OnOK() implementation doesn't perform.
{
	UpdateData(TRUE);
	CString		sAdded = "";
	HKEY		hKey = NULL, hKeyAdd = NULL;
	BOOL		bWatchSubtree = FALSE;
	DWORD		dwWatchFilter = 0;

	// Define:	description string for added watch;
	//			whether HKEY_CURRENT_USER or HKEY_LOCAL_MACHINE key is used;
	//			whether key subtrees are watched;
	//			which changes should be reported.
	switch ( GetCheckedRadioButton(IDC_HKEY_CURRENT_USER_RADIO, IDC_HKEY_LOCAL_MACHINE_RADIO) )
		{
		case IDC_HKEY_CURRENT_USER_RADIO:
			hKey = HKEY_CURRENT_USER;
			sAdded = "HKEY_CURRENT_USER\\" + m_HkeyStr;
			break;
		case IDC_HKEY_LOCAL_MACHINE_RADIO:
			hKey = HKEY_LOCAL_MACHINE;
			sAdded = "HKEY_LOCAL_MACHINE\\" + m_HkeyStr;
			break;
		}
	sAdded += "; ";
	if ( IsDlgButtonChecked(IDC_SUBTREE) )
		{
		bWatchSubtree = TRUE;
		sAdded += " +";
		}
	else
		{
		bWatchSubtree = FALSE;
		sAdded += " -";
		}
	if ( IsDlgButtonChecked(IDC_NAMECHANGE) )
		{
		dwWatchFilter |= COXRegistryWatcher::OXRegistryWatchChangeName;
		sAdded += "N";
		}
	else
		sAdded += ".";
	if ( IsDlgButtonChecked(IDC_VALCHANGE) )
		{
		dwWatchFilter |= COXRegistryWatcher::OXRegistryWatchChangeLastSet;
		sAdded += "V";
		}
	else
		sAdded += ".";
	if ( IsDlgButtonChecked(IDC_ATTRCHANGE) )
		{
		dwWatchFilter |= COXRegistryWatcher::OXRegistryWatchChangeAttributes;
		sAdded += "A";
		}
	else
		sAdded += ".";
	if ( IsDlgButtonChecked(IDC_SECCHANGE) )
		{
		dwWatchFilter |= COXRegistryWatcher::OXRegistryWatchChangeSecurity;
		sAdded += "S";
		}
	else
		sAdded += ".";

	// Attempt to add watch.
	LV_FINDINFO FindInfo = {LVFI_STRING, sAdded};
	if ( m_KeyList.FindItem(&FindInfo, -1) < 0 )
		{
		if ( hKey )
			{
			if ( ::RegOpenKeyEx(hKey, (LPCTSTR)m_HkeyStr, 0, KEY_NOTIFY | KEY_ENUMERATE_SUB_KEYS, &hKeyAdd) == 
				ERROR_SUCCESS && hKeyAdd )
				{
				DWORD dwID = m_RegWatch.AddWatch(hKeyAdd, bWatchSubtree, dwWatchFilter);
				if ( dwID > 0 )
					{
					if ( m_RegWatch.EnableWindowNotification(dwID, this) )
						{
						m_MesMap[dwID] = sAdded;
						CString sMessAdd = ".";
						if ( m_KeyList.InsertItem(m_KeyList.GetItemCount(), 
							(LPCTSTR)sAdded) >= 0 )
							m_RemAllBttn.EnableWindow();
						else
							sMessAdd = ",\nbut record wasn't added to Watched Keys List.";
						AfxMessageBox(_T("Registry Key watch was successfully set"+
							sMessAdd), MB_OK|MB_ICONINFORMATION);
						}
					else
						AfxMessageBox(_T("Failure to set window to receive notification."), 
							MB_OK|MB_ICONSTOP);
					}
				else
					AfxMessageBox(_T("Failure to add Registry Key watch."), 
						MB_OK|MB_ICONSTOP);
				//::RegCloseKey(hKeyAdd);
				}
			else
				AfxMessageBox(_T("Failure to open Registry Key."), MB_OK|MB_ICONSTOP);
			}
		else
			AfxMessageBox(_T("Registry Key is not defined."), MB_OK|MB_ICONSTOP);
		}
	else
		AfxMessageBox(_T("This Registry Key is already watched."), MB_OK|MB_ICONSTOP);

	//CDialog::OnOK();
}

void CRegEventDlg::OnClickKeylist(NMHDR*  /* pNMHDR */, LRESULT* pResult)
// Called when the user clicks the list of watched keys. "Remove Watch" button becomes enabled.
{
	m_RemBttn.EnableWindow();
	*pResult = 0;
}

void CRegEventDlg::OnKillfocusKeylist(NMHDR* /* pNMHDR */, LRESULT* pResult)
// Called when the user kills focus from the list of watched keys.
// "Remove Watch" button becomes disabled if focus doesn't move to it.
{
	if ( !m_RemBttn.m_bClick || !m_KeyList.GetItemCount() )
		m_RemBttn.EnableWindow(FALSE);
	m_RemBttn.m_bClick = FALSE;
	*pResult = 0;
}

void CRegEventDlg::OnRembttn()
// Called when the user clicks the "Remove Watch" button.
// Removes Registry Key watch from "watch queue".
{
	AfxGetApp()->DoWaitCursor(1);
	int nItemInd = m_KeyList.GetNextItem(-1, LVNI_SELECTED);

	if ( nItemInd >= 0 )
		{
		CString		sItem = m_KeyList.GetItemText(nItemInd, 0), sRet = "";
		DWORD		dwKey = 0;
		POSITION	map_pos = m_MesMap.GetStartPosition();
		while ( map_pos )
			{
			m_MesMap.GetNextAssoc(map_pos, dwKey, sRet);
			if ( sRet == sItem )
				{
				if ( m_RegWatch.RemoveWatch(dwKey) )
					{
					m_MesMap.RemoveKey(dwKey);
					m_KeyList.DeleteItem(nItemInd);
					}
				break;
				}
			}
		}

	m_RemBttn.EnableWindow(FALSE);
	if ( !m_KeyList.GetItemCount() )
		m_RemAllBttn.EnableWindow(FALSE);
	AfxGetApp()->DoWaitCursor(-1);
}

void CRegEventDlg::OnRemallbttn()
// Called when the user clicks the "Remove All" button.
// Removes all Registry Key watches from "watch queue".
{
	AfxGetApp()->DoWaitCursor(1);
	if ( m_RegWatch.RemoveAllWatches() )
		{
		m_MesMap.RemoveAll();
		m_KeyList.DeleteAllItems();
		m_RemBttn.EnableWindow(FALSE);
		m_RemAllBttn.EnableWindow(FALSE);
		}
	AfxGetApp()->DoWaitCursor(-1);
}

void CRegEventDlg::OnClrbttn() 
// Called when the user clicks the "Clear List" button.
// Empties the "Registry Changes List".
{
	m_ChangeList.DeleteAllItems();
	m_ClrBttn.EnableWindow(FALSE);
}
