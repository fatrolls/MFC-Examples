#include "StdAfx.h"
#include "LoginDlg.h"

CLoginDlg::CLoginDlg(void)
{
	m_lpQQClient = NULL;
	m_pLoginAccountList = NULL;
	m_hDlgIcon = m_hDlgSmallIcon = NULL;
	memset(&m_stAccountInfo, 0, sizeof(m_stAccountInfo));
	m_stAccountInfo.nStatus = QQ_STATUS_ONLINE;
}

CLoginDlg::~CLoginDlg(void)
{
}

BOOL CLoginDlg::GetLoginAccountInfo(LOGIN_ACCOUNT_INFO * lpAccount)
{
	if (NULL == lpAccount)
		return FALSE;

	memcpy(lpAccount, &m_stAccountInfo, sizeof(LOGIN_ACCOUNT_INFO));
	return TRUE;
}

BOOL CLoginDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	SetWindowPos(HWND_TOPMOST, 0, 0, 350, 266, SWP_NOMOVE);

	// center the dialog on the screen
	CenterWindow();

	// set icons
	m_hDlgIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(m_hDlgIcon, TRUE);
	m_hDlgSmallIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(m_hDlgSmallIcon, FALSE);

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	m_bFirstModify = FALSE;
	InitUI();

	return TRUE;
}

void CLoginDlg::OnSysCommand(UINT nID, CPoint pt)
{
	if (nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
		return;
	}

	SetMsgHandled(FALSE);
}

void CLoginDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	m_SkinMenu.OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CLoginDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_SkinMenu.OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CLoginDlg::OnClose()
{
	EndDialog(IDCANCEL);
}

void CLoginDlg::OnDestroy()
{
	// unregister message filtering and idle updates
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

	UninitUI();
}

// “QQ帐号”组合框
void CLoginDlg::OnCbo_EditChange_UID(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CString strText;
	m_cboUid.GetWindowText(strText);

	LOGIN_ACCOUNT_INFO * lpAccount = m_pLoginAccountList->Find(strText);
	if (NULL == lpAccount)
	{
		if (m_bFirstModify)
		{
			m_bFirstModify = FALSE;

			m_picHead.SetBitmap(_T("DefaultFace.png"));		// 设置用户头像
			m_picHead.Invalidate();
			
			m_btnRememberPwd.SetCheck(m_stAccountInfo.bRememberPwd ? BST_CHECKED : BST_UNCHECKED);
			m_btnAutoLogin.SetCheck(m_stAccountInfo.bAutoLogin ? BST_CHECKED : BST_UNCHECKED);
			m_stAccountInfo.nStatus = QQ_STATUS_ONLINE;
			StatusMenuBtn_SetIconPic(m_btnLoginStatus, (QQ_STATUS)m_stAccountInfo.nStatus);
			m_edtPwd.SetWindowText(_T(""));
			m_edtPwd.SetDefaultTextMode(TRUE);
		}
	}
	else
		SetCurUser(strText);
}

// “QQ帐号”组合框
void CLoginDlg::OnCbo_SelChange_UID(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	int nCurSel = m_cboUid.GetCurSel();
	if (nCurSel != -1)
	{
		CString strUser;
		m_cboUid.GetLBText(nCurSel, strUser);
		SetCurUser(strUser);
	}
}

// “记住密码”复选框
void CLoginDlg::OnBtn_RememberPwd(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	// 取消“记住密码”复选框，则自动取消“自动登录”复选框
	if (m_btnRememberPwd.GetCheck() == BST_UNCHECKED)
		m_btnAutoLogin.SetCheck(BST_UNCHECKED);
}

// “自动登录”复选框
void CLoginDlg::OnBtn_AutoLogin(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	// 选中“自动登录”复选框，则自动选上“记住密码”复选框
	if (m_btnAutoLogin.GetCheck() == BST_CHECKED)
		m_btnRememberPwd.SetCheck(BST_CHECKED);
}

// “登录”按钮
void CLoginDlg::OnBtn_Login(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	if (m_cboUid.IsDefaultText())
	{
		MessageBox(_T("请输入帐号！"), _T("提示"), MB_OK|MB_ICONINFORMATION);
		m_cboUid.SetFocus();
		return;
	}

	if (m_edtPwd.IsDefaultText())
	{
		MessageBox(_T("请输入密码！"), _T("提示"), MB_OK|MB_ICONINFORMATION);
		m_edtPwd.SetFocus();
		return;
	}

	m_cboUid.GetWindowText(m_stAccountInfo.szUser, sizeof(m_stAccountInfo.szUser)/sizeof(TCHAR));
	m_edtPwd.GetWindowText(m_stAccountInfo.szPwd, sizeof(m_stAccountInfo.szPwd)/sizeof(TCHAR));
	m_stAccountInfo.bRememberPwd = (m_btnRememberPwd.GetCheck() == BST_CHECKED);
	m_stAccountInfo.bAutoLogin = (m_btnAutoLogin.GetCheck() == BST_CHECKED);

	EndDialog(IDOK);
}

// “设置”按钮
void CLoginDlg::OnBtn_Set(UINT uNotifyCode, int nID, CWindow wndCtl)
{
}

// “登录状态”菜单按钮
void CLoginDlg::OnMenu_LoginStatus(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	m_stAccountInfo.nStatus = (int)GetStatusFromMenuID(nID);
	StatusMenuBtn_SetIconPic(m_btnLoginStatus, (QQ_STATUS)m_stAccountInfo.nStatus);
}

BOOL CLoginDlg::InitUI()
{
	m_SkinDlg.SetBgPic(_T("LoginBg.png"));
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

	int nBtnWidth = 69;
	int nBtnHeight = 22;

	m_btnMultiAccount.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnMultiAccount.SetTransparent(TRUE, hDlgBgDC);
	m_btnMultiAccount.SetBgPic(_T("Button\\btn_normal.png"), _T("Button\\btn_highlight.png"),
		_T("Button\\btn_down.png"), _T("Button\\btn_focus.png"));
	m_btnMultiAccount.SetIconPic(_T("SwitchBtn.png"));
	m_btnMultiAccount.SetRound(4, 4);
	m_btnMultiAccount.SubclassWindow(GetDlgItem(ID_BTN_MULTI_ACCOUNT));
	m_btnMultiAccount.MoveWindow(7, 238, nBtnWidth, nBtnHeight, FALSE);

	m_btnSet.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnSet.SetTransparent(TRUE, hDlgBgDC);
	m_btnSet.SetBgPic(_T("Button\\btn_normal.png"), _T("Button\\btn_highlight.png"),
		_T("Button\\btn_down.png"), _T("Button\\btn_focus.png"));
	m_btnSet.SetRound(4, 4);
	m_btnSet.SubclassWindow(GetDlgItem(ID_BTN_SET));
	m_btnSet.MoveWindow(83, 238, nBtnWidth, nBtnHeight, FALSE);

	m_btnLogin.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnLogin.SetTransparent(TRUE, hDlgBgDC);
	m_btnLogin.SetBgPic(_T("Button\\btn_normal.png"), _T("Button\\btn_highlight.png"),
		_T("Button\\btn_down.png"), _T("Button\\btn_focus.png"));
	m_btnLogin.SetRound(4, 4);
	m_btnLogin.SubclassWindow(GetDlgItem(ID_BTN_LOGIN));
	m_btnLogin.MoveWindow(270, 238, nBtnWidth, nBtnHeight, FALSE);

	m_btnRememberPwd.SetButtonType(SKIN_CHECKBOX);
	m_btnRememberPwd.SetTransparent(TRUE, hDlgBgDC);
	m_btnRememberPwd.SetCheckBoxPic(_T("CheckBox\\checkbox_normal.png"), _T("CheckBox\\checkbox_hightlight.png"),
		_T("CheckBox\\checkbox_tick_normal.png"), _T("CheckBox\\checkbox_tick_highlight.png"));
	m_btnRememberPwd.SubclassWindow(GetDlgItem(ID_CHECK_REMEMBER_PWD));
	m_btnRememberPwd.MoveWindow(146, 196, 68, 15, FALSE);

	m_btnAutoLogin.SetButtonType(SKIN_CHECKBOX);
	m_btnAutoLogin.SetTransparent(TRUE, hDlgBgDC);
	m_btnAutoLogin.SetCheckBoxPic(_T("CheckBox\\checkbox_normal.png"), _T("CheckBox\\checkbox_hightlight.png"),
		_T("CheckBox\\checkbox_tick_normal.png"), _T("CheckBox\\checkbox_tick_highlight.png"));
	m_btnAutoLogin.SubclassWindow(GetDlgItem(ID_CHECK_AUTO_LOGIN));
	m_btnAutoLogin.MoveWindow(226, 196, 68, 15, FALSE);

	m_lnkRegAccount.SetTransparent(TRUE, hDlgBgDC);
	m_lnkRegAccount.SetLinkColor(RGB(22, 112, 235));
	m_lnkRegAccount.SetHoverLinkColor(RGB(22, 112, 235));
	m_lnkRegAccount.SetVisitedLinkColor(RGB(22, 112, 235));
	m_lnkRegAccount.SubclassWindow(GetDlgItem(ID_STATIC_REG_ACCOUNT));
	m_lnkRegAccount.SetLabel(_T("注册帐号"));
	m_lnkRegAccount.SetHyperLink(_T("http://zc.qq.com/chs/index.html?from=client&ptlang=2052&ADUIN=0&ADSESSION=0&ADTAG=CLIENT.QQ.4153_NewAccount_Btn.0"));
	//m_lnkRegAccount.SetToolTipText(_T("注册帐号"));
	m_lnkRegAccount.MoveWindow(288, 132, 48, 14, FALSE);

	m_lnkLostPwd.SetTransparent(TRUE, hDlgBgDC);
	m_lnkLostPwd.SetLinkColor(RGB(22, 112, 235));
	m_lnkLostPwd.SetHoverLinkColor(RGB(22, 112, 235));
	m_lnkLostPwd.SetVisitedLinkColor(RGB(22, 112, 235));
	m_lnkLostPwd.SubclassWindow(GetDlgItem(ID_STATIC_LOST_PWD));
	m_lnkLostPwd.SetLabel(_T("找回密码"));
	m_lnkLostPwd.SetHyperLink(_T("http://aq.qq.com/cn2/findpsw/findpsw_index?source_id=1003&ptlang=2052&aquin=123456"));
	//m_lnkLostPwd.SetToolTipText(_T("找回密码"));
	m_lnkLostPwd.MoveWindow(288, 168, 48, 14, FALSE);

	m_cboUid.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_cboUid.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_cboUid.SetArrowNormalPic(_T("ComboBox\\login_inputbtn_normal.png"));
	m_cboUid.SetArrowHotPic(_T("ComboBox\\login_inputbtn_highlight.png"));
	m_cboUid.SetArrowPushedPic(_T("ComboBox\\login_inputbtn_down.png"));
	m_cboUid.SetTransparent(TRUE, hDlgBgDC);
	m_cboUid.SetArrowWidth(23);
	m_cboUid.SetDefaultText(_T("请输入帐号"));
	m_cboUid.SubclassWindow(GetDlgItem(ID_COMBO_UID));
	m_cboUid.MoveWindow(102, 126, 180, 26, FALSE);
	m_cboUid.SetItemHeight(-1, 22);

	if (m_pLoginAccountList != NULL)	// 添加登录帐号列表
	{
		for (int i = 0; i < m_pLoginAccountList->GetCount(); i++)
		{
			LOGIN_ACCOUNT_INFO * lpAccount = m_pLoginAccountList->GetAccountInfo(i);
			if (lpAccount != NULL)
				m_cboUid.AddString(lpAccount->szUser);
		}
	}
	
	m_edtPwd.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtPwd.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtPwd.SetIconPic(_T("keyboard.png"));
	m_edtPwd.SetTransparent(TRUE, hDlgBgDC);
	m_edtPwd.SetDefaultText(_T("请输入密码"));
	m_edtPwd.SubclassWindow(GetDlgItem(ID_EDIT_PWD));
	m_edtPwd.MoveWindow(102, 162, 180, 26, FALSE);

	m_edtPwd.SetPasswordChar(0x25CF);

	m_picHead.SetTransparent(TRUE, hDlgBgDC);
	m_picHead.SetBitmap(_T("DefaultFace.png"));
	m_picHead.SubclassWindow(GetDlgItem(ID_STATIC_FACE));
	m_picHead.MoveWindow(10, 126, 82, 82, FALSE);

	m_SkinMenu.SetBgPic(_T("Menu\\menu_left_bg.png"), _T("Menu\\menu_right_bg.png"));
	m_SkinMenu.SetSelectedPic(_T("Menu\\menu_selected.png"));
	m_SkinMenu.SetSepartorPic(_T("Menu\\menu_separtor.png"));
	m_SkinMenu.SetArrowPic(_T("Menu\\menu_arrow.png"));
	m_SkinMenu.SetCheckPic(_T("Menu\\menu_check.png"));
	m_SkinMenu.SetTextColor(RGB(0, 20, 35));
	m_SkinMenu.SetSelTextColor(RGB(254, 254, 254));
	m_SkinMenu.LoadMenu(ID_MENU_LOGINSTATUS);

	DWORD dwMenuIDs[] = {ID_MENU_IMONLINE, ID_MENU_QME, 
		ID_MENU_AWAY, ID_MENU_BUSY, ID_MENU_MUTE, ID_MENU_INVISIBLE};
	CString strFileNames[] = {_T("Status\\imonline.png"), _T("Status\\Qme.png"), 
		_T("Status\\away.png"), _T("Status\\busy.png"), _T("Status\\mute.png"), 
		_T("Status\\invisible.png")};

	for (int i = 0; i < 6; i++)
	{
		m_SkinMenu.SetIcon(dwMenuIDs[i], FALSE, strFileNames[i], strFileNames[i]);
	}

	CSkinMenu PopupMenu = m_SkinMenu.GetSubMenu(0);

	m_btnLoginStatus.SetButtonType(SKIN_MENU_BUTTON);
	m_btnLoginStatus.SetTransparent(TRUE, hDlgBgDC);
	m_btnLoginStatus.SetBgPic(NULL , _T("menubtn_highlight.png"), _T("menubtn_highlight.png"), NULL);
	m_btnLoginStatus.SetArrowPic(_T("MainPanel_FolderNode_expandTexture.png"));
	m_btnLoginStatus.SetIconPic(_T("Status\\imonline.png"));
	m_btnLoginStatus.SubclassWindow(GetDlgItem(ID_BTN_LOGIN_STATUS));
	m_btnLoginStatus.MoveWindow(102, 192, 35, 22, FALSE);
	m_btnLoginStatus.SetMenu(PopupMenu.m_hMenu);

	if (m_stAccountInfo.szUser[0] != _T('\0'))
	{
		SetCurUser(m_stAccountInfo.szUser, TRUE);
	}
	else
	{
		if (m_pLoginAccountList != NULL && m_pLoginAccountList->GetCount() > 0)
		{
			LOGIN_ACCOUNT_INFO * lpAccount = m_pLoginAccountList->GetLastLoginAccountInfo();
			if (lpAccount != NULL)
				SetCurUser(lpAccount->szUser);
		}
		else
		{
			SetCurUser(NULL);
		}
	}

	return TRUE;
}

void CLoginDlg::SetCurUser(LPCTSTR lpszUser, BOOL bPwdInvalid/* = FALSE*/)
{
	if (NULL == lpszUser)
	{
		m_picHead.SetBitmap(_T("DefaultFace.png"));		// 设置用户头像
		m_picHead.Invalidate();

		m_btnRememberPwd.SetCheck(m_stAccountInfo.bRememberPwd ? BST_CHECKED : BST_UNCHECKED);
		m_btnAutoLogin.SetCheck(m_stAccountInfo.bAutoLogin ? BST_CHECKED : BST_UNCHECKED);
		m_stAccountInfo.nStatus = (int)QQ_STATUS_ONLINE;
		StatusMenuBtn_SetIconPic(m_btnLoginStatus, (QQ_STATUS)m_stAccountInfo.nStatus);
		m_cboUid.SetWindowText(_T(""));
		m_edtPwd.SetWindowText(_T(""));
		m_edtPwd.SetDefaultTextMode(TRUE);
	}
	else
	{
		if (m_pLoginAccountList != NULL)
		{
			LOGIN_ACCOUNT_INFO * lpAccount = m_pLoginAccountList->Find(lpszUser);
			if (NULL == lpAccount)
			{
				m_picHead.SetBitmap(_T("DefaultFace.png"));		// 设置用户头像
				m_picHead.Invalidate();

				m_btnRememberPwd.SetCheck(m_stAccountInfo.bRememberPwd ? BST_CHECKED : BST_UNCHECKED);
				m_btnAutoLogin.SetCheck(m_stAccountInfo.bAutoLogin ? BST_CHECKED : BST_UNCHECKED);
				StatusMenuBtn_SetIconPic(m_btnLoginStatus, (QQ_STATUS)m_stAccountInfo.nStatus);
				CString strText;
				m_cboUid.GetWindowText(strText);
				if (strText != lpszUser)
					m_cboUid.SetWindowText(lpszUser);
				m_edtPwd.SetWindowText(_T(""));
				m_edtPwd.SetDefaultTextMode(TRUE);
			}
			else
			{
				if (m_lpQQClient != NULL)	// 设置用户头像
				{
					UINT nQQUin = _tcstoul(lpszUser, NULL, 10);
					tstring strFileName = m_lpQQClient->GetUserHeadPicFullName(nQQUin);
					if (!ZYM::CPath::IsFileExist(strFileName.c_str()))
						strFileName = _T("DefaultFace.png");
					m_picHead.SetBitmap(strFileName.c_str());
					m_picHead.Invalidate();
				}

				m_btnRememberPwd.SetCheck(lpAccount->bRememberPwd ? BST_CHECKED : BST_UNCHECKED);
				m_btnAutoLogin.SetCheck(lpAccount->bAutoLogin ? BST_CHECKED : BST_UNCHECKED);
				m_stAccountInfo.nStatus = (int)lpAccount->nStatus;
				StatusMenuBtn_SetIconPic(m_btnLoginStatus, (QQ_STATUS)m_stAccountInfo.nStatus);
				CString strText;
				m_cboUid.GetWindowText(strText);
				if (strText != lpszUser)
					m_cboUid.SetWindowText(lpszUser);
				if (!bPwdInvalid && lpAccount->bRememberPwd)
				{
					m_edtPwd.SetDefaultTextMode(FALSE);
					m_edtPwd.SetWindowText(lpAccount->szPwd);
				}
				else
				{
					m_edtPwd.SetWindowText(_T(""));
					m_edtPwd.SetDefaultTextMode(TRUE);
				}
				m_bFirstModify = TRUE;
			}
		}
	}
}

void CLoginDlg::UninitUI()
{
	if (m_cboUid.IsWindow())
		m_cboUid.DestroyWindow();

	if (m_edtPwd.IsWindow())
		m_edtPwd.DestroyWindow();

	if (m_btnRememberPwd.IsWindow())
		m_btnRememberPwd.DestroyWindow();

	if (m_btnAutoLogin.IsWindow())
		m_btnAutoLogin.DestroyWindow();

	if (m_lnkRegAccount.IsWindow())
		m_lnkRegAccount.DestroyWindow();

	if (m_lnkLostPwd.IsWindow())
		m_lnkLostPwd.DestroyWindow();

	if (m_btnMultiAccount.IsWindow())
		m_btnMultiAccount.DestroyWindow();

	if (m_btnSet.IsWindow())
		m_btnSet.DestroyWindow();

	if (m_btnLogin.IsWindow())
		m_btnLogin.DestroyWindow();

	if (m_btnLoginStatus.IsWindow())
		m_btnLoginStatus.DestroyWindow();

	if (m_picHead.IsWindow())
		m_picHead.DestroyWindow();

	m_SkinMenu.DestroyMenu();
}

// 从菜单ID获取对应的QQ_STATUS
QQ_STATUS CLoginDlg::GetStatusFromMenuID(int nMenuID)
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
void CLoginDlg::StatusMenuBtn_SetIconPic(CSkinButton& btnStatus, QQ_STATUS nStatus)
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

