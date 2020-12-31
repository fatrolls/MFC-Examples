#if !defined(AFX_GDIDOC_H__B4A122AC_2E77_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__B4A122AC_2E77_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#define PALETTE_SIZE		256
#define PALVERSION			0x300

class CGDIDoc : public CDocument
{
protected:
	CPalette m_palDraw;
	HGLOBAL m_hDIB;
	CGDIDoc();
	DECLARE_DYNCREATE(CGDIDoc)

public:
	HGLOBAL GetHDib(){return m_hDIB;}
	HGLOBAL ConvertDDBtoDIB(CBitmap *);
	DWORD GetColorTableSize(WORD);
	CPalette *GetPalette(){return &m_palDraw;}
	void GetCaptureBitmap(CBitmap *);
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
	afx_msg void OnCaptureGo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__B4A122AC_2E77_11D1_9C9A_444553540000__INCLUDED_)
