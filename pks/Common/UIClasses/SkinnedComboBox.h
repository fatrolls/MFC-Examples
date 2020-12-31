#if !defined(AFX_SKINNEDCOMBOBOX_H__B93256E8_F295_45E6_8CB7_17AC63870425__INCLUDED_)
#define AFX_SKINNEDCOMBOBOX_H__B93256E8_F295_45E6_8CB7_17AC63870425__INCLUDED_

#include "SkinnedEdit.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinnedComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkinnedComboBox window


#define IDC_COMBOBOX_EDIT				0x0000F007
#define IDC_COMBOBOX_BUTTON				0x0000F008
#define IDC_COMBOBOX_LIST				0x0000F009

#define COMBOBOX_BUTTON_WIDTH			24

#include "SkinnedEdit.h"
#include "SkinnedListBox.h"
#include "SkinnedButton.h"

class CSkinnedComboBox : public CWnd, public CSkinControl
{
// Construction
public:
	CSkinnedComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinnedComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetElementCount();
	void ClearAllContents();
	void SetTextAlignment(int nAlignment);
	void HideDropDown();
	int GetLBText(int nIndex, LPTSTR lpszText );
	int GetCurSel();
	void SetCurSel(int nIndex);
	void SetBackgroundColor(int nBackgroundState, COLORREF crColor);
	LPCTSTR SetFontName(LPCTSTR lpszFontFaceName);
	int SetFontSize(int nFontSize);
	int SetFontStyle(int nFontStyle);

	void SetButtonImageResource(INT nUnPressedID=-1, INT nHoverID=-1, INT nPressedID=-1, INT nDisabledID=-1);
	void BltEx();
	void MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags=0);
	void AddString(LPTSTR lpszItem);
	BOOL CreateSkinControl(LPCTSTR lpszWindowName, 
				LPRECT lpRect, 
				CWnd *pParentWnd, 
				UINT nControlID, 
				long lFlags=0);
	virtual ~CSkinnedComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinnedComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nSelectedItem;
	int m_nComboHeight;
	CSkinnedListBox m_csList;
	CSkinnedButton m_csButton;
	CSkinnedEdit m_csEdit;
	long m_lFlags;
	BOOL m_bDisplayList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINNEDCOMBOBOX_H__B93256E8_F295_45E6_8CB7_17AC63870425__INCLUDED_)
