#if !defined(AFX_DOC_H__D1AB534A_4563_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DOC_H__D1AB534A_4563_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#define STYLE_ICON			0
#define STYLE_SMALLICON		1
#define STYLE_LIST			2
#define STYLE_REPORT		3

class CExplorerView;

class CExplorerDoc : public CDocument
{
protected:
	UINT m_uStyle;
	CExplorerDoc();
	DECLARE_DYNCREATE(CExplorerDoc)

public:
	CExplorerView *GetCExplorerView();
	void ChangePath();
	//{{AFX_VIRTUAL(CExplorerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CExplorerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CExplorerDoc)
	afx_msg void OnViewLargeIcons();
	afx_msg void OnViewList();
	afx_msg void OnViewSmallIcons();
	afx_msg void OnViewDetails();
	afx_msg void OnUpdateViewDetails(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewLargeIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewSmallIcons(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DOC_H__D1AB534A_4563_11D1_9C9A_444553540000__INCLUDED_)
