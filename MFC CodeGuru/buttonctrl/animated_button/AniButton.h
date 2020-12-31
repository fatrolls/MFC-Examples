#if !defined(AFX_ANIBUTTON_H__E9AC4132_284A_11D1_931F_00A0247B4CE3__INCLUDED_)
#define AFX_ANIBUTTON_H__E9AC4132_284A_11D1_931F_00A0247B4CE3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AniButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAniButton window

class CAniButton : public CButton
{
// Construction
public:
	CAniButton();

// Attributes
public:
    BOOL Create( LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );
// Operations
public:
    UINT m_nAniID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAniButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadAVI(UINT nAniID);
	virtual ~CAniButton();

	// Generated message map functions
protected:
    CAnimateCtrl	m_AnimateCtrl;

    BOOL m_bPlaying;
	//{{AFX_MSG(CAniButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawButton(CDC* pDC, UINT nState, CRect rect);
    DECLARE_MESSAGE_MAP()
    

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIBUTTON_H__E9AC4132_284A_11D1_931F_00A0247B4CE3__INCLUDED_)
