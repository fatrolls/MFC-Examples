// -----------------------------------------------------------------------------
// AudioDialogDlg.h : header file
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

#include "stdafx.h"
#include "AudioDialog.h"

#include "afxcmn.h"
#include "MixerCapsDlg.h"
#include "DestinationsDialog.h"
#include "ControlsDialog.h"
#include "..\AudioMixerAPI\MixerDestination.h"
#include "..\AudioMixerAPI\Mixer.h"
#include "ControlGroup.h"

// -----------------------------------------------------------------------------
// CAudioDialogDlg dialog
// -----------------------------------------------------------------------------
class CAudioDialogDlg : public CDialog
{
// Construction
public:
	CAudioDialogDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CAudioDialogDlg();

// Dialog Data
	enum { IDD = IDD_AUDIODIALOG_DIALOG };

	protected:

// Implementation
protected:
	void HideDataDialogs(void) ;
	void UpdateConnectionInfoDialog() ;
	void UpdateDestInfoDialog() ;
	void UpdateMixerInfoDialog() ;
	void UpdateConnectionControlInfoDialog() ;
	void UpdateDestControlInfoDialog() ;
	void CreateCtrlArray( int mixerIndex, int destIndex ) ;
	void OnCheckBoxClicked(unsigned int nCtrlID) ;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HICON m_hIcon;
	unsigned int			mMixerCount;		// Number of mixers found 
	HMIXER					mhMixer;			// Mixer handle
	CMixerCapsDlg*			mpMixerDlg ;
	CDestinationsDialog*	mpDestinationsDlg ;	// IDD_DESTINATIONS_DIALOG
	CDestinationsDialog*	mpConnectionDlg ;
	CControlsDialog*		mpControlsDlg ;		// IDD_CONTROLS_DIALOG
	unsigned int			mnNextResourceID ;	// Next ID of dynamically created control
	CControlGroup*			mpControlGroup ;	
	unsigned int			mnGroupHorzOffset ;
	int						mnScrollPos ;
	int						mnScrollThumbWidth ;
	int						mnScrollMax ;
	CFont					mFont ;


	struct SMixerLineControlInfo {		// One for each destination
		unsigned int nControls ;		// Number of controls for this destination
		MIXERLINECONTROLS lineControls ;
		MIXERCONTROL* pControlInfo ;	// One for each of the nControls
	} ;

	struct SMixerInfo {
		unsigned int nDestinations ; 
		MIXERCAPS  mixerCaps ;
		MIXERLINE* pMixerLineInfo ;			  // One for each destination
		SMixerLineControlInfo* pControlData	; // One for each destination
	} ;
	
	SMixerInfo* mpMixerInfo ;
	CMixer* mpCMixer ;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCbnSelchangeMixerSelectCombo();
	afx_msg void OnCbnSelchangeComboDest();
	afx_msg void OnCbnSelchangeComboConnectionControl();
	afx_msg void OnCbnSelchangeComboDestControl();
	afx_msg void OnCbnSelchangeCombo();
	afx_msg void OnBnClickedMixerButton();
	afx_msg void OnBnClickedDestButton();
	afx_msg void OnBnClickedDestCtrlButton();
	afx_msg void OnBnClickedConnectionButton();
	afx_msg void OnBnClickedConnCtrlButton();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// Manually added:
	long OnMixerControlChange( WPARAM wParam, LPARAM lParam ) ;
	long OnMixerLineChange( WPARAM wParam, LPARAM lParam ) ;

	DECLARE_MESSAGE_MAP()
};
// -----------------------------------------------------------------------------
