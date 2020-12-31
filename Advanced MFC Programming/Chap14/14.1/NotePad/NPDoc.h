#if !defined(AFX_NPDOC_H__7B48640A_43AD_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_NPDOC_H__7B48640A_43AD_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif


class CNotePadDoc : public CDocument
{
protected:
	CNotePadDoc();
	DECLARE_DYNCREATE(CNotePadDoc)

public:
	//{{AFX_VIRTUAL(CNotePadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CNotePadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CNotePadDoc)
	afx_msg void OnSearchFind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_NPDOC_H__7B48640A_43AD_11D1_9C9A_444553540000__INCLUDED_)
