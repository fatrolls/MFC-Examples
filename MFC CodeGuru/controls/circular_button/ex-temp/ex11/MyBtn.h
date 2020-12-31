#if !defined(AFX_MYBTN_H__289CB976_3A41_11D1_9774_004033298A13__INCLUDED_)
#define AFX_MYBTN_H__289CB976_3A41_11D1_9774_004033298A13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyBtn window

class CMyBtn : public CButton
{
// Construction
public:
	CMyBtn();

// Attributes
public:

// Operations
public:
	void DrawWhiteText(CDC* pDC, CRect* pRect, CString& text );
	void GradientFill (CDC* pDC, CRect* pRect);
	void SetRound(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyBtn)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyBtn)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBTN_H__289CB976_3A41_11D1_9774_004033298A13__INCLUDED_)
