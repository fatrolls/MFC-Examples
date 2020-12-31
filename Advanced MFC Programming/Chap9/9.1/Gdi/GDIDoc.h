#if !defined(AFX_GDIDOC_H__A10707E1_1ACF_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__A10707E1_1ACF_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIDoc : public CDocument
{
protected:
	CGDIDoc();
	DECLARE_DYNCREATE(CGDIDoc)
	CFont m_fontDraw;
	COLORREF m_colorFont;
	BOOL m_bTransparentBgd;

public:
	//{{AFX_VIRTUAL(CGDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	CFont *GetCurrentFont(){return &m_fontDraw;}
	COLORREF GetFontColor(){return m_colorFont;}
	BOOL GetBgdStyle(){return m_bTransparentBgd;}
	virtual ~CGDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CGDIDoc)
	afx_msg void OnFontSelect();
	afx_msg void OnFontStyle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__A10707E1_1ACF_11D1_9C9A_444553540000__INCLUDED_)
