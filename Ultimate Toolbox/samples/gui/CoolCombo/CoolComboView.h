// CoolComboView.h : interface of the CCoolComboView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COOLCOMBOVIEW_H__FE6B1BD1_A5BD_11D2_B475_00E0291A4FD3__INCLUDED_)
#define AFX_COOLCOMBOVIEW_H__FE6B1BD1_A5BD_11D2_B475_00E0291A4FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "OXSeparator.h"
#include "OXCoolComboBox.h"

class CCoolComboView : public CFormView
{
protected: // create from serialization only
	CCoolComboView();
	DECLARE_DYNCREATE(CCoolComboView)

public:
	//{{AFX_DATA(CCoolComboView)
	enum { IDD = IDD_COOLCOMBO_FORM };
	COXSeparator	m_separator;
	COXSeparator	m_heading;
	COXCoolComboBox	m_combo;
	BOOL	m_bCoolState;
	BOOL	m_bDisabled;
	BOOL	m_bDisabledInToolbar;
	CString	m_sTooltipText;
	int		m_nComboStyle;
	//}}AFX_DATA

// Attributes
public:
	CCoolComboDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolComboView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCoolComboView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void RecreateCombo(const DWORD dwAddStyle, const DWORD dwRemoveStyle);
	void PopulateCombo();

// Generated message map functions
protected:
	//{{AFX_MSG(CCoolComboView)
	afx_msg void OnCheckCool();
	afx_msg void OnCheckDisable();
	afx_msg void OnCheckDisableintoolbar();
	afx_msg void OnChangeEditTooltiptext();
	afx_msg void OnRadioDropdown();
	afx_msg void OnRadioDropdownlist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CoolComboView.cpp
inline CCoolComboDoc* CCoolComboView::GetDocument()
   { return (CCoolComboDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLCOMBOVIEW_H__FE6B1BD1_A5BD_11D2_B475_00E0291A4FD3__INCLUDED_)
