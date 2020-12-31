// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// ICMPCom wrapper class

class ICMPCom : public COleDispatchDriver
{
public:
	ICMPCom() {}		// Calls COleDispatchDriver default constructor
	ICMPCom(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ICMPCom(const ICMPCom& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void StartICMP();
	void StopICMP();
	void SetPingVariables(LPCTSTR hostname, long opttrcrt, long optresolve, long optnofrag, long optruntointerupt, long optttl, long optpacketlen, long optnumpackets, long optrroutenum, long opttimestamp, long opttos, long opttimeout);
	void RunPing();
	void StopPing();
};
