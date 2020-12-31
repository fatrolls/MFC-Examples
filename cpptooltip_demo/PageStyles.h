#if !defined(AFX_PAGESTYLES_H__5A4FE9A3_B1E6_11D7_84BD_00C026A7402A__INCLUDED_)
#define AFX_PAGESTYLES_H__5A4FE9A3_B1E6_11D7_84BD_00C026A7402A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageStyles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageStyles dialog

class CPageStyles : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageStyles)

// Construction
public:
	CPageStyles();
	~CPageStyles();

// Dialog Data
	//{{AFX_DATA(CPageStyles)
	enum { IDD = IDD_PAGE_STYLES };
	int		m_anchor_placement;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageStyles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageStyles)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangePlacement();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESTYLES_H__5A4FE9A3_B1E6_11D7_84BD_00C026A7402A__INCLUDED_)
