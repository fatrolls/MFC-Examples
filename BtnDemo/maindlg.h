// maindlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__C40B4C5B_3830_11D6_B650_0048548B09C5__INCLUDED_)
#define AFX_MAINDLG_H__C40B4C5B_3830_11D6_B650_0048548B09C5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	CBmpBtn m_ok;
	CBmpBtn m_cancel;
	CBmpBtn m_autofire;

	CProgressBarCtrl m_progress;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return IsDialogMessage(pMsg);
	}

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_RANGE_HANDLER(IDC_CHECK1, IDC_CHECK2, OnCheck)
		COMMAND_ID_HANDLER(IDAUTOFIRE, OnAutofire)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
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

		// change the OK button extended style
		DWORD dw = BMPBTN_AUTOSIZE | BMPBTN_AUTO3D_SINGLE | BMPBTN_SHAREIMAGELISTS;
		m_ok.SetBitmapButtonExtendedStyle(dw);

		// create the OK button's imagelist
		m_ok.m_ImageList.Create(IDB_BUTTONS, 64, 0, RGB(192,192,192));

		// get the handle to use for other buttons
		HIMAGELIST hImage = m_ok.GetImageList();

		// configure OK bitmap button
		//
		// set normal, pressed, hover, disabled images
		m_ok.SetImages(0, 1, 2, 3);
		m_ok.SetToolTipText(_T("OK button tip"));
		// subclass the OK button
		m_ok.SubclassWindow(GetDlgItem(IDOK));

		// configure Cancel bitmap button
		m_cancel.SetImageList(hImage); // OK button imagelist
		m_cancel.SetImages(4, 5, 6, 7);
		m_cancel.SetToolTipText(_T("Cancel button tip"));
		m_cancel.SubclassWindow(GetDlgItem(IDCANCEL));

		// configure Autofire bitmap button
		m_autofire.SetImageList(hImage); // OK button imagelist
		m_autofire.SetImages(8);
		m_autofire.SetToolTipText(_T("Autofire button tip"));
		m_autofire.SubclassWindow(GetDlgItem(IDAUTOFIRE));
		// add the autofire style to the button
		DWORD dwExtendedStyle = BMPBTN_AUTOFIRE | BMPBTN_AUTOSIZE | BMPBTN_AUTO3D_SINGLE;
		m_autofire.SetBitmapButtonExtendedStyle(dwExtendedStyle);

		// get the handle of the progress control
		m_progress = GetDlgItem(IDC_PROGRESS1);

		return TRUE;
	}

	LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL&)
	{
		// destroy OK button imagelist
		m_ok.m_ImageList.Destroy();
		return 0;	
	}

	LRESULT OnOK(WORD, WORD wID, HWND, BOOL&)
	{
		CloseDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD, WORD wID, HWND, BOOL&)
	{
		CloseDialog(wID);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}

	LRESULT OnCheck(WORD, WORD wID, HWND, BOOL&)
	{
		UINT nFlag = IsDlgButtonChecked(wID);

		if (wID == IDC_CHECK1)
			m_cancel.EnableWindow(!nFlag); // enable/disable Cancel button
		else if (wID == IDC_CHECK2)
			SetHover(nFlag); // set hover style for buttons

		return 0;	
	}

	void SetHover(BOOL bOn = true)
	{
		DWORD dwExtendedStyle = BMPBTN_AUTOSIZE | BMPBTN_AUTO3D_SINGLE;

		if (bOn)
			dwExtendedStyle |= BMPBTN_HOVER; // add hover style
		else
			dwExtendedStyle |= ~BMPBTN_HOVER; // remove hover style

		// change the OK button style
		m_ok.SetBitmapButtonExtendedStyle(dwExtendedStyle);
		m_ok.Invalidate();
		m_ok.UpdateWindow();

		// change the Cancel button style
		m_cancel.SetBitmapButtonExtendedStyle(dwExtendedStyle);
		m_cancel.Invalidate();
		m_cancel.UpdateWindow();
	}

	LRESULT OnAutofire(WORD, WORD wID, HWND, BOOL&)
	{
		static UINT nPos = 0;

		// increment the progress control
		if (wID == IDAUTOFIRE)
			m_progress.SetPos(++nPos);

		return 0;	
	}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__C40B4C5B_3830_11D6_B650_0048548B09C5__INCLUDED_)
