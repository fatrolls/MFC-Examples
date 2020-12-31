#if !defined(AFX_DDD_H__B4721AA3_7EB6_11D3_9810_0088CC094230__INCLUDED_)
#define AFX_DDD_H__B4721AA3_7EB6_11D3_9810_0088CC094230__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ddd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cddd dialog

class Cddd : public CDialog
{
// Construction
public:
	Cddd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cddd)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cddd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cddd)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDD_H__B4721AA3_7EB6_11D3_9810_0088CC094230__INCLUDED_)
