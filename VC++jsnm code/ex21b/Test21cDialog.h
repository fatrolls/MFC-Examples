#if !defined(AFX_TEST21CDIALOG_H__CBB31424_974D_11D0_BED2_00C04FC2A0C2__INCLUDED_)
#define AFX_TEST21CDIALOG_H__CBB31424_974D_11D0_BED2_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

extern "C" __declspec(dllimport) double Ex21cSquareRoot(double d);

// Test21cDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTest21cDialog dialog

class CTest21cDialog : public CDialog
{
// Construction
public:
	CTest21cDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTest21cDialog)
	enum { IDD = IDD_EX21C };
	double	m_dInput;
	double	m_dOutput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest21cDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTest21cDialog)
	afx_msg void OnCompute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST21CDIALOG_H__CBB31424_974D_11D0_BED2_00C04FC2A0C2__INCLUDED_)
