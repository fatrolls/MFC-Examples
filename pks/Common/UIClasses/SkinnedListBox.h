#if !defined(AFX_SKINNEDLISTBOX_H__030D3D60_0711_45C3_BC0E_635D8EAF42B4__INCLUDED_)
#define AFX_SKINNEDLISTBOX_H__030D3D60_0711_45C3_BC0E_635D8EAF42B4__INCLUDED_

#include "SkinnedScrollBar.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinnedListBox.h : header file
//

#define	IDC_LIST_CONTAINER	2100
#define IDC_LISTBOX_SCROLL	2101
#define IDC_CHILD_BUTTONS	2102

/////////////////////////////////////////////////////////////////////////////
// CSkinnedListBox window

#include "SkinControl.h"
#include "SkinnedButton.h"

class CSkinnedListBox : public CWnd, public CSkinControl
{
// Construction
public:
	CSkinnedListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinnedListBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL UpdateString(int nIndex, LPTSTR lpszItem);
	CDC* GetItemDC(int nItemIndex);
	BOOL ClearCurSel(int nIndex);
	int GetLastSelected();
	int GetSelItems(int *nItems);
	void UnselectAll();
	void UnselectItem(int nIndex);
	long GetTextAlignment();
	void SetTextAlignment(int nAlignment);
	void SetTopPadding(int nPad);
	void SetLeftPadding(int nPad);
	int GetSelCount();
	BOOL SetCurSel(int nIndex);
	int GetCurSel();
	int GetTextLength(int nIndex);
	int GetText(int nIndex, LPTSTR lpszBuffer);
	BOOL GetSel(int nIndex);
	int GetCount();
	BOOL SelectString(LPTSTR lpszItem);
	int FindString(LPCTSTR lszItem);
	void ResetContent();
	void InsertString(int nIndex, LPTSTR lpszItem);
	BOOL DeleteString(LPTSTR lpszItem);
	BOOL DeleteString(int nIndex);
	void AddString(LPTSTR lpszItem);
	void MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags=0);
	BOOL CreateSkinControl(LPCTSTR lpszWindowName, 
						LPRECT lpRect, 
						CWnd *pParentWnd, 
						UINT nControlID, 
						long lFlags=FL_LISTBOX_TYPE_NORMAL);
	virtual ~CSkinnedListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinnedListBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
	afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );
	afx_msg void OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void UpdateList();
	int m_nContainerTop;
	CWnd m_ContainerWnd;
	CSkinnedScrollBar m_scroll;
	HWND m_hControllerHwnd;
	void BltEx();
	int m_nLeftPad, m_nTopPad;
	CObList m_cobjElementList;
	int m_nChildControlID;
	long m_lFlags;
	long m_lSelectedItem;
	BOOL m_bProcess;
	int m_nLastSelected;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINNEDLISTBOX_H__030D3D60_0711_45C3_BC0E_635D8EAF42B4__INCLUDED_)
