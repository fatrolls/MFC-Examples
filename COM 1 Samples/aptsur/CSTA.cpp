////////////////////////////////////////////////////////
//
// CSTA.cpp - Copyright 1997, Don Box 
//
// A SingleThreadedApartment that accepts activation
// requests via PostMessage.
//


#include "CSTA.h"

#if !defined(_WIN32_WINNT) || _WIN32_WINNT < 0x402
#error "You need to define _WIN32_WINNT=0x402 and use SP2-compliant SDK headers to compile this file."
#endif        

DWORD WINAPI CSingleThreadedApartment::ThreadProc(void *pv)
{
    CSingleThreadedApartment *pThis = (CSingleThreadedApartment *)pv;
    CoInitializeEx(0, COINIT_APARTMENTTHREADED);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        switch (msg.message)
        {
        case WM_CREATEINSTANCE:
            pThis->OnCreateInstance();
            break;
        case WM_GETCLASSOBJECT:
            pThis->OnGetClassObject();
            break;
        default:
            DispatchMessage(&msg);
        }
    }

    CoUninitialize();
    return 0;
}

void 
CSingleThreadedApartment::OnCreateInstance(void)
{
    IUnknown *pUnk = 0;
    m_pStmMarshalData = 0;
    m_hresultRequest = CoCreateInstance(m_clsid, 0, CLSCTX_INPROC_SERVER,
                                        m_iid, (void**)&pUnk);
    if (SUCCEEDED(m_hresultRequest))
    {
        m_hresultRequest = CoMarshalInterThreadInterfaceInStream(m_iid, pUnk, &m_pStmMarshalData);
        pUnk->Release();
    }
    SetEvent(m_heventDone);
}

void 
CSingleThreadedApartment::OnGetClassObject(void)
{
    IUnknown *pUnk = 0;
    m_pStmMarshalData = 0;
    m_hresultRequest = CoGetClassObject(m_clsid, CLSCTX_INPROC_SERVER, 0,
                                        m_iid, (void**)&pUnk);
    if (SUCCEEDED(m_hresultRequest))
    {
        m_hresultRequest = CoMarshalInterThreadInterfaceInStream(m_iid, pUnk, &m_pStmMarshalData);
        pUnk->Release();
    }
    SetEvent(m_heventDone);
}

CSingleThreadedApartment::CSingleThreadedApartment(void)
{
    InitializeCriticalSection(&m_cs);
    m_heventDone = CreateEvent(0, FALSE, FALSE, 0);
    assert(m_heventDone);
    m_pStmMarshalData = 0;
    m_hresultRequest = E_FAIL;
    m_clsid = GUID_NULL;
    m_iid = GUID_NULL;
    m_hthread = CreateThread(0, 0, ThreadProc, this, CREATE_SUSPENDED, &m_dwThreadId);
    assert(m_hthread);
    ResumeThread(m_hthread);
}

CSingleThreadedApartment::~CSingleThreadedApartment(void)
{
    DeleteCriticalSection(&m_cs);
    CloseHandle(m_heventDone);
    CloseHandle(m_hthread);
    if (m_pStmMarshalData)
        m_pStmMarshalData->Release();
}

HRESULT 
CSingleThreadedApartment::SwitchToApartment(REQUEST_TYPE rt, REFCLSID rclsid, 
                                            REFIID riid, void **ppv)
{
    HRESULT hr = E_FAIL;
    *ppv = 0;
// lock this apartment for the duration of the call
    Lock mtx(this); 
// set [in] parameters
    m_clsid = rclsid;
    m_iid = riid;
// switch to target thread
    PostThreadMessage(m_dwThreadId, rt, 0, 0);
// wait for completion notification
    DWORD dwWait = WaitForSingleObject(m_heventDone, INFINITE);
    if (dwWait == WAIT_OBJECT_0)
    {
// harvest [out] parameter(s)
        if (SUCCEEDED(hr = m_hresultRequest))
        {
            hr = CoGetInterfaceAndReleaseStream(m_pStmMarshalData, riid, ppv);
            m_pStmMarshalData = 0;
        }
    }
    else
        hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, GetLastError());
    return hr;
}

HRESULT 
CSingleThreadedApartment::RequestNewObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    return SwitchToApartment(WM_CREATEINSTANCE, rclsid, riid, ppv);
}

HRESULT 
CSingleThreadedApartment::RequestClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    return SwitchToApartment(WM_GETCLASSOBJECT, rclsid, riid, ppv);
}

DWORD 
CSingleThreadedApartment::RequestShutdown(DWORD dwTimeOut)
{
    PostThreadMessage(m_dwThreadId, WM_QUIT, 0, 0);
    return 0;
}

