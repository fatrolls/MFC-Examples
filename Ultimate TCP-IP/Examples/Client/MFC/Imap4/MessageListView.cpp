// MessageListView.cpp : implementation file
//

#include "stdafx.h"
#include "IMAPClient.h"
#include "IMAPClientDoc.h"
#include "MainFrame.h"
#include "MessageListView.h"

#include "MessageFolderView.h"
#include "MessageDlg.h"

#include "ut_strop.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageListView

IMPLEMENT_DYNCREATE(CMessageListView, CListView)

CMessageListView::CMessageListView()
{
}

CMessageListView::~CMessageListView()
{
}


BEGIN_MESSAGE_MAP(CMessageListView, CListView)
	//{{AFX_MSG_MAP(CMessageListView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDoubleClickItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageListView drawing

void CMessageListView::OnDraw(CDC* /* pDC */)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMessageListView diagnostics

#ifdef _DEBUG
void CMessageListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMessageListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMessageListView message handlers


void CMessageListView::OnUpdate(CView* /* pSender */, LPARAM lHint, CObject* /* pHint */) 
{
	if (lHint == IDN_UPDATE_MESSAGE_LIST) {

		CWaitCursor w;
		
		CUT_IMAP4Client& imapc = GetAppFrameWnd()->m_imapClient;
		CListCtrl& list = GetListCtrl();

		imapc.MailBoxSelect(GetAppFrameWnd()->GetMessageFolderView()->GetSelectedFolder());
		imapc.MessageFetch("1:*", MSG_BODY_HEADER);

		list.DeleteAllItems();

    CUT_MsgData    *ptrMsgData;
	for (int i = 0; i < imapc.GetMsgDataListSize(); i++) {
                    
        if(imapc.GetMsgDataListItem(i, ptrMsgData) != UTE_SUCCESS)
            break;

        AddMessageEntry(ptrMsgData);
        }
	}	
}

void CMessageListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	CListCtrl& list = GetListCtrl();

	list.ModifyStyle(NULL, LVS_REPORT | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	
	list.InsertColumn(0, _T("UID"), LVCFMT_LEFT, 40);
	list.InsertColumn(1, _T("Flags"), LVCFMT_LEFT, 60);
	list.InsertColumn(2, _T("From"), LVCFMT_LEFT, 150);
	list.InsertColumn(3, _T("Subject"), LVCFMT_LEFT, 200);
	list.InsertColumn(4, _T("Size"), LVCFMT_LEFT, 50);
	list.InsertColumn(5, _T("Date"), LVCFMT_LEFT, 150);
}

void CMessageListView::AddMessageEntry(CUT_MsgData* pMessageData)
{
	CListCtrl& list = GetListCtrl();

	CUT_Msg msg;
	CUT_HeaderEncoding enc;

	if(pMessageData->m_ptrData != NULL) {
		msg.LoadMessage(*pMessageData->m_ptrData);

		CString sMessageInfo;
		sMessageInfo.Format(_T("%d"), pMessageData->m_lUID);
		int nItem = list.InsertItem(list.GetItemCount(), sMessageInfo, 0);

		sMessageInfo.Empty();
		if (pMessageData->m_lFlags & SYS_FLAG_SEEN)
			sMessageInfo += _T("S");
		else 
			sMessageInfo += _T("_");

		if (pMessageData->m_lFlags & SYS_FLAG_ANSWERED)
			sMessageInfo += _T("A");
		else 
			sMessageInfo += _T("_");

		if (pMessageData->m_lFlags & SYS_FLAG_FLAGGED)
			sMessageInfo += _T("F");
		else 
			sMessageInfo += _T("_");

		if (pMessageData->m_lFlags & SYS_FLAG_DELETED)
			sMessageInfo += _T("D");
		else 
			sMessageInfo += _T("_");

		if (pMessageData->m_lFlags & SYS_FLAG_DRAFT)
			sMessageInfo += _T("D");
		else 
			sMessageInfo += _T("_");

		if (pMessageData->m_lFlags & SYS_FLAG_RECENT)
			sMessageInfo += _T("R");
		else 
			sMessageInfo += _T("_");
			
		if (pMessageData->m_lFlags & SYS_FLAG_SPECIAL)
			sMessageInfo += _T("*");
		else 
			sMessageInfo += _T("_");

		list.SetItem(nItem, 1, LVIF_TEXT, sMessageInfo, 0, 0, 0, 0);

		// v4.2 charset now a char*, not a ref to an LPCSTR 
		char szCharSet[80];
		msg.DecodeHeader(UTM_FROM, szCharSet);
		msg.DecodeHeader(UTM_SUBJECT, szCharSet);

		msg.GetHeaderByType(UTM_FROM, sMessageInfo.GetBuffer(128), 127);
		list.SetItem(nItem, 2, LVIF_TEXT, sMessageInfo, 0, 0, 0, 0);

		msg.GetHeaderByType(UTM_SUBJECT, sMessageInfo.GetBuffer(128), 127);
		list.SetItem(nItem, 3, LVIF_TEXT, sMessageInfo, 0, 0, 0, 0);

		sMessageInfo.Format(_T("%d KB"), pMessageData->m_lSize / 1024);
		list.SetItem(nItem, 4, LVIF_TEXT, sMessageInfo, 0, 0, 0, 0);

		// v4.2 message data now returned with _TCHAR
		list.SetItem(nItem, 5, LVIF_TEXT, pMessageData->m_szDateTime, 0, 0, 0, 0);
	}
}

void CMessageListView::OnDoubleClickItem(NMHDR* /* pNMHDR */, LRESULT* pResult) 
{
	// Relay the message to the message list view
	LVHITTESTINFO lvhti;

	GetCursorPos(&lvhti.pt);
	ScreenToClient(&lvhti.pt);

	int nItem = GetListCtrl().HitTest(&lvhti);
	if (nItem != -1 && lvhti.flags & LVHT_ONITEMLABEL) {
		
		CWaitCursor w;
		CString s;

		GetListCtrl().GetItemText(nItem, 0, s.GetBuffer(32), 31);
		s.ReleaseBuffer();
		
		CMessageDlg(this, _ttol(s), GetAppFrameWnd()->m_imapClient).DoModal();
	}

	*pResult = 0;
}
