// MessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imapclient.h"
#include "MessageDlg.h"

#include "ut_strop.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg dialog


CMessageDlg::CMessageDlg(CWnd* pParent, long lUID, CUT_IMAP4Client& imapc)
	: CDialog(CMessageDlg::IDD, pParent), m_lUID(lUID), m_imapc(imapc)
{
	//{{AFX_DATA_INIT(CMessageDlg)
	m_sMessageBody = _T("");
	//}}AFX_DATA_INIT
}


void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CMessageDlg)
	DDX_Control(pDX, IDC_HEADER_LIST, m_listHeaders);
	DDX_Control(pDX, IDC_MESSAGE_ATTACHMENT_LIST, m_comboAttachments);
	DDX_Text(pDX, IDC_MESSAGE_BODY, m_sMessageBody);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialog)
	//{{AFX_MSG_MAP(CMessageDlg)
	ON_BN_CLICKED(IDC_MESSAGE_SAVE_ATTACHMENT, OnMessageSaveAttachment)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg message handlers

BOOL CMessageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LoadMessage();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMessageDlg::LoadMessage()
{
	CString     s;
    CUT_MsgData    *ptrMsgData;
	CEdit       *pEdit = static_cast<CEdit*>(GetDlgItem(IDC_MESSAGE_BODY));
	
	s.Format(_T("%d"), m_lUID);
	m_imapc.MessageFetch(s, MSG_BODY, TRUE, TRUE);
	
	for (int i = 0; i < m_imapc.GetMsgDataListSize(); i++) {
                    
        if(m_imapc.GetMsgDataListItem(i, ptrMsgData) != UTE_SUCCESS)
            break;
		
		if (ptrMsgData->m_lUID == m_lUID) {
			
			CUT_Msg msg;
			msg.LoadMessage(*ptrMsgData->m_ptrData);
			
			pEdit->SetWindowText(_T(""));
			pEdit->SetSel(pEdit->GetWindowTextLength(), pEdit->GetWindowTextLength());

			_TCHAR *szBody = new _TCHAR[MAX_PATH];
			size_t size;
			int result = msg.GetMessageBody(szBody, MAX_PATH, &size);
			if(result == UTE_SUCCESS) {
				pEdit->ReplaceSel(szBody);
			}
			else {
				if(result == UTE_BUFFER_TOO_SHORT) {
					delete [] szBody;
					szBody = new _TCHAR[size];
					msg.GetMessageBody(szBody, size, &size);
					pEdit->ReplaceSel(szBody);
				}
			}
			delete [] szBody;


            // Fill headers
            _TCHAR    hBuf[1024];
			_TCHAR	  nameBuf[1024];

			for( int nHeader = UTM_MESSAGE_ID; nHeader < UTM_MAX_FIELD; nHeader++) 
				for(int j = 0; j < msg.GetHeaderCount((HeaderFieldID)nHeader); j++) {
					if((HeaderFieldID)nHeader == UTM_CUSTOM_FIELD) 
						msg.GetCustomFieldName(nameBuf, 1024, j, &size);
					else 
						msg.GetFieldName(nameBuf, 1024, (HeaderFieldID)nHeader, &size);

					msg.GetHeaderByType(hBuf, 1024, (HeaderFieldID)nHeader, j, &size);

					_tcscat(nameBuf, hBuf);
					m_listHeaders.AddString(nameBuf);

				}


			if (msg.GetAttachmentNumber() > 0) {
			
				// Add the list of all attachments to the combo box
				//
				
				CString sName, sType;				
				for (int j = 0; j < msg.GetAttachmentNumber(); j++) {

					msg.GetAttachmentInfo(j, sName.GetBuffer(MAX_PATH + 1), MAX_PATH,
						sType.GetBuffer(MAX_PATH + 1), MAX_PATH);

					sName.ReleaseBuffer();
					sType.ReleaseBuffer();				
				
					m_comboAttachments.AddString(sName);
				}
			}
			else {

				GetDlgItem(IDC_MESSAGE_SAVE_ATTACHMENT)->EnableWindow(FALSE);
				m_comboAttachments.EnableWindow(FALSE);
			}

			break;
		}
	}
}

void CMessageDlg::OnMessageSaveAttachment() 
{


	
}

void CMessageDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	
	CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(IDC_MESSAGE_BODY));
	if (pEdit != NULL) {
/*
		CRect rect;
		pEdit->GetWindowRect(&rect);
		pEdit->SetWindowPos(&CWnd::wndTop, rect.left, rect.top, cx - 7, cy - 7, SWP_SHOWWINDOW);
*/
	}
}

#pragma warning ( pop )