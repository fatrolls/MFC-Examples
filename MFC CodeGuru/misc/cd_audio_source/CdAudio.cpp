//////////////////////////////////////////////////////////////////////////
// CCdAudio implementation file
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

#include "stdafx.h"
#include "CdAudio.h"

//////////////////////////////////////////////////////////////////////////
// CCdAudio implementation
//
const DWORD CCdAudio::FormatMilliseconds = MCI_FORMAT_MILLISECONDS;
const DWORD CCdAudio::FormatMSF			 = MCI_FORMAT_MSF;
const DWORD CCdAudio::FormatTMSF		 = MCI_FORMAT_TMSF;

const DWORD CCdAudio::StatusCurrentTrack = MCI_STATUS_CURRENT_TRACK;
const DWORD CCdAudio::StatusLength		 = MCI_STATUS_LENGTH;
const DWORD CCdAudio::StatusPosition	 = MCI_STATUS_POSITION;
const DWORD CCdAudio::StatusStart		 = MCI_STATUS_START;

const DWORD CCdAudio::TrackTypeAudio = MCI_CDA_TRACK_AUDIO;
const DWORD CCdAudio::TrackTypeOther = MCI_CDA_TRACK_OTHER;

// Open
DWORD CCdAudio::Open(BOOL bShareable /*=FALSE*/) 
{
	return CMciDevice::Open(MCI_DEVTYPE_CD_AUDIO, bShareable);	
}

// Set the device time format. Allowable time formats are:
// MCI_FORMAT_TMSF, MCI_FORMAT_MSF, MCI_FORMAT_MILLISECONDS
DWORD CCdAudio::SetTimeFormat(DWORD dwTimeFormat) {   
	MCI_SET_PARMS mciSetParms;
	
	mciSetParms.dwTimeFormat = dwTimeFormat;

	return SendCommand(MCI_SET, 
        	MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &mciSetParms);    
}

// Gest the current time format
DWORD CCdAudio::GetTimeFormat() {
	return GetStatus(MCI_STATUS_TIME_FORMAT);
}

// Plays a given CD audio track using MCI_OPEN, MCI_PLAY. Returns as 
// soon as playback begins.
DWORD CCdAudio::PlayTrack(BYTE nTrack, BOOL bAsync /*=TRUE*/)
{
	DWORD dwReturn;
	// Save current time format
	DWORD dwOldTimeFormat = GetTimeFormat();
    
	// Set the time format to track/minute/second/frame (TMSF).
    if (dwReturn = SetTimeFormat(MCI_FORMAT_TMSF))
		return dwReturn;
	
	// Get track lenght
	CMsf msf = GetTrackLength(nTrack);
	
	CTmsf msfFrom = CTmsf(nTrack, 0, 0, 0);
	CTmsf msfTo = CTmsf(nTrack, 
		msf.GetMinute(), msf.GetSecond(), msf.GetFrame());
	    
	// Play the track
	if (dwReturn = Play(msfFrom, msfTo, bAsync))
		return dwReturn;
    	
	// Restore the saved time format
	return SetTimeFormat(dwOldTimeFormat);
}

// Plays CD from a position to another. dwFrom and dwTo are interpreted
// accordingly with the current time format.
DWORD CCdAudio::Play(DWORD dwFrom /*=0L*/, DWORD dwTo /*=0L*/, 
					 BOOL bAsync /*=TRUE*/)
{
	MCI_PLAY_PARMS mciPlayParms;
    mciPlayParms.dwFrom = dwFrom;
	mciPlayParms.dwTo = dwTo;
	
	DWORD dwFlags = MCI_FROM | MCI_TO;
	if (bAsync) {		
		mciPlayParms.dwCallback = (DWORD) m_hMainWnd;
		dwFlags |= MCI_NOTIFY;
	}

	return SendCommand(MCI_PLAY, dwFlags, (DWORD)(LPVOID) &mciPlayParms);
}

// Stops playback
DWORD CCdAudio::Stop() {
	MCI_GENERIC_PARMS mciGenericParms;

	mciGenericParms.dwCallback = (DWORD) m_hMainWnd;

	return SendCommand(MCI_STOP, 0, (DWORD) &mciGenericParms);
}

// Pauses playback
DWORD CCdAudio::Pause() {
	MCI_GENERIC_PARMS mciGenericParms;

	mciGenericParms.dwCallback = (DWORD) m_hMainWnd;
	
	return SendCommand(MCI_PAUSE, 0, (DWORD) &mciGenericParms);
}

// Open the CD door
DWORD CCdAudio::OpenDoor(BOOL bOpen /*=TRUE*/)
{
	if (bOpen)
		return Set(MCI_SET_DOOR_OPEN);
	else
		return Set(MCI_SET_DOOR_CLOSED);
}

// Retrieves the starting position of a track
DWORD CCdAudio::GetTrackPos(DWORD dwTrack) {	
	return GetTrackInfo(dwTrack, StatusPosition);	
}

// Retrieves the type of a track
DWORD CCdAudio::GetTrackType(DWORD dwTrack) {	
	return GetTrackInfo(dwTrack, MCI_CDA_STATUS_TYPE_TRACK);
}

// Retrieves the length of a track
DWORD CCdAudio::GetTrackLength(DWORD dwTrack) {	
	return GetTrackInfo(dwTrack, StatusLength);
}

// Retrieves the total CD length
DWORD CCdAudio::GetMediaLength(DWORD dwTrack) {	
	return GetStatus(StatusLength);
}

// Retrieves a track information
DWORD CCdAudio::GetTrackInfo(DWORD dwTrack, DWORD dwItem) {	
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwCallback = (DWORD) m_hMainWnd;
	mciStatusParms.dwItem = dwItem;
	mciStatusParms.dwTrack = dwTrack;
	mciStatusParms.dwReturn = 0;
	
	SendCommand(MCI_STATUS, 
		MCI_STATUS_ITEM|MCI_TRACK, (DWORD) &mciStatusParms);
		
	return mciStatusParms.dwReturn;
}

// Retrieves the current track
DWORD CCdAudio::GetCurrentTrack() {
	return GetStatus(StatusCurrentTrack);
}

// Retrieves the CD current position
DWORD CCdAudio::GetCurrentPos() {
	return GetStatus(StatusPosition);
}

// Retrieves the CD starting position
DWORD CCdAudio::GetStartPos() {
	return GetStatus(StatusStart);
}

// Gets the number of playable tracks
DWORD CCdAudio::GetNumberOfTracks() {
	return GetStatus(StatusNumberOfTracks);
}

// Seek to a specified position
DWORD CCdAudio::Seek(DWORD dwTo, BOOL bAsync /*=FALSE*/) {
	return Seek(dwTo, MCI_TO, bAsync);
}

// Seek to end
DWORD CCdAudio::SeekToStart(BOOL bAsync /*=FALSE*/) {
	return Seek(0, MCI_SEEK_TO_START, bAsync);
}

// Seek to start
DWORD CCdAudio::SeekToEnd(BOOL bAsync /*=FALSE*/) {
	return Seek(0, MCI_SEEK_TO_END, bAsync);
}

// Generic Seek
DWORD CCdAudio::Seek(DWORD dwTo, DWORD dwFlags, BOOL bAsync) {	
	MCI_SEEK_PARMS mciSeekParms;

	if (bAsync) {
		mciSeekParms.dwCallback = (DWORD) m_hMainWnd;
		dwFlags |= MCI_NOTIFY;
	}

	mciSeekParms.dwTo = dwTo;
    	
	return SendCommand(MCI_SEEK, dwFlags, (DWORD) &mciSeekParms);	
}

// Checks if the device is Ready to be operated
BOOL CCdAudio::IsReady() {
	return GetStatus(StatusReady);
}

// Generic MCI_SET command
DWORD CCdAudio::Set(DWORD dwWhat)
{
	MCI_SET_PARMS mciSetParms;

	mciSetParms.dwCallback = (DWORD) m_hMainWnd;
	
	return SendCommand(MCI_SET, dwWhat, (DWORD) &mciSetParms);
}

// Generic MCI_GETDEVCAPS_ITEM command
DWORD CCdAudio::GetDevCapsItem(DWORD dwItem) {	
	MCI_GETDEVCAPS_PARMS mciCapsParms;

	mciCapsParms.dwCallback = (DWORD) m_hMainWnd;
	mciCapsParms.dwItem = dwItem;
	mciCapsParms.dwReturn = 0;
	
	SendCommand(MCI_GETDEVCAPS, MCI_GETDEVCAPS_ITEM,
		(DWORD) &mciCapsParms);
	
	return mciCapsParms.dwReturn;
}

