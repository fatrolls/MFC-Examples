// ex10bView.h : interface of the CEx10bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX10BVIEW_H__297A6603_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX10BVIEW_H__297A6603_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx10bView : public CScrollView
{
private:
	const CSize m_sizeEllipse;
	CPoint   m_pointTopLeft;
	BOOL     m_bCaptured;
	CSize    m_sizeOffset;
	CDC*     m_pdcMemory;
	CBitmap* m_pBitmap;

protected: // create from serialization only
	CEx10bView();
	DECLARE_DYNCREATE(CEx10bView)

// Attributes
public:
	CEx10bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx10bView)
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
	virtual ~CEx10bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx10bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex10bView.cpp
inline CEx10bDoc* CEx10bView::GetDocument()
   { return (CEx10bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX10BVIEW_H__297A6603_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
