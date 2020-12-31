/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#if !defined(AFX_DLGCOMBOCHOICE_H__8ADC43A3_A1BA_11D3_B733_00C04F6A7AE6__INCLUDED_)
#define AFX_DLGCOMBOCHOICE_H__8ADC43A3_A1BA_11D3_B733_00C04F6A7AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgComboChoice.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgComboChoice dialog

class CDlgComboChoice : public CDialog
{
// Construction
public:
	CDlgComboChoice(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgComboChoice)
	enum { IDD = IDD_COMBO_CHOICE };
	int		m_iRadio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgComboChoice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgComboChoice)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOMBOCHOICE_H__8ADC43A3_A1BA_11D3_B733_00C04F6A7AE6__INCLUDED_)
