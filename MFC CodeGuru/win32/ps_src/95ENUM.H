#ifndef WIN95_ENUM_H_INLCUDED
#define WIN95_ENUM_H_INLCUDED

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>   // Toolhelp 32
#include "enum.h"

// Win95 functions
typedef BOOL (WINAPI *PROCESSWALK)(
    HANDLE hSnapshot,    
    LPPROCESSENTRY32 lppe
);
 
typedef HANDLE (WINAPI *CREATESNAPSHOT)(
    DWORD dwFlags, 
    DWORD th32ProcessID
); 

class Win95_enumerator : public process_enumerator 
{

	HANDLE kernel;
    HANDLE snapshot;
    PROCESSENTRY32 proc;

    CREATESNAPSHOT CreateToolhelp32Snapshot; 
    PROCESSWALK Process32First; 
    PROCESSWALK Process32Next; 

protected:
	virtual bool real_show();

public:
    Win95_enumerator(display &d);
};

#endif
