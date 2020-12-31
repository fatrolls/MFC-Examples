#if !defined(AFX_LISTPRINTPAGE2_H__2DCD2CC2_9D76_11D1_8BAC_0000B43382FE__INCLUDED_)
#define AFX_LISTPRINTPAGE2_H__2DCD2CC2_9D76_11D1_8BAC_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListPrintPage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListPrintPage2 dialog

class CListPrintPage2 : public CDialog
{
// Construction
public:
	void Update();
	CListPrintPage2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListPrintPage2)
	enum { IDD = IDD_LISTPAGE2 };
	int		iDown;
	int		iDx;
	int		iSx;
	int		iUp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListPrintPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListPrintPage2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTPRINTPAGE2_H__2DCD2CC2_9D76_11D1_8BAC_0000B43382FE__INCLUDED_)
