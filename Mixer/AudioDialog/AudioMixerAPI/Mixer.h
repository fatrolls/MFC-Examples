// -----------------------------------------------------------------------------
// Mixer.h
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

#include <mmsystem.h>		// LINK WITH  Winmm.lib
#include "MixerDestination.h"

// -----------------------------------------------------------------------------
// Global data structure for mixer control state data

	struct sStateData {
		MIXERCONTROLDETAILS_UNSIGNED Left ;
		MIXERCONTROLDETAILS_UNSIGNED Right ;
	} ;

// -----------------------------------------------------------------------------
class CMixer
{
public:
	CMixer(void);
	virtual ~CMixer(void);

	// Handle types used in initializing a CMixer object. For example, 
	// use h_MIDI_IN when passing the handle returned by the midiInOpen function 
	// to InitWithDevHandle()
	enum HandleTypes {
		h_MIDI_IN  = MIXER_OBJECTF_HMIDIIN, 	
		h_MIDI_OUT = MIXER_OBJECTF_HMIDIOUT, 	
		h_Wave_IN  = MIXER_OBJECTF_HWAVEIN, 	
		h_Wave_OUT = MIXER_OBJECTF_HWAVEOUT 	 
	} ;

	// Device types used in initializing a CMixer object. For example, us Wave_IN 
	// when passing the in index value of a Wave Input device. Index values will be 
	// in the range of zero to one less than the number of devices enumerated in the 
	// system. 
	enum DeviceTypes {
		Aux      = MIXER_OBJECTF_AUX, 		
		MIDI_IN  = MIXER_OBJECTF_MIDIIN, 	
		MIDI_OUT = MIXER_OBJECTF_MIDIOUT, 	
		Wave_IN  = MIXER_OBJECTF_WAVEIN, 	
		Wave_OUT = MIXER_OBJECTF_WAVEOUT 
	} ;

	// Open and initialize by mixer index, 0...N. For all Init methods, hWnd is the 
	// handle of the window that will receive mixer control change event messages
	int Init( unsigned int mixerIndex, HWND hWnd );

	// Open and initialize the mixer associated with the passed device handle
	int InitWithDevHandle( unsigned int devHandle, HandleTypes handleType, HWND hWnd ) ;

	// Open and initialize the mixer associated with the passed device ID
	// Given 3 MIDI devices, 0...2, using a devID of 1 opens the mixer 
	// associated with the second MIDI device.
	int InitWithDevID(  unsigned int devID, DeviceTypes devType, HWND hWnd ) ;

	int GetDestinationCount() ;
	int GetDestinationControlCount( int destIndex ) ;
	int GetConnectionCount( int destIndex ) ;
	int GetConnectionControlCount( int destIndex, int connectionIndex ) ;

	// Get MIXERCAPS data - describes the capabilities of a mixer device.
	int GetMixerCaps( MIXERCAPS* pMixerCaps ) ;

	// The MIXERLINE structure describes the state and metrics 
	// of a connection or destination.

	// Methods to get destination or connection MIXERLINE info
	int GetDestInfo( int destIndex, MIXERLINE* pMixerLine ) ;
	int GetConnectionInfo( int destIndex, int connectionIndex, MIXERLINE* pMixerLine ) ;
	
	// ID enumeration methods
	int GetDestControlDwID( int destIndex, int ctrlIndex ) ;
	int GetConnControlDwID( int destIndex, int connIndex, int ctrlIndex ) ;

	// The MIXERCONTROL structure describes the state and metrics of a single control 
	// for a connection or destination.

	// Methods for controls, get/set MIXERCONTROL data by control ID
	int GetControlMetrics( DWORD dwID, MIXERCONTROL* pMC ) ;
	int GetControlState( DWORD dwID, sStateData* pStateData, unsigned int* nBuffSize ) ;
	int SetControlState( DWORD dwID, sStateData* pStateData, unsigned int* nBuffSize ) ;
	int GetControlChannelCount( DWORD dwID ) ; 

	// Methods for controls, get/set MIXERCONTROL data by index
	int GetDestControlMetrics( int destIndex, int controlIndex, MIXERCONTROL* pMC ) ;
	int GetConnectionControlMetrics( int destIndex, int connectionIndex, 
											  int controlIndex, MIXERCONTROL* pMC ) ;

	int GetDestControlState( unsigned int destIndex, unsigned int controlIndex,  
									sStateData* pStateData, unsigned int* nBuffSize ) ;
	int SetDestControlState( unsigned int destIndex, unsigned int controlIndex,  
									sStateData* pStateData, unsigned int* nBuffSize ) ;	

	int GetConnectionControlState( unsigned int destIndex, unsigned int connectionIndex, 
			unsigned int controlIndex, sStateData* pStateData, unsigned int* nBuffSize ) ;
	int SetConnectionControlState( unsigned int destIndex, unsigned int connectionIndex, 
			unsigned int controlIndex, sStateData* pStateData, unsigned int* nBuffSize ) ;

protected:
	int GetDestinationDetails(void);	// Get MIXERLINE info
	int GetMixerDetails(void);
	CMixerDestination* GetCDestination( unsigned int destIndex ) ;

	int				mnMixerCount ;		// Number of mixers in system
	unsigned int	mnDestinations ;	// Number of destinations for this mixer
	unsigned int	mnMixerNumber ;		// This mixer's index value 0 -> mnMixerCount-1
	MIXERCAPS		mMixerCaps ;
	HMIXER			mhMixer ;

	CMixerDestination*	mpMixerDests ;	// MIXERLINE info
};

// -----------------------------------------------------------------------------
