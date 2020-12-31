#if !defined(AFX_FOLDERSBAR_H__5D073941_54B9_4749_A865_7935F422220D__INCLUDED_)
#define AFX_FOLDERSBAR_H__5D073941_54B9_4749_A865_7935F422220D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FoldersBar.h : header file
//

#include "OXSizeCtrlBar.h"
#include "OXShellFolderTree.h"

/////////////////////////////////////////////////////////////////////////////
// CFoldersBar window

class CFoldersBar : public COXSizeControlBar
{
// Construction
public:
	CFoldersBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFoldersBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	COXShellFolderTree m_FolderTree;
	virtual ~CFoldersBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFoldersBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDERSBAR_H__5D073941_54B9_4749_A865_7935F422220D__INCLUDED_)
