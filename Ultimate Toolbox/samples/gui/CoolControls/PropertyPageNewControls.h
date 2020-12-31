#if !defined(AFX_PROPERTYPAGENEWCONTROLS_H__3696ECEB_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
#define AFX_PROPERTYPAGENEWCONTROLS_H__3696ECEB_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyPageNewControls.h : header file
//

#if _MSC_VER > 0x0421

#include "OXCoolCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageNewControls dialog

class CPropertyPageNewControls : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropertyPageNewControls)

// Construction
public:
	CPropertyPageNewControls();
	~CPropertyPageNewControls();

// Dialog Data
	//{{AFX_DATA(CPropertyPageNewControls)
	enum { IDD = IDD_DIALOG_NEWCONTROLS };
	COXCoolCtrl<CIPAddressCtrl>	m_ipAddress;
	COXCoolCtrl<CMonthCalCtrl>	m_monthCal;
	COXCoolCtrl<CDateTimeCtrl>	m_dtpUpDown;
	COXCoolCtrl<CDateTimeCtrl>	m_dtpDropDown;
	COXCoolButton	m_btnDisable;
	BOOL	m_bDisable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageNewControls)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageNewControls)
	afx_msg void OnCheckDisableAll();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // _MSC_VER > 0x0421

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGENEWCONTROLS_H__3696ECEB_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
