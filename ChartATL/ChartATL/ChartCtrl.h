// ChartCtrl.h : Declaration of the CChartCtrl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "ChartATL.h"
#include <commctrl.h>
#include "ChartDlg.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

// CChartCtrl
class ATL_NO_VTABLE CChartCtrl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IChartCtrl, &IID_IChartCtrl, &LIBID_ChartATLLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CChartCtrl>,
	public IOleControlImpl<CChartCtrl>,
	public IOleObjectImpl<CChartCtrl>,
	public IOleInPlaceActiveObjectImpl<CChartCtrl>,
	public IViewObjectExImpl<CChartCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CChartCtrl>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CChartCtrl>,
	public ISpecifyPropertyPagesImpl<CChartCtrl>,
	public IQuickActivateImpl<CChartCtrl>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CChartCtrl>,
#endif
	public IProvideClassInfo2Impl<&CLSID_ChartCtrl, NULL, &LIBID_ChartATLLib>,
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
	public IObjectSafetyImpl<CChartCtrl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
#endif
	public CComCoClass<CChartCtrl, &CLSID_ChartCtrl>,
	public CComControl<CChartCtrl>
{
public:
	CContainedWindow m_ctlSysAnimate32;
	CChartDlg	m_ChartDlg;

#pragma warning(push)
#pragma warning(disable: 4355) // 'this' : used in base member initializer list

#ifdef _WIN32_WCE
#error "The common control SysAnimate32 is not supported on Windows CE!"
#endif

	CChartCtrl()
		: m_ctlSysAnimate32(_T("SysAnimate32"), this, 1)
	{

		m_bWindowOnly = TRUE;

		put_BackColor(RGB(000, 000, 000));
		put_VerticalLineColor((COLORREF) RGB(000, 125, 000));
		put_HorizontalLineColor((COLORREF) RGB(000, 125, 000));
		put_ChartColor_1(RGB(255, 255, 000));
		put_ChartColor_2(RGB(255, 000, 000));
		put_VerticalLineStyle(L_SOLID);
		put_HorizontalLineStyle(L_SOLID);
		put_ChartFillStyle_1(B_SOLID);
		put_ChartFillStyle_2(B_SOLID);


	}

#pragma warning(pop)

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_CHARTCTRL)


BEGIN_COM_MAP(CChartCtrl)
	COM_INTERFACE_ENTRY(IChartCtrl)
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
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
#endif
END_COM_MAP()

BEGIN_PROP_MAP(CChartCtrl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
	PROP_ENTRY("BackColor", 1, CLSID_NULL)
	PROP_ENTRY("VerticalLineStyle", 2, CLSID_NULL)
	PROP_ENTRY("VerticalLineColor", 4, CLSID_NULL)
	PROP_ENTRY("HorizontalLineColor", 5, CLSID_NULL)
	PROP_ENTRY("ChartColor_1", 6, CLSID_NULL)
	PROP_ENTRY("ChartColor_2", 7, CLSID_NULL)
	PROP_ENTRY("ChartFillStyle_1", 8, CLSID_NULL)
	PROP_ENTRY("ChartFillStyle_2", 9, CLSID_NULL)
	PROP_ENTRY("HorizontalLineStyle", 12, CLSID_NULL)
	PROP_ENTRY("RefreshSpeed", 13, CLSID_NULL)
END_PROP_MAP()


BEGIN_MSG_MAP(CChartCtrl)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	CHAIN_MSG_MAP(CComControl<CChartCtrl>)
ALT_MSG_MAP(1)
	// Replace this with message map entries for superclassed SysAnimate32
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	BOOL PreTranslateAccelerator(LPMSG pMsg, HRESULT& hRet)
	{
		if(pMsg->message == WM_KEYDOWN)
		{
			switch(pMsg->wParam)
			{
			case VK_LEFT:
			case VK_RIGHT:
			case VK_UP:
			case VK_DOWN:
			case VK_HOME:
			case VK_END:
			case VK_NEXT:
			case VK_PRIOR:
				hRet = S_FALSE;
				return TRUE;
			}
		}
		//TODO: Add your additional accelerator handling code here
		return FALSE;
	}

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = CComControl<CChartCtrl>::OnSetFocus(uMsg, wParam, lParam, bHandled);
		if (m_bInPlaceActive)
		{
			if(!IsChild(::GetFocus()))
				m_ctlSysAnimate32.SetFocus();
		}
		return lRes;
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
		InitCommonControls();
		m_ctlSysAnimate32.Create(m_hWnd, rc);
		m_ChartDlg.Create(m_ctlSysAnimate32.m_hWnd, rc);
		::SetWindowPos(m_ChartDlg.m_hWnd, NULL, rc.left, rc.top,
			rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
		m_ChartDlg.ShowWindow(TRUE);
		return 0;
	}

	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<CChartCtrl>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		::SetWindowPos(m_ctlSysAnimate32.m_hWnd, NULL, 0,
			0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
		return S_OK;
	}

// ISupportsErrorInfok
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] =
		{
			&IID_IChartCtrl,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IChartCtrl

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
public:
	PenStyle V_LineStyle;
	PenStyle H_LineStyle;
	BrushStyle FillStyle_1;
	BrushStyle FillStyle_2;

	VOID ChangeStyleValue(PenStyle NewStyleValue, int type);
	VOID ChangeBrushStyleValue(BrushStyle NewStyleValue, int type);

		//Chart Background properties API's
	STDMETHOD(get_BackColor)(OLE_COLOR* pVal);
	STDMETHOD(put_BackColor)(OLE_COLOR newVal);
	STDMETHOD(get_VerticalLineStyle)(PenStyle* pVal);
	STDMETHOD(put_VerticalLineStyle)(PenStyle newVal);
	STDMETHOD(get_HorizontalLineStyle)(PenStyle* pVal);
	STDMETHOD(put_HorizontalLineStyle)(PenStyle newVal);
	STDMETHOD(get_VerticalLineColor)(OLE_COLOR* pVal);
	STDMETHOD(put_VerticalLineColor)(OLE_COLOR newVal);
	STDMETHOD(get_HorizontalLineColor)(OLE_COLOR* pVal);
	STDMETHOD(put_HorizontalLineColor)(OLE_COLOR newVal);
	STDMETHOD(get_ChartColor_1)(OLE_COLOR* pVal);
	STDMETHOD(put_ChartColor_1)(OLE_COLOR newVal);
	STDMETHOD(get_ChartColor_2)(OLE_COLOR* pVal);
	STDMETHOD(put_ChartColor_2)(OLE_COLOR newVal);
	STDMETHOD(get_ChartFillStyle_1)(BrushStyle* pVal);
	STDMETHOD(put_ChartFillStyle_1)(BrushStyle newVal);
	STDMETHOD(get_ChartFillStyle_2)(BrushStyle* pVal);
	STDMETHOD(put_ChartFillStyle_2)(BrushStyle newVal);
	STDMETHOD(put_RefreshSpeed)(USHORT newVal);
	STDMETHOD(UpdateChart)(USHORT ChartValue1, USHORT ChartValue2);
	STDMETHOD(get_RefreshSpeed)(USHORT* pVal);
public:
	virtual HRESULT OnDraw(ATL_DRAWINFO& di);
};

OBJECT_ENTRY_AUTO(__uuidof(ChartCtrl), CChartCtrl)

