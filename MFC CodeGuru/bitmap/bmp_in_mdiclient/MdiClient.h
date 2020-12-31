#if !defined(AFX_VNMDICLIENT_H__FC9EC8F2_8175_11D1_A16B_000000000000__INCLUDED_)
#define AFX_VNMDICLIENT_H__FC9EC8F2_8175_11D1_A16B_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMdiClient : public CWnd
{
	DECLARE_DYNCREATE(CMdiClient)

// Construction
public:
	CMdiClient();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdiClient)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetBitmap(UINT nID);
	COLORREF SetBackColor(COLORREF nBackColor);
	virtual ~CMdiClient();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMdiClient)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBitmap*	m_pBmp;
	COLORREF	m_nBackColor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VNMDICLIENT_H__FC9EC8F2_8175_11D1_A16B_000000000000__INCLUDED_)
