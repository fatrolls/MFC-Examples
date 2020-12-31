/////////////////////////////////////////////////////////////////////////////
//
//                           Public Domain.
//
/////////////////////////////////////////////////////////////////////////////
//
//
//  File     :   KMAddIn.cpp
//
//  Author   :   Darren Richards
//
//  Date     :   25th February 98
//
//  Synopsis :   Implementation of KMAddIn object - where it all happens.
//
////////////////

/////////////////////////////////////////////////////////////////////////////
//
//  includes
//
///////////////

#include "stdafx.h"
#include "KbdMac.h"
#include "KMAddIn.h"

/////////////////////////////////////////////////////////////////////////////
//
//  locals
//
///////////////

static const int MAX_EVENTS = 500;         // maximum number of recorded events
static EVENTMSG s_rgsEvents[MAX_EVENTS];   // recorded events
static int      s_cEvents  = 0;            // number of events recorded
static int      s_iPlayPos = 0;            // playback position in events
static HHOOK    s_hhkJournal = NULL;       // journal hook handle

enum KMState
{
    KM_Stopped,
    KM_Recording,
    KM_Playing
} 
s_eKMState = KM_Stopped;                   // state of play

LRESULT CALLBACK JournalRecordProc(int code,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK JournalPlaybackProc(int code,WPARAM wParam,LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
//
//  CKMAddIn implementation
//
///////////////

STDMETHODIMP CKMAddIn::OnConnection(IApplication*   pApp,
                                    VARIANT_BOOL    bFirstTime,
                                    long            dwAddInID,
                                    VARIANT_BOOL*   bOnConnection)
{
	HRESULT hr       = S_OK;
	m_spApplication  = pApp;
	m_dwAddInID      = dwAddInID;

    try
    {
        //
        //  tell devstudio about our toolbar bitmaps
        //

	    hr = pApp->SetAddInInfo((long)_Module.GetModuleInstance(), 
		                        static_cast<IKMAddIn*>(this),
                                IDB_TOOLBAR_MEDIUM_KMADDIN,
                                IDB_TOOLBAR_LARGE_KMADDIN,
                                dwAddInID);

        if (FAILED(hr))
            throw hr;

        //
        //  add our commands to the devstudio
        //  

	    VARIANT_BOOL bRet;

        hr = pApp->AddCommand(CComBSTR(_T("KMRecord\nKMRecord\nRecord Keyboard Macro\nRecord Keyboard Macro")),
                              CComBSTR(_T("KMRecord")),
                              0,
                              dwAddInID,
                              &bRet);
        if (FAILED(hr))
            throw hr;

        hr = pApp->AddCommand(CComBSTR(_T("KMStop\nKMStop\nStop Playing/Recording Keyboard Macro\nStop Playing/Recording Keyboard Macro")),
                              CComBSTR(_T("KMStop")),
                              1,
                              dwAddInID,
                              &bRet);
        if (FAILED(hr))
            throw hr;

        hr = pApp->AddCommand(CComBSTR(_T("KMPlay\nKMPlay\nPlay Keyboard Macro\nPlay Keyboard Macro")),
                              CComBSTR(_T("KMPlay")),
                              2,
                              dwAddInID,
                              &bRet);
        if (FAILED(hr))
            throw hr;

        //
        //  add toolbar buttons if first time
        //

	    if (bFirstTime)
	    {
            hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(_T("KMRecord")), dwAddInID);

            if (FAILED(hr))
                throw hr;

            hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(_T("KMStop")), dwAddInID);

            if (FAILED(hr))
                throw hr;

            hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(_T("KMPlay")), dwAddInID);

            if (FAILED(hr))
                throw hr;
	    }
    }

    catch (HRESULT hrError)
    {
        hr = hrError;
    }

	*bOnConnection = SUCCEEDED(hr) ? VARIANT_TRUE :VARIANT_FALSE;

	return hr;
}

STDMETHODIMP CKMAddIn::OnDisconnection(VARIANT_BOOL bLastTime)
{
    //
    //  ensure recording or playback is stopped
    //

    KMStop();

	return S_OK;
}

STDMETHODIMP CKMAddIn::KMPlay()
{
    //
    //  ensure we are stopped first
    //

    KMStop();

    //
    //  clear state for Ctrl-Break so we can look out for it
    //

    GetAsyncKeyState(VK_CANCEL);

    //
    //  if we have some recorded events...
    //

    if (s_cEvents)
    {
        //
        //  ...play them back
        //

        s_eKMState = KM_Playing;
        s_iPlayPos = 0; 
        s_hhkJournal = SetWindowsHookEx(WH_JOURNALPLAYBACK,
                                        JournalPlaybackProc,
                                        GetModuleHandle(NULL),
                                        0);
    }
    
    else
    {
        //
        //  ...otherwise just whinge
        //

        MessageBeep((UINT)-1);
    }

	return S_OK;
}

STDMETHODIMP CKMAddIn::KMStop()
{
    //
    //  if we aren't currently stopped then unhook current journal hook
    //

    if (s_eKMState != KM_Stopped)
        UnhookWindowsHookEx(s_hhkJournal);

    s_eKMState = KM_Stopped;

	return S_OK;
}

STDMETHODIMP CKMAddIn::KMRecord()
{
    //
    //  ensure we are stopped first
    //

    KMStop();
    
    //
    //  clear down our event store
    //

    ZeroMemory(s_rgsEvents,sizeof(s_rgsEvents));
    s_cEvents = 0;

    //
    //  kick off recording
    //

    s_eKMState = KM_Recording;
    s_hhkJournal = SetWindowsHookEx(WH_JOURNALRECORD,
                                    JournalRecordProc,
                                    GetModuleHandle(NULL),
                                    0);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
//  Journal Hook Callbacks
//
///////////////

inline BOOL IsKbdEvent(EVENTMSG* pEvt)
{
    return (pEvt->message >= WM_KEYFIRST && pEvt->message <= WM_KEYLAST);
}

inline BOOL IsEventForUs(EVENTMSG* pEvt)
{
    DWORD dwProcess = 0;

    //
    //  work out where keyboard focus is
    //

    HWND hwndKbdFocus = GetFocus();
    
    //
    //  get the process owning this window
    //

    GetWindowThreadProcessId(GetFocus(), &dwProcess);

    //
    //  is it us ?
    //

    return dwProcess == GetCurrentProcessId();
}

LRESULT CALLBACK JournalRecordProc(int code,WPARAM wParam,LPARAM lParam)
{
    CallNextHookEx(s_hhkJournal, code, wParam, lParam);

    try
    {
        switch(code)
        {
        case HC_ACTION:

            //
            //  if we have sufficient space for another event...
            //

            if (s_cEvents < MAX_EVENTS)
            {
                EVENTMSG* pEvt = (EVENTMSG*)lParam;

                //
                //  ...then we check that it is a keyboard message for this
                //  instance of devstudio...
                //

                if (IsKbdEvent(pEvt) && IsEventForUs(pEvt))
                {
                    //
                    //  ...and if it is, stick the message in our buffer
                    //

                    s_rgsEvents[s_cEvents] = *pEvt;
                    s_cEvents++;
                }
            }

            //
            //  ...otherwise stop recording...
            //

            else
            {
                UnhookWindowsHookEx(s_hhkJournal);
                s_eKMState = KM_Stopped;
                MessageBeep((UINT)-1);
            }
            break;

        case HC_SYSMODALON:
        case HC_SYSMODALOFF:

            //
            //  we just give up if we see any system modal dialogs
            //  (they are generally bad)
            //

            UnhookWindowsHookEx(s_hhkJournal);
            s_eKMState = KM_Stopped;
            break;
        } // switch(code)
    } // try

    catch( ... )
    {
        UnhookWindowsHookEx(s_hhkJournal);
        s_eKMState = KM_Stopped;
    }

    return 0L;
}

LRESULT CALLBACK JournalPlaybackProc(int code,
                                     WPARAM wParam,
                                     LPARAM lParam )
{
    EVENTMSG* pEvt = NULL;

    LRESULT lResult = CallNextHookEx(s_hhkJournal, code, wParam, lParam);

    try 
    {
        switch(code)
        {
        case HC_GETNEXT:
            
            //
            //  return next event to played immediately
            //

            pEvt = (EVENTMSG*)lParam;
            *pEvt = s_rgsEvents[s_iPlayPos];
            pEvt->time = GetTickCount();
            lResult = 0;
            break;

        case HC_SKIP:
            
            //
            //  if Ctrl-Break has been hit or we're out of events, stop
            //

            if (GetAsyncKeyState(VK_CANCEL) || (s_iPlayPos++) == s_cEvents)
            {
                UnhookWindowsHookEx(s_hhkJournal);
                s_eKMState = KM_Stopped;
            }
            break;
        } // switch(code)
    } // try

    catch( ... )
    {
        UnhookWindowsHookEx(s_hhkJournal);
        s_eKMState = KM_Stopped;
    }

    return lResult;
}

