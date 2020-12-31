// MessengerView.cpp : implementation of the CMessengerTree class
//

#include "stdafx.h"

#include "Messenger.h"
#include "MainFrm.h"

#include "MessengerDoc.h"
#include "MessengerTree.h"

#include "WNetEnum.h"

#include "MailMessage.h"
#include "MAILSLOT.H"	// Added by ClassView

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessengerTree

IMPLEMENT_DYNCREATE(CMessengerTree, CView)

BEGIN_MESSAGE_MAP(CMessengerTree, CView)
	//{{AFX_MSG_MAP(CMessengerTree)
	ON_WM_SIZE()
	ON_COMMAND(ID_TOOLS_REFRESH_NETWORK_TREE, OnToolsRefreshNetworkTree)
	ON_COMMAND(ID_TOOLS_SENDMESSAGE, OnSendButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessengerTree construction/destruction

CMessengerTree::CMessengerTree()
{
	// TODO: add construction code here

}

CMessengerTree::~CMessengerTree()
{
}

BOOL CMessengerTree::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CMessengerTree diagnostics

#ifdef _DEBUG
void CMessengerTree::AssertValid() const
{
	CView::AssertValid();
}

void CMessengerTree::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMessengerTree message handlers

void CMessengerTree::OnDraw(CDC* pDC) 
{
	pDC;
	// TODO: Add your specialized code here and/or call the base class
	
	
}

void CMessengerTree::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	int i;

	if(m_ctlImage.Create(16,16,ILC_MASK,0,2))
	{
		UINT bmpId [] = 
		{
			IDB_MWN_BITMAP,
			IDB_DOMAIN_BITMAP,
			IDB_COMPUTER_BITMAP,
			IDB_SHARE_BITMAP,
			IDB_PRINTER_BITMAP,
		};

		CBitmap	bmp;
		m_ctlImage.SetBkColor(GetSysColor(COLOR_WINDOW));

		for(i = 0;i < _countof(bmpId);i ++)
		{
			bmp.LoadBitmap(bmpId[i]);
			m_ctlImage.Add(&bmp,RGB(128,128,0));
			bmp.DeleteObject();
		}
	}
	
	
	DWORD dwTreeCtrlStyle = WS_VISIBLE | WS_CHILD | WS_TABSTOP |
		TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_DISABLEDRAGDROP;
		

	CRect rc;

	GetClientRect(&rc);
	m_ctlTree.Create(dwTreeCtrlStyle,rc,this,1);
	m_ctlTree.SetImageList(&m_ctlImage);
	m_ctlTree.EnableToolTips(TRUE);

//	PostMessage(WM_COMMAND,ID_TOOLS_REFRESH_NETWORK_TREE);
}

void CMessengerTree::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_ctlTree.GetSafeHwnd() != NULL)
	{
		m_ctlTree.MoveWindow(CRect(0,0,cx,cy));
	}
}


void CMessengerTree::OnToolsRefreshNetworkTree() 
{
	// TODO: Add your command handler code here
	m_ctlTree.Refresh();
}


void CMessengerTree::OnSendButton() 
{
	// TODO: Add your command handler code here
	CString text;
	CTreeCursor cursor;
	cursor = m_ctlTree.GetFirstSelectedItem();

	while(cursor)
	{
		text = cursor.GetText();
		if(!text.IsEmpty() && cursor.GetData() == RESOURCEDISPLAYTYPE_SERVER)
		{
			SendTo(text);
		}
		cursor = m_ctlTree.GetNextSelectedItem(cursor);
	}

	((CMainFrame*)AfxGetMainWnd())->AddMessageText();
	
}

void CMessengerTree::SendTo(LPCSTR pComputerName)
{
	CClientMailslot mailslot;
	if (!mailslot.Open(pComputerName,COMMUNICATION_SLOT))
	{
		AfxMessageBox("Fail create client mailslot");
		return;
	}
	
	//create the message
	SMailMessage msg;
	_tcscpy(msg.m_sMessage, ((CMainFrame*)AfxGetMainWnd())->GetMessageText());
	
	TCHAR sUserName[MAX_NAME_SIZE];
	DWORD dwUserNameSize = MAX_NAME_SIZE;
	if (GetUserName(sUserName, &dwUserNameSize))
		_tcscpy(msg.m_sSenderName, sUserName);
	else
		_tcscpy(msg.m_sSenderName, _T("unknown"));
	
	TCHAR sComputerName[MAX_NAME_SIZE];
	DWORD dwComputerNameSize = MAX_NAME_SIZE;
	if (GetComputerName(sComputerName, &dwComputerNameSize))
		_tcscpy(msg.m_sSenderMachine, sComputerName);
	else
		_tcscpy(msg.m_sSenderMachine, _T("unknown"));
	
	_tcscpy(msg.m_sTo,pComputerName);
	GetLocalTime(&msg.m_SentTime);
	
	//Send the message
	BeginWaitCursor();
	DWORD dwBytesWritten = 0;
	DWORD dwBytesToWrite = sizeof(SMailMessage);
	if (!mailslot.Write(&msg, dwBytesToWrite, &dwBytesWritten) ||
		(dwBytesToWrite != dwBytesWritten))
	{
		EndWaitCursor();
		AfxMessageBox("Fail send message");
		return;
	}
	EndWaitCursor();
}
