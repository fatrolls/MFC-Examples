
#include "StdAfx.h"
#include "SkinLayeredWnd.h"
#include "DrawHelpers.h"

// 枚举结构
struct tagEnumChildInfo
{
	CWnd* pWndControl; // 控制窗口
	CWnd* pWndLayered; // 分层窗口
	CRgn* pRegionResult; // 结果区域
};

BEGIN_MESSAGE_MAP(CSkinLayeredWnd, CWnd)
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// 构造函数
CSkinLayeredWnd::CSkinLayeredWnd()
{
	// 设置变量
	m_pWndControl = NULL;
}

// 析构函数
CSkinLayeredWnd::~CSkinLayeredWnd()
{
}

// 创建窗口
VOID CSkinLayeredWnd::CreateLayered(CWnd* pWndControl, CRect& rcWindow)
{
	// 效验参数
	ASSERT((pWndControl != NULL) && (pWndControl->m_hWnd != NULL));
	if ((pWndControl == NULL) || (pWndControl->m_hWnd == NULL)) return;

	// 设置变量
	m_pWndControl = pWndControl;

	// 创建窗口
	CreateEx(WS_EX_LAYERED, TEXT("STATIC"), TEXT(""), 0, rcWindow, pWndControl, 0L);

	return;
}

// 设置区域
VOID CSkinLayeredWnd::InitLayeredArea(CDC* pDCImage, BYTE cbAlpha, CRect& rcUnLayered, CPoint& PointRound, bool bUnLayeredChild)
{
	// 效验参数
	ASSERT((pDCImage != NULL) && (pDCImage->m_hDC != NULL));
	if ((pDCImage == NULL) || (pDCImage->m_hDC == NULL)) return;

	// 变量定义
	BITMAP Bitmap;
	ZeroMemory(&Bitmap, sizeof(Bitmap));

	// 获取图像
	CBitmap* pBitmap = pDCImage->GetCurrentBitmap();
	if (pBitmap != NULL) pBitmap->GetBitmap(&Bitmap);

	// 获取大小
	CSize SizeImage;
	SizeImage.SetSize(Bitmap.bmWidth, Bitmap.bmHeight);

	// 效验大小
	ASSERT((SizeImage.cx > 0) && (SizeImage.cy > 0));
	if ((SizeImage.cx == 0) || (SizeImage.cy == 0)) return;

	// 变量定义
	BLENDFUNCTION BlendFunction;
	ZeroMemory(&BlendFunction, sizeof(BlendFunction));

	// 设置参数
	BlendFunction.BlendOp = 0;
	BlendFunction.BlendFlags = 0;
	BlendFunction.AlphaFormat = AC_SRC_ALPHA;
	BlendFunction.SourceConstantAlpha = cbAlpha;

	// 设置分层
	CPoint ImagePoint(0, 0);
	CClientDC ClientDC(this);
	UpdateLayeredWindow(&ClientDC, NULL, &SizeImage, pDCImage, &ImagePoint, 0L, &BlendFunction, ULW_ALPHA);

	// 创建区域
	CRgn RegionResult;
	RegionResult.CreateRectRgn(0, 0, SizeImage.cx, SizeImage.cy);

	// 窗口排除
	if (bUnLayeredChild == true)
	{
		// 变量定义
		tagEnumChildInfo EnumChildInfo;
		ZeroMemory(&EnumChildInfo, sizeof(EnumChildInfo));

		// 设置变量
		EnumChildInfo.pWndLayered = this;
		EnumChildInfo.pWndControl = m_pWndControl;
		EnumChildInfo.pRegionResult = &RegionResult;

		// 枚举窗口
		ASSERT(m_pWndControl->GetSafeHwnd() != NULL);
		EnumChildWindows(m_pWndControl->m_hWnd, EnumChildProc, (LPARAM)&EnumChildInfo);
	}

	// 区域排除
	if (rcUnLayered.IsRectEmpty() == FALSE)
	{
		// 创建区域
		CRgn RegionUnLayered;
		RegionUnLayered.CreateRoundRectRgn(rcUnLayered.left, rcUnLayered.top, rcUnLayered.right + 1, rcUnLayered.bottom + 1, PointRound.x, PointRound.y);

		// 合并区域
		RegionResult.CombineRgn(&RegionResult, &RegionUnLayered, RGN_DIFF);
	}

	// 设置区域
	SetWindowRgn(RegionResult, TRUE);

	return;
}

//设置区域
VOID CSkinLayeredWnd::InitLayeredArea(CSkinImage& Image, BYTE cbAlpha, CRect& rcUnLayered, CPoint& PointRound, bool bUnLayeredChild)
{
	// 创建缓冲
	CSkinImage BufferImage;
	BufferImage.Create(Image.GetWidth(), Image.GetHeight());
	CCompatibleDC BufferDC(NULL, (HBITMAP)BufferImage);

	// 绘画界面
	Image.DrawImage(&BufferDC, 0, 0);

	//创建分层
	InitLayeredArea(&BufferDC, cbAlpha, rcUnLayered, PointRound, bUnLayeredChild);

	return;
}

// 关闭消息
VOID CSkinLayeredWnd::OnClose()
{
	// 投递消息
	if (m_pWndControl != NULL)
	{
		m_pWndControl->PostMessage(WM_CLOSE);
	}

	return;
}

// 焦点消息
VOID CSkinLayeredWnd::OnSetFocus(CWnd* pOldWnd)
{
	//设置焦点
	if (m_pWndControl != NULL)
	{
		m_pWndControl->SetFocus();
	}
}

// 枚举函数
BOOL CALLBACK CSkinLayeredWnd::EnumChildProc(HWND hWndChild, LPARAM lParam)
{
	// 获取位置
	CRect rcWindow;
	::GetWindowRect(hWndChild, &rcWindow);

	// 创建区域
	if ((rcWindow.Width() > 0) && (rcWindow.Height() > 0))
	{
		// 变量定义
		ASSERT(lParam != 0L);
		tagEnumChildInfo* pEnumChildInfo = (tagEnumChildInfo*)lParam;

		// 窗口判断
		HWND hWndParent = ::GetParent(hWndChild);
		if (hWndParent != pEnumChildInfo->pWndControl->GetSafeHwnd())
		{
			return TRUE;
		}

		// 转换位置
		ASSERT(pEnumChildInfo->pWndControl != NULL);
		pEnumChildInfo->pWndControl->ScreenToClient(&rcWindow);

		// 创建区域
		CRgn RgnChild;
		RgnChild.CreateRectRgn(rcWindow.left, rcWindow.top, rcWindow.right, rcWindow.bottom);

		// 合并区域
		ASSERT(pEnumChildInfo->pRegionResult != NULL);
		pEnumChildInfo->pRegionResult->CombineRgn(pEnumChildInfo->pRegionResult, &RgnChild, RGN_DIFF);
	}

	return TRUE;
}