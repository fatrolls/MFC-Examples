#if !defined(AFX_DLGATTACHMENTS_H__333BA6DC_F593_11D1_870E_444553540001__INCLUDED_)
#define AFX_DLGATTACHMENTS_H__333BA6DC_F593_11D1_870E_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgAttachments.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAttachments dialog

class CDlgAttachments : public CDialog
{
// Construction
public:
	CStringArray m_Files;
	CDlgAttachments(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAttachments)
	enum { IDD = IDD_ATTACHMENTS };
	CListBox	m_ctlFiles;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAttachments)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAttachments)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGATTACHMENTS_H__333BA6DC_F593_11D1_870E_444553540001__INCLUDED_)
