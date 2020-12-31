// TransferDlg.cpp : implementation file
//

#include "stdafx.h"
#include "serial.h"
#include "TransferDlg.h"

#include "OXSCFILE.H"
#include "OXCRCCHK.H"

#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDM_START_SENDING	(WM_USER + 10)
#define IDM_START_RECEIVING (WM_USER + 11)

//#define __USE_MESSAGES
//
// Uncomment the above directive if you wish MESSAGE-ing between the two
// sides enabled.  Obviosly a "Real" protocol would implement such a device but this 
// application is only intended as a sample and hence does not cover advanced
// topics like synchronization.  Popular protocols are Z-modem, Y-modem, and X-modem.
//
//
#define MESSAGE_TYPE		UINT
#define MESSAGE_SIZE		sizeof(UINT)
#define MESSAGE_NONE		(0x0000)
#define MESSAGE_CANCEL		(0x0001)
#define MESSAGE_STOPPED		(0x0002)
#define MESSAGE_WANTSEND	(0x0004)
#define MESSAGE_OKAYSEND	(0x0008)

/////////////////////////////////////////////////////////////////////////////
// CTransferDlg dialog

CTransferDlg::CTransferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransferDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransferDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pFile = NULL;
	m_pCommFile = NULL;

	m_bSending = TRUE;
	m_bCancelPressed = FALSE;
}

void CTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransferDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTransferDlg, CDialog)
	//{{AFX_MSG_MAP(CTransferDlg)
	//}}AFX_MSG_MAP
	ON_MESSAGE(IDM_START_SENDING, OnStartSending)
	ON_MESSAGE(IDM_START_RECEIVING, OnStartReceiving)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransferDlg message handlers

BOOL CTransferDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_TRANSFER_TEXT, m_sMessage);

	//
	// Start either Receivng or Sending data
	//
	if (m_bSending)
		PostMessage(IDM_START_SENDING);
	else 
		PostMessage(IDM_START_RECEIVING);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LONG CTransferDlg::OnStartReceiving(WPARAM, LPARAM)
{
	//
	//
	// This function (message handler) will begin receiving data on the
	// COMM port. This function is not multi-threaded, instead it uses
	// the global PumpMessages function to maintain the Applications message
	// pump.  This function should be implemented as another thread, but, as
	// mentioned before, this is left up to you to implement.
	//
	// The function will wait for incoming data to appear in the Receive queue.
	// Once data is found it begins receiving it by first, reading the filesize,
	// next the filename, and then the file checksum. After all this
	// the file is read in 1024 chunks until complete. Again, this is a very simple
	// protocol. You should investigate Z-modem, Y-modem and other popular
	// protocols.
	//
	// The file checksum is only checked once at the end of the transmission. This is
	// done for simplicity.  Idealy, you would check the checksum of each transmitted
	// packet. Thus, if the checksum of a packed failed you could simply ask to have
	// it transmitted instead of having the whole file re-transmitted (as the case
	// would be in this scenario).
	//
	// On completion, CDialog::OnOK or CDialog::OnCancel is called to close the dialog
	// window.
	//
	
	ASSERT_VALID(m_pCommFile);

	if (m_pCommFile == NULL)
	{
		CDialog::OnCancel();
		return -1;
	}
	ShowWindow(SW_SHOW);

	CString sNewFilename = GetAppDir();
	CFile f;
	BYTE bBuffer[1024];
	UINT nBytesReceived = 0;
	UINT nTotalBytesReceived = 0;

	DWORD dwFileSize;
	TCHAR szFilename[MAX_PATH];
	DWORD dwChecksum;

	TRY
	{
		// Wait
		m_sMessage.Format(_T("Waiting for incoming files..."));
		SetDlgItemText(IDC_TRANSFER_TEXT, m_sMessage);

		while (m_pCommFile->IsRxQueueEmpty() && !m_bCancelPressed)
		{
			PumpMessages();
		}

		if (m_bCancelPressed)
		{
			CDialog::OnCancel();
			return 0;
		}

		// first: read the filesize
		m_pCommFile->Read(&dwFileSize, sizeof(dwFileSize));

		// second: read the filename
		m_pCommFile->Read(szFilename, sizeof(szFilename));

		// display message about incoming file
		m_sMessage.Format(_T("file %s (%d bytes long) detected.\r\n"), szFilename, dwFileSize);
		SetDlgItemText(IDC_TRANSFER_TEXT, m_sMessage);

		// third: read the checksum
		m_pCommFile->Read(&dwChecksum, sizeof(dwChecksum));
				
		CProgressCtrl* pProg = (CProgressCtrl*) GetDlgItem(IDC_TRANSFER_PROGRESS);
		ASSERT_VALID(pProg);

		pProg->SetRange(0, 100);
		pProg->SetPos(0);

		// fourth: read the incoming data (streamed into a file object)
		sNewFilename += _T('\\');
		sNewFilename += szFilename;
		if (!f.Open(sNewFilename, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite | CFile::shareDenyRead))
		{
			m_sMessage.Format(_T("Error: Unable to create the new file."));
		}
		else
		{
			TRY
			{
				//
				// Keep reading the file until either the user cancels or 
				// the file has finsihed.
				//
				while ((nTotalBytesReceived < dwFileSize) && !m_bCancelPressed)
				{
					nBytesReceived = m_pCommFile->Read(bBuffer, sizeof(bBuffer));
					nTotalBytesReceived += nBytesReceived;
					
					m_sMessage.Format(_T("%s\n%d of %d bytes received."), sNewFilename, nTotalBytesReceived, dwFileSize);
					SetDlgItemText(IDC_TRANSFER_TEXT, m_sMessage);

					f.Write(bBuffer, nBytesReceived);
					
					pProg->SetPos(((nTotalBytesReceived * 100 / (UINT) dwFileSize)));
					PumpMessages();
				}

				if (m_bCancelPressed)
				{
#ifdef __USE_MESSAGES
					// the transfer has been cancelled; wait for the other side to
					// acknowledge receipt of this message
					MESSAGE_TYPE message = MESSAGE_CANCEL;
					m_pCommFile->Write(&message, MESSAGE_SIZE);
					do
					{
						m_pCommFile->Read(&message, MESSAGE_SIZE);
					}
					while (message != MESSAGE_STOPPED);
#endif

					m_sMessage.Format(_T("Transfer was cancelled\r\n"));

					CDialog::OnCancel();
					return 0;
				}

				f.Close();
			}
			CATCH(CFileException, e)
			{
				TCHAR szError[256];
				e->GetErrorMessage(szError, sizeof(szError));

				m_sMessage.Format(_T("Error: %s\r\n"), szError);
			}
			END_CATCH
		}
	}
	CATCH(COXSerialCommException, e)
	{
		m_sMessage.Format(_T("An Exception occurred (%d)\r\n"), e->m_cause);
	}
	END_CATCH

	// perform simple integrity check on the file
	if (nTotalBytesReceived == dwFileSize)
	{
		COXCheckSum32 checksum;
		DWORD dwNewChecksum;
		TRY
		{
			dwNewChecksum = checksum.CalculateFile(sNewFilename);
			TRACE(_T("%s has checksum of %d\n"), sNewFilename, dwNewChecksum);
		}
		CATCH(CFileException, e)
		{
			m_sMessage.Format(_T("%s successfully received\r\nChecksum test failed.\r\n"), sNewFilename);
			CDialog::OnOK();
			return 0;
		}
		END_CATCH

		if (dwChecksum == dwNewChecksum)
		{
			m_sMessage.Format(_T("%s successfully received\r\nFile passed integrity check (%d)\r\n"), sNewFilename, dwNewChecksum);
		}
		else
		{
			m_sMessage.Format(_T("%s successfully received\r\nFile failed integrity check (remote:%d; local:%d)\r\n"), sNewFilename, dwChecksum, dwNewChecksum);
		}
	}
	else
	{
		m_sMessage.Format(_T("%s was not properly received (%d bytes not received)\r\n"), sNewFilename, dwFileSize - nTotalBytesReceived);
	}


	CDialog::OnOK();

	return 0;
}

LONG CTransferDlg::OnStartSending(WPARAM, LPARAM)
{
	// 
	//
	// The function will begin sending the file over the COMM port. It assumes that
	// the awaiting client is ready to receive. Really however, A 
	// "Are you ready to receive" message should be send to the client to ensure
	// the transfer works properly. In this application if the user isn't waiting to
	// receive a file, the data will appear in his/her "Terminal" window.
	//
	// This function should run in a thread. Instead, for simplicity's sake it uses the
	// simple PumpMessage function to maintain the application's message pump.
	//
	// See CTransferDlg::OnStartReceiving for more information about the protocol used
	// to transfer files.
	//

	ASSERT_VALID(m_pFile);
	ASSERT_VALID(m_pCommFile);

	if (m_pFile == NULL || m_pCommFile == NULL || m_sFilename.IsEmpty())
	{
		CDialog::OnCancel();
		return -1;
	}

	ShowWindow(SW_SHOW);

	CProgressCtrl* pProg = (CProgressCtrl*) GetDlgItem(IDC_TRANSFER_PROGRESS);
	ASSERT_VALID(pProg);

	DWORD dwTotal = 0;
	DWORD dwCount = 0;

	// CFile object m_pFile already open
	COXCheckSum32 checksum;
	DWORD dwChecksum;
	TRY
	{
		// calculate the file checksum
		dwChecksum = checksum.CalculateFile(m_pFile);
		m_pFile->SeekToBegin();

		TRACE(_T("%s has checksum of %d\n"), m_sFilename, dwChecksum);
	}
	CATCH(CFileException, e)
	{
		m_sMessage.Format(_T("Fatal Error: Unable to calculate file checksum\r\n"));
		TRACE(_T("Unable to calculate file checksum\r\n"));
		return -1;
	}
	END_CATCH
	
	BYTE bBuffer[1024];
	TCHAR szFilename[MAX_PATH];

	lstrcpy(szFilename, (LPCTSTR) m_sFilename);

	// first: send number of bytes this file is
	DWORD dwFileSize = m_pFile->GetLength();
	m_pCommFile->Write(&dwFileSize, sizeof(DWORD));

	// second: send filename
	m_pCommFile->Write(&szFilename, sizeof(szFilename));

	// third: send checksum
	m_pCommFile->Write(&dwChecksum, sizeof(dwChecksum));
	
	pProg->SetRange(0, 100);
	pProg->SetPos(0);

	// fourth: write the file
	while ((dwCount = m_pFile->Read(bBuffer, sizeof(bBuffer))) != 0 && !m_bCancelPressed)
	{
		dwTotal += dwCount;
		m_pCommFile->Write(bBuffer, dwCount);

		m_sMessage.Format(_T("%s\n%d of %d bytes sent"), m_sFilename, dwTotal, dwFileSize);
		SetDlgItemText(IDC_TRANSFER_TEXT, m_sMessage);

		pProg->SetPos(((dwTotal * 100 / dwFileSize)));

#ifdef __USE_MESSAGES
		m_pCommFile->Read(&message, MESSAGE_SIZE);
		if (message == MESSAGE_CANCEL)
		{
			m_bCancelPressed = TRUE;
			message = MESSAGE_STOPPED;
			m_pCommFile->Write(&message, MESSAGE_SIZE);
			break;
		}
#endif

		PumpMessages();
	}

#ifdef __USE_MESSAGES
	if (message == MESSAGE_CANCEL)
		m_sMessage.Format(_T("Other side cancelled transfer; %d of %d bytes sent\r\n"), dwTotal, dwFileSize);
	else
		m_sMessage.Format(_T("Finished. Successfully sent %d byte(s).\r\n"), dwTotal);
#else
	m_sMessage.Format(_T("Finished. Successfully sent %d byte(s).\r\n"), dwTotal);
#endif

	if (m_bCancelPressed)
		CDialog::OnCancel();
	else
		CDialog::OnOK();

	return 0;
}

void CTransferDlg::OnCancel() 
{
	// User has pressed the cancel button; Disable the button and set
	// flag
	//
	m_bCancelPressed = TRUE;
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
}
