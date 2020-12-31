// InetFunc.cpp: implementation of the CInetFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InetFunc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0

#define ICMP_MIN 8 // minimum 8 byte icmp packet (just header)

/* The IP header */
typedef struct iphdr 
{
	unsigned int h_len:4;          // length of the header
	unsigned int version:4;        // Version of IP
	unsigned char tos;             // Type of service
	unsigned short total_len;      // total length of the packet
	unsigned short ident;          // unique identifier
	unsigned short frag_and_flags; // flags
	unsigned char  ttl; 
	unsigned char proto;           // protocol (TCP, UDP etc)
	unsigned short checksum;       // IP checksum

	unsigned int sourceIP;
	unsigned int destIP;

}IpHeader;

//
// ICMP header
//
typedef struct _ihdr 
{
  BYTE i_type;
  BYTE i_code; /* type sub code */
  USHORT i_cksum;
  USHORT i_id;
  USHORT i_seq;
  /* This is not the std header, but we reserve space for time */
  ULONG timestamp;
}IcmpHeader;

#define STATUS_FAILED 0xFFFF
#define DEF_PACKET_SIZE 32
#define MAX_PACKET 1024//65536

#define xmalloc(s) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(s))
#define xfree(p)   HeapFree (GetProcessHeap(),0,(p))

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInetFunc::CInetFunc()
{
	seq_no = 0;
}

CInetFunc::~CInetFunc()
{

}

CString CInetFunc::ResolveIPToHost(CString strIP)
{
	CString	strRet = _T("");
	//Task 1:	Given IP Address i.e. "111.111.111.111",
	//	Return Network byte ordered address (ulIP)	
	unsigned long ulIP;
	struct hostent	*hHost;
	struct sockaddr_in	*sin;

	ulIP = inet_addr(strIP);
	
	sin->sin_family = AF_INET;
	sin->sin_addr.S_un.S_addr = ulIP;
	hHost = gethostbyaddr((char*)&sin->sin_addr, 4, PF_INET);
	if(hHost != NULL)
	{
		strRet = hHost->h_name;
		return strRet;
	}
	else
	{
		strRet.Format("Can't resolve %s", strIP);
	}
	return strRet;

}

CString CInetFunc::ResolveHostToIP(CString strHost)
{
	CString strRet = _T("");
	unsigned long ulIP;	
	hostent* phostent;	
	LPSTR szAddr;	
	struct in_addr inetAddr;

	phostent = gethostbyname(strHost);	
	if (phostent == NULL)
	{
		strRet.Format("Can't resolve %s", strHost);
		return strRet;
	}
	ulIP = *(DWORD*)(*phostent->h_addr_list);
	inetAddr.s_addr = ulIP;
	szAddr = inet_ntoa(inetAddr);	
	strRet = szAddr;
	return strRet;
}

CString CInetFunc::Ping(CString strHost, UINT nPacketSize)
{
	CString				strRet = _T("");
	SOCKET				sockRaw;
	struct sockaddr_in	dest,from;
	struct hostent		*hp;
	int					bread,datasize;
	int					fromlen = sizeof(from);
	int					timeout = 10;
	char				*dest_ip;
	char				*icmp_data;
	char				*recvbuf;
	unsigned int		addr=0;
	int					bwrote;

	CString	strError = _T("");

	sockRaw = WSASocket(AF_INET,
					   SOCK_RAW,
					   IPPROTO_ICMP,
					   NULL, 0,0);
  
	if (sockRaw == INVALID_SOCKET) 
	{
		strError.Format("WSASocket() failed: %d",WSAGetLastError());
		AfxMessageBox(strError);
		return strError;
	}
	bread = setsockopt(sockRaw,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,
  					sizeof(timeout));
	if(bread == SOCKET_ERROR) 
	{
  		strError.Format("failed to set recv timeout: %d",WSAGetLastError());
		AfxMessageBox(strError);
		return strError;
	}
	
//	timeout = 1000;
	/*bread*/bwrote = setsockopt(sockRaw,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,
  					sizeof(timeout));
	if(/*bread*/bwrote == SOCKET_ERROR) 
	{
  		strError.Format("failed to set send timeout: %d",WSAGetLastError());
		AfxMessageBox(strError);
		return strError;
	}
	memset(&dest,0,sizeof(dest));

	hp = gethostbyname(strHost);
	
	if (!hp)
	{
		addr = inet_addr(strHost);
	}
	if ((!hp)  && (addr == INADDR_NONE) ) 
	{
		strError.Format("Unable to resolve %s",strHost);
		AfxMessageBox(strError);
		return strError;
	}
	
	if (hp != NULL)
	  memcpy(&(dest.sin_addr),hp->h_addr,hp->h_length);
	else
  		dest.sin_addr.s_addr = addr;

	if (hp)
		dest.sin_family = hp->h_addrtype;
	else
		dest.sin_family = AF_INET;

	dest_ip = inet_ntoa(dest.sin_addr);

	if (nPacketSize > 0) 
	{
		datasize = nPacketSize;
		if (datasize == 0)
			datasize = DEF_PACKET_SIZE;
	}
	else
	  datasize = DEF_PACKET_SIZE;
	
	datasize += sizeof(IcmpHeader);  

	icmp_data = (char*)xmalloc(MAX_PACKET);
	recvbuf = (char*)xmalloc(MAX_PACKET);
	
	if (!icmp_data) 
	{
		strError.Format("HeapAlloc failed %d",GetLastError());
		AfxMessageBox(strError);
		return strError;
	}
	
	memset(icmp_data,0,MAX_PACKET);
	Fill_Icmp_Data(icmp_data,datasize);

	//int bwrote;

	((IcmpHeader*)icmp_data)->i_cksum = 0;
	((IcmpHeader*)icmp_data)->timestamp = GetTickCount();

	((IcmpHeader*)icmp_data)->i_seq = seq_no++;
	((IcmpHeader*)icmp_data)->i_cksum = Checksum((USHORT*)icmp_data, 
										datasize);

	bwrote = sendto(sockRaw,icmp_data,datasize,0,(struct sockaddr*)&dest,
				sizeof(dest));
	if (bwrote == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT) 
		{
	  		strRet = "timed out";
			return strRet;
		}
		strError.Format("sendto failed: %d",WSAGetLastError());
		AfxMessageBox(strError);
		return strError;
	}
	if (bwrote < datasize ) 
	{
		strRet.Format("Wrote %d bytes",bwrote);
	}
	bread = recvfrom(sockRaw,recvbuf,MAX_PACKET,0,(struct sockaddr*)&from,
			         &fromlen);
	if (bread == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT) 
		{
	  		strRet = "timed out";
			return strRet;
		}
		strError.Format("recvfrom failed: %d",WSAGetLastError());
		AfxMessageBox(strError);
		return strError;
	}
	strRet = Decode_Resp(recvbuf,bread,&from);
	Sleep(500);
	xfree(icmp_data);
	xfree(recvbuf);
	closesocket(sockRaw);
	return strRet;

}

void CInetFunc::Fill_Icmp_Data(char * icmp_data, int datasize)
{
	IcmpHeader *icmp_hdr;
	char *datapart;

	icmp_hdr = (IcmpHeader*)icmp_data;

	icmp_hdr->i_type = ICMP_ECHO;
	icmp_hdr->i_code = 0;
	icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum = 0;
	icmp_hdr->i_seq = 0;
  
	datapart = icmp_data + sizeof(IcmpHeader);
	  //
	  // Place some junk in the buffer.
	  //
	memset(datapart,'E', datasize - sizeof(IcmpHeader));
}

USHORT CInetFunc::Checksum(USHORT * buffer, int size)
{
	unsigned long cksum=0;

	while(size >1) 
	{
		cksum+=*buffer++;
		size -=sizeof(USHORT);
	}
  
	if(size ) 
	{
		cksum += *(UCHAR*)buffer;
	}

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >>16);
	return (USHORT)(~cksum);
}

CString CInetFunc::Decode_Resp(char * buf, int bytes, struct sockaddr_in * from)
{
	IpHeader *iphdr;
	IcmpHeader *icmphdr;
	unsigned short iphdrlen;
	CString strRet = _T("");

	iphdr = (IpHeader *)buf;

	iphdrlen = iphdr->h_len * 4 ; // number of 32-bit words *4 = bytes

	if (bytes  < iphdrlen + ICMP_MIN) 
	{
		strRet.Format("Too few bytes from %s",inet_ntoa(from->sin_addr));
	}

	icmphdr = (IcmpHeader*)(buf + iphdrlen);

	if (icmphdr->i_type != ICMP_ECHOREPLY) 
	{
		strRet.Format("non-echo type %d recvd",icmphdr->i_type);
		return strRet;
	}
	if (icmphdr->i_id != (USHORT)GetCurrentProcessId()) 
	{
		strRet.Format("someone else's packet!");
		return strRet;
	}
	strRet.Format("%d bytes from %s: icmp_seq = %d.  time: %d ms",
		bytes, inet_ntoa(from->sin_addr),
		icmphdr->i_seq,
		GetTickCount()-icmphdr->timestamp);
	return strRet;

}

BOOL CInetFunc::ScanPorts(CString strHostOrIP, LIVE_PORTS *pPorts, UINT nPort)
{
	struct servent		*pServent;
	struct sockaddr_in	sa_in;
	struct hostent		*pHostEnt;
	int					sock;
	CString				strError;
	
	if(strHostOrIP == "")
		return FALSE;
	// resolve host name.
	pHostEnt = gethostbyname(strHostOrIP);
	if(pHostEnt == NULL)
		return FALSE;

	sa_in.sin_family = AF_INET;
	sa_in.sin_port = htons(nPort);
	memcpy(&(sa_in.sin_addr.s_addr), pHostEnt->h_addr, sizeof(int));

	sock = socket(AF_INET, SOCK_STREAM, 6);
	if(sock == 0)
		return FALSE;
	// check for available ports:
	if((pServent = getservbyport(htons(nPort), NULL)) != (struct servent *)NULL)
	{
		// existing port.

	}
	if(connect(sock, (struct sockaddr *)&sa_in, sizeof(sa_in)))
	{
		strError = InterpretError(WSAGetLastError());
		return FALSE;
	}
	else
	{
		
		if(pServent)
		{
			pPorts->strName = pServent->s_name;
			//pPorts->strAliases = pServent->s_aliases;
			pPorts->s_port = nPort;
			pPorts->strProto = pServent->s_proto;
		}
		else
		{
			pPorts->strName = "Unknown";
			//pPorts->strAliases = pServent->s_aliases;
			pPorts->s_port = nPort;
			pPorts->strProto = "Unknown";
		}
	}

	closesocket(sock);
	return TRUE;
}

CString CInetFunc::InterpretError(UINT nErrCode)
{
	CString	strRet = _T("");
	switch(nErrCode)
	{
	case WSANOTINITIALISED: 
		strRet = "A successful WSAStartup must occur before using this function.";
		break;
	case WSAENETDOWN :
		strRet = "The network subsystem has failed. ";
		break;
	case WSAEADDRINUSE :
		strRet = "The specified address is already in use. ";
		break;
	case WSAEINTR:
		strRet = "The (blocking) call was canceled through WSACancelBlockingCall. ";
		break;
	case WSAEINPROGRESS :
		strRet = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function. ";
		break;
	case WSAEALREADY :
		strRet = "A nonblocking connect call is in progress on the specified socket. ";
		break;
	case WSAEADDRNOTAVAIL :
		strRet = "The specified address is not available from the local machine. ";
		break;
	case WSAEAFNOSUPPORT :
		strRet = "Addresses in the specified family cannot be used with this socket. ";
		break; 
	case WSAECONNREFUSED :
		strRet = "The attempt to connect was forcefully rejected. ";
		break;
	case WSAEFAULT :
		strRet = "The name or the namelen parameter is not a valid part of the user address space, the namelen parameter is too small, or the name parameter contains incorrect address format for the associated address family. ";
		break;
	case WSAEINVAL :
		strRet = "The parameter s is a listening socket, or the destination address specified is not consistent with that of the constrained group the socket belongs to. ";
		break;
	case WSAEISCONN :
		strRet = "The socket is already connected (connection-oriented sockets only). ";
		break;
	case WSAENETUNREACH :
		strRet = "The network cannot be reached from this host at this time. ";
		break;
	case WSAENOBUFS :
		strRet = "No buffer space is available. The socket cannot be connected. ";
		break;
	case WSAENOTSOCK :
		strRet = "The descriptor is not a socket. ";
		break;
	case WSAETIMEDOUT :
		strRet = "Attempt to connect timed out without establishing a connection. ";
		break;
	case WSAEWOULDBLOCK :
		strRet = "The socket is marked as nonblocking and the connection cannot be completed immediately. Use select to determine the completion of the connection request by checking to see if the socket is writable. ";
		break;
	case WSAEACCES :
		strRet = "Attempt to connect datagram socket to broadcast address failed because setsockopt option SO_BROADCAST is not enabled. ";
		break;
	default:
		strRet = "Undefined";
	}
	return strRet;
}

CString CInetFunc::GetRemoteTime(CString strHost)
{
	time_t		t;
	int			sock;
	struct sockaddr_in a;
	struct hostent *h;
	CString strRet;

	h = gethostbyname(strHost);
	if(h == NULL)
	{
		strRet = "Cannot resolve";
		return strRet;
	}

	a.sin_family = AF_INET;
	a.sin_port = htons(37);
	memcpy(&(a.sin_addr.s_addr), h->h_addr, sizeof(int));
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock == 0)
	{
		strRet = "Cannot establish connection";
		return strRet;
	}
	if(connect(sock, (struct sockaddr *)&a, sizeof(a)))
	{
		strRet = "Cannot establish connection";
		closesocket(sock);
		return strRet;
	}
	if(recv(sock, (char *)&t, 4, 0) != 4)
	{
		strRet = "Unable to get time";
		closesocket(sock);
	}
	else
	{
		t = ntohl(t) - 2208988800;
		strRet.Format("%s", asctime(gmtime(&t)));
	}
	closesocket(sock);
	return strRet;
}

