//////////////////////////////////////////////////////////////////////////////
//
//	Module:		sleepinj - Test injdll.exe
//	File:		sleepinj.cpp
//
//  Copyright 1998-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.4 (Build 45)
//
#include <stdio.h>
#include <windows.h>

#define arrayof(x)		(sizeof(x)/sizeof(x[0]))

//////////////////////////////////////////////////////////////////////////////
//
void PrintUsage(void)
{
	printf("Usage:\n"
		   "    sleepinj [options] [command line]\n"
		   "Options:\n"
           "    /e:event      : Signal this event when program can resume.\n"
           "                   (Defaults to detours_inject_test_event.)\n"
		   "    /d:file.dll   : Inject file.dll.\n"
           "    /i:injdll.exe : Path to injdll.exe.\n"
		   "    /?            : This help screen.\n");
}

//////////////////////////////////////////////////////////////////////// main.
//
int CDECL main(int argc, char **argv)
{
	BOOLEAN fNeedHelp = FALSE;
	CHAR szDllPath[MAX_PATH] = "";
    CHAR szEvent[MAX_PATH] = "detours_inject_test_event";
    CHAR szInject[MAX_PATH] = "injdll.exe";

	for (int arg = 1;
		 arg < argc && (argv[arg][0] == '-' || argv[arg][0] == '/');
		 arg++) {
		
		CHAR *argp = argv[arg] + 2;
		if (*argp == ':') {
			argp++;
        }
		
		switch (argv[arg][1]) {
			
		  case 'd':										// Set DLL path.
		  case 'D':
			strcpy(szDllPath, argp);
			break;

		  case 'e':										// Set event name.
		  case 'E':
            strcpy(szEvent, argp);
			break;

		  case 'i':										// Set injdll.exe path.
		  case 'I':
            strcpy(szInject, argp);
			break;

		  case 'h':										// Help
		  case 'H':
		  case '?':
			fNeedHelp = TRUE;
			break;
			
		  default:
			fNeedHelp = TRUE;
			printf("sleepinj: Bad argument: %s\n", argv[arg]);
			break;
		}
	}

	if (szDllPath[0] == 0) {
		fNeedHelp = TRUE;
	}
	if (argc == 1) {
		fNeedHelp = TRUE;
	}
	
	if (fNeedHelp) {
		PrintUsage();
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////
    HANDLE hEvent;

    hEvent = CreateEvent(NULL, TRUE, FALSE, szEvent);
    if (hEvent == NULL) {
        printf("sleepinj: Creation of event failed: %d\n", GetLastError());
        return 1;
    }
    
	//////////////////////////////////////////////////////////////////////////

	STARTUPINFO si;
	PROCESS_INFORMATION piChild;
	CHAR szCommand[2048];
	CHAR szExe[1024];
	CHAR szFullExe[1024] = "\0";
	PCHAR pszFileExe = NULL;
	
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&piChild, sizeof(piChild));
	si.cb = sizeof(si);

	szCommand[0] = L'\0';
	strcpy(szExe, argv[arg]);
	for (; arg < argc; arg++) {
		if (strchr(argv[arg], ' ') != NULL || strchr(argv[arg], '\t') != NULL) {
			strcat(szCommand, "\"");
			strcat(szCommand, argv[arg]);
			strcat(szCommand, "\"");
		}
		else {
			strcat(szCommand, argv[arg]);
		}
		
		if (arg + 1 < argc)
			strcat(szCommand, " ");
	}
	printf("sleepinj: Starting child: `%s'\n\n", szCommand);
    fflush(stdout);

	SetLastError(0);
	SearchPath(NULL, szExe, ".exe", arrayof(szFullExe), szFullExe, &pszFileExe);
    if (!CreateProcess(szFullExe[0] ? szFullExe : NULL, szCommand, NULL, NULL, TRUE,
                       CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &piChild)) {
        printf("sleepinj: CreateProcess failed: %d\n", GetLastError());
        ExitProcess(2);
    }
	Sleep(1500);    // Wait for the child process to start.

	//////////////////////////////////////////////////////////////////////////

	PROCESS_INFORMATION piInject;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&piInject, sizeof(piInject));
	si.cb = sizeof(si);

    sprintf(szCommand, "%s /p:%d /d:%s", szInject, piChild.dwProcessId, szDllPath);
	printf("sleepinj: Starting inject: `%s'\n\n", szCommand);
    fflush(stdout);

	SetLastError(0);
	SearchPath(NULL, szInject, ".exe", arrayof(szFullExe), szFullExe, &pszFileExe);
    if (!CreateProcess(szFullExe[0] ? szFullExe : NULL, szCommand, NULL, NULL, TRUE,
                       CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &piInject)) {
        printf("sleepinj: CreateProcess failed: %d\n", GetLastError());
        ExitProcess(2);
    }

	WaitForSingleObject(piInject.hProcess, INFINITE);

	//////////////////////////////////////////////////////////////////////////

    printf("\nsleepinj: Resuming execution through shared event...\n\n");
    fflush(stdout);
    SetEvent(hEvent);
    
    //////////////////////////////////////////////////////////////////////////

	WaitForSingleObject(piChild.hProcess, INFINITE);
    
	DWORD dwResult = 0;
	if (!GetExitCodeProcess(piChild.hProcess, &dwResult)) {
		printf("sleepinj: GetExitCodeProcess failed: %d\n", GetLastError());
		dwResult = 3;
	}
	
	return dwResult;
}
//
///////////////////////////////////////////////////////////////// End of File.
