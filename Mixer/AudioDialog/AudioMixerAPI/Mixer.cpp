// -----------------------------------------------------------------------------
// Mixer.cpp
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// Only the following types of control types are supported: 
// 
// 	MIXERCONTROL_CT_CLASS_SWITCH        0x20000000L
// 	MIXERCONTROL_CT_CLASS_SLIDER        0x40000000L
// 	MIXERCONTROL_CT_CLASS_FADER         0x50000000L
// 
// Assumes that all fader controls have at least two channels. 
// 
// -----------------------------------------------------------------------------

#include "StdAfx.h"
#include "Mixer.h"

// -----------------------------------------------------------------------------
CMixer::CMixer(void)
{
	mnDestinations = 0 ;
	mnMixerNumber = 0 ;
	mhMixer = (HMIXER)-1 ;
	mpMixerDests = NULL ;
	mnMixerCount = mixerGetNumDevs();
	memset( (VOID*)&mMixerCaps, 0, sizeof(MIXERCAPS) ) ;
}

// -----------------------------------------------------------------------------
CMixer::~CMixer(void)
{
	if( mhMixer != (HMIXER)-1 )	// Only close an open mixer handle
		mixerClose( mhMixer ) ;

	if( mpMixerDests )
		delete [] mpMixerDests ;
}

// -----------------------------------------------------------------------------
// Open and initialize by mixer index, 0...N. For all Init methods, hWnd is the 
// handle of the window that will receive mixer control change event messages
// Returns -1 on error, mixer count on success.
int CMixer::Init( unsigned int nIndex, HWND hWnd )
{
	int nRet =	-1 ; 
	MMRESULT	mrResult ;
	DWORD		fdwOpen ;

	// Check for invalid index number
	if( mnMixerCount == 0  ||  nIndex >= (unsigned int)mnMixerCount  )
		return -1 ;

	mnMixerNumber = nIndex ;

	if( mhMixer != (HMIXER)-1 )	// Close an already open mixer handle
		mixerClose( mhMixer ) ;

	// Open the mixer identified by it's index value, 0...N
	fdwOpen = MIXER_OBJECTF_MIXER ;
	if( hWnd != NULL ) fdwOpen |= CALLBACK_WINDOW ;
	mrResult = mixerOpen( &mhMixer, mnMixerNumber, (DWORD_PTR)hWnd,
							NULL, fdwOpen ) ;
	if( mrResult != MMSYSERR_NOERROR )
	{
		mhMixer = (HMIXER)-1 ;
		return -1 ;
	}

	nRet = GetDestinationDetails() ;
	if( nRet < 0 )
		return nRet ;

	return mnMixerCount ;
}

// -----------------------------------------------------------------------------
// Open and initialize the mixer associated with the passed device handle
// Returns -1 on error, mixer count on success.
int CMixer::InitWithDevHandle( unsigned int devHandle, HandleTypes devType, HWND hWnd ) 
{
	int nRet =	-1 ; 
	MMRESULT	mrResult ;
	DWORD		fdwOpen ;

	if( mhMixer != (HMIXER)-1 )	// Close an already open mixer handle
		mixerClose( mhMixer ) ;

	fdwOpen = devType ;
	if( hWnd != NULL ) fdwOpen |= CALLBACK_WINDOW ;
	mrResult = mixerOpen( &mhMixer, devHandle, (DWORD_PTR)hWnd,
							NULL, fdwOpen ) ;
	if( mrResult != MMSYSERR_NOERROR )
	{
		mhMixer = (HMIXER)-1 ;
		return -1 ;
	}

	nRet = GetDestinationDetails() ;
	if( nRet < 0 )
		return nRet ;

	return mnMixerCount ;
}

// -----------------------------------------------------------------------------
// Open and initialize the mixer associated with the passed device ID
// Given 3 MIDI devices, 0...2, using a devID of 1 opens the mixer 
// associated with the second MIDI device.
// Returns -1 on error, mixer count on success.
int CMixer::InitWithDevID(  unsigned int devID, DeviceTypes devType, HWND hWnd )
{
	return InitWithDevHandle( devID, (HandleTypes)devType, hWnd ) ;
}

// -----------------------------------------------------------------------------
int CMixer::GetMixerDetails(void)
{
	MMRESULT mrResult ;

	// Get the number of "destinations" for the selected mixer or return error. 
	memset( (VOID*)&mMixerCaps, 0, sizeof(MIXERCAPS) ) ;
	mrResult = mixerGetDevCaps( (UINT_PTR)mhMixer, &mMixerCaps, sizeof(MIXERCAPS) );
	if( mrResult != MMSYSERR_NOERROR )
		return -1 ;

	return 0;
}

// -----------------------------------------------------------------------------
int CMixer::GetMixerCaps( MIXERCAPS* pMixerCaps ) 
{
	if( mnMixerCount <= 0 )
		return -1 ;

	memcpy( (void*)pMixerCaps, (void*)&mMixerCaps, sizeof(MIXERCAPS) ); 
	
	return sizeof(MIXERCAPS) ;
}

// -----------------------------------------------------------------------------
CMixerDestination* CMixer::GetCDestination( unsigned int destIndex ) 
{
	if( destIndex >= mnDestinations )
		return NULL ;
	return &mpMixerDests[destIndex] ;
}

// -----------------------------------------------------------------------------
// Get the line info for all destinations of this mixer.
// Return -1 on error. 
int CMixer::GetDestinationDetails(void)
{
	int nRet = -1 ;
	unsigned int n1 ;

	nRet = GetMixerDetails() ;
	mnDestinations = mMixerCaps.cDestinations ;
	if( mnDestinations == 0 ) {	// Should never happen,  
			MessageBox( NULL, TEXT("Mixer has no destinations!"), TEXT("Error"), MB_OK ) ;
			return -1 ;
	}
	else						// there is always at least one destination
	{
		if( mpMixerDests )
			delete [] mpMixerDests ;
		mpMixerDests = (CMixerDestination*) new CMixerDestination[mnDestinations] ;
		if( !mpMixerDests )
			return -1 ;
		
		// Get MIXERLINE, MIXERLINECONTROLS, and MIXERCONTROL data for each destination
		// and all connections associated with the destination.
		for( n1=0 ; n1<mnDestinations ; n1++ )
		{
			nRet = mpMixerDests[n1].Init( n1, mhMixer ) ;
		}
	}
	return mnDestinations ;
}

// -----------------------------------------------------------------------------
int CMixer::GetDestInfo( int destIndex, MIXERLINE* pMixerLine ) 
{
	int nRet = mpMixerDests[destIndex].GetDestMixerLineInfo( pMixerLine ) ;
	return nRet ;
}

// -----------------------------------------------------------------------------
int CMixer::GetConnectionInfo( int destIndex, int connectionIndex, MIXERLINE* pMixerLine ) 
{
	int nRet = mpMixerDests[destIndex].GetConnectionMixerLineInfo( connectionIndex, pMixerLine ) ;
	return nRet ;
}

// -----------------------------------------------------------------------------
// Return the number of destinations this mixer has
int CMixer::GetDestinationCount() 
{
	return mnDestinations ;
}

// -----------------------------------------------------------------------------
// Return the number of controls for the selected destination of this mixer.
int CMixer::GetDestinationControlCount( int destIndex ) 
{
	int n1 = -1 ;
	if( destIndex >= 0  &&  destIndex < (int)mnDestinations )
		n1 = mpMixerDests[destIndex].GetDestControlCount() ;
	return n1 ;
}

// -----------------------------------------------------------------------------
// Return the number of connections for the selected mixer destination. 
int CMixer::GetConnectionCount( int destIndex ) 
{
	int n1 = -1 ;
	if( destIndex >= 0  &&  destIndex < (int)mnDestinations )
		n1 = mpMixerDests[destIndex].GetConnectionCount() ;
	return n1 ; ;
}

// -----------------------------------------------------------------------------
// Return the number of controls for the selected mixer destination and connection
int CMixer::GetConnectionControlCount( int destIndex, int connectionIndex ) 
{
	int n1 = -1 ;
	if( connectionIndex >= 0  &&  connectionIndex < mpMixerDests[destIndex].GetConnectionCount() )
		n1 = mpMixerDests[destIndex].GetConnectionControlCount(connectionIndex) ;
	return n1 ; ;
}

// -----------------------------------------------------------------------------
// Get the ID of a destination connection control
// destIndex: Mixer destination 0...N
// connIndex: Connection index 0...N
// ctrlIndex: Connection control index 0...N
// Returns ID on success
// Returns -1 on failure
int CMixer::GetConnControlDwID( int destIndex, int connIndex, int ctrlIndex ) 
{
	int n1 = -1 ;
	if( destIndex >= 0  &&  destIndex < (int)mnDestinations )
	{
		if( connIndex >= 0  &&  connIndex < mpMixerDests[destIndex].GetConnectionCount() )
		{
			if( ctrlIndex >= 0  &&  ctrlIndex < mpMixerDests[destIndex].GetConnectionControlCount(connIndex) )
				n1 = mpMixerDests[destIndex].GetConnControlDwID( connIndex, ctrlIndex ) ;
		}
	}
	return n1 ;
}

// -----------------------------------------------------------------------------
// Get the ID of a destination control
// destIndex: Mixer destination 0...N
// ctrlIndex: Destination control index 0...N
// Returns ID on success
// Returns -1 on failure
int CMixer::GetDestControlDwID( int destIndex, int ctrlIndex ) 
{
	int n1 = -1 ;
	if( destIndex >= 0  &&  destIndex < (int)mnDestinations )
	{
		if( ctrlIndex >= 0  &&  ctrlIndex < mpMixerDests[destIndex].GetDestControlCount() )
			n1 = mpMixerDests[destIndex].GetDestControlDwID( ctrlIndex ) ;
	}
	return n1 ;
}

// -----------------------------------------------------------------------------
// Get the metrics info for a destination control by index: 0..Control count - 1
// Data is from the MIXERCONTROL structure for the selected control
// Return -1 on error
int CMixer::GetDestControlMetrics( int destIndex, int controlIndex, MIXERCONTROL* pMC )
{
	int nRet = -1 ;
	if( destIndex >= 0  &&  destIndex < (int)mnDestinations )
		nRet = mpMixerDests[destIndex].GetDestControlMetrics( controlIndex, pMC ) ; 

	return nRet ;
}

// -----------------------------------------------------------------------------
int CMixer::GetConnectionControlMetrics( int destIndex, int connectionIndex, 
										 int controlIndex, MIXERCONTROL* pMC )
{
	int nRet = -1 ;
	if( destIndex>=0 && destIndex<(int)mnDestinations )
	{
		nRet = mpMixerDests[destIndex].GetConnectionControlMetrics( connectionIndex, 
															controlIndex, pMC ) ; 
	}
	return nRet ;
}
// -----------------------------------------------------------------------------
// Returns control channel count and mixer control data on success. 
int CMixer::GetControlMetrics( DWORD dwID, MIXERCONTROL* pMC ) 
{
	int nRet ;
	unsigned int destIndex ; 

	for( destIndex=0 ; destIndex<mnDestinations ; destIndex++ )
	{
		nRet = mpMixerDests[destIndex].GetControlMetrics( dwID, pMC ) ; 
		if( nRet >= 0 )
			break ;
	}
	return nRet ;
}

// -----------------------------------------------------------------------------
int CMixer::GetControlChannelCount( DWORD dwID ) 
{
	int nChannels ;
	MIXERCONTROL mc ;

	nChannels = GetControlMetrics( dwID, &mc ) ;

	return nChannels ;
}

// -----------------------------------------------------------------------------
int CMixer::GetControlState( DWORD dwID, sStateData* pStateData, unsigned int* nBuffSize ) 
{
	int nRet ;
	unsigned int destIndex ; 

	for( destIndex=0 ; destIndex<mnDestinations ; destIndex++ )
	{
		nRet = mpMixerDests[destIndex].GetControlState( dwID, pStateData, nBuffSize ) ; 
		if( nRet >= 0 )
			break ;
	}
	return nRet ;
}
// -----------------------------------------------------------------------------
int CMixer::SetControlState( DWORD dwID, sStateData* pStateData, unsigned int* nBuffSize ) 
{
	int nRet ;
	unsigned int destIndex ; 

	for( destIndex=0 ; destIndex<mnDestinations ; destIndex++ )
	{
		nRet = mpMixerDests[destIndex].SetControlState( dwID, pStateData, nBuffSize ) ; 
		if( nRet >= 0 )
			break ;
	}
	return nRet ;
}
// -----------------------------------------------------------------------------
int CMixer::GetConnectionControlState( unsigned int destIndex, unsigned int connectionIndex, 
				unsigned int controlIndex, sStateData* pStateData, unsigned int* nBuffSize ) 
{
	int nRet ;

	nRet = GetConnControlDwID( destIndex, connectionIndex, controlIndex ) ;
	if( nRet < 0 )
		return nRet ;

	nRet = mpMixerDests[destIndex].GetControlState( nRet, pStateData, nBuffSize ) ;

	return nRet ;
}
// -----------------------------------------------------------------------------
int CMixer::SetConnectionControlState( unsigned int destIndex, unsigned int connectionIndex, 
				unsigned int controlIndex, sStateData* pStateData, unsigned int* nBuffSize ) 
{
	int nRet ;

	nRet = GetConnControlDwID( destIndex, connectionIndex, controlIndex ) ;
	if( nRet < 0 )
		return nRet ;

	nRet = mpMixerDests[destIndex].SetControlState( nRet, pStateData, nBuffSize ) ;

	return nRet ;
}
// -----------------------------------------------------------------------------

int CMixer::GetDestControlState( unsigned int destIndex, unsigned int controlIndex,  
								 sStateData* pStateData, unsigned int* nBuffSize ) 
{
	int nRet ;

	nRet = GetDestControlDwID( destIndex, controlIndex ) ;
	if( nRet < 0 )
		return nRet ;

	nRet = mpMixerDests[destIndex].GetControlState( nRet, pStateData, nBuffSize ) ;

	return nRet ;
}
// -----------------------------------------------------------------------------
int CMixer::SetDestControlState( unsigned int destIndex, unsigned int controlIndex,  
								 sStateData* pStateData, unsigned int* nBuffSize ) 
{
	int nRet ;

	nRet = GetDestControlDwID( destIndex, controlIndex ) ;
	if( nRet < 0 )
		return nRet ;

	nRet = mpMixerDests[destIndex].SetControlState( nRet, pStateData, nBuffSize ) ;

	return nRet ;
}

// -----------------------------------------------------------------------------
