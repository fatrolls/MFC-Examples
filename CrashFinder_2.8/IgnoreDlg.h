#if !defined(AFX_IGNOREDLG_H__F2508BE2_C38E_11D1_8D69_00A0244A1BB3__INCLUDED_)
#define AFX_IGNOREDLG_H__F2508BE2_C38E_11D1_8D69_00A0244A1BB3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// IgnoreDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIgnoreDlg dialog

class CIgnoreDlg : public CDialog
{
// Construction
public:
	CIgnoreDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIgnoreDlg)
	enum { IDD = IDD_IGNOREDDLG };
	CCheckListBox	m_IgnoreList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIgnoreDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	CMapStringToPtr m_DeleteList;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIgnoreDlg)
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IGNOREDLG_H__F2508BE2_C38E_11D1_8D69_00A0244A1BB3__INCLUDED_)
