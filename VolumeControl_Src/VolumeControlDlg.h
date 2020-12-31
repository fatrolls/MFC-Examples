// VolumeControlDlg.h : header file
//

#if !defined(AFX_VOLUMECONTROLDLG_H__61F9B1DD_2170_4152_9C04_2A5992F8E6E4__INCLUDED_)
#define AFX_VOLUMECONTROLDLG_H__61F9B1DD_2170_4152_9C04_2A5992F8E6E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVolumeControlDlg dialog

class SystrayIcon;
class MouseHook;

class CVolumeControlDlg : public CDialog
{
// Construction
public:
	CVolumeControlDlg(CWnd* pParent = NULL);	// standard constructor
	~CVolumeControlDlg();

// Dialog Data
	//{{AFX_DATA(CVolumeControlDlg)
	enum { IDD = IDD_VOLUMECONTROL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVolumeControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVolumeControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();	
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMenuExit();
	virtual void OnCancel();
	afx_msg LONG OnTrayNotify( WPARAM wParam, LPARAM lParam );	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	void OnMixerControlChange( WPARAM wPrm, LPARAM lPrm );
	void OnMButtonUp( WPARAM wPrm, LPARAM lPrm );

private:

	void InvalidateIcon();

	SystrayIcon* m_pTrayIcon;
	MouseHook* m_pMouseHook;

	bool m_bIsMute;

	//FOR VOLUME CONTROL
	DWORD m_dwVolumeValue;
	DWORD m_dwPrevVolumeValue;

	UINT m_nNumMixers;
	HMIXER m_hMixer;
	MIXERCAPS m_mxcaps;

	CString m_strDstLineName, m_strVolumeControlName;
	DWORD m_dwMinimum, m_dwMaximum;
	DWORD m_dwVolumeControlID;

    bool m_bWasJetAudioMutedByUs;
    bool m_bWasWmpMutedByUs;
    bool m_bWasWinampMutedByUs;
    bool m_bWasiTunesMutedByUs;

private:

	BOOL UninitializeMixer();
	BOOL InitializeMixer();
	BOOL GetMasterVolumeControl();
	BOOL GetMasterVolumeValue( DWORD &dwVal ) const;
	BOOL SetMasterVolumeValue( DWORD dwVal ) const;

    void RedrawIcon( bool bMute = false );

    void OnSessionChange( WPARAM wPrm, LPARAM lPrm );
    void MuteVolume( bool bMute = true );

    void PauseJetAudio( bool bMute = true );
    void PauseWinamp( bool bMute = true );
    void PauseiTunes( bool bMute = true );
    void PauseWMP( bool bMute = true );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLUMECONTROLDLG_H__61F9B1DD_2170_4152_9C04_2A5992F8E6E4__INCLUDED_)
