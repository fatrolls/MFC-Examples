/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Implementation File ThreadDispatcher.cpp
// class CWizThreadDispatcher
//
// 15/07/1996 11:54                             Author: Poul
///////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "ThreadDispatcher.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
#define new DEBUG_NEW

///////////////////////////////////////////////////////////////////
// class CWizThreadDispatcher
//*****************************************************************
// Default Constructor
CWizThreadDispatcher::CWizThreadDispatcher(CWizMultiThreadedWorker &rWorker, int MaxThreads)
	: m_nMaxThreads(MaxThreads),
	  m_rWorker(rWorker),
	  m_ShutDownEvent(TRUE),
	  m_HasDataEvent (FALSE),
	  m_StartedDataTreatEvent(FALSE),
	  m_ahWorkersHandles(NULL),
	  m_hThisThread(NULL),
	  m_pWnd (NULL),
	  m_nMessage(0)
{
	m_ahStartedTreatmentEvents[0] = m_ShutDownEvent.m_h;
	m_ahStartedTreatmentEvents[1] = m_StartedDataTreatEvent.m_h;
	m_ahWorkersHandles = new HANDLE[m_nMaxThreads + 1];
	if (m_ahWorkersHandles == NULL)
		AfxThrowMemoryException();
	for (INDEX i = 0; i < m_nMaxThreads; i++)
		m_ahWorkersHandles[i] = NULL;
}
//*****************************************************************
// Destructor
CWizThreadDispatcher::~CWizThreadDispatcher()
{
	delete [] m_ahWorkersHandles;
	Stop(FALSE);
}
//*****************************************************************
void	CWizThreadDispatcher::Start()
{
	CWinThread* pThr = AfxBeginThread(CWizThreadDispatcherFun, this);
	if (pThr == NULL)
		AfxThrowMemoryException();
}
//*****************************************************************
void	CWizThreadDispatcher::Stop(BOOL bWait)
{
	m_ShutDownEvent.Set();
	if (bWait)
		WaitShutDown();
}
//*****************************************************************
void	CWizThreadDispatcher::MsgStop (CWnd* pWnd, UINT Message)
{
	m_pWnd = pWnd;
	m_nMessage = Message;
	Stop(FALSE);
}
//*****************************************************************
void	CWizThreadDispatcher::WaitShutDown()
{
	const int hMax = m_nMaxThreads + 1;
	for (INDEX i = 0; i < hMax; i++)
		{
		while (1)
			{
			const DWORD dwWaitRes = ::MsgWaitForMultipleObjects(1, &(m_ahWorkersHandles[i]), TRUE, INFINITE,QS_ALLINPUT);
			if (dwWaitRes == WAIT_OBJECT_0 + 1)
				{
				MSG msg;
				while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
					if(!AfxGetApp()->PumpMessage())
						{
						ASSERT(0);
						ExitProcess(1);
						}
				}
			else
				{
				DWORD ExitCode;
				if (!GetExitCodeThread(m_ahWorkersHandles[i], &ExitCode) ||
					 ExitCode != STILL_ACTIVE)
					break; // from while
				}
			} // while
		} // for
}
//*****************************************************************
UINT AFX_CDECL CWizThreadDispatcherFun(LPVOID pParam)
{
	ASSERT(pParam != NULL);
	return ((CWizThreadDispatcher *)pParam)->Run();
}
//*****************************************************************
UINT 	CWizThreadDispatcher::Run()
{
	CWizMultiThreadedWorker::Stack stack(m_rWorker);
	m_hThisThread = AfxGetThread()->m_hThread;
	m_ahWorkersHandles[m_nMaxThreads] = m_hThisThread;
	//---------------------------------------------------------
	// Start all working threads
	for (INDEX i = 0; i < m_nMaxThreads; i++)
		{
		WorkerThread* pTr = new WorkerThread(m_rWorker, 
				m_HasDataEvent.m_h,
				m_StartedDataTreatEvent.m_h,
				m_ShutDownEvent.m_h);

		if (pTr == NULL)
			AfxThrowMemoryException();
		CWinThread* pThr = AfxBeginThread(CWizThreadDispatcher_WorkerThread_Fun, pTr);
		if (pThr == NULL)
			AfxThrowMemoryException();
		m_ahWorkersHandles[i] = pThr->m_hThread;
		}
	//---------------------------------------------------------
	while (1)
		{
		if (!m_rWorker.WaitForData(m_ShutDownEvent.m_h))
			{
			m_ShutDownEvent.Set();
			goto end;
			}
		m_HasDataEvent.Set();
		const DWORD res = 
			::WaitForMultipleObjects(StartedTreatmentEventsCount, m_ahStartedTreatmentEvents, FALSE, INFINITE);
		switch (res)
			{
			case WAIT_OBJECT_0: // Shut down!
				goto end;
			case (WAIT_OBJECT_0 + 1): // Worker thread started to treat data
				break;
			case WAIT_FAILED: // something wrong!
				throw XWaitFailed();
			default:
				ASSERT(0);
			}
		} // while 1
	//---------------------------------------------------------
end:
	//---------------------------------------------------------
	if (m_pWnd != NULL)
		{
		for (INDEX i = 0; i < m_nMaxThreads; i++)
			::WaitForSingleObject(m_ahWorkersHandles[i], INFINITE);
		for(i = 0; i < 10 ; i++)
			if (::IsWindow(m_pWnd->m_hWnd))
				{
				m_pWnd->PostMessage(m_nMessage,0,0);
				break;
				}
			else
				Sleep(100);
		}
	//---------------------------------------------------------
	return 0;
}
//*****************************************************************
///////////////////////////////////////////////////////////////////
CWizThreadDispatcher::WorkerThread::WorkerThread(CWizMultiThreadedWorker &rWorker, 
				HANDLE hDataReadyEvent,
				HANDLE hStartedTreatEvent,
				HANDLE hShutDownEvent)
	: m_rWorker (rWorker),
	  m_hStartedTreatEvent (hStartedTreatEvent)
{
	m_hDataWait[0] = hShutDownEvent;
	m_hDataWait[1] = hDataReadyEvent;
}
//*****************************************************************
UINT CWizThreadDispatcher::WorkerThread::Run()
{
	while (1)
		{
		const DWORD res = 
			::WaitForMultipleObjects(DataWaitHCount, m_hDataWait, FALSE, INFINITE);
		switch (res)
			{
			case WAIT_FAILED: // something wrong!
				throw CWizThreadDispatcher::XWaitFailed();
			case WAIT_OBJECT_0: // Shut down!
				return 0;
			case (WAIT_OBJECT_0 + 1): // Has data to treat
				if (!m_rWorker.TreatData(m_hDataWait[0], m_hStartedTreatEvent))
					return 0;
				break;
			default:
				ASSERT(0);
			}
		} // while 1
	return 0;
}
//*****************************************************************
UINT AFX_CDECL CWizThreadDispatcher_WorkerThread_Fun(LPVOID pParam)
{
	CWizThreadDispatcher::WorkerThread* pWorker = (CWizThreadDispatcher::WorkerThread*)pParam;
	ASSERT(pWorker != NULL);
	UINT res = 0;
	try
		{
		UINT res = pWorker->Run();
		}
	catch(...)
		{
		delete pWorker;
		throw;
		}
	delete pWorker;
	return res;
}
//*****************************************************************
