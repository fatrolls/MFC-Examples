// VirtualList.h : Declaration of the CVirtualList
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
// Copyright (c) 2000.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//

#ifndef __VIRTUALLIST_H_
#define __VIRTUALLIST_H_

#include "resource.h"       // main symbols
#include "VirtualControlsCP.h"


/////////////////////////////////////////////////////////////////////////////
// CVirtualList

#define SB_CHAPTERUP 500
#define SB_CHAPTERDOWN 501

class ATL_NO_VTABLE CVirtualList : 
   public CComObjectRootEx<CComSingleThreadModel>,
   public CStockPropImpl<CVirtualList, IVirtualList, &IID_IVirtualList, &LIBID_VIRTUALCONTROLSLib>,
   public CComCompositeControl<CVirtualList>,
   public IPersistStreamInitImpl<CVirtualList>,
   public IOleControlImpl<CVirtualList>,
   public IOleObjectImpl<CVirtualList>,
   public IOleInPlaceActiveObjectImpl<CVirtualList>,
   public IViewObjectExImpl<CVirtualList>,
   public IOleInPlaceObjectWindowlessImpl<CVirtualList>,
   public ISupportErrorInfoImpl<&IID_IVirtualList>,
   public IConnectionPointContainerImpl<CVirtualList>,
   public IPersistStorageImpl<CVirtualList>,
   public ISpecifyPropertyPagesImpl<CVirtualList>,
   public IQuickActivateImpl<CVirtualList>,
   public IDataObjectImpl<CVirtualList>,
   public IProvideClassInfo2Impl<&CLSID_VirtualList, &DIID__IVirtualListEvents, &LIBID_VIRTUALCONTROLSLib>,
   public IPropertyNotifySinkCP<CVirtualList>,
   public CComCoClass<CVirtualList, &CLSID_VirtualList>,
   public CProxy_IVirtualListEvents< CVirtualList >
{
public:
   CVirtualList()
   {
      m_bWindowOnly = TRUE;
      CalcExtent(m_sizeExtent);
      // Default values
      m_dwListIndex = 0;
      m_dwPageStep = 0;
      m_dwCount = 0;
      m_bGridLines = FALSE;
      m_bTrackSelect = FALSE;
      //
      m_cxScroll = ::GetSystemMetrics(SM_CXHSCROLL);
      m_cyScroll = ::GetSystemMetrics(SM_CYHSCROLL);
   }

DECLARE_REGISTRY_RESOURCEID(IDR_VIRTUALLIST)
DECLARE_NOT_AGGREGATABLE(CVirtualList)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVirtualList)
   COM_INTERFACE_ENTRY(IVirtualList)
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
   COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
   COM_INTERFACE_ENTRY(IQuickActivate)
   COM_INTERFACE_ENTRY(IPersistStorage)
   COM_INTERFACE_ENTRY(IDataObject)
   COM_INTERFACE_ENTRY(IProvideClassInfo)
   COM_INTERFACE_ENTRY(IProvideClassInfo2)
   COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CVirtualList)
   PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
   PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
   PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
   PROP_ENTRY("BorderStyle", DISPID_BORDERSTYLE, CLSID_NULL)
   PROP_ENTRY("Caption", DISPID_CAPTION, CLSID_NULL)
   PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
   PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
   PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)
   PROP_ENTRY("TabStop", DISPID_TABSTOP, CLSID_NULL)
   PROP_DATA_ENTRY("ListCount", m_dwCount, VT_UI4)
   PROP_DATA_ENTRY("PageStep", m_dwPageStep, VT_UI4)
   PROP_DATA_ENTRY("GridLines", m_bGridLines, VT_BOOL)
   PROP_DATA_ENTRY("TrackSelect", m_bTrackSelect, VT_BOOL)
   PROP_PAGE(CLSID_StockFontPage)
   PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CVirtualList)
   CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
   CONNECTION_POINT_ENTRY(DIID__IVirtualListEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CVirtualList)
   CHAIN_MSG_MAP(CComCompositeControl<CVirtualList>)
   MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
   MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
   MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)
   MESSAGE_HANDLER(WM_SIZE, OnSize)
   MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
   NOTIFY_HANDLER(IDC_LIST, LVN_GETDISPINFO, OnListGetDispInfo)
   NOTIFY_HANDLER(IDC_LIST, LVN_ITEMCHANGED, OnListChanged)   
   NOTIFY_HANDLER(IDC_LIST, NM_CLICK, OnListClick)   
   NOTIFY_HANDLER(IDC_LIST, NM_DBLCLK, OnListDblClick)   
   MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
   COMMAND_HANDLER(IDC_DOWN, BN_CLICKED, OnClickedDown)
   COMMAND_HANDLER(IDC_UP, BN_CLICKED, OnClickedUp)
END_MSG_MAP()

BEGIN_SINK_MAP(CVirtualList)
   //Make sure the Event Handlers have __stdcall calling convention
END_SINK_MAP()

// IOleControl
public:
   STDMETHOD(OnAmbientPropertyChange)(DISPID dispid);

// CComControlBase
public:
   BOOL PreTranslateAccelerator(LPMSG /*pMsg*/, HRESULT& /*hRet*/);

// IViewObjectEx
public:
   DECLARE_VIEW_STATUS(0)

// IVirtualList
public:
   STDMETHOD(get_ListCount)(/*[out, retval]*/ long *pVal);
   STDMETHOD(put_ListCount)(/*[in]*/ long newVal);
   STDMETHOD(Clear)();
   STDMETHOD(get_PageStep)(/*[out, retval]*/ long *pVal);
   STDMETHOD(put_PageStep)(/*[in]*/ long newVal);
   STDMETHOD(get_ListIndex)(/*[out, retval]*/ long *pVal);
   STDMETHOD(put_ListIndex)(/*[in]*/ long newVal);
   STDMETHOD(get_TopIndex)(/*[out, retval]*/ long *pVal);
   STDMETHOD(put_TopIndex)(/*[in]*/ long newVal);
   STDMETHOD(get_GridLines)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_GridLines)(/*[in]*/ VARIANT_BOOL newVal);
   STDMETHOD(get_TrackSelect)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_TrackSelect)(/*[in]*/ VARIANT_BOOL newVal);

// Implementation
protected:
   BOOL DefineScrollRange();
   BOOL EnsureVisible(long iIndex);

// Attributes
public:
   OLE_COLOR   m_clrBackColor;
   LONG        m_nBorderStyle;
   CComBSTR    m_bstrCaption;
   BOOL        m_bEnabled;
   CComPtr<IFontDisp> m_pFont;
   OLE_COLOR   m_clrForeColor;
   BOOL        m_bTabStop;
   DWORD       m_dwCount;
   DWORD       m_dwPageStep;
   DWORD       m_dwListIndex;
   BOOL        m_bGridLines;
   BOOL        m_bTrackSelect;
   //
   CListViewCtrl m_ctlList;
   CScrollBar  m_ctlScrollbar;
   CButton     m_ctlUp;
   CButton     m_ctlDown;
   CBitmap     m_bmpUp;
   CBitmap     m_bmpDown;
   //
   int         m_cxScroll;
   int         m_cyScroll;

   enum { IDD = IDD_VIRTUALLIST };

// Windows message handlers
public:
   LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnClickedDown(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
   LRESULT OnClickedUp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
   //
   LRESULT OnListGetDispInfo(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
   LRESULT OnListChanged(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
   LRESULT OnListClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
   LRESULT OnListDblClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
};

#endif //__VIRTUALLIST_H_
