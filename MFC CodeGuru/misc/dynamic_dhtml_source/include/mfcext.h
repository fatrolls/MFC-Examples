#if !defined(AFX_MFCEXT_H__33BA08B0_E19D_11D1_ABF7_99B5C24DD97B__INCLUDED_)
#define AFX_MFCEXT_H__33BA08B0_E19D_11D1_ABF7_99B5C24DD97B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// mfcext.h : header file
//
#include <exdisp.h> //For IWebBrowser2* and others
#include <mshtml.h>
#include <mshtmhst.h>
/////////////////////////////////////////////////////////////////////////////
// CBrowserView view

class CHTMLForm;
#define IDC_EXPLORER 1

class AFX_EXT_CLASS CBrowserView : public CView
{
protected:
	CBrowserView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBrowserView)

// Attributes
public:

// Operations
public:
	virtual void OnContextMenu(POINT pt);
	BOOL LoadForm(CHTMLForm* pForm);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBrowserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	BOOL m_bNewForm;
	IWebBrowser2* m_pWebBrowser2;
	CWnd m_wndWebBrowser;
	CHTMLForm* m_pForm;

	//{{AFX_MSG(CBrowserView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDownloadComplete();
	afx_msg void OnDocumentComplete(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CHTMLForm;

};

/////////////////////////////////////////////////////////////////////////////


class AFX_EXT_CLASS CHTMLForm : public CObject 
{
public:
	void SetURL(LPCTSTR strURL);
	IHTMLInputTextElement* GetInputElement(LPCTSTR lpszName);
	IHTMLElement* GetElement(LPCTSTR lpszName);
	IDispatch* GetElementDisp(LPCTSTR lpszName);
	virtual void ExecuteCmd(LPCTSTR lpszCmd);

	CHTMLForm(LPCTSTR lpszURL );
	CHTMLForm();
	virtual ~CHTMLForm();
	
	DECLARE_DYNCREATE(CHTMLForm)
protected:
	IHTMLElementCollection* m_pCollection;
	virtual void OnInitializeVars();
	virtual void OnLoad(IHTMLElementCollection* pCollection);
	CString m_strURL;

	friend class CBrowserView;
};


class CDocHostUIHandler : public IDocHostUIHandler  
{
public:
	CDocHostUIHandler();
	virtual ~CDocHostUIHandler();
   public:
        virtual HRESULT STDMETHODCALLTYPE ShowContextMenu( 
            /* [in] */ DWORD dwID,
            /* [in] */ POINT __RPC_FAR *ppt,
            /* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
            /* [in] */ IDispatch __RPC_FAR *pdispReserved) ;
        
        virtual HRESULT STDMETHODCALLTYPE GetHostInfo( 
            /* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo) ;
        
        virtual HRESULT STDMETHODCALLTYPE ShowUI( 
            /* [in] */ DWORD dwID,
            /* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
            /* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
            /* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc) ;
        
        virtual HRESULT STDMETHODCALLTYPE HideUI( void) ;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateUI( void) ;
        
        virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
            /* [in] */ BOOL fEnable) ;
    
        virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate( 
            /* [in] */ BOOL fActivate) ;
        
        virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate( 
            /* [in] */ BOOL fActivate) ;
        
        virtual HRESULT STDMETHODCALLTYPE ResizeBorder( 
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
            /* [in] */ BOOL fRameWindow) ;
        
        virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
            /* [in] */ LPMSG lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID) ;
        
        virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath( 
            /* [out] */ LPOLESTR __RPC_FAR *pchKey,
            /* [in] */ DWORD dw) ;
        
        virtual HRESULT STDMETHODCALLTYPE GetDropTarget( 
            /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
            /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget) ;
        
        virtual HRESULT STDMETHODCALLTYPE GetExternal( 
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch) ;
        
        virtual HRESULT STDMETHODCALLTYPE TranslateUrl( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut) ;
        
        virtual HRESULT STDMETHODCALLTYPE FilterDataObject( 
            /* [in] */ IDataObject __RPC_FAR *pDO,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet) ;

		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject);
		
		virtual ULONG STDMETHODCALLTYPE AddRef();

		virtual ULONG STDMETHODCALLTYPE Release();

protected:
	CBrowserView* m_pBrowserView;
	ULONG m_dwRefCount;
	friend class CBrowserView;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCEXT_H__33BA08B0_E19D_11D1_ABF7_99B5C24DD97B__INCLUDED_)
