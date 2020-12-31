//////////////////////////////////////////////////////////////////////////
// CMciDevice implementation file
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
#include "mci.h"

//////////////////////////////////////////////////////////////////////////
// CMciDevice implementation
//

// Common Modes
const DWORD CMciDevice::ModeNotReady = MCI_MODE_NOT_READY;
const DWORD CMciDevice::ModePause	 = MCI_MODE_PAUSE;
const DWORD CMciDevice::ModePlay	 = MCI_MODE_PLAY;
const DWORD CMciDevice::ModeStop	 = MCI_MODE_STOP;
const DWORD CMciDevice::ModeOpen	 = MCI_MODE_OPEN;
const DWORD CMciDevice::ModeRecord	 = MCI_MODE_RECORD;
const DWORD CMciDevice::ModeSeek	 = MCI_MODE_SEEK;
// Common status
const DWORD CMciDevice::StatusReady			 = MCI_STATUS_READY;
const DWORD CMciDevice::StatusMediaPresent	 = MCI_STATUS_MEDIA_PRESENT;
const DWORD CMciDevice::StatusMode			 = MCI_STATUS_MODE;
const DWORD CMciDevice::StatusNumberOfTracks = MCI_STATUS_NUMBER_OF_TRACKS;
// Common capabilites
const DWORD CMciDevice::GetdevcapsCanEject	 = MCI_GETDEVCAPS_CAN_EJECT;
const DWORD CMciDevice::GetdevcapsCanPlay	 = MCI_GETDEVCAPS_CAN_PLAY;
const DWORD CMciDevice::GetdevcapsCanRecord	 = MCI_GETDEVCAPS_CAN_RECORD;
const DWORD CMciDevice::GetdevcapsCanSave	 = MCI_GETDEVCAPS_CAN_SAVE;
const DWORD CMciDevice::GetdevcapsCompound	 = MCI_GETDEVCAPS_COMPOUND_DEVICE;
const DWORD CMciDevice::GetdevcapsDeviceType = MCI_GETDEVCAPS_DEVICE_TYPE;
const DWORD CMciDevice::GetdevcapsHasAudio	 = MCI_GETDEVCAPS_HAS_AUDIO;
const DWORD CMciDevice::GetdevcapsHasVideo	 = MCI_GETDEVCAPS_HAS_VIDEO;
const DWORD CMciDevice::GetdevcapsUsesFiles	 = MCI_GETDEVCAPS_USES_FILES;

const DWORD CMciDevice::InfoProduct = MCI_INFO_PRODUCT;

const DWORD CMciDevice::DevtypeAnimation	= MCI_DEVTYPE_ANIMATION;
const DWORD CMciDevice::DevtypeCdaudio		= MCI_DEVTYPE_CD_AUDIO;		
const DWORD CMciDevice::DevtypeDat			= MCI_DEVTYPE_DAT;		
const DWORD CMciDevice::DevtypeDigitalvideo = MCI_DEVTYPE_DIGITAL_VIDEO;
const DWORD CMciDevice::DevtypeOther		= MCI_DEVTYPE_OTHER;
const DWORD CMciDevice::DevtypeOverlay		= MCI_DEVTYPE_OVERLAY;	
const DWORD CMciDevice::DevtypeScanner		= MCI_DEVTYPE_SCANNER;	
const DWORD CMciDevice::DevtypeSequencer	= MCI_DEVTYPE_SEQUENCER;
const DWORD CMciDevice::DevtypeVcr			= MCI_DEVTYPE_VCR;
const DWORD CMciDevice::DevtypeVideodisc	= MCI_DEVTYPE_VIDEODISC;
const DWORD CMciDevice::DevtypeWaveaudio	= MCI_DEVTYPE_WAVEFORM_AUDIO;

CMciDevice::CMciDevice() {
	m_wDeviceID = NULL;
	m_hMainWnd = NULL;
	m_bReportErrors = FALSE;
}

CMciDevice::~CMciDevice() {
}

// Open by device name (obtained by the registry or system.ini)
DWORD CMciDevice::Open(LPCSTR lpstrName, BOOL bShareable /*=FALSE*/) 
{	
	ASSERT(lpstrName != NULL);

	DWORD dwReturn;
	MCI_OPEN_PARMS mciOpenParms;

	// Open a device by specifying the device name.
	mciOpenParms.lpstrDeviceType = lpstrName;		
	
	DWORD dwFlags = MCI_OPEN_TYPE|MCI_WAIT;
	if (bShareable) dwFlags |= MCI_OPEN_SHAREABLE;

	dwReturn = SendCommand(MCI_OPEN, dwFlags, (DWORD)(LPVOID) &mciOpenParms);
	
	if (dwReturn == 0) {
		// The device opened successfully; get the device ID.
		m_wDeviceID = mciOpenParms.wDeviceID;		
	}
	
	return dwReturn;
}

// Open by device type
DWORD CMciDevice::Open(DWORD dwDeviceType, BOOL bShareable /*=FALSE*/) 
{
	DWORD dwReturn;
	MCI_OPEN_PARMS mciOpenParms;

	// Opens a device by specifying a device-type constant.
	mciOpenParms.lpstrDeviceType = (LPCSTR) dwDeviceType;
	
	DWORD dwFlags = MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_WAIT;
	if (bShareable) dwFlags |= MCI_OPEN_SHAREABLE;

	dwReturn = SendCommand(MCI_OPEN, dwFlags, 
			(DWORD)(LPVOID) &mciOpenParms);

	if (dwReturn == 0) {
		// The device opened successfully; get the device ID.
		m_wDeviceID = mciOpenParms.wDeviceID;		
	}
		
	return dwReturn;
}

// Closes the device
DWORD CMciDevice::Close() {	
	MCI_GENERIC_PARMS mciGenericParms;
	mciGenericParms.dwCallback = (DWORD) m_hMainWnd;
	return SendCommand(MCI_CLOSE, 0, (DWORD) &mciGenericParms);	
}

// Gets the current callback window
HWND CMciDevice::GetCallbackHwnd() const {
	return m_hMainWnd;
}

// Set the current callback window
void CMciDevice::SetCallbackWnd(CWnd *pWnd) {
	ASSERT(pWnd != NULL);
	m_hMainWnd = pWnd->GetSafeHwnd();
}

// Set the current callback window
void CMciDevice::SetCallbackWnd(HWND hWnd) {
	ASSERT(hWnd != NULL);
	m_hMainWnd = hWnd;
}

// Attaches the MCI device to a device already opened
void CMciDevice::Attach(UINT wDeviceID) {
	m_wDeviceID = wDeviceID;
}

// Gets the device ID
MCIDEVICEID CMciDevice::GetDeviceID() const {
	return m_wDeviceID;
}

// mciSendCommand with error handling
DWORD CMciDevice::SendCommand(UINT uMsg, DWORD fdwCommand, DWORD dwParam) {
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(m_wDeviceID, uMsg, fdwCommand, dwParam)) {
		m_dwLastError = dwReturn;
		if (m_bReportErrors) 
			ShowError(dwReturn);
	}
	return dwReturn;
}

MCIERROR CMciDevice::GetLastError() const {
	return m_dwLastError;
}

// Generic MCI_GETDEVCAPS_ITEM command: good for all devices
DWORD CMciDevice::GetDevCaps(DWORD dwDevcaps, BOOL bItem /*=FALSE*/) {	
	MCI_GETDEVCAPS_PARMS mciCapsParms;

	mciCapsParms.dwCallback = (DWORD) m_hMainWnd;    
    mciCapsParms.dwReturn = 0;
	
	if (bItem) {
		mciCapsParms.dwItem = dwDevcaps;
		dwDevcaps |= MCI_GETDEVCAPS_ITEM;
	}

	SendCommand(MCI_GETDEVCAPS, dwDevcaps, (DWORD) &mciCapsParms);
	
	return mciCapsParms.dwReturn;
}

// Generic MCI_INFO command
DWORD CMciDevice::GetInfo(DWORD dwInfo, LPSTR lpstrReturn, DWORD dwRetSize) {
	MCI_INFO_PARMS mciInfoParms;	
	 
	mciInfoParms.dwCallback = (DWORD) m_hMainWnd;
    mciInfoParms.lpstrReturn = lpstrReturn;
    mciInfoParms.dwRetSize = dwRetSize;

	return SendCommand(MCI_INFO, dwInfo, (DWORD) &mciInfoParms);	
}

// Set error report on/off
void CMciDevice::ReportErrors(BOOL bReport /*=TRUE*/) {
	m_bReportErrors = bReport;
}

// Uses mciGetErrorString to get a textual description of an MCI error.
// Displays the error description using MessageBox.
void CMciDevice::ShowError(DWORD dwError)
{
    char szErrorBuf[MAXERRORLENGTH];
    MessageBeep(MB_ICONEXCLAMATION);
	
	CWnd* pMainWnd = AfxGetApp()->m_pMainWnd;
	ASSERT(pMainWnd != NULL);
	HWND hMainWnd = pMainWnd->GetSafeHwnd();

    if(mciGetErrorString(dwError, (LPSTR) szErrorBuf, MAXERRORLENGTH)) {
		MessageBox(hMainWnd, szErrorBuf, _T("MCI Error"),
			       MB_ICONEXCLAMATION);
	}
    else
        MessageBox(hMainWnd, _T("Unknown Error"), _T("MCI Error"),
			       MB_ICONEXCLAMATION);
}

// Closes all MCI devices opened by the application.
// Waits until devices are closed before returning.
DWORD CMciDevice::CloseAll()
{
	DWORD dwReturn;

	if (dwReturn = mciSendCommand(MCI_ALL_DEVICE_ID, MCI_CLOSE, MCI_WAIT, NULL))
		ShowError(dwReturn);
	return dwReturn;
}

DWORD CMciDevice::GetMode() {
	return GetStatus(StatusMode);
}

// Generic MCI_STATUS command
DWORD CMciDevice::GetStatus(DWORD dwItem) {	
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwCallback = (DWORD) m_hMainWnd;
	mciStatusParms.dwItem = dwItem;
	mciStatusParms.dwReturn = 0;
	
	SendCommand(MCI_STATUS, MCI_STATUS_ITEM, (DWORD) &mciStatusParms);
		
	return mciStatusParms.dwReturn;
}