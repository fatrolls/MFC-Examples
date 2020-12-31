///////////////////////////////////////////////////////////////////////////////
//
// itftable.h - Copyright 1995-1997, Don Box
//
// This file contains a datatype, INTERFACE_ENTRY that can be used to build
// tables that map IIDs onto vptrs. 
//
// The data structure INTERFACE_ENTRY should be considered opaque, and the
// the following preprocesor macros:
//
//     BEGIN_INTERFACE_TABLE(tablename) - begins function GetInterfaceEntries
//     INTERFACE_TABLE_ENTRY(piid, pfnFindItf, dwData) - generic entry
//     IMPLEMENTS_INTERFACE(itf) - IID_itf -> (itf*)this;
//     IMPLEMENTS_INTERFACE_AS(req, itf) - IID_req -> (itf*)this;
//     IMPLEMENTS_INTERFACE_WITH_COMPOSITE(itf, innerclass, member) - IID_itf -> (itf*)&this->member;
//     END_INTERFACE_TABLE() - terminates table/function definition
//
// where pfnFindItf can be any function with the following prototype:
//
//    HRESULT STDAPICALLTYPE Find(void *pThis, DWORD dwData, REFIID, void **);
// 
// This file contains the prototype for a routine that implements
// QueryInterface based on an interface table.
//
//     InterfaceTableQueryInterface - finds and AddRef's vptr on an object
//     

#ifndef _INTTABLE_H
#define _INTTABLE_H

typedef HRESULT (STDAPICALLTYPE *INTERFACE_FINDER)(void *pThis, DWORD dwData, REFIID riid, void **ppv);
#define ENTRY_IS_OFFSET INTERFACE_FINDER(-1)

// basic table layout
typedef struct _INTERFACE_ENTRY
{
    const IID * pIID;           // the IID to match
    INTERFACE_FINDER pfnFinder; // finder function
    long        dwData;         // aux data for finder function
} INTERFACE_ENTRY;

// the routine that implements QueryInterface basd on the table
EXTERN_C HRESULT STDAPICALLTYPE InterfaceTableQueryInterface(void *pThis, const INTERFACE_ENTRY *pTable, REFIID riid, void **ppv);

#define BASE_OFFSET(ClassName, BaseName) \
    (DWORD(static_cast<BaseName*>(reinterpret_cast<ClassName*>(0x10000000))) - 0x10000000)

#define COMPOSITE_OFFSET(ClassName, BaseName, MemberType, MemberName) \
    (DWORD(static_cast<BaseName*>(reinterpret_cast<MemberType*>(0x10000000 + offsetof(ClassName, MemberName)))) - 0x10000000)

#define BEGIN_INTERFACE_TABLE(ClassName) \
typedef ClassName _InterfaceTableClassName;\
static const INTERFACE_ENTRY *GetInterfaceTable(void) \
{\
    static const INTERFACE_ENTRY table[] = {\

#define INTERFACE_TABLE_ENTRY(piid, pfn, dwData) \
        { piid, pfn, dwData },

#define IMPLEMENTS_INTERFACE(ItfName) \
        { &IID_##ItfName, ENTRY_IS_OFFSET,  BASE_OFFSET(_InterfaceTableClassName, ItfName) },

#define IMPLEMENTS_INTERFACE_AS(RequestedItfName, BaseClassName) \
        { &IID_##RequestedItfName, ENTRY_IS_OFFSET ,  BASE_OFFSET(_InterfaceTableClassName, BaseClassName)},

#define IMPLEMENTS_INTERFACE_WITH_COMPOSITE(RequestedItfName, DataMemberType, DataMemberName) \
        { &IID_##RequestedItfName, ENTRY_IS_OFFSET ,  COMPOSITE_OFFSET(_InterfaceTableClassName, RequestedItfName, DataMemberType, DataMemberName) },

#define END_INTERFACE_TABLE() \
        { 0, 0, 0 }\
    };\
    return table;\
}

#endif

