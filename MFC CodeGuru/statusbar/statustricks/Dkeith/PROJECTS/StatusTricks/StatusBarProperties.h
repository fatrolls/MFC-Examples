#if !defined(AFX_STATUSBARPROPERTIES_H__9823BE5C_4C57_11D1_B853_0020AF6F26D6__INCLUDED_)
#define AFX_STATUSBARPROPERTIES_H__9823BE5C_4C57_11D1_B853_0020AF6F26D6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StatusBarProperties.h : header file
//

#include "ColorStatusBar.h"

/////////////////////////////////////////////////////////////////////////////
// CStatusBarProperties dialog

class CStatusBarProperties : public CDialog
{
protected:
	CStatusPaneInfo	*pInfo;		// status pane info for this pane

public:
					 CStatusBarProperties(CStatusPaneInfo *pane, BOOL bBanner,
						CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CStatusBarProperties)
	enum { IDD = IDD_STATUSPANEPROPERTIES };
	CString	m_sSampleFont;
	BOOL	m_bShowBanner;
	BOOL	m_bTransparentText;
	BOOL	m_bHorizontalScrolling;
	BOOL	m_bVerticalScrolling;
	BOOL	m_bClearBackground;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusBarProperties)
protected:
	virtual void		 DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CStatusBarProperties)
	virtual BOOL		 OnInitDialog();
	afx_msg void		 OnChangecolorback();
	afx_msg void		 OnChangecolorfore();
	afx_msg void		 OnChangefont();
	virtual void		 OnOK();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSBARPROPERTIES_H__9823BE5C_4C57_11D1_B853_0020AF6F26D6__INCLUDED_)
