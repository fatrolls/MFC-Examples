#if !defined(AFX_RESAMPLEIMAGEDLG_H__366C6742_8B7A_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_RESAMPLEIMAGEDLG_H__366C6742_8B7A_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ResampleImageDlg.h : header file
//

#include "OXSpinCtrl.h"
#include "DIBManagerDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CResampleImageDlg dialog

class CResampleImageDlg : public CDialog
{
// Construction
public:
	CResampleImageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResampleImageDlg)
	enum { IDD = IDD_DIALOG_RESAMPLE };
	CButton	m_ctlCheckMatchZoomLevel;
	CButton	m_ctlCheckConvertTo;
	CEdit	m_ctlEditWidthPixels;
	CEdit	m_ctlEditWidthPercents;
	COXSpinCtrl	m_ctlSpinWidthPixels;
	COXSpinCtrl	m_ctlSpinWidthPercents;
	COXSpinCtrl	m_ctlSpinHeightPixels;
	COXSpinCtrl	m_ctlSpinHeightPercents;
	CEdit	m_ctlEditHeightPixels;
	CEdit	m_ctlEditHeightPercents;
	CComboBox	m_ctlComboConvertTo;
	CButton	m_ctlCheckMaintainRatio;
	BOOL	m_bMaintainRatio;
	BOOL	m_bMatchZoomLevel;
	CString	m_sHeightOrig;
	CString	m_sWidthOrig;
	UINT	m_nWidthPercents;
	UINT	m_nWidthPixels;
	UINT	m_nHeightPercents;
	UINT	m_nHeightPixels;
	BOOL	m_bConvertTo;
	int		m_nConvertTo;
	//}}AFX_DATA
	UINT m_nCurrentZoomLevel;
	// we provide convertion only of 24-bit image to 8-bit
	BOOL m_bCanConvert;
	// we provide resizing only of 24-bit or 8-bit images
	BOOL m_bCanResize;
	// original height and width
	// of the current image
	UINT	m_nOrigHeight;
	UINT	m_nOrigWidth;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResampleImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ShowControls(BOOL bHeightChanged=FALSE);

	// Generated message map functions
	//{{AFX_MSG(CResampleImageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckConvertTo();
	afx_msg void OnCheckMaintainRatio();
	afx_msg void OnCheckMatchZoomLevel();
	afx_msg void OnChangeHeightPercents();
	afx_msg void OnChangeHeightPixels();
	afx_msg void OnChangeWidthPercents();
	afx_msg void OnChangeWidthPixels();
	afx_msg void OnButtonReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESAMPLEIMAGEDLG_H__366C6742_8B7A_11D1_A3D5_0080C83F712F__INCLUDED_)
