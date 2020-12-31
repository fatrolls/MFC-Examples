// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <sstream>
#include <iomanip>
#include <atltime.h>
#include "TreeCtrl.h"

class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
	CMainDlg()
	{
		m_bShowThemed = TRUE;
	}
	
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(IDC_THEME, OnTheme)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

protected:
	CTreeCtrl m_wndTreeCtrl;
	CEdit m_wndEdit;
	CImageList m_ilItemImages;
	BOOL m_bShowThemed;

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		SetIcon(hIconSmall, FALSE);

		m_wndTreeCtrl.SubclassWindow( GetDlgItem( IDC_TREECTRL ) );
		m_wndEdit.Attach( GetDlgItem( IDC_EDIT ) );
		
		m_wndEdit.SetWindowText( _T( "Click here to remove focus from Tree control (greyed selection)" ) );
		
		if ( !m_ilItemImages.CreateFromImage( IDB_EXAMPLE, 16, 0, RGB( 255, 0, 255 ), IMAGE_BITMAP, LR_CREATEDIBSECTION ) )
			return FALSE;
		
		m_wndTreeCtrl.SetImageList( m_ilItemImages );
		
		HTREEITEM hParent = m_wndTreeCtrl.InsertItem( _T( "Top Level 1.1" ), 0, 1, TVI_ROOT, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Second Level 2.1" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Second Level 2.2" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.Expand( hParent, TVE_EXPAND );
		m_wndTreeCtrl.SelectItem( hParent );
		hParent = m_wndTreeCtrl.InsertItem( _T( "Second Level 2.3" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Third Level 3.1" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Third Level 3.2" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.Expand( hParent, TVE_EXPAND );
		hParent = m_wndTreeCtrl.InsertItem( _T( "Third Level 3.3" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Fourth Level 4.1" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.Expand( hParent, TVE_EXPAND );
		hParent = m_wndTreeCtrl.InsertItem( _T( "Top Level 1.2" ), 0, 1, TVI_ROOT, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Second Level 2.1" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Second Level 2.2" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.Expand( hParent, TVE_EXPAND );
		hParent = m_wndTreeCtrl.InsertItem( _T( "Second Level 2.3" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Third Level 3.1" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Third Level 3.2" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.Expand( hParent, TVE_EXPAND );
		hParent = m_wndTreeCtrl.InsertItem( _T( "Third Level 3.3" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.InsertItem( _T( "Fourth Level 4.1" ), 0, 1, hParent, TVI_LAST );
		m_wndTreeCtrl.Expand( hParent, TVE_EXPAND );		
		
		m_wndTreeCtrl.SetMultipleSelect( TRUE );
		m_wndTreeCtrl.SetFocus();		
		
		return FALSE;
	}
	
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
	
	LRESULT OnTheme(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		m_bShowThemed = !m_bShowThemed;
		m_wndTreeCtrl.ShowThemed( m_bShowThemed );
		return 0;
	}
};
