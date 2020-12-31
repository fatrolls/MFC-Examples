#include "stdafx.h"
#include "DaoMTDemo.h"
#include "TestSet.h"
#include "Shared.h"

extern HWND		g_hWndMain;
extern HANDLE	g_hDBMutex;
extern HANDLE	g_hAbortDeleteSignal;
extern BOOL		g_bDeleteThreadRunning;

UINT DeletingThreadFunction(LPVOID lpvData)
{
	g_bDeleteThreadRunning = TRUE;

	LONG nTotalRecordCount = 0;
	DWORD dwWait;
	HANDLE hTerminateSignal = (HANDLE)lpvData;

	ASSERT(hTerminateSignal != NULL);
	ASSERT(IsWindow(g_hWndMain));

	CDaoDatabase* pDB = InitializeDAO();
	if(!pDB)
	{
		::PostMessage(g_hWndMain, MYWM_TERMINATING, GetCurrentThreadId(), 0);
		g_bDeleteThreadRunning = FALSE;
		return -1;
	}
	
	//
	// Open table recordset.
	// Calc number of records to be deleted.
	// 

	WaitAndPumpMessages(g_hDBMutex, INFINITE);

	AfxGetDaoState()->m_pDAODBEngine = (DAODBEngine *)TlsGetValue(dwDBEngineSlot);
	ASSERT(AfxGetDaoState()->m_pDAODBEngine!=NULL);

	// Force DAO engine to reload data from disk
	pDB->m_pWorkspace->Idle( dbRefreshCache );

	CTestSet set(pDB);
	try
	{
		set.Open(dbOpenDynaset);	// Open dynaset. Otherwize we dont get the corrent
									// number of records in the database 
		if(!set.IsEOF() && !set.IsBOF())
		{
			set.MoveLast();
			nTotalRecordCount = set.GetRecordCount();
			set.MoveFirst();
		}
	}
	catch(CException* pException)
	{
		set.Close();

		pException->ReportError();
		pException->Delete();

		TerminateDAO(pDB);
		::PostMessage(g_hWndMain, MYWM_TERMINATING, GetCurrentThreadId(), 0);
		g_bDeleteThreadRunning = FALSE;
		return -2;
	}

	if(!nTotalRecordCount)
	{
		set.Close();
		
		TerminateDAO(pDB);
		
		::PostMessage(g_hWndMain, MYWM_TERMINATING, GetCurrentThreadId(), 0);
		g_bDeleteThreadRunning = FALSE;

		AfxMessageBox(_T("No records to be deleted !!!"));
		return -3;
	}


	ReleaseMutex(g_hDBMutex);

	int nPos = 0;
	int nRangeFactor = 1;
	int nRange = nTotalRecordCount;
	while(nRange > SHRT_MAX)
	{
		nRange /= 2;
		nRangeFactor *= 2;
	}


	CProgressCtrl wndProgress;
	wndProgress.Attach(::GetDlgItem(g_hWndMain, IDC_DELETE_PROGRESS));
	wndProgress.SetPos(0);
	wndProgress.SetRange(0, nRange);
	wndProgress.ShowWindow(SW_SHOW);

	::SetDlgItemInt(g_hWndMain, IDC_DELETE_COUNT, nTotalRecordCount, FALSE);

	HANDLE hWaits[] = { hTerminateSignal, g_hAbortDeleteSignal };


	while(nTotalRecordCount--)
	{
		dwWait = MsgWaitForMultipleObjects(2, hWaits, FALSE, 0, QS_ALLINPUT);

		MSG msg;
		while(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(dwWait == WAIT_OBJECT_0+1)
			break;

		if(dwWait == WAIT_TIMEOUT)
		{
			WaitAndPumpMessages(g_hDBMutex, INFINITE);


			AfxGetDaoState()->m_pDAODBEngine = (DAODBEngine *)TlsGetValue(dwDBEngineSlot);
			ASSERT(AfxGetDaoState()->m_pDAODBEngine!=NULL);

			try
			{
				set.Delete();
				set.MoveNext();
				nPos += 1;
			}
			catch(CException* pe)
			{
				pe->ReportError();
				pe->Delete();
				break;
			}

			ReleaseMutex(g_hDBMutex);

			wndProgress.SetPos(nPos / nRangeFactor);
			wndProgress.UpdateWindow();
		}
		else if(dwWait == WAIT_OBJECT_0)
		{
			// Terminate signal set.
			// Bread out of loop
			break;
		}
	}

	wndProgress.ShowWindow(SW_HIDE);
	wndProgress.Detach();
	SetWindowText(::GetDlgItem(g_hWndMain, IDC_DELETE_COUNT), _T(""));

	WaitAndPumpMessages(g_hDBMutex, INFINITE);
	AfxGetDaoState()->m_pDAODBEngine = (DAODBEngine *)TlsGetValue(dwDBEngineSlot);
	ASSERT(AfxGetDaoState()->m_pDAODBEngine!=NULL);


	try
	{
		set.Close();
	}
	catch(CException* pe)
	{
		pe->ReportError();
		pe->Delete();
	}

	TerminateDAO(pDB);

	::PostMessage(g_hWndMain, MYWM_TERMINATING, GetCurrentThreadId(), 0);
	ReleaseMutex(g_hDBMutex);

	g_bDeleteThreadRunning = FALSE;
	return 0;
}