#ifndef NTENUM_H_INCLUDED
#define NTENUM_H_INCLUDED

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vdmdbg.h>
#include <psapi.h>
#include <string.h>

#include "enum.h"

//Windows NT Functions
typedef BOOL (WINAPI *ENUMPROCESSES)(
  DWORD * lpidProcess,  // array to receive the process identifiers
  DWORD cb,             // size of the array
  DWORD * cbNeeded      // receives the number of bytes returned
);

typedef BOOL (WINAPI *ENUMPROCESSMODULES)(
  HANDLE hProcess,      // handle to the process
  HMODULE * lphModule,  // array to receive the module handles
  DWORD cb,             // size of the array
  LPDWORD lpcbNeeded    // receives the number of bytes returned
);

typedef DWORD (WINAPI *GETMODULEFILENAME)( 
  HANDLE hProcess,		// handle to the process
  HMODULE hModule,		// handle to the module
  LPTSTR lpstrFileName,	// array to receive filename
  DWORD nSize			// size of filename array.
);

typedef DWORD (WINAPI *GETMODULEBASENAME)( 
  HANDLE hProcess,		// handle to the process
  HMODULE hModule,		// handle to the module
  LPTSTR lpstrFileName,	// array to receive base name of module
  DWORD nSize			// size of module name array.
);

typedef INT (WINAPI *VDMENUMTASKWOWEX)(
  DWORD dwProcessId,	// ID of NTVDM process
  TASKENUMPROCEX fp,	// address of our callback function
  LPARAM lparam);		// anything we want to pass to the callback function.

class NT_process_enumerator : public process_enumerator {

	enum { max_num = 1024 };

    HANDLE psapi; 
	HANDLE vdmdbg;

    ENUMPROCESSES       EnumProcesses;
    GETMODULEFILENAME   GetModuleFileName;
    ENUMPROCESSMODULES  EnumProcessModules;  
	VDMENUMTASKWOWEX	VDMEnumTaskWOWEx;
	GETMODULEBASENAME	GetModuleBaseName;

	static BOOL WINAPI show_task(DWORD dwThreadId, 
								 WORD hMod16, 
								 WORD hTask16,
								 PSZ pszModName, 
								 PSZ FileName, 
                                 LPARAM lpUserDefined);

    void show_task(char const *FileName, DWORD ProcessID) {
		process_enumerator::show_task(FileName, ProcessID);
	}

public:
    NT_process_enumerator(display &d);
	virtual bool real_show();	
};

#endif
