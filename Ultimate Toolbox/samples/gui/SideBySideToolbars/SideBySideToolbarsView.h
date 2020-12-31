// SideBySideToolbarsView.h : interface of the CSideBySideToolbarsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIDEBYSIDETOOLBARSVIEW_H__09162242_5044_44AB_A504_766AC6324B49__INCLUDED_)
#define AFX_SIDEBYSIDETOOLBARSVIEW_H__09162242_5044_44AB_A504_766AC6324B49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSideBySideToolbarsView : public CView
{
protected: // create from serialization only
	CSideBySideToolbarsView();
	DECLARE_DYNCREATE(CSideBySideToolbarsView)

// Attributes
public:
	CSideBySideToolbarsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSideBySideToolbarsView)
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
	virtual ~CSideBySideToolbarsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSideBySideToolbarsView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SideBySideToolbarsView.cpp
inline CSideBySideToolbarsDoc* CSideBySideToolbarsView::GetDocument()
   { return (CSideBySideToolbarsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIDEBYSIDETOOLBARSVIEW_H__09162242_5044_44AB_A504_766AC6324B49__INCLUDED_)
