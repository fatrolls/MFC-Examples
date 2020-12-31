// UT_Finger.cpp: implementation of the CUT_FingerPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UT_Finger.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996 )


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "finger_c.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUT_FingerPage::CUT_FingerPage(LPTSTR title):CUCPage(IDD_FINGER_PAGE,title)
{
	m_HistoryCtrl.SetTimeStampFormat(_T("%c"));
}

CUT_FingerPage::~CUT_FingerPage()
{
	
}


void CUT_FingerPage::OnInitDialog(WPARAM /* wParam */, LPARAM /* lParam */)
{
	
	//attach the history window to the control
	m_HistoryCtrl.AttachHistoryWindow(m_hWnd,IDC_FINGER_HISTORY);
	//set the maximum length of the buffer of this window
	m_HistoryCtrl.SetHistoryLength(500);
	// set the font for the history window
	m_hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
	m_HistoryCtrl.SetFont(m_hFont);
	
	//setup the controls
	SetDlgItemText(m_hWnd, IDC_USER_NDOMAIN,_T("help@berkeley.edu"));

    // default log file
	SetDlgItemText(m_hWnd, IDC_FINGER_LOG_FILE,_T("session.txt"));

	m_bEnableLogChecked = FALSE;
	EnableWindow(GetDlgItem(m_hWnd,IDC_FINGER_LOG_FILE),m_bEnableLogChecked);
	
	
}

void CUT_FingerPage::OnHelp(LPARAM lParam){

    HELPINFO hInfo = *((LPHELPINFO) lParam);    

	::WinHelp((HWND)hInfo.hItemHandle, _T("DSITools.hlp"),
		   HELP_WM_HELP, (DWORD)(ULONG_PTR)(LPVOID)dwFingerHelpMap);


}

void CUT_FingerPage::OnClicked(int controlId)
{
	switch (controlId)
	{
		
    case IDC_FINGER_ABOUT:
        {
		::WinHelp(m_hWnd, _T("DSITools.hlp"),
		   HELP_CONTENTS,0);
        return;
        }
		
	case IDC_FINGER_ENABLE_LOG:
		{
			if (m_bEnableLogChecked)
			{
				m_bEnableLogChecked = FALSE;
				// just disable the log
				m_HistoryCtrl.EnableLog (m_bEnableLogChecked);
			}
			else
				m_bEnableLogChecked = TRUE;
			
			
			EnableWindow(GetDlgItem(m_hWnd,IDC_FINGER_LOG_FILE),m_bEnableLogChecked);
			
			break;
			
		}
	case IDC_FINGER_BTN:
		{
			//set the cursor to an hourglass	
			SetCursor(LoadCursor(NULL,IDC_WAIT));
			_TCHAR buf[MAX_PATH];
			
			
			if (m_bEnableLogChecked)
			{
				_TCHAR	szLogFileName[MAX_PATH];
				// get the name of the file to log to
				GetDlgItemText(m_hWnd,IDC_FINGER_LOG_FILE,szLogFileName,MAX_PATH-1);
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
					
			//clear the history control
			m_HistoryCtrl.ClearHistory();
			//get the information to finger
			GetDlgItemText(m_hWnd, IDC_USER_NDOMAIN,buf,MAX_PATH-1);
			
			if (_tcsstr(buf, _T("@")) == NULL) {
				
				// Oops, forgot the @ symbol
				MessageBox(m_hWnd, _T("The finger address must contain the @ symbol."), 
					NULL, MB_OK | MB_ICONINFORMATION);
			}
			else {
				
                TCHAR    szDispString[MAX_PATH];
                _sntprintf(szDispString, MAX_PATH, _T("Results of finger query \"%s\":"), buf);
                m_HistoryCtrl.AddStampedLine(_T(" "));
                m_HistoryCtrl.AddLine(szDispString);
                m_HistoryCtrl.AddLine(_T(" "));

                //perform the finger
				CUT_FingerClient fc;
                int res = fc.Finger(buf);
				if(res == UTE_SUCCESS){
					//show the results
					int numLines = fc.GetNumberReturnLines();
					for(int index =0;index <numLines;index++){
						m_HistoryCtrl.AddLine(fc.GetReturnLine(index));
                    }
				}
                m_HistoryCtrl.AddLine(" ");
                m_HistoryCtrl.AddLine(CUT_ERR::GetErrorString(res));
                m_HistoryCtrl.AddLine("-----------------------------");
                m_HistoryCtrl.AddLine(" ");
				
				//set the cursor back to the arrow
				SetCursor(LoadCursor(NULL,IDC_ARROW));
			}
			
			break;
		}
	}
}

#pragma warning ( pop )