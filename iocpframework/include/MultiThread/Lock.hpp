#ifndef __THREAD_AUTO_LOCK_HPP
#define __THREAD_AUTO_LOCK_HPP

#include <cassert>

namespace async
{

	namespace thread
	{

	
	//-------------------------------------------------------
	// CAutoNull

	class CAutoNull
	{
	public:
		void Lock(){}
		void Unlock(){}
	};



	//-------------------------------------------------------
	// CAutoSpinLock

	class CAutoSpinLock
	{
	private:
		CRITICAL_SECTION m_sec;

	public:
		CAutoSpinLock(u_long dwCount = 4000) 
		{
			::InitializeCriticalSectionAndSpinCount(&m_sec, dwCount);	// MS 
		}

		~CAutoSpinLock() 
		{
			::DeleteCriticalSection(&m_sec);
		}

	public:
		void Lock() 
		{
			::EnterCriticalSection(&m_sec);
		}

		void Unlock() 
		{
			::LeaveCriticalSection(&m_sec);
		}

		CRITICAL_SECTION &operator()()
		{
			return m_sec;
		}
	};

	//-------------------------------------------------------
	// CAutoCriticalSection

	class CAutoCriticalSection
	{
	private:
		CRITICAL_SECTION m_sec;

	public:
		CAutoCriticalSection() 
		{
			::InitializeCriticalSection(&m_sec);
		}

		~CAutoCriticalSection() 
		{
			::DeleteCriticalSection(&m_sec);
		}

	public:
		void Lock() 
		{
			::EnterCriticalSection(&m_sec);
		}

		void Unlock() 
		{
			::LeaveCriticalSection(&m_sec);
		}

		CRITICAL_SECTION &operator()()
		{
			return m_sec;
		}
	};


	//-------------------------------------------------------
	// CAutoMutex

	class CAutoMutex
	{
	private:
		HANDLE m_hMutex;

	public:
		CAutoMutex()
			: m_hMutex(NULL)
		{
			m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
		}
		~CAutoMutex()
		{
			if( m_hMutex != NULL )
				::CloseHandle(m_hMutex);
		}

	public:
		void Lock()
		{
			::WaitForSingleObject(m_hMutex, INFINITE);
		}

		void UnLock()
		{
			::ReleaseMutex(m_hMutex);
		}

		HANDLE &operator()()
		{
			return m_hMutex;
		}
	};

	//-------------------------------------------------------
	// CAutoEvent

	class CAutoEvent
	{
	public:
		HANDLE m_hEvent;

		CAutoEvent(HANDLE hEvent = INVALID_HANDLE_VALUE) : m_hEvent(hEvent)
		{ 
		}

		~CAutoEvent()
		{
			Close();
		}

		BOOL Create(LPCTSTR pstrName = NULL, BOOL bManualReset = FALSE, BOOL bInitialState = FALSE, LPSECURITY_ATTRIBUTES pEventAttributes = NULL)
		{
			assert(pstrName==NULL || !::IsBadStringPtr(pstrName,(UINT)-1));
			assert(m_hEvent==INVALID_HANDLE_VALUE);

			m_hEvent = ::CreateEvent(pEventAttributes, bManualReset, bInitialState, pstrName);
			assert(m_hEvent!=INVALID_HANDLE_VALUE);

			return m_hEvent != INVALID_HANDLE_VALUE;
		}

		BOOL Open(LPCTSTR pstrName, DWORD dwDesiredAccess = EVENT_ALL_ACCESS, BOOL bInheritHandle = TRUE)
		{
			assert(!::IsBadStringPtr(pstrName,(UINT)-1));
			assert(m_hEvent==INVALID_HANDLE_VALUE);

			m_hEvent = ::OpenEvent(dwDesiredAccess, bInheritHandle, pstrName);
			assert(m_hEvent!=INVALID_HANDLE_VALUE);

			return m_hEvent != INVALID_HANDLE_VALUE;
		}

		BOOL IsOpen() const
		{
			return m_hEvent != INVALID_HANDLE_VALUE;
		}

		void Close()
		{
			if( m_hEvent == INVALID_HANDLE_VALUE ) 
				return;

			::CloseHandle(m_hEvent);
			m_hEvent = INVALID_HANDLE_VALUE;
		}

		void Attach(HANDLE hEvent)
		{
			assert(m_hEvent==INVALID_HANDLE_VALUE);
			m_hEvent= hEvent;
		}  

		HANDLE Detach()
		{
			HANDLE hEvent = m_hEvent;
			m_hEvent = INVALID_HANDLE_VALUE;
			return hEvent;
		}

		BOOL ResetEvent()
		{
			assert(m_hEvent!=INVALID_HANDLE_VALUE);
			return ::ResetEvent(m_hEvent);
		}

		BOOL SetEvent()
		{
			assert(m_hEvent!=INVALID_HANDLE_VALUE);
			return ::SetEvent(m_hEvent);
		}

		BOOL PulseEvent()
		{
			assert(m_hEvent!=INVALID_HANDLE_VALUE);
			return ::PulseEvent(m_hEvent);
		}

		BOOL IsSignalled() const
		{
			assert(m_hEvent!=INVALID_HANDLE_VALUE);
			return ::WaitForSingleObject(m_hEvent, 0) == WAIT_OBJECT_0;
		}

		BOOL WaitForEvent(DWORD dwTimeout = INFINITE)
		{
			assert(m_hEvent!=INVALID_HANDLE_VALUE);
			return ::WaitForSingleObject(m_hEvent, dwTimeout) == WAIT_OBJECT_0;
		}

		operator HANDLE() const 
		{ 
			return m_hEvent; 
		}
	};



	//-------------------------------------------------------
	// CAutoLock

	template<typename T>
	class CAutoLock
	{
	private:
		T &m_lock;

	public:
		CAutoLock(T &lock)
			: m_lock(lock)
		{
			m_lock.Lock();
		}
		~CAutoLock()
		{
			m_lock.Unlock();
		}

	private:
		CAutoLock(const CAutoLock &);
		CAutoLock &operator=(const CAutoLock &);
	};

}

}

#endif