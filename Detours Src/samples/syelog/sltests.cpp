//////////////////////////////////////////////////////////////////////
//
//	File:		sltests.cpp
//	Module:		sltests.exe
//
//	Copyright 1999-2001, Microsoft Corporation. All rights reserved.
//
//	Microsoft Research Detours Package Version 1.5 (Build 46)
//
//  Test the socket-based connection to the syelog system-event logger.
//
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "syelog.h"

VOID MyErrExit(PCSTR pszMsg)
{
    fprintf(stderr, "Error %s: %d\n", pszMsg, GetLastError());
    exit(1);
}

//////////////////////////////////////////////////////////////////////////////
//
class Syelog
{
  public:
    static BOOL SetServer(PCSTR pszHost = NULL, INT nPort = 0, BYTE nFacility = 0);
    static BOOL Log(BYTE nSeverity, PCSTR pszMsg, ...);
    static BOOL Flush();
    static BOOL Disconnect();

  protected:
    static BOOL Connect();
    static BOOL Send(PCSTR pbData, INT cbData);
    
    static SOCKADDR_IN  s_serverAddr;
    static SOCKET       s_serverSock;
    static BYTE         s_nFacility;
};

SOCKADDR_IN Syelog::s_serverAddr;
SOCKET      Syelog::s_serverSock = INVALID_SOCKET;
BYTE        Syelog::s_nFacility = SYELOG_FACILITY_APPLICATION;

BOOL Syelog::SetServer(PCSTR pszHost, INT nPort, BYTE nFacility)
{
    if (nFacility != 0) {
        s_nFacility = nFacility;
    }
    
    WSADATA WsaData;
    INT err = WSAStartup(0x0101, &WsaData);
    if (err != 0) {
        fprintf(stderr, "WSAStartup() failed: %ld\n", WSAGetLastError());
        return FALSE;
    }
    
    // Connect to an agreed upon port on the host.  See the
    // commdef.h file for the actual port number
    //
    ZeroMemory(&s_serverAddr, sizeof (s_serverAddr));
    s_serverAddr.sin_family = AF_INET;
    s_serverAddr.sin_port = htons((nPort != 0) ? (USHORT)nPort : (USHORT)SYELOG_TCP_PORT);
    s_serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (pszHost) {
        PHOSTENT host = gethostbyname(pszHost);
        if (host == NULL) {
            // See if the host is specified in "dot address" form
            //
            s_serverAddr.sin_addr.s_addr = inet_addr(pszHost);
            if (s_serverAddr.sin_addr.s_addr == -1) {
                fprintf(stderr, "Syelog::SetServer Unknown remote host: %s\n", pszHost);
                return FALSE;
            }
        }
        else {
            CopyMemory(&s_serverAddr.sin_addr, host->h_addr, host->h_length);
        }
    }
    return TRUE;
}

BOOL Syelog::Connect()
{
    if (s_serverSock != INVALID_SOCKET) {
        return TRUE;
    }
    
    if (s_serverAddr.sin_family != AF_INET) {
        SetServer();
    }

    // Open a socket using the Internet Address family and TCP
    //
    s_serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (s_serverSock == INVALID_SOCKET) {
        fprintf(stderr, "Syelog::Connect: socket failed: %ld\n", WSAGetLastError());
        return FALSE;
    }

    INT err = connect(s_serverSock, (PSOCKADDR)&s_serverAddr, sizeof(s_serverAddr));
    if (err != 0) {
        fprintf(stderr, "Syelog::Connect: connect failed: %ld\n", WSAGetLastError());
        closesocket(s_serverSock);
        return FALSE;
    }
    return TRUE;
}

BOOL Syelog::Flush()
{
    FlushFileBuffers((HANDLE)s_serverSock);
    return TRUE;
}

BOOL Syelog::Disconnect()
{
    if (s_serverSock != INVALID_SOCKET) {
        // Close connection to remote host
        //
        INT err = closesocket(s_serverSock);
        if (err != 0) {
            fprintf(stderr, "Syelog::Disconnect closesocket failed: %d, %ld\n",
                    err, WSAGetLastError());
            return FALSE;
        }
    }
    return TRUE;
}

BOOL Syelog::Send(PCSTR pbData, INT cbData)
{
    if (pbData == NULL || cbData == 0) {
        return TRUE;
    }
    
    if (s_serverSock == INVALID_SOCKET) {
        if (!Connect()) {
            return FALSE;
        }
    }

    INT err = send(s_serverSock, pbData, cbData, 0);
    if (err != cbData) {
        fprintf(stderr, "Syelog::Send(%08x,%d) send failed: %d/%d/%d\n",
                pbData, cbData,
                err, WSAGetLastError(), GetLastError());
        return FALSE;
    }
    return TRUE;
}

static PCHAR do_hex(PCHAR pszOut, DWORD dwValue)
{
	CHAR szHex[9];
	for (int nHex = 7; nHex >= 0; nHex--) {
		szHex[nHex] = "0123456789ABCDEF"[dwValue & 0xf];
		dwValue >>= 4;
	}
	for (nHex = 0; nHex < 7 && szHex[nHex] == '0'; nHex++) {
		// skip leading zeros.
	}
	for (; nHex < 8; nHex++) {
		*pszOut++ = szHex[nHex];
	}
	return pszOut;
}

static PCHAR do_dec(PCHAR pszOut, DWORD dwValue)
{
	CHAR szDec[16];
	for (int nDec = 14; nDec >= 0; nDec--) {
		szDec[nDec] = "0123456789"[dwValue % 10];
		dwValue /= 10;
	}
	for (nDec = 0; nDec < 14 && szDec[nDec] == '0'; nDec++) {
		// skip leading zeros.
	}
	for (; nDec < 15; nDec++) {
		*pszOut++ = szDec[nDec];
	}
	return pszOut;
}

static VOID _VPrint(PCSTR pszMsg, va_list args, PCHAR pszBuffer, LONG cbBuffer)
{
	INT nDigits = 0;
	PCHAR pszOut = pszBuffer;
	pszBuffer[0] = '\0';

	__try {
		while (*pszMsg) {
			if (*pszMsg == '%') {
				pszMsg++;

				while (*pszMsg >= '0' && *pszMsg <= '9') {
					nDigits = nDigits * 10 + (*pszMsg++ - '0');
				}
				
				BOOL fLarge = FALSE;
				if (*pszMsg == 'h') {
					fLarge = FALSE;
					pszMsg++;
				}
				else if (*pszMsg == 'l') {
					fLarge = TRUE;
					pszMsg++;
				}

				if (*pszMsg == 's') {
					pszMsg++;
					PCHAR pszBuf = pszOut;
					PVOID pvData = va_arg(args, PVOID);
					
					__try {
						*pszOut++ = '\"';
						if (fLarge) {
							PWCHAR pwz = (PWCHAR)pvData;

							for (int n = 0; *pwz && n < 120; n++) {
								WCHAR w = *pwz++;
								*pszOut++ = (w >= ' ' && w < 127) ? (CHAR)w : '.';
							}
						}
						else {
							PCHAR psz = (PCHAR)pvData;
							
							for (int n = 0; *psz && n < 120; n++) {
								CHAR c = *psz++;
								*pszOut++ = (c >= ' ' && c < 127) ? c : '.';
							}
						}
						*pszOut++ = '\"';
					} __except(EXCEPTION_EXECUTE_HANDLER) {
						pszOut = pszBuf;
						*pszOut++ = 'x';
						pszOut = do_hex(pszOut, (DWORD)pvData);
					}
				}
				else if (*pszMsg == 'x') {
					pszMsg++;
					*pszOut++ = 'x';
					pszOut = do_hex(pszOut, va_arg(args, DWORD));
				}	
				else if (*pszMsg == 'd') {
					pszMsg++;
					pszOut = do_dec(pszOut, va_arg(args, DWORD));
				}	
				else {
					*pszOut++ = *pszMsg++;
				}
			}
			else {
				*pszOut++ = *pszMsg++;
			}
		}
		*pszOut = '\0';
		pszBuffer[cbBuffer - 1] = '\0';
	} __except(EXCEPTION_EXECUTE_HANDLER) {
		strcpy(pszBuffer, "<exception>");
	}
}

BOOL Syelog::Log(BYTE nSeverity, PCSTR pszMsg, ...)
{
    SYELOG_MESSAGE msg;

    msg.nFacility = s_nFacility;
    msg.nSeverity = nSeverity;
    msg.nProcessId = GetCurrentProcessId();
    GetSystemTimeAsFileTime(&msg.ftOccurance);
	
	va_list args;
	va_start(args, pszMsg);
	_VPrint(pszMsg, args, msg.szMessage, sizeof(msg.szMessage) - 1);
	va_end(args);

    msg.szMessage[sizeof(msg.szMessage)-1] = '\0';
    for (PCSTR pszEnd = msg.szMessage; *pszEnd; pszEnd++) {
        // no internal contents.
    }
    msg.nBytes = (USHORT)(pszEnd - ((PCSTR)&msg) + 1);
    
    return Send((PCSTR)&msg, msg.nBytes);
}

//////////////////////////////////////////////////////////////////////////////
//
BOOL fVerbose;
DWORD dwIterations;
DWORD dwTransferSize;
IN_ADDR RemoteIpAddress;

//////////////////////////////////////////////////////////////////////////////
//
int CDECL main(int argc, char *argv[])
{
    INT nSeverity = SYELOG_SEVERITY_INFORMATION;
    INT nPort = SYELOG_TCP_PORT;
    PCSTR pszHost = "localhost";
    BOOL fNeedHelp = FALSE;
    
	for (int arg = 1; arg < argc; arg++) {
		if (argv[arg][0] == '-' || argv[arg][0] == '/') {
			CHAR *argn = argv[arg] + 1;
			CHAR *argp = argn;
			while (*argp && *argp != ':')
				argp++;
			if (*argp == ':')
				*argp++ = '\0';
			
			switch (argn[0]) {

              case 'h':                                 // Host
              case 'H':
                pszHost = argp;
                break;

              case 'p':                                 // Port
              case 'P':
                nPort = strtoul(argp, NULL, 10);
                break;
                
              case 's':                                 // Severity
              case 'S':
                nSeverity = strtoul(argp, NULL, 10);
                break;
                
              case '?':
				fNeedHelp = TRUE;
				break;
				
              default:
				fNeedHelp = TRUE;
				printf("Bad argument: %ls:%ls\n", argn, argp);
				break;
			}
		}
		else {
            fNeedHelp = TRUE;
		}
	}
    if (fNeedHelp) {
        printf("Usage:\n"
               "    sltests [options]\n"
               "Options:\n"
               "    -f:facility\n"
               "    -h:host\n"
               "    -p:port\n"
               "    -s:severity\n"
               "\n");
        exit(1);
    }

    TIME_ZONE_INFORMATION tzi;
    GetTimeZoneInformation(&tzi);
    Syelog::Log((UCHAR)nSeverity, "sltests: Hello World!");
    GetTimeZoneInformation(&tzi);
    Syelog::Disconnect();
    GetTimeZoneInformation(&tzi);
    return 0;
}
//
///////////////////////////////////////////////////////////////// End of File.
