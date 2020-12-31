#if !defined(AFX_LISTCOLORDIALOG_H__F3B02DE1_DFD4_11D8_B14D_002018574596__INCLUDED_)
#define AFX_LISTCOLORDIALOG_H__F3B02DE1_DFD4_11D8_B14D_002018574596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListColorDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListColorDialog dialog

#include "quicklist.h"

class CListColorDialog : public CDialog
{
// Construction
public:
	CListColorDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListColorDialog)
	enum { IDD = IDD_DIALOG_COLOR };
	CQuickList	m_list;
	//}}AFX_DATA

	afx_msg LRESULT OnGetListItem(WPARAM wParam, LPARAM lParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListColorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListColorDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCOLORDIALOG_H__F3B02DE1_DFD4_11D8_B14D_002018574596__INCLUDED_)
