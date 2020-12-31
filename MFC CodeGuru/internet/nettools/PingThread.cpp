// PingThread.cpp : implementation file
//

#include "stdafx.h"
#include "nettools.h"
#include "PingParmList.h"
#include "winsock.h"
#include "ipexport.h"
#include "PingThread.h"






#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct IPErrors
{
	CHAR   msg[30];
};
                  

struct IPErrors ErrorCodes[23] =
{
	{"OK"},
	{"Buffer too small"},            
    {"Dest Net Unreachable"},
	{"Dest Host Unreachable"},
    {"Dest Prot Unreachable"},
    {"Dest Port Unreachable"},
    {"No Resources"},
	{"Bad IP Option"},
	{"Hardware Error"},
	{"Packet Too Big"},
	{"Request Timed Out"},
	{"Bad Request"},
	{"Bad Route"},
	{"TTL Expired Transit"},
	{"TTL Expired Re-Assembly"},
	{"Parameter Problem"},
	{"Source Quench"},
	{"Option Too Large"},
	{"Bad Destination"},
	{"Address Deleted"},
	{"Spec MTU Change"},
	{"MTU Change"},
	{"Unload"}
};
    

//
//  The Main Thread Procedure
//
UINT CPingThreadProc(LPVOID lparam)
{
	BOOL bPingThreadComplete;
	CPingThreadParmList *lpPingParms;
	CPingThread *mythread;

	lpPingParms = (CPingThreadParmList*)lparam;
	mythread = (CPingThread*)lpPingParms->m_mythread;
	
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
			    mythread->RunTracert(lpPingParms);
		else
			bPingThreadComplete = 
			    mythread->RunPing(lpPingParms);
			

		// Set event to indicate that we're done (i.e., no longer in progres),
		// even if perhaps interrupted by "kill" event.
		SetEvent(lpPingParms->m_hEventPingDone);
		
		// tell main app we're done this request
		::PostMessage(lpPingParms->m_hwndNotifyPingDone,
			WM_USER_PING_DONE, 0, (LONG)lpPingParms);
	}

	// tell main app this thread has terminated.
	SetEvent(lpPingParms->m_hEventPingDead);

	return 0;

		
	

	
	
}

/////////////////////////////////////////////////////////////////////////////
// CPingThread

IMPLEMENT_DYNCREATE(CPingThread, CWinThread)

CPingThread::CPingThread()
{
}

CPingThread::~CPingThread()
{
}

BOOL CPingThread::InitInstance()
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
	Icmpdll = LoadLibrary("ICMP.DLL");
	if (Icmpdll == NULL)
		return FALSE;

	IcmpCreateFile = 
	(ICMPCREATEFILE) GetProcAddress(Icmpdll,"IcmpCreateFile");

	IcmpCloseHandle =
	(ICMPCLOSEHANDLE) GetProcAddress(Icmpdll,"IcmpCloseHandle");

	IcmpSendEcho = 
		(ICMPSENDECHO) GetProcAddress(Icmpdll,"IcmpSendEcho");



	
	return TRUE;
}


BEGIN_MESSAGE_MAP(CPingThread, CWinThread)
	//{{AFX_MSG_MAP(CPingThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPingThread message handlers



void CPingThread::Kill()
{
	bKill = TRUE;
	
}


BOOL CPingThread::Start()
{
	BOOL rc = TRUE;
	bKill = FALSE;
	rc = CreateThread();
	if (!rc)
		return rc;

	rc = InitInstance();
	if (!rc)
		return rc;

	return rc;


}

BOOL CPingThread::Running()
{
	DWORD Status;
	::GetExitCodeThread(m_hThread,&Status);
	if (Status == STILL_ACTIVE)
		return TRUE;
	else
		return FALSE;


}

HANDLE CPingThread::Icmp_Open()
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

BOOL CPingThread::Icmp_Close(HANDLE h)
{
	BOOL rc;
	rc = (*IcmpCloseHandle)(h);
	return rc;

}

BOOL CPingThread::Icmp_Sendto(CPingThreadParmList *lppingvars,
							  CHAR *OUTBuf,
							  CHAR *INBuf,
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
	NumberOfEchoReplies = (*IcmpSendEcho)
						(PingSocket,sendaddr,OUTBuf,
						 lppingvars->opt_packetlen_val,
						 lpIpopt,
						 INBuf,
						 maxinbuffsize,
						 lppingvars->opt_timeout_val);

	
	
	
	return TRUE;
	

}

BOOL CPingThread::Icmp_SetOpts(CPingThreadParmList *lppingvars,
							   struct ipopt_info *lpIpopt,
							   UCHAR *optdata,
							   INT optsize)
{
	BOOL HaveOpts = FALSE;
	int numrrdata;
	
	memset(lpIpopt,0,IPOPT_INFO_LEN);
	
	struct in_addr rr_inaddr;
	UCHAR *routes;

	


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
	

	if (lppingvars->opt_rrloose || lppingvars->opt_rrstrict)
	{
		numrrdata = lppingvars->opt_rrdata.GetSize();
		memset(optdata,0xff,optsize);		
		memset(optdata,0,3+(4*numrrdata));
		optdata[IPOPT_OLEN] = 3+(4*numrrdata);
		optdata[IPOPT_OFFSET] = IPOPT_MINOFF;
		routes =  optdata+3; 
		for (int x = 0;x<numrrdata;x++)
		{
			GetAddr(lppingvars->opt_rrdata[x],&rr_inaddr);
			*routes = rr_inaddr.s_net;
			*(routes+1) = rr_inaddr.s_host;
			*(routes+2) = rr_inaddr.s_lh;
			*(routes+3) = rr_inaddr.s_impno;
			routes += 4; 

		}
		if (lppingvars->opt_rrloose)
			optdata[IPOPT_OPTVAL] = IP_OPT_LSRR;
		else
			optdata[IPOPT_OPTVAL] = IP_OPT_SSRR;

		lpIpopt->Ttl = numrrdata;

		
	}




	if (!HaveOpts)
		return FALSE;
		
		
	return TRUE;

}

ULONG CPingThread::GetAddr(LPCTSTR szHost,struct in_addr *inaddr)
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

BOOL CPingThread::RunPing(CPingThreadParmList *lppingvars)
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
	
	PingSocket = Icmp_Open();
	if (PingSocket == 0)
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
	
	bKill = FALSE;
	int numpacks;
	numpacks = lppingvars->opt_numpackets_val;
	
	if (lppingvars->opt_interrupt)  // allow 100 pings no options
	{
		numpacks = 100;
		lpIpoptInfo = NULL;
	}

	for (int x = 0;x <= numpacks;x++)
	{
		if (bKill)
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
	
			Icmp_Close(PingSocket);
			return FALSE;
		}
		
	
	}


	
	Icmp_Close(PingSocket);
	return TRUE;

}

BOOL CPingThread::ProcessReply(CPingThreadParmList *lppingvars,
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

void CPingThread::PrintLine(LPSTR szMsg,CPingThreadParmList *lppingvars)
{
	//CString m_errmsg;
	//CHAR *pm_errmsg;
	
	//pm_errmsg = m_errmsg.GetBuffer(LBLINESIZE+1);
	//strcpy(pm_errmsg,szMsg);
	//m_errmsg.ReleaseBuffer();
	//m_PingOutPut.Add(m_errmsg);
	
	::SendMessage(lppingvars->m_hwndNotifyPingDone,
				WM_USER_PING_PRINT, 0, (LONG)szMsg);
	
	return;

}


CPingThread::CPingThread(CPingThreadParmList *lpPingvars)
{
	//
	// Init ourselves
	//

	lpPingvars->m_mythread = this;
	m_bAutoDelete = FALSE;
	m_pThreadParams = lpPingvars;
	m_pfnThreadProc = CPingThreadProc;


}

BOOL CPingThread::RunTracert(CPingThreadParmList *lppingvars)
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
	
	PingSocket = Icmp_Open();
	if (PingSocket == 0)
	{
		PrintLine("Ping: Error - ICMP Open Failed",lppingvars);
		return FALSE;
	}

	SendToAddr = GetAddr(lppingvars->hostname);
	EchoReply = (struct icmp_reply *)achINBuf;

	bKill = FALSE;
	
	

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
			if (bKill)
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
				Icmp_Close(PingSocket);
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


BOOL CPingThread::TracertReply(CPingThreadParmList *lppingvars,
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

void CPingThread::CleanUp()
{
	FreeLibrary(Icmpdll);  // remove icmp dll
	WSACleanup();
	

}
