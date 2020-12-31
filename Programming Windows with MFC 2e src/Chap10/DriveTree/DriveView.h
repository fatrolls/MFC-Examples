// DriveTreeView.h : interface of the CDriveView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVETREEVIEW_H__090B382D_959D_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_DRIVETREEVIEW_H__090B382D_959D_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDriveView : public CTreeView
{
protected: // create from serialization only
	CDriveView();
	DECLARE_DYNCREATE(CDriveView)

// Attributes
public:
	CDriveTreeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriveView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDriveView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL AddDriveItem (LPCTSTR pszDrive);
	int AddDirectories (HTREEITEM hItem, LPCTSTR pszPath);
	void DeleteAllChildren (HTREEITEM hItem);
	void DeleteFirstChild (HTREEITEM hItem);
	CString GetPathFromItem (HTREEITEM hItem);
	BOOL SetButtonState (HTREEITEM hItem, LPCTSTR pszPath);
	int AddDrives ();
	CImageList m_ilDrives;
	//{{AFX_MSG(CDriveView)
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DriveTreeView.cpp
inline CDriveTreeDoc* CDriveView::GetDocument()
   { return (CDriveTreeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVETREEVIEW_H__090B382D_959D_11D2_8E53_006008A82731__INCLUDED_)
