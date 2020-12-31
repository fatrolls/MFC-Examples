#if !defined(AFX_MENUDOC_H__D7E0A2EB_F772_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MENUDOC_H__D7E0A2EB_F772_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CMenuDoc : public CDocument
{
protected:
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
	BOOL m_bPasteAvailable;
	BOOL m_bDataPasted;
	//{{AFX_MSG(CMenuDoc)
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MENUDOC_H__D7E0A2EB_F772_11D0_9C9A_444553540000__INCLUDED_)
