#if !defined(AFX_TREEBAR_H__10B67BA2_85D7_11D1_BAA0_006097DA5345__INCLUDED_)
#define AFX_TREEBAR_H__10B67BA2_85D7_11D1_BAA0_006097DA5345__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TreeBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeBar window

class CTreeBar : public CMRCSizeControlBar
{
// Construction
public:
	CTreeBar();

// Attributes
public:
    CTabCtrl    m_TabCtrl;
    CImageList  m_ImgList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
    afx_msg void OnTabChanged( NMHDR * pNotifyStruct, LRESULT * result );
	DECLARE_MESSAGE_MAP()

    virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

    // helper functions.
    CWnd * GetTabWindow(int nTab);
    void ShowSelTabWindow();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEBAR_H__10B67BA2_85D7_11D1_BAA0_006097DA5345__INCLUDED_)
