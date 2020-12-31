// =================================================================
//  class: CUT_EchoServer
//	class: CUT_EchoThread
//  File:  Echo_s.h
//  
//  Purpose:
//
//	  ECHO secure server
//       
// ===================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================

#if !defined(AFX_ECHO_S_H__22C99AAB_D54E_43E3_97F8_31CB1D906D9E__INCLUDED_)
#define AFX_ECHO_S_H__22C99AAB_D54E_43E3_97F8_31CB1D906D9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _WINSOCK_2_0_
    #define _WINSOCKAPI_    /* Prevent inclusion of winsock.h in windows.h   */
                            /* Remove this line if you are using WINSOCK 1.1 */
#endif

#include "ut_srvr.h"
#include "uh_ctrl.h"

class CUT_EchoThread;

//****************************************************************
//***	CUT_EchoServer class
//****************************************************************
class CUT_EchoServer : public CUT_WSServer  
{
friend CUT_EchoThread;

protected:
    // Create class instance callback, this is where a C_WSTHREAD clss is created
    CUT_WSThread    *CreateInstance();

    // This function is called so that the instance created above can be released
    void            ReleaseInstance(CUT_WSThread *ptr);

    // On display status
    virtual int     OnStatus(LPCTSTR StatusText);
#if defined _UNICODE
    virtual int     OnStatus(LPCSTR StatusText);
#endif

public:

    #ifdef UT_DISPLAYSTATUS 
        // The examples of a finger server in UT2.0 uses the history control.
        // Applications you will be developing may not need the functionality of the history 
        // control window.  This statement was left in as a define - to enable it from the 
        // project settings define  UT_DISPLAYSTATUS as a preprocessor defenition 
        // in the preprocessor category of the C++ tab (VC)
        CUH_Control *ctrlHistory;
    #endif      // #ifdef UT_DISPLAYSTATUS 

};

//****************************************************************
//***	CUT_EchoThread class
//****************************************************************
class CUT_EchoThread : public CUT_WSThread
{
public:
	// Called after establishing socket connection to initialize
	// security libraries, create security credentials, perform 
	// handshake and verify the security sertificate
	virtual int SocketOnConnected(SOCKET s, const char *lpszName);

protected:
	// Maximum connections reached
    virtual void    OnMaxConnect();

	// Client connected to the server
    virtual void    OnConnect(); 

	// Function can be overridden to handle security errors
	virtual void HandleSecurityError(char *lpszErrorDescription);

	// Last security error
	char	m_szLastError[1024];
};

#endif // !defined(AFX_ECHO_S_H__22C99AAB_D54E_43E3_97F8_31CB1D906D9E__INCLUDED_)
