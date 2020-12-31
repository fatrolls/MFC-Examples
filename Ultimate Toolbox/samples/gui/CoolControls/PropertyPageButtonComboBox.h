#if !defined(AFX_PROPERTYPAGEBUTTONCOMBOBOX_H__3696ECE6_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
#define AFX_PROPERTYPAGEBUTTONCOMBOBOX_H__3696ECE6_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyPageButtonComboBox.h : header file
//

#include "OXCoolComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageButtonComboBox dialog

class CPropertyPageButtonComboBox : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropertyPageButtonComboBox)

// Construction
public:
	CPropertyPageButtonComboBox();
	~CPropertyPageButtonComboBox();

// Dialog Data
	//{{AFX_DATA(CPropertyPageButtonComboBox)
	enum { IDD = IDD_DIALOG_BUTTON_COMBOBOX };
	COXCoolButton	m_btnPush3;
	COXCoolButton	m_btnPush2;
	COXCoolButton	m_radio1;
	COXCoolButton	m_radio2;
	COXCoolButton	m_radio3;
	COXCoolButton	m_radioPushlike1;
	COXCoolButton	m_radioPushlike2;
	COXCoolButton	m_radioPushlike3;
	COXCoolComboBox	m_comboSimple;
	COXCoolComboBox	m_comboDropdownlist;
	COXCoolComboBox	m_comboDropdown;
	COXCoolButton	m_btnCheckRight;
	COXCoolButton	m_btnCheckPushlike;
	COXCoolButton	m_btnCheckLeft;
	COXCoolButton	m_btnDisable;
	COXCoolButton	m_btnPush1;
	COXCoolButton	m_btnDefault;
	BOOL	m_bDisable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageButtonComboBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageButtonComboBox)
	afx_msg void OnCheckDisableAll();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEBUTTONCOMBOBOX_H__3696ECE6_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
