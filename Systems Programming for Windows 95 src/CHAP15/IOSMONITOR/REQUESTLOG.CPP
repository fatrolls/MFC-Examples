// RequestLog.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "reqmon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD __stdcall DoMonitor(CRequestLog* log);
__declspec(thread) CRequestLog* logptr;
void WINAPI callback(PMONINFO mip);

/////////////////////////////////////////////////////////////////////////////
// CRequestLog dialog


CRequestLog::CRequestLog(HANDLE hreqmon)
{
	//{{AFX_DATA_INIT(CRequestLog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_reqmon = hreqmon;	// remember VxD handle
	m_paused = TRUE;	// not logging requests yet
	InitializeCriticalSection(&m_cs);
	m_evkill = CreateEvent(NULL, FALSE, FALSE, NULL); // create auto-reset event
	m_nlog = 100;				// default
	m_all = TRUE;				// ditto
	m_thread = NULL;
}


void CRequestLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRequestLog)
	DDX_Control(pDX, IDC_REQLOG, m_ctlList);
	DDX_Control(pDX, IDB_PAUSE, m_ctlPause);
	DDX_Control(pDX, IDB_RESUME, m_ctlResume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRequestLog, CDialog)
	//{{AFX_MSG_MAP(CRequestLog)
	ON_BN_CLICKED(IDB_CLOSE, OnClose)
	ON_BN_CLICKED(IDB_PAUSE, OnPause)
	ON_BN_CLICKED(IDB_RESUME, OnResume)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER+256, OnRequest)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRequestLog message handlers

BOOL CRequestLog::OnInitDialog() 
	{							// CRequestLog::OnInitDialog
	CDialog::OnInitDialog();

	// Determine width of the font

	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	int cx = tm.tmAveCharWidth;

	// Layout the columns of the list view

	m_ctlList.InsertColumn(COL_DEVICE, "Device", LVCFMT_LEFT, 20 * cx, COL_DEVICE);
	m_ctlList.InsertColumn(COL_FUNC, "Operation", LVCFMT_LEFT, 20 * cx, COL_FUNC);
	m_ctlList.InsertColumn(COL_SECTOR, "Sector", LVCFMT_LEFT, 10 * cx, COL_SECTOR);
	m_ctlList.InsertColumn(COL_NBYTES, "Count", LVCFMT_LEFT, 10 * cx, COL_NBYTES);
	m_ctlList.InsertColumn(COL_STATUS, "Status", LVCFMT_LEFT, 10000, COL_STATUS);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}							// CRequestLog::OnInitDialog

void CRequestLog::OnClose() 
	{							// CRequestLog::OnClose
	GetParent()->SendMessage(WM_COMMAND, ID_REQUESTS_MONITOR, (LPARAM) m_hWnd);
	}							// CRequestLog::OnClose

void CRequestLog::OnPause() 
	{							// CRequestLog::OnClose
	// We can get a second OnPause if user uses menu choice to
	// close log window while it's paused
	
	if (m_thread)
		{						// monitor thread is running
		SetEvent(m_evkill);
		WaitForSingleObject(m_thread, 1000);
		}						// monitor thread is running
	m_paused = TRUE;			// flag that we're paused
	m_ctlPause.EnableWindow(FALSE);
	m_ctlResume.EnableWindow(TRUE);
	}							// CRequestLog::OnClose

void CRequestLog::OnResume() 
	{							// CRequestLog::OnResume
	m_paused = FALSE;
	m_ctlPause.EnableWindow(TRUE);
	m_ctlResume.EnableWindow(FALSE);
	ResetEvent(m_evkill);	// just be sure it's reset
	DWORD junk;				// to receive thread id
	ASSERT(!m_thread);
	if (m_thread)
		TerminateThread(m_thread, 2);
	m_thread = ::CreateThread(NULL, 4096, (DWORD (__stdcall *)(void *)) DoMonitor, this, 0, &junk);
	}							// CRequestLog::OnResume

LRESULT CRequestLog::OnRequest(WPARAM wParam, LPARAM lParam)
	{						// CRequestLog::OnRequest
	static char *reqname[] = {"READ", "WRITE", "VERIFY", "CANCEL",
		"WRITEV", "MEDIA_CHECK", "MEDIA_CHECK_RESET", "LOAD_MEDIA",
		"EJECT_MEDIA", "LOCK_MEDIA", "UNLOCK_MEDIA", "REQUEST_SENSE",
		"COMPUTE_GEOM", "GEN_IOCTL", "FORMAT", "SCSI_PASS_THROUGH",
		"CLEAR_QUEUE", "DOS_RESET", "SCSI_REQUEST",

		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL,

		"SET_WRITE_STATUS", "RESTART_QUEUE", "ABORT_QUEUE", "SPIN_DOWN", "SPIN_UP",
		"FLUSH_DRIVE", "FLUSH_DRIVE_AND_DISCARD", "FSD_EXT"};

	static char *reqstatus[] = {"SUCCESS", "SUCCESS_WITH_RETRY", "SUCCESS_WITH_ECC",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		
		"INVALID_PARM", "CANCELED", "CMD_IN_PROGRESS", "INVALID_CMD_PTR", "MEDIA_ERROR",
		"DEVICE_ERROR", "INVALID_COMMAND", "NO_DEVICE", "NO_MEDIA", "UNCERTAIN_MEDIA",
		"UNREC_ERROR", "HW_FAILURE", "UNFORMATTED_MEDIA", "MEMORY_ERROR", "TIME_OUT",
		"WRITE_PROTECT",

		"NOT_READY", "BUSY", "VOL_NOT_LOCKED", "VOL_LOCKED", "VOL_NOT_REMOVABLE",
		"VOL_IN_USE", "LOCK_COUNT_EXCEEDED", "VALID_EJECT_FAILED", "ILLEGAL_ACCESS_MODE",
		"LOCK_VIOLATION", "WRONG_MEDIA", "OUT_OF_SPACE", "BIG_IO_BREAKUP_FAILED"};

	if (m_ctlList.GetItemCount() >= m_nlog)
		m_ctlList.DeleteItem(0);	// make room for new item
	
	PMONINFO mip = (PMONINFO) lParam;

	int row = m_ctlList.InsertItem(m_ctlList.GetItemCount(), DriveName(mip->dcb));
	m_ctlList.EnsureVisible(row, FALSE); // partially visible not okay

	CString opcode;
	if (mip->opcode < arraysize(reqname) && reqname[mip->opcode])
		opcode = reqname[mip->opcode];
	else
		opcode = csprintf("<unknown fcn %X>", mip->opcode);
	m_ctlList.SetItemText(row, COL_FUNC, opcode);

	m_ctlList.SetItemText(row, COL_SECTOR, csprintf("%8.8X", mip->sector));
	m_ctlList.SetItemText(row, COL_NBYTES, csprintf("%d", mip->nbytes));

	CString status;
	if (mip->status < arraysize(reqstatus) && reqstatus[mip->status])
		status = reqstatus[mip->status];
	else
		status = csprintf("<unknown status %X>", mip->status);
	m_ctlList.SetItemText(row, COL_STATUS, status);
	
	DeviceIoControl(m_reqmon, REQMON_RETURNBLOCK, &lParam, sizeof(lParam),
		NULL, 0, NULL, NULL);
	return 0;
	}						// CRequestLog::OnRequest

DWORD __stdcall DoMonitor(CRequestLog* log)
	{						// DoMonitor
	void (WINAPI *acallback)(PMONINFO) = callback;
	if (!DeviceIoControl(log->m_reqmon, REQMON_SETMONITORADDRESS,
		&acallback, sizeof(acallback), NULL, 0, NULL, NULL))
		{					// can't establish callback
		PostMessage(log->m_hWnd, WM_COMMAND, IDB_PAUSE, 0);
		return 1;
		}					// can't establish callback
	logptr = log;
	while (WaitForSingleObjectEx(log->m_evkill, INFINITE, TRUE) == WAIT_IO_COMPLETION)
		;					// until told to quit
	acallback = NULL;
	DeviceIoControl(log->m_reqmon, REQMON_SETMONITORADDRESS,
		&acallback, sizeof(acallback), NULL, 0, NULL, NULL);
	log->m_thread = NULL;	// we're out of here
	return 0;
	}						// DoMonitor

void WINAPI callback(PMONINFO mip)
	{						// callback
	if (!logptr->m_all)
		{					// monitoring only selected devices
		EnterCriticalSection(&logptr->m_cs);
		int n = logptr->m_devlist.GetSize();
		for (int i = 0; i < n; ++i)
			if (mip->dcb == logptr->m_devlist[i])
				break;
		LeaveCriticalSection(&logptr->m_cs);
		if (i >= n)
			{				// ignore this event
			DeviceIoControl(logptr->m_reqmon, REQMON_RETURNBLOCK, &mip, sizeof(mip),
				NULL, 0, NULL, NULL);
			return;
			}				// ignore this event
		}					// monitoring only selecte devices

	PostMessage(logptr->m_hWnd, WM_USER+256, 0, (LPARAM) mip);
	}						// callback
