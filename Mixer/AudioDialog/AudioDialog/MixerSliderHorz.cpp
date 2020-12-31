// -----------------------------------------------------------------------------
// MixerSliderHorz.cpp : implementation file
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
#include "MixerSliderHorz.h"

// -----------------------------------------------------------------------------
// CMixerSliderHorz

IMPLEMENT_DYNAMIC(CMixerSliderHorz, CSliderCtrl)

// -----------------------------------------------------------------------------
CMixerSliderHorz::CMixerSliderHorz()
{
	mStateDataSize = 2*sizeof(MIXERCONTROLDETAILS_UNSIGNED) ;
}

// -----------------------------------------------------------------------------
CMixerSliderHorz::~CMixerSliderHorz()
{
}

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CMixerSliderHorz, CSliderCtrl)
END_MESSAGE_MAP()

// -----------------------------------------------------------------------------
// Set the slider thumb position according to the current channel vol values. 
// Each channel can range from bounds.min to bounds.max, if the channels are in 
// balance, both L and R vol values are the same and equal to the current volume. 
// Hence the channel with the larger value is equal to the current volume setting.
//
// Returns -1 on error or if there are less than two channels.
// -----------------------------------------------------------------------------
int CMixerSliderHorz::Init(MIXERCONTROL mixerControl, int nChannels, void* state )
{
	mnRangeMax = mixerControl.Bounds.dwMaximum ;
	mnRangeMin = mixerControl.Bounds.dwMinimum ; 
	mnDelta = mnRangeMax - mnRangeMin ;

	mnDoubleDelta = 2*mnDelta ;

	if( nChannels < 2 )	// Must have two channels to have a balance
		return -1 ;

	SetRangeMin( 0, FALSE );			// Slider minimum is zero
	SetRangeMax( mnDoubleDelta, TRUE ); // Slider maximum is 2*mnDelta

	SetTic( 0 );
	SetTic( mnDelta );
	SetTic( mnDoubleDelta );

	// Save state data
	memcpy( (void*)&mStateData, (void*)state, mStateDataSize ) ;

	mBalLeft  = mStateData.Left.dwValue  < 1 ? 1 : mStateData.Left.dwValue ; 
	mBalRight = mStateData.Right.dwValue < 1 ? 1 : mStateData.Right.dwValue ;  

	SetCurrentPos( mBalLeft, mBalRight ) ;

	return 1 ;
}

// -----------------------------------------------------------------------------
// Get the current slider position in terms of the volume range. Assumes that if  
// the channels are in balance, both L and R vol values are the same and equal 
// to the volume. 
// Inputs:  volLeft and volRight are the current channel volumes
// Outputs: volLeft and volRight are adjusted to reflect the slider position
//          range is the control range
// Returns: The current slider position. 
// -----------------------------------------------------------------------------
int CMixerSliderHorz::GetCurrentPos( DWORD* volLeft, DWORD* volRight, int* range )
{
	DWORD dwMaxVol ;
	int nPos = GetPos() ;

	dwMaxVol = ( *volLeft > *volRight ) ? *volLeft : *volRight ;

	// Adjust volume to reflect the slider position

	if( nPos <= mnDelta )		// If thumb is either left of center or at center,
	{
		*volLeft  = dwMaxVol ;	// only change right
		*volRight = (dwMaxVol*nPos) / mnDelta ;
	}
	else						// Else, thumb is to the right of center, 
	{
		*volRight = dwMaxVol ;	// only change left 
		*volLeft  = (dwMaxVol*(mnDoubleDelta - nPos)) / mnDelta ;
	}

	*range = mnDoubleDelta ;

	return nPos ;
}

// -----------------------------------------------------------------------------
int CMixerSliderHorz::SetCurrentPos( DWORD dwLeft, DWORD dwRight )
{
	const unsigned long balThreshold = 15 ;
	DWORD dwMaxVol ;
	int thumbPos ;
	int nMin, nMax ;

	// Place thumb in center position if control is disabled. 
	if( !IsWindowEnabled() )
	{
		GetRange( nMin, nMax ) ;
		SetPos( (nMax-nMin)/2 ) ;
		return 0 ;
	}

	// Only save balance state when above the state tracking threshold to 
	// to prevent large thumb movements when L and/or R volume nears zero. 
	if( dwLeft > balThreshold  ||  dwRight > balThreshold )
	{
		mBalLeft  = dwLeft  < 1 ? 1 : dwLeft ;
		mBalRight = dwRight < 1 ? 1 : dwRight ;
	}

	// Calculate balance slider thumb position using current channel volume values.
	if( mBalLeft > mBalRight )
	{
		dwMaxVol = dwLeft  < mBalLeft  ? mBalLeft  : dwLeft ;
		dwRight  = dwRight < mBalRight ? mBalRight : dwRight ;
		thumbPos = mnDelta - (dwMaxVol*mnDelta - dwRight*mnDelta)/dwMaxVol  ;
	}
	else
	{
		dwMaxVol = dwRight < mBalRight ? mBalRight : dwRight ;
		dwLeft   = dwLeft  < mBalLeft  ? mBalLeft  : dwLeft ;
		thumbPos = mnDelta + (dwMaxVol*mnDelta - dwLeft*mnDelta)/dwMaxVol  ;
	}

	SetPos( thumbPos ) ;

	return 1 ;
}

// -----------------------------------------------------------------------------
// CMixerSliderHorz message handlers
// -----------------------------------------------------------------------------


