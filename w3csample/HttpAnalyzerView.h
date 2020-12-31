// HttpAnalyzerView.h : interface of the CHttpAnalyzerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPANALYZERVIEW_H__A7BED3D8_14C0_4D38_ADCB_A2B0CBA2D9A8__INCLUDED_)
#define AFX_HTTPANALYZERVIEW_H__A7BED3D8_14C0_4D38_ADCB_A2B0CBA2D9A8__INCLUDED_

#include "w3c.h"
#include "HttpAnalyzerDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHttpAnalyzerView : public CHtmlView {
public:
	void doShow();
protected: // create from serialization only
	CHttpAnalyzerView();
	DECLARE_DYNCREATE(CHttpAnalyzerView)

// Attributes
public:
	CHttpAnalyzerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHttpAnalyzerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHttpAnalyzerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHttpAnalyzerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	W3Client *_pclient;
};

#ifndef _DEBUG  // debug version in HttpAnalyzerView.cpp
inline CHttpAnalyzerDoc* CHttpAnalyzerView::GetDocument()
   { return (CHttpAnalyzerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTTPANALYZERVIEW_H__A7BED3D8_14C0_4D38_ADCB_A2B0CBA2D9A8__INCLUDED_)
