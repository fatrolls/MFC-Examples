#ifndef __IOCP_IOCP_HPP
#define __IOCP_IOCP_HPP


#include <cassert>



namespace async
{

	namespace IOCP
	{
		//--------------------------------------------------------------
		// class CIOCP

		class CIOCP
		{
		private:
			HANDLE m_hIOCP;

		public:
			CIOCP(int nMaxConcurrency = -1)
				: m_hIOCP(NULL)
			{
				if( nMaxConcurrency != -1 )
					Create(nMaxConcurrency);
			}
			~CIOCP()
			{
				if( m_hIOCP != NULL )
				{
					assert(::CloseHandle(m_hIOCP));
				}
			}

		public:
			bool IsOpen() const
			{
				return m_hIOCP != NULL;
			}

			bool Close()
			{
				BOOL bRes = ::CloseHandle(m_hIOCP);
				m_hIOCP = NULL;

				return bRes == TRUE;
			}

			bool Create(int nMaxConcurrency = 0)
			{
				m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, nMaxConcurrency);

				assert(m_hIOCP != NULL);

				return m_hIOCP != NULL;
			}

			bool AssociateDevice(HANDLE hDevice, ULONG_PTR ulCompKey)
			{
				BOOL bOk = (::CreateIoCompletionPort(hDevice, m_hIOCP, ulCompKey, 0) == m_hIOCP);

				assert(bOk);
				return bOk == TRUE;
			}

			bool AssociateSocket(SOCKET hSocket, ULONG_PTR ulComKey)
			{
				return AssociateDevice(reinterpret_cast<HANDLE>(hSocket), ulComKey);
			}

			bool PostStatus(ULONG_PTR ulCompKey, DWORD dwNumBytes = 0, OVERLAPPED *pOver = NULL)
			{
				BOOL bOk = ::PostQueuedCompletionStatus(m_hIOCP, dwNumBytes, ulCompKey, pOver);
				assert(bOk);

				return bOk == TRUE;
			}

			bool GetStatus(ULONG_PTR *pCompKey, PDWORD pdwNumBytes, OVERLAPPED **pOver, DWORD dwMilliseconds = INFINITE)
			{
				return TRUE == ::GetQueuedCompletionStatus(m_hIOCP, pdwNumBytes, pCompKey, pOver, dwMilliseconds);
			}

			operator HANDLE() const
			{
				return m_hIOCP;
			}
		};


	}

}

#endif