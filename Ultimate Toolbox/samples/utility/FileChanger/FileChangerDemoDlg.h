// CFileChangerDemoDlg.h : header file
//

#if !defined(AFX_CFileChangerDemoDlg_H__C3AA0CE6_F410_11D0_B8FE_444553540000__INCLUDED_)
#define AFX_CFileChangerDemoDlg_H__C3AA0CE6_F410_11D0_B8FE_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CMyFileChanger

#include "OXFileChanger.h"

/////////////////////////////////////////////////////////////////////////////
// CFileChangerDemoDlg dialog

class CFileChangerDemoDlg : public CDialog
{
// Construction
public:
	static void toBinary(CString& sText, CByteArray* binary = NULL, BOOL bFormat = TRUE);
	static int xch2int(TCHAR ch);
	CFileChangerDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFileChangerDemoDlg)
	enum { IDD = IDD_FILECHANGER_DIALOG };
	CButton	m_ctlOverwrite;
	CButton	m_ctlWholeWord;
	CEdit	m_ctlFileOut;
	CButton	m_ctlBrowseOut;
	CButton	m_ctlMatchCase;
	BOOL	m_bAll;
	CString	m_sFileIn;
	CString	m_sFileOut;
	CString	m_sFindText;
	BOOL	m_bMatchCase;
	BOOL	m_bOverwrite;
	CString	m_sReplaceText;
	BOOL	m_bUseCFile;
	BOOL	m_bWholeWord;
	int		m_nTextBinary;
	BOOL	m_bMessage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileChangerDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	COXFileChanger m_fc;
	void OnBrowse(CString& sEditBoxText);

	// Generated message map functions
	//{{AFX_MSG(CFileChangerDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelectTextBinary();
	afx_msg void OnFind();
	afx_msg void OnReplace();
	afx_msg void OnSelectOverwrite();
	afx_msg void OnBrowseIn();
	afx_msg void OnBrowseOut();
	afx_msg void OnUsecfile();
	afx_msg void OnMessage();
	afx_msg LRESULT OnFileMatchFound(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFilePreReplace(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFilePostReplace(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFileChangerDemoDlg_H__C3AA0CE6_F410_11D0_B8FE_444553540000__INCLUDED_)
