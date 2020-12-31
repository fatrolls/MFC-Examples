#if !defined(AFX_PROPERTYPAGEDESTINATION_H__E32DDA23_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_PROPERTYPAGEDESTINATION_H__E32DDA23_805A_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropertyPageDestination.h : header file
//

#include "OXContextHelpPropertyPage.h"
#include "OXLayoutManager.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageDestination dialog

class CPropertyPageDestination : public COXContextHelpPropertyPage
{
//	DECLARE_DYNCREATE(CPropertyPageDestination)

// Construction
public:
	CPropertyPageDestination();
	~CPropertyPageDestination();

	BOOL AdjustToolTips();

// Dialog Data
	//{{AFX_DATA(CPropertyPageDestination)
	enum { IDD = IDD_PROPPAGE_DESTINATION };
	CButton	m_ctlCheckFile;
	CButton	m_ctlCheckClipboard;
	BOOL	m_bClipboard;
	BOOL	m_bFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageDestination)
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
	//{{AFX_MSG(CPropertyPageDestination)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEDESTINATION_H__E32DDA23_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
