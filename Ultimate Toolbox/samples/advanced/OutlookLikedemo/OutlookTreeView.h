#if !defined(AFX_OUTLOOKTREEVIEW_H__DA7AA838_2C67_11D2_88E3_0080C859A484__INCLUDED_)
#define AFX_OUTLOOKTREEVIEW_H__DA7AA838_2C67_11D2_88E3_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutlookTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutlookTreeView view

class COutlookTreeView : public CTreeView
{
protected:
	COutlookTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COutlookTreeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COutlookTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList m_ilTree;

	// Generated message map functions
protected:
	//{{AFX_MSG(COutlookTreeView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKTREEVIEW_H__DA7AA838_2C67_11D2_88E3_0080C859A484__INCLUDED_)
