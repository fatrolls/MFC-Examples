#include "95enum.h"

Win95_enumerator::Win95_enumerator(display &d) :
	process_enumerator(d),
	kernel(GetModuleHandle("KERNEL32.DLL")) 
{
	if ( NULL == kernel )
        return;

	CreateToolhelp32Snapshot = 
			(CREATESNAPSHOT)GetProcAddress((HINSTANCE)kernel, 
			"CreateToolhelp32Snapshot"); 
	Process32First = (PROCESSWALK)GetProcAddress((HINSTANCE)kernel, 
			"Process32First"); 
	Process32Next  = (PROCESSWALK)GetProcAddress((HINSTANCE)kernel, 
			"Process32Next"); 

	if (
		NULL == CreateToolhelp32Snapshot	|| 
		NULL == Process32First				||
        NULL == Process32Next)
        return;
    proc.dwSize = sizeof(proc);
}

bool Win95_enumerator::real_show() 
{

    if (
		NULL == CreateToolhelp32Snapshot	|| 
		NULL == Process32First				||
        NULL == Process32Next)
        return false;

    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

/* Now that we have a snapshot of the system state, we simply
 * walk the list it represents by calling Process32First once,
 * then call Proces32Next repeatedly until we get to the end 
 * of the list.
 */
    Process32First(snapshot, &proc);
    show_task(proc.szExeFile, proc.th32ProcessID);

    while (TRUE == Process32Next(snapshot, &proc))
        show_task(proc.szExeFile, proc.th32ProcessID);

/* This should happen automatically when we terminate, but it never
 * hurts to clean up after ourselves.
 */
    CloseHandle(snapshot);

    return true;
}
