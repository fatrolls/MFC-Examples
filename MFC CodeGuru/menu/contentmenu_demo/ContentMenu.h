#if !defined(AFX_CONTENTMENU_H__CD0C34BC_CA2E_11D1_AE8A_0004AC31E75C__INCLUDED_)
#define AFX_CONTENTMENU_H__CD0C34BC_CA2E_11D1_AE8A_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ContentMenu.h : header file
//


typedef struct
{
    UINT    nImageID;
    char*   strText;
} CONTENT_ITEMS, *pCONTENT_ITEMS;

/////////////////////////////////////////////////////////////////////////////
// CContentMenu window

class CContentMenu : public CListBox
{
// Construction
public:
	CContentMenu();

// Attributes
public:

// Operations
public:
    void SetItems(pCONTENT_ITEMS pItems, int nNumItems)
    {
        m_pContents = pItems;
        m_nNumItems = nNumItems;
        for (int i= 0;i < nNumItems; i++) AddString("");
    }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContentMenu)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CContentMenu();

protected:
    bool            m_bHilight;
    bool            m_bLBDown;
    pCONTENT_ITEMS  m_pContents;
    int             m_nNumItems;
    CPoint          m_Point;

	// Generated message map functions
protected:
	//{{AFX_MSG(CContentMenu)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTENTMENU_H__CD0C34BC_CA2E_11D1_AE8A_0004AC31E75C__INCLUDED_)
