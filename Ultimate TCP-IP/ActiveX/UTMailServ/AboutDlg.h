// =================================================================
//  class: CAboutDlg
//  File:  AboutDlg.h
//  
//  Purpose:
//
//	Display Finger ActiveX Control about box
//
// =================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// =================================================================
#ifndef __ABOUTDLG_H_
#define __ABOUTDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg
class CAboutDlg : 
	public CAxDialogImpl<CAboutDlg>
{
private:
	LPCTSTR	lpszMessage;	// Pointer to the additional message

public:
	CAboutDlg(LPCTSTR message = NULL) : lpszMessage(message)
	{
	}

	~CAboutDlg()
	{
	}

	enum { IDD = IDD_ABOUTDLG };

BEGIN_MSG_MAP(CAboutDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		#ifdef EVALUATION_MODE

			// Change about box text in case of evaluation mode
			char	szVersionText[50], szEvaluationVersionText[50];
			GetDlgItemText(IDC_VERSION_TEXT, szVersionText, sizeof(szVersionText) - 1);
			
			strcpy(szEvaluationVersionText, "Evaluation ");
			strcat(szEvaluationVersionText, szVersionText);
			strcat(szEvaluationVersionText, " Not for commercial use!");

			SetDlgItemText(IDC_VERSION_TEXT, szEvaluationVersionText);
		#endif

		// Set additional message in the version number field
		if(lpszMessage)
			SetDlgItemText(IDC_VERSION_TEXT, lpszMessage);

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#pragma warning(pop)

#endif //__ABOUTDLG_H_
