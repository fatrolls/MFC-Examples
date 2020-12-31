#include "NTenum.h"

NT_process_enumerator::NT_process_enumerator(display &d) :
    process_enumerator(d)
{
    psapi = LoadLibrary("PSAPI.DLL");
    vdmdbg = LoadLibrary("VDMDBG.DLL");

	if ( NULL == psapi || NULL == vdmdbg )
        return;

	VDMEnumTaskWOWEx = (VDMENUMTASKWOWEX)GetProcAddress(
        (HINSTANCE)vdmdbg, "VDMEnumTaskWOWEx");

	EnumProcesses =(ENUMPROCESSES)GetProcAddress(
			(HINSTANCE)psapi, "EnumProcesses");

	GetModuleFileName = (GETMODULEFILENAME)GetProcAddress(
			(HINSTANCE)psapi, "GetModuleFileNameExA");

	GetModuleBaseName = (GETMODULEBASENAME)GetProcAddress(
			(HINSTANCE)psapi, "GetModuleBaseNameA");

	EnumProcessModules = (ENUMPROCESSMODULES)GetProcAddress(
			(HINSTANCE)psapi, "EnumProcessModules");

	if (
		NULL == VDMEnumTaskWOWEx	||
		NULL == EnumProcesses		|| 
		NULL == GetModuleFileName	|| 
		NULL == GetModuleBaseName	||
		NULL == EnumProcessModules  )
        return;
}

bool
NT_process_enumerator::real_show() {

    DWORD process_ids[max_num];
    DWORD num_processes;

    if (
		NULL == VDMEnumTaskWOWEx	||
		NULL == EnumProcesses		|| 
		NULL == GetModuleFileName	|| 
		NULL == GetModuleBaseName	||
		NULL == EnumProcessModules  )
        return false;

    int success = EnumProcesses(process_ids, 
        sizeof(process_ids), 
        &num_processes);

    num_processes /= sizeof(process_ids[0]);

    if ( !success ) {
        disp.system_error("Enumerating Processes");
        return false;
    }  

    for ( unsigned i=0; i<num_processes; i++) {

        HANDLE process = OpenProcess(
            PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 
            FALSE, 
            process_ids[i]);

        HMODULE modules[max_num];
        DWORD num_modules;
        char file_name[MAX_PATH];

        EnumProcessModules(process,  
                           modules, 
                           sizeof(modules), 
                           &num_modules);

        num_modules /= sizeof(modules[0]);

        if (GetModuleFileName(process, 
                              modules[0], 
                              file_name, 
                              sizeof(file_name))) 
        {
			show_task(file_name, process_ids[i]);

			GetModuleBaseName(process,
							  modules[0],
							  file_name,
							  sizeof(file_name));

            if ( 0 == _stricmp(file_name, "NTVDM.EXE"))
            {
                // We've got an NT VDM -- enumerate the processes
                // it contains.
                VDMEnumTaskWOWEx(process_ids[i], show_task, (long)&disp);
            }
        }
        CloseHandle(process);
    }
	FreeLibrary((HINSTANCE)vdmdbg);
	FreeLibrary((HINSTANCE)psapi);
	return true;
}

BOOL WINAPI
NT_process_enumerator::show_task(DWORD dwThreadId,
                                 WORD hMod16,
                                 WORD hTask16,
                                 PSZ pszModName,
                                 PSZ FileName,
                                 LPARAM lpUserDefined)
{
    display &disp = *(display *)lpUserDefined;

    char string[256];
    wsprintf(string,"     %-55s\t%#10x", FileName, hTask16);
    disp << string;
    return TRUE;
}
