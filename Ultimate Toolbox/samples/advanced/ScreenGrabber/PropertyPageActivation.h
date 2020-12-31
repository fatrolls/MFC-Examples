#if !defined(AFX_PROPERTYPAGEACTIVATION_H__ACC74CA2_804B_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_PROPERTYPAGEACTIVATION_H__ACC74CA2_804B_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropertyPageActivation.h : header file
//

#include "OXContextHelpPropertyPage.h"
#include "OXSpinCtrl.h"
#include "OXLayoutManager.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageActivation dialog

class CPropertyPageActivation : public COXContextHelpPropertyPage
{
//	DECLARE_DYNCREATE(CPropertyPageActivation)

// Construction
public:
	CPropertyPageActivation();   // standard constructor
	~CPropertyPageActivation();

	BOOL AdjustToolTips();

// Dialog Data
	//{{AFX_DATA(CPropertyPageActivation)
	enum { IDD = IDD_PROPPAGE_ACTIVATION };
	CButton	m_ctlCheckInitialDelay;
	CStatic	m_ctlStaticHotKey;
	COXSpinCtrl	m_ctlSpinInitialDelay;
	CEdit	m_ctlEditInitialDelay;
	CComboBox	m_ctlComboHotKey;
	CString	m_sHotKey;
	UINT	m_nInitialDelay;
	BOOL	m_bInitialDelay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageActivation)
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
	//{{AFX_MSG(CPropertyPageActivation)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckInitialDelay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEACTIVATION_H__ACC74CA2_804B_11D1_A3D5_0080C83F712F__INCLUDED_)
