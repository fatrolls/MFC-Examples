#if !defined(AFX_URLDLG_H__1C26A2A2_F3D6_11D1_8F58_EA8491322E38__INCLUDED_)
#define AFX_URLDLG_H__1C26A2A2_F3D6_11D1_8F58_EA8491322E38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UrlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUrlDlg dialog

class CUrlDlg : public CDialog
{
// Construction
protected: // create from serialization only

	DECLARE_SERIAL(CUrlDlg)

public:
	CUrlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUrlDlg)
	enum { IDD = IDD_GETURL };
	CComboBox	m_comboBox;
	BOOL	m_root;
	//}}AFX_DATA

	CStringList m_list;
	CString m_WebFileName;

	int m_select;
	int m_count;
	char buffer[260];
	BOOL SaveFile (LPCSTR lpszFileName);
	BOOL LoadFile (LPCSTR lpszFileName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUrlDlg)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUrlDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeUrlcombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URLDLG_H__1C26A2A2_F3D6_11D1_8F58_EA8491322E38__INCLUDED_)
