#if !defined(AFX_INIVIEW_H__D1C586AE_3E3F_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_INIVIEW_H__D1C586AE_3E3F_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CIniView : public CView
{
protected:
	CIniView();
	DECLARE_DYNCREATE(CIniView)

public:
	CIniDoc* GetDocument();
	//{{AFX_VIRTUAL(CIniView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CIniView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CIniView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CIniDoc* CIniView::GetDocument()
   { return (CIniDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_INIVIEW_H__D1C586AE_3E3F_11D1_9C9A_444553540000__INCLUDED_)
