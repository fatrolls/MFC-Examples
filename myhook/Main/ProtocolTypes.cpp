#include "StdAfx.h"
#include "ProtocolTypes.h"
///////////////////////////////////////////////////////////////////////
//
// 函数名       : checksum
// 功能描述     : 计算校验和
// 参数         : USHORT* buff		要计算校验和的缓冲区
// 参数         : int size			buff缓冲区的大小
// 返回值       : USHORT			数据的校验和	
//
///////////////////////////////////////////////////////////////////////
USHORT CProtocolHeader::ComputeChecksum(USHORT* buff, int size) 
{
	unsigned long cksum = 0;
	while(size>1)
	{
		cksum += *buff++;
		size -= sizeof(USHORT);
	}
	// 是奇数
	if(size)
	{
		cksum += *(UCHAR*)buff;
	}
	// 将32位的chsum高16位和低16位相加，然后取反
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);			
	return (USHORT)(~cksum);
}
USHORT checksum(USHORT* buff, int size) 
{
    unsigned long cksum = 0;
	while(size>1)
	{
		cksum += *buff++;
		size -= sizeof(USHORT);
	}
	// 是奇数
	if(size)
	{
		cksum += *(UCHAR*)buff;
	}
	// 将32位的chsum高16位和低16位相加，然后取反
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);			
	return (USHORT)(~cksum);
}
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
void _UDPHeader::ComputeUdpPseudoHeaderChecksum(IPHeader *pIphdr, UDPHeader *pUdphdr, char *payload, int payloadlen)
{
	char buff[1024];
	char *ptr = buff;
	int chksumlen = 0;
	ULONG zero = 0;
	
	// 包含源IP地址和目的IP地址
	memcpy(ptr, &pIphdr->ipSource, sizeof(pIphdr->ipSource));
	ptr += sizeof(pIphdr->ipSource);
	chksumlen += sizeof(pIphdr->ipSource);

	memcpy(ptr, &pIphdr->ipDestionation, sizeof(pIphdr->ipDestionation));
	ptr += sizeof(pIphdr->ipDestionation);
	chksumlen += sizeof(pIphdr->ipDestionation);

	// 包含8位0域
	memcpy(ptr, &zero, 1);
	ptr += 1;
	chksumlen += 1;

	// 协议
	memcpy(ptr, &pIphdr->ipProtocol, sizeof(pIphdr->ipProtocol));
	ptr += sizeof(pIphdr->ipProtocol);
	chksumlen += sizeof(pIphdr->ipProtocol);

	// UDP长度
	memcpy(ptr, &pUdphdr->len, sizeof(pUdphdr->len));
	ptr += sizeof(pUdphdr->len);
	chksumlen += sizeof(pUdphdr->len);

	// UDP源端口号
	memcpy(ptr, &pUdphdr->sourcePort, sizeof(pUdphdr->sourcePort));
	ptr += sizeof(pUdphdr->sourcePort);
	chksumlen += sizeof(pUdphdr->sourcePort);

	// UDP目的端口号
	memcpy(ptr, &pUdphdr->destinationPort, sizeof(pUdphdr->destinationPort));
	ptr += sizeof(pUdphdr->destinationPort);
	chksumlen += sizeof(pUdphdr->destinationPort);

	// 又是UDP长度
	memcpy(ptr, &pUdphdr->len, sizeof(pUdphdr->len));
	ptr += sizeof(pUdphdr->len);
	chksumlen += sizeof(pUdphdr->len);

	// 16位的UDP校验和，置为0
	memcpy(ptr, &zero, sizeof(USHORT));
	ptr += sizeof(USHORT);
	chksumlen += sizeof(USHORT);

	// 净荷
	memcpy(ptr, payload, payloadlen);
	ptr += payloadlen;
	chksumlen += payloadlen;

	// 补齐到下一个16位边界
	for(int i=0; i<payloadlen%2; i++)
	{
		*ptr = 0;
		ptr++;
		chksumlen++;
	}
	// 计算这个校验和，将结果填充到UDP头
	pUdphdr->checksum = ComputeChecksum((USHORT*)buff, chksumlen);
}
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
void _TCPHeader::ComputeTcpPseudoHeaderChecksum(IPHeader *pIphdr, TCPHeader *pTcphdr, char *payload, int payloadlen)
{
	char buff[1024];
	char *ptr = buff;
	int chksumlen = 0;
	ULONG zero = 0;
	
		// 伪头
	// 包含源IP地址和目的IP地址
	memcpy(ptr, &pIphdr->ipSource, sizeof(pIphdr->ipSource));
	ptr += sizeof(pIphdr->ipSource);
	chksumlen += sizeof(pIphdr->ipSource);

	memcpy(ptr, &pIphdr->ipDestionation, sizeof(pIphdr->ipDestionation));
	ptr += sizeof(pIphdr->ipDestionation);
	chksumlen += sizeof(pIphdr->ipDestionation);

	// 包含8位0域
	memcpy(ptr, &zero, 1);
	ptr += 1;
	chksumlen += 1;

	// 协议
	memcpy(ptr, &pIphdr->ipProtocol, sizeof(pIphdr->ipProtocol));
	ptr += sizeof(pIphdr->ipProtocol);
	chksumlen += sizeof(pIphdr->ipProtocol);

	// TCP长度
	USHORT tcp_len = htons(sizeof(TCPHeader) + payloadlen);
	memcpy(ptr, &tcp_len, sizeof(tcp_len));
	ptr += sizeof(tcp_len);
	chksumlen += sizeof(tcp_len);

		// TCP头
	memcpy(ptr, pTcphdr, sizeof(TCPHeader));
	ptr += sizeof(TCPHeader);
	chksumlen += sizeof(TCPHeader);

		// 净荷
	memcpy(ptr, payload, payloadlen);
	ptr += payloadlen;
	chksumlen += payloadlen;

	// 补齐到下一个16位边界
	for(int i=0; i<payloadlen%2; i++)
	{
		*ptr = 0;
		ptr++;
		chksumlen++;
	}

	// 计算这个校验和，将结果填充到TCP头
	pTcphdr->checksum = ComputeChecksum((USHORT*)buff, chksumlen);
}


_IPHeader::_IPHeader(char* szSourceIP, char* szDestIP, int nProtocol, UINT nTTL, char* pMsg, int nMsgLen)
{
	iphVerLen = (4<<4 | (sizeof(IPHeader)/sizeof(ULONG)));
	ipLength = ::htons(sizeof(IPHeader) + sizeof(UDPHeader) + nMsgLen);
	ipTTL = nTTL;
	ipProtocol = nProtocol;
	ipSource = ::inet_addr(szSourceIP);
	ipDestionation = ::inet_addr(szDestIP);
	ipChecksum = 0;
	ipChecksum = ComputeChecksum((USHORT*)this, sizeof(IPHeader));
}

_TCPHeader::_TCPHeader(PIPHeader pIpHdr, USHORT uSourcePort, USHORT uDestPort, ULONG uSequenceNumb, UCHAR flags, int windowsize, char* pMsg, int nMsgLen)
{
	sourcePort = htons(uSourcePort);
	destinationPort = htons(uDestPort);
	sequenceNumber = htonl(uSequenceNumb);
	acknowledgeNumber = 0;
	dataoffset =  (sizeof(TCPHeader)/4<<4|0); 
    flags = flags;   // #define   TCP_SYN   0x02
	urgentPointer = 0;
	windows = htons(windowsize);
	checksum = 0;
	ComputeTcpPseudoHeaderChecksum(pIpHdr, this, pMsg, nMsgLen);
}

_UDPHeader::_UDPHeader(PIPHeader pIpHdr, USHORT uSourcePort, USHORT uDestPort, char* pMsg, int nMsgLen)
{
	sourcePort = htons(uSourcePort);
	destinationPort = htons(uDestPort);
	len = htons(sizeof(UDPHeader) + nMsgLen);
	checksum = 0;
	ComputeUdpPseudoHeaderChecksum(pIpHdr, this, pMsg, nMsgLen);

}
//不包含Ether Header
bool _UDPHeader::ComposeUdpPacket(char* szRetbuf, int& nBufLen, char* szSourceIP, char* szDestIP, 
					  USHORT uSourcePort, USHORT uDestPort, UINT nTTL, char* pMsg, int nMsgLen)
{
	int nSize = sizeof(IPHeader) + sizeof(UDPHeader) + nMsgLen;
	if (szRetbuf == NULL || nBufLen < nSize)
	{
		nBufLen = nSize;
		return false;
	}
	nBufLen = nSize;
	IPHeader iphdr(szSourceIP, szDestIP, IPPROTO_UDP, nTTL, pMsg, nMsgLen);
	UDPHeader udpHdr(&iphdr, uSourcePort, uDestPort, pMsg, nMsgLen);
	memcpy(szRetbuf, &iphdr, sizeof(iphdr));
	memcpy(szRetbuf+sizeof(IPHeader), &udpHdr, sizeof(udpHdr));
	memcpy(szRetbuf+sizeof(IPHeader)+sizeof(UDPHeader), pMsg, nMsgLen);
	return true;
}
//包含Ether Header
bool _UDPHeader::ComposeUdpPacket2(char* szRetbuf, int& nBufLen, UCHAR sourMac[6], UCHAR destMac[6], char* szSourceIP, char* szDestIP, USHORT uSourcePort, USHORT uDestPort, UINT nTTL, char* pMsg, int nMsgLen)
{
    int nSize = sizeof(ETHeader) + sizeof(IPHeader) + sizeof(UDPHeader) + nMsgLen;
	if (szRetbuf == NULL || nBufLen < nSize)
	{
		nBufLen = nSize;
		return false;
	}
    ETHeader ethdr(sourMac, destMac, ETHERTYPE_IP);
	memcpy(szRetbuf, &ethdr, sizeof(ETHeader));
	char* pBuf = szRetbuf + sizeof(ETHeader);
	int nLen = nBufLen - sizeof(ETHeader);
	ASSERT(ComposeUdpPacket(pBuf, nLen, szSourceIP, szDestIP, uSourcePort, uDestPort, nTTL, pMsg, nMsgLen));
	nBufLen = nSize;
	return true;
}
//不包含Ether Header
bool _TCPHeader::ComposeTcpPacket(char* szRetbuf, int& nBufLen, char* szSourceIP, char* szDestIP, UINT nTTL, 
					  USHORT uSourcePort, USHORT uDestPort, ULONG uSequenceNumb, UCHAR flags,
					  int windowsize, char* pMsg, int nMsgLen)
{
    int nSize = sizeof(IPHeader) + sizeof(TCPHeader) + nMsgLen;
	if (szRetbuf == NULL || nBufLen < nSize)
	{
		nBufLen = nSize;
		return false;
	}
	nBufLen = nSize;
	IPHeader iphdr(szSourceIP, szDestIP, IPPROTO_TCP, nTTL, pMsg, nMsgLen);
	TCPHeader tcphdr(&iphdr, uSourcePort, uDestPort,  uSequenceNumb,  flags, windowsize,  pMsg,  nMsgLen);
    memcpy(szRetbuf, &iphdr, sizeof(iphdr));
	memcpy(szRetbuf+sizeof(IPHeader), &tcphdr, sizeof(tcphdr));
	memcpy(szRetbuf+sizeof(IPHeader)+sizeof(TCPHeader), pMsg, nMsgLen);
	return true;
}
//包含Ether Header
bool _TCPHeader::ComposeTcpPacket2(char* szRetbuf, int& nBufLen, UCHAR sourMac[6], UCHAR destMac[6], char* szSourceIP, char* szDestIP, UINT nTTL, 
					  USHORT uSourcePort, USHORT uDestPort, ULONG uSequenceNumb, UCHAR flags,
					  int windowsize, char* pMsg, int nMsgLen)
{
    int nSize = sizeof(ETHeader) + sizeof(IPHeader) + sizeof(TCPHeader) + nMsgLen;
	if (szRetbuf == NULL || nBufLen < nSize)
	{
		nBufLen = nSize;
		return false;
	}

	ETHeader ethdr(sourMac, destMac, ETHERTYPE_IP);
	memcpy(szRetbuf, &ethdr, sizeof(ETHeader));
	char* pBuf = szRetbuf + sizeof(ETHeader);
	int nLen = nBufLen - sizeof(ETHeader);
	ASSERT(ComposeTcpPacket(pBuf, nLen, szSourceIP, szDestIP, nTTL, uSourcePort, uDestPort, uSequenceNumb, flags, windowsize, pMsg, nMsgLen));
	nBufLen = nSize;
	return true;
}

_ICMPHeader::_ICMPHeader(UCHAR uType, UCHAR uCode, USHORT nID, USHORT nSequence, char* pMsg, int nMsgLen)
{	
	Type		= uType;
	Code		= uCode;
	Checksum	= 0;
	ID			= nID;
	Seq			= nSequence;
	TimeStamp	= GetTickCount();
	ComputeICMPPesudoChecksum(this, pMsg, nMsgLen);
}

void _ICMPHeader::ComputeICMPPesudoChecksum(_ICMPHeader* pIcmpHdr, char* pMsg, int nMsgLen)
{
    int nSize = sizeof(ICMPHeader) + nMsgLen;
	char* buf = new char[nSize];
	memcpy(buf, pIcmpHdr, sizeof(ICMPHeader));
	memcpy(buf+sizeof(ICMPHeader), pMsg, nMsgLen);
	pIcmpHdr->Checksum = ComputeChecksum((USHORT*)buf, nSize);
	delete [] buf;	
}
//不包含Ether header
bool _ICMPHeader::ComposeIcmpPacket(char* szRetbuf, int& nBufLen, char* szSourceIP, char* szDestIP, UINT nTTL, UCHAR uType, UCHAR uCode, USHORT nID, USHORT nSequence, char* pMsg, int nMsgLen)
{
    int nSize = sizeof(IPHeader) + sizeof(ICMPHeader) + nMsgLen;
	if (szRetbuf == NULL || nBufLen < nSize)
	{
		nBufLen = nSize;
		return false;
	}
	nBufLen = nSize;
    IPHeader iphdr(szSourceIP, szDestIP, IPPROTO_TCP, nTTL, pMsg, nMsgLen);
    ICMPHeader icmphdr(uType, uCode, nID, nSequence, pMsg, nMsgLen);
	memcpy(szRetbuf, &iphdr, sizeof(iphdr));
	memcpy(szRetbuf+sizeof(IPHeader), &icmphdr, sizeof(icmphdr));
	memcpy(szRetbuf+sizeof(IPHeader)+sizeof(ICMPHeader), pMsg, nMsgLen);
	return true;
}
//包含Ether Header
bool _ICMPHeader::ComposeIcmpPacket2(char* szRetbuf, int& nBufLen, UCHAR sourMac[6], UCHAR destMac[6], char* szSourceIP, char* szDestIP, UINT nTTL, UCHAR uType, UCHAR uCode, USHORT nID, USHORT nSequence, char* pMsg, int nMsgLen)
{
    int nSize = sizeof(ETHeader) + sizeof(IPHeader) + sizeof(ICMPHeader) + nMsgLen;
	if (szRetbuf == NULL || nBufLen < nSize)
	{
		nBufLen = nSize;
		return false;
	}

	ETHeader ethdr(sourMac, destMac, ETHERTYPE_IP);
	memcpy(szRetbuf, &ethdr, sizeof(ETHeader));
	char* pBuf = szRetbuf + sizeof(ETHeader);
	int nLen = nBufLen - sizeof(ETHeader);
	ASSERT(ComposeIcmpPacket(pBuf, nLen, szSourceIP, szDestIP, nTTL, uType, uCode, nID, nSequence, pMsg, nMsgLen));
	nBufLen = nSize;
	return true;
}