// -----------------------------------------------------------------------------
// MixerControl.cpp
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// Gets the MIXERCONTROL state and metrics data for the controls associated 
// with a destination or connection of a mixer destination. Sets the state 
// data of any of the controls. Note that a connection provides source data for 
// a mixers destination line. 
// -----------------------------------------------------------------------------

#include "StdAfx.h"
#include "MixerControl.h"

// -----------------------------------------------------------------------------
CMixerControl::CMixerControl(void)
{
	mnControlCount = 0 ;
	mpControlData = NULL ;
	mpMixerControl = NULL ;
	mpMixerControlStateInfo = NULL ;
	mpbHaveStateInfo = NULL ;
}

// -----------------------------------------------------------------------------
CMixerControl::~CMixerControl(void)
{
	CleanupHeap() ;
}

// -----------------------------------------------------------------------------
void CMixerControl::CleanupHeap() 
{
	if( mpMixerControlStateInfo )
	{
		for( int n1=0 ; n1<(int)mnControlCount ; n1++ )
		{
			if( mpMixerControlStateInfo[n1].paDetails )
				delete [] mpMixerControlStateInfo[n1].paDetails ;
		}
		delete [] mpMixerControlStateInfo ;
	}

	if( mpMixerControl )
		delete [] mpMixerControl ;

	if( mpbHaveStateInfo )
		delete [] mpbHaveStateInfo ;
}

// -----------------------------------------------------------------------------
// Get the control's MIXERCONTROL data.
// Return -1 on error, 
// Returns control channel count and data on success.
int CMixerControl::GetControlInfoByIndex( int nIndex, MIXERCONTROL* pMC )
{
	if( nIndex < 0  ||  nIndex > (int)mnControlCount )
		return -1 ;		// Error return on bad control index 

	memcpy( (void*)pMC, (void*)&mMixerLineControls.pamxctrl[nIndex], sizeof(MIXERCONTROL) ) ;

	return mpMixerLine.cChannels ;	// Number of channels for this control. 
}

// -----------------------------------------------------------------------------
// Get the (MIXERCONTROL) control info for this mixer destination line
// Returns the number of controls on success, -1 on error
int CMixerControl::GetControlInfo( MIXERLINE* pMixerLine, HMIXER hMixer )
{
	if( pMixerLine->cControls < 1  ||	// If there isn't at least one control, 
		mpMixerControl != NULL	) {		// or this is not the first time here,  
		return -1 ;						// error return. 
	}

	int nRet = -1 ;
	MMRESULT mmr ;
	mhMixer = hMixer ;

	mnControlCount = pMixerLine->cControls ;
	mpMixerControl = new MIXERCONTROL[mnControlCount] ;
	if( !mpMixerControl )
		return -1 ;

	mMixerLineControls.cbStruct      = sizeof(MIXERLINECONTROLS);
	mMixerLineControls.dwLineID      = pMixerLine->dwLineID ;
	mMixerLineControls.dwControlType = 0 ;
	mMixerLineControls.cControls     = pMixerLine->cControls ;
	mMixerLineControls.cbmxctrl      = sizeof(MIXERCONTROL) ;
	mMixerLineControls.pamxctrl      = mpMixerControl ;
	
	// Get general (MIXERLINECONTROLS) info for all controls
	mmr = mixerGetLineControls( (HMIXEROBJ)hMixer, &mMixerLineControls, 
								MIXER_GETLINECONTROLSF_ALL ) ;
	if( mmr != MMSYSERR_NOERROR )	// If there were errors, 
	{
		delete [] mpMixerControl ;
		mpMixerControl = NULL ;
		return -1 ;					// error return. 
	}

	memcpy( (void*)&mpMixerLine, (void*)pMixerLine, sizeof(MIXERLINE) ) ;

	mpbHaveStateInfo = (bool*)new bool[mnControlCount] ;
	mpMixerControlStateInfo = new MIXERCONTROLDETAILS[mnControlCount] ;

	// Get the MIXERCONTROL control info for all controls
	if( mpbHaveStateInfo && mpMixerControlStateInfo )
		nRet = InitMixerControlDetails() ;

	if( nRet<0 )			// If there were errors, 
	{
		CleanupHeap() ;
		return -1 ;			// error return. 
	}

	return mnControlCount ;	// Success return.
}

// -----------------------------------------------------------------------------
// Initialialize MIXERCONTROLDETAILS structures for all controls
int CMixerControl::InitMixerControlDetails() 
{
	unsigned int n1 ;
	for( n1=0 ; n1<mnControlCount ; n1++ )
	{
		mpbHaveStateInfo[n1] = FALSE ;

		mpMixerControlStateInfo[n1].cbStruct = sizeof(MIXERCONTROLDETAILS) ;
		mpMixerControlStateInfo[n1].dwControlID = 0 ;

		// Future: use actual HWND (not NULL) if MIXERCONTROL.fdwControl 
		// MIXER_SETCONTROLDETAILSF_CUSTOM flag bit is set:
		mpMixerControlStateInfo[n1].hwndOwner = NULL ;	

		// .cChannels:
		if( mpMixerControl[n1].dwControlType & MIXERCONTROL_CONTROLTYPE_CUSTOM )
			mpMixerControlStateInfo[n1].cChannels = 1 ;
		else
			mpMixerControlStateInfo[n1].cChannels = mpMixerLine.cChannels ;

		// cMultipleItems:
		if( mpMixerControl[n1].fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE )
			mpMixerControlStateInfo[n1].cMultipleItems = mpMixerControl[n1].cMultipleItems ;
		else if( mpMixerControl[n1].dwControlType & MIXERCONTROL_CONTROLTYPE_CUSTOM  && 
				 mpMixerControl[n1].fdwControl & MIXER_SETCONTROLDETAILSF_CUSTOM )
			mpMixerControlStateInfo[n1].cMultipleItems = (DWORD)mpMixerControlStateInfo[n1].hwndOwner ;
		else
			mpMixerControlStateInfo[n1].cMultipleItems = 0 ;

		// .cbDetails and paDetails:
		DWORD dwClass = mpMixerControl[n1].dwControlType & MIXERCONTROL_CT_CLASS_MASK ;
		switch( dwClass ) 
		{
		case MIXERCONTROL_CT_CLASS_FADER:	//MIXERCONTROLDETAILS_UNSIGNED
			mpMixerControlStateInfo[n1].cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED) ;
			mpControlData = (void*)new MIXERCONTROLDETAILS_UNSIGNED[mpMixerControlStateInfo[n1].cChannels] ;
			mpMixerControlStateInfo[n1].paDetails = mpControlData ; 
			break ;
		case MIXERCONTROL_CT_CLASS_SLIDER:	//MIXERCONTROLDETAILS_SIGNED
			mpMixerControlStateInfo[n1].cbDetails = sizeof(MIXERCONTROLDETAILS_SIGNED) ;
			mpControlData = (void*)new MIXERCONTROLDETAILS_SIGNED[mpMixerControlStateInfo[n1].cChannels] ;
			mpMixerControlStateInfo[n1].paDetails = mpControlData ;
			break ;
		case MIXERCONTROL_CT_CLASS_SWITCH:	//MIXERCONTROLDETAILS_BOOLEAN
			mpMixerControlStateInfo[n1].cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN) ;
			mpControlData = (void*)new MIXERCONTROLDETAILS_BOOLEAN[mpMixerControlStateInfo[n1].cChannels] ;
			mpMixerControlStateInfo[n1].paDetails = mpControlData ;
			break ;
		case MIXERCONTROL_CT_CLASS_CUSTOM:	
			mpMixerControlStateInfo[n1].cbDetails = mpMixerControl[n1].Metrics.cbCustomData ;
			mpControlData = (void*)new unsigned char[mpMixerControl[n1].Metrics.cbCustomData] ;
			break ;
			// For now, the following are ignored as they require multiple structures:
		case MIXERCONTROL_CT_CLASS_METER:	// Uses MIXERCONTROLDETAILS_BOOLEAN, MIXERCONTROLDETAILS_SIGNED, and MIXERCONTROLDETAILS_UNSIGNED
		case MIXERCONTROL_CT_CLASS_NUMBER:	// Uses MIXERCONTROLDETAILS_SIGNED and MIXERCONTROLDETAILS_UNSIGNED 
		case MIXERCONTROL_CT_CLASS_LIST:	// Uses MIXERCONTROLDETAILS_BOOLEAN, MIXERCONTROLDETAILS_LISTTEXT
		case MIXERCONTROL_CT_CLASS_TIME:	// Unsupported
			return -1 ;
		}
	}
	return 0 ;
}

// -----------------------------------------------------------------------------
// Get the state data for all channels of control.dwControlID and copy the data
// to the passed buffer. Ignores MIXERCONTROL_CONTROLF_MULTIPLE controls.
// Only the channel data is copied to the passed buffer, pDetails.
//
// If the passed buffer size is too small, the required size is returned in 
// nSizeOfDetails. The buffer is a MIXERCONTROLDETAILS structure combined with 
// an array of one or more (one per channel) MIXERCONTROLDETAILS_UNSIGNED structures 
//
// Parameters:
// dwControlID    =	MIXERCONTROL.dwControlID
// pDetails       =	destination buffer for data read from control
// nSizeOfDetails = Size of the destination buffer
// 
// Error returns:  
//	-1  : Control function call returned an error. 
//	-2  : Buffer too small.
//  -3  : ID not found.
// -----------------------------------------------------------------------------
int CMixerControl::GetControStateData( DWORD dwControlID, void* pDetails, 
					unsigned int* nSizeOfDetails )	
{
	unsigned int n1 ;
	unsigned int nSize ;
	MMRESULT mmr ;

	// Get the control index associated with the ID value
	for( n1=0 ; n1<mnControlCount ; n1++ )
	{
		if( mpMixerControl[n1].dwControlID == dwControlID )
			break ;
	}

	if( n1 >= mnControlCount )	// Error return if ID not found  
	{
		*nSizeOfDetails = 0 ;
		return -3 ;	
	}

	// Note: cbDetails and cChannels are set in InitMixerControlDetails()
	nSize = mpMixerControlStateInfo[n1].cbDetails * 
			mpMixerControlStateInfo[n1].cChannels ;
	if( nSize > *nSizeOfDetails )	// Error return if target buffer is too small. 
	{
		*nSizeOfDetails = nSize ;	// Return required size
		return -2 ;
	}

	memset( (void*)pDetails, 0, *nSizeOfDetails ) ;

	mpMixerControlStateInfo[n1].cbStruct = sizeof(MIXERCONTROLDETAILS) ;
	mpMixerControlStateInfo[n1].dwControlID = dwControlID ;

	// Future: use actual HWND (not NULL) if MIXERCONTROL.fdwControl 
	// MIXER_SETCONTROLDETAILSF_CUSTOM flag bit is set:
	mpMixerControlStateInfo[n1].hwndOwner = NULL ;	

	//Ignore MIXERCONTROL_CONTROLF_MULTIPLE flag:
	mpMixerControlStateInfo[n1].cMultipleItems = 0 ; 

	// .cChannels:
	if( mpMixerControl[n1].dwControlType & MIXERCONTROL_CONTROLTYPE_CUSTOM )
		mpMixerControlStateInfo[n1].cChannels = 1 ;
	//else if( bAllChanels  ||  mpMixerControl[n1].fdwControl & MIXERCONTROL_CONTROLF_UNIFORM )
	//	mpMixerControlStateInfo[n1].cChannels = 1 ;
	else
		mpMixerControlStateInfo[n1].cChannels = mpMixerLine.cChannels ;

	// Read the data from the control
	mmr = mixerGetControlDetails( (HMIXEROBJ)mhMixer, &mpMixerControlStateInfo[n1], 
										MIXER_GETCONTROLDETAILSF_VALUE ) ;	
	if( mmr != MMSYSERR_NOERROR )
		return -1 ;

	mpbHaveStateInfo[n1] = TRUE ;	// Indicate that state data is present; must do 
									// at least one read before a write can be done. 
	memcpy( (void*)pDetails, (void*)mpMixerControlStateInfo[n1].paDetails, 
		mpMixerControlStateInfo[n1].cChannels * mpMixerControlStateInfo[n1].cbDetails ) ;
	return 0 ;
}

// -----------------------------------------------------------------------------
// Set the state data for the selected control. 
// 
// Parameters:
// dwControlID    =	MIXERCONTROL.dwControlID
// pDetails       =	destination buffer for data to be written to the control
// nSizeOfDetails = Size of the destination buffer
// 
// Returns 0 on success. 
// Error returns:  
//	-1  : Control function call returned an error. 
//	-2  : Buffer too small.
//  -3  : ID not found.
// If the passed buffer size is incorrect, the required size is returned in 
// nSizeOfDetails
// -----------------------------------------------------------------------------
int CMixerControl::SetControStateData( DWORD dwControlID, void* pDetails, 
										unsigned int* nSizeOfDetails )	
{
	unsigned int n1 ;
	unsigned int nSize ;
	MMRESULT mmr ;

	// Get the control index associated with the ID value
	for( n1=0 ; n1<mnControlCount ; n1++ )
	{
		if( mpMixerControl[n1].dwControlID == dwControlID )
			break ;
	}

	if( n1 >= mnControlCount )	// Error return if ID not found  
	{
		*nSizeOfDetails = 0 ;
		return -3 ;	
	}

	if(	!mpbHaveStateInfo[n1] )	// Must do at least one read before 
		return -1 ;				// a write can be done. 

	// Note: cbDetails and cChannels are set in InitMixerControlDetails()
	nSize = mpMixerControlStateInfo[n1].cbDetails * 
			mpMixerControlStateInfo[n1].cChannels ;

	if( nSize > *nSizeOfDetails )	// Error return if buffer size is too small. 
	{
		*nSizeOfDetails = nSize ;	// return required size
		return -2 ;	
	}

	mpMixerControlStateInfo[n1].cbStruct = sizeof(MIXERCONTROLDETAILS) ;
	mpMixerControlStateInfo[n1].dwControlID = dwControlID ;

	// Future: use actual HWND (not NULL) if MIXERCONTROL.fdwControl 
	// MIXER_SETCONTROLDETAILSF_CUSTOM flag bit is set:
	mpMixerControlStateInfo[n1].hwndOwner = NULL ;	

	//Ignore MIXERCONTROL_CONTROLF_MULTIPLE flag:
	mpMixerControlStateInfo[n1].cMultipleItems = 0 ; 

	// .cChannels:
	if( mpMixerControl[n1].dwControlType & MIXERCONTROL_CONTROLTYPE_CUSTOM )
		mpMixerControlStateInfo[n1].cChannels = 1 ;
	//else if( bAllChanels  ||  mpMixerControl[n1].fdwControl & MIXERCONTROL_CONTROLF_UNIFORM )
	//	mpMixerControlStateInfo[n1].cChannels = 1 ;
	else
		mpMixerControlStateInfo[n1].cChannels = mpMixerLine.cChannels ;
	
	memcpy( (void*)mpMixerControlStateInfo[n1].paDetails, pDetails, 
				mpMixerLine.cChannels * mpMixerControlStateInfo[n1].cbDetails ) ;
	// Write the data to the control
	mmr = mixerSetControlDetails( (HMIXEROBJ)mhMixer, &mpMixerControlStateInfo[n1], 
										MIXER_SETCONTROLDETAILSF_VALUE ) ;
	if( mmr != MMSYSERR_NOERROR )
		return -1 ;

	return 0 ;
}

// -----------------------------------------------------------------------------
int CMixerControl::GetControlCount(void)
{
	return mnControlCount ;
}

// -----------------------------------------------------------------------------

