// =============================================================================
// 							Class Specification : COXWebView
// =============================================================================
//
// Header file : OXWebView.h
//
// /////////////////////////////////////////////////////////////////////////////
//
// Properties:
//
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject
//	YES	Is a Cwnd.
//	NO	Two stage creation (constructor & Create())
//	YES	Has a message map
//	NO  Needs a resource (template)
//	NO	Persistent objects (saveable on disk)
//	NO	Uses exceptions
//
////////////////////////////////////////////////////////////////////////////////
//
// Desciption :
//		This class provides a simple to use html viewer by leveraging
//		Microsoft's Internet Explorer web control.
//
// Remark:
//
// Prerequisites (necessary conditions):
//		The user must have Microsoft Internet Explorer v3.x (or higher)
//		installed on his machine in order for this class to function.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __OXWEBVIEW_H__
#define __OXWEBVIEW_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


#include <Exdisp.h>
#include "OXWebCtrl.h"


class OX_CLASS_DECL COXWebView : public CView
{
// Data members -------------------------------------------------------------
public:
protected:
private:
	static CFont* m_pfontToolbarURL;
	static int m_nNumInstantiated;

	CComboBox m_cbxToolbarURL;
	COXWebCtrl m_WebCtrl;
	CToolBar m_Toolbar;
	CToolTipCtrl m_Tooltips;

	BOOL m_bCanGoBack;
	BOOL m_bCanGoForward;
	BOOL m_bCanRefresh;

// Member functions ---------------------------------------------------------
public:
	virtual ~COXWebView();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

	COXWebCtrl& GetWebControl()
		{ return m_WebCtrl; }
	// --- In  :
	// --- Out : 
	// --- Returns : A reference to the web control embedded within the view.
	// --- Effect : This method allows the user to get at the web control
	//				if access is needed.

	CToolBar& GetToolbar()
		{ return m_Toolbar; }
	// --- In  :
	// --- Out :
	// --- Returns : A reference to the toolbar contained within the view.
	// --- Effect : This method allows the user to get at the toolbar of
	//              the web view.

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXWebView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	DECLARE_DYNCREATE(COXWebView)
	enum { IDC_WEB_CTRL = 100, IDC_TOOLBAR_URL = 101 };

	COXWebView();	// create from serialization only
	virtual void BeforeNavigate(LPCTSTR pcszURL, long lFlags, LPCTSTR pcszTargetFrameName, VARIANT* PostData, LPCTSTR pcszHeaders, VARIANT_BOOL* pbCancel);
	virtual void NavigateComplete(LPCTSTR pcszURL);
	virtual void StatusTextChange(LPCTSTR pcszText);
	virtual void Quit(VARIANT_BOOL* pbCancel);
	virtual void DownloadBegin();
	virtual void NewWindow(LPCTSTR pcszURL, long lFlags, LPCTSTR pcszTargetFrameName, VARIANT* PostData, LPCTSTR pcszHeaders, VARIANT_BOOL* pbCancel);
	virtual void ProgressChange(long lProgress, long lProgressMax);
	virtual void DownloadComplete();
	virtual void CommandStateChange(long lCmdID, BOOL bEnabled);
	virtual void PropertyChange(LPCTSTR pcszProperty);
	virtual void TitleChange(LPCTSTR pcszTitle);
	virtual void FrameBeforeNavigate(LPCTSTR pcszURL, long lFlags, LPCTSTR pcszTargetFrameName, VARIANT* PostData, LPCTSTR pcszHeaders, VARIANT_BOOL* pbCancel);
	virtual void FrameNavigateComplete(LPCTSTR pcszURL);
	virtual void FrameNewWindow(LPCTSTR pcszURL, long lFlags, LPCTSTR pcszTargetFrameName, VARIANT* PostData, LPCTSTR pcszHeaders, VARIANT_BOOL* pbCancel);

	//{{AFX_MSG(COXWebView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWebviewBack();
	afx_msg void OnWebviewForward();
	afx_msg void OnUpdateWebviewBack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWebviewForward(CCmdUI* pCmdUI);
	afx_msg void OnWebviewHome();
	afx_msg void OnWebviewSearch();
	afx_msg void OnUpdateWebviewStop(CCmdUI* pCmdUI);
	afx_msg void OnWebviewStop();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateWebviewRefresh(CCmdUI* pCmdUI);
	afx_msg void OnWebviewRefresh();
	//}}AFX_MSG
	afx_msg void OnToolbarURLChange();
	afx_msg BOOL OnTooltipNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif	// __OXWEBVIEW_H__

