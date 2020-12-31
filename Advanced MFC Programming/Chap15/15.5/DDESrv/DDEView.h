#if !defined(AFX_DDEVIEW_H__747EBB2C_49F6_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DDEVIEW_H__747EBB2C_49F6_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CDDESrvView : public CEditView
{
protected:
	CDDESrvView();
	DECLARE_DYNCREATE(CDDESrvView)

public:
	CDDESrvDoc* GetDocument();
	//{{AFX_VIRTUAL(CDDESrvView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

public:
	virtual ~CDDESrvView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CDDESrvView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CDDESrvDoc* CDDESrvView::GetDocument()
   { return (CDDESrvDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DDEVIEW_H__747EBB2C_49F6_11D1_9C9A_444553540000__INCLUDED_)
