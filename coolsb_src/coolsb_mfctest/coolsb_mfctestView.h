// coolsb_mfctestView.h : interface of the CCoolsb_mfctestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COOLSB_MFCTESTVIEW_H__9540A896_BAEB_47BA_92D0_949362F82F5F__INCLUDED_)
#define AFX_COOLSB_MFCTESTVIEW_H__9540A896_BAEB_47BA_92D0_949362F82F5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCoolsb_mfctestView : public CView
{
protected: // create from serialization only
	CCoolsb_mfctestView();
	DECLARE_DYNCREATE(CCoolsb_mfctestView)

// Attributes
public:
	CCoolsb_mfctestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolsb_mfctestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCoolsb_mfctestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	int nVScrollMax, nVScrollPos, nVScrollPage;
	int nHScrollMax, nHScrollPos, nHScrollPage;
	int nHNumLines;
	int nVNumLines;

	int xChar, yChar;

	void SetupScrollbars();

// Generated message map functions
protected:
	//{{AFX_MSG(CCoolsb_mfctestView)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in coolsb_mfctestView.cpp
inline CCoolsb_mfctestDoc* CCoolsb_mfctestView::GetDocument()
   { return (CCoolsb_mfctestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLSB_MFCTESTVIEW_H__9540A896_BAEB_47BA_92D0_949362F82F5F__INCLUDED_)
