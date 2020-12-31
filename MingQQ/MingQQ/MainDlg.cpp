// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

#pragma comment(lib, "winmm.lib")

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->hwnd == m_edtSign.m_hWnd)   
	{
		if (pMsg->message == WM_CHAR && pMsg->wParam == VK_RETURN) 
		{
			SetFocus();
		} 
	}

 	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
 	{
 		return FALSE;
 	}

	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

CMainDlg::CMainDlg(void)
{
	m_nLastMsgType = QQ_MSG_TYPE_BUDDY;
	m_nLastSenderId = 0;

	m_hAppIcon = NULL;
	memset(m_hLoginIcon, 0, sizeof(m_hLoginIcon));
	m_nCurLoginIcon = 0;
	m_hMsgIcon = NULL;
	m_dwLoginTimerId = NULL;
	m_dwMsgTimerId = NULL;

	m_hDlgIcon = m_hDlgSmallIcon = NULL;
	m_fontNickName = NULL;
	memset(&m_stAccountInfo, 0, sizeof(m_stAccountInfo));
}

CMainDlg::~CMainDlg(void)
{
}

BOOL CMainDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	SetWindowPos(HWND_TOPMOST, 989, 64, 300, 600, NULL);

	// set icons
	m_hDlgIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(m_hDlgIcon, TRUE);
	m_hDlgSmallIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(m_hDlgSmallIcon, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	Init();

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	m_QQClient.Init();

	LoadAppIcon(m_QQClient.GetStatus());
	m_TrayIcon.AddIcon(m_hWnd, WM_TRAYICON_NOTIFY, 1, m_hAppIcon, _T("MingQQ"));

	// 加载系统表情列表
	tstring strFileName = ZYM::CPath::GetAppPath() + _T("Face\\FaceConfig.xml");
	m_FaceList.LoadConfigFile(strFileName.c_str());

	// 加载登录帐号列表
	strFileName = ZYM::CPath::GetAppPath()+_T("LoginAccountList.dat");
	m_LoginAccountList.LoadFile(strFileName.c_str());
	



// 	CImageEx img;
// 	img.LoadFromFile(_T("C:\\DefGMemberHeadPic16x16.png"));
// 	img.GrayScale();
// 	img.Save(_T("C:\\1.png"));

// 	Gdiplus::Bitmap * lpImage = new Gdiplus::Bitmap(_T("C:\\DefBuddyHeadPic.png"));
// 
// 	Gdiplus::Bitmap* pThumbnail = (Gdiplus::Bitmap*)lpImage->GetThumbnailImage(16, 16);
// 
// 	CLSID Clsid;
// 	Clsid = GetEncoderClsidByMimeType(L"image/png");
// 	pThumbnail->Save(_T("C:\\1.png"), &Clsid);
// 
// 	pThumbnail->GetHBITMAP()

	StartLogin(m_LoginAccountList.IsAutoLogin());

	// 设置用户头像
	UINT nQQUin = _tcstoul(m_stAccountInfo.szUser, NULL, 10);
	strFileName = m_QQClient.GetUserHeadPicFullName(nQQUin);
	if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefBuddyHeadPic.png");
	m_picHead.SetBitmap(strFileName.c_str());

	return TRUE;
}

void CMainDlg::OnSysCommand(UINT nID, CPoint pt)
{
	if (nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
		return;
	}

	SetMsgHandled(FALSE);
}

void CMainDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	m_SkinMenu.OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CMainDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_SkinMenu.OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CMainDlg::OnGetMinMaxInfo(LPMINMAXINFO lpMMI)
{
	lpMMI->ptMinTrackSize.x = 300;
	lpMMI->ptMinTrackSize.y = 600;
}

void CMainDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (GetFocus() == m_edtSign.m_hWnd)
		SetFocus();
}

void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	m_TrayIcon.OnTimer(nIDEvent);

	if (nIDEvent == m_dwMsgTimerId)		// 来消息闪烁动画
	{
		static BOOL bSwitch = FALSE;

		if (m_dwLoginTimerId != NULL)	// 未登录成功
			return;

		bSwitch = !bSwitch;
		if (bSwitch)
			m_TrayIcon.ModifyIcon(NULL, _T(""));
		else
			m_TrayIcon.ModifyIcon(m_hMsgIcon, _T(""));
	}
	else if (nIDEvent == m_dwLoginTimerId)	// 登录动画
	{
		m_TrayIcon.ModifyIcon(m_hLoginIcon[m_nCurLoginIcon], _T(""));
		m_nCurLoginIcon++;
		if (m_nCurLoginIcon >= 6)
			m_nCurLoginIcon = 0;
	}
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);

	CRect rcClient;
	GetClientRect(&rcClient);

	if (m_btnMainMenu.IsWindow())
		m_btnMainMenu.MoveWindow(6, rcClient.Height()-48, 40, 40);

	if (m_btnSystemSet.IsWindow())
		m_btnSystemSet.MoveWindow(46, rcClient.Height()-30, 22, 22);

	if (m_btnMsgMgr.IsWindow())
		m_btnMsgMgr.MoveWindow(72, rcClient.Height()-30, 22, 22);

	if (m_btnSafe.IsWindow())
		m_btnSafe.MoveWindow(94, rcClient.Height()-30, 62, 22);

	if (m_btnFind.IsWindow())
		m_btnFind.MoveWindow(156, rcClient.Height()-30, 62, 22);

	if (m_btnSign.IsWindow())
		m_btnSign.MoveWindow(56, 54, rcClient.Width()-102, 22);

	if (m_edtSign.IsWindow())
		m_edtSign.MoveWindow(56, 54, rcClient.Width()-102, 22);

	if (m_edtSearch.IsWindow())
		m_edtSearch.MoveWindow(3, 104, rcClient.Width()-6, 27);

	if (m_btnMsgBox.IsWindow())
		m_btnMsgBox.MoveWindow(rcClient.Width()-48, 80, 22, 20);

	if (m_btnChangeExterior.IsWindow())
		m_btnChangeExterior.MoveWindow(rcClient.Width()-26, 80, 20, 20);

	if (m_btnAppMgr.IsWindow())
		m_btnAppMgr.MoveWindow(rcClient.Width()-38, rcClient.bottom-60, 22, 22);

	if (m_tbBottom.IsWindow())
		m_tbBottom.MoveWindow(46, rcClient.bottom-60, 212, 22);

	if (m_TabCtrl.IsWindow())
	{
		int nCount = m_TabCtrl.GetItemCount();
		if (nCount > 0)
		{
			int nWidth = (rcClient.Width()-2) / nCount;
			int nRemainder = (rcClient.Width()-2) % nCount;

			for (int i = 0; i < nCount; i++)
			{
				m_TabCtrl.SetItemSize(i, nWidth, 34, nWidth-19, 19);
			}

			m_TabCtrl.SetItemSize(nCount-1, nWidth+nRemainder, 34, nWidth+nRemainder-19, 19);
		}

		m_TabCtrl.MoveWindow(1, 135, rcClient.right - 2, 34);
	}

	if (m_BuddyListCtrl.IsWindow())
		m_BuddyListCtrl.MoveWindow(1, 135+34, rcClient.Width() - 2, rcClient.Height()-236);

	if (m_GroupListCtrl.IsWindow())
		m_GroupListCtrl.MoveWindow(1, 135+34, rcClient.Width() - 2, rcClient.Height()-236);

	if (m_RecentListCtrl.IsWindow())
		m_RecentListCtrl.MoveWindow(1, 135+34, rcClient.Width() - 2, rcClient.Height()-236);

	if (m_picLogining.IsWindow())
		m_picLogining.MoveWindow((rcClient.Width() - 220) / 2, 76, 220, 150);
	
	if (m_staQQNum.IsWindow())
		m_staQQNum.MoveWindow(rcClient.left, 226, rcClient.Width(), 14);

	if (m_staLogining.IsWindow())
		m_staLogining.MoveWindow(rcClient.left, 240, rcClient.Width(), 16);

	if (m_btnCancel.IsWindow())
		m_btnCancel.MoveWindow((rcClient.Width() - 86) / 2, 304, 86, 30);
}

void CMainDlg::OnHotKey(int nHotKeyID, UINT uModifiers, UINT uVirtKey)
{
	switch (nHotKeyID)
	{
	case 1001:
		{
			OnTrayIconNotify(WM_TRAYICON_NOTIFY, NULL, WM_LBUTTONUP);
		}
		break;
	}
}

void CMainDlg::OnClose()
{
	CloseDialog(IDOK);
}

void CMainDlg::OnDestroy()
{
	if (m_staNickName.IsWindow())
		m_staNickName.DestroyWindow();

	m_btnSystemSet.DestroyWindow();
	//m_TrayIcon.RemoveIcon();
	m_SkinMenu.DestroyMenu();
	if (m_BuddyChatDlg.IsWindow())
		m_BuddyChatDlg.DestroyWindow();
	if (m_GroupChatDlg.IsWindow())
		m_GroupChatDlg.DestroyWindow();

	DestroyAppIcon();
	DestroyLoginIcon();

	if (m_hMsgIcon != NULL)
	{
		::DestroyIcon(m_hMsgIcon);
		m_hMsgIcon = NULL;
	}

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

	if (m_fontNickName != NULL)
	{
		::DeleteObject(m_fontNickName);
		m_fontNickName = NULL;
	}

	::UnregisterHotKey(m_hWnd, 1001);	// 反注册提取消息热键

	// 保存杂项配置
	tstring strFileName = m_QQClient.GetPersonalFolder()+_T("MiscConfig.xml");
	SaveMiscConfig(strFileName.c_str());

	m_QQClient.UnInit();

	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
}

void CMainDlg::OnAppAbout(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CMainDlg::CloseDialog(int nVal)
{
	if (m_dwLoginTimerId != NULL)
	{
		KillTimer(m_dwLoginTimerId);
		m_dwLoginTimerId = NULL;
	}
	if (m_dwMsgTimerId != NULL)
	{
		KillTimer(m_dwMsgTimerId);
		m_dwMsgTimerId = NULL;
	}

	m_TrayIcon.RemoveIcon();
	CloseAllDlg();
	m_CascadeWinManager.Clear();
	ShowWindow(SW_HIDE);

	if (m_QQClient.GetStatus() != QQ_STATUS_OFFLINE)
	{
		m_QQClient.Logout();
	}
	else
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}
}

// 初始化Top工具栏
BOOL CMainDlg::InitTopToolBar()
{
	int nIndex = m_tbTop.AddItem(101, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 35, 20);
	m_tbTop.SetItemText(nIndex, _T("10"));
	m_tbTop.SetItemToolTipText(nIndex, _T("QQ空间信息中心\r\n  好友动态(10+)"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("MainTopToolBar\\qzone.png"));

	nIndex = m_tbTop.AddItem(102, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 22, 20);
	m_tbTop.SetItemToolTipText(nIndex, _T("腾讯微博"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("MainTopToolBar\\wblog.png"));

	nIndex = m_tbTop.AddItem(103, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 35, 20);
	m_tbTop.SetItemText(nIndex, _T("99"));
	m_tbTop.SetItemToolTipText(nIndex, _T("QQ邮箱\r\n  收件箱(84)\r\n  群邮件(20)\r\n  漂流瓶(1)"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("MainTopToolBar\\mail.png"));

	nIndex = m_tbTop.AddItem(104, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 22, 20);
	m_tbTop.SetItemToolTipText(nIndex, _T("朋友网"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("MainTopToolBar\\friend.png"));

	nIndex = m_tbTop.AddItem(105, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 22, 20);
	m_tbTop.SetItemToolTipText(nIndex, _T("腾讯网购"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("MainTopToolBar\\paipai.png"));

	nIndex = m_tbTop.AddItem(106, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 22, 20);
	m_tbTop.SetItemToolTipText(nIndex, _T("QQ钱包"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("MainTopToolBar\\purse.png"));

	nIndex = m_tbTop.AddItem(107, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 22, 20);
	m_tbTop.SetItemToolTipText(nIndex, _T("搜搜个人中心\r\n  搜搜问问邀请你参加新手任务"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("MainTopToolBar\\soso.png"));

	nIndex = m_tbTop.AddItem(108, STBI_STYLE_BUTTON);
	m_tbTop.SetItemSize(nIndex, 22, 20);
	m_tbTop.SetItemToolTipText(nIndex, _T("腾讯网我的资讯"));
	m_tbTop.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTop.SetItemIconPic(nIndex, _T("MainTopToolBar\\Today.png"));

	m_tbTop.SetLeftTop(2, 0);
	m_tbTop.SetTransparent(TRUE, m_SkinDlg.GetBgDC());

	CRect rcTopToolBar(4, 80, 4+210, 80+20);
	m_tbTop.Create(m_hWnd, rcTopToolBar, NULL, WS_CHILD|WS_VISIBLE, NULL, ID_TOOLBAR_TOP);

	return TRUE;
}

// 初始化Bottom工具栏
BOOL CMainDlg::InitBottomToolBar()
{
	int nIndex = m_tbBottom.AddItem(201, STBI_STYLE_BUTTON);
	m_tbBottom.SetItemSize(nIndex, 22, 22);
	m_tbBottom.SetItemPadding(nIndex, 5);
	m_tbBottom.SetItemToolTipText(nIndex, _T("手机生活"));
	m_tbBottom.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbBottom.SetItemIconPic(nIndex, _T("MainBottomToolBar\\WirelessLive.png"));

	nIndex = m_tbBottom.AddItem(202, STBI_STYLE_BUTTON);
	m_tbBottom.SetItemSize(nIndex, 22, 22);
	m_tbBottom.SetItemPadding(nIndex, 5);
	m_tbBottom.SetItemToolTipText(nIndex, _T("QQ游戏"));
	m_tbBottom.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbBottom.SetItemIconPic(nIndex, _T("MainBottomToolBar\\QQGame.png"));

	nIndex = m_tbBottom.AddItem(203, STBI_STYLE_BUTTON);
	m_tbBottom.SetItemSize(nIndex, 22, 22);
	m_tbBottom.SetItemPadding(nIndex, 5);
	m_tbBottom.SetItemToolTipText(nIndex, _T("QQ宠物"));
	m_tbBottom.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbBottom.SetItemIconPic(nIndex, _T("MainBottomToolBar\\QQPet.png"));

	nIndex = m_tbBottom.AddItem(204, STBI_STYLE_BUTTON);
	m_tbBottom.SetItemSize(nIndex, 22, 22);
	m_tbBottom.SetItemPadding(nIndex, 5);
	m_tbBottom.SetItemToolTipText(nIndex, _T("QQ音乐"));
	m_tbBottom.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbBottom.SetItemIconPic(nIndex, _T("MainBottomToolBar\\QQMusic.png"));

	nIndex = m_tbBottom.AddItem(205, STBI_STYLE_BUTTON);
	m_tbBottom.SetItemSize(nIndex, 22, 22);
	m_tbBottom.SetItemPadding(nIndex, 5);
	m_tbBottom.SetItemToolTipText(nIndex, _T("腾讯视频"));
	m_tbBottom.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbBottom.SetItemIconPic(nIndex, _T("MainBottomToolBar\\QQLive.png"));

	nIndex = m_tbBottom.AddItem(206, STBI_STYLE_BUTTON);
	m_tbBottom.SetItemSize(nIndex, 22, 22);
	m_tbBottom.SetItemPadding(nIndex, 5);
	m_tbBottom.SetItemToolTipText(nIndex, _T("QQ旅游"));
	m_tbBottom.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbBottom.SetItemIconPic(nIndex, _T("MainBottomToolBar\\Tourism.png"));

	nIndex = m_tbBottom.AddItem(207, STBI_STYLE_BUTTON);
	m_tbBottom.SetItemSize(nIndex, 22, 22);
	m_tbBottom.SetItemPadding(nIndex, 5);
	m_tbBottom.SetItemToolTipText(nIndex, _T("QQ电脑管家"));
	m_tbBottom.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbBottom.SetItemIconPic(nIndex, _T("MainBottomToolBar\\QQPCMgr.png"));

	nIndex = m_tbBottom.AddItem(208, STBI_STYLE_BUTTON);
	m_tbBottom.SetItemSize(nIndex, 22, 22);
	m_tbBottom.SetItemPadding(nIndex, 5);
	m_tbBottom.SetItemToolTipText(nIndex, _T("拍拍购物"));
	m_tbBottom.SetItemBgPic(nIndex, NULL, _T("aio_toolbar_highligh.png"), 
		_T("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbBottom.SetItemIconPic(nIndex, _T("MainBottomToolBar\\PaiPai.png"));

	m_tbBottom.SetTransparent(TRUE, m_SkinDlg.GetBgDC());

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcBottomToolBar(46, rcClient.bottom-60, 46+212, (rcClient.bottom-60)+22);
	m_tbBottom.Create(m_hWnd, rcBottomToolBar, NULL, WS_CHILD|WS_VISIBLE, NULL, ID_TOOLBAR_BOTTOM);

	return TRUE;
}

// 初始化Tab栏
BOOL CMainDlg::InitTabCtrl()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	int nWidth = (rcClient.Width()-2) / 5;
	int nRemainder = (rcClient.Width()-2) % 5;

	int nIndex = m_TabCtrl.AddItem(301, STCI_STYLE_DROPDOWN);
	m_TabCtrl.SetItemSize(nIndex, nWidth, 34, nWidth-19, 19);
	m_TabCtrl.SetItemToolTipText(nIndex, _T("联系人"));
	m_TabCtrl.SetItemIconPic(nIndex, _T("MainTabCtrl\\icon_contacts_normal.png"),
		_T("MainTabCtrl\\icon_contacts_selected.png"));

	nIndex = m_TabCtrl.AddItem(302, STCI_STYLE_DROPDOWN);
	m_TabCtrl.SetItemSize(nIndex, nWidth, 34, nWidth-19, 19);
	m_TabCtrl.SetItemToolTipText(nIndex, _T("朋友"));
	m_TabCtrl.SetItemIconPic(nIndex, _T("MainTabCtrl\\FriendSocial_TabBtn_Normal.png"),
		_T("MainTabCtrl\\FriendSocial_TabBtn_Focus.png"));

	nIndex = m_TabCtrl.AddItem(303, STCI_STYLE_DROPDOWN);
	m_TabCtrl.SetItemSize(nIndex, nWidth, 34, nWidth-19, 19);
	m_TabCtrl.SetItemToolTipText(nIndex, _T("群/讨论组"));
	m_TabCtrl.SetItemIconPic(nIndex, _T("MainTabCtrl\\icon_group_normal.png"),
		_T("MainTabCtrl\\icon_group_selected.png"));

	nIndex = m_TabCtrl.AddItem(304, STCI_STYLE_BUTTON);
	m_TabCtrl.SetItemSize(nIndex, nWidth, 34, nWidth-19, 19);
	m_TabCtrl.SetItemToolTipText(nIndex, _T("微博"));
	m_TabCtrl.SetItemIconPic(nIndex, _T("MainTabCtrl\\WBlog_TabBtn_Normal_Msg.png"),
		_T("MainTabCtrl\\WBlog_TabBtn_Focus.png"));

	nIndex = m_TabCtrl.AddItem(305, STCI_STYLE_DROPDOWN);
	m_TabCtrl.SetItemSize(nIndex, nWidth+nRemainder, 34, nWidth+nRemainder-19, 19);
	m_TabCtrl.SetItemToolTipText(nIndex, _T("最近联系人"));
	m_TabCtrl.SetItemIconPic(nIndex, _T("MainTabCtrl\\icon_last_normal.png"),
		_T("MainTabCtrl\\icon_last_selected.png"));

	m_TabCtrl.SetBgPic(_T("MainTabCtrl\\main_tab_bkg.png"), CRect(5,1,5,1));
	m_TabCtrl.SetItemsBgPic(NULL, _T("MainTabCtrl\\main_tab_highlight.png"), 
		_T("MainTabCtrl\\main_tab_check.png"), CRect(5,1,5,1));
	m_TabCtrl.SetItemsArrowPic(_T("MainTabCtrl\\main_tabbtn_highlight.png"), 
		_T("MainTabCtrl\\main_tabbtn_down.png"));

	m_TabCtrl.SetTransparent(TRUE, m_SkinDlg.GetBgDC());

	CRect rcTabCtrl(1, 135, rcClient.right - 1, 135+34);
	m_TabCtrl.Create(m_hWnd, rcTabCtrl, NULL, WS_CHILD | WS_VISIBLE, NULL, ID_TABCTRL_MAIN, NULL);

	m_TabCtrl.SetCurSel(0);

	return TRUE;
}

// 初始化好友列表控件
BOOL CMainDlg::InitBuddyListCtrl()
{
	m_BuddyListCtrl.SetMargin(CRect(2,0,2,0));
	m_BuddyListCtrl.SetBgPic(_T("BuddyList\\Bg.png"));
	m_BuddyListCtrl.SetBuddyTeamHotBgPic(_T("BuddyList\\BuddyTeamHotBg.png"));
	m_BuddyListCtrl.SetBuddyItemHotBgPic(_T("BuddyList\\BuddyItemHotBg.png"), CRect(1,1,1,1));
	m_BuddyListCtrl.SetBuddyItemSelBgPic(_T("BuddyList\\BuddyItemSelBg.png"), CRect(1,1,1,1));
	m_BuddyListCtrl.SetHeadFramePic(_T("BuddyList\\Padding4Select.png"), CRect(6,6,6,6));
	m_BuddyListCtrl.SetNormalArrowPic(_T("BuddyList\\MainPanel_FolderNode_collapseTexture.png"));
	m_BuddyListCtrl.SetHotArrowPic(_T("BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_BuddyListCtrl.SetSelArrowPic(_T("BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_BuddyListCtrl.SetNormalExpArrowPic(_T("BuddyList\\MainPanel_FolderNode_expandTexture.png"));
	m_BuddyListCtrl.SetHotExpArrowPic(_T("BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_BuddyListCtrl.SetSelExpArrowPic(_T("BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_BuddyListCtrl.SetStdGGHeadPic(_T("BuddyList\\trad_boy.png"));
	m_BuddyListCtrl.SetStdMMHeadPic(_T("BuddyList\\trad_girl.png"));
	m_BuddyListCtrl.SetStyle(BLC_BIG_ICON_STYLE);
	m_BuddyListCtrl.SetShowBigIconInSel(TRUE);
	m_BuddyListCtrl.SetBuddyTeamHeight(24);
	m_BuddyListCtrl.SetBuddyItemHeightInBigIcon(54);
	m_BuddyListCtrl.SetBuddyItemHeightInSmallIcon(28);
	m_BuddyListCtrl.SetBuddyItemHeightInStandardIcon(24);
	m_BuddyListCtrl.SetBuddyItemPadding(1);

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcListCtrl(1, 135+34, rcClient.right - 1, (135+34)+(rcClient.Height()-236));
	m_BuddyListCtrl.Create(m_hWnd, rcListCtrl, NULL, WS_CHILD|WS_VISIBLE, NULL, ID_LISTCTRL_BUDDY);

	return TRUE;
}

// 初始化群列表控件
BOOL CMainDlg::InitGroupListCtrl()
{
	m_GroupListCtrl.SetMargin(CRect(2,0,2,0));
	m_GroupListCtrl.SetBgPic(_T("BuddyList\\Bg.png"));
	m_GroupListCtrl.SetBuddyTeamHotBgPic(_T("BuddyList\\BuddyTeamHotBg.png"));
	m_GroupListCtrl.SetBuddyItemHotBgPic(_T("BuddyList\\BuddyItemHotBg.png"), CRect(1,1,1,1));
	m_GroupListCtrl.SetBuddyItemSelBgPic(_T("BuddyList\\BuddyItemSelBg.png"), CRect(1,1,1,1));
	m_GroupListCtrl.SetHeadFramePic(_T("BuddyList\\Padding4Select.png"), CRect(6,6,6,6));
	m_GroupListCtrl.SetNormalArrowPic(_T("BuddyList\\MainPanel_FolderNode_collapseTexture.png"));
	m_GroupListCtrl.SetHotArrowPic(_T("BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_GroupListCtrl.SetSelArrowPic(_T("BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_GroupListCtrl.SetNormalExpArrowPic(_T("BuddyList\\MainPanel_FolderNode_expandTexture.png"));
	m_GroupListCtrl.SetHotExpArrowPic(_T("BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_GroupListCtrl.SetSelExpArrowPic(_T("BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_GroupListCtrl.SetStdGGHeadPic(_T("BuddyList\\trad_boy.png"));
	m_GroupListCtrl.SetStdMMHeadPic(_T("BuddyList\\trad_girl.png"));
	m_GroupListCtrl.SetStyle(BLC_SMALL_ICON_STYLE);
	m_GroupListCtrl.SetShowBigIconInSel(TRUE);
	m_GroupListCtrl.SetBuddyTeamHeight(24);
	m_GroupListCtrl.SetBuddyItemHeightInBigIcon(54);
	m_GroupListCtrl.SetBuddyItemHeightInSmallIcon(28);
	m_GroupListCtrl.SetBuddyItemHeightInStandardIcon(24);
	m_GroupListCtrl.SetBuddyItemPadding(1);

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcListCtrl(1, 135+34, rcClient.right - 1, (135+34)+(rcClient.Height()-236));
	m_GroupListCtrl.Create(m_hWnd, rcListCtrl, NULL, WS_CHILD, NULL, ID_LISTCTRL_GROUP);

	return TRUE;
}

// 初始化最近联系人列表控件
BOOL CMainDlg::InitRecentListCtrl()
{
	m_RecentListCtrl.SetMargin(CRect(2,0,2,0));
	m_RecentListCtrl.SetBgPic(_T("BuddyList\\Bg.png"));
	m_RecentListCtrl.SetBuddyTeamHotBgPic(_T("BuddyList\\BuddyTeamHotBg.png"));
	m_RecentListCtrl.SetBuddyItemHotBgPic(_T("BuddyList\\BuddyItemHotBg.png"), CRect(1,1,1,1));
	m_RecentListCtrl.SetBuddyItemSelBgPic(_T("BuddyList\\BuddyItemSelBg.png"), CRect(1,1,1,1));
	m_RecentListCtrl.SetHeadFramePic(_T("BuddyList\\Padding4Select.png"), CRect(6,6,6,6));
	//m_RecentListCtrl.AddBuddyItemSmallIcon(int nID, LPCTSTR lpszToolTipText, LPCTSTR lpszFileName);
	m_RecentListCtrl.SetNormalArrowPic(_T("BuddyList\\MainPanel_FolderNode_collapseTexture.png"));
	m_RecentListCtrl.SetHotArrowPic(_T("BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_RecentListCtrl.SetSelArrowPic(_T("BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_RecentListCtrl.SetNormalExpArrowPic(_T("BuddyList\\MainPanel_FolderNode_expandTexture.png"));
	m_RecentListCtrl.SetHotExpArrowPic(_T("BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_RecentListCtrl.SetSelExpArrowPic(_T("BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_RecentListCtrl.SetStdGGHeadPic(_T("BuddyList\\trad_boy.png"));
	m_RecentListCtrl.SetStdMMHeadPic(_T("BuddyList\\trad_girl.png"));
	m_RecentListCtrl.SetStyle(BLC_BIG_ICON_STYLE);
	m_RecentListCtrl.SetShowBigIconInSel(TRUE);
	m_RecentListCtrl.SetBuddyTeamHeight(24);
	m_RecentListCtrl.SetBuddyItemHeightInBigIcon(54);
	m_RecentListCtrl.SetBuddyItemHeightInSmallIcon(28);
	m_RecentListCtrl.SetBuddyItemHeightInStandardIcon(24);
	m_RecentListCtrl.SetBuddyItemPadding(1);

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcListCtrl(1, 135+34, rcClient.right - 1, (135+34)+(rcClient.Height()-236));
	m_RecentListCtrl.Create(m_hWnd, rcListCtrl, NULL, WS_CHILD, NULL, ID_LISTCTRL_RECENT);

	return TRUE;
}

BOOL CMainDlg::Init()
{
	m_SkinDlg.SetBgPic(_T("main_panel_bg.png"), CRect(2, 135, 2, 67));
	//m_SkinDlg.SetTitleBarBgPic(_T("main_panel_title.png"));
	m_SkinDlg.SetMinSysBtnPic(_T("SysBtn\\btn_mini_normal.png"), 
		_T("SysBtn\\btn_mini_highlight.png"), _T("SysBtn\\btn_mini_down.png"));
	m_SkinDlg.SetMaxSysBtnPic(_T("SysBtn\\btn_max_normal.png"), 
		_T("SysBtn\\btn_max_highlight.png"), _T("SysBtn\\btn_max_down.png"));
	m_SkinDlg.SetRestoreSysBtnPic(_T("SysBtn\\btn_restore_normal.png"), 
		_T("SysBtn\\btn_restore_highlight.png"), _T("SysBtn\\btn_restore_down.png"));
	m_SkinDlg.SetCloseSysBtnPic(_T("SysBtn\\btn_close_normal.png"), 
		_T("SysBtn\\btn_close_highlight.png"), _T("SysBtn\\btn_close_down.png"));
	m_SkinDlg.SubclassWindow(m_hWnd);
	m_SkinDlg.SetTitleText(_T("MingQQ"));

	HDC hDlgBgDC = m_SkinDlg.GetBgDC();

	CRect rcClient;
	GetClientRect(&rcClient);

	m_btnMainMenu.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnMainMenu.SetTransparent(TRUE, hDlgBgDC);
	m_btnMainMenu.SetBgPic(_T("menu_btn_normal.png"), 
		_T("menu_btn_highlight.png"), _T("menu_btn_highlight.png"), _T("menu_btn_normal.png"));
	m_btnMainMenu.SubclassWindow(GetDlgItem(ID_BTN_MAIN_MENU));
	m_btnMainMenu.MoveWindow(6, rcClient.Height()-48, 40, 40, TRUE);
	m_btnMainMenu.SetToolTipText(_T("主菜单"));

	m_btnSystemSet.SetButtonType(SKIN_ICON_BUTTON);
	m_btnSystemSet.SetTransparent(TRUE, hDlgBgDC);
	m_btnSystemSet.SetBgPic(NULL, _T("allbtn_highlight.png"), _T("allbtn_down.png"), NULL);
	m_btnSystemSet.SetIconPic(_T("SystemSet.png"));
	m_btnSystemSet.SubclassWindow(GetDlgItem(ID_BTN_SYSTEM_SET));
	m_btnSystemSet.MoveWindow(46, rcClient.Height()-30, 22, 22, TRUE);
	m_btnSystemSet.SetToolTipText(_T("打开系统设置"));

	m_btnMsgMgr.SetButtonType(SKIN_ICON_BUTTON);
	m_btnMsgMgr.SetTransparent(TRUE, hDlgBgDC);
	m_btnMsgMgr.SetBgPic(NULL, _T("allbtn_highlight.png"), _T("allbtn_down.png"), NULL);
	m_btnMsgMgr.SetIconPic(_T("message.png"));
	m_btnMsgMgr.SubclassWindow(GetDlgItem(ID_BTN_MSG_MGR));
	m_btnMsgMgr.MoveWindow(72, rcClient.Height()-30, 22, 22, TRUE);
	m_btnMsgMgr.SetToolTipText(_T("打开消息管理器"));

	m_btnSafe.SetButtonType(SKIN_ICON_BUTTON);
	m_btnSafe.SetTransparent(TRUE, hDlgBgDC);
	m_btnSafe.SetBgPic(NULL, _T("allbtn_highlight2.png"), _T("allbtn_down2.png"), NULL);
	m_btnSafe.SetIconPic(_T("QQSafe.png"));
	m_btnSafe.SubclassWindow(GetDlgItem(ID_BTN_SAFE));
	m_btnSafe.MoveWindow(94, rcClient.Height()-30, 62, 22, TRUE);
	m_btnSafe.SetToolTipText(_T("打开安全概况"));

	m_btnFind.SetButtonType(SKIN_ICON_BUTTON);
	m_btnFind.SetTransparent(TRUE, hDlgBgDC);
	m_btnFind.SetBgPic(NULL, _T("allbtn_highlight2.png"), _T("allbtn_down2.png"), NULL);
	m_btnFind.SetIconPic(_T("find.png"));
	m_btnFind.SubclassWindow(GetDlgItem(ID_BTN_FIND));
	m_btnFind.MoveWindow(156, rcClient.Height()-30, 62, 22, TRUE);
	m_btnFind.SetToolTipText(_T("查找联系人"));

	m_btnSign.SetButtonType(SKIN_ICON_BUTTON);
	m_btnSign.SetTransparent(TRUE, hDlgBgDC);
	m_btnSign.SetBgPic(NULL, _T("allbtn_highlight2.png"), _T("allbtn_down2.png"), NULL, CRect(3,0,3,0));
	m_btnSign.SetTextAlign(DT_LEFT);
	m_btnSign.SubclassWindow(GetDlgItem(ID_BTN_SIGN));
	m_btnSign.MoveWindow(56, 54, rcClient.Width()-102, 22, TRUE);
	m_btnSign.SetWindowText(_T("这家伙很懒,什么都没有留下。"));
	m_btnSign.SetToolTipText(_T("这家伙很懒,什么都没有留下。"));

	m_picHead.SetTransparent(TRUE, hDlgBgDC);
	m_picHead.SetShowCursor(TRUE);
	m_picHead.SetBgPic(_T("HeadCtrl\\Padding4Normal.png"), _T("HeadCtrl\\Padding4Hot.png"), _T("HeadCtrl\\Padding4Hot.png"));
	m_picHead.SubclassWindow(GetDlgItem(ID_PIC_HEAD));
	m_picHead.MoveWindow(6, 32, 48, 48, TRUE);
	m_picHead.SetToolTipText(_T("个人资料完整度30%，完善个人资料"));

	m_staNickName.SetTransparent(TRUE, hDlgBgDC);
	m_staNickName.SubclassWindow(GetDlgItem(ID_STATIC_NICKNAME));
	m_staNickName.MoveWindow(95, 35, 220, 14, FALSE);
	m_staNickName.SetWindowText(_T("昵称"));

	CFontHandle font = (HFONT)::SendMessage(m_hWnd, WM_GETFONT, 0, 0L);
	LOGFONT lf = {0};
	font.GetLogFont(&lf);
	lf.lfHeight = 15;
	lf.lfWeight = FW_BOLD;
	m_fontNickName = ::CreateFontIndirect(&lf); 
	m_staNickName.SetFont(m_fontNickName);

	m_SkinMenu.SetBgPic(_T("Menu\\menu_left_bg.png"), _T("Menu\\menu_right_bg.png"));
	m_SkinMenu.SetSelectedPic(_T("Menu\\menu_selected.png"));
	m_SkinMenu.SetSepartorPic(_T("Menu\\menu_separtor.png"));
	m_SkinMenu.SetArrowPic(_T("Menu\\menu_arrow.png"));
	m_SkinMenu.SetCheckPic(_T("Menu\\menu_check.png"));
	m_SkinMenu.SetTextColor(RGB(0, 20, 35));
	m_SkinMenu.SetSelTextColor(RGB(254, 254, 254));
	m_SkinMenu.LoadMenu(ID_MENU_MAIN_PANEL);

	DWORD dwMenuIDs[] = {ID_MENU_IMONLINE, ID_MENU_QME, ID_MENU_AWAY, 
		ID_MENU_BUSY, ID_MENU_MUTE, ID_MENU_INVISIBLE, ID_MENU_IMOFFLINE, 
		ID_MENU_LOCK, ID_MENU_GROUP_HOMEPAGE};
	CString strFileNames[] = {_T("Status\\imonline.png"), _T("Status\\Qme.png"), 
		_T("Status\\away.png"), _T("Status\\busy.png"), _T("Status\\mute.png"), 
		_T("Status\\invisible.png"), _T("Status\\imoffline.png"), _T("lock20.png"),
		_T("groupmainpage.png")};

	CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(0);
	for (int i = 0; i < 9; i++)
	{
		PopupMenu.SetIcon(dwMenuIDs[i], FALSE, strFileNames[i], strFileNames[i]);
	}

	PopupMenu = m_SkinMenu.GetSubMenu(2);
	for (int i = 0; i < 9; i++)
	{
		PopupMenu.SetIcon(dwMenuIDs[i], FALSE, strFileNames[i], strFileNames[i]);
	}

	PopupMenu = m_SkinMenu.GetSubMenu(3);
	PopupMenu.SetIcon(0, TRUE, _T("modehead.png"), _T("modehead.png"));
	PopupMenu = m_SkinMenu.GetSubMenu(4);
	PopupMenu.SetIcon(0, TRUE, _T("modehead.png"), _T("modehead.png"));
	PopupMenu = m_SkinMenu.GetSubMenu(5);
	PopupMenu.SetIcon(0, TRUE, _T("modehead.png"), _T("modehead.png"));
	PopupMenu = m_SkinMenu.GetSubMenu(6);
	PopupMenu.SetIcon(0, TRUE, _T("modehead.png"), _T("modehead.png"));

	PopupMenu = m_SkinMenu.GetSubMenu(0);

	m_btnStatus.SetButtonType(SKIN_MENU_BUTTON);
	m_btnStatus.SetTransparent(TRUE, hDlgBgDC);
	m_btnStatus.SetBgPic(NULL, _T("menubtn_highlight.png"), _T("menubtn_highlight.png"), NULL);
	m_btnStatus.SetArrowPic(_T("MainPanel_FolderNode_expandTexture.png"));
	m_btnStatus.SetIconPic(_T("Status\\imonline.png"));
	m_btnStatus.SubclassWindow(GetDlgItem(ID_BTN_STATUS));
	m_btnStatus.MoveWindow(54, 30, 35, 22, TRUE);
	m_btnStatus.SetMenu(PopupMenu.m_hMenu);

	m_edtSign.SetBgNormalPic(_T("SignEditBg.png"), CRect(1,1,1,1));
	m_edtSign.SubclassWindow(GetDlgItem(ID_EDIT_SIGN));
	m_edtSign.MoveWindow(56, 54, rcClient.Width()-102, 22, TRUE);
	m_edtSign.ShowWindow(SW_HIDE);

	m_edtSearch.SetBgNormalPic(_T("SearchBar\\bg.png"), CRect(3,3,3,3));
	m_edtSearch.SetIconPic(_T("SearchBar\\main_search_normal.png"));
	m_edtSearch.SetDefaultText(_T("搜索联系人，网页信息和问问答案"));
	m_edtSearch.SubclassWindow(GetDlgItem(ID_EDIT_SEARCH));
	m_edtSearch.MoveWindow(3, 104, rcClient.Width()-6, 27, TRUE);

	m_btnMsgBox.SetButtonType(SKIN_ICON_BUTTON);
	m_btnMsgBox.SetTransparent(TRUE, hDlgBgDC);
	m_btnMsgBox.SetBgPic(NULL, _T("allbtn_highlight.png"), _T("allbtn_down.png"), NULL);
	m_btnMsgBox.SetIconPic(_T("MsgBox.png"));
	m_btnMsgBox.SubclassWindow(GetDlgItem(ID_BTN_MSG_BOX));
	m_btnMsgBox.MoveWindow(rcClient.Width()-48, 80, 22, 20, TRUE);
	m_btnMsgBox.SetToolTipText(_T("打开消息盒子"));

	m_btnChangeExterior.SetButtonType(SKIN_ICON_BUTTON);
	m_btnChangeExterior.SetTransparent(TRUE, hDlgBgDC);
	m_btnChangeExterior.SetBgPic(NULL, _T("allbtn_highlight.png"), _T("allbtn_down.png"), NULL);
	m_btnChangeExterior.SetIconPic(_T("colour.png"));
	m_btnChangeExterior.SubclassWindow(GetDlgItem(ID_BTN_CHANGE_EXTERIOR));
	m_btnChangeExterior.MoveWindow(rcClient.Width()-26, 80, 20, 20, TRUE);
	m_btnChangeExterior.SetToolTipText(_T("更改外观"));

	m_btnAppMgr.SetButtonType(SKIN_ICON_BUTTON);
	m_btnAppMgr.SetTransparent(TRUE, hDlgBgDC);
	m_btnAppMgr.SetBgPic(NULL, _T("allbtn_highlight.png"), _T("allbtn_down.png"), NULL);
	m_btnAppMgr.SetIconPic(_T("appbox_mgr_btn.png"));
	m_btnAppMgr.SubclassWindow(GetDlgItem(ID_BTN_APP_MGR));
	m_btnAppMgr.MoveWindow(rcClient.Width()-38, rcClient.bottom-60, 22, 22, TRUE);
	m_btnAppMgr.SetToolTipText(_T("打开应用管理器"));

	m_picLogining.SetTransparent(TRUE, hDlgBgDC);
	m_picLogining.SubclassWindow(GetDlgItem(ID_PIC_LOGINING));
	m_picLogining.MoveWindow((rcClient.Width() - 220) / 2, 76, 220, 150, TRUE);

	m_staQQNum.SetTransparent(TRUE, hDlgBgDC);
	m_staQQNum.SubclassWindow(GetDlgItem(ID_STATIC_QQNUM));
	m_staQQNum.MoveWindow(rcClient.left, 226, rcClient.Width(), 14, FALSE);

	m_staLogining.SetTransparent(TRUE, hDlgBgDC);
	m_staLogining.SubclassWindow(GetDlgItem(ID_STATIC_LOGINING));
	m_staLogining.MoveWindow(rcClient.left, 240, rcClient.Width(), 16, FALSE);

	m_btnCancel.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnCancel.SetTransparent(TRUE, hDlgBgDC);
	m_btnCancel.SetBgPic(_T("Button\\login_btn_normal.png"), _T("Button\\login_btn_highlight.png"),
		_T("Button\\login_btn_down.png"), _T("Button\\login_btn_focus.png"));
	m_btnCancel.SetRound(4, 4);
	m_btnCancel.SubclassWindow(GetDlgItem(ID_BTN_CANCEL));
	m_btnCancel.MoveWindow((rcClient.Width() - 86) / 2, 304, 86, 30, TRUE);

	InitTopToolBar();		// 初始化Top工具栏
	InitBottomToolBar();	// 初始化Bottom工具栏
	InitTabCtrl();			// 初始化Tab栏
	InitBuddyListCtrl();	// 初始化好友列表控件
	InitGroupListCtrl();	// 初始化群列表控件
	InitRecentListCtrl();	// 初始化最近联系人列表控件

	return TRUE;
}

void CMainDlg::UnInit()
{

}

// 显示指定面板函数(bShow：TRUE表示显示主面板，FALSE表示显示登录面板)
void CMainDlg::ShowPanel(BOOL bShow)
{
	int nShow = bShow ? SW_HIDE : SW_SHOW;
	m_picLogining.ShowWindow(nShow);
	m_staQQNum.ShowWindow(nShow);
	m_staLogining.ShowWindow(nShow);
	m_btnCancel.ShowWindow(nShow);

	nShow = bShow ? SW_SHOW : SW_HIDE;
	m_btnMainMenu.ShowWindow(nShow);
	m_btnSystemSet.ShowWindow(nShow);
	m_btnMsgMgr.ShowWindow(nShow);
	m_btnSafe.ShowWindow(nShow);
	m_btnFind.ShowWindow(nShow);
	m_btnStatus.ShowWindow(nShow);
	m_edtSearch.ShowWindow(nShow);
	m_picHead.ShowWindow(nShow);
	m_staNickName.ShowWindow(nShow);
	m_btnSign.ShowWindow(nShow);
	m_tbTop.ShowWindow(nShow);
	m_tbBottom.ShowWindow(nShow);
	m_btnMsgBox.ShowWindow(nShow);
	m_btnChangeExterior.ShowWindow(nShow);
	m_btnAppMgr.ShowWindow(nShow);;
	m_TabCtrl.ShowWindow(nShow);
	m_BuddyListCtrl.ShowWindow(nShow);

	if (bShow)	// 显示主面板
	{
		m_SkinDlg.SetBgPic(_T("main_panel_bg.png"), CRect(2, 135, 2, 67));
		m_picLogining.SetBitmap(NULL, TRUE);
		StatusMenuBtn_SetIconPic(m_btnStatus, m_QQClient.GetStatus());
	}
	else		// 显示登录面板
	{
		m_SkinDlg.SetBgPic(_T("LoginPanel_window_windowBkg.png"), CRect(4, 65, 4, 4));

		tstring strFileName = ZYM::CPath::GetAppPath() + _T("Image\\Logining.gif");
		m_picLogining.SetBitmap(strFileName.c_str(), TRUE);

		m_staQQNum.SetWindowText(m_stAccountInfo.szUser);
		m_staLogining.SetWindowText(_T("正在登录"));
	}
}

void CMainDlg::StartLogin(BOOL bAutoLogin/* = FALSE*/)
{
	if (bAutoLogin)
	{
		BOOL bRet = m_LoginAccountList.GetLastLoginAccountInfo(&m_stAccountInfo);
		if (!bRet)
			return;
	}
	else
	{
		LoadAppIcon(m_QQClient.GetStatus());
		m_TrayIcon.AddIcon(m_hWnd, WM_TRAYICON_NOTIFY, 1, m_hAppIcon, _T("MingQQ"));

		ShowWindow(SW_HIDE);

		m_LoginDlg.m_lpQQClient = &m_QQClient;
		m_LoginDlg.m_pLoginAccountList = &m_LoginAccountList;
		if (m_LoginDlg.DoModal(m_hWnd) != IDOK)	// 显示登录对话框
		{
			CloseDialog(IDOK);
			return;
		}
		m_LoginDlg.GetLoginAccountInfo(&m_stAccountInfo);
	}

	ShowPanel(FALSE);		// 显示登录面板
	ShowWindow(SW_SHOW);

	LoadLoginIcon();
	m_dwLoginTimerId = SetTimer(1, 200, NULL);

	m_QQClient.SetUser(m_stAccountInfo.szUser, m_stAccountInfo.szPwd);
	m_QQClient.SetLoginStatus((QQ_STATUS)m_stAccountInfo.nStatus);
	m_QQClient.SetCallBackWnd(m_hWnd);
	m_QQClient.Login();
}

LRESULT CMainDlg::OnTrayIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// wParam为uID, lParam为鼠标消息
	m_TrayIcon.OnTrayIconNotify(wParam, lParam);

	UINT uID = (UINT)wParam;
	UINT uIconMsg = (UINT)lParam;

	switch (uIconMsg)
	{
	case WM_LBUTTONUP:
		OnTrayIcon_LButtunUp();
		break;
	case WM_RBUTTONUP:
		OnTrayIcon_RButtunUp();
		break;
	case WM_MOUSEHOVER:
		OnTrayIcon_MouseHover();
		break;
	case WM_MOUSELEAVE:
		OnTrayIcon_MouseLeave();
		break;
	}
	return 0;
}

void CMainDlg::OnMenu_ShowMainPanel(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	if (m_LoginDlg.IsWindow())
	{
		m_LoginDlg.ShowWindow(SW_SHOW);
		m_LoginDlg.SetFocus();
	}
	else if (IsWindow())
	{
		ShowWindow(SW_SHOW);
		SetFocus();
	}
}

void CMainDlg::OnMenu_Exit(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	if (m_LoginDlg.IsWindow())
		m_LoginDlg.PostMessage(WM_CLOSE);
	else if (IsWindow())
		PostMessage(WM_CLOSE);
}

void CMainDlg::OnBtn_Sign(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CString strText;
	m_btnSign.GetWindowText(strText);
	m_edtSign.SetWindowText(strText);

	m_btnSign.ShowWindow(SW_HIDE);
	m_edtSign.ShowWindow(SW_SHOW);

	m_edtSign.SetSel(0, -1);
	m_edtSign.SetFocus();
}

LRESULT CMainDlg::OnTabCtrlDropDown(LPNMHDR pnmh)
{
	CSkinMenu PopupMenu;
	CRect rcItem;
	int nCurSel, nIndex;

	nCurSel = m_TabCtrl.GetCurSel();

	switch (nCurSel)
	{
	case 0:
		nIndex = 3;
		break;

	case 1:
		nIndex = 4;
		break;

	case 2:
		nIndex = 5;
		break;

	case 4:
		nIndex = 6;
		break;

	default:
		return 0;
	}

	PopupMenu = m_SkinMenu.GetSubMenu(nIndex);
	if (PopupMenu.IsMenu())
	{
		m_TabCtrl.GetItemRectByIndex(nCurSel, rcItem);
		m_TabCtrl.ClientToScreen(&rcItem);
		PopupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL, 
			rcItem.right-19, rcItem.bottom + 4, m_hWnd, &rcItem);
	}

	return 0;
}

LRESULT CMainDlg::OnBuddyListDblClk(LPNMHDR pnmh)
{
	int nTeamIndex, nIndex;
	m_BuddyListCtrl.GetCurSelIndex(nTeamIndex, nIndex);

	if (nTeamIndex != -1 && nIndex != -1)
	{
		UINT nQQUin = m_BuddyListCtrl.GetBuddyItemID(nTeamIndex, nIndex);
		SendMessage(WM_SHOW_BUDDYCHATDLG, 0, nQQUin);
	}	
	return 0;
}

LRESULT CMainDlg::OnGroupListDblClk(LPNMHDR pnmh)
{
	int nTeamIndex, nIndex;
	m_GroupListCtrl.GetCurSelIndex(nTeamIndex, nIndex);

	if (nTeamIndex != -1 && nIndex != -1)
	{
		UINT nGroupCode = m_GroupListCtrl.GetBuddyItemID(nTeamIndex, nIndex);
		SendMessage(WM_SHOW_GROUPCHATDLG, nGroupCode, 0);
	}	
	return 0;
}

LRESULT CMainDlg::OnRecentListDblClk(LPNMHDR pnmh)
{
	int nTeamIndex, nIndex;
	m_RecentListCtrl.GetCurSelIndex(nTeamIndex, nIndex);

	if (nTeamIndex != -1 && nIndex != -1)
	{
		int nIndex2 = m_RecentListCtrl.GetBuddyItemID(nTeamIndex, nIndex);

		CRecentList * lpRecentList = m_QQClient.GetRecentList();
		if (lpRecentList != NULL)
		{
			CRecentInfo * lpRecentInfo = lpRecentList->GetRecent(nIndex2);
			if (lpRecentInfo != NULL)
			{
				if (0 == lpRecentInfo->m_nType)			// 好友
				{
					SendMessage(WM_SHOW_BUDDYCHATDLG, 0, lpRecentInfo->m_nQQUin);
				}
				else if (1 == lpRecentInfo->m_nType)	// 群
				{
					CGroupList * lpGroupList = m_QQClient.GetGroupList();
					if (lpGroupList != NULL)
					{
						CGroupInfo * lpGroupInfo = lpGroupList->GetGroupById(lpRecentInfo->m_nQQUin);
						if (lpGroupInfo != NULL)
						{
							SendMessage(WM_SHOW_GROUPCHATDLG, lpGroupInfo->m_nGroupCode, 0);
						}
					}
				}
			}
		}
	}
	return 0;
}

LRESULT CMainDlg::OnTabCtrlSelChange(LPNMHDR pnmh)
{
	int nCurSel = m_TabCtrl.GetCurSel();
	switch (nCurSel)
	{
	case 0:
		m_BuddyListCtrl.ShowWindow(SW_SHOW);
		m_GroupListCtrl.ShowWindow(SW_HIDE);
		m_RecentListCtrl.ShowWindow(SW_HIDE);
		m_BuddyListCtrl.SetFocus();
		break;

	case 2:
		m_BuddyListCtrl.ShowWindow(SW_HIDE);
		m_GroupListCtrl.ShowWindow(SW_SHOW);
		m_RecentListCtrl.ShowWindow(SW_HIDE);
		m_GroupListCtrl.SetFocus();
		break;

	case 4:
		m_BuddyListCtrl.ShowWindow(SW_HIDE);
		m_GroupListCtrl.ShowWindow(SW_HIDE);
		m_RecentListCtrl.ShowWindow(SW_SHOW);
		m_RecentListCtrl.SetFocus();
		break;

	case 1:
	case 3:
		m_BuddyListCtrl.ShowWindow(SW_HIDE);
		m_GroupListCtrl.ShowWindow(SW_HIDE);
		m_RecentListCtrl.ShowWindow(SW_HIDE);
		break;
	}

	return 0;
}

// “取消”按钮(取消登录)
void CMainDlg::OnBtn_Cancel(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	m_QQClient.CancelLogin();
}

// “用户头像”控件
void CMainDlg::OnPic_Clicked_Head(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CBuddyInfo * lpBuddyInfo = m_QQClient.GetUserInfo();
	if (lpBuddyInfo != NULL)
		ShowBuddyInfoDlg(lpBuddyInfo->m_nQQUin, TRUE);
}

// “大头像”菜单
void CMainDlg::OnMenu_BigHeadPic(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	int nCurSel, nIndex;
	CBuddyListCtrl * lpBuddyListCtrl = NULL;

	nCurSel = m_TabCtrl.GetCurSel();
	if (0 == nCurSel)
	{
		nIndex = 3;
		lpBuddyListCtrl = &m_BuddyListCtrl;
	}
	else if (2 == nCurSel)
	{
		nIndex = 5;
		lpBuddyListCtrl = &m_GroupListCtrl;
	}
	else if (4 == nCurSel)
	{
		nIndex = 6;
		lpBuddyListCtrl = &m_RecentListCtrl;
	}

	if (NULL == lpBuddyListCtrl || lpBuddyListCtrl->GetStyle() == BLC_BIG_ICON_STYLE)
		return;

	CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(nIndex);
	PopupMenu.CheckMenuRadioItem(ID_MENU_BIGHEADPIC, 
		ID_MENU_STDHEADPIC, ID_MENU_BIGHEADPIC, MF_BYCOMMAND);
	PopupMenu.CheckMenuItem(ID_MENU_SHOWBIGHEADPICINSEL, MF_UNCHECKED|MF_BYCOMMAND);
	PopupMenu.EnableMenuItem(ID_MENU_SHOWBIGHEADPICINSEL, MF_GRAYED|MF_BYCOMMAND);

	lpBuddyListCtrl->SetStyle(BLC_BIG_ICON_STYLE);
	lpBuddyListCtrl->Invalidate();
}

// “小头像”菜单
void CMainDlg::OnMenu_SmallHeadPic(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	int nCurSel, nIndex;
	UINT nCheck;
	CBuddyListCtrl * lpBuddyListCtrl = NULL;

	nCurSel = m_TabCtrl.GetCurSel();
	if (0 == nCurSel)
	{
		nIndex = 3;
		lpBuddyListCtrl = &m_BuddyListCtrl;
	}
	else if (2 == nCurSel)
	{
		nIndex = 5;
		lpBuddyListCtrl = &m_GroupListCtrl;
	}
	else if (4 == nCurSel)
	{
		nIndex = 6;
		lpBuddyListCtrl = &m_RecentListCtrl;
	}

	if (NULL == lpBuddyListCtrl || lpBuddyListCtrl->GetStyle() == BLC_SMALL_ICON_STYLE)
		return;

	nCheck = lpBuddyListCtrl->IsShowBigIconInSel() ? MF_CHECKED : MF_UNCHECKED;

	CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(nIndex);
	PopupMenu.CheckMenuRadioItem(ID_MENU_BIGHEADPIC, 
		ID_MENU_STDHEADPIC, ID_MENU_SMALLHEADPIC, MF_BYCOMMAND);
	PopupMenu.EnableMenuItem(ID_MENU_SHOWBIGHEADPICINSEL, MF_ENABLED|MF_BYCOMMAND);
	PopupMenu.CheckMenuItem(ID_MENU_SHOWBIGHEADPICINSEL, nCheck|MF_BYCOMMAND);

	lpBuddyListCtrl->SetStyle(BLC_SMALL_ICON_STYLE);
	lpBuddyListCtrl->Invalidate();
}

// “标准头像”菜单
void CMainDlg::OnMenu_StdHeadPic(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	int nCurSel, nIndex;
	CBuddyListCtrl * lpBuddyListCtrl = NULL;

	nCurSel = m_TabCtrl.GetCurSel();
	if (0 == nCurSel)
	{
		nIndex = 3;
		lpBuddyListCtrl = &m_BuddyListCtrl;
	}
	else if (2 == nCurSel)
	{
		nIndex = 5;
		lpBuddyListCtrl = &m_GroupListCtrl;
	}
	else if (4 == nCurSel)
	{
		nIndex = 6;
		lpBuddyListCtrl = &m_RecentListCtrl;
	}

	if (NULL == lpBuddyListCtrl || lpBuddyListCtrl->GetStyle() == BLC_STANDARD_ICON_STYLE)
		return;

	CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(nIndex);
	PopupMenu.CheckMenuRadioItem(ID_MENU_BIGHEADPIC, 
		ID_MENU_STDHEADPIC, ID_MENU_STDHEADPIC, MF_BYCOMMAND);
	PopupMenu.CheckMenuItem(ID_MENU_SHOWBIGHEADPICINSEL, MF_UNCHECKED|MF_BYCOMMAND);
	PopupMenu.EnableMenuItem(ID_MENU_SHOWBIGHEADPICINSEL, MF_GRAYED|MF_BYCOMMAND);

	lpBuddyListCtrl->SetStyle(BLC_STANDARD_ICON_STYLE);
	lpBuddyListCtrl->Invalidate();
}

// “选中时显示大头像”菜单
void CMainDlg::OnMenu_ShowBigHeadPicInSel(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	int nCurSel, nIndex;
	CBuddyListCtrl * lpBuddyListCtrl = NULL;

	nCurSel = m_TabCtrl.GetCurSel();
	if (0 == nCurSel)
	{
		nIndex = 3;
		lpBuddyListCtrl = &m_BuddyListCtrl;
	}
	else if (2 == nCurSel)
	{
		nIndex = 5;
		lpBuddyListCtrl = &m_GroupListCtrl;
	}
	else if (4 == nCurSel)
	{
		nIndex = 6;
		lpBuddyListCtrl = &m_RecentListCtrl;
	}

	if (NULL == lpBuddyListCtrl)
		return;

	CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(nIndex);
	UINT nState = PopupMenu.GetMenuState(ID_MENU_SHOWBIGHEADPICINSEL, MF_BYCOMMAND);
	if (nState & MF_CHECKED)
	{
		PopupMenu.CheckMenuItem(ID_MENU_SHOWBIGHEADPICINSEL, MF_UNCHECKED|MF_BYCOMMAND);
		lpBuddyListCtrl->SetShowBigIconInSel(FALSE);
	}
	else
	{
		PopupMenu.CheckMenuItem(ID_MENU_SHOWBIGHEADPICINSEL, MF_CHECKED|MF_BYCOMMAND);
		lpBuddyListCtrl->SetShowBigIconInSel(TRUE);
	}
	lpBuddyListCtrl->Invalidate();
}

// “个性签名”编辑文本框
void CMainDlg::OnEdit_Sign_KillFocus(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CString strOldText, strNewText;
	m_btnSign.GetWindowText(strOldText);
	m_edtSign.GetWindowText(strNewText);
	if (strOldText != strNewText)
	{
		m_QQClient.ModifyQQSign(strNewText);
		m_btnSign.SetWindowText(strNewText);
	}
	m_edtSign.ShowWindow(SW_HIDE);
	m_btnSign.ShowWindow(SW_SHOW);
}

// “用户在线状态”菜单
void CMainDlg::OnMenu_Status(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	QQ_STATUS nNewStatus = GetStatusFromMenuID(nID);
	if (nNewStatus != m_QQClient.GetStatus())	// 离线后重新登录暂时未处理
	{
		LoadAppIcon(nNewStatus);
		if (NULL == m_dwMsgTimerId)
			m_TrayIcon.ModifyIcon(m_hAppIcon, _T("MingQQ"));
		m_QQClient.ChangeStatus(nNewStatus);

		StatusMenuBtn_SetIconPic(m_btnStatus, nNewStatus);
	}
}

// 登录返回消息
LRESULT CMainDlg::OnLoginResult(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	QQ_LOGIN_RESULT_CODE nCode = (QQ_LOGIN_RESULT_CODE)lParam;

 	KillTimer(m_dwLoginTimerId);
 	m_dwLoginTimerId = NULL;

	QQ_STATUS nStatus = m_QQClient.GetStatus();

 	LoadAppIcon(nStatus);
 	m_TrayIcon.ModifyIcon(m_hAppIcon, _T("MingQQ"));

	switch (nCode)
	{
	case QLRC_SUCCESS:				// 登录成功
		{
			ShowPanel(TRUE);
			ShowWindow(SW_SHOW);
			Invalidate();

			// 保存登录帐号列表
			LOGIN_ACCOUNT_INFO * lpAccount = m_LoginAccountList.Find(m_stAccountInfo.szUser);
			if (lpAccount != NULL)
				memcpy(lpAccount, &m_stAccountInfo, sizeof(LOGIN_ACCOUNT_INFO));
			else
				m_LoginAccountList.Add(m_stAccountInfo.szUser, m_stAccountInfo.szPwd,
					m_stAccountInfo.nStatus, m_stAccountInfo.bRememberPwd, m_stAccountInfo.bAutoLogin);
			m_LoginAccountList.SetLastLoginUser(m_stAccountInfo.szUser);
			tstring strFileName = ZYM::CPath::GetAppPath()+_T("LoginAccountList.dat");
			m_LoginAccountList.SaveFile(strFileName.c_str());

			// 加载杂项配置
			strFileName = m_QQClient.GetPersonalFolder()+_T("MiscConfig.xml");
			LoadMiscConfig(strFileName.c_str());

			// 注册提取消息热键(Ctrl+Alt+X)
			::RegisterHotKey(m_hWnd, 1001, MOD_CONTROL|MOD_ALT, g_cHotKey);
		}
		break;

	case QLRC_FAILED:				// 登录失败
		{
			MessageBox(_T("登录失败!"), _T("提示"), MB_OK);
			StartLogin();
		}
		break;

	case QLRC_PASSWORD_ERROR:		// 密码错误
		{
			MessageBox(_T("密码错误!"), _T("提示"), MB_OK);
			StartLogin();
		}
		break;

	case QLRC_VERIFY_CODE_ERROR:	// 验证码错误
		{
			MessageBox(_T("验证码错误!"), _T("提示"), MB_OK);
		}
	case QLRC_NEED_VERIFY_CODE:		// 需要输入验证码
		{
			const BYTE * lpData = NULL;
			DWORD dwSize = 0;
			BOOL bRet = m_QQClient.GetVerifyCodePic(lpData, dwSize);
			if (!bRet)
			{
				MessageBox(_T("获取验证码图片失败!"), _T("提示"), MB_OK);
				StartLogin();
				break;
			}

			CVerifyCodeDlg VerifyCodeDlg;
			VerifyCodeDlg.SetVerifyCodePic(lpData, dwSize);
			if (VerifyCodeDlg.DoModal() == IDOK)
			{
				LoadLoginIcon();
				m_dwLoginTimerId = SetTimer(1, 200, NULL);

				m_QQClient.SetVerifyCode(VerifyCodeDlg.GetVerifyCode());
				m_QQClient.Login();
			}
			else
			{
				StartLogin();
			}
		}
		break;

	case QLRC_USER_CANCEL_LOGIN:	// 用户取消登录
		{
			StartLogin();
		}
		break;
	}

	return 0;
}

// 注销返回消息
LRESULT CMainDlg::OnLogoutResult(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CloseDialog(IDOK);
	return 0;
}

// 更新用户信息
LRESULT CMainDlg::OnUpdateUserInfo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CBuddyInfoResult * lpBuddyInfoResult = (CBuddyInfoResult *)lParam;
	if (NULL == lpBuddyInfoResult)
		return 0;
	//m_QQClient.OnUpdateUserInfo(lpBuddyInfoResult);
	delete lpBuddyInfoResult;

	return 0;
}

// 更新好友列表消息
LRESULT CMainDlg::OnUpdateBuddyList(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = (BOOL)lParam;
	if (!bSuccess)
		return 0;

	UpdateBuddyTreeCtrl();		// 更新好友列表控件

	return 0;
}

// 更新群列表消息
LRESULT CMainDlg::OnUpdateGroupList(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = (BOOL)lParam;
	if (!bSuccess)
		return 0;

	UpdateGroupTreeCtrl();		// 更新群列表控件

	return 0;
}

// 更新最近联系人列表消息
LRESULT CMainDlg::OnUpdateRecentList(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = (BOOL)lParam;
	if (!bSuccess)
		return 0;

	UpdateRecentTreeCtrl();		// 更新最近联系人列表控件

	return 0;
}

// 好友消息
LRESULT CMainDlg::OnBuddyMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = (UINT)wParam;
	UINT nMsgId = (UINT)lParam;
	if (0 == nQQUin || 0 == nMsgId)
		return 0;

	tstring strFileName = ZYM::CPath::GetAppPath() + _T("Sound\\msg.wav");	// 播放来消息提示音
	::sndPlaySound(strFileName.c_str(), SND_ASYNC);

	std::map<UINT, CBuddyChatDlg *>::iterator iter;
	iter = m_mapBuddyChatDlg.find(nQQUin);
	if (iter != m_mapBuddyChatDlg.end())
	{
		CBuddyChatDlg * lpBuddyDlg = iter->second;
		if (lpBuddyDlg != NULL && lpBuddyDlg->IsWindow())
		{
			lpBuddyDlg->OnRecvMsg(nQQUin, nMsgId);
			return 0;
		}
	}

	int nTeamIndex, nIndex;
	m_BuddyListCtrl.GetItemIndexByID(nQQUin, nTeamIndex, nIndex);
	m_BuddyListCtrl.SetBuddyItemHeadFlashAnim(nTeamIndex, nIndex, TRUE);

	UpdateMsgIcon();

	if (m_MsgTipDlg.IsWindow())
		m_MsgTipDlg.AddMsgSender(QQ_MSG_TYPE_BUDDY, nQQUin);

	if (NULL == m_dwMsgTimerId)
		m_dwMsgTimerId = SetTimer(2, ::GetCaretBlinkTime(), NULL);

	return 0;
}

// 群消息
LRESULT CMainDlg::OnGroupMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nMsgId = (UINT)lParam;
	if (0 == nGroupCode || 0 == nMsgId)
		return 0;

	std::map<UINT, CGroupChatDlg *>::iterator iter;
	iter = m_mapGroupChatDlg.find(nGroupCode);
	if (iter != m_mapGroupChatDlg.end())
	{
		CGroupChatDlg * lpGroupDlg = iter->second;
		if (lpGroupDlg != NULL && lpGroupDlg->IsWindow())
		{
			lpGroupDlg->OnRecvMsg(nGroupCode, nMsgId);
			return 0;
		}
	}

	CMessageList * lpMsgList = m_QQClient.GetMessageList();
	if (lpMsgList != NULL)
	{
		CMessageSender * lpMsgSender = lpMsgList->GetMsgSender(QQ_MSG_TYPE_GROUP, nGroupCode);
		if (lpMsgSender != NULL)
		{
			if (lpMsgSender->GetMsgCount() == 1)
			{
				tstring strFileName = ZYM::CPath::GetAppPath() + _T("Sound\\msg.wav");	// 播放来消息提示音
				::sndPlaySound(strFileName.c_str(), SND_ASYNC);
			}
		}
	}

	int nTeamIndex, nIndex;
	m_GroupListCtrl.GetItemIndexByID(nGroupCode, nTeamIndex, nIndex);
	m_GroupListCtrl.SetBuddyItemHeadFlashAnim(nTeamIndex, nIndex, TRUE);

	UpdateMsgIcon();

	if (m_MsgTipDlg.IsWindow())
		m_MsgTipDlg.AddMsgSender(QQ_MSG_TYPE_GROUP, nGroupCode);

	if (NULL == m_dwMsgTimerId)
		m_dwMsgTimerId = SetTimer(2, ::GetCaretBlinkTime(), NULL);

	return 0;
}

// 临时会话消息
LRESULT CMainDlg::OnSessMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = (UINT)wParam;
	UINT nMsgId = (UINT)lParam;
	if (0 == nQQUin || 0 == nMsgId)
		return 0;

	tstring strFileName = ZYM::CPath::GetAppPath() + _T("Sound\\msg.wav");	// 播放来消息提示音
	::sndPlaySound(strFileName.c_str(), SND_ASYNC);

	std::map<UINT, CSessChatDlg *>::iterator iter;
	iter = m_mapSessChatDlg.find(nQQUin);
	if (iter != m_mapSessChatDlg.end())
	{
		CSessChatDlg * lpSessChatDlg = iter->second;
		if (lpSessChatDlg != NULL && lpSessChatDlg->IsWindow())
		{
			lpSessChatDlg->OnRecvMsg(nQQUin, nMsgId);
			return 0;
		}
	}

	UpdateMsgIcon();

	if (m_MsgTipDlg.IsWindow())
		m_MsgTipDlg.AddMsgSender(QQ_MSG_TYPE_SESS, nQQUin);

	if (NULL == m_dwMsgTimerId)
		m_dwMsgTimerId = SetTimer(2, ::GetCaretBlinkTime(), NULL);

	return 0;
}

// 好友状态改变消息
LRESULT CMainDlg::OnStatusChangeMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = (UINT)lParam;
	if (0 == nQQUin)
		return 0;

	CBuddyList * lpBuddyList = m_QQClient.GetBuddyList();
	if (NULL == lpBuddyList)
		return 0;

	CBuddyInfo * lpBuddyInfo = lpBuddyList->GetBuddy(nQQUin);
	if (NULL == lpBuddyInfo)
		return 0;

	CBuddyTeamInfo * lpBuddyTeam = lpBuddyList->GetBuddyTeam(lpBuddyInfo->m_nTeamIndex);
	if (NULL == lpBuddyTeam)
		return 0;

	int nOnlineCnt = lpBuddyTeam->GetOnlineBuddyCount();
	BOOL bOnline = (lpBuddyInfo->m_nStatus != QQ_STATUS_OFFLINE ? TRUE : FALSE);

	if (bOnline)	// 播放好友上线声音
	{
		tstring strFileName = ZYM::CPath::GetAppPath() + _T("Sound\\Global.wav");
		::sndPlaySound(strFileName.c_str(), SND_ASYNC);
	}

	int nTeamIndex, nIndex;	// 获取好友项索引
	m_BuddyListCtrl.GetItemIndexByID(nQQUin, nTeamIndex, nIndex);

	// 更新好友分组在线人数
	m_BuddyListCtrl.SetBuddyTeamCurCnt(nTeamIndex, nOnlineCnt);

	// 更新好友头像
	tstring strFileName = m_QQClient.GetBuddyHeadPicFullName(lpBuddyInfo->m_nQQNum);
	if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefBuddyHeadPic.png");
	m_BuddyListCtrl.SetBuddyItemHeadPic(nTeamIndex, nIndex, strFileName.c_str(), !bOnline);

	// 设置好友在线状态并启动上线动画
	m_BuddyListCtrl.SetBuddyItemOnline(nTeamIndex, nIndex, bOnline, TRUE);

	m_BuddyListCtrl.Invalidate();	// 刷新好友列表控件

	return 0;
}

// 被踢下线消息
LRESULT CMainDlg::OnKickMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR lpszReason = _T("被踢下线！");
	MessageBox(lpszReason, _T("提示"), MB_OK);
	PostMessage(WM_CLOSE);
	return 0;
}

// 群系统消息
LRESULT CMainDlg::OnSysGroupMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)lParam;
	if (0 == nGroupCode)
		return 0;

	tstring strFileName = ZYM::CPath::GetAppPath() + _T("Sound\\system.wav");	// 播放来系统消息提示音
	::sndPlaySound(strFileName.c_str(), SND_ASYNC);

	UpdateMsgIcon();

	if (m_MsgTipDlg.IsWindow())
		m_MsgTipDlg.AddMsgSender(QQ_MSG_TYPE_SYSGROUP, nGroupCode);

	if (NULL == m_dwMsgTimerId)
		m_dwMsgTimerId = SetTimer(2, ::GetCaretBlinkTime(), NULL);

	return 0;
}

// 更新好友号码
LRESULT CMainDlg::OnUpdateBuddyNumber(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = (UINT)lParam;
	if (0 == nQQUin)
		return 0;

 	NotifyBuddyChatDlg(nQQUin, QQ_MSG_UPDATE_BUDDY_NUMBER);		// 通知好友聊天窗口更新
 	NotifyBuddyInfoDlg(nQQUin, QQ_MSG_UPDATE_BUDDY_NUMBER);		// 通知好友信息窗口更新

	return 0;
}

// 更新群成员号码
LRESULT CMainDlg::OnUpdateGMemberNumber(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = (UINT)lParam;
	if (0 == nGroupCode || 0 == nQQUin)
		return 0;

 	NotifyGroupChatDlg(nGroupCode, QQ_MSG_UPDATE_GMEMBER_NUMBER, wParam, lParam);// 通知群聊天窗口更新
	NotifyGMemberInfoDlg(nGroupCode, nQQUin, QQ_MSG_UPDATE_GMEMBER_NUMBER);	// 通知群成员信息窗口更新
	NotifySessChatDlg(nQQUin, QQ_MSG_UPDATE_GMEMBER_NUMBER);				// 通知群成员聊天窗口更新

	return 0;
}

// 更新群号码
LRESULT CMainDlg::OnUpdateGroupNumber(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)lParam;
	if (0 == nGroupCode)
		return 0;

 	NotifyGroupChatDlg(nGroupCode, QQ_MSG_UPDATE_GROUP_NUMBER, 0, 0);// 通知群聊天窗口更新
 	NotifyGroupInfoDlg(nGroupCode, QQ_MSG_UPDATE_GROUP_NUMBER);		// 通知群信息窗口更新

	return 0;
}

// 更新好友个性签名
LRESULT CMainDlg::OnUpdateBuddySign(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = lParam;
	if (0 == nQQUin)
		return 0;

	CBuddyInfo * lpBuddyInfo = m_QQClient.GetUserInfo();
	if (lpBuddyInfo != NULL && lpBuddyInfo->m_nQQUin == nQQUin)	// 更新用户个性签名
	{
		if (!lpBuddyInfo->m_strSign.empty())
		{
			m_btnSign.SetWindowText(lpBuddyInfo->m_strSign.c_str());
			m_btnSign.SetToolTipText(lpBuddyInfo->m_strSign.c_str());
		}
		else
		{
			m_btnSign.SetWindowText(_T("这家伙很懒,什么都没有留下。"));
			m_btnSign.SetToolTipText(_T("这家伙很懒,什么都没有留下。"));
		}
	}
	else	// 更新好友个性签名
	{
		CBuddyList * lpBuddyList = m_QQClient.GetBuddyList();		// 更新好友列表控件的个性签名
		if (lpBuddyList != NULL)
		{
			CBuddyInfo * lpBuddyInfo = lpBuddyList->GetBuddy(nQQUin);
			if (lpBuddyInfo != NULL)
			{
				int nTeamIndex, nIndex;
				m_BuddyListCtrl.GetItemIndexByID(nQQUin, nTeamIndex, nIndex);
				m_BuddyListCtrl.SetBuddyItemSign(nTeamIndex, nIndex, lpBuddyInfo->m_strSign.c_str());
			}
		}

		NotifyBuddyChatDlg(nQQUin, QQ_MSG_UPDATE_BUDDY_SIGN);		// 通知好友聊天窗口更新
		NotifyBuddyInfoDlg(nQQUin, QQ_MSG_UPDATE_BUDDY_SIGN);		// 通知好友信息窗口更新
	}

	return 0;
}

// 更新群成员个性签名
LRESULT CMainDlg::OnUpdateGMemberSign(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = (UINT)lParam;
	if (0 == nGroupCode || 0 == nQQUin)
		return 0;

	NotifyGMemberInfoDlg(nGroupCode, nQQUin, QQ_MSG_UPDATE_GMEMBER_SIGN);	// 通知群成员信息窗口更新

	return 0;
}

// 更新好友信息
LRESULT CMainDlg::OnUpdateBuddyInfo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = lParam;
	if (0 == nQQUin)
		return 0;

 	CBuddyInfo * lpBuddyInfo = m_QQClient.GetUserInfo();
 	if (lpBuddyInfo != NULL && lpBuddyInfo->m_nQQUin == nQQUin)	// 更新用户昵称
 		m_staNickName.SetWindowText(lpBuddyInfo->m_strNickName.c_str());
	else
		NotifyBuddyInfoDlg(nQQUin, QQ_MSG_UPDATE_BUDDY_INFO);		// 通知好友信息窗口更新

	return 0;
}

// 更新群成员信息
LRESULT CMainDlg::OnUpdateGMemberInfo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = (UINT)lParam;
	if (0 == nGroupCode || 0 == nQQUin)
		return 0;

	NotifyGMemberInfoDlg(nGroupCode, nQQUin, QQ_MSG_UPDATE_GMEMBER_INFO);	// 通知群成员信息窗口更新

	return 0;
}

// 更新群信息
LRESULT CMainDlg::OnUpdateGroupInfo(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)lParam;
	if (0 == nGroupCode)
		return 0;

 	NotifyGroupChatDlg(nGroupCode, QQ_MSG_UPDATE_GROUP_INFO, 0, 0);	// 通知群聊天窗口更新
 	NotifyGroupInfoDlg(nGroupCode, QQ_MSG_UPDATE_GROUP_INFO);		// 通知群信息窗口更新

	return 0;
}

// HTREEITEM CMainDlg::FindTreeItemByQQUin(CTreeViewCtrl& treeCtrl, UINT nQQUin)
// {
// 	HTREEITEM hItem = treeCtrl.GetRootItem();
// 	while (hItem != NULL)
// 	{
// 		UINT nQQUin2 = (UINT)treeCtrl.GetItemData(hItem);
// 		if (nQQUin2 == nQQUin)
// 			return hItem;
// 
// 		HTREEITEM hFindItem = FindTreeItemByQQUin2(treeCtrl, hItem, nQQUin);
// 		if (hFindItem != NULL)
// 			return hFindItem;
// 
// 		hItem = treeCtrl.GetNextItem(hItem, TVGN_NEXT);
// 	}
// 	return NULL;
// }
// 
// HTREEITEM CMainDlg::FindTreeItemByQQUin2(CTreeViewCtrl& treeCtrl, HTREEITEM hItem, UINT nQQUin)
// {
// 	if (treeCtrl.ItemHasChildren(hItem))
// 	{
// 		HTREEITEM hChildItem = treeCtrl.GetChildItem(hItem);
// 
// 		while (hChildItem != NULL)
// 		{
// 			UINT nQQUin2 = (UINT)treeCtrl.GetItemData(hItem);
// 			if (nQQUin2 == nQQUin)
// 				return hItem;
// 
// 			HTREEITEM hFindItem = FindTreeItemByQQUin2(treeCtrl, hChildItem, nQQUin);
// 			if (hFindItem != NULL)
// 				return hFindItem;
// 
// 			hChildItem = treeCtrl.GetNextItem(hChildItem, TVGN_NEXT);
// 		}
// 	}
// 
// 	UINT nQQUin2 = (UINT)treeCtrl.GetItemData(hItem);
// 	return  (nQQUin2 == nQQUin) ? hItem : NULL;
// }

// 更新好友头像图片
LRESULT CMainDlg::OnUpdateBuddyHeadPic(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nQQUin = (UINT)lParam;

	CBuddyInfo * lpBuddyInfo = m_QQClient.GetUserInfo();
	if (lpBuddyInfo != NULL && lpBuddyInfo->m_nQQUin == nQQUin)	// 更新用户头像
	{
		tstring strFileName = m_QQClient.GetUserHeadPicFullName(nQQUin);
		if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
			strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefBuddyHeadPic.png");
		m_picHead.SetBitmap(strFileName.c_str());
		m_picHead.Invalidate();
		return 0;
	}

	// 更新好友列表头像
	UINT nQQNum = 0;
	BOOL bGray = FALSE;
	CBuddyList * lpBuddyList = m_QQClient.GetBuddyList();
	if (lpBuddyList != NULL)
	{
		CBuddyInfo * lpBuddyInfo = lpBuddyList->GetBuddy(nQQUin);
		if (lpBuddyInfo != NULL)
		{
			nQQNum = lpBuddyInfo->m_nQQNum;
			bGray = lpBuddyInfo->m_nStatus != QQ_STATUS_OFFLINE ? FALSE : TRUE;
		}
	}

	tstring strFileName = m_QQClient.GetBuddyHeadPicFullName(nQQNum);
	if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefBuddyHeadPic.png");
	int nTeamIndex, nIndex;
	m_BuddyListCtrl.GetItemIndexByID(nQQUin, nTeamIndex, nIndex);
	m_BuddyListCtrl.SetBuddyItemHeadPic(nTeamIndex, nIndex, strFileName.c_str(), bGray);

	// 更新最近联系人列表头像
	int nItemCnt = m_RecentListCtrl.GetBuddyItemCount(0);
	for (int i = 0; i < nItemCnt; i++)
	{
		int nIndex = m_RecentListCtrl.GetBuddyItemID(0, i);

		CRecentList * lpRecentList = m_QQClient.GetRecentList();
		if (lpRecentList != NULL)
		{
			CRecentInfo * lpRecentInfo = lpRecentList->GetRecent(nIndex);
			if (lpRecentInfo != NULL)
			{
				if (0 == lpRecentInfo->m_nType)			// 好友
				{
					if (nQQUin == lpRecentInfo->m_nQQUin)
					{
						m_RecentListCtrl.GetItemIndexByID(nIndex, nTeamIndex, nIndex);
						m_RecentListCtrl.SetBuddyItemHeadPic(nTeamIndex, nIndex, strFileName.c_str(), bGray);
						break;
					}
				}
			}
		}
	}

	NotifyBuddyChatDlg(nQQUin, QQ_MSG_UPDATE_BUDDY_HEADPIC);		// 通知好友聊天窗口更新

	return 0;
}

// 更新群成员头像图片
LRESULT CMainDlg::OnUpdateGMemberHeadPic(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = (UINT)lParam;

	NotifyGroupChatDlg(nGroupCode, QQ_MSG_UPDATE_GMEMBER_HEADPIC, wParam, lParam);	// 通知群聊天窗口更新
	NotifySessChatDlg(nQQUin, QQ_MSG_UPDATE_GMEMBER_HEADPIC);						// 通知群成员聊天窗口更新

	return 0;
}

// 更新群头像图片
LRESULT CMainDlg::OnUpdateGroupHeadPic(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;

	// 更新群列表头像
	UINT nGroupNum = 0;
	CGroupList * lpGroupList = m_QQClient.GetGroupList();
	if (lpGroupList != NULL)
	{
		CGroupInfo * lpGroupInfo = lpGroupList->GetGroupByCode(nGroupCode);
		if (lpGroupInfo != NULL)
			nGroupNum = lpGroupInfo->m_nGroupNumber;
	}

	tstring strFileName = m_QQClient.GetGroupHeadPicFullName(nGroupNum);
	if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefGroupHeadPic.jpg");
	int nTeamIndex, nIndex;
	m_GroupListCtrl.GetItemIndexByID(nGroupCode, nTeamIndex, nIndex);
	m_GroupListCtrl.SetBuddyItemHeadPic(nTeamIndex, nIndex, strFileName.c_str(), FALSE);

	// 更新最近联系人列表头像
	int nItemCnt = m_RecentListCtrl.GetBuddyItemCount(0);
	for (int i = 0; i < nItemCnt; i++)
	{
		int nIndex = m_RecentListCtrl.GetBuddyItemID(0, i);

		CRecentList * lpRecentList = m_QQClient.GetRecentList();
		if (lpRecentList != NULL)
		{
			CRecentInfo * lpRecentInfo = lpRecentList->GetRecent(nIndex);
			if (lpRecentInfo != NULL)
			{
				if (1 == lpRecentInfo->m_nType)	// 群
				{
					CGroupList * lpGroupList = m_QQClient.GetGroupList();
					if (lpGroupList != NULL)
					{
						CGroupInfo * lpGroupInfo = lpGroupList->GetGroupById(lpRecentInfo->m_nQQUin);
						if (lpGroupInfo != NULL && nGroupCode == lpGroupInfo->m_nGroupCode)
						{
							m_RecentListCtrl.GetItemIndexByID(nIndex, nTeamIndex, nIndex);
							m_RecentListCtrl.SetBuddyItemHeadPic(nTeamIndex, nIndex, strFileName.c_str(), FALSE);
							break;
						}
					}
				}
			}
		}
	}

	NotifyGroupChatDlg(nGroupCode, QQ_MSG_UPDATE_GROUP_HEADPIC, wParam, lParam);// 通知群聊天窗口更新

	return 0;
}

// 改变在线状态返回消息
LRESULT CMainDlg::OnChangeStatusResult(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = (BOOL)wParam;
	QQ_STATUS nNewStatus = (QQ_STATUS)lParam;
	if (!bSuccess)
		MessageBox(_T("改变在线状态失败！"));
	return 0;
}

LRESULT CMainDlg::OnShowOrCloseDlg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nGroupCode = (UINT)wParam;
	UINT nQQUin = (UINT)lParam;

	switch (uMsg)
	{
	case WM_SHOW_BUDDYCHATDLG:
		ShowBuddyChatDlg(nQQUin, TRUE);
		break;
	case WM_SHOW_GROUPCHATDLG:
		ShowGroupChatDlg(nGroupCode, TRUE);
		break;
	case WM_SHOW_SESSCHATDLG:
		ShowSessChatDlg(nGroupCode, nQQUin, TRUE);
		break;
	case WM_SHOW_SYSGROUPCHATDLG:
		ShowSysGroupChatDlg(nGroupCode, TRUE);
		break;
	case WM_SHOW_BUDDYINFODLG:
		ShowBuddyInfoDlg(nQQUin, TRUE);
		break;
	case WM_SHOW_GMEMBERINFODLG:
		ShowGMemberInfoDlg(nGroupCode, nQQUin, TRUE);
		break;
	case WM_SHOW_GROUPINFODLG:
		ShowGroupInfoDlg(nGroupCode, TRUE);
		break;
	case WM_CLOSE_BUDDYCHATDLG:
		ShowBuddyChatDlg(nQQUin, FALSE);
		break;
	case WM_CLOSE_GROUPCHATDLG:
		ShowGroupChatDlg(nGroupCode, FALSE);
		break;
	case WM_CLOSE_SESSCHATDLG:
		ShowSessChatDlg(nGroupCode, nQQUin, FALSE);
		break;
	case WM_CLOSE_SYSGROUPCHATDLG:
		ShowSysGroupChatDlg(nGroupCode, FALSE);
		break;
	case WM_CLOSE_BUDDYINFODLG:
		ShowBuddyInfoDlg(nQQUin, FALSE);
		break;
	case WM_CLOSE_GMEMBERINFODLG:
		ShowGMemberInfoDlg(nGroupCode, nQQUin, FALSE);
		break;
	case WM_CLOSE_GROUPINFODLG:
		ShowGroupInfoDlg(nGroupCode, FALSE);
		break;
	}
	return 0;
}

LRESULT CMainDlg::OnDelMsgSender(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	QQ_MSG_TYPE nType = (QQ_MSG_TYPE)wParam;
	UINT nSenderId = (UINT)lParam;

	if (m_MsgTipDlg.IsWindow())
		m_MsgTipDlg.DelMsgSender(nType, nSenderId);

	if (nType == QQ_MSG_TYPE_BUDDY)
	{
		int nTeamIndex, nIndex;
		m_BuddyListCtrl.GetItemIndexByID(nSenderId, nTeamIndex, nIndex);
		m_BuddyListCtrl.SetBuddyItemHeadFlashAnim(nTeamIndex, nIndex, FALSE);
	}
	else if (nType == QQ_MSG_TYPE_GROUP)
	{
		int nTeamIndex, nIndex;
		m_GroupListCtrl.GetItemIndexByID(nSenderId, nTeamIndex, nIndex);
		m_GroupListCtrl.SetBuddyItemHeadFlashAnim(nTeamIndex, nIndex, FALSE);
	}

	UpdateMsgIcon();

	CMessageList * lpMsgList = m_QQClient.GetMessageList();
	if (lpMsgList != NULL && lpMsgList->GetMsgSenderCount() <= 0)
	{
		if (m_MsgTipDlg.IsWindow())
			m_MsgTipDlg.DestroyWindow();
		KillTimer(m_dwMsgTimerId);
		m_dwMsgTimerId = NULL;
		m_nLastMsgType = QQ_MSG_TYPE_BUDDY;
		m_nLastSenderId = 0;
		m_TrayIcon.ModifyIcon(m_hAppIcon, _T("MingQQ"));
	}

	return 0;
}

LRESULT CMainDlg::OnCancelFlash(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KillTimer(m_dwMsgTimerId);
	m_dwMsgTimerId = NULL;
	m_TrayIcon.ModifyIcon(m_hAppIcon, _T("MingQQ"));
	return 0;
}

void CMainDlg::ShowBuddyChatDlg(UINT nQQUin, BOOL bShow)
{
	if (nQQUin == 0)
		return;

	if (bShow)
	{
		std::map<UINT, CBuddyChatDlg *>::iterator iter;
		iter = m_mapBuddyChatDlg.find(nQQUin);
		if (iter != m_mapBuddyChatDlg.end())
		{
			CBuddyChatDlg * lpBuddyChatDlg = iter->second;
			if (lpBuddyChatDlg != NULL)
			{
				if (!lpBuddyChatDlg->IsWindow())
					lpBuddyChatDlg->Create(NULL);
				lpBuddyChatDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpBuddyChatDlg->m_hWnd);
			}
		}
		else
		{
			CBuddyChatDlg * lpBuddyChatDlg = new CBuddyChatDlg;
			if (lpBuddyChatDlg != NULL)
			{
				lpBuddyChatDlg->m_lpQQClient = &m_QQClient;
				lpBuddyChatDlg->m_lpFaceList = &m_FaceList;
				lpBuddyChatDlg->m_lpCascadeWinManager = &m_CascadeWinManager;
				lpBuddyChatDlg->m_hMainDlg = m_hWnd;
				lpBuddyChatDlg->m_nQQUin = nQQUin;
				m_mapBuddyChatDlg[nQQUin] = lpBuddyChatDlg;
				lpBuddyChatDlg->Create(NULL);
				lpBuddyChatDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpBuddyChatDlg->m_hWnd);
			}
		}
	}
	else
	{
		std::map<UINT, CBuddyChatDlg *>::iterator iter;
		iter = m_mapBuddyChatDlg.find(nQQUin);
		if (iter != m_mapBuddyChatDlg.end())
		{
			CBuddyChatDlg * lpBuddyChatDlg = iter->second;
			if (lpBuddyChatDlg != NULL)
			{
				if (lpBuddyChatDlg->IsWindow())
					lpBuddyChatDlg->DestroyWindow();
				delete lpBuddyChatDlg;
			}
			m_mapBuddyChatDlg.erase(iter);
		}
	}
}

void CMainDlg::ShowGroupChatDlg(UINT nGroupCode, BOOL bShow)
{
	if (nGroupCode == 0)
		return;

	if (bShow)
	{
		std::map<UINT, CGroupChatDlg *>::iterator iter;
		iter = m_mapGroupChatDlg.find(nGroupCode);
		if (iter != m_mapGroupChatDlg.end())
		{
			CGroupChatDlg * lpGroupChatDlg = iter->second;
			if (lpGroupChatDlg != NULL)
			{
				if (!lpGroupChatDlg->IsWindow())
					lpGroupChatDlg->Create(NULL);
				lpGroupChatDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpGroupChatDlg->m_hWnd);
			}
		}
		else
		{
			CGroupChatDlg * lpGroupChatDlg = new CGroupChatDlg;
			if (lpGroupChatDlg != NULL)
			{
				lpGroupChatDlg->m_lpQQClient = &m_QQClient;
				lpGroupChatDlg->m_lpFaceList = &m_FaceList;
				lpGroupChatDlg->m_lpCascadeWinManager = &m_CascadeWinManager;
				lpGroupChatDlg->m_hMainDlg = m_hWnd;
				lpGroupChatDlg->m_nGroupCode = nGroupCode;
				m_mapGroupChatDlg[nGroupCode] = lpGroupChatDlg;
				lpGroupChatDlg->Create(NULL);
				lpGroupChatDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpGroupChatDlg->m_hWnd);
			}
		}
	}
	else
	{
		std::map<UINT, CGroupChatDlg *>::iterator iter;
		iter = m_mapGroupChatDlg.find(nGroupCode);
		if (iter != m_mapGroupChatDlg.end())
		{
			CGroupChatDlg * lpGroupChatDlg = iter->second;
			if (lpGroupChatDlg != NULL)
			{
				if (lpGroupChatDlg->IsWindow())
					lpGroupChatDlg->DestroyWindow();
				delete lpGroupChatDlg;
			}
			m_mapGroupChatDlg.erase(iter);
		}
	}
}

void CMainDlg::ShowSessChatDlg(UINT nGroupCode, UINT nQQUin, BOOL bShow)
{
	if (nQQUin == 0)
		return;

	if (bShow)
	{
		std::map<UINT, CSessChatDlg *>::iterator iter;
		iter = m_mapSessChatDlg.find(nQQUin);
		if (iter != m_mapSessChatDlg.end())
		{
			CSessChatDlg * lpSessChatDlg = iter->second;
			if (lpSessChatDlg != NULL)
			{
				if (!lpSessChatDlg->IsWindow())
					lpSessChatDlg->Create(NULL);
				lpSessChatDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpSessChatDlg->m_hWnd);
			}
		}
		else
		{
			CSessChatDlg * lpSessChatDlg = new CSessChatDlg;
			if (lpSessChatDlg != NULL)
			{
				lpSessChatDlg->m_lpQQClient = &m_QQClient;
				lpSessChatDlg->m_lpFaceList = &m_FaceList;
				lpSessChatDlg->m_lpCascadeWinManager = &m_CascadeWinManager;
				lpSessChatDlg->m_hMainDlg = m_hWnd;
				lpSessChatDlg->m_nGroupCode = nGroupCode;
				lpSessChatDlg->m_nQQUin = nQQUin;
				m_mapSessChatDlg[nQQUin] = lpSessChatDlg;
				lpSessChatDlg->Create(NULL);
				lpSessChatDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpSessChatDlg->m_hWnd);
			}
		}
	}
	else
	{
		std::map<UINT, CSessChatDlg *>::iterator iter;
		iter = m_mapSessChatDlg.find(nQQUin);
		if (iter != m_mapSessChatDlg.end())
		{
			CSessChatDlg * lpSessChatDlg = iter->second;
			if (lpSessChatDlg != NULL)
			{
				if (lpSessChatDlg->IsWindow())
					lpSessChatDlg->DestroyWindow();
				delete lpSessChatDlg;
			}
			m_mapSessChatDlg.erase(iter);
		}
	}
}

void CMainDlg::ShowSysGroupChatDlg(UINT nGroupCode, BOOL bShow)
{
	CString strText, strGroupName, strAdminName, strAdminUin, strMsg;
	UINT nGroupNumber;

	CGroupList * lpGroupList = m_QQClient.GetGroupList();
	CMessageList * lpMsgList = m_QQClient.GetMessageList();
	if (NULL == lpGroupList || NULL == lpMsgList)
		return;

	CGroupInfo * lpGroupInfo = lpGroupList->GetGroupByCode(nGroupCode);
	CMessageSender * lpMsgSender = lpMsgList->GetMsgSender(QQ_MSG_TYPE_SYSGROUP, nGroupCode);
	if (NULL == lpMsgSender)
		return;

	if (lpGroupInfo != NULL)
		strGroupName = lpGroupInfo->m_strName.c_str();

	int nMsgCnt = lpMsgSender->GetMsgCount();
	for (int i = 0; i < nMsgCnt; i++)
	{
		CSysGroupMessage * lpSysGroupMsg = lpMsgSender->GetSysGroupMsg(i);
		if (lpSysGroupMsg != NULL)
		{
			strAdminName = lpSysGroupMsg->m_strAdminNickName.c_str();
			strAdminUin = lpSysGroupMsg->m_strAdminUin.c_str();
			strMsg = lpSysGroupMsg->m_strMsg.c_str();
			nGroupNumber = lpSysGroupMsg->m_nGroupNumber;

			if (lpSysGroupMsg->m_strSubType == _T("group_request_join_agree"))
			{
				LPCTSTR lpFmt = _T("管理员已同意您加入群%s(%u)");
				strText.Format(lpFmt, strGroupName, nGroupNumber);
				MessageBox(strText, _T("提示"), MB_OK);
			}
			else if (lpSysGroupMsg->m_strSubType == _T("group_request_join_deny"))
			{
				LPCTSTR lpFmt = _T("管理员已拒绝您加入群%s(%u)。拒绝理由：%s");
				strText.Format(lpFmt, strGroupName, nGroupNumber, strMsg);
				MessageBox(strText, _T("提示"), MB_OK);
			}
			else if (lpSysGroupMsg->m_strSubType == _T("group_leave"))
			{
				LPCTSTR lpFmt = _T("%s(%u)管理员%s(%s)已将您移除出该群。");
				strText.Format(lpFmt, strGroupName, nGroupNumber, strAdminName, strAdminUin);
				MessageBox(strText, _T("提示"), MB_OK);
			}
		}
	}
	lpMsgList->DelMsgSender(QQ_MSG_TYPE_SYSGROUP, nGroupCode);
	OnDelMsgSender(NULL, QQ_MSG_TYPE_SYSGROUP, nGroupCode);
}

void CMainDlg::ShowBuddyInfoDlg(UINT nQQUin, BOOL bShow)
{
	if (nQQUin == 0)
		return;

	if (bShow)
	{
		std::map<UINT, CBuddyInfoDlg *>::iterator iter;
		iter = m_mapBuddyInfoDlg.find(nQQUin);
		if (iter != m_mapBuddyInfoDlg.end())
		{
			CBuddyInfoDlg * lpBuddyInfoDlg = iter->second;
			if (lpBuddyInfoDlg != NULL)
			{
				if (!lpBuddyInfoDlg->IsWindow())
					lpBuddyInfoDlg->Create(NULL);
				lpBuddyInfoDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpBuddyInfoDlg->m_hWnd);
			}
		}
		else
		{
			CBuddyInfoDlg * lpBuddyInfoDlg = new CBuddyInfoDlg;
			if (lpBuddyInfoDlg != NULL)
			{
				m_mapBuddyInfoDlg[nQQUin] = lpBuddyInfoDlg;
				lpBuddyInfoDlg->m_lpQQClient = &m_QQClient;
				lpBuddyInfoDlg->m_hMainDlg = m_hWnd;
				lpBuddyInfoDlg->m_nQQUin = nQQUin;
				lpBuddyInfoDlg->m_bIsGMember = FALSE;
				lpBuddyInfoDlg->m_nGroupCode = 0;
				lpBuddyInfoDlg->Create(NULL);
				lpBuddyInfoDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpBuddyInfoDlg->m_hWnd);
			}
		}
	}
	else
	{
		std::map<UINT, CBuddyInfoDlg *>::iterator iter;
		iter = m_mapBuddyInfoDlg.find(nQQUin);
		if (iter != m_mapBuddyInfoDlg.end())
		{
			CBuddyInfoDlg * lpBuddyInfoDlg = iter->second;
			if (lpBuddyInfoDlg != NULL)
			{
				if (lpBuddyInfoDlg->IsWindow())
					lpBuddyInfoDlg->DestroyWindow();
				delete lpBuddyInfoDlg;
			}
			m_mapBuddyInfoDlg.erase(iter);
		}
	}
}

void CMainDlg::ShowGMemberInfoDlg(UINT nGroupCode, UINT nQQUin, BOOL bShow)
{
	if (0 == nGroupCode || 0 == nQQUin)
		return;

	if (bShow)
	{
		CGMemberInfoMapKey key;
		key.m_nGroupCode = nGroupCode;
		key.m_nQQUin = nQQUin;
		std::map<CGMemberInfoMapKey, CBuddyInfoDlg *>::iterator iter;
		iter = m_mapGMemberInfoDlg.find(key);
		if (iter != m_mapGMemberInfoDlg.end())
		{
			CBuddyInfoDlg * lpBuddyInfoDlg = iter->second;
			if (lpBuddyInfoDlg != NULL)
			{
				if (!lpBuddyInfoDlg->IsWindow())
					lpBuddyInfoDlg->Create(NULL);
				lpBuddyInfoDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpBuddyInfoDlg->m_hWnd);
			}
		}
		else
		{
			CBuddyInfoDlg * lpBuddyInfoDlg = new CBuddyInfoDlg;
			if (lpBuddyInfoDlg != NULL)
			{
				m_mapGMemberInfoDlg[key] = lpBuddyInfoDlg;
				lpBuddyInfoDlg->m_lpQQClient = &m_QQClient;
				lpBuddyInfoDlg->m_hMainDlg = m_hWnd;
				lpBuddyInfoDlg->m_nQQUin = nQQUin;
				lpBuddyInfoDlg->m_bIsGMember = TRUE;
				lpBuddyInfoDlg->m_nGroupCode = nGroupCode;
				lpBuddyInfoDlg->Create(NULL);
				lpBuddyInfoDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpBuddyInfoDlg->m_hWnd);
			}
		}
	}
	else
	{
		CGMemberInfoMapKey key;
		key.m_nGroupCode = nGroupCode;
		key.m_nQQUin = nQQUin;
		std::map<CGMemberInfoMapKey, CBuddyInfoDlg *>::iterator iter;
		iter = m_mapGMemberInfoDlg.find(key);
		if (iter != m_mapGMemberInfoDlg.end())
		{
			CBuddyInfoDlg * lpBuddyInfoDlg = iter->second;
			if (lpBuddyInfoDlg != NULL)
			{
				if (lpBuddyInfoDlg->IsWindow())
					lpBuddyInfoDlg->DestroyWindow();
				delete lpBuddyInfoDlg;
			}
			m_mapGMemberInfoDlg.erase(iter);
		}
	}
}

void CMainDlg::ShowGroupInfoDlg(UINT nGroupCode, BOOL bShow)
{
	if (0 == nGroupCode)
		return;

	if (bShow)
	{
		std::map<UINT, CGroupInfoDlg *>::iterator iter;
		iter = m_mapGroupInfoDlg.find(nGroupCode);
		if (iter != m_mapGroupInfoDlg.end())
		{
			CGroupInfoDlg * lpGroupInfoDlg = iter->second;
			if (lpGroupInfoDlg != NULL)
			{
				if (!lpGroupInfoDlg->IsWindow())
					lpGroupInfoDlg->Create(NULL);
				lpGroupInfoDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpGroupInfoDlg->m_hWnd);
			}
		}
		else
		{
			CGroupInfoDlg * lpGroupInfoDlg = new CGroupInfoDlg;
			if (lpGroupInfoDlg != NULL)
			{
				m_mapGroupInfoDlg[nGroupCode] = lpGroupInfoDlg;
				lpGroupInfoDlg->m_lpQQClient = &m_QQClient;
				lpGroupInfoDlg->m_hMainDlg = m_hWnd;
				lpGroupInfoDlg->m_nGroupCode = nGroupCode;
				lpGroupInfoDlg->Create(NULL);
				lpGroupInfoDlg->ShowWindow(SW_SHOW);
				::SetForegroundWindow(lpGroupInfoDlg->m_hWnd);
			}
		}
	}
	else
	{
		std::map<UINT, CGroupInfoDlg *>::iterator iter;
		iter = m_mapGroupInfoDlg.find(nGroupCode);
		if (iter != m_mapGroupInfoDlg.end())
		{
			CGroupInfoDlg * lpGroupInfoDlg = iter->second;
			if (lpGroupInfoDlg != NULL)
			{
				if (lpGroupInfoDlg->IsWindow())
					lpGroupInfoDlg->DestroyWindow();
				delete lpGroupInfoDlg;
			}
			m_mapGroupInfoDlg.erase(iter);
		}
	}
}

// 通知好友聊天窗口更新
void CMainDlg::NotifyBuddyChatDlg(UINT nQQUin, UINT uMsg)
{
	std::map<UINT, CBuddyChatDlg *>::iterator iter;
	iter = m_mapBuddyChatDlg.find(nQQUin);
	if (iter != m_mapBuddyChatDlg.end())
	{
		CBuddyChatDlg * lpBuddyChatDlg = iter->second;
		if (lpBuddyChatDlg != NULL && lpBuddyChatDlg->IsWindow())
		{
			switch (uMsg)
			{
			case QQ_MSG_UPDATE_BUDDY_NUMBER:
				lpBuddyChatDlg->OnUpdateBuddyNumber();
				break;

			case QQ_MSG_UPDATE_BUDDY_SIGN:
				lpBuddyChatDlg->OnUpdateBuddySign();
				break;

			case QQ_MSG_UPDATE_BUDDY_HEADPIC:
				lpBuddyChatDlg->OnUpdateBuddyHeadPic();
				break;
			}
		}
	}
}

// 通知群聊天窗口更新
void CMainDlg::NotifyGroupChatDlg(UINT nGroupCode, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	std::map<UINT, CGroupChatDlg *>::iterator iter;
	iter = m_mapGroupChatDlg.find(nGroupCode);
	if (iter != m_mapGroupChatDlg.end())
	{
		CGroupChatDlg * lpGroupChatDlg = iter->second;
		if (lpGroupChatDlg != NULL && lpGroupChatDlg->IsWindow())
		{
			switch (uMsg)
			{
			case QQ_MSG_UPDATE_GROUP_INFO:
				lpGroupChatDlg->OnUpdateGroupInfo();
				break;

			case QQ_MSG_UPDATE_GROUP_NUMBER:
				lpGroupChatDlg->OnUpdateGroupNumber();
				break;

			case QQ_MSG_UPDATE_GROUP_HEADPIC:
				lpGroupChatDlg->OnUpdateGroupHeadPic();
				break;

			case QQ_MSG_UPDATE_GMEMBER_NUMBER:
				lpGroupChatDlg->OnUpdateGMemberNumber(wParam, lParam);
				break;

			case QQ_MSG_UPDATE_GMEMBER_HEADPIC:
				lpGroupChatDlg->OnUpdateGMemberHeadPic(wParam, lParam);
				break;
			}
		}
	}
}

// 通知临时会话聊天窗口更新
void CMainDlg::NotifySessChatDlg(UINT nQQUin, UINT uMsg)
{
	std::map<UINT, CSessChatDlg *>::iterator iter;
	iter = m_mapSessChatDlg.find(nQQUin);
	if (iter != m_mapSessChatDlg.end())
	{
		CSessChatDlg * lpSessChatDlg = iter->second;
		if (lpSessChatDlg != NULL && lpSessChatDlg->IsWindow())
		{
 			switch (uMsg)
 			{
			case QQ_MSG_UPDATE_GMEMBER_NUMBER:
				lpSessChatDlg->OnUpdateGMemberNumber();
				break;
 			case QQ_MSG_UPDATE_GMEMBER_HEADPIC:
 				lpSessChatDlg->OnUpdateGMemberHeadPic();
 				break;
 			}
		}
	}
}

// 通知好友信息窗口更新
void CMainDlg::NotifyBuddyInfoDlg(UINT nQQUin, UINT uMsg)
{
	std::map<UINT, CBuddyInfoDlg *>::iterator iter;
	iter = m_mapBuddyInfoDlg.find(nQQUin);
	if (iter != m_mapBuddyInfoDlg.end())
	{
		CBuddyInfoDlg * lpBuddyInfoDlg = iter->second;
		if (lpBuddyInfoDlg != NULL && lpBuddyInfoDlg->IsWindow())
		{
			switch (uMsg)
			{
			case QQ_MSG_UPDATE_BUDDY_INFO:
				lpBuddyInfoDlg->OnUpdateBuddyInfo();
				break;

			case QQ_MSG_UPDATE_BUDDY_NUMBER:
				lpBuddyInfoDlg->OnUpdateBuddyNumber();
				break;

			case QQ_MSG_UPDATE_BUDDY_SIGN:
				lpBuddyInfoDlg->OnUpdateBuddySign();
				break;
			}
		}
	}
}

// 通知群成员信息窗口更新
void CMainDlg::NotifyGMemberInfoDlg(UINT nGroupCode, UINT nQQUin, UINT uMsg)
{
	CGMemberInfoMapKey key;
	key.m_nGroupCode = nGroupCode;
	key.m_nQQUin = nQQUin;
	std::map<CGMemberInfoMapKey, CBuddyInfoDlg *>::iterator iter;
	iter = m_mapGMemberInfoDlg.find(key);
	if (iter != m_mapGMemberInfoDlg.end())
	{
		CBuddyInfoDlg * lpBuddyInfoDlg = iter->second;
		if (lpBuddyInfoDlg != NULL && lpBuddyInfoDlg->IsWindow())
		{
			switch (uMsg)
			{
			case QQ_MSG_UPDATE_GMEMBER_INFO:
				lpBuddyInfoDlg->OnUpdateBuddyInfo();
				break;

			case QQ_MSG_UPDATE_GMEMBER_NUMBER:
				lpBuddyInfoDlg->OnUpdateBuddyNumber();
				break;

			case QQ_MSG_UPDATE_GMEMBER_SIGN:
				lpBuddyInfoDlg->OnUpdateBuddySign();
				break;
			}
		}
	}
}

// 通知群信息窗口更新
void CMainDlg::NotifyGroupInfoDlg(UINT nGroupCode, UINT uMsg)
{
	std::map<UINT, CGroupInfoDlg *>::iterator iter;
	iter = m_mapGroupInfoDlg.find(nGroupCode);
	if (iter != m_mapGroupInfoDlg.end())
	{
		CGroupInfoDlg * lpGroupInfoDlg = iter->second;
		if (lpGroupInfoDlg != NULL && lpGroupInfoDlg->IsWindow())
		{
			switch (uMsg)
			{
			case QQ_MSG_UPDATE_GROUP_INFO:
				lpGroupInfoDlg->OnUpdateGroupInfo();
				break;

			case QQ_MSG_UPDATE_GROUP_NUMBER:
				lpGroupInfoDlg->OnUpdateGroupNumber();
				break;
			}
		}
	}
}

void CMainDlg::UpdateBuddyTreeCtrl()
{
	CBuddyList * lpBuddyList = m_QQClient.GetBuddyList();
	if (NULL == lpBuddyList)
		return;

	m_BuddyListCtrl.DelAllItems();

	int nBuddyTeamCount = lpBuddyList->GetBuddyTeamCount();
	for (int i = 0; i < nBuddyTeamCount; i++)
	{
		int nBuddyCount = lpBuddyList->GetBuddyCount(i);
		int nOnlineBuddyCount = lpBuddyList->GetOnlineBuddyCount(i);
		int nTeamIndex = 0;

		CBuddyTeamInfo * lpBuddyTeamInfo = lpBuddyList->GetBuddyTeam(i);
		if (lpBuddyTeamInfo != NULL)
		{
			nTeamIndex = m_BuddyListCtrl.AddBuddyTeam(i);
			m_BuddyListCtrl.SetBuddyTeamName(nTeamIndex, lpBuddyTeamInfo->m_strName.c_str());
			m_BuddyListCtrl.SetBuddyTeamMaxCnt(nTeamIndex, nBuddyCount);
			m_BuddyListCtrl.SetBuddyTeamCurCnt(nTeamIndex, nOnlineBuddyCount);
			m_BuddyListCtrl.SetBuddyTeamExpand(nTeamIndex, FALSE);
		}

		for (int j = 0; j < nBuddyCount; j++)
		{
			CBuddyInfo * lpBuddyInfo = lpBuddyList->GetBuddy(i, j);
			if (lpBuddyInfo != NULL)
			{
				CString strQQNum;
				strQQNum.Format(_T("%u"), lpBuddyInfo->m_nQQNum);

				BOOL bGender = (lpBuddyInfo->m_strGender == _T("male")) ? TRUE : FALSE;
				BOOL bGray = lpBuddyInfo->m_nStatus != QQ_STATUS_OFFLINE ? FALSE : TRUE;

				tstring strFileName = m_QQClient.GetBuddyHeadPicFullName(lpBuddyInfo->m_nQQNum);
				if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
					strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefBuddyHeadPic.png");

				int nIndex = m_BuddyListCtrl.AddBuddyItem(nTeamIndex, lpBuddyInfo->m_nQQUin);
				m_BuddyListCtrl.SetBuddyItemQQNum(nTeamIndex, nIndex, strQQNum);
				m_BuddyListCtrl.SetBuddyItemNickName(nTeamIndex, nIndex, lpBuddyInfo->m_strNickName.c_str());
				m_BuddyListCtrl.SetBuddyItemMarkName(nTeamIndex, nIndex, lpBuddyInfo->m_strMarkName.c_str());
				m_BuddyListCtrl.SetBuddyItemGender(nTeamIndex, nIndex, bGender);
				m_BuddyListCtrl.SetBuddyItemHeadPic(nTeamIndex, nIndex, strFileName.c_str(), bGray);
				m_BuddyListCtrl.SetBuddyItemOnline(nTeamIndex, nIndex, !bGray, FALSE);
			}
		}
	}

	if (m_BuddyListCtrl.IsWindowVisible())
		m_BuddyListCtrl.Invalidate();
}

void CMainDlg::UpdateGroupTreeCtrl()
{
	CGroupList * lpGroupList = m_QQClient.GetGroupList();
	if (NULL == lpGroupList)
		return;

	m_GroupListCtrl.DelAllItems();

	int nGroupCount = lpGroupList->GetGroupCount();

	int nTeamIndex = m_GroupListCtrl.AddBuddyTeam(0);
	m_GroupListCtrl.SetBuddyTeamName(nTeamIndex, _T("我的QQ群"));
	m_GroupListCtrl.SetBuddyTeamMaxCnt(nTeamIndex, nGroupCount);
	m_GroupListCtrl.SetBuddyTeamCurCnt(nTeamIndex, nGroupCount);
	m_GroupListCtrl.SetBuddyTeamExpand(nTeamIndex, FALSE);

	for (int i = 0; i < nGroupCount; i++)
	{
		CGroupInfo * lpGroupInfo = lpGroupList->GetGroup(i);
		if (lpGroupInfo != NULL)
		{
			tstring strFileName = m_QQClient.GetGroupHeadPicFullName(lpGroupInfo->m_nGroupNumber);
			if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
				strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefGroupHeadPic.jpg");

			int nIndex = m_GroupListCtrl.AddBuddyItem(nTeamIndex, lpGroupInfo->m_nGroupCode);
			m_GroupListCtrl.SetBuddyItemNickName(nTeamIndex, nIndex, lpGroupInfo->m_strName.c_str());
			m_GroupListCtrl.SetBuddyItemHeadPic(nTeamIndex, nIndex, strFileName.c_str(), FALSE);
		}
	}

	if (m_GroupListCtrl.IsWindowVisible())
		m_GroupListCtrl.Invalidate();
}

void CMainDlg::UpdateRecentTreeCtrl()
{
	CRecentList * lpRecentList = m_QQClient.GetRecentList();
	if (NULL == lpRecentList)
		return;

	m_RecentListCtrl.DelAllItems();

	int nTeamIndex = m_RecentListCtrl.AddBuddyTeam(-1);
	m_RecentListCtrl.SetBuddyTeamName(nTeamIndex, _T("最近联系人"));
	m_RecentListCtrl.SetBuddyTeamExpand(nTeamIndex, FALSE);

	int nCount = 0;

	int nRecentCount = lpRecentList->GetRecentCount();
	for (int i = 0; i < nRecentCount; i++)
	{
		CRecentInfo * lpRecentInfo = lpRecentList->GetRecent(i);
		if (lpRecentInfo != NULL)
		{
			if (0 == lpRecentInfo->m_nType)			// 好友
			{
				CBuddyList * lpBuddyList = m_QQClient.GetBuddyList();
				if (lpBuddyList != NULL)
				{
					CBuddyInfo * lpBuddyInfo = lpBuddyList->GetBuddy(lpRecentInfo->m_nQQUin);
					if (lpBuddyInfo != NULL)
					{
						CString strQQNum;
						strQQNum.Format(_T("%u"), lpBuddyInfo->m_nQQNum);

						BOOL bGender = (lpBuddyInfo->m_strGender == _T("male")) ? TRUE : FALSE;
						BOOL bGray = lpBuddyInfo->m_nStatus != QQ_STATUS_OFFLINE ? FALSE : TRUE;

						tstring strFileName = m_QQClient.GetBuddyHeadPicFullName(lpBuddyInfo->m_nQQNum);
						if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
							strFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefBuddyHeadPic.png");

						int nIndex = m_RecentListCtrl.AddBuddyItem(nTeamIndex, i);
						m_RecentListCtrl.SetBuddyItemQQNum(nTeamIndex, nIndex, strQQNum);
						m_RecentListCtrl.SetBuddyItemNickName(nTeamIndex, nIndex, lpBuddyInfo->m_strNickName.c_str());
						m_RecentListCtrl.SetBuddyItemMarkName(nTeamIndex, nIndex, lpBuddyInfo->m_strMarkName.c_str());
						m_RecentListCtrl.SetBuddyItemGender(nTeamIndex, nIndex, bGender);
						m_RecentListCtrl.SetBuddyItemHeadPic(nTeamIndex, nIndex, strFileName.c_str(), bGray);

						nCount++;
					}
				}
			}
			else if (1 == lpRecentInfo->m_nType)	// 群
			{
				CGroupList * lpGroupList = m_QQClient.GetGroupList();
				if (lpGroupList != NULL)
				{
					CGroupInfo * lpGroupInfo = lpGroupList->GetGroupById(lpRecentInfo->m_nQQUin);
					if (lpGroupInfo != NULL)
					{
						tstring strFileName = m_QQClient.GetGroupHeadPicFullName(lpGroupInfo->m_nGroupNumber);
						if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
							strFileName = _T("Image\\DefGroupHeadPic.jpg");

						int nIndex = m_RecentListCtrl.AddBuddyItem(nTeamIndex, i);
						m_RecentListCtrl.SetBuddyItemNickName(nTeamIndex, nIndex, lpGroupInfo->m_strName.c_str());
						m_RecentListCtrl.SetBuddyItemHeadPic(nTeamIndex, nIndex, strFileName.c_str(), FALSE);

						nCount++;
					}
				}
			}
			else if (2 == lpRecentInfo->m_nType)	// 好像是讨论组
			{
			}
		}
	}

	m_RecentListCtrl.SetBuddyTeamMaxCnt(nTeamIndex, nCount);
	m_RecentListCtrl.SetBuddyTeamCurCnt(nTeamIndex, nCount);

	if (m_RecentListCtrl.IsWindowVisible())
		m_RecentListCtrl.Invalidate();
}

void CMainDlg::OnTrayIcon_LButtunUp()
{
	if (m_dwMsgTimerId != NULL)
	{
		CMessageList * lpMsgList = m_QQClient.GetMessageList();
		if (lpMsgList != NULL && lpMsgList->GetMsgSenderCount() > 0)
		{
			CMessageSender * lpMsgSender = lpMsgList->GetLastMsgSender();
			if (lpMsgSender != NULL)
			{
				QQ_MSG_TYPE nType = lpMsgSender->GetMsgType();
				UINT nSenderId = lpMsgSender->GetSenderId();
				UINT nGroupCode = lpMsgSender->GetGroupCode();

				switch (nType)
				{
				case QQ_MSG_TYPE_BUDDY:
					ShowBuddyChatDlg(nSenderId, TRUE);
					break;
				case QQ_MSG_TYPE_GROUP:
					ShowGroupChatDlg(nSenderId, TRUE);
					break;
				case QQ_MSG_TYPE_SESS:
					ShowSessChatDlg(nGroupCode, nSenderId, TRUE);
					break;
				case QQ_MSG_TYPE_SYSGROUP:
					ShowSysGroupChatDlg(nGroupCode, TRUE);
					break;
				}
			}
		}
	}
	else
	{
		if (m_LoginDlg.IsWindow())
		{
			m_LoginDlg.ShowWindow(SW_SHOW);
			::SetForegroundWindow(m_LoginDlg.m_hWnd);
		}
		else if (IsWindow())
		{
			ShowWindow(SW_SHOW);
			::SetForegroundWindow(m_hWnd);
		}
	}
}

void CMainDlg::OnTrayIcon_RButtunUp()
{
	if (m_MsgTipDlg.IsWindow())
		m_MsgTipDlg.DestroyWindow();

	int nPos = (m_QQClient.GetStatus() != QQ_STATUS_OFFLINE) ? 2 : 1;

	CPoint pt;
	GetCursorPos(&pt);

	::SetForegroundWindow(m_hWnd);

	CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(nPos);
	PopupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, m_hWnd);

	// BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
	::PostMessage(m_hWnd, WM_NULL, 0, 0);
}

void CMainDlg::OnTrayIcon_MouseHover()
{
	if (m_dwMsgTimerId != NULL)
	{
		CMessageList * lpMsgList = m_QQClient.GetMessageList();
		if (lpMsgList != NULL && lpMsgList->GetMsgSenderCount() > 0)
		{
			CRect rcTrayIcon;
			m_TrayIcon.GetTrayIconRect(&rcTrayIcon);

			m_MsgTipDlg.m_lpQQClient = &m_QQClient;
			m_MsgTipDlg.m_hMainDlg = m_hWnd;
			m_MsgTipDlg.m_rcTrayIcon = rcTrayIcon;
			if (!m_MsgTipDlg.IsWindow())
				m_MsgTipDlg.Create(m_hWnd);
			m_MsgTipDlg.ShowWindow(SW_SHOWNOACTIVATE);
		}
	}
	//::OutputDebugString(_T("WM_MOUSEHOVER\n"));
}

void CMainDlg::OnTrayIcon_MouseLeave()
{
	if (m_MsgTipDlg.IsWindow())
	{
		CRect rcWindow;
		m_MsgTipDlg.GetWindowRect(&rcWindow);

		POINT pt = {0};
		::GetCursorPos(&pt);

		if (!::PtInRect(&rcWindow, pt))
			m_MsgTipDlg.DestroyWindow();
		else
			m_MsgTipDlg.StartTrackMouseLeave();
	}
	//::OutputDebugString(_T("WM_MOUSELEAVE\n"));
}

BOOL CMainDlg::LoadAppIcon(QQ_STATUS nStatus)
{
	DestroyAppIcon();

	tstring strFileName;
	switch (nStatus)
	{
	case QQ_STATUS_ONLINE:
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\imonline.ico");
		break;
	case QQ_STATUS_CALLME:
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\Qme.ico");
		break;
	case QQ_STATUS_AWAY:
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\away.ico");
		break;
	case QQ_STATUS_BUSY:
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\busy.ico");
		break;
	case QQ_STATUS_SILENT:
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\mute.ico");
		break;
	case QQ_STATUS_HIDDEN:
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\invisible.ico");
		break;
	case QQ_STATUS_OFFLINE:
		strFileName = ZYM::CPath::GetAppPath() + _T("Image\\offline.ico");
		break;
	}
	m_hAppIcon = AtlLoadIconImage(strFileName.c_str(), LR_DEFAULTCOLOR|LR_LOADFROMFILE, 
		::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	return m_hAppIcon != NULL ? TRUE : FALSE;
}

void CMainDlg::DestroyAppIcon()
{
	if (m_hAppIcon != NULL)
	{
		::DestroyIcon(m_hAppIcon);
		m_hAppIcon = NULL;
	}
}

BOOL CMainDlg::LoadLoginIcon()
{
	DestroyLoginIcon();

	CString strFileName;
	for (int i = 0; i < 6; i++)
	{
		strFileName.Format(_T("%sImage\\Loading_%d.ico"), ZYM::CPath::GetAppPath().c_str(), i+1);
		m_hLoginIcon[i] = AtlLoadIconImage((LPCTSTR)strFileName, LR_DEFAULTCOLOR|LR_LOADFROMFILE, 
			::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	}

	return TRUE;
}

void CMainDlg::DestroyLoginIcon()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_hLoginIcon[i] != NULL)
		{
			::DestroyIcon(m_hLoginIcon[i]);
			m_hLoginIcon[i] = NULL;
		}
	}
}

void CMainDlg::UpdateMsgIcon()
{
	CMessageList * lpMsgList = m_QQClient.GetMessageList();
	if (NULL == lpMsgList)
		return;

	CMessageSender * lpMsgSender = lpMsgList->GetLastMsgSender();
	if (NULL == lpMsgSender)
		return;
	
	QQ_MSG_TYPE nMsgType = lpMsgSender->GetMsgType();
	UINT nSenderId = lpMsgSender->GetSenderId();
	UINT nGroupCode = lpMsgSender->GetGroupCode();

	if (m_nLastMsgType != nMsgType || m_nLastSenderId != nSenderId)
	{
		m_nLastMsgType = nMsgType;
		m_nLastSenderId = nSenderId;

		if (m_hMsgIcon != NULL)
		{
			::DestroyIcon(m_hMsgIcon);
			m_hMsgIcon = NULL;
		}

		CString strHeadPicFileName;

		if (QQ_MSG_TYPE_BUDDY == nMsgType)
			strHeadPicFileName = GetHeadPicFullName(0, nSenderId);
		else if (QQ_MSG_TYPE_GROUP == nMsgType)
			strHeadPicFileName = GetHeadPicFullName(nSenderId, 0);
		else if (QQ_MSG_TYPE_SESS == nMsgType)
			strHeadPicFileName = GetHeadPicFullName(nGroupCode, nSenderId);
// 		else if (QQ_MSG_TYPE_SYSGROUP == nMsgType)
// 			strHeadPicFileName = ZYM::CPath::GetAppPath() + _T("Image\\DefSysHeadPic.ico");

		m_hMsgIcon = ExtractIcon(strHeadPicFileName);
		if (NULL == m_hMsgIcon)
		{
			if (QQ_MSG_TYPE_BUDDY == nMsgType || QQ_MSG_TYPE_SESS == nMsgType)
				m_hMsgIcon = AtlLoadIconImage(IDI_BUDDY, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
			else if (QQ_MSG_TYPE_GROUP == nMsgType)
				m_hMsgIcon = AtlLoadIconImage(IDI_GROUPCHATDLG_16, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
			else if (QQ_MSG_TYPE_SYSGROUP == nMsgType)
				m_hMsgIcon = AtlLoadIconImage(IDI_SYS, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
		}
	}
}

CString CMainDlg::GetHeadPicFullName(UINT nGroupCode, UINT nQQUin)
{
	UINT nGroupNum, nQQNum;
	GetNumber(nGroupCode, nQQUin, nGroupNum, nQQNum);

	if (nGroupCode != 0 && nQQUin != 0)	// 群成员
		return m_QQClient.GetSessHeadPicFullName(nQQNum).c_str();
	else if (nGroupCode != 0)			// 群
		return m_QQClient.GetGroupHeadPicFullName(nGroupNum).c_str();
	else								// 好友
		return m_QQClient.GetBuddyHeadPicFullName(nQQNum).c_str();
}

void CMainDlg::GetNumber(UINT nGroupCode, UINT nQQUin, UINT& nGroupNum, UINT& nQQNum)
{
	nGroupNum = nQQNum = 0;

	if (nGroupCode != 0 && nQQUin != 0)
	{
		CGroupList * lpGroupList = m_QQClient.GetGroupList();
		if (lpGroupList != NULL)
		{
			CBuddyInfo * lpBuddyInfo = lpGroupList->GetGroupMemberByCode(nGroupCode, nQQUin);
			if (lpBuddyInfo != NULL)
				nQQNum = lpBuddyInfo->m_nQQNum;
		}
	}
	else if (nGroupCode != 0)
	{
		CGroupList * lpGroupList = m_QQClient.GetGroupList();
		if (lpGroupList != NULL)
		{
			CGroupInfo * lpGroupInfo = lpGroupList->GetGroupByCode(nGroupCode);
			if (lpGroupInfo != NULL)
				nGroupNum = lpGroupInfo->m_nGroupNumber;
		}
	}
	else if (nQQUin != 0)
	{
		CBuddyList * lpBuddyList = m_QQClient.GetBuddyList();
		if (lpBuddyList != NULL)
		{
			CBuddyInfo * lpBuddyInfo = lpBuddyList->GetBuddy(nQQUin);
			if (lpBuddyInfo != NULL)
				nQQNum = lpBuddyInfo->m_nQQNum;
		}
	}
}

HICON CMainDlg::ExtractIcon(LPCTSTR lpszFileName)
{
	if (NULL == lpszFileName || NULL == *lpszFileName)
		return NULL;

	int cx = 16, cy = 16;
	HBITMAP hBmp = NULL;

	Gdiplus::Bitmap imgHead(lpszFileName);
	if (imgHead.GetLastStatus() != Gdiplus::Ok)
		return NULL;

	if (imgHead.GetWidth() != cx || imgHead.GetHeight() != cy)
	{
		Gdiplus::Bitmap* pThumbnail = (Gdiplus::Bitmap*)imgHead.GetThumbnailImage(cx, cy, NULL, NULL);
		if (pThumbnail != NULL)
		{
			pThumbnail->GetHBITMAP(Gdiplus::Color(255,255,255), &hBmp);
			delete pThumbnail;
		}
	}
	else
	{
		imgHead.GetHBITMAP(Gdiplus::Color(255,255,255), &hBmp);
	}

	if (NULL == hBmp)
		return NULL;

	HICON hIcon = NULL;

	CImageList imgList;
	BOOL bRet = imgList.Create(cx, cy, TRUE | ILC_COLOR32, 1, 1);
	if (bRet)
	{
		imgList.SetBkColor(RGB(255,255,255));
		imgList.Add(hBmp);
		hIcon = imgList.ExtractIcon(0);
	}
	::DeleteObject(hBmp);
	imgList.Destroy();

	return hIcon;
}

void CMainDlg::CloseAllDlg()
{
	{
		std::map<UINT, CBuddyChatDlg *>::iterator iter;
		for (iter = m_mapBuddyChatDlg.begin(); iter != m_mapBuddyChatDlg.end(); iter++)
		{
			CBuddyChatDlg * lpBuddyChatDlg = iter->second;
			if (lpBuddyChatDlg != NULL)
			{
				if (lpBuddyChatDlg->IsWindow())
					lpBuddyChatDlg->DestroyWindow();
				delete lpBuddyChatDlg;
			}
		}
		m_mapBuddyChatDlg.clear();
	}

	{
		std::map<UINT, CGroupChatDlg *>::iterator iter;
		for (iter = m_mapGroupChatDlg.begin(); iter != m_mapGroupChatDlg.end(); iter++)
		{
			CGroupChatDlg * lpGroupChatDlg = iter->second;
			if (lpGroupChatDlg != NULL)
			{
				if (lpGroupChatDlg->IsWindow())
					lpGroupChatDlg->DestroyWindow();
				delete lpGroupChatDlg;
			}
		}
		m_mapGroupChatDlg.clear();
	}

	{
		std::map<UINT, CSessChatDlg *>::iterator iter;
		for (iter = m_mapSessChatDlg.begin(); iter != m_mapSessChatDlg.end(); iter++)
		{
			CSessChatDlg * lpSessChatDlg = iter->second;
			if (lpSessChatDlg != NULL)
			{
				if (lpSessChatDlg->IsWindow())
					lpSessChatDlg->DestroyWindow();
				delete lpSessChatDlg;
			}
		}
		m_mapSessChatDlg.clear();
	}

	{
		std::map<UINT, CBuddyInfoDlg *>::iterator iter;
		for (iter = m_mapBuddyInfoDlg.begin(); iter != m_mapBuddyInfoDlg.end(); iter++)
		{
			CBuddyInfoDlg * lpBuddyInfoDlg = iter->second;
			if (lpBuddyInfoDlg != NULL)
			{
				if (lpBuddyInfoDlg->IsWindow())
					lpBuddyInfoDlg->DestroyWindow();
				delete lpBuddyInfoDlg;
			}
		}
		m_mapBuddyInfoDlg.clear();
	}

	{
		std::map<CGMemberInfoMapKey, CBuddyInfoDlg *>::iterator iter;
		for (iter = m_mapGMemberInfoDlg.begin(); iter != m_mapGMemberInfoDlg.end(); iter++)
		{
			CBuddyInfoDlg * lpBuddyInfoDlg = iter->second;
			if (lpBuddyInfoDlg != NULL)
			{
				if (lpBuddyInfoDlg->IsWindow())
					lpBuddyInfoDlg->DestroyWindow();
				delete lpBuddyInfoDlg;
			}
		}
		m_mapGMemberInfoDlg.clear();
	}

	{
		std::map<UINT, CGroupInfoDlg *>::iterator iter;
		for (iter = m_mapGroupInfoDlg.begin(); iter != m_mapGroupInfoDlg.end(); iter++)
		{
			CGroupInfoDlg * lpGroupInfoDlg = iter->second;
			if (lpGroupInfoDlg != NULL)
			{
				if (lpGroupInfoDlg->IsWindow())
					lpGroupInfoDlg->DestroyWindow();
				delete lpGroupInfoDlg;
			}
		}
		m_mapGroupInfoDlg.clear();
	}
}

// 从菜单ID获取对应的QQ_STATUS
QQ_STATUS CMainDlg::GetStatusFromMenuID(int nMenuID)
{
	switch (nMenuID)
	{
	case ID_MENU_IMONLINE:
		return QQ_STATUS_ONLINE;
	case ID_MENU_QME:
		return QQ_STATUS_CALLME;
	case ID_MENU_AWAY:
		return QQ_STATUS_AWAY;
	case ID_MENU_BUSY:
		return QQ_STATUS_BUSY;
	case ID_MENU_MUTE:
		return QQ_STATUS_SILENT;
	case ID_MENU_INVISIBLE:
		return QQ_STATUS_HIDDEN;
	case ID_MENU_IMOFFLINE:
		return QQ_STATUS_OFFLINE;
	default:
		return QQ_STATUS_OFFLINE;
	}
}

// 根据指定状态设置状态菜单按钮的图标
void CMainDlg::StatusMenuBtn_SetIconPic(CSkinButton& btnStatus, QQ_STATUS nStatus)
{
	LPCTSTR lpszFileName;

	switch (nStatus)
	{
	case QQ_STATUS_ONLINE:
		lpszFileName = _T("Status\\imonline.png");
		break;
	case QQ_STATUS_CALLME:
		lpszFileName = _T("Status\\Qme.png");
		break;
	case QQ_STATUS_AWAY:
		lpszFileName = _T("Status\\away.png");
		break;
	case QQ_STATUS_BUSY:
		lpszFileName = _T("Status\\busy.png");
		break;
	case QQ_STATUS_SILENT:
		lpszFileName = _T("Status\\mute.png");
		break;
	case QQ_STATUS_HIDDEN:
		lpszFileName = _T("Status\\invisible.png");
		break;
	case QQ_STATUS_OFFLINE:
		lpszFileName = _T("Status\\imoffline.png");
		break;
	default:
		return;
	}

	btnStatus.SetIconPic(lpszFileName);
	btnStatus.Invalidate();
}