#if !defined(AFX_PROPERTYPAGESOURCE_H__E32DDA22_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_PROPERTYPAGESOURCE_H__E32DDA22_805A_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropertyPageSource.h : header file
//

#include "OXContextHelpPropertyPage.h"
#include "OXLayoutManager.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageSource dialog

class CPropertyPageSource : public COXContextHelpPropertyPage
{
//	DECLARE_DYNCREATE(CPropertyPageSource)

// Construction
public:
	CPropertyPageSource();
	~CPropertyPageSource();

	BOOL AdjustToolTips();

// Dialog Data
	//{{AFX_DATA(CPropertyPageSource)
	enum { IDD = IDD_PROPPAGE_SOURCE };
	CButton	m_ctlRadioCurrentWindow;
	int		m_nRadioCapturedArea;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageSource)
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
	//{{AFX_MSG(CPropertyPageSource)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGESOURCE_H__E32DDA22_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
