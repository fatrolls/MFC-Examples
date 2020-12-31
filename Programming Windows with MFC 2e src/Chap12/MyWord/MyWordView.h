// MyWordView.h : interface of the CMyWordView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYWORDVIEW_H__C85C908D_A154_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_MYWORDVIEW_H__C85C908D_A154_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyWordCntrItem;

class CMyWordView : public CRichEditView
{
protected: // create from serialization only
	CMyWordView();
	DECLARE_DYNCREATE(CMyWordView)

// Attributes
public:
	CMyWordDoc* GetDocument();

// Operations
public:
    void GetFontInfo (LPTSTR pszFaceName, int& nSize);
    void ChangeFont (LPCTSTR pszFaceName);
    void ChangeFontSize (int nSize);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWordView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyWordView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyWordView)
	afx_msg void OnDestroy();
	afx_msg void OnCharBold();
	afx_msg void OnCharItalic();
	afx_msg void OnCharUnderline();
	afx_msg void OnParaLeft();
	afx_msg void OnParaCenter();
	afx_msg void OnParaRight();
	afx_msg void OnUpdateCharBold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCharItalic(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCharUnderline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParaLeft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParaCenter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParaRight(CCmdUI* pCmdUI);
	//}}AFX_MSG
    afx_msg void OnUpdateLineNumber (CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyWordView.cpp
inline CMyWordDoc* CMyWordView::GetDocument()
   { return (CMyWordDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWORDVIEW_H__C85C908D_A154_11D2_8E53_006008A82731__INCLUDED_)
