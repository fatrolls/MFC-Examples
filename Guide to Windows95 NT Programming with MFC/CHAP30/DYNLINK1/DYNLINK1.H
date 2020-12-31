///////////////////////////////////////////////////////////////////
//  Header  : DYNLINK1.H
//
//  Purpose : Header file for the DYNLINK1.DLL
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 06-02-96
///////////////////////////////////////////////////////////////////

// Macro for DLL exports in Win32, replaces Win16 __export
#define DllImport  __declspec(dllimport)

// Prototype
DllImport LONG Multiply2Longs(LONG lNum1, LONG lNum2);

