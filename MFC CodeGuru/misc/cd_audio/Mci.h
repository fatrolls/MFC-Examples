//////////////////////////////////////////////////////////////////////////
// Mci.h : header file
//
// This header file provides generic support for mci devices
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

#if !defined(AFX_MCI_H_098R22G3234_23453_235124_123A44HQ13451_INCLUDED_)
#define AFX_MCI_H_098R22G3234_23453_235124_123A44HQ13451_INCLUDED_

#include <mmsystem.h>

class CMsf {
public:
	CMsf() {
		m_dwMsf = 0;
	}

	CMsf(DWORD dwMsf) {		
		m_dwMsf = dwMsf;
	}

	CMsf(BYTE minute, BYTE second, BYTE frame) {		
		m_dwMsf = MCI_MAKE_MSF(minute, second, frame);
	}
	
	operator DWORD() const {return m_dwMsf;}
	
	BYTE GetMinute() const { return MCI_MSF_MINUTE(m_dwMsf); }
	BYTE GetSecond() const { return MCI_MSF_SECOND(m_dwMsf); }
	BYTE GetFrame() const { return MCI_MSF_FRAME(m_dwMsf); }

protected:
	DWORD m_dwMsf;
};

class CTmsf {
public:
	CTmsf() {
		m_dwTmsf = 0;
	}

	CTmsf(DWORD dwTmsf) {		
		m_dwTmsf = dwTmsf;
	}

	CTmsf(BYTE track, BYTE minute, BYTE second, BYTE frame) {		
		m_dwTmsf = MCI_MAKE_TMSF(track, minute, second, frame);
	}
	
	operator DWORD() const {return m_dwTmsf;}

	BYTE GetTrack() const { return MCI_TMSF_TRACK(m_dwTmsf); }
	BYTE GetMinute() const { return MCI_TMSF_MINUTE(m_dwTmsf); }
	BYTE GetSecond() const { return MCI_TMSF_SECOND(m_dwTmsf); }
	BYTE GetFrame() const { return MCI_TMSF_FRAME(m_dwTmsf); }

protected:
	DWORD m_dwTmsf;
};

//////////////////////////////////////////////////////////////////////////
// The CMciDevice class is the base class for all MCI devices
//
class CMciDevice {
public:	
	// Common modes
	static const DWORD ModeNotReady;
	static const DWORD ModePause;
	static const DWORD ModePlay;
	static const DWORD ModeStop;
	static const DWORD ModeOpen;
	static const DWORD ModeRecord;
	static const DWORD ModeSeek;
	// Common status items
	static const DWORD StatusReady;
	static const DWORD StatusMediaPresent;
	static const DWORD StatusMode;
	static const DWORD StatusNumberOfTracks;
	// Common capabilites
	static const DWORD GetdevcapsCanEject;
	static const DWORD GetdevcapsCanPlay;
	static const DWORD GetdevcapsCanRecord;
	static const DWORD GetdevcapsCanSave;
	static const DWORD GetdevcapsCompound;
	static const DWORD GetdevcapsDeviceType;	
	static const DWORD GetdevcapsHasAudio;
	static const DWORD GetdevcapsHasVideo;
	static const DWORD GetdevcapsUsesFiles;
	
	// Device Info
	static const DWORD InfoProduct;

	// Device types
	static const DWORD DevtypeAnimation;
	static const DWORD DevtypeCdaudio;
	static const DWORD DevtypeDat;
	static const DWORD DevtypeDigitalvideo;
	static const DWORD DevtypeOther;
	static const DWORD DevtypeOverlay;
	static const DWORD DevtypeScanner;
	static const DWORD DevtypeSequencer;
	static const DWORD DevtypeVcr;
	static const DWORD DevtypeVideodisc;
	static const DWORD DevtypeWaveaudio;

	

	// Construction/Destruction
	CMciDevice();
	~CMciDevice();

	// Open/Close: All derived classes must implement them
	virtual DWORD Open(DWORD dwDeviceType, BOOL bShareable = FALSE);
	virtual DWORD Open(LPCSTR lpstrName, BOOL bShareable = FALSE);	
	virtual DWORD Close();

	// Attaches the device to a MCI device already opened
	inline void  Attach(UINT wDeviceID);
	
	// Gets device ID
	MCIDEVICEID GetDeviceID() const;
	
	// Closes all open MCI devices: wait until devices are closed
	static  DWORD CloseAll();
	
	// Retrieves a device static information
	DWORD GetDevCaps(DWORD dwDevcaps, BOOL bItem = FALSE);
	
	// Retrieves a device status item
	virtual DWORD GetStatus(DWORD dwStatusItem);
	
	// Retrieves the device mode
	virtual DWORD GetMode();

	// Retrieves a string information from the device
	virtual DWORD GetInfo(DWORD dwInfo, LPSTR lpstrReturn, DWORD dwRetSize);

	// Get/Set Callback Window
	HWND GetCallbackHwnd() const;
	void SetCallbackWnd(CWnd* pWnd);
	void SetCallbackWnd(HWND hWnd);
	
	// Sets MCI error report on/off
	void ReportErrors(BOOL bReport = TRUE);

protected:
	// mciSendCommand with error handling
	DWORD SendCommand(UINT uMsg, DWORD fdwCommand, DWORD dwParam);
		
	// MCI error report
	static void ShowError(DWORD dwError);
	MCIERROR GetLastError() const;

// Data members
protected:
	MCIDEVICEID	m_wDeviceID;					// The device ID
	HWND		m_hMainWnd;						// The callback window handle

private:
	MCIERROR	m_dwLastError;					// The last error code
	BOOL		m_bReportErrors;				// Report MCI errors?	
};

#endif // !defined(AFX_MCI_H_098R22G3234_23453_235124_123A44HQ13451_INCLUDED_)
