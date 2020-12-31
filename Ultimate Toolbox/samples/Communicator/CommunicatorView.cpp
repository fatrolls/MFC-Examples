// CommunicatorView.cpp : implementation of the CCommunicatorView class
//

#include "stdafx.h"
#include "Communicator.h"

#include "CommunicatorDoc.h"
#include "CommunicatorView.h"
#include "SendDataDlg.h"
#include "OXBlob.h"

#include <afxpriv.h>	// for OnIdleUpdateCmdUI
#include <afxmt.h>		// For mutex support

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorView

#pragma data_seg(".sdata")
// Store the usage count of this application so that multiple instances will
// cascade nicely on the screen
LONG nUsageCount = 0;
#pragma data_seg()


IMPLEMENT_DYNCREATE(CCommunicatorView, CFormView)

BEGIN_MESSAGE_MAP(CCommunicatorView, CFormView)
	//{{AFX_MSG_MAP(CCommunicatorView)
	ON_BN_CLICKED(IDC_CONNECT_SERVER, OnConnectServer)
	ON_BN_CLICKED(IDC_DISCONNECT_CLIENT, OnDisconnectClient)
	ON_BN_CLICKED(IDC_DISCONNECT_SERVER, OnDisconnectServer)
	ON_BN_CLICKED(IDC_LISTEN, OnListen)
	ON_BN_CLICKED(IDC_SEND_CLIENT, OnSendClient)
	ON_BN_CLICKED(IDC_SEND_SERVER, OnSendServer)
	ON_BN_CLICKED(IDC_SHUTDOWN, OnShutdown)
	ON_MESSAGE_VOID(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorView construction/destruction

CCommunicatorView::CCommunicatorView()
	: CFormView(CCommunicatorView::IDD)
	{
	//{{AFX_DATA_INIT(CCommunicatorView)
	m_sLocalAddress = _T("");
	m_nLocalPort = 1000;
	m_sRemoteAddress = _T("");
	m_nRemotePort = 1000;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	}

CCommunicatorView::~CCommunicatorView()
	{
	}

void CCommunicatorView::DoDataExchange(CDataExchange* pDX)
	{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommunicatorView)
	DDX_Control(pDX, IDC_CANCEL, m_wndCancel);
	DDX_Control(pDX, IDC_LOCAL_PORT_LABEL, m_wndLocalPortLabel);
	DDX_Control(pDX, IDC_SERVER_GROUP, m_wndServerGroup);
	DDX_Control(pDX, IDC_REMOTE_ADDRESS_LABEL, m_wndRemoteAddressLabel);
	DDX_Control(pDX, IDC_REMOTE_PORT_LABEL, m_wndRemotePortLabel);
	DDX_Control(pDX, IDC_LOCAL_ADDRESS_LABEL, m_wndLocalAddressLabel);
	DDX_Control(pDX, IDC_CLIENT_GROUP, m_wndClientGroup);
	DDX_Control(pDX, IDC_CLIENT_ADDRESSES_LABEL, m_wndClientAddressLabel);
	DDX_Control(pDX, IDC_SEND_SERVER, m_wndSendServer);
	DDX_Control(pDX, IDC_DISCONNECT_SERVER, m_wndDisconnectServer);
	DDX_Control(pDX, IDC_CONNECT_SERVER, m_wndConnectServer);
	DDX_Control(pDX, IDC_REMOTE_PORT, m_wndRemotePort);
	DDX_Control(pDX, IDC_REMOTE_ADDRESS, m_wndRemoteAddress);
	DDX_Control(pDX, IDC_DISCONNECT_CLIENT, m_wndDisconnectClient);
	DDX_Control(pDX, IDC_SEND_CLIENT, m_wndSendClient);
	DDX_Control(pDX, IDC_SHUTDOWN, m_wndShutdown);
	DDX_Control(pDX, IDC_LISTEN, m_wndListen);
	DDX_Control(pDX, IDC_LOCAL_PORT, m_wndLocalPort);
	DDX_Control(pDX, IDC_LOCAL_ADDRESS, m_wndLocalAddress);
	DDX_Control(pDX, IDC_CLIENT_ADDRESSES, m_wndClientAddresses);
	DDX_Control(pDX, IDC_RECEIVED_DATA, m_wndReceivedData);
	DDX_Text(pDX, IDC_LOCAL_ADDRESS, m_sLocalAddress);
	DDX_Text(pDX, IDC_LOCAL_PORT, m_nLocalPort);
	DDX_Text(pDX, IDC_REMOTE_ADDRESS, m_sRemoteAddress);
	DDX_Text(pDX, IDC_REMOTE_PORT, m_nRemotePort);
	//}}AFX_DATA_MAP
	}

BOOL CCommunicatorView::PreCreateWindow(CREATESTRUCT& cs)
	{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CFormView::PreCreateWindow(cs);
	}

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorView diagnostics

#ifdef _DEBUG
void CCommunicatorView::AssertValid() const
	{
	CFormView::AssertValid();
	}

void CCommunicatorView::Dump(CDumpContext& dc) const
	{
	CFormView::Dump(dc);
	}

CCommunicatorDoc* CCommunicatorView::GetDocument() // non-debug version is inline
	{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommunicatorDoc)));
	return (CCommunicatorDoc*)m_pDocument;
	}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorView message handlers

void CCommunicatorView::OnConnectServer() 
	{
	if (GetDocument()->IsBlocking())
		{
		TRACE(_T("CCommunicatorView::OnConnectServer : Communicator is still blocking\n"));
		MessageBeep(0xFFFF);
		return;
		}

	UpdateData(TRUE);
	// If remote address is not filled out, try a local connection
	if (m_sRemoteAddress.IsEmpty())
		{
		m_sRemoteAddress = GetDocument()->GetLocalAddress();
		UpdateData(FALSE);
		}
	// Do not use the specified local port, let winsockets pick one
	if (!GetDocument()->ConnectServer(m_sRemoteAddress, m_nRemotePort, 0))
		AfxMessageBox(IDS_FAILED_CONNECT, MB_ICONEXCLAMATION);
	m_nLocalPort = GetDocument()->GetLocalPort();
	UpdateData(FALSE);
	}

void CCommunicatorView::OnDisconnectClient() 
	{
	if (GetDocument()->IsBlocking())
		{
		TRACE(_T("CCommunicatorView::OnDisconnectClient : Communicator is still blocking\n"));
		MessageBeep(0xFFFF);
		return;
		}

	UINT nSelCount = m_wndClientAddresses.GetSelCount();
	if (0 < nSelCount)
		{
		int index;
		int* rgSels = new int[nSelCount];
		m_wndClientAddresses.GetSelItems(nSelCount, rgSels);
		for (index = (int)nSelCount - 1; 0 <= index; index--)
			GetDocument()->DisconnectClient(m_wndClientAddresses.GetItemData(rgSels[index]));
		delete rgSels;
		}
	}

void CCommunicatorView::OnDisconnectServer() 
	{
	if (GetDocument()->IsBlocking())
		{
		TRACE(_T("CCommunicatorView::OnDisconnectServer : Communicator is still blocking\n"));
		MessageBeep(0xFFFF);
		return;
		}

	GetDocument()->Shutdown();
	}

void CCommunicatorView::OnListen() 
	{
	if (GetDocument()->IsBlocking())
		{
		TRACE(_T("CCommunicatorView::OnListen : Communicator is still blocking\n"));
		MessageBeep(0xFFFF);
		return;
		}

	UpdateData(TRUE);
	if (!GetDocument()->Listen(m_nLocalPort))
		AfxMessageBox(IDS_FAILED_LISTEN, MB_ICONEXCLAMATION);
	}

void CCommunicatorView::OnSendClient() 
	{
	if (GetDocument()->IsBlocking())
		{
		TRACE(_T("CCommunicatorView::OnSendClient : Communicator is still blocking\n"));
		MessageBeep(0xFFFF);
		return;
		}

	COXCommMsg* pCommMsg = new COXCommMsg;

	CSendDataDlg dlg(pCommMsg);
	if (dlg.DoModal() == IDOK)
		{
		UINT nSelCount = m_wndClientAddresses.GetSelCount();
		if (0 < nSelCount)
			{
			int index;
			int* rgSels = new int[nSelCount];
			m_wndClientAddresses.GetSelItems(nSelCount, rgSels);
			for (index = 0; index < (int)nSelCount; index++)
				GetDocument()->Send(m_wndClientAddresses.GetItemData(rgSels[index]), pCommMsg);
			delete rgSels;
			}
		}
	delete pCommMsg;
	}

void CCommunicatorView::OnSendServer() 
	{
	if (GetDocument()->IsBlocking())
		{
		TRACE(_T("CCommunicatorView::OnSendServer : Communicator is still blocking\n"));
		MessageBeep(0xFFFF);
		return;
		}

	COXCommMsg* pCommMsg = new COXCommMsg;

	CSendDataDlg dlg(pCommMsg);
	if (dlg.DoModal() == IDOK)
		GetDocument()->SendServer(pCommMsg);

	delete pCommMsg;
	}

void CCommunicatorView::OnShutdown() 
	{
	if (GetDocument()->IsBlocking())
		{
		TRACE(_T("CCommunicatorView::OnShutdown : Communicator is still blocking\n"));
		MessageBeep(0xFFFF);
		return;
		}

	GetDocument()->Shutdown();
	}

void CCommunicatorView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
	{
	UNREFERENCED_PARAMETER(pSender);
	CCommunicatorDoc::CHintData* pHintData = (CCommunicatorDoc::CHintData*)pHint;
	CString sText;
	int index;
	switch(lHint)
		{
		case CCommunicatorDoc::NotifyAddClient:
			// Add the client address to the list
			sText.Format(_T("%i. %s (%i)"), pHintData->m_hClient, 
				(LPCTSTR)pHintData->m_sClientAddress, pHintData->m_nClientPort);

			index = m_wndClientAddresses.AddString(sText);
			m_wndClientAddresses.SetItemData(index, pHintData->m_hClient);
			// If nothing is selected, select this item
			if (m_wndClientAddresses.GetSelCount() == 0)
				m_wndClientAddresses.SetSel(index);
			break;
		case CCommunicatorDoc::NotifyRemoveClient:
			// Remove the client address from the list
			for (index = 0; index < m_wndClientAddresses.GetCount(); index++)
				{
				if ((int)m_wndClientAddresses.GetItemData(index) == pHintData->m_hClient)
					m_wndClientAddresses.DeleteString(index);
				}
			// If nothing is selected, select the first one
			if (m_wndClientAddresses.GetSelCount() == 0)
				m_wndClientAddresses.SetSel(0);
			break;
		case CCommunicatorDoc::NotifyRemoveAllClients:
			// Remove all the client address from the list
			m_wndClientAddresses.ResetContent();
			break;
		case CCommunicatorDoc::NotifyAddData:
			// Show the received data
			ShowData(pHintData);
			break;
		default:
			break;
		}
	}

void CCommunicatorView::ShowData(CCommunicatorDoc::CHintData* pHintData) 
	{
	CString sText;
	CString sValue;
	if (pHintData->m_pCommMsg == NULL)
		{
		if (pHintData->m_nDataLength != 0)
			sText.Format(_T("%i. <Unknown Format> (length = %i)\r\n"), 
				pHintData->m_hClient, pHintData->m_nDataLength);
		else
			sText.Format(_T("%i. <Unknown Format> (length = unknown)\r\n"), 
				pHintData->m_hClient);
		AddText(sText);
		return;
		}

	sText.Format(_T("%i. Array of size %i\r\n"), 
			pHintData->m_hClient, pHintData->m_pCommMsg->GetSize());
	AddText(sText);

	COXVariant variant;
	UINT nOleType;
	UINT nType;
	for (int index = 0; index < pHintData->m_pCommMsg->GetSize(); index++)
		{
		// Convert variant to string to visualize
		variant = pHintData->m_pCommMsg->GetAt(index);
		nOleType = V_VT(&variant);
		for (nType = 0; 
			 (nType < COXCommMsg::m_nArgumentTypesCount) && (nOleType != (UINT)COXCommMsg::m_types[nType]); 
			 nType++)
			;
		// ... Must have found the type
		ASSERT(nType < COXCommMsg::m_nArgumentTypesCount);

		sValue.Empty();
		TRY	
			{ 
			if (nOleType != COXCommMsg::ATBlob)
				{
				if (V_VT(&variant) == COXCommMsg::ATError)
					// ... Variant is a union, just change the type
					// oleVariant.lVal= oleVariant.scode ;
					V_VT(&variant) = COXCommMsg::ATI4;
				variant.ChangeType(COXCommMsg::ATStr); 
				sValue = V_BSTR(&variant);
				}
			else
				{
				ASSERT(nOleType == COXCommMsg::ATBlob);
				CString sTempPath;
				CString sTempFileName;
				COXBlob blob;
				VERIFY(::GetTempPath(_MAX_PATH, sTempPath.GetBuffer(_MAX_PATH)) != 0);
				sTempPath.ReleaseBuffer();
				VERIFY(::GetTempFileName(sTempPath,	_T("BLB"), 0,
				    	   sTempFileName.GetBuffer(_MAX_PATH)) != 0);
				sTempFileName.ReleaseBuffer();
				blob = variant;
				blob.WriteRaw(sTempFileName);
				sValue.Format(_T("<binary of length %i> (stored as %s)"), blob.GetSize(), sTempFileName);
				}
			} 
		END_TRY
		sText.Format(_T("\t%i. (%s) %s\r\n"), 
			index + 1,
			(LPCTSTR)COXCommMsg::m_typeNames[nType],
			(LPCTSTR)sValue);
		AddText(sText);
		}
	}

void CCommunicatorView::AddText(LPCTSTR pszText) 
	{
	LONG nWindowTextLength;
	nWindowTextLength = m_wndReceivedData.GetWindowTextLength();
	m_wndReceivedData.SetSel(nWindowTextLength, nWindowTextLength);
	m_wndReceivedData.ReplaceSel(pszText);
	}

void CCommunicatorView::OnInitialUpdate() 
	{
	CFormView::OnInitialUpdate();
	
	// Show local server name
	m_sLocalAddress = GetDocument()->GetLocalAddress();
	UpdateData(FALSE);

	// Fit frame around view
	ResizeParentToFit(FALSE);

	// Fit mainframe around frame, do this only once
	static bMainFrameResized = FALSE;
	if (!bMainFrameResized)
		{
		bMainFrameResized = TRUE;

		// Get the size of frame and main frame
		CRect frameRect;
		CRect mainFrameRect;
		CRect mainFrameClientRect;
		GetParentFrame()->GetWindowRect(frameRect);
		AfxGetMainWnd()->GetWindowRect(mainFrameRect);
		AfxGetMainWnd()->GetClientRect(mainFrameClientRect);

		// Resize the mainframe so that this view frame will completely fill the client area
		mainFrameRect.right += frameRect.Width() - mainFrameClientRect.Width();
		mainFrameRect.bottom += frameRect.Height() - mainFrameClientRect.Height();

		// Take other windows into account that also populate the main frames client area
		CWnd* pChild;
		CRect childRect;
		pChild = AfxGetMainWnd()->GetWindow(GW_CHILD);
		while (pChild != NULL)
			{
			// ... Skip the MDI frame window
			if (pChild != GetParentFrame()->GetParent())
				{
				pChild->GetWindowRect(childRect);
				// Statusbar and buttonbar take up the entire width (or height)
				// Use the smallest of the two
				if (childRect.Height() < childRect.Width())
					mainFrameRect.bottom += childRect.Height();
				else
					mainFrameRect.right += childRect.Width();
				}
			pChild = pChild->GetWindow(GW_HWNDNEXT);
			}

		// Position multiple instance next to each other
		CMutex mutex(FALSE, _T("COMMUNICATOR_MOVE"));
		// ... Lock the mutex, destructor will unlock
		CSingleLock lock(&mutex, TRUE);
		nUsageCount++;

		// If at most two instances are running
		if (nUsageCount <= 2)
			{
			// Put main frame in top left corner (0,0)
			mainFrameRect.right -= mainFrameRect.left;
			mainFrameRect.bottom -= mainFrameRect.top;
			mainFrameRect.left = 0;
			mainFrameRect.top = 0;

			// Position it next to the other instance (if it exists)
			mainFrameRect.left = mainFrameRect.right * (nUsageCount - 1);
			mainFrameRect.right = mainFrameRect.right * nUsageCount;
			}

		AfxGetMainWnd()->MoveWindow(mainFrameRect);
		}
	}

void CCommunicatorView::OnIdleUpdateCmdUI()
	{
	BOOL bClientSelected = (0 < m_wndClientAddresses.GetSelCount());
	BOOL bOpen = GetDocument()->IsOpen();
	BOOL bServer = FALSE;
	BOOL bClient = FALSE;
	if (bOpen)
		{
		bServer = GetDocument()->IsListening();
		bClient = !bServer;
		}

	// Conditionally disable controls
	// Server
	m_wndServerGroup.		EnableWindow(!bOpen || bServer);
	m_wndLocalAddressLabel.	EnableWindow(!bOpen);
	m_wndLocalAddress.		EnableWindow(!bOpen);
	m_wndLocalPortLabel.	EnableWindow(!bOpen);
	m_wndLocalPort.			EnableWindow(!bOpen);
	m_wndListen.			EnableWindow(!bOpen);
	m_wndShutdown.			EnableWindow(bServer);
	m_wndSendClient.		EnableWindow(bServer && bClientSelected);
	m_wndDisconnectClient.	EnableWindow(bServer && bClientSelected);
	m_wndClientAddressLabel.EnableWindow(bServer);
	m_wndClientAddresses.	EnableWindow(bServer);

	// Client
	m_wndClientGroup.		EnableWindow(!bOpen || bClient);
	m_wndRemoteAddressLabel.EnableWindow(!bOpen);
	m_wndRemoteAddress.		EnableWindow(!bOpen);
	m_wndRemotePortLabel.	EnableWindow(!bOpen);
	m_wndRemotePort.		EnableWindow(!bOpen);
	m_wndConnectServer.		EnableWindow(!bOpen);
	m_wndSendServer.		EnableWindow(bClient);
	m_wndDisconnectServer.	EnableWindow(bClient);

	// Global
	m_wndCancel.			EnableWindow(bOpen);
	}

void CCommunicatorView::PostNcDestroy() 
	{
	// Relase this instance count
	CMutex mutex(FALSE, _T("COMMUNICATOR_MOVE"));
	// ... Lock the mutex, destructor will unlock
	CSingleLock lock(&mutex, TRUE);
	nUsageCount--;

	CFormView::PostNcDestroy();
	}
