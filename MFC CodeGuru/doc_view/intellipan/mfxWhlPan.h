#if !defined(AFX_MFXWHLPAN_H__4E9C2711_CFCD_11D1_87BA_400011900025__INCLUDED_)
#define AFX_MFXWHLPAN_H__4E9C2711_CFCD_11D1_87BA_400011900025__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// mfxWhlPan.h : header file
//

//Enumerations for intellimouse support.
enum MfxDirectionType {
	MFX_UP               = 1,
	MFX_LEFT             = 2,
	MFX_DOWN             = 3,
	MFX_RIGHT            = 4,
	MFX_PGDOWN           = 5,
	MFX_PGUP             = 6,
	MFX_TOP              = 7,
	MFX_BOTTOM           = 8,
	MFX_MOSTLEFT         = 9,
	MFX_MOSTRIGHT        = 10,
	MFX_TOPLEFT          = 11,
	MFX_BOTTOMRIGHT      = 12,
};

void MfxTrackAutoPan(CWnd* pParentWnd);

/////////////////////////////////////////////////////////////////////////////
// CWheelWnd window

class CWheelWnd : public CWnd
{
// Construction
public:
	CWheelWnd();
	virtual ~CWheelWnd();
	BOOL Create(CWnd* pParentWnd);

// Attributes
public:
	CWnd*	m_pParentWnd;
	CPoint	m_ptWheelOrg;
	CBitmap	m_bmpOrigin;
	int		m_nOriginBmpIndex;
	UINT	m_nWheelTimer;
	HWND	m_hFocusWnd;
	BOOL	m_bNoVertScroll;
	BOOL	m_bNoHorzScroll;

	int		m_nScrollSum;
	CPoint	m_ptScrollSum;
	BOOL	m_bOnlyOneDirection;


// Operations
public:
	void SetCursor(int nCursor);
	BOOL DoScroll(int nDirection, int nSize);
	BOOL DoScroll(CPoint ptDelta);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWheelWnd)
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWheelWnd)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFXWHLPAN_H__4E9C2711_CFCD_11D1_87BA_400011900025__INCLUDED_)
