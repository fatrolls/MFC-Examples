//////////////////////////////////////////////////////////////////////////////
//
//	Module:		syelogd.exe
//	File:		syelogd.cpp
//
//	Copyright:	1999-2001, Microsoft Corporation
//
//	Microsoft Research Detours Package Version 1.5 (Build 46)
//
#include <windows.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "syelog.h"

enum {
    CLIENT_SOCK                 = 0x10,
    CLIENT_AWAITING_SOCK_ACCEPT = 0x11,
    CLIENT_AWAITING_SOCK_HEADER = 0x12,
    CLIENT_AWAITING_SOCK_DATA   = 0x13,

    CLIENT_PIPE                 = 0x20,
    CLIENT_AWAITING_PIPE_ACCEPT = 0x21,
    CLIENT_AWAITING_PIPE_DATA   = 0x22,
};

typedef struct _CLISTATE : OVERLAPPED
{
    HANDLE          hFile;
    DWORD           dwState;
} CLISTATE, *PCLISTATE;

typedef struct _CLIENT : _CLISTATE
{ 
    SYELOG_MESSAGE  Message;
} CLIENT, *PCLIENT; 

typedef struct _CLIACCEPT : _CLISTATE
{
    PCLIENT         pClient;
} CLIACCEPT, *PCLIACCEPT; 

//////////////////////////////////////////////////////////////////////////////
//
BOOL        s_fLogEvents    = FALSE;    // Accept events from the NT Event Log.
BOOL        s_fLogSockets   = FALSE;    // Accept events from incoming sockets.
BOOL        s_fLogPipes     = TRUE;     // Accept events from incoming named pipes.
BOOL        s_fLogToScreen  = TRUE;     // Log output to screen.
HANDLE      s_hOutFile      = INVALID_HANDLE_VALUE;

LONG        s_nActiveClients = 0;
SOCKET      s_sListenSock;
CLIACCEPT   s_caListenSock;
LONGLONG    s_llStartTime;

//////////////////////////////////////////////////////////////////////////////
//
VOID MyErrExit(PCSTR pszMsg)
{
    fprintf(stderr, "SYELOGD: Error %d in %s.\n", GetLastError(), pszMsg);
    fflush(stderr);
    exit(1);
}

//////////////////////////////////////////////////////////////////////////////
//
static PCSTR FileTimeToString(PCHAR pszBuffer, DWORD cbBuffer, FILETIME ftTime)
{
    (void)cbBuffer;
    
    static BOOL bGotTzi = FALSE;
    static DWORD dwTzi = TIME_ZONE_ID_UNKNOWN;
    static TIME_ZONE_INFORMATION tzi;
    if (!bGotTzi) {
        dwTzi = GetTimeZoneInformation(&tzi);
        if (dwTzi == TIME_ZONE_ID_UNKNOWN) {
            ZeroMemory(&tzi, sizeof(tzi));
        }
        bGotTzi = TRUE;
    }
    SYSTEMTIME stUtc;
    SYSTEMTIME stLocal;
    
    pszBuffer[0] = '\0';
    
    if (!FileTimeToSystemTime(&ftTime, &stUtc)) {
        sprintf(pszBuffer, "ft:%16I64d", *(LONGLONG *)&ftTime);
        return pszBuffer;
    }
    else if (!SystemTimeToTzSpecificLocalTime(&tzi, &stUtc, &stLocal)) {
        CopyMemory(&stLocal, &stUtc, sizeof(stLocal));
    }
    
    sprintf(pszBuffer, "%4d%02d%02d%02d%02d%02d%03d",
            stLocal.wYear,
            stLocal.wMonth,
            stLocal.wDay,
            stLocal.wHour,
            stLocal.wMinute,
            stLocal.wSecond,
            stLocal.wMilliseconds);
    return pszBuffer;
}

PCLIENT CreateConnection(HANDLE hCompletionPort, HANDLE hFile)
{
    if (hFile == NULL) {
        MyErrExit("CreateConnection with hFile == NULL");
    }

    // Allocate the client data structure.
    //
    PCLIENT pClient = (PCLIENT) GlobalAlloc(GPTR, sizeof(CLIENT)); 
    if (pClient == NULL) 
        MyErrExit("GlobalAlloc pClient"); 

    ZeroMemory(pClient, sizeof(*pClient));
    pClient->hFile = hFile;
    pClient->dwState = 0;

    // Associate file with our complietion port.
    //
    if (!CreateIoCompletionPort(pClient->hFile, hCompletionPort, (DWORD)pClient, 0)) {
        MyErrExit("CreateIoComplietionPort pClient");
    }
    
    return pClient;
}

BOOL CloseConnection(PCLIENT pClient)
{
    InterlockedDecrement(&s_nActiveClients);
    if (pClient != NULL) {
        if (pClient->hFile != INVALID_HANDLE_VALUE) {
            FlushFileBuffers(pClient->hFile);
            if (pClient->dwState & CLIENT_PIPE) {
                if (!DisconnectNamedPipe(pClient->hFile)) {
                    MyErrExit("DisconnectNamedPipe");
                }
            }
            CloseHandle(pClient->hFile);
            pClient->hFile = INVALID_HANDLE_VALUE;
        }
        GlobalFree(pClient);
        pClient = NULL;
    }
    return TRUE;
}

// Creates a pipe instance and initiate an accept request. 
// 
PCLIENT CreatePipeConnection(HANDLE hCompletionPort) 
{ 
    HANDLE hPipe = CreateNamedPipe(SYELOG_PIPE_NAME,           // pipe name 
                                   PIPE_ACCESS_INBOUND |       // read-only access 
                                   FILE_FLAG_OVERLAPPED,       // overlapped mode 
                                   PIPE_TYPE_MESSAGE |         // message-type pipe 
                                   PIPE_READMODE_MESSAGE |     // message read mode 
                                   PIPE_WAIT,                   // blocking mode 
                                   PIPE_UNLIMITED_INSTANCES,   // unlimited instances 
                                   0,                          // output buffer size 
                                   0,                          // input buffer size 
                                   20000,                      // client time-out 
                                   NULL);                      // no security attributes
    if (hPipe == INVALID_HANDLE_VALUE) 
        MyErrExit("CreatePipe"); 

    PCLIENT pClient = CreateConnection(hCompletionPort, hPipe);
    
    pClient->dwState = CLIENT_AWAITING_PIPE_ACCEPT;
    if (!ConnectNamedPipe(hPipe, pClient)) {
        if (GetLastError() != ERROR_IO_PENDING &&
            GetLastError() != ERROR_PIPE_LISTENING) {
            MyErrExit("ConnectNamedPipe");
        }
    }
    else {
        printf("SYELOGD: ConnectNamedPipe accepted immediately.\n");
    }
    return pClient;
} 

// Creates a socket instance and initiate an accept request. 
// 
PCLIENT CreateSockConnection(HANDLE hCompletionPort) 
{
    DWORD dwBytes;

    SOCKET sSock = socket(AF_INET, SOCK_STREAM, 0);
    if (sSock == INVALID_SOCKET) 
        MyErrExit("socket"); 

    PCLIENT pClient = CreateConnection(hCompletionPort, (HANDLE)sSock);

    s_caListenSock.dwState = CLIENT_AWAITING_SOCK_ACCEPT;
    s_caListenSock.pClient = pClient;
    if (!AcceptEx(s_sListenSock, sSock,
                  pClient->Message.szMessage, 0, 32, 32, &dwBytes, pClient)) {
        if (WSAGetLastError() != ERROR_IO_PENDING) {
            MyErrExit("AcceptEx");
        }
    }
    else {
        printf("SYELOGD: AcceptEx accepted immediately.\n");
    }
    return pClient;
} 

BOOL LogMessage(PSYELOG_MESSAGE pMessage, DWORD nBytes)
{
    // Sanity check the size of the message.
    //
    if (nBytes > pMessage->nBytes) {
        nBytes = pMessage->nBytes;
    }
    if (nBytes >= sizeof(*pMessage)) {
        nBytes = sizeof(*pMessage) - 1;
    }

    // Don't log message if there isn't and message text.
    //
    if (nBytes <= offsetof(SYELOG_MESSAGE, szMessage)) {
        return FALSE;
    }
    
    CHAR szTime[64];
    FileTimeToString(szTime, sizeof(szTime), pMessage->ftOccurance);
    
    PCHAR pszMsg = pMessage->szMessage;
    while (*pszMsg) {
        pszMsg++;
    }
    while (pszMsg > pMessage->szMessage && isspace(pszMsg[-1])) {
        *--pszMsg = '\0';
    }

    if (s_fLogToScreen) {
        printf("%-17.17s %4d %02x.%02x: %s\n",
               szTime,
               pMessage->nProcessId,
               pMessage->nFacility,
               pMessage->nSeverity,
               pMessage->szMessage);
    }
    if (s_hOutFile != INVALID_HANDLE_VALUE) {
		DWORD cbWritten = 0;
        CHAR szBuf[4096];
		INT cbToWrite;
	
        cbToWrite = _snprintf(szBuf, sizeof(szBuf), "%-17.17s %4d %02x.%02x: %s\n",
                              szTime,
                              pMessage->nProcessId,
                              pMessage->nFacility,
                              pMessage->nSeverity,
                              pMessage->szMessage);

        if (cbToWrite < 0) {
            szBuf[sizeof(szBuf)-2] = '\n';
            szBuf[sizeof(szBuf)-1] = '\0';
            cbToWrite = sizeof(szBuf);
        }
		WriteFile(s_hOutFile, szBuf, cbToWrite, &cbWritten, NULL);
    }
    return TRUE;
}

DWORD WINAPI WorkerThread(LPVOID pvVoid)
{
    PCLIENT pClient;
    BOOL b;
    LPOVERLAPPED lpo;
    DWORD nBytes;
    DWORD err;
    HANDLE hCompletionPort = (HANDLE)pvVoid;

    for (;;) {
        pClient = NULL;
        nBytes = 0;
        b = GetQueuedCompletionStatus(hCompletionPort,
                                      &nBytes, (PDWORD)&pClient, &lpo, INFINITE);
        if (!b && lpo == NULL) {
            MyErrExit("GetQueuedCompletionState");
            break;
        }
        else if (!b) {
            if (pClient) {
#if 0                
                fprintf(stdout, "GetQueuedCompletionStatus failed %d %08x\n",
                        GetLastError(), pClient);
#endif                
                CloseConnection(pClient);
            }
            continue;
        }
        
        switch (pClient->dwState) {

          case CLIENT_AWAITING_SOCK_ACCEPT: {
              PCLIACCEPT pCliAccept = (PCLIACCEPT)pClient;
              pClient = pCliAccept->pClient;
              
              err = setsockopt((SOCKET)pClient->hFile, 
                               SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, 
                               (char *)&s_sListenSock, sizeof(s_sListenSock)); 
              
              pClient->dwState = CLIENT_AWAITING_SOCK_HEADER;
              b = ReadFile(pClient->hFile,
                           &pClient->Message,
                           offsetof(SYELOG_MESSAGE, szMessage),
                           &nBytes,
                           pClient);

              CreateSockConnection(hCompletionPort);
              break;
          }

          case CLIENT_AWAITING_SOCK_HEADER: {
              if (nBytes < offsetof(SYELOG_MESSAGE, szMessage)) {
                  CloseConnection(pClient);
                  continue;
              }
              
              pClient->dwState = CLIENT_AWAITING_SOCK_DATA;
              b = ReadFile(pClient->hFile,
                           &pClient->Message.szMessage,
                           pClient->Message.nBytes - nBytes,
                           &nBytes,
                           pClient);
          }

          case CLIENT_AWAITING_SOCK_DATA: {
              pClient->Message.szMessage[nBytes] = '\0';
              LogMessage(&pClient->Message,
                         offsetof(SYELOG_MESSAGE, szMessage) + nBytes);
              
              pClient->dwState = CLIENT_AWAITING_SOCK_HEADER;
              b = ReadFile(pClient->hFile,
                           &pClient->Message,
                           offsetof(SYELOG_MESSAGE, szMessage),
                           &nBytes,
                           pClient);
              break;
          }
          
          case CLIENT_AWAITING_PIPE_ACCEPT: {
              pClient->dwState = CLIENT_AWAITING_PIPE_DATA;
              b = ReadFile(pClient->hFile, 
                           &pClient->Message, 
                           sizeof(pClient->Message),
                           &nBytes,
                           pClient);

              CreatePipeConnection(hCompletionPort);
              break;
          }

          case CLIENT_AWAITING_PIPE_DATA: {
              if (nBytes < offsetof(SYELOG_MESSAGE, szMessage)) {
                  CloseConnection(pClient);
              }

              LogMessage(&pClient->Message, nBytes);
              
              pClient->dwState = CLIENT_AWAITING_PIPE_DATA;
              b = ReadFile(pClient->hFile, 
                           &pClient->Message, 
                           sizeof(pClient->Message),
                           &nBytes,
                           pClient);
              break;
          }

          default:
            printf("SYELOGD: Unknown state: %d\n", pClient->dwState);
            break;
        }
    }
    return 0;
}

DWORD WINAPI EventLogThread(LPVOID pvVoid)
{
    const DWORD BUFFER_SIZE = 16384;
    const LONGLONG llSecsTo1970 = 116444736000000000;
    
    HANDLE hEventLog = (HANDLE)pvVoid;
    HANDLE hReady = CreateEvent(NULL, TRUE, TRUE, NULL);
    BYTE bBuffer[BUFFER_SIZE]; 
    EVENTLOGRECORD *pevlr;
    SYELOG_MESSAGE Message;
    DWORD dwRead;
    DWORD dwNeeded;
    LONGLONG llTemp;

    if (hReady == NULL) {
        MyErrExit("CreateEvent");
        CloseHandle(hEventLog);
        return 0;
    }

    NotifyChangeEventLog(hEventLog, hReady);
    
    for (;;) {
        // Opening the event log positions the file pointer for this 
        // handle at the beginning of the log. Read the records 
        // sequentially until there are no more. 
        //
        pevlr = (EVENTLOGRECORD *)bBuffer;
        while (ReadEventLog(hEventLog,                // event log handle 
                            EVENTLOG_FORWARDS_READ |  // reads forward 
                            EVENTLOG_SEQUENTIAL_READ, // sequential read 
                            0,            // ignored for sequential reads 
                            pevlr,        // pointer to buffer 
                            BUFFER_SIZE,  // size of buffer 
                            &dwRead,      // number of bytes read 
                            &dwNeeded)) {   // bytes in next record
            
            while (dwRead > 0) { 
                // Print the event identifier, type, and source name. 
                // The source name is just past the end of the 
                // formal structure. 
                llTemp = Int32x32To64(pevlr->TimeGenerated,10000000) + llSecsTo1970;

                if (llTemp >= s_llStartTime) {
                
                    Message.nFacility = SYELOG_FACILITY_LOGGING;
                    switch (pevlr->EventType) {
                      case EVENTLOG_ERROR_TYPE:
                        Message.nSeverity = SYELOG_SEVERITY_ERROR;
                        break;
                      case EVENTLOG_WARNING_TYPE:
                        Message.nSeverity = SYELOG_SEVERITY_WARNING;
                        break;
                      case EVENTLOG_INFORMATION_TYPE:
                        Message.nSeverity = SYELOG_SEVERITY_INFORMATION;
                        break;
                      case EVENTLOG_AUDIT_SUCCESS:
                        Message.nSeverity = SYELOG_SEVERITY_AUDIT_PASS;
                        break;
                      case EVENTLOG_AUDIT_FAILURE:
                        Message.nSeverity = SYELOG_SEVERITY_AUDIT_FAIL;
                        break;
                      default:
                        Message.nSeverity = SYELOG_SEVERITY_NOTICE;
                        break;
                    }
                    Message.ftOccurance.dwLowDateTime = (DWORD)llTemp;
                    Message.ftOccurance.dwHighDateTime = (DWORD)(llTemp >> 32);
                
                    sprintf(Message.szMessage, "event: %08X, %s",
                            pevlr->EventID, ((LPBYTE) pevlr + sizeof(EVENTLOGRECORD))); 

                    Message.szMessage[sizeof(Message.szMessage)-1] = '\0';
                    for (PCSTR pszEnd = Message.szMessage; *pszEnd; pszEnd++) {
                        // no internal contents.
                    }
                    Message.nBytes = (USHORT)(pszEnd - ((PCSTR)&Message) + 1);
                
                    LogMessage(&Message, Message.nBytes);
                }
                
                dwRead -= pevlr->Length; 
                pevlr = (EVENTLOGRECORD *)((LPBYTE)pevlr + pevlr->Length); 
            }
            pevlr = (EVENTLOGRECORD *) &bBuffer; 
        }
        
        // Wait for some events to be avaiable in log.
        //
        DWORD dwErr = WaitForSingleObject(hReady, INFINITE);
        if (dwErr == WAIT_ABANDONED) {
            break;
        }
        ResetEvent(hReady);
    }
    CloseEventLog(hEventLog);
    CloseHandle(hReady);
    
    return 1;
}

BOOL CreateEventWorker(PCSTR pszSourceName)
{
    HANDLE hEventLog;
    HANDLE hThread;
    DWORD dwThread;

    hEventLog = OpenEventLog(NULL, pszSourceName);
    if (hEventLog == NULL) {
        MyErrExit("OpenEventLog");
    }
    
    hThread = CreateThread(NULL, 0, EventLogThread, hEventLog, 0, &dwThread);
    if (!hThread) {
        MyErrExit("CreateThread EventLogThread");
        if (hEventLog) {
            CloseEventLog(hEventLog);
            hEventLog = NULL;
        }
        return FALSE;
    }
    CloseHandle(hThread);
    return TRUE;
}

BOOL CreateWorkers(HANDLE hCompletionPort)
{
    DWORD dwThread;
    HANDLE hThread;
    DWORD i;
    SYSTEM_INFO SystemInfo;
    
    GetSystemInfo(&SystemInfo);

    for (i = 0; i < 2 * SystemInfo.dwNumberOfProcessors; i++) {
        hThread = CreateThread(NULL, 0, WorkerThread, hCompletionPort, 0, &dwThread);
        if (!hThread) {
            MyErrExit("CreateThread WorkerThread");
            return FALSE;
        }
        CloseHandle(hThread);
    }
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//
BOOL WINAPI ControlHandler(DWORD dwCtrlType)
{
    switch (dwCtrlType) {
      case CTRL_C_EVENT:
      case CTRL_BREAK_EVENT:
      case CTRL_CLOSE_EVENT:
      case CTRL_LOGOFF_EVENT:
      case CTRL_SHUTDOWN_EVENT:
        printf("\nSYELOGD: Closing connections.\n");
        if (s_hOutFile != INVALID_HANDLE_VALUE) {
            printf("Closing file.\n");
            FlushFileBuffers(s_hOutFile);
            CloseHandle(s_hOutFile);
            s_hOutFile = INVALID_HANDLE_VALUE;
        }
        ExitProcess(0);
    }
    return FALSE;
}

DWORD main(int argc, char **argv) 
{
    INT err;
    WSADATA WsaData;
    HANDLE hCompletionPort;
    BOOL fNeedHelp = FALSE;

    GetSystemTimeAsFileTime((FILETIME *)&s_llStartTime);
    SetConsoleCtrlHandler(ControlHandler, TRUE);
    
	for (int arg = 1; arg < argc; arg++) {
		if (argv[arg][0] == '-' || argv[arg][0] == '/') {
			CHAR *argn = argv[arg] + 1;
			CHAR *argp = argn;
			while (*argp && *argp != ':')
				argp++;
			if (*argp == ':')
				*argp++ = '\0';
			
			switch (argn[0]) {

              case 'e':                                 // NT Events
              case 'E':
                s_fLogEvents = TRUE;
                break;

              case 'p':                                 // Pipes
              case 'P':
                s_fLogPipes = FALSE;
                break;
                
              case 's':                                 // Sockets
              case 'S':
                s_fLogSockets = TRUE;
                break;

              case 'q':                                 // Quiet
              case 'Q':
                s_fLogToScreen = FALSE;
                break;
                
              case '?':
				fNeedHelp = TRUE;
				break;
				
              default:
				fNeedHelp = TRUE;
				printf("SYELOGD: Bad argument: %ls:%ls\n", argn, argp);
				break;
			}
		}
        else {
            if (s_hOutFile != INVALID_HANDLE_VALUE) {
                printf("SYELOGD: Error, more than one output file specified.\n\n");
                fNeedHelp = TRUE;
                break;
            }
            
            s_hOutFile = CreateFile(argv[arg],
                                    GENERIC_WRITE,
                                    FILE_SHARE_READ,
                                    NULL,
                                    CREATE_ALWAYS,
                                    FILE_ATTRIBUTE_NORMAL |
                                    FILE_FLAG_SEQUENTIAL_SCAN,
                                    NULL);
            if (s_hOutFile == INVALID_HANDLE_VALUE) {
                printf("SYELOGD: Error opening output file: %s: %d\n\n",
                       argv[arg], GetLastError());
                fNeedHelp = TRUE;
                break;
            }
            else {
                printf("SYELOGD: Logging to %s.\n", argv[arg]);
            }
        }
	}
    if (!s_fLogEvents && !s_fLogPipes && !s_fLogSockets) {
        fNeedHelp = TRUE;
    }
    if (fNeedHelp) {
        printf("Usage:\n"
               "    syelogd [options] {output_file}\n"
               "Options:\n"
               "    -e         Enable support for NT event records.\n"
               "    -s         Enable support for socket-based loggers.\n"
               "    -p         Disable support for named-pipe loggers.\n"
               "    -q         Disable event logging to screen (quiet mode).\n"
               "    -?         Display this help message.\n"
               "Summary:\n"
               "    If given, all events will be logged to the output file.\n"
               "\n");
        exit(1);
    }

    
    // Create the completion port.
    hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
    if (hCompletionPort == NULL) {
        MyErrExit("CreateIoCompletionPort");
    }

    // Create complietion port worker threads.
    //
    CreateWorkers(hCompletionPort);
    
    if (s_fLogSockets) {
        // Start WinSock
        //
        err = WSAStartup(0x0101, &WsaData);
        if (err == SOCKET_ERROR) {
            MyErrExit("WSAStartup");
        }

        // Open a socket to listen for incoming connections.
        //
        s_sListenSock = socket(AF_INET, SOCK_STREAM, 0);
        if (s_sListenSock == INVALID_SOCKET) {
            MyErrExit("socket");
        }
        ZeroMemory(&s_caListenSock, sizeof(s_caListenSock));

        // Bind our server to the agreed upon port number.
        //
        SOCKADDR_IN localAddr;
        ZeroMemory(&localAddr, sizeof(localAddr));
        localAddr.sin_port = htons(SYELOG_TCP_PORT);
        localAddr.sin_family = AF_INET;
        err = bind(s_sListenSock, (PSOCKADDR) &localAddr, sizeof(localAddr));
        if (err == SOCKET_ERROR) {
            MyErrExit("bind");
        }
    
        // Prepare to accept client connections.
        //
        err = listen(s_sListenSock, 5);
        if (err == SOCKET_ERROR) {
            MyErrExit("listen");
        }
        
        if (!CreateIoCompletionPort((HANDLE)s_sListenSock, hCompletionPort,
                                    (DWORD)&s_caListenSock, 0)) {
            MyErrExit("CreateIoCompletionPort s_caListenSock");
        }
    
        CreateSockConnection(hCompletionPort);
    }
    
    if (s_fLogPipes) {
        CreatePipeConnection(hCompletionPort);
    }

    if (s_fLogEvents) {
        CreateEventWorker("Application");
        CreateEventWorker("System");
        CreateEventWorker("Security");
    }
    
    printf("SYELOGD: Ready for clients.  Press Ctrl-C to stop.\n");
    while (argc) {
        Sleep(10000);
    }

    SetConsoleCtrlHandler(ControlHandler, FALSE);
    
    if (s_hOutFile == INVALID_HANDLE_VALUE) {
        FlushFileBuffers(s_hOutFile);
        CloseHandle(s_hOutFile);
        s_hOutFile = INVALID_HANDLE_VALUE;
    }
    
    return 0; 
} 
//
//////////////////////////////////////////////////////////////////////////////
