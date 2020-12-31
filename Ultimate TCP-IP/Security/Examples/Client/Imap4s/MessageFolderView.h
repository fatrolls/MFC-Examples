#if !defined(AFX_MESSAGEFOLDERVIEW_H__1FE0A7E5_27E9_11D3_B75D_00203596449E__INCLUDED_)
#define AFX_MESSAGEFOLDERVIEW_H__1FE0A7E5_27E9_11D3_B75D_00203596449E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageFolderView.h : header file
//

class CIMAPClientDoc;
/////////////////////////////////////////////////////////////////////////////
// CMessageFolderView view

#pragma warning ( disable : 4511 4512 ) // VC6 level 4 - copy ctor & op=

class CMessageFolderView : public CTreeView
{
protected:
	CMessageFolderView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMessageFolderView)

// Attributes
public:
	void BuildFolderList();
	const CString& GetSelectedFolder() const { return m_sSelectedFolder; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageFolderView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
		CIMAPClientDoc* GetDocument() const { return (CIMAPClientDoc*)(m_pDocument); }

// Implementation
protected:
	virtual ~CMessageFolderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	HTREEITEM m_hRootItem;
	CString m_sSelectedFolder;
	static const LPCTSTR m_lpFoldersName;

private:
	void AddChildFolders(HTREEITEM hParentItem);
	void CreateFolder(LPCSTR lpFolder);
	void BuildSelectedFolderString(HTREEITEM hItem);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMessageFolderView)
	afx_msg void OnSingleClickItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( disable : 4511 4512 ) // VC6 level 4 - copy ctor & op=

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEFOLDERVIEW_H__1FE0A7E5_27E9_11D3_B75D_00203596449E__INCLUDED_)
