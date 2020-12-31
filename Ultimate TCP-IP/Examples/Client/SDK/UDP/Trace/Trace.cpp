// Trace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\UDP_Client.h"

int main(int /* argc */, char* /* argv[] */)
{
    // lets setup an object for tracing...
    CUDP_Client tracer;
    
    // open a UDP socket for writing...
    // note that we don't need to specify a port, since we
    // don't expect clients to be sending us data.
    // (call tracer.GetLocalPort() to see what port was assigned)
    tracer.Open();

    // the write command can take optional address and port, but
    // since were going to be using this as a debug trace, why not just
    // set and forget...
    tracer.SetRemotePort(9999);
    tracer.SetRemoteAddress("127.0.0.1");

	tracer.Write("Hello World!");
	return 0;
}

