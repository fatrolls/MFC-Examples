///////////////////////////////////////////////////////////////////////////////
//
// clstable.h - Copyright 1997, Don Box
//
// This file contains a datatype, COCLASS_ENTRY that can be used to build
// tables that map CLSIDs onto GetClassObject/UpdateRegistry routines. These
// tables can be used to implement 3 of the 4 DllXXX entry points as well as
// most of the body of an out-of-process server.
//
// The data structure COCLASS_ENTRY should be considered opaque, and the
// the following preprocesor macros:
//
//     BEGIN_COCLASS_TABLE(tablename) - begins table named tablename
//     IMPLEMENTS_COCLASS(class) - (CLSID_class, class::GetClassObject, class::UpdateRegistry)
//     IMPLEMENTS_COCLASS_AS(coclass,class) - (CLSID_coclass, class::GetClassObject, class::UpdateRegistry)
//     COCLASS_TABLE_ENTRY(pclsid, pfngco, pfnur) - (pclsid, pfngco, pfnur)
//     END_COCLASS_TABLE() - terminates table definition
//
// This file contains the prototypes for several routines that manage 
// coclass tables and implement DllGetClassObject, DllRegisterServer, 
// DllUnregisterServer, and WinMain for out-of-process servers
//
//     ClassTableUpdateRegistry - installs/uninstalls registry entries
//     ClassTableGetClassObject - for use in DllGetClassObject
//     ClassTableRegisterClassObjects - used at start of WinMain in oop server
//     ClassTableRevokeClassObjects - used at end of WinMain in oop server
//     

#ifndef _CLSTABLE_H
#define _CLSTABLE_H

typedef HRESULT (STDAPICALLTYPE *GET_CLASS_OBJECT_PROC)(REFIID riid, void **ppv);
typedef HRESULT (STDAPICALLTYPE *UPDATE_REGISTRY_PROC)(HINSTANCE hInstance, BOOL bInstalling);

typedef struct _COCLASS_ENTRY {
    const CLSID            *pclsid;
    GET_CLASS_OBJECT_PROC   pfnGetClassObject;
    UPDATE_REGISTRY_PROC    pfnUpdateRegistry;
    DWORD                   dwReg;
} COCLASS_ENTRY;

#define BEGIN_COCLASS_TABLE(TableName) \
static COCLASS_ENTRY TableName[] = {

#define COCLASS_TABLE_ENTRY(pclsid, pfnGetClassObject, pfnUpdateRegistry)\
    { pclsid, pfnGetClassObject, pfnUpdateRegistry, 0 },


#ifdef __cplusplus
#define IMPLEMENTS_COCLASS(ClassName) \
    COCLASS_TABLE_ENTRY(&CLSID_##ClassName, ClassName::GetClassObject, ClassName::UpdateRegistry)

#define IMPLEMENTS_COCLASS_AS(RequestedClass, ClassName) \
    COCLASS_TABLE_ENTRY(&CLSID_##RequestedClass, ClassName::GetClassObject, ClassName::UpdateRegistry)
#endif

#define END_COCLASS_TABLE()\
    { &GUID_NULL, 0, 0, 0 }, \
};

struct _REGISTRY_ENTRY;

EXTERN_C HRESULT STDAPICALLTYPE ClassTableUpdateRegistry(HINSTANCE hInstance, COCLASS_ENTRY *pTable, struct _REGISTRY_ENTRY *pModuleRegTable, BOOL bModuleHasTypeLib, BOOL bInstalling);

EXTERN_C HRESULT STDAPICALLTYPE ClassTableGetClassObject(COCLASS_ENTRY *pTable, REFCLSID rclsid, REFIID riid, void **ppv);

EXTERN_C HRESULT STDAPICALLTYPE ClassTableRegisterClassObjects(COCLASS_ENTRY *pTable, 
                                                             DWORD dwClsCtx = CLSCTX_LOCAL_SERVER,
                                                             DWORD dwRegCls = REGCLS_MULTIPLEUSE,
                                                             BOOL bResumeClassObjects = TRUE);
EXTERN_C HRESULT STDAPICALLTYPE ClassTableRevokeClassObjects(COCLASS_ENTRY *pTable);

#endif

