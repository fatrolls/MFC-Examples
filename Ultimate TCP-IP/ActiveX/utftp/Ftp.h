// Ftp.h : Declaration of the CFtp

#ifndef __FTP_H_
#define __FTP_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "UTFtpCP.h"
#include "Ftp_c.h"
#include "MarshalEvents.h"
#include "FtpLicense.h"
#include "UT_MethodQueue.h"

	// Types of methods
	typedef enum MethodTypeTag {
		METHOD_CDUP,
		METHOD_CHDIR,
		METHOD_CONNECT,
		METHOD_CLOSE,
		METHOD_DELETE_FILE,
		METHOD_GET_DIR_INFO,
		METHOD_GET_HELP,
		METHOD_MKDIR,
		METHOD_NOOP,
		METHOD_RECEIVE_FILE,
		METHOD_RENAME_FILE,
		METHOD_REMOVE_DIR,
		METHOD_SEND_FILE,
		METHOD_RESUME_FILE,
		METHOD_QUOTE,
		METHOD_GET_CUR_DIR,
		METHOD_SET_TRANSFER_MODE,
		METHOD_SET_TRANSFER_STRUCTURE,
		METHOD_SET_TRANSFER_TYPE
		} MethodType;


/////////////////////////////////////////////////////////////////////////////
// CFtp
class ATL_NO_VTABLE CFtp : 
	public CUT_MethodQueue<CFtp, MethodTypeTag>,

	public CUT_FTPClient,

	public CMarshalEvents<CFtp, &DIID__IFtpEvents, TRUE>,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CFtp, IFtp, &IID_IFtp, &LIBID_UTFTPLib>,
	public CComControl<CFtp>,
	public IPersistStreamInitImpl<CFtp>,
	public IOleControlImpl<CFtp>,
	public IOleObjectImpl<CFtp>,
	public IOleInPlaceActiveObjectImpl<CFtp>,
	public IViewObjectExImpl<CFtp>,
	public IOleInPlaceObjectWindowlessImpl<CFtp>,
	public IPersistStorageImpl<CFtp>,
	public IPersistPropertyBagImpl<CFtp>,
	public ISpecifyPropertyPagesImpl<CFtp>,
	public IDataObjectImpl<CFtp>,
	public IProvideClassInfo2Impl<&CLSID_Ftp, &DIID__IFtpEvents, &LIBID_UTFTPLib>,
	public CProxy_IFtpEvents< CFtp >,
	public IPropertyNotifySinkCP< CFtp >,
	public CComCoClass<CFtp, &CLSID_Ftp>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CFtp>,
	public IObjectSafetyImpl<CFtp, INTERFACESAFE_FOR_UNTRUSTED_CALLER >

{

friend	CProxy_IFtpEvents< CFtp >;
friend	CUT_MethodQueue<CFtp, MethodTypeTag>;

public:
	CFtp();
	~CFtp();

DECLARE_REGISTRY_RESOURCEID(IDR_FTP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFtp)
	COM_INTERFACE_ENTRY(IFtp)
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

BEGIN_PROP_MAP(CFtp)
	PROP_ENTRY("ConnectTimeOut", DISPID_CONNECT_TIME_OUT, CLSID_FtpPropPage )
	PROP_ENTRY("BlockingMode", DISPID_BLOCKING_MODE, CLSID_FtpPropPage )
	PROP_ENTRY("FireWallMode", DISPID_FIREWALL_MODE, CLSID_FtpPropPage )
	PROP_ENTRY("HostName", DISPID_HOST_NAME, CLSID_FtpPropPage )
	PROP_ENTRY("UserName", DISPID_USER_NAME, CLSID_FtpPropPage )
	PROP_ENTRY("Password", DISPID_USER_PASSWORD, CLSID_FtpPropPage )
	PROP_ENTRY("Account", DISPID_ACCOUNT, CLSID_FtpPropPage )
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CFtp)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IFtpEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CFtp)
	CHAIN_MSG_MAP(CComControl<CFtp>)
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
	DECLARE_CLASSFACTORY2(CFtpLicense)

// IFtp
public:
	STDMETHOD(get_CurrentDir)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(ResumeFile)(/*[in]*/ BSTR SourceFileName, /*[in]*/ BSTR DestFileName, /*[out, retval]*/ long * Result);
	STDMETHOD(Quote)(/*[in]*/ BSTR Command, /*[out, retval]*/ long * Result);
	STDMETHOD(SetTransferType)(/*[in]*/ FtpTransferType TransferType, /*[out, retval]*/ long *Result);
	STDMETHOD(SetTransferStructure)(/*[in]*/ FtpTransferStructure TransferStructure, /*[out, retval]*/ long *Result);
	STDMETHOD(SetTransferMode)(/*[in]*/ FtpTransferMode TransferMode, /*[out, retval]*/ long *Result);
	STDMETHOD(get_DirEntryIsDir)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_DirEntryMinute)(/*[out, retval]*/ int *pVal);
	STDMETHOD(get_DirEntryHour)(/*[out, retval]*/ int *pVal);
	STDMETHOD(get_DirEntryYear)(/*[out, retval]*/ int *pVal);
	STDMETHOD(get_DirEntryMonth)(/*[out, retval]*/ int *pVal);
	STDMETHOD(get_DirEntryDay)(/*[out, retval]*/ int *pVal);
	STDMETHOD(get_DirEntrySize)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_DirEntryName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Account)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Account)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_UserPassword)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UserPassword)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_UserName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UserName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_HostName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_HostName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_MultilineResponseLineCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_TransferType)(/*[out, retval]*/ FtpTransferType *pVal);
	STDMETHOD(get_TransferStructure)(/*[out, retval]*/ FtpTransferStructure *pVal);
	STDMETHOD(get_TransferMode)(/*[out, retval]*/ FtpTransferMode *pVal);
	STDMETHOD(get_FireWallMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_FireWallMode)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(GetMultilineResponse)(/*[in]*/ long Index, /*[out, retval]*/ BSTR * Result);
	STDMETHOD(EnumDirEntry)(/*[out, retval]*/ long * Result);
	STDMETHOD(ResetDirEntryEnum)();
	STDMETHOD(GetCurDir)(/*[out, retval]*/ long * Result);
	STDMETHOD(SendFile)(/*[in]*/ BSTR SourceFileName, /*[in]*/ BSTR DestFileName, /*[out, retval]*/ long * Result);
	STDMETHOD(RemoveDir)(/*[in]*/ BSTR Directory, /*[out, retval]*/ long * Result);
	STDMETHOD(RenameFile)(/*[in]*/ BSTR SourceFileName, /*[in]*/ BSTR DestFileName, /*[out, retval]*/ long * Result);
	STDMETHOD(ReceiveFile)(/*[in]*/ BSTR SourceFileName, /*[in]*/ BSTR DestFileName, /*[out, retval]*/ long * Result);
	STDMETHOD(NoOp)(/*[out, retval]*/ long * Result);
	STDMETHOD(MkDir)(/*[in]*/ BSTR Directory, /*[out, retval]*/ long * Result);
	STDMETHOD(GetHelp)(/*[in, defaultvalue("")]*/ BSTR Param, /*[out, retval]*/ long * Result);
	STDMETHOD(GetDirInfo)(/*[out, retval]*/ long * Result);
	STDMETHOD(DeleteFile)(/*[in]*/ BSTR FileName, /*[out, retval]*/ long * Result);
	STDMETHOD(Connect)(/*[out, retval]*/ long * Result);
	STDMETHOD(Close)(/*[out, retval]*/ long * Result);
	STDMETHOD(ChDir)(/*[in]*/ BSTR DirName, /*[out, retval]*/ long * Result);
	STDMETHOD(CdUp)(/*[out, retval]*/ long * Result);

	STDMETHOD(AboutBox)();
	STDMETHOD(CancelFtp)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);
	STDMETHOD(get_ConnectTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ConnectTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_BlockingMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BlockingMode)(/*[in]*/ VARIANT_BOOL newVal);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);

	HRESULT OnDraw(ATL_DRAWINFO& di);

// IFtp Private data members
private:
	HICON				m_hFtpIcon;				// Ftp icon handle

	LONG				m_nCurDirEntryIndex;	// Current directory entry index
	CUT_DIRINFO			m_CurDirEntry;			// Current directory entry

    _bstr_t             m_bstrServerCurDir;     // Current directory on the server        

	LONG				m_lnConnectTimeOut;		// Connection TimeOut in seconds
	BOOL				m_bAbortFlag;			// TRUE if we are going to abort Ftp
	BOOL				m_bBlockingMode;		// TRUE if we are working in blocking mode

	BOOL				m_bGoingToClose;		// TRUE if the control is going to be destroyed

	_bstr_t				m_bstrHostName;			// Host name property variable
	_bstr_t				m_bstrUserName;			// User name property variable
	_bstr_t				m_bstrUserPassword;		// User password property variable
	_bstr_t				m_bstrAccount;			// Account property variable

	// Execute specified method
	virtual long	ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking);

	// Waits for the object to be signaled
	BOOL			WaitWithMsgLoop(HANDLE hEvent, long lTimeout);

	// Return TRUE if we are going to abort operation
	virtual BOOL	IsAborted();		

	// Monitor progress and/or cancel the receive 
	virtual BOOL	ReceiveFileStatus(long bytesReceived);

	// Monitor progress and/or cancel the send
	virtual BOOL	SendFileStatus(long bytesSent);

};

#endif //__FTP_H_
