#include "stdafx.h"

#include <process.h>

#include "Dispatcher.hpp"
#include "WinException.hpp"



namespace async
{
	
	namespace IOCP
	{
		// 获取适合系统的线程数
		size_t GetFitThreadNum(size_t perCPU/* = 2*/)
		{
			SYSTEM_INFO systemInfo = {0};
			::GetSystemInfo(&systemInfo);

			return perCPU * systemInfo.dwNumberOfProcessors;
		}


		IODispatcher::IODispatcher(size_t numThreads/* = 0*/)
		{
			if( !m_hIOCP.Create(numThreads) )
				throw Win32Exception("m_hIOCP.Create()");

			try
			{
				// 创建指定的线程数
				m_threads.reserve(numThreads);

				for(int i = 0; i != numThreads; ++i)
				{
					HANDLE hThread = (HANDLE)::_beginthreadex(NULL, 0, &IODispatcher::_ThreadIOImpl, this, 0, 0);

					if( hThread == NULL )
						throw Win32Exception("_beginthreadex");

					m_threads.push_back(hThread);
				}
			}
			catch(const std::exception &e)
			{
				Stop();
				throw e;
			}
		}

		IODispatcher::~IODispatcher()
		{
			try
			{		
				Stop();
				m_hIOCP.Close();
			}
			catch(...)
			{
				std::cerr << "Unknown error!" << std::endl;
			}
		}

		void IODispatcher::Bind(HANDLE hHandle)
		{
			if( !m_hIOCP.AssociateDevice(hHandle, 0) )
				throw Win32Exception("m_hIOCP.AssociateDevice");
		}

		void IODispatcher::Post(const AsyncResultPtr &async)
		{
			async->AddRef();

			if( 0 == m_hIOCP.PostStatus(0, 0, &*async) )
				throw Win32Exception("m_hIOCP.PostStatus");
		}

		void IODispatcher::Stop()
		{
			// 先停止所有的线程
			for(ThreadsIter iter = m_threads.begin();
				iter != m_threads.end();
				++iter)
			{
				m_hIOCP.PostStatus(static_cast<ULONG_PTR>(~0), 0, NULL);
			}

			// 等待线程退出并关闭句柄
			if( !m_threads.empty() )
				::WaitForMultipleObjects(m_threads.size(), &*m_threads.begin(), TRUE, INFINITE);

			std::for_each(m_threads.begin(), m_threads.end(), std::ptr_fun(::CloseHandle));

			m_threads.clear();
		}


		void IODispatcher::_ThreadIO()
		{
			DWORD dwSize = 0;
			ULONG_PTR uKey = 0;
			OVERLAPPED *pOverlapped = NULL;

			while(true)
			{
				BOOL bSuc = ::GetQueuedCompletionStatus(m_hIOCP, &dwSize, &uKey, &pOverlapped, INFINITE);
				//if( !bSuc )
				//{
				//	//throw Win32Exception("GetQueuedCompletionStatus");
				//	continue;
				//}

				if( uKey != 0 || pOverlapped == NULL )
					break;

				// 回调
				AsyncResultPtr asynResult = static_cast<AsyncResult *>(pOverlapped);
				asynResult->Release();

				if( asynResult->m_callback != NULL )
				{
					try
					{
						asynResult->m_callback(std::tr1::cref(asynResult));
					}
					catch(const std::exception &e)
					{
						std::cerr << e.what() << std::endl;
						assert(0);
						// Opps!!
					}
					catch(...)
					{
						assert(0);
						// Opps!!
					}
				}
			}
		}


		size_t IODispatcher::_ThreadIOImpl(LPVOID pParam)
		{
			IODispatcher *pThis = reinterpret_cast<IODispatcher *>(pParam);

			pThis->_ThreadIO();

			::OutputDebugStringW(L"Exit\n");
			return 0;
		}


	}

}