// DirectSoundTestDlg.h : header file
//

#if !defined(AFX_DIRECTSOUNDTESTDLG_H__68C8C315_C5F5_4040_B6F2_DAC103EB350C__INCLUDED_)
#define AFX_DIRECTSOUNDTESTDLG_H__68C8C315_C5F5_4040_B6F2_DAC103EB350C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWaveFile;
class CMyDirectSound;
class CDirectSoundTestDlg : public CDialog
{
// Construction
public:

	CDirectSoundTestDlg(CWnd* pParent = NULL);	// standard constructor
	void TimerCallback();
	HRESULT GetAudioSamples(LPBYTE lpDesBuf, const DWORD dwRequiredBytes, DWORD &dwRetBytes);

// Dialog Data
	//{{AFX_DATA(CDirectSoundTestDlg)
	enum { IDD = IDD_DIRECTSOUNDTEST_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectSoundTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDirectSoundTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	virtual void OnOK();
	afx_msg void OnPlay();
	afx_msg void OnPause();
	afx_msg void OnStop();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CWaveFile *m_pWavFile;	
	CString m_strFileName;
	CMyDirectSound *m_pMyDS;
	CSliderCtrl	m_ctrlPlaySlider;
	int			m_iBeginPlayPos;
	MMRESULT m_timerID;
};
//</CDirectSoundTestDlg>

#endif // !defined(AFX_DIRECTSOUNDTESTDLG_H__68C8C315_C5F5_4040_B6F2_DAC103EB350C__INCLUDED_)
