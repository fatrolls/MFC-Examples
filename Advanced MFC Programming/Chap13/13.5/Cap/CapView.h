#if !defined(AFX_CAPVIEW_H__EBE87B4C_34BD_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CAPVIEW_H__EBE87B4C_34BD_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CCapView : public CView
{
protected:
	CCapView();
	DECLARE_DYNCREATE(CCapView)

public:
	CCapDoc* GetDocument();
	//{{AFX_VIRTUAL(CCapView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CCapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CCapView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CCapDoc* CCapView::GetDocument()
   { return (CCapDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CAPVIEW_H__EBE87B4C_34BD_11D1_9C9A_444553540000__INCLUDED_)
