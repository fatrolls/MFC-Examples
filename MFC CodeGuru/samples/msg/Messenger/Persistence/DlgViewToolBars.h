/* 
 * Copyright (c)1997 David Carballo, All Right Reserved
 *
 * Created October 1997
 * Revised: -
 * Written by David Carballo
 * Internet: fibeto@redestb.es
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 */

/* *******************     IMPORTANT  ****************************************

IN YOUR RESOURCE FILE YOU WILL NEED A DIALOG LIKE THIS

IDD_VIEW_TOOLBARS DIALOG DISCARDABLE  0, 0, 189, 106
STYLE DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Toolbars"
FONT 8, "MS Sans Serif"
BEGIN
    LTEXT           "&Toolbars:",IDC_STATIC,7,7,30,8
    LISTBOX         IDC_LIST_TOOLBARS,7,18,117,66,LBS_OWNERDRAWFIXED | 
                    LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | WS_VSCROLL | 
                    WS_TABSTOP
    CONTROL         "&Show Tooltips",IDC_CHECK_TOOLTIPS,"Button",
                    BS_AUTOCHECKBOX | WS_TABSTOP,7,89,61,10
    DEFPUSHBUTTON   "Close",IDOK,132,7,50,14
END

*/

#ifndef __DLGVIEWTOOLBARS_H_
#define __DLGVIEWTOOLBARS_H_

#include "resource.h"

class CDlgViewToolBars: public CDialog
{
// Construction
public:
	CDlgViewToolBars(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewToolBars)
	enum { IDD = IDD_VIEW_TOOLBARS };
	CCheckListBox	m_lstToolbars;
	BOOL	m_bShowToolTips;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewToolBars)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewToolBars)
	afx_msg void OnCheckTooltips();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void FillListToolBars();
};

#endif	// __DLGVIEWTOOLBARS_H_
