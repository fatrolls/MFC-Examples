// MessengerList.cpp : implementation file
//

#include "stdafx.h"
#include "messenger.h"
#include "MessengerList.h"
#include "TitledMenu.h"


#ifndef __AFXDISP_H__
	#include <afxdisp.h>
#endif



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMessengerList

IMPLEMENT_DYNCREATE(CMessengerList, CView)

CMessengerList::CMessengerList()
{
}

CMessengerList::~CMessengerList()
{
}


BEGIN_MESSAGE_MAP(CMessengerList, CView)
	//{{AFX_MSG_MAP(CMessengerList)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LIST_DELETE, OnListDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessengerList drawing


/////////////////////////////////////////////////////////////////////////////
// CMessengerList diagnostics

#ifdef _DEBUG
void CMessengerList::AssertValid() const
{
	CView::AssertValid();
}

void CMessengerList::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMessengerList message handlers

void CMessengerList::OnDraw(CDC* pDC) 
{
	pDC;
	// TODO: Add your specialized code here and/or call the base class
	
	
}

void CMessengerList::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	int i;
	DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_TABSTOP |
		LVS_REPORT | LVS_NOLABELWRAP;

	CRect rc;

	GetClientRect(&rc);
	m_ctlList.Create(dwStyle,rc,this,1);

	m_ctlList.AddColumn("From",0);

	m_ctlList.AddColumn("Subject",1);

	m_ctlList.AddColumn("Received",2);

	m_ctlList.SetExtendedStyles(LVS_EX_FULLROWSELECT);

	CMessengerApp *pApp = (CMessengerApp *)AfxGetApp();
	m_MailMessage.LoadDAO(pApp->m_DBPath);

	for(i = 0;i < m_MailMessage.GetSize();i ++)
	{
		AddItem(m_MailMessage[i]);
	}

	m_ctlList.SetColumnWidth( 0, LVSCW_AUTOSIZE );
	m_ctlList.SetColumnWidth( 1, LVSCW_AUTOSIZE );
	m_ctlList.SetColumnWidth( 2, LVSCW_AUTOSIZE );

	//Create the server mailslot to listen for incoming messages
	if (!m_ServerMailslot.Open(COMMUNICATION_SLOT))
	{
		AfxMessageBox("Fail create mail slot");
	}

	//Create the timer to check for new mail
	m_nTimerID = SetTimer(1, 2000, NULL);
}

void CMessengerList::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_ctlList.GetSafeHwnd() != NULL)
	{
		m_ctlList.MoveWindow(CRect(0,0,cx,cy));
	}
	
}

void CMessengerList::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnTimer(nIDEvent);

	//Read all the messages waiting in 
	//the server mailslot
	while (m_ServerMailslot.MessageWaiting())
	{
		DWORD dwMsgSize = m_ServerMailslot.SizeOfWaitingMessage();
		BYTE* pMsg = new BYTE[dwMsgSize];
		
		DWORD dwNumberOfBytesRead = 0;
		if (m_ServerMailslot.Read(pMsg, dwMsgSize, &dwNumberOfBytesRead))
		{
			if (dwNumberOfBytesRead == sizeof(SMailMessage))
			{
				SMailMessage msg;

				memcpy(&msg, pMsg, dwNumberOfBytesRead);

				AddItem(msg);
				m_MailMessage.Add(msg);

				MessageBeep(MB_ICONEXCLAMATION);
			}
		}
		delete []pMsg;
	}

}

void CMessengerList::AddItem(SMailMessage &msg)
{
	COleDateTime oleTime(msg.m_SentTime);
				
	m_ctlList.AddItem(0,0,msg.m_sSenderName);
	m_ctlList.AddItem(0,1,msg.m_sMessage);
	m_ctlList.AddItem(0,2,oleTime.Format());
}


void CMessengerList::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
  //Don't forget to destroy the timer
	KillTimer(m_nTimerID);

	CMessengerApp *pApp = (CMessengerApp *)AfxGetApp();
	m_MailMessage.SaveDAO(pApp->m_DBPath);
}

BOOL CMessengerList::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	// CG: This block was added by the Pop-up Menu component
	{
		// Shift+F10: show pop-up menu.
		if ((((pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN) && // If we hit a key and
			(pMsg->wParam == VK_F10) && (GetKeyState(VK_SHIFT) & ~1)) != 0) ||	// it's Shift+F10 OR
			(pMsg->message == WM_CONTEXTMENU) ||
			(pMsg->message == WM_RBUTTONDOWN))									// Natural keyboard key
		{
			CPoint point;
			GetCursorPos(&point);

			OnContextMenu(NULL, point);

			return TRUE;
		}
	}
	
	return CView::PreTranslateMessage(pMsg);
}

void CMessengerList::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	pWnd;
	// TODO: Add your message handler code here
	
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_LIST));
	
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	
	// call the helper function to setup this as a titled popup menu
	AddMenuTitle(pPopup,"List menu   ");
	
	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
	
}

void CMessengerList::OnListDelete() 
{
	// TODO: Add your command handler code here
	int	nCount = m_ctlList.GetItemCount();

	while(nCount)
	{
		if (m_ctlList.GetItemState(nCount,LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_ctlList.DeleteItem(nCount);
		}
		nCount --;
	}
}
