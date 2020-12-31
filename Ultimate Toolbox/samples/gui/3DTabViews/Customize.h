#if !defined(AFX_CUSTOMIZE_H__229EBDA3_561B_11D2_B475_00E0291A4FD3__INCLUDED_)
#define AFX_CUSTOMIZE_H__229EBDA3_561B_11D2_B475_00E0291A4FD3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Customize.h : header file
//

#include "OXSeparator.h"
#include "OXStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDlg dialog

class CCustomizeDlg : public CDialog
{
// Construction
public:
	CCustomizeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeDlg)
	enum { IDD = IDD_CUSTOMIZE };
	COXStatic	m_ctlTiltle;
	COXSeparator	m_separator3;
	COXSeparator	m_separator2;
	COXSeparator	m_separator1;
	CSpinButtonCtrl	m_spinOffsetExt;
	DWORD	m_dwOffsetExt;
	CSpinButtonCtrl	m_spinOffsetInt;
	DWORD	m_dwOffsetInt;
	BOOL	m_bBottom;
	BOOL	m_bFixedWidth;
	BOOL	m_bMultiline;
	BOOL	m_bScrollOpposite;
	BOOL	m_bOpenCustomizeDlg;
	BOOL	m_bVertical;
	//}}AFX_DATA
	DWORD m_dwStyle;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomizeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckVertical();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZE_H__229EBDA3_561B_11D2_B475_00E0291A4FD3__INCLUDED_)
