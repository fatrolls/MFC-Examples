#if !defined(AFX_RESOURCETREE_H__0E66E493_ADE2_11D1_8359_00A0244DBC26__INCLUDED_)
#define AFX_RESOURCETREE_H__0E66E493_ADE2_11D1_8359_00A0244DBC26__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ResourceTree.h : header file
//
#define ILI_CLOSED_FOLDER 3
#define ILI_OPEN_FOLDER   4
class PERsrcTbl;
/////////////////////////////////////////////////////////////////////////////
// CResourceTree view 

class CResourceTree : public CTreeView
{
protected:
	CResourceTree();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CResourceTree)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceTree)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CResourceTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	CImageList m_imglFolders;
	//{{AFX_MSG(CResourceTree)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddResourceInst(HTREEITEM hitem);
	void DeleteAllChildren(HTREEITEM hParent);
	void DeleteFirstChild(HTREEITEM hParent);
	BOOL InitTree(PERsrcTbl* RsrcTbl);


};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESOURCETREE_H__0E66E493_ADE2_11D1_8359_00A0244DBC26__INCLUDED_)
