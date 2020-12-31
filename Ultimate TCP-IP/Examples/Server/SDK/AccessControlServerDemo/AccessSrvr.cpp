// ===================================================================
//     Class: CUT_AccessServer
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
#include "SampleSvr.h"
#include "AccessSampleThread.h"


CUT_AccessServer::CUT_AccessServer(){
	m_status = NULL;
}

CUT_AccessServer::~CUT_AccessServer(){
	m_bShutDown = TRUE;
	while(m_nNumConnections)
		Sleep(2);
}

CUT_WSThread* CUT_AccessServer::CreateInstance() {
	return new CUT_AccessThread;
}

void CUT_AccessServer::ReleaseInstance(CUT_WSThread * ptr) {

	
	delete ptr;
}

/***************************************************
OnStatus
    This virtual function is called each time we have any
	status information to display.
Params
	StatusText	- status text
Return
	UTE_SUCCESS - success   
****************************************************/
int CUT_AccessServer::OnStatus(LPCSTR   StatusText )
{
	if (m_status != NULL && !m_bShutDown )
		m_status->AddLine(StatusText);

	return UTE_SUCCESS;
}
