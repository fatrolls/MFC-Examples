#if !defined(AFX_COMPDIALOG_H__6A38F6B6_F108_11D3_ACC3_0050BAAB46B1__INCLUDED_)
#define AFX_COMPDIALOG_H__6A38F6B6_F108_11D3_ACC3_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CompDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCompDialog dialog


class CCompDialog : public CDialog
{
// Construction
public:
	enum {ACTION_NEW=1,
		ACTION_MODIFY};

	UINT m_nAction;
	CCompDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCompDialog)
	enum { IDD = IDD_DIALOG_COMPT };
	BOOL	m_bEnabled;
	BOOL	m_bScrollable;
	BOOL	m_bSizeable;
	UINT	m_nHeight;
	int		m_nLeft;
	CString	m_sName;
	CString	m_sSource;
	int		m_nTop;
	UINT	m_nWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCompDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPDIALOG_H__6A38F6B6_F108_11D3_ACC3_0050BAAB46B1__INCLUDED_)
