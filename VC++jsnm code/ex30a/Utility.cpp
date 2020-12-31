// utility.cpp -- contains stuff used by more than one thread
#include <stdafx.h>
#include "blocksock.h"
#include "utility.h"

volatile int g_nConnection = 0; // connection number
CString g_strServerName = "localhost"; // used by both winsock and wininet
CString g_strServerIP;
volatile UINT g_nPort = 80;
CString g_strFile = "/custom";

CCallbackInternetSession::CCallbackInternetSession( LPCTSTR pstrAgent, DWORD dwContext,
	 DWORD dwAccessType, LPCTSTR pstrProxyName, LPCTSTR pstrProxyBypass, DWORD dwFlags) :
	CInternetSession(pstrAgent, dwContext, dwAccessType, pstrProxyName, pstrProxyBypass, dwFlags)
{
	EnableStatusCallback();
}

void CCallbackInternetSession::OnStatusCallback(DWORD dwContext, DWORD dwInternalStatus,
		LPVOID lpvStatusInformation, DWORD dwStatusInformationLength)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int errors[] = {10, 11, 20, 21, 30, 31, 40, 41, 42, 43, 50, 51, 60, 70, 100, 110, 0};
	char* text[] = { 
		"Resolving name",       	
		"Name resolved",       
		"Connecting to server",
		"Connected to server",  
		"Sending request",      
		"Request sent",         
		"Receiving response",   
		"Response received",    
		"Ctl response received",
		"Prefetch",             
		"Closing connection",   
		"Connection closed",    
		"Handle created",       
		"Handle closing",       
		"Request complete",     
		"Redirect",
		"Unknown" };
	int n;
/*  // demonstrates request cancellation 
	if(dwInternalStatus == INTERNET_STATUS_REQUEST_SENT) {
		AfxThrowInternetException(dwContext, 999);
	}
*/
	for(n = 0; errors[n] != 0; n++) {
		if(errors[n] == (int) dwInternalStatus) break;
	}
	g_csStatus.Lock();
	  strcpy(g_pchStatus, text[n]);
	  if(dwInternalStatus  == INTERNET_STATUS_RESOLVING_NAME || 
				dwInternalStatus == INTERNET_STATUS_NAME_RESOLVED) {
		strcat(g_pchStatus, "-");
		strcat(g_pchStatus, (char*) lpvStatusInformation);
	  }
	  TRACE("WININET STATUS: %s\n", g_pchStatus);
	g_csStatus.Unlock();
	// frame doesn't need a handler -- message triggers OnIdle, which updates status bar
	::PostMessage(g_hMainWnd, WM_CALLBACK, 0, 0);
}

void LogInternetException(LPVOID pParam, CInternetException* pe)
{	// pParam holds the HWND for the destination window (in another thread)
	CString strGmt = CTime::GetCurrentTime().FormatGmt("%m/%d/%y %H:%M:% GMT");
	char text1[300], text2[100];
	wsprintf(text1, "CLIENT ERROR: WinInet error #%d -- %s\r\n   ",
		pe->m_dwError, (const char*) strGmt);
	pe->GetErrorMessage(text2, 99);
	strcat(text1, text2);
	if(pe->m_dwError == 12152) {
		strcat(text1, "  URL not found?\r\n");
	}
	::SendMessage((HWND) pParam, EM_SETSEL, (WPARAM) 65534, 65535);
	::SendMessage((HWND) pParam, EM_REPLACESEL, (WPARAM) 0, (LPARAM) text1);
}

