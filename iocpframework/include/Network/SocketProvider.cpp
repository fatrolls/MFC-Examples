#include "stdafx.h"
#include "SocketProvider.hpp"


#include "../IOCP/WinException.hpp"



#include "Socket.hpp"




namespace async
{



	namespace network
	{

		SocketProvider::SocketProvider(IODispatcher &io)
		{
			static GUID guidTransmitFile		= WSAID_TRANSMITFILE;
			static GUID guidAcceptEx			= WSAID_ACCEPTEX;
			static GUID guidGetAcceptExSockaddrs= WSAID_GETACCEPTEXSOCKADDRS;
			static GUID guidTransmitPackets		= WSAID_TRANSMITPACKETS;
			static GUID guidConnectEx			= WSAID_CONNECTEX;
			static GUID guidDisconnectEx		= WSAID_DISCONNECTEX;
			static GUID guidWSARecvMsg			= WSAID_WSARECVMSG;

			SocketPtr socket(new Socket(io));
			GetExtensionFuncPtr(socket, &guidTransmitFile,			&TransmitFile);
			GetExtensionFuncPtr(socket, &guidAcceptEx,				&AcceptEx);
			GetExtensionFuncPtr(socket, &guidGetAcceptExSockaddrs,	&GetAcceptExSockaddrs);
			GetExtensionFuncPtr(socket, &guidTransmitPackets,		&TransmitPackets);
			GetExtensionFuncPtr(socket, &guidConnectEx,				&ConnectEx);
			GetExtensionFuncPtr(socket, &guidDisconnectEx,			&DisconnectEx);
			GetExtensionFuncPtr(socket, &guidWSARecvMsg,			&WSARecvMsg);
		}

		SocketProvider::~SocketProvider()
		{
		}


		void SocketProvider::GetExtensionFuncPtr(const SocketPtr &sock, GUID *guid, LPVOID pFunc)
		{
			SocketBufferPtr inBuf(new SocketBuffer(sizeof(GUID)));
			SocketBufferPtr outBuf(new SocketBuffer(sizeof(void *)));

			RtlMoveMemory(inBuf->data(), guid, sizeof(GUID));

			sock->IOControl(SIO_GET_EXTENSION_FUNCTION_POINTER, inBuf, outBuf);
			RtlMoveMemory(pFunc, outBuf->data(), sizeof(void *));
		}
	}

}