#if !defined(AFX_SPWDOC_H__D3F202D8_FC3A_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_SPWDOC_H__D3F202D8_FC3A_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CSpwDoc : public CDocument
{
protected:
	CSpwDoc();
	DECLARE_DYNCREATE(CSpwDoc)

public:
	//{{AFX_VIRTUAL(CSpwDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CSpwDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CSpwDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_SPWDOC_H__D3F202D8_FC3A_11D0_9C9A_444553540000__INCLUDED_)
