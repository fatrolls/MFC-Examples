// LocationDlg.h : Declaration of the CLocationDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

using namespace ATL;
#include <atlstr.h>
#include "wtl/atlapp.h"
#include "wtl/atldlgs.h"

// CLocationDlg

class CLocationDlg : 
	public CDialogImpl<CLocationDlg>
{
public:
	CLocationDlg( )
	{
	}

	~CLocationDlg()
	{
	}
    enum { IDD = IDD_NEWLOCATIONDLG };
    LPCTSTR GetName(){return mstrName;}
private:
     ATL::CString mstrName;

BEGIN_MSG_MAP(CLocationDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
    //COMMAND_ID_HANDLER(IDOK, OnOK)
    //COMMAND_ID_HANDLER(IDCANCEL, OnCancel)

END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//CDialogImpl<CLocationDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);

        CenterWindow();

        // set icons
        HICON hIcon = (HICON)::LoadImage((HINSTANCE) _AtlBaseModule.m_hInst, MAKEINTRESOURCE(IDR_PROJECTTREECTRL), 
            IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
        SetIcon(hIcon, TRUE);
        HICON hIconSmall = (HICON)::LoadImage((HINSTANCE) _AtlBaseModule.m_hInst, MAKEINTRESOURCE(IDR_PROJECTTREECTRL), 
            IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
        SetIcon(hIconSmall, FALSE);

        GetDlgItem(IDC_EDIT_NAME).SetFocus();
		bHandled = TRUE;
		return FALSE;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
        GetDlgItemText(IDC_EDIT_NAME, mstrName);
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

 

};


