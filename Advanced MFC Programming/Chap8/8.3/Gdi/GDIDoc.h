#if !defined(AFX_GDIDOC_H__7CD207C9_1873_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__7CD207C9_1873_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIDoc : public CDocument
{
protected:
	CGDIDoc();
	DECLARE_DYNCREATE(CGDIDoc)

public:
	void AddPoint(CPoint pt){m_dwaPts.Add(pt.x); m_dwaPts.Add(pt.y);}
	int GetNumOfPts(){return m_dwaPts.GetSize()/2;}
	CPoint GetOnePt(int nID)
	{
		return CPoint(m_dwaPts.GetAt(nID*2), m_dwaPts.GetAt(nID*2+1));
	}
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
	CDWordArray m_dwaPts;
	//{{AFX_MSG(CGDIDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__7CD207C9_1873_11D1_9C9A_444553540000__INCLUDED_)
