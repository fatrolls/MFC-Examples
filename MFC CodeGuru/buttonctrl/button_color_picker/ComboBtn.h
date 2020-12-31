// colorctl.h : header file
//

#ifndef __COLORCTL_H
#define __COLORCTL_H

/////////////////////////////////////////////////////////////////////////////
// CWndCombo window

class CWndCombo : public CWnd
{
// Construction
public:
	CWndCombo();

// Attributes
public:

protected:
	CSize 			m_sizeGrid, m_sizeBtn;
	UINT			m_nBitmapIDResource;
	CWnd 			*m_pParent;
	COLORREF		m_rgbBkColor;
	int 			m_iSelectedItem, m_iNbImages;
	CBitmap			m_bmImage;
	CFont			m_font;
	CStringArray 	m_lstTextItems;
	
// Operations
public:
	BOOL Create(int x, int y, CSize sizeGrid, CSize sizeBtn, CWnd * pParent, CString sTextItems = "");
	BOOL Create(int x, int y, CSize sizeGrid, UINT nBitmapIDResource, int iNbImages, 
				CWnd * pParent, CString sTextItems = "");

	BOOL 		IsCreate() { return m_hWnd != NULL; }
	void 		SetBkColor(COLORREF rgbBkColor) { m_rgbBkColor = rgbBkColor; }
	COLORREF 	GetBkColor() { return m_rgbBkColor; }
	int 		GetItem(CPoint point, CRect * pRect);
	void		DrawBtnFace(CDC * pDC, CRect rect, long lItem);		

	void		SetSelectedItem(int iItem) { m_iSelectedItem = iItem; }

protected:
	CSize	UpdateTextItems(CString sTextItems);

// Overrides
public:
	COLORREF GetColor(int iIndex);	

// Implementation
public:
	virtual ~CWndCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndCombo)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CButtonCombo window

class CButtonCombo : public CWnd
{
// Construction
public:
	CButtonCombo();

// Attributes
public:
    
protected:
	CWnd 		*m_pParent;
	UINT		m_nID;
	CWndCombo	m_wndColor;  
	BOOL		m_bLeftBtnDown, m_bRightBtnDown, m_bLeftBtnOut;	
	long 		m_lItem;
	int			m_iRealItem;
		
// Operations
public:
	BOOL Create(CRect rect, CSize sizeGrid, CSize sizeBtn, CWnd * pParent, 
				UINT nID, CString sTextItems = "");
	BOOL Create(CRect rect, CSize sizeGrid, UINT nBitmapIDResource, int iNbImages, 
				CWnd * pParent, UINT nID, CString sTextItems = "");

	void DrawArrow(CDC * pDC, CRect * pRect);
	void OnItemSelected(long lItem, int iRealItem);
	void UnpressRightButton();
	
	long GetSelectedItem() { return m_lItem; }
	
protected:
	void 	DrawDisabled( CDC * pDC, const CRect & rc ); 

// Overrides
public:

// Implementation
public:
	virtual ~CButtonCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonCombo)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif

