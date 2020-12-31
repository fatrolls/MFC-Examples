// fanView.h : interface of the CFanView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FANVIEW_H__477B0C5D_6FB8_11D3_9803_0088CC094230__INCLUDED_)
#define AFX_FANVIEW_H__477B0C5D_6FB8_11D3_9803_0088CC094230__INCLUDED_

//#include "WaitRedraw.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct point
{
	int x;
	int y;
};
class CFanView : public CView
{
protected: // create from serialization only
	CFanView();
	DECLARE_DYNCREATE(CFanView)

// Attributes
public:
	CFanDoc* GetDocument();
	int m_nMaxX,m_nMaxY;
	HBITMAP m_hBit;
	HDC m_memdc;
	HBRUSH m_hBrush;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFanView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CFanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	COLORREF tempcolor,color[20][10];
	void myDraw();
	int time;
	void Star();
	int count;
	void Isover();
//	CWaitRedraw wait;
	int dop();
	int Isbottom();
	int Isout(int w);
	int round(int as);
	void clean(int b);
	int index;
	int R;
	int L;
	int H;
	int cor[20][10];
	int J;
	CBitmap* m_pbmpContents; // to get a faster update if flickerfree is on
	int K;
	BOOL flag,flag2;
	int Y;
	int X;

	int k;
	
	point aa[4],bb[4],dd[4];
	//{{AFX_MSG(CFanView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void On1();
	afx_msg void OnUpdate1(CCmdUI* pCmdUI);
	afx_msg void On2();
	afx_msg void OnUpdate2(CCmdUI* pCmdUI);
	afx_msg void On3();
	afx_msg void OnUpdate3(CCmdUI* pCmdUI);
	afx_msg void OnStar();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in fanView.cpp
inline CFanDoc* CFanView::GetDocument()
   { return (CFanDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FANVIEW_H__477B0C5D_6FB8_11D3_9803_0088CC094230__INCLUDED_)
