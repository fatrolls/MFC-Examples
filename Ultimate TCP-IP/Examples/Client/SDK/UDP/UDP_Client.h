// ===================================================================
//     Class: CUDP_Client
//      File: UDP_Client.h
//   Created: October 13, 1999
//   Revised: 
//   Purpose: Demonstrate CUT_WSClient UDP functionality
// Developer: Hugh D. Pea
// ===================================================================
// 
// ===================================================================
#ifndef _UDP_CLIENT_H_
#define _UDP_CLIENT_H_

#include "ut_clnt.h"

class CUDP_Client : public CUT_WSClient {
private:
	// private member declarations
	CUDP_Client(const CUDP_Client& );
	CUDP_Client operator=(const CUDP_Client&);

    char    m_fromAddress[32];
    
protected:
	// protected member declarations
    

public:
	// public member declarations

	CUDP_Client();
	virtual ~CUDP_Client();

    LPCSTR GetRemoteAddress();
    void   SetRemotePort(unsigned int port);
    int    SetRemoteAddress(LPSTR address);

    int Open(unsigned int port = 0, LPSTR address = NULL);
    int Read(LPSTR data, int &dataLen, unsigned long timeout = 1);
    int Write(LPSTR data, int len=-1, LPCSTR address = NULL, unsigned int port = 0);
};

#endif
