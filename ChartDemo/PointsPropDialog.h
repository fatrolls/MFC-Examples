#if !defined(AFX_POINTSPROPDIALOG_H__F83DDA1D_53B7_457E_B354_02462E1C8568__INCLUDED_)
#define AFX_POINTSPROPDIALOG_H__F83DDA1D_53B7_457E_B354_02462E1C8568__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointsPropDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointsPropDialog dialog

class CPointsPropDialog : public CDialog
{
// Construction
public:
	CPointsPropDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPointsPropDialog)
	enum { IDD = IDD_POINTPROP_DLG };
	int		m_iPointsHeight;
	int		m_iPointsWidth;
	int		m_iPointsType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointsPropDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointsPropDialog)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTSPROPDIALOG_H__F83DDA1D_53B7_457E_B354_02462E1C8568__INCLUDED_)
