#if !defined(AFX_COMBOEDIT_H__8C929806_75F2_11D1_A694_006097A45E77__INCLUDED_)
#define AFX_COMBOEDIT_H__8C929806_75F2_11D1_A694_006097A45E77__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ComboEdit.h : header file
//

class CTypeAheadCombo;

/////////////////////////////////////////////////////////////////////////////
// CComboEdit window

class CComboEdit : public CEdit
{
// Construction
public:
	CComboEdit();

// Attributes
protected:
	int					m_nStartAfter;
	bool				m_bHighlighted;
	bool				m_bBackspace;
	bool				m_bDelete;
	CString				m_SearchString;
	WORD				m_nPos;

// Operations
protected:
	void DoFind(UINT nChar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOEDIT_H__8C929806_75F2_11D1_A694_006097A45E77__INCLUDED_)
