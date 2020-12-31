// VirtualListView.h : interface of the CVirtualListView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUALLISTVIEW_H__A1E706A2_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
#define AFX_VIRTUALLISTVIEW_H__A1E706A2_5F36_11D1_959E_D1A30ED05A05__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CVirtualListView : public CListView
{
protected: // create from serialization only
	CVirtualListView();
	DECLARE_DYNCREATE(CVirtualListView)

// Attributes
public:
	CVirtualListDoc* GetDocument();
	virtual CDaoRecordset* GetRecordSet();
	virtual long GetRecordCount();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVirtualListView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVirtualListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList* m_pImageList;
// Generated message map functions
protected:
	//{{AFX_MSG(CVirtualListView)
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VirtualListView.cpp
inline CVirtualListDoc* CVirtualListView::GetDocument()
   { return (CVirtualListDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIRTUALLISTVIEW_H__A1E706A2_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
