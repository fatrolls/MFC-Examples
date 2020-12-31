//=================================================================
//
//  class: CHistory
//  File:  History.h
//
//  Purpose:
//		Provide output to custom control and file logging 
//      for status messages.
//      
// ===================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================

#ifndef __HISTORY_H_
#define __HISTORY_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "uh_ctrl.h"
#include "UTHistoryCP.h"

class CFontNotifyImpl;

/////////////////////////////////////////////////////////////////////////////
// CHistory
class ATL_NO_VTABLE CHistory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CHistory, IHistory, &IID_IHistory, &LIBID_UTHISTORYLib>,
	public CComControl<CHistory>,
	public IPersistStreamInitImpl<CHistory>,
	public IOleControlImpl<CHistory>,
	public IOleObjectImpl<CHistory>,
	public IOleInPlaceActiveObjectImpl<CHistory>,
	public IViewObjectExImpl<CHistory>,
	public IOleInPlaceObjectWindowlessImpl<CHistory>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CHistory>,
	public IPersistStorageImpl<CHistory>,
	public IPersistPropertyBagImpl<CHistory>,
	public ISpecifyPropertyPagesImpl<CHistory>,
	public IQuickActivateImpl<CHistory>,
	public IDataObjectImpl<CHistory>,
	public IProvideClassInfo2Impl<&CLSID_History, &DIID__IHistoryEvents, &LIBID_UTHISTORYLib>,
	public IPropertyNotifySinkCP<CHistory>,
	public CComCoClass<CHistory, &CLSID_History>,
	public CProxy_IHistoryEvents< CHistory >
{

public:
	CHistory();
	~CHistory();

DECLARE_REGISTRY_RESOURCEID(IDR_HISTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHistory)
	COM_INTERFACE_ENTRY(IHistory)
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
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CHistory)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	
	PROP_ENTRY("LogName", DISPID_LOG_NAME, CLSID_HistoryPropPage)
	PROP_ENTRY("EnableLog", DISPID_ENABLE_LOG, CLSID_HistoryPropPage)
	PROP_ENTRY("TimeStampedLog", DISPID_TIME_STAMPED_LOG, CLSID_HistoryPropPage)
	PROP_ENTRY("Aligment", DISPID_ALIGNMENT, CLSID_HistoryPropPage)
	PROP_ENTRY("Margin", DISPID_MARGIN, CLSID_HistoryPropPage)
	PROP_ENTRY("TimeStampFormat", DISPID_TIME_STAMP_FORMAT, CLSID_HistoryPropPage)
	PROP_ENTRY("MaxHistoryLength", DISPID_MAX_HISTORY_LENGTH, CLSID_HistoryPropPage)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CHistory)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IHistoryEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CHistory)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	CHAIN_MSG_MAP(CComControl<CHistory>)
ALT_MSG_MAP(1)

END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	STDMETHOD(IOleObject_SetClientSite)(LPOLECLIENTSITE pSite);

// IHistory
public:
	STDMETHOD(AboutBox)();
	STDMETHOD(ClearHistory)();
	STDMETHOD(AppendToLine)(/*[in]*/ BSTR String, /*[in]*/ BOOL AddToLog);
	STDMETHOD(AddStampedLine)(/*[in]*/ BSTR String, /*[in]*/ OLE_COLOR TextColor, /*[in]*/ OLE_COLOR BackColor, /*[in]*/ BOOL AddToLog);
	STDMETHOD(AddLine)(/*[in]*/ BSTR String, /*[in]*/ OLE_COLOR TextColor, /*[in]*/ OLE_COLOR BackColor, /*[in]*/ BOOL AddToLog);
	STDMETHOD(get_MaxHistoryLength)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_MaxHistoryLength)(/*[in]*/ long newVal);
	STDMETHOD(get_TimeStampFormat)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TimeStampFormat)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Margin)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Margin)(/*[in]*/ long newVal);
	STDMETHOD(get_Alignment)(/*[out, retval]*/ AlignmentType *pVal);
	STDMETHOD(put_Alignment)(/*[in]*/ AlignmentType newVal);
	STDMETHOD(get_TimeStampedLog)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_TimeStampedLog)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_EnableLog)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_EnableLog)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_LogName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_LogName)(/*[in]*/ BSTR newVal);
    STDMETHOD(put_BackColor)(/*[in]*/OLE_COLOR newVal);
	STDMETHOD(put_ForeColor)(/*[in]*/OLE_COLOR newVal);
	STDMETHOD(putref_Font)(/*[in]*/IFontDisp* newVal);
	STDMETHOD(put_Font)(/*[in]*/IFontDisp* newVal);


	STDMETHODIMP	SetObjectRects(LPCRECT prcPos,LPCRECT prcClip);
	LRESULT			OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT			OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT			OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	BOOL			PreTranslateAccelerator(LPMSG pMsg, HRESULT& hRet);

	OLE_COLOR						m_clrBackColor;			// Back color
	OLE_COLOR						m_clrForeColor;			// Text color
	CComPtr<IFontDisp>				m_pFont;				// Text font
	CComQIPtr<IFont,&IID_IFont>		*m_pIFont;				// Text font IFont interface
	BOOL							m_bEnableLog;			// Log enabled flag

	CContainedWindow				m_ctlContainedWnd;		// Contained window
	CUH_Control						m_ctlHistory;			// History control object

};

#endif //__HISTORY_H_
