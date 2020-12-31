#if !defined(AFX_STANDARDDLG_H__60CB2B84_E9A4_11D1_8855_0080C83F712F__INCLUDED_)
#define AFX_STANDARDDLG_H__60CB2B84_E9A4_11D1_8855_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StandardDlg.h : header file
//

#include "OXItemTip.h"

/////////////////////////////////////////////////////////////////////////////
// CStandardDlg dialog

void CALLBACK ItemTipHelper(LPARAM lpSource, LPARAM lpInfo);

class CStandardDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CStandardDlg)

// Construction
public:
	CStandardDlg();   // standard constructor
	~CStandardDlg();   

// Dialog Data
	//{{AFX_DATA(CStandardDlg)
	enum { IDD = IDD_DIALOG_STANDARD };
	CButton	m_btnSmart;
	CButton	m_btnTextFont;
	CButton	m_btnBkColor;
	CListCtrl	m_listStandard;
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
	//{{AFX_VIRTUAL(CStandardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void GetVars();
	void SetVars();
	void ShowControls();

// Implementation
protected:

	COXItemTip m_ItemTip;

	void FillListCtrl(void);

	// Generated message map functions
	//{{AFX_MSG(CStandardDlg)
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

#endif // !defined(AFX_STANDARDDLG_H__60CB2B84_E9A4_11D1_8855_0080C83F712F__INCLUDED_)
