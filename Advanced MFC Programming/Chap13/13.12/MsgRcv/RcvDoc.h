#if !defined(AFX_RCVDOC_H__D649DA77_3EFC_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_RCVDOC_H__D649DA77_3EFC_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CMsgRcvDoc : public CDocument
{
protected:
	CMsgRcvDoc();
	DECLARE_DYNCREATE(CMsgRcvDoc)

public:
	//{{AFX_VIRTUAL(CMsgRcvDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CMsgRcvDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CMsgRcvDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_RCVDOC_H__D649DA77_3EFC_11D1_9C9A_444553540000__INCLUDED_)
