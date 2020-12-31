#if !defined(AFX_TRANSFERDLG_H__26E6D945_0616_11D2_88B2_0080C859A484__INCLUDED_)
#define AFX_TRANSFERDLG_H__26E6D945_0616_11D2_88B2_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TransferDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransferDlg dialog

class COXSerialCommFile;

class CTransferDlg : public CDialog
{
// Construction
public:
	CTransferDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransferDlg)
	enum { IDD = IDD_TRANSFER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

protected:
	BOOL m_bCancelPressed;

public:
	CString m_sFilename;
	CString m_sMessage;

	COXSerialCommFile* m_pCommFile;

	CFile* m_pFile;

	BOOL m_bSending;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransferDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg LONG OnStartSending(WPARAM, LPARAM);
	afx_msg LONG OnStartReceiving(WPARAM, LPARAM);

	// Generated message map functions
	//{{AFX_MSG(CTransferDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFERDLG_H__26E6D945_0616_11D2_88B2_0080C859A484__INCLUDED_)
