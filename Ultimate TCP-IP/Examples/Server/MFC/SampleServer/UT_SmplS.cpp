// ===================================================================
//     Class: CUT_SampleServer
//      File: UT_SmplS.cpp
//   Revised: 
//   Purpose: Sample server derived class for Help tuorial.
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
#include "UT_SmplS.h"
#include "UT_SmplT.h"


CUT_SampleServer::CUT_SampleServer(){
}

CUT_SampleServer::~CUT_SampleServer(){
	m_bShutDown = TRUE;
	while(m_nNumConnections)
		Sleep(50);
}

CUT_WSThread* CUT_SampleServer::CreateInstance() {
	return new CUT_SampleThread;
}

void CUT_SampleServer::ReleaseInstance(CUT_WSThread * ptr) {

	
	delete ptr;
}

int CUT_SampleServer::Start() {

	int result;

	// start our sample server - we'll use port 9000
	if(CUT_SUCCESS != (result = ConnectToPort(9000))) {
		return result;
		// rem - 0  =  CUT_SUCCESS
		//       1  =  WSAStartup error
		//       2  =  Socket creation error
		//		 3  =  Socket bind error
		//		 4  =  Listen call failed
	}

	
	return StartAccept();
}

