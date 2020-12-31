// SerialDoc.cpp : implementation of the CSerialDoc class
//

#include "stdafx.h"
#include "Serial.h"
#include "SerialDoc.h"

#include "MainFrame.h"
#include "SerialView.h"

#include "TimeoutDlg.h"
#include "TransferDlg.h"

#include "OXSCSTP.H"
#include "OXSCFILE.H"
#include "OXSCEXCP.H"

#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static TCHAR _szAllFilesFilter[] = _T("All Files (*.*)|*.*||");

typedef struct tagTHREADINFO
{
	COXSerialCommFile*	pCommDevice;
	HANDLE				hEvent;
	UINT				msgOutput;
	UINT				msgBackspace;
	HWND				hWnd;
} THREADINFO, *PTHREADINFO, FAR* LPTHREADINFO;


/////////////////////////////////////////////////////////////////////////////
// CSerialDoc

IMPLEMENT_DYNCREATE(CSerialDoc, CDocument)

BEGIN_MESSAGE_MAP(CSerialDoc, CDocument)
	//{{AFX_MSG_MAP(CSerialDoc)
	ON_COMMAND(IDM_CONNECT, OnConnect)
	ON_UPDATE_COMMAND_UI(IDM_CONNECT, OnUpdateConnect)
	ON_COMMAND(IDM_DISCONNECT, OnDisconnect)
	ON_UPDATE_COMMAND_UI(IDM_DISCONNECT, OnUpdateDisconnect)
	ON_COMMAND(IDM_RECEIVE, OnReceive)
	ON_UPDATE_COMMAND_UI(IDM_RECEIVE, OnUpdateReceive)
	ON_COMMAND(IDM_SEND, OnSend)
	ON_UPDATE_COMMAND_UI(IDM_SEND, OnUpdateSend)
	ON_COMMAND(IDM_SERIAL_SETUP, OnSerialSetup)
	ON_UPDATE_COMMAND_UI(IDM_SERIAL_SETUP, OnUpdateSerialSetup)
	ON_COMMAND(IDM_SET_TIMEOUT, OnSetTimeout)
	ON_UPDATE_COMMAND_UI(IDM_SET_TIMEOUT, OnUpdateSetTimeout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialDoc construction/destruction

CSerialDoc::CSerialDoc()
{
	m_pCommFile = NULL;
	m_pCommConfig = NULL;

	m_dwTxTimeout =
	m_dwRxTimeout = 200L;

	m_pIncomingTextThread = NULL;
}

CSerialDoc::~CSerialDoc()
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);

	if (m_pIncomingTextThread != NULL)
	{
		m_pIncomingTextThread->ResumeThread();
		m_eventClose.SetEvent();
		::WaitForSingleObject(m_pIncomingTextThread->m_hThread, INFINITE);
	}

	if (m_pCommConfig != NULL)
	{
		delete m_pCommConfig;
		m_pCommConfig = NULL;
	}

	if (m_pCommFile != NULL)
	{
		delete m_pCommFile;
		m_pCommFile = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSerialDoc serialization

void CSerialDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*) m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSerialDoc diagnostics

#ifdef _DEBUG
void CSerialDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSerialDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSerialDoc helpers

inline CSerialView* CSerialDoc::GetView() const
{
	// Returns a pointer to the "Terminal" view
		
	ASSERT_VALID(this);
	ASSERT_VALID(AfxGetMainWnd());

	POSITION pos = GetFirstViewPosition();

	if (pos != NULL)
	{
		CSerialView* pView = (CSerialView*) GetNextView(pos);
		ASSERT_VALID(pView);
		ASSERT_KINDOF(CSerialView, pView);

		return pView;
	}
	
	ASSERT(FALSE);
	return NULL;
}

BOOL CSerialDoc::SendKeyDown(UINT nChar)
{
	// If a connection is open SendKeyDown will send nChar to the receiving side's
	// "Terminal" view. If the connection is closed, nothing happens.
	//
	//
	
	if (!m_pCommFile->IsOpen())
		return FALSE;

	if (nChar == VK_RETURN)
	{
		GetView()->Output(_T("\r\n"));
		m_pCommFile->Write(_T("\r\n"), sizeof(_T("\r\n")));
	}
	else if (nChar == VK_BACK)
	{
		GetView()->Backspace();
		m_pCommFile->Write(_T("\b"), sizeof(_T("\b")));
	}
	else
	{
		GetView()->Output(_T("%c"), (char) nChar);
		m_pCommFile->Write(&nChar, sizeof(nChar));
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Thread & Thread helper functions

DWORD ReadEventBytesFromPort(COXSerialCommFile* pCommHandle, LPBYTE pbBuffer, DWORD dwLength)
{
	//
	// pCommHandle - a pointer to a COXSerialCommFile object from which to receive
	// pbBuffer - buffer to receive incoming data
	// dwLength - size of pbBuffer
	//
	//
	// This function will determine if there is any data to be read on pCommHandle, if
	// there is it is read into pbBuffer.
	
	DWORD dwBytesToRead = 0;
	
	TRY
	{
		dwBytesToRead = pCommHandle->GetBytesToRead();

		if (dwBytesToRead > dwLength)
			dwBytesToRead = dwLength;

		return pCommHandle->Read(pbBuffer, dwBytesToRead);
	}
	CATCH(COXSerialCommException, e)
	{
		TRACE(_T("There was an error trying to read from the COMM port.\n"));

		e->ReportError(MB_OK | MB_ICONSTOP);
	}
	END_CATCH

	return 0;
}

UINT IncomingTextThread(LPVOID pParam)
{
	//
	// pParam - pointer to THREADINFO structure
	//
	// This thread will monitor incoming data. Any incoming data is sent to the 
	// "Terminal" window as output text.
	//
	// This thread is suspended and resumed to minimize overhead.
	
	PTHREADINFO pInfo = NULL;
	pInfo = (PTHREADINFO) pParam;

	if (pInfo == NULL)
		return (UINT)-1;

	////////////////////////////////////////////////////////////////////////////
	// Monitor incoming data

	BYTE bBuffer[256];
	DWORD dwBytesRead = 0;

	while (WaitForSingleObject(pInfo->hEvent, 0) != WAIT_OBJECT_0)
	{
		bBuffer[0] = 0;
		dwBytesRead = ReadEventBytesFromPort(pInfo->pCommDevice, bBuffer, sizeof(bBuffer));
		ASSERT(dwBytesRead <= sizeof(bBuffer));

		if (dwBytesRead > 0)
		{
			if (bBuffer[0] == _T('\b'))
				SendMessage(pInfo->hWnd, pInfo->msgBackspace, 0, 0);
			else
				SendMessage(pInfo->hWnd, pInfo->msgOutput, 0, (LPARAM) bBuffer);
		}
	}
	
	delete pInfo;

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CSerialDoc overrides

BOOL CSerialDoc::SaveModified() 
{
	return TRUE;	// don't allow saving
}

BOOL CSerialDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*) m_viewList.GetHead())->SetWindowText(NULL);


	//
	// Create the COXSerialCommFile and COXSerialCommConfig objects	
	//
	ASSERT(m_pCommConfig == NULL);
	if (m_pCommConfig == NULL && (m_pCommConfig = new COXSerialCommConfig()) == NULL)
	{
		TRACE(_T("Unable to allocate new COXSerialCommConfig object\n"));
		return -1;
	}
	ASSERT_VALID(m_pCommConfig);

	ASSERT(m_pCommFile == NULL);
	if (m_pCommFile == NULL && (m_pCommFile = new COXSerialCommFile()) == NULL)
	{
		TRACE(_T("Unable to allocate new COXSerialCommFile object\n"));
		return -1;
	}
	ASSERT_VALID(m_pCommFile);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSerialDoc message handlers

void CSerialDoc::OnConnect() 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
		return;
	
	//
	// Attempt to make a connection
	//
	COXSerialCommException e;
	if (!m_pCommFile->Open(*m_pCommConfig, &e))
	{
		TRACE(_T("Unable to open serial communication device\n"));

		TCHAR szBuffer[256];

		e.GetErrorMessage(szBuffer, sizeof(szBuffer));
		GetView()->Output(szBuffer);
		GetView()->Output(_T("\r\n"));

		return;
	}
	else
	{
		//
		// setup which events we want to recieve on this comm port
		//
		DWORD dwEventMask;
		if (m_pCommFile->GetCommMask(dwEventMask))
		{
			dwEventMask |= EV_RXCHAR;
			VERIFY(m_pCommFile->SetCommMask(dwEventMask));
		}
		else
		{
			GetView()->Output(_T("Error (#%d): Unable to set event states on %s.\r\n"), ::GetLastError(), m_pCommConfig->GetCommName());
		}
		
		GetView()->Output(_T("A serial connection has been established on port %s.\r\n"), m_pCommConfig->GetCommName());
	}

	//
	// Create the new thread (if not created before); If the user has already connected
	// before we resume the suspended thread.
	//
	if (m_pIncomingTextThread == NULL)
	{
		PTHREADINFO pInfo = new THREADINFO;
		if (pInfo == NULL)
			return;

		pInfo->hEvent = (HANDLE) m_eventClose;
		pInfo->pCommDevice = m_pCommFile;
		pInfo->msgOutput = IDM_OUTPUT;
		pInfo->msgBackspace = IDM_BACKSPACE;
		pInfo->hWnd = GetView()->GetSafeHwnd();

		m_pIncomingTextThread = AfxBeginThread(IncomingTextThread, pInfo, THREAD_PRIORITY_IDLE);
	}
	else
	{
		// Thread already exists, resume it
		ASSERT_VALID(m_pIncomingTextThread);
		m_pIncomingTextThread->ResumeThread();
	}
}

void CSerialDoc::OnUpdateConnect(CCmdUI* pCmdUI) 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(m_pCommFile->IsOpen() == FALSE);
}

void CSerialDoc::OnDisconnect() 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);
	ASSERT_VALID(m_pIncomingTextThread);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
		return;

	//
	// Close the communications port and suspend the IncomingTextThread
	// (the thread is closed in the destructor)
	//
	m_pIncomingTextThread->SuspendThread();

	m_pCommFile->Close();
	GetView()->Output(_T("The communication port has been closed.\r\n"));
}

void CSerialDoc::OnUpdateDisconnect(CCmdUI* pCmdUI) 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(m_pCommFile->IsOpen());
}

void CSerialDoc::OnReceive() 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);
	ASSERT_VALID(m_pIncomingTextThread);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
	{
		GetView()->Output(_T("Invalid handles, unable to read.\r\n"));
		return;
	}

	ASSERT(m_pCommFile->IsOpen() == TRUE);

	//
	// Clear the send and receive queues	
	m_pCommFile->PurgeRx();
	m_pCommFile->PurgeTx();
	
	GetView()->Output(_T("Waiting for incoming files...\r\n"));

	CTransferDlg dlg;

	// Setup the transfer dialog
	//
	dlg.m_bSending = FALSE;
	dlg.m_pCommFile = m_pCommFile;
	dlg.m_pFile = NULL;

	/////////////////
	// Suspend the incoming Text thread 
	m_pIncomingTextThread->SuspendThread();

	//
	// Show the dialog
	// (the dialog will automatically terminate when the transfer is done)
	//
	if (dlg.DoModal() == IDCANCEL)
	{
		m_pCommFile->PurgeTx();
		m_pCommFile->PurgeRx();
		GetView()->Output(_T("Receive file cancelled by user.\r\n"));
	}
	else
	{
		GetView()->Output(dlg.m_sMessage);
	}	

	/////////////////
	// Resume the incoming Text thread 
	m_pIncomingTextThread->ResumeThread();
}

void CSerialDoc::OnUpdateReceive(CCmdUI* pCmdUI) 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(m_pCommFile->IsOpen());
}

void CSerialDoc::OnSend() 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);
	ASSERT_VALID(m_pIncomingTextThread);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
	{
		GetView()->Output(_T("Invalid handles, unable to write.\r\n"));
		return;
	}

	ASSERT(m_pCommFile->IsOpen() == TRUE);

	//
	// Purge the incoming and outgoing queues
	//
	m_pCommFile->PurgeRx();
	m_pCommFile->PurgeTx();

	//
	// Prompt the user for the file to send
	//
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _szAllFilesFilter);
	if (dlg.DoModal() == IDOK)
	{
		/////////////////
		// Suspend the Incoming text thread
		m_pIncomingTextThread->SuspendThread();

		CFile f;
		if (f.Open(dlg.GetPathName(), CFile::modeRead))
		{
			GetView()->Output(_T("Sending file %s which is %d bytes long; "), dlg.GetPathName(), f.GetLength());
			
			CTransferDlg tdlg;

			//
			// setup the transfer dialog
			//
			tdlg.m_sMessage.Format(_T("Waiting for other side to confirm transfer"));
			tdlg.m_sFilename = dlg.GetFileName();
			tdlg.m_pCommFile = m_pCommFile;
			tdlg.m_pFile = &f;
			tdlg.m_bSending = TRUE;

			//
			// Show the dialog
			//
			if (tdlg.DoModal() == IDCANCEL)
			{
				m_pCommFile->PurgeTx();
				m_pCommFile->PurgeRx();
				GetView()->Output(_T("Transfer cancelled.\r\n"));
			}
			else
			{
				GetView()->Output(tdlg.m_sMessage);
			}
		}
		else
			GetView()->Output(_T("Error: Unable to send; There was an error opening the file.\r\n"));
	
		/////////////////
		// Resume the Incoming Text Thread
		m_pIncomingTextThread->ResumeThread();
	}
}

void CSerialDoc::OnUpdateSend(CCmdUI* pCmdUI) 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(m_pCommFile->IsOpen());
}

void CSerialDoc::OnSerialSetup() 
{
	ASSERT_VALID(m_pCommConfig);

	if (m_pCommConfig != NULL)
	{
		//
		// Allow the user to edit COMM properties
		//
		// COXSerialCommConfig takes care of data validation
		m_pCommConfig->DoConfigDialog();
	}
}

void CSerialDoc::OnUpdateSerialSetup(CCmdUI* pCmdUI) 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(!m_pCommFile->IsOpen());
}

void CSerialDoc::OnSetTimeout() 
{
	ASSERT_VALID(m_pCommConfig);

	if (m_pCommConfig != NULL)
	{
		//
		// Allow user to change Send/Receive timeouts by showing the CTimeoutDlg
		// dialog.
		//		
		CTimeoutDlg dlg;

		dlg.m_dwRxTimeout = m_dwRxTimeout;
		dlg.m_dwTxTimeout = m_dwTxTimeout;

		if (dlg.DoModal() == IDOK)
		{
			m_dwRxTimeout = dlg.m_dwRxTimeout;
			m_dwTxTimeout = dlg.m_dwTxTimeout;
			GetView()->Output(_T("Timeout values set to Rx: %d, Tx: %d.\r\n"), m_dwRxTimeout, m_dwTxTimeout);
		}
	}	
}

void CSerialDoc::OnUpdateSetTimeout(CCmdUI* pCmdUI) 
{
	ASSERT_VALID(m_pCommFile);
	ASSERT_VALID(m_pCommConfig);

	if (m_pCommFile == NULL || m_pCommConfig == NULL)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(!m_pCommFile->IsOpen());
}
