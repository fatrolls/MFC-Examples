// -----------------------------------------------------------------------------
// MixerDestination.cpp
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// Gets MIXERLINE, MIXERLINECONTROLS, and MIXERCONTROL data for a single 
// destination line of a mixer. 
// 
// Gets the MIXERCONTROL control data for this destination’s controls and the 
// MIXERCONTROL control data for each connection of this destination creating a 
// CmixerControl for each connection. Note that a connection provides source 
// data for a mixer destination line.
// -----------------------------------------------------------------------------

#include "StdAfx.h"
#include "MixerDestination.h"

// -----------------------------------------------------------------------------
CMixerDestination::CMixerDestination(void)
{
	mnConnections = 0 ;
	mnDestControls = 0 ;
	mpDestControls = NULL ;
	mpControls = NULL ;
	mpConnectionsMixerLineInfo = NULL ;
	mhMixer = (HMIXER)-1 ;
	mnDestIndex = -1 ;
}

// -----------------------------------------------------------------------------
CMixerDestination::~CMixerDestination(void)
{
	if( mpDestControls ) 
		delete mpDestControls ;
	if( mpControls )
		delete [] mpControls ;
	if( mpConnectionsMixerLineInfo )
		delete [] mpConnectionsMixerLineInfo ;
}

// -----------------------------------------------------------------------------
// Return the number of connections for this destination
int CMixerDestination::GetConnectionCount() 
{
	return mnConnections ;
}
// -----------------------------------------------------------------------------
// Return the number of controls for the selected destination
int CMixerDestination::GetDestControlCount() 
{
	return mnDestControls ;
}
// -----------------------------------------------------------------------------
// Return the number of controls for the selected connection
int CMixerDestination::GetConnectionControlCount( int connectionIndex ) 
{
	int n1 = -1 ;
	if( connectionIndex >= 0  &&  (unsigned int)connectionIndex < mnConnections )
		n1 = mpControls[connectionIndex].GetControlCount() ;
	return n1 ;
}

// -----------------------------------------------------------------------------
// connectionIndex = 0..N index of connection for this destination
// controlIndex = 0..N index of connection control 
// Return -1 on error, or dwID value on success
int CMixerDestination::GetConnControlDwID( int connectionIndex, int controlIndex ) 
{
	MIXERCONTROL MC ;
	int nRet ;

	if( connectionIndex < 0  ||  (unsigned int)connectionIndex >= mnConnections )
		return -1 ;

	if( controlIndex < 0  ||  controlIndex >= mpControls[connectionIndex].GetControlCount() ) 
		return -1 ;

	nRet = mpControls[connectionIndex].GetControlInfoByIndex( controlIndex, &MC ) ;
	if( nRet < 0 )
		return -1 ;

	return MC.dwControlID ;
}
// -----------------------------------------------------------------------------
// controlIndex = 0..N index of destination control
// Return -1 on error, or dwID value on success
int CMixerDestination::GetDestControlDwID( int controlIndex ) 
{
	MIXERCONTROL MC ;

	if( controlIndex < 0  ||  (unsigned int)controlIndex >= mnDestControls )
		return -1 ;
	mpDestControls->GetControlInfoByIndex( controlIndex, &MC ) ;

	return MC.dwControlID ;
}

// -----------------------------------------------------------------------------
// Get MIXERLINE and MIXERCONTROL data for this destination and its connections. 
// Returns -1 on error
int CMixerDestination::Init(unsigned int destIndex, HMIXER hMixer)
{
	int nRet = -1 ;
	MMRESULT mmr ;

	mhMixer = hMixer ;
	mnDestIndex = destIndex ;

	mMixerLineInfo.cbStruct = sizeof(MIXERLINE) ;
	mMixerLineInfo.dwDestination = (DWORD)destIndex ;
	mMixerLineInfo.dwSource = 0 ;	// Flag indicating this is a destination 
									// line, not a source line. 
	// Get the MIXERLINE info for this destination (destIndex) 
	mmr = mixerGetLineInfo( (HMIXEROBJ)mhMixer,&mMixerLineInfo, 
						MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_DESTINATION) ;

	// Get the MIXERCONTROL data for each connection of this destination.
	mnDestControls = mMixerLineInfo.cControls ;
	if( mmr == MMSYSERR_NOERROR )
		nRet = GetConnectionsControlData() ;
	else
	{
		MessageBox( NULL, TEXT("mixerGetLineInfo call failed!"), TEXT("Error"), MB_OK ) ;
		mnDestControls = 0 ;
		return -1 ;
	}

	// If there are destination controls, get the info for the controls. 
	if( mnDestControls )
	{
		mpDestControls = new CMixerControl ;	// Only need one for a destination
		if( mpDestControls )
			nRet = mpDestControls->GetControlInfo(  &mMixerLineInfo, mhMixer ) ;
	}

	return nRet ;
}

// -----------------------------------------------------------------------------
// Get the MIXERCONTROL control data for each connection associated with this 
// destination 
int CMixerDestination::GetConnectionsControlData(void)
{
	unsigned int n1 ;
	MMRESULT mmr ;

	if( mhMixer == (HMIXER)-1 ) {	// Invalid handle means that destination 
		return -1 ;					// data has not been queried yet. 
	}
	mnConnections = mMixerLineInfo.cConnections ;	// MIXERLINE.cConnections 
	if( !mnConnections ) {
		return -2 ;
	}

	// Array of MIXERLINE structures, one for each connection
	mpConnectionsMixerLineInfo = (MIXERLINE*)new MIXERLINE[mnConnections] ;
	
	// Array of mixer control objects, one for each connection
	mpControls = new CMixerControl[mnConnections] ;

	// Get (MIXERCONTROL) control info for each connection
	for( n1=0 ; n1<mnConnections ; n1++ )
	{
		memcpy( (void*)&mpConnectionsMixerLineInfo[n1] , (void*)&mMixerLineInfo, sizeof(MIXERLINE) ) ;
		mpConnectionsMixerLineInfo[n1].dwSource = n1 ;
		mmr = mixerGetLineInfo( (HMIXEROBJ)mhMixer, &mpConnectionsMixerLineInfo[n1], 
								 MIXER_GETLINEINFOF_SOURCE ) ;
		mpControls[n1].GetControlInfo( &mpConnectionsMixerLineInfo[n1], mhMixer ) ;
	}

	return 0;
}

// -----------------------------------------------------------------------------
// Get the metrics info for a destination or connection control by control ID 
// value: dwID. 
// Return -1 on control not found error.
// Returns control channel count and mixer control data on success. 
int CMixerDestination::GetControlMetrics( DWORD dwID, MIXERCONTROL* pMC ) 
{
	unsigned int controlIndex ;
	unsigned int connectionIndex ; 
	unsigned int nControls ;
	int nChannels ;

	// Check destination controls
	for( controlIndex=0 ; controlIndex<mnDestControls ; controlIndex++ )
	{
		nChannels = GetDestControlMetrics( (int)controlIndex, pMC ) ; 
		if( pMC->dwControlID == dwID )
			return( nChannels ) ;
	}

	// Check connection controls
	for( connectionIndex=0 ; connectionIndex<mnConnections ; connectionIndex++ )
	{
		nControls = mpControls[connectionIndex].GetControlCount() ;
		for( controlIndex=0 ; controlIndex<nControls ; controlIndex++ )
		{
			nChannels = mpControls[connectionIndex].GetControlInfoByIndex( controlIndex, pMC ) ;
			if( pMC->dwControlID == dwID )
				return( nChannels ) ;
		}
	}

	return -1 ;	// Error, control not found.
}

// -----------------------------------------------------------------------------
// Get the metrics info for a destination control by index 0..Control count - 1
// Data is from the MIXERCONTROL structure for the selected control
// Return -1 on error
// Returns control channel count on success. 
int CMixerDestination::GetDestControlMetrics( int controlIndex, MIXERCONTROL* pMC )
{
	int nChannels ;

	if( controlIndex < 0  ||  (unsigned int)controlIndex >= mnDestControls )
		return -1 ;
		
	nChannels = mpDestControls->GetControlInfoByIndex( controlIndex, pMC ) ;
	return nChannels ;
}

// -----------------------------------------------------------------------------
int CMixerDestination::GetDestControlState( int controlIndex, void* pStateData, 
										    unsigned int* nBuffSize )
{
	int nRet ;

	nRet = GetDestControlDwID( controlIndex ) ;
	if( nRet < 0 )
		return -1 ;

	nRet = GetControlState( nRet, pStateData, nBuffSize ) ;

	return nRet ;
}
// -----------------------------------------------------------------------------
int CMixerDestination::SetDestControlState( int controlIndex, void* pStateData, 
										    unsigned int* nBuffSize )
{
	int nRet ;

	nRet = GetDestControlDwID( controlIndex ) ;
	if( nRet < 0 )
		return -1 ;

	nRet = SetControlState( nRet, pStateData, nBuffSize ) ;

	return nRet ;
}
// -----------------------------------------------------------------------------
// Get the metrics info for a connection control by control index 0..Control count - 1
// Data is from the MIXERCONTROL structure for the selected control
// Return -1 on error
// Returns control channel count and mixer control data on success
int CMixerDestination::GetConnectionControlMetrics( int connectionIndex, 
										int controlIndex, MIXERCONTROL* pMC ) 
{
	int nChannels ;

	if(  connectionIndex < 0  ||  (unsigned int)connectionIndex >= mnConnections )
		return -1 ;
		
	if(  controlIndex < 0  ||  controlIndex >= mpControls[connectionIndex].GetControlCount() )
		return -1 ;
		
	nChannels = mpControls[connectionIndex].GetControlInfoByIndex( controlIndex, pMC ) ;

	return nChannels ;
}

// -----------------------------------------------------------------------------
// Get the state data for the connection control selected by connection index 
// and control index. 
// Returns -1 on error. If buffer size is too small, the required size is 
// returned in nBuffSize
int CMixerDestination::GetConnectionControlState( unsigned int connectionIndex, 
		unsigned int controlIndex, void* pStateData, unsigned int* nBuffSize ) 
{
	int nRet = -1 ;
	DWORD dwID ;

	nRet = GetConnControlDwID( connectionIndex, controlIndex ) ;
	if( nRet < 0 )
		return nRet ;

	dwID = (DWORD)nRet ;
	nRet = mpControls[connectionIndex].GetControStateData( dwID, pStateData, nBuffSize ) ;

	return nRet ;
}

// -----------------------------------------------------------------------------
// Get the state data for the connection control with ID = dwID
// Returns -1 on error. If buffer size is too small, the required size is 
// returned in nBuffSize
// -----------------------------------------------------------------------------
int CMixerDestination::GetControlState( DWORD dwID, void* pStateData, 
									    unsigned int* nBuffSize ) 
{
	int nRet = -1 ;
	unsigned int nControlCount ;
	unsigned int controlIndex ;
	unsigned int connectionIndex ; 
	unsigned int n1 = *nBuffSize ;

	// Search destination controls
	for( controlIndex=0 ; controlIndex<mnDestControls ; controlIndex++ )
	{
		n1 = *nBuffSize ;
		nRet = mpDestControls->GetControStateData( dwID, pStateData, &n1 ) ;
		if( nRet < 0 )				// If error
		{
			if( nRet == -2 )		// If ID found but buffer size is incorrect,
			{
				*nBuffSize = n1 ;	// return required buffer size
				return -1  ;
			}
		}
		else	// Control found and buffer size is correct. 
			return nRet ;
	}

	// Search connection controls
	for( connectionIndex=0 ; connectionIndex<mnConnections ; connectionIndex++ )
	{
		nControlCount = mpControls[connectionIndex].GetControlCount() ;
		for( controlIndex=0 ; controlIndex<nControlCount ; controlIndex++ )
		{
			n1 = *nBuffSize ;
			nRet = mpControls[connectionIndex].GetControStateData( dwID, pStateData, &n1 ) ;
			if( nRet < 0  )			// If error
			{
				if( nRet == -2 )	// If ID found but buffer size is incorrect,
				{
					*nBuffSize = n1 ;	// return required buffer size
					return nRet  ;
				}
			}
			else	// Control found and buffer size is correct. 
				return nRet ;
		}
	}
	
	return nRet ;
}
// -----------------------------------------------------------------------------
int CMixerDestination::SetControlState( DWORD dwID, void* pStateData, 
										unsigned int* nBuffSize )   
{
	int nRet ;
	unsigned int nControlCount ;
	unsigned int controlIndex ;
	unsigned int connectionIndex ; 
	unsigned int n1 ;

	// Search destination controls
	for( controlIndex=0 ; controlIndex<mnDestControls ; controlIndex++ )
	{
		n1 = *nBuffSize ;
		nRet = mpDestControls->SetControStateData( dwID, pStateData, &n1 ) ;
		if( nRet < 0 )				// If error
		{
			if( nRet == -2 )		// If ID found but buffer size is incorrect,
			{
				*nBuffSize = n1 ;	// return required buffer size
				return -1  ;
			}
		}
		else	// Control found and buffer size is correct, new state values set. 
			return nRet ;
	}

	// Search connection controls
	for( connectionIndex=0 ; connectionIndex<mnConnections ; connectionIndex++ )
	{
		nControlCount = mpControls[connectionIndex].GetControlCount() ;
		for( controlIndex=0 ; controlIndex<nControlCount ; controlIndex++ )
		{
			n1 = *nBuffSize ;
			nRet = mpControls[connectionIndex].SetControStateData( dwID, pStateData, &n1 ) ;
			if( nRet < 0 )				// If error
			{
				if( nRet == -2 )		// If ID found but buffer size is incorrect,
				{
					*nBuffSize = n1 ;	// return required buffer size
					return -1  ;
				}
			}
			else	// Control found and buffer size is correct, new state values set. 
				return nRet ;
		}
	}
	
	return -1 ;
}
// -----------------------------------------------------------------------------
int CMixerDestination::SetConnectionControlState( unsigned int connectionIndex, 
		unsigned int controlIndex, void* pStateData, unsigned int* nBuffSize ) 
{
	int nRet = -1 ;
	DWORD dwID ;

	nRet = GetConnControlDwID( connectionIndex, controlIndex ) ;
	if( nRet < 0 )
		return nRet ;

	dwID = (DWORD)nRet ;
	nRet = mpControls[connectionIndex].SetControStateData( dwID, pStateData, nBuffSize ) ;

	return nRet ;
}

// -----------------------------------------------------------------------------
int CMixerDestination::GetDestMixerLineInfo( MIXERLINE* pMixerLineInfo ) 
{
	if( mnDestIndex < 0 )
		return -1 ;

	memcpy( (void*)pMixerLineInfo, (void*)&mMixerLineInfo, sizeof(MIXERLINE) ) ;

	return 0 ;
}

// -----------------------------------------------------------------------------
int CMixerDestination::GetConnectionMixerLineInfo( unsigned int connectionIndex, 
												   MIXERLINE* pMixerLineInfo ) 
{
	if( mnDestIndex < 0  ||  connectionIndex >= mnConnections )
		return -1 ;

	memcpy( (void*)pMixerLineInfo, (void*)&mpConnectionsMixerLineInfo[connectionIndex], 
			sizeof(MIXERLINE) ) ;

	return 0 ;
}

// -----------------------------------------------------------------------------
