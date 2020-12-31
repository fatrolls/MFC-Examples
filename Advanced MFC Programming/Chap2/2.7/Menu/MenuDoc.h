#if !defined(AFX_MENUDOC_H__8B64D7AA_F9D0_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MENUDOC_H__8B64D7AA_F9D0_11D0_9C9A_444553540000__INCLUDED_

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
	//{{AFX_MSG(CMenuDoc)
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MENUDOC_H__8B64D7AA_F9D0_11D0_9C9A_444553540000__INCLUDED_)
