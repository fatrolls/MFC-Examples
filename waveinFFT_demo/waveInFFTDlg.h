// waveInFFTDlg.h : header file
//

#if !defined(AFX_WAVEINFFTDLG_H__B35B1921_6188_488A_9283_39FCE9E3DA70__INCLUDED_)
#define AFX_WAVEINFFTDLG_H__B35B1921_6188_488A_9283_39FCE9E3DA70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpectrumGraph.h"
#include "Recorder.h"
struct DataHolder
{
	void* pData;
	void* pData2;
};
/////////////////////////////////////////////////////////////////////////////
// CWaveInFFTDlg dialog

class CWaveInFFTDlg : public CDialog
{
// Construction
public:
	CWaveInFFTDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWaveInFFTDlg)
	enum { IDD = IDD_WAVEINFFT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveInFFTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CFrequencyGraph m_graph;
	CFrequencyGraph m_graph2;
	DataHolder m_data;
	Recorder m_rec;

	// Generated message map functions
	//{{AFX_MSG(CWaveInFFTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEqMode();
	afx_msg void OnMicroEq();
	afx_msg void OnOscilloscope();
	afx_msg void OnPeak();
	afx_msg void OnPeakAlt();
	afx_msg void OnPixelgram();
	afx_msg void OnSpectrum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL DestroyWindow();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEINFFTDLG_H__B35B1921_6188_488A_9283_39FCE9E3DA70__INCLUDED_)
