////////////////////////////////////////////////////////
//
// CSTA.h - Copyright 1997, Don Box 
//
// A SingleThreadedApartment that accepts activation
// requests via PostMessage.
//

#ifndef _CSTA_H
#define _CSTA_H


#include <windows.h>
#include <assert.h>

class CSingleThreadedApartment
{
    DWORD               m_dwThreadId;
    HANDLE              m_hthread;
    CRITICAL_SECTION    m_cs;
    HANDLE              m_heventDone;
    IStream             *m_pStmMarshalData;
    HRESULT             m_hresultRequest;
    CLSID               m_clsid;
    IID                 m_iid;
    enum REQUEST_TYPE
    {  
        WM_CREATEINSTANCE = WM_USER + 0x400,
        WM_GETCLASSOBJECT
    };

    static DWORD WINAPI ThreadProc(void*);
    HRESULT SwitchToApartment(REQUEST_TYPE rt, REFCLSID rclsid, 
                              REFIID riid, void **ppv);
    void OnCreateInstance(void);
    void OnGetClassObject(void);
    
    class Lock 
    {
        CRITICAL_SECTION *m_pcs;
    public:
        Lock(CSingleThreadedApartment *pThis)
            : m_pcs(&pThis->m_cs)
        { EnterCriticalSection(m_pcs); }
        ~Lock(void)
            
        { LeaveCriticalSection(m_pcs); }
    };
    friend class Lock;
public:
    CSingleThreadedApartment(void);
    ~CSingleThreadedApartment(void);

    HRESULT RequestNewObject(REFCLSID rclsid, REFIID riid, void **ppv);
    HRESULT RequestClassObject(REFCLSID rclsid, REFIID riid, void **ppv);
    DWORD RequestShutdown(DWORD dwTimeOut = INFINITE);

};

#endif
