// PropertySheetCapture.h : header file
//

#if !defined(AFX_PropertySheetCapture_H__B53D38E8_8037_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_PropertySheetCapture_H__B53D38E8_8037_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetCapture dialog

#include "CaptureTaskbarIcon.h"
#include "OXContextHelpPropertySheet.h"
#include "oxdib.h"
#include "OXLayoutManager.h"

#include "WndTrackingHelper.h"

class CPropertySheetCapture : public COXContextHelpPropertySheet
{
// Construction
public:
	CPropertySheetCapture(UINT nIDCaption, CWnd *pParentWnd = NULL, 
		UINT iSelectPage = 0);
	CPropertySheetCapture(LPCTSTR pszCaption, CWnd *pParentWnd = NULL, 
		UINT iSelectPage = 0);

protected:
	BOOL AdjustToolTips();
	void IniPropertySheet();
	void IniTaskbarIcon();

	void DoCapture();
	void StreamCapture(COXDIB* pDIB);
	BOOL SaveAsClipboard(COXDIB* pDIB);
	BOOL SaveAsBMP(COXDIB* pDIB, LPCTSTR lpszPathName);
	BOOL SaveAsJPEG(COXDIB* pDIB, LPCTSTR lpszPathName);
	BOOL SaveAsGIF(COXDIB* pDIB, LPCTSTR lpszPathName);
	BOOL CleanupCapture();

	BOOL DoRegisterHotKey();

	void SetTrackingHelper();
	void RemoveTrackingHelper();

	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}

// Implementation
public:

protected:
	HICON m_hIcon;
	CWndTrackingHelper* pWndTrackingHelper;
	CCaptureTaskbarIcon m_TaskbarIcon;
	COXLayoutManager m_LayoutManager;

	BOOL m_bInitialized;
	CRect m_rectPage;

	// define if process of capturing is going
	BOOL m_bIsCapturing;
	// timer ID for initial delay
	UINT m_nTimerCaptureDelay;
	// define if process of getting rectangular area to capture is going
	BOOL m_bGettingRectArea;

	// Generated message map functions
	//{{AFX_MSG(CPropertySheetCapture)
	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnButtonCapture();
	afx_msg void OnButtonClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	afx_msg void OnMinimize();
	afx_msg void OnOpen();
	afx_msg void OnAppAbout();
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PropertySheetCapture_H__B53D38E8_8037_11D1_A3D5_0080C83F712F__INCLUDED_)

