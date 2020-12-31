// FileWatcherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "FileWatcher.h"
#include "FileWatcherDlg.h"
#include "EnterNewDir.h"
#include "OXMainRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_NOTIFICATION	100

/////////////////////////////////////////////////////////////////////////////


struct _PathInfo
{
	_PathInfo( CString sPath, BOOL bSubTree, DWORD dwFilter);

	CString m_sPath;
	BOOL	m_bSubTree;
	DWORD	m_dwFilter;
};

_PathInfo::_PathInfo( CString sPath, BOOL bSubTree, DWORD dwFilter)
:m_sPath( sPath),
m_bSubTree( bSubTree),
m_dwFilter( dwFilter)
{
}

/////////////////////////////////////////////////////////////////////////////
// CFileWatcherDlg dialog

CFileWatcherDlg::CFileWatcherDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFileWatcherDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileWatcherDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFileWatcherDlg::~CFileWatcherDlg()
{
	for( int i=0; i<m_arPaths.GetSize(); i++)
	{
		delete (_PathInfo*)m_arPaths[i];
	}
}

void CFileWatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileWatcherDlg)
	DDX_Control(pDX, IDC_WATCHED_DIRS, m_lbWatchedDirs);
	DDX_Control(pDX, IDC_NOTIFICATIONS, m_lbNotifications);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileWatcherDlg, CDialog)
	//{{AFX_MSG_MAP(CFileWatcherDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_DIR, OnAddDir)
	ON_BN_CLICKED(IDC_REMOVE_DIR, OnRemoveDir)
	ON_MESSAGE( WM_OX_FILE_NOTIFY, OnFileNotify )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileWatcherDlg message handlers

BOOL CFileWatcherDlg::OnInitDialog()
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rc;
	CString str;

	// Watched dirs
	m_lbWatchedDirs.GetClientRect( &rc);

	str.LoadString( IDS_DIRECTORY);
	m_lbWatchedDirs.InsertColumn( 0, str, LVCFMT_LEFT, int(0.2*rc.Width()));

	str.LoadString( IDS_WATCH_SUBDIRS);
	m_lbWatchedDirs.InsertColumn( 1, str, LVCFMT_LEFT, int(0.1*rc.Width()), 1);

	str.LoadString( IDS_FILTER);
	m_lbWatchedDirs.InsertColumn( 2, str, LVCFMT_LEFT, int(0.7*rc.Width()), 2);

	// Notifications
	m_lbNotifications.GetClientRect( &rc);

	str.LoadString( IDS_DIRECTORY);
	m_lbNotifications.InsertColumn( 0, str, LVCFMT_LEFT, int(0.2*rc.Width()));

	str.LoadString( IDS_TIME);
	m_lbNotifications.InsertColumn( 1, str, LVCFMT_LEFT, int(0.12*rc.Width()), 1);

	str.LoadString( IDS_EXTENDED_INFO);
	m_lbNotifications.InsertColumn( 2, str, LVCFMT_LEFT, int(0.07*rc.Width()), 2);

	str.LoadString( IDS_ACTION);
	m_lbNotifications.InsertColumn( 3, str, LVCFMT_LEFT, int(0.13*rc.Width()), 3);

	str.LoadString( IDS_FILE_NAME);
	m_lbNotifications.InsertColumn( 4, str, LVCFMT_LEFT, int(0.24*rc.Width()), 4);

	str.LoadString( IDS_NEW_FILE_NAME);
	m_lbNotifications.InsertColumn( 5, str, LVCFMT_LEFT, int(0.24*rc.Width()), 5);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileWatcherDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileWatcherDlg::OnPaint() 
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
HCURSOR CFileWatcherDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CFileWatcherDlg::OnAddDir() 
// --- In  : 
// --- Out : 
// --- Returns : 
// --- Effect : Responds to the 'Add dir...' button
{
	CEnterNewDir dlg;
	CString str;

	// Gets the watched directory and filter
	if(dlg.DoModal() == IDOK)
	{
		if(!dlg.m_sDir.IsEmpty())
		{
			DWORD filter=0;

			// Determines the watch filter
			if( dlg.m_bChangeAttributes)
			{
				filter |= COXFileWatcher::OXFileWatchChangeAttributes;
			}
			if( dlg.m_bChangeCreation)
			{
				filter |= COXFileWatcher::OXFileWatchChangeCreation;
			}
			if( dlg.m_bChangeDirName)
			{
				filter |= COXFileWatcher::OXFileWatchChangeDirName;
			}
			if( dlg.m_bChangeFileName)
			{
				filter |= COXFileWatcher::OXFileWatchChangeFileName;
			}
			if( dlg.m_bChangeLastAccess)
			{
				filter |= COXFileWatcher::OXFileWatchChangeLastAccess;
			}
			if( dlg.m_bChangeLastWrite)
			{
				filter |= COXFileWatcher::OXFileWatchChangeLastWrite;
			}
			if( dlg.m_bChangeSecurity)
			{
				filter |= COXFileWatcher::OXFileWatchChangeSecurity;
			}
			if( dlg.m_bChangeSize)
			{
				filter |= COXFileWatcher::OXFileWatchChangeSize;
			}

			if( fwWatcher.AddWatch( dlg.m_sDir, dlg.m_bSubTree, filter))
			{
				// If the directory is added set the window for notifications
				fwWatcher.EnableWindowNotification( dlg.m_sDir, this, TRUE);

				// Fills the listbox in the dialog

				// First check if the path isn't in the list
				_PathInfo* pi = NULL;
				int i=0;
				for(i=0; i<m_arPaths.GetSize(); i++)
				{
					pi=(_PathInfo*)m_arPaths[i];
					if( pi->m_sPath == dlg.m_sDir) break;
				}
				if( i > m_arPaths.GetUpperBound())
				{
					// Add new path
					LV_ITEM lvi; 

					// Initialize LV_ITEM members that are common to all items. 
					lvi.mask = LVIF_TEXT; 
					lvi.iItem = m_lbWatchedDirs.GetItemCount();
					lvi.iSubItem = 0;
					lvi.pszText = (LPTSTR)(LPCTSTR)dlg.m_sDir;   
					if(m_lbWatchedDirs.InsertItem( &lvi) != -1)
					{
						lvi.iSubItem = 1;

						str.LoadString((dlg.m_bSubTree)?IDS_YES:IDS_NO);
						lvi.pszText = (LPTSTR)(LPCTSTR)str;   

						if(m_lbWatchedDirs.SetItem( &lvi))
						{
							lvi.iSubItem = 2;
							lvi.pszText = (LPTSTR)(LPCTSTR)GetStringFromFilter( filter, str);   

							if(m_lbWatchedDirs.SetItem( &lvi))
							{
								_PathInfo* piNewPath= new _PathInfo( dlg.m_sDir, dlg.m_bSubTree, filter);
								if( piNewPath!=NULL)
								{
									m_arPaths.Add( piNewPath);
								}
							}
						}
					}
				}
				else
				{
					pi->m_bSubTree |= dlg.m_bSubTree;
					pi->m_dwFilter |= filter;

					LV_ITEM lvi; 
					lvi.mask = LVIF_TEXT; 
					lvi.iItem = i;

					str.LoadString((pi->m_bSubTree)?IDS_YES:IDS_NO);
					lvi.iSubItem = 1;
					lvi.pszText = (LPTSTR)(LPCTSTR)str;   
					m_lbWatchedDirs.SetItem( &lvi);

					lvi.iSubItem = 2;
					lvi.pszText = (LPTSTR)(LPCTSTR)GetStringFromFilter( pi->m_dwFilter, str);   
					m_lbWatchedDirs.SetItem( &lvi);
				}
			}
			else
			{
#ifdef _DEBUG
				str=COXFileWatcher::GetResultMessage( fwWatcher.GetLastError());
#else

				// Ghazi Code Change 
				str =  " Please confirm that you have checked at least one selection";//IDS_SOMETHING_WRONG);
#endif
				MessageBox( str);
			}
		}
		else
		{
			str.LoadString( IDS_NO_PATH);
			MessageBox( str, NULL, MB_ICONEXCLAMATION);
		}
	}
}

void CFileWatcherDlg::OnRemoveDir() 
// --- In  : 
// --- Out : 
// --- Returns : 
// --- Effect : Responds to the 'Remove dir' button
{
	// Is any thing selected?
	if( m_lbWatchedDirs.GetSelectedCount( )==0) 
	{
		CString str;
		str.LoadString( IDS_NO_DIR_IS_SELECTED);
		MessageBox( str);
		return;
	}

	int inx=m_lbWatchedDirs.GetNextItem( -1, LVNI_ALL|LVNI_SELECTED);
	if( inx != -1)
	{
		_PathInfo* pi=(_PathInfo*)m_arPaths[inx];
		fwWatcher.RemoveWatch( pi->m_sPath);
		m_lbWatchedDirs.DeleteItem( inx);
		m_arPaths.RemoveAt(inx);
		delete pi;
	}
	m_lbWatchedDirs.SetFocus();
}

LRESULT CFileWatcherDlg::OnFileNotify(WPARAM wP, LPARAM)
// --- In  : wP: the ID of the Notifier object
// --- Out : 
// --- Returns : ...
// --- Effect : Responds to the notification message from FileWatcher
{
	CString str;

	COXFileWatchNotifier fwnNotifier;
	fwnNotifier = fwWatcher.GetFileWatchNotifier( wP);

	// If the wP is an invalid ID then the notifier is empty
	if( !fwnNotifier.IsEmpty())
	{
		LV_ITEM lvi; 

		// Initialize LV_ITEM members that are common to all items. 
		lvi.mask = LVIF_TEXT; 
		lvi.iItem = m_lbNotifications.GetItemCount();
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)fwnNotifier.GetPath();   
		m_lbNotifications.InsertItem( &lvi);

		CString time=fwnNotifier.GetNotificationTime().Format(_T("%H:%M:%S"));
		lvi.iSubItem = 1;
		lvi.pszText = (LPTSTR)(LPCTSTR)time;   
		m_lbNotifications.SetItem( &lvi);

		lvi.iSubItem = 2;
		str.LoadString((fwnNotifier.IsExtendedInfoAvailable())?IDS_YES:IDS_NO);
		lvi.pszText = (LPTSTR)(LPCTSTR)str;   
		m_lbNotifications.SetItem( &lvi);

		if( fwnNotifier.IsExtendedInfoAvailable())
		{
			lvi.iSubItem = 3;
			lvi.pszText = (LPTSTR)(LPCTSTR)GetStringFromAction(fwnNotifier.GetAction(), str);   
			m_lbNotifications.SetItem( &lvi);

			lvi.iSubItem = 4;
			lvi.pszText = (LPTSTR)(LPCTSTR)fwnNotifier.GetFileName();
			m_lbNotifications.SetItem( &lvi);

			lvi.iSubItem = 5;
			lvi.pszText = (LPTSTR)(LPCTSTR)fwnNotifier.GetNewFileName();
			m_lbNotifications.SetItem( &lvi);
		}

		if( m_lbNotifications.GetItemCount()>MAX_NOTIFICATION)
		{
			m_lbNotifications.DeleteItem( 0);
		}
		m_lbNotifications.EnsureVisible( m_lbNotifications.GetItemCount()-1, FALSE);
	}
	return 0;
}


CString&	CFileWatcherDlg::GetStringFromFilter( DWORD dwFilter, CString& str)
// --- In  : dwFilter: value of the filter
// --- Out : str: text description of the value in the dwFilter
// --- Returns : A reference to the str
// --- Effect : Converts the given filter value to the textual representation
{
	CString tmp;
	CString sep;

	sep.LoadString( IDS_SEPARATOR);

	str.Empty();
	if( dwFilter & COXFileWatcher::OXFileWatchChangeFileName)
	{
		tmp.LoadString( IDS_CH_FILE_NAME);
		str = tmp;
	}
	if( dwFilter & COXFileWatcher::OXFileWatchChangeDirName)
	{
		tmp.LoadString( IDS_CH_DIR_NAME);
		if( str.GetLength()>0) str+=sep;
		str += tmp;
	}
	if( dwFilter & COXFileWatcher::OXFileWatchChangeAttributes)
	{
		tmp.LoadString( IDS_CH_ATTR);
		if( str.GetLength()>0) str+=sep;
		str += tmp;
	}
	if( dwFilter & COXFileWatcher::OXFileWatchChangeSize)
	{
		tmp.LoadString( IDS_CH_SIZE);
		if( str.GetLength()>0) str+=sep;
		str += tmp;
	}
	if( dwFilter & COXFileWatcher::OXFileWatchChangeLastWrite)
	{
		tmp.LoadString( IDS_CH_LAST_WRITE);
		if( str.GetLength()>0) str+=sep;
		str += tmp;
	}
	if( dwFilter & COXFileWatcher::OXFileWatchChangeLastAccess)
	{
		tmp.LoadString( IDS_CH_LAST_ACCESS);
		if( str.GetLength()>0) str+=sep;
		str += tmp;
	}
	if( dwFilter & COXFileWatcher::OXFileWatchChangeCreation)
	{
		tmp.LoadString( IDS_CH_CREATION);
		if( str.GetLength()>0) str+=sep;
		str += tmp;
	}
	if( dwFilter & COXFileWatcher::OXFileWatchChangeSecurity)
	{
		tmp.LoadString( IDS_CH_SECURITY);
		if( str.GetLength()>0) str+=sep;
		str += tmp;
	}
	return str;
}

CString&	CFileWatcherDlg::GetStringFromAction( DWORD dwAction, CString& str)
// --- In  : dwAction: value of the action
// --- Out : str: text description of the value in the dwAction
// --- Returns : A reference to the str
// --- Effect : Converts the given action value to the textual representation
{
	str.Empty();

	if( dwAction == COXFileWatchNotifier::OXFileWatchActionAdded)
	{
		str.LoadString( IDS_ADDED);
		return str;
	}
	if( dwAction == COXFileWatchNotifier::OXFileWatchActionRemoved)
	{
		str.LoadString( IDS_REMOVED);
		return str;
	}
	if( dwAction == COXFileWatchNotifier::OXFileWatchActionModified)
	{
		str.LoadString( IDS_MODIFIED);
		return str;
	}
	if( dwAction == COXFileWatchNotifier::OXFileWatchActionRename)
	{
		str.LoadString( IDS_RENAME);
		return str;
	}
	return str;
}
