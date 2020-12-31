// MenuDoc.h : interface of the CMenuDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUDOC_H__D7E0A2EB_F772_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MENUDOC_H__D7E0A2EB_F772_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMenuDoc : public CDocument
{
protected: // create from serialization only
	CMenu m_menuSub;
	BOOL m_bSubMenuOn;
	CMenuDoc();
	DECLARE_DYNCREATE(CMenuDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMenuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CMenuDoc)
	afx_msg void OnEditInsertDynamicMenu();
	afx_msg void OnUpdateEditInsertDynamicMenu(CCmdUI* pCmdUI);
	afx_msg void OnEditDeleteDynamicMenu();
	afx_msg void OnUpdateEditDeleteDynamicMenu(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUDOC_H__D7E0A2EB_F772_11D0_9C9A_444553540000__INCLUDED_)
