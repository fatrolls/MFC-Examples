#if !defined(AFX_WPDOC_H__D065BD80_43C2_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_WPDOC_H__D065BD80_43C2_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CWordPadDoc : public CRichEditDoc
{
protected:
	CWordPadDoc();
	DECLARE_DYNCREATE(CWordPadDoc)

public:
	BOOL DoSave(LPCTSTR, BOOL);
	//{{AFX_VIRTUAL(CWordPadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem *CreateClientItem(REOBJECT *preo) const;

public:
	virtual ~CWordPadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CWordPadDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_WPDOC_H__D065BD80_43C2_11D1_9C9A_444553540000__INCLUDED_)
