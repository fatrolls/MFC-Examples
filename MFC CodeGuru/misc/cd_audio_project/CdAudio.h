//////////////////////////////////////////////////////////////////////////
// CCdAudio header file
//
// This class encapsulates the MCI API for the CD-Audio device
//
// Copyright (C) 1997, 1998 Giancarlo Iovino (giancarlo@saria.com)
// All rights reserved. May not be sold for profit.
//
// This software is provided 'as it is' without implicit or explicit
// warranty.
//
// This code was develeped for MFC Programmer's Sourcebook
// (http://www.codeguru.com)
//

#if !defined(AFX_MCI_H_0S1R45G3534_142DS_215344_123444DGG3451_INCLUDED_)
#define AFX_MCI_H_0S1R45G3534_142DS_215344_123444DGG3451_INCLUDED_

#include "mci.h"

//////////////////////////////////////////////////////////////////////////
// CCdAudio
//

class CCdAudio : public CMciDevice {

public:
	// Specific time formats	
	static const DWORD FormatMilliseconds;
	static const DWORD FormatMSF;
	static const DWORD FormatTMSF;

	// Specific status
	static const DWORD StatusCurrentTrack;
	static const DWORD StatusLength;
	static const DWORD StatusPosition;
	static const DWORD StatusStart;
	static const DWORD TrackTypeAudio;
	static const DWORD TrackTypeOther;	
	
	// Specific info
	static const DWORD InfoProduct;
	static const DWORD InfoMediaIdentity;
	static const DWORD InfoMediaUPC;	
	
	// Open	
	DWORD Open(BOOL bShareable = FALSE);	
	
	// Playback/Stop/Pause
	DWORD PlayTrack(BYTE bTrack, BOOL bAsync = TRUE);
	DWORD Play(DWORD dwFrom = 0L, DWORD dwTo = 0L, BOOL bAsync = TRUE);
	DWORD Stop();		
	DWORD Pause();
	
	// Open/Close CD door
	DWORD OpenDoor(BOOL bOpenDoor /*=TRUE*/);	
	
	// Seek	
	DWORD Seek(DWORD dwTo, BOOL bAsync = FALSE);
	DWORD SeekToStart(BOOL bAsync = FALSE);
	DWORD SeekToEnd(BOOL bAsync = FALSE);

	// Device status important items
	DWORD GetMediaLength(DWORD dwTrack);
	DWORD GetNumberOfTracks();		
	DWORD GetCurrentTrack();
	DWORD GetCurrentPos();
	DWORD GetStartPos();
	BOOL IsReady();
	
	// Track info		
	DWORD GetTrackPos(DWORD dwTrack);
	DWORD GetTrackLength(DWORD dwTrack);
	DWORD GetTrackType(DWORD dwTrack);	
	
	// Get/Set the time format
	DWORD GetTimeFormat();
	DWORD SetTimeFormat(DWORD dwTimeFormat);

protected:
	DWORD Seek(DWORD dwTo, DWORD dwFlags, BOOL bAsync);
	DWORD Set(DWORD dwWhat);	
	DWORD GetDevCapsItem(DWORD dwItem);	
	DWORD GetTrackInfo(DWORD dwTrack, DWORD dwItem);
};

#endif // !defined(AFX_MCI_H_0S1R45G3534_142DS_215344_123444DGG3451_INCLUDED_)