// SounderDlg.h : header file
//

#if !defined(AFX_SOUNDERDLG_H__139DFB65_C00E_402E_BFFF_6E0BC3A7A949__INCLUDED_)
#define AFX_SOUNDERDLG_H__139DFB65_C00E_402E_BFFF_6E0BC3A7A949__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DirectSound.h"
using namespace DirectSound;

/////////////////////////////////////////////////////////////////////////////
// CSounderDlg dialog

class CSounderDlg : public CDialog
{
	CDSound		m_dsound;
	CDSoundPlay m_player;
	BOOL m_bRunning;
private:
	BOOL _Load();
// Construction
public:
	CSounderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSounderDlg)
	enum { IDD = IDD_SOUNDER_DIALOG };
	CSliderCtrl	m_sliderVolume;
	CSliderCtrl	m_sliderPan;
	CSliderCtrl	m_sliderFreq;
	CString	m_strPath;
	BOOL	m_bRepeat;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSounderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSounderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnPlayStop();
	afx_msg void OnDestroy();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	static CSounderDlg *pThis;
	static LONG NotifyCallback(LONG f);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDERDLG_H__139DFB65_C00E_402E_BFFF_6E0BC3A7A949__INCLUDED_)
