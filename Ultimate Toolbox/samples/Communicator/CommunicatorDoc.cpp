// CommunicatorDoc.cpp : implementation of the CCommunicatorDoc class
//

#include "stdafx.h"
#include "Communicator.h"

#include "CommunicatorDoc.h"
#include "OXCommMsg.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorDoc

IMPLEMENT_DYNCREATE(CCommunicatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CCommunicatorDoc, CDocument)
	//{{AFX_MSG_MAP(CCommunicatorDoc)
	ON_BN_CLICKED(IDC_SPY, OnSpy)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCommunicatorDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CCommunicatorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IComm to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F44C48E2-6DD7-11CF-8508-00AA0021F02C}
static const IID IID_IComm =
{ 0xf44c48e2, 0x6dd7, 0x11cf, { 0x85, 0x8, 0x0, 0xaa, 0x0, 0x21, 0xf0, 0x2c } };

BEGIN_INTERFACE_MAP(CCommunicatorDoc, CDocument)
	INTERFACE_PART(CCommunicatorDoc, IID_IComm, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorDoc construction/destruction

CCommunicatorDoc::CCommunicatorDoc()
	:
	m_dataCommunicator(this),
	m_pCancelWnd(NULL),
	m_nTimeOut(10000)
	{
	m_pCancelWnd = AfxGetMainWnd();

	EnableAutomation();

	AfxOleLockApp();
	}

CCommunicatorDoc::~CCommunicatorDoc()
	{
	AfxOleUnlockApp();
	Shutdown();
	}

BOOL CCommunicatorDoc::OnNewDocument()
	{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// Get the local server name
	const int nMaxAddressLength = 128;
	char szLocalAddress[nMaxAddressLength];
	gethostname(szLocalAddress, nMaxAddressLength);
	m_sLocalAddress = szLocalAddress;

	return TRUE;
	}

CString CCommunicatorDoc::GetLocalAddress() const
	{
	return m_sLocalAddress;
	}

UINT CCommunicatorDoc::GetLocalPort() const
	{
	CString sAddress;
	UINT nPort;
	if ((m_dataCommunicator.m_hSocket != INVALID_SOCKET) && 
		((CAsyncSocket*)&m_dataCommunicator)->GetSockName(sAddress, nPort))
		{
		return nPort;
		}
	else
		return 0;
	}

BOOL CCommunicatorDoc::IsOpen()
	{
	return m_dataCommunicator.IsOpen();
	}

BOOL CCommunicatorDoc::IsListening()
	{
	return m_dataCommunicator.IsListening();
	}

BOOL CCommunicatorDoc::IsBlocking()
	{
	return m_dataCommunicator.AreAnyBlocking();
	}

void CCommunicatorDoc::CancelBlocking()
	{
	m_dataCommunicator.CancelAllBlockingCalls();
	}

BOOL CCommunicatorDoc::Listen(long nServerPort)
	{
	BOOL bSuccess = TRUE;
	if (m_dataCommunicator.m_hSocket != INVALID_SOCKET);
		{
		if (m_dataCommunicator.Create(nServerPort) &&
		    m_dataCommunicator.Listen())
			{
			m_dataCommunicator.Initialize(m_nTimeOut, m_pCancelWnd);
			}
		else
			{
			TRACE(_T("CComServerDoc::Listen : Failed to create socket server\n"));
			m_dataCommunicator.Close();
			bSuccess = FALSE;
			}
		}
	ASSERT(bSuccess == m_dataCommunicator.IsListening());
	return bSuccess;
	}

void CCommunicatorDoc::Shutdown()
	{
	// ... m_pDataCommunicator may already be NULL
	TRY
		{
		m_dataCommunicator.Close();
		}
	END_TRY
	// Warn view of shutdown
	UpdateAllViews(NULL, NotifyRemoveAllClients, NULL);
	}

void CCommunicatorDoc::DisconnectClient(HCLIENT_COMMUNICATOR hClient)
	{
	COXCommunicator* pClientCommunicator = m_dataCommunicator.GetClientCommunicator(hClient);
	if (pClientCommunicator == NULL)
		return;
	TRY
		{
		pClientCommunicator->Close();
		}
	END_TRY

	// Warn view
	CHintData hintData;
	hintData.m_hClient = hClient;
	UpdateAllViews(NULL, NotifyRemoveClient, &hintData);
	}

BOOL CCommunicatorDoc::Send(HCLIENT_COMMUNICATOR hClient, COXCommMsg* pCommMsg)
	{
	ASSERT(pCommMsg != NULL);
	COXCommunicator* pClientCommunicator = m_dataCommunicator.GetClientCommunicator(hClient);
	if (pClientCommunicator == NULL)
		return FALSE;
	BOOL bSuccess = FALSE;
	TRY
		{
		pCommMsg->Serialize(*pClientCommunicator->GetOutStream());
		pClientCommunicator->GetOutStream()->Flush();
		bSuccess = TRUE;
		}
	END_TRY
	return bSuccess;
	}

BOOL CCommunicatorDoc::ConnectServer(CString sRemoteAddress, int nRemotePort, int nLocalPort)
	{
	BOOL bSuccess = TRUE;
	if (!m_dataCommunicator.Create(nLocalPort) ||
		!(m_dataCommunicator.Initialize(m_nTimeOut, m_pCancelWnd), TRUE) ||
		!m_dataCommunicator.Connect(sRemoteAddress, nRemotePort))
		{
		TRACE(_T("CComServerDoc::ConnectServer : Failed to create socket server\n"));

		m_dataCommunicator.Close();
		bSuccess = FALSE;
		}
	return bSuccess;
	}

BOOL CCommunicatorDoc::SendServer(COXCommMsg* pCommMsg)
	{
	BOOL bSuccess = FALSE;
	TRY
		{
		if (m_dataCommunicator.GetOutStream() != NULL)
			{
			pCommMsg->Serialize(*m_dataCommunicator.GetOutStream());
			m_dataCommunicator.GetOutStream()->Flush();
			bSuccess = TRUE;
			}
		}
	END_TRY
	return bSuccess;
	}

void CCommunicatorDoc::OnReceive(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pCommunicator, int nErrorCode)
	{
	POSITION pos = GetFirstViewPosition();
	if (pos != NULL)
		GetNextView(pos);
	if (pos == NULL)
		// At most one view is attached to this doc, which cannot be a Spy view
		OnReceiveDirect(hClient, pCommunicator, nErrorCode);
	else
		// More than one view is attached to this doc, 
		// at least one of them must be Spy view
		OnReceiveHex(hClient, pCommunicator, nErrorCode);
	}

void CCommunicatorDoc::OnReceiveDirect(HCLIENT_COMMUNICATOR hClient, 
									   COXCommunicator* pCommunicator, int nErrorCode)
	{
	UNREFERENCED_PARAMETER(nErrorCode);

	if (pCommunicator->GetMaxReadable() == 0)
		// Ignore no data
		return;

	CArchive* pInStream = pCommunicator->GetInStream();

	CHintData hintData;
	COXCommMsg commMsg;

	BOOL bVariantSuccess = FALSE;

	// Read the data directly in a variant array
	TRY
		{
		commMsg.Serialize(*pInStream);
		bVariantSuccess = TRUE;
		}
	CATCH(CFileException, e)
		{
		TRACE(_T("CComServerDoc::OnClientReceive : Catching CFileException\n"));
		}
	AND_CATCH(CArchiveException, e)
		{
		TRACE(_T("CComServerDoc::OnClientReceive : Catching CArchiveException\n"));
		}
	END_CATCH

	hintData.m_hClient = hClient;
	hintData.m_pData = NULL;
	hintData.m_nDataLength = 0;
	if (bVariantSuccess)
		hintData.m_pCommMsg = &commMsg;
	UpdateAllViews(NULL, NotifyAddData, &hintData);
	}

void CCommunicatorDoc::OnReceiveHex(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pCommunicator, int nErrorCode)
	{
	UNREFERENCED_PARAMETER(nErrorCode);

	if (pCommunicator->GetMaxReadable() == 0)
		// Ignore no data
		return;

	CArchive* pInStream = pCommunicator->GetInStream();

	CHintData hintData;
	UINT nDataLength = 0;
	BYTE* pData = NULL;
	COXCommMsg commMsg;

	BOOL bDataSuccess = FALSE;
	BOOL bVariantSuccess = FALSE;

	// First read into memory block
	CMemFile memFile;
	TRY
		{
		unsigned char pc[2];;
		pc[1] = '\0';
		do
			{
			do
				{
				pInStream->Read(pc, 1);
				memFile.Write(pc, 1);
				} while (!pInStream->IsBufferEmpty());
			} while(pCommunicator->GetMaxReadable() != 0);
		nDataLength = memFile.GetLength();
		pData = memFile.Detach();
		bDataSuccess = TRUE;
		}
	CATCH(CFileException, e)
		{
		TRACE(_T("CComServerDoc::OnReceive : Catching CFileException\n"));
		if (pData == NULL)
			{
			nDataLength = memFile.GetLength();
			pData = memFile.Detach();
			}
		}
	AND_CATCH(CArchiveException, e)
		{
		TRACE(_T("CComServerDoc::OnReceive : Catching CArchiveException\n"));
		if (pData == NULL)
			{
			nDataLength = memFile.GetLength();
			pData = memFile.Detach();
			}
		}
	END_CATCH

	// Now reread the data in a variant array
	TRY
		{
		memFile.Attach(pData, nDataLength);
		CArchive inStream(&memFile, CArchive::load);
		commMsg.Serialize(inStream);
		memFile.Detach();
		bVariantSuccess = TRUE;
		}
	CATCH(CFileException, e)
		{
		TRACE(_T("CComServerDoc::OnClientReceive : Catching CFileException\n"));
		memFile.Detach();
		}
	AND_CATCH(CArchiveException, e)
		{
		TRACE(_T("CComServerDoc::OnClientReceive : Catching CArchiveException\n"));
		memFile.Detach();
		}
	END_CATCH

	hintData.m_hClient = hClient;
	if (bDataSuccess)
		{
		hintData.m_pData = pData;
		hintData.m_nDataLength = nDataLength;
		}
	if (bVariantSuccess)
		hintData.m_pCommMsg = &commMsg;
	UpdateAllViews(NULL, NotifyAddData, &hintData);

	// Clean up memory
	free(pData);
	}

void CCommunicatorDoc::OnClientCreate(HCLIENT_COMMUNICATOR hClient, 
									  COXCommunicator* pClientCommunicator)
	{
	CHintData hintData;
	hintData.m_hClient = hClient;
	pClientCommunicator->GetPeerName(hintData.m_sClientAddress, hintData.m_nClientPort);
	UpdateAllViews(NULL, NotifyAddClient, &hintData);
	}

void CCommunicatorDoc::OnClientReceive(HCLIENT_COMMUNICATOR hClient, 
									   COXCommunicator* pClientCommunicator, 
									   DWORD nSize, int nErrorCode)
	{
	UNREFERENCED_PARAMETER(nSize);
	OnReceive(hClient, pClientCommunicator, nErrorCode);
	}

void CCommunicatorDoc::OnClientClose(HCLIENT_COMMUNICATOR hClient, 
									 COXCommunicator* pClientCommunicator, 
									 int nErrorCode)
	{
	UNREFERENCED_PARAMETER(nErrorCode);
	UNREFERENCED_PARAMETER(pClientCommunicator);
	CHintData hintData;
	hintData.m_hClient = hClient;
	UpdateAllViews(NULL, NotifyRemoveClient, &hintData);
	}

void CCommunicatorDoc::OnServerReceive(DWORD nSize, int nErrorCode)
	{
	UNREFERENCED_PARAMETER(nSize);
	OnReceive(0, &m_dataCommunicator, nErrorCode);
	}

void CCommunicatorDoc::OnServerClose(int nErrorCode)
	{
	UNREFERENCED_PARAMETER(nErrorCode);
	}

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorDoc serialization

void CCommunicatorDoc::Serialize(CArchive& ar)
	{
	if (ar.IsStoring())
		{
		// TODO: add storing code here
		}
	else
		{
		// TODO: add loading code here
		}
	}

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorDoc diagnostics

#ifdef _DEBUG
void CCommunicatorDoc::AssertValid() const
	{
	CDocument::AssertValid();
	}

void CCommunicatorDoc::Dump(CDumpContext& dc) const
	{
	CDocument::Dump(dc);
	}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorDoc commands

void CCommunicatorDoc::OnSpy() 
	{
	COleDateTime oleDate;
	SYSTEMTIME t;
	t.wYear = 1996;
	t.wMonth = 10;
	t.wDay = 6;
	t.wHour = 16;
	t.wMinute = 53;
	t.wSecond = 24;

	oleDate = t;


	CFrameWnd* pHexFrame = NULL;
	pHexFrame = ((CCommunicatorApp*)AfxGetApp())->m_pHexDocTemplate->CreateNewFrame(this, NULL);
	pHexFrame->InitialUpdateFrame(this, TRUE);
	}

void CCommunicatorDoc::OnCancel() 
	{
	m_dataCommunicator.CancelAllBlockingCalls();
	}

BOOL CCommunicatorDoc::IsModified()
	{
	// Never ask to save the doc
	return FALSE;
	}