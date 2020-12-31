#if !defined(AFX_DOC_H__D1AB534A_4563_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DOC_H__D1AB534A_4563_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CExplorerDoc : public CDocument
{
protected:
	CExplorerDoc();
	DECLARE_DYNCREATE(CExplorerDoc)

public:
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DOC_H__D1AB534A_4563_11D1_9C9A_444553540000__INCLUDED_)
