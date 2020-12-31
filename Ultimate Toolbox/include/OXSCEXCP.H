#ifndef __OXSCEXCP_H_
#define __OXSCEXCP_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


OX_API_DECL void AFXAPI AfxThrowSerialCommException(int cause,
													LPCTSTR lpszSerialCommName = NULL);

class OX_CLASS_DECL COXSerialCommException: public CFileException
{
DECLARE_DYNAMIC(COXSerialCommException)

// Data Members
public:
	enum VALUE
	{
		none,
		notAvailable,
		breakDetect,
		rxTimeout,
		ctsTimeout,
		dsrTimeout,
		cdTimeout,
		frameError,
		parityError,
		overrunError,
		rxQueueOverflow,
		txQueueFull,
		wmQuitReceived,
		ioError,
		modeError
	};

	int m_ext_cause;

// Member Functions
public:
	COXSerialCommException(int cause = none,
		LPCTSTR lpszSerialCommName = NULL);
	COXSerialCommException(COXSerialCommException& other);
	COXSerialCommException& operator = (const COXSerialCommException& other);
	virtual BOOL GetErrorMessage( LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext = NULL );
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif


};

#endif //__OXSCEXCP_H_
