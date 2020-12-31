#if !defined(AFX_LISTPRINTSETUP_H__E1B3DDE5_9D53_11D1_8BAC_0000B43382FE__INCLUDED_)
#define AFX_LISTPRINTSETUP_H__E1B3DDE5_9D53_11D1_8BAC_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListPrintSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListPrintSetup dialog
#include "CoolButton.h"
#include "ListPrintPage1.h"
#include "ListPrintPage2.h"

// This are some small helper macros to manage CDialogs as tab pages

// put this in the header file with numDialog = number of cdialogs pages
#define GfxTabSupport(numDialog)	CDialog * __gfxTabDialog[numDialog];

// used to set up the array of CDialog * with the pages pointer; see OnInitDialog for sample
#define GfxSetTabDialog(numDialog, pDialog)	__gfxTabDialog[numDialog] = (CDialog *) pDialog;

// used to insert tabs in the control; m_ctlTab is the tab control, nId the index of page
// and pText the label of the page; see OnInitDialog for sample
#define GfxAddTabItem(m_ctlTab, nId, pText)\
{\
	TC_ITEM TabCtrlItem;\
	TabCtrlItem.mask = TCIF_TEXT;\
	TabCtrlItem.pszText = pText;\
	m_ctlTab.InsertItem( nId, &TabCtrlItem );\
}

// called in the CTabCtrl OnSelChange to switch between pages
#define GfxSwitchTabDialog(numDialog, maxDialog)\
{\
	for (int __gfxT = 0; __gfxT < maxDialog; __gfxT++)\
	{\
		if (__gfxT == numDialog) \
			__gfxTabDialog[__gfxT]->ShowWindow(SW_SHOW); \
		else \
			__gfxTabDialog[__gfxT]->ShowWindow(SW_HIDE); \
	}\
}

class CListPrintSetup : public CDialog
{
// Construction
public:
	CListPrintSetup(CWnd* pParent = NULL);   // standard constructor
	CListPrintPage1	dlgSheet1;
	CListPrintPage2 dlgSheet2;

	enum { iNumDialog = 2};
	GfxTabSupport(iNumDialog);

	void OnUpdateDialog();

// Dialog Data
	//{{AFX_DATA(CListPrintSetup)
	enum { IDD = IDD_LISTSETUP };
	CCoolButton	wndOk;
	CCoolButton	wndCancel;
	CTabCtrl	wndTab;
	CCoolButton	wndPrintOpt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListPrintSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListPrintSetup)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtPrintopt();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTPRINTSETUP_H__E1B3DDE5_9D53_11D1_8BAC_0000B43382FE__INCLUDED_)
