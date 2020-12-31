#if !defined(AFX_CAPDOC_H__EBE87B4A_34BD_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CAPDOC_H__EBE87B4A_34BD_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CCapDoc : public CDocument
{
protected:
	CCapDoc();
	DECLARE_DYNCREATE(CCapDoc)

public:
	//{{AFX_VIRTUAL(CCapDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CCapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CCapDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CAPDOC_H__EBE87B4A_34BD_11D1_9C9A_444553540000__INCLUDED_)
