// ===================================================================
//     Class: CUT_SampleThread
//      File: UT_SmplT.cpp
//   Created: February 22, 1999
//   Revised: 
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
#include "UT_SmplT.h"
#include "UT_SmplS.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

CUT_SampleThread::CUT_SampleThread(){
}

CUT_SampleThread::~CUT_SampleThread(){
}


void CUT_SampleThread::OnConnect() {
	// each connection will out derived server to create a 
	// instance of this class and call this method.
	// Process the client requests here!

	LPSTR indata =  new char[1024];		// receive
	LPSTR outdata = new char[1024];		// send
	LPSTR pstring = new char[1024];		// store and parse

	ZeroMemory( indata, 1024 );
	ZeroMemory( outdata, 1024 );
	ZeroMemory( pstring, 1024 );

// v4.2 Unused...
//	long len = 1024;
	long index = 0;
	long chktime = 0;
	int  words = 0;

	char name[128];

	GetClientName(name,127);
	_snprintf(outdata, 1024,"Hello, %s\r\nWelcome to the sample server!\r\n\r\n", name);


	Send(outdata);

	for(;;) {	
		if(!IsConnected())
					break;		
		// SECTION 1
		// connect with a telnet client in non-line mode
		if(CUT_SUCCESS == WaitForReceive(0,500)) {
						// check connection 
			if(Receive(indata, 1) > 0)	{	// data rec'd
				if(*indata == 8) {			// handle backspace
					--index;
					if(0 > index) {			// avoid backing up
						index ^= index;		// past  beginning of line
						*pstring = 0;
					}
					else {
						Send("\b \b");
						*(pstring + index) = 0;
					}
				}
				else {
					Send(indata, 1);			// echo chars
					*(pstring + index) = *indata;	// accumulate data
					++index;						// advance index
				
					if(*indata == '\r' || 1023 == index) {
						*(pstring + index) = 0;
						words = CUT_StrMethods::GetParseStringPieces (pstring, " ");
						_snprintf(outdata, 1024,"\r\nYou entered %d words\r\n", words);
						Send(outdata);
						index ^= index;
					}
				}			
			}
		}	
		else {
			// SECTION 2
			++chktime;
			if (chktime > 10000) {
				if(!IsConnected())
					break;					// check connection 
				chktime ^= chktime;
			}
		}

		

		// SECTION 3
		// check for shutdown - this is not done for you 
		// by the base class.
		if(m_winsockclass_this->GetShutDownFlag ()) {
			Send("\r\nSystem going off line - please try again later...\r\n");
			break;
		}
	}

 	if(IsConnected())
		Send("****Disconnecting****\r\n");


	delete[] indata;
	delete[] outdata;
	delete[] pstring;

}

#pragma warning ( pop )