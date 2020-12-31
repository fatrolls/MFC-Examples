/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.
   Author: Leon Finker  1/2001
**************************************************************************/
// maindlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__DD8854E4_D952_44D9_9873_29A4017E8EC3__INCLUDED_)
#define AFX_MAINDLG_H__DD8854E4_D952_44D9_9873_29A4017E8EC3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "controls.h"

class CMainDlg : public CAxDialogImpl<CMainDlg>
{
	CEditBox m_edit;
	CTreeBox m_tree;
	CListViewBox m_listview;
	CStaticBox m_stat;
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

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
		
		/////////////////////////////////
		m_edit.SubclassWindow(GetDlgItem(IDC_EDIT1));
		if(!m_edit.InitDragDrop())
			return -1;
		/////////////////////////////////
		m_listview.SubclassWindow(GetDlgItem(IDC_LISTVIEW));
		if(!m_listview.InitDragDrop())
			return -1;
		m_listview.InsertColumn(0, "Column 1", LVCFMT_LEFT , 100, -1);
		m_listview.InsertItem(0,"item1");
		m_listview.InsertItem(1,"item2");
		m_listview.InsertItem(2,"item3");
		/////////////////////////////////
		m_tree.SubclassWindow(GetDlgItem(IDC_TREE1));
		if(!m_tree.InitDragDrop())
			return -1;
		
		TVINSERTSTRUCT tvins={0};
		tvins.hParent = TVI_ROOT;
		tvins.hInsertAfter = TVI_LAST;
		TVITEM tvit={0};
		tvit.mask = TVIF_TEXT;
		tvit.pszText = "some string";
		tvins.item = tvit;
		TreeView_InsertItem(m_tree, &tvins);
		/////////////////////////////////
		m_stat.SubclassWindow(GetDlgItem(IDC_BITMAP));
		m_stat.ModifyStyle(0, SS_BITMAP|SS_CENTERIMAGE|SS_REALSIZEIMAGE);
		HBITMAP hBmp=LoadBitmap(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDB_BITMAP1));
		m_stat.SetBitmap(hBmp);
		if(!m_stat.InitDragDrop())
			return -1;
		/////////////////////////////////
		return TRUE;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__DD8854E4_D952_44D9_9873_29A4017E8EC3__INCLUDED_)
