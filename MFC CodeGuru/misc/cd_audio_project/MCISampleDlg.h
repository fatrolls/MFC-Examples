// MCISampleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMCISampleDlg dialog

#include "CdAudio.h"

class CMCISampleDlg : public CDialog
{
// Construction
public:
	CMCISampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMCISampleDlg)
	enum { IDD = IDD_MCISAMPLE_DIALOG };
	CButton	m_btnEject;
	CButton	m_btnPlaySection;
	CButton	m_btnPlay;
	CButton	m_btnStop;
	CButton	m_btnPause;
	CStatic	m_wndStatus;
	CComboBox	m_comboTrack;
	CString	m_strTrack;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMCISampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMCISampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnSelchangeTrackselect();
	afx_msg void OnClose();
	afx_msg void OnPause();
	afx_msg void OnEject();	
	afx_msg void OnPlaySection();
	//}}AFX_MSG
	afx_msg BOOL OnDeviceChange( UINT nEventType, DWORD dwData );
	afx_msg LONG OnMciNotify(UINT wParam, LONG lDevId);
	DECLARE_MESSAGE_MAP()
	
	CTmsf m_tmsfFrom;
	CTmsf m_tmsfTo;
	CCdAudio m_CdAudio;
	BYTE m_nTrackToPlay;

	void UpdateControls();
	void EnableControls(BOOL bEnablePlay, BOOL bEnableStop = TRUE);
};
