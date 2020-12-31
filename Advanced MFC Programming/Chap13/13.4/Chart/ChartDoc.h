#if !defined(AFX_CHARTDOC_H__093F7922_3414_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CHARTDOC_H__093F7922_3414_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CChartDoc : public CDocument
{
protected:
	int m_nA;
	int m_nB;
	int m_nC;
	CChartDoc();
	DECLARE_DYNCREATE(CChartDoc)

public:
	void GetABC(int &nA, int &nB, int &nC){nA=m_nA; nB=m_nB; nC=m_nC;} 
	//{{AFX_VIRTUAL(CChartDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CChartDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CChartDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CHARTDOC_H__093F7922_3414_11D1_9C9A_444553540000__INCLUDED_)
