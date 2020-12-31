// UT_VrfyEmail.cpp: implementation of the CUT_VrfyEmail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UT_VrfyEmail.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996 )


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//IDD_VERIFY_EMAIL
//IDC_VERIFY_HISTORY
CUT_VrfyEmail::CUT_VrfyEmail(LPTSTR title):CUCPage(IDD_VERIFY_EMAIL,title)
{

}

CUT_VrfyEmail::~CUT_VrfyEmail()
{

}


void CUT_VrfyEmail::OnInitDialog(WPARAM /* wParam */, LPARAM /* lParam */)
{



	//attach the history window to the control
	m_HistoryCtrl.AttachHistoryWindow(m_hWnd,IDC_VERIFY_HISTORY);
	//set the maximum length of the buffer of this window
	m_HistoryCtrl.SetHistoryLength(500);
	// set the font for the history window
	m_hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
	m_HistoryCtrl.SetFont(m_hFont);

	//setup the controls
	SetDlgItemText(m_hWnd, IDC_VERIFY_SERVER,_T("a.root-servers.net"));
	m_bEnableLogChecked = FALSE;
	m_bAbort = FALSE;
	m_hThread = NULL;

}

void CUT_VrfyEmail::OnClicked(int controlId)
{
	switch (controlId)
	{
	case IDC_VERIFY_BTN:
		{

			if (m_hThread == NULL)
			{
				// Create a new thread
				SetDlgItemText(m_hWnd ,IDC_VERIFY_BTN,_T("&Stop"));
				m_hThread = (HANDLE) _beginthread((void (__cdecl *)(void *))VerifyThread,NULL,	reinterpret_cast<void*>(this));
			}
			else
			{
			}
			break;
		}		

	}
}
unsigned __stdcall CUT_VrfyEmail::VerifyThread(void * pThis){

	// pointer to the page class since we are inside a static function	CUT_PingPage*		pThisObject = static_cast<CUT_PingPage*>(pThis );

	// pointer to the page class since we are inside a static function
	CUT_VrfyEmail*		pThisObject = static_cast<CUT_VrfyEmail*>(pThis );


	CUT_MXLookup		mxClient;
	_TCHAR				szVerifyServer[MAX_PATH];
	_TCHAR				szEmail[MAX_PATH];
	_TCHAR				szUseEmail[MAX_PATH];


	// get the Domain to be pinged
	GetDlgItemText(pThisObject->m_hWnd ,IDC_VERIFY_SERVER,szVerifyServer,MAX_PATH-1);

	// get the Domain to be pinged
	GetDlgItemText(pThisObject->m_hWnd ,IDC_VERIFY_EMAIL_TARGET,szEmail,MAX_PATH-1);

	// get the Domain to be pinged
	GetDlgItemText(pThisObject->m_hWnd ,IDC_USING_EMAIL,szUseEmail,MAX_PATH-1);



	int retCode = UTE_SUCCESS;
	BOOL bFound = FALSE;

	if ((retCode = mxClient.LookupMX (szVerifyServer, szEmail)) == UTE_SUCCESS)
	{
		for (int mxCounter = 0;mxCounter < mxClient.GetMXRecordCount() ;mxCounter++)
		{
// v4.2 TODO("TD Using AC(). Overload, if used (this page not shown)")
			if (SendLikeMailToServer(mxClient.GetMXRecord (),AC(szEmail), AC(szUseEmail) , pThisObject) == UTE_SUCCESS)
			{
				pThisObject->m_HistoryCtrl.AddLine (_T("Is a valid email"));
				bFound =TRUE;
				break;

			}
		}
		if (!bFound)
			pThisObject->m_HistoryCtrl.AddLine ("Is not a valid email");

	}else 
	{
		pThisObject->m_HistoryCtrl.AddLine (CUT_ERR::GetErrorString(retCode));
		pThisObject->m_HistoryCtrl.AddLine ("-----------------------------");
		pThisObject->m_HistoryCtrl.AddLine (" ");
	}



	// reste the thread indicator
	pThisObject->m_hThread = NULL;
	return 1;
}
int __stdcall CUT_VrfyEmail::SendLikeMailToServer(LPCSTR serverName,LPCSTR email,LPCSTR from, CUT_VrfyEmail *page){



	CUT_WSClient emailLikeClient;
	int retCode = UTE_SUCCESS;
	char zsTempBuff[MAX_PATH];
	int nFailCode = 0;

	page->m_HistoryCtrl.AddLine("Attempting Connection to ");
	page->m_HistoryCtrl.AppendToLine (serverName);

	if ((retCode = emailLikeClient.Connect (25,serverName))== UTE_SUCCESS)
	{

		// Send the HELO line
		if (emailLikeClient.Send("HELO localhost\r\n") >0)
		{
			// receive the response from the server
			if (emailLikeClient.ReceiveLine(zsTempBuff,MAX_PATH-1) > 4)
				// check the response
			{
				emailLikeClient.ClearReceiveBuffer();
				if (strncmp(zsTempBuff,"220",3)==0)
				{
					_snprintf(zsTempBuff, sizeof(zsTempBuff),"MAIL from: <%s>\r\n",from);
					if (emailLikeClient.Send(zsTempBuff) >0)
					{
						// receive the response from the server
						if (emailLikeClient.ReceiveLine(zsTempBuff,MAX_PATH-1) > 4)
							// check the response
						{
							if (strncmp(zsTempBuff,"250",3)==0)
							{
								_snprintf(zsTempBuff, sizeof(zsTempBuff),"RCPT to: <%s>\r\n",email);
								if (emailLikeClient.Send(zsTempBuff) >0)
								{
									// receive the response from the server
									if (emailLikeClient.ReceiveLine(zsTempBuff,MAX_PATH-1) > 4)
										// check the response
									{
										if (strncmp(zsTempBuff,"250",3)==0)
										{
											page->m_HistoryCtrl.AddLine ("Email Verified");
											page->m_HistoryCtrl.AddLine(zsTempBuff);
											// Send the Quit command
											emailLikeClient.Send("QUIT\r\n");
											return UTE_SUCCESS;
										}
										else
											nFailCode = 8;
									}
									else
										nFailCode = 7;
								}
								else
									nFailCode = 6;
							}
							else
								nFailCode = 5;
						}
						else
							nFailCode = 4;
					}
					else
						nFailCode = 4;
				}
				else
					nFailCode = 3;
			}
			else
				nFailCode = 2;
		}
		else
			nFailCode = 1;
	}

	_snprintf(zsTempBuff, sizeof(zsTempBuff)," Code: %d",nFailCode);
	page->m_HistoryCtrl.AppendToLine (zsTempBuff);

	return 1;

}

#pragma warning ( pop )