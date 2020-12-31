// ColorSelectorDlg.h : header file
//

#if !defined(AFX_COLORSELECTORDLG_H__73571DD9_02C8_4867_B81F_D7134BA5FAFB__INCLUDED_)
#define AFX_COLORSELECTORDLG_H__73571DD9_02C8_4867_B81F_D7134BA5FAFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BuddiedSliderCtrl.h"
#include "SpectrumWnd.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CColorSelectorDlg dialog

class CColorSelectorDlg : public CDialog
{
// Construction
public:
	CBrush m_brSampleColor;
	CSpectrumWnd m_wndSpectrum;
	CColorSelectorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CColorSelectorDlg)
	enum { IDD = IDD_COLORSELECTOR_DIALOG };
	CStatic	m_ctlSampleColor;
	CBuddiedSliderCtrl	m_ctlSlideRed;
	CBuddiedSliderCtrl	m_ctlSlideLum;
	CBuddiedSliderCtrl	m_ctlSlideGreen;
	CBuddiedSliderCtrl	m_ctlSlideBlue;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorSelectorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CColorSelectorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnCopyValueToClipboard();
	//}}AFX_MSG
	afx_msg LRESULT OnSpectrumWindowEvent(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSELECTORDLG_H__73571DD9_02C8_4867_B81F_D7134BA5FAFB__INCLUDED_)
