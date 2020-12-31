#if !defined(AFX_CONTROLS_H__F1365403_AC7E_11D1_B25A_006097960BB7__INCLUDED_)
#define AFX_CONTROLS_H__F1365403_AC7E_11D1_B25A_006097960BB7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Controls.h : header file
//

#include "ApBarDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CControlsDlg dialog

class CControlsDlg : public CAppBarDlg
{
// Construction
public:
	CControlsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CControlsDlg)
	enum { IDD = IDD_APPBAR };
	CButton	m_btnStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CControlsDlg)
	afx_msg void OnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLS_H__F1365403_AC7E_11D1_B25A_006097960BB7__INCLUDED_)
