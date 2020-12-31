// DragEditView.h : interface of the CDragEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAGEDITVIEW_H__871E3CCE_6359_11D1_8251_444553540000__INCLUDED_)
#define AFX_DRAGEDITVIEW_H__871E3CCE_6359_11D1_8251_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDragEditView : public CView
{
protected: // create from serialization only
	CDragEditView();
	DECLARE_DYNCREATE(CDragEditView)

// Attributes
public:
	CDragEditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragEditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDragEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDragEditView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DragEditView.cpp
inline CDragEditDoc* CDragEditView::GetDocument()
   { return (CDragEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGEDITVIEW_H__871E3CCE_6359_11D1_8251_444553540000__INCLUDED_)
