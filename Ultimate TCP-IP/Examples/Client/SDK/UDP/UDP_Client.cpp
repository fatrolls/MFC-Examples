// ===================================================================
//     Class: CUDP_Client
//      File: UDP_Client.cpp
//   Created: October 13, 1999
//   Revised: 
//   Purpose: Demonstrate CUT_WSClient UDP functionality
// Developer: Hugh D. Pea
// ===================================================================
// 
// ===================================================================

#include "ut_clnt.h"
#include "UDP_Client.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

CUDP_Client::CUDP_Client(){
}

CUDP_Client::~CUDP_Client(){
}

// useful after receive 
LPCSTR CUDP_Client::GetRemoteAddress()
{
    return m_fromAddress;
}

int CUDP_Client::SetRemoteAddress(LPSTR address)
{
    if(!IsIPAddress(address))
        return OnError(UTE_INVALID_ADDRESS);
    else
        strcpy(m_szAddress,address);
        
    return OnError(UTE_SUCCESS);
}

void CUDP_Client::SetRemotePort(unsigned int port)
{
    m_nRemotePort = port;
}

int CUDP_Client::Open(unsigned int port, LPSTR addr) 
{
    return OnError(CreateUDPSocket(port, 0, "", addr));
}

int  CUDP_Client::Read(LPSTR data,int &dataLen,unsigned long timeout)
{
    int retval = UTE_SUCCESS;

    if(TRUE == IsDataWaiting()) {
        retval = ReceiveFrom( data, dataLen, timeout);
        if (UTE_SUCCESS == retval) {
            // translate remote address to string
               sprintf((char*)m_fromAddress, "%d.%d.%d.%d", m_sockAddr.sin_addr.S_un.S_un_b.s_b1,
                              m_sockAddr.sin_addr.S_un.S_un_b.s_b2,
                              m_sockAddr.sin_addr.S_un.S_un_b.s_b3,
                              m_sockAddr.sin_addr.S_un.S_un_b.s_b4);
        }
    }
    return OnError(retval);
}

// make it easy - if remote port and remote address already set up, 
// and data is not binary, all we need to write is the string.
int CUDP_Client::Write(LPSTR data, int len, LPCSTR address, unsigned int port)
{
    if(NULL == data)
        return OnError(UTE_ERROR);

    if(address != NULL)
        strcpy(m_szAddress, address);

    if(port != 0)
        m_nRemotePort = port;

    int dataLen; 
    if (len == -1)
        dataLen = (int)strlen(data);
    else 
        dataLen = len;

    return OnError(SendTo(data, dataLen));
}

#pragma warning ( pop )