/*****************************************************************************
Module name: hookDLL.h
Purpose: hooks dll function declarations
*****************************************************************************/

#ifndef HOOKDLL_H
#define HOOKDLL_H

#ifndef HOOKLIBAPI
#define HOOKLIBAPI  __declspec(dllimport)
#endif


///////////////////////////////////////////////////////////////////////////////


HOOKLIBAPI BOOL WINAPI Hook_Start (char* lpszClassNameToBeMonitored);
HOOKLIBAPI BOOL WINAPI Hook_Stop ();


///////////////////////////////// End of File /////////////////////////////////

#endif // HOOKDLL_H