#if !defined(AFX_EXPORTDLG_H__645E3D42_7531_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_EXPORTDLG_H__645E3D42_7531_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ExportDlg.h : header file
//

#include "OXHistoryCombo.h"
#include "OXSpinCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CExportDlg dialog

class CExportDlg : public CDialog
{
// Construction
protected:
	CButton& ctlOptimize() { return *(CButton*)GetDlgItem(IDC_CHECK_OPTIMIZE); }
	void ShowButtons();
	BOOL CheckFileName();

public:
	CExportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExportDlg)
	enum { IDD = IDD_DIALOG_EXPORT };
	CEdit	m_ctlEditSmooth;
	CEdit	m_ctlEditQuality;
	COXSpinCtrl	m_ctlSpinSmooth;
	COXSpinCtrl	m_ctlSpinQuality;
	COXHistoryCombo	m_cbFileName;
	BOOL	m_bBaseline;
	BOOL	m_bGrayscale;
	BOOL	m_bOptimize;
	BOOL	m_bProgressive;
	BOOL	m_bSmooth;
	CString	m_sFileName;
	UINT	m_nQuality;
	UINT	m_nSmooth;
	//}}AFX_DATA
	// we use mem file as temporarily one to export info to JPEG file
	CMemFile m_tmpBMPFile;
	BOOL m_bCheckFileName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CExportDlg)
	afx_msg void OnCheckProgressive();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTDLG_H__645E3D42_7531_11D1_A3D5_0080C83F712F__INCLUDED_)
