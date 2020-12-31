/////////////////////////////////////////////////////
//
// ChatSession.cpp
//
// Copyright 1997, Don Box/Addison Wesley
//
// This code accompanies the book "The Component
// Object Model" from Addison Wesley. Blah blah blah
//
//

#include "ChatSession.h"
#include <iaccess.h>

// these routines are defined in svc.cpp to 
// control server lifetime
extern void ModuleLock(void);
extern void ModuleUnlock(void);

// these access control objects are created
// in svc.cpp to control various privileged 
// operations. Most operations in this class
// are non-privileged, so anyone can get in.
extern IAccessControl *g_pacUsers;
extern IAccessControl *g_pacAdmins;

// utility functions /////////////////////////

// duplicate an OLECHAR * using CoTaskMemAlloc
OLECHAR *OLESTRDUP(const OLECHAR *pwsz)
{
    DWORD cb = sizeof(OLECHAR)*(wcslen(pwsz) + 1);
    OLECHAR *pwszResult = (OLECHAR*)CoTaskMemAlloc(cb);
    if (pwszResult)
        wcscpy(pwszResult, pwsz);
    return pwszResult;
}

// get the caller's username (or "anonymous" if
// no authentication was specified by the caller).
OLECHAR *GetCaller(void)
{
    OLECHAR *pwsz = 0;
    HRESULT hr = CoQueryClientBlanket(0,0,0,0,0,(void**)&pwsz,0);
    if (SUCCEEDED(hr))
        return OLESTRDUP(pwsz);
    else
        return OLESTRDUP(OLESTR("anonymous"));
}

// class ChatSession ///////////////////////////////

ChatSession::ChatSession(const OLECHAR *pwszSessionName,
                         bool bAllowAnonymousAccess)
: m_cRef(0),
  m_bAllowAnonymousAccess(bAllowAnonymousAccess),
  m_pHeadListeners(0)
{
    wcscpy(m_wszSessionName, pwszSessionName);
    InitializeCriticalSection(&m_csStatementLock);
    InitializeCriticalSection(&m_csAdviseLock);
}

ChatSession::~ChatSession(void)
{
    DeleteCriticalSection(&m_csStatementLock);
    DeleteCriticalSection(&m_csAdviseLock);
// tear down connected listeners
    while (m_pHeadListeners)
    {
        LISTENER *pThisNode = m_pHeadListeners;
        if (pThisNode->pItf)
            pThisNode->pItf->Release();
        if (pThisNode->pwszUser)
            CoTaskMemFree(pThisNode->pwszUser);
        m_pHeadListeners = pThisNode->pNext;
        delete pThisNode;
    }
}

// helper methods ///////////

void ChatSession::Disconnect(void)
{
    CoDisconnectObject(this, 0);
// tear down connected listeners
    ALock();
    while (m_pHeadListeners)
    {
        LISTENER *pThisNode = m_pHeadListeners;
        if (pThisNode->pItf)
            pThisNode->pItf->Release();
        if (pThisNode->pwszUser)
            CoTaskMemFree(pThisNode->pwszUser);
        m_pHeadListeners = pThisNode->pNext;
        delete pThisNode;
    }
    AUnlock();
}

// send the OnNewStatement event to all listeners
void 
ChatSession::Fire_OnNewStatement(const OLECHAR *pwszUser,
                                 const OLECHAR *pwszStatement)
{
    ALock();
    for (LISTENER *pNode = m_pHeadListeners;
         pNode != 0; pNode = pNode->pNext)
    {
        if (pNode->pItf)
            pNode->pItf->OnNewStatement(pwszUser, pwszStatement);
    }
    AUnlock();
}

// send the OnNewUser event to all listeners
void 
ChatSession::Fire_OnNewUser(const OLECHAR *pwszUser)
{
    ALock();
    for (LISTENER *pNode = m_pHeadListeners;
         pNode != 0; pNode = pNode->pNext)
    {
        if (pNode->pItf)
            pNode->pItf->OnNewUser(pwszUser);
    }
    AUnlock();
}

// send the OnUserLeft event to all listeners
void 
ChatSession::Fire_OnUserLeft(const OLECHAR *pwszUser)
{
    ALock();
    for (LISTENER *pNode = m_pHeadListeners;
         pNode != 0; pNode = pNode->pNext)
    {
        if (pNode->pItf)
            pNode->pItf->OnUserLeft(pwszUser);
    }
    AUnlock();
}

// lock wrappers
void ChatSession::SLock(void)
{
    EnterCriticalSection(&m_csStatementLock);
}

void ChatSession::SUnlock(void)
{
    LeaveCriticalSection(&m_csStatementLock);
}

void ChatSession::ALock(void)
{
    EnterCriticalSection(&m_csAdviseLock);
}

void ChatSession::AUnlock(void)
{
    LeaveCriticalSection(&m_csAdviseLock);
}

// helper method to check access to Say method
bool 
ChatSession::CheckAccess(const OLECHAR *pwszUser)
{
    if (wcscmp(pwszUser, L"anonymous") == 0)
        return m_bAllowAnonymousAccess;
// form trustee from caller and use Access Control
// object hardwired to COMChat Users group
    TRUSTEEW trustee = {
        0, NO_MULTIPLE_TRUSTEE, TRUSTEE_IS_NAME, 
        TRUSTEE_IS_USER, 
        const_cast<OLECHAR*>(pwszUser) 
    };
    BOOL bIsAllowed;
    HRESULT hr = g_pacUsers->IsAccessAllowed(&trustee,0,
                                             COM_RIGHTS_EXECUTE, 
                                             &bIsAllowed);
    return SUCCEEDED(hr) && bIsAllowed != FALSE;
}

// IUnknown methods
STDMETHODIMP 
ChatSession::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
        *ppv = static_cast<IChatSession*>(this);
    else if (riid == IID_IChatSession)
        *ppv = static_cast<IChatSession*>(this);
    else 
        return (*ppv = 0), E_NOINTERFACE;
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;

}

STDMETHODIMP_(ULONG) 
ChatSession::AddRef(void)
{
    ModuleLock();
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) 
ChatSession::Release(void)
{
    LONG res = InterlockedDecrement(&m_cRef);
    if (res == 0)
        delete this;
    ModuleUnlock();
    return res;
}

// IChatSession methods
STDMETHODIMP 
ChatSession::get_SessionName(OLECHAR **ppwsz)
{
    if (!ppwsz)
        return E_INVALIDARG;
    else if ((*ppwsz = OLESTRDUP(m_wszSessionName)) == 0)
        return E_OUTOFMEMORY;
    return S_OK;
}

STDMETHODIMP 
ChatSession::Say(const OLECHAR *pwszStatement)
{
    HRESULT hr = S_OK;
// protect access to method
    OLECHAR *pwszUser = GetCaller();
    if (pwszUser && CheckAccess(pwszUser))
    {
        SLock();
        try
        {
            wstring s = pwszUser;
            s += L":";
            s += pwszStatement;
            m_statements.push_back(s);
        }
        catch(...)
        {
            hr = E_OUTOFMEMORY;
        }
        SUnlock();
        if (SUCCEEDED(hr))
            Fire_OnNewStatement(pwszUser, pwszStatement);
    }
    else
        hr = E_ACCESSDENIED;
    CoTaskMemFree(pwszUser);
    return hr;
}

STDMETHODIMP 
ChatSession::GetStatements(IEnumString **ppes)
{
    if (ppes == 0)
        return E_INVALIDARG;
    *ppes = new StatementEnumerator(this);
    if (*ppes == 0)
        return E_OUTOFMEMORY;
    (*ppes)->AddRef();
    return S_OK;
}

STDMETHODIMP 
ChatSession::Advise(IChatSessionEvents *pEventSink, 
                    DWORD *pdwReg)
{
    HRESULT hr = S_OK;
    if (pEventSink == 0 || pdwReg == 0)
        return E_INVALIDARG;
    LISTENER *pNew = new LISTENER;
    if (pNew == 0)
        return E_OUTOFMEMORY;
    OLECHAR *pwszUser = GetCaller();
    if (pwszUser)
    {
        Fire_OnNewUser(pwszUser);
        ALock();
        pNew->pwszUser = pwszUser;
        if (pNew->pItf = pEventSink)
            pEventSink->AddRef();
        pNew->pNext = m_pHeadListeners;
        if (m_pHeadListeners)
            m_pHeadListeners->pPrev = pNew;
        pNew->pPrev = 0;
        m_pHeadListeners = pNew;
        AUnlock();
    }
    else
    {
        delete pNew;
        return E_OUTOFMEMORY;
    }
    *pdwReg = reinterpret_cast<DWORD>(pNew);
    return hr;
}

STDMETHODIMP 
ChatSession::Unadvise(DWORD dwReg)
{
    if (dwReg == 0)
        return E_INVALIDARG;
    HRESULT hr = S_OK;
    LISTENER *pThisNode = reinterpret_cast<LISTENER *>(dwReg);
    ALock();
    if (pThisNode->pPrev)
        pThisNode->pPrev->pNext = pThisNode->pNext;
    else
        m_pHeadListeners = pThisNode->pNext;
    if (pThisNode->pNext)
        pThisNode->pNext->pPrev = pThisNode->pPrev;
    if (pThisNode->pItf)
        pThisNode->pItf->Release();
    OLECHAR *pwszUser = pThisNode->pwszUser;
    delete pThisNode;
    AUnlock();
    Fire_OnUserLeft(pwszUser);
    CoTaskMemFree(pwszUser);
    return hr;
}

// class StatementEnumerator ///////////////////

StatementEnumerator::StatementEnumerator(ChatSession *pThis)
: m_cRef(0),
  m_pThis(pThis),
  m_cursor(pThis->m_statements.begin())
{
    m_pThis->AddRef();
    InitializeCriticalSection(&m_csLock);
}

StatementEnumerator::~StatementEnumerator(void)
{
    m_pThis->Release();
    DeleteCriticalSection(&m_csLock);
}

// lock helpers (note that ChatSession is locked
// simultaneously)
void
StatementEnumerator::Lock(void)
{
    EnterCriticalSection(&m_csLock);
    m_pThis->SLock();
}

void
StatementEnumerator::Unlock(void)
{
    LeaveCriticalSection(&m_csLock);
    m_pThis->SUnlock();
}

// IUnknown methods
STDMETHODIMP 
StatementEnumerator::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
        *ppv = static_cast<IEnumString*>(this);
    else if (riid == IID_IEnumString)
        *ppv = static_cast<IEnumString*>(this);
    else 
        return (*ppv = 0), E_NOINTERFACE;
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;

}

STDMETHODIMP_(ULONG) 
StatementEnumerator::AddRef(void)
{
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) 
StatementEnumerator::Release(void)
{
    LONG res = InterlockedDecrement(&m_cRef);
    if (res == 0)
        delete this;
    return res;
}

// IEnumString methods
STDMETHODIMP 
StatementEnumerator::Next(ULONG cElems, OLECHAR **rgElems, 
                          ULONG *pcFetched)
{
    if (pcFetched == 0 && cElems > 1)
        return E_INVALIDARG;
    ZeroMemory(rgElems, sizeof(OLECHAR*) * cElems);
    Lock();
    ULONG cActual = 0;
    while (cActual < cElems 
           && m_cursor != m_pThis->m_statements.end())
    {
        if (rgElems[cActual] = OLESTRDUP((*m_cursor).c_str()))
        {
            m_cursor++;
            cActual++;
        }
        else // allocation error, unwind
        {
            while (cActual > 0)
            {
                cActual--;
                CoTaskMemFree(rgElems[cActual]);
                rgElems[cActual] = 0;
            }
            break;
        }
    }
    Unlock();
    if (pcFetched)
        *pcFetched = cActual;
    return cElems == cActual ? S_OK : S_FALSE;
}

STDMETHODIMP 
StatementEnumerator::Skip(ULONG cElems)
{
    Lock();
    ULONG cActual = 0;
    while (cActual < cElems 
           && m_cursor != m_pThis->m_statements.end())
    {
        m_cursor++;
        cActual++;
    }
    Unlock();
    return cElems == cActual ? S_OK : S_FALSE;
}

STDMETHODIMP 
StatementEnumerator::Reset(void)
{
    Lock();
    m_cursor = m_pThis->m_statements.begin();
    Unlock();
    return S_OK;
}

STDMETHODIMP 
StatementEnumerator::Clone(IEnumString **ppes)
{
    if (ppes == 0)
        return E_INVALIDARG;
    if (*ppes = new StatementEnumerator(m_pThis))
        return S_OK;
    return E_OUTOFMEMORY;
}

// class ChatSessionClass /////////////////////

ChatSessionClass::ChatSessionClass(void)
: m_cStrongLocks(0)
{
    InitializeCriticalSection(&m_csSessionLock);
}

ChatSessionClass::~ChatSessionClass(void)
{
    DeleteCriticalSection(&m_csSessionLock);
}

void
ChatSessionClass::Lock(void)
{
    EnterCriticalSection(&m_csSessionLock);
}

void
ChatSessionClass::Unlock(void)
{
    LeaveCriticalSection(&m_csSessionLock);
}
// helper method to protect access to DeleteSession
// to only allow COMChat Admins to delete groups
bool 
ChatSessionClass::CheckAccess(const OLECHAR *pwszUser)
{
    if (wcscmp(pwszUser, L"anonymous") == 0)
        return false;

    TRUSTEEW trustee = {
        0, NO_MULTIPLE_TRUSTEE, TRUSTEE_IS_NAME, 
        TRUSTEE_IS_USER, const_cast<OLECHAR*>(pwszUser)
    };
    BOOL bIsAllowed;
    HRESULT hr = g_pacAdmins->IsAccessAllowed(&trustee,0,
                                              COM_RIGHTS_EXECUTE,
                                              &bIsAllowed);
    if (FAILED(hr))
        bIsAllowed = false;
    return SUCCEEDED(hr) && bIsAllowed != FALSE;
}


// IUnknown methods
STDMETHODIMP 
ChatSessionClass::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
        *ppv = static_cast<IChatSessionManager*>(this);
    else if (riid == IID_IChatSessionManager)
        *ppv = static_cast<IChatSessionManager*>(this);
    else if (riid == IID_IExternalConnection)
        *ppv = static_cast<IExternalConnection*>(this);
    else 
        return (*ppv = 0), E_NOINTERFACE;
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) 
ChatSessionClass::AddRef(void)
{
    return 2;
}

STDMETHODIMP_(ULONG) 
ChatSessionClass::Release(void)
{
    return 1;
}

// IExternalConnection methods
STDMETHODIMP_(DWORD) 
ChatSessionClass::AddConnection(DWORD extconn, DWORD)
{
    if (extconn & EXTCONN_STRONG)
    {
        ModuleLock();
        return InterlockedIncrement(&m_cStrongLocks);
    }
    return 0;
}

STDMETHODIMP_(DWORD) 
ChatSessionClass::ReleaseConnection(DWORD extconn, DWORD, 
                                    BOOL bLastReleaseKillsStub)
{
    if (extconn & EXTCONN_STRONG)
    {
        LONG res = InterlockedDecrement(&m_cStrongLocks);
        if (res == 0 && bLastReleaseKillsStub)
            CoDisconnectObject(
                static_cast<IExternalConnection*>(this), 0);
        ModuleUnlock();
        return res;
    }
    return 0;
}

// IChatSessionManager methods
STDMETHODIMP 
ChatSessionClass::GetSessionNames(IEnumString **ppes)
{
    if (ppes == 0)
        return E_INVALIDARG;
    if (*ppes = new SessionNamesEnumerator(this))
    {
        (*ppes)->AddRef();
        return S_OK;
    }
    else
        return E_OUTOFMEMORY;
}

STDMETHODIMP 
ChatSessionClass::FindSession(const OLECHAR *pwszSessionName, 
                              BOOL bDontCreate,
                              BOOL bAllowAnonymousAccess,
                              IChatSession **ppcs)
{
    if (ppcs == 0)
        return E_INVALIDARG;
    HRESULT hr = E_FAIL;
    *ppcs = 0;
    OLECHAR *pwszUser = GetCaller();
    Lock();
    SESSIONMAP::iterator it = m_sessions.find(pwszSessionName);
    if (it == m_sessions.end())
    {
        if (bDontCreate)
            hr = E_FAIL;
        else if (!bAllowAnonymousAccess 
                 && wcscmp(pwszUser, L"anonymous") == 0)
            hr = E_ACCESSDENIED;
        else 
        {
            ChatSession *pNew = 
                new ChatSession(pwszSessionName, 
                                bAllowAnonymousAccess != FALSE);
            if (pNew)
            {
                pNew->AddRef();
                m_sessions.insert(
                    pair<wstring,
                         ChatSession*>(pwszSessionName,
                                       pNew));
                (*ppcs = pNew)->AddRef();
                hr = S_OK;
            }
            else 
                hr = E_OUTOFMEMORY;
        }
    }
    else
    {
        (*ppcs = (*it).second)->AddRef();
        hr = S_OK;
    }
    Unlock();
    CoTaskMemFree(pwszUser);
    return hr;
}

STDMETHODIMP 
ChatSessionClass::DeleteSession(const OLECHAR *pwszSessionName)
{
    if (pwszSessionName == 0)
        return E_INVALIDARG;
    HRESULT hr = E_FAIL;
    OLECHAR *pwszUser = GetCaller();
    if (CheckAccess(pwszUser))
    {
        Lock();
        SESSIONMAP::iterator it 
                        = m_sessions.find(pwszSessionName);
        if (it == m_sessions.end())
        {
            hr = E_FAIL;
        }
        else
        {
            (*it).second->Disconnect();
            (*it).second->Release();
            m_sessions.erase(it);
            hr = S_OK;
        }
        Unlock();
    }
    else
        hr = E_ACCESSDENIED;
    CoTaskMemFree(pwszUser);
    return hr;
}

// class SessionNamesEnumerator 

vector<wstring>& 
SessionNamesEnumerator::Strings(void)
{
    if (m_pStrings)
        return *m_pStrings;
    else 
        return *(m_pCloneSource->m_pStrings);
}

void 
SessionNamesEnumerator::Lock(void)
{
    EnterCriticalSection(&m_csLock);
}

void 
SessionNamesEnumerator::Unlock(void)
{
    LeaveCriticalSection(&m_csLock);
}

SessionNamesEnumerator::SessionNamesEnumerator(
                                 ChatSessionClass *pSessionClass)
: m_cRef(0),
  m_pStrings(0),
  m_pCloneSource(0)
{
    typedef ChatSessionClass::SESSIONMAP::iterator iterator;
    ChatSessionClass::SESSIONMAP &sessions 
        = pSessionClass->m_sessions;
    m_pStrings = new vector<wstring>;
    pSessionClass->Lock();
    for (iterator it = sessions.begin();
         it != sessions.end();
         it++)
    {
        m_pStrings->push_back((*it).first);
    }
    pSessionClass->Unlock();
    m_cursor = Strings().begin();
    InitializeCriticalSection(&m_csLock);
}

SessionNamesEnumerator::SessionNamesEnumerator(
                        SessionNamesEnumerator *pCloneSource)
: m_cRef(0),
  m_pStrings(0),
  m_pCloneSource(pCloneSource)
{
    m_pCloneSource->AddRef();
    m_cursor = Strings().begin();
    InitializeCriticalSection(&m_csLock);
}

SessionNamesEnumerator::~SessionNamesEnumerator(void)
{
    if (m_pCloneSource)
        m_pCloneSource->Release();
    else if (m_pStrings)
        delete m_pStrings;
    DeleteCriticalSection(&m_csLock);
}

// IUnknown methods

STDMETHODIMP 
SessionNamesEnumerator::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
        *ppv = static_cast<IEnumString*>(this);
    else if (riid == IID_IEnumString)
        *ppv = static_cast<IEnumString*>(this);
    else 
        return (*ppv = 0), E_NOINTERFACE;
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) 
SessionNamesEnumerator::AddRef(void)
{
    ModuleLock();
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) 
SessionNamesEnumerator::Release(void)
{
    LONG res = InterlockedDecrement(&m_cRef);
    if (res == 0)
        delete this;
    ModuleUnlock();
    return res;
}

// IEnumString methods
STDMETHODIMP 
SessionNamesEnumerator::Next(ULONG cElems, OLECHAR **rgElems, 
                             ULONG *pcFetched)
{
    if (cElems > 1 && pcFetched == 0)
        return E_INVALIDARG;
    ULONG cActual = 0;
    vector<wstring> &rstrings = Strings();
    Lock();
    while (cActual < cElems 
           && m_cursor != rstrings.end())
    {
        if (rgElems[cActual] = OLESTRDUP((*m_cursor).c_str()))
        {
            m_cursor++;
            cActual++;
        }
        else // allocation error, unwind
        {
            while (cActual > 0)
            {
                cActual--;
                CoTaskMemFree(rgElems[cActual]);
                rgElems[cActual] = 0;
            }
            break;
        }
    }
    Unlock();
    if (cActual)
        *pcFetched = cActual;
    return cActual == cElems ? S_OK : S_FALSE; 
}

STDMETHODIMP 
SessionNamesEnumerator::Skip(ULONG cElems)
{
    ULONG cActual = 0;
    vector<wstring> &rstrings = Strings();
    Lock();
    while (cActual < cElems 
           && m_cursor != rstrings.end())
    {
        m_cursor++;
        cActual++;
    }
    Unlock();
    return cActual == cElems ? S_OK : S_FALSE; 
}

STDMETHODIMP 
SessionNamesEnumerator::Reset(void)
{
    Lock();
    m_cursor = Strings().begin();
    Unlock();
    return S_OK;
}

STDMETHODIMP 
SessionNamesEnumerator::Clone(IEnumString **ppes)
{
    if (ppes == 0)
        return E_INVALIDARG;
    SessionNamesEnumerator *pCloneSource = m_pCloneSource;
    if (pCloneSource == 0) // we are the source
        m_pCloneSource = this;
    *ppes = new SessionNamesEnumerator(pCloneSource);
    if (*ppes)
    {
        (*ppes)->AddRef();
        return S_OK;
    }
    return E_OUTOFMEMORY;
}
