#include "stdafx.h"
#include "NetworkImpl.h"

#include <MSTcpIP.h>

//#include "Protocol.h"
#include"../include/network/SocketProvider.hpp"




// alterable IO
void WINAPI APCFunc(ULONG_PTR pParam)
{
	// do nothing
}


NetworkImpl::NetworkImpl(IODispatcher &io)
: io_(io)
, acceptor_(new Socket(io))
{
}

NetworkImpl::~NetworkImpl()
{
	Stop();
}

void NetworkImpl::Start(u_short uPort)
{
	try
	{
		// 将建监听socket
		if( *acceptor_ == INVALID_SOCKET )
			acceptor_->Create();
	
		acceptor_->Bind(uPort);
		acceptor_->Listen();

		// 创建Accept 线程
		acceptThread_.RegisterFunc(std::tr1::bind(&NetworkImpl::_ThreadAccept, this));
		acceptThread_.Start();

		//acceptor_->BeginAccept(std::tr1::bind(&NetworkImpl::OnAccept, this, std::tr1::placeholders::_1), acceptor_);
	} 
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}


void NetworkImpl::Stop()
{
	acceptor_->Close();

	// 可提醒IO，退出监听线程
	::QueueUserAPC(APCFunc, acceptThread_, NULL);
	acceptThread_.Stop();
}



void NetworkImpl::OnAccept(const AsyncResultPtr &asyncResult)
{
	try 
	{
		// 获取远程连接
		SocketPtr listenSocket = asyncResult->m_asynState;
		SocketPtr acceptSocket = listenSocket->EndAccept(asyncResult);
		
		// 获取提供的Buffer
		SocketBufferPtr addrBuffer = asyncResult->m_buffer;

		// 设置超时
		struct TCPKeepAlive
		{
			u_long onoff;
			u_long keepalivetime;
			u_long keepaliveinterval;				
		};

		TCPKeepAlive inKeepAlive = {0};
		DWORD dwInLen = sizeof(TCPKeepAlive);
		TCPKeepAlive outKeepAlive = {0};
		DWORD dwOutLen = sizeof(TCPKeepAlive);
		DWORD dwBytesReturn = 0;
		inKeepAlive.onoff = 1;
		inKeepAlive.keepalivetime = 30000;
		inKeepAlive.keepaliveinterval = 2000;	
		::WSAIoctl(acceptSocket->GetHandle(), SIO_KEEPALIVE_VALS, &inKeepAlive, dwInLen, 
			&outKeepAlive, dwOutLen, &dwBytesReturn, NULL, NULL);


		// 获取远程地址
		SOCKADDR_IN *pLocalAddr = NULL, *pRemoteAddr = NULL;
		int szLocalLen = 0, szRemoteLen = 0;

		SocketProvider::GetSingleton(io_).GetAcceptExSockaddrs(addrBuffer->data(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, 
			reinterpret_cast<SOCKADDR **>(&pLocalAddr), &szLocalLen, reinterpret_cast<SOCKADDR **>(&pRemoteAddr), &szRemoteLen);

		// 管理
		_AddRemote(acceptSocket, *pLocalAddr);

		// 投递新的接受请求
		SocketBufferPtr buffer(new SocketBuffer);
		acceptSocket->BeginRecv(buffer, 0, buffer->allocSize(),
			std::tr1::bind(&NetworkImpl::OnRecv, this, std::tr1::placeholders::_1), acceptSocket);
	} 
	catch(const std::exception &e) 
	{
		std::cerr << e.what() << std::endl;
	}

}


void NetworkImpl::OnRecv(const AsyncResultPtr &asyncResult)
{
	SocketPtr sock = asyncResult->m_asynState;

	try 
	{
		size_t size = sock->EndRecv(asyncResult);
		SocketBufferPtr buffer = asyncResult->m_buffer;

		buffer->resize(size);

		if( size == 0 )
		{
			_RemoveRemote(sock);
			return ;
		}

		// 返回已接收的数据
		sock->BeginSend(buffer, 0, size, std::tr1::bind(&NetworkImpl::OnSend, this, std::tr1::placeholders::_1), sock);

	}
	catch(const std::exception &e) 
	{
		std::cerr << e.what() << std::endl;
		_RemoveRemote(sock);
	}
}

void NetworkImpl::OnSend(const AsyncResultPtr &asyncResult)
{
	SocketPtr socket = asyncResult->m_asynState;

	try 
	{
		SocketBufferPtr buffer = asyncResult->m_buffer;
		size_t size = socket->EndSend(asyncResult);
		if( size != 0 )
		{
			socket->BeginRecv(buffer, 0, buffer->allocSize(),
				std::tr1::bind(&NetworkImpl::OnRecv, this, std::tr1::placeholders::_1), socket);
		}
		else 
		{
			_RemoveRemote(socket);
			return;
		}
	}
	catch(const std::exception &e) 
	{
		std::cerr << e.what() << std::endl;
		_RemoveRemote(socket);
	}
}


size_t NetworkImpl::GetClientSize() const
{
	LockType lock(mutex_);

	return remotes_.size();
}



void NetworkImpl::_AddRemote(const SocketPtr &remoteSock, const SOCKADDR_IN &remoteAddr)
{
	{
		LockType lock(mutex_);
		remotes_.insert(std::make_pair(remoteSock->GetHandle(), remoteAddr));
	}
}

void NetworkImpl::_RemoveRemote(const SocketPtr &remoteSock)
{
	try
	{	
		remoteSock->BeginDisconnect();
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	{
		LockType lock(mutex_);
		remotes_.erase(*remoteSock);
	}
}

//
//size_t NetworkImpl::_ParseProtocol(const SocketBufferPtr &buffer)
//{
//	if( buffer->size() >= sizeof(PackageHeader) )
//	{
//		CPackageHelper package(reinterpret_cast<char *>(buffer->data()), buffer->size());
//		if( package.GetHeader()->StartFlag != START_FLAG )
//			return 0;
//		else
//			return package.GetHeader()->Length;
//	}
//
//	return 0;
//}


DWORD NetworkImpl::_ThreadAccept()
{
	// 通过使用WSAEventSelect来判断是否有足够的AcceptEx，或者检测出一个非正常的客户请求
	HANDLE hAcceptEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	::WSAEventSelect(acceptor_->GetHandle(), hAcceptEvent, FD_ACCEPT);

	while(!acceptThread_.IsAborted())
	{	
		DWORD dwError = ::WaitForSingleObjectEx(hAcceptEvent, INFINITE, TRUE);
		if( dwError == WAIT_FAILED || dwError == WAIT_IO_COMPLETION )
			break;
		else if( dwError == WAIT_OBJECT_0 )
		{
			// 投递接收连接
			for(int i = 0; i != MAX_ACCEPT; ++i)
			{
				acceptor_->BeginAccept(std::tr1::bind(&NetworkImpl::OnAccept, this, std::tr1::placeholders::_1), acceptor_);
			}
		}
	}

	::CloseHandle(hAcceptEvent);

	return 0;
}