////////////////////////////////////////////////////////
//
// MultiSTASurrogate.cpp - Copyright 1997, Don Box 
//
// A custom surrogate that creates multiple STAs and
// spreads activation requests across them in a roundrobin
// fashion.
//
// Note: Be sure to configure your InprocServer to use this
//       process as a custom surrogate. 
//


#include "CSurrogate.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR szCmdParam, int)
{
// join the multi-threaded apartment
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    assert(hr == S_OK);

    GUID appid;
    CLSID clsidInitialClass;
    
// on input, we will receive the CLSID of the class that caused our surrogate 
// to load as a command line argument. 
    hr = CSurrogate::ParseCommandLine(szCmdParam, &clsidInitialClass, &appid);
    assert(hr == S_OK);
    if (SUCCEEDED(hr))
    {
// pick up access permission settings from our AppID.
        hr = CoInitializeSecurity((void*)&appid, -1, 0, 0,
                                          0, 0, 0, EOAC_APPID, 0);
// declare and register our implementation of ISurrogate
        int nThreads = 5;
        char *szThreadCount = strstr(szCmdParam, "-threads:");
        if (szThreadCount)
            nThreads = atoi(szThreadCount + 9);
        CSurrogate sur(nThreads); // we will use five STA threads
        hr = CoRegisterSurrogate(&sur);
        assert(hr == S_OK);

// explicitly load/register the initial CLSID manually
        hr = sur.LoadDllServer(clsidInitialClass);
        if (SUCCEEDED(hr))
        {
            MSG msg;
            while (GetMessage(&msg, 0, 0, 0))
                DispatchMessage(&msg);
        }
    }
    CoUninitialize();
    return 0;
}
