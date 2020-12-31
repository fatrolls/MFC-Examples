//////////////////////////////////////////////////////////////////////////////
//
//	Module:		image.exe
//	File:		image.cpp
//
//	Copyright:	1996-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.5 (Build 46)
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ole2.h>
#include <shellapi.h>
#include "detours.h"

#define arrayof(x)		(sizeof(x)/sizeof(x[0]))

//////////////////////////////////////////////////////////////////////////////
//
#ifndef _DEFINED_ASMBREAK_
#define _DEFINED_ASMBREAK_
#define ASMBREAK()	__asm { int 3 }
//#define ASMBREAK()	DebugBreak()
#endif	// _DEFINED_ASMBREAK_

#ifndef NODEBUG
#undef ASSERT
VOID DetourAssertMessage(CONST PCHAR szMsg, CONST PCHAR szFile, DWORD nLine);

#define ASSERT(x)   \
do { if (!(x)) { DetourAssertMessage(#x, __FILE__, __LINE__); ASMBREAK(); }} while (0)
	;
#undef ASSERTX
#define ASSERTX(x)   \
do { if (!(x)) { DetourAssertMessage(#x, __FILE__, __LINE__); PCHAR p=(PCHAR)(x); *p = 1; }} while (0)
	;
#else	// NODEBUG
#undef ASSERT
#define ASSERT(x)
#undef ASSERTX
#define ASSERTX(x)
#endif	// NODEBUG
//
//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////// Error Messages.
//
VOID DetourAssertMessage(CONST PCHAR szMsg, CONST PCHAR szFile, DWORD nLine)
{
	printf("ASSERT(%s) failed in %s, line %d.", szMsg, szFile, nLine);
}



static BOOL CALLBACK ExportCallback(PVOID pContext,
									DWORD nOrdinal,
									PCHAR pszSymbol,
									PBYTE pbTarget)
{
    (void)pContext;
    
	printf("        %4d %-30s %08x\n",
		   nOrdinal,
		   pszSymbol ? pszSymbol : "[NO NAME]",
		   pbTarget);
	return TRUE;
}

BOOL DumpFile(PCHAR pszPath)
{
	HINSTANCE hInst = LoadLibrary(pszPath);
	if (hInst == NULL) {
		printf("Unable to load %s: Error %d\n", pszPath, GetLastError());
		return FALSE;
	}
	
	printf("%s @ %08lx\n", pszPath, hInst);
	
	PBYTE pbEntry = DetourGetEntryPoint(hInst);
	printf("    EntryPoint: %08lx\n", pbEntry);
	
	DetourEnumerateExports(hInst, NULL, ExportCallback);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//
void PrintUsage(void)
{
	printf("Usage:\n"
		   "    dumpe [.dll files]\n"
		   "Misc. Options:\n"
		   "    /h       : Help screen.\n");
}

//////////////////////////////////////////////////////////////////////// main.
//
int CDECL main(int argc, char **argv)
{
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

			case 'h':
			case '?':
				fNeedHelp = TRUE;
				break;
				
			default:
				fNeedHelp = TRUE;
				printf("Bad argument: %s:%s\n", argn, argp);
				break;
			}
		}
		else {
			DumpFile(argv[arg]);
		}
	}
	if (fNeedHelp || argc == 1) {
		PrintUsage();
		return 1;
	}
	return 0;
}

// End of File
