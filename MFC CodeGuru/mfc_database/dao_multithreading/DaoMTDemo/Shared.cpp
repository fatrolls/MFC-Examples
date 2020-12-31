#include "stdafx.h"
#include "Shared.h"

extern HANDLE	g_hDBMutex;

CDaoDatabase* InitializeDAO()
{
	CDaoDatabase* pDB = NULL;
	CDaoWorkspace* pWS = NULL;

	WaitAndPumpMessages(g_hDBMutex, INFINITE);

	AfxDaoInit();
	_DAODBEngine* pEngine = AfxGetDaoState()->m_pDAODBEngine;
	TlsSetValue(dwDBEngineSlot, pEngine);

	TRACE(_T("Initialize DAO for thread %d\n"), GetCurrentThreadId());

	//
	// Open database
	//
	try
	{
		CString s;
		s.Format("NyWS%x", GetCurrentThreadId());
		pWS = new CDaoWorkspace;
		pWS->Create(s, "admin", "");
		pWS->Append();
		pDB = new CDaoDatabase(pWS);
		pDB->Open(_T("test.mdb"));
		
	}
	catch(CException* pException)
	{
		pException->ReportError();
		pException->Delete();

		if(pDB)
		{
			delete pDB;
			pDB = NULL;
		}
		if(pWS)
		{
			delete pWS;
			pWS = NULL;
		}
	}

	ReleaseMutex(g_hDBMutex);
	return pDB;
}

void TerminateDAO(CDaoDatabase* pDB)
{
	WaitAndPumpMessages(g_hDBMutex, INFINITE);
	ASSERT_VALID(pDB);

	AfxGetDaoState()->m_pDAODBEngine = (DAODBEngine *)TlsGetValue(dwDBEngineSlot);
	ASSERT(AfxGetDaoState()->m_pDAODBEngine!=NULL);


	TRACE(_T("Terminate DAO for thread %d\n"), GetCurrentThreadId());

	try
	{
		pDB->Close();
		pDB->m_pWorkspace->Close();

	}
	catch(CException* pException)
	{
		pException->ReportError();
		pException->Delete();

	}

	delete pDB->m_pWorkspace;
	delete pDB;

	_DAODBEngine* pEngine = (_DAODBEngine *)TlsGetValue(dwDBEngineSlot);
	if(pEngine)
		pEngine->Release();
	TlsSetValue(dwDBEngineSlot, NULL);

	ReleaseMutex(g_hDBMutex);
}





DWORD WaitAndPumpMessages(HANDLE hWait, DWORD dwTimeout)
{
	DWORD dwWait = MsgWaitForMultipleObjects(1, &hWait, FALSE, dwTimeout, QS_ALLINPUT);

	// Do we have a message in the queue
	if(dwWait == (WAIT_OBJECT_0+1))
	{
		MSG msg;
		while(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

	return dwWait;
}
