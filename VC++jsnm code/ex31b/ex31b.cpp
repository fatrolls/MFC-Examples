// EX31B.CPP - Implementation file for your Internet Server
//    ex31b Filter

#include "stdafx.h"
#include "ex31b.h"

#define WM_SENDTEXT WM_USER + 5

///////////////////////////////////////////////////////////////////////
// The one and only CWinApp object
// NOTE: You may remove this object if you alter your project to no
// longer use MFC in a DLL.

CWinApp theApp;



///////////////////////////////////////////////////////////////////////
// The one and only CEx31bFilter object

CEx31bFilter theFilter;


///////////////////////////////////////////////////////////////////////
// CEx31bFilter implementation

CEx31bFilter::CEx31bFilter()
{
}

CEx31bFilter::~CEx31bFilter()
{
}

BOOL CEx31bFilter::GetFilterVersion(PHTTP_FILTER_VERSION pVer)
{
	// Call default implementation for initialization
	CHttpFilter::GetFilterVersion(pVer);

	// Clear the flags set by base class
	pVer->dwFlags &= ~SF_NOTIFY_ORDER_MASK;

	// Set the flags we are interested in
	pVer->dwFlags |= SF_NOTIFY_ORDER_LOW | SF_NOTIFY_SECURE_PORT | SF_NOTIFY_NONSECURE_PORT
			 | SF_NOTIFY_READ_RAW_DATA;
	// Load description string
	TCHAR sz[SF_MAX_FILTER_DESC_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_FILTER, sz, SF_MAX_FILTER_DESC_LEN));
	_tcscpy(pVer->lpszFilterDesc, sz);
	// m_hWndDest, m_hProcessDest used by SendTextToWindow
	m_hProcessDest = NULL;
	if((m_hWndDest = ::FindWindow(NULL, "ex31b")) != NULL) {
		DWORD dwProcessId;
		GetWindowThreadProcessId(m_hWndDest, &dwProcessId);
		m_hProcessDest = OpenProcess(PROCESS_DUP_HANDLE, FALSE, 
			dwProcessId);
		SendTextToWindow("EX31B filter started\r\n");
	}
	return TRUE;
}

DWORD CEx31bFilter::OnReadRawData(CHttpFilterContext* pCtxt,
	PHTTP_FILTER_RAW_DATA pRawData)
{
	TRACE("CEx31bFilter::OnReadRawData\n");
	// sends time/date, from IP, to IP, request data to a window
	char pchVar[50] = "";
	char pchOut[2000];
	DWORD dwSize = 50;
	BOOL bRet;
	CString strGmt = CTime::GetCurrentTime().FormatGmt("%m/%d/%y %H:%M:%S \
		GMT");
	strcpy(pchOut, strGmt);
	bRet = pCtxt->GetServerVariable("REMOTE_ADDR", pchVar, &dwSize);
	if(bRet && dwSize > 1) {
		strcat(pchOut, ", From ");
		strcat(pchOut, pchVar);
	}
	bRet = pCtxt->GetServerVariable("SERVER_NAME", pchVar, &dwSize);
	if(bRet && dwSize > 1) {
		strcat(pchOut, ", To ");
		strcat(pchOut, pchVar);
	}
	strcat(pchOut, "\r\n");
	int nLength = strlen(pchOut);
	// Raw data is not zero-terminated
	strncat(pchOut, (const char*) pRawData->pvInData, pRawData->cbInData);
	nLength += pRawData->cbInData;
	pchOut[nLength] = '\0';
	SendTextToWindow(pchOut);
	return SF_STATUS_REQ_NEXT_NOTIFICATION;
}

void CEx31bFilter::SendTextToWindow(char* pchData)
{
	if(m_hProcessDest != NULL) {
		int nSize = strlen(pchData) + 1;
		HANDLE hMMFReceiver;
		HANDLE hMMF = ::CreateFileMapping((HANDLE) 0xFFFFFFFF, NULL, 
			PAGE_READWRITE, 0, nSize, NULL);
		ASSERT(hMMF != NULL);
		LPVOID lpvFile = ::MapViewOfFile(hMMF, FILE_MAP_WRITE, 0, 0, nSize);
		ASSERT(lpvFile != NULL);
		memcpy((char*) lpvFile, pchData, nSize);
		::DuplicateHandle(::GetCurrentProcess(), hMMF, m_hProcessDest, 
			&hMMFReceiver, 0, FALSE, DUPLICATE_SAME_ACCESS | 
			DUPLICATE_CLOSE_SOURCE);
		::PostMessage(m_hWndDest, WM_SENDTEXT, (WPARAM) 0, 
			(LPARAM) hMMFReceiver);
		::UnmapViewOfFile(lpvFile);
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CEx31bFilter, CHttpFilter)
	//{{AFX_MSG_MAP(CEx31bFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/
