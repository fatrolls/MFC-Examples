//////////////////////////////////////////////////////////////////////////////
//
//	Module:		injdll.exe - Test DetourCreateProcessWithDll function.
//	File:		injdll.cpp
//
//  Copyright 1998-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.5 (Build 46)
//
#include <stdio.h>
#include <windows.h>
#include <detours.h>

#define arrayof(x)		(sizeof(x)/sizeof(x[0]))

//////////////////////////////////////////////////////////////////////////////
//
void PrintUsage(void)
{
	printf("Usage:\n"
		   "    injdll /p:pid /d:dll\n"
		   "Options:\n"
		   "    /p:number    : Attach to process number.\n"
		   "    /d:file.dll  : Inject file.dll.\n"
		   "    /?           : This help screen.\n");
}

//////////////////////////////////////////////////////////////////////// main.
//
int CDECL main(int argc, char **argv)
{
	BOOLEAN fNeedHelp = FALSE;
	INT nProcessId = -1;
	CHAR szDllPath[MAX_PATH] = "";

	for (int arg = 1;
		 arg < argc && (argv[arg][0] == '-' || argv[arg][0] == '/');
		 arg++) {
		
		CHAR *argp = argv[arg] + 2;
		if (*argp == ':') {
			argp++;
        }
		
		switch (argv[arg][1]) {
			
		  case 'd':										// Set DLL Name
		  case 'D':
			strcpy(szDllPath, argp);
			break;

		  case 'p':										// Set Process #
		  case 'P':
			nProcessId = atoi(argp);
			break;

		  case 'h':										// Help
		  case 'H':
		  case '?':
			fNeedHelp = TRUE;
			break;
			
		  default:
			fNeedHelp = TRUE;
			printf("Bad argument: %s\n", argv[arg]);
			break;
		}
	}

	if (szDllPath[0] == 0) {
		fNeedHelp = TRUE;
	}
	if (nProcessId < 0) {
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

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, nProcessId);
	if (hProcess == NULL) {
		printf("injdll.exe: OpenProcess(%d) failed: %d\n",
               nProcessId, GetLastError());
		return 2;
	}
 	
    printf("injdll.exe: Injecting %s into process %d.\n", szDllPath, nProcessId);
    fflush(stdout);
    
	if (!DetourContinueProcessWithDllA(hProcess, szDllPath)) {
		printf("injdll.exe: DetourContinueProcessWithDll(%s) failed: %d",
               szDllPath, GetLastError());
		return 3;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
// End of File
