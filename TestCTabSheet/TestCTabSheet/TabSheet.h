#if !defined(AFX_TABSHEET_H__42EE262D_D15F_46D5_8F26_28FD049E99F4__INCLUDED_)
#define AFX_TABSHEET_H__42EE262D_D15F_46D5_8F26_28FD049E99F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabSheet window

class CTabSheet : public CTabCtrl
{
// Construction
public:
	CTabSheet();
	virtual ~CTabSheet();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabSheet)
protected:
	virtual  void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// override to draw text only; eg, colored text or different font
	virtual  void OnDrawText(CDC& dc, CRect rc, CString sText, BOOL bDisabled, UINT format);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetCurSel();
	int SetCurSel(int nItem);
	//void Show();
	BOOL AddPage(LPCTSTR title, CDialog *pDialog, UINT ID, int nImage=-1);
	void EnableTab(int iIndex, BOOL bEnable = TRUE);//Index从0开始计数
	void EnableAllTabs(BOOL bEnable = TRUE);
	void DeleteAllTabs();
	void DeleteTab(int iIndex);
	virtual BOOL IsTabEnabled(int iIndex);
	BOOL HideTab(BOOL bHide = FALSE);
	BOOL IsTabHided();
	enum ITEMPOS{TOP,BOTTOM,LEFT,RIGHT};//设置选项卡的位置：顶、底、左、右
	void SetItemPos(ITEMPOS nItemPos);//设置选项卡的位置：顶、底、左、右

protected:
	//void SetRect();
	void SetRect(int iIndex);

	// Generated message map functions
protected:
	CArray<BOOL, BOOL> m_arrayStatusTab; //** enabled Y\N

	BOOL m_bHideTab;

	CStringArray m_Title;
	CUIntArray m_IDD;
	typedef CDialog* PDIALOG;
	CArray<PDIALOG, PDIALOG> m_pPages;
	int m_nCurrentPage;
	//{{AFX_MSG(CTabSheet)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABSHEET_H__42EE262D_D15F_46D5_8F26_28FD049E99F4__INCLUDED_)
