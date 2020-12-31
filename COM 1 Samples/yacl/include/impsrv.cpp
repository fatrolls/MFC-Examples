///////////////////////////////////////////////////////////////////////////////
//
// impsrv.h - Copyright 1995-1997, Don Box
//
// This file contains several function implementations that
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

#ifndef _IMPSRV_CPP
#define _IMPSRV_CPP

#include <windows.h>
#include "impsrv.h"

HINSTANCE STDAPICALLTYPE GetThisInstance(void)
{
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(GetThisInstance, &mbi, sizeof(mbi));
    return (HINSTANCE)mbi.AllocationBase;
}


#ifdef EXESVC

PARSE_RESULT STDAPICALLTYPE SvcParseCommandLine(char *pszCmdParam)
{
    char szCmdParam[MAX_PATH];
    lstrcpyA(szCmdParam, pszCmdParam);
    CharUpperA(szCmdParam);
    PARSE_RESULT result = PARSE_NORMAL;
    if (strstr(szCmdParam, "/REGSERVER") 
        || strstr(szCmdParam, "-REGSERVER"))
        result = PARSE_REGISTER_SERVER;
    else if (strstr(szCmdParam, "/UNREGSERVER") 
        || strstr(szCmdParam, "-UNREGSERVER"))
        result = PARSE_UNREGISTER_SERVER;
    else if (strstr(szCmdParam, "/AUTOMATION") 
        || strstr(szCmdParam, "-AUTOMATION"))
        result = PARSE_AUTOMATION;
    else if (strstr(szCmdParam, "/EMBEDDING") 
        || strstr(szCmdParam, "-EMBEDDING"))
        result = PARSE_EMBEDDING;
    return result;
}

PARSE_RESULT STDAPICALLTYPE SvcParseCommandLineV(int argc, char **argv, int *pargTag)
{
    PARSE_RESULT result = PARSE_NORMAL;
    int i = 0;
    for (i = 0; i < argc && (result == PARSE_NORMAL); i++)
    {
        if (!strcmpi(argv[i], "/REGSERVER") 
            || !strcmpi(argv[i], "-REGSERVER"))
            result = PARSE_REGISTER_SERVER;
        else if (!strcmpi(argv[i], "/UNREGSERVER") 
            || !strcmpi(argv[i], "-UNREGSERVER"))
            result = PARSE_UNREGISTER_SERVER;
        else if (!strcmpi(argv[i], "/EMBEDDING") 
            || !strcmpi(argv[i], "-EMBEDDING"))
            result = PARSE_EMBEDDING;
        else if (!strcmpi(argv[i], "/AUTOMATION") 
            || !strcmpi(argv[i], "-AUTOMATION"))
            result = PARSE_AUTOMATION;
    }
    if (result != PARSE_NORMAL && pargTag)
        *pargTag = i;
    return result;
}
#else
#endif


#endif