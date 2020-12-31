// multiplayerDlg.h : header file
//

#if !defined(AFX_MULTIPLAYERDLG_H__53AA7027_F925_407D_BA23_9F931D9E07B4__INCLUDED_)
#define AFX_MULTIPLAYERDLG_H__53AA7027_F925_407D_BA23_9F931D9E07B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMultiplayerDlg dialog
#include "SndMan.h"

class CMultiplayerDlg : public CDialog
{
// Construction
public:
	CMultiplayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMultiplayerDlg)
	enum { IDD = IDD_MULTIPLAYER_DIALOG };
	CListBox	m_PlayEvenList;
	CComboBox	m_comboPlayList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiplayerDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
        
    CSoundManager* m_pSndMan; 

	// Generated message map functions
	//{{AFX_MSG(CMultiplayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnVMnormal();
	afx_msg void OnBtnVMfadein();
	afx_msg void OnBtnVMfadeout();
	afx_msg void OnBtnPMnormal();
	afx_msg void OnBtnPMloop();
	afx_msg void OnBtnStatusplay();
	afx_msg void OnBtnStatusstop();
	afx_msg void OnBtnspeedup();
	afx_msg void OnBtnspeeddown();
	afx_msg void OnBtnvolumeup();
	afx_msg void OnBtnvolumedown();
	afx_msg void OnBtnleftup();
	afx_msg void OnBtnleftdown();
	afx_msg void OnBtnrightup();
	afx_msg void OnBtnrightdown();
	afx_msg void OnBtnpancenter();
	afx_msg void OnPlayall();
	afx_msg void OnStopall();
	afx_msg void OnFileopen();
	afx_msg void OnSelchangeComboplaylist();
	afx_msg void OnBtnreset();
	//}}AFX_MSG
    afx_msg LONG OnDSBPlayEnd(UINT uiParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIPLAYERDLG_H__53AA7027_F925_407D_BA23_9F931D9E07B4__INCLUDED_)
