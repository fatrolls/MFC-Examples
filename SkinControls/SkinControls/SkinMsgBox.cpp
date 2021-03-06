
#include "StdAfx.h"
#include "Resource.h"
#include "SkinMsgBox.h"
#include "SkinHelper.h"

// 时间标识
#define IDI_MESSAGE					100									// 消息标识

// 窗口位置
#define SMB_WINDOW_WIDTH			230									// 最小宽度

// 图标偏移
#define SMB_ICON_LEFT				20									// 图标偏移
#define SMB_ICON_WIDTH				32									// 图标宽度
#define SMB_ICON_HEIGHT				32									// 图标高度

// 字符偏移
#define SMB_STRING_TOP				25									// 字符偏移
#define SMB_STRING_LEFT				20									// 字符偏移
#define SMB_STRING_RIGHT			40									// 字符偏移
#define SMB_STRING_BOTTOM			25									// 字符偏移
#define SMB_STRING_WIDTH			600									// 最大宽度
#define SMB_STRING_HEIGHT			600									// 最大宽度

// 按钮偏移
#define SMB_BUTTON_LEFT				12									// 按钮偏移
#define SMB_BUTTON_RIGHT			12									// 按钮偏移
#define SMB_BUTTON_SPACE			20									// 按钮间隔
#define SMB_BUTTON_WIDTH			70									// 按钮偏移
#define SMB_BUTTON_HEIGHT			23									// 按钮偏移

// 按钮区域
#define SMB_BUTTON_AREA_HEIGHT		30									// 按钮区域

// 窗口非客户区
#define WND_TOP_HEIGHT				27									// 窗口顶部
#define WND_BOTOOM_HEIGHT			3									// 窗口底部
#define WND_LEFT_WIDTH				3									// 窗口左边
#define WND_RIGHT_WIDTH				3									// 窗口右边

BEGIN_MESSAGE_MAP(CSkinMsgBox, CSkinDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// 构造函数
CSkinMsgBox::CSkinMsgBox(CWnd* pParentWnd) : CSkinDialog(IDD_SKINMSGBOX, pParentWnd)
{
	// 设置变量
	m_uType = MB_OK;

	// 辅助变量
	m_nElapse = 0;
	m_nBtCount = 0;
	m_uDefBtnIndex = 0;
}

// 析构函数
CSkinMsgBox::~CSkinMsgBox()
{
}

// 初始化消息
BOOL CSkinMsgBox::OnInitDialog()
{
	__super::OnInitDialog();

	// 设置标题
	SetWindowText(m_strCaption);

	// 设置资源
	AfxSetResourceHandle(GetModuleHandle(SKIN_CONTROLS_DLL_NAME));

	// 设置图标
	HICON hIcon = LoadIcon(GetModuleHandle(SKIN_CONTROLS_DLL_NAME), MAKEINTRESOURCE(IDI_MAINFRAME));
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	// 按钮区域
	CreateBoxButton();
	int nButtonAreaWidth = m_nBtCount * SMB_BUTTON_WIDTH + (m_nBtCount + 1) * SMB_BUTTON_SPACE + SMB_BUTTON_LEFT + SMB_BUTTON_RIGHT;

	// 字符空间
	CClientDC ClientDC(this);
	CRect rcString(0, 0, SMB_STRING_WIDTH, SMB_STRING_HEIGHT);
	ClientDC.SelectObject(&CSkinHelper::GetDefaultFont());
	ClientDC.DrawText(m_strString, rcString, DT_CALCRECT | DT_EXPANDTABS | DT_NOCLIP | DT_WORD_ELLIPSIS);

	// 字符区域
	int nStringAreaHeight = rcString.Height() + SMB_STRING_TOP + SMB_STRING_BOTTOM;
	int nStringAreaWidth = rcString.Width() + SMB_ICON_LEFT + SMB_ICON_WIDTH + SMB_STRING_LEFT + SMB_STRING_RIGHT;

	// 窗口区域
	int nWindowAreaHeight = nStringAreaHeight + SMB_BUTTON_AREA_HEIGHT;
	int nWindowAreaWidth = max(SMB_WINDOW_WIDTH, max(nStringAreaWidth, nButtonAreaWidth));

	// 输出位置
	if (nWindowAreaWidth > nStringAreaWidth)
	{
		m_rcString.top = SMB_STRING_TOP;
		m_rcString.left= SMB_ICON_LEFT + SMB_ICON_WIDTH + SMB_STRING_LEFT + (nWindowAreaWidth - nStringAreaWidth) / 2;
		m_rcString.right = m_rcString.left + rcString.Width();
		m_rcString.bottom = m_rcString.top + rcString.Height();
	}
	else
	{
		m_rcString.top = SMB_STRING_TOP;
		m_rcString.left = SMB_ICON_LEFT + SMB_ICON_WIDTH + SMB_STRING_LEFT;
		m_rcString.right = m_rcString.left + rcString.Width();
		m_rcString.bottom = m_rcString.top + rcString.Height();
	}

	// 调整窗口
	int nWindowWidth = nWindowAreaWidth + WND_LEFT_WIDTH + WND_RIGHT_WIDTH;
	int nWindowHeight = nWindowAreaHeight + WND_TOP_HEIGHT + WND_BOTOOM_HEIGHT;
	SetWindowPos(NULL, 0, 0, nWindowWidth, nWindowHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOCOPYBITS);

	// 计算位置
	CRect rcClient;
	GetClientRect(rcClient);
	int nYButton = rcClient.bottom - SMB_BUTTON_AREA_HEIGHT + (SMB_BUTTON_AREA_HEIGHT - SMB_BUTTON_HEIGHT) / 2 + 2;
	int nXButton = (rcClient.Width() - m_nBtCount * SMB_BUTTON_WIDTH - (m_nBtCount + 1) * SMB_BUTTON_SPACE) / 2 + SMB_BUTTON_SPACE;

	// 调整按钮
	for (UINT i = 0; i < m_nBtCount; i++)
	{
		m_btnButton[i].SetWindowPos(NULL, nXButton, nYButton, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
		nXButton += SMB_BUTTON_SPACE + SMB_BUTTON_WIDTH;
	}

	// 默认按钮
	m_uDefBtnIndex = (m_uType & MB_DEFMASK) >> 8;
	if (m_uDefBtnIndex >= m_nBtCount) m_uDefBtnIndex = 0;
	m_btnButton[m_uDefBtnIndex].SetFocus();
	m_btnButton[m_uDefBtnIndex].SetButtonStyle(m_btnButton[m_uDefBtnIndex].GetButtonStyle() | BS_DEFPUSHBUTTON);
	m_btnButton[m_uDefBtnIndex].GetWindowText(m_strDefBtn);
	m_strDefBtn = m_strDefBtn.Left(m_strDefBtn.Find(TEXT("(")));

	// 居中窗口
	SetActiveWindow();
	SetForegroundWindow();
	CenterWindow(GetParent());

	// 设置时间
	if (m_nElapse != 0) SetTimer(IDI_MESSAGE, 1000, NULL);

	return FALSE;
}

// 命令消息
BOOL CSkinMsgBox::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// 按钮标识
	UINT uButtonID = LOWORD(wParam);

	// 存在判断
	for (UINT i = 0; i < m_nBtCount; i++)
	{
		// 获取标识
		UINT uExistID = GetWindowLong(m_btnButton[i], GWL_ID);

		// 标识处理
		if (uButtonID == uExistID)
		{
			EndDialog(uButtonID);
			return TRUE;
		}
	}

	// 默认处理
	if (uButtonID == IDOK)
	{
		EndDialog(GetWindowLong(m_btnButton[m_uDefBtnIndex], GWL_ID));
		return TRUE;
	}

	// 取消处理
	if (uButtonID == IDCANCEL)
	{
		EndDialog(GetWindowLong(m_btnButton[m_nBtCount - 1], GWL_ID));
		return TRUE;
	}

	// 默认处理
	EndDialog(uButtonID);

	return TRUE;
}

// 显示消息
int CSkinMsgBox::ShowMsgBox(LPCTSTR pszString, UINT uType, UINT nElapse)
{
	return ShowMsgBox(TEXT("系统提示"), pszString, uType, nElapse);
}

// 显示消息
int CSkinMsgBox::ShowMsgBox(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType, UINT nElapse)
{
	// 设置变量
	m_uType = uType;
	m_nElapse = nElapse;
	m_strString = pszString;
	m_strCaption = pszCaption;

	// 设置资源
	AfxSetResourceHandle(GetModuleHandle(SKIN_CONTROLS_DLL_NAME));

	// 显示窗口
	int nResult = (int)DoModal();

	return nResult;
}

// 激活按钮
void CSkinMsgBox::CreateBoxButton()
{
	// 变量定义
	UINT uButtonID[3] = {0,0,0};
	LPCTSTR pszString[3] = {NULL, NULL, NULL};

	// 设置按钮
	switch (m_uType & MB_TYPEMASK)
	{
	case MB_OKCANCEL:
		{
			m_nBtCount = 2;
			uButtonID[0] = IDOK;
			uButtonID[1] = IDCANCEL;
			pszString[0] = TEXT("确定(&O)");
			pszString[1] = TEXT("取消(&C)");
			break;
		}
	case MB_YESNO:
		{
			m_nBtCount = 2;
			uButtonID[0] = IDYES;
			uButtonID[1] = IDNO;
			pszString[0] = TEXT("是(&Y)");
			pszString[1] = TEXT("否(&N)");
			break;
		}
	case MB_YESNOCANCEL:
		{
			m_nBtCount = 3;
			uButtonID[0] = IDYES;
			uButtonID[1] = IDNO;
			uButtonID[2] = IDCANCEL;
			pszString[0] = TEXT("是(&Y)");
			pszString[1] = TEXT("否(&N)");
			pszString[2] = TEXT("取消(&C)");
			break;
		}
	case MB_RETRYCANCEL:
		{
			m_nBtCount = 2;
			uButtonID[0] = IDRETRY;
			uButtonID[1] = IDCANCEL;
			pszString[0] = TEXT("重试(&R)");
			pszString[1] = TEXT("取消(&C)");
			break;
		}
	case MB_ABORTRETRYIGNORE:
		{
			m_nBtCount = 3;
			uButtonID[0] = IDABORT;
			uButtonID[1] = IDRETRY;
			uButtonID[2] = IDIGNORE;
			pszString[0] = TEXT("中止(&A)");
			pszString[1] = TEXT("重试(&R)");
			pszString[2] = TEXT("忽略(&I)");
			break;
		}
	default:
		{
			m_nBtCount=1;
			uButtonID[0]=IDOK;
			pszString[0]=TEXT("确定(&O)");
			break;
		}
	}

	// 显示按钮
	CRect rcButton(0, 0, SMB_BUTTON_WIDTH, SMB_BUTTON_HEIGHT);
	for (UINT i = 0; i< m_nBtCount; i++) m_btnButton[i].Create(pszString[i], WS_CHILD, rcButton, this, uButtonID[i]);

	return;
}

// 绘画消息
void CSkinMsgBox::OnPaint()
{
	CPaintDC dc(this);

	// 获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	// 加载图标
	HICON hIcon = NULL;
	UINT uIconType = (m_uType & MB_ICONMASK);
	if (uIconType == MB_ICONHAND) hIcon = LoadIcon(NULL,IDI_HAND);
	else if (uIconType == MB_ICONQUESTION) hIcon = LoadIcon(NULL,IDI_QUESTION);
	else if (uIconType == MB_ICONEXCLAMATION) hIcon = LoadIcon(NULL,IDI_EXCLAMATION);
	else hIcon = LoadIcon(NULL, IDI_ASTERISK);

	// 绘画图标
	int nYPos=(m_rcString.bottom + m_rcString.top) / 2 - SMB_ICON_HEIGHT / 2;
	DrawIconEx(dc, SMB_ICON_LEFT, nYPos, hIcon, SMB_ICON_WIDTH, SMB_ICON_HEIGHT, 0, NULL, DI_NORMAL);

	// 绘画字体
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(10, 10, 10));
	dc.SelectObject(&CSkinHelper::GetDefaultFont());
	dc.DrawText(m_strString, &m_rcString, DT_EXPANDTABS | DT_NOCLIP | DT_WORD_ELLIPSIS);

	return;
}

// 时间消息
void CSkinMsgBox::OnTimer(UINT_PTR nIDEvent)
{
	// 倒数时间
	if (nIDEvent == IDI_MESSAGE)
	{
		// 删除判断
		if (m_nElapse == 0)
		{
			PostMessage(WM_CLOSE, 0, 0);
			return;
		}

		// 设置界面
		CString strBtn;
		strBtn.Format(TEXT("%s(%ld)"), m_strDefBtn, m_nElapse--);
		m_btnButton[m_uDefBtnIndex].SetWindowText(strBtn);

		return;
	}

	__super::OnTimer(nIDEvent);
}

// 显示消息
extern "C" SKIN_CONTROLS_EXPORT int ShowMsgBox(LPCTSTR pszString, UINT uType, UINT nElapse)
{
	CSkinMsgBox SkinMsgBox;
	return SkinMsgBox.ShowMsgBox(pszString, uType, nElapse);
}

// 显示消息
extern "C" SKIN_CONTROLS_EXPORT int ShowMsgBoxEx(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType, UINT nElapse)
{
	CSkinMsgBox SkinMsgBox;
	return SkinMsgBox.ShowMsgBox(pszCaption, pszString, uType, nElapse);
}
