#if !defined(AFX_RIGHTPANEFRAME_H__C50FD506_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
#define AFX_RIGHTPANEFRAME_H__C50FD506_CEFA_11D1_9B01_0060970863EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RightPaneFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRightPaneFrame frame

#include "SplitterView.h"
#include "ListCtrlView.h"
#include "EditCtrlView.h"

#define  VIEW_SPLITTER 1
#define  VIEW_LISTCTRL 2
#define  VIEW_EDIT     3


class CRightPaneFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CRightPaneFrame)
protected:
	CRightPaneFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterView* m_pSplitterView;
	CListCtrlView* m_pListCtrlView;
	CEditCtrlView* m_pEditCtrlView;
	UINT           m_nCurrentViewID;

// Operations
public:
	void SwitchToView(UINT nView);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRightPaneFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRightPaneFrame();

	// Generated message map functions
	//{{AFX_MSG(CRightPaneFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTPANEFRAME_H__C50FD506_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
