// -----------------------------------------------------------------------------
// MixerSliderHorz.h
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
// CMixerSliderHorz

// -----------------------------------------------------------------------------
class CMixerSliderHorz : public CSliderCtrl
{
	DECLARE_DYNAMIC(CMixerSliderHorz)

public:
	CMixerSliderHorz();
	virtual ~CMixerSliderHorz();

	int Init(MIXERCONTROL mixerControl, int nChannels, void* state ) ;
	int GetCurrentPos( DWORD* volLeft, DWORD* volRight, int* range ) ;
	int SetCurrentPos( DWORD  volLeft, DWORD  volRight ) ;

protected:
	int mnRangeMin ;
	int mnRangeMax ;
	int mnDelta ; 
	int mnDoubleDelta ; 
	unsigned long mBalLeft ;
	unsigned long mBalRight ;

	sStateData mStateData ;
	unsigned int mStateDataSize ;

	DECLARE_MESSAGE_MAP()
};

// -----------------------------------------------------------------------------
