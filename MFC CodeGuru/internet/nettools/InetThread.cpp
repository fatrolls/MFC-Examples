// InetThread.cpp : implementation file
//

#include "stdafx.h"
#include "nettools.h"
#include <snmp.h>
#include <winsock.h>
#include "InetThreadParms.h"
#include "InetThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct TCPStates
{
	CHAR state[12];
};

struct TCPStates StateTable[12] =
{
	{"Closed     "},
	{"Listen     "},
	{"SynSent    "},
	{"SynReceived"},
	{"Established"},
	{"FinWait1   "},
	{"FinWait2   "},
	{"CloseWait  "},
	{"LastAck    "},
	{"Closing    "},
	{"TimeWait   "},
	{"DeleteTCB  "}
};

//typedef BOOL (CALLBACK* SEQUERY)(BYTE,RFC1157VarBindList*,AsnInteger*,AsnInteger*);
//typedef BOOL (CALLBACK* SEINIT)(DWORD,HANDLE*,AsnObjectIdentifier*);


//WSADATA Inetwsad;
//HANDLE snmpevent = NULL;
//SEINIT SnmpExtensionInit;
//SEQUERY SnmpExtensionQuery;
//HINSTANCE inetdll;

UINT CInetThreadProc(LPVOID pParam)
{
	CInetThreadParms *lpInetParms;
	CInetThread *mythread;

	lpInetParms = (CInetThreadParms*)pParam;
	mythread = (CInetThread*)lpInetParms->m_mythread;

	while (TRUE)
	{

	
	

		// Wait until the main application thread asks this thread to do
		//      another calculation.
		if (WaitForSingleObject(lpInetParms->m_hEventStartInet,
								INFINITE) != WAIT_OBJECT_0)
			break;

		// Exit the thread if the main application sets the "kill recalc"
		// event. The main application will set the "start recalc" event
		// before setting the "kill recalc" event.

		if (WaitForSingleObject(lpInetParms->m_hEventKillInet, 0)
			== WAIT_OBJECT_0)
			break; // Terminate this thread by existing the proc.

		// Reset event to indicate "not done", that is, recalculation is in progress.
		//ResetEvent(lpInetParms->m_hEventInetDone);

	
		mythread->RunInet(lpInetParms);
			

		// Set event to indicate that recalculation is done (i.e., no longer in progres),
		// even if perhaps interrupted by "kill recalc" event detected in the SlowAdd function.
		SetEvent(lpInetParms->m_hEventInetDone);

		//if (!bPingThreadComplete)  // If interrupted by kill then...
		//	break; // terminate this thread by exiting the proc.

		::PostMessage(lpInetParms->m_hwndNotifyInetDone,
			WM_USER_INET_DONE, 0, (LONG)lpInetParms);
	}

	//if (!bPingThreadComplete)
	
	SetEvent(lpInetParms->m_hEventInetDead);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CInetThread

IMPLEMENT_DYNCREATE(CInetThread, CWinThread)

CInetThread::CInetThread()
{
}

CInetThread::CInetThread(CInetThreadParms *inetparms)
{
	
	inetparms->m_mythread = this;
	m_bAutoDelete = FALSE;
	m_pfnThreadProc = CInetThreadProc;
	m_pThreadParams = inetparms;

}

CInetThread::~CInetThread()
{
}

BOOL CInetThread::InitInstance()
{
	WSADATA Inetwsad;
	// TODO:  perform and per-thread initialization here
	inetdll = LoadLibrary("INETMIB1.DLL");
    if(!inetdll)
    {
        
		return FALSE;
	}
	
    
	SnmpExtensionQuery = (SEQUERY)GetProcAddress(inetdll,"SnmpExtensionQuery");
	SnmpExtensionInit = (SEINIT)GetProcAddress(inetdll,"SnmpExtensionInit");

  	if (SnmpExtensionQuery == NULL || SnmpExtensionInit == NULL)
		return FALSE;


	
	AsnObjectIdentifier mview;
	DWORD mtime;
	mtime = GetCurrentTime();
	snmpevent = NULL;
	BOOL rc;
    rc = (*SnmpExtensionInit)(mtime,&snmpevent,&mview);
	if (!rc)
	{
		
		return FALSE;
	}

	WSAStartup(0x0101,&Inetwsad);
	return TRUE;
}

int CInetThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CInetThread, CWinThread)
	//{{AFX_MSG_MAP(CInetThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInetThread message handlers

BOOL CInetThread::Start()
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

BOOL CInetThread::RunInet(CInetThreadParms *inetparms)
{
	//
	// setup default tabs. some routines will change as needed
	//

	
	
	bKill = FALSE;
	
	if (inetparms->allopts)
	{
		inetparms->connections = TRUE;
		inetparms->icmpstats = TRUE;
		inetparms->ifstats = TRUE;
		inetparms->ipstats = TRUE;
		inetparms->routtable = TRUE;
		inetparms->tcpstats = TRUE;
		inetparms->udpstats = TRUE;
	}

	INT Tabs1[7]  = {32,32,32,32,32,32,32};
	

	::SendMessage(inetparms->m_hwndNotifyInetDone,
				WM_USER_INET_TABS, 0, (LONG)Tabs1);


	if (inetparms->connections)
		DoConnections(inetparms);
	
	if (bKill)
		return TRUE;

	if(inetparms->routtable)
		DoRouteTable(inetparms);

	if (bKill)
		return TRUE;

	INT Tabs[7]  = {100,100,100,100,100,100,100};
	::SendMessage(inetparms->m_hwndNotifyInetDone,
				WM_USER_INET_TABS, 0, (LONG)Tabs);

	if(inetparms->icmpstats)
		DoIcmpStats(inetparms);

	if (bKill)
		return TRUE;

	if(inetparms->ifstats)
		DoIfStats(inetparms);

	if (bKill)
		return TRUE;

	if(inetparms->ipstats)
		DoIpStats(inetparms);

	if (bKill)
		return TRUE;


	if(inetparms->tcpstats)
		DoTcpStats(inetparms);

	if (bKill)
		return TRUE;

	if(inetparms->udpstats)
		DoUdpStats(inetparms);

	

	return TRUE;




}

void CInetThread::Free_Var(RFC1157VarBind *var)
{
		// For NT we must SnmpMemFree the name and value.
  // for 95 the name we allocated ourselves, and the value
  // is static
  SnmpUtilMemFree(var->name.ids);
    // Free the mem block in the value bit depending on what it is...
  switch(var->value.asnType)
  {
    case ASN_SEQUENCE:
    case ASN_OCTETSTRING:
    case ASN_RFC1155_IPADDRESS:
    case ASN_RFC1155_OPAQUE:
      // AsnOctetString is the base type for all the complex types.
    if(var->value.asnValue.string.dynamic)
        SnmpUtilMemFree(var->value.asnValue.string.stream);
  }
  

}

void CInetThread::Make_Oid(AsnObjectIdentifier* dst,UINT n, UINT* src)
{
			// Fill in the length
	dst->idLength = n;
	dst->ids = NULL;
	dst->ids = (UINT*)SnmpUtilMemAlloc(sizeof(UINT)*n);
	CopyMemory(dst->ids,src,sizeof(UINT)*n);

}

BOOL CInetThread::DoConnections(CInetThreadParms *inetparms)
{
	int requestType;
	AsnInteger errorStatus;
	AsnInteger errorIndex;
	UINT ids_tcpconn[8] = {1,3,6,1,2,1,6,13};
	UINT ids_udpconn[8] = {1,3,6,1,2,1,7,5};
	AsnObjectIdentifier saveobj;
	RFC1157VarBind Getnextlist[1];
	RFC1157VarBindList Getnextbindlist = {Getnextlist,1};
	
	

	BOOL rc;
	CHAR textbuf[255];

	
	// pick up all the tcp connections
	Make_Oid(&Getnextlist[0].name,8,ids_tcpconn);

    Getnextlist[0].value.asnType = ASN_NULL;
   
      
    requestType = ASN_RFC1157_GETNEXTREQUEST;

	strcpy(textbuf,"Connection Information");
	PrintLine(inetparms,textbuf);
	PrintLine(inetparms,":");

	strcpy(textbuf,
	"Proto     Local Address\tForeign Address\tState");
	PrintLine(inetparms,textbuf);

   
    while(1)
	{

        
        rc = (*SnmpExtensionQuery)(requestType, &Getnextbindlist,
                           &errorStatus, &errorIndex);

		if (!rc)

            {
            // The API is indicating an error.
			wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

            PrintLine(inetparms,textbuf);

            break;
            }
        else
            {
            // The API succeeded, errors may be indicated from the remote
            // agent.


            // Test for end of subtree or end of MIB.

            if (errorStatus == SNMP_ERRORSTATUS_NOSUCHNAME)
			{
			
				break;
			}
			
			if (Getnextlist[0].value.asnType == 
				ASN_RFC1155_IPADDRESS)
			{
				
				break;

			}



            // Test for general error conditions or sucesss.

            if (errorStatus > 0)
			{
				wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

				PrintLine(inetparms,textbuf);
			
				break;
			}
            else
			{
				PrintConnInfo(inetparms,
							  &Getnextlist[0].name,
							  "TCP");
				
			}

		} // end if


		if (bKill)
		{
			Free_Var(&Getnextlist[0]);
			PrintLine(inetparms,"Netstat Interupt!");
			return TRUE;
			break;
		}
		SnmpUtilOidCpy(&saveobj,&Getnextlist[0].name);
			         
		Free_Var(&Getnextlist[0]);
	
		Make_Oid(&Getnextlist[0].name,saveobj.idLength,saveobj.ids);	
		

		Getnextlist[0].value.asnType = ASN_NULL;
		SnmpUtilOidFree(&saveobj);
	
        
	} // end while()

	// get all UDP Connections

	Make_Oid(&Getnextlist[0].name,8,ids_udpconn);

    Getnextlist[0].value.asnType = ASN_NULL;
   
      
    requestType = ASN_RFC1157_GETNEXTREQUEST;

	
    while(1)
	{

        
        rc = (*SnmpExtensionQuery)(requestType, &Getnextbindlist,
                           &errorStatus, &errorIndex);

		if (!rc)

            {
            // The API is indicating an error.

            wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

            PrintLine(inetparms,textbuf);

            break;
            }
        else
            {
            // The API succeeded, errors may be indicated from the remote
            // agent.


            // Test for end of subtree or end of MIB.

            if (errorStatus == SNMP_ERRORSTATUS_NOSUCHNAME)
			{
			
				break;
			}
			
			if (Getnextlist[0].value.asnType == ASN_INTEGER)
			{
				
				break;

			}



            // Test for general error conditions or sucesss.

            if (errorStatus > 0)
			{
				wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

				PrintLine(inetparms,textbuf);
			
				break;
			}
            else
			{
				PrintConnInfo(inetparms,
					&Getnextlist[0].name,"UDP");
				
			}

		} // end if

		if (bKill)
		{
			Free_Var(&Getnextlist[0]);
			PrintLine(inetparms,"Netstat Interupt!");
			return TRUE;
			break;
		}
		SnmpUtilOidCpy(&saveobj,&Getnextlist[0].name);
			         
		Free_Var(&Getnextlist[0]);
	
		Make_Oid(&Getnextlist[0].name,saveobj.idLength,saveobj.ids);	
		

		Getnextlist[0].value.asnType = ASN_NULL;
		SnmpUtilOidFree(&saveobj);
	
        
	} // end while()

	PrintLine(inetparms,":");
	return TRUE;

}

BOOL CInetThread::PrintConnInfo(CInetThreadParms *inetparms,
								AsnObjectIdentifier * obj,
								CHAR * conntype)
{

	INT tcpvarbinds = 5;
	INT udpvarbinds = 2;
	INT q;
	AsnInteger dispstate;
	AsnInteger localport;
	AsnInteger remoteport;

	AsnInteger errorStatus;
	AsnInteger errorIndex;
	
	RFC1157VarBind tcplist[5];
	RFC1157VarBindList tcpbindlist = {tcplist,tcpvarbinds};
	RFC1157VarBind udplist[2];
	RFC1157VarBindList udpbindlist = {udplist,udpvarbinds};
	CHAR textbuf[255];
	BYTE *routes;
	u_long localaddr;
	u_long remoteaddr;
	CHAR szlocaladdr[128];
	CHAR szremoteaddr[128];
	CHAR szlocalhost[128];
	CHAR *szTempName;
	struct in_addr convaddr;
	struct hostent *resolve_addr;
	int rc;

	rc = strcmp(conntype,"TCP");
	if (rc == 0)
	{
		for(q = 0; q<tcpvarbinds; q++)   // for for #of var binds
		{
			
			Make_Oid(&tcplist[q].name,obj->idLength,obj->ids);
			tcplist[q].name.ids[9] = q+1;
			tcplist[q].value.asnType = ASN_NULL;
		}
	
		

		rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
						&tcpbindlist,
						&errorStatus,
						&errorIndex);


		if (!rc)

            {
            // The API is indicating an error.

            wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

            PrintLine(inetparms,textbuf);

            return FALSE;
            }

		//
		// build connstate table to look up the name. 
		// convert the ip addr from BYTE* to u_long then inet_ntoa
		// the ports are int values.
		//
		

		dispstate = tcplist[0].value.asnValue.number;    // State 

		
		// local address
		routes = tcplist[1].value.asnValue.string.stream;

		//
		// convert to ULONG leave net order in tact
		//

		localaddr = (*routes<<24) | (*(routes+1)<<16) |
							 (*(routes+2)<<8) | *(routes+3);
					
		//values1 = list[1].value.asnValue.;
		// local port
		localport = tcplist[2].value.asnValue.number;

		// remote address

		routes = tcplist[3].value.asnValue.string.stream;
		remoteaddr = (*routes<<24) | (*(routes+1)<<16) |
							 (*(routes+2)<<8) | *(routes+3);
		

		localaddr = ntohl(localaddr);
		remoteaddr = ntohl(remoteaddr);

		convaddr.s_addr = localaddr;
		szTempName = inet_ntoa(convaddr);
		strcpy(szlocaladdr,szTempName);

		convaddr.s_addr = remoteaddr;
		szTempName = inet_ntoa(convaddr);
		strcpy(szremoteaddr,szTempName);

		if (inetparms->resolveaddrs)
		{
			rc = strncmp(szlocaladdr,"127",3);
			if ((localaddr == INADDR_ANY) ||  //0.0.0.0
				(rc == 0))
				 
			{
	     		 gethostname(szlocalhost,sizeof(szlocalhost));
				 strcpy(szlocaladdr,szlocalhost);
			}
			else
			{
				resolve_addr = gethostbyaddr((CHAR *)&localaddr,
												4,AF_INET);
				if (resolve_addr)
					strcpy(szlocaladdr,resolve_addr->h_name);
			}

			if (remoteaddr != INADDR_ANY)
			{
				remoteport = tcplist[4].value.asnValue.number;
				resolve_addr = gethostbyaddr((CHAR *)&remoteaddr,
												4,AF_INET);
			    if (resolve_addr)
					strcpy(szremoteaddr,resolve_addr->h_name);
			}
			else
				remoteport = 0;


		}
			// remote port
		
		


		

		wsprintf(textbuf,"TCP     %s:%d \t%s:%d \t%s",
			szlocaladdr,
			localport,
			szremoteaddr,
			remoteport,
			StateTable[dispstate - 1].state);

		PrintLine(inetparms,textbuf);

			
		for(int x=0; x<tcpvarbinds; x++)
		Free_Var(&tcplist[x]);

		return TRUE;
	} // end if TCP

	rc = strcmp(conntype,"UDP");
	if (rc == 0)
	
	{
		for(q = 0; q<udpvarbinds; q++)   // for for #of var binds
		{
			
			Make_Oid(&udplist[q].name,obj->idLength,obj->ids);
			udplist[q].name.ids[9] = q+1;
			udplist[q].value.asnType = ASN_NULL;
		}
	
	  
		rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
						&udpbindlist,
						&errorStatus,
						&errorIndex);


		if (!rc)

            {
            // The API is indicating an error.

            wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

            PrintLine(inetparms,textbuf);

            return FALSE;
            }
		// local address
		routes = udplist[0].value.asnValue.string.stream;

		//
		// convert to ULONG leave net order in tact
		//

		localaddr = (*routes<<24) | (*(routes+1)<<16) |
							 (*(routes+2)<<8) | *(routes+3);
					

		// local port
		localport = udplist[1].value.asnValue.number;

		

		localaddr = ntohl(localaddr);
		

		convaddr.s_addr = localaddr;
		szTempName = inet_ntoa(convaddr);
		strcpy(szlocaladdr,szTempName);

		strcpy(szremoteaddr,"*:*");

		if (inetparms->resolveaddrs)
		{
			rc = strncmp(szlocaladdr,"127",3);
			if ((localaddr == INADDR_ANY) ||  //0.0.0.0
				(rc == 0))
				 
			{
	     		 gethostname(szlocalhost,sizeof(szlocalhost));
				 strcpy(szlocaladdr,szlocalhost);
			}
			else
			{
				resolve_addr = gethostbyaddr((CHAR *)&localaddr,
												4,AF_INET);
				if (resolve_addr)
					strcpy(szlocaladdr,resolve_addr->h_name);
			}
		}
		

		wsprintf(textbuf,"UDP    %s:%i\t%s",
			szlocaladdr,
			localport,
			szremoteaddr);
		

		PrintLine(inetparms,textbuf);

			
		for(int x=0; x<udpvarbinds; x++)
		Free_Var(&udplist[x]);

		return TRUE;
	} // end if UDP

	// no type 
	return FALSE;

}

BOOL CInetThread::PrintLine(CInetThreadParms *inetparms,
							CHAR * line)
{
	::SendMessage(inetparms->m_hwndNotifyInetDone,
				WM_USER_INET_PRINT, 0, (LONG)line);

	return TRUE;
}

BOOL CInetThread::DoIcmpStats(CInetThreadParms *inetparms)
{

	int numvarbinds = 26;
	DWORD value1;
	DWORD value2;
	DWORD values;
	CHAR textbuf[256];
	int startpt = 0;  // start 1 less makes logic better
	


	AsnInteger errorStatus;
	AsnInteger errorIndex;
	
	RFC1157VarBind list[26];
	RFC1157VarBindList bindlist = {list,26};
	UINT ids_icmpstats[9] = {1,3,6,1,2,1,5,0,0};
	int q;
	int rc;
	
	
    for(q = 0; q<numvarbinds; q++)   // for for #of var binds
	{
		ids_icmpstats[7] = ++startpt;  // plug byte 7
		Make_Oid(&list[q].name,9,ids_icmpstats);
		list[q].value.asnType = ASN_NULL;
		
	}
	
	

	
	  
	rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
						&bindlist,
						&errorStatus,
						&errorIndex);

	if (!rc)
		{
            // The API is indicating an error.

            wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

            PrintLine(inetparms,textbuf);

            return FALSE;
        }

	  
	wsprintf(textbuf,"ICMP Statistics:\tSend\tRecv");  
	PrintLine(inetparms,textbuf);

	value1 = list[13].value.asnValue.counter;
	value2 = list[0].value.asnValue.counter;
	wsprintf(textbuf,"MSGS \t%d\t%d",
			 value1,
			 value2);
	PrintLine(inetparms,textbuf);

	
		
	value1 = list[14].value.asnValue.counter;
	value2 = list[1].value.asnValue.counter;
	
	wsprintf(textbuf,"Errors \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);

	
	value1 = list[15].value.asnValue.counter;	
	value2 = list[2].value.asnValue.counter;
	wsprintf(textbuf,"Dest Unreach \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);

	value1 = list[16].value.asnValue.counter;	 
	value2 = list[3].value.asnValue.counter;
	wsprintf(textbuf,"Time Exceeded \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);


	values = list[17].value.asnValue.counter;	
	values = list[4].value.asnValue.counter;
	wsprintf(textbuf,"Parm Problems \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);

	
	value1 = list[18].value.asnValue.counter;
	value2 = list[5].value.asnValue.counter;
	wsprintf(textbuf,"Source Quenches \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);

	
	value1 = list[19].value.asnValue.counter;	
	value2 = list[6].value.asnValue.counter;
	wsprintf(textbuf,"Redirects \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);


	value1 = list[20].value.asnValue.counter; 	  
	value2 = list[7].value.asnValue.counter;
	wsprintf(textbuf,"Echos \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);

	value1 = list[21].value.asnValue.counter;
	value2 = list[8].value.asnValue.counter;
	wsprintf(textbuf,"Echo Replies \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);

	value1 = list[22].value.asnValue.counter;
	value2 = list[9].value.asnValue.counter;
	wsprintf(textbuf,"Timestamps \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);

	value1 = list[23].value.asnValue.counter;
	value2 = list[10].value.asnValue.counter;
	wsprintf(textbuf,"Timestamp Replies \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);
	
	value1 = list[24].value.asnValue.counter;
	value2 = list[11].value.asnValue.counter;
	wsprintf(textbuf,"Addr Mask Req \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);

	value1 = list[25].value.asnValue.counter;
	value2 = list[12].value.asnValue.counter;
	wsprintf(textbuf,"Addr Mask Replies \t%d\t%d",
			value1,
			value2);
	PrintLine(inetparms,textbuf);

	
	PrintLine(inetparms,":");
	
	for(int x=0; x<numvarbinds; x++)
		Free_Var(&list[x]);

	return TRUE;

}

BOOL CInetThread::DoIfStats(CInetThreadParms *inetparms)
{
	int numvarbinds = 12;
	AsnCounter values1;
	AsnCounter values2;
	AsnInteger numofinterfaces;
	CHAR textbuf[256];
	CHAR catbuf[256];
	int startpt = 9;  // start 1 less makes logic better
	
	UINT reqids[12] = {2,10,16,11,17,12,18,13,19,14,20,15};


	AsnInteger errorStatus;
	AsnInteger errorIndex;
	
	RFC1157VarBind list[12];
	RFC1157VarBindList bindlist = {list,12};

	//
	UINT ids_ifstats[11] = {1,3,6,1,2,1,2,2,1,0,0};
	//                                        x n
	//                           where x = mibtype (offset =9) 
	//                                 n = interface # (off = 10)
	UINT ifstatlen = 11;

	UINT ids_ifnumber[9] = {1,3,6,1,2,1,2,1,0};
	RFC1157VarBind Singlelist[1];
	RFC1157VarBindList Singlebindlist = {Singlelist,1};
	int q;
	int rc;
	

	//
	// get number of interfaces
	//

	Make_Oid(&Singlelist[0].name,9,ids_ifnumber);
	Singlelist[0].value.asnType = ASN_NULL;

	rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
						&Singlebindlist,
						&errorStatus,
						&errorIndex);
	

	if (!rc)
		{
            // The API is indicating an error.

            wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

            PrintLine(inetparms,textbuf);

            return FALSE;
        }
	numofinterfaces = Singlelist[0].value.asnValue.number;
	Free_Var(&Singlelist[0]);

	wsprintf(textbuf,"Interface Statistics:");  
	PrintLine(inetparms,textbuf);
	
	while(numofinterfaces)
	{

	

		for(q = 0; q<numvarbinds; q++)   // for for #of var binds
		{
			ids_ifstats[9] = reqids[q];
			ids_ifstats[10] = numofinterfaces;  
			Make_Oid(&list[q].name,ifstatlen,ids_ifstats);
			list[q].value.asnType = ASN_NULL;
		}
	
	  
		rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
						&bindlist,
						&errorStatus,
						&errorIndex);

		if (!rc)
			{
            // The API is indicating an error.

            wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

            PrintLine(inetparms,textbuf);

            return FALSE;
            }



	
		
		lstrcpyn(textbuf,
				(LPCTSTR)list[0].value.asnValue.string.stream,
				list[0].value.asnValue.string.length+1);
		wsprintf(catbuf,"%s\tSend\tRecv",textbuf);
		PrintLine(inetparms,catbuf);
		PrintLine(inetparms," ");
	
	
		values1 = list[1].value.asnValue.counter;
		values2 = list[2].value.asnValue.counter;
		wsprintf(textbuf,"Bytes \t%d\t%d",
			values2,
			values1);
		
		PrintLine(inetparms,textbuf);

		
		values1 = list[3].value.asnValue.counter;
		values2 = list[4].value.asnValue.counter;
		wsprintf(textbuf,"Unicast \t%d\t%d",
			values2,
			values1);
		PrintLine(inetparms,textbuf);

		values1 = list[5].value.asnValue.counter;
		values2 = list[6].value.asnValue.counter;
		wsprintf(textbuf,"Non-Unicast \t%d\t%d",
			values2,
			values1);
		
		PrintLine(inetparms,textbuf);

		values1 = list[7].value.asnValue.counter;
		values2 = list[8].value.asnValue.counter;
		wsprintf(textbuf,"Discards \t%d\t%d",
			values2,
			values1);
		
		PrintLine(inetparms,textbuf);

		values1 = list[9].value.asnValue.counter;
		values2 = list[10].value.asnValue.counter;
		wsprintf(textbuf,"Errors \t%d\t%d",
			values2,
			values1);
		
		PrintLine(inetparms,textbuf);

		values1 = list[11].value.asnValue.counter;
		values2 = 0;
		wsprintf(textbuf,"UnknownProtos \t%d\t%d",
			values2,
			values1);
			
		PrintLine(inetparms,textbuf);
	
		for (int x=0;x<numvarbinds;x++)
		{
			Free_Var(&list[x]);
		}

		PrintLine(inetparms,":");
		numofinterfaces--;

	} // end WHILE

	return TRUE;

}

BOOL CInetThread::DoIpStats(CInetThreadParms *inetparms)
{

	int numvarbinds = 17;
	DWORD values;
	CHAR textbuf[256];
	int startpt = 0;  // start 1 less makes logic better
	
	int rc;

	AsnInteger errorStatus;
	AsnInteger errorIndex;
	
	RFC1157VarBind list[17];
	RFC1157VarBindList bindlist = {list,17};
	UINT ids_ipstats[9] = {1,3,6,1,2,1,4,0,0};
	UINT ids_ipvals[17] = {3,4,5,6,7,8,9,10,11,12,14,15,
						   16,17,18,19,23};
	int q;
	
	
    for(q = 0; q<numvarbinds; q++)   // for for #of var binds
	{
		ids_ipstats[7] = ids_ipvals[q];  // plug byte 7
		Make_Oid(&list[q].name,9,ids_ipstats);
		list[q].value.asnType = ASN_NULL;
		
	}
	
	

	
	  
	rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
						&bindlist,
						&errorStatus,
						&errorIndex);

	if (!rc)
		{
            // The API is indicating an error.

            wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

            PrintLine(inetparms,textbuf);

            return FALSE;
        }
	  
	  
	PrintLine(inetparms,"IP Statistics:");
	values = list[0].value.asnValue.counter;
	wsprintf(textbuf,"Packets Received \t%d",values);
	PrintLine(inetparms,textbuf);

		
	values = list[1].value.asnValue.counter;
	wsprintf(textbuf,"Received HDR Errors \t%d",values);
	PrintLine(inetparms,textbuf);

		
	values = list[2].value.asnValue.counter;
	wsprintf(textbuf,"Received ADDR Errors \t%d",values);
	PrintLine(inetparms,textbuf);

	values = list[3].value.asnValue.counter;
	wsprintf(textbuf,"Datagrams Forwarded \t%d",values);
	PrintLine(inetparms,textbuf);
	

	values = list[4].value.asnValue.counter;
	wsprintf(textbuf,"Unknown Protos Received \t%d",values);
	PrintLine(inetparms,textbuf);

	
	values = list[5].value.asnValue.counter;
	wsprintf(textbuf,"Received Packets Discarded \t%d",values);
	PrintLine(inetparms,textbuf);

	
	values = list[6].value.asnValue.counter;
	wsprintf(textbuf,"Received Packets Delivered \t%d",values);
	PrintLine(inetparms,textbuf);

	
	values = list[7].value.asnValue.counter;
	wsprintf(textbuf,"Output Requests \t%d",values);
	PrintLine(inetparms,textbuf);

	
	values = list[8].value.asnValue.counter;
	wsprintf(textbuf,"Routing Discards \t%d",values);
	PrintLine(inetparms,textbuf);

	
	values = list[9].value.asnValue.counter;
	wsprintf(textbuf,"Discarded Output Packets \t%d",values);
	PrintLine(inetparms,textbuf);

	
	values = list[10].value.asnValue.counter;
	wsprintf(textbuf,"Output Packet No Route \t%d",values);
	PrintLine(inetparms,textbuf);

	values = list[11].value.asnValue.counter;
	wsprintf(textbuf,"Reassembly Required \t%d",values);
	PrintLine(inetparms,textbuf);


	values = list[12].value.asnValue.counter;
	wsprintf(textbuf,"Reassembly Successful \t%d",values);
	PrintLine(inetparms,textbuf);

	values = list[13].value.asnValue.counter;
	wsprintf(textbuf,"Reassembly Failures \t%d",values);
	PrintLine(inetparms,textbuf);
//
	values = list[14].value.asnValue.counter;
	wsprintf(textbuf,"Successfully Fragmented \t%d",values);
	PrintLine(inetparms,textbuf);
//
	values = list[15].value.asnValue.counter;
	wsprintf(textbuf,"Failing Fragmentation \t%d",values);
	PrintLine(inetparms,textbuf);

	values = list[16].value.asnValue.counter;
	wsprintf(textbuf,"Fragments Created \t%d",values);
	PrintLine(inetparms,textbuf);

	PrintLine(inetparms,":");
	
	for(int x=0; x<numvarbinds; x++)
		Free_Var(&list[x]);
	return TRUE;

}

BOOL CInetThread::DoRouteTable(CInetThreadParms *inetparms)
{
	int requestType;
	AsnInteger errorStatus;
	AsnInteger errorIndex;
	UINT ids_iproutes[8] = {1,3,6,1,2,1,4,21};
	AsnObjectIdentifier saveobj;
	RFC1157VarBind Getnextlist[1];
	RFC1157VarBindList Getnextbindlist = {Getnextlist,1};


	BOOL rc;
	CHAR textbuf[255];



	// pick up all the tcp connections
	Make_Oid(&Getnextlist[0].name,8,ids_iproutes);

    Getnextlist[0].value.asnType = ASN_NULL;
   
      
    requestType = ASN_RFC1157_GETNEXTREQUEST;

	strcpy(textbuf,"Routing Table Information");
	PrintLine(inetparms,textbuf);
	PrintLine(inetparms,":");
	strcpy(textbuf,
	"Net Address\tMask Address\tGateway Address\tInterface");
	PrintLine(inetparms,textbuf);

   
    while(1)
	{

        
        rc = (*SnmpExtensionQuery)(requestType, &Getnextbindlist,
                           &errorStatus, &errorIndex);

		if (!rc)

            {
            // The API is indicating an error.

            wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

            PrintLine(inetparms,textbuf);

            break;
            }
        else
            {
            // The API succeeded, errors may be indicated from the remote
            // agent.


            // Test for end of subtree or end of MIB.

            if (errorStatus == SNMP_ERRORSTATUS_NOSUCHNAME)
			{
			
				break;
			}
			
			if (Getnextlist[0].value.asnType == 
				ASN_INTEGER)
			{
				
				break;

			}



            // Test for general error conditions or sucesss.

            if (errorStatus > 0)
			{
				wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

				PrintLine(inetparms,textbuf);
				break;
			}
            else
			{
				PrintRouteInfo(inetparms,&Getnextlist[0].name);
				
			}

		} // end if

		if (bKill)
		{
			Free_Var(&Getnextlist[0]);
			PrintLine(inetparms,"Netstat Interupt!");
			break;
		}
		SnmpUtilOidCpy(&saveobj,&Getnextlist[0].name);
			         
		Free_Var(&Getnextlist[0]);
	
		Make_Oid(&Getnextlist[0].name,saveobj.idLength,saveobj.ids);	
		

		Getnextlist[0].value.asnType = ASN_NULL;
		SnmpUtilOidFree(&saveobj);
	
        
	} // end while()

	PrintLine(inetparms,":");
	return TRUE;

}

BOOL CInetThread::PrintRouteInfo(CInetThreadParms *inetparms,AsnObjectIdentifier *obj)
{
	//struct hostent *resolve_addr;
	INT ipvarbinds = 5;
	
	INT q;
	AsnInteger metric;
	

	AsnInteger errorStatus;
	AsnInteger errorIndex;

	RFC1157VarBind iplist[5];
	RFC1157VarBindList ipbindlist = {iplist,ipvarbinds};
	RFC1157VarBind iflist[1];
	RFC1157VarBindList ifbindlist = {iflist,1};
	UINT ifreq[11] = {1,3,6,1,2,1,2,2,1,6,0};
	INT reqids[5] = {1,2,3,7,11};
	CHAR textbuf[255];
	BYTE *routes;
	u_long interfaceaddr;
	u_long gatewayaddr;
	u_long netaddr;
	u_long maskaddr;
	CHAR szinterfaceaddr[128];
	CHAR szgatewayaddr[128];
	CHAR sznetaddr[128];
	CHAR szmaskaddr[128];
	CHAR *szTempName;
	struct in_addr convaddr;
	int rc;



	for(q = 0; q<ipvarbinds; q++)   // for for #of var binds
	{
		
		Make_Oid(&iplist[q].name,obj->idLength,obj->ids);
		iplist[q].name.ids[9] = reqids[q];
		iplist[q].value.asnType = ASN_NULL;
	}

  
	rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
					&ipbindlist,
					&errorStatus,
					&errorIndex);


	if (!rc)
	{
		wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

        PrintLine(inetparms,textbuf);

        return FALSE;
	}
	//
	// set up call for interface mib physaddr
	//

	ifreq[10] = iplist[1].value.asnValue.number;
	Make_Oid(&iflist[0].name,11,ifreq);
	iflist[0].value.asnType = ASN_NULL;

	rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
					&ifbindlist,
					&errorStatus,
					&errorIndex);


	if (!rc)
	{
		wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

        PrintLine(inetparms,textbuf);

        return FALSE;
	}

	//
	// if physaddr exists use it else use gateway
	//
	if (iflist[0].value.asnValue.string.length != 0)
	{
		routes = iflist[0].value.asnValue.string.stream;
		
	}
	else
	{
		routes = iplist[3].value.asnValue.string.stream;
		
	}
	interfaceaddr = (*routes<<24) | (*(routes+1)<<16) |
						 (*(routes+2)<<8) | *(routes+3);


	//
	// build connstate table to look up the name. 
	// convert the ip addr from BYTE* to u_long then inet_ntoa
	// the ports are int values.
	//
	

	

	
	// local address
	routes = iplist[0].value.asnValue.string.stream;

	//
	// convert to ULONG leave net order in tact
	//

	netaddr = (*routes<<24) | (*(routes+1)<<16) |
						 (*(routes+2)<<8) | *(routes+3);
				
	
	// gateway address

	routes = iplist[3].value.asnValue.string.stream;
	gatewayaddr = (*routes<<24) | (*(routes+1)<<16) |
						 (*(routes+2)<<8) | *(routes+3);
	

	// mask address

	routes = iplist[4].value.asnValue.string.stream;
	maskaddr = (*routes<<24) | (*(routes+1)<<16) |
						 (*(routes+2)<<8) | *(routes+3);

	 
	metric = iplist[2].value.asnValue.number;

	gatewayaddr = ntohl(gatewayaddr);
	maskaddr = ntohl(maskaddr);
	netaddr = ntohl(netaddr);
	interfaceaddr = ntohl(interfaceaddr);

	convaddr.s_addr = maskaddr;
	szTempName = inet_ntoa(convaddr);
	strcpy(szmaskaddr ,szTempName);

	//
	
		
	convaddr.s_addr = gatewayaddr;
	szTempName = inet_ntoa(convaddr);
	strcpy(szgatewayaddr,szTempName);

	convaddr.s_addr = netaddr;
	szTempName = inet_ntoa(convaddr);
	strcpy(sznetaddr ,szTempName);

	convaddr.s_addr = interfaceaddr;
	szTempName = inet_ntoa(convaddr);
	strcpy(szinterfaceaddr ,szTempName);



		

	wsprintf(textbuf,"%s \t%s \t%s \t%s",
		sznetaddr,
		szmaskaddr,
		szgatewayaddr,
		szinterfaceaddr);
		//metric);

	PrintLine(inetparms,textbuf);

		
	for(int x=0; x<ipvarbinds; x++)
	{
		Free_Var(&iplist[x]);
	}

	Free_Var(&iflist[0]);
	return TRUE;

}

BOOL CInetThread::DoTcpStats(CInetThreadParms *inetparms)
{
	int numvarbinds = 8;
	DWORD values;
	CHAR textbuf[256];
	int startpt = 4;  // start 1 less makes logic better



	AsnInteger errorStatus;
	AsnInteger errorIndex;
	
	RFC1157VarBind list[8];
	RFC1157VarBindList bindlist = {list,8};
	UINT ids_tcpstats[9] = {1,3,6,1,2,1,6,0,0};
	int rc;

     
	
    for(int q = 0; q<numvarbinds; q++)   // for for #of var binds
	{
		ids_tcpstats[7] = ++startpt;  // plug byte 7
		Make_Oid(&list[q].name,9,ids_tcpstats);
		list[q].value.asnType = ASN_NULL;
	}

	
	  
	rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
						&bindlist,
						&errorStatus,
						&errorIndex);

	 
	if (!rc)
	{
	
		wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

        PrintLine(inetparms,textbuf);

        return FALSE;
	}
	
	PrintLine(inetparms,"TCP Statistics:");
	  // Set the value "active opens"
	values = list[0].value.asnValue.counter;
	  
	wsprintf(textbuf,"Active opens \t%d",values);
	PrintLine(inetparms,textbuf);
	  
	
	// Set the value "passive opens"
	values = list[1].value.asnValue.counter;
	wsprintf(textbuf,"Passive opens \t%d",values);
	PrintLine(inetparms,textbuf);

	  

	  // Set the value "attempts failed
	values = list[2].value.asnValue.counter;
	wsprintf(textbuf,"Attempts Failed \t%d",values);
	PrintLine(inetparms,textbuf);
	

	  // set the value "ressets established"
	values = list[3].value.asnValue.counter;
	wsprintf(textbuf,"Resets Established \t%d",values);
	PrintLine(inetparms,textbuf);
	
	  
	// Set  value "connections currently established"
	// check guage
	values = list[4].value.asnValue.counter;
	wsprintf(textbuf,"Current Sessions Established \t%d",values);
	PrintLine(inetparms,textbuf);
	

	  // Set value "tcp in segs"
	values = list[5].value.asnValue.counter;
	wsprintf(textbuf,"Segments Received \t%d",values);
	PrintLine(inetparms,textbuf);
	

	// Set the "tcp out segs".
	values = list[6].value.asnValue.counter;
	wsprintf(textbuf,"Segments Sent \t%d",values);
	PrintLine(inetparms,textbuf);
	
  
	  // set retrans
	values = list[7].value.asnValue.counter;
	wsprintf(textbuf,"Retransmitted Segments \t%d",values);
	PrintLine(inetparms,textbuf);
	
	PrintLine(inetparms,":");

	for(int x=0; x<numvarbinds; x++)
		Free_Var(&list[x]);

	return TRUE;

}

BOOL CInetThread::DoUdpStats(CInetThreadParms *inetparms)
{
	int numvarbinds = 4;
	DWORD values;
	CHAR textbuf[256];
	int startpt = 0;  // start 1 less makes logic better
	

	int rc;

	AsnInteger errorStatus;
	AsnInteger errorIndex;
	
	RFC1157VarBind list[4];
	RFC1157VarBindList bindlist = {list,4};
	UINT ids_udpstats[9] = {1,3,6,1,2,1,7,0,0};
	int q;
	
	
    for(q = 0; q<numvarbinds; q++)   // for for #of var binds
	{
		ids_udpstats[7] = ++startpt;  // plug byte 7
		Make_Oid(&list[q].name,9,ids_udpstats);
		list[q].value.asnType = ASN_NULL;
		
	}
	
	

	
	  
	rc = (*SnmpExtensionQuery)(ASN_RFC1157_GETREQUEST,
						&bindlist,
						&errorStatus,
						&errorIndex);

	 
	if (!rc)
	{
		wsprintf(textbuf,"SNMP Error Status = %d Index = %d",
						errorStatus,errorIndex);

        PrintLine(inetparms,textbuf);

        return FALSE;
	}
	  
	PrintLine(inetparms,"UDP Statistics:");
	values = list[0].value.asnValue.counter;
	wsprintf(textbuf,"Datagrams Received \t%d",values);
	PrintLine(inetparms,textbuf);

		
	values = list[1].value.asnValue.counter;
	wsprintf(textbuf,"No Ports \t%d",values);
	PrintLine(inetparms,textbuf);

		
	values = list[2].value.asnValue.counter;
	wsprintf(textbuf,"Receive Errors \t%d",values);
	PrintLine(inetparms,textbuf);

	values = list[3].value.asnValue.counter;
	wsprintf(textbuf,"Datagrams Sent \t%d",values);
	PrintLine(inetparms,textbuf);
	

	
	PrintLine(inetparms,":");
	
	for(int x=0; x<numvarbinds; x++)
		Free_Var(&list[x]);

	return TRUE;

	

}

BOOL CInetThread::CleanUp()
{
	FreeLibrary(inetdll);
	WSACleanup();
	return TRUE;


}

void CInetThread::Kill()
{
	bKill = TRUE;

}
