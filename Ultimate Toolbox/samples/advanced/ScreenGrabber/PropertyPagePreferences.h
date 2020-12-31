#if !defined(AFX_PROPERTYPAGEPREFERENCES_H__E32DDA26_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_PROPERTYPAGEPREFERENCES_H__E32DDA26_805A_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropertyPagePreferences.h : header file
//

#include "OXContextHelpPropertyPage.h"
#include "OXLayoutManager.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyPagePreferences dialog

class CPropertyPagePreferences : public COXContextHelpPropertyPage
{
//	DECLARE_DYNCREATE(CPropertyPagePreferences)

// Construction
public:
	CPropertyPagePreferences();
	~CPropertyPagePreferences();

	BOOL AdjustToolTips();

// Dialog Data
	//{{AFX_DATA(CPropertyPagePreferences)
	enum { IDD = IDD_PROPPAGE_PREFERENCES };
	CButton	m_ctlCheckNotifyEnd;
	CButton	m_ctlCheckHideIcon;
	BOOL	m_bHideIcon;
	BOOL	m_bNotifyEnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPagePreferences)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void CheckVars();
	void ShowControls();

	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
// Implementation
protected:
	COXLayoutManager m_LayoutManager;

	// Generated message map functions
	//{{AFX_MSG(CPropertyPagePreferences)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEPREFERENCES_H__E32DDA26_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
