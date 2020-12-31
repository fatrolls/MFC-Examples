///////////////////////////////////////////////////////////////////
// Header File RawSocket.h
// class CWizSyncSocket & CWizReadWriteSocket
//
// 23/07/1996 14:54                             Author: Poul A. Costinsky
///////////////////////////////////////////////////////////////////

#ifndef __CWizRawSocket_H
#define __CWizRawSocket_H

/////////////////////////////////////////////////////////////////////////////
// class CWizSyncSocket
// Simple encapsulation of the SOCKET handle and 
// simple operations with it.
class CWizSyncSocket
{
public:
	// Exception class if createsocket fails in constructor 
	struct XCannotCreate {};
	// Constructors
	CWizSyncSocket(int nPort);	// Connects for listening 
								// on the port nPort
	CWizSyncSocket(SOCKET h = INVALID_SOCKET); // incapsulates 
								// ready socket handle
	// Destructor
	~CWizSyncSocket();

	BOOL	Create(int nPort);	// Creates listening socket
	void	Close();			// Closes socket
	SOCKET	Accept();			// waits to accept connection
								// and returns a descriptor 
								// for the accepted packet
	BOOL	Connect(LPCTSTR lpszHostAddress, UINT nHostPort );
								// establishes a connection to a peer
	SOCKET	H() const { return m_hSocket; }
								// returns a handle of the socket
	BOOL GetHostName(LPTSTR lpszAddress, size_t nAddrSize, UINT& rSocketPort);
	BOOL GetPeerName(LPTSTR lpszAddress, size_t nAddrSize, UINT& rPeerPort);

protected:
	void Init(SOCKET h);		// initialize data members
	BOOL InitializeSocket(int nPort); 
								// associates a local address 
								// with a socket and establishes
								// a socket to listen for incoming connection
	int	 SetIntOption(int level, int optname, int val);
								// sets a socket option
	SOCKET	m_hSocket;			// socket handle
};

/////////////////////////////////////////////////////////////////////////////
// class CWizReadWriteSocket
// Class provides synchronous I/O for the socket
class CWizReadWriteSocket : public CWizSyncSocket
{	
	public:
		struct X {};
		struct XRead	: public X {};
		struct XWrite	: public X {};
	public:
		// constructor usually receives a handle from Accept
		CWizReadWriteSocket(SOCKET h = INVALID_SOCKET)
			: CWizSyncSocket(h) {}

		// Read/write any data. Both functions return 
		// an actual number of bytes read/written,
		// accept pointer to data and number of bytes.
		int	Read(void *pData, int nLen); 
		int	Write(const void *pData, int nLen); 
		// Read/write strings. nLen is in characters,
		// not bytes.
		BOOL ReadString  (char*  lpszString, int nLen);
		BOOL ReadString  (WCHAR* lpszString, int nLen);
		// If nLen == -1, the actual length is calculated
		// assuming lpszString is zero-terminated.
		BOOL WriteString (const char* lpszString, int nLen = -1);
		BOOL WriteString (const WCHAR* lpszString, int nLen = -1);
};

/////////////////////////////////////////////////////////////////////////////
template<class T>
BOOL	RawRead(CWizReadWriteSocket& rSocket, T& data)
{
	return (rSocket.Read (&data, sizeof(T)) == sizeof(T));
}

template<class T>
BOOL	RawWrite(CWizReadWriteSocket& rSocket, const T& data)
{
	return (rSocket.Write (&data, sizeof(T)) == sizeof(T));
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
void	RawReadX(CWizReadWriteSocket& rSocket, T& data)
{
	if (!RawRead(rSocket, data))
		throw CWizReadWriteSocket::XRead();
}

template<class T>
void	RawWriteX(CWizReadWriteSocket& rSocket, const T& data)
{
	if (!RawWrite(rSocket, data))
		throw CWizReadWriteSocket::XWrite();
}

/////////////////////////////////////////////////////////////////////////////

inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, int& i)
{
	int ni;
	RawReadX(rSocket, ni);
	i = ntohl(ni);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, int i)
{
	int ni = htonl(i);
	RawWriteX(rSocket, ni);
	return rSocket;
}

/////////////////////////////////////////////////////////////////////////////
inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, char& i)
{
	RawReadX(rSocket, i);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, char i)
{
	RawWriteX(rSocket, i);
	return rSocket;
}

/////////////////////////////////////////////////////////////////////////////
inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, short& i)
{
	short ni;
	RawReadX(rSocket, ni);
	i = ntohs(ni);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, short i)
{
	short ni = htons(i);
	RawWriteX(rSocket, ni);
	return rSocket;
}
/////////////////////////////////////////////////////////////////////////////
inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, double& d)
{
	const int MAX_CHAR = 30;
	char buffer[MAX_CHAR];

	if(!rSocket.ReadString(buffer,MAX_CHAR))
		throw CWizReadWriteSocket::XRead();
	
	d = atof(buffer);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, double d)
{
	int     decimal,   sign;   
	char    *buffer;   
	int     precision = 10;
	buffer = _ecvt( d, precision, &decimal, &sign );	
	if (NULL == buffer || 0 == *buffer)
		buffer = "0";

	if(!rSocket.WriteString(buffer))
		throw CWizReadWriteSocket::XWrite();

	return rSocket;
}

/////////////////////////////////////////////////////////////////////////////
inline CWizReadWriteSocket& operator>>(CWizReadWriteSocket& rSocket, u_long& ul)
{
	u_long l;

	RawReadX(rSocket, l);
	ul = ntohl(l);
	return rSocket;
}

inline CWizReadWriteSocket& operator<<(CWizReadWriteSocket& rSocket, u_long ul)
{
	const u_long l = htonl(ul);
	RawWriteX(rSocket, l);
	return rSocket;
}

/////////////////////////////////////////////////////////////////////////////
#endif // __CWizRawSocket_H


