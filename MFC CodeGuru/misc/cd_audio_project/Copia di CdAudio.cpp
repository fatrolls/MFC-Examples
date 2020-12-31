//////////////////////////////////////////////////////////////////////////
// CCdAudio implementation file
//
// This class encapsulates the MCI API for the CD-Audio device
//
// Copyright (C) 1997, 1998 Giancarlo Iovino (giancarlo@saria.com)
// All rights reserved. May not be sold for profit.
//
// This software is provided 'as is' without implicit or explicit
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

CCdAudio::CCdAudio() {
	m_bOpened = FALSE;
}

// Open by device name (obtained by the registry or system.ini)
DWORD CCdAudio::OpenByName(LPCSTR lpstrName, CWnd* pWndNotify /*=NULL*/) 
{	
	ASSERT(lpstrName != NULL);

	DWORD dwReturn;
	MCI_OPEN_PARMS mciOpenParms;

	// Open a device by specifying the device name.
	mciOpenParms.lpstrDeviceType = lpstrName;		
	
	dwReturn = SendCommand(MCI_OPEN,
		MCI_OPEN_TYPE|MCI_OPEN_SHAREABLE|MCI_WAIT,
		(DWORD)(LPVOID) &mciOpenParms);
	
	if (dwReturn == 0) {
		// The device opened successfully; get the device ID.
		m_wDeviceID = mciOpenParms.wDeviceID;
		m_hMainWnd = pWndNotify ? pWndNotify->GetSafeHwnd() : 0;
	}
	
	m_bOpened = TRUE;
	return dwReturn;
}

// Open
DWORD CCdAudio::Open(CWnd* pWndNotify /*=NULL*/) 
{
	DWORD dwReturn;
	MCI_OPEN_PARMS mciOpenParms;

	// Opens a device by specifying a device-type constant.
	mciOpenParms.lpstrDeviceType = (LPCSTR) MCI_DEVTYPE_CD_AUDIO;
	
	dwReturn = SendCommand(MCI_OPEN,
		MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_OPEN_SHAREABLE|MCI_WAIT,
		(DWORD)(LPVOID) &mciOpenParms);

	if (dwReturn == 0) {
		// The device opened successfully; get the device ID.
		m_wDeviceID = mciOpenParms.wDeviceID;
		m_hMainWnd = pWndNotify ? pWndNotify->GetSafeHwnd() : 0;
	}
	
	m_bOpened = TRUE;
	return dwReturn;
}

// Close the device
DWORD CCdAudio::Close() {	
	MCI_GENERIC_PARMS mciGenericParms;
	mciGenericParms.dwCallback = (DWORD) m_hMainWnd;
	m_bOpened = FALSE;
	return SendCommand(MCI_CLOSE, 0, (DWORD) &mciGenericParms);	
}

// Set the device time format.
// Allowable time formats are:
// MCI_FORMAT_TMSF,	MCI_FORMAT_MSF, MCI_FORMAT_MILLISECONDS
DWORD CCdAudio::SetTimeFormat(DWORD dwTimeFormat) {   
	MCI_SET_PARMS mciSetParms;

    mciSetParms.dwTimeFormat = dwTimeFormat;

    return SendCommand(MCI_SET, 
        MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &mciSetParms);    
}

// Plays a given CD audio track using MCI_OPEN, MCI_PLAY. Returns as 
// soon as playback begins.
DWORD CCdAudio::PlayTrack(BYTE nTrack)
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
	if (dwReturn = Play(msfFrom, msfTo))
		return dwReturn;
    	
	// Restore the saved time format
	return SetTimeFormat(dwOldTimeFormat);
}

// Play CD from a position to another. dwFrom and dwTo are interpreted
// accordingly with the current time format.
DWORD CCdAudio::Play(DWORD dwFrom /*=0L*/, DWORD dwTo /*=0L*/)
{
    MCI_PLAY_PARMS mciPlayParms;
    
    mciPlayParms.dwFrom = dwFrom;
    mciPlayParms.dwTo = dwTo;
    mciPlayParms.dwCallback = (DWORD) m_hMainWnd;
    
	return SendCommand(MCI_PLAY,
        MCI_FROM | MCI_TO | MCI_NOTIFY, (DWORD)(LPVOID) &mciPlayParms);    
}

// Stop playback
DWORD CCdAudio::Stop() {
	MCI_GENERIC_PARMS mciGenericParms;

	mciGenericParms.dwCallback = (DWORD) m_hMainWnd;

	return SendCommand(MCI_STOP, 0, (DWORD) &mciGenericParms);
}

// Pause playback
DWORD CCdAudio::Pause() {
	MCI_GENERIC_PARMS mciGenericParms;

	mciGenericParms.dwCallback = (DWORD) m_hMainWnd;
	
	return SendCommand(MCI_PAUSE, 0, (DWORD) &mciGenericParms);
}

// Open the CD door
DWORD CCdAudio::SetDoorOpen(BOOL bOpen)
{
	if (bOpen)
		return Set(MCI_SET_DOOR_OPEN);
	else
		return Set(MCI_SET_DOOR_CLOSED);
}

// Generic MCI_SET command
DWORD CCdAudio::Set(DWORD dwWhat)
{
	MCI_SET_PARMS mciSetParms;

	mciSetParms.dwCallback = (DWORD) m_hMainWnd;
	
	return SendCommand(MCI_SET, dwWhat, (DWORD) &mciSetParms);
}

// Obtains a description of the hardware associated with a device.
// Devices should supply a description that identifies both the driver and the hardware used.
DWORD CCdAudio::GetProductInfo(LPSTR lpstrReturn, DWORD dwRetSize) {
	return GetInfo(MCI_INFO_PRODUCT, lpstrReturn, dwRetSize);		
}

// Get the media identity
DWORD CCdAudio::GetMediaIdentity(LPSTR lpstrReturn, DWORD dwRetSize) {
	return GetInfo(MCI_INFO_MEDIA_IDENTITY, lpstrReturn, dwRetSize);	
}

// Get media UPC (Universal Product Code). The UPC is a string of digits
// and might not be available for all CDs
DWORD CCdAudio::GetMediaUPC(LPSTR lpstrReturn, DWORD dwRetSize) {
	return GetInfo(MCI_INFO_MEDIA_UPC, lpstrReturn, dwRetSize);	
}

// Generic MCI_INFO command
DWORD CCdAudio::GetInfo(DWORD dwInfo, LPSTR lpstrReturn, DWORD dwRetSize) {
	MCI_INFO_PARMS mciInfoParms;	
	 
	mciInfoParms.dwCallback = (DWORD) m_hMainWnd;
    mciInfoParms.lpstrReturn = lpstrReturn;
    mciInfoParms.dwRetSize = dwRetSize;

	return SendCommand(MCI_INFO, dwInfo, (DWORD) &mciInfoParms);	
}

// Get the starting position of a track
DWORD CCdAudio::GetTrackPos(DWORD dwTrack) {	
	return GetTrackInfo(dwTrack, MCI_STATUS_POSITION);	
}

// Get the type of a track
DWORD CCdAudio::GetTrackType(DWORD dwTrack) {	
	return GetTrackInfo(dwTrack, MCI_CDA_STATUS_TYPE_TRACK);
}

// Get the length of a track
DWORD CCdAudio::GetTrackLength(DWORD dwTrack) {	
	return GetTrackInfo(dwTrack, MCI_STATUS_LENGTH);
}

// Get a track info item
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

// Get current track
DWORD CCdAudio::GetCurrentTrack() {
	return GetStatusItem(MCI_STATUS_CURRENT_TRACK);
}

// Get media Lenght
DWORD CCdAudio::GetMediaLenght() {
	return GetStatusItem(MCI_STATUS_LENGTH);
}

// Get the starting position
DWORD CCdAudio::GetStartPos() {
	return GetStatusItem(MCI_STATUS_START);
}

// Get the CD status mode
DWORD CCdAudio::GetMode() {
	return GetStatusItem(MCI_STATUS_MODE);
}

// Get current position
DWORD CCdAudio::GetCurrentPos() {
	return GetStatusItem(MCI_STATUS_POSITION);
}

// Get the current time format
DWORD CCdAudio::GetTimeFormat() {
	return GetStatusItem(MCI_STATUS_TIME_FORMAT);
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

// Check if the CD device can play
BOOL CCdAudio::CanPlay() {
	return GetDevCaps(MCI_GETDEVCAPS_CAN_PLAY);
}

// Check if the CD device can eject
BOOL CCdAudio::CanEject() {
	return GetDevCaps(MCI_GETDEVCAPS_CAN_EJECT);
}

// Get the number of playable tracks: all devices support this command
DWORD CCdAudio::GetNumberOfTracks()
{
	return GetStatusItem(MCI_STATUS_NUMBER_OF_TRACKS);	
}

// Check if the MCI device is ready: all devices support this command
BOOL CCdAudio::IsReady() {
	return GetStatusItem(MCI_STATUS_READY);
}

// Check if the media is present: all devices support this command
BOOL CCdAudio::IsMediaPresent() {
	return GetStatusItem(MCI_STATUS_MEDIA_PRESENT);
}

// Check if the CD is playing
BOOL CCdAudio::IsPlaying() { 
	return (GetMode() == MCI_MODE_PLAY); 
}

// Check if the device was successfully opened
BOOL CCdAudio::IsOpened() const { 
	return m_bOpened; 
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

// Generic MCI_STATUS_ITEM command
DWORD CCdAudio::GetStatusItem(DWORD dwItem) {	
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwCallback = (DWORD) m_hMainWnd;
    mciStatusParms.dwItem = dwItem;
    mciStatusParms.dwReturn = 0;
	
	SendCommand(MCI_STATUS, MCI_STATUS_ITEM, (DWORD) &mciStatusParms);
		
	return mciStatusParms.dwReturn;
}