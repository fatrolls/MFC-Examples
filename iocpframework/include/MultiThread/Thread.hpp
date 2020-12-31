#ifndef __THREAD_THREAD_HPP
#define __THREAD_THREAD_HPP


#include <process.h>

#ifndef ATLTRY
#define ATLTRY(x) (x)
#endif // ATLTRY





namespace async
{

	namespace thread
	{


		//-----------------------------------------------------
		// Thread

		template< bool t_bManaged >
		class ThreadT
		{
		public:
			HANDLE m_hThread;       // Handle to thread
			DWORD m_dwThreadID;     // Thread ID
			bool m_bSuspended;      // Thread currently suspended?

			ThreadT(HANDLE hThread = NULL) : m_hThread(hThread), m_dwThreadID(0), m_bSuspended(false)
			{
			}

			~ThreadT()
			{
				if( t_bManaged ) Release();
			}

			// Operations

			bool Create(LPTHREAD_START_ROUTINE pThreadProc, LPVOID pParam = NULL, int iPriority = THREAD_PRIORITY_NORMAL)
			{
				assert(m_hThread==NULL);
				assert(pThreadProc);

#if defined(_MT) || defined(_DLL)
				m_hThread = (HANDLE) _beginthreadex(NULL, 0, (UINT (WINAPI*)(void*)) pThreadProc, pParam, CREATE_SUSPENDED, (UINT*) &m_dwThreadID);
#else
				m_hThread = ::CreateThread(NULL, 0, pThreadProc, pParam, CREATE_SUSPENDED, &m_dwThreadID);
#endif // _MT

				if( m_hThread == NULL ) 
					return FALSE;

				if( iPriority != THREAD_PRIORITY_NORMAL ) 
				{
					if( !::SetThreadPriority(m_hThread, iPriority) ) 
					{
						assert(!"Couldn't set thread priority");
					}
				}

				return ::ResumeThread(m_hThread) != (DWORD) -1;
			}

			bool Release()
			{
				if( m_hThread == NULL ) 
					return TRUE;
				if( ::CloseHandle(m_hThread) == FALSE ) 
					return FALSE;

				m_hThread = NULL;
				m_dwThreadID = 0;

				return TRUE;
			}

			void Attach(HANDLE hThread)
			{
				assert(m_hThread==NULL);
				m_hThread = hThread;
			}

			HANDLE Detach()
			{
				HANDLE hThread = m_hThread;
				m_hThread = NULL;

				return hThread;
			}

			bool SetPriority(int iPriority) const
			{
				assert(m_hThread);

				return ::SetThreadPriority(m_hThread, iPriority);
			}

			int GetPriority() const
			{
				assert(m_hThread);

				return ::GetThreadPriority(m_hThread);
			}

			bool Suspend()
			{
				assert(m_hThread);

				if( m_bSuspended ) 
					return TRUE;

				if( ::SuspendThread(m_hThread) == (DWORD) -1 ) 
					return FALSE;

				m_bSuspended = true;

				return TRUE;
			}

			bool Resume()
			{
				assert(m_hThread);

				if( !m_bSuspended ) 
					return TRUE;

				if( ::ResumeThread(m_hThread) == (DWORD) -1 ) 
					return FALSE;

				m_bSuspended = false;

				return TRUE;
			}

			bool IsSuspended() const
			{
				assert(m_hThread);

				return m_bSuspended == true;
			}

			bool IsRunning() const
			{
				if( m_hThread == NULL ) 
					return FALSE;
				DWORD dwCode = 0;

				::GetExitCodeThread(m_hThread, &dwCode);

				return dwCode == STILL_ACTIVE;
			}

			bool WaitForThread(DWORD dwTimeout = INFINITE) const
			{
				assert(m_hThread);

				return ::WaitForSingleObject(m_hThread, dwTimeout) == WAIT_OBJECT_0;
			}

			bool Terminate(DWORD dwExitCode = 0) const
			{
				// See Q254956 why calling this could be a bad idea!
				assert(m_hThread);

				return TRUE == ::TerminateThread(m_hThread, dwExitCode);
			}

			DWORD GetThreadID() const
			{
				return m_dwThreadID;
			}

			bool GetExitCode(DWORD* pExitCode) const
			{
				assert(m_hThread);
				assert(pExitCode);

				return ::GetExitCodeThread(m_hThread, pExitCode);
			}

#if(WINVER >= 0x0500)

			bool GetThreadTimes(LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime) const
			{
				assert(m_hThread);
				assert(lpExitTime!=NULL && lpKernelTime!=NULL && lpUserTime!=NULL);

				return ::GetThreadTimes(m_hThread, lpCreationTime, lpExitTime, lpKernelTime, lpUserTime);
			}

#endif // WINVER

#if(WINVER >= 0x0501)

			bool SetThreadAffinityMask(DWORD dwThreadMask)
			{
				assert(m_hThread);

				return ::SetThreadAffinityMask(m_hThread, dwThreadMask) != 0;
			}

			bool SetThreadIdealProcessor(DWORD dwIdealProcessor)
			{
				assert(m_hThread);

				return ::SetThreadIdealProcessor(m_hThread, dwIdealProcessor) != (DWORD) -1;
			}

			DWORD GetThreadIdealProcessor() const
			{
				assert(m_hThread);

				return ::SetThreadIdealProcessor(m_hThread, MAXIMUM_PROCESSORS);
			}

#endif // WINVER

			operator HANDLE() const 
			{ 
				return m_hThread; 
			}
		};

		typedef ThreadT<false>	ThreadHandle;
		typedef ThreadT<true>	Thread;



		//----------------------------------------------------------------------
		// Thread Stop policy

		class ThreadStopAtBool
		{
		public:
			volatile bool m_bStopped;
			ThreadStopAtBool() : m_bStopped(false) { };
			bool _ClearAbort()        { m_bStopped = false; return TRUE; };
			bool _Abort()             { m_bStopped = true; return TRUE; };
			bool _IsAborted() const   { return m_bStopped == true; };
		};

		class ThreadStopAtEvent
		{
		public:
			HANDLE m_hStopEvent;
			ThreadStopAtEvent()      { m_hStopEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL); };
			~ThreadStopAtEvent()     { ::CloseHandle(m_hStopEvent); };
			BOOL _ClearAbort()        { return ::ResetEvent(m_hStopEvent); };
			BOOL _Abort()             { return ::SetEvent(m_hStopEvent); };
			bool _IsAborted() const   { return ::WaitForSingleObject(m_hStopEvent, 0) != WAIT_TIMEOUT; };
		};


		/////////////////////////////////////////////////////////////////////////////
		// ThreadImpl

		template< typename T, typename TStopPolicy = ThreadStopAtBool >
		class ThreadImpl 
			: public Thread
			, public TStopPolicy
		{
		public:
			bool m_bAutoDelete;     // Thread class will delete itself upon thread exit?
			bool m_bAutoCleanup;    // Thread class will wait for thread completion upon scope exit?

			ThreadImpl() 
				: m_bAutoDelete(false)
				, m_bAutoCleanup(true)
			{
			}

			~ThreadImpl()
			{
				if( m_bAutoCleanup ) 
					Stop();
			}

			// Operations

			bool Start()
			{
				if( !_ClearAbort() )
					return FALSE;
				if( !Create(ThreadProc, (LPVOID) static_cast<T*>(this)) ) 
					return FALSE;

				return TRUE;
			}

			void Stop()
			{
				if( !Abort() ) 
					return;

				WaitForThread();
				Release();
			}

			bool Abort()
			{
				if( m_hThread == NULL ) 
					return FALSE;
				if( !_Abort() )
					return FALSE;
				if( m_bSuspended ) 
					Resume();

				return TRUE;
			}

			bool IsAborted() const
			{
				assert(m_hThread);

				return _IsAborted();
			}

			void SetAutoClean(bool bAutoClean = true)
			{
				m_bAutoCleanup = bAutoClean;
			}

			void SetDeleteOnExit(bool bAutoDelete = true)
			{
				m_bAutoDelete = bAutoDelete;
				m_bAutoCleanup = !bAutoDelete;
			}

			// Static members

			static DWORD WINAPI ThreadProc(LPVOID pData)
			{
				T* pThis = static_cast<T*>(pData);

#if defined(_MT) || defined(_DLL)
				ATLTRY( ::_endthreadex(pThis->Run()) );
				if( pThis->m_bAutoDelete ) 
					delete pThis;
				return 0;
#else
				DWORD dwRet = 0;
				ATLTRY( dwRet = pThis->Run() );
				if( pThis->m_bAutoDelete ) 
					delete pThis;
				return dwRet;
#endif // _MT
			}

			// Overridables

			DWORD Run()
			{
				assert(false); // must override this
				//
				// Sample thread loop...
				//
				//  while( !IsAborted() ) {
				//    ...
				//  }
				//
				return 0;
			}
		};


		//---------------------------------------------------------------
		// CThreadImplEx

		template<typename TStopPolicy>
		class ThreadImplExT 
			: public Thread
			, private TStopPolicy
		{
			typedef std::tr1::function<DWORD(void)> ThreadFunc;

		public:
			bool m_bAutoDelete;     // Thread class will delete itself upon thread exit?
			bool m_bAutoCleanup;    // Thread class will wait for thread completion upon scope exit?

			ThreadFunc m_fThread;	// Thread work function

		public:
			ThreadImplExT() 
				: m_bAutoDelete(false)
				, m_bAutoCleanup(true)
			{
			}

			~ThreadImplExT()
			{
				if( m_bAutoCleanup ) 
					Stop();
			}

			// Register Thread work function
			void RegisterFunc(ThreadFunc func)
			{
				m_fThread = func;
			}

			// Operations

			bool Start()
			{
				if( !_ClearAbort() )
					return FALSE;
				if( !Create(ThreadProc, reinterpret_cast<LPVOID>(this)) ) 
					return FALSE;

				return TRUE;
			}

			void Stop(DWORD dwTime = INFINITE)
			{
				if( !Abort() ) 
					return;

				if( WaitForThread(dwTime) )
					Terminate(-1);

				Release();
			}

			bool Abort()
			{
				if( m_hThread == NULL ) 
					return FALSE;
				if( !_Abort() )
					return FALSE;
				if( m_bSuspended ) 
					Resume();

				return TRUE;
			}

			bool IsAborted() const
			{
				assert(m_hThread);

				return _IsAborted();
			}

			void SetAutoClean(bool bAutoClean = true)
			{
				m_bAutoCleanup = bAutoClean;
			}

			void SetDeleteOnExit(bool bAutoDelete = true)
			{
				m_bAutoDelete = bAutoDelete;
				m_bAutoCleanup = !bAutoDelete;
			}

			// Static members

			static DWORD WINAPI ThreadProc(LPVOID pData)
			{
				ThreadImplExT* pThis = reinterpret_cast<ThreadImplExT *>(pData);

				// Not Register?
				if( pThis->m_fThread == NULL )
					return -1L;

#if defined(_MT) || defined(_DLL)
				ATLTRY( _endthreadex(pThis->m_fThread()) );
				if( pThis->m_bAutoDelete ) 
					delete pThis;
				return 0;
#else
				DWORD dwRet = 0;
				ATLTRY( dwRet = pThis->pThis->m_fThread() );
				if( pThis->m_bAutoDelete ) 
					delete pThis;
				return dwRet;
#endif // _MT
			}
		};

		typedef ThreadImplExT<ThreadStopAtBool>		ThreadImplEx;
		typedef ThreadImplExT<ThreadStopAtEvent>	ThreadImplExEvent;



		//-----------------------------------------------------------
		// MessageThreadImpl

		template< typename T >
		class MessageThreadImpl 
			: public ThreadImpl<T>
		{
		public:
			// Operations

			bool PostQuitMessage()
			{
				assert(m_hThread);
				if( m_hThread == NULL ) 
					return FALSE;

				return ::PostThreadMessage(m_dwThreadID, WM_QUIT, 0, 0L);
			}

			bool PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L)
			{
				assert(m_hThread);
				if( m_hThread == NULL ) 
					return FALSE;

				return ::PostThreadMessage(m_dwThreadID, uMsg, wParam, lParam);
			}

			// Overridables

			void InitQueue()
			{
			}

			void CloseQueue()
			{
			}

			void ProcessWindowMessage(LPVOID /*pReserved*/, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& /*lResult*/, DWORD /*dwReserved*/)
			{
				assert(false); // must override this
			}

			// Implementation

			DWORD Run()
			{
				T* pT = static_cast<T*>(this);
				MSG msg;
				::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
				pT->InitQueue();
				while( !IsAborted() )
				{
					int iRet = (int) 
						::GetMessage(&msg, NULL, 0, 0);
					if( iRet <= 0 ) 
						break;

					LRESULT lResult = 0;
					pT->ProcessWindowMessage(NULL, msg.message, msg.wParam, msg.lParam, lResult, 0L);
				}

				pT->CloseQueue();
				return 0;
			}
		};


		//--------------------------------------------------------------
		// CMessageThreadImplEx

		template<typename StopPolicyT>
		class MessageThreadImplExT 
			: public ThreadImplExT<StopPolicyT>
		{
			typedef std::tr1::function<void(MSG &, LRESULT &)> ThreadMessageFunc;

		public:
			ThreadMessageFunc m_fMessageFunc;

		protected:
			void RegisterFunc(ThreadFunc);

		public:
			// Operations

			void RegisterMessageFunc(ThreadMessageFunc func)
			{
				m_fMessageFunc = func;
				m_fThread = std::tr1::bind(&MessageThreadImplExT::Run, this);
			}

			bool PostQuitMessage()
			{
				assert(m_hThread);
				if( m_hThread == NULL ) 
					return FALSE;

				return 0 != ::PostThreadMessage(m_dwThreadID, WM_QUIT, 0, 0L);
			}

			bool PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L)
			{
				assert(m_hThread);
				if( m_hThread == NULL ) 
					return FALSE;

				return 0 != ::PostThreadMessage(m_dwThreadID, uMsg, wParam, lParam);
			}

			// Implementation

			DWORD Run()
			{
				assert(m_fMessageFunc != NULL);
				// Not Register?
				if( m_fMessageFunc == NULL )
					return -1L;

				MSG msg;
				::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);

				while( !IsAborted() )
				{
					LRESULT lResult = 0;
					m_fMessageFunc(msg, lResult);
					if( lResult != S_OK )
						break;
				}


				return 0;
			}
		};

		typedef MessageThreadImplExT<ThreadStopAtBool>		MessageThreadImplEx;
		typedef MessageThreadImplExT<ThreadStopAtEvent>		MessageThreadImplExEvent;

	}

}

#endif // __THREAD_THREAD_HPP

