#if !defined(AFX_OUTLOOKLISTVIEW_H__DA7AA839_2C67_11D2_88E3_0080C859A484__INCLUDED_)
#define AFX_OUTLOOKLISTVIEW_H__DA7AA839_2C67_11D2_88E3_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutlookListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutlookListView view

class COutlookListView : public CListView
{
protected:
	COutlookListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COutlookListView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COutlookListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList m_ilList;

	// Generated message map functions
protected:
	//{{AFX_MSG(COutlookListView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKLISTVIEW_H__DA7AA839_2C67_11D2_88E3_0080C859A484__INCLUDED_)
