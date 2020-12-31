#if !defined(AFX_GDIDOC_H__1010F3AA_28F5_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__1010F3AA_28F5_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#define PALETTE_SIZE		256
#define COLOR_BUTTON_NUM	20

class CGDIView;

class CGDIDoc : public CDocument
{
protected:
	int m_nRatio;
	BOOL m_bGridOn;
	CPalette m_palDraw;
	HBITMAP m_hDIB;
	CGDIDoc();
	DECLARE_DYNCREATE(CGDIDoc)

public:
	CPalette *GetPalette(){return &m_palDraw;}
	HBITMAP GetHDib(){return m_hDIB;}
	DWORD GetColorTableSize(WORD);
	int GetRatio(){return m_nRatio;}
	BOOL GetGridOn(){return m_bGridOn;}
	CGDIView *GetCGDIView();
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
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnGrid();
	afx_msg void OnUpdateGrid(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__1010F3AA_28F5_11D1_9C9A_444553540000__INCLUDED_)
