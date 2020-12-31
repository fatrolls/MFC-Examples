#if !defined(AFX_DBVIEW_H__B3AB0A7B_13BE_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DBVIEW_H__B3AB0A7B_13BE_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CDBView : public CFormView
{
protected:
	CDBView();
	DECLARE_DYNCREATE(CDBView)

public:
	//{{AFX_DATA(CDBView)
	enum{ IDD = IDD_DB_FORM };
	//}}AFX_DATA

public:
	CDBDoc* GetDocument();
	//{{AFX_VIRTUAL(CDBView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

public:
	virtual ~CDBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRect m_rectA;
	CRect m_rectB;
	CRect m_rectEdit;
	CRect m_rectStaticGrp;
	BOOL m_bSizeAvailable;
	//{{AFX_MSG(CDBView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg BOOL OnToolTipNotify(UINT, NMHDR *, LRESULT *);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CDBDoc* CDBView::GetDocument()
   { return (CDBDoc*)m_pDocument; }
#endif
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DBVIEW_H__B3AB0A7B_13BE_11D1_9C9A_444553540000__INCLUDED_)
