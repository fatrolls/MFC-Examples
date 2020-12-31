// InetFunc.h: interface for the CInetFunc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INETFUNC_H__AD824F56_B618_11D1_B18B_006008085F93__INCLUDED_)
#define AFX_INETFUNC_H__AD824F56_B618_11D1_B18B_006008085F93__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

typedef struct tagLIVE_PORTS
{
	CString		strName;    
	CString		strAliases;    
	short       s_port;
    CString     strProto;
}LIVE_PORTS;

class CInetFunc  
{
public:
	CString GetRemoteTime(CString strHost);
	BOOL ScanPorts(CString strHostOrIP, LIVE_PORTS *pPorts, UINT nPort);
	CString Ping(CString strHost, UINT nPacketSize);
	CString ResolveHostToIP(CString strHost);
	CString ResolveIPToHost(CString strIP);
	CInetFunc();
	virtual ~CInetFunc();

private:
	CString InterpretError(UINT nErrCode);
	USHORT seq_no;
	CString Decode_Resp(char * buf, int bytes, struct sockaddr_in * from);
	USHORT Checksum(USHORT * buffer, int size);
	void Fill_Icmp_Data(char * icmp_data, int datasize);
};

#endif // !defined(AFX_INETFUNC_H__AD824F56_B618_11D1_B18B_006008085F93__INCLUDED_)
