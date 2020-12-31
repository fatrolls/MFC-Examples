#include "stdafx.h"
#include "DaoMTDemo.h"
#include "TestSet.h"
#include "Shared.h"

extern HWND		g_hWndMain;
extern LONG		g_nAddedRecordCount;
extern BOOL		g_bUseTransactionsWhenAdding;
extern HANDLE	g_hDBMutex;


UINT AddingThreadFunction(LPVOID lpvData)
{
	DWORD dwWait;
	HANDLE hTerminateSignal = (HANDLE)lpvData;

	ASSERT(hTerminateSignal != NULL);
	ASSERT(IsWindow(g_hWndMain));

	CDaoDatabase* pDB = InitializeDAO();
	if(!pDB)
	{
		::PostMessage(g_hWndMain, MYWM_TERMINATING, GetCurrentThreadId(), 0);
		return -1;
	}
			   

	srand(GetTickCount());

	WaitAndPumpMessages(g_hDBMutex, INFINITE);

	AfxGetDaoState()->m_pDAODBEngine = (DAODBEngine *)TlsGetValue(dwDBEngineSlot);
	ASSERT(AfxGetDaoState()->m_pDAODBEngine!=NULL);

	//
	// Get hold on the semaphore
	// Open table recordset.
	// 
	CTestSet set(pDB);
	try
	{
		set.Open(dbOpenTable);	// Table set faster when adding new records !!!
	}
	catch(CException* pException)
	{

		pException->ReportError();
		pException->Delete();

		TerminateDAO(pDB);
		::PostMessage(g_hWndMain, MYWM_TERMINATING, GetCurrentThreadId(), 0);
		return -2;
	}

	ReleaseMutex(g_hDBMutex);

	while(1)
	{
		dwWait = MsgWaitForMultipleObjects(1, &hTerminateSignal, FALSE, 0, QS_ALLINPUT);

		MSG msg;
		while(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(dwWait == WAIT_TIMEOUT)
		{			
			BOOL bTransactionActive = FALSE;
			try
			{
				WaitAndPumpMessages(g_hDBMutex, INFINITE);

				
				AfxGetDaoState()->m_pDAODBEngine = (DAODBEngine *)TlsGetValue(dwDBEngineSlot);
				ASSERT(AfxGetDaoState()->m_pDAODBEngine!=NULL);

				if(g_bUseTransactionsWhenAdding)
				{
					set.m_pDatabase->m_pWorkspace->BeginTrans();
					bTransactionActive = TRUE;
				}

				
				set.AddNew();
				set.m_test_number = rand();
				set.m_test_string.Format(_T("CodeGuru #%d"), set.m_test_number);
				set.Update();
				if(bTransactionActive)
				{
					set.m_pDatabase->m_pWorkspace->CommitTrans();
					//DAO_CHECK(set.m_pDatabase->m_pWorkspace->m_pDAOWorkspace->CommitTrans( dbForceOSFlush ));
				}

				ReleaseMutex(g_hDBMutex);

				InterlockedIncrement(&g_nAddedRecordCount);
			}
			catch(CException* pe)
			{
				if(bTransactionActive)
					set.m_pDatabase->m_pWorkspace->Rollback();

				pe->ReportError();
				pe->Delete();
				break;
			}
		}
		else if(dwWait == WAIT_OBJECT_0)
		{
			// Terminate signal set.
			// Break out of loop
			break;
		}
	}

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
	ReleaseMutex(g_hDBMutex);

	::PostMessage(g_hWndMain, MYWM_TERMINATING, GetCurrentThreadId(), 0);

	return 0;
}