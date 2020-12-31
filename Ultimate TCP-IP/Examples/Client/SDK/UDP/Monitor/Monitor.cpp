// Monitor.cpp : Defines the entry point for the console application.
//
// This little program just waits for data on port 9999.  

#include "stdafx.h"
#include "..\UDP_Client.h"

#pragma warning (push)
#pragma warning (disable : 4702)
// v4.2 this caused an 'unreachable code' warning at the return statement
int main(int /* argc */, char* /* argv[] */)
{
    // create a UDP_Client object
    CUDP_Client monitor;

    // bind to local port 9999.  Clients will need this number
    monitor.Open(9999);

    char buffer[256];
    int len;

	for(;;) {
        if(monitor.IsDataWaiting()) {
             len = 256;
             monitor.Read(buffer, len);
             buffer[len] = 0;
             if( 0 < len) {
                 printf("%d bytes received from %s ==>\n%s\n", len, monitor.GetRemoteAddress(), buffer);
             }
        }
    }
	return 0;
}
#pragma warning (pop)

