////////////////////////////////////////////////////////////////
// 1999 Paul DiLascia
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#pragma once

// folder tab control style flags
#define FTS_FULLBORDER	0x1 // draw full border
#define FTS_BUTTONS	   0x2 // draw next/prev buttons

#define  FTS_NUMBUTTONS  4


// notification: tab changed
enum { FTN_TABCHANGED = 1, FTN_EDITSHEETS = 2, FTN_TABNAMECHANGED = 3,
	   FTN_ADDSHEET = 4, FTN_DELETESHEET = 5 };

enum { FTBFIRST = 1, FTBPREV = 2, FTBNEXT = 3, FTBLAST = 4 };	 // folder button IDs

struct NMFOLDERTAB : public NMHDR {		 // notification struct
	int iItem;									 // item index
	CString lpText;							 // tab text
};

class CFolderTab; // fwd ref

//////////////////
// Next/prev folder button to navigate tabs when they don't all fit
//
class CFolderButton : public CButton 
{
protected:
	int  m_iState;
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDis);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_DYNAMIC(CFolderButton);
	DECLARE_MESSAGE_MAP()
};

//////////////////
// Folder tab control, similar to tab control
//
class CFolderTabCtrl : public CWnd {
protected:
	CFolderButton m_wndButton [FTS_NUMBUTTONS];	 // folder buttons
	CEdit         * m_editBox;
	CPtrList		m_lsTabs;					 // array of CFolderTabs
	DWORD			m_dwFtabStyle;				 // folder tab style flags
	int			m_iCurItem;					 // current selected tab
	CFont			m_fontNormal;				 // current font, normal ntab
	CFont			m_fontSelected;			 // current font, selected tab
	int			m_cxDesired;				 // exact fit width
	int			m_cxButtons;				 // width of buttons
	int			m_iFirstTab;				 // first tab to show

	// helpers
	void InvalidateTab(int iTab, BOOL bErase=TRUE);
	void DrawTabs(CDC& dc, const CRect& rc);
	void UpdateButtons();
	CFolderTab* GetTab(int iPos);

public:
	CFolderTabCtrl();
	virtual ~CFolderTabCtrl();

	BOOL CreateFromStatic(UINT nID, CWnd* pParent);

	virtual BOOL Create(DWORD dwWndStyle, const RECT& rc,
		CWnd* pParent, UINT nID, DWORD dwFtabStyle=0);
	virtual BOOL Load(UINT nIDRes);

	int	GetSelectedItem()				{ return m_iCurItem; }
	int	GetItemCount()					{ return m_lsTabs.GetCount(); }
	int	GetDesiredWidth()				{ return m_cxDesired; }
	int	GetDesiredHeight()			{ return GetSystemMetrics(SM_CYHSCROLL); }
	BOOL  AddItem(LPCTSTR lpszText);
	BOOL  RemoveItem(int iPos);
	void	RecomputeLayout();
	int	HitTest(CPoint pt);
	int	SelectItem(int iTab);
	void	SetFonts(CFont& fontNormal, CFont& fontSelected);
	LPCTSTR GetItemText(int iItem);
	void    SetItemText(int iItem, LPCTSTR lpText);

protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFirstTab();
	afx_msg void OnNextTab();
	afx_msg void OnPrevTab();
	afx_msg void OnLastTab();
	afx_msg void OnEditBoxKillFocus();
	afx_msg void OnEditProperties();
	afx_msg void OnEditAddSheet();
	afx_msg void OnEditDeleteSheet();
	afx_msg void OnEditRenameSheet();
	DECLARE_DYNAMIC(CFolderTabCtrl);
	DECLARE_MESSAGE_MAP()
};
