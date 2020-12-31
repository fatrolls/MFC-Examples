	
// CICMPCom.h : Declaration of the CCICMPCom

#ifndef __CICMPCOM_H_
#define __CICMPCOM_H_

#include "resource.h"       // main symbols
//#include "cpicmpcom.h"      // proxy events
#include "cpdicmpcom.h"      // proxy events
#include "pingparmlist.h"


/////////////////////////////////////////////////////////////////////////////
// CCICMPCom
class ATL_NO_VTABLE CCICMPCom : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCICMPCom, &CLSID_CICMPCom>,
	public IConnectionPointContainerImpl<CCICMPCom>,
	public IDispatchImpl<ICMPCom, &IID_ICMPCom, &LIBID_ICMPCOMLib>,
	public CProxyDICMPComEvent<CCICMPCom>
{
public:
	CCICMPCom()
	{
		m_pUnkMarshaler = NULL;
		m_pPingParmList = NULL;
		m_Thread = NULL;
		
		
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CICMPCOM)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CCICMPCom)
	COM_INTERFACE_ENTRY(ICMPCom)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCICMPCom)
	CONNECTION_POINT_ENTRY(DIID_DICMPComEvent)
END_CONNECTION_POINT_MAP()


	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;
	

// ICMPCom
public:
	// interface methods
	STDMETHOD(StopPing)();
	STDMETHOD(RunPing)();
	STDMETHOD(StopICMP)();
	STDMETHOD(StartICMP)();

	// internal methods

	void PingMsg(BSTR pbMsg);
	void PingDone();
	BOOL InitInstance(CPingParmList *lppingvars);
	BOOL Ping(CPingParmList *lppingvars);
	BOOL ProcessReply(CPingParmList *lppingvars,
							   struct icmp_reply *lpReply);
	BOOL TracertReply(CPingParmList *lppingvars,
							   struct icmp_reply *lpReply,
							   UINT ttl,
							   UINT probe,
							   ULONG Timestamp);
	BOOL Tracert(CPingParmList *lppingvars);
	void Kill(CPingParmList *lppingvars);
	BOOL Running(CPingParmList *lppingvars);
	BOOL ISActive(HANDLE hThread);
	void PrintLine(LPSTR szMsg,
					CPingParmList *lppingvars);
	HANDLE Icmp_Open();
	BOOL Icmp_Close(HANDLE h);
	BOOL Icmp_Sendto(CPingParmList *lppingvars,
							  _TCHAR *OUTBuf,
							  _TCHAR *INBuf,
							  struct ipopt_info *lpIpopt,
							  ULONG sendaddr,
							  INT maxoutbuffsize,
							  INT maxinbuffsize);
	BOOL Icmp_SetOpts(CPingParmList *lppingvars,
							   struct ipopt_info *lpIpopt,
							   UCHAR *optdata,
							   INT optsize);
	ULONG GetAddr(LPCTSTR szHost,
			      struct in_addr *inaddr = NULL);
	STDMETHOD(SetPingVariables)(BSTR hostname,
								BOOL opttrcrt,
								BOOL optresolve,
								BOOL optnofrag,
								BOOL optruntointerupt,
								INT optttl,
								INT optpacketlen,
								INT optnumpackets,
								INT optrroutenum,
								INT opttimestamp,
								INT opttos,
								INT opttimeout);
	void CleanUp(CPingParmList *lppingvars);
	
private:
	
	HANDLE m_Thread;
	static unsigned __stdcall CPingProc(LPVOID);


	
	
protected:
	CPingParmList* m_pPingParmList;
	
	
};

#endif //__CICMPCOM_H_

	//
	//
