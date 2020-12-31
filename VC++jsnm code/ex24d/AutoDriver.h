// Machine generated IDispatch wrapper class(es) created with ClassWizard
// AutoDriver.h
/////////////////////////////////////////////////////////////////////////////
// IEx24bAuto wrapper class

class IEx24bAuto : public COleDispatchDriver
{
public:
	IEx24bAuto() {}		// calls COleDispatchDriver default constructor
	IEx24bAuto(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IEx24bAuto(const IEx24bAuto& dispatchSrc) : 
	    COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetLongData();
	void SetLongData(long);
	VARIANT GetTextData();
	void SetTextData(const VARIANT&);

// Operations
public:
	BOOL DisplayDialog();
};
