#if !defined(AFX_MENUVIEW_H__D7E0A304_F772_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MENUVIEW_H__D7E0A304_F772_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CMenuView : public CView
{
protected:
	CMenuView();
	DECLARE_DYNCREATE(CMenuView)

public:
	CMenuDoc* GetDocument();
	//{{AFX_VIRTUAL(CMenuView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

public:
	virtual ~CMenuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CMenuView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CMenuDoc* CMenuView::GetDocument()
   { return (CMenuDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MENUVIEW_H__D7E0A304_F772_11D0_9C9A_444553540000__INCLUDED_)
