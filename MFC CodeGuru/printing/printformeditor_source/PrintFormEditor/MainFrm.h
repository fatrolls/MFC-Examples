// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__17660EAD_0940_11D2_840B_0000B43382FE__INCLUDED_)
#define AFX_MAINFRM_H__17660EAD_0940_11D2_840B_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PropDlg.h"
#include "PapersBar.h"
#include "GfxProperty.h"

CPropDlg * GfxGetProp();
bool GfxIsProp();

CGfxProperty * GfxGetProp2();
bool GfxIsProp2();

CPapersBar * GfxGetPaperList();

class CMainFrame : public SECWorkbook
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CPropDlg propDlg;
	CPapersBar paperBar;
	CGfxProperty	gfxProp;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	SECToolBarManager* GetManager() const;
	void DoTrackMenu(const int menuId, const int iPopPos, CWnd * pSendTo, CPoint pt);

protected:  // control bar embedded members
	SECStatusBar  m_wndStatusBar;




// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnProperty();
	afx_msg void OnUpdateProperty(CCmdUI* pCmdUI);
	afx_msg void OnShowPagebar();
	afx_msg void OnUpdateShowPagebar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



inline SECToolBarManager* CMainFrame::GetManager() const 
{ 
	return (SECToolBarManager*) m_pControlBarManager; 
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__17660EAD_0940_11D2_840B_0000B43382FE__INCLUDED_)
