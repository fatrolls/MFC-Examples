//////////////////////////////////////////////////////////////////////////////
//
//	Module:		dimp.exe
//	File:		dimp.cpp
//
//	Copyright:	1996-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.5 (Build 46)
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include <detours.h>

////////////////////////////////////////////////////////////// Error Messages.
//
VOID AssertMessage(PCSTR szMsg, PCSTR szFile, DWORD nLine)
{
	printf("ASSERT(%s) failed in %s, line %d.", szMsg, szFile, nLine);
}

#define ASSERT(x)   \
do { if (!(x)) { AssertMessage(#x, __FILE__, __LINE__); DebugBreak(); }} while (0)
	;

//////////////////////////////////////////////////////////////////////////////
//
static BOOL s_fSubs = FALSE;

//////////////////////////////////////////////////////////////////////////////
//
static CHAR s_szFile[MAX_PATH] = "\0";

static BOOL CALLBACK ListFileCallback(PVOID pContext,
									  PCHAR pszOrigFile,
									  PCHAR pszFile,
									  PCHAR *ppszOutFile)
{
    (void)pContext;
    (void)pszFile;
    
	*ppszOutFile = NULL;

	strcpy(s_szFile, pszOrigFile);
	
	PCHAR psz;
	if ((psz = strchr(s_szFile, '.')) != NULL) {
		*psz = '\0';
	}
	return TRUE;
}

BOOL CALLBACK ListSymbolCallback(PVOID pContext,
								 DWORD nOrdinal,
								 PCHAR pszOrigSymbol,
								 PCHAR pszSymbol,
								 PCHAR *ppszOutSymbol)
{
    (void)pContext;
    (void)nOrdinal;
    (void)pszSymbol;
    
	*ppszOutSymbol = NULL;
	printf("  %s::%s\n", s_szFile, pszOrigSymbol);
	return TRUE;
}

BOOL DimpFile(PCHAR pszPath)
{
	BOOL bGood = TRUE;
	HANDLE hOld = INVALID_HANDLE_VALUE;
	PDETOUR_BINARY pBinary = NULL;
			
	
	hOld = CreateFile(pszPath,
					  GENERIC_READ,
					  FILE_SHARE_READ,
					  NULL,
					  OPEN_EXISTING,
					  FILE_ATTRIBUTE_NORMAL,
					  NULL);
				
	if (hOld == INVALID_HANDLE_VALUE) {
		printf("%s: Failed to open input file with error: %d\n",
			   pszPath, GetLastError());
		bGood = FALSE;
		goto end;
	}

	if ((pBinary = DetourBinaryOpen(hOld)) == NULL) {
		printf("%s: DetourBinaryOpen failed: %d\n", pszPath, GetLastError());
		goto end;
	}

	if (hOld != INVALID_HANDLE_VALUE) {
		CloseHandle(hOld);
		hOld = INVALID_HANDLE_VALUE;
	}
				
	printf("%s:\n", pszPath);
	if (!DetourBinaryEditImports(pBinary,
								 NULL,
								 NULL,
								 ListFileCallback,
								 ListSymbolCallback,
								 NULL)) {
		
		printf("%s: DetourBinaryEditImports failed: %d\n", pszPath, GetLastError());
	}
	
	DetourBinaryClose(pBinary);
	pBinary = NULL;
			
  end:
	if (pBinary) {
		DetourBinaryClose(pBinary);
		pBinary = NULL;
	}
	if (hOld != INVALID_HANDLE_VALUE) {
		CloseHandle(hOld);
		hOld = INVALID_HANDLE_VALUE;
	}
	return bGood;
}

//////////////////////////////////////////////////////////////////////////////
int DimpArgument(char *dir, char *argp, int fDoSubs)
{
	//////////////////////////////////////////////////////////////////////////

	WIN32_FIND_DATA wfd;
	HANDLE 	hFind = NULL;
	char 	name[1024];
	int		nFound = 0;

	strcpy(name, dir ? dir : "");
	strcat(name, argp);

	hFind = FindFirstFile(name, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				strcpy(name, dir ? dir : "");
				strcat(name, wfd.cFileName);
			
				nFound += DimpFile(name);
			}
		} while (FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}

	if (fDoSubs) {
		strcpy(name, dir ? dir : "");
		strcat(name, "*");
		
		hFind = FindFirstFile(name, &wfd);
		if (hFind == INVALID_HANDLE_VALUE)
			return nFound;
		
		do {
			if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				wfd.cFileName[0] != '.') {

				strcpy(name, dir ? dir : "");
				strcat(name, wfd.cFileName);
				strcat(name, "\\");

				nFound += DimpArgument(name, argp, fDoSubs);
			}
		} while (FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}
	return nFound;
}


//////////////////////////////////////////////////////////////////////////////
//
void PrintUsage(void)
{
	printf("Usage:\n"
		   "    dimp [options] binary_files\n"
		   "Options:\n"
		   "    -s           : Recurse through subdirectories.\n"
		   "    -?           : This help screen.\n"
		   "Examples:\n"
		   "    dimp /s *.exe\n"
		   "");
}

//////////////////////////////////////////////////////////////////////// main.
//
int CDECL main(int argc, char **argv)
{
	BOOL fNeedHelp = FALSE;
	BOOL fSubdirs = FALSE;

	for (int arg = 1; arg < argc; arg++) {
		if (argv[arg][0] == '-' || argv[arg][0] == '/') {
			CHAR *argn = argv[arg] + 1;
			CHAR *argp = argn;
			while (*argp && *argp != ':')
				argp++;
			if (*argp == ':')
				*argp++ = '\0';
			
			switch (argn[0]) {

			  case 's':									// Do Subdirectories.
			  case 'S':
				fSubdirs = TRUE;
				break;
				
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
			CHAR szDir[MAX_PATH] = "";
			CHAR szArg[MAX_PATH] = "";
			PCHAR pszDir;
			
			if ((pszDir = strrchr(argv[arg], '\\')) != NULL) {
				*pszDir++ = '\0';
				strcpy(szArg, pszDir);
				strcpy(szDir, argv[arg]);
				strcat(szDir, "\\");
			}
			else {
				if (GetCurrentDirectory(sizeof(szDir), szDir) > 3) {
					strcat(szDir, "\\");
				}
				strcpy(szArg, argv[arg]);
			}
			
            DimpArgument(szDir, szArg, fSubdirs);
		}
	}
	if (argc == 1) {
		fNeedHelp = TRUE;
	}
	if (fNeedHelp) {
		PrintUsage();
		return 1;
	}
	return 0;
}

// End of File
