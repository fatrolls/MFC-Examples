
#include "stdafx.h"
#include "SkinTreeCtrl.h"
#include "SkinHelper.h"

#define ITEM_HEIGHT 26 // 子项高度

IMPLEMENT_DYNAMIC(CSkinTreeCtrl, CTreeCtrl)

BEGIN_MESSAGE_MAP(CSkinTreeCtrl, CTreeCtrl)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CLICK, OnNMLClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRClick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTvnSelchanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnTvnItemexpanding)
END_MESSAGE_MAP()

CSkinTreeCtrl::CSkinTreeCtrl()
{
	// 设置变量
	m_nXScroll=0;
	m_nYScroll=0;

	// 辅助变量
	m_hItemMouseHover=NULL;
	m_hTreeClickExpand=NULL;

	m_crBack = RGB(255,255,255);
	m_crLine = RGB(223,223,223);
	m_crSelected = RGB(253,231,161);
	m_crHover = RGB(163, 219, 255);
}

CSkinTreeCtrl::~CSkinTreeCtrl()
{
}

// 创建消息
int CSkinTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1) return -1;

	// 设置属性
	SetItemHeight(ITEM_HEIGHT);
	ModifyStyle(0,TVS_HASBUTTONS|TVS_HASLINES|TVS_SHOWSELALWAYS|TVS_TRACKSELECT|TVS_FULLROWSELECT|TVS_HASLINES);

	// 设置滚动
	m_SkinScrollBar.InitScroolBar(this);

	return 0;
}

// 控件子类化
void CSkinTreeCtrl::PreSubclassWindow() 
{
	// 设置属性
	SetItemHeight(ITEM_HEIGHT);
	ModifyStyle(0,TVS_HASBUTTONS|TVS_HASLINES|TVS_SHOWSELALWAYS|TVS_TRACKSELECT|TVS_FULLROWSELECT|TVS_HASLINES);

	// 设置滚动
	m_SkinScrollBar.InitScroolBar(this);

	CTreeCtrl::PreSubclassWindow();
}

// 窗口函数
LRESULT CSkinTreeCtrl::DefWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	// 双击消息
	switch (uMessage)
	{
	case WM_LBUTTONDOWN: // 鼠标消息
		{
			// 鼠标坐标
			CPoint MousePoint;
			MousePoint.SetPoint(LOWORD(lParam),HIWORD(lParam));

			// 设置变量
			m_hTreeClickExpand=NULL;

			// 点击测试
			HTREEITEM hTreeItem=HitTest(MousePoint);

			// 消息处理
			if ((hTreeItem!=NULL)&&(GetChildItem(hTreeItem)!=NULL))
			{
				// 选择树项
				SetFocus();
				Select(hTreeItem,TVGN_CARET);

				// 获取位置
				CRect rcTreeItem;
				GetItemRect(hTreeItem,&rcTreeItem,TRUE);

				// 消息处理
				if (rcTreeItem.PtInRect(MousePoint)==TRUE)
				{
					// 展开列表
					if (ExpandVerdict(hTreeItem)==false)
					{
						m_hTreeClickExpand=hTreeItem;
						Expand(m_hTreeClickExpand,TVE_EXPAND);
					}

					return 0;
				}
			}

			break;
		}
	case WM_LBUTTONDBLCLK: // 鼠标消息
		{
			// 鼠标坐标
			CPoint MousePoint;
			MousePoint.SetPoint(LOWORD(lParam),HIWORD(lParam));

			// 点击测试
			HTREEITEM hTreeItem=HitTest(MousePoint);

			// 消息处理
			if ((hTreeItem!=NULL)&&(GetChildItem(hTreeItem)!=NULL))
			{
				// 选择树项
				SetFocus();
				Select(hTreeItem,TVGN_CARET);

				// 位置判断
				CRect rcTreeItem;
				GetItemRect(hTreeItem,&rcTreeItem,TRUE);
				if (rcTreeItem.PtInRect(MousePoint)==FALSE) break;

				// 展开判断
				if ((m_hTreeClickExpand!=hTreeItem)&&(ExpandVerdict(hTreeItem)==true))
				{
					// 设置变量
					m_hTreeClickExpand=NULL;

					// 展开列表
					Expand(hTreeItem,TVE_COLLAPSE);
				}

				return 0;
			}

			break;
		}
	}

	return __super::DefWindowProc(uMessage,wParam,lParam);
}

// 从资源加载图片设置箭头
void CSkinTreeCtrl::SetArrowImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	// 加载位图
	m_ImageArrow.DestroyImage();
	m_ImageArrow.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageArrow.IsValid());
}

// 从文件加载图片设置箭头
void CSkinTreeCtrl::SetArrowImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pszFileName);
	if (pszFileName == NULL) return ;

	// 加载位图
	m_ImageArrow.DestroyImage();
	m_ImageArrow.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageArrow.IsValid());
}

// 从内存加载图片设置箭头
void CSkinTreeCtrl::SetArrowImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pBuffer && dwBufferSize);
	if (pBuffer == NULL || dwBufferSize == 0) return;

	// 加载图
	m_ImageArrow.DestroyImage();
	m_ImageArrow.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageArrow.IsValid());
}

// 获取选择
HTREEITEM CSkinTreeCtrl::GetCurrentSelectItem(bool bOnlyText)
{
	// 获取光标
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	// 点击判断
	HTREEITEM hTreeItem=HitTest(MousePoint);

	if (bOnlyText==true)
	{
		// 获取位置
		CRect rcTreeItem;
		GetItemRect(hTreeItem,&rcTreeItem,TRUE);

		// 选择判断
		if (rcTreeItem.PtInRect(MousePoint)==FALSE) return NULL;
	}

	return hTreeItem;
}

// 展开状态
bool CSkinTreeCtrl::ExpandVerdict(HTREEITEM hTreeItem)
{
	if (hTreeItem!=NULL)
	{
		UINT uState=GetItemState(hTreeItem,TVIS_EXPANDED);
		return ((uState&TVIS_EXPANDED)!=0);
	}

	return false;
}

// 展开列表
bool CSkinTreeCtrl::ExpandListItem(HTREEITEM hTreeItem)
{
	// 效验参数
	ASSERT(hTreeItem!=NULL);
	if (hTreeItem==NULL) return false;

	// 展开列表
	HTREEITEM hCurrentItem=hTreeItem;
	do
	{
		Expand(hCurrentItem,TVE_EXPAND);
		hCurrentItem=GetParentItem(hCurrentItem);
	} while (hCurrentItem!=NULL);

	return true;
}

// 绘画子项
void CSkinTreeCtrl::DrawTreeItem(CDC* pDC, CRect& rcClient, CRect& rcClipBox)
{
	// 首项判断
	HTREEITEM hItemCurrent=GetFirstVisibleItem();
	if (hItemCurrent==NULL) return;

	// 获取属性
	UINT uTreeStyte=GetWindowLong(m_hWnd,GWL_STYLE);

	// 绘画子项
	do
	{
		// 变量定义
		CRect rcItem;
		CRect rcRect;

		// 获取状态
		HTREEITEM hParent=GetParentItem(hItemCurrent);
		UINT uItemState=GetItemState(hItemCurrent,TVIF_STATE);

		// 获取属性
		bool bDrawChildren=(ItemHasChildren(hItemCurrent)==TRUE);
		bool bDrawSelected=(uItemState&TVIS_SELECTED)&&((this==GetFocus())||(uTreeStyte&TVS_SHOWSELALWAYS));

		// 获取区域
		if (GetItemRect(hItemCurrent,rcItem,TRUE))
		{
			// 绘画过滤
			if (rcItem.top>=rcClient.bottom) break;
			if (rcItem.top>=rcClipBox.bottom) continue;

			// 设置位置
			rcRect.left=0;
			rcRect.top=rcItem.top+1;
			rcRect.bottom=rcItem.bottom;
			rcRect.right=rcClient.Width();

			// 绘画选择
			if (bDrawSelected==true)
			{
				pDC->FillSolidRect(&rcRect, m_crSelected);
			}

			// 绘画经过
			if ((bDrawSelected==false)&&(m_hItemMouseHover==hItemCurrent))
			{
				pDC->FillSolidRect(&rcRect, m_crHover);
			}

			// 绘制箭头
			if (bDrawChildren==true)
			{
				// 计算位置
				//int nXPos=rcItem.left-m_ImageArrow.GetWidth()/2 - 25;
				INT nXPos=rcItem.left-m_ImageArrow.GetWidth()/2 - 5;
				INT nYPos=rcItem.top+1+(rcItem.Height()-m_ImageArrow.GetHeight())/2;

				// 绘画图标
				int nIndex=(uItemState&TVIS_EXPANDED)?1L:0L;
				m_ImageArrow.DrawImage(pDC,nXPos,nYPos,m_ImageArrow.GetWidth()/2,m_ImageArrow.GetHeight(),
					nIndex*m_ImageArrow.GetWidth()/2,0,m_ImageArrow.GetWidth()/2,m_ImageArrow.GetHeight(),MASK_COLOR);
			}

			// 绘制列表
			//DrawListImage(pDC,rcItem,hItemCurrent);	

			// 绘制文本
			DrawItemString(pDC,rcItem,hItemCurrent,bDrawSelected);
		}
	} while ((hItemCurrent=GetNextVisibleItem(hItemCurrent))!= NULL);

	return;
}

// 绘画背景
void CSkinTreeCtrl::DrawTreeBack(CDC* pDC, CRect& rcClient, CRect& rcClipBox)
{
	// 绘画背景
	pDC->FillSolidRect(&rcClient, m_crBack);

	// 绘制横线
	for (int nYPos=m_nYScroll/ITEM_HEIGHT*ITEM_HEIGHT;nYPos<rcClient.Height();nYPos+=ITEM_HEIGHT)
	{
		pDC->FillSolidRect(0,nYPos,rcClient.Width(),1,m_crLine);
	}

	return;
}

// 绘画图标
void CSkinTreeCtrl::DrawListImage(CDC* pDC, CRect rcRect, HTREEITEM hTreeItem)
{
	// 获取属性
	int nImage,nSelectedImage;
	GetItemImage(hTreeItem,nImage,nSelectedImage);

	//// 获取信息
	//IMAGEINFO ImageInfo;
	//m_ImageList.GetImageInfo(nImage,&ImageInfo);

	//// 绘画图标
	//int nImageWidth=ImageInfo.rcImage.right-ImageInfo.rcImage.left;
	//int nImageHeight=ImageInfo.rcImage.bottom-ImageInfo.rcImage.top;
	//m_ImageList.Draw(pDC,nImage,CPoint(rcRect.left-nImageWidth-3,rcRect.top+(rcRect.Height()-nImageHeight)/2+1),ILD_TRANSPARENT);

	return;
}

// 绘制文本
void CSkinTreeCtrl::DrawItemString(CDC* pDC, CRect rcRect, HTREEITEM hTreeItem, bool bSelected)
{
	// 设置颜色
	COLORREF crString=RGB(0,0,0);

	// 设置字体
	pDC->SelectObject(&CSkinHelper::GetDefaultFont());

	// 设置环境
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(crString);

	// 绘画字体
	CString strString=GetItemText(hTreeItem);
	pDC->DrawText(strString,rcRect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	return;
}

// 重画消息
void CSkinTreeCtrl::OnPaint()
{
	CPaintDC dc(this);

	// 剪切位置
	CRect rcClip;
	dc.GetClipBox(&rcClip);

	// 获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	// 创建缓冲
	CDC BufferDC;
	CBitmap BufferImage;
	BufferDC.CreateCompatibleDC(&dc);
	BufferImage.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());

	// 设置 DC
	BufferDC.SelectObject(&BufferImage);

	// 绘画控件
	DrawTreeBack(&BufferDC,rcClient,rcClip);
	DrawTreeItem(&BufferDC,rcClient,rcClip);

	// 绘画背景
	dc.BitBlt(rcClip.left,rcClip.top,rcClip.Width(),rcClip.Height(),&BufferDC,rcClip.left,rcClip.top,SRCCOPY);

	// 删除资源
	BufferDC.DeleteDC();
	BufferImage.DeleteObject();

	return;
}

// 绘画背景
BOOL CSkinTreeCtrl::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

// 位置消息
void CSkinTreeCtrl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// 获取大小
	CRect rcClient;
	GetClientRect(&rcClient);

	// 获取信息
	SCROLLINFO ScrollInfoH;
	SCROLLINFO ScrollInfoV;
	ZeroMemory(&ScrollInfoH,sizeof(ScrollInfoH));
	ZeroMemory(&ScrollInfoV,sizeof(ScrollInfoV));

	// 获取信息
	GetScrollInfo(SB_HORZ,&ScrollInfoH,SIF_POS|SIF_RANGE);
	GetScrollInfo(SB_VERT,&ScrollInfoV,SIF_POS|SIF_RANGE);

	// 设置变量
	m_nXScroll=-ScrollInfoH.nPos;
	m_nYScroll=-ScrollInfoV.nPos;

	return;
}

// 鼠标移动
void CSkinTreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// 子项测试
	HTREEITEM hItemMouseHover=HitTest(point);

	// 重画判断
	if ((hItemMouseHover!=NULL)&&(hItemMouseHover!=m_hItemMouseHover))
	{
		// 设置变量
		m_hItemMouseHover=hItemMouseHover;

		// 重画界面
		Invalidate(FALSE);
	}

	return __super::OnMouseMove(nFlags,point);
}

// 光标消息
BOOL CSkinTreeCtrl::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	return TRUE;
}

// 右键列表
void CSkinTreeCtrl::OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 获取选择
	HTREEITEM hTreeItem=GetCurrentSelectItem(false);

	// 选择判断
	if (hTreeItem==NULL) return;

	// 设置选择
	Select(hTreeItem,TVGN_CARET);

	return;
}

// 左击列表
void CSkinTreeCtrl::OnNMLClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 获取选择
	HTREEITEM hTreeItem=GetCurrentSelectItem(false);

	// 选择判断
	if (hTreeItem==NULL) return;

	// 设置选择
	Select(hTreeItem,TVGN_CARET);

	return;
}

// 列表改变
void CSkinTreeCtrl::OnTvnSelchanged(NMHDR * pNMHDR, LRESULT * pResult)
{
	// 获取选择
	HTREEITEM hTreeItem=GetSelectedItem();

	// 选择判断
	if (hTreeItem==NULL) return;

	return;
}

// 列表展开
void CSkinTreeCtrl::OnTvnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 变量定义
	LPNMTREEVIEW pNMTreeView=reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// 动作处理
	if (pNMTreeView->action==TVE_EXPAND)
	{
	}

	return;
}
