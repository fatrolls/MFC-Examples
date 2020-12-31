///////////////////////////////////////////////////////////////////////////////
//
// combook.h - Copyright 1994-1997, Don Box
//
// This file includes the whole enchilada and can be brought into
// every translation unit
//
// It also defines one monster-sized macro that implements heap-based IUnknown,
// a default registry table and class factory, and begins an interface table definition:
//
//    IMPLEMENT_COCLASS(ClassName, szCLSID, szFriendlyName, szProgID, szVersionIndependentProgID, szThreadingModel)
//
// Usage:
/*

class Hello : public IHello, public IGoodbye
{
IMPLEMENT_COCLASS(Hello, "{12341234-1234-1234-1234-123412341234}", "Hello Class", "HelloLib.Hello.1", "HelloLib.Hello", "both")
    IMPLEMENTS_INTERFACE(IHello)
    IMPLEMENTS_INTERFACE(IGoodbye)
END_INTERFACE_TABLE()
};

BEGIN_COCLASS_TABLE(Classes)
    IMPLEMENTS_COCLASS(Hello)
END_COCLASS_TABLE()

IMPLEMENT_DLL_MODULE_ROUTINES()
IMPLEMENT_DLL_ENTRY_POINTS(Classes, 0, TRUE)

*/

#ifndef _COMBOOK_H
#define _COMBOOK_H

#include "clstable.h"
#include "inttable.h"
#include "regtable.h"
#if defined(DLLSVC) || defined(EXESVC)
#include "gencf.h"
#endif
#include "impunk.h"
#include "impsrv.h"
#include "smartif.h"
#include "ustring.h"

#define IMPLEMENT_COCLASS(ClassName, szCLSID, szFriendlyName, szProgID, szVersionIndependentProgID, szThreadingModel)\
DEFAULT_CLASS_REGISTRY_TABLE(ClassName, szCLSID, szFriendlyName, szProgID, szVersionIndependentProgID, szThreadingModel)\
IMPLEMENT_UNKNOWN(ClassName)\
IMPLEMENT_GENERIC_CLASS_FACTORY(ClassName)\
IMPLEMENT_CREATE_INSTANCE(ClassName)\
BEGIN_INTERFACE_TABLE(ClassName)\



#endif
