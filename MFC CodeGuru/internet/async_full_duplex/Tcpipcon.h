#ifndef _TCPIPCON_H_
#define _TCPIPCON_H_

#include "inout.h"
#include "winsock.h"
#include "afxsock.h"

class CTcpIpConnection : public CInOutConnection
{
	public:
		CTcpIpConnection();
		virtual ~CTcpIpConnection();

		virtual BOOL InitConnection(SOCKET inSocket, SOCKET outSocket);
		virtual void ResetConnection();
		virtual void SetTerminate();
		virtual void* cioReceiveMessage(int* Error, int* length);
		virtual BOOL cioSendMessage(void* msg, int msg_size);

				//sockets
		SOCKET GetInSocket(){return InSocket;};
		SOCKET GetOutSocket(){return OutSocket;};

		//client side of the connection
		virtual void* GetConnectionMessage(DWORD portNo, DWORD& length);
		virtual BOOL ConnectToServer(char* serverName, int port);
		virtual BOOL ConnectionMessageValid(void* msg, DWORD& length);
		//server side
		virtual DWORD GetConnectionPort(void* msg, DWORD length);

		//receive and send parts of the network connection - static for common purposes
		static BOOL SendNetworkMessage(SOCKET sock, void* msg, int length, DWORD msg_frame = CInOutConnection::DEFAULT_FRAME);
		static void* ReceiveNetworkMessage(SOCKET sock, DWORD& length, DWORD msg_frame = CInOutConnection::DEFAULT_FRAME);
		static BOOL ReceiveMsg(SOCKET sock, char* buf, int size);

		BOOL SendNetMessage(void* msg, int msg_size); //TCP/IP wrapper

		SOCKET InSocket, OutSocket;
		BOOL m_waitForReplyOnConnection;
};

#endif