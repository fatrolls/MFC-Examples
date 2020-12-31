#if !defined(AFX_GDIDOC_H__A9BED22A_2386_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__A9BED22A_2386_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIDoc : public CDocument
{
protected:
	CPalette m_palDraw;
	HGLOBAL m_hDIB;

	CGDIDoc();
	DECLARE_DYNCREATE(CGDIDoc)

public:
	CPalette *GetPalette(){return &m_palDraw;}
	HGLOBAL GetHDib(){return m_hDIB;}
	DWORD GetColorTableSize(WORD);
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
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__A9BED22A_2386_11D1_9C9A_444553540000__INCLUDED_)
