// TapiLine.h

#ifndef __MSM_TAPILINE__
#define __MSM_TAPILINE__

// In VC5+ do this.. ok
// To build  a TAPI 1.4 application put a define as below in your source
// file before you include TAPI.H:
//
#define TAPI_CURRENT_VERSION 0x00010004

#include <tapi.h>

//
// User defined messages notified by TAPI for Logs maintenence
// Capture them in to ur view class ok.
//

#define TAPI_LINECALLSTATE_CONNECTED WM_USER+5

#define WM_TAPI_DIALING			WM_USER+10
#define WM_TAPI_CONNECT			WM_TAPI_DIALING+1
#define WM_TAPI_DISCONNECT		WM_TAPI_DIALING+2
#define WM_TAPI_IDLE			WM_TAPI_DIALING+3	
#define WM_TAPI_STATUS			WM_TAPI_DIALING+4
#define WM_TAPI_CALL_PROCEEDING	WM_TAPI_DIALING+6
#define WM_TAPI_CALL_ACCEPTED	WM_TAPI_DIALING+7
#define WM_TAPI_LINE_REPLY		WM_TAPI_DIALING+8
#define WM_TAPI_VOICE_SUPPORT	WM_TAPI_DIALING+9

// All TAPI line functions return 0 for SUCCESS, so define it.
#define SUCCESS 0
#define ERRORS	-1


// The TAPI versions
#define TAPI_VERSION_1_0 0x00010003
#define TAPI_VERSION_1_4 0x00010004
#define TAPI_VERSION_2_0 0x00020000

// TAPI versions that this sample is designed to use.
#define WIN95TAPIVERSION		TAPI_VERSION_1_4
#define EARLY_TAPI_VERSION		TAPI_VERSION_1_0


/////////////////////////////////////////////////////////////////////////////
// CTapiLine window

class CTapiLine
{
protected:
	static CTapiLine* MyThis;
	
	HWND  m_hWnd;
	HINSTANCE m_hInst;

	// The params passed to call backs and are must...
	DWORD m_dwDevice, m_dwMessage, m_dwCallbackInstance;
    DWORD m_dwParam1, m_dwParam2, m_dwParam3;

    HLINEAPP m_LineHandle;	//  tapi line handle
    HCALL m_hCall;			//  call handle
    HLINE m_hLine;			//  line handle 
	HANDLE m_hComm;			//	comm handle
	DWORD m_dwLines;		//  count of available lines/devices
	LINECALLPARAMS m_LineParams;	// need this structure
	
	int  m_nDevice;
	long m_nPrivilege;
	long m_nMediaMode;

    DWORD m_dwAPIVersion;		// the API version
    char m_szPhoneNumber[64];	// the phone number to call
    char m_szMessage[128];		// Tapi reults

// Construction
public:
	CTapiLine();

// Attributes
public:

// Operations
protected:
// Overrides
	// protected virtual functions
    virtual void TapiCallBack();
    virtual void HandleCallState();

protected:
	void SetCallbackParams(
						DWORD dwDevice, DWORD dwMsg, 
						DWORD dwCallbackInstance, 
						DWORD dwParam1, DWORD dwParam2, 
						DWORD dwParam3);
	void Delay(UINT lFactor);
	void SetVarProps(HWND hWnd, DWORD hDevice );
	LONG LineStateConnected();

public:
// Overrides
	//
	// public virtual functions
	//
	virtual void Create(HWND& hWnd);
	virtual LONG DialCall( LPTSTR PhoneNumber );
    virtual LONG HangupCall();
	
// Implementation
public:
	virtual ~CTapiLine();
	void TapiStatus(LPSTR lpszError, BOOL bShowMsgBox=FALSE);
	LPSTR GetTapiStatus() const
	{
		return (LPSTR)m_szMessage;
	}
	// static functions
    static void CALLBACK lineCallbackFunc(
        DWORD dwDevice,DWORD dwMessage,DWORD dwCallbackInstance, 
        DWORD dwParam1,DWORD dwParam2, DWORD dwParam3);
};

#endif // __MSM_TAPILINE__

/////////////////////////////////////////////////////////////////////////////
