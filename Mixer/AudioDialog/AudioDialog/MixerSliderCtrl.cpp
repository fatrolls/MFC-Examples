// -----------------------------------------------------------------------------
// MixerSliderCtrl.cpp : implementation file
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// -----------------------------------------------------------------------------

#include "stdafx.h"
#include "MixerSliderCtrl.h"

// -----------------------------------------------------------------------------
// CMixerSliderCtrl

IMPLEMENT_DYNAMIC(CMixerSliderCtrl, CSliderCtrl)

// -----------------------------------------------------------------------------
CMixerSliderCtrl::CMixerSliderCtrl()
{
	mStateDataSize = 2*sizeof(MIXERCONTROLDETAILS_UNSIGNED) ;
}

// -----------------------------------------------------------------------------
CMixerSliderCtrl::~CMixerSliderCtrl()
{
}

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CMixerSliderCtrl, CSliderCtrl)
END_MESSAGE_MAP()

// -----------------------------------------------------------------------------
int CMixerSliderCtrl::Init(MIXERCONTROL mixerControl, int nChannels, void* state )
{
	mnRangeMax = mixerControl.Bounds.dwMaximum ;
	mnRangeMin = mixerControl.Bounds.dwMinimum ; 
	mnDelta = mnRangeMax - mnRangeMin ;
	DWORD dwMaxVol ;
	int thumbPos ;
	DWORD dwLeft ;
	DWORD dwRight ;
	int n1 ;

	SetRangeMin( 0, FALSE ) ;		// Slider minimum is zero	
	SetRangeMax( mnDelta, TRUE  ); 	// Slider maximum is mnDelta

	for( n1=0 ; n1<6 ; n1++ )		// 7 Tics
	{
		thumbPos = (n1*mnDelta)/6 ;
		SetTic( thumbPos ) ;
	}

	// Save state data
	memcpy( (void*)&mStateData, (void*)state, mStateDataSize ) ;

	dwLeft  = mStateData.Left.dwValue; 
	dwRight = mStateData.Right.dwValue ; 
	dwMaxVol = ( dwLeft < dwRight ) ? dwRight : dwLeft ;	// Get max volume

	SetPos( mnDelta - dwMaxVol ) ;

	return 1 ;
}

// -----------------------------------------------------------------------------
// Get the current slider position in terms of the volume range. Assumes that if  
// the channels are in balance, both L and R vol values are the same and equal 
// to the volume range, mnDelta. 
// -----------------------------------------------------------------------------
int CMixerSliderCtrl::GetCurrentPos( DWORD* vol, DWORD* range )
{
	*vol = mnDelta - GetPos() ;
	*range = mnDelta ;

	return *vol ;
}

// -----------------------------------------------------------------------------
int CMixerSliderCtrl::SetCurrentPos( unsigned int volLeft, unsigned int volRight )
{
	int maxVol = ( volLeft < volRight ) ? volRight : volLeft ;	// Get max volume
	SetPos( mnDelta - maxVol ) ; 

	return maxVol ;
}

// -----------------------------------------------------------------------------
// CMixerSliderCtrl message handlers
// -----------------------------------------------------------------------------
