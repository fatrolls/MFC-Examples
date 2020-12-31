#if !defined(AFX_SCALEROLLUPDLG_H__FA4A5D82_7AB2_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_SCALEROLLUPDLG_H__FA4A5D82_7AB2_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScaleRollupDlg.h : header file
//

#include "oxrollup.h"
#include "OXSpinCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CScaleRollupDlg dialog

class CScaleRollupDlg : public COXRollup
{
// Construction
public:
	CScaleRollupDlg(CWnd* pParent = NULL);   // standard constructor
	// overridden from base class
	LPCTSTR GetTitleBarBitmap() { return _T("TITLEBAR_BMP"); }

	void ShowControls();

// Dialog Data
	//{{AFX_DATA(CScaleRollupDlg)
	enum { IDD = IDD_DIALOG_ROLLUP };
	CEdit	m_ctlZoomLevel;
	COXSpinCtrl	m_ctlSpinZoom;
	CStatic	m_ctlPicture;
	UINT	m_nScaledHeight;
	UINT	m_nScaledWidth;
	int		m_nZoomLevel;
	//}}AFX_DATA
	// original height and width
	// of the current image
	UINT	m_nOrigHeight;
	UINT	m_nOrigWidth;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScaleRollupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CScaleRollupDlg)
	afx_msg void OnButtonApply();
	afx_msg void OnChangeZoomLevel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCALEROLLUPDLG_H__FA4A5D82_7AB2_11D1_A3D5_0080C83F712F__INCLUDED_)
