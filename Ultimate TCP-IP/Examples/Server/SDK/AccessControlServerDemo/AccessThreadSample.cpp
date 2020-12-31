// ===================================================================
//     Class: CUT_AccessThread
//      File: AccessThreadSample.cpp

//   Purpose: Sample CUT_Thread dervd class for server framework tutorial.
//			  Illustrates the discussion of the server framework in 
//			  the TCPIPSERVER help file.
// Developer: 
// ===================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================

#include "stdafx.h"
#include "UT_Srvr.h"
#include "SampleSvr.h"
#include "AccessSampleThread.h"

#pragma warning (push)
#pragma warning (disable : 4996)

CUT_AccessThread::CUT_AccessThread(){
}

CUT_AccessThread::~CUT_AccessThread(){
}

/**********************************************************************

**********************************************************************/
void CUT_AccessThread::OnConnect() {

	CUT_AccessServer	*ns 	= (CUT_AccessServer *)m_winsockclass_this;
	char				data[WSS_BUFFER_SIZE];
	long				len 	= WSS_BUFFER_SIZE;
	int 				nTries	= 0;
	int 				nCounter = 0;
	int 				scs = 5;	// just a small time value 
									// remove to be set by the class latter 
	
	// Send as status the address of connected client
	LPSTR	szClientAddress = inet_ntoa(m_clientSocketAddr.sin_addr);
	if(szClientAddress != NULL) 
	{
		_snprintf(data, WSS_BUFFER_SIZE,"%s connected", szClientAddress);
		ns->OnStatus(data);
	}
	else
		return;
	
	
     Send("Welcome to the Server Demo!!!!\r\n");
    
	// v4.2 change to eliminate C4127: conditional expression is constant
	for(;;)
    {
		scs = 5;	  // set the time to 5 seconds
		if ( !IsConnected())
			break;


		for (;scs;scs--) // loop for 5 seconds
		{
			// receive line 
			len = ReceiveLine(data,WSS_BUFFER_SIZE,1);
			//	
			if(ns->m_bShutDown )
			{
				return; 
			}
			if(0 != len) {
					CUT_StrMethods::RemoveCRLF(data);
					ns->OnStatus(data);
			   break;
			}
		}

		// out of read loop - assume if len = 0 we've timed out
		if(0 == len || ns->m_bShutDown) 
			break; 

		// increase number of tries 	
		nTries++;
		 
		 // check if we reached the number of tries too here
		nCounter = 0;
		while(!ns->m_aclObj.IsAddressAllowed(szClientAddress))
		{	
			Sleep(50);
			if(nCounter++ > 1000)
			{
				_snprintf(data, WSS_BUFFER_SIZE,"%s Disconnected", szClientAddress);
				Send("Shutting down!!\r\n");
				ns->OnStatus(data);	
				return;
			}
			if(ns->m_bShutDown )
			{
				Send("Shutting down!!\r\n");
				break; 
			}
		}

		// now that we have received a password 
		// lets check the password if it does corresponds to 
		// a good user password 
		// Our high tech password test
		if (_stricmp(data,"PASS") != 0 )
		{
			// so the password failed
			// what do we do now
			Send("WRONG\r\n");
			ns->m_aclObj.AddTempBlockedAddress (szClientAddress);
		}
		else
		{
			// good password so remove the client from the 
			// Temporary blocked list
			Send("GOOD\r\n");
			ns->m_aclObj.DeleteTempBlockedAddress (szClientAddress);
			nTries = 0;
		 }

		 // if the user has attempted to 
		 //connect more than the allowed number
		 // kick him out 
		 if (nTries > 3)
		 {
			Send("Maximum tries reached\r\n");
			break;
		 }
		 
		 ns->OnStatus(data);
	}

	_snprintf(data, WSS_BUFFER_SIZE,"%s Disconnected", szClientAddress);
	Send("Shutting down!!\r\n");
	ns->OnStatus(data);
	
	return;
}

#pragma warning(pop)