// CICMPCom.cpp : Implementation of CCICMPCom
#include "stdafx.h"
#include "winsock.h"
#include "ipexport.h"
#include "pingparmlist.h"
#include "Icmpcom.h"
#include "CICMPCom.h"
#include <process.h>

ICMPCREATEFILE  IcmpCreateFile;
ICMPSENDECHO    IcmpSendEcho;
ICMPCLOSEHANDLE IcmpCloseHandle;

/////////////////////////////////////////////////////////////////////////////
// CCICMPCom


STDMETHODIMP CCICMPCom::StartICMP()
{

	
	if (m_Thread != NULL)
	{
		Fire_PingMsgEvent(CComBSTR("ICMP Allready Started"));
		return S_OK;

	}

	m_pPingParmList = new CPingParmList;

	if (!m_pPingParmList)
	{
		Fire_PingMsgEvent(CComBSTR("Create Parmlist Failed"));
		return S_OK;

	}

	memset(m_pPingParmList,0,sizeof(CPingParmList));
	m_pPingParmList->m_Events = (CCICMPCom*)this;


	if	(m_Thread == NULL)
	{ 
		if (!InitInstance(m_pPingParmList))  // go load ICMP
		{
			Fire_PingMsgEvent(CComBSTR("ICMP DLL LOAD FAILED"));
			return S_OK;

		}
	}

	
	//
	//
	// create the events
	//

	m_pPingParmList->m_hEventStartPing =
	CreateEvent(NULL, FALSE, FALSE, NULL);

	m_pPingParmList->m_hEventPingDone =
		CreateEvent(NULL, TRUE, TRUE, NULL);
	m_pPingParmList->m_hEventKillPing =
		CreateEvent(NULL, FALSE, FALSE, NULL);
	m_pPingParmList->m_hEventPingDead = 
		CreateEvent(NULL, FALSE, FALSE, NULL);

	unsigned dwt;
	//m_Thread = CreateThread(NULL,0,&CPingProc,m_pPingParmList,0,&dwt);
	m_Thread = (HANDLE)_beginthreadex(NULL,0,
									  CPingProc,
									  m_pPingParmList,
									  0,
									  &dwt);
	if (!m_Thread)
	{
		Fire_PingMsgEvent(CComBSTR("Thread Create Failed"));
		return S_OK;
	}
		


	return S_OK;
}

STDMETHODIMP CCICMPCom::StopICMP()
{
	// TODO: Add your implementation code here
	
	if (m_Thread != NULL)
	{
		CleanUp(m_pPingParmList);  //stop icmp/tcp
	
		// Kill the worker thread by setting the "kill thread" event.
		// See comment in OnKillWorkerThread for explanation of the sequence
		// of the "kill thread" and "start recalc" events.
		SetEvent(m_pPingParmList->m_hEventKillPing);
		SetEvent(m_pPingParmList->m_hEventStartPing);
		WaitForSingleObject(m_pPingParmList->m_hEventPingDead,
							INFINITE);
		m_Thread = NULL;

		if (m_pPingParmList)
		{
			delete m_pPingParmList;
			m_pPingParmList = NULL;
		}
		
	    Fire_PingTerminated();
	}
	return S_OK;
}




STDMETHODIMP CCICMPCom::SetPingVariables(BSTR hostname,
										 BOOL opttrcrt,
										 BOOL optresolve,
										 BOOL optnofrag,
										 BOOL optruntointerupt,
										 INT optttl,
										 INT optpacketlen,
										 INT optnumpackets,
										 INT optrroutenum,
										 INT opttimestamp,
										 INT opttos,
										 INT opttimeout)
{
	// TODO: Add your implementation code here
	if (m_pPingParmList == NULL)
	{
		Fire_PingMsgEvent(CComBSTR("ICMP Not Started"));
		return S_OK;
		
		
	}

	
	WideCharToMultiByte(CP_ACP,
						0,
						(LPWSTR)hostname,
						-1,
						m_pPingParmList->hostname,
						sizeof(m_pPingParmList->hostname),
						NULL,
						NULL); 
	
	m_pPingParmList->opt_tracert = opttrcrt;
	m_pPingParmList->opt_resolve = optresolve;
	m_pPingParmList->opt_dontfragment = optnofrag;
	m_pPingParmList->opt_interrupt = optruntointerupt;
	m_pPingParmList->opt_ttl_val = optttl;
	m_pPingParmList->opt_packetlen_val = optpacketlen;
	m_pPingParmList->opt_rroute_val = optrroutenum;
	m_pPingParmList->opt_timestamp_val = opttimestamp;
	m_pPingParmList->opt_tos_val = opttos;
	m_pPingParmList->opt_timeout_val = opttimeout;
	m_pPingParmList->opt_numpackets_val = optnumpackets;



	return S_OK;
}


//
// handle ping thread
//
//
//


//
//  The Main Thread Procedure
//
//DWORD WINAPI CPingProc(LPVOID lparam)
unsigned __stdcall CCICMPCom::CPingProc(LPVOID lparam)
{
	
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	BOOL bPingThreadComplete;
	CPingParmList *lpPingParms;
	

	lpPingParms = (CPingParmList*)lparam;
	CCICMPCom* picmpcom = (CCICMPCom*)lpPingParms->m_Events;
	
	
	while (TRUE)
	{

	
		bPingThreadComplete = FALSE;

		// Wait until the main application thread asks this thread to do
		// something.

		if (WaitForSingleObject(lpPingParms->m_hEventStartPing,
								INFINITE) != WAIT_OBJECT_0)
			break;

		// Exit the thread if the main application sets the "kill"
		// event. The main application will set the "start event
		// before setting the "kill" event.

		if (WaitForSingleObject(lpPingParms->m_hEventKillPing, 0)
			== WAIT_OBJECT_0)
			break; // Terminate this thread by existing the proc.

		// Reset event to indicate "not done", that is, in progress.
		//ResetEvent(lpPingParms->m_hEventPingDone);

		// Run PING!!
		if (lpPingParms->opt_tracert)
			bPingThreadComplete = 
			    picmpcom->Tracert(lpPingParms);
		else
			bPingThreadComplete = 
			    picmpcom->Ping(lpPingParms);
			

		// Set event to indicate that we're done (i.e., no longer in progres),
		// even if perhaps interrupted by "kill" event.
		SetEvent(lpPingParms->m_hEventPingDone);
		
		// tell main app we're done this request
		picmpcom->PingDone();
			
	}

	// tell main app this thread has terminated.
	SetEvent(lpPingParms->m_hEventPingDead);

	return 0;

		
	

	
	
}

/////////////////////////////////////////////////////////////////////////////

BOOL CCICMPCom::InitInstance(CPingParmList *lppingvars)
{
	
	// start winsock
	WSADATA wsaData;
	WORD version;
	version = MAKEWORD(2,1);
	if (WSAStartup(version,&wsaData))
		return FALSE;
	//
	// load icmp dll
	//
	lppingvars->Icmpdll = LoadLibrary("ICMP.DLL");
	if (lppingvars->Icmpdll == NULL)
		return FALSE;

	IcmpCreateFile = 
	(ICMPCREATEFILE) GetProcAddress(lppingvars->Icmpdll,"IcmpCreateFile");

	IcmpCloseHandle =
	(ICMPCLOSEHANDLE) GetProcAddress(lppingvars->Icmpdll,"IcmpCloseHandle");

	IcmpSendEcho = 
		(ICMPSENDECHO) GetProcAddress(lppingvars->Icmpdll,"IcmpSendEcho");



	
	return TRUE;
}




void CCICMPCom::Kill(CPingParmList *lppingvars)
{
	lppingvars->bKill = TRUE;
	
}




BOOL CCICMPCom::Running(CPingParmList *lppingvars)
{
	BOOL rc;
	// if true then we are stopping else we are running;

	rc = (lppingvars->bKill == TRUE) ? FALSE : TRUE;
	return rc;

}
BOOL CCICMPCom::ISActive(HANDLE hThread)
{
	DWORD Status;
	::GetExitCodeThread(hThread,&Status);
	if (Status == STILL_ACTIVE)
		return TRUE;
	else
		return FALSE;


}

HANDLE CCICMPCom::Icmp_Open()
{
	HANDLE File;
	File = (*IcmpCreateFile)();
	if (File != INVALID_HANDLE_VALUE)
		return File;
	else
	{
		File = 0;
		return File;
	}

}

BOOL CCICMPCom::Icmp_Close(HANDLE h)
{
	BOOL rc;
	rc =  (*IcmpCloseHandle)(h);
	return rc;

}

BOOL CCICMPCom::Icmp_Sendto(CPingParmList *lppingvars,
							  _TCHAR *OUTBuf,
							  _TCHAR *INBuf,
							  struct ipopt_info *lpIpopt,
							  ULONG sendaddr,
							  INT maxoutbuffsize,
							  INT maxinbuffsize)
{
	u_short i;
	char c;

	
	//DWORD NumberOfEchoReplies;
   	memset(OUTBuf,0,maxoutbuffsize);
	c=' ';   /* first char: space */
	for (i=0;
		   ((i < (lppingvars->opt_packetlen_val)) && (i < maxoutbuffsize)); 
		i++) 
	{
		OUTBuf[i] = c;
		c++;
		if (c > '~')	/* go up to ASCII 126, then back to 32 */
			c= ' ';
	}

	
    
	

	memset(INBuf,0,maxinbuffsize);
	(*IcmpSendEcho)(lppingvars->PingSocket,
					sendaddr,OUTBuf,
					lppingvars->opt_packetlen_val,
					lpIpopt,
					INBuf,
					maxinbuffsize,
					lppingvars->opt_timeout_val);

	
	
	
	return TRUE;
	

}

BOOL CCICMPCom::Icmp_SetOpts(CPingParmList *lppingvars,
							   struct ipopt_info *lpIpopt,
							   UCHAR *optdata,
							   INT optsize)
{
	BOOL HaveOpts = FALSE;
	
	
	memset(lpIpopt,0,IPOPT_INFO_LEN);
	
	struct in_addr;
	

	


	if (lppingvars->opt_timeout_val == 0)  // Timeout value specified?
	{
		//set default timeout
		lppingvars->opt_timeout_val = 5000;
				
	}
	
	//
	// the remaining options if set require us to set  
	// a pointer to the options for the sendecho else
	// the pointer should be set to null
	//

	if (lppingvars->opt_ttl_val != 0)  // TTL value specified?
	{
		//set TTL if specified
		lpIpopt->Ttl = lppingvars->opt_ttl_val;
		HaveOpts = TRUE;
		
		
	}
	
	
	if (lppingvars->opt_tos_val != 0) // TOS value specified?
	{
		//set TOS if specified
		lpIpopt->Tos = lppingvars->opt_tos_val;
		if (lpIpopt->Ttl == 0)
			lpIpopt->Ttl = 255;
		HaveOpts = TRUE;
		
		
	}

	if (lppingvars->opt_dontfragment) // dont Frag?
	{
		//set dont frag 
		lpIpopt->Flags |= IP_FLAG_DF;
		if (lpIpopt->Ttl == 0)
			lpIpopt->Ttl = 255;
		HaveOpts = TRUE;
		
		
	}


	if (lppingvars->opt_rroute_val != 0) // Record Route?
	{
		memset(optdata,0xff,optsize);		
		memset(optdata,0,3+(4*lppingvars->opt_rroute_val));
		optdata[IPOPT_OPTVAL] = IP_OPT_RR;
		optdata[IPOPT_OLEN] = 3+(4*lppingvars->opt_rroute_val);
		optdata[IPOPT_OFFSET] = IPOPT_MINOFF;
		lpIpopt->OptionsData = optdata;
		lpIpopt->OptionsSize = optdata[IPOPT_OLEN];
		if (lpIpopt->Ttl == 0)
			lpIpopt->Ttl = lppingvars->opt_rroute_val;
		HaveOpts = TRUE;
	}

	if (lppingvars->opt_timestamp_val != 0) // ts?
	{
		memset(optdata,0xff,optsize);		
		memset(optdata,0,
			   4+(8*lppingvars->opt_timestamp_val));
		optdata[IPOPT_OPTVAL] = IP_OPT_TS;
		optdata[IPOPT_OLEN] = 4+(8*lppingvars->opt_timestamp_val);
		optdata[IPOPT_OFFSET] = (IPOPT_MINOFF + 1);
		optdata[IPOPT_TSFLAGS] = IP_OPT_TS_REGADDR;
		lpIpopt->OptionsData = optdata;
		lpIpopt->OptionsSize = optdata[IPOPT_OLEN];
		if (lpIpopt->Ttl == 0)
			lpIpopt->Ttl = 255;
		HaveOpts = TRUE;


	}
	

	


	if (!HaveOpts)
		return FALSE;
		
		
	return TRUE;

}

ULONG CCICMPCom::GetAddr(LPCTSTR szHost,struct in_addr *inaddr)
{
	LPHOSTENT lpstHost = NULL;
	struct in_addr stinaddr;
	u_long lAddr = INADDR_ANY;

	if (*szHost)
	{
		//lAddr = inet_addr(szHost);
		stinaddr.s_addr = inet_addr(szHost);
		if ((stinaddr.s_addr == INADDR_NONE) &&
			(strcmp(szHost,"255.255.255.255")))
		{
			lpstHost = gethostbyname(szHost);
			if (lpstHost)
			{
				lAddr = *((u_long *) (lpstHost->h_addr));
				if (inaddr)
					inaddr->s_addr = *((u_long *) (lpstHost->h_addr));
			}
			else
			{
				lAddr = INADDR_ANY;
				if (inaddr)
					inaddr->s_addr = INADDR_ANY;

			}
		}
		else
		{
			lAddr = stinaddr.s_addr;
			if (inaddr)
				inaddr->s_addr = stinaddr.s_addr;

		}
			
	}
	
	return (lAddr);

}

BOOL CCICMPCom::Ping(CPingParmList *lppingvars)
{
	
	BOOL Sendok;
	struct ipopt_info IpoptInfo;
	struct ipopt_info *lpIpoptInfo;
	struct icmp_reply *EchoReply;
	INT RRsize = 3+4*PING_NROUTES+1;
	UCHAR RRSpace[3+4*PING_NROUTES+1];
	
	IPAddr SendToAddr;
	CHAR achINBuf[PNGINBUFSIZE];
	CHAR achOUTBuf[PNGOUTBUFSIZE];
	
	lppingvars->PingSocket = Icmp_Open();
	if (lppingvars->PingSocket == 0)
	{
		PrintLine("Ping: Error - ICMP Open Failed",lppingvars);
		return FALSE;
	}

	SendToAddr = GetAddr(lppingvars->hostname);
	EchoReply = (struct icmp_reply *)achINBuf;
	EchoReply->RoundTripTime = 0xffffffff;

	lpIpoptInfo = &IpoptInfo; // point to ip options

	if (!Icmp_SetOpts(lppingvars,lpIpoptInfo,RRSpace,RRsize))
		lpIpoptInfo = NULL;
	
	lppingvars->bKill = FALSE;
	int numpacks;
	numpacks = lppingvars->opt_numpackets_val;
	
	if (lppingvars->opt_interrupt)  // allow 100 pings no options
	{
		numpacks = 100;
		lpIpoptInfo = NULL;
	}

	for (int x = 0;x <= numpacks;x++)
	{
		if (lppingvars->bKill)
		{
			PrintLine("Ping Interrupted!",lppingvars);
			return FALSE;
		}
		Sendok = Icmp_Sendto(lppingvars,achOUTBuf,achINBuf,
							lpIpoptInfo,SendToAddr,
							PNGOUTBUFSIZE,
							PNGINBUFSIZE);
		
		if (!ProcessReply(lppingvars,(struct icmp_reply *)achINBuf))
		{
	
			Icmp_Close(lppingvars->PingSocket);
			return FALSE;
		}
		
	
	}


	
	Icmp_Close(lppingvars->PingSocket);
	return TRUE;

}

BOOL CCICMPCom::ProcessReply(CPingParmList *lppingvars,
							   struct icmp_reply *lpReply)
{
	struct in_addr convaddr;
	struct hostent *resolve_addr;
	CHAR *szTempName;
	CHAR szHost[MAXHOSTSIZE];
	CHAR szLBLine[LBLINESIZE];
	UCHAR RETSpace[3+4*PING_NROUTES+1];

	int NumberOfAddresses;
	UCHAR *routes;
	u_long holdaddr,holdtime;
	int x;
	int count;


	if (lpReply->Status != IP_SUCCESS)
		
		if (lpReply->Status == IP_REQ_TIMED_OUT)
		{
			PrintLine("Request Timed Out",lppingvars);
			return TRUE;
		}
		else
        if (lpReply->Status > IP_UNLOAD)
		{
			wsprintf(szLBLine,"Ping: Error - Status = %ld",
					 lpReply->Status);
			PrintLine(szLBLine,lppingvars);
			return FALSE;
		}
		else
		{
			u_long errtab;
			errtab = lpReply->Status - IP_STATUS_BASE;
			wsprintf(szLBLine,"Ping: Error - Status = %ld %s",
				lpReply->Status,
				ErrorCodes[errtab].msg);
			PrintLine(szLBLine,lppingvars);
			return FALSE;
		}
	
	
	

	convaddr.s_addr = lpReply->Address;
    szTempName = inet_ntoa(convaddr);
	if (szTempName)
		strcpy(szHost,szTempName);
	else
		strcpy(szHost,"Unknown Address");
	
	if (lppingvars->opt_resolve)
	{
		resolve_addr = gethostbyaddr((char*)&lpReply->Address,
									4,AF_INET);
		if (resolve_addr)
			wsprintf(szLBLine,
			    "Ping: Reply from %s [%s] Time %ld ms TTL %u Size %u",
			    resolve_addr->h_name,
				szHost,
				lpReply->RoundTripTime,
				lpReply->Options.Ttl,
				lppingvars->opt_packetlen_val);
		else
			wsprintf(szLBLine,
			    "Ping: Reply from %s [Unknown] Time %ld ms TTL %u Size %u",
			    szHost,
				lpReply->RoundTripTime,
				lpReply->Options.Ttl,
				lppingvars->opt_packetlen_val);

	}
	else
	{
		wsprintf(szLBLine,
			    "Ping: Reply from %s Time %ld ms TTL %u Size %u",
				szHost,
				lpReply->RoundTripTime,
				lpReply->Options.Ttl,
				lppingvars->opt_packetlen_val);
	}

	PrintLine(szLBLine,lppingvars);
	
	if (lppingvars->opt_rroute_val != 0) // Record Route?
	{
		count = (int)lpReply->Options.OptionsData[IPOPT_OLEN];
		memset(RETSpace,0,sizeof(RETSpace));
		for (x=0;x<count;x++)
		{
			RETSpace[x] = lpReply->Options.OptionsData[x];
		}
		if (RETSpace[IPOPT_OFFSET] > IPOPT_MINOFF)
		{
			NumberOfAddresses = 
			 ((RETSpace[IPOPT_OFFSET] - 4)
				/ 4);
			routes = RETSpace+3;
			for(x=0;x<NumberOfAddresses;x++)
			{
				// ensure holdaddr will remain in network 
				// order while the UCHAR data is converted
				// to u_long

				holdaddr = (*routes<<24) | (*(routes+1)<<16) |
					     (*(routes+2)<<8) | *(routes+3);
				holdaddr = ntohl(holdaddr);
				convaddr.s_addr = holdaddr;
				szTempName = inet_ntoa(convaddr);
				strcpy(szHost,szTempName);
				

				if (lppingvars->opt_resolve)
				{
					resolve_addr = gethostbyaddr((char*)&holdaddr,
												4,AF_INET);
					if (resolve_addr)
						wsprintf(szLBLine,"Ping: Reply Route %s [%s]",
							resolve_addr->h_name,
							szHost);
					else
						wsprintf(szLBLine,"Ping: Reply Route %s [Unkown]",
							szHost);
				}
				else
				{
					wsprintf(szLBLine,"Ping: Reply Route %s",
								szHost);
				}
				
				PrintLine(szLBLine,lppingvars);
				routes = routes + 4;
			}
		}
		else
		{
			PrintLine("No Routes Recorded",lppingvars);
		
		}
	}

	// timestamp option
	if (lppingvars->opt_timestamp_val != 0) // Timestamp?
	{
		count = (int)lpReply->Options.OptionsData[IPOPT_OLEN];
		memset(RETSpace,0,sizeof(RETSpace));
		for (x=0;x<count;x++)
		{
			RETSpace[x] = lpReply->Options.OptionsData[x];
		}
		if (RETSpace[IPOPT_OFFSET] > IPOPT_MINOFF)
		{
			NumberOfAddresses = 
			 ((RETSpace[IPOPT_OFFSET] - 5)
				/ 8);
			routes = RETSpace+4;
			for(x=0;x<NumberOfAddresses;x++)
			{
				// ensure holdaddr will remain in network 
				// order while the UCHAR data is converted
				// to u_long

				holdaddr = (*routes<<24) | (*(routes+1)<<16) |
					     (*(routes+2)<<8) | *(routes+3);
				holdaddr = ntohl(holdaddr);
				convaddr.s_addr = holdaddr;
				szTempName = inet_ntoa(convaddr);
				strcpy(szHost,szTempName);
				holdtime = (*(routes+4)<<24) | (*(routes+5)<<16) |
					     (*(routes+6)<<8) | *(routes+7);
				holdtime = ntohl(holdtime);
				if (lppingvars->opt_resolve)
				{
					resolve_addr = gethostbyaddr((char*)&holdaddr,
												4,AF_INET);
					if (resolve_addr)

						wsprintf(szLBLine,
						    "Ping:      Route %s [%s] TS %lu",
						    resolve_addr->h_name,
							szHost,
							holdtime);
					else
						wsprintf(szLBLine,
						    "Ping:      Route %s [Unknown] TS %lu",
						    szHost,
							holdtime);
				}
				else
				{
					wsprintf(szLBLine,"Ping:      Route %s TS %lu",
							szHost,holdtime);
				}
				PrintLine(szLBLine,lppingvars);
				routes = routes + 4;
			}
		}
		else
		{
			PrintLine("No Routes Recorded",lppingvars);
			
		}
	}
	
	return TRUE;

}

void CCICMPCom::PrintLine(LPSTR szMsg,CPingParmList *lppingvars)
{
	CCICMPCom *pp;
	pp = (CCICMPCom*)lppingvars->m_Events;

	CComBSTR *mymsg = new CComBSTR(strlen(szMsg),szMsg);

	pp->PingMsg(mymsg->m_str);
			
	//delete mymsg;

	return;

}




BOOL CCICMPCom::Tracert(CPingParmList *lppingvars)
{
	BOOL Sendok;
	UINT MaxTtl = 30;
	UINT probecnt = 3;
	struct hostent *resolve_addr;
	CHAR szLBLine[LBLINESIZE];
	ULONG Timestamp;
	CHAR *szTempName;
	CHAR szHost[MAXHOSTSIZE];
	struct in_addr convaddr;
	struct ipopt_info IpoptInfo;
	struct ipopt_info *lpIpoptInfo;
	struct icmp_reply *EchoReply;

// get rid of these below/
	IPAddr SendToAddr;
	CHAR achINBuf[PNGINBUFSIZE];
	CHAR achOUTBuf[PNGOUTBUFSIZE];
	
	lppingvars->PingSocket = Icmp_Open();
	if (lppingvars->PingSocket == 0)
	{
		PrintLine("Ping: Error - ICMP Open Failed",lppingvars);
		return FALSE;
	}

	SendToAddr = GetAddr(lppingvars->hostname);
	EchoReply = (struct icmp_reply *)achINBuf;

	lppingvars->bKill = FALSE;
	
	

	lpIpoptInfo = &IpoptInfo;
	memset(lpIpoptInfo,0,IPOPT_INFO_LEN);

	convaddr.s_addr = SendToAddr;

	// convert addr to dotted

    szTempName = inet_ntoa(convaddr);
	if (szTempName)
		strcpy(szHost,szTempName);
	else
		strcpy(szHost,"Unknown Address");

	// set ttl defaults or values
	// set timeout defaults and values

	if (lppingvars->opt_timeout_val == 0)  // Timeout value specified?
	{
		//set default timeout
		lppingvars->opt_timeout_val = 5000;
				
	}
	
	if (lppingvars->opt_ttl_val == 0)  // Timeout value specified?
	{
		//set default timeout
		lppingvars->opt_ttl_val = 30;

	}

	MaxTtl = lppingvars->opt_ttl_val;
	// print the report header
	if (lppingvars->opt_resolve)
	{
		resolve_addr = gethostbyaddr((char*)&SendToAddr,
									4,AF_INET);
		if (resolve_addr)
			wsprintf(szLBLine,
				"Tracing: %s [%s] TTL %u Size %u",
				resolve_addr->h_name,
				szHost,
				MaxTtl,
				lppingvars->opt_packetlen_val);
		else
			wsprintf(szLBLine,
				"Tracing: %s [Unkown] TTL %u Size %u",
				lppingvars->hostname,
				MaxTtl,
				lppingvars->opt_packetlen_val);
	}
	else
	{
			wsprintf(szLBLine,
				"Tracing: %s TTL %u Size %u",
				lppingvars->hostname,
				MaxTtl,
				lppingvars->opt_packetlen_val);
		
	}
	
	PrintLine(szLBLine,lppingvars);
	

				
	//
	// ttl loop
	//
	for (INT x = 1;x <= lppingvars->opt_ttl_val;x++)
	{
		
		lpIpoptInfo->Ttl = x;
		//
		// probe loop
		//
		for (UINT y = 1;y<=probecnt;y++)
		{
			if (lppingvars->bKill)
			{
				PrintLine("Ping Interrupted!",lppingvars);
				return FALSE;
			}

			Timestamp = GetTickCount();
			Sendok = Icmp_Sendto(lppingvars,achOUTBuf,achINBuf,
							lpIpoptInfo,SendToAddr,
							PNGOUTBUFSIZE,
							PNGINBUFSIZE);
			
			
			if (!TracertReply(lppingvars,
								(struct icmp_reply *)achINBuf,
								x,y,
								Timestamp))
			{
				Icmp_Close(lppingvars->PingSocket);
				return FALSE;
			}
			if (x > 1 && EchoReply->Address == SendToAddr && y == probecnt)
			{
				x = MaxTtl + 1;
			}
		}
	}
	return TRUE;
	
}


BOOL CCICMPCom::TracertReply(CPingParmList *lppingvars,
							   struct icmp_reply *lpReply,
							   UINT ttl,
							   UINT probe,
							   ULONG Timestamp)
{
	
	CHAR *szTempName;
	CHAR szHost[MAXHOSTSIZE];
	struct in_addr convaddr;
	struct hostent *resolve_addr;
	CHAR build_line[LBLINESIZE];
	CHAR szLBLine[LBLINESIZE];
	ULONG errtab;
	ULONG RRTime;
			
	//
	
	RRTime = GetTickCount() - Timestamp;
	if (lpReply->Status > IP_UNLOAD)
	{
		wsprintf(szLBLine,"Ping: Error - Status = %ld",
				 lpReply->Status);
		PrintLine(szLBLine,lppingvars);
		return FALSE;
	}
	if (lpReply->Status != IP_SUCCESS)
	{
		if (!(lpReply->Status == IP_REQ_TIMED_OUT ||
							   IP_TTL_EXPIRED_TRANSIT))
	
		{
		
			errtab = lpReply->Status - IP_STATUS_BASE;
			wsprintf(szLBLine,"Ping: Error - Status = %ld %s",
				lpReply->Status,
				ErrorCodes[errtab].msg);
			PrintLine(szLBLine,lppingvars);
			return FALSE;
		}
	}

	

	wsprintf(szLBLine,
			"    TTL = %u Probe = %u ",
			    ttl,
				probe);


	convaddr.s_addr = lpReply->Address;

    szTempName = inet_ntoa(convaddr);
	if (szTempName)
		strcpy(szHost,szTempName);
	else
		strcpy(szHost,"Unknown Address");

	if (lppingvars->opt_resolve)
	{
		resolve_addr = gethostbyaddr((char*)&lpReply->Address,
									4,AF_INET);
		if (resolve_addr)
			wsprintf(build_line,
				"from %s [%s] ",
			    resolve_addr->h_name,
				szHost);
		else
			wsprintf(build_line,
				"from %s [Unkown] ",
			    szHost);

			
	}
	else
	{
		wsprintf(build_line,
				"from %s ",
			    szHost);
		
	}

	
		
	strcat(szLBLine,build_line);
	
	if (lpReply->Status == IP_SUCCESS)
	{
		wsprintf(build_line,
			"Time %ld ms ",
			lpReply->RoundTripTime);
		strcat(szLBLine,build_line);
		
	}
	else
	{
		wsprintf(build_line,
			"Time %lu ms Timed Out",
			RRTime);
   		    
		strcat(szLBLine,build_line);
		//errtab = lpReply->Status;
		//errtab -= IP_STATUS_BASE;
		//strcat(szLBLine,
		//	   ErrorCodes[errtab].msg);
		
	}

	PrintLine(szLBLine,lppingvars);
	return TRUE;

}

void CCICMPCom::CleanUp(CPingParmList *lppingvars)
{
	FreeLibrary(lppingvars->Icmpdll);  // remove icmp dll
	WSACleanup();
	

}


void CCICMPCom::PingDone()
{
	Fire_PingDoneEvent();

}

void CCICMPCom::PingMsg(BSTR pbMsg)
{
	Fire_PingMsgEvent(pbMsg);

}

STDMETHODIMP CCICMPCom::RunPing()
{
	// TODO: Add your implementation code here
	if (!m_pPingParmList)
	{
		Fire_PingMsgEvent(CComBSTR("ICMP not Started"));
		return S_OK;
	}

	if (!m_Thread)
	{
		Fire_PingMsgEvent(CComBSTR("ICMP not Started"));
		return S_OK;
	}

	ResetEvent(m_pPingParmList->m_hEventPingDone);
	ResetEvent(m_pPingParmList->m_hEventKillPing);
	ResetEvent(m_pPingParmList->m_hEventPingDead);
	SetEvent(m_pPingParmList->m_hEventStartPing);

	return S_OK;
}

STDMETHODIMP CCICMPCom::StopPing()
{
	// TODO: Add your implementation code here

	m_pPingParmList->bKill = TRUE;
	return S_OK;
}
