// -----------------------------------------------------------------------------
// AudioControlsDlg.h : header file
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// -----------------------------------------------------------------------------

#pragma once
#include "..\MixerLib\Mixer.h"


// -----------------------------------------------------------------------------
// CVolumeControlDlg dialog
class CVolumeControlDlg : public CDialog
{
// Construction
public:
	CVolumeControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VOLUMECONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CSliderCtrl* mpVolCtrl ;
	CMixer mCMixer ;
	unsigned int mCtrlID ;
	sStateData mStateData ;
	long mnRangeMax ;
	long mnRangeMin ;
	long mnDelta ; 
	long mnVolStep ;
	long mBalLeft ;
	long mBalRight ;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// Vol control specific functions
	int InitVolSlider(MIXERCONTROL mixerControl, int nChannels, sStateData* state);
	int GetCurrentPos(DWORD* vol, DWORD* range);
	int SetCurrentPos(unsigned int volLeft, unsigned int volRight);
	long OnMixerControlChange( WPARAM wParam, LPARAM lParam ) ;

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

// -----------------------------------------------------------------------------
