// ex18bView.h : interface of the CEx18bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX18BVIEW_H__870AB903_89D8_11D0_8FE4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX18BVIEW_H__870AB903_89D8_11D0_8FE4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx18bView : public CView
{
protected: // create from serialization only
	CEx18bView();
	DECLARE_DYNCREATE(CEx18bView)

// Attributes
public:
	CEx18bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx18bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nPage;
	virtual ~CEx18bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx18bView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PrintPageHeader(CDC* pDC);
	void PrintPageFooter(CDC* pDC);
};

#ifndef _DEBUG  // debug version in ex18bView.cpp
inline CEx18bDoc* CEx18bView::GetDocument()
   { return (CEx18bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX18BVIEW_H__870AB903_89D8_11D0_8FE4_00C04FC2A0C2__INCLUDED_)
