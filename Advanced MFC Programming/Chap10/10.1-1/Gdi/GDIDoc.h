#if !defined(AFX_GDIDOC_H__A9BED22A_2386_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__A9BED22A_2386_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIDoc : public CDocument
{
protected:
	CBitmap m_bmpDraw;
	CGDIDoc();
	DECLARE_DYNCREATE(CGDIDoc)

public:
	CBitmap *GetBitmap(){return &m_bmpDraw;}
	//{{AFX_VIRTUAL(CGDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CGDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CGDIDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__A9BED22A_2386_11D1_9C9A_444553540000__INCLUDED_)
