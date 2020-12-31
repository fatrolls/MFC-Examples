// Machine generated IDispatch wrapper class(es) created with ClassWizard
// ClockDriver.h
/////////////////////////////////////////////////////////////////////////////
// IEx24c wrapper class

class IEx24c : public COleDispatchDriver
{
public:
	IEx24c() {}		// Calls COleDispatchDriver default constructor
	IEx24c(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IEx24c(const IEx24c& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	DATE GetTime();
	void SetTime(DATE);

// Operations
public:
	VARIANT GetFigure(short n);
	void SetFigure(short n, const VARIANT& newValue);
	void ShowWin();
	LPDISPATCH CreateAlarm(DATE Time);
	void RefreshWin();
};
/////////////////////////////////////////////////////////////////////////////
// IAlarm wrapper class

class IAlarm : public COleDispatchDriver
{
public:
	IAlarm() {}		// Calls COleDispatchDriver default constructor
	IAlarm(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAlarm(const IAlarm& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	DATE GetTime();
	void SetTime(DATE);

// Operations
public:
};
