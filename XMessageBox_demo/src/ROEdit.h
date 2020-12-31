// ROEdit.h : header file
//

#ifndef ROEDIT_H
#define ROEDIT_H

/////////////////////////////////////////////////////////////////////////////
// CROEdit window

class CROEdit : public CEdit
{
// Construction
public:
	CROEdit();
	virtual ~CROEdit();

// Attributes
public:
	void SetWindowText(LPCTSTR lpszString);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROEdit)
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_brush;

	// Generated message map functions
protected:
	//{{AFX_MSG(CROEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //ROEDIT_H
