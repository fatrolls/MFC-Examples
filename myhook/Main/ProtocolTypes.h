#ifndef __PROTOCOL_TYPES_H__
#define __PROTOCOL_TYPES_H__
//各种网络协议的头定义

class CProtocolHeader
{
	///////////////////////////////////////////////////////////////////////
	//
	// 函数名       : checksum
	// 功能描述     : 计算校验和
	// 参数         : USHORT* buff		要计算校验和的缓冲区
	// 参数         : int size			buff缓冲区的大小
	// 返回值       : USHORT			数据的校验和	
	//
	///////////////////////////////////////////////////////////////////////
protected:
	USHORT ComputeChecksum(USHORT* buff, int size) ;
};
USHORT checksum(USHORT* buff, int size) ;
//以太帧
//    目的MAC(6字节) | 源MAC(6字节) | 协议类型(2字节) | IP数据报(46---1500字节)
#define ETHERTYPE_IP 0x0800
#define ETHERTYPE_ARP 0x806
//以太帧头
typedef struct _ETHeader:public CProtocolHeader
{
	UCHAR destHost[6]; //目的机器的MAC地址
	UCHAR sourceHost[6];//源机器的MAC地址
	USHORT type;//数据的协议类型
	_ETHeader()
	{
		memset(destHost, 0, 6);
		memset(sourceHost, 0, 6);
		type = 0;
	}
	_ETHeader(UCHAR sourceMac[6], UCHAR destMac[6], USHORT uType)
	{
		memcpy(sourceHost, sourceMac, 6);
        memcpy(destHost, destMac, 6);
        type = htons(uType);
	}
} ETHeader, *PETHeader;
//ARP数据报格式
#define ARPHRD_ETHER 1
//ARP数据类型
#define ARPOP_REQUEST 1 //表示该ARP数据报是ARP请求
#define ARPOP_REPLY 2   //表示该ARP数据报是ARP响应
//ARP头
typedef struct _ARPHeader:public CProtocolHeader
{
   USHORT hrd;    //硬件地址空间， 为ARPHRD_ETHER
   USHORT eth_type;  //以太网类型 ETHERTYPE_IP
   UCHAR  maclen;    //MAC地址长度 6
   UCHAR  iplen;     //ip地址长度, 4
   USHORT opcode;    //操作代码， ARPOP_REQUEST， ARPOP_REPLY
   UCHAR  sourcemac[6];   //源MAC
   UCHAR  sourceip[4];    //源IP
   UCHAR  destmac[6];     //目的MAC
   UCHAR  destip[4];      //目的IP
} ARPHeader, *PARPHeader;
//IP报头
typedef struct _IPHeader:public CProtocolHeader
{
	UCHAR iphVerLen;   //版本号和头长度 各占4位
	UCHAR ipTOS;       //服务类型
	USHORT ipLength;   //封包总长度 包含IP头和数据
	USHORT ipID;       //封包标识， 唯一标识发送的每一个数据报
	USHORT  ipFlags;    //标志
	UCHAR  ipTTL;      //生存时间 就是TTL
	UCHAR  ipProtocol; //协议， 可能是TCP, UDP, ICMP ....
	USHORT ipChecksum; //校验和
	ULONG  ipSource;   //源IP地址
	ULONG  ipDestionation; //目的IP地址
	_IPHeader() {}
	_IPHeader(char* szSourceIP, char* szDestIP, int nProtocol, UINT nTTL, char* pMsg, int nMsgLen);
} IPHeader, *PIPHeader;
//TCP报头
#define TCP_FLAG_FIN 0x01
#define TCP_FLAG_SYN 0x02
#define TCP_FLAG_RST 0x04
#define TCP_FLAG_PUSH 0x08
#define TCP_FLAG_ACK 0x10
#define TCP_FLAG_URG 0x20
#define TCP_FLAG_ACE_0x40
#define TCP_FLAG_CWR 0x80

typedef struct _TCPHeader:public CProtocolHeader
{
    USHORT	sourcePort;			// 16位源端口号
	USHORT	destinationPort;	// 16位目的端口号
	ULONG	sequenceNumber;		// 32位序列号
	ULONG	acknowledgeNumber;	// 32位确认号
	UCHAR	dataoffset;			// 高4位表示数据偏移
	UCHAR	flags;				// 6位标志位
	                            //FIN - 0x01
	                            //SYN - 0x02
	                            //RST - 0x04 
	                            //PUSH- 0x08
	                            //ACK- 0x10
	                            //URG- 0x20
	                            //ACE- 0x40
	                            //CWR- 0x80
	USHORT	windows;			// 16位窗口大小
	USHORT	checksum;			// 16位校验和
	USHORT	urgentPointer;		// 16位紧急数据偏移量 
	_TCPHeader() {}
	_TCPHeader(PIPHeader pIpHdr, USHORT uSourcePort, USHORT uDestPort, ULONG uSequenceNumb, UCHAR flags, int windowsize = 512, char* pMsg = NULL, int nMsgLen = 0);
	/* 
	计算TCP伪头校验和。TCP校验和基于如下几个域：
	源IP地址
	目的IP地址
	8位0域
	8位协议域
	16位TCP长度
	TCP头
	TCP数据
	*/
	void ComputeTcpPseudoHeaderChecksum(IPHeader *pIphdr, _TCPHeader *pTcphdr, char *payload, int payloadlen);
	//组建TCP报文//不包含Ether header
	bool ComposeTcpPacket(char* szRetbuf, int& nBufLen, char* szSourceIP, char* szDestIP,  UINT nTTL, 
					  USHORT uSourcePort, USHORT uDestPort, ULONG uSequenceNumb, UCHAR flags,
					  int windowsize, char* pMsg, int nMsgLen);
	//组建TCP报文//包含Ether header
	bool ComposeTcpPacket2(char* szRetbuf, int& nBufLen, UCHAR sourMac[6], UCHAR destMac[6], char* szSourceIP, char* szDestIP, UINT nTTL, 
					  USHORT uSourcePort, USHORT uDestPort, ULONG uSequenceNumb, UCHAR flags,
					  int windowsize, char* pMsg, int nMsgLen);
} TCPHeader, *PTCPHeader;
//UDP报头
typedef struct _UDPHeader:public CProtocolHeader
{
	USHORT sourcePort;  //源端口号
    USHORT destinationPort; //目的端口号
	USHORT len;         //封包长度
	USHORT checksum;    //校验和
	_UDPHeader() {}
	_UDPHeader(_IPHeader* pIpHdr, USHORT uSourcePort, USHORT uDestPort, char* pMsg, int nMsgLen);
	/* 
	计算UDP伪头校验和。UDP校验和基于如下几个域：
	源IP地址
	目的IP地址
	8位0域
	8位协议域
	16位UDP长度
	16位源端口号
	16位目的端口号
	16位UDP封包长度
	16位UDP校验和（0）
	UDP净荷
	*/
	void ComputeUdpPseudoHeaderChecksum(_IPHeader *pIphdr, _UDPHeader *pUdphdr, char *payload, int payloadlen);
	//组建UDP报文//不包含Ether header
    bool ComposeUdpPacket(char* szRetbuf, int& nBufLen, char* szSourceIP, char* szDestIP, USHORT uSourcePort, USHORT uDestPort, UINT nTTL, char* pMsg, int nMsgLen);
	//组建UDP报文//包含Ether header
    bool ComposeUdpPacket2(char* szRetbuf, int& nBufLen, UCHAR sourMac[6], UCHAR destMac[6], char* szSourceIP, char* szDestIP, USHORT uSourcePort, USHORT uDestPort, UINT nTTL, char* pMsg, int nMsgLen);
} UDPHeader, *PUDPHeader;

#define ICMP_TYPE_ECHO_REPLY	0       //回显应答     code = 0
#define ICMP_TYPE_NET_NOT_AVAIABLE 3  //网络不可到达 code = 0
                                    //主机不可到达 code = 1
                                    //协议不可到达 code = 2
                                    //端口不可到达 code = 3
                                    //需要分割， 但设置了DF code = 4
                                    //源路由失败 code = 5
                                    //目标网络未知 code = 6
                                    //目标主机未知 code = 7
                                    //code = 8
                                    //目标网络被强行禁止 code = 9
                                    //目标主机被强行禁止 code = 10
                                    //因为TOS（服务器类型), 网络不可到达 code = 11
                                    //因为TOS, 主机不可到达 code = 12
                                    //由于过滤， 通讯被强行禁止 code = 13
                                    //主机越权 code = 14
                                    //优先权终止失效 code = 15
#define ICMP_TYPE_ERROR 4           // code = 0 源端被关闭
#define ICM_TYPE_ERROR_REDIRECT 5   //code =0  对网络重定向
                                    //code == 1对主机重定向
                                    //code = 2 对TOS和网络重定向
                                    //code = 3 对TOS和主机重定向
#define ICMP_TYPE_ECHO_REQUEST	8   //code = 0 请求回显
#define ICMP_TYPE_ROUTE_BROADCAST 9   //code = 0 路由通告
#define ICMP_TYPE_REQUEST_REQUEST 10 //路由请求 code = 0
#define ICMP_TYPE_ERROR_TIMEOUT   11 //code = 0 超时， 传输中TTL == 0
#define ICMP_TYPE_ERROR_BAD_PARAMETER 12 //code == 0 IP头错误
                                         // code = 1 缺少必要的选项

// ICMP Header - RFC 792
typedef struct _ICMPHeader:public CProtocolHeader
{
	UCHAR	Type;			// Type
	UCHAR	Code;			// Code
	USHORT	Checksum;		// Checksum
	USHORT	ID;				// Identification
	USHORT	Seq;			// Sequence
	ULONG	TimeStamp;			// Data

	_ICMPHeader() { }
	_ICMPHeader(UCHAR uType, UCHAR uCode, USHORT nID, USHORT nSequence, char* pMsg, int nMsgLen);
    void ComputeICMPPesudoChecksum(_ICMPHeader* pIcmpHdr, char* pMsg, int nMsgLen);
	bool ComposeIcmpPacket(char* szRetbuf, int& nBufLen, char* szSourceIP, char* szDestIP, UINT nTTL, UCHAR uType, UCHAR uCode, USHORT nID, USHORT nSequence, char* pMsg, int nMsgLen);
    bool ComposeIcmpPacket2(char* szRetbuf, int& nBufLen, UCHAR sourMac[6], UCHAR destMac[6], char* szSourceIP, char* szDestIP, UINT nTTL, UCHAR uType, UCHAR uCode, USHORT nID, USHORT nSequence, char* pMsg, int nMsgLen);
}ICMPHeader, *PICMPHeader;

#define REQ_DATASIZE 32

/*
// ICMP Echo Request
typedef struct _ECHOREQUEST
{
	ICMPHeader icmpHdr;
	DWORD	dwTime;
	char	cData[REQ_DATASIZE];
}ECHOREQUEST, *PECHOREQUEST;


// ICMP Echo Reply
typedef struct tagECHOREPLY
{
	IPHeader	ipHdr;
	ECHOREQUEST	echoRequest;
	char    cFiller[256];
}ECHOREPLY, *PECHOREPLY;
*/

// ICMP Echo Reply
typedef struct tagECHOREPLY
{
	IPHeader	ipHdr;
	ICMPHeader	echoRequest;
	char    cFiller[256];
}ECHOREPLY, *PECHOREPLY;

// 定义过滤规则的结构
typedef struct _IPFilterRule
{
    USHORT protocol;   //使用的协议
	ULONG sourceIP;    //源IP地址
	ULONG destIP;      //目的IP地址
	ULONG sourceMask;  //源地址屏蔽码
	ULONG destMask;    //目的地址屏蔽码
	USHORT sourcePort; //源端口号
	USHORT destPort;   //目的端口号
	BOOLEAN bDrop;        //是否丢弃改封包
} IPFilterRule, *PIPFilterRule;

// 过滤规则列表
typedef struct _FilterRuleList
{
    IPFilterRule ipf;
	_FilterRuleList* pNext;
} FilterRuleList, *PFilterRuleList;

struct MySockaddr_In : public sockaddr_in
{
    MySockaddr_In() { }
	MySockaddr_In(USHORT uPort, char* szIP)
	{
		sin_family = AF_INET;
		sin_port = htons(uPort);
		sin_addr.S_un.S_addr = inet_addr(szIP);
	}
	MySockaddr_In(USHORT uPort, ULONG dwIP = INADDR_ANY)
	{
        sin_family = AF_INET;
		sin_port = htons(uPort);
		sin_addr.S_un.S_addr = dwIP;
	}
};
// 自定义设备类型，在创建设备对象时使用
// 注意，自定义值的范围是32768-65535
#define FILE_DEVICE_MYHOOKDRV 0x006543

// 自定义的IO控制代码，用于区分不同的设备控制请求
// 注意，自定义值的范围是2048-4095
#define MYHOOKDRV_IOCTL_INDEX 0x830

#undef FILE_ALL_ACCESS 
#define FILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)
//
//
// 定义各种设备控制代码。分别是开始过滤、停止过滤、添加过滤规则、清除过滤规则
//
#define START_IP_HOOK   CTL_CODE(FILE_DEVICE_MYHOOKDRV, MYHOOKDRV_IOCTL_INDEX, METHOD_BUFFERED, FILE_ALL_ACCESS)
#define STOP_IP_HOOK    CTL_CODE(FILE_DEVICE_MYHOOKDRV, MYHOOKDRV_IOCTL_INDEX+1, METHOD_BUFFERED, FILE_ALL_ACCESS)
#define ADD_FILTER      CTL_CODE(FILE_DEVICE_MYHOOKDRV, MYHOOKDRV_IOCTL_INDEX+2, METHOD_BUFFERED, FILE_ALL_ACCESS)
#define CLEAR_FILTER    CTL_CODE(FILE_DEVICE_MYHOOKDRV, MYHOOKDRV_IOCTL_INDEX+3, METHOD_BUFFERED, FILE_ALL_ACCESS)

#define MAX_RULE_NUM 256

#endif