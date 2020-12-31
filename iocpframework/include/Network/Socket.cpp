#include "stdafx.h"

#include "Socket.hpp"
#include "SocketProvider.hpp"

#include "../IOCP/WinException.hpp"


namespace async
{


	namespace network
	{

		Socket::Socket(IODispatcher &io, int nType /* = SOCK_STREAM */, int nProtocol /* = IPPROTO_TCP */)
			: socket_(INVALID_SOCKET)
			, io_(io)
		{
			SocketProvider &provider = SocketProvider::GetSingleton(io_);

			// 创建
			Create(nType, nProtocol);

			// 绑定到IOCP
			io_.Bind(reinterpret_cast<HANDLE>(socket_));
		}

		Socket::~Socket()
		{
			Close();
		}


		void Socket::Create(int nType /* = SOCK_STREAM */, int nProtocol /* = IPPROTO_TCP */)
		{
			if( socket_ != INVALID_SOCKET )
				return;

			socket_ = ::WSASocket(AF_INET, nType, nProtocol, NULL, 0, WSA_FLAG_OVERLAPPED); //::socket(AF_INET, nType, nProtocol);
			if( socket_ == INVALID_SOCKET )
				throw Win32Exception("WSASocket");

			// 绑定到IOCP
			//io_.Bind(reinterpret_cast<HANDLE>(socket_));
		}

		void Socket::Close()
		{
			if( socket_ == INVALID_SOCKET )
				return;

			::shutdown(socket_, SD_BOTH);
			::closesocket(socket_);
			socket_ = INVALID_SOCKET;
		}

		void Socket::IOControl(DWORD dwIOControl, const SocketBufferPtr &inBuf, const SocketBufferPtr &outBuf)
		{
			DWORD dwRet = 0;

			if( 0 != ::WSAIoctl(socket_, dwIOControl, inBuf->data(), inBuf->allocSize(), 
				outBuf->data(), outBuf->allocSize(), &dwRet, 0, 0) )
				throw Win32Exception("WSAIoCtl");

			outBuf->resize(dwRet);
		}

		void Socket::Bind(u_short uPort /* = 0 */, const IPAddress &addr /* = INADDR_ANY */)
		{
			sockaddr_in addrIn = {0};
			addrIn.sin_family		= AF_INET;
			addrIn.sin_port			= ::htons(uPort);
			addrIn.sin_addr.s_addr	= ::htonl(addr.Address());

			if( 0 != ::bind(socket_, (const SOCKADDR *)&addrIn, sizeof(SOCKADDR)) )
				throw Win32Exception("bind");
		}

		void Socket::Listen(int nMax)
		{
			if( 0 != ::listen(socket_, nMax) )
				throw Win32Exception("listen");
		}

		SocketPtr Socket::Accept()
		{
			return EndAccept(BeginAccept());
		}

		void Socket::Connect(const IPAddress &addr, u_short uPort)
		{
			EndConnect(BeginConnect(addr, uPort));
		}

		void Socket::DisConnect(bool bReuseSocket /* = false */)
		{
			EndDisconnect(BeginDisconnect(bReuseSocket));
		}


		size_t Socket::Recv(const SocketBufferPtr &buf)
		{
			return EndRecv(BeginRecv(buf, 0, buf->allocSize()));
		}

		size_t Socket::Send(const SocketBufferPtr &buf)
		{
			return EndSend(BeginSend(buf, 0, buf->size()));
		}


		size_t Socket::_EndAsyncOperation(const AsyncResultPtr &asyncResult)
		{
			DWORD size = 0;

			if( 0 == ::GetOverlappedResult((HANDLE)socket_, asyncResult.Get(), &size, TRUE) )
				throw Win32Exception("GetOverlappedResult");

			return size;
		}

		AsyncResultPtr Socket::BeginAccept(AsyncCallbackFunc callback /* = 0 */, const ObjectPtr &asyncState/* = nothing*/)
		{
			SocketBufferPtr acceptBuffer(new SocketBuffer((sizeof(sockaddr_in) + 16) * 2));
			SocketPtr acceptSocket(new Socket(io_));
			AsyncResultPtr asyncResult(new AsyncResult(this, acceptBuffer, asyncState, acceptSocket, callback));
			asyncResult->AddRef();

			// 不需要接收远程客户机第一块数据，故设置为0
			if( !SocketProvider::GetSingleton(io_).AcceptEx(socket_, acceptSocket->socket_, acceptBuffer->data(), 0,
				sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, 0, asyncResult.Get()) 
				&& ::WSAGetLastError() != ERROR_IO_PENDING )
			{
				asyncResult->Release();

				throw Win32Exception("AcceptEx");
			}

			return asyncResult;
		}

		SocketPtr Socket::EndAccept(const AsyncResultPtr &asynResult)
		{
			_EndAsyncOperation(asynResult);
			return asynResult->m_internalState;
		}


		// 异步调用
		AsyncResultPtr Socket::BeginConnect(const IPAddress &addr, u_short uPort, AsyncCallbackFunc callback /* = NULL */, const ObjectPtr &asyncState /* = nothing */)
		{
			AsyncResultPtr asynResult(new AsyncResult(this, nothing, asyncState, nothing, callback));
			asynResult->AddRef();

			sockaddr_in remoteAddr = {0};
			remoteAddr.sin_family		= AF_INET;
			remoteAddr.sin_port			= ::htons(uPort);
			remoteAddr.sin_addr.s_addr	= addr.Address();

			// 很变态，需要先bind
			::bind(socket_, reinterpret_cast<const sockaddr *>(&remoteAddr), sizeof(sockaddr_in));

			if( !SocketProvider::GetSingleton(io_).ConnectEx(socket_, reinterpret_cast<SOCKADDR *>(&remoteAddr), sizeof(SOCKADDR), 0, 0, 0, asynResult.Get()) 
				&& ::WSAGetLastError() != WSA_IO_PENDING )
			{
				asynResult->Release();
				throw Win32Exception("ConnectionEx");
			}

			return asynResult;
		}

		void Socket::EndConnect(const AsyncResultPtr &asyncResult)
		{
			_EndAsyncOperation(asyncResult);
		}


		AsyncResultPtr Socket::BeginDisconnect(bool bReuseSocket /* = true */, AsyncCallbackFunc callback /* = NULL */, const ObjectPtr &asyncState /* = nothing */)
		{
			AsyncResultPtr asynResult(new AsyncResult(this, nothing, asyncState, nothing, callback));
			asynResult->AddRef();

			DWORD dwFlags = bReuseSocket ? TF_REUSE_SOCKET : 0;

			if( !SocketProvider::GetSingleton(io_).DisconnectEx(socket_, asynResult.Get(), dwFlags, 0) 
				&& ::WSAGetLastError() != WSA_IO_PENDING )
			{
				asynResult->Release();
				throw Win32Exception("DisConnectionEx");
			}

			return asynResult;
		}

		void Socket::EndDisconnect(const AsyncResultPtr &asyncResult)
		{
			_EndAsyncOperation(asyncResult);
		}


		AsyncResultPtr Socket::BeginRecv(const SocketBufferPtr &buf, size_t nOffset, size_t nSize, AsyncCallbackFunc callback /* = NULL */, const ObjectPtr &asyncState /* = nothing */, const ObjectPtr &internalState /*= nothing*/)
		{
			AsyncResultPtr asynResult(new AsyncResult(this, buf, asyncState, internalState, callback));
			asynResult->AddRef();


			WSABUF wsabuf = {0};
			wsabuf.buf = reinterpret_cast<char *>(buf->data(nOffset));
			wsabuf.len = nSize;

			DWORD dwFlag = 0;
			if(  0 != ::WSARecv(socket_, &wsabuf, 1, NULL, &dwFlag, asynResult.Get(), NULL)
				&& ::WSAGetLastError() != WSA_IO_PENDING )
			{
				asynResult->Release();
				throw Win32Exception("WSARecv");
			}

			return asynResult;
		}

		size_t Socket::EndRecv(const AsyncResultPtr &asyncResult)
		{
			return _EndAsyncOperation(asyncResult);
		}


		AsyncResultPtr Socket::BeginSend(const SocketBufferPtr &buf, size_t nOffset, size_t nSize, AsyncCallbackFunc callback /* = NULL */, const ObjectPtr &asyncState /* = nothing */, const ObjectPtr &internalState /*= nothing*/)
		{
			AsyncResultPtr asynResult(new AsyncResult(this, buf, asyncState, internalState, callback));
			asynResult->AddRef();


			WSABUF wsabuf = {0};
			wsabuf.buf = reinterpret_cast<char *>(buf->data(nOffset));
			wsabuf.len = nSize;

			DWORD dwFlag = 0;
			if(  0 != ::WSASend(socket_, &wsabuf, 1, NULL, dwFlag, asynResult.Get(), NULL)
				&& ::WSAGetLastError() != WSA_IO_PENDING )
			{
				asynResult->Release();
				throw Win32Exception("WSASend");
			}

			return asynResult;
		}

		size_t Socket::EndSend(const AsyncResultPtr &asyncResult)
		{
			return _EndAsyncOperation(asyncResult);
		}
	}

}