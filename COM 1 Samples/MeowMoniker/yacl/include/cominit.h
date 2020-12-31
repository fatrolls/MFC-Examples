///////////////////////////////////////////////////////////////////////////////
//
// cominit.h - Copyright 1997, Chris Sells
//
// Usage:
/*

#include <windows.h>
#include <ccominit.h>

int main()
{
    try
    {
        CComInit    com;

        // Use COM
    }
    catch( HRESULT hr )
    {
        return hr;
    }

    return S_OK;
}

*/

#ifndef __CCOMINIT_H__
#define __CCOMINIT_H__

struct CComInit
{
    CComInit(DWORD dwCoInit = COINIT_APARTMENTTHREADED)
    {
        HRESULT hr;
#ifdef __WIN32_DCOM
        hr = CoInitializeEx(0, dwCoInit);
#else
        hr = CoInitialize(0);
#endif
        if( FAILED(hr) ) throw hr;
    }

    ~CComInit()
    {
        CoUninitialize();
    }
};

#endif  // __CCOMINIT_H__
