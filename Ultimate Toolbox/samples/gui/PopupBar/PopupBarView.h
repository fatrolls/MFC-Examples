// PopupBarView.h : interface of the CPopupBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POPUPBARVIEW_H__95493CEF_F252_11D1_B475_B0D808C10000__INCLUDED_)
#define AFX_POPUPBARVIEW_H__95493CEF_F252_11D1_B475_B0D808C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define ID_EDGE_MARGIN		20
#define ID_BORDER_MARGIN	7
#define ID_TEXT_MARGIN		10

class CPopupBarView : public CView
{
protected: // create from serialization only
	CPopupBarView();
	DECLARE_DYNCREATE(CPopupBarView)

// Attributes
public:
	CPopupBarDoc* GetDocument();

// Operations
public:

protected:
	void CalculateRects();
	void DrawBorder(CDC* pDC, CRect rect, int nBorderStyle, int nLineStyle);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupBarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPopupBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRect m_rectWholeSquare;

	CRect m_rectFirstSquare;
	CRect m_rectSecondSquare;
	CRect m_rectThirdSquare;
	CRect m_rectFourthSquare;

	CSize m_textSize;

// Generated message map functions
protected:
	//{{AFX_MSG(CPopupBarView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PopupBarView.cpp
inline CPopupBarDoc* CPopupBarView::GetDocument()
   { return (CPopupBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPBARVIEW_H__95493CEF_F252_11D1_B475_B0D808C10000__INCLUDED_)
