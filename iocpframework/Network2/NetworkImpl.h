#ifndef __NETWORK_IMPL_HPP
#define __NETWORK_IMPL_HPP


#include "../include/network/Socket.hpp"
#include "../include/MultiThread/Thread.hpp"


//#include <Comm/Allocator/ContainerAllocator.hpp>


using namespace async;
using namespace async::network;



class NetworkImpl
{
public:
	// 锁类型
	typedef async::thread::CAutoLock<async::thread::CAutoCriticalSection>	LockType;
	// 管理远程连接
	typedef std::map<SOCKET, SOCKADDR_IN/*, std::less<SOCKET>, ContainerAllocator<std::pair<SOCKET, SOCKADDR_IN>>*/>	ClientSockets;
	
	// 一次投递Accept个数
	enum { MAX_ACCEPT = 10 };

private:
	IODispatcher &io_;
	SocketPtr acceptor_;
	
	ClientSockets		remotes_;
	mutable async::thread::CAutoCriticalSection mutex_;

	// 投递Accept线程
	async::thread::ThreadImplEx acceptThread_;

public:
	explicit NetworkImpl(IODispatcher &io);
	~NetworkImpl();


public:
	void Start(u_short);
	void Stop();

	void OnAccept(const AsyncResultPtr &);
	void OnRecv(const AsyncResultPtr &);
	void OnSend(const AsyncResultPtr &);

	void Send(const SocketBufferPtr &);


	size_t GetClientSize() const;

private:
	DWORD _ThreadAccept();

	//size_t _ParseProtocol(const SocketBufferPtr &buffer);

	// 增加远程连接
	void _AddRemote(const SocketPtr &, const SOCKADDR_IN &);
	// 移除远程连接
	void _RemoveRemote(const SocketPtr &);

};


#endif