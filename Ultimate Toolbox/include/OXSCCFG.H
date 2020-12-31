// ==========================================================================
// 							Class Specification : COXSerialCommConfig
// ==========================================================================

// Header file : OXSCCFG.H

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	NO	Is derived from Wnd
//	NO  Two stage creation (constructor & Initialize())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Description :         
//	COXSerialCommConfig class
//		This object defines the port configuration settings like port ID, baudrate,
//		bytesize, parity, stopbits and flowcontrol. You can set also the size of
//		the software buffers and the timeout values of the ‘clear to send’,
//		‘data set ready’ and ‘Carrier detect’ signals. These settings can be loaded
//		and saved to disk.

// Remark:
//


// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXSCCFG_H_
#define __OXSCCFG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXSerialCommConfig : public CObject
{
	DECLARE_SERIAL(COXSerialCommConfig);

// Data Members
public:
	enum EFlowControl				// flow control enum type
	{
		NONE,
		HARDWARE,
		XON_XOFF
	};

    BYTE m_nPortId;					// 0..8 (COM1..COM9)
    UINT m_nBaudRate;				// CBR_xxx (as in DCB)
    BYTE m_nByteSize;				// 7..8 (as in DCB)
    BYTE m_nParity;					// 0..2 (as in DCB)
    BYTE m_nStopBits;				// 0/2  (as in DCB)
    EFlowControl m_eFlowControl;	// flow control type

    UINT m_nSizeReceivingQueue;		// buffer size of the incomming queue
    UINT m_nSizeTransmissionQueue;	// buffer size of the outgoing queue
    UINT m_nCdTimeout;				// the time that the carrier must be down
									// before the signal is changing state
    UINT m_nCtsTimeout;				// Clear to send timeout
    UINT m_nDsrTimeout;				// Data set ready timeout

protected:

private:

// Member Functions
public:
	COXSerialCommConfig();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: Constructs the configutration object

	COXSerialCommConfig(COXSerialCommConfig& config);
	// --- In: config: another COXSerialCommConfig object
	// --- Out: none
	// --- Returns: none
	// --- Effect: copy constructor

    COXSerialCommConfig& operator = (const COXSerialCommConfig& config);
	// --- In: config: another COXSerialCommConfig object
	// --- Out: none
	// --- Returns: the reference of the object that is copied into
	// --- Effect: copy operator

	CString GetCommName() const;
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the communication device as a stdio filename
	//				(example: "COM1" for port com1)
	// --- Effect: none

    int DoConfigDialog(CString sTitle = _T(""));
	// --- In: sTitle: the title of the dialog box (a default title is used if empty)
	// --- Out: none
	// --- Returns: IDOK or IDCANCEL
	// --- Effect: start a modal configuration dialog box 

    BOOL IsPortAvailable() const;   
	// --- In: none
	// --- Out: none
	// --- Returns: if the port is available or not
	// --- Effect: tries to open the port

    BOOL Load(CString sFileName);
	// --- In: sFileName: the filename of the configuration file
	// --- Out: none
	// --- Returns: if the configuration file is successfully loaded
	// --- Effect: loads the configuration file into this object

    BOOL Save(CString sFileName);
	// --- In: sFileName: the filename of the configuration file
	// --- Out: none
	// --- Returns: if the configuration file is successfully saved
	// --- Effect: saves the configuration setting to file

protected:
	virtual void Serialize(CArchive& ar);

private:

};

#endif //__OXSCCFG_H_
