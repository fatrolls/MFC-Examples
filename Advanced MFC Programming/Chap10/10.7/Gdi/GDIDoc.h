#if !defined(AFX_GDIDOC_H__A9BED22A_2386_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__A9BED22A_2386_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#define BMP_FORMAT_NONE			0
#define BMP_FORMAT_MONO			1
#define BMP_FORMAT_16COLOR		2
#define BMP_FORMAT_256COLOR		3
#define BMP_FORMAT_24BIT		4

class CGDIDoc : public CDocument
{
protected:
	CPalette m_palDraw;
	HGLOBAL m_hDIB;
	int m_nBmpFormat;

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
	afx_msg void OnConvert256toRGB();
	afx_msg void OnUpdateConvert256toRGB(CCmdUI* pCmdUI);
	afx_msg void OnConvertRGBto256();
	afx_msg void OnUpdateConvertRGBto256(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__A9BED22A_2386_11D1_9C9A_444553540000__INCLUDED_)
