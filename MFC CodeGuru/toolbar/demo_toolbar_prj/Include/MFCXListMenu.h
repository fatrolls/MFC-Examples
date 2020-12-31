// MFCXListMenu.h : header file
//
// 1998 Kirk Stowell ( kstowel@sprynet.com )
// www.geocities.com/SiliconValley/Haven/8230/index.html
//
// You are free to use, modify and distribute this source, as long as
// there is no charge, and this HEADER stays intact. This source is
// supplied "AS-IS", and without WARRANTY OF ANY KIND, and the user
// holds the author blameless for any or all problems that may arise
// from the use of this code.
//
//////////////////////////////////////////////////////////////////////
//
// This code is based on the class ContentMenu.cpp, my modifications
// are marked *** Kirk Stowell
//
// Designed by Shekar Narayanan
// Please do not remove the above line
//
//////////////////////////////////////////////////////////////////////

#ifndef MFCXLISTMENU__H
#define MFCXLISTMENU__H

#ifndef MFCX_PROJ
#define CLASS_EXPORT AFX_CLASS_EXPORT
#else
#define CLASS_EXPORT AFX_CLASS_IMPORT
#endif

// *** Kirk Stowell - container class for menu items.
//////////////////////////////////////////////////////////////////////

class CLASS_EXPORT CContentItems
{
	UINT nImageID;
	CString strText;

public:
	CContentItems( UINT nID, CString str ) :
	  nImageID( nID ), strText( str ) {
	}

	void operator = ( CContentItems& pItems ) {
		nImageID = pItems.nImageID;
		strText  = pItems.strText;
	}

	UINT GetImageID() { return nImageID; }
	CString GetText() { return strText;  }
};

/////////////////////////////////////////////////////////////////////////////
// CMFCXListMenu window

class CLASS_EXPORT CMFCXListMenu : public CListBox
{
	DECLARE_DYNAMIC(CMFCXListMenu)
	CHeaderCtrl* pHeader;

// Construction
public:
	CMFCXListMenu();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCXListMenu)
	public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
    void SetItems( CContentItems* pItems, int nNumItems );
	void SetImageList( UINT uList, UINT uSize, COLORREF clrMask );
	virtual ~CMFCXListMenu();
	virtual void OnSelButton() = 0;

	// Generated message map functions
protected:
    CPoint          m_point;
	CImageList*		m_pImageList;
	CContentItems*  m_pContents;
    int             m_nNumItems;
	int             m_nIndex;
    bool            m_bHilight;
    bool            m_bLBDown;

	//{{AFX_MSG(CMFCXListMenu)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
