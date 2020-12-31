///////////////////////////////////////////////////////////////////////////////
//
// regtable.h - Copyright 1996-1997, Don Box
//
// This file contains a datatype, REGISTRY_ENTRY that can be used to build
// tables that contain registry strings. 
//
// The data structure REGISTRY_ENTRY should be considered opaque, and the
// the following preprocesor macros:
//
//     BEGIN_REGISTRY_TABLE(tablename) - begins table named tablename
//     REGISTRY_KEY(hkeyRoot, "key", "valueName", "value", flags) - adds new key
//     REGISTRY_SUBKEY("subkey", "valueName", "value", flags) - adds subkey beneath the last REGISTRY_KEY entry
//     END_REGISTRY_TABLE() - terminates table definition
//
// where flags can be one of the following:
// 
//    REGFLAG_NORMAL - add at install, remove at uninstall
//    REGFLAG_NEVER_DELETE - add at install, ignore at uninstall
//    REGFLAG_DELETE_WHEN_REGISTERING - remove at install, ignore at uninstall
//    REGFLAG_DELETE_BEFORE_REGISTERING - remove then add at install, remove at uninstall
//
//  The following wrapper macros define a routine called UpdateRegistry
//  based on a registry table:
//
//     BEGIN_CLASS_REGISTRY_TABLE(ClassName)
//     END_CLASS_REGISTRY_TABLE()
//
//  The following convenience macro defines the default entries for a coclass:
//
//     DEFAULT_CLASS_REGISTRY_ENTRIES(szCLSID, szFriendlyName, szProgID, szVersionIndependentProgID, szThreadingModel)
//
//  The following convenience macro defines an UpdateRegistry routine that 
//  contains only the default entries for a coclass:
//
//     DEFAULT_CLASS_REGISTRY_TABLE(ClassName, szCLSID, szFriendlyName, szProgID, szVersionIndependentProgID, szThreadingModel)
//
//  
//  The following pre-defined pseudo-strings are allowed:
//
//     REG_MODULE_NAME - a token that is replaced with the actual module name
//     REG_SERVER_TYPE - "InprocServer32" or "LocalServer32" depending on DLLSVC/EXESVC
//     REG_DEFAULT_VALUE - used to indicate default value
//
// This file contains the prototype for a routine that adds/removes
// the table's registry entries and optionally registers a type library.
//
//     RegistryTableUpdateRegistry - adds/removes registry entries for table
//     
// Usage:
/*
class Hello : public IHello {
DEFAULT_CLASS_REGISTRY_TABLE(Hello, 
                             "{12345678-1234-1234-1234-123412341234}", 
                             "Hello Class", 
                             "HelloLib.Hello.1", 
                             "HelloLib.Hello", 
                             "both")  
};

class Goodbye : public IHello {
BEGIN_REGISTRY_TABLE(Goodbye)
    REGISTRY_KEY(HKEY_CLASSES_ROOT, "CLSID\\{12345678-1234-1234-1234-123412341234}", 0, "Goodbye Class", REGFLAGS_DELETE_BEFORE_REGISTERING)  
        REGISTRY_SUBKEY("Automation", 0, "", REGFLAGS_NORMAL)  
        REGISTRY_SUBKEY(REG_SERVER_TYPE, 0, REG_MODULE_NAME, REGFLAGS_NORMAL)  
END_REGISTRY_TABLE()
};
*/

#ifndef _REGTABLE_H
#define _REGTABLE_H

// basic table layout
typedef struct _REGISTRY_ENTRY {
    HKEY        hkeyRoot;
    const char *pszKey;
    const char *pszValueName;
    const char *pszValue;
    int         fFlags;
} REGISTRY_ENTRY;

// the routine that inserts/deletes Registry keys based on the table
EXTERN_C HRESULT STDAPICALLTYPE RegistryTableUpdateRegistry(HINSTANCE hInstance, REGISTRY_ENTRY *pEntries, BOOL bRegisterModuleAsTypeLib, BOOL bInstalling);

// some default strings
#define REG_DEFAULT_VALUE 0 
#define REG_MODULE_NAME ((char*)-1)
#if defined(DLLSVC)
    #define REG_SERVER_TYPE "InprocServer32"
#elif defined(EXESVC)
    #define REG_SERVER_TYPE "LocalServer32"
#endif

// flags for 
enum REGFLAGS {
    REGFLAG_NORMAL = 0x0,
    REGFLAG_NEVER_DELETE = 0x1,
    REGFLAG_DELETE_WHEN_REGISTERING = 0x2,
    REGFLAG_DELETE_BEFORE_REGISTERING = 0x4
};


#define BEGIN_REGISTRY_TABLE(TableName) \
static REGISTRY_ENTRY TableName [] = {        

#define REGISTRY_KEY(hkr, pszKey, pszValueName, pszValue, fFlags) \
    { hkr, pszKey, pszValueName, pszValue, fFlags },

#define REGISTRY_SUBKEY(pszSubKey, pszValueName, pszValue, fFlags) \
    { 0, pszSubKey, pszValueName, pszValue, (fFlags|0x1000) },

#define END_REGISTRY_TABLE() \
    { 0, 0, 0, 0, -1 } \
};

#define BEGIN_CLASS_REGISTRY_TABLE(ClassName) \
    static HRESULT STDAPICALLTYPE UpdateRegistry(HINSTANCE hInstance, BOOL bInstalling) \
    {\
        BEGIN_REGISTRY_TABLE(entries)

#define END_CLASS_REGISTRY_TABLE() \
        END_REGISTRY_TABLE()\
        return RegistryTableUpdateRegistry(hInstance, entries, FALSE, bInstalling);\
    }   

#ifdef DLLSVC
#define DEFAULT_CLASS_REGISTRY_ENTRIES(szCLSID, szFriendlyName, szProgID, szVersionIndependentProgID, szThreadingModel)\
REGISTRY_KEY(HKEY_CLASSES_ROOT, szProgID, 0, szFriendlyName, REGFLAG_DELETE_BEFORE_REGISTERING)\
    REGISTRY_SUBKEY("CLSID", 0, szCLSID, REGFLAG_NORMAL)\
REGISTRY_KEY(HKEY_CLASSES_ROOT, szVersionIndependentProgID, 0, szFriendlyName, REGFLAG_NORMAL)\
    REGISTRY_SUBKEY("CurVer", 0, szProgID, REGFLAG_NORMAL)\
REGISTRY_KEY(HKEY_CLASSES_ROOT, "CLSID\\" szCLSID, 0, szFriendlyName, REGFLAG_NORMAL)\
    REGISTRY_SUBKEY(REG_SERVER_TYPE, 0, REG_MODULE_NAME, REGFLAG_NORMAL)\
    REGISTRY_SUBKEY(REG_SERVER_TYPE, "ThreadingModel", "Both", REGFLAG_NORMAL)\
    REGISTRY_SUBKEY("ProgID", 0, szProgID, REGFLAG_NORMAL)\
    REGISTRY_SUBKEY("VersionIndependentProgID", 0, szVersionIndependentProgID, REGFLAG_NORMAL)\

#else

#define DEFAULT_CLASS_REGISTRY_ENTRIES(szCLSID, szFriendlyName, szProgID, szVersionIndependentProgID, szThreadingModel)\
REGISTRY_KEY(HKEY_CLASSES_ROOT, szProgID, 0, szFriendlyName, REGFLAG_DELETE_BEFORE_REGISTERING)\
    REGISTRY_SUBKEY("CLSID", 0, szCLSID, REGFLAG_NORMAL)\
REGISTRY_KEY(HKEY_CLASSES_ROOT, szVersionIndependentProgID, 0, szFriendlyName, REGFLAG_NORMAL)\
    REGISTRY_SUBKEY("CurVer", 0, szProgID, REGFLAG_NORMAL)\
REGISTRY_KEY(HKEY_CLASSES_ROOT, "CLSID\\" szCLSID, 0, szFriendlyName, REGFLAG_NORMAL)\
    REGISTRY_SUBKEY(REG_SERVER_TYPE, 0, REG_MODULE_NAME, REGFLAG_NORMAL)\
    REGISTRY_SUBKEY("ProgID", 0, szProgID, REGFLAG_NORMAL)\
    REGISTRY_SUBKEY("VersionIndependentProgID", 0, szVersionIndependentProgID, REGFLAG_NORMAL)\

#endif

#define DEFAULT_CLASS_REGISTRY_TABLE(ClassName, szCLSID, szFriendlyName, szProgID, szVersionIndependentProgID, szThreadingModel)\
BEGIN_CLASS_REGISTRY_TABLE(ClassName)\
DEFAULT_CLASS_REGISTRY_ENTRIES(szCLSID, szFriendlyName, szProgID, szVersionIndependentProgID, szThreadingModel)\
END_CLASS_REGISTRY_TABLE()



#endif

