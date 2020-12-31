#if !defined(AFX_CREDITDIALOG_H__97882521_4ABC_11D1_9E3C_00A0245800CF__INCLUDED_)
#define AFX_CREDITDIALOG_H__97882521_4ABC_11D1_9E3C_00A0245800CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CreditDialog.h : header file
//

#include "CreditStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CCreditDialog dialog

class CCreditDialog : public CDialog
{
// Construction
public:
	CCreditDialog(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CCreditDialog)
	enum { IDD = IDD_DISPLAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreditDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCreditStatic m_static;
	UINT bitmapIDs[2];
	UINT TimerOn;
	// Generated message map functions
	//{{AFX_MSG(CCreditDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREDITDIALOG_H__97882521_4ABC_11D1_9E3C_00A0245800CF__INCLUDED_)
