#if !defined(AFX_ONCEDOC_H__21AF860C_30FF_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_ONCEDOC_H__21AF860C_30FF_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class COnceDoc : public CDocument
{
protected:
	COnceDoc();
	DECLARE_DYNCREATE(COnceDoc)

public:
	//{{AFX_VIRTUAL(COnceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~COnceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(COnceDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_ONCEDOC_H__21AF860C_30FF_11D1_9C9A_444553540000__INCLUDED_)
