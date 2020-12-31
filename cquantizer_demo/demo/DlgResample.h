#if !defined(AFX_DLGRESAMPLE_H__96A4AF61_B1E5_11D5_8DD4_00E07D8144D0__INCLUDED_)
#define AFX_DLGRESAMPLE_H__96A4AF61_B1E5_11D5_8DD4_00E07D8144D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgResample.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgResample dialog

class DlgResample : public CDialog
{
// Construction
public:
	DlgResample(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgResample)
	enum { IDD = IDD_DIALOG3 };
	float	m_factor;
	BOOL	m_fast;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgResample)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgResample)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRESAMPLE_H__96A4AF61_B1E5_11D5_8DD4_00E07D8144D0__INCLUDED_)
