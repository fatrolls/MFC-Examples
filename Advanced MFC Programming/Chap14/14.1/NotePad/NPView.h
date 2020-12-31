#if !defined(AFX_NPVIEW_H__7B48640C_43AD_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_NPVIEW_H__7B48640C_43AD_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CNotePadView : public CEditView
{
protected:
	CNotePadView();
	DECLARE_DYNCREATE(CNotePadView)

public:
	CNotePadDoc* GetDocument();

	//{{AFX_VIRTUAL(CNotePadView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CNotePadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CNotePadView)
	afx_msg void OnEditSelectall();
	afx_msg void OnEditTimedate();
	afx_msg void OnEditDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG 
inline CNotePadDoc* CNotePadView::GetDocument()
   { return (CNotePadDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_NPVIEW_H__7B48640C_43AD_11D1_9C9A_444553540000__INCLUDED_)
