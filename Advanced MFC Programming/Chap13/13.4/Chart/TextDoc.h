#if !defined(AFX_TEXTDOC_H__9A773A61_342E_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_TEXTDOC_H__9A773A61_342E_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CTextDoc : public CDocument
{
protected:
	CTextDoc();
	DECLARE_DYNCREATE(CTextDoc)

public:
	//{{AFX_VIRTUAL(CTextDoc)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

public:
	virtual ~CTextDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CTextDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_TEXTDOC_H__9A773A61_342E_11D1_9C9A_444553540000__INCLUDED_)
