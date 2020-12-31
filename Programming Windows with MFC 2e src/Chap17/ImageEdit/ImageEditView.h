// ImageEditView.h : interface of the CImageEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEEDITVIEW_H__9D77AEEC_AA14_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_IMAGEEDITVIEW_H__9D77AEEC_AA14_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImageEditView : public CScrollView
{
protected: // create from serialization only
	CImageEditView();
	DECLARE_DYNCREATE(CImageEditView)

// Attributes
public:
	CImageEditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageEditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageEditView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageEditView.cpp
inline CImageEditDoc* CImageEditView::GetDocument()
   { return (CImageEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEEDITVIEW_H__9D77AEEC_AA14_11D2_8E53_006008A82731__INCLUDED_)
