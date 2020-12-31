#if !defined(AFX_TYPEAHEADCOMBO_H__10B86526_725D_11D1_8342_EB207C898677__INCLUDED_)
#define AFX_TYPEAHEADCOMBO_H__10B86526_725D_11D1_8342_EB207C898677__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TypeAheadCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTypeAheadCombo window

class CTypeAheadCombo : public CComboBox
{
// Construction
public:
	CTypeAheadCombo();

// Attributes
public:

	CComboEdit	m_xEdit;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypeAheadCombo)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTypeAheadCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTypeAheadCombo)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPEAHEADCOMBO_H__10B86526_725D_11D1_8342_EB207C898677__INCLUDED_)
