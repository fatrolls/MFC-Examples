//=================================================================
//  class: CFinger
//  File:  Finger.h
//
//  Implementation of CFinger class
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

#ifndef __FINGER_H_
#define __FINGER_H_

#include "UTFingerCP.h"
#include "resource.h"       // main symbols
#include <atlctl.h>

#include "ut_clnt.h"	
#include "finger_c.h"	
#include "MarshalEvents.h"


/////////////////////////////////////////////////////////////////////////////
// CFinger
class ATL_NO_VTABLE CFinger : 
	public CUT_FingerClient,

	public CMarshalEvents<CFinger, &DIID__IFingerEvents, FALSE>,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CFinger, IFinger, &IID_IFinger, &LIBID_UTFINGERLib>,
	public CComControl<CFinger>,
	public IPersistStreamInitImpl<CFinger>,
	public IOleControlImpl<CFinger>,
	public IOleObjectImpl<CFinger>,
	public IOleInPlaceActiveObjectImpl<CFinger>,
	public IViewObjectExImpl<CFinger>,
	public IOleInPlaceObjectWindowlessImpl<CFinger>,
	public IPersistStorageImpl<CFinger>,
	public IPersistPropertyBagImpl<CFinger>,
	public ISpecifyPropertyPagesImpl<CFinger>,
	public IDataObjectImpl<CFinger>,
	public IProvideClassInfo2Impl<&CLSID_Finger, &DIID__IFingerEvents, &LIBID_UTFINGERLib>,
	public CProxy_IFingerEvents< CFinger >,
	public IPropertyNotifySinkCP< CFinger >,
	public CComCoClass<CFinger, &CLSID_Finger>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CFinger>,
	public IObjectSafetyImpl<CFinger, INTERFACESAFE_FOR_UNTRUSTED_CALLER >

{

friend	CProxy_IFingerEvents< CFinger >;

public:
	CFinger();
	~CFinger();

DECLARE_REGISTRY_RESOURCEID(IDR_FINGER)

DECLARE_PROTECT_FINAL_CONSTRUCT()


BEGIN_COM_MAP(CFinger)
	COM_INTERFACE_ENTRY(IFinger)
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


BEGIN_PROP_MAP(CFinger)
	PROP_ENTRY("ConnectTimeOut", DISPID_CONNECT_TIME_OUT, CLSID_FingerProp )
	PROP_ENTRY("ReceiveTimeOut", DISPID_RECEIVE_TIME_OUT, CLSID_FingerProp )
	PROP_ENTRY("BlockingMode", DISPID_BLOCKING_MODE, CLSID_FingerProp )

	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CFinger)
	CONNECTION_POINT_ENTRY(DIID__IFingerEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CFinger)
	CHAIN_MSG_MAP(CComControl<CFinger>)
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
	DECLARE_CLASSFACTORY2(CFingerLicense)

// IFinger
public:
	STDMETHOD(AboutBox)();
	STDMETHOD(CancelFinger)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);
	STDMETHOD(get_NumberReturnLines)(/*[out, retval]*/ long *pVal);
	STDMETHOD(GetReturnLine)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *Line);
	STDMETHOD(Finger)(/*[in]*/ BSTR Address, /*[in, defaultvalue("")]*/ BSTR FileName, /*[out, retval]*/ long *Result);
	STDMETHOD(get_ReceiveTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ReceiveTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_ConnectTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ConnectTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_BlockingMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BlockingMode)(/*[in]*/ VARIANT_BOOL newVal);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);


	HRESULT OnDraw(ATL_DRAWINFO& di);


// IFinger Private data members
private:
	HICON				m_hFingerIcon;			// Finger icon handle

	LONG				m_lnConnectTimeOut;		// Connection TimeOut in seconds
	LONG				m_lnReceiveTimeOut;		// Receive TimeOut in seconds
	LONG				m_lnNumberOfLines;		// Number of lines returned
	BOOL				m_bAbortFlag;			// TRUE if we are going to abort finger
	BOOL				m_bBlockingMode;		// TRUE if we are working in blocking mode

	_bstr_t				m_bstrAddress;			// Adress to finger
	_bstr_t				m_bstrFileName;			// Optional file name to put the data in
	BOOL				m_bFingerThreadRunning;	// TRUE if thread running
	BOOL				m_bGoingToClose;		// TRUE if the control is going to be destroyed
	HANDLE				m_hFingerThread;

	static void __stdcall		FingerThread( LPVOID pThis );

	// Waits for the object to be signaled
	BOOL			WaitWithMsgLoop(HANDLE hEvent, long lTimeout);

	// Return TRUE if we are going to abort operation
	virtual BOOL	IsAborted();		

};

#endif //__FINGER_H_
