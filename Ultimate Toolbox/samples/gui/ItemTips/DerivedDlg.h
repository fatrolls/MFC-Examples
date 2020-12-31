#if !defined(AFX_DERIVEDDLG_H__60CB2B84_E9A4_11D1_8855_0080C83F712F__INCLUDED_)
#define AFX_DERIVEDDLG_H__60CB2B84_E9A4_11D1_8855_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StandardDlg.h : header file
//

#include "MyListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDerivedDlg dialog

class CDerivedDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CDerivedDlg)

// Construction
public:
	CDerivedDlg();   // standard constructor
	~CDerivedDlg();   

// Dialog Data
	//{{AFX_DATA(CDerivedDlg)
	enum { IDD = IDD_DIALOG_DERIVED };
	CButton	m_btnSmart;
	CButton	m_btnTextFont;
	CButton	m_btnBkColor;
	CMyListCtrl	m_listStandard;
	DWORD	m_clrBackground;
	CString	m_sFontName;
	BOOL	m_bCustomize;
	BOOL	m_bSmart;
	//}}AFX_DATA

	CImageList	*m_pimagelist;
	CImageList	*m_pimagelistSmall;

	DWORD m_clrText;
	CFont m_font;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDerivedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void GetVars();
	void SetVars();
	void ShowControls();

// Implementation
protected:

	void FillListCtrl(void);

	// Generated message map functions
	//{{AFX_MSG(CDerivedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBkcolor();
	afx_msg void OnButtonTextfont();
	afx_msg void OnCheckCustomize();
	afx_msg void OnCheckSmart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DERIVEDDLG_H__60CB2B84_E9A4_11D1_8855_0080C83F712F__INCLUDED_)
