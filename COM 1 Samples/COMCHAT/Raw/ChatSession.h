/////////////////////////////////////////////////////
//
// ChatSession.h
//
// Copyright 1997, Don Box/Addison Wesley
//
// This code accompanies the book "The Component
// Object Model" from Addison Wesley. Blah blah blah
//
//

#ifndef _CHATSESSION_H
#define _CHATSESSION_H

// this pragma shuts up the compiler warnings due to
// the pre MSC11SP1 debugger choking on long template names.
#pragma warning(disable:4786)

#define _WIN32_WINNT 0x403
#include <windows.h>
#include <map>
#include <vector>
#include <string>
using namespace std;

// bring in IDL-generated interface definitions
#include "..\include\COMChat.h"

// this class models a particular chat session
class ChatSession : public IChatSession
{
    friend class StatementEnumerator;
    LONG	            m_cRef;
    CRITICAL_SECTION    m_csStatementLock;
    CRITICAL_SECTION    m_csAdviseLock;
    OLECHAR             m_wszSessionName[1024];
    bool	            m_bIsDeleted;
    bool                m_bAllowAnonymousAccess;
    vector<wstring>     m_statements;
    struct LISTENER
    {
        LISTENER           *pPrev;
        LISTENER           *pNext;
        OLECHAR            *pwszUser;
        IChatSessionEvents *pItf;
    };
    LISTENER           *m_pHeadListeners;
    void SLock(void);
    void SUnlock(void);
    void ALock(void);
    void AUnlock(void);
    bool CheckAccess(const OLECHAR *pwszUser);
protected:
    virtual ~ChatSession(void);
    void Fire_OnNewStatement(const OLECHAR *pwszUser,
                             const OLECHAR *pwszStatement);
    void Fire_OnNewUser(const OLECHAR *pwszUser);
    void Fire_OnUserLeft(const OLECHAR *pwszUser);
public:
    ChatSession(const OLECHAR *pwszSessionName,
                bool bAllowAnonymousAccess);
    
    void Disconnect(void);
// IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    
// IChatSession methods
    STDMETHODIMP get_SessionName(OLECHAR **ppwsz);
    STDMETHODIMP Say(const OLECHAR *pwszStatement);
    STDMETHODIMP GetStatements(IEnumString **ppes);
    STDMETHODIMP Advise(IChatSessionEvents *pEventSink, 
                        DWORD *pdwReg);
    STDMETHODIMP Unadvise(DWORD dwReg);
};

// this class enumerates the statements of a session
class StatementEnumerator : public IEnumString
{
    LONG                        m_cRef;
    ChatSession                *m_pThis;
    vector<wstring>::iterator   m_cursor;
    CRITICAL_SECTION            m_csLock;
protected:
    void Lock(void);
    void Unlock(void);
    virtual ~StatementEnumerator(void);
public:
    StatementEnumerator(ChatSession *pThis);

// IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    
// IEnumString methods
    STDMETHODIMP Next(ULONG cElems, OLECHAR **rgElems, 
                      ULONG *pcFetched);
    STDMETHODIMP Skip(ULONG cElems);
    STDMETHODIMP Reset(void);
    STDMETHODIMP Clone(IEnumString **ppes);
};

// this class models the management of chat sessions
// and acts as the class object for CLSID_ChatSession
class ChatSessionClass : public IChatSessionManager,
                         public IExternalConnection
{
    friend class SessionNamesEnumerator;
    typedef map<wstring, ChatSession *> SESSIONMAP;
    LONG                m_cStrongLocks;
    SESSIONMAP          m_sessions;
    CRITICAL_SECTION    m_csSessionLock;
    void Lock(void);
    void Unlock(void);
    bool CheckAccess(const OLECHAR *pwszUser);
public:
    virtual ~ChatSessionClass(void);
    ChatSessionClass(void);
    
    // IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    
// IExternalConnection methods
    STDMETHODIMP_(DWORD) AddConnection(DWORD extconn, DWORD);
    STDMETHODIMP_(DWORD) ReleaseConnection(DWORD extconn, DWORD, 
                                      BOOL bLastReleaseKillsStub);
// IChatSessionManager methods
    STDMETHODIMP GetSessionNames(IEnumString **ppes);
    STDMETHODIMP FindSession(const OLECHAR *pwszSessionName, 
                             BOOL bDontCreate,
                             BOOL bAllowAnonymousAccess,
                             IChatSession **ppcs);
    STDMETHODIMP DeleteSession(const OLECHAR *pwszSessionName);
};

// this class enumerates the session names of a server
class SessionNamesEnumerator : public IEnumString
{
    LONG                        m_cRef;
    vector<wstring>            *m_pStrings;
    SessionNamesEnumerator     *m_pCloneSource;
    vector<wstring>::iterator   m_cursor;
    CRITICAL_SECTION            m_csLock;
protected:
    vector<wstring>& Strings(void);
    void Lock(void);
    void Unlock(void);
    virtual ~SessionNamesEnumerator(void);
public:
    SessionNamesEnumerator(ChatSessionClass *pSessionClass);
    SessionNamesEnumerator(SessionNamesEnumerator *pCloneSource);

// IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    
// IEnumString methods
    STDMETHODIMP Next(ULONG cElems, OLECHAR **rgElems, 
                      ULONG *pcFetched);
    STDMETHODIMP Skip(ULONG cElems);
    STDMETHODIMP Reset(void);
    STDMETHODIMP Clone(IEnumString **ppes);
};

#endif
