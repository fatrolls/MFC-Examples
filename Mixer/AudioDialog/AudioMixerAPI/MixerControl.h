// -----------------------------------------------------------------------------
// MixerControl.h
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

// -----------------------------------------------------------------------------
class CMixerControl
{
public:
	CMixerControl(void);
	virtual ~CMixerControl(void);

	int GetControlCount(void) ;
	int GetControlInfo(MIXERLINE* pMixerLine, HMIXER hMixer );
	int GetControlInfoByIndex( int nIndex, MIXERCONTROL* pMC ) ;
	int GetControStateData(DWORD dwControlID, void* pDetails, unsigned int* nSizeOfDetails); 
	int SetControStateData(DWORD dwControlID, void* pDetails, unsigned int* nSizeOfDetails); 

protected:

	int InitMixerControlDetails() ;
	void CleanupHeap() ;

	HMIXER				 mhMixer ;
	unsigned int		 mnControlCount ;			// Number of controls for this mixer line
	MIXERLINE			 mpMixerLine ;				// Line info for this line
	MIXERLINECONTROLS	 mMixerLineControls ;

	bool*				 mpbHaveStateInfo ;			// Indicates that state data has been previously read
	void*				 mpControlData ;
	MIXERCONTROL*		 mpMixerControl ;			// One MIXERCONTROL per control
	MIXERCONTROLDETAILS* mpMixerControlStateInfo ;	// One MIXERCONTROLDETAILS per control
} ;

// -----------------------------------------------------------------------------
