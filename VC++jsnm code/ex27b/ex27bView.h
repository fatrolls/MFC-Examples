// ex27bView.h : interface of the CEx27bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX27BVIEW_H__1EAAB6E1_6011_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX27BVIEW_H__1EAAB6E1_6011_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define CF_OBJECTDESCRIPTOR	"Object Descriptor"
#define CF_EMBEDDEDOBJECT "Embedded Object"
#define SETFORMATETC(fe, cf, asp, td, med, li)   \
	((fe).cfFormat=cf, \
	 (fe).dwAspect=asp, \
	 (fe).ptd=td, \
	 (fe).tymed=med, \
	 (fe).lindex=li)

/////////////////////////////////////////////////////////////////////////////
class CEx27bView : public CScrollView
{
public:
	CLIPFORMAT m_cfObjDesc;
	CLIPFORMAT m_cfEmbedded;
	CSize m_sizeTotal;  // document size
	CRectTracker m_tracker;
	CRect m_rectTracker; // logical coords
protected: // create from serialization only
	CEx27bView();
	DECLARE_DYNCREATE(CEx27bView)

// Attributes
public:
	CEx27bDoc* GetDocument();

private:
	void GetSize();
	void SetNames();
	void SetViewAdvise();
	BOOL MakeMetafilePict(COleDataSource* pSource);
	COleDataSource* SaveObject();
	BOOL DoPasteObject(COleDataObject* pDataObject);
	BOOL DoPasteObjectDescriptor(COleDataObject* pDataObject);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx27bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx27bView)
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyto();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditPastefrom();
	afx_msg void OnEditInsertobject();
	afx_msg void OnUpdateEditInsertobject(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex27bView.cpp
inline CEx27bDoc* CEx27bView::GetDocument()
   { return (CEx27bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations 
//  immediately before the previous line.

#endif 
// !defined(AFX_EX27BVIEW_H__1EAAB6E1_6011_11D0_848F_00400526305B__INCLUDED_)
