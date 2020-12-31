// -----------------------------------------------------------------------------
// MixerDestination.h
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
#include "MixerControl.h"

// -----------------------------------------------------------------------------
class CMixerDestination
{
public:
	CMixerDestination(void);
	virtual ~CMixerDestination(void);

	int Init(unsigned int nDestIndex, HMIXER hMixer);

	int GetDestControlCount() ;
	int GetConnectionCount() ;
	int GetConnectionControlCount( int connectionIndex ) ;

	int GetControlMetrics( DWORD dwID, MIXERCONTROL* pMC ) ;
	int GetControlState( DWORD dwID, void* pStateData, unsigned int* nBuffSize ) ;
	int SetControlState( DWORD dwID, void* pStateData, unsigned int* nBuffSize ) ; 

	int GetDestControlMetrics( int controlIndex, MIXERCONTROL* pMC ) ;
	int GetDestControlState( int controlIndex, void* pStateData, unsigned int* nBuffSize ) ; 
	int SetDestControlState( int controlIndex, void* pStateData, unsigned int* nBuffSize ) ; 

	int GetConnectionControlMetrics( int connectionIndex, int controlIndex, MIXERCONTROL* pMC ) ;
	int GetConnectionControlState( unsigned int connectionIndex, unsigned int controlIndex, 
												void* pStateData, unsigned int* nBuffSize ) ; 
	int SetConnectionControlState( unsigned int connectionIndex, unsigned int controlIndex, 
												void* pStateData, unsigned int* nBuffSize ) ; 

	int GetConnControlDwID( int connectionIndex, int controlIndex ) ;
	int GetDestControlDwID( int controlIndex ) ;

	int GetDestMixerLineInfo( MIXERLINE* pMixerLineInfo ) ;
	int GetConnectionMixerLineInfo( unsigned int connectionIndex, MIXERLINE* pMixerLineInfo ) ;

protected:
	int GetConnectionsControlData(void);

	unsigned int		mnConnections;		// Number of connections for this destination
	unsigned int		mnDestControls ;	// Number of controls for this destination
	int					mnDestIndex ;		// Mixer destination index 0..N
	HMIXER				mhMixer ;
	MIXERLINE			mMixerLineInfo ;				// One MIXERLINE for this destination
	MIXERLINE*			mpConnectionsMixerLineInfo ;	// One MIXERLINE per connection
	CMixerControl*		mpDestControls;	// One for each control of this destination
	CMixerControl*		mpControls ;	// One for each connection, contains controls info
} ;

// -----------------------------------------------------------------------------
