#if !defined(AFX_PAGEPAGE1_H__09EE3121_0F7F_11D2_842D_0000B43382FE__INCLUDED_)
#define AFX_PAGEPAGE1_H__09EE3121_0F7F_11D2_842D_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PagePage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPagePage1 dialog
class Doc;

class CPagePage1 : public CDialog
{
// Construction
public:
	CPagePage1(CWnd* pParent = NULL);   // standard constructor
	Doc * pDoc;

// Dialog Data
	//{{AFX_DATA(CPagePage1)
	enum { IDD = IDD_PAGE_PAGE1 };
	int		iBottom;
	int		iLeft;
	CString	csName;
	int		iRight;
	int		iTop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPagePage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPagePage1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEPAGE1_H__09EE3121_0F7F_11D2_842D_0000B43382FE__INCLUDED_)
