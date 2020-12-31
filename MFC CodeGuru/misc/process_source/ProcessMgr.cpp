/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1997 by Joerg Koenig and the ADG mbH, Mannheim, Germany
// All rights reserved
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////

// last revised $Date: 3.02.98 20:24 $

#include "stdafx.h"
#ifndef __AFXTEMPL_H__
	#error "you have to #include <afxtempl.h> before you can use this file"
#endif
#include "ProcessMgr.h"
#include "resource.h"		// main symbols
#include <Tlhelp32.h>
#include <winperf.h>
#include <shlguid.h>
#include <shlobj.h>
#include <tchar.h>

extern "C" {
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
}
  


/////////////////////////////////////////////////////////////////////////////
// manifest constants
#define INITIAL_SIZE        51200
#define EXTEND_SIZE         25600
#define REGKEY_PERF         TEXT("software\\microsoft\\windows nt\\currentversion\\perflib")
#define REGSUBKEY_COUNTERS  TEXT("Counters")
#define PROCESS_COUNTER     TEXT("process")
#define PROCESSID_COUNTER   TEXT("id process")
#define UNKNOWN_TASK        TEXT("unknown")

/////////////////////////////////////////////////////////////////////////////
// helpers at file scope


// Type definitions for pointers to call tool help functions.
typedef BOOL (WINAPI *PROCESSWALK)(HANDLE hSnapshot,
    LPPROCESSENTRY32 lppe);
typedef HANDLE (WINAPI *CREATESNAPSHOT)(DWORD dwFlags,
    DWORD th32ProcessID);

// File scope globals. These pointers are declared because of the need
// to dynamically link to the functions.  They are exported only by
// the Windows 95 kernel. Explicitly linking to them will make this
// application unloadable in Microsoft(R) Windows NT(TM) and will
// produce an ugly system dialog box.
static CREATESNAPSHOT gpCreateToolhelp32Snapshot = 0 ;
static PROCESSWALK gpProcess32First = 0 ;
static PROCESSWALK gpProcess32Next  = 0 ;
static HMODULE ghKernel = 0 ;

// Class scope globals.
BOOL CProcessMgr::m_bToolHelpOK = CProcessMgr::InitToolhelp32() ;



// class CProcessMgr  --  construction/destruction

CProcessMgr :: CProcessMgr()
	: m_strSpace(TEXT(" \t"))
	, m_pstrCmd(0)
	, m_nIdx(0)
	, m_nLen(0)
{
	CoInitialize(0);
}

CProcessMgr :: ~CProcessMgr() {
	CoUninitialize();
}




// CProcessMgr :: GetLinkInfo() fills the filename and path buffer
// with relevant information
// strLinkName	- name of the link file passed into the function.
// strPath		- the buffer that will receive the filepath name.
 
BOOL CProcessMgr :: GetLinkInfo( const CString & strLinkName, CString & strPath ) const {
	HRESULT hres;
	IShellLink * psl;
	WIN32_FIND_DATA wfd;
 
	// Call CoCreateInstance to obtain the IShellLink
	// Interface pointer. This call fails if
	// CoInitialize is not called, so it is assumed that
	// CoInitialize has been called.
 
	hres =	CoCreateInstance(
				CLSID_ShellLink,
				0,
				CLSCTX_INPROC_SERVER,
				IID_IShellLink,
				(LPVOID *)&psl
			);

	if( SUCCEEDED(hres) ) {
		IPersistFile * ppf;
 
		// The IShellLink Interface supports the IPersistFile
		// interface. Get an interface pointer to it.
		hres =	psl->QueryInterface(
					IID_IPersistFile,
					(LPVOID *)&ppf
				);
		if( SUCCEEDED( hres ) ) {
			WORD wsz[MAX_PATH];
 
			//Convert the given link name string to wide character string.
			MultiByteToWideChar(
				CP_ACP,
				0,
				strLinkName,
				-1,
				wsz,
				MAX_PATH
			);
			//Load the file.
			hres = ppf->Load( wsz, STGM_READ );
			if( SUCCEEDED( hres ) ) {
				// Resolve the link by calling the Resolve() interface function.
				hres =	psl->Resolve(
							0,
							SLR_ANY_MATCH | SLR_NO_UI
						);
				if( SUCCEEDED( hres ) ) {
					char chPath[MAX_PATH];
					hres =	psl->GetPath(
								chPath,
								MAX_PATH,
								(WIN32_FIND_DATA*)&wfd,
								SLGP_SHORTPATH
							);
					if( SUCCEEDED( hres ) ) {
						// check wether the string needs expansion
 						TCHAR szPath[MAX_PATH];
						strPath = chPath;
						if( strPath.Find( TEXT('%') ) >= 0 ) {
							ExpandEnvironmentStrings( chPath, szPath, MAX_PATH );
							strPath = szPath;
						}
					}
				}
			}
			ppf->Release();
		}
		psl->Release();
	}
	return SUCCEEDED(hres) ? TRUE : FALSE;
}



// Function that initializes tool help functions. If this function fails, then
// this program is running under NT instead of Win 95 ! 
BOOL CProcessMgr::InitToolhelp32() {
	BOOL   bRet  = FALSE ;
 
	// Obtain the module handle of the kernel to retrieve addresses of
	// the tool helper functions.
	if( ! ghKernel )
		ghKernel = GetModuleHandle( TEXT("KERNEL32.DLL") ) ;
 
	if( ghKernel ) {
		gpCreateToolhelp32Snapshot = 
			(CREATESNAPSHOT)GetProcAddress( ghKernel, 
			"CreateToolhelp32Snapshot" ) ;

		gpProcess32First = (PROCESSWALK)GetProcAddress(ghKernel,
			"Process32First");
		gpProcess32Next  = (PROCESSWALK)GetProcAddress(ghKernel,
			"Process32Next");

		// All addresses must be non-NULL to be successful.
		// If one of these addresses is NULL, one of
		// the needed lists cannot be walked.
		bRet = (gpProcess32First && gpProcess32Next && gpCreateToolhelp32Snapshot) ?
				TRUE : FALSE ;
	}

	return bRet;
} 

// a short helper struct to communicate between application and callback routine:
struct WinID {
	DWORD dwPID ;
	CList<HWND,HWND> listhWnd ;
} ;

static BOOL CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam ) {
    DWORD		pid = 0;
    WinID *		pWID = (WinID *)lParam;


    // get the processid for this window
    GetWindowThreadProcessId( hwnd, &pid ) ;

    if( pid == pWID->dwPID )
		pWID->listhWnd.AddTail( hwnd ) ;

	// continue the enumeration
	return TRUE;
}


BOOL CProcessMgr :: SwitchProcessIntoForeground( DWORD dwPID ) const {
	// enumerate all windows
	WinID lParam ;
	lParam.dwPID = dwPID ;
	EnumWindows( EnumWindowsProc, (LPARAM) &lParam );

	if( lParam.listhWnd.IsEmpty() ) {
		#ifdef IDS_CannotSwitchToProgram
			AfxMessageBox( IDS_CannotSwitchToProgram );
		#endif
		return FALSE ;
	}

	TRACE2("\nenumerator found %d windows related to process %lu\n",lParam.listhWnd.GetCount(),dwPID);

	for( POSITION pos = lParam.listhWnd.GetHeadPosition() ; pos ; ) {
		HWND hWnd = lParam.listhWnd.GetNext( pos ) ;
		TRACE1( "trying window 0x%lx\n", long( hWnd ) ) ;
		
		if( GetParent( hWnd ) ) {
			TRACE0( "	window is a child -> skipping\n" );
			continue ;
		}

		char buf[1024] ;
		if( ! GetWindowText( hWnd, buf, 1023 ) )
			buf[0] = 0 ;
		if( strlen( buf ) <= 0 ) {
			TRACE0( "	window has no title -> skipping\n" ) ;
			continue ;
		} else {
			TRACE1( "	windows title: \"%s\"\n", buf ) ;
		}

		if( ! IsWindowVisible( hWnd ) ) {
			TRACE0( "	window is invisible -> skipping\n" ) ;
			continue ;
		}

		if( IsIconic( hWnd ) ) {
			TRACE0( "	window is minimized -> zooming\n" );
			ShowWindow(hWnd, SW_RESTORE);
		}
		
		TRACE1( "	window 0x%lx becomes active...\n", long( hWnd ) ) ;

		SetForegroundWindow( hWnd ) ;
		SetActiveWindow( hWnd ) ;
		SetFocus( hWnd ) ;
		return TRUE;
	}
	return FALSE;
}




DWORD CProcessMgr :: IsProgramRunning( const CString & rstrExeFile_p ) const {
	CString strExeFile = rstrExeFile_p ;

	// first: have a look at the file itself. If it is a shortcut, then obtain
	// the real file name:
	CString strPath;
	if( GetLinkInfo(rstrExeFile_p, strPath) ) {
		TRACE1( "link points to \"%s\".\n", LPCTSTR(strPath) );
		strExeFile = strPath;
	} else {
		TRACE1( "\"%s\" is not a link\n", LPCTSTR(rstrExeFile_p) ) ;
	}

	DWORD dwPID = 0;

	if( m_bToolHelpOK ) {
		// Windows 95 running: use toolhelp library to find process ...
		HANDLE hSnapshot =	(*gpCreateToolhelp32Snapshot)(
								TH32CS_SNAPPROCESS,		// flags: only make a process snapshot
								0						// process identifier (0 == current)
							) ;

		PROCESSENTRY32 pe ;
		pe.dwSize = sizeof( PROCESSENTRY32 ) ;
		
		// now iterate the snapshot until the proper program is found ...
		for( BOOL bOK = (*gpProcess32First)( hSnapshot, &pe ) ;
			 GetLastError() != ERROR_NO_MORE_FILES ;
			 bOK = (*gpProcess32Next)( hSnapshot, &pe ) ) {
			if( bOK ) {
				TRACE( "checking %s <> %s\n", LPCTSTR(strExeFile), pe.szExeFile ) ;
				if( 0 < pe.cntUsage && CompareFilenames(strExeFile, pe.szExeFile) ) {
					dwPID = pe.th32ProcessID;
					break;
				}
			} else {
				TRACE0( "Process32(First|Next) function failed\n" );
			}
		}

		CloseHandle( hSnapshot ) ;
	} else {
		// NT running: use the performance data (much more difficult) ...

		// define all local variables here at once, because we use "goto".
		// The use of goto is legal here, because it would blow up code
		// (and faultiness), if we would write the final code 100 of times ...
		DWORD                        rc;
		HKEY                         hKeyNames;
		DWORD                        dwType;
		DWORD                        dwSize;
		LPBYTE                       buf = NULL;
		CHAR                         szSubKey[1024];
		LANGID                       lid;
		LPSTR                        p;
		LPSTR                        p2;
		PPERF_DATA_BLOCK             pPerf;
		PPERF_OBJECT_TYPE            pObj;
		PPERF_INSTANCE_DEFINITION    pInst;
		PPERF_COUNTER_BLOCK          pCounter;
		PPERF_COUNTER_DEFINITION     pCounterDef;
		DWORD                        i;
		DWORD                        dwProcessIdTitle;
		DWORD                        dwProcessIdCounter;
		CHAR                         szProcessName[MAX_PATH];
		DWORD                        dwLimit ;
		CString						 strCommand = strExeFile ;
		int							 nIdx = strExeFile.ReverseFind( TEXT('\\') ) ;
		CString						 strProcess ;

		// strip path from exe-filename
		if( nIdx >= 0 )
			strCommand = strExeFile.Mid( nIdx + 1 );
		strCommand.MakeUpper();

		// Look for the list of counters.  Always use the neutral
		// English version, regardless of the local language.  We
		// are looking for some particular keys, and we are always
		// going to do our looking in English.  We are not going
		// to show the user the counter names, so there is no need
		// to go find the corresponding name in the local language.
		lid = MAKELANGID( LANG_ENGLISH, SUBLANG_NEUTRAL );
		sprintf( szSubKey, "%s\\%03x", REGKEY_PERF, lid );
		rc = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
						   szSubKey,
						   0,
						   KEY_READ,
						   &hKeyNames
						 );
		if( rc != ERROR_SUCCESS ) {
			goto cleanup;
		}

		// get the buffer size for the counter names
		rc = RegQueryValueEx( hKeyNames,
							  REGSUBKEY_COUNTERS,
							  0,
							  &dwType,
							  0,
							  &dwSize
							);

		if( rc != ERROR_SUCCESS ) {
			goto cleanup;
		}

		// allocate the counter names buffer
		buf = new BYTE [ dwSize ];
		if( buf == 0 ) {
			goto cleanup;
		}
		memset( buf, 0, dwSize );

		// read the counter names from the registry
		rc = RegQueryValueEx( hKeyNames,
							  REGSUBKEY_COUNTERS,
							  0,
							  &dwType,
							  buf,
							  &dwSize
							);

		if( rc != ERROR_SUCCESS ) {
			goto cleanup;
		}

		// now loop thru the counter names looking for the following counters:
		//
		//      1.  "Process"           process name
		//      2.  "ID Process"        process id
		//
		// the buffer contains multiple null terminated strings and then
		// finally null terminated at the end.  the strings are in pairs of
		// counter number and counter name.

		p = LPSTR(buf);
		while (*p) {
			if (p > LPSTR(buf)) {
				for( p2=p-2; isdigit(*p2); p2--) ;
				}
			if (stricmp(p, PROCESS_COUNTER) == 0) {
				// look backwards for the counter number
				for( p2=p-2; isdigit(*p2); p2--) ;
				strcpy( szSubKey, p2+1 );
			}
			else
			if (stricmp(p, PROCESSID_COUNTER) == 0) {
				// look backwards for the counter number
				for( p2=p-2; isdigit(*p2); p2--) ;
				dwProcessIdTitle = atol( p2+1 );
			}
			// next string
			p += (strlen(p) + 1);
		}

		// free the counter names buffer
		delete [] buf ;


		// allocate the initial buffer for the performance data
		dwSize = INITIAL_SIZE;


		for(;;) {
			buf = new BYTE [ dwSize ];
			if( buf == 0 ) {
				goto cleanup;
			}
			memset( buf, 0, dwSize );

			rc = RegQueryValueEx( HKEY_PERFORMANCE_DATA,
								  szSubKey,
								  NULL,
								  &dwType,
								  buf,
								  &dwSize
								);

			pPerf = (PPERF_DATA_BLOCK) buf;

			// check for success and valid perf data block signature
			if( (rc == ERROR_SUCCESS) &&
				(dwSize > 0) &&
				(pPerf)->Signature[0] == (WCHAR)'P' &&
				(pPerf)->Signature[1] == (WCHAR)'E' &&
				(pPerf)->Signature[2] == (WCHAR)'R' &&
				(pPerf)->Signature[3] == (WCHAR)'F' ) {
				break;
			}

			// if buffer is not big enough, reallocate and try again
			if (rc == ERROR_MORE_DATA) {
				dwSize += EXTEND_SIZE;
				delete [] buf ;
			}
			else {
				goto cleanup;
			}
		}

		// set the perf_object_type pointer
		pObj = (PPERF_OBJECT_TYPE) ((DWORD)pPerf + pPerf->HeaderLength);

		// loop thru the performance counter definition records looking
		// for the process id counter and then save its offset
		pCounterDef = (PPERF_COUNTER_DEFINITION) ((DWORD)pObj + pObj->HeaderLength);
		for( i=0; i<(DWORD)pObj->NumCounters; i++ ) {
			if( pCounterDef->CounterNameTitleIndex == dwProcessIdTitle ) {
				dwProcessIdCounter = pCounterDef->CounterOffset;
				break;
			}
			pCounterDef++;
		}

		// receive the number of currently running instances
		dwLimit = (DWORD)pObj->NumInstances ;

		// get first instance (i.e. process)
		pInst = (PPERF_INSTANCE_DEFINITION) ((DWORD)pObj + pObj->DefinitionLength);


		// loop thru the performance instance data extracting each process name
		// and process id
		for( i=0 ; i<dwLimit ; i++ ) {
			// pointer to the process name
			p = (LPSTR) ((PCHAR)pInst + pInst->NameOffset);

			// convert it to ascii
			rc = WideCharToMultiByte( CP_ACP,
									  0,
									  (LPCWSTR)p,
									  -1,
									  szProcessName,
									  sizeof(szProcessName),
									  0,
									  0
									);

			if( rc ) {
				// get the process id
				DWORD dwProcessId ;
				pCounter = (PPERF_COUNTER_BLOCK) ((DWORD)pInst + pInst->ByteLength);
				dwProcessId = *((LPDWORD) ((DWORD)pCounter + dwProcessIdCounter));
				// NOTE that there can be "dummy" processes such as "_Total" !
				if( dwProcessId > 0 ) {
					strProcess = szProcessName ;

					TRACE( "found process: \"%s\" : %lu check \"%s\"\n",
						LPCTSTR(strProcess), dwProcessId, LPCTSTR(strCommand) );

					if( strProcess.GetLength() <= strCommand.GetLength() ) {
						strProcess.MakeUpper();
						// unfortunataly CString has no "strncmp()" equivalent ...
						if( 0 == _tcsncmp( strProcess, strCommand, strProcess.GetLength()) ) {
							// this is the right PID
							dwPID = dwProcessId;
							break ;
						}
					}
				}
			}

			// next process
			pInst = (PPERF_INSTANCE_DEFINITION) ((DWORD)pCounter + pCounter->ByteLength);
		}

	cleanup:
		if( buf )
			delete [] buf ;

		RegCloseKey( hKeyNames );
		// the following statement causes the application to crash ...
		//RegCloseKey( HKEY_PERFORMANCE_DATA );
	}

	return dwPID ;
}


DWORD CProcessMgr :: IsProgramRunning(DWORD PID) const {
	HANDLE hProcess = HANDLE(PID);
	DWORD dwExitCode;
	if( GetExitCodeProcess(hProcess, &dwExitCode) )
		return (dwExitCode == STILL_ACTIVE) ? PID : 0;
	return DWORD(-1);
}


BOOL CProcessMgr :: CompareFilenames( LPCSTR pszPath1, LPCSTR pszPath2 ) const {
	// this function compares the PIDLs of the two file names.
	// NOTE that you cannot compare the names directly (strcmp() for
	// instance), because one of the names might appear in
	// long file name format and the other in short file name
	// format. That's why we have to receive the IDs and compare them...
	VERIFY(pszPath1 != 0);
	VERIFY(pszPath2 != 0);

	BOOL bRet = FALSE;

	LPSHELLFOLDER pDesktopFolder;

	if( SUCCEEDED( SHGetDesktopFolder(&pDesktopFolder)) ) {
		// COM-interface always needs unicode strings ...
		OLECHAR	olePath1[MAX_PATH], olePath2[MAX_PATH];
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszPath1, -1, olePath1, MAX_PATH);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszPath2, -1, olePath2, MAX_PATH);

		// retrieve PIDLs
		LPITEMIDLIST pidl1, pidl2;
		DWORD dwAttr;
		DWORD dummy;
		if( SUCCEEDED(pDesktopFolder->ParseDisplayName(0, 0, olePath1, &dummy, &pidl1, &dwAttr)) &&
			SUCCEEDED(pDesktopFolder->ParseDisplayName(0, 0, olePath2, &dummy, &pidl2, &dwAttr)) ) {

			// now we can compare the PIDLs
			HRESULT hRes = pDesktopFolder->CompareIDs(0, pidl1, pidl2);
			if( HRESULT_CODE(hRes) == 0 )
				bRet = TRUE;

			// free the PIDLs ...
			LPMALLOC pMalloc;
			SHGetMalloc(&pMalloc);
			pMalloc->Free((void *)pidl1);
			pMalloc->Free((void *)pidl2);
			pMalloc->Release();
		}
		pDesktopFolder->Release();
	}

	return bRet;
}



CProcessMgr::LEXER CProcessMgr :: LexCommand( CString & strToken ) {
	strToken = TEXT("");

	ASSERT(m_pstrCmd != 0);

	// skip leading blanks ...
	for( ; m_nIdx < m_nLen && m_strSpace.Find(m_pstrCmd->GetAt(m_nIdx)) >= 0; ++m_nIdx );

	if( m_nIdx >= m_nLen )
		return TOK_EOF;

	if( m_pstrCmd->GetAt(m_nIdx) == TEXT('"') ) {
		// quoted string
		while( ++m_nIdx < m_nLen && m_pstrCmd->GetAt(m_nIdx) != TEXT('"') )
			strToken += m_pstrCmd->GetAt(m_nIdx);
		++m_nIdx;
	} else {
		// simple string
		while( m_nIdx < m_nLen && m_strSpace.Find(m_pstrCmd->GetAt(m_nIdx)) < 0 ) {
			register const BOOL bSep = (m_pstrCmd->GetAt(m_nIdx) == TEXT(';')) ? TRUE : FALSE;

			if( bSep )
				if( strToken.GetLength() )
					break;

			strToken += m_pstrCmd->GetAt(m_nIdx++);

			if( bSep )
				break;
		}
	}

	if( strToken.CompareNoCase(TEXT("cd")) == 0 )
		return TOK_CD;
	if( strToken == TEXT(";") )
		return TOK_CMDSEP;

	return TOK_STRING;
}


BOOL CProcessMgr :: ParseCommand( const CString & strCmdLine, CString & strDirectory, CString & strCmd, CString & strArgs ) {
	strCmd = TEXT("");
	strArgs = TEXT("");
	strDirectory = TEXT("");

	CString strToken;
	LEXER eToken, eLastToken = TOK_EOF;
	BOOL bNeedSep = FALSE;

	m_pstrCmd = &strCmdLine;
	m_nIdx = 0;
	m_nLen = m_pstrCmd->GetLength();

	do {
		if( (eToken = LexCommand(strToken)) == TOK_STRING ) {
			if( eLastToken == TOK_CD ) {
				if( strCmd.GetLength() )
					return FALSE;
				strDirectory = strToken;
				if( (eToken = LexCommand(strToken)) != TOK_CMDSEP )
					return FALSE;
			} else if( strCmd.GetLength() == 0 )
				strCmd = strToken;
			else if( strCmd.GetLength() > 0 ) {
				if( bNeedSep )
					strArgs += TEXT(" ");
				strArgs += strToken;
				bNeedSep = TRUE;
			}
		}

		if( eToken == TOK_EOF && strCmd.IsEmpty() )
			return FALSE;	// at least a command must be given

		eLastToken = eToken;
	} while( eToken != TOK_EOF );

	return TRUE;
}


DWORD CProcessMgr :: Execute(
						const CString & strCmd,
						const CString & strArgs,
						const CString & strDir,
						BOOL bWait) {
	TRACE3("ProcessMgr::Execute(%s,%s,%s)\n",LPCTSTR(strCmd),LPCTSTR(strArgs),LPCTSTR(strDir));

	CString strPath;
	if( GetLinkInfo(strCmd, strPath) ) {
		TRACE1( "link points to \"%s\".\n", LPCTSTR(strPath) );
	} else {
		TRACE1( "\"%s\" is not a link\n", LPCTSTR(strCmd) ) ;
		strPath = strCmd;
	}

	// first check, which program to use to start <strCmd>
	TCHAR szExe[1024];
	if( int(FindExecutable(
			strPath,									// pointer to filename
			strDir.IsEmpty() ? 0 : LPCTSTR(strDir),		// pointer to default directory
			szExe										// result-buffer
		)) <= 32 ) {
		OnExecError(GetLastError(), strCmd);
		return 0;
	}
	TRACE2("found association for \"%s\": \"%s\"\n", LPCTSTR(strCmd),szExe);

	CString strCmdLine = strPath;
	if( !strArgs.IsEmpty() )
		strCmdLine += " " + strArgs;

	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
	StartupInfo.cb = sizeof(STARTUPINFO);

	PROCESS_INFORMATION ProcessInfo;
	DWORD dwRetVal = 0;

	BOOL bStat =	CreateProcess(
						szExe,						// pointer to name of executable module 
						LPTSTR(LPCTSTR(strCmdLine)),// pointer to command line string 
						0,							// pointer to process security attributes 
						0,							// pointer to thread security attributes 
						TRUE,						// handle inheritance flag 
						0,							// creation flags 
						0,							// pointer to new environment block 
						strDir.IsEmpty() ? 0 : LPCTSTR(strDir),
						&StartupInfo,				// pointer to STARTUPINFO 
						&ProcessInfo				// pointer to PROCESS_INFORMATION 
					);
	if( bStat ) {
		if( bWait )
			dwRetVal = Wait( DWORD(ProcessInfo.hProcess) );
		else
			dwRetVal = DWORD(ProcessInfo.hProcess);

		CloseHandle(ProcessInfo.hThread);
	} else
		OnExecError(GetLastError(), strCmd);

	return dwRetVal;
}


DWORD CProcessMgr :: Wait( DWORD PID ) const {
	DWORD dwRetVal = 0;
	HANDLE hProcess = HANDLE(PID);
	WaitForSingleObject(hProcess, INFINITE);
	GetExitCodeProcess(hProcess, &dwRetVal);
	CloseHandle(hProcess);
	return dwRetVal;
}

BOOL CProcessMgr :: GetErrorText( int nError, CString & strErrText ) {
    LPTSTR lpszTemp = 0;

    DWORD dwRet =	::FormatMessage(
						FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_ARGUMENT_ARRAY,
						0,
						nError,
						LANG_NEUTRAL,
						(LPTSTR)&lpszTemp,
						0,
						0
					);

	if( dwRet ) {
        lpszTemp[_tcsclen(lpszTemp)-2] = TEXT('\0');  //remove cr/nl characters
	    strErrText = lpszTemp;
    }

    if( lpszTemp )
        LocalFree(HLOCAL(lpszTemp));

    return dwRet ? TRUE : FALSE;
}


void CProcessMgr :: OnExecError(int nError, const CString & strCmd) {
	CString strErr;
	if( ! GetErrorText(nError, strErr) )
		strErr = TEXT("Unknown error.");
	CString strMes = strCmd;
	strMes += TEXT("\r\n");
	strMes += strErr;
	AfxMessageBox(strMes, MB_ICONSTOP|MB_APPLMODAL);
}