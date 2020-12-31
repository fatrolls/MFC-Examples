// ChartDemoDlg.h : header file
//

#if !defined(AFX_CHARTDEMODLG_H__1C3B17D7_0821_47FC_B873_9D9337728F79__INCLUDED_)
#define AFX_CHARTDEMODLG_H__1C3B17D7_0821_47FC_B873_9D9337728F79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartCtrl.h"
#include "ColourPicker.h"
#include "ChartLineSerie.h"

/////////////////////////////////////////////////////////////////////////////
// CChartDemoDlg dialog

class CChartDemoDlg : public CDialog
{
// Construction
public:
	CChartDemoDlg(CWnd* pParent = NULL);	// standard constructor
 
// Dialog Data
	//{{AFX_DATA(CChartDemoDlg)
	enum { IDD = IDD_CHARTDEMO_DIALOG };
	CEdit	m_TitlesEdit;
	CListBox	m_SeriesList;
	CEdit	m_AxisMinValEdit;
	CEdit	m_AxisMaxValEdit;
	CButton	m_LegendVisBtn;
	CColourPicker	m_BackgndColSel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChartDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddseries();
	afx_msg void OnLegendVisible();
	afx_msg void OnBottomAxisRadio();
	afx_msg void OnLeftAxisRadio();
	afx_msg void OnRightAxisRadio();
	afx_msg void OnTopAxisRadio();
	afx_msg void OnAxisAutomaticCheck();
	afx_msg void OnAxisGridVisCheck();
	afx_msg void OnAxisVisibleCheck();
	afx_msg void OnAxisScrollBarCheck();
	afx_msg LONG OnChangeBckCol(UINT lParam, LONG wParam);
	afx_msg void OnChangeAxisMax();
	afx_msg void OnChangeAxisMin();
	afx_msg void OnAxisInvertedCheck();
	afx_msg void OnChangeAxisLabel();
	afx_msg void OnDeleteSeries();
	afx_msg void OnChangeTitle();
	afx_msg void OnPanCheck();
	afx_msg void OnZoomCheck();
	afx_msg void OnSaveImage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
 
	CChartAxis* GetSelectedAxis();

	CChartCtrl m_ChartCtrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTDEMODLG_H__1C3B17D7_0821_47FC_B873_9D9337728F79__INCLUDED_)
