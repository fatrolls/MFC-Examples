// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// CCgiDispatchDrv wrapper class

class CCgiDispatchDrv : public COleDispatchDriver
{
public:
	CCgiDispatchDrv() {}		// Calls COleDispatchDriver default constructor
	CCgiDispatchDrv(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCgiDispatchDrv(const CCgiDispatchDrv& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetOutput(LPCTSTR sOutput);
	CString GetInput(const VARIANT& vIndex);
	CString GetPathInfo();
	CString GetScriptName();
	CString GetAccepted();
	CString GetRemoteAddress();
	CString GetClientInfo(LPCTSTR sInfoKey);
	CString GetServerName();
	short GetServerPort();
	CString GetServerProtocol();
	CString GetServerSoftware();
};
