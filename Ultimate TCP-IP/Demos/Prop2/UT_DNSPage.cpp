// UT_DNSPage.cpp: implementation of the CUT_DNSPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UT_DNSPage.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996 )


#define HISTORY_BLACK		RGB(0,0,0)
#define HISTORY_BLUE		RGB(0,255,0)
#define HISTORY_RED 	RGB(255,0,0)
#define HISTORY_YELLOW RGB(220,255,220)
#define HISTORY_WHITE RGB(255,255,255)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// The constructor will use the Property page IDD_DNS_PAGE
// from the resource
CUT_DNSPage::CUT_DNSPage(LPTSTR title):CUCPage(IDD_DNS_PAGE,title)
{
	m_HistoryCtrl.SetTimeStampFormat(_T("%c"));

}

CUT_DNSPage::~CUT_DNSPage()
{
	
}

void CUT_DNSPage::OnInitDialog(WPARAM /* wParam */, LPARAM /* lParam */)
{
	
	
	/* HICON icon= */ LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_DNS));
	//attach the history window to the control
	m_HistoryCtrl.AttachHistoryWindow(m_hWnd,IDC_HISTORY_DNS);
	//set the maximum length of the buffer of this window
	m_HistoryCtrl.SetHistoryLength(500);
	// set the font for the history window
	m_hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
	m_HistoryCtrl.SetFont(m_hFont);
	
	
	// IDC_DNS_LOG_FILE
	// disable the file name window
	EnableWindow(GetDlgItem(m_hWnd,IDC_DNS_LOG_FILE),FALSE);
	
	m_bEnableLogChecked = FALSE;
	
	
	//setup the controls
	SetDlgItemText(m_hWnd, IDC_DNSSERVER,_T("A.ROOT-SERVERS.NET"));

    // default log file
	SetDlgItemText(m_hWnd, IDC_DNS_LOG_FILE,_T("session.txt"));
	
	//setup the controls
	SetDlgItemText(m_hWnd, IDC_LOOKUP,_T("Ultimate TCP/IP.com"));
	
	HWND hWndCombo = GetDlgItem(m_hWnd,IDC_QUERY_COMBO);
	// add a the query types as string to the combobox		
	//text strings
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_ALL (All records)"));
	//address
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_NS (name server)"));
	//name server
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_MD (mail destination (obs))"));
	//mail destination (obs)
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_MF (mail forwarder (obs))"));
	//mail forwarder (obs)
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_CNAME (canonical name)"));
	//canonical name
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_SOA (start of authority)"));
	//start of authority
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_MB (mailbox domain)"));
	//mailbox domain
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_MG (mail group)"));
	//mail group
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_MR (mail rename domain)"));
	//mail rename domain
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_NULL (NULL)"));
	//null 
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_WKS (well known service description)"));
	//well known service description
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_PTR (domain name pointer)"));
	//domain name pointer	
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_HINFO (host info)"));
	//host info
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_MINFO (mailbox or mail list info)"));
	//mailbox or mail list info
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_MX (mail exchange server)"));
	//mail server
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_TXT (text strings)"));
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_A (address)"));
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_AXFR (Zone Transfer)"));
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_MAILB"));
	SendMessage (hWndCombo,
		CB_ADDSTRING,
		0,
		(LONG)(ULONG_PTR)(LPSTR) _T("CUT_DNS_MAILA"));
	
	SendMessage (hWndCombo,
		CB_SETCURSEL,
		0,
		0);
	//IDC_USE_TCP
	m_bUseUDP = FALSE;
	m_hThread = NULL;

	
	
	
}

int CUT_DNSPage::SelectedQuery(int index)
{
	
	// Return the Query type based on the passed index from the 
	// ComboBox
	int nQueryType  = 0;
	switch (index)
	{
	case 0:
		{
			nQueryType = CUT_DNS_ALL;
			break;
			
		}
	case 1:
		{
			nQueryType = CUT_DNS_NS; 		//name server
			break;
		}
	case 2:
		{
			nQueryType = CUT_DNS_MD; 		//mail destination (obs)
			break;
		}
	case 3:
		{
			nQueryType = CUT_DNS_MF; 		//mail forwarder (obs)
			break;
		}
	case 4:
		{
			nQueryType = CUT_DNS_CNAME;	//canonical name
			break;
		}
	case 5:
		{
			nQueryType = CUT_DNS_SOA;		//start of authority
			break;
		}
	case 6:
		{
			nQueryType = CUT_DNS_MB; 		//mailbox domain
			break;
		}
	case 7:
		{
			nQueryType = CUT_DNS_MG; 		//mail group
			break;
		}
	case 8:
		{
			nQueryType = CUT_DNS_MR; 		//mail rename domain
			break;
		}
	case 9:
		{
			nQueryType = CUT_DNS_NULL;		//null 
			break;
		}
	case 10:
		{
			nQueryType = CUT_DNS_WKS;		//well known service description
			break;
		}
	case 11:
		{
			nQueryType = CUT_DNS_PTR;		//domain name pointer	
			break;
		}
	case 12:
		{
			nQueryType = CUT_DNS_HINFO;	//host info
			break;
		}
	case 13:
		{
			nQueryType = CUT_DNS_MINFO;	//mailbox or mail list info
			break;
		}
	case 14:
		{
			nQueryType = CUT_DNS_MX; 		//mail server
			break;
			
		}
	case 15:
		{
			nQueryType = CUT_DNS_TXT;		//text strings
			break;
		}
	case 16:
		{
			nQueryType = CUT_DNS_A;			//address
			break;
			
		}
	case 17:
		{
			nQueryType = CUT_DNS_AXFR;
			break;
		}
	case 18:
		{
			nQueryType = CUT_DNS_MAILA;
			break;
		}
	case 19:
		{
			nQueryType = CUT_DNS_MAILB;
			break;
		}
	default:
		nQueryType = CUT_DNS_ALL;
	}
	
	return nQueryType;
}

void CUT_DNSPage::OnCommand(WPARAM /* wParam */,LPARAM /* lParam */)
{
	
	
}
void CUT_DNSPage::OnSelChange(int /* item */ ,HWND)
{
	
}


void CUT_DNSPage::OnHelp(LPARAM lParam){

   
HELPINFO hInfo = *((LPHELPINFO) lParam);    

		::WinHelp((HWND)hInfo.hItemHandle, _T("DSITools.hlp"),
		   HELP_WM_HELP, (DWORD)(ULONG_PTR)(LPVOID)dwDNSHelpMap);


}


void CUT_DNSPage::OnClicked(int controlId)
{
	switch(controlId)
	{
	case  IDC_USE_TCP:
		{	// the user checked or unchecked the UseUDP check box
			if (m_bUseUDP)
				m_bUseUDP = FALSE;
			else
				m_bUseUDP = TRUE;					
			return ;
		}
    case IDC_DNS_ABOUT:
        {
		::WinHelp(m_hWnd, _T("DSITools.hlp"),
		   HELP_CONTENTS,0);
        return;
        }

	case IDC_DNS_ENABLE_LOG:
		{
			
			if (m_bEnableLogChecked)
			{
				m_bEnableLogChecked = FALSE;
					// just disable the log
				m_HistoryCtrl.EnableLog (m_bEnableLogChecked);
			}
			else
				m_bEnableLogChecked = TRUE;

			
			EnableWindow(GetDlgItem(m_hWnd,IDC_DNS_LOG_FILE),m_bEnableLogChecked);
			
			break;
		}
		
				case IDC_AUTHLOOKUPBTN:
					{
					if (m_hThread == NULL)
					{
						
						// call the thread from here 
						//8888888888888888888888888888888
							// Create a new thread
						SetDlgItemText(m_hWnd ,IDC_AUTHLOOKUPBTN,_T("&Stop"));
						EnableWindow(GetDlgItem(m_hWnd , IDC_LOOKUPBTN),FALSE);

						m_hThread = (HANDLE) _beginthread((void (__cdecl *)(void *))AuthLookUpThread,NULL,	reinterpret_cast<void*>(this));
					}
					else
					{
						// terminate the thread 
						DWORD dwExitCode = 0;
						if (m_hThread != NULL){
							WaitForSingleObject(m_hThread,200);
							TerminateThread(m_hThread,dwExitCode);
							CloseHandle(m_hThread);
							m_hThread = NULL;
					}
						SetDlgItemText(m_hWnd ,IDC_LOOKUPBTN,_T("&Lookup"));
						EnableWindow(GetDlgItem(m_hWnd , IDC_LOOKUPBTN),TRUE);
						SetDlgItemText(m_hWnd ,IDC_AUTHLOOKUPBTN,_T("Auth. Loo&kup"));
						EnableWindow(GetDlgItem(m_hWnd , IDC_AUTHLOOKUPBTN),TRUE);

						
					}

						return ;
					}
				case IDC_LOOKUPBTN:{
					
					if (m_hThread == NULL)
					{					
						// call the thread from here 
						//8888888888888888888888888888888
							// Create a new thread
						SetDlgItemText(m_hWnd ,IDC_LOOKUPBTN,_T("&Stop"));
						EnableWindow(GetDlgItem(m_hWnd , IDC_AUTHLOOKUPBTN),FALSE);

						m_hThread = (HANDLE) _beginthread((void (__cdecl *)(void *))LookUpThread,NULL,	reinterpret_cast<void*>(this));
					}
					else
					{
						// terminate the thread 
						DWORD dwExitCode = 0;
						if (m_hThread != NULL){
							WaitForSingleObject(m_hThread,200);
							TerminateThread(m_hThread,dwExitCode);
							CloseHandle(m_hThread);
							m_hThread = NULL;
						}
						SetDlgItemText(m_hWnd ,IDC_LOOKUPBTN,_T("&Lookup"));
						EnableWindow(GetDlgItem(m_hWnd , IDC_LOOKUPBTN),TRUE);
						SetDlgItemText(m_hWnd ,IDC_AUTHLOOKUPBTN,_T("Auth. Loo&kup"));
						EnableWindow(GetDlgItem(m_hWnd , IDC_AUTHLOOKUPBTN),TRUE);


						
					}
					return ;
								   }
	}
	
	
	
}


void CUT_DNSPage::DisplayEntries(CUT_DNSClient &dns)
{
	// lets start from the begining
	dns.ResetEnumerations();
	CUT_DNSEntry entry;
	_TCHAR buf1[MAX_PATH], buf2[MAX_PATH];
	
	//display the results
	int count = 0;
	BOOL white = TRUE;
	COLORREF backColor, textColor= HISTORY_BLACK;
	while(dns.EnumDNSEntry(&entry) == CUT_SUCCESS){
		
		if (white )
		{
			backColor = HISTORY_WHITE ;
			white = FALSE;
		}else
		{
			backColor = HISTORY_YELLOW;
			
			white = TRUE;
		}
		// v4.2 CUT_DNSEntry has _TCHAR strings
		m_HistoryCtrl.AddLine("***********************************************",textColor,backColor);
		_sntprintf(buf1, MAX_PATH-1,_T("Entry Number (%d) Host: \"%s\""),count++,entry.szHost);
		m_HistoryCtrl.AddLine(buf1,textColor,backColor);
		_sntprintf(buf1, MAX_PATH-1,_T("Description: %s"),dns.GetLongName(entry.nType));
		m_HistoryCtrl.AddLine(buf1,textColor,backColor);
	
       	_sntprintf(buf2, MAX_PATH-1,_T("Time To live  (%lu)"), entry.lTTL);
		m_HistoryCtrl.AddLine(buf2,textColor,backColor);

        if (entry.nType == 6) {
            
            _sntprintf(buf2, MAX_PATH-1,_T("SOA: Serial: %lu  Refresh: %lu  Retry: %lu  Expire: %lu  Minimum: %lu"),
                entry.lTTL,
                entry.lSOA_Serial,
                entry.lSOA_Refresh,
                entry.lSOA_Retry,
                entry.lSOA_Expire,
                entry.lSOA_Minimum);
            
            m_HistoryCtrl.AddLine(buf2,textColor,backColor);
        }
		// v4.2 CUT_DNSEntry has _TCHAR strings
		 _sntprintf(buf2, MAX_PATH-1,_T("Data: \"%s\""),entry.szData);
		 m_HistoryCtrl.AddLine(buf2,textColor,backColor);
         if(entry.szData2[0] != '\0') {
		    _sntprintf(buf2, MAX_PATH-1,_T("Data2: \"%s\""),entry.szData2);
		    m_HistoryCtrl.AddLine(buf2,textColor,backColor);
         }
         if(entry.nType == 15) {
		    _sntprintf(buf2, MAX_PATH-1,_T("Mx Prefrence: (%u)"),entry.nMX_Preference);
		    m_HistoryCtrl.AddLine(buf2,textColor,backColor);
         }
	}
}

unsigned __stdcall CUT_DNSPage::LookUpThread(void * pThis){
    
    // pointer to the page class since we are inside a static function
    CUT_DNSPage*		pThisObject = static_cast<CUT_DNSPage*>(pThis );

    // pointer to the page class since we are inside a static function
    HWND hWndCombo = GetDlgItem(pThisObject->m_hWnd,IDC_QUERY_COMBO);

    //get the name server and domain name to lookup
    _TCHAR szNameServer[256];
    GetDlgItemText(pThisObject->m_hWnd,IDC_DNSSERVER,szNameServer,256);
    
    
    if (pThisObject->m_bEnableLogChecked)
    {
		_TCHAR	szLogFileName[MAX_PATH];
        // get the name of the file to log to
        GetDlgItemText(pThisObject->m_hWnd,IDC_DNS_LOG_FILE,szLogFileName,MAX_PATH-1);
        if (_tcslen(szLogFileName) <1)
        {
            int iAnswer = IDOK;
            iAnswer = MessageBox(pThisObject->m_hWnd,_T("Log file name is not present, Continue without logging?"),_T("Verify"),MB_OKCANCEL);
            if (iAnswer != IDOK   )
            {
                // reste the thread indicator
                pThisObject->m_hThread = NULL;
                return 0 ;
            }
        }
        else
        {
            // set up the log file if needed
            pThisObject->m_HistoryCtrl.SetLogName (szLogFileName);
            pThisObject->m_HistoryCtrl.EnableLog (pThisObject->m_bEnableLogChecked);
        }
    }
    
    _TCHAR lookUp[256];

    GetDlgItemText(pThisObject->m_hWnd,IDC_LOOKUP,lookUp,256);
    //clear the history window
    pThisObject->m_HistoryCtrl.ClearHistory();
    
    //check the input strings
    if(szNameServer[0] ==0){
        pThisObject->m_HistoryCtrl.AddLine(_T("No Name Server Was Specified"));
        // reste the thread indicator
        pThisObject->m_hThread = NULL;
        return 0 ;
        
    }
    if(lookUp[0] ==0){
        pThisObject->m_HistoryCtrl.AddLine(_T("No Name Was Entered To Lookup"));
        // reset the thread indicator
        CloseHandle(pThisObject->m_hThread);
        pThisObject->m_hThread = NULL;
        return 0 ;
    }
    
    _TCHAR szDisplayString[MAX_PATH];
    _sntprintf(szDisplayString, MAX_PATH-1,_T("DNS lookup (non-Authorized) for %s:"), lookUp);
    pThisObject->m_HistoryCtrl.AddStampedLine("");
    pThisObject->m_HistoryCtrl.AddLine(szDisplayString);
    pThisObject->m_HistoryCtrl.AddLine("");
    
    CUT_DNSClient *dns = new CUT_DNSClient ;
    
    int wIndex = (WORD) SendMessage (hWndCombo, CB_GETCURSEL, 0, 0L);
    // lets see what query is the user interested in
    int nQueryType  = pThisObject->SelectedQuery(wIndex);
    //set the cursor to an hourglass
    dns->SetUseUDP (pThisObject->m_bUseUDP);
    int res = dns->LookupName  (szNameServer,lookUp,nQueryType );
    if(res == UTE_SUCCESS)
        pThisObject->DisplayEntries(*dns);
    
    pThisObject->m_HistoryCtrl.AddLine(_T(""));
    pThisObject->m_HistoryCtrl.AddLine(CUT_ERR::GetErrorString(res));
    pThisObject->m_HistoryCtrl.AddLine(_T("-----------------------------"));
    pThisObject->m_HistoryCtrl.AddLine(_T(" "));
				
    //set the buttons back							
    SetDlgItemText(pThisObject->m_hWnd ,IDC_LOOKUPBTN,_T("&Lookup"));
    EnableWindow(GetDlgItem(pThisObject->m_hWnd , IDC_LOOKUPBTN),TRUE);
    SetDlgItemText(pThisObject->m_hWnd ,IDC_AUTHLOOKUPBTN,_T("Auth. Loo&kup"));
    EnableWindow(GetDlgItem(pThisObject->m_hWnd , IDC_AUTHLOOKUPBTN),TRUE);
    
    pThisObject->m_hThread = NULL;
    delete dns;						
    return 0;
    
}

unsigned __stdcall CUT_DNSPage::AuthLookUpThread(void * pThis){
    
    // pointer to the page class since we are inside a static function
    CUT_DNSPage*		pThisObject = static_cast<CUT_DNSPage*>(pThis );

    HWND hWndCombo = GetDlgItem(pThisObject->m_hWnd,IDC_QUERY_COMBO);

    //get the name server and domain name to lookup
    _TCHAR szNameServer[256];
    GetDlgItemText(pThisObject->m_hWnd,IDC_DNSSERVER,szNameServer,256);
    
    
    if (pThisObject->m_bEnableLogChecked)
    {
		_TCHAR	szLogFileName[MAX_PATH];
        // get the name of the file to log to
        GetDlgItemText(pThisObject->m_hWnd,IDC_DNS_LOG_FILE,szLogFileName,MAX_PATH-1);
        if (_tcslen(szLogFileName) <1)
        {
            int iAnswer = IDOK;
            iAnswer = MessageBox(pThisObject->m_hWnd,_T("Log file name is not present, Continue without logging?"),_T("Verify"),MB_OKCANCEL);
            if (iAnswer != IDOK   )
            {
                // reste the thread indicator
                pThisObject->m_hThread = NULL;
                return 0 ;
            }
        }
        else
        {
            // set up the log file if needed
            pThisObject->m_HistoryCtrl.SetLogName (szLogFileName);
            pThisObject->m_HistoryCtrl.EnableLog (pThisObject->m_bEnableLogChecked);
        }
    }
    
 	_TCHAR lookUp[256];

    GetDlgItemText(pThisObject->m_hWnd,IDC_LOOKUP,lookUp,256);
    //clear the history window
    pThisObject->m_HistoryCtrl.ClearHistory();
    
    //check the input strings
    if(szNameServer[0] ==0){
        pThisObject->m_HistoryCtrl.AddLine(_T("No Name Server Was Specified"));
        // reste the thread indicator
        pThisObject->m_hThread = NULL;
        return 0 ;
        
    }
    if(lookUp[0] ==0){
        pThisObject->m_HistoryCtrl.AddLine(_T("No Name Was Entered To Lookup"));
        // reste the thread indicator
        pThisObject->m_hThread = NULL;
        return 0 ;
    }
    
    
    _TCHAR szDisplayString[MAX_PATH];
    _sntprintf(szDisplayString, MAX_PATH-1, _T("DNS lookup (Authorized) for %s:"), lookUp);
    pThisObject->m_HistoryCtrl.AddStampedLine(_T(""));
    pThisObject->m_HistoryCtrl.AddLine(szDisplayString);
    pThisObject->m_HistoryCtrl.AddLine(_T(""));
    
    CUT_DNSClient *dns = new CUT_DNSClient ;
    
    int wIndex = (WORD) SendMessage (hWndCombo, CB_GETCURSEL, 0, 0L);

    // lets see what query is the user interested in
    int nQueryType  = pThisObject->SelectedQuery(wIndex);

    //set the cursor to an hourglass
    dns->SetUseUDP (pThisObject->m_bUseUDP);
    int res = dns->AuthoritativeLookup (szNameServer,lookUp,nQueryType );
    if(res == UTE_SUCCESS)
        pThisObject->DisplayEntries(*dns);
    
    pThisObject->m_HistoryCtrl.AddLine(_T(" "));
    pThisObject->m_HistoryCtrl.AddLine(CUT_ERR::GetErrorString(res));
    pThisObject->m_HistoryCtrl.AddLine(_T("-----------------------------"));
    pThisObject->m_HistoryCtrl.AddLine(_T(" "));
    
    //set the buttons back							
    SetDlgItemText(pThisObject->m_hWnd ,IDC_LOOKUPBTN,_T("&Lookup"));
    EnableWindow(GetDlgItem(pThisObject->m_hWnd , IDC_LOOKUPBTN),TRUE);
    SetDlgItemText(pThisObject->m_hWnd ,IDC_AUTHLOOKUPBTN,_T("Auth. Loo&kup"));
    EnableWindow(GetDlgItem(pThisObject->m_hWnd , IDC_AUTHLOOKUPBTN),TRUE);
    
    pThisObject->m_hThread = NULL;
    delete dns;
    
    
    
    return 0;
    
}

#pragma warning ( pop )