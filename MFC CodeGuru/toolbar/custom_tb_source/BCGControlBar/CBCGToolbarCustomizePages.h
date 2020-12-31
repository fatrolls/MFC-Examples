// CBCGToolbarCustomizePages.h : header file
//

#ifndef __CBCGTOOLBARCUSTOMIZEPAGES_H__
#define __CBCGTOOLBARCUSTOMIZEPAGES_H__

#include "ButtonsList.h"
#include "ButtonsTextList.h"
#include "resource.h"

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif
/////////////////////////////////////////////////////////////////////////////
// CCustomizePage dialog

class CBCGToolbarButton;
class CBCGToolBarImages;
class CBCGToolBar;

class CCustomizePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCustomizePage)

// Construction
public:
	CCustomizePage();
	~CCustomizePage();

// Operations:
	void SetImages (CBCGToolBarImages* pImages);
	void AddButton (LPCTSTR lpszCategory, const CBCGToolbarButton& button);
	BOOL SetUserCategory (LPCTSTR lpszCategory);

	void OnChangeSelButton (CBCGToolbarButton* pButton);

// Dialog Data
	//{{AFX_DATA(CCustomizePage)
	enum { IDD = IDD_PROPPAGE1 };
	CButtonsTextList	m_wndUserTools;
	CComboBox	m_wndCategory;
	CButtonsList	m_wndButtons;
	CString	m_strButtonDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCustomizePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustomizePage)
	afx_msg void OnButtonsList();
	afx_msg void OnSelchangeCategory();
	afx_msg void OnSelchangeUserTools();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes:
protected:
	CMap<CString, LPCTSTR, CObList*, CObList*> m_Buttons;
	CStringList			m_Categories;

	CBCGToolbarButton*	m_pSelButton;
	CObList*			m_pUserCategory;
	CBCGToolBarImages*	m_pImages;
};


/////////////////////////////////////////////////////////////////////////////
// CToolbarsPage dialog

class CToolbarsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CToolbarsPage)

// Construction
public:
	CToolbarsPage();
	~CToolbarsPage();

// Dialog Data
	//{{AFX_DATA(CToolbarsPage)
	enum { IDD = IDD_PROPPAGE2 };
	CCheckListBox	m_wndToobarList;
	BOOL	m_bShowTooltips;
	//}}AFX_DATA

// Operations:
public:
	void ShowToolBar (CBCGToolBar* pToolBar, BOOL bShow);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CToolbarsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CToolbarsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeToolbarList();
	afx_msg void OnDblclkToolbarList();
	afx_msg void OnShowTooltips();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __CBCGTOOLBARCUSTOMIZEPAGES_H__
