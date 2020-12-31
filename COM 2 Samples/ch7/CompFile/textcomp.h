// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// ITextObject wrapper class

class ITextObject : public COleDispatchDriver
{
public:
	ITextObject() {}		// Calls COleDispatchDriver default constructor
	ITextObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ITextObject(const ITextObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetText();
	void SetText(const VARIANT&);

// Operations
public:
};
