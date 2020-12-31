#if !defined(AFX_MODELESSPPSH_H__DE9611DB_F003_11D1_A7E2_E88B6FC70000__INCLUDED_)
#define AFX_MODELESSPPSH_H__DE9611DB_F003_11D1_A7E2_E88B6FC70000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ModelessPpsh.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModelessPpsh

class CModelessPpsh : public CPropertySheet
{
	DECLARE_DYNAMIC(CModelessPpsh)

// Construction
public:
	CModelessPpsh(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CModelessPpsh(LPCTSTR pszCaption = "", CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelessPpsh)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CModelessPpsh();

	// Generated message map functions
protected:
	//{{AFX_MSG(CModelessPpsh)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELESSPPSH_H__DE9611DB_F003_11D1_A7E2_E88B6FC70000__INCLUDED_)
