// SpecialFXDlg.h : header file
//

#if !defined(AFX_SPECIALFXDLG_H__A0F3BB40_1B46_4C4B_99ED_2C97AF5C65AF__INCLUDED_)
#define AFX_SPECIALFXDLG_H__A0F3BB40_1B46_4C4B_99ED_2C97AF5C65AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSpecialFXDlg dialog
#include "CWaterRoutine.h"
#include "CFireRoutine.h"
#include "CPlasmaRoutine.h"
#include "DIBSectionLite.h"

class CSpecialFXDlg : public CDialog
{
// Construction
public:
	CSpecialFXDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpecialFXDlg)
	enum { IDD = IDD_SPECIALFX_DIALOG };
	CSliderCtrl	m_sldrPlasma;
	CSliderCtrl	m_sldrFire;
	CButton	m_chkWater;
	CButton	m_chkPlasma;
	CButton	m_chkFire;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpecialFXDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// member vars
	UINT			m_nTimer;
	CDIBSectionLite	m_bmpRenderSource;
	CDIBSectionLite m_bmpRenderTarget;


	CWaterRoutine	m_myWater;
	CFireRoutine	m_myFire;
	CPlasmaRoutine	m_myPlasma;

	BOOL			m_bRunWater;
	BOOL			m_bRunFire;
	BOOL			m_bRunPlasma;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpecialFXDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonanimate();
	afx_msg void OnButtonstop();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCheckfire();
	afx_msg void OnCheckplasma();
	afx_msg void OnCheckwater();
	afx_msg void OnReleasedcaptureSliderplasmaalpha(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderfirealpha(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECIALFXDLG_H__A0F3BB40_1B46_4C4B_99ED_2C97AF5C65AF__INCLUDED_)
