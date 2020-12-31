// initSock.cpp: implementation of the CinitSock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "main.h"
#include "initSock.h"
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CinitSock::CinitSock()
{
   WSADATA data;
   WSAStartup(MAKEWORD(2, 2), &data);
}

CinitSock::~CinitSock()
{
   WSACleanup();
}
