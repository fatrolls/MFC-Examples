#if !defined(AFX_PROPDLG_H__91A4B002_0AB6_11D2_8412_0000B43382FE__INCLUDED_)
#define AFX_PROPDLG_H__91A4B002_0AB6_11D2_8412_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropDlg dialog
#include "PropPage1.h"
#include "PropPage2.h"
#include "PropPage3.h"

#include "gfx.h"

class Doc;
class View;

class CPropDlg : public CDialog
{
// Construction
public:
	void SetObject(Doc * pd, View * pv);
	CPropDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropDlg)
	enum { IDD = IDD_PROP_DLG };
	CTabCtrl	wndTab;
	//}}AFX_DATA

	CPropPage1 dlgSheet1;
	CPropPage2 dlgSheet2;
	CPropPage3 dlgSheet3;

	enum { iNumDialog = 3};
	GfxTabSupport(iNumDialog);

	View * pView;
	Doc  * pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPDLG_H__91A4B002_0AB6_11D2_8412_0000B43382FE__INCLUDED_)
