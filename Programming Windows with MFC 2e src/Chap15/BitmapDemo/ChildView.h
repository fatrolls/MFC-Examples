// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__D71EF54B_A6FE_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_CHILDVIEW_H__D71EF54B_A6FE_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	void DoGradientFill (CDC* pDC, LPRECT pRect);
	CPalette m_palette;
	CMaskedBitmap m_bitmap;
	BOOL m_bDrawOpaque;
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnOptionsDrawOpaque();
	afx_msg void OnOptionsDrawTransparent();
	afx_msg void OnUpdateOptionsDrawOpaque(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsDrawTransparent(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__D71EF54B_A6FE_11D2_8E53_006008A82731__INCLUDED_)
