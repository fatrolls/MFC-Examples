#if !defined(AFX_CUSTOMIZERULERSDLG_H__12E49EA1_E788_11D2_A7F6_525400DAF3CE__INCLUDED_)
#define AFX_CUSTOMIZERULERSDLG_H__12E49EA1_E788_11D2_A7F6_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomizeRulersDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomizeRulersDlg dialog

class CCustomizeRulersDlg : public CDialog
{
// Construction
public:
	CCustomizeRulersDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeRulersDlg)
	enum { IDD = IDD_DIALOG_RULERS };
	BOOL	m_bShowHorz;
	BOOL	m_bShowVert;
	int		m_nUnit;
	UINT	m_nSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeRulersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomizeRulersDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZERULERSDLG_H__12E49EA1_E788_11D2_A7F6_525400DAF3CE__INCLUDED_)
