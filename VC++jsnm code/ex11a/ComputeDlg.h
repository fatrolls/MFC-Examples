#if !defined(AFX_COMPUTEDLG_H__7D11C137_6C0B_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_COMPUTEDLG_H__7D11C137_6C0B_11D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ComputeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComputeDlg dialog

class CComputeDlg : public CDialog
{
private:
	int m_nTimer;
	int m_nCount;
	enum { nMaxCount = 10000 };

// Construction
public:
	CComputeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComputeDlg)
	enum { IDD = IDD_COMPUTE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComputeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComputeDlg)
	afx_msg void OnStart();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPUTEDLG_H__7D11C137_6C0B_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
