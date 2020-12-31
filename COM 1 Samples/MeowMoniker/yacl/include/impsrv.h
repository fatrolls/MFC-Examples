///////////////////////////////////////////////////////////////////////////////
//
// impsrv.h - Copyright 1995-1997, Don Box
//
// This file contains several macros and function prototypes that
// automate implementing servers.
//
//    HINSTANCE GetThisInstance(void); // returns this HINSTANCE
//
// There are two routines for detecting the standard commandline
// arguments:
//
//    PARSE_RESULT SvcParseCommandLine(const char *); 
//    PARSE_RESULT SvcParseCommandLineV(int argc, char **argv); 
//
// There are several default implementations of ModuleAddRef, ModuleRelease,
// ModuleIsStopping, ModuleIsIdle, and ModuleServerListen
//
//   IMPLEMENT_MTAEXE_MODULE_ROUTINES() - out-of-proc MTA server
//   IMPLEMENT_STAEXE_MODULE_ROUTINES() - out-of-proc STA server
//   IMPLEMENT_DLL_MODULE_ROUTINES() - in-proc server
//
// There is also a macro that automates the boilerplate code for 
// implementing the 4 standard COM inproc server exports:
//
//    IMPLEMENT_DLL_ENTRY_POINTS(ClassTable, ModuleRegTable, bModuleHasTypeLib)
//
// There is also a macro that automates the boilerplate code for 
// implementing the CoRegisterClassObject/Wait/CoRevokeClassObject sequence
// for out-of-process servers:
//
//    IMPLEMENT_EXE_ENTRY_POINTS(szCmdParam, ClassTable, ModuleRegTable, bModuleHasTypeLib, dwClsCtx, dwRegCls)
//


#ifndef _IMPSRV_H
#define _IMPSRV_H

EXTERN_C HINSTANCE STDAPICALLTYPE GetThisInstance(void);

#ifdef EXESVC

enum PARSE_RESULT {
    PARSE_NORMAL,
    PARSE_REGISTER_SERVER,
    PARSE_UNREGISTER_SERVER,
    PARSE_AUTOMATION,
    PARSE_EMBEDDING
};

EXTERN_C PARSE_RESULT STDAPICALLTYPE SvcParseCommandLine(char *pszCmdParam);
EXTERN_C PARSE_RESULT STDAPICALLTYPE SvcParseCommandLineV(int argc, char **argv, int *pargTag);

#define IMPLEMENT_MTAEXE_MODULE_ROUTINES()\
HANDLE g_heventDone = CreateEvent(0, TRUE, FALSE, 0);\
void STDAPICALLTYPE ModuleAddRef(void)\
{\
    CoAddRefServerProcess();\
}\
void STDAPICALLTYPE  ModuleRelease(void)\
{\
    if (CoReleaseServerProcess() == 0)\
        SetEvent(g_heventDone);\
}\
BOOL STDAPICALLTYPE ModuleIsStopping(void)\
{\
    return WaitForSingleObject(g_heventDone, 0) == WAIT_OBJECT_0;\
}\
void STDAPICALLTYPE ModuleServerListen(void)\
{\
    WaitForSingleObject(g_heventDone, INFINITE);\
}\

#define IMPLEMENT_STAEXE_MODULE_ROUTINES()\
HANDLE g_heventDone = CreateEvent(0, TRUE, FALSE, 0);\
void STDAPICALLTYPE ModuleAddRef(void)\
{\
    CoAddRefServerProcess();\
}\
void STDAPICALLTYPE  ModuleRelease(void)\
{\
    if (CoReleaseServerProcess() == 0)\
        SetEvent(g_heventDone);\
}\
BOOL STDAPICALLTYPE ModuleIsStopping(void)\
{\
    return WaitForSingleObject(g_heventDone, 0) == WAIT_OBJECT_0;\
}\
void STDAPICALLTYPE ModuleServerListen(void)\
{\
    DWORD dw;\
    while ((dw = MsgWaitForMultipleObjects(1, &g_heventDone, FALSE, INFINITE, QS_ALLINPUT)) != WAIT_OBJECT_0)\
    {\
        MSG msg;\
        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))\
            DispatchMessage(&msg);\
    }\
}\

#define IMPLEMENT_EXE_ENTRY_POINTS(szCmdParam, ClassTable, ModuleRegTable, bModuleHasTypeLib, dwClsCtx, dwRegCls)\
PARSE_RESULT action = SvcParseCommandLine(szCmdParam);\
if (action == PARSE_REGISTER_SERVER)\
    ClassTableUpdateRegistry(hInstance, ClassTable, ModuleRegTable, bModuleHasTypeLib, TRUE);\
else if (action == PARSE_UNREGISTER_SERVER)\
    ClassTableUpdateRegistry(hInstance, ClassTable, ModuleRegTable, bModuleHasTypeLib, FALSE);\
else if (action == PARSE_EMBEDDING || action == PARSE_AUTOMATION)\
{\
    hr = ClassTableRegisterClassObjects(ClassTable, dwClsCtx, dwRegCls);\
    if (SUCCEEDED(hr))\
    {\
        ModuleServerListen();\
        hr = ClassTableRevokeClassObjects(ClassTable);\
    }\
}



#else

#define IMPLEMENT_DLL_MODULE_ROUTINES()\
LONG g_cLocks = 0;\
void STDAPICALLTYPE ModuleAddRef(void)\
{\
    InterlockedIncrement(&g_cLocks);\
}\
void STDAPICALLTYPE  ModuleRelease(void)\
{\
    InterlockedDecrement(&g_cLocks);\
}\
BOOL STDAPICALLTYPE ModuleIsStopping(void)\
{\
    return FALSE;\
}\
BOOL STDAPICALLTYPE ModuleIsIdle(void)\
{\
    return g_cLocks == 0;\
}\

#define IMPLEMENT_DLL_ENTRY_POINTS(ClassTable, ModuleRegTable, bModuleHasTypeLib)\
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)\
{\
    return ClassTableGetClassObject(ClassTable, rclsid, riid, ppv);\
}\
STDAPI DllCanUnloadNow(void)\
{\
    return ModuleIsIdle() ? S_OK : S_FALSE;\
}\
STDAPI DllRegisterServer(void)\
{\
    return ClassTableUpdateRegistry(GetThisInstance(), ClassTable, ModuleRegTable, bModuleHasTypeLib, TRUE);\
}\
STDAPI DllUnregisterServer(void)\
{\
    return ClassTableUpdateRegistry(GetThisInstance(), ClassTable, ModuleRegTable, bModuleHasTypeLib, FALSE);\
}\


#endif

#endif