// DemoDlg.h : header file
//

#if !defined(AFX_DEMODLG_H__AC8429F8_C181_44B2_838E_3FAFC1B7038C__INCLUDED_)
#define AFX_DEMODLG_H__AC8429F8_C181_44B2_838E_3FAFC1B7038C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

#include "BitmapSlider.h"

class CDemoDlg : public CDialog
{
// Construction
public:
	CDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_CBITMAPSLIDERDEMO_DIALOG };
	CBitmapSlider	m_sliderVol2;
	CBitmapSlider	m_sliderVol;
	CBitmapSlider	m_sliderBus;
	CBitmapSlider	m_sliderMP;
	CBitmapSlider	m_sliderBird;
	CBitmapSlider	m_sliderBalloon;
	int		m_nMax;
	int		m_nMin;
	int		m_nPos;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bEnable;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnApply();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDisable();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLG_H__AC8429F8_C181_44B2_838E_3FAFC1B7038C__INCLUDED_)
