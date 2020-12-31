// MFCXToolBar.h: interface for the CMFCXToolBar class.
//
// 1998 Kirk Stowell ( kstowel@sprynet.com )
// www.geocities.com/SiliconValley/Haven/8230/index.html
//
// You are free to use, modify and distribute this source, as long as
// there is no charge, and this HEADER stays intact. This source is
// supplied "AS-IS", and without WARRANTY OF ANY KIND, and the user
// holds the author blameless for any or all problems that may arise
// from the use of this code.
//
//////////////////////////////////////////////////////////////////////

#ifndef MFCXTOOLBAR__H
#define MFCXTOOLBAR__H

#ifndef MFCX_PROJ
#define CLASS_EXPORT AFX_CLASS_EXPORT
#else
#define CLASS_EXPORT AFX_CLASS_IMPORT
#endif

#ifndef TB_SETEXTENDEDSTYLE
// Old commctrl.h compatibility
#define TB_SETEXTENDEDSTYLE     (WM_USER + 84)  // For TBSTYLE_EX_*
#define TBSTYLE_EX_DRAWDDARROWS 0x00000001
#define TBSTYLE_AUTOSIZE        0x0010			// automatically calculate the cx of the button 
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CLASS_EXPORT CMFCXToolBar : public CToolBar  
{
	DECLARE_DYNAMIC(CMFCXToolBar)
public:
	CMFCXToolBar();
	virtual ~CMFCXToolBar();

	CWnd* InsertControl(CRuntimeClass* pClass, CString strTitle,
		CRect& pRect, UINT nID, DWORD dwStyle);
	void DrawNoGripper() { m_bNoGripper = true; }
	void SetImageList(CImageList * pList, DWORD dwStyle);
	void SetButtonDropDown(int nID);

protected:
	// There is a bug in comctl32.dll, version 4.71+ that causes it to
	// draw vertical separators in addition to horizontal ones, when the
	// toolbar is vertical. Set this to FALSE to eliminate them--but then
	// you lose your dropdown arrows.
	//
	bool	 m_bShowDropdownArrowWhenVertical;
	bool	 m_bNoGripper;
	CFont	 m_font;
	CObList* m_pControls;	 // list of custom controls (if any)

	void SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert = FALSE);
	void DrawGripper(CDC & dc) const;

	// MFC has versions of these are hidden--why?
	//
	void GetButton(int nIndex, TBBUTTON* pButton) const;
	void SetButton(int nIndex, TBBUTTON* pButton);
	
	int WrapToolBar(TBBUTTON* pData, int nCount, int nWidth);
	CSize CalcSize(TBBUTTON* pData, int nCount);
	CSize CalcLayout(DWORD nMode, int nLength = -1);

	void EraseNonClient(BOOL);
	void DrawBorders(CDC* pDC, CRect& rect);

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCXToolBar)
	protected:
	virtual CSize GetButtonSize(TBBUTTON* pData, int iButton);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);	
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCXToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////
// The following class was copied from BARTOOL.CPP in the MFC source.
// All I changed was SetCheck--PD.
//
class CMFCXToolCmdUI : public CCmdUI
{
public: // re-implementations only
	virtual void Enable(BOOL bOn);
	virtual void SetCheck(int nCheck);
	virtual void SetText(LPCTSTR lpszText);
};

#endif
