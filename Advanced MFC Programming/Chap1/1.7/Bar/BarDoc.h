#if !defined(AFX_BARDOC_H__C0A99CF7_ED67_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_BARDOC_H__C0A99CF7_ED67_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CBarDoc : public CDocument
{
protected:
	CBarDoc();
	DECLARE_DYNCREATE(CBarDoc)

public:
	//{{AFX_VIRTUAL(CBarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CBarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	UINT m_uCurrentBtn;
	//{{AFX_MSG(CBarDoc)
	//}}AFX_MSG
	afx_msg void OnButtons(UINT);
	afx_msg void OnUpdateButtons(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_BARDOC_H__C0A99CF7_ED67_11D0_9C9A_444553540000__INCLUDED_)
