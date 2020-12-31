///////////////////////////////////////////////////////////////////
//  Module   : DYNLINK1.C
//
//  Purpose  : Program to show how to write a basic Win32 DLL in C
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-02-96
///////////////////////////////////////////////////////////////////

#include <windows.h>

// Macro for DLL exports in Win32, replaces Win16 __export
#define DllExport  __declspec(dllexport)

///////////////////////////////////////////////////////////////////
// Multiply2Longs()

DllExport LONG Multiply2Longs(LONG lNum1, LONG lNum2) 
{ 
   return lNum1 * lNum2; 
}
