//=================================================================
//  class: CUT_SMTPMailClient, CUT_POP3MailClient
//  File:  MailClient.cpp
//
//  Implementation of CUT_SMTPMailClient, CUT_POP3MailClient
//
//=================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
//=================================================================

#include "stdafx.h"
#include "MailClient.h"
#include "ut_clnt.h"


////////////////////////////////////////////////////////////////////
//	SMTP Mail class
////////////////////////////////////////////////////////////////////

/***************************************************
CUT_SMTPMailClient
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CUT_SMTPMailClient::CUT_SMTPMailClient() :
		m_bAbortFlag(FALSE)				// Clear abort flag
{
}

/***************************************************
~CUT_SMTPMailClient
	Destructor.
Params
    none
Return
	none
****************************************************/
CUT_SMTPMailClient::~CUT_SMTPMailClient()
{
}

/***************************************************
IsAborted
    This virtual function is called during time consuming
	operations to check if we want to abort operatin
Params
    none
Return
    TRUE	- abort operation
	FALSE	- continue
****************************************************/
BOOL CUT_SMTPMailClient::IsAborted() {
	return m_bAbortFlag;
}

/********************************
OnSendMailProgress
  Virtual function to be overridden to inform the user
  of the send mail progress and to check if the user wants
  to cancel the process.
PARAM:
    long bytesSent  - number of bytes sent 
    long totalBytes - Total number of bytes for the message being processed
RETURN
    FALSE - cancel the send process
    TRUE  - Continue
*********************************/
BOOL CUT_SMTPMailClient::OnSendMailProgress(long bytesSent,long totalBytes){
    return !m_bAbortFlag;
}


////////////////////////////////////////////////////////////////////
//	POP3 Mail class
////////////////////////////////////////////////////////////////////

/***************************************************
CUT_SMTPMailClient
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CUT_POP3MailClient::CUT_POP3MailClient() :
		m_bAbortFlag(FALSE)				// Clear abort flag
{
}

/***************************************************
~CUT_SMTPMailClient
	Destructor.
Params
    none
Return
	none
****************************************************/
CUT_POP3MailClient::~CUT_POP3MailClient()
{
}

/***************************************************
IsAborted
    This virtual function is called during time consuming
	operations to check if we want to abort operatin
Params
    none
Return
    TRUE	- abort operation
	FALSE	- continue
****************************************************/
BOOL CUT_POP3MailClient::IsAborted() {
	return m_bAbortFlag;
}

/***************************************************
    Virtual function designed to be overridden to  
    receive report of progress of save message process.
PARAM
    bytesRetrieved - Number of bytes received so far
RETURN
    TRUE	- to continue
    FALSE	- to cancel
****************************************************/
BOOL CUT_POP3MailClient::OnSaveMsg(long bytesRetrieved) {
    return !m_bAbortFlag;
}
