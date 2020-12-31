// ex10aView.h : interface of the CEx10aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX10AVIEW_H__297A65ED_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX10AVIEW_H__297A65ED_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx10aView : public CScrollView
{
protected: // create from serialization only
	CEx10aView();
	DECLARE_DYNCREATE(CEx10aView)

// Attributes
public:
	CEx10aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx10aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx10aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx10aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSize m_sizeDest;
	CSize m_sizeSource;
	CBitmap* m_pBitmap;
	CDC* m_pdcMemory;
};

#ifndef _DEBUG  // debug version in ex10aView.cpp
inline CEx10aDoc* CEx10aView::GetDocument()
   { return (CEx10aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX10AVIEW_H__297A65ED_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
