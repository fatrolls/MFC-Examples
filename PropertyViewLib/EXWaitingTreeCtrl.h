// WaitingTreeCtrl.h : header file
//
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2001 by Paolo Messina
// (http://www.geocities.com/ppescher - ppescher@yahoo.com)
//
// The contents of this file are subject to the Artistic License (the "License").
// You may not use this file except in compliance with the License. 
// You may obtain a copy of the License at:
// http://www.opensource.org/licenses/artistic-license.html
//
// If you find this code useful, credits would be nice!
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAITINGTREECTRL_H__80CBE29B_F1A6_41D5_9DF3_B725E73BCF0F__INCLUDED_)
#define AFX_WAITINGTREECTRL_H__80CBE29B_F1A6_41D5_9DF3_B725E73BCF0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWaitingTreeCtrl window

#include <afxcmn.h>	//ctreectrl

class EXWaitingTreeCtrl : public CTreeCtrl
{
DECLARE_DYNAMIC( EXWaitingTreeCtrl )
private:
	void DestroySnapshot();
	void DrawSnapshot(CDC* pDC);
	void TakeSnapshot();
	HANDLE m_hThread;				// secondary thread for animations
	HANDLE m_hTimerEvent;			// signaled at each timer period
	HANDLE m_hRedrawEvent;			// signaled at each population update
	volatile BOOL m_bAbortAnimation;	// request to terminate secondary thread
	BOOL m_bDrawSnapshot;			// whether to draw background during populating
	CBitmap m_bmpSnapshot;			// snapshot bitmap
	UINT m_nTimerID;				// animation timer id
	UINT m_nTimerDelay;				// animation timer period (ms)
	CString m_sWaitMsg;				// text for the wait message
	HICON m_hIconMsg;				// icon for the wait message
	BOOL m_bShowWaitMsg;			// wether to show the wait message
	int m_iItemIndex;				// population progress index
	int m_iItemCount;				// population progress max index
	HTREEITEM m_hItemMsg;			// wait message item
	HTREEITEM m_hItemToPopulate;	// item being populated

	// secondary thread entry point
	static DWORD WINAPI AnimationThreadProc(LPVOID pThis);
	
	void StartAnimation();		// set up animation thread
	void StopAnimation();		// animation clean up
	
	void PreExpandItem(HTREEITEM hItem);	// before expanding
	void ExpandItem(HTREEITEM hItem);		// after expanded

	BOOL NeedsChildren(HTREEITEM hParent);	// true if no child items
	void DeleteChildren(HTREEITEM hParent);

	void DrawUserIcon();	// draw wait message icon

// Construction
public:
	EXWaitingTreeCtrl();
	virtual ~EXWaitingTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitingTreeCtrl)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	void RefreshSubItems(HTREEITEM hParent);
	void SetWaitMessage(LPCTSTR pszText, HICON hIcon = NULL);
	void ShowWaitMessage()
	{
		m_bShowWaitMsg = TRUE;
	};

protected:
	// animation functions (with timer)
	void SetAnimationDelay(UINT nMilliseconds);

	// animation functions (with or without timer)
	virtual void PreAnimation(HTREEITEM hItemMsg);
	virtual void DoAnimation(BOOL bTimerEvent, int iMaxSteps, int iStep);
	virtual void PostAnimation();
	BOOL GetItemImageRect(HTREEITEM hItem, LPRECT pRect);

	// tree content functions
	void PopulateRoot();
	virtual BOOL WantsRefresh(HTREEITEM hItem);
	virtual BOOL PopulateItem(HTREEITEM hParent) = 0;	// must be implemented

	// tree content functions (for animations without timer)
	int GetPopulationCount(int *piMaxSubItems = NULL);
	void SetPopulationCount(int iMaxSubItems, int iFirstSubItem = 0);
	void IncreasePopulation(int iSubItemsToAdd = 1);
	void UpdatePopulation(int iSubItems);

	// Generated message map functions
	//{{AFX_MSG(CWaitingTreeCtrl)
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITINGTREECTRL_H__80CBE29B_F1A6_41D5_9DF3_B725E73BCF0F__INCLUDED_)
