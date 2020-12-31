
#include "Stdafx.h"
#include "Resource.h"
#include "SkinListCtrl.h"
#include "SkinHelper.h"

// 排序信息
struct tagSortInfo
{
	bool bAscendSort; // 升序标志
	WORD wColumnIndex; // 列表索引
	CSkinListCtrl* pSkinListCtrl; // 列表控件
};

BEGIN_MESSAGE_MAP(CSkinHeaderCtrl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSkinListCtrl, CListCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()

// 默认属性
#define LIST_STYTE LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_ONECLICKACTIVATE

// 构造函数
CSkinHeaderCtrl::CSkinHeaderCtrl()
{
	// 设置变量
	m_uLockCount = 0L;
	m_uItemHeight = 130;
	m_crTitle = RGB(10,10,10);
}

// 析构函数
CSkinHeaderCtrl::~CSkinHeaderCtrl()
{
}

// 控件绑定
void CSkinHeaderCtrl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	// 创建字体
	CFont Font;
	Font.CreatePointFont(m_uItemHeight, TEXT("宋体"));

	// 设置字体
	SetFont(&Font);

	return;
}

// 控件消息
BOOL CSkinHeaderCtrl::OnChildNotify(UINT uMessage, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// 变量定义
	NMHEADER * pNMHearder=(NMHEADER*)lParam;

	// 拖动消息
	if ((pNMHearder->hdr.code==HDN_BEGINTRACKA)||(pNMHearder->hdr.code==HDN_BEGINTRACKW))
	{
		// 禁止拖动
		if (pNMHearder->iItem<(int)m_uLockCount)
		{
			*pLResult=TRUE;
			return TRUE;
		}
	}

	return __super::OnChildNotify(uMessage,wParam,lParam,pLResult);
}

// 设置锁定
void CSkinHeaderCtrl::SetLockCount(UINT uLockCount)
{
	// 设置变量
	m_uLockCount=uLockCount;

	return;
}

// 设置列高
void CSkinHeaderCtrl::SetItemHeight(UINT uItemHeight)
{
	// 设置变量
	m_uItemHeight = uItemHeight;

	// 设置控件
	if (m_hWnd != NULL)
	{
		// 创建字体
		CFont Font;
		Font.CreatePointFont(m_uItemHeight, TEXT("宋体"));

		// 设置字体
		SetFont(&Font);
	}

	return;
}

// 设置资源
void CSkinHeaderCtrl::SetHeaderImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pszFileName);
	if (pszFileName == NULL) return;

	// 加载图
	m_ImageHead.DestroyImage();
	m_ImageHead.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageHead.IsValid());

	return;
}

// 设置资源
void CSkinHeaderCtrl::SetHeaderImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pBuffer && dwBufferSize);
	if (pBuffer==NULL || dwBufferSize == 0) return;

	// 加载图
	m_ImageHead.DestroyImage();
	m_ImageHead.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageHead.IsValid());

	return;
}

// 设置资源
void CSkinHeaderCtrl::SetHeaderImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	m_ImageHead.DestroyImage();
	m_ImageHead.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageHead.IsValid());

	return;
}

// 重画函数
void CSkinHeaderCtrl::OnPaint() 
{
	CPaintDC dc(this);

	// 获取位置
	CRect rcRect;
	GetClientRect(&rcRect);

	// 建立缓冲
	CDC BufferDC;
	CBitmap BufferBmp;
	BufferDC.CreateCompatibleDC(&dc);
	BufferBmp.CreateCompatibleBitmap(&dc,rcRect.Width(),rcRect.Height());

	// 设置 DC
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SelectObject(&BufferBmp);
	BufferDC.SetTextColor(m_crTitle);
	BufferDC.SelectObject(&CSkinHelper::GetDefaultFont());

	// 绘画背景
	m_ImageHead.DrawImage(&BufferDC, 0, 0, rcRect.Width(), rcRect.Height(), 1, 0, 1, m_ImageHead.GetHeight());

	// 绘画子项
	CRect rcItem;
	HDITEM HDItem;
	TCHAR szBuffer[64];
	for (int i = 0; i < GetItemCount(); i++)
	{
		// 构造变量
		HDItem.mask=HDI_TEXT;
		HDItem.pszText=szBuffer;
		HDItem.cchTextMax=CountArray(szBuffer);

		// 获取信息
		GetItem(i,&HDItem);
		GetItemRect(i,&rcItem);

		// 绘画背景
		m_ImageHead.DrawImage(&BufferDC, rcItem.left, rcItem.top, 1, rcItem.Height(), 0, 0, 1, rcItem.Height());
		m_ImageHead.DrawImage(&BufferDC, rcItem.left + 1, rcItem.top, rcItem.Width() - 2, rcItem.Height(), 1, 0, 1, m_ImageHead.GetHeight());
		m_ImageHead.DrawImage(&BufferDC, rcItem.right - 1, rcItem.top, 1, rcItem.Height(), 2, 0, 1, rcItem.Height());
	
		// 绘画标题
		rcItem.DeflateRect(3,1,3,1);
		BufferDC.DrawText(szBuffer, lstrlen(szBuffer), &rcItem, DT_END_ELLIPSIS|DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}

	// 绘画界面
	dc.BitBlt(0, 0, rcRect.Width(), rcRect.Height(),&BufferDC, 0, 0, SRCCOPY);

	// 清理资源
	BufferDC.DeleteDC();
	BufferBmp.DeleteObject();
	
	return;
}

// 背景函数
BOOL CSkinHeaderCtrl::OnEraseBkgnd(CDC * pDC) 
{
	return TRUE;
}

// 构造函数
CSkinListCtrl::CSkinListCtrl()
{
	// 设置变量
	m_bAscendSort = false;
	m_crTitle = RGB(10,10,10);
	m_crListTX = RGB(10,10,10);
	m_crListBK = RGB(229,249,255);
}

// 析构函数
CSkinListCtrl::~CSkinListCtrl()
{
}

// 控件绑定
void CSkinListCtrl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	// 设置滚动
	m_SkinScrollBar.InitScroolBar(this);

	// 设置颜色
	SetBkColor(m_crListBK);
	SetTextColor(m_crListTX);
	SetTextBkColor(m_crListBK);

	// 设置属性
	SetExtendedStyle(LIST_STYTE);
	m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	return;
}

// 绘画函数
void CSkinListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// 变量定义
	CRect rcItem = lpDrawItemStruct->rcItem;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	// 获取属性
	int nItemID = lpDrawItemStruct->itemID;
	int nColumnCount = m_SkinHeaderCtrl.GetItemCount();

	// 定制颜色
	COLORREF rcTextColor = RGB(10,10,10);
	COLORREF rcBackColor = RGB(229,249,255);
	GetItemColor(lpDrawItemStruct,rcTextColor,rcBackColor);

	// 绘画区域
	CRect rcClipBox;
	pDC->GetClipBox(&rcClipBox);

	// 设置环境
	pDC->SetBkColor(rcBackColor);
	pDC->SetTextColor(rcTextColor);

	// 绘画子项
	for (int i=0;i<nColumnCount;i++)
	{
		// 获取位置
		CRect rcSubItem;
		GetSubItemRect(nItemID,i,LVIR_BOUNDS,rcSubItem);

		// 绘画判断
		if (rcSubItem.left>rcClipBox.right) break;
		if (rcSubItem.right<rcClipBox.left) continue;

		// 绘画背景
		pDC->FillSolidRect(&rcSubItem,rcBackColor);

		// 绘画数据
		DrawCustomItem(pDC,lpDrawItemStruct,rcSubItem,i);
	}

	// 绘画焦点
	if (lpDrawItemStruct->itemState&ODS_FOCUS)
	{
		pDC->DrawFocusRect(&rcItem);
	}

	return;
}

// 建立消息
int CSkinListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	// 设置滚动
	m_SkinScrollBar.InitScroolBar(this);

	// 设置颜色
	SetBkColor(m_crListBK);
	SetTextColor(m_crListTX);
	SetTextBkColor(m_crListBK);

	// 设置属性
	SetExtendedStyle(LIST_STYTE);
	m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	return 0;
}

// 获取位置
int CSkinListCtrl::GetInsertIndex(void* pItemData)
{
	return GetItemCount();
}

// 排列数据
int CSkinListCtrl::SortItemData(LPARAM lParam1, LPARAM lParam2, WORD wColumnIndex, bool bAscendSort)
{
	// 获取数据
	TCHAR szBuffer1[256]=TEXT("");
	TCHAR szBuffer2[256]=TEXT("");
	GetItemText((int)lParam1,wColumnIndex,szBuffer1,CountArray(szBuffer1));
	GetItemText((int)lParam2,wColumnIndex,szBuffer2,CountArray(szBuffer2));

	// 对比数据
	int nResult=lstrcmp(szBuffer1,szBuffer2);
	return (bAscendSort==true)?nResult:-nResult;
}

// 描述字符
void CSkinListCtrl::ConstructString(void* pItemData, WORD wColumnIndex, LPTSTR pszString, WORD wMaxCount)
{
	// 参数效验
	ASSERT(pszString!=NULL);
	if (pszString==NULL) return;

	// 设置变量
	pszString[0]=0;

	return;
}

// 获取颜色
void CSkinListCtrl::GetItemColor(LPDRAWITEMSTRUCT lpDrawItemStruct, COLORREF& crColorText, COLORREF& crColorBack)
{
	// 设置颜色
	if (lpDrawItemStruct->itemState&ODS_SELECTED)
	{
		// 选择颜色
		crColorText=RGB(10,10,10);
		crColorBack=RGB(212,208,200);
	}
	else
	{
		// 设置变量
		crColorText=RGB(10,10,10);
		crColorBack=RGB(229,249,255);
	}

	return;
}

// 绘画数据
void CSkinListCtrl::DrawCustomItem(CDC* pDC, LPDRAWITEMSTRUCT lpDrawItemStruct, CRect& rcSubItem, int nColumnIndex)
{
	// 获取文字
	TCHAR szString[256]=TEXT("");
	GetItemText(lpDrawItemStruct->itemID,nColumnIndex,szString,CountArray(szString));

	// 绘画文字
	rcSubItem.left+=5;
	pDC->DrawText(szString,lstrlen(szString),&rcSubItem,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	return;
}

// 插入数据
void CSkinListCtrl::InsertDataItem(void* pItemData)
{
	// 效验状态
	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
	
	// 变量定义
	int nItemInsert=0;
	int nColumnCount=m_SkinHeaderCtrl.GetItemCount();

	// 插入数据
	for (int i=0;i<nColumnCount;i++)
	{
		// 获取描述
		TCHAR szString[256]=TEXT("");
		ConstructString(pItemData,i,szString,CountArray(szString));

		// 插入列表
		if (i==0)
		{
			nItemInsert=InsertItem(LVIF_TEXT|LVIF_PARAM,GetInsertIndex(pItemData),szString,0,0,0,(LPARAM)pItemData);
		}
		else
		{
			SetItem(nItemInsert,i,LVIF_TEXT,szString,0,0,0,0);
		}
	}

	return;
}

// 更新数据
void CSkinListCtrl::UpdateDataItem(void* pItemData)
{
	// 效验状态
	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
	
	// 变量定义
	LVFINDINFO FindInfo;
	ZeroMemory(&FindInfo,sizeof(FindInfo));

	// 设置变量
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=(LPARAM)pItemData;

	// 查找数据
	int nItem=FindItem(&FindInfo);
	int nColumnCount=m_SkinHeaderCtrl.GetItemCount();

	// 更新数据
	if (nItem!=-1L)
	{
		// 更新数据
		for (int i=0;i<nColumnCount;i++)
		{
			// 获取描述
			TCHAR szString[256]=TEXT("");
			ConstructString(pItemData,i,szString,CountArray(szString));

			// 设置列表
			SetItem(nItem,i,LVIF_TEXT,szString,0,0,0,0);
		}

		// 更新子项
		RedrawItems(nItem,nItem);
	}

	return;
}

// 删除数据
void CSkinListCtrl::DeleteDataItem(void* pItemData)
{
	// 效验状态
	ASSERT((pItemData!=NULL)&&(m_hWnd!=NULL));
	if ((pItemData==NULL)||(m_hWnd==NULL)) return;
	
	// 变量定义
	LVFINDINFO FindInfo;
	ZeroMemory(&FindInfo,sizeof(FindInfo));

	// 构造变量
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=(LPARAM)pItemData;

	// 删除数据
	int nItem=FindItem(&FindInfo);
	if (nItem!=-1L) DeleteItem(nItem);

	return;
}

// 绘画背景
BOOL CSkinListCtrl::OnEraseBkgnd(CDC * pDC)
{
	// 获取窗口
	CWnd* pHeader=GetHeaderCtrl();

	// 窗口判断
	if (pHeader->GetSafeHwnd()!=NULL)
	{
		// 获取位置
		CRect rcClient;
		GetClientRect(&rcClient);

		// 获取位置
		CRect rcHeader;
		pHeader->GetWindowRect(&rcHeader);

		// 绘画背景
		rcClient.top=rcHeader.Height();
		pDC->FillSolidRect(&rcClient,GetBkColor());

		return TRUE;
	}

	return __super::OnEraseBkgnd(pDC);
}

// 排列函数
int CALLBACK CSkinListCtrl::SortFunction(LPARAM lParam1, LPARAM lParam2, LPARAM lParamList)
{
	// 变量定义
    tagSortInfo* pSortInfo=(tagSortInfo*)lParamList;
	CSkinListCtrl* pSkinListCtrl=pSortInfo->pSkinListCtrl;

	// 数据排序
	return pSkinListCtrl->SortItemData(lParam1,lParam2,pSortInfo->wColumnIndex,pSortInfo->bAscendSort);
}

// 点击消息
void CSkinListCtrl::OnColumnclick(NMHDR * pNMHDR, LRESULT * pResult)
{
	// 变量定义
	NM_LISTVIEW * pNMListView=(NM_LISTVIEW *)pNMHDR;

	// 变量定义
	tagSortInfo SortInfo;
	ZeroMemory(&SortInfo,sizeof(SortInfo));

	// 设置变量
	SortInfo.pSkinListCtrl=this;
	SortInfo.bAscendSort=m_bAscendSort;
	SortInfo.wColumnIndex=pNMListView->iSubItem;

	// 设置变量
	m_bAscendSort=!m_bAscendSort;

	// 排列列表
	SortItems(SortFunction,(LPARAM)&SortInfo);

	return;
}

void CSkinListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	/*LVHITTESTINFO lht;
	lht.pt = point;
	lht.flags = LVHT_ABOVE;

	int nItem = SubItemHitTest(&lht);
	if(m_nMoveItem != nItem)
	{
		CRect rc;
		if (m_nMoveItem != -1)
			GetItemRect(m_nMoveItem, &rc,LVIR_BOUNDS);
		m_nMoveItem = lht.iItem;
		InvalidateRect(&rc, FALSE);
		if (m_nMoveItem != -1)
			GetItemRect(m_nMoveItem, &rc,LVIR_BOUNDS);
		InvalidateRect(&rc, FALSE);
	}*/

	return __super::OnMouseMove(nFlags, point);
}

// 测量子项
void CSkinListCtrl::MeasureItem(LPMEASUREITEMSTRUCT   lpMeasureItemStruct) 
{ 
	lpMeasureItemStruct->itemHeight  = 20; // 要设置的高度
} 