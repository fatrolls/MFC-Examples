// -----------------------------------------------------------------------------
// ControlGroup.h
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

#include <afxmt.h>
#include "..\AudioMixerAPI\Mixer.h"
#include "MixerSliderCtrl.h"
#include "MixerSliderHorz.h"
#include "MixerCheckBoxMute.h"

// -----------------------------------------------------------------------------
class CControlGroup
{
public:
	CControlGroup(void);
	virtual ~CControlGroup(void);

	int CreateControls( CMixer* pCMixer, int destIndex, CWnd* pcWnd, 
						int offsetX, int offsetY, unsigned int resourceID ) ;
	int UpdateMixerControlState( unsigned int winCtrlID ) ;
	int UpdateWinControlState( unsigned int mixerID ) ;

protected:
	struct sChannelData {
		sStateData stateData ;
		int nChannels ;
	} ;

	void InitGroupLabel(   CString csText, int nGroup, int offsetX, int offsetY ) ;
	void InitBalanceLabel( CString csText, int nGroup, int offsetX, int offsetY ) ;
	void InitVolLabel(     CString csText, int nGroup, int offsetX, int offsetY ) ;
	int  InitBalSlider( MIXERCONTROL mixerControl, sChannelData channelData, int nGroup, int offsetX, int offsetY ) ;
	int  InitVolSlider( MIXERCONTROL mixerControl, sChannelData channelData, int nGroup, int offsetX, int offsetY ) ;
	int  InitCheckBox(  MIXERCONTROL mixerControl, sChannelData channelData, int nGroup, int offsetX, int offsetY ) ;
	void GetDestTargetTypeStr( DWORD dwType, CString& strType ) ;
	int  GetControlsForID( unsigned int groupIndex, CMixerSliderCtrl** pVolCtrl, 
						   CMixerSliderHorz** pBalCtrl, CMixerCheckBoxMute** pMuteCtrl ) ;

	CMixer* mpCMixer ;
	CWnd* mpcWnd ;
	int mDestID ;
	int mConnID ;
	int mOffsetX ;
	int mOffsetY ;
	int mnGroups ; 
	unsigned int nextResourceID ;

	enum ctrlType {
		Bal = 0, 
		Vol, 
		Mute
	} ;

	struct sCtrl_LUT {
		unsigned int winCtrlID ;
		unsigned int mixerCtrlID ;
		unsigned int groupIndex ;
		ctrlType	 CtrlType ;	
		CWnd*		 cWnd ;
	} ;

	sCtrl_LUT* mpCtrl_LUT ;
	unsigned int Ctrl_LUT_Index ;
	unsigned int Ctrl_LUT_Count ;

	CStatic*			mpCStaticLabel ;
	CStatic*			mpCStaticBal ;
	CMixerSliderHorz*	mpCSliderCtrlBal ;
	CStatic*			mpCStaticVol ;
	CMixerSliderCtrl*	mpCSliderCtrlVol ;
	CMixerCheckBoxMute*	mpCCheckBoxMute ;
};

// -----------------------------------------------------------------------------
