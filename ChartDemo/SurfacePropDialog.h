#if !defined(AFX_SURFACEPROPDIALOG_H__88893012_E2F3_477F_833A_B3D7B10CC8A8__INCLUDED_)
#define AFX_SURFACEPROPDIALOG_H__88893012_E2F3_477F_833A_B3D7B10CC8A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SurfacePropDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSurfacePropDialog dialog

class CSurfacePropDialog : public CDialog
{
// Construction
public:
	CSurfacePropDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSurfacePropDialog)
	enum { IDD = IDD_SURFACEPROP_DLG };
	int		m_iHorizSurf;
	int		m_FillStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSurfacePropDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSurfacePropDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SURFACEPROPDIALOG_H__88893012_E2F3_477F_833A_B3D7B10CC8A8__INCLUDED_)
