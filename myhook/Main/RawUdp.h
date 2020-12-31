// RawUdp.h: interface for the CSendRawUdpPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAWUDP_H__695165BB_2D21_4B10_BAAA_413B516BD50D__INCLUDED_)
#define AFX_RAWUDP_H__695165BB_2D21_4B10_BAAA_413B516BD50D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSendRawUdpPacket  
{
public:
	CSendRawUdpPacket();
	virtual ~CSendRawUdpPacket();
    bool SendPacket(char* pMsg, int nMsgLen, char* szSourceIP, char* szDestIP, USHORT uSourcePort, USHORT uDestPort, UINT nTTL = 128);
};

#endif // !defined(AFX_RAWUDP_H__695165BB_2D21_4B10_BAAA_413B516BD50D__INCLUDED_)
