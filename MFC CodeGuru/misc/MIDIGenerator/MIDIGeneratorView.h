// MIDIGeneratorView.h : interface of the CMIDIGeneratorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDIGENERATORVIEW_H__0892C6DD_841E_11D1_A3FC_000000000000__INCLUDED_)
#define AFX_MIDIGENERATORVIEW_H__0892C6DD_841E_11D1_A3FC_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMIDIGeneratorView : public CView
{
protected: // create from serialization only
	CMIDIGeneratorView();
	DECLARE_DYNCREATE(CMIDIGeneratorView)

// Attributes
public:
	CMIDIGeneratorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIDIGeneratorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMIDIGeneratorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMIDIGeneratorView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MIDIGeneratorView.cpp
inline CMIDIGeneratorDoc* CMIDIGeneratorView::GetDocument()
   { return (CMIDIGeneratorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDIGENERATORVIEW_H__0892C6DD_841E_11D1_A3FC_000000000000__INCLUDED_)
