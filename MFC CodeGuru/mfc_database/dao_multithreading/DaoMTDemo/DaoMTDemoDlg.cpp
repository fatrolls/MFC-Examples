// DaoMTDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DaoMTDemo.h"
#include "DaoMTDemoDlg.h"
#include "Shared.h"
#include "TestSet.h"
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HWND		g_hWndMain = NULL;
LONG		g_nAddedRecordCount = 0;
LONG		g_nAddThreadCount = 0;
BOOL		g_bUseTransactionsWhenAdding = TRUE;
HANDLE		g_hDBMutex;
HANDLE		g_hAbortDeleteSignal;
BOOL		g_bDeleteThreadRunning = FALSE;

extern UINT AddingThreadFunction(LPVOID lpvData);
extern UINT DeletingThreadFunction(LPVOID lpvData);


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
// CDaoMTDemoDlg dialog

CDaoMTDemoDlg::CDaoMTDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDaoMTDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDaoMTDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bAllowRemovingListItems = TRUE;
	g_hDBMutex = CreateMutex(NULL, FALSE, NULL);
	g_hAbortDeleteSignal = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void CDaoMTDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDaoMTDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDaoMTDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDaoMTDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_START, OnAddStart)
	ON_BN_CLICKED(IDC_ADD_STOP, OnAddStop)
	ON_BN_CLICKED(IDC_ADD_STOP2, OnAddStop2)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ADD_USE_TRANSACTIONS, OnAddUseTransactions)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ADD_CLEAR, OnAddClear)
	ON_BN_CLICKED(IDC_ABORT_DELETION, OnAbortDeletion)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_REPAIR_DB, OnRepairDb)
	ON_BN_CLICKED(IDC_COMPACT_DB, OnCompactDb)
	//}}AFX_MSG_MAP
	ON_MESSAGE(MYWM_UPDATE, OnUpdateStatus)
	ON_MESSAGE(MYWM_TERMINATING, OnThreadTerminating)
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)

	ON_UPDATE_COMMAND_UI(IDOK, OnUpdateOK)
	ON_UPDATE_COMMAND_UI(IDC_ABORT_DELETION, OnUpdateAbortDelete)
	ON_UPDATE_COMMAND_UI(IDC_CLEAR, OnUpdateDelete)
	ON_UPDATE_COMMAND_UI(IDC_ADD_START, OnUpdateStart)
	ON_UPDATE_COMMAND_UI(IDC_ADD_STOP, OnUpdateStop)
	ON_UPDATE_COMMAND_UI(IDC_ADD_STOP2, OnUpdateStop)
	
	ON_UPDATE_COMMAND_UI(IDC_REPAIR_DB, OnUpdateRepairAndCompact)
	ON_UPDATE_COMMAND_UI(IDC_COMPACT_DB, OnUpdateRepairAndCompact)
	

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDaoMTDemoDlg message handlers

BOOL CDaoMTDemoDlg::OnInitDialog()
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


	g_hWndMain = GetSafeHwnd();

	SetTimer(1, 50, NULL);
	GetDlgItem(IDC_HEADER)->SetFont( CFont::FromHandle((HFONT)GetStockObject(SYSTEM_FONT) ));
	

	//
	// HACK HACK HACK
	// Modify jet registry setting in order to make this app work whitout using
	// transactions.
	//
	HKEY hKey;
	if(RegOpenKeyEx(
		HKEY_LOCAL_MACHINE, 
		_T("SOFTWARE\\Microsoft\\Jet\\3.5\\Engines\\Jet 3.5"),
		0,
		KEY_SET_VALUE,
		&hKey) != ERROR_SUCCESS)
	{
		AfxMessageBox("Error opening Jet3.5 registry key "
			"'HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Jet\\3.5\\Engines\\Jet 3.5'",
			MB_ICONWARNING|MB_OK);
	}
	else
	{
		if(RegSetValueEx(hKey, "ImplicitCommitSync", 0, REG_SZ, (LPBYTE)"yes", 4) != ERROR_SUCCESS)
		{
			AfxMessageBox("Error setting Jet3.5 registry value for 'ImplicitCommitSync' !!!",
				MB_ICONWARNING|MB_OK);
		}

		RegCloseKey(hKey);
	}

	//
	// Store default jet engine in thread local storage 
	//
	AfxDaoInit();
	_DAODBEngine* pEngine = AfxGetDaoState()->m_pDAODBEngine;
	TlsSetValue(dwDBEngineSlot, pEngine);




	// Force update of UI items
	UpdateDialogControls(this, FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDaoMTDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDaoMTDemoDlg::OnPaint() 
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
HCURSOR CDaoMTDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


const nPriList[] = {
	THREAD_PRIORITY_IDLE,
	THREAD_PRIORITY_LOWEST,
	THREAD_PRIORITY_BELOW_NORMAL,
	THREAD_PRIORITY_NORMAL,
	THREAD_PRIORITY_ABOVE_NORMAL,
	THREAD_PRIORITY_HIGHEST,
	THREAD_PRIORITY_TIME_CRITICAL,
};




extern LONG g_nAddThreads;

LRESULT CDaoMTDemoDlg::OnUpdateStatus(WPARAM, LPARAM)
{
	SetDlgItemInt(IDC_ADD_COUNT, g_nAddedRecordCount, FALSE);
	SetDlgItemInt(IDC_ADD_THREADS, g_nAddThreadCount, FALSE);

	GetDlgItem(IDC_ADD_THREADS)->UpdateWindow();
	GetDlgItem(IDC_ADD_COUNT)->UpdateWindow();

	return 0;
}

LRESULT CDaoMTDemoDlg::OnThreadTerminating(WPARAM wParam, LPARAM)
{
	if(!m_bAllowRemovingListItems)
		return 0;

	THREAD_DATA* pThreadData;

	POSITION pos, prev_pos;
	for(pos = m_ThreadList.GetHeadPosition();pos!=NULL;)
	{
		prev_pos = pos;
		pThreadData = m_ThreadList.GetNext(pos);
		ASSERT_VALID(pThreadData);


		if(pThreadData->nThreadId == wParam)
		{
			switch(pThreadData->byType)
			{
			case ADD_THREAD:
				g_nAddThreadCount -= 1;
				break;
			}

			CloseHandle(pThreadData->hThread);
			CloseHandle(pThreadData->hTerminateSignal);
			m_ThreadList.RemoveAt(prev_pos);
			delete pThreadData;

			OnUpdateStatus(0,0);
			break;
		}
	}

	return 0;
}

void CDaoMTDemoDlg::OnAddStart() 
{
	CWinThread* pThread;
	HANDLE hTerminateSignal = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	// FOR NOW: USE FIXED PRIORITY !!!
	pThread = AfxBeginThread(&AddingThreadFunction, hTerminateSignal, 
		THREAD_PRIORITY_BELOW_NORMAL, 0, CREATE_SUSPENDED);
	if(pThread)
	{
		HANDLE hThread;
		DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, GetCurrentProcess(),
			&hThread, 0, TRUE, DUPLICATE_SAME_ACCESS);

		THREAD_DATA* pThreadData = new THREAD_DATA;
		pThreadData->byType = ADD_THREAD;
		pThreadData->hThread = hThread;
		pThreadData->hTerminateSignal = hTerminateSignal;
		pThreadData->nThreadId = pThread->m_nThreadID;
		
		m_ThreadList.AddTail(pThreadData);
		g_nAddThreadCount += 1;

		pThread->ResumeThread();
	}
	else
	{
		AfxMessageBox(_T("Error strarting new adding thread!"));
		CloseHandle(hTerminateSignal);
	}
}

void CDaoMTDemoDlg::OnAddStop() 
{
	THREAD_DATA* pThreadData;

	if(m_ThreadList.IsEmpty())
		return;

	POSITION pos = m_ThreadList.GetHeadPosition();
	while(pos!=NULL)
	{
		pThreadData = m_ThreadList.GetNext(pos);
		ASSERT_VALID(pThreadData);
		if(pThreadData->byType == ADD_THREAD)
		{
			//
			// Signal the thread to terminate and wait for it 
			// to exit.
			//
			CWaitCursor theWait;
			SetEvent(pThreadData->hTerminateSignal);
			WaitForSingleObject(pThreadData->hThread, 10000);

			// Note: The thread will post a terminating message
			// which will remove it from the list
			break;
		}
	}
}

void CDaoMTDemoDlg::OnAddStop2() 
{
	THREAD_DATA* pThreadData;

	if(m_ThreadList.IsEmpty())
		return;

	CWaitCursor theWait;
	POSITION pos = m_ThreadList.GetHeadPosition();
	while(pos!=NULL)
	{
		pThreadData = m_ThreadList.GetNext(pos);
		if(pThreadData->byType == ADD_THREAD)
		{
			//
			// Signal the thread to terminate.
			//
			SetEvent(pThreadData->hTerminateSignal);
			WaitAndPumpMessages(pThreadData->hThread, 5000);

			// Note: The thread will post a terminating message
			// which will remove it from the list
		}
	}
}

void CDaoMTDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	CloseHandle(g_hDBMutex);
	CloseHandle(g_hAbortDeleteSignal);

}

void CDaoMTDemoDlg::OnAddUseTransactions() 
{
	g_bUseTransactionsWhenAdding = 
		((CButton*)GetDlgItem(IDC_ADD_USE_TRANSACTIONS))->GetCheck();
}

void CDaoMTDemoDlg::OnClear() 
{
	CWinThread* pThread;
	HANDLE hTerminateSignal = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	ResetEvent(g_hAbortDeleteSignal);
	pThread = AfxBeginThread(&DeletingThreadFunction, hTerminateSignal, 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	if(pThread)
	{
		HANDLE hThread;
		DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, GetCurrentProcess(),
			&hThread, 0, TRUE, DUPLICATE_SAME_ACCESS);

		THREAD_DATA* pThreadData = new THREAD_DATA;
		pThreadData->byType = DELETING_THREAD;
		pThreadData->hThread = hThread;
		pThreadData->hTerminateSignal = hTerminateSignal;
		pThreadData->nThreadId = pThread->m_nThreadID;
	
		m_ThreadList.AddTail(pThreadData);
		pThread->ResumeThread();
	}
	else
	{
		AfxMessageBox(_T("Error strarting new deleting thread!"));
		CloseHandle(hTerminateSignal);
	}
}

void CDaoMTDemoDlg::OnClose() 
{
	if(m_ThreadList.GetCount())
	{
		MessageBeep(-1);
		return;
	}
	
	DestroyWindow();
}

void CDaoMTDemoDlg::OnCancel() 
{
	OnClose();
}

void CDaoMTDemoDlg::OnOK() 
{
	OnClose();
}

void CDaoMTDemoDlg::OnTimer(UINT nIDEvent) 
{
	if(g_nAddThreadCount)
		OnUpdateStatus(0,0);


	static int nUpdateDelay = -1;
	struct _stati64 stat;

	nUpdateDelay = (nUpdateDelay+1)%20;

	if(!nUpdateDelay)
	{
		if(_stati64( _T("test.mdb"), &stat )==0)
		{
			CString s;
			s.Format("%d kb", (int)(stat.st_size/1024));
			SetDlgItemText(IDC_DB_SIZE, s);
			GetDlgItem(IDC_DB_SIZE)->UpdateWindow();
		}
		else
			SetDlgItemText(IDC_DB_SIZE, _T("Error!"));
	}


}

void CDaoMTDemoDlg::OnAddClear() 
{
	g_nAddedRecordCount = 0;	
	OnUpdateStatus(0,0);
}

void CDaoMTDemoDlg::OnAbortDeletion() 
{
	SetEvent(g_hAbortDeleteSignal);
		
}

void CDaoMTDemoDlg::OnRepairDb() 
{
	CWaitCursor theWait;

	AfxGetDaoState()->m_pDAODBEngine = (DAODBEngine *)TlsGetValue(dwDBEngineSlot);
	ASSERT(AfxGetDaoState()->m_pDAODBEngine!=NULL);

	try
	{
		CDaoWorkspace::RepairDatabase(_T("test.mdb"));
	}
	catch(CDaoException* pe)
	{
		pe->ReportError();
		pe->Delete();
	}
	catch(CMemoryException*)
	{
		AfxMessageBox("Out of memory");
	}
}

void CDaoMTDemoDlg::OnCompactDb() 
{
	CWaitCursor theWait;

	AfxGetDaoState()->m_pDAODBEngine = (DAODBEngine *)TlsGetValue(dwDBEngineSlot);
	ASSERT(AfxGetDaoState()->m_pDAODBEngine!=NULL);

	try
	{
		CString strTempPath;
		CString strTempFile;

		GetTempPath(MAX_PATH, strTempPath.GetBuffer(MAX_PATH));
		strTempPath.ReleaseBuffer();

		GetTempFileName(strTempPath, _T("MT"), GetTickCount(), strTempFile.GetBuffer(MAX_PATH));
		strTempFile.ReleaseBuffer();

		CDaoWorkspace::CompactDatabase(_T("test.mdb"), strTempFile);

		DeleteFile(_T("test.mdb"));
		MoveFile(strTempFile, _T("test.mdb"));
	}
	catch(CDaoException* pe)
	{
		pe->ReportError();
		pe->Delete();
	}
	catch(CMemoryException*)
	{
		AfxMessageBox("Out of memory");
	}
}

LRESULT CDaoMTDemoDlg::OnKickIdle(WPARAM, LPARAM)
{
	UpdateDialogControls(this, FALSE);
	return 0;
}

void CDaoMTDemoDlg::OnUpdateOK(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( !m_ThreadList.GetCount() );
}

void CDaoMTDemoDlg::OnUpdateAbortDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( g_bDeleteThreadRunning );
}

void CDaoMTDemoDlg::OnUpdateDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( !g_bDeleteThreadRunning && m_ThreadList.GetCount() < 64);
}

void CDaoMTDemoDlg::OnUpdateStart(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( m_ThreadList.GetCount() < 64 );
}

void CDaoMTDemoDlg::OnUpdateStop(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( g_nAddThreadCount );
}

void CDaoMTDemoDlg::OnUpdateRepairAndCompact(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( !m_ThreadList.GetCount() );
}
