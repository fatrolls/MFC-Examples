// -----------------------------------------------------------------------------
// MixerSliderCtrl.h
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
#include "..\AudioMixerAPI\Mixer.h"

// -----------------------------------------------------------------------------
// CMixerSliderCtrl

// -----------------------------------------------------------------------------
class CMixerSliderCtrl : public CSliderCtrl
{
	DECLARE_DYNAMIC(CMixerSliderCtrl)

public:
	CMixerSliderCtrl();
	virtual ~CMixerSliderCtrl();

	int Init(MIXERCONTROL mixerControl, int nChannels, void* state ) ;
	int GetCurrentPos( DWORD* vol, DWORD* range ) ;
	int SetCurrentPos( unsigned int volLeft, unsigned int volRight ) ;
	
protected:
	int mnRangeMin ;
	int mnRangeMax ;
	int mnDelta ; 

	sStateData mStateData ;
	unsigned int mStateDataSize ;

	DECLARE_MESSAGE_MAP()
} ;

// -----------------------------------------------------------------------------
