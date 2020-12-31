//=================================================================
//  class: CDNS
//  File:  DNS.h
//
//  Implementation of CDNS class
//
//=================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
//=================================================================

#ifndef __DNS_H_
#define __DNS_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "ut_clnt.h"	
#include "dns_c.h"	
#include "MarshalEvents.h"
#include "DNSLicense.h"
#include "UTDnsCP.h"
 

/////////////////////////////////////////////////////////////////////////////
// CDNS
class ATL_NO_VTABLE CDNS : 
	public CUT_DNSClient,

	public CMarshalEvents<CDNS, &DIID__IDNSEvents, TRUE>,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CDNS, IDNS, &IID_IDNS, &LIBID_UTDNSLib>,
	public CComControl<CDNS>,
	public IPersistStreamInitImpl<CDNS>,
	public IOleControlImpl<CDNS>,
	public IOleObjectImpl<CDNS>,
	public IOleInPlaceActiveObjectImpl<CDNS>,
	public IViewObjectExImpl<CDNS>,
	public IOleInPlaceObjectWindowlessImpl<CDNS>,
	public IPersistStorageImpl<CDNS>,
	public IPersistPropertyBagImpl<CDNS>,
	public ISpecifyPropertyPagesImpl<CDNS>,
	public IDataObjectImpl<CDNS>,
	public IProvideClassInfo2Impl<&CLSID_DNS, &DIID__IDNSEvents, &LIBID_UTDNSLib>,
	public CProxy_IDNSEvents< CDNS >,
	public IPropertyNotifySinkCP< CDNS >,
	public CComCoClass<CDNS, &CLSID_DNS>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDNS>,
	public IObjectSafetyImpl<CDNS, INTERFACESAFE_FOR_UNTRUSTED_CALLER >

{

friend	CProxy_IDNSEvents< CDNS >;

public:
	CDNS();
	~CDNS();

DECLARE_REGISTRY_RESOURCEID(IDR_DNS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDNS)
	COM_INTERFACE_ENTRY(IDNS)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IPersistPropertyBag)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IObjectSafety) 

END_COM_MAP()

BEGIN_PROP_MAP(CDNS)
	PROP_ENTRY("LookupTimeOut", DISPID_LOOKUP_TIME_OUT, CLSID_DNSPropPage )
	PROP_ENTRY("IncludeDefMX", DISPID_INCLUDE_DEF_MX, CLSID_DNSPropPage )
	PROP_ENTRY("BlockingMode", DISPID_BLOCKING_MODE, CLSID_DNSPropPage )
	PROP_ENTRY("Protocol", DISPID_PROTOCOL, CLSID_DNSPropPage )

	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CDNS)
	CONNECTION_POINT_ENTRY(DIID__IDNSEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CDNS)
	CHAIN_MSG_MAP(CComControl<CDNS>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IClassFactory2
	DECLARE_CLASSFACTORY2(CDNSLicense)

// IDNS
public:
	STDMETHOD(get_Protocol)(/*[out, retval]*/ ProtocolTypes *pVal);
	STDMETHOD(put_Protocol)(/*[in]*/ ProtocolTypes newVal);
	STDMETHOD(get_EntryMX_Preference)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_EntryData2)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_EntryData)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_EntrySOA_Minimum)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_EntrySOA_Expire)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_EntrySOA_Retry)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_EntrySOA_Refresh)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_EntrySOA_Serial)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_EntryTimeToLive)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_EntryType)(/*[out, retval]*/ DNSEntryTypes *pVal);
	STDMETHOD(get_EntryHostName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(GetEntryLongName)(/*[in]*/ DNSEntryTypes EntryType, /*[out, retval]*/ BSTR *Name);
	STDMETHOD(GetEntryShortName)(/*[in]*/ DNSEntryTypes EntryType, /*[out, retval]*/ BSTR *Name);
	STDMETHOD(get_IsAuthoritative)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_IncludeDefaultMX)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IncludeDefaultMX)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_BlockingMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BlockingMode)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_LookupTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_LookupTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(AuthoritativeLookup)(/*[in]*/ BSTR Server, /*[in]*/ BSTR Domain, /*[in]*/ DNSRequestTypes Type, /*[out, retval]*/ int *Result);
	STDMETHOD(Lookup)(/*[in]*/ BSTR Server, /*[in]*/ BSTR Domain, /*[in]*/ DNSRequestTypes Type, /*[out, retval]*/ int *Result);
	STDMETHOD(EnumDNSEntry)(/*[out, retval]*/ int *Result);
	STDMETHOD(EnumMXRecords)(/*[out]*/ BSTR *Name, /*[out]*/ BSTR *Address, /*[out, retval]*/ int *Result);
	STDMETHOD(EnumDNSServers)(/*[out]*/ BSTR *Name, /*[out]*/ BSTR *Address, /*[out, retval]*/ int *Result);
	STDMETHOD(ResetEnumeration)();
	STDMETHOD(GetAddressFromName)(/*[in]*/ BSTR Name, /*[out]*/ BSTR *Address, /*[out, retval]*/ int *Result);
	STDMETHOD(GetNameFromAddress)(/*[in]*/ BSTR Address, /*[out]*/ BSTR *Name, /*[out, retval]*/ int *Result);
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);
	STDMETHOD(AboutBox)();
	STDMETHOD(CancelLookup)();
	HRESULT OnDraw(ATL_DRAWINFO& di);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);


private:
	HICON			m_hDNSIcon;					// DNS icon handle

	CUT_DNSEntry	    m_CurDNSEntry;				// Current DNS entry
	BOOL			m_bDNSEntryValid;			// TRUE if Current DNS entry is valid
	BOOL			m_bDoAuthoritativeLookup;	// TRUE if we are makig Authoritative Lookup

	_bstr_t			m_bstrServer;				// Server name to send the request to
	_bstr_t			m_bstrDomain;				// Domain name to lookup
	int				m_nType;					// Request type

	LONG			m_lnLookupTimeOut;			// Lookup TimeOut in seconds
	BOOL			m_bAbortFlag;				// TRUE if we are going to abort finger
	BOOL			m_bBlockingMode;			// TRUE if we are working in blocking mode

	BOOL			m_bDNSThreadRunning;		// TRUE if thread running
	BOOL			m_bGoingToClose;			// TRUE if the control is going to be destroyed
	HANDLE			m_hDNSThread;

	static void __stdcall		DNSThread( LPVOID pThis );

	// Waits for the object to be signaled
	BOOL			WaitWithMsgLoop(HANDLE hEvent, long lTimeout);

	// Return TRUE if we are going to abort operation
	virtual BOOL	IsAborted();		

	
	};

#endif //__DNS_H_
