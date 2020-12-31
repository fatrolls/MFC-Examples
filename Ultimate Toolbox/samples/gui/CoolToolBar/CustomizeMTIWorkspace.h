#if !defined(AFX_CUSTOMIZEMTIWORKSPACE_H__229EBDA3_561B_11D2_B475_00E0291A4FD3__INCLUDED_)
#define AFX_CUSTOMIZEMTIWORKSPACE_H__229EBDA3_561B_11D2_B475_00E0291A4FD3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomizeMTIWorkspace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomizeMTIWorkspace dialog

class CCustomizeMTIWorkspace : public CDialog
{
// Construction
public:
	CCustomizeMTIWorkspace(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeMTIWorkspace)
	enum { IDD = IDD_MTICUSTOMIZE };
	CSpinButtonCtrl	m_spinOffset;
	CListBox	m_lbStyles;
	DWORD	m_dwOffset;
	//}}AFX_DATA
	DWORD m_dwStyle;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeMTIWorkspace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomizeMTIWorkspace)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZEMTIWORKSPACE_H__229EBDA3_561B_11D2_B475_00E0291A4FD3__INCLUDED_)
