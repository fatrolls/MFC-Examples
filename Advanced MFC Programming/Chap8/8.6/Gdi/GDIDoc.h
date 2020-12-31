#if !defined(AFX_GDIDOC_H__E61CF0FD_17B9_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__E61CF0FD_17B9_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIDoc : public CDocument
{
protected:
	CGDIDoc();
	DECLARE_DYNCREATE(CGDIDoc)

public:
	void AddRect(CRect rect){m_paRects.Add(new CRect(rect));}
	CRect *GetRect(int nID){return (CRect *)m_paRects.GetAt(nID);}
	int GetNumOfRects(){return m_paRects.GetSize();}
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
	CPtrArray m_paRects;
	//{{AFX_MSG(CGDIDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__E61CF0FD_17B9_11D1_9C9A_444553540000__INCLUDED_)
