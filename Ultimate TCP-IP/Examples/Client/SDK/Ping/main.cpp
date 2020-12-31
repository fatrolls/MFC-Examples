// ===================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// NOTE: 
// 
//  Raw sockets are only available in Winsock 2.0 (or better)
//  and only network administrators or users with 
//  administrator previleges are permitted to create raw sockets.
//  i.e. If you are not an administrator (or do not have equivalent
//  access, this sample will fail.
//
//  To resolve this problem ask your system administrator to create
//  the following registry key:
//
//
//  HKLM\System\CurrentControlSet\Services\Afd\Parameters\DisableRawSecurity DWORD 1
// ===================================================================
#include "stdafx.h"

// suppress VC6 warnings
#pragma warning (push,3)
#include <iostream>
#pragma warning (pop)

#include "UT_ICMP.h"
#include "uterr.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

using namespace std;

// We'll derive a class from CUT_ICMP to override the OnError and 
// OnReceiveICMP methods.
class myPing : public CUT_ICMP
{
    void OnReceiveICMP()
    {
        cout << endl << GetResponseSequence() << ". " 
            << GetResponseDuration() << "ms" << " \t " 
            << GetResponseAddress() << "\t" 
            << GetResponseName() << endl 
            << "Type: " << GetResponseType() 
            << "  Code: " << GetResponseCode() << " "
            << GetResponseMessage() << endl;
        if(GetResponseFinished())
            cout << endl << "Data finshed." << endl;
    }
    
    // OnError is a member of the CUT_WSClient class, from which
    // CUT_ICMP inherits...
    int OnError(int error)
    {
        if(UTE_SUCCESS != error && UTE_ERROR != error) 
            cout << endl << CUT_ERR::GetErrorString(error) << endl;
        return error;
    }
public :
    myPing(){
    };
    ~myPing(){
    };    
};
int main()
{
    myPing icmp;
    char buf[MAX_PATH];
    char addressTmp[30];
    int done = 0;
    while (!done)
    {
        cout << "Enter name or address to ping or 'q' to exit: ";
        cin >> buf ;
        if(strlen(buf)==1 && *buf == 'q' || *buf == 'Q'){
            ++done;
            continue;
        }
        // the call to ping or traceroute will do the lookup as well, but we
        // can do it here for display then use the dotted IP in the call...
        if (!icmp.IsIPAddress(buf))
        {
            cout << "Looking up address..." << flush;
            if(icmp.GetAddressFromName(buf,addressTmp,
                              sizeof(addressTmp)/sizeof(char)-1) == CUT_SUCCESS)
            {
                cout << "Tracing " << addressTmp << endl;
                strcpy(buf, addressTmp);
            }
            else 
            {
                continue;
            }
        }
        else
        {
            cout << "Tracing " << buf << endl;
        }
        // set lookup and max timeouts
        // note that allowing lookups is time consuming 
        icmp.SetDoLookup(true);
        icmp.SetMaxTimeOuts(6);

        // icmp.Ping(buf, 5000, 32, 5);        
        // to change the program to a trace route comment the above line 
        // and uncomment the line below        
        icmp.TraceRoute  (buf, 5000, 32);
    }    
    return 0;
}
 
#pragma warning ( pop )