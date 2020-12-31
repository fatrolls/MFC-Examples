#if !defined(AFX_TEST21DDIALOG_H__1AA889D6_9788_11D0_BED2_00C04FC2A0C2__INCLUDED_)
#define AFX_TEST21DDIALOG_H__1AA889D6_9788_11D0_BED2_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Test21dDialog.h : header file
//

extern "C" __declspec(dllimport) void Ex21dEntry(); // dummy function
#define RYG_SETSTATE WM_USER + 0
#define RYG_GETSTATE WM_USER + 1


/////////////////////////////////////////////////////////////////////////////
// CTest21dDialog dialog

class CTest21dDialog : public CDialog
{
private:
	enum { OFF, RED, YELLOW, GREEN } m_nState;

// Construction
public:
	CTest21dDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTest21dDialog)
	enum { IDD = IDD_EX21D };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest21dDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTest21dDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnClickedRyg();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST21DDIALOG_H__1AA889D6_9788_11D0_BED2_00C04FC2A0C2__INCLUDED_)
