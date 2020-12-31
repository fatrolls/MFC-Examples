#pragma once

#include "stdafx.h"

#ifndef INCLUDE_THREAD
#define INCLUDE_THREAD

/************************************************************************/
/* CThread                                                              */
/************************************************************************/
class CThread
{
private:
	HANDLE m_hThread;
	DWORD m_dwThreadId;
	BOOL m_Suspended;

	static DWORD CALLBACK ThreadProc(LPVOID lpParameter)
	{
		CThread* pThread = (CThread*)lpParameter;
		if(pThread == NULL)
			return 0;

		pThread->Execute();
		return 0;
	}

protected:
	BOOL m_Stop;
	virtual void Execute() = 0; /* this pure virtual function should be implemented by child class 
								which inherited from this class
								*/
public:
	CThread(BOOL pCreateSuspened = TRUE) : m_hThread(NULL), m_dwThreadId(0), m_Stop(FALSE), m_Suspended(FALSE)
	{
		m_hThread = CreateThread(NULL, 0, ThreadProc, (void*)this,
			(pCreateSuspened == TRUE) ? CREATE_SUSPENDED : 0, &m_dwThreadId);
		m_Suspended = TRUE;
	}

	~CThread()
	{
		if(m_hThread != NULL)
		{
			CloseHandle(m_hThread);
		}
	}

	void Resume()
	{
		if(m_hThread != NULL && m_Suspended == TRUE && !m_Stop)
		{
			ResumeThread(m_hThread);
			m_Suspended = FALSE;
		}
	}

	void Suspend()
	{
		if(m_hThread != NULL && m_Suspended == FALSE && !m_Stop)
		{
			SuspendThread(m_hThread);
			m_Suspended = TRUE;
		}
	}

	BOOL Suspended() { return m_Suspended; }

	void Stop()
	{
		m_Stop = TRUE;
		if(!Suspended())
			Suspend();
	}
};

#endif
