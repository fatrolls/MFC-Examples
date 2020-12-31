//=================================================================
//  class: CFingerServ
//  File:  FingerServ.h
//
//  Implementation of CFingerServ class
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

#ifndef __FINGERSERV_H_
#define __FINGERSERV_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "UTFingerServCP.h"
#include "FingerServLicense.h"
#include "MarshalEvents.h"
#include "finger_s.h"

class CUT_FingerThreadEx;

/////////////////////////////////////////////////////////////////////////////
// CFingerServ
/////////////////////////////////////////////////////////////////////////////

class ATL_NO_VTABLE CFingerServ : 

	public CUT_FingerServer,

	public CMarshalEvents<CFingerServ, &DIID__IFingerServEvents, TRUE>,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CFingerServ, IFingerServ, &IID_IFingerServ, &LIBID_UTFINGERSERVLib>,
	public CComControl<CFingerServ>,
	public IPersistStreamInitImpl<CFingerServ>,
	public IOleControlImpl<CFingerServ>,
	public IOleObjectImpl<CFingerServ>,
	public IOleInPlaceActiveObjectImpl<CFingerServ>,
	public IViewObjectExImpl<CFingerServ>,
	public IOleInPlaceObjectWindowlessImpl<CFingerServ>,
	public IPersistStorageImpl<CFingerServ>,
	public IPersistPropertyBagImpl<CFingerServ>,
	public ISpecifyPropertyPagesImpl<CFingerServ>,
	public IDataObjectImpl<CFingerServ>,
	public IProvideClassInfo2Impl<&CLSID_FingerServ, &DIID__IFingerServEvents, &LIBID_UTFINGERSERVLib>,
	public CProxy_IFingerServEvents< CFingerServ >,
	public IPropertyNotifySinkCP< CFingerServ >,
	public CComCoClass<CFingerServ, &CLSID_FingerServ>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CFingerServ>,
	public IObjectSafetyImpl<CFingerServ, INTERFACESAFE_FOR_UNTRUSTED_CALLER >
{

friend CProxy_IFingerServEvents< CFingerServ >;
friend CUT_FingerThreadEx;
public:
	CFingerServ();
	~CFingerServ();

DECLARE_REGISTRY_RESOURCEID(IDR_FINGERSERV)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFingerServ)
	COM_INTERFACE_ENTRY(IFingerServ)
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

BEGIN_PROP_MAP(CFingerServ)
	PROP_ENTRY("Path", DISPID_PATH, CLSID_FingerServProp )
	PROP_ENTRY("MaxConnections", DISPID_MAX_CONNECTIONS, CLSID_FingerServProp )
	PROP_ENTRY("Port", DISPID_PORT, CLSID_FingerServProp )

	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CFingerServ)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IFingerServEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CFingerServ)
	CHAIN_MSG_MAP(CComControl<CFingerServ>)
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
	DECLARE_CLASSFACTORY2(CFingerServLicense)

// IFingerServ
public:
	STDMETHOD(Stop)();
	STDMETHOD(get_Port)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Port)(/*[in]*/ long newVal);
	STDMETHOD(get_MaxConnections)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_MaxConnections)(/*[in]*/ long newVal);
	STDMETHOD(get_Connections)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Path)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Path)(/*[in]*/ BSTR newVal);
	STDMETHOD(Start)(/*[out, retval]*/ long *Result);
	STDMETHOD(AboutBox)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);


	HRESULT OnDraw(ATL_DRAWINFO& di);
	

// IFinger protected data members
protected:
	HICON				m_hFingerServIcon;			// Finger server icon handle
	long				m_lFingerServerPort;		// Finger server listening port number
	BOOL				m_bGoingToClose;			// TRUE if we are going to destroy the control

	CComCriticalSection	m_EventLock;				// Event critical section object

	// Returns a pointer to an instance
	// of a class derived from CUT_WSThread
    CUT_WSThread	*CreateInstance();

	// This virtual function is called each time we have any
	// status information to display.
	virtual int		OnStatus(LPCSTR StatusText);

    // This virtual function is called each time the server 
    // accepting new connection.
    virtual long    OnCanAccept(LPCSTR address);
};

//=================================================================
//  class: CUT_FingerThread
//=================================================================

class CUT_FingerThreadEx : public CUT_FingerThread {

friend CFingerServ;

protected:

    // Over ride this to handle the max connection reached
    virtual void	OnMaxConnect();    
    
    // Over ride this to handle each client connection separatly
	virtual void	OnConnect();       

};


#endif //__FINGERSERV_H_
