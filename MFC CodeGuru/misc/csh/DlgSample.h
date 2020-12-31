#if !defined(AFX_DLGSAMPLE_H__73AC6303_CCD6_11D1_8018_A601086D0638__INCLUDED_)
#define AFX_DLGSAMPLE_H__73AC6303_CCD6_11D1_8018_A601086D0638__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgSample.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSample dialog

class CDlgSample : public CDialog
{
// Construction
public:
	CDlgSample(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSample)
	enum { IDD = IDD_SAMPLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSample)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static const DWORD m_nHelpIDs[];
	// Generated message map functions
	//{{AFX_MSG(CDlgSample)
	virtual BOOL OnInitDialog();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSAMPLE_H__73AC6303_CCD6_11D1_8018_A601086D0638__INCLUDED_)
