//=================================================================
//  class: CMessage
//  File:  Message.h
//
//  Implementation of CMessage class
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

#ifndef __MESSAGE_H_
#define __MESSAGE_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "UTMessage.h"
#include "MsgLicense.h"

/////////////////////////////////////////////////////////////////////////////
// CMessage
class ATL_NO_VTABLE CMessage : 
    public CUT_Msg,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CMessage, IMessage, &IID_IMessage, &LIBID_UTMSGLib>,
	public CComControl<CMessage>,
	public IPersistStreamInitImpl<CMessage>,
	public IOleControlImpl<CMessage>,
	public IOleObjectImpl<CMessage>,
	public IOleInPlaceActiveObjectImpl<CMessage>,
	public IViewObjectExImpl<CMessage>,
	public IOleInPlaceObjectWindowlessImpl<CMessage>,
	public IPersistStorageImpl<CMessage>,
	public IPersistPropertyBagImpl<CMessage>,
	public ISpecifyPropertyPagesImpl<CMessage>,
	public IDataObjectImpl<CMessage>,
	public IProvideClassInfo2Impl<&CLSID_Message, &DIID__IMessageEvents, &LIBID_UTMSGLib>,
	public IPropertyNotifySinkCP< CMessage >,
	public CComCoClass<CMessage, &CLSID_Message>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMessage>,
	public IObjectSafetyImpl<CMessage, INTERFACESAFE_FOR_UNTRUSTED_CALLER >
    
{
public:
	CMessage();
	~CMessage();

DECLARE_REGISTRY_RESOURCEID(IDR_MESSAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMessage)
	COM_INTERFACE_ENTRY(IMessage)
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

BEGIN_PROP_MAP(CMessage)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CMessage)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CMessage)
	CHAIN_MSG_MAP(CComControl<CMessage>)
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
	DECLARE_CLASSFACTORY2(CMessageLicense)

// IMessage
public:
	STDMETHOD(DecodeAttachment)(/*[in]*/ long Index, /*[in]*/ BSTR FileName, /*[out,retval]*/ long *Result);
	STDMETHOD(Save)(/*[in]*/ BSTR FileName, /*[out,retval]*/ long *Result);
	STDMETHOD(Load)(/*[in]*/ BSTR FileName, /*[out,retval]*/ long *Result);
	STDMETHOD(GetHeaderByType)(/*[in]*/ HeaderFieldType Type, /*[in]*/ long Index, /*[out,retval]*/ BSTR *Header);
	STDMETHOD(GetHeaderByName)(/*[in]*/ BSTR Name, /*[in]*/ long Index, /*[out,retval]*/ BSTR *Header);
	STDMETHOD(GetHeaderCountByType)(/*[in]*/ HeaderFieldType Type, /*[out,retval]*/ long *Number);
	STDMETHOD(GetHeaderCountByName)(/*[in]*/ BSTR Name, /*[out,retval]*/ long *Number);
	STDMETHOD(ClearHeader)(/*[in]*/ HeaderFieldType Type, BSTR CustomName);
	STDMETHOD(AddHeaderField)(/*[in]*/ BSTR Data, /*[in]*/ HeaderFieldType Type, /*[in,defaultvalue("")]*/ BSTR FieldName, /*[out,retval]*/ long *Result);
	STDMETHOD(SetMessageBody)(/*[in]*/ BSTR Text, /*[out,retval]*/ long *Result);
	STDMETHOD(GetMessageBody)(/*[out,retval]*/ BSTR *Text);
	STDMETHOD(GetFieldName)(/*[in]*/ HeaderFieldType Field, /*[out,retval]*/ BSTR *Name);
	STDMETHOD(GetCustomFieldName)(/*[in]*/ long Index, /*[out,retval]*/ BSTR *Name);
	STDMETHOD(SetDefaultEncoding)(/*[in]*/ EncodingType Type, /*[out, retval]*/ long *Result);
	STDMETHOD(AddAttachmentHeaderTag)(/*[in]*/ BSTR Tag, /*[out,retval]*/ long *Result);
	STDMETHOD(GetAttachmentParam)(/*[in]*/ long Index, /*[out,retval]*/ BSTR *Param);
	STDMETHOD(GetAttachmentType)(/*[in]*/ long Index, /*[out,retval]*/ BSTR *Type);
	STDMETHOD(GetAttachmentName)(/*[in]*/ long Index, /*[out,retval]*/ BSTR *Name);
	STDMETHOD(GetAttachmentSize)(/*[in, defaultvalue(-1)]*/ long Index, /*[out,retval]*/ long *Size);
	STDMETHOD(EmptyAttachmentList)();
	STDMETHOD(GetAttachmentNumber)(/*[out, retval]*/ long *Number);
	STDMETHOD(AddAttachment)(/*[in]*/ BSTR FileName, /*[in, defaultvalue("")]*/ BSTR Params, /*[out,retval]*/ long *Result);
	STDMETHOD(AboutBox)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);

	HRESULT OnDraw(ATL_DRAWINFO& di);

// IMessage Private data members
private:
	HICON				m_hMessageIcon;			// Message icon handle
};

#endif //__MESSAGE_H_
