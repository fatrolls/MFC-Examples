#if !defined(AFX_SKINNEDEDIT_H__80D2E1ED_9B5C_4E6F_876E_9DFB41626561__INCLUDED_)
#define AFX_SKINNEDEDIT_H__80D2E1ED_9B5C_4E6F_876E_9DFB41626561__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinnedEdit.h : header file
//

#include "SkinControl.h"
/////////////////////////////////////////////////////////////////////////////
// CSkinnedEdit window

#define IDC_EDIT_CHILD	2000

class CSkinnedEdit : public CWnd, public CSkinControl
{
// Construction
public:
	CSkinnedEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinnedEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsDataValid();
	BOOL IsReadOnly();
	int SetFontStyle(int nFontStyle);
	void ReadOnly(BOOL bReadOnly=TRUE);
	void SetEnabled(BOOL bEnable);
	CString GetControlText();
	LPCTSTR SetFontName(LPCTSTR lpszFontFaceName);
	void MoveWindowEng(int nLeft, int nTop, BOOL bRedraw, long lFlags=0);
	void MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags=0);
	void SetControlText(LPCTSTR lpszText);
	BOOL CreateSkinControl(LPCTSTR lpszWindowName, LPRECT lpRect, CWnd *pParentWnd, UINT nControlID, long lFlags=BORDER_STYLE_3D);
	void SetControlType(UINT nType = CONTROL_TYPE_ALPHANUMERIC);
	UINT GetControlType() const;
	void SetSel(int nStartChar=0, int nEndChar=-1, BOOL bNoScroll=FALSE);
	virtual ~CSkinnedEdit();

	void SetCharLimit(int nMaxChar);
	int GetCharLimit();

	void SetDecimalPlaceLimit(int nMaxDecimalPlace);
	int GetDecimalPlaceLimit();
	void ValidateDecimalPlaces();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinnedEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_brush;
	BOOL m_bValidateData;
	BOOL m_bReadonly;
	long m_lStyle;
	UINT m_nControlType;
	CEdit m_edit;
	int m_nMaxChars;
	int m_nDecimalPlaces;
	BOOL m_bBackSpace;

	void BltEx();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINNEDEDIT_H__80D2E1ED_9B5C_4E6F_876E_9DFB41626561__INCLUDED_)
