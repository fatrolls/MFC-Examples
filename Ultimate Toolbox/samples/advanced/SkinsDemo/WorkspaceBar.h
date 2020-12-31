#if !defined(AFX_WORKSPACEBAR_H__1EC50BBE_B9C5_4FBF_8AA3_B149151D6DCD__INCLUDED_)
#define AFX_WORKSPACEBAR_H__1EC50BBE_B9C5_4FBF_8AA3_B149151D6DCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkspaceBar.h : header file
//

#include "OXSizeCtrlBar.h"
#include "OX3DTabView.h"
#include "OXShortcutBar.h"

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar window

class CWorkspaceBar : public COXSizeControlBar
{
// Construction
public:
	CWorkspaceBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	COXShortcutBar m_ShortcutBar;
	virtual ~CWorkspaceBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnShortcutBarSelectItem(NMHDR* pNotifyStruct, LRESULT* result);
	DECLARE_MESSAGE_MAP()

	CImageList m_ilLarge;
	CImageList m_ilSmall;
	CImageList m_ilTree;

private:
	void InitShortcutBar();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACEBAR_H__1EC50BBE_B9C5_4FBF_8AA3_B149151D6DCD__INCLUDED_)
