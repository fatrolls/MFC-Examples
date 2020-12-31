#if !defined(AFX_DBDOC_H__B3AB0A79_13BE_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DBDOC_H__B3AB0A79_13BE_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CDBDoc : public CDocument
{
protected:
	CDBDoc();
	DECLARE_DYNCREATE(CDBDoc)

public:
	//{{AFX_VIRTUAL(CDBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CDBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CDBDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DBDOC_H__B3AB0A79_13BE_11D1_9C9A_444553540000__INCLUDED_)
