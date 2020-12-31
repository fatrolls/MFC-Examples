#if !defined(AFX_GDIDOC_H__1010F3AA_28F5_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__1010F3AA_28F5_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#define PALETTE_SIZE		256
#define COLOR_BUTTON_NUM	20

#define TOOL_FREESEL		0
#define TOOL_RECTSEL		1
#define TOOL_PEN			2
#define TOOL_LINE			3

#define TOOL_HEAD_ID		ID_BUTTON_FREESEL	
#define TOOL_TAIL_ID		ID_BUTTON_LINE		

#define WIDTHBYTES(bits) ((((bits)+31)/32)*4)

class CGDIView;

class CGDIDoc : public CDocument
{
protected:
	int m_nRatio;
	int m_nFgdIndex;
	int m_nBgdIndex;
	int m_nCurrentTool;
	LPBYTE m_lpBits;
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
	int GetFgdIndex(){return m_nFgdIndex;}
	int GetBgdIndex(){return m_nBgdIndex;}
	int GetCurrentTool(){return m_nCurrentTool;}
	BOOL GetGridOn(){return m_bGridOn;}
	HGLOBAL CreateCopyCutDIB();
	void SetLPBits(LPBYTE lpBits){m_lpBits=lpBits;}
	void SetFgdIndex(int nFgdIndex){m_nFgdIndex=nFgdIndex;}
	void SetBgdIndex(int nBgdIndex){m_nBgdIndex=nBgdIndex;}
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
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnDrawTool(UINT);
	afx_msg void OnUpdateDrawTool(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__1010F3AA_28F5_11D1_9C9A_444553540000__INCLUDED_)
