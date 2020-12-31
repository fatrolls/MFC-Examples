// shelldocDlg.h : header file
//

#if !defined(AFX_SHELLDOCDLG_H__A773FE79_4192_11D1_AE13_006097D60BAC__INCLUDED_)
#define AFX_SHELLDOCDLG_H__A773FE79_4192_11D1_AE13_006097D60BAC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CShelldocDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CShelldocDlg dialog

class CShelldocDlg : public CDialog
{
	DECLARE_DYNAMIC(CShelldocDlg);
	friend class CShelldocDlgAutoProxy;

// Construction
public:
	CShelldocDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CShelldocDlg();

// Dialog Data
	//{{AFX_DATA(CShelldocDlg)
	enum { IDD = IDD_SHELLDOC_DIALOG };
	CStatic	m_xDispName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShelldocDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CShelldocDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CShelldocDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLDOCDLG_H__A773FE79_4192_11D1_AE13_006097D60BAC__INCLUDED_)
