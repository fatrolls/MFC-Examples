#include "StdAfx.h"
#include "BuddyInfoDlg.h"

CBuddyInfoDlg::CBuddyInfoDlg(void)
{
	m_lpQQClient = NULL;
	m_hMainDlg = NULL;
	m_nQQUin = 0;
	m_bIsGMember = FALSE;
	m_nGroupCode = 0;
	m_hDlgIcon = m_hDlgSmallIcon = NULL;
}

CBuddyInfoDlg::~CBuddyInfoDlg(void)
{
}

BOOL CBuddyInfoDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	SetWindowPos(NULL, 0, 0, 580, 480, SWP_NOMOVE);

	CenterWindow();

	// set icons
	m_hDlgIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(m_hDlgIcon, TRUE);
	m_hDlgSmallIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(m_hDlgSmallIcon, FALSE);

	Init();		// 初始化

	CBuddyInfo * lpBuddyInfo = GetBuddyInfoPtr();
	if (NULL == lpBuddyInfo)
		return TRUE;

	CString strTitle;
	if (m_bIsGMember || lpBuddyInfo->m_strMarkName.empty())
		strTitle.Format(_T("%s的资料"), lpBuddyInfo->m_strNickName.c_str());
	else
		strTitle.Format(_T("%s的资料"), lpBuddyInfo->m_strMarkName.c_str());
	m_SkinDlg.SetTitleText(strTitle);

	if (m_lpQQClient != NULL)
	{
		if (!lpBuddyInfo->IsHasBuddyInfo())
		{
			if (!m_bIsGMember)
				m_lpQQClient->UpdateBuddyInfo(m_nQQUin);
			else
				m_lpQQClient->UpdateGroupMemberInfo(m_nGroupCode, m_nQQUin);
		}
		if (!lpBuddyInfo->IsHasQQNum())
		{
			if (!m_bIsGMember)
				m_lpQQClient->UpdateBuddyNum(m_nQQUin);
			else
				m_lpQQClient->UpdateGroupMemberNum(m_nGroupCode, m_nQQUin);
		}
		if (!lpBuddyInfo->IsHasQQSign())
		{
			if (!m_bIsGMember)
				m_lpQQClient->UpdateBuddySign(m_nQQUin);
			else
				m_lpQQClient->UpdateGroupMemberSign(m_nGroupCode, m_nQQUin);
		}
	}

	UpdateCtrls();

	return TRUE;
}

void CBuddyInfoDlg::OnClose()
{
	if (!m_bIsGMember)
		::PostMessage(m_hMainDlg, WM_CLOSE_BUDDYINFODLG, NULL, m_nQQUin);
	else
		::PostMessage(m_hMainDlg, WM_CLOSE_GMEMBERINFODLG, m_nGroupCode, m_nQQUin);
}

void CBuddyInfoDlg::OnDestroy()
{
	SetMsgHandled(FALSE);

	UnInit();	// 反初始化

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
}

// “更新”按钮
void CBuddyInfoDlg::OnBtn_Update(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	if (m_lpQQClient != NULL)
	{
		if (!m_bIsGMember)
		{
			m_lpQQClient->UpdateBuddyInfo(m_nQQUin);
			m_lpQQClient->UpdateBuddyNum(m_nQQUin);
			m_lpQQClient->UpdateBuddySign(m_nQQUin);
		}
		else
		{
			m_lpQQClient->UpdateGroupMemberInfo(m_nGroupCode, m_nQQUin);
			m_lpQQClient->UpdateGroupMemberNum(m_nGroupCode, m_nQQUin);
			m_lpQQClient->UpdateGroupMemberSign(m_nGroupCode, m_nQQUin);
		}
	}
}

// “关闭”按钮
void CBuddyInfoDlg::OnBtn_Close(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	SendMessage(WM_CLOSE);
}

void CBuddyInfoDlg::OnUpdateBuddyInfo()
{
	UpdateCtrls();
}

void CBuddyInfoDlg::OnUpdateBuddyNumber()
{
	UpdateCtrls();
}

void CBuddyInfoDlg::OnUpdateBuddySign()
{
	UpdateCtrls();
}

CBuddyInfo * CBuddyInfoDlg::GetBuddyInfoPtr()
{
	if (NULL == m_lpQQClient)
		return NULL;

	if (!m_bIsGMember)
	{
		CBuddyInfo * lpUserInfo = m_lpQQClient->GetUserInfo();
		if (lpUserInfo != NULL && lpUserInfo->m_nQQUin == m_nQQUin)
		{
			return lpUserInfo;
		}
		else
		{
			CBuddyList * lpBuddyList = m_lpQQClient->GetBuddyList();
			if (lpBuddyList != NULL)
				return lpBuddyList->GetBuddy(m_nQQUin);
		}
	}
	else
	{
		CGroupList * lpGroupList = m_lpQQClient->GetGroupList();
		if (lpGroupList != NULL)
			return lpGroupList->GetGroupMemberByCode(m_nGroupCode, m_nQQUin);
	}

	return NULL;
}

void CBuddyInfoDlg::UpdateCtrls()
{
	CString strText;
	CBuddyInfo * lpBuddyInfo = GetBuddyInfoPtr();
	if (lpBuddyInfo != NULL)
	{
		SetDlgItemText(ID_EDIT_NICKNAME, lpBuddyInfo->m_strNickName.c_str());
		SetDlgItemText(ID_EDIT_MARKNAME, lpBuddyInfo->m_strMarkName.c_str());
		strText.Format(_T("%u"), lpBuddyInfo->m_nQQNum);
		SetDlgItemText(ID_EDIT_NUMBER, strText);
		SetDlgItemText(ID_EDIT_SIGN, lpBuddyInfo->m_strSign.c_str());

		SetDlgItemText(ID_EDIT_GENDER, lpBuddyInfo->GetDisplayGender().c_str());
		SetDlgItemText(ID_EDIT_SHENGXIAO, lpBuddyInfo->GetDisplayShengXiao().c_str());
		SetDlgItemText(ID_EDIT_CONSTEL, lpBuddyInfo->GetDisplayConstel().c_str());
		SetDlgItemText(ID_EDIT_BLOOD, lpBuddyInfo->GetDisplayBlood().c_str());
		SetDlgItemText(ID_EDIT_BIRTHDAY, lpBuddyInfo->m_strBirthday.c_str());
		SetDlgItemText(ID_EDIT_COUNTRY, lpBuddyInfo->m_strCountry.c_str());
		SetDlgItemText(ID_EDIT_PROVINCE, lpBuddyInfo->m_strProvince.c_str());
		SetDlgItemText(ID_EDIT_CITY, lpBuddyInfo->m_strCity.c_str());
		SetDlgItemText(ID_EDIT_PHONE, lpBuddyInfo->m_strPhone.c_str());
		SetDlgItemText(ID_EDIT_MOBILE, lpBuddyInfo->m_strMobile.c_str());
		SetDlgItemText(ID_EDIT_EMAIL, lpBuddyInfo->m_strEmail.c_str());
		SetDlgItemText(ID_EDIT_OCCUPATION, lpBuddyInfo->m_strOccupation.c_str());
		SetDlgItemText(ID_EDIT_COLLEGE, lpBuddyInfo->m_strCollege.c_str());
		SetDlgItemText(ID_EDIT_HOMEPAGE, lpBuddyInfo->m_strHomepage.c_str());
		SetDlgItemText(ID_EDIT_PERSONAL, lpBuddyInfo->m_strPersonal.c_str());
	}
}

// 初始化
BOOL CBuddyInfoDlg::Init()
{
	m_SkinDlg.SetBgPic(_T("LoginPanel_window_windowBkg.png"), CRect(40, 86, 152, 155));
	m_SkinDlg.SetMinSysBtnPic(_T("SysBtn\\btn_mini_normal.png"), 
		_T("SysBtn\\btn_mini_highlight.png"), _T("SysBtn\\btn_mini_down.png"));
	m_SkinDlg.SetCloseSysBtnPic(_T("SysBtn\\btn_close_normal.png"), 
		_T("SysBtn\\btn_close_highlight.png"), _T("SysBtn\\btn_close_down.png"));
	m_SkinDlg.SubclassWindow(m_hWnd);

	HDC hDlgBgDC = m_SkinDlg.GetBgDC();

	m_staNumber.SetTransparent(TRUE, hDlgBgDC);
	m_staNumber.SubclassWindow(GetDlgItem(ID_STATIC_NUMBER));
	m_staNickName.SetTransparent(TRUE, hDlgBgDC);
	m_staNickName.SubclassWindow(GetDlgItem(ID_STATIC_NICKNAME));
	m_staMarkName.SetTransparent(TRUE, hDlgBgDC);
	m_staMarkName.SubclassWindow(GetDlgItem(ID_STATIC_MARKNAME));
	m_staSign.SetTransparent(TRUE, hDlgBgDC);
	m_staSign.SubclassWindow(GetDlgItem(ID_STATIC_SIGN));
	m_staGender.SetTransparent(TRUE, hDlgBgDC);
	m_staGender.SubclassWindow(GetDlgItem(ID_STATIC_GENDER));
	m_staShengXiao.SetTransparent(TRUE, hDlgBgDC);
	m_staShengXiao.SubclassWindow(GetDlgItem(ID_STATIC_SHENGXIAO));
	m_staConstel.SetTransparent(TRUE, hDlgBgDC);
	m_staConstel.SubclassWindow(GetDlgItem(ID_STATIC_CONSTEL));
	m_staBlood.SetTransparent(TRUE, hDlgBgDC);
	m_staBlood.SubclassWindow(GetDlgItem(ID_STATIC_BLOOD));
	m_staBirthday.SetTransparent(TRUE, hDlgBgDC);
	m_staBirthday.SubclassWindow(GetDlgItem(ID_STATIC_BIRTHDAY));
	m_staProvince.SetTransparent(TRUE, hDlgBgDC);
	m_staProvince.SubclassWindow(GetDlgItem(ID_STATIC_PROVINCE));
	m_staPhone.SetTransparent(TRUE, hDlgBgDC);
	m_staPhone.SubclassWindow(GetDlgItem(ID_STATIC_PHONE));
	m_staEmail.SetTransparent(TRUE, hDlgBgDC);
	m_staEmail.SubclassWindow(GetDlgItem(ID_STATIC_EMAIL));
	m_staCollege.SetTransparent(TRUE, hDlgBgDC);
	m_staCollege.SubclassWindow(GetDlgItem(ID_STATIC_COLLEGE));
	m_staCountry.SetTransparent(TRUE, hDlgBgDC);
	m_staCountry.SubclassWindow(GetDlgItem(ID_STATIC_COUNTRY));
	m_staCity.SetTransparent(TRUE, hDlgBgDC);
	m_staCity.SubclassWindow(GetDlgItem(ID_STATIC_CITY));
	m_staMobile.SetTransparent(TRUE, hDlgBgDC);
	m_staMobile.SubclassWindow(GetDlgItem(ID_STATIC_MOBILE));
	m_staOccupation.SetTransparent(TRUE, hDlgBgDC);
	m_staOccupation.SubclassWindow(GetDlgItem(ID_STATIC_OCCUPATION));
	m_staHomepage.SetTransparent(TRUE, hDlgBgDC);
	m_staHomepage.SubclassWindow(GetDlgItem(ID_STATIC_HOMEPAGE));
	m_staPersonal.SetTransparent(TRUE, hDlgBgDC);
	m_staPersonal.SubclassWindow(GetDlgItem(ID_STATIC_PERSONAL));

	m_edtNumber.SetTransparent(TRUE, hDlgBgDC);
	m_edtNumber.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtNumber.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtNumber.SubclassWindow(GetDlgItem(ID_EDIT_NUMBER));
	m_edtNickName.SetTransparent(TRUE, hDlgBgDC);
	m_edtNickName.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtNickName.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtNickName.SubclassWindow(GetDlgItem(ID_EDIT_NICKNAME));
	m_edtMarkName.SetTransparent(TRUE, hDlgBgDC);
	m_edtMarkName.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtMarkName.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtMarkName.SubclassWindow(GetDlgItem(ID_EDIT_MARKNAME));
	m_edtSign.SetTransparent(TRUE, hDlgBgDC);
	m_edtSign.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtSign.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtSign.SetMultiLine(TRUE);
	m_edtSign.SubclassWindow(GetDlgItem(ID_EDIT_SIGN));
	m_edtGender.SetTransparent(TRUE, hDlgBgDC);
	m_edtGender.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtGender.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtGender.SubclassWindow(GetDlgItem(ID_EDIT_GENDER));
	m_edtShengXiao.SetTransparent(TRUE, hDlgBgDC);
	m_edtShengXiao.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtShengXiao.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtShengXiao.SubclassWindow(GetDlgItem(ID_EDIT_SHENGXIAO));
	m_edtConstel.SetTransparent(TRUE, hDlgBgDC);
	m_edtConstel.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtConstel.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtConstel.SubclassWindow(GetDlgItem(ID_EDIT_CONSTEL));
	m_edtBlood.SetTransparent(TRUE, hDlgBgDC);
	m_edtBlood.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtBlood.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtBlood.SubclassWindow(GetDlgItem(ID_EDIT_BLOOD));
	m_edtBirthday.SetTransparent(TRUE, hDlgBgDC);
	m_edtBirthday.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtBirthday.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtBirthday.SubclassWindow(GetDlgItem(ID_EDIT_BIRTHDAY));
	m_edtProvince.SetTransparent(TRUE, hDlgBgDC);
	m_edtProvince.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtProvince.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtProvince.SubclassWindow(GetDlgItem(ID_EDIT_PROVINCE));
	m_edtPhone.SetTransparent(TRUE, hDlgBgDC);
	m_edtPhone.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtPhone.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtPhone.SubclassWindow(GetDlgItem(ID_EDIT_PHONE));
	m_edtEmail.SetTransparent(TRUE, hDlgBgDC);
	m_edtEmail.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtEmail.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtEmail.SubclassWindow(GetDlgItem(ID_EDIT_EMAIL));
	m_edtCollege.SetTransparent(TRUE, hDlgBgDC);
	m_edtCollege.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtCollege.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtCollege.SubclassWindow(GetDlgItem(ID_EDIT_COLLEGE));
	m_edtCountry.SetTransparent(TRUE, hDlgBgDC);
	m_edtCountry.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtCountry.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtCountry.SubclassWindow(GetDlgItem(ID_EDIT_COUNTRY));
	m_edtCity.SetTransparent(TRUE, hDlgBgDC);
	m_edtCity.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtCity.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtCity.SubclassWindow(GetDlgItem(ID_EDIT_CITY));
	m_edtMobile.SetTransparent(TRUE, hDlgBgDC);
	m_edtMobile.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtMobile.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtMobile.SubclassWindow(GetDlgItem(ID_EDIT_MOBILE));
	m_edtOccupation.SetTransparent(TRUE, hDlgBgDC);
	m_edtOccupation.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtOccupation.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtOccupation.SubclassWindow(GetDlgItem(ID_EDIT_OCCUPATION));
	m_edtHomepage.SetTransparent(TRUE, hDlgBgDC);
	m_edtHomepage.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtHomepage.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtHomepage.SubclassWindow(GetDlgItem(ID_EDIT_HOMEPAGE));
	m_edtPersonal.SetTransparent(TRUE, hDlgBgDC);
	m_edtPersonal.SetBgNormalPic(_T("frameBorderEffect_normalDraw.png"), CRect(2,2,2,2));
	m_edtPersonal.SetBgHotPic(_T("frameBorderEffect_mouseDownDraw.png"), CRect(2,2,2,2));
	m_edtPersonal.SetMultiLine(TRUE);
	m_edtPersonal.SubclassWindow(GetDlgItem(ID_EDIT_PERSONAL));

	m_btnUpdate.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnUpdate.SetTransparent(TRUE, hDlgBgDC);
	m_btnUpdate.SetBgPic(_T("Button\\btn_normal.png"), _T("Button\\btn_highlight.png"),
		_T("Button\\btn_down.png"), _T("Button\\btn_focus.png"));
	m_btnUpdate.SubclassWindow(GetDlgItem(ID_BTN_UPDATE));

	m_btnClose.SetButtonType(SKIN_PUSH_BUTTON);
	m_btnClose.SetTransparent(TRUE, hDlgBgDC);
	m_btnClose.SetBgPic(_T("Button\\btn_normal.png"), _T("Button\\btn_highlight.png"),
		_T("Button\\btn_down.png"), _T("Button\\btn_focus.png"));
	m_btnClose.SubclassWindow(GetDlgItem(ID_BTN_CLOSE));

	return TRUE;
}

// 反初始化
void CBuddyInfoDlg::UnInit()
{
	if (m_staNumber.IsWindow())
		m_staNumber.DestroyWindow();
	if (m_staNickName.IsWindow())
		m_staNickName.DestroyWindow();
	if (m_staMarkName.IsWindow())
		m_staMarkName.DestroyWindow();
	if (m_staSign.IsWindow())
		m_staSign.DestroyWindow();
	if (m_staGender.IsWindow())
		m_staGender.DestroyWindow();
	if (m_staShengXiao.IsWindow())
		m_staShengXiao.DestroyWindow();
	if (m_staConstel.IsWindow())
		m_staConstel.DestroyWindow();
	if (m_staBlood.IsWindow())
		m_staBlood.DestroyWindow();
	if (m_staBirthday.IsWindow())
		m_staBirthday.DestroyWindow();
	if (m_staProvince.IsWindow())
		m_staProvince.DestroyWindow();
	if (m_staPhone.IsWindow())
		m_staPhone.DestroyWindow();
	if (m_staEmail.IsWindow())
		m_staEmail.DestroyWindow();
	if (m_staCollege.IsWindow())
		m_staCollege.DestroyWindow();
	if (m_staCountry.IsWindow())
		m_staCountry.DestroyWindow();
	if (m_staCity.IsWindow())
		m_staCity.DestroyWindow();
	if (m_staMobile.IsWindow())
		m_staMobile.DestroyWindow();
	if (m_staOccupation.IsWindow())
		m_staOccupation.DestroyWindow();
	if (m_staHomepage.IsWindow())
		m_staHomepage.DestroyWindow();
	if (m_staPersonal.IsWindow())
		m_staPersonal.DestroyWindow();

	if (m_edtNumber.IsWindow())
		m_edtNumber.DestroyWindow();
	if (m_edtNickName.IsWindow())
		m_edtNickName.DestroyWindow();
	if (m_edtMarkName.IsWindow())
		m_edtMarkName.DestroyWindow();
	if (m_edtSign.IsWindow())
		m_edtSign.DestroyWindow();
	if (m_edtGender.IsWindow())
		m_edtGender.DestroyWindow();
	if (m_edtShengXiao.IsWindow())
		m_edtShengXiao.DestroyWindow();
	if (m_edtConstel.IsWindow())
		m_edtConstel.DestroyWindow();
	if (m_edtBlood.IsWindow())
		m_edtBlood.DestroyWindow();
	if (m_edtBirthday.IsWindow())
		m_edtBirthday.DestroyWindow();
	if (m_edtProvince.IsWindow())
		m_edtProvince.DestroyWindow();
	if (m_edtPhone.IsWindow())
		m_edtPhone.DestroyWindow();
	if (m_edtEmail.IsWindow())
		m_edtEmail.DestroyWindow();
	if (m_edtCollege.IsWindow())
		m_edtCollege.DestroyWindow();
	if (m_edtCountry.IsWindow())
		m_edtCountry.DestroyWindow();
	if (m_edtCity.IsWindow())
		m_edtCity.DestroyWindow();
	if (m_edtMobile.IsWindow())
		m_edtMobile.DestroyWindow();
	if (m_edtOccupation.IsWindow())
		m_edtOccupation.DestroyWindow();
	if (m_edtHomepage.IsWindow())
		m_edtHomepage.DestroyWindow();
	if (m_edtPersonal.IsWindow())
		m_edtPersonal.DestroyWindow();

	if (m_btnUpdate.IsWindow())
		m_btnUpdate.DestroyWindow();
	if (m_btnClose.IsWindow())
		m_btnClose.DestroyWindow();
}