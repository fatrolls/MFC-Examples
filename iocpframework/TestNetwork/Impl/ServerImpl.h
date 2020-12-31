#ifndef __SERVICE_HPP
#define __SERVICE_HPP

#include <array>

#include "../../include/network/Socket.hpp"


using namespace async::network;


class Session
	: public std::tr1::enable_shared_from_this<Session>
{
private:
	SocketPtr socket_;
	SocketBufferPtr data_;

public:
	Session(const SocketPtr &sock)
		: socket_(sock)
		, data_(new SocketBuffer)
	{
	}
	~Session()
	{
		Stop();
	}
	SocketPtr& GetSocket()
	{
		return socket_;
	}

	void Start()
	{
		try
		{		
			socket_->BeginRecv(data_, 0, data_->allocSize(), std::tr1::bind(&Session::_HandleRead, shared_from_this(), std::tr1::placeholders::_1));
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	void Stop()
	{
		socket_->Close();
	}

private:
	void _HandleRead(const AsyncResultPtr &asyncResult)
	{
		try
		{
			size_t bytes = socket_->EndRecv(asyncResult);
			if( bytes == 0 )
			{
				socket_->BeginDisconnect(true, std::tr1::bind(&Session::_DisConnect, shared_from_this(), std::tr1::placeholders::_1));
				return;
			}

			data_->resize(bytes);
			socket_->BeginSend(data_, 0, data_->size(), std::tr1::bind(&Session::_HandleWrite, shared_from_this(), std::tr1::placeholders::_1));
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	void _HandleWrite(const AsyncResultPtr &asyncResult)
	{
		Start();
	}

	void _DisConnect(const AsyncResultPtr &asyncResult)
	{
		Stop();
	}
};

typedef std::tr1::shared_ptr<Session> SessionPtr;


class Server
{
private:
	IODispatcher &io_;
	SocketPtr acceptor_;

public:
	Server(IODispatcher &io, short port)
		: io_(io)
		, acceptor_(new Socket(io_))
	{
		acceptor_->Bind(port);
		acceptor_->Listen();
	}

	~Server()
	{
		_StopServer();
	}

public:
	void Start()
	{
		_StartAccept();
	}

	void Stop()
	{
		_StopServer();
	}

private:
	void _StartAccept()
	{		
		try
		{
			acceptor_->BeginAccept(std::tr1::bind(&Server::_OnAccept, this, std::tr1::placeholders::_1));
		} 
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	void _StopServer()
	{
		acceptor_->Close();
	}

private:
	void _OnAccept(const AsyncResultPtr &asyncResult)
	{
		try
		{
			if( *acceptor_ == INVALID_SOCKET )
				return;

			SocketPtr acceptSocket = acceptor_->EndAccept(asyncResult);

			SessionPtr session_(new Session(acceptSocket));
			session_->Start();

			_StartAccept();
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
};



#endif