#if !defined(AFX_INIDOC_H__D1C586AC_3E3F_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_INIDOC_H__D1C586AC_3E3F_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CIniDoc : public CDocument
{
protected:
	CIniDoc();
	DECLARE_DYNCREATE(CIniDoc)

public:
	//{{AFX_VIRTUAL(CIniDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CIniDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CIniDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_INIDOC_H__D1C586AC_3E3F_11D1_9C9A_444553540000__INCLUDED_)
