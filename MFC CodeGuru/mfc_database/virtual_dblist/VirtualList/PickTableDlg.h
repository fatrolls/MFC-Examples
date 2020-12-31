#if !defined(AFX_PICKTABLEDLG_H__A1E706AD_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
#define AFX_PICKTABLEDLG_H__A1E706AD_5F36_11D1_959E_D1A30ED05A05__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PickTableDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CPickTableDlg dialog

class CPickTableDlg : public CDialog
{
// Construction
public:
	CPickTableDlg(CWnd* pParent = NULL);   // standard constructor
	CPickTableDlg(CDaoDatabase* pDB, CWnd* pParent = NULL);   // standard constructor
	void GetTableName(CString& tableName); 

// Dialog Data
	//{{AFX_DATA(CPickTableDlg)
	enum { IDD = IDD_DIALOG1 };
	CListBox	m_ListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPickTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDaoDatabase* m_pDB;
	void PopulateList(); 
	CString m_TableName;
	// Generated message map functions
	//{{AFX_MSG(CPickTableDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICKTABLEDLG_H__A1E706AD_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
