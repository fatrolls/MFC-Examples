#if !defined(AFX_CUSTTOOLBARDLG_H__6656D215_C47F_11D1_A644_00A0C93A70EC__INCLUDED_)
#define AFX_CUSTTOOLBARDLG_H__6656D215_C47F_11D1_A644_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustToolbarDlg.h : header file
//

#include "ButtonsList.h"
#include "ButtonsTextList.h"

class CBCGToolbarButton;
class CBCGToolBarImages;

/////////////////////////////////////////////////////////////////////////////
// CCustToolbarDlg dialog

class AFX_EXT_CLASS CCustToolbarDlg : public CDialog
{
// Construction
public:
	CCustToolbarDlg(CWnd* pParentWnd, CBCGToolBarImages* pImages);
	virtual ~CCustToolbarDlg();

// Operations:
	void AddButton (LPCTSTR lpszCategory, const CBCGToolbarButton& button);
	void AddButton (LPCTSTR lpszCategory, UINT uiID, int iImage, LPCTSTR lpszText = NULL);
	BOOL SetUserCategory (LPCTSTR lpszCategory);

	void OnChangeSelButton (CBCGToolbarButton* pButton);

protected:
	void SetFrameCustMode (BOOL bCustMode);

// Dialog Data
	//{{AFX_DATA(CCustToolbarDlg)
	CButtonsTextList	m_wndUserTools;
	CButtonsList	m_wndButtons;
	CComboBox	m_wndCategory;
	CString	m_strButtonDescription;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustToolbarDlg)
	public:
	virtual BOOL Create();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustToolbarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNcDestroy();
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCancel();
	afx_msg void OnSelchangeCategory();
	afx_msg void OnSelchangeUserTools();
	afx_msg void OnButtonsList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes:
	CWnd*				m_pParentWnd;
	CBCGToolBarImages*	m_pImages;

	CMap<CString, LPCTSTR, CObList*, CObList*> m_Buttons;
	CStringList			m_Categories;

	CBCGToolbarButton*	m_pSelButton;
	CObList*			m_pUserCategory;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTTOOLBARDLG_H__6656D215_C47F_11D1_A644_00A0C93A70EC__INCLUDED_)
