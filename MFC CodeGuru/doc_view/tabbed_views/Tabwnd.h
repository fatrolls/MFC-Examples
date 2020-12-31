#if !defined(AFX_TABWND_H__E22ADFB8_5063_11D1_8E9B_4854E827046F__INCLUDED_)
#define AFX_TABWND_H__E22ADFB8_5063_11D1_8E9B_4854E827046F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TabWnd.h : header file
//

#define TABWND_DEFAULT_ID 0x2578   
#define TABWND_HEIGHT     32		/* the height of the gray border between the toolbar and the client area */
#define TAB_HEIGHT        20        
#define TAB_SPACE         17		
#define TABSEL_HEIGHT     22		/* the height of the selected tab */
#define TAB_DEPL          5			/* the distance between the tabs and the client area */

#define WM_TABRESIZE      (WM_USER+0x47)
#define WM_TABCHANGED     (WM_USER+0x48)

typedef struct
{
	CWnd *pWnd;
	char szLabel[32];
	int x_min, x_max;
}TABWND_MEMBER;


/////////////////////////////////////////////////////////////////////////////
// CTabWnd window

class CTabWnd : public CWnd
{
// Construction
public:
	CTabWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabWnd)
	public:
	virtual BOOL Create(DWORD dwStyle, CWnd* pParentWnd, UINT nID=AFX_IDW_PANE_FIRST);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SwitchView(int iNewView);
	int GetTabLength();
	UINT m_dwStyle;
	BOOL m_bLock;
	int HitTest(int x, int y);
	int m_selTab;
	BOOL CreateView(LPCTSTR lpszLabel, CRuntimeClass *pViewClass, CCreateContext *pContext);
	virtual ~CTabWnd();

protected:
	CList <TABWND_MEMBER *,TABWND_MEMBER *> m_viewList;
	int DrawTab(CDC *pDC, int x, LPCTSTR szText);
	int DrawSelTab(CDC *pDC, int x, LPCTSTR szText);
	CBrush brushBlack, brushWhite, brushLGray, brushDGray, brushText;
	CPen penWhite, penWhite2, penBlack, penL1Gray, penL2Gray, penDGray, penDGray2;
	void CreateFont();
	CFont *m_pFont, *m_pBoldFont;

	// Generated message map functions
protected:
    LRESULT OnTabResize(WPARAM, LPARAM);
	//{{AFX_MSG(CTabWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnSizeParent(WPARAM, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABWND_H__E22ADFB8_5063_11D1_8E9B_4854E827046F__INCLUDED_)
