// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__228E35BD_01CF_40BF_A0BD_9D2BADFFA102__INCLUDED_)
#define AFX_STDAFX_H__228E35BD_01CF_40BF_A0BD_9D2BADFFA102__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers



#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#pragma warning(disable: 4786)


#include <winsock2.h>
#include <BCGCBProInc.h>
#include <map>
#include <vector>

#include <iprtrmib.h>

using namespace std;

#define BUFFER_SIZE 1024

typedef struct _MIBICMPSTATS_EX
{
    DWORD       dwMsgs;
    DWORD       dwErrors;
    DWORD       rgdwTypeCount[256];
} MIBICMPSTATS_EX, *PMIBICMPSTATS_EX;

typedef struct _MIB_ICMP_EX
{
    MIBICMPSTATS_EX icmpInStats;
    MIBICMPSTATS_EX icmpOutStats;
} MIB_ICMP_EX,*PMIB_ICMP_EX;

typedef struct 
{
  DWORD   dwState;        	// 连接状态
  DWORD   dwLocalAddr;    	// 本地地址
  DWORD   dwLocalPort;    	// 本地端口
  DWORD   dwRemoteAddr;   	// 远程地址
  DWORD   dwRemotePort;   	// 远程端口
  DWORD	  dwProcessId;		// 进程ID号
} MIB_TCPEXROW, *PMIB_TCPEXROW;

typedef struct 
{
	DWORD			dwNumEntries;
	MIB_TCPEXROW	table[ANY_SIZE];
} MIB_TCPEXTABLE, *PMIB_TCPEXTABLE;

typedef struct 
{
  DWORD   dwLocalAddr;    	// 本地地址
  DWORD   dwLocalPort;    	// 本地端口
  DWORD	  dwProcessId;		// 进程ID号
} MIB_UDPEXROW, *PMIB_UDPEXROW;

typedef struct 
{
	DWORD			dwNumEntries;
	MIB_UDPEXROW	table[ANY_SIZE];
} MIB_UDPEXTABLE, *PMIB_UDPEXTABLE;

#define IP_OPTIONS      1 /* set/get IP options */
#define IP_HDRINCL      2 /* header is included with data */
#define IP_TOS          3 /* IP type of service and preced*/
#define IP_TTL          4 /* IP time to live */
#define IP_MULTICAST_IF     9 /* set/get IP multicast i/f  */
#define IP_MULTICAST_TTL       10 /* set/get IP multicast ttl */
#define IP_MULTICAST_LOOP      11 /*set/get IP multicast loopback */
#define IP_ADD_MEMBERSHIP      12 /* add an IP group membership */
#define IP_DROP_MEMBERSHIP     13/* drop an IP group membership */
#define IP_DONTFRAGMENT     14 /* don't fragment IP datagrams */
#define IP_ADD_SOURCE_MEMBERSHIP  15 /* join IP group/source */
#define IP_DROP_SOURCE_MEMBERSHIP 16 /* leave IP group/source */
#define IP_BLOCK_SOURCE           17 /* block IP group/source */
#define IP_UNBLOCK_SOURCE         18 /* unblock IP group/source */
#define IP_PKTINFO                19 /* receive packet information for ipv4*/
#define IP_RECEIVE_BROADCAST      22 /* allow/block broadcast reception */

struct ip_mreq {
    struct in_addr imr_multiaddr;   /* IP multicast address of group */
    struct in_addr imr_interface;   /* local IP address of interface */
};

//如果在搜索路径中将Platform SDK Include路径放在第一个， 应该避免包含
//头文件ws2tcpip.h 和wspiapi.h, 用到者两个文件中的内容直接拷贝出来
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__228E35BD_01CF_40BF_A0BD_9D2BADFFA102__INCLUDED_)
