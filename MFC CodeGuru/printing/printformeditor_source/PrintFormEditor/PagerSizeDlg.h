#if !defined(AFX_PAGERSIZEDLG_H__08DDE513_0B44_11D2_8413_0000B43382FE__INCLUDED_)
#define AFX_PAGERSIZEDLG_H__08DDE513_0B44_11D2_8413_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PagerSizeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPagerSizeDlg dialog

class CPagerSizeDlg : public CDialog
{
// Construction
public:
	CPagerSizeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPagerSizeDlg)
	enum { IDD = IDD_PAPERSIZE };
	int		iBottom;
	int		iLeft;
	int		iRight;
	int		iTop;
	CString	csPageName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPagerSizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPagerSizeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGERSIZEDLG_H__08DDE513_0B44_11D2_8413_0000B43382FE__INCLUDED_)
