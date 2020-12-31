#if !defined(AFX_MENUDOC_H__D7E0A2EB_F772_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MENUDOC_H__D7E0A2EB_F772_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CMenuDoc : public CDocument
{
protected:
	CMenu m_menuSub;
	CBitmap m_bmpCheck;
	CBitmap m_bmpUnCheck;
	BOOL m_bSubMenuOn;
	CMenuDoc();
	DECLARE_DYNCREATE(CMenuDoc)

public:
	//{{AFX_VIRTUAL(CMenuDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CMenuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CMenuDoc)
	afx_msg void OnEditInsertDynamicMenu();
	afx_msg void OnUpdateEditInsertDynamicMenu(CCmdUI* pCmdUI);
	afx_msg void OnEditDeleteDynamicMenu();
	afx_msg void OnUpdateEditDeleteDynamicMenu(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnPopUpItem1();
	afx_msg void OnPopUpItem2();
	afx_msg void OnPopUpItem3();
	afx_msg void OnPopUpItem4();
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MENUDOC_H__D7E0A2EB_F772_11D0_9C9A_444553540000__INCLUDED_)
