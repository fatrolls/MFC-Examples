#if !defined(AFX_DDEDOC_H__747EBB2A_49F6_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DDEDOC_H__747EBB2A_49F6_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CDDESrvDoc : public CDocument
{
protected:
	CDDESrvDoc();
	DECLARE_DYNCREATE(CDDESrvDoc)

public:
	//{{AFX_VIRTUAL(CDDESrvDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CDDESrvDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CDDESrvDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DDEDOC_H__747EBB2A_49F6_11D1_9C9A_444553540000__INCLUDED_)
