#if !defined(AFX_WPVIEW_H__D065BD82_43C2_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_WPVIEW_H__D065BD82_43C2_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CWordPadCntrItem;

class CWordPadView : public CRichEditView
{
protected:
	CWordPadView();
	DECLARE_DYNCREATE(CWordPadView)

public:
	CWordPadDoc* GetDocument();
	//{{AFX_VIRTUAL(CWordPadView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CWordPadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CWordPadView)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CWordPadDoc* CWordPadView::GetDocument()
   { return (CWordPadDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_WPVIEW_H__D065BD82_43C2_11D1_9C9A_444553540000__INCLUDED_)
