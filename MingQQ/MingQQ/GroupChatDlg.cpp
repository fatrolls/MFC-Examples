#include "StdAfx.h"
#include "GroupChatDlg.h"

CGroupChatDlg::CGroupChatDlg(void)
{
	m_lpQQClient = NULL;
	m_lpFaceList = NULL;
	m_lpCascadeWinManager = NULL;
	m_hMainDlg = NULL;
	m_nGroupCode = 0;

	m_hDlgIcon = m_hDlgSmallIcon = NULL;
	m_fontGroupNameLink = NULL;
	m_hRBtnDownWnd = NULL;
	memset(&m_ptRBtnDown, 0, sizeof(m_ptRBtnDown));
	m_pLastImageOle = NULL;
	m_cxPicBarDlg = 122;
	m_cyPicBarDlg = 24;

	m_nGroupId = m_nGroupNumber = 0;
	m_nUserNumber = 0;
	m_strGroupName = _T("群名称");
	m_strUserName = _T("");
	m_nMemberCnt = m_nOnlineMemberCnt = 0;

	m_dwThreadId = 0;
}

CGroupChatDlg::~CGroupChatDlg(void)
{
}

BOOL CGroupChatDlg::PreTranslateMessage(MSG* pMsg)
{
	if (::GetForegroundWindow() == m_hWnd && !m_Accelerator.IsNull() && 
		m_Accelerator.TranslateAccelerator(m_hWnd, pMsg))
		return TRUE;

	if (pMsg->hwnd == m_richRecv.m_hWnd || pMsg->hwnd == m_richSend.m_hWnd)
	{
		if (pMsg->message == WM_MOUSEMOVE)			// 发送/接收文本框的鼠标移动消息
		{
			if (OnRichEdit_MouseMove(pMsg))
				return TRUE;
		}
		else if (pMsg->message == WM_LBUTTONDBLCLK) // 发送/接收文本框的鼠标双击消息
		{
			if (OnRichEdit_LBtnDblClk(pMsg))
				return TRUE;
		}
		else if (pMsg->message == WM_RBUTTONDOWN)	// 发送/接收文本框的鼠标右键按下消息
		{
			if (OnRichEdit_RBtnDown(pMsg))
				return TRUE;
		}

		if ((pMsg->hwnd == m_richSend.m_hWnd) && (pMsg->message == WM_KEYDOWN) 
			&& (pMsg->wParam == 'V') && (pMsg->lParam & VK_CONTROL))	// 发送文本框的Ctrl+V消息
		{
			m_richSend.PasteSpecial(CF_TEXT);
			return TRUE;
		}
	}

	return CWindow::IsDialogMessage(pMsg);
}

// 接收群消息
void CGroupChatDlg::OnRecvMsg(UINT nGroupCode, UINT nMsgId)
{
	if (NULL == m_lpQQClient || m_nGroupCode != nGroupCode)
		return;

	if (::GetForegroundWindow() != m_hWnd)
		FlashWindowEx(m_hWnd, 3);

	if (nMsgId == 0)
	{
		CMessageList * lpMsgList = m_lpQQClient->GetMessageList();
		if (lpMsgList != NULL)
		{
			CMessageSender * lpMsgSender = lpMsgList->GetMsgSender(QQ_MSG_TYPE_GROUP, nGroupCode);
			if (lpMsgSender != NULL)
			{
				int nMsgCnt = lpMsgSender->GetMsgCount();
				for (int i = 0; i < nMsgCnt; i++)
				{
					CGroupMessage * lpGroupMsg = lpMsgSender->GetGroupMsg(i);
					if (lpGroupMsg != NULL)
					{
						AddMsgToRecvEdit(lpGroupMsg);
					}
				}
				lpMsgList->DelMsgSender(QQ_MSG_TYPE_GROUP, nGroupCode);
				::PostMessage(m_hMainDlg, WM_DEL_MSG_SENDER, QQ_MSG_TYPE_GROUP, nGroupCode);
			}
		}
	}
	else
	{
		CMessageList * lpMsgList = m_lpQQClient->GetMessageList();
		if (lpMsgList != NULL)
		{
			CMessageSender * lpMsgSender = lpMsgList->GetMsgSender(QQ_MSG_TYPE_GROUP, nGroupCode);
			if (lpMsgSender != NULL)
			{
				CGroupMessage * lpGroupMsg = lpMsgSender->GetGroupMsgById(nMsgId);
				if (lpGroupMsg != NULL)
				{
					AddMsgToRecvEdit(lpGroupMsg);
					lpMsgSender->DelMsgById(nMsgId);
				}

				if (lpMsgSender->GetMsgCount() <= 0)
					lpMsgList->DelMsgSender(QQ_MSG_TYPE_GROUP, nGroupCode);
			}
		}
	}
}

// 更新群信息
void CGroupChatDlg::OnUpdateGroupInfo()
{
	UpdateData();						// 更新信息

	UpdateDlgTitle();					// 更新对话框标题
	UpdateGroupNameCtrl();				// 更新群名称控件
	UpdateGroupMemo();					// 更新群公告
	UpdateGroupMemberList();			// 更新群成员列表
}

// 更新群号码
void CGroupChatDlg::OnUpdateGroupNumber()
{
	UpdateData();						// 更新信息
	UpdateGroupNameCtrl();				// 更新群名称控件
}

// 更新群头像
void CGroupChatDlg::OnUpdateGroupHeadPic()
{
	tstring strFileName;
	if (m_lpQQClient != NULL && m_nGroupNumber != 0)
		strFileName = m_lpQQClient->GetGroupHeadPicFullName(m_nGroupNumber);
	if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefGroupHeadPic.jpg");
	m_picHead.SetBitmap(strFileName.c_str());
	m_picHead.Invalidate();
}

// 更新群成员号码
void CGroupChatDlg::OnUpdateGMemberNumber(WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = (UINT)lParam;

	CBuddyInfo * lpBuddyInfo = GetGMemberInfoPtr(nQQUin);
	if (NULL == lpBuddyInfo || 0 == lpBuddyInfo->m_nQQNum)
		return;

	CString strNickName, strText, strFileName;

	if (!lpBuddyInfo->m_strGroupCard.empty())
		strNickName = lpBuddyInfo->m_strGroupCard.c_str();
	else
		strNickName = lpBuddyInfo->m_strNickName.c_str();

	strText.Format(_T("%s(%u)"), strNickName, lpBuddyInfo->m_nQQNum);

	BOOL bGray = lpBuddyInfo->m_nStatus != QQ_STATUS_OFFLINE ? FALSE : TRUE;
	strFileName = m_lpQQClient->GetSessHeadPicFullName(lpBuddyInfo->m_nQQNum).c_str();

	int nItem = FindMemberListByUin(nQQUin);
	if (nItem != -1)
	{
		m_ListCtrl.SetItemText(nItem, 0, strText);
		if (ZYM::CPath::IsFileExist(strFileName))
			m_ListCtrl.SetItemImage(nItem, 0, strFileName, bGray);
	}
}

// 更新群成员头像
void CGroupChatDlg::OnUpdateGMemberHeadPic(WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = (UINT)lParam;

	CBuddyInfo * lpBuddyInfo = GetGMemberInfoPtr(nQQUin);
	if (NULL == lpBuddyInfo || 0 == lpBuddyInfo->m_nQQNum)
		return;

	BOOL bGray = lpBuddyInfo->m_nStatus != QQ_STATUS_OFFLINE ? FALSE : TRUE;

	CString strFileName = m_lpQQClient->GetSessHeadPicFullName(lpBuddyInfo->m_nQQNum).c_str();
	if (!ZYM::CPath::IsFileExist(strFileName))
		return;
	
	int nItem = FindMemberListByUin(nQQUin);
	if (nItem != -1)
	{
		m_ListCtrl.SetItemImage(nItem, 0, strFileName, bGray);
	}
}

BOOL CGroupChatDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	m_lpCascadeWinManager->Add(m_hWnd, 592, 511);

	// set icons
	m_hDlgIcon = AtlLoadIconImage(IDI_GROUPCHATDLG_32, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(m_hDlgIcon, TRUE);
	m_hDlgSmallIcon = AtlLoadIconImage(IDI_GROUPCHATDLG_16, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(m_hDlgSmallIcon, FALSE);

	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);

	CGroupInfo * lpGroupInfo = GetGroupInfoPtr();
	if (lpGroupInfo != NULL)
	{
		if (!lpGroupInfo->IsHasGroupInfo())		// 更新群信息
			m_lpQQClient->UpdateGroupInfo(m_nGroupCode);

		if (!lpGroupInfo->IsHasGroupNumber())	// 更新群号码
		{
			m_lpQQClient->UpdateGroupNum(m_nGroupCode);
		}
		else									// 更新群头像
		{
			if (m_lpQQClient->IsNeedUpdateGroupHeadPic(lpGroupInfo->m_nGroupNumber))
				m_lpQQClient->UpdateGroupHeadPic(m_nGroupCode, lpGroupInfo->m_nGroupNumber);
		}
	}

	UpdateData();
	Init();

	PostMessage(WM_SETDLGINITFOCUS, 0, 0);		// 设置对话框初始焦点
	SetTimer(1001, 300, NULL);

	return TRUE;
}

BOOL CGroupChatDlg::OnCopyData(CWindow wnd, PCOPYDATASTRUCT pCopyDataStruct)
{
	if (NULL == pCopyDataStruct)
		return FALSE;

	switch (pCopyDataStruct->dwData)
	{
	case IPC_CODE_MSGLOG_PASTE:			// 消息记录浏览窗口粘贴消息
		{
			if (pCopyDataStruct->lpData != NULL && pCopyDataStruct->cbData > 0)
				AddMsgToSendEdit((LPCTSTR)pCopyDataStruct->lpData);
		}
		break;

	case IPC_CODE_MSGLOG_EXIT:			// 消息记录浏览窗口退出消息
		{
			m_tbMid.SetItemCheckState(11, FALSE);
			m_tbMid.Invalidate();
		}
		break;
	}

	return TRUE;
}

void CGroupChatDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	m_SkinMenu.OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CGroupChatDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_SkinMenu.OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CGroupChatDlg::OnGetMinMaxInfo(LPMINMAXINFO lpMMI)
{
	lpMMI->ptMinTrackSize.x = 592;
	lpMMI->ptMinTrackSize.y = 511;
}

void CGroupChatDlg::OnMove(CPoint ptPos)
{
	SetMsgHandled(FALSE);

	m_lpCascadeWinManager->SetPos(m_hWnd, ptPos.x, ptPos.y);
}

void CGroupChatDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);

	CRect rcClient;
	GetClientRect(&rcClient);

	if (m_picAD.IsWindow())
		m_picAD.MoveWindow(rcClient.right-202, rcClient.top+44, 200, 42);

	if (m_staMemoTitle.IsWindow())
		m_staMemoTitle.MoveWindow(rcClient.right-201, 86, 198, 24);

	if (m_staMemberTitle.IsWindow())
		m_staMemberTitle.MoveWindow(rcClient.right-201, 274, 198, 24);

	if (m_edtMemo.IsWindow())
		m_edtMemo.MoveWindow(rcClient.right-201, 110, 198, 164);

	if (m_btnClose.IsWindow())
		m_btnClose.MoveWindow(rcClient.right-366, rcClient.bottom-5-22, 69, 22);

	if (m_btnSend.IsWindow())
		m_btnSend.MoveWindow(rcClient.right-292, rcClient.bottom-5-22, 64, 22);

	if (m_btnArrow.IsWindow())
		m_btnArrow.MoveWindow(rcClient.right-209-19, rcClient.bottom-5-22, 19, 22);

// 	if (m_tbTop.IsWindow())
// 		m_tbTop.MoveWindow(3, 45, 383, 44);

	if (m_tbMid.IsWindow())
		m_tbMid.MoveWindow(1, rcClient.bottom-140, rcClient.Width()-1-209, 27);

	if (m_richRecv.IsWindow())
	{
		if (!::IsWindowVisible(m_FontSelDlg.m_hWnd))
			m_richRecv.MoveWindow(6, rcClient.top+44+44, rcClient.Width()-6-209, rcClient.Height()-228);
		else
			m_richRecv.MoveWindow(6, rcClient.top+44+44, rcClient.Width()-6-209, rcClient.Height()-228-32);
	}

	if (m_richSend.IsWindow())
		m_richSend.MoveWindow(6, rcClient.bottom-113, rcClient.Width()-6-209, 80);

	if (m_ListCtrl.IsWindow())
	{
		CRect rcListCtrl(rcClient.right-3-198, 298, rcClient.right-3, rcClient.bottom-4);
		m_ListCtrl.MoveWindow(&rcListCtrl);
	}

	if (::IsWindowVisible(m_FontSelDlg.m_hWnd))
		m_FontSelDlg.MoveWindow(1, rcClient.bottom-172, rcClient.Width()-1-209, 32);
}

void CGroupChatDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1001)
	{
		UpdateGroupMemberList();		// 更新群成员列表
		OnRecvMsg(m_nGroupCode, NULL);	// 显示消息
		KillTimer(nIDEvent);
		SetTimer(1002, 300, NULL);
	}
	else if (nIDEvent == 1002)
	{
		if (!m_FontSelDlg.IsWindow())
			m_FontSelDlg.Create(m_hWnd);
		KillTimer(nIDEvent);
	}
}

void CGroupChatDlg::OnClose()
{
	DestroyWindow();
}

void CGroupChatDlg::OnDestroy()
{
	SetMsgHandled(FALSE);

	CloseMsgLogBrowser();

	m_lpCascadeWinManager->Del(m_hWnd);

	UnInit();	// 反初始化控件

	if (m_hDlgIcon != NULL)
	{
		::DestroyIcon(m_hDlgIcon);
		m_hDlgIcon = NULL;
	}

	if (m_hDlgSmallIcon != NULL)
	{
		::DestroyIcon(m_hDlgSmallIcon);
		m_hDlgSmallIcon = NULL;
	}

	if (m_fontGroupNameLink != NULL)
	{
		::DeleteObject(m_fontGroupNameLink);
		m_fontGroupNameLink = NULL;
	}

	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
}

// “群名称”超链接控件
void CGroupChatDlg::OnLnk_GroupName(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	::PostMessage(m_hMainDlg, WM_SHOW_GROUPINFODLG, m_nGroupCode, NULL);
}

// “字体选择工具栏”按钮
void CGroupChatDlg::OnBtn_Font(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	if (BN_PUSHED == uNotifyCode)
	{
		if (!m_FontSelDlg.IsWindow())
			m_FontSelDlg.Create(m_hWnd);
		
		CRect rcClient;
		GetClientRect(&rcClient);
		m_richRecv.MoveWindow(6, rcClient.top+44+44, rcClient.Width()-6-209, rcClient.Height()-228-32);
		m_FontSelDlg.MoveWindow(1, rcClient.bottom-172, rcClient.Width()-1-209, 32);
		m_FontSelDlg.ShowWindow(SW_SHOW);
	}
	else if (BN_UNPUSHED == uNotifyCode)
	{
		m_FontSelDlg.ShowWindow(SW_HIDE);
		CRect rcClient;
		GetClientRect(&rcClient);
		m_richRecv.MoveWindow(6, rcClient.top+44+44, rcClient.Width()-6-209, rcClient.Height()-228);
	}
}

// “表情”按钮
void CGroupChatDlg::OnBtn_Face(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	if (BN_PUSHED == uNotifyCode)
	{
		m_FaceSelDlg.SetFaceList(m_lpFaceList);
		if (!m_FaceSelDlg.IsWindow())
		{
			m_FaceSelDlg.Create(m_hWnd);

			CRect rcBtn;
			m_tbMid.GetItemRectByIndex(1, rcBtn);
			m_tbMid.ClientToScreen(&rcBtn);

			int cx = 432;
			int cy = 236;
			int x = rcBtn.left - cx / 2;
			int y = rcBtn.top - cy;

			m_FaceSelDlg.SetWindowPos(NULL, x, y, cx, cy, NULL);
			m_FaceSelDlg.ShowWindow(SW_SHOW);
		}
	}
	else if (BN_UNPUSHED == uNotifyCode)
	{

	}
}

// “发送图片”按钮
void CGroupChatDlg::OnBtn_Image(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	BOOL bOpenFileDialog = TRUE;
	LPCTSTR lpszDefExt = NULL;
	LPCTSTR lpszFileName = NULL;
	DWORD dwFlags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR|OFN_EXTENSIONDIFFERENT;
	LPCTSTR lpszFilter = _T("图像文件(*.bmp;*.jpg;*.jpeg;*.gif;*.png)\0*.bmp;*.jpg;*.jpeg;*.gif;*.png\0\0");;
	HWND hWndParent = m_hWnd;

	CFileDialog fileDlg(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, hWndParent);
	fileDlg.m_ofn.lpstrTitle = _T("打开图片");
	if (fileDlg.DoModal() == IDOK)
	{
		_RichEdit_InsertFace(m_richSend.m_hWnd, fileDlg.m_ofn.lpstrFile, -1, -1);
		m_richSend.SetFocus();
	}
}

// “来消息不提示”按钮
void CGroupChatDlg::OnBtn_MsgNotPrompt(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CSkinMenu PopupMenu = PopupMenu = m_SkinMenu.GetSubMenu(1).GetSubMenu(5);
	if (PopupMenu.IsMenu())
	{
		CRect rcBtn;
		m_tbMid.GetItemRectByIndex(10, rcBtn);
		m_tbMid.ClientToScreen(&rcBtn);
		PopupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL, 
			rcBtn.left, rcBtn.bottom + 4, m_hWnd, &rcBtn);
	}
}

// “消息记录”按钮
void CGroupChatDlg::OnBtn_MsgLog(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	if (uNotifyCode == BN_CLICKED)
	{
		BOOL bChecked = m_tbMid.GetItemCheckState(11);
		if (!bChecked)
		{
			CloseMsgLogBrowser();
			return;
		}

		OpenMsgLogBrowser();
	}
}

// “点击另存为”按钮
void CGroupChatDlg::OnBtn_SaveAs(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	OnMenu_SaveAs(uNotifyCode, nID, wndCtl);
}

// “关闭”按钮
void CGroupChatDlg::OnBtn_Close(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	PostMessage(WM_CLOSE);
}

// “发送”按钮
void CGroupChatDlg::OnBtn_Send(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	if (NULL == m_lpQQClient)
		return;

	int nCustomPicCnt = RichEdit_GetCustomPicCount(m_richSend.m_hWnd);
	if (nCustomPicCnt > 1)
	{
		MessageBox(_T("每条消息最多包含1张图片，多张图片请分条发送。"), _T("提示"));
		return;
	}

	tstring strText;
	RichEdit_GetText(m_richSend.m_hWnd, strText);

	if (strText.size() <= 0)
		return;

	time_t nTime = m_lpQQClient->GetServerTime();

	AddMsgToRecvEdit(nTime, strText.c_str());

	CFontInfo fontInfo = m_FontSelDlg.GetFontInfo();

	TCHAR szColor[32] = {0};
	RGBToHexStr(fontInfo.m_clrText, szColor, sizeof(szColor)/sizeof(TCHAR));

	TCHAR szFontInfo[1024] = {0};
	LPCTSTR lpFontFmt = _T("/o[\"%s,%d,%s,%d,%d,%d\"]");
	wsprintf(szFontInfo, lpFontFmt, fontInfo.m_strName.c_str(), fontInfo.m_nSize, 
		szColor, fontInfo.m_bBold, fontInfo.m_bItalic, fontInfo.m_bUnderLine);

	strText += szFontInfo;

	m_lpQQClient->SendGroupMsg(m_nGroupId, nTime, strText.c_str());

	m_richSend.SetWindowText(_T(""));
	m_richSend.SetFocus();
}

// “箭头”按钮
void CGroupChatDlg::OnBtn_Arrow(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(5);
	if (PopupMenu.IsMenu())
	{
		CRect rc;
		m_btnArrow.GetClientRect(&rc);
		m_btnArrow.ClientToScreen(&rc);
		PopupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL, 
			rc.left, rc.bottom + 4, m_hWnd, &rc);
	}
}

LRESULT CGroupChatDlg::OnToolbarDropDown(LPNMHDR pnmh)
{
	NMTOOLBAR * pnmtb = (NMTOOLBAR *)pnmh;
	CSkinMenu PopupMenu;
	CRect rc(pnmtb->rcButton);

	switch (pnmtb->iItem)
	{
	case 101:
		m_tbTop.ClientToScreen(&rc);
		PopupMenu = m_SkinMenu.GetSubMenu(0);
		break;

	case 108:
		m_tbTop.ClientToScreen(&rc);
		PopupMenu = m_SkinMenu.GetSubMenu(1);
		break;

	case 208:
		m_tbMid.ClientToScreen(&rc);
		PopupMenu = m_SkinMenu.GetSubMenu(2);
		break;

	case 209:
		m_tbMid.ClientToScreen(&rc);
		PopupMenu = m_SkinMenu.GetSubMenu(3);
		break;

	case 212:
		m_tbMid.ClientToScreen(&rc);
		PopupMenu = m_SkinMenu.GetSubMenu(4);
		break;

	default:
		return 0;
	}

	if (PopupMenu.IsMenu())
	{
		PopupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL, 
			rc.left, rc.bottom + 4, m_hWnd, &rc);
	}

	return 0;
}

// 更新字体信息
LRESULT CGroupChatDlg::OnUpdateFontInfo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CFontInfo fontInfo = m_FontSelDlg.GetFontInfo();
	RichEdit_SetDefFont(m_richSend.m_hWnd, fontInfo.m_strName.c_str(),
		fontInfo.m_nSize, fontInfo.m_clrText, fontInfo.m_bBold,
		fontInfo.m_bItalic, fontInfo.m_bUnderLine, FALSE);
	return 0;
}

// “表情”控件选取消息
LRESULT CGroupChatDlg::OnFaceCtrlSel(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nFaceId = m_FaceSelDlg.GetSelFaceId();
	int nFaceIndex = m_FaceSelDlg.GetSelFaceIndex();
	CString strFileName = m_FaceSelDlg.GetSelFaceFileName();
	if (!strFileName.IsEmpty())
	{
		_RichEdit_InsertFace(m_richSend.m_hWnd, strFileName, nFaceId, nFaceIndex);
		m_richSend.SetFocus();
	}

	m_tbMid.SetItemCheckState(1, FALSE);
	m_tbMid.Invalidate();

	return 0;
}

// 设置对话框初始焦点
LRESULT CGroupChatDlg::OnSetDlgInitFocus(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	m_richSend.SetFocus();
	return 0;
}

//	“接收消息”富文本框链接点击消息
LRESULT CGroupChatDlg::OnRichEdit_Recv_Link(LPNMHDR pnmh)
{
	if (pnmh->code == EN_LINK)
	{
		ENLINK *pLink = (ENLINK *)pnmh;
		if (pLink->msg == WM_LBUTTONUP)
		{
			m_richRecv.SetSel(pLink->chrg);
			m_richRecv.GetSelText(m_strCurLink);

			if (m_strCurLink.Left(7).MakeLower() == _T("http://"))
				::ShellExecute(NULL, _T("open"), m_strCurLink, NULL, NULL, SW_SHOWNORMAL);
			else
			{
				DWORD dwPos = GetMessagePos();
				CPoint point(LOWORD(dwPos), HIWORD(dwPos));

				CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(6);
				PopupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, m_hWnd);
			}
		}
	}
	return 0;
}

LRESULT CGroupChatDlg::OnRichEdit_Send_Paste(LPNMHDR pnmh)
{
	NMRICHEDITOLECALLBACK * lpOleNotify = (NMRICHEDITOLECALLBACK *)pnmh;
	if (lpOleNotify != NULL && lpOleNotify->hdr.code == EN_PASTE
		&& lpOleNotify->hdr.hwndFrom == m_richSend.m_hWnd)
	{
		AddMsgToSendEdit(lpOleNotify->lpszText);
	}
	return 0;
}

// “群成员”列表双击消息
LRESULT CGroupChatDlg::OnGMemberList_DblClick(LPNMHDR pnmh)
{
	int nCurSel = m_ListCtrl.GetCurSelItemIndex();
	if (nCurSel != -1)
	{
		UINT nQQUin = (UINT)m_ListCtrl.GetItemData(nCurSel, 0);
		::SendMessage(m_hMainDlg, WM_SHOW_SESSCHATDLG, m_nGroupCode, nQQUin);
	}
	return 0;
}

// “群成员”列表右键单击消息
LRESULT CGroupChatDlg::OnGMemberList_RClick(LPNMHDR pnmh)
{
	int nCurSel = m_ListCtrl.GetCurSelItemIndex();
	if (nCurSel != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));

		CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(6);
		PopupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, m_hWnd);
	}
	return 0;
}

// “剪切”菜单
void CGroupChatDlg::OnMenu_Cut(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	m_richSend.Cut();
}

// “复制”菜单
void CGroupChatDlg::OnMenu_Copy(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	HWND hWnd = GetFocus();
	if (hWnd == m_richSend.m_hWnd)
	{
		m_richSend.Copy();
	}
	else if (hWnd == m_richRecv.m_hWnd)
	{
		m_richRecv.Copy();
	}
}

// “粘贴”菜单
void CGroupChatDlg::OnMenu_Paste(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	m_richSend.PasteSpecial(CF_TEXT);
}

// “全部选择”菜单
void CGroupChatDlg::OnMenu_SelAll(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	HWND hWnd = GetFocus();
	if (hWnd == m_richSend.m_hWnd)
	{
		m_richSend.SetSel(0, -1);
	}
	else if (hWnd == m_richRecv.m_hWnd)
	{
		m_richRecv.SetSel(0, -1);
	}
}

// “清屏”菜单
void CGroupChatDlg::OnMenu_Clear(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	m_richRecv.SetWindowText(_T(""));
}

// “显示比例”菜单
void CGroupChatDlg::OnMenu_ZoomRatio(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	switch (nID)
	{
	case ID_MENU_ZOOMRATIO_400:
		::SendMessage(m_richRecv.m_hWnd, EM_SETZOOM, 16, 4);
		break;
	case ID_MENU_ZOOMRATIO_200:
		::SendMessage(m_richRecv.m_hWnd, EM_SETZOOM, 8, 4);
		break;
	case ID_MENU_ZOOMRATIO_150:
		::SendMessage(m_richRecv.m_hWnd, EM_SETZOOM, 6, 4);
		break;
	case ID_MENU_ZOOMRATIO_125:
		::SendMessage(m_richRecv.m_hWnd, EM_SETZOOM, 5, 4);
		break;
	case ID_MENU_ZOOMRATIO_100:
		::SendMessage(m_richRecv.m_hWnd, EM_SETZOOM, 0, 0);
		break;
	case ID_MENU_ZOOMRATIO_75:
		::SendMessage(m_richRecv.m_hWnd, EM_SETZOOM, 3, 4);
		break;
	case ID_MENU_ZOOMRATIO_50:
		::SendMessage(m_richRecv.m_hWnd, EM_SETZOOM, 1, 2);
		break;
	default:
		return;
	}

	CSkinMenu menuPopup = m_SkinMenu.GetSubMenu(8);
	for (int i = ID_MENU_ZOOMRATIO_400; i <= ID_MENU_ZOOMRATIO_50; i++)
	{
		if (i != nID)
			menuPopup.CheckMenuItem(i, MF_BYCOMMAND|MF_UNCHECKED);
		else
			menuPopup.CheckMenuItem(i, MF_BYCOMMAND|MF_CHECKED);
	}	
}

// “另存为”菜单
void CGroupChatDlg::OnMenu_SaveAs(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	IImageOle * pImageOle = NULL;
	BOOL bRet = RichEdit_GetImageOle(m_hRBtnDownWnd, m_ptRBtnDown, &pImageOle);
	if (!bRet || NULL == pImageOle)
		return;

	CString strFileName;

	BSTR bstrFileName = NULL;
	HRESULT hr = pImageOle->GetFileName(&bstrFileName);
	if (SUCCEEDED(hr))
		strFileName = bstrFileName;
	if (bstrFileName != NULL)
		::SysFreeString(bstrFileName);

	TCHAR cFileName[MAX_PATH] = {0};
	BOOL bOpenFileDialog = FALSE;
	LPCTSTR lpszDefExt;
	LPCTSTR lpszFileName = _T("未命名");
	DWORD dwFlags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR|OFN_EXTENSIONDIFFERENT;
	LPCTSTR lpszFilter;
	HWND hWndParent = m_hWnd;

	GUID guid = {0};
	hr = pImageOle->GetRawFormat(&guid);

	if (InlineIsEqualGUID(guid, Gdiplus::ImageFormatJPEG))
	{
		lpszDefExt = _T(".jpg");
		lpszFilter = _T("图像文件(*.jpg)\0*.jpg\0图像文件(*.bmp)\0*.bmp\0\0");
	}
	else if (InlineIsEqualGUID(guid, Gdiplus::ImageFormatPNG))
	{
		lpszDefExt = _T(".png");
		lpszFilter = _T("图像文件(*.png)\0*.png\0\0");
	}
	else if (InlineIsEqualGUID(guid, Gdiplus::ImageFormatGIF))
	{
		lpszDefExt = _T(".gif");
		lpszFilter = _T("图像文件(*.gif)\0*.gif\0图像文件(*.jpg)\0*.jpg\0图像文件(*.bmp)\0*.bmp\0\0");
	}
	else
	{
		lpszDefExt = _T(".jpg");
		lpszFilter = _T("图像文件(*.jpg)\0*.jpg\0图像文件(*.bmp)\0*.bmp\0\0");
	}

	CFileDialog fileDlg(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, hWndParent);
	fileDlg.m_ofn.lpstrTitle = _T("保存图片");
	if (fileDlg.DoModal() == IDOK)
	{
		CString strSavePath = fileDlg.m_ofn.lpstrFile;
		CString strExtName = (_T(".") + ZYM::CPath::GetExtension(strSavePath)).c_str();
		GUID guid2 = GetFileTypeGuidByExtension(strExtName);

		if (InlineIsEqualGUID(guid, guid2))
		{
			CopyFile(strFileName, strSavePath, FALSE);
		}
		else
		{
			BSTR bstrSavePath = ::SysAllocString(strSavePath);
			if (bstrSavePath != NULL)
			{
				pImageOle->SaveAsFile(bstrSavePath);
				::SysFreeString(bstrSavePath);
			}
		}
	}

	if (pImageOle != NULL)
		pImageOle->Release();
}

// “查看资料”菜单
void CGroupChatDlg::OnMenu_ViewInfo(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));

	HWND hWnd = ::WindowFromPoint(point);
	if (hWnd == m_richRecv.m_hWnd)
	{
		UINT nQQNum = _tcstoul(m_strCurLink, NULL, 10);
		CGroupInfo * lpGroupInfo = GetGroupInfoPtr();
		if (lpGroupInfo != NULL)
		{
			CBuddyInfo * lpBuddyInfo = lpGroupInfo->GetMemberByNum(nQQNum);
			if (lpBuddyInfo != NULL)
				::PostMessage(m_hMainDlg, WM_SHOW_GMEMBERINFODLG, m_nGroupCode, lpBuddyInfo->m_nQQUin);
		}
	}
	else if (hWnd == m_ListCtrl.m_hWnd)
	{
		int nCurSel = m_ListCtrl.GetCurSelItemIndex();
		if (nCurSel != -1)
		{
			UINT nQQUin = (UINT)m_ListCtrl.GetItemData(nCurSel, 0);
			::PostMessage(m_hMainDlg, WM_SHOW_GMEMBERINFODLG, m_nGroupCode, nQQUin);
		}
	}
}

// “发送消息”菜单
void CGroupChatDlg::OnMenu_SendMsg(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));

	HWND hWnd = ::WindowFromPoint(point);
	if (hWnd == m_richRecv.m_hWnd)
	{
		UINT nQQNum = _tcstoul(m_strCurLink, NULL, 10);
		CGroupInfo * lpGroupInfo = GetGroupInfoPtr();
		if (lpGroupInfo != NULL)
		{
			CBuddyInfo * lpBuddyInfo = lpGroupInfo->GetMemberByNum(nQQNum);
			if (lpBuddyInfo != NULL)
				::SendMessage(m_hMainDlg, WM_SHOW_SESSCHATDLG, m_nGroupCode, lpBuddyInfo->m_nQQUin);
		}
	}
	else if (hWnd == m_ListCtrl.m_hWnd)
	{
		int nCurSel = m_ListCtrl.GetCurSelItemIndex();
		if (nCurSel > -1)
		{
			UINT nQQUin = (UINT)m_ListCtrl.GetItemData(nCurSel, 0);
			::SendMessage(m_hMainDlg, WM_SHOW_SESSCHATDLG, m_nGroupCode, nQQUin);
		}
	}
}

// 发送/接收文本框的鼠标移动消息
BOOL CGroupChatDlg::OnRichEdit_MouseMove(MSG * pMsg)
{
	IImageOle * pNewImageOle = NULL;
	RECT rc = {0};

	POINT pt = {LOWORD(pMsg->lParam), HIWORD(pMsg->lParam)};
	IImageOle * pImageOle = NULL;
	BOOL bRet = RichEdit_GetImageOle(pMsg->hwnd, pt, &pImageOle);
	if (bRet && pImageOle != NULL)
	{
		pNewImageOle = pImageOle;
		pImageOle->GetObjectRect(&rc);
	}
	if (pImageOle != NULL)
		pImageOle->Release();

	if (m_pLastImageOle != pNewImageOle)
	{
		m_pLastImageOle = pNewImageOle;
		if (m_pLastImageOle != NULL)
		{
			m_hRBtnDownWnd = pMsg->hwnd;
			m_ptRBtnDown = pt;

			if (!m_PicBarDlg.IsWindow())
				m_PicBarDlg.Create(m_hWnd);

			RECT rc2 = {0};
			::GetClientRect(pMsg->hwnd, &rc2);
			POINT pt = {rc.right, rc.bottom-m_cyPicBarDlg};
			if (pt.x < rc2.left)
				pt.x = rc2.left;
			if (pt.x > rc2.right)
				pt.x = rc2.right;
			if (pt.y > rc2.bottom-m_cyPicBarDlg)
				pt.y = rc2.bottom-m_cyPicBarDlg;
			::ClientToScreen(pMsg->hwnd, &pt);

			::SetWindowPos(m_PicBarDlg.m_hWnd, NULL, pt.x, pt.y, m_cxPicBarDlg, m_cyPicBarDlg, SWP_NOACTIVATE|SWP_SHOWWINDOW);
		}
		else
		{
			::ShowWindow(m_PicBarDlg.m_hWnd, SW_HIDE);
		}
	}
	return FALSE;
}

// 发送/接收文本框的鼠标双击消息
BOOL CGroupChatDlg::OnRichEdit_LBtnDblClk(MSG * pMsg)
{
	POINT pt = {GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam)};

	IImageOle * pImageOle = NULL;
	BOOL bRet = RichEdit_GetImageOle(pMsg->hwnd, pt, &pImageOle);
	if (bRet && pImageOle != NULL)					// 双击的是图片
	{
		LONG nFaceId = -1, nFaceIndex = -1;
		pImageOle->GetFaceId(&nFaceId);
		pImageOle->GetFaceIndex(&nFaceIndex);
		if (-1 == nFaceId && -1 == nFaceIndex)		// 非系统表情
		{
			BSTR bstrFileName = NULL;				// 获取图片文件名
			HRESULT hr = pImageOle->GetFileName(&bstrFileName);
			if (SUCCEEDED(hr))						// 调用图片浏览器程序打开图片
			{
				CString strExeName = ZYM::CPath::GetAppPath().c_str();
				strExeName += _T("ImageView.exe");

				CString strArg = _T("\"");
				strArg += bstrFileName;
				strArg += _T("\"");

				if (ZYM::CPath::IsFileExist(strExeName))
				{
					HWND hWnd = ::FindWindow(_T("DUI_WINDOW"), _T("ImageView"));
					if (::IsWindow(hWnd))
						::SendMessage(hWnd, WM_CLOSE, 0, 0);
					::ShellExecute(NULL, NULL, strExeName, strArg, NULL, SW_SHOWNORMAL);
				}
				else
					::ShellExecute(NULL, _T("open"), bstrFileName, NULL, NULL, SW_SHOWNORMAL);
			}
			if (bstrFileName != NULL)
				::SysFreeString(bstrFileName);
		}
	}
	if (pImageOle != NULL)
		pImageOle->Release();

	return bRet;
}

// 发送/接收文本框的鼠标右键按下消息
BOOL CGroupChatDlg::OnRichEdit_RBtnDown(MSG * pMsg)
{
	if (pMsg->hwnd == m_richSend.m_hWnd)
	{
		m_hRBtnDownWnd = pMsg->hwnd;
		m_ptRBtnDown.x = GET_X_LPARAM(pMsg->lParam);
		m_ptRBtnDown.y = GET_Y_LPARAM(pMsg->lParam);

		CSkinMenu menuPopup = m_SkinMenu.GetSubMenu(7);

		UINT nSel = ((m_richSend.GetSelectionType() != SEL_EMPTY) ? 0 : MF_GRAYED);
		menuPopup.EnableMenuItem(ID_MENU_CUT, MF_BYCOMMAND|nSel);
		menuPopup.EnableMenuItem(ID_MENU_COPY, MF_BYCOMMAND|nSel);

		UINT nPaste = (m_richSend.CanPaste() ? 0 : MF_GRAYED) ;
		menuPopup.EnableMenuItem(ID_MENU_PASTE, MF_BYCOMMAND|nPaste);

		IImageOle * pImageOle = NULL;
		BOOL bRet = RichEdit_GetImageOle(pMsg->hwnd, m_ptRBtnDown, &pImageOle);
		UINT nSaveAs = ((bRet && pImageOle != NULL) ? 0 : MF_GRAYED) ;
		menuPopup.EnableMenuItem(ID_MENU_SAVEAS, MF_BYCOMMAND|nSaveAs);
		if (pImageOle != NULL)
			pImageOle->Release();

		menuPopup.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			pMsg->pt.x, pMsg->pt.y, m_hWnd, NULL);
	}
	else if (pMsg->hwnd == m_richRecv.m_hWnd)
	{
		m_hRBtnDownWnd = pMsg->hwnd;
		m_ptRBtnDown.x = GET_X_LPARAM(pMsg->lParam);
		m_ptRBtnDown.y = GET_Y_LPARAM(pMsg->lParam);

		CSkinMenu menuPopup = m_SkinMenu.GetSubMenu(8);

		UINT nSel = ((m_richRecv.GetSelectionType() != SEL_EMPTY) ? 0 : MF_GRAYED);
		menuPopup.EnableMenuItem(ID_MENU_COPY, MF_BYCOMMAND|nSel);
		//menuPopup.EnableMenuItem(ID_MENU_CLEAR, MF_BYCOMMAND|nSel);

		IImageOle * pImageOle = NULL;
		BOOL bRet = RichEdit_GetImageOle(pMsg->hwnd, m_ptRBtnDown, &pImageOle);
		UINT nSaveAs = ((bRet && pImageOle != NULL) ? 0 : MF_GRAYED) ;
		menuPopup.EnableMenuItem(ID_MENU_SAVEAS, MF_BYCOMMAND|nSaveAs);
		if (pImageOle != NULL)
			pImageOle->Release();

		menuPopup.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			pMsg->pt.x, pMsg->pt.y, m_hWnd, NULL);
	}
	return FALSE;
}

// 获取群信息指针
CGroupInfo * CGroupChatDlg::GetGroupInfoPtr()
{
	if (m_lpQQClient != NULL)
	{
		CGroupList * lpGroupList = m_lpQQClient->GetGroupList();
		if (lpGroupList != NULL)
			return lpGroupList->GetGroupByCode(m_nGroupCode);
	}
	return NULL;
}

// 获取群成员信息指针
CBuddyInfo * CGroupChatDlg::GetGMemberInfoPtr(UINT nQQUin)
{
	if (m_lpQQClient != NULL)
	{
		CGroupList * lpGroupList = m_lpQQClient->GetGroupList();
		if (lpGroupList != NULL)
		{
			CGroupInfo * lpGroupInfo = lpGroupList->GetGroupByCode(m_nGroupCode);
			if (lpGroupInfo != NULL)
				return lpGroupInfo->GetMemberByUin(nQQUin);
		}
	}
	return NULL;
}

// 获取用户信息指针
CBuddyInfo * CGroupChatDlg::GetUserInfoPtr()
{
	if (m_lpQQClient != NULL)
	{
		CBuddyInfo * lpUserInfo = m_lpQQClient->GetUserInfo();
		if (lpUserInfo != NULL)
		{
			CBuddyInfo * lpGMemberInfo = NULL;
			CGroupInfo * lpGroupInfo = GetGroupInfoPtr();
			if (lpGroupInfo != NULL)
				lpGMemberInfo = lpGroupInfo->GetMemberByUin(lpUserInfo->m_nQQUin);
			if (lpGMemberInfo != NULL && 0 == lpGMemberInfo->m_nQQNum)
				lpGMemberInfo->m_nQQNum = lpUserInfo->m_nQQNum;
			return (lpGMemberInfo != NULL) ? lpGMemberInfo : lpUserInfo;
		}
	}
	return NULL;
}

// 更新信息
void CGroupChatDlg::UpdateData()
{
	CGroupInfo * lpGroupInfo = GetGroupInfoPtr();
	if (lpGroupInfo != NULL)
	{
		m_nMemberCnt = lpGroupInfo->GetMemberCount();
		m_nOnlineMemberCnt = lpGroupInfo->GetOnlineMemberCount();
		m_nGroupId = lpGroupInfo->m_nGroupId;
		m_nGroupNumber = lpGroupInfo->m_nGroupNumber;
		m_strGroupName = lpGroupInfo->m_strName.c_str();
	}

	CBuddyInfo * lpUserInfo = GetUserInfoPtr();
	if (lpUserInfo != NULL)
	{
		if (!lpUserInfo->m_strGroupCard.empty())
			m_strUserName = lpUserInfo->m_strGroupCard.c_str();
		else
			m_strUserName = lpUserInfo->m_strNickName.c_str();
		m_nUserNumber = lpUserInfo->m_nQQNum;
	}
}

// 更新对话框标题栏
void CGroupChatDlg::UpdateDlgTitle()
{
	SetWindowText(m_strGroupName);
}

// 更新群名称超链接控件
BOOL CGroupChatDlg::UpdateGroupNameCtrl()
{
	CString strText;
	if (m_nGroupNumber != 0)
		strText.Format(_T("%s(%u)"), m_strGroupName, m_nGroupNumber);
	else
		strText.Format(_T("%s"), m_strGroupName);
	m_lnkGroupName.SetLabel(strText);
	return TRUE;
}

// 更新群公告
BOOL CGroupChatDlg::UpdateGroupMemo()
{
	m_edtMemo.SetWindowText(_T("暂无公告"));
	CGroupInfo * lpGroupInfo = GetGroupInfoPtr();
	if (lpGroupInfo != NULL)
	{
		if (!lpGroupInfo->m_strMemo.empty())
			m_edtMemo.SetWindowText(lpGroupInfo->m_strMemo.c_str());
	}
	return TRUE;
}

// 更新群成员列表
BOOL CGroupChatDlg::UpdateGroupMemberList()
{
	CGroupInfo * lpGroupInfo = GetGroupInfoPtr();
	if (NULL == lpGroupInfo)
		return FALSE;

	CString strText, strNickName, strFileName;

 	strText.Format(_T("  群成员(%d/%d)"), m_nOnlineMemberCnt, m_nMemberCnt);
	m_staMemberTitle.SetWindowText(strText);

	m_ListCtrl.SetRedraw(FALSE);
	m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < lpGroupInfo->GetMemberCount(); i++)
	{
		CBuddyInfo * lpBuddyInfo = lpGroupInfo->GetMember(i);
		if (lpBuddyInfo != NULL)
		{
			if (!lpBuddyInfo->m_strGroupCard.empty())
				strNickName = lpBuddyInfo->m_strGroupCard.c_str();
			else
				strNickName = lpBuddyInfo->m_strNickName.c_str();

			if (lpBuddyInfo->m_nQQNum != 0)
				strText.Format(_T("%s(%u)"), strNickName, lpBuddyInfo->m_nQQNum);
			else
				strText.Format(_T("%s"), strNickName);

			BOOL bGray = lpBuddyInfo->m_nStatus != QQ_STATUS_OFFLINE ? FALSE : TRUE;

			strFileName = m_lpQQClient->GetSessHeadPicFullName(lpBuddyInfo->m_nQQNum).c_str();
			if (!ZYM::CPath::IsFileExist(strFileName))
			{
				if (!bGray)
					strFileName = (ZYM::CPath::GetAppPath() + _T("Image\\DefGMemberHeadPic16x16.png")).c_str();
				else
					strFileName = (ZYM::CPath::GetAppPath() + _T("Image\\DefGMemberGrayHeadPic16x16.png")).c_str();
				bGray = FALSE;
			}
			
			m_ListCtrl.InsertItem(i, strText, strFileName, bGray, DT_LEFT, 0);
			m_ListCtrl.SetItemData(i, 0, lpBuddyInfo->m_nQQUin);
		}
	}
	m_ListCtrl.SetRedraw(TRUE);
	m_ListCtrl.Invalidate();

	return TRUE;
}

// 初始化Top工具栏
BOOL CGroupChatDlg::InitTopToolBar()
{
	int nIndex = m_tbTop.AddItem(101, STBI_STYLE_DROPDOWN);
	m_tbTop.SetItemSize(nIndex, 52, 40, 42, 10);
	m_tbTop.SetItemPadding(nIndex, 1);
	m_tbTop.SetItemToolTipText(nIndex, _T("群社区"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemLeftBgPic(nIndex, _T("aio_toolbar_leftnormal.png"), 
		_T("aio_toolbar_leftdown.png"), CRect(0,0,0,0));
	m_tbTop.SetItemRightBgPic(nIndex, _T("aio_toolbar_rightnormal.png"), 
		_T("aio_toolbar_rightdown.png"), CRect(0,0,0,0));
	m_tbTop.SetItemArrowPic(nIndex, _T("aio_littletoolbar_arrow.png"));
	m_tbTop.SetItemIconPic(nIndex, _T("GroupTopToolBar\\GroupCommunity.png"));

	nIndex = m_tbTop.AddItem(102, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 36, 40);
	m_tbTop.SetItemPadding(nIndex, 1);
	m_tbTop.SetItemToolTipText(nIndex, _T("群共享"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("GroupTopToolBar\\GroupShare.png"));

	nIndex = m_tbTop.AddItem(103, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 36, 40);
	m_tbTop.SetItemPadding(nIndex, 1);
	m_tbTop.SetItemToolTipText(nIndex, _T("群相册"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("GroupTopToolBar\\GroupAlbum.png"));

	nIndex = m_tbTop.AddItem(104, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 36, 40);
	m_tbTop.SetItemPadding(nIndex, 2);
	m_tbTop.SetItemToolTipText(nIndex, _T("休闲小游戏"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("GroupTopToolBar\\Game.png"));

	nIndex = m_tbTop.AddItem(105, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 36, 40);
	m_tbTop.SetItemPadding(nIndex, 2);
	m_tbTop.SetItemToolTipText(nIndex, _T("创建讨论组"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("GroupTopToolBar\\create_disc_group.png"));

	nIndex = m_tbTop.AddItem(106, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 36, 40);
	m_tbTop.SetItemPadding(nIndex, 2);
	m_tbTop.SetItemToolTipText(nIndex, _T("发起多人语音会话"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("GroupTopToolBar\\MultiAudio.png"));

	nIndex = m_tbTop.AddItem(107, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 36, 40);
	m_tbTop.SetItemPadding(nIndex, 2);
	m_tbTop.SetItemToolTipText(nIndex, _T("搜索"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("GroupTopToolBar\\soso.png"));

	nIndex = m_tbTop.AddItem(108, STBI_STYLE_DROPDOWN);
	m_tbTop.SetItemSize(nIndex, 52, 40, 42, 10);
	m_tbTop.SetItemPadding(nIndex, 2);
	m_tbTop.SetItemToolTipText(nIndex, _T("群设置"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemLeftBgPic(nIndex, _T("aio_toolbar_leftnormal.png"), 
		_T("aio_toolbar_leftdown.png"), CRect(0,0,0,0));
	m_tbTop.SetItemRightBgPic(nIndex, _T("aio_toolbar_rightnormal.png"), 
		_T("aio_toolbar_rightdown.png"), CRect(0,0,0,0));
	m_tbTop.SetItemArrowPic(nIndex, _T("aio_littletoolbar_arrow.png"));
	m_tbTop.SetItemIconPic(nIndex, _T("GroupTopToolBar\\GroupSet.png"));

	nIndex = m_tbTop.AddItem(109, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 36, 40);
	m_tbTop.SetItemPadding(nIndex, 2);
	m_tbTop.SetItemToolTipText(nIndex, _T("举报"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("GroupTopToolBar\\Report.png"));

	m_tbTop.SetLeftTop(2, 2);
	m_tbTop.SetTransparent(TRUE, m_SkinDlg.GetBgDC());

	CRect rcTopToolBar(3, 45, 3+383, 45+44);
	m_tbTop.Create(m_hWnd, rcTopToolBar, NULL, WS_CHILD|WS_VISIBLE, NULL, ID_TOOLBAR_TOP);

	return TRUE;
}

// 初始化Middle工具栏
BOOL CGroupChatDlg::InitMidToolBar()
{
	int nIndex = m_tbMid.AddItem(201, STBI_STYLE_BUTTON|STBI_STYLE_CHECK);
	m_tbMid.SetItemSize(nIndex, 24, 20);
	m_tbMid.SetItemPadding(nIndex, 1);
	m_tbMid.SetItemToolTipText(nIndex, _T("字体选择工具栏"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\aio_quickbar_font.png"));

	nIndex = m_tbMid.AddItem(202, STBI_STYLE_BUTTON|STBI_STYLE_CHECK);
	m_tbMid.SetItemSize(nIndex, 24, 20);
	m_tbMid.SetItemPadding(nIndex, 1);
	m_tbMid.SetItemToolTipText(nIndex, _T("选择表情"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\aio_quickbar_face.png"));

	nIndex = m_tbMid.AddItem(203, STBI_STYLE_BUTTON);
	m_tbMid.SetItemSize(nIndex, 24, 20);
	m_tbMid.SetItemPadding(nIndex, 1);
	m_tbMid.SetItemToolTipText(nIndex, _T("会员魔法表情/超级表情/涂鸦表情"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\aio_quickbar_richface.png"));

	nIndex = m_tbMid.AddItem(204, STBI_STYLE_BUTTON|STBI_STYLE_CHECK);
	m_tbMid.SetItemSize(nIndex, 24, 20);
	m_tbMid.SetItemPadding(nIndex, 2);
	m_tbMid.SetItemToolTipText(nIndex, _T("多功能辅助输入"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\QQIme.png"));

	nIndex = m_tbMid.AddItem(205, STBI_STYLE_SEPARTOR);
	m_tbMid.SetItemSize(nIndex, 2, 20);
	m_tbMid.SetItemPadding(nIndex, 1);
	m_tbMid.SetItemSepartorPic(nIndex, _T("aio_qzonecutline_normal.png"));

	nIndex = m_tbMid.AddItem(206, STBI_STYLE_BUTTON);
	m_tbMid.SetItemSize(nIndex, 24, 20);
	m_tbMid.SetItemPadding(nIndex, 1);
	m_tbMid.SetItemToolTipText(nIndex, _T("发送图片"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\aio_quickbar_sendpic.png"));

	nIndex = m_tbMid.AddItem(207, STBI_STYLE_BUTTON);
	m_tbMid.SetItemSize(nIndex, 24, 20);
	m_tbMid.SetItemPadding(nIndex, 1);
	m_tbMid.SetItemToolTipText(nIndex, _T("点歌"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\musicsharebtn20.png"));

	nIndex = m_tbMid.AddItem(208, STBI_STYLE_DROPDOWN);
	m_tbMid.SetItemSize(nIndex, 31, 20, 23, 8);
	m_tbMid.SetItemPadding(nIndex, 1);
	m_tbMid.SetItemToolTipText(nIndex, _T("屏幕截图 Ctrl + Alt + A"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemLeftBgPic(nIndex, _T("aio_toolbar_leftnormal.png"), 
		_T("aio_toolbar_leftdown.png"), CRect(1,0,0,0));
	m_tbMid.SetItemRightBgPic(nIndex, _T("aio_toolbar_rightnormal.png"), 
		_T("aio_toolbar_rightdown.png"), CRect(0,0,1,0));
	m_tbMid.SetItemArrowPic(nIndex, _T("aio_littletoolbar_arrow.png"));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\aio_quickbar_cut.png"));

	nIndex = m_tbMid.AddItem(209, STBI_STYLE_DROPDOWN);
	m_tbMid.SetItemSize(nIndex, 31, 20, 23, 8);
	m_tbMid.SetItemPadding(nIndex, 2);
	m_tbMid.SetItemToolTipText(nIndex, _T("划词搜索"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemLeftBgPic(nIndex, _T("aio_toolbar_leftnormal.png"), 
		_T("aio_toolbar_leftdown.png"), CRect(1,0,0,0));
	m_tbMid.SetItemRightBgPic(nIndex, _T("aio_toolbar_rightnormal.png"), 
		_T("aio_toolbar_rightdown.png"), CRect(0,0,1,0));
	m_tbMid.SetItemArrowPic(nIndex, _T("aio_littletoolbar_arrow.png"));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\SoSo.png"));

	nIndex = m_tbMid.AddItem(210, STBI_STYLE_SEPARTOR);
	m_tbMid.SetItemSize(nIndex, 2, 20);
	m_tbMid.SetItemPadding(nIndex, 1);
	m_tbMid.SetItemSepartorPic(nIndex, _T("aio_qzonecutline_normal.png"));

	nIndex = m_tbMid.AddItem(211, STBI_STYLE_BUTTON);
	m_tbMid.SetItemSize(nIndex, 37, 20);
	m_tbMid.SetItemPadding(nIndex, 1);
	m_tbMid.SetItemToolTipText(nIndex, _T("来消息不提示"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\aio_quickbar_screen1.png"));

	nIndex = m_tbMid.AddItem(212, STBI_STYLE_DROPDOWN|STBI_STYLE_CHECK);
	m_tbMid.SetItemSize(nIndex, 82, 20, 74, 8);
	m_tbMid.SetItemPadding(nIndex, 2);
	m_tbMid.SetItemText(nIndex, _T("消息记录"));
	m_tbMid.SetItemToolTipText(nIndex, _T("显示消息记录"));
	m_tbMid.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbMid.SetItemLeftBgPic(nIndex, _T("aio_toolbar_leftnormal.png"), 
		_T("aio_toolbar_leftdown.png"), CRect(1,0,0,0));
	m_tbMid.SetItemRightBgPic(nIndex, _T("aio_toolbar_rightnormal.png"), 
		_T("aio_toolbar_rightdown.png"), CRect(0,0,1,0));
	m_tbMid.SetItemArrowPic(nIndex, _T("aio_littletoolbar_arrow.png"));
	m_tbMid.SetItemIconPic(nIndex, _T("MidToolBar\\aio_quickbar_register.png"));

	m_tbMid.SetLeftTop(2, 4);
	m_tbMid.SetBgPic(_T("MidToolBar\\bg.png"), CRect(0,0,0,0));

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcMidToolBar(1, rcClient.bottom-140, 1+382, (rcClient.bottom-140)+27);
	m_tbMid.Create(m_hWnd, rcMidToolBar, NULL, WS_CHILD|WS_VISIBLE, NULL, ID_TOOLBAR_MID);

	return TRUE;
}

// 初始化IRichEditOleCallback接口
BOOL CGroupChatDlg::InitRichEditOleCallback()
{
	IRichEditOleCallback2* pRichEditOleCallback2 = NULL;
	HRESULT hr = ::CoCreateInstance(CLSID_ImageOle, NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IRichEditOleCallback2), (void**)&pRichEditOleCallback2);
	if (SUCCEEDED(hr))
	{
		pRichEditOleCallback2->SetNotifyHwnd(m_hWnd);
		pRichEditOleCallback2->SetRichEditHwnd(m_richRecv.m_hWnd);
		m_richRecv.SetOleCallback(pRichEditOleCallback2);
		pRichEditOleCallback2->Release();
	}

	pRichEditOleCallback2 = NULL;
	hr = ::CoCreateInstance(CLSID_ImageOle, NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IRichEditOleCallback2), (void**)&pRichEditOleCallback2);
	if (SUCCEEDED(hr))
	{
		pRichEditOleCallback2->SetNotifyHwnd(m_hWnd);
		pRichEditOleCallback2->SetRichEditHwnd(m_richSend.m_hWnd);
		m_richSend.SetOleCallback(pRichEditOleCallback2);
		pRichEditOleCallback2->Release();
	}

	return SUCCEEDED(hr);
}

// 初始化
BOOL CGroupChatDlg::Init()
{
	m_SkinDlg.SubclassWindow(m_hWnd);
	m_SkinDlg.SetBgPic(_T("GroupChatDlgBg.png"), CRect(40, 86, 209, 140));
	m_SkinDlg.SetMinSysBtnPic(_T("SysBtn\\btn_mini_normal.png"), 
		_T("SysBtn\\btn_mini_highlight.png"), _T("SysBtn\\btn_mini_down.png"));
	m_SkinDlg.SetMaxSysBtnPic(_T("SysBtn\\btn_max_normal.png"), 
		_T("SysBtn\\btn_max_highlight.png"), _T("SysBtn\\btn_max_down.png"));
	m_SkinDlg.SetRestoreSysBtnPic(_T("SysBtn\\btn_restore_normal.png"), 
		_T("SysBtn\\btn_restore_highlight.png"), _T("SysBtn\\btn_restore_down.png"));
	m_SkinDlg.SetCloseSysBtnPic(_T("SysBtn\\btn_close_normal.png"), 
		_T("SysBtn\\btn_close_highlight.png"), _T("SysBtn\\btn_close_down.png"));

	HDC hDlgBgDC = m_SkinDlg.GetBgDC();

	CRect rcClient;
	GetClientRect(&rcClient);

	m_picHead.SubclassWindow(GetDlgItem(ID_PIC_HEAD));
	m_picHead.MoveWindow(8, 6, 32, 32, FALSE);
	m_picHead.SetTransparent(TRUE, hDlgBgDC);
	m_picHead.SetBgPic(_T("aio_head_normal.png"), _T("aio_head_normal.png"), _T("aio_head_normal.png"));

	tstring strFileName;
	if (m_lpQQClient != NULL && m_nGroupNumber != 0)
		strFileName = m_lpQQClient->GetGroupHeadPicFullName(m_nGroupNumber);
	if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefGroupHeadPic.jpg");
	m_picHead.SetBitmap(strFileName.c_str());

	m_lnkGroupName.SubclassWindow(GetDlgItem(ID_LINK_GROUPNAME));
	m_lnkGroupName.MoveWindow(44, 8, 60, 14, FALSE);
	m_lnkGroupName.SetTransparent(TRUE, hDlgBgDC);
	m_lnkGroupName.SetLinkColor(RGB(0,0,0));
	m_lnkGroupName.SetHoverLinkColor(RGB(0,0,0));
	m_lnkGroupName.SetVisitedLinkColor(RGB(0,0,0));

	CFontHandle font = (HFONT)::SendMessage(m_hWnd, WM_GETFONT, 0, 0L);
	LOGFONT lf = {0};
	font.GetLogFont(&lf);
	lf.lfHeight = 13;
	lf.lfWeight = FW_BOLD;
	m_fontGroupNameLink = ::CreateFontIndirect(&lf); 
	m_lnkGroupName.SetNormalFont(m_fontGroupNameLink);

	m_staGroupCategory.SubclassWindow(GetDlgItem(ID_STATIC_GROUPCATEGORY));
	m_staGroupCategory.MoveWindow(44, 22, 60, 14, FALSE);
	m_staGroupCategory.SetTransparent(TRUE, hDlgBgDC);

	m_picAD.SubclassWindow(GetDlgItem(ID_PIC_AD));
	m_picAD.MoveWindow(rcClient.right-202, 44, 200, 42, FALSE);
	strFileName = ZYM::CPath::GetAppPath()+_T("Image\\AD_4.png");
	m_picAD.SetBitmap(strFileName.c_str());
	m_picAD.SetDrawMode(DRAW_MODE_STRETCH);

	m_staMemoTitle.SubclassWindow(GetDlgItem(ID_STATIC_MEMOTITLE));
	m_staMemoTitle.MoveWindow(rcClient.right-201, 86, 198, 24, FALSE);
	m_staMemoTitle.SetTransparent(TRUE, hDlgBgDC);
	m_staMemoTitle.SetNormalBgPic(_T("MemoTitleBg.png"));

	m_staMemberTitle.SubclassWindow(GetDlgItem(ID_STATIC_MERBERTITLE));
	m_staMemberTitle.MoveWindow(rcClient.right-201, 274, 198, 24, FALSE);
	m_staMemberTitle.SetTransparent(TRUE, hDlgBgDC);
	m_staMemberTitle.SetNormalBgPic(_T("MemoTitleBg.png"));

	m_edtMemo.SetMultiLine(TRUE);
	m_edtMemo.SubclassWindow(GetDlgItem(ID_EDIT_MEMO));
	m_edtMemo.MoveWindow(rcClient.right-201, 110, 198, 164, FALSE);
	//m_edtMemo.SetReadOnly();

	m_btnClose.SubclassWindow(GetDlgItem(ID_BTN_CLOSE));
	m_btnClose.MoveWindow(rcClient.right-366, rcClient.bottom-5-22, 69, 22, FALSE);
	m_btnClose.SetTransparent(TRUE, hDlgBgDC);
	m_btnClose.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnClose.SetBgPic(_T("Button\\btn_normal.png"), _T("Button\\btn_highlight.png"),
		_T("Button\\btn_down.png"), _T("Button\\btn_focus.png"));

	m_btnSend.SubclassWindow(GetDlgItem(ID_BTN_SEND));
	m_btnSend.MoveWindow(rcClient.right-292, rcClient.bottom-5-22, 64, 22, FALSE);
	m_btnSend.SetTransparent(TRUE, hDlgBgDC);
	m_btnSend.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnSend.SetBgPic(_T("Button\\btnleft_normal.png"), _T("Button\\btnleft_highlight.png"),
		_T("Button\\btnleft_down.png"), _T("Button\\btnleft_focus.png"));

	m_btnArrow.SubclassWindow(GetDlgItem(ID_BTN_ARROW));
	m_btnArrow.MoveWindow(rcClient.right-209-19, rcClient.bottom-5-22, 19, 22, FALSE);
	m_btnArrow.SetTransparent(TRUE, hDlgBgDC);
	m_btnArrow.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnArrow.SetBgPic(_T("Button\\btnright_normal.png"), _T("Button\\btnright_highlight.png"),
		_T("Button\\btnright_down.png"), _T("Button\\btnright_fouce.png"));

	m_SkinMenu.LoadMenu(ID_MENU_GROUPCHAT);
	m_SkinMenu.SetBgPic(_T("Menu\\menu_left_bg.png"), _T("Menu\\menu_right_bg.png"));
	m_SkinMenu.SetSelectedPic(_T("Menu\\menu_selected.png"));
	m_SkinMenu.SetSepartorPic(_T("Menu\\menu_separtor.png"));
	m_SkinMenu.SetArrowPic(_T("Menu\\menu_arrow.png"));
	m_SkinMenu.SetCheckPic(_T("Menu\\menu_check.png"));
	m_SkinMenu.SetTextColor(RGB(0, 20, 35));
	m_SkinMenu.SetSelTextColor(RGB(254, 254, 254));

	InitTopToolBar();				// 初始化Top工具栏
	InitMidToolBar();				// 初始化Middle工具栏
	m_PicBarDlg.Create(m_hWnd);		// 创建图片悬浮工具栏

	CRect rcRecv = CRect(CPoint(6, rcClient.top+44+44), CSize(rcClient.Width()-6-209, rcClient.Height()-228));
	DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_MULTILINE|ES_AUTOVSCROLL|WS_VSCROLL|ES_WANTRETURN;
	m_richRecv.Create(m_hWnd, rcRecv, NULL, dwStyle, WS_EX_TRANSPARENT, ID_RICHEDIT_RECV);
	m_richRecv.SetTransparent(TRUE, hDlgBgDC);

	CRect rcSend = CRect(CPoint(6, rcClient.bottom-113), CSize(rcClient.right-6-209, 80));
	m_richSend.Create(m_hWnd, rcSend, NULL, dwStyle, WS_EX_TRANSPARENT, ID_RICHEDIT_SEND);
	m_richSend.SetTransparent(TRUE, hDlgBgDC);
	//m_richSend.SetBackgroundColor(RGB(252, 253, 254));

	// 发送消息富文本框控件
	CFontInfo fontInfo = m_FontSelDlg.GetPublicFontInfo();
	RichEdit_SetDefFont(m_richSend.m_hWnd, fontInfo.m_strName.c_str(),
		fontInfo.m_nSize, fontInfo.m_clrText, fontInfo.m_bBold,
		fontInfo.m_bItalic, fontInfo.m_bUnderLine, FALSE);

	// 接收消息富文本框控件
	DWORD dwMask = m_richRecv.GetEventMask();
	dwMask = dwMask | ENM_LINK  | ENM_MOUSEEVENTS | ENM_SCROLLEVENTS | ENM_KEYEVENTS;
	m_richRecv.SetEventMask(dwMask);

	m_richRecv.SetReadOnly();

	CRect rcListCtrl(rcClient.right-3-198, 298, rcClient.right-3, rcClient.bottom-4);
	m_ListCtrl.Create(m_hWnd, rcListCtrl, NULL, WS_CHILD|WS_VISIBLE, NULL, ID_LIST_MERBER);

	m_ListCtrl.SetBgPic(_T("ListCtrl\\listctrlbg.png"));
	m_ListCtrl.SetItemSelBgPic(_T("ListCtrl\\listitem_select.png"));
	m_ListCtrl.SetHeadVisible(FALSE);
	m_ListCtrl.AddColumn(_T("群成员"), NULL, DT_LEFT, 184);

	UpdateGroupNameCtrl();	// 更新群名称控件
	UpdateDlgTitle();		// 更新对话框标题
	UpdateGroupMemo();		// 更新群公告

	m_Accelerator.LoadAccelerators(ID_ACCE_CHATDLG);

	InitRichEditOleCallback();	// 初始化IRichEditOleCallback接口

	return TRUE;
}

// 反初始化
BOOL CGroupChatDlg::UnInit()
{
	if (m_PicBarDlg.IsWindow())
		m_PicBarDlg.DestroyWindow();

	if (m_picHead.IsWindow())
		m_picHead.DestroyWindow();

	if (m_lnkGroupName.IsWindow())
		m_lnkGroupName.DestroyWindow();

	if (m_staGroupCategory.IsWindow())
		m_staGroupCategory.DestroyWindow();

	if (m_picAD.IsWindow())
		m_picAD.DestroyWindow();

	if (m_staMemoTitle.IsWindow())
		m_staMemoTitle.DestroyWindow();

	if (m_staMemberTitle.IsWindow())
		m_staMemberTitle.DestroyWindow();

	if (m_edtMemo.IsWindow())
		m_edtMemo.DestroyWindow();

	if (m_btnClose.IsWindow())
		m_btnClose.DestroyWindow();

	if (m_btnSend.IsWindow())
		m_btnSend.DestroyWindow();

	if (m_btnArrow.IsWindow())
		m_btnArrow.DestroyWindow();

	m_SkinMenu.DestroyMenu();

	if (m_tbTop.IsWindow())
		m_tbTop.DestroyWindow();

	if (m_tbMid.IsWindow())
		m_tbMid.DestroyWindow();

	if (m_FontSelDlg.IsWindow())
		m_FontSelDlg.DestroyWindow();

	if (m_FaceSelDlg.IsWindow())
		m_FaceSelDlg.DestroyWindow();

	if (m_richRecv.IsWindow())
		m_richRecv.DestroyWindow();

	if (m_richSend.IsWindow())
		m_richSend.DestroyWindow();

	if (m_ListCtrl.IsWindow())
		m_ListCtrl.DestroyWindow();

	m_Accelerator.DestroyObject();
//	m_menuRichEdit.DestroyMenu();

	return TRUE;
}

int CGroupChatDlg::FindMemberListByUin(UINT nQQUin)
{
	int nCount = m_ListCtrl.GetItemCount();
	for (int i = 0; i < nCount; i++)
	{
		UINT nQQUin2 = (UINT)m_ListCtrl.GetItemData(i, 0);
		if (nQQUin2 == nQQUin)
			return i;
	}
	return -1;
}

void CGroupChatDlg::GetSenderInfo(UINT nQQUin, CString& strName, UINT& nQQNum)
{
	strName = _T("");
	nQQNum = 0;

	CGroupInfo * lpGroupInfo = GetGroupInfoPtr();
	if (lpGroupInfo != NULL)
	{
		CBuddyInfo * lpBuddyInfo = lpGroupInfo->GetMemberByUin(nQQUin);
		if (lpBuddyInfo != NULL)
		{
			if (!lpBuddyInfo->m_strGroupCard.empty())
				strName = lpBuddyInfo->m_strGroupCard.c_str();
			else
				strName = lpBuddyInfo->m_strNickName.c_str();
			nQQNum = lpBuddyInfo->m_nQQNum;
		}
	}
}

void CGroupChatDlg::_RichEdit_ReplaceSel(HWND hWnd, LPCTSTR lpszNewText)
{
	if (hWnd == m_richRecv.m_hWnd)
	{
		CFontInfo fontInfo = m_FontSelDlg.GetFontInfo();
		RichEdit_ReplaceSel(hWnd, lpszNewText, 
			fontInfo.m_strName.c_str(), fontInfo.m_nSize, 
			fontInfo.m_clrText, fontInfo.m_bBold, fontInfo.m_bItalic, 
			fontInfo.m_bUnderLine, FALSE, 300);
	}
	else
	{
		RichEdit_ReplaceSel(hWnd, lpszNewText);
	}
}

BOOL CGroupChatDlg::_RichEdit_InsertFace(HWND hWnd, LPCTSTR lpszFileName, int nFaceId, int nFaceIndex)
{
	ITextServices * pTextServices;
	ITextHost * pTextHost;
	BOOL bRet;

	if (hWnd == m_richRecv.m_hWnd)
	{
		pTextServices = m_richRecv.GetTextServices();
		pTextHost = m_richRecv.GetTextHost();

		long lStartChar = 0, lEndChar = 0;
		RichEdit_GetSel(hWnd, lStartChar, lEndChar);
		bRet = RichEdit_InsertFace(pTextServices, pTextHost, 
			lpszFileName, nFaceId, nFaceIndex, RGB(255,255,255), TRUE, 40);
		if (bRet)
		{
			lEndChar = lStartChar + 1;
			RichEdit_SetSel(hWnd, lStartChar, lEndChar);
			RichEdit_SetStartIndent(hWnd, 300);
			RichEdit_SetSel(hWnd, lEndChar, lEndChar);
		}
	}
	else
	{
		pTextServices = m_richSend.GetTextServices();
		pTextHost = m_richSend.GetTextHost();

		bRet = RichEdit_InsertFace(pTextServices, pTextHost, 
			lpszFileName, nFaceId, nFaceIndex, RGB(255,255,255), TRUE, 40);
	}

	if (pTextServices != NULL)
		pTextServices->Release();
	if (pTextHost != NULL)
		pTextHost->Release();

	return bRet;
}

BOOL CGroupChatDlg::HandleSysFaceId(HWND hRichEditWnd, LPCTSTR& p, CString& strText)
{
	int nFaceId = GetBetweenInt(p+2, _T("[\""), _T("\"]"), -1);
	CFaceInfo * lpFaceInfo = m_lpFaceList->GetFaceInfoById(nFaceId);
	if (lpFaceInfo != NULL)
	{
		if (!strText.IsEmpty())
		{
			_RichEdit_ReplaceSel(hRichEditWnd, strText); 
			strText = _T("");
		}

		_RichEdit_InsertFace(hRichEditWnd, lpFaceInfo->m_strFileName.c_str(), 
			lpFaceInfo->m_nId, lpFaceInfo->m_nIndex);

		p = _tcsstr(p+2, _T("\"]"));
		p++;
		return TRUE;
	}
	return FALSE;
}

BOOL CGroupChatDlg::HandleSysFaceIndex(HWND hRichEditWnd, LPCTSTR& p, CString& strText)
{
	int nFaceIndex = GetBetweenInt(p+2, _T("[\""), _T("\"]"), -1);
	CFaceInfo * lpFaceInfo = m_lpFaceList->GetFaceInfoByIndex(nFaceIndex);
	if (lpFaceInfo != NULL)
	{
		if (!strText.IsEmpty())
		{
			_RichEdit_ReplaceSel(hRichEditWnd, strText); 
			strText = _T("");
		}

		_RichEdit_InsertFace(hRichEditWnd, lpFaceInfo->m_strFileName.c_str(), 
			lpFaceInfo->m_nId, lpFaceInfo->m_nIndex);

		p = _tcsstr(p+2, _T("\"]"));
		p++;
		return TRUE;
	}
	return FALSE;
}

BOOL CGroupChatDlg::HandleCustomPic(HWND hRichEditWnd, LPCTSTR& p, CString& strText)
{
	CString strFileName = GetBetweenString(p+2, _T("[\""), _T("\"]")).c_str();
	if (!strFileName.IsEmpty())
	{
		if (!strText.IsEmpty())
		{
			_RichEdit_ReplaceSel(hRichEditWnd, strText); 
			strText = _T("");
		}

		if (::PathIsRelative(strFileName))
			strFileName = m_lpQQClient->GetChatPicFullName(strFileName).c_str();

		_RichEdit_InsertFace(hRichEditWnd, strFileName, -1, -1);

		p = _tcsstr(p+2, _T("\"]"));
		p++;
		return TRUE;
	}
	return FALSE;
}

// "/f["系统表情id"] /s["系统表情index"] /c["自定义图片路径"]"
void CGroupChatDlg::AddMsg(HWND hRichEditWnd, LPCTSTR lpText)
{
	if (NULL == lpText || NULL == *lpText)
		return;

	CString strText;

	for (LPCTSTR p = lpText; *p != _T('\0'); p++)
	{
		if (*p == _T('/'))
		{
			if (*(p+1) == _T('/'))
			{
				strText += *p;
				p++;
				continue;
			}
			else if (*(p+1) == _T('f'))
			{
				if (HandleSysFaceId(hRichEditWnd, p, strText))
					continue;
			}
			else if (*(p+1) == _T('s'))
			{
				if (HandleSysFaceIndex(hRichEditWnd, p, strText))
					continue;
			}
			else if (*(p+1) == _T('c'))
			{
				if (HandleCustomPic(hRichEditWnd, p, strText))
					continue;
			}
		}
		strText += *p;
	}

	if (!strText.IsEmpty())
		_RichEdit_ReplaceSel(hRichEditWnd, strText);
}

void CGroupChatDlg::AddMsgToSendEdit(LPCTSTR lpText)
{
	AddMsg(m_richSend.m_hWnd, lpText);
	m_richSend.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

void CGroupChatDlg::AddMsgToRecvEdit(time_t nTime, LPCTSTR lpText)
{
	if (NULL == lpText || NULL == *lpText)
		return;

	TCHAR cTime[32] = {0};
	FormatTime(nTime, _T("%H:%M:%S"), cTime, sizeof(cTime)/sizeof(TCHAR));

	CString strText;
	strText.Format(_T("%s(%u)  %s\r\n"), m_strUserName, m_nUserNumber, cTime);

	RichEdit_SetSel(m_richRecv.m_hWnd, -1, -1);
	RichEdit_ReplaceSel(m_richRecv.m_hWnd, strText, 
		_T("宋体"), 10, RGB(0,128,64), FALSE, FALSE, FALSE, FALSE, 0);
	strText = _T("");

	AddMsg(m_richRecv.m_hWnd, lpText);

	RichEdit_ReplaceSel(m_richRecv.m_hWnd, _T("\r\n"));
	RichEdit_SetStartIndent(m_richRecv.m_hWnd, 0);
	m_richRecv.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

void CGroupChatDlg::AddMsgToRecvEdit(CGroupMessage * lpGroupMsg)
{
	if (NULL == lpGroupMsg || NULL == m_lpQQClient)
		return;

	CString strText, strSenderName;
	UINT nSenderNum;
	CFontInfo fontInfo;

	TCHAR cTime[32] = {0};
	if (IsToday(lpGroupMsg->m_nTime))
		FormatTime(lpGroupMsg->m_nTime, _T("%H:%M:%S"), cTime, sizeof(cTime)/sizeof(TCHAR));
	else
		FormatTime(lpGroupMsg->m_nTime, _T("%Y-%m-%d %H:%M:%S"), cTime, sizeof(cTime)/sizeof(TCHAR));

	GetSenderInfo(lpGroupMsg->m_nSendUin, strSenderName, nSenderNum);

	m_richRecv.SetAutoURLDetect(FALSE);

	RichEdit_SetSel(m_richRecv.m_hWnd, -1, -1);

	if (nSenderNum != 0)
	{
		strText.Format(_T("%s("), strSenderName);
		RichEdit_ReplaceSel(m_richRecv.m_hWnd, strText, 
			_T("宋体"), 10, RGB(0, 0, 255), FALSE, FALSE, FALSE, FALSE, 0);

		strText.Format(_T("%u"), nSenderNum);
		RichEdit_ReplaceSel(m_richRecv.m_hWnd, strText, 
			_T("宋体"), 10, RGB(0, 114, 193), FALSE, FALSE, TRUE, TRUE, 0);
		
		strText.Format(_T(")  %s\r\n"), cTime);
		RichEdit_ReplaceSel(m_richRecv.m_hWnd, strText, 
			_T("宋体"), 10, RGB(0, 0, 255), FALSE, FALSE, FALSE, FALSE, 0);
	}
	else
	{
		strText.Format(_T("%s  %s\r\n"), strSenderName, cTime);
		RichEdit_ReplaceSel(m_richRecv.m_hWnd, strText, 
			_T("宋体"), 10, RGB(0, 0, 255), FALSE, FALSE, FALSE, FALSE, 0);
	}

	m_richRecv.SetAutoURLDetect(TRUE);

	for (int i = 0; i < (int)lpGroupMsg->m_arrContent.size(); i++)
	{
		CContent * lpContent = lpGroupMsg->m_arrContent[i];
		if (lpContent != NULL)
		{
			switch (lpContent->m_nType)
			{
			case CONTENT_TYPE_FONT_INFO:
				{
					fontInfo.m_strName = lpContent->m_FontInfo.m_strName;
					fontInfo.m_nSize = lpContent->m_FontInfo.m_nSize;
					fontInfo.m_clrText = lpContent->m_FontInfo.m_clrText;
					fontInfo.m_bBold = lpContent->m_FontInfo.m_bBold;
					fontInfo.m_bItalic = lpContent->m_FontInfo.m_bItalic;
					fontInfo.m_bUnderLine = lpContent->m_FontInfo.m_bUnderLine;
				}
				break;

			case CONTENT_TYPE_TEXT:
				{
					RichEdit_ReplaceSel(m_richRecv.m_hWnd, lpContent->m_strText.c_str(), 
						fontInfo.m_strName.c_str(), fontInfo.m_nSize, 
						fontInfo.m_clrText, fontInfo.m_bBold, fontInfo.m_bItalic, 
						fontInfo.m_bUnderLine, FALSE, 300);
				}
				break;

			case CONTENT_TYPE_FACE:
				{
					if (m_lpFaceList != NULL)
					{
						CFaceInfo * lpFaceInfo = m_lpFaceList->GetFaceInfoById(lpContent->m_nFaceId);
						if (lpFaceInfo != NULL)
						{
							_RichEdit_InsertFace(m_richRecv.m_hWnd, 
								lpFaceInfo->m_strFileName.c_str(), lpFaceInfo->m_nId, lpFaceInfo->m_nIndex);
						}
					}
				}
				break;

			case CONTENT_TYPE_CUSTOM_FACE:
				{
					tstring strFileName = m_lpQQClient->GetChatPicFullName(lpContent->m_CFaceInfo.m_strName.c_str());
					if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
						strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DownloadFailed.gif");
					_RichEdit_InsertFace(m_richRecv.m_hWnd, strFileName.c_str(), -1, -1);
				}
				break;
			}
		}
	}

	RichEdit_ReplaceSel(m_richRecv.m_hWnd, _T("\r\n"));
	RichEdit_SetStartIndent(m_richRecv.m_hWnd, 0);
	m_richRecv.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

// 打开消息记录浏览窗口
void CGroupChatDlg::OpenMsgLogBrowser()
{
	CString strExeName = ZYM::CPath::GetAppPath().c_str();
	strExeName += _T("MsgLogBrowser.exe");

	if (!ZYM::CPath::IsFileExist(strExeName))
		return;

	CString strMsgFile = m_lpQQClient->GetMsgLogFullName().c_str();
	strMsgFile.Replace(_T("\\"), _T("/"));

	CString strChatPicDir = m_lpQQClient->GetChatPicFolder().c_str();
	strChatPicDir.Replace(_T("\\"), _T("/"));

	CString strCmdLine;
	strCmdLine.Format(_T("\"%s\" %u %u %u %u %u \"%s\" \"%s\""), 
		strExeName, m_hWnd, 0, m_nGroupNumber, 0, m_nUserNumber, strMsgFile, strChatPicDir);
	LPTSTR lpszCmdLine = _tcsdup(strCmdLine.GetBuffer());
	if (NULL == lpszCmdLine)
		return;

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi = {0};

	si.cb = sizeof(si);

	BOOL bRet = ::CreateProcess(NULL, lpszCmdLine, NULL,
		NULL, FALSE, 0, NULL, NULL, &si, &pi);
	free(lpszCmdLine);
	if (!bRet)
		return;

	m_dwThreadId = pi.dwThreadId;

	::CloseHandle(pi.hProcess);
	::CloseHandle(pi.hThread);
}

// 关闭消息记录浏览窗口
void CGroupChatDlg::CloseMsgLogBrowser()
{
	if (m_dwThreadId != NULL)
	{
		::PostThreadMessage(m_dwThreadId, WM_CLOSE_MSGLOGDLG, 0, 0);
		m_dwThreadId = NULL;
	}
}