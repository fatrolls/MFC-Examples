// UT_PingPage.cpp: implementation of the CUT_PingPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UT_PingPage.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996 )


#define HISTORY_YELLOW RGB(220,255,220)
#define HISTORY_BLACK		RGB(0,0,0)
#define HISTORY_WHITE RGB(255,255,255)


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void myPing::OnReceiveICMP()
{
    
    if(!GetResponseSequence())
        m_nAggResp = m_nAvgResp = m_nCount = 0;

    _TCHAR szBuffer[MAX_PATH];
	_TCHAR szTemp[MAX_PATH];
	size_t size;

    _sntprintf(szBuffer, sizeof(szBuffer), _T("%d.\t%ums. \t\"%s\""),
        GetResponseSequence()
        ,GetResponseDuration() 
        ,GetResponseMessage()
        );
        m_parent->m_HistoryCtrl.AddLine (szBuffer,m_rfTextColor,m_rfBackColor);
        if(255 != GetResponseType()) {
            _sntprintf(szBuffer, sizeof(szBuffer), _T("\t\tRes. Type:(%d)\tRes. Code:(%d)"),
                GetResponseType() 
                ,GetResponseCode());
            m_parent->m_HistoryCtrl.AddLine (szBuffer,m_rfTextColor,m_rfBackColor);

			*szTemp = _T('\0');
			size = 0;
			GetResponseAddress(szTemp, MAX_PATH, &size);
            _sntprintf(szBuffer, sizeof(szBuffer), _T("\t\tFrom:\"%s\""), szTemp);
            m_parent->m_HistoryCtrl.AddLine (szBuffer,m_rfTextColor,m_rfBackColor);
            if(GetDoLookup()) {
				*szTemp = _T('\0');
				size = 0;
				GetResponseName(szTemp, MAX_PATH, &size);
                _sntprintf(szBuffer, sizeof(szBuffer), _T("\t\tName: %s"), szTemp);
                m_parent->m_HistoryCtrl.AddLine (szBuffer,m_rfTextColor,m_rfBackColor);
            }
            m_nAggResp += GetResponseDuration();
            ++m_nCount;
        }
        
    
    // switch the back color on and off
    if (m_rfBackColor == HISTORY_WHITE)
        m_rfBackColor = HISTORY_YELLOW;
    else
        m_rfBackColor = HISTORY_WHITE;
    
    
}

myPing::myPing(){
    m_parent = NULL;
    m_rfTextColor = HISTORY_BLACK;
    m_rfBackColor = HISTORY_WHITE ;
    m_nCount = 0;
    m_nAvgResp = 0;
    m_nAggResp = 0;
    
}
myPing::~myPing(){
}



BOOL myPing::IsAborted() {
    return m_parent->m_bAbort;
}

int myPing::GetAvgResponse() {
    if(m_nCount)
        return m_nAggResp / m_nCount;
    else 
        return 0;
}




CUT_PingPage::CUT_PingPage(LPTSTR title):CUCPage(IDD_PING_PAGE2,title)
{
    m_hThread = NULL;
	m_HistoryCtrl.SetTimeStampFormat(_T("%c"));

}

CUT_PingPage::~CUT_PingPage()
{
    
}



void CUT_PingPage::OnInitDialog(WPARAM /* wParam */, LPARAM /* lParam */)
{
    
    //attach the history window to the control
    m_HistoryCtrl.AttachHistoryWindow(m_hWnd,IDC_PING_HISTORY);
    //set the maximum length of the buffer of this window
    m_HistoryCtrl.SetHistoryLength(500);
    // set the font for the history window
    m_hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
    m_HistoryCtrl.SetFont(m_hFont);
    
    //setup the controls
    SetDlgItemText(m_hWnd, IDC_PING_NDOMAIN,_T("Ultimate TCP/IP.com"));
    m_bEnableLogChecked = FALSE;
    m_bAbort = FALSE;
    m_bShowName = FALSE;
    EnableWindow(GetDlgItem(m_hWnd,IDC_PING_LOG_FILE),m_bEnableLogChecked);
    
    // default log file
	SetDlgItemText(m_hWnd, IDC_PING_LOG_FILE,_T("session.txt"));
    
    SetDlgItemText(m_hWnd, IDC_PING_TIME_OUT,_T("5000"));
    SetDlgItemText(m_hWnd, IDC_PING_DATA_SIZE,_T("32"));
    SetDlgItemText(m_hWnd, IDC_PING_INTERVALS,_T("500"));
    SetDlgItemText(m_hWnd, IDC_PING_NUMBER_HITS,_T("20"));
    SetDlgItemText(m_hWnd, IDC_PING_NUMBER_TIMEOUTS,_T("8"));
    
}


void CUT_PingPage::OnHelp(LPARAM lParam){

   
HELPINFO hInfo = *((LPHELPINFO) lParam);    

		::WinHelp((HWND)hInfo.hItemHandle, _T("DSITools.hlp"),
		   HELP_WM_HELP, (DWORD)(ULONG_PTR)(LPVOID)dwPingHelpMap);


}

void CUT_PingPage::OnClicked(int controlId)
{
    switch (controlId)
    {
    case IDC_PING_ABOUT:
        {
		::WinHelp(m_hWnd, _T("DSITools.hlp"),
		   HELP_CONTENTS,0);
        return;
        }

    case IDC_PING_SHOW_NAME:
        {
            if (m_bShowName )
                m_bShowName = FALSE;
            else
                m_bShowName = TRUE;
            
            break;
        }
        
    case IDC_PING_ENABLE_LOG:
        {
            if (m_bEnableLogChecked)
            {
                m_bEnableLogChecked = FALSE;
                // just disable the log
                m_HistoryCtrl.EnableLog (m_bEnableLogChecked);
            }
            else
                m_bEnableLogChecked = TRUE;
            
            
            EnableWindow(GetDlgItem(m_hWnd,IDC_PING_LOG_FILE),m_bEnableLogChecked);
            
            break;
            
        }
    case IDC_PING_BTN:
        {			
            if (m_hThread == NULL)
            {
                
                m_bAbort = FALSE;
                if (m_bEnableLogChecked)
                {
                    _TCHAR	szLogFileName[MAX_PATH];
                    // get the name of the file to log to
                    GetDlgItemText(m_hWnd,IDC_PING_LOG_FILE,szLogFileName,MAX_PATH-1);
                    if (_tcslen(szLogFileName) <1)
                    {
                        int iAnswer = IDOK;
                        iAnswer = MessageBox(m_hWnd,_T("Log file name is not present, Continue without logging?"),_T("Verify"),MB_OKCANCEL);
                        if (iAnswer != IDOK   )
                            return;
                    }
                    else
                    {
                        // set up the log file if needed
                        m_HistoryCtrl.SetLogName (szLogFileName);
                        m_HistoryCtrl.EnableLog (m_bEnableLogChecked);
                    }
                }
                // Create a new thread
                SetDlgItemText(m_hWnd ,IDC_PING_BTN,_T("&Stop"));
                m_hThread = (HANDLE) _beginthread((void (__cdecl *)(void *))PingThread,NULL,	reinterpret_cast<void*>(this));
            }
            else
            {
                m_bAbort = TRUE;
            }
            break;
        }		
    }
}



unsigned __stdcall CUT_PingPage::PingThread(void * pThis){
    
    // pointer to the page class since we are inside a static function
    CUT_PingPage*		pThisObject = static_cast<CUT_PingPage*>(pThis );
    
    
    
    // the target domain
    _TCHAR				szDomain[MAX_PATH];
    _TCHAR              szDisplayString[MAX_PATH];

    // our one and only ping client
    myPing				pingClient;
    
    // the time to wait until the echo reply is considered time out
    int					nTimeOut = 5000;
    BOOL				bTranslated = TRUE;
    // get the time to wait until the echo reply is considered time out
    nTimeOut = GetDlgItemInt(pThisObject->m_hWnd ,IDC_PING_TIME_OUT,&bTranslated,FALSE);
    
    
    
    // the size of data to be sent with the ping packet
    int					nDataSize = 64;
    // get the  size of data to be sent with the ping packet
    nDataSize = GetDlgItemInt(pThisObject->m_hWnd ,IDC_PING_DATA_SIZE,&bTranslated,FALSE);
    
    
    // interval between each ping attempt
    int					nIntervalMS = 5000;
    // get the  size of data to be sent with the ping packet
    nIntervalMS = GetDlgItemInt(pThisObject->m_hWnd ,IDC_PING_INTERVALS,&bTranslated,FALSE);
    
    // number of pings to attempt
    int					nPacketsCounts = 30; //IDC_PING_NUMBER_HITS
    // get the  size of data to be sent with the ping packet
    nPacketsCounts = GetDlgItemInt(pThisObject->m_hWnd ,IDC_PING_NUMBER_HITS,&bTranslated,FALSE);
    
    
    int					nMaxTimeOuts = 6; //IDC_PING_NUMBER_TIMEOUTS
    // get the  size of data to be sent with the ping packet
    nMaxTimeOuts = GetDlgItemInt(pThisObject->m_hWnd ,IDC_PING_NUMBER_TIMEOUTS,&bTranslated,FALSE);
    
    
    
    // set the delegated class as the Pingpage class so we can access its memebers from our ping
    // Some Programming schools may disagree with this approeach since it breaks encapsulation of OO
    // However, to satisfy them when can add Getters and Setters functions latter on
    pingClient.m_parent = pThisObject;
    
    // get the Domain to be pinged
    GetDlgItemText(pThisObject->m_hWnd ,IDC_PING_NDOMAIN,szDomain,MAX_PATH-1);
    
    // Clear the history control
    pThisObject->m_HistoryCtrl.ClearHistory ();
    
    // does the user wants to see the name of the address replying?
    pingClient.SetDoLookup (pThisObject->m_bShowName);
    
    
    // maximum number of time outs
    pingClient.SetMaxTimeOuts(nMaxTimeOuts);
    
    _sntprintf(szDisplayString, MAX_PATH-1, _T("Pinging: %s with %d bytes of data"), szDomain, nDataSize);
    pThisObject->m_HistoryCtrl.AddStampedLine(_T(" ") );
    pThisObject->m_HistoryCtrl.AddLine(szDisplayString);
    pThisObject->m_HistoryCtrl.AddLine(_T(" ") );
    
    // perform the ping opertation
	// v4.2 Ping can take wide char
    int res = pingClient.Ping( szDomain , nTimeOut , nDataSize , nIntervalMS , (unsigned short)nPacketsCounts);
    if (res == UTE_SOCK_CREATE_FAILED)
        MessageBox(pThisObject->m_hWnd,_T("Ping and TraceRoute require the ability to create Raw Sockets.\nYou must be logged in with Adminitrators privileges to enable this."),_T("Verify"),MB_OK);

    // output result text to history control
    pThisObject->m_HistoryCtrl.AddLine(" ");
    pThisObject->m_HistoryCtrl.AddLine(CUT_ERR::GetErrorString(res));
    pThisObject->m_HistoryCtrl.AddLine(" ");

    if(res == UTE_SUCCESS) {
        _sntprintf(szDisplayString, sizeof(szDisplayString),_T("Average response time: %dms"), pingClient.GetAvgResponse());
        pThisObject->m_HistoryCtrl.AddLine(szDisplayString);
        pThisObject->m_HistoryCtrl.AddLine(_T("-----------------------------"));
        pThisObject->m_HistoryCtrl.AddLine(_T(" "));
    }

    // set the button back to Ping
    SetDlgItemText(pThisObject->m_hWnd ,IDC_PING_BTN,_T("&Ping"));
    
    // reste the thread indicator
    pThisObject->m_hThread = NULL;
    return 1;
}

#pragma warning ( pop )