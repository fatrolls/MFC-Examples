////////////////////////////////////////////////////////
//
// CSurrogate.h - Copyright 1997, Don Box 
//
// An implementation of ISurrogate that that forwards 
// activation requests to one of N STAs.
//

#ifndef _CSURROGATE_H
#define _CSURROGATE_H


#include <windows.h>
#include <assert.h>
#include <vector>

#ifndef __ISurrogate_INTERFACE_DEFINED__
#error "You need to define _WIN32_WINNT=0x402 and use SP2-compliant SDK headers to compile this file."
#endif        

#include "CSTA.h"

class CSurrogate : public ISurrogate
{
// we need to track all of our class objects and CoRevoke them at teardown time
    std::vector<DWORD> m_rgdwReg;
    CSingleThreadedApartment *m_prgSTAs;
    int m_nMaxThreads;
    LONG m_iNextThread;
    DWORD m_dwThreadId;
    static CSurrogate *s_pSurrogate;
public:
    CSurrogate(int nSTAThreads);
    virtual ~CSurrogate(void);

// get correct apartment for next activation request
    CSingleThreadedApartment *GetNextApartment(REFCLSID rclsid);

    // IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    
    // ISurrogate methods
    STDMETHODIMP LoadDllServer(REFCLSID rclsid);
    STDMETHODIMP FreeSurrogate();

    static HRESULT ParseCommandLine(LPSTR szCmdParam,
                                 CLSID *pclsidInitial,
                                 GUID  *pappid);

    static CSurrogate *GetSurrogate(void);
};



#endif
