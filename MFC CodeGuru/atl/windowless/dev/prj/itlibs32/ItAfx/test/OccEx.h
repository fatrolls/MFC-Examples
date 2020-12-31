#ifndef __OccEx_h__
#define __OccEx_h__

#ifndef DISPID_DATASOURCE
#pragma pack(push, _AFX_PACKING)
#include "../src/occimpl.h"
#pragma pack(pop)
#endif

class COleControlContainerEx;
class COleControlSiteEx;
class COccManagerEx;
class CWindowlessControl;


/////////////////////////////////////////////////////////////////////////////
// Windowless control container support

// container class supporting windowless activation
class COleControlContainerEx : public COleControlContainer
{
	DECLARE_DYNCREATE(COleControlContainerEx);
	friend class COccManagerEx;
protected:
	COleControlContainerEx();
	virtual void Init();
	virtual ~COleControlContainerEx();

// Windowless activation
public:
	bool m_bSupportWindowlessActivation;
	COleControlSiteEx* m_pCapture;	// windowless control which has captured the mouse
	COleControlSiteEx* m_pFocus;	// windowless control wich has the focus

// Ambient properties
public:
	virtual void AmbientPropertyChanged(DISPID dispid);

public:
	// do not use COleControlContainer::CreateControl or CWnd::CreateControl !!
	// (it's one of these MFC design flaws that none of the CreateControl functions 
	// is virtual!)
	// Use either this CreateControl function or CWindowlessControl::CreateControl.
	virtual BOOL CreateControl(CWnd* pWnd, REFCLSID clsid,
		LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, UINT nID,
		CFile* pPersist=NULL, BOOL bStorage=FALSE, BSTR bstrLicKey=NULL,
		COleControlSite** ppNewSite=NULL);

	// call this function from your container windows drawing code
	// i.e. OnDraw (CView derived classes) or OnPaint (CWnd derived classes)
	virtual void OnDraw(CDC* pDC);

// Implementation
protected:
	// we automatically subclasses the container window
	WNDPROC m_pfnContWndProc;
	static LRESULT CALLBACK ContWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	virtual bool OnWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	virtual COleControlSiteEx* WindowlessSiteFromPoint(CPoint pt);

	// strange hack due to a bug in MFC 4.21 import lib (see CPP file)
	const AFX_INTERFACEMAP* GetBaseInterfaceMap()
	{ return COleControlContainer::GetInterfaceMap(); }

	BEGIN_INTERFACE_PART(OleInPlaceFrame, IOleInPlaceFrame)
		INIT_INTERFACE_PART(COleControlContainer, OleIPFrame)
		STDMETHOD(GetWindow)(HWND*);
		STDMETHOD(ContextSensitiveHelp)(BOOL);
		STDMETHOD(GetBorder)(LPRECT);
		STDMETHOD(RequestBorderSpace)(LPCBORDERWIDTHS);
		STDMETHOD(SetBorderSpace)(LPCBORDERWIDTHS);
		STDMETHOD(SetActiveObject)(LPOLEINPLACEACTIVEOBJECT, LPCOLESTR);
		STDMETHOD(InsertMenus)(HMENU, LPOLEMENUGROUPWIDTHS);
		STDMETHOD(SetMenu)(HMENU, HOLEMENU, HWND);
		STDMETHOD(RemoveMenus)(HMENU);
		STDMETHOD(SetStatusText)(LPCOLESTR);
		STDMETHOD(EnableModeless)(BOOL);
		STDMETHOD(TranslateAccelerator)(LPMSG, WORD);
	END_INTERFACE_PART(OleInPlaceFrame)

	DECLARE_INTERFACE_MAP()
};

// site class supporting windowless activation
class COleControlSiteEx : public COleControlSite
{
	DECLARE_DYNCREATE(COleControlSiteEx);
	friend class COccManagerEx;
protected:
	COleControlSiteEx();
	virtual void Init();
	virtual ~COleControlSiteEx();

public:
	virtual bool OnWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	virtual void AmbientPropertyChanged(DISPID dispid);

	virtual DWORD GetStyle() const;
	virtual DWORD GetExStyle() const;
	virtual BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags);
	virtual BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags);
	virtual BOOL SetWindowPos(const CWnd* pWndInsertAfter, int x, int y,
		int cx, int cy, UINT nFlags);
	virtual BOOL ShowWindow(int nCmdShow);
	virtual CWnd* SetFocus();

	// see comment for COleControlContainerEx::CreateControl
	virtual HRESULT CreateControl(CWnd* pWndCtrl, REFCLSID clsid,
		LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, UINT nID,
		CFile* pPersist=NULL, BOOL bStorage=FALSE, BSTR bstrLicKey=NULL);
	// these are overridden only to avoid asserts
#ifdef _DEBUG
	virtual void SetWindowText(LPCTSTR lpszString);
	virtual void GetWindowText(CString& str) const;
#endif

	bool IsWindowlessActive() const
	{
		return (m_dwActivateFlags & ACTIVATE_WINDOWLESS) != 0;
	}

	DWORD m_dwActivateFlags;
	IOleInPlaceObjectWindowless* m_pIPOW;

	virtual void Draw(CDC* pDC);

// Implementation
protected:
	// strange hack due to a bug in MFC 4.21 import lib (see CPP file)
	const AFX_INTERFACEMAP* GetBaseInterfaceMap()
	{ return COleControlSite::GetInterfaceMap(); }

	BEGIN_INTERFACE_PART(OleInPlaceSiteWindowless, IOleInPlaceSiteWindowless)
	// IOleWindow
		INIT_INTERFACE_PART(CGOleCtrlSite, OleInPlaceSiteWindowless)
		STDMETHOD(GetWindow)(HWND*);
		STDMETHOD(ContextSensitiveHelp)(BOOL);
	// IOleInPlaceSite
		STDMETHOD(CanInPlaceActivate)();
		STDMETHOD(OnInPlaceActivate)();
		STDMETHOD(OnUIActivate)();
		STDMETHOD(GetWindowContext)(LPOLEINPLACEFRAME*,
			LPOLEINPLACEUIWINDOW*, LPRECT, LPRECT, LPOLEINPLACEFRAMEINFO);
		STDMETHOD(Scroll)(SIZE);
		STDMETHOD(OnUIDeactivate)(BOOL);
		STDMETHOD(OnInPlaceDeactivate)();
		STDMETHOD(DiscardUndoState)();
		STDMETHOD(DeactivateAndUndo)();
		STDMETHOD(OnPosRectChange)(LPCRECT);
	// IOleInPlaceSiteEx
        STDMETHOD(OnInPlaceActivateEx)(BOOL* pfNoRedraw, DWORD dwFlags);
        STDMETHOD(OnInPlaceDeactivateEx)(BOOL fNoRedraw);        
        STDMETHOD(RequestUIActivate)();
	// IOleInPlaceSiteWindowless
        STDMETHOD(CanWindowlessActivate)();
        STDMETHOD(GetCapture)();
        STDMETHOD(SetCapture)(BOOL fCapture);
        STDMETHOD(GetFocus)();
        STDMETHOD(SetFocus)(BOOL fFocus);
        STDMETHOD(GetDC)(LPCRECT pRect, DWORD grfFlags, HDC* phDC);
        STDMETHOD(ReleaseDC)(HDC hDC);
        STDMETHOD(InvalidateRect)(LPCRECT pRect, BOOL fErase);
        STDMETHOD(InvalidateRgn)(HRGN hRGN, BOOL fErase);
        STDMETHOD(ScrollRect)(INT dx, INT dy, LPCRECT pRectScroll, LPCRECT pRectClip);
        STDMETHOD(AdjustRect)(LPRECT prc);
        STDMETHOD(OnDefWindowMessage)(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT* plResult);
	END_INTERFACE_PART(OleInPlaceSiteWindowless)
	DECLARE_INTERFACE_MAP()

    virtual HDC WindowlessGetDC(LPCRECT pRect, DWORD grfFlags);
    virtual void WindowlessReleaseDC(HDC hDC);
    virtual void WindowlessInvalidateRect(LPCRECT pRect, BOOL fErase);
    virtual void WindowlessInvalidateRgn(HRGN hRGN, BOOL fErase);
    virtual void WindowlessScrollRect(INT dx, INT dy, LPCRECT pRectScroll, LPCRECT pRectClip);
    virtual void WindowlessAdjustRect(LPRECT prc);
    virtual BOOL WindowlessOnDefWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
};

// an enhanced OCC manager class. 
// The container and site classes to instantiate are gives as CRuntimeClass objects.
// The default creates COleControlContainerEx and COleControlSiteEx.
class COccManagerEx : public COccManager
{
public:
	COccManagerEx(CRuntimeClass* pContainerClass = RUNTIME_CLASS(COleControlContainerEx), 
		CRuntimeClass* pSiteClass = RUNTIME_CLASS(COleControlSiteEx));

	// Internal object creation
	virtual COleControlContainer* CreateContainer(CWnd* pWnd);
	virtual COleControlSite* CreateSite(COleControlContainer* pCtrlCont);

	CRuntimeClass* m_pContainerClass;
	CRuntimeClass* m_pSiteClass;
};

// Useful CWnd replacement for windowless controls.
// Just redefines CreateControl.
class CWindowlessControl : public CWnd
{
	DECLARE_DYNCREATE(CWindowlessControl)
public:
	CWindowlessControl();

	BOOL CreateControl(REFCLSID clsid, LPCTSTR pszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID, CFile* pPersist=NULL,
		BOOL bStorage=FALSE, BSTR bstrLicKey=NULL);

	BOOL CreateControl(LPCTSTR pszClass, LPCTSTR pszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID, CFile* pPersist=NULL,
		BOOL bStorage=FALSE, BSTR bstrLicKey=NULL);
};

#endif // OccEx.h
