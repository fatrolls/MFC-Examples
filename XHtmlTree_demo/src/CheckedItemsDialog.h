// CheckedItemsDialog.h : header file
//

#ifndef CHECKEDITEMSDIALOG_H
#define CHECKEDITEMSDIALOG_H

#include "resource.h"
#include "roedit.h"

extern UINT WM_CHECKEDITEMSDIALOG_CLOSING;

/////////////////////////////////////////////////////////////////////////////
// CCheckedItemsDialog dialog

class CCheckedItemsDialog : public CDialog
{
// Construction
public:
	CCheckedItemsDialog(CWnd* pParent, CPoint point);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckedItemsDialog)
	enum { IDD = IDD_CHECKED_ITEMS };
	CEdit	m_edit;
	CROEdit m_checkeditems;
	//}}AFX_DATA

	CString m_strText;

// Operations
public:
	void SetText(LPCTSTR lpszText);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckedItemsDialog)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnCancel();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd * m_pParent;

	// Generated message map functions
	//{{AFX_MSG(CCheckedItemsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //CHECKEDITEMSDIALOG_H
