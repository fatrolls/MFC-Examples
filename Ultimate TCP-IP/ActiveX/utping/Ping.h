// =================================================================
//  class: CPing
//  File:  Ping.h
//  
//  Purpose:
//
//	Ping ActiveX Control
//
// =================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// =================================================================

#ifndef __PING_H_
#define __PING_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "UT_ICMP.h"
#include "MarshalEvents.h"
#include "UTPingCP.h"
#include "PingLicense.h"

#include <vector>
using namespace std ;

class CICMP_Data 
{
public:
    CICMP_Data(LPCSTR Message, LPCSTR Address, LPCSTR Name, const long Duration, const long Type, const long Code, const long Sequence) :
        m_strMessage(Message),
        m_strAddress(Address),
        m_strName(Name),
        m_lDuration(Duration),
        m_lType(Type),
        m_lCode(Code),
        m_lSequence(Sequence)   {  }

    string  m_strMessage;
    string  m_strAddress;
    string  m_strName;
    long    m_lDuration;
    long    m_lType;
    long    m_lCode;
    long    m_lSequence;
};

typedef vector<CICMP_Data> ICMP_DATA_VECTOR;

/////////////////////////////////////////////////////////////////////////////
// CPing
class ATL_NO_VTABLE CPing : 
	public CUT_ICMP,

	public CMarshalEvents<CPing, &DIID__IPingEvents, TRUE>,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CPing, IPing, &IID_IPing, &LIBID_UTPINGLib>,
	public CComControl<CPing>,
	public IPersistStreamInitImpl<CPing>,
	public IOleControlImpl<CPing>,
	public IOleObjectImpl<CPing>,
	public IOleInPlaceActiveObjectImpl<CPing>,
	public IViewObjectExImpl<CPing>,
	public IOleInPlaceObjectWindowlessImpl<CPing>,
	public IPersistStorageImpl<CPing>,
	public IPersistPropertyBagImpl<CPing>,
	public ISpecifyPropertyPagesImpl<CPing>,
	public IDataObjectImpl<CPing>,
	public IProvideClassInfo2Impl<&CLSID_Ping, &DIID__IPingEvents, &LIBID_UTPINGLib>,
	public CProxy_IPingEvents< CPing >,
	public IPropertyNotifySinkCP< CPing >,
	public CComCoClass<CPing, &CLSID_Ping>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPing>,
	public IObjectSafetyImpl<CPing, INTERFACESAFE_FOR_UNTRUSTED_CALLER >
	
{

friend	CProxy_IPingEvents< CPing >;

public:
	CPing();
	~CPing();

DECLARE_REGISTRY_RESOURCEID(IDR_PING)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPing)
	COM_INTERFACE_ENTRY(IPing)
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
	COM_INTERFACE_ENTRY(IObjectSafety)END_COM_MAP()

BEGIN_PROP_MAP(CPing)
	PROP_ENTRY("BlockingMode", DISPID_BLOCKING_MODE, CLSID_PingProp )
    PROP_ENTRY("DoLookup", DISPID_DO_LOOKUP, CLSID_PingProp )
    PROP_ENTRY("MaxTimeOuts", DISPID_MAX_TIME_OUTS, CLSID_PingProp )
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CPing)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IPingEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CPing)
	CHAIN_MSG_MAP(CComControl<CPing>)
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
	DECLARE_CLASSFACTORY2(CPingLicense)

// IPing
public:
	STDMETHOD(GetResponseSequence)(/*[in]*/ long Index, /*[out,retval]*/ long *Sequence);
	STDMETHOD(GetResponseCode)(/*[in]*/ long Index, /*[out,retval]*/ long *Code) ;
	STDMETHOD(GetResponseType)(/*[in]*/ long Index, /*[out,retval]*/ long *Type);
	STDMETHOD(GetResponseDuration)(/*[in]*/ long Index, /*[out,retval]*/ long *Duration);
	STDMETHOD(GetResponseName)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *Name);
	STDMETHOD(GetResponseAddress)(/*[in]*/ long Index, /*[out, retval]*/ BSTR * Address);
	STDMETHOD(GetResponseMessage)(/*[in]*/ long Index, /*[out,retval]*/ BSTR *Message);
	STDMETHOD(GetResponseSize)(/*[out,retval]*/ long *Size);
	STDMETHOD(get_MaxTimeOuts)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_MaxTimeOuts)(/*[in]*/ long newVal);
	STDMETHOD(get_DoLookup)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DoLookup)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_BlockingMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BlockingMode)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(TraceRoute)(/*[in]*/ BSTR Address,  /*[in, defaultvalue(2000)]*/ int TimeOut,  /*[in, defaultvalue(30)]*/ int MaxHops, /*[in, defaultvalue(32)]*/ int DataSize, /*[out, retval]*/ int *Result);
	STDMETHOD(Ping)(/*[in]*/ BSTR Address, /*[in, defaultvalue(5)]*/ int Count, /*[in, defaultvalue(2000)]*/ int TimeOut, /*[in, defaultvalue(500)]*/ int Interval, /*[in, defaultvalue(32)]*/ int DataSize, /*[out, retval]*/ int *Result);
	STDMETHOD(AboutBox)();
	STDMETHOD(CancelPing)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);


	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);
	
	HRESULT OnDraw(ATL_DRAWINFO& di);

// IPing Private data members
private:
	BOOL				m_bBlockingMode;		// TRUE if we are working in blocking mode
    HICON				m_hPingIcon;			// Ping icon handle

	BOOL				m_bAbortFlag;			// TRUE if we are going to abort Ping
	BOOL				m_bTraceRoute;			// TRUE if we are making trace out

	_bstr_t				m_bstrAddress;			// Adress to Ping
	int					m_nPingCount;			// Ping count
	LONG				m_lnTimeOut;			// TimeOut in milli seconds
	LONG				m_lnInterval;			// Interval
	int					m_nDataSize;			// Size of data to send
	int					m_nMaxHops;				// Max hops number

	UTIcmpHeader		m_CurIcmpHeader;		// Current ICMP Header
	_bstr_t				m_bstrCurFromAddress;	// Current from address

	BOOL				m_bPingThreadRunning;	// TRUE if thread running
	BOOL				m_bGoingToClose;		// TRUE if the control is going to be destroyed
	HANDLE				m_hPingThread;

    ICMP_DATA_VECTOR    m_DataVector;           // ICMP data vector

	// Ping thread function
	static void __stdcall		PingThread( LPVOID pThis );

	// Waits for the object to be signaled
	BOOL			WaitWithMsgLoop(HANDLE hEvent, long lTimeout);

	// Return TRUE if we are going to abort operation
	virtual BOOL	IsAborted();		

	virtual void	OnReceiveICMP();

	};

#endif //__PING_H_
