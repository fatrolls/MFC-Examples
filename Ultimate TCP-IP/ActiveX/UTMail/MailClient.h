//=================================================================
//  class: CUT_SMTPMailClient, CUT_POP3MailClient
//  File:  MailClient.h
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

#ifndef __MAILCLIENT_H_
#define __MAILCLIENT_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "ut_clnt.h"	
#include "pop3_c.h"	
#include "smtp_c.h"	


////////////////////////////////////////////////////////////////////
//	SMTP Mail class
////////////////////////////////////////////////////////////////////

class CUT_SMTPMailClient : protected CUT_SMTPClient {

protected:
		BOOL		m_bAbortFlag;			// TRUE if we are going to abort finger

public:
		CUT_SMTPMailClient();
		~CUT_SMTPMailClient();

        // Delegated function to be invoked to inform us of the message send progress
        virtual BOOL	OnSendMailProgress(long bytesSent,long totalBytes); 

		// Return TRUE if we are going to abort operation
		virtual BOOL	IsAborted();
};

////////////////////////////////////////////////////////////////////
//	POP3 Mail class
////////////////////////////////////////////////////////////////////

class CUT_POP3MailClient : protected CUT_POP3Client {

protected:
		BOOL		m_bAbortFlag;			// TRUE if we are going to abort finger

public:
		CUT_POP3MailClient();
		~CUT_POP3MailClient();

        // Virtual function to be overridden to report the save message progress
        virtual BOOL	OnSaveMsg(long bytesRetrieved);

		// Return TRUE if we are going to abort operation
		virtual BOOL	IsAborted();		
};


#endif
