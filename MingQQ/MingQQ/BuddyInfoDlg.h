#pragma once

#include "resource.h"
#include "CustomMsgDef.h"
#include "Utils.h"
#include "SkinLib/SkinLib.h"
#include "QQClient/QQClient.h"

class CBuddyInfoDlg : public CDialogImpl<CBuddyInfoDlg>
{
public:
	CBuddyInfoDlg(void);
	~CBuddyInfoDlg(void);

	enum { IDD = IDD_BUDDYINFODLG };

	BEGIN_MSG_MAP_EX(CBuddyInfoDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_DESTROY(OnDestroy)
		COMMAND_HANDLER_EX(ID_BTN_UPDATE, BN_CLICKED, OnBtn_Update)
		COMMAND_HANDLER_EX(ID_BTN_CLOSE, BN_CLICKED, OnBtn_Close)
	END_MSG_MAP()

public:
	void OnUpdateBuddyInfo();
	void OnUpdateBuddyNumber();
	void OnUpdateBuddySign();

private:
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	void OnClose();
	void OnDestroy();
	void OnBtn_Update(UINT uNotifyCode, int nID, CWindow wndCtl);	// “更新”按钮
	void OnBtn_Close(UINT uNotifyCode, int nID, CWindow wndCtl);	// “关闭”按钮

	CBuddyInfo * GetBuddyInfoPtr();
	void UpdateCtrls();

	BOOL Init();		// 初始化
	void UnInit();		// 反初始化

public:
	CQQClient * m_lpQQClient;
	HWND m_hMainDlg;
	UINT m_nQQUin;
	BOOL m_bIsGMember;
	UINT m_nGroupCode;

private:
	CSkinDialog m_SkinDlg;

	CSkinStatic m_staNumber, m_staNickName, m_staMarkName;
	CSkinStatic m_staSign;
	CSkinStatic m_staGender, m_staShengXiao, m_staConstel, m_staBlood;
	CSkinStatic m_staBirthday, m_staProvince, m_staPhone, m_staEmail, m_staCollege;
	CSkinStatic m_staCountry, m_staCity, m_staMobile, m_staOccupation, m_staHomepage;
	CSkinStatic m_staPersonal;

	CSkinEdit m_edtNumber, m_edtNickName, m_edtMarkName;
	CSkinEdit m_edtSign;
	CSkinEdit m_edtGender, m_edtShengXiao, m_edtConstel, m_edtBlood;
	CSkinEdit m_edtBirthday, m_edtProvince, m_edtPhone, m_edtEmail, m_edtCollege;
	CSkinEdit m_edtCountry, m_edtCity, m_edtMobile, m_edtOccupation, m_edtHomepage;
	CSkinEdit m_edtPersonal;

	CSkinButton m_btnUpdate, m_btnClose;

	HICON m_hDlgIcon, m_hDlgSmallIcon;
};
