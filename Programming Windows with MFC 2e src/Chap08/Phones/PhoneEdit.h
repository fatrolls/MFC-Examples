#if !defined(AFX_PHONEEDIT_H__7BE4B251_90ED_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_PHONEEDIT_H__7BE4B251_90ED_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PhoneEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPhoneEdit window

class CPhoneEdit : public CEdit
{
// Construction
public:
	CPhoneEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhoneEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPhoneEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPhoneEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHONEEDIT_H__7BE4B251_90ED_11D2_8E53_006008A82731__INCLUDED_)
