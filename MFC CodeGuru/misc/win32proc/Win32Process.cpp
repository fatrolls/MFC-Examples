// Win32Process.cpp: implementation of the Win32Process class.
//
//////////////////////////////////////////////////////////////////////

/******************************************************************************\
		Win32Process: a Win95/NT-compatible class for acquiring the list
		of currently active processes.
		Copyright (C) 1998 Tomer Petel
		You may modify and/or integrate this code into your commercial software
		for free in exchange for a small e-mail, just so I can know
		if this code ever became useful to someone else but me.
		email to: tomerp@eng2.uconn.edu
\******************************************************************************/

#include "stdafx.h"
#include "Win32Process.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Win32Process::Win32Process()
{
	m_p_fnProcess32Next=NULL;
	m_p_fnProcess32First=NULL;
	m_p_fnCreateToolhelp32Snapshot=NULL;
}

Win32Process::~Win32Process()
{
	m_strArray.RemoveAll();
}

bool Win32Process::Init()
{
	DWORD dwVersion = ::GetVersion();

   // Windows NT?
   if(dwVersion < 0x80000000) 
       // Yes, Windows NT
	   m_bIsNt=true;
    // Windows 95?
   else if(LOBYTE(LOWORD(dwVersion)) >= 4) 
	   m_bIsNt=false;
   else
   {
	   m_strLastError=_T("Unsupported OS version");
	   return false;  // Win16, 32s or NT3.x.
   }
   ////if its Win95, we must get the appropriate function pointers...
   ////This esnures that we dont tie up to a specific Compiler option, and that we can run on
   ////both 95 or NT (because NT does not have the following procedures in its kernel32.dll)
 
   if (!m_bIsNt)
   { 
		//// If here, We are running on Win95. Must use the tool help functions....

		m_hWin95Kernel=GetModuleHandle(_T("kernel32.dll"));
		if(!m_hWin95Kernel)
		{
			m_strLastError=_T("Could not get kernel32 handle");
			return false;
		}
		m_p_fnCreateToolhelp32Snapshot=(PFN_CREATETHELP32SNPSHT)GetProcAddress(m_hWin95Kernel,"CreateToolhelp32Snapshot");
		if (!m_p_fnCreateToolhelp32Snapshot)
		{
			m_strLastError=_T("Could not get CreateToolhelp32Snapshot pointer");
			return false;
		}

		m_p_fnProcess32First=(PFN_PROCESS32FIRST)GetProcAddress(m_hWin95Kernel,"Process32First");
		if (!m_p_fnProcess32First)
		{
			m_strLastError=_T("Could not get Process32First pointer");
			return false;
		}

		m_p_fnProcess32Next=(PFN_PROCESS32NEXT)GetProcAddress(m_hWin95Kernel,"Process32Next");
		if (!m_p_fnProcess32Next)
		{
			m_strLastError=_T("Could not get Process32Next pointer");
			return false;
		}

   }
   return true;

}

bool Win32Process::GetProcessStatus(CString* procname, bool* status)
{
	/// On exit from this pprocedure, status will be true if the process under question is alive...
	if (m_bIsNt)
	{
		if(FindProcessesNT(procname,true))
		{
			*status=m_bActive;
			return true;
		}
		else 
			return false;
	}
	else
	{
		//we are on Win95...
		//make the process name lower case, since we anyway cannot deal with case differences in Win95 ToolHelp functions...
		procname->MakeLower();
		if (FindProcesses95(procname,true))
		{
			*status=m_bActive;
			return true;
		}
		else 
			return false;
	}

		
}

bool Win32Process::EnumAllProcesses()
{
	if (m_bIsNt)
		//we are on NT
		return FindProcessesNT(NULL,false);
	else		
		//we are on Win95...
		return FindProcesses95(NULL,false);
	
}

CString Win32Process::GetLastError()
{
	return m_strLastError;
}

CStringArray* Win32Process::GetAllProcessesNames()
{
	//returns an MFC string array pointer, containint all the processes names...
	return &m_strArray;
}


bool Win32Process::FindProcessesNT(CString* ProcessName, bool bJustCheckingOne)
{
	///This function gets all the running process, the winNT way, using the
	///registry. If you simply are checking if a process is active
	///pass its name as a parameter and make the second parameter false.
	///Otherwise, the function will ignore the ProcessName param and add to the array
	///all the currently active processes...
	
	if (!bJustCheckingOne)
	{
		m_strArray.RemoveAll();
	}
	else
	{
		m_bActive=false;
		ASSERT ((*ProcessName)!=""); ///If just checking if a process is alive, this must be the process' name
	}
 
	//This following was coded using the tlist example, but is it optimized, 
	//to only search for processes names.

	bool						 bErrorOccured=false;
	DWORD                        rc;
    HKEY                         hKeyNames;
    DWORD                        dwType;
    DWORD                        dwSize;
    LPBYTE                       buf = NULL;
    TCHAR                        szSubKey[1024];
    LANGID                       lid;
    LPSTR                        p;
    LPSTR                        p2;
    PPERF_DATA_BLOCK             pPerf;
    PPERF_OBJECT_TYPE            pObj;
    PPERF_INSTANCE_DEFINITION    pInst;
    PPERF_COUNTER_BLOCK          pCounter;
    DWORD                        i;
    TCHAR                         szProcessName[MAX_PATH];
    DWORD                        dwLimit = 256;
	DWORD dwNumTasks;
    lid = MAKELANGID(LANG_ENGLISH, SUBLANG_NEUTRAL);
    _stprintf( szSubKey, _T("%s\\%03x"), REGKEY_PERF, lid );
    rc = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                       szSubKey,
                       0,
                       KEY_READ,
                       &hKeyNames
                     );
    if (rc != ERROR_SUCCESS)
	{
		bErrorOccured=true;
		m_strLastError=_T("Could not open performance registry key");
        goto exit;

    }

    //
    // get the buffer size for the counter names
    //
    rc = RegQueryValueEx(hKeyNames,
                          REGSUBKEY_COUNTERS,
                          NULL,
                          &dwType,
                          NULL,
                          &dwSize
                        );

    if (rc != ERROR_SUCCESS)
	{
		bErrorOccured=true;
		m_strLastError=_T("Could not open counter registry key");
        goto exit;
    }

    //
    // allocate the counter names buffer
    //
    buf = (LPBYTE) malloc(dwSize);
    if (buf == NULL)
	{
		bErrorOccured=true;
		m_strLastError=_T("Out of Memory");
        goto exit;
    }
    memset(buf, 0, dwSize);

    //
    // read the counter names from the registry
    //
    rc = RegQueryValueEx( hKeyNames,
                          REGSUBKEY_COUNTERS,
                          NULL,
                          &dwType,
                          buf,
                          &dwSize
                        );

    if (rc != ERROR_SUCCESS) 
	{
		bErrorOccured=true;
		m_strLastError=_T("Could Not Read the counter Names");
        goto exit;
    }

    //
    // now loop thru the counter names looking for the "Process" counters:
    // the buffer contains multiple null terminated strings and then
    // finally null terminated at the end.  the strings are in pairs of
    // counter number and counter name.
    //

    p =(LPSTR) buf;
    while (*p) 
	{
        if (p > (LPSTR)buf) 
		{
            for( p2=p-2; _istdigit(*p2); p2--)
						;
        }
        if (_tcsicmp(p, PROCESS_COUNTER) == 0)
		{
            // look backwards for the counter number
            for(p2=p-2; _istdigit(*p2); p2--) 
						;
            _tcscpy(szSubKey, p2+1);
        }
        p += (_tcslen(p) + 1);
    }


    // free the counter names buffer
    free(buf);


    // allocate the initial buffer for the performance data

    dwSize = INITIAL_SIZE;
    buf = (LPBYTE)malloc( dwSize );
    if (buf == NULL)
	{
		bErrorOccured=true;
		m_strLastError=_T("Out of Memory");
        goto exit;
    }
    memset(buf, 0, dwSize);
    while (true)
	{

        rc = RegQueryValueEx( HKEY_PERFORMANCE_DATA,
                              szSubKey,
                              NULL,
                              &dwType,
                              buf,
                              &dwSize
                            );

        pPerf = (PPERF_DATA_BLOCK) buf;

        // check for success and valid perf data block signature

        if ((rc == ERROR_SUCCESS) &&
            (dwSize > 0) &&
            (pPerf)->Signature[0] == (WCHAR)'P' &&
            (pPerf)->Signature[1] == (WCHAR)'E' &&
            (pPerf)->Signature[2] == (WCHAR)'R' &&
            (pPerf)->Signature[3] == (WCHAR)'F' )
		{
            break;
        }

        // if buffer is not big enough, reallocate and try again

        if (rc == ERROR_MORE_DATA)
		{
            dwSize += EXTEND_SIZE;
            buf = (LPBYTE)realloc( buf, dwSize );
            memset( buf, 0, dwSize );
        }
        else 
		{
			bErrorOccured=true;
			m_strLastError=_T("Could Not Obtain Performance Data");
			goto exit;
        }
    }

    // set the perf_object_type pointer

    pObj = (PPERF_OBJECT_TYPE) ((DWORD)pPerf + pPerf->HeaderLength);
    dwNumTasks = min( dwLimit, (DWORD)pObj->NumInstances );
    pInst = (PPERF_INSTANCE_DEFINITION) ((DWORD)pObj + pObj->DefinitionLength);

    // loop thru the performance instance data extracting each process name

    for (i=0; i<dwNumTasks; i++)
	{
        //
        // pointer to the process name
        //
        p = (LPSTR) ((DWORD)pInst + pInst->NameOffset);

        //
        // convert it to ascii
        //
        rc = WideCharToMultiByte( CP_ACP,
                                  0,
                                  (LPCWSTR)p,
                                  -1,
                                  szProcessName,
                                  sizeof(szProcessName),
                                  NULL,
                                  NULL
                                );

		if (rc)
		{
			if (bJustCheckingOne)
			{
				if (ProcessName->CompareNoCase(szProcessName)==0)
				{	//found the process. It is running!
					m_bActive=true;
					goto exit;
				}
			}
			else
   				m_strArray.Add(szProcessName);
		}
        // get the process id
        pCounter = (PPERF_COUNTER_BLOCK) ((DWORD)pInst + pInst->ByteLength);
        // next process
        pInst = (PPERF_INSTANCE_DEFINITION) ((DWORD)pCounter + pCounter->ByteLength);
    }

exit:
    if (buf) 
	{
        free(buf);
    }

    RegCloseKey(hKeyNames);
    RegCloseKey(HKEY_PERFORMANCE_DATA);
	return !bErrorOccured;

}


bool Win32Process::FindProcesses95(CString* ProcessName, bool bJustCheckingOne)
{
	///This function gets all the running process, the win95 way, using the
	///ToolHelp functions. If you simply are checking if a process is active
	///pass its name as a parameter and make the second parameter false.
	///Otherwise, the function will ignore the ProcessName param and add to the array
	///all the currently active processes...
	ASSERT(m_p_fnProcess32Next);
	ASSERT(m_p_fnProcess32First);
	ASSERT(m_p_fnCreateToolhelp32Snapshot);	   ///must have successfully called Init() first

	
	if (!bJustCheckingOne)
	{
		m_strArray.RemoveAll();
	}
	else
	{
		m_bActive=false;
		ASSERT ((*ProcessName)!=""); ///If just checking if a process is alive, this must be the process' name
	}
	HANDLE handle;
	handle=m_p_fnCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if ((const int)handle==-1)
	{
		m_strLastError=_T("Failed in creating snapshot");
		return false;
	}

	PROCESSENTRY32 process;
	process.dwSize=sizeof(PROCESSENTRY32);

	BOOL bContinue=m_p_fnProcess32First(handle,&process);

	while(bContinue)
	{
		if (!bJustCheckingOne) //do we want to enumerate all processes, or do we just wanna check if one is active?
			m_strArray.Add(ExtractProcessName(process.szExeFile));
		else
		{
			///if here, then we are just looking to see if a certain process is alive...
			if ((*ProcessName)==ExtractProcessName(process.szExeFile))
			{
				///found the process, it is active....
				CloseHandle(handle);	
				m_bActive=true;
				return true;
			}
		}
		bContinue=m_p_fnProcess32Next(handle,&process);
	}

	CloseHandle(handle);		
	return true;
}

bool Win32Process::IsWinNT()
{
	return m_bIsNt;
}

TCHAR * Win32Process::ExtractProcessName(TCHAR * path)
{
	//gets the process name out of the whole path name and makes it lower case.
	//this is only necessary in WIN95 since the ToolHelp functions return 
	//the entire path of the executable, in upper case...

	ASSERT (path);
	TCHAR *p, *tmp=_tcsrchr (path, '\\');
	if (tmp)
	{	
		tmp++; //get after the backslash
		p=_tcsrchr (tmp, '.');
		*p=0;				  //get rid of the .exe extension
		return (_tcslwr(tmp)); //make it lower case and return it.
	}
	else	 //couldnt find the backslash: just deal with the .exe:
	{
		p=_tcsrchr (path, '.');
		*p=0;				  //get rid of the .exe extension
		return (_tcslwr(path)); //make it lower case and return it.
	}
}
