// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// ITeleSc wrapper class

class ITeleSc : public COleDispatchDriver
{
public:
	ITeleSc() {}		// Calls COleDispatchDriver default constructor
	ITeleSc(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ITeleSc(const ITeleSc& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetFinished();
	void SetFinished(BOOL);
	BOOL GetServer();
	void SetServer(BOOL);
	BOOL GetAsciiOut();
	void SetAsciiOut(BOOL);
	short GetResultCode();
	void SetResultCode(short);
	BOOL GetTestMode();
	void SetTestMode(BOOL);
	BOOL GetCallStarted();
	void SetCallStarted(BOOL);

// Operations
public:
	BOOL ToScript(LPCTSTR FieldLabel, LPCTSTR Value);
	void ShutDown();
	BOOL OpenScript(LPCTSTR FullPath);
	BOOL FromScript(LPCTSTR Label, BSTR* Value);
	BOOL ResetScript();
	VARIANT GetValue(LPCTSTR FieldName);
	void AddResultCode(LPCTSTR Name, short Code, short Callback);
	void BringMainWindowToTop();
	BOOL OutputValues(LPCTSTR szPath, LPCTSTR szOperator, short iResultCode, long lDuration, short iOutputMode);
	void HideMainWindow();
	BOOL MakeDst(LPCTSTR szPath);
	CString GetFirstFieldName();
	CString GetNextFieldName();
};
