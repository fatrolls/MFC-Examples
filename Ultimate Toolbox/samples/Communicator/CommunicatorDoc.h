// CommunicatorDoc.h : interface of the CCommunicatorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "OXDataCommunicator.h"

class COXCommMsg;

class CCommunicatorDoc : public CDocument
{
protected: // create from serialization only
	CCommunicatorDoc();
	DECLARE_DYNCREATE(CCommunicatorDoc)

// Attributes
public:

// Operations
public:
	CString GetLocalAddress() const;
	UINT GetLocalPort() const;
	BOOL IsOpen();
	BOOL IsListening();
	BOOL IsBlocking();
	void CancelBlocking();

	BOOL Listen(long nServerPort);
	void Shutdown();
	void DisconnectClient(HCLIENT_COMMUNICATOR hClient);
	BOOL Send(HCLIENT_COMMUNICATOR hClient, COXCommMsg* pCommMsg);
	BOOL ConnectServer(CString sRemoteAddress, int nRemotePort, int nLocalPort);
	BOOL SendServer(COXCommMsg* pCommMsg);

	void OnReceive(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pCommunicator, int nErrorCode);
	void OnReceiveDirect(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pCommunicator, int nErrorCode);
	void OnReceiveHex(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pCommunicator, int nErrorCode);

	void OnClientCreate(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator);
	void OnClientReceive(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator, DWORD nSize, int nErrorCode);
	void OnClientClose(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator, int nErrorCode);
	void OnServerReceive(DWORD nSize, int nErrorCode);
	void OnServerClose(int nErrorCode);

	enum 
		{
		NotifyAddClient =		1,
		NotifyRemoveClient =	2,
		NotifyRemoveAllClients =3,
		NotifyAddData =			4
		};

	class CHintData : public CObject
		{
		public:
			HCLIENT_COMMUNICATOR	m_hClient;
			CString				m_sClientAddress;
			UINT				m_nClientPort;
			COXCommMsg*			m_pCommMsg;
			BYTE*				m_pData;
			UINT				m_nDataLength;
		CHintData()
			:
			m_hClient(0),
			m_sClientAddress(""),
			m_nClientPort(0),
			m_pCommMsg(NULL),
			m_pData(NULL),
			m_nDataLength(0)
			{
			}
		};


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommunicatorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	virtual BOOL IsModified();

protected:
	CString m_sLocalAddress;
	COXDataCommunicator m_dataCommunicator;
	CWnd* m_pCancelWnd;
	UINT m_nTimeOut;


// Implementation
public:
	virtual ~CCommunicatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCommunicatorDoc)
	afx_msg void OnSpy();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCommunicatorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
