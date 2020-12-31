// VSTab.cpp : implementation file
//

#include "stdafx.h"
#include "VSTab.h"

// CVSTab

IMPLEMENT_DYNAMIC(CVSTab, CWnd)

CVSTab::CVSTab()
{
	m_nItemCount = 0;
	m_nCurItem = 0;
	m_nCurMouseHoverItem = HIT_OUT_OF_RANGE;
	m_nOldMouseHoverItem = HIT_OUT_OF_RANGE;
	m_bTimerAlive = false;

	m_nItemHeight = DEFAULT_ITEM_HEIGHT;
	m_nItemWidth = DEFAULT_ITEM_WIDHT;

	m_btnState[BTN_NEW_ITEM] = BTNST_NORMAL;
	m_btnState[BTN_DROP_MENU] = BTNST_NORMAL;
	m_btnState[BTN_CLOSE_ITEM] = BTNST_NORMAL;
}

CVSTab::~CVSTab()
{
	for (POSITION pos = m_TabItemList.GetHeadPosition(); pos != NULL; )
	{
		TabItem* pItem = m_TabItemList.GetNext(pos);
		delete pItem;
	}
	m_TabItemList.RemoveAll();
	m_fontText.DeleteObject();
}


BEGIN_MESSAGE_MAP(CVSTab, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CVSTab message handlers

BOOL CVSTab::Create(CWnd *pParent, CRect rc, UINT nID)
{
	CString sWindowClassName = ::AfxRegisterWndClass(CS_DBLCLKS); 

	if(!CWnd::Create(sWindowClassName, "VSTab", WS_CHILD|WS_VISIBLE, rc, pParent, nID))
	{
		return FALSE;
	}
	
	m_nControlID = nID;
	SetItemTextFont("Microsoft Sans Serif", 14);
	SetItemTextColor(RGB(0,0,0));

	return TRUE;
}

void CVSTab::OnPaint()
{
	CPaintDC dc(this);
	CMemDC pDC(&dc);

	CRect rect, rcItem;
	GetClientRect(&rect);

	//画背景
	pDC->FillSolidRect(&rect, COLOR_BK_NORMAL);
	DrawLine(pDC, CPoint(rect.left, rect.bottom-1), CPoint(rect.right, rect.bottom-1), COLOR_BORDER);

	//画最右边的关闭按钮
	rcItem.right = rect.right;	
	rcItem.top = rect.top + VMARGIN;
	rcItem.bottom = rect.bottom - VMARGIN;
	rcItem.left  = rcItem.right - CLOSE_ITEM_WIDTH;
	rcItem.DeflateRect(0,1);
	if (m_btnState[BTN_CLOSE_ITEM] == BTNST_HOT)
	{
		CPen pen(PS_SOLID,1, COLOR_BORDER);
		CPen* oldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(rcItem);
		pDC->SelectObject(oldPen);
		rcItem.DeflateRect(1,1);
		pDC->FillSolidRect(&rcItem,COLOR_BK_HOT);
		rcItem.DeflateRect(-1,-1);
		//pDC->DrawEdge(&rcItem,BDR_SUNKENINNER,BF_LEFT|BF_BOTTOM|BF_FLAT);
	}
	else
		pDC->FillSolidRect(&rcItem,COLOR_BK_NORMAL);
	rcItem.DeflateRect(0,-1);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText("x", rcItem, DT_CENTER);

	//画下拉菜单按钮
	rcItem.right = rcItem.left-HMARGIN;	
	rcItem.top = rect.top + VMARGIN;
	rcItem.bottom = rect.bottom - VMARGIN;
	rcItem.left  = rcItem.right - DROP_MENU_WIDTH;
	rcItem.DeflateRect(0,1);
	if (m_btnState[BTN_DROP_MENU] == BTNST_HOT)
	{
		CPen pen(PS_SOLID,1, COLOR_BORDER);
		CPen* oldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(rcItem);
		pDC->SelectObject(oldPen);
		rcItem.DeflateRect(1,1);
		pDC->FillSolidRect(&rcItem,COLOR_BK_HOT);
		rcItem.DeflateRect(-1,-1);
		//pDC->DrawEdge(&rcItem,BDR_SUNKENINNER,BF_LEFT|BF_BOTTOM|BF_FLAT);
	}
	else
		pDC->FillSolidRect(&rcItem,COLOR_BK_NORMAL);
	rcItem.DeflateRect(0,-1);
	DrawArrow(pDC, rcItem.CenterPoint());

	//画新建标签页面
	rcItem.left = m_nItemCount * m_nItemWidth+HMARGIN;	
	rcItem.top = rect.top + VMARGIN;
	rcItem.bottom = rect.bottom - VMARGIN;
	rcItem.right  = rcItem.left + NEW_ITEM_WIDTH;
	rcItem.DeflateRect(0,1);

	if (m_btnState[BTN_NEW_ITEM] == BTNST_HOT)
	{
		CPen pen(PS_SOLID,1, COLOR_BORDER);
		CPen* oldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(rcItem);
		pDC->SelectObject(oldPen);
		rcItem.DeflateRect(1,1);
		pDC->FillSolidRect(&rcItem,COLOR_BK_HOT);
		rcItem.DeflateRect(-1,-1);
		//pDC->DrawEdge(&rcItem,BDR_SUNKENINNER,BF_LEFT|BF_BOTTOM|BF_FLAT);
	}
	else
		pDC->FillSolidRect(&rcItem,COLOR_BK_NORMAL);
	rcItem.DeflateRect(0,-1);
	pDC->SetBkMode(TRANSPARENT);
	DrawIcon(pDC, 2, CPoint(rcItem.left+HMARGIN, rcItem.top+4+VMARGIN));
	
	//最后开始画标签
	for (int i = 0; i < m_nItemCount; i++)
	{
		rcItem.left = i * m_nItemWidth;
		rcItem.right = rcItem.left + m_nItemWidth;
		DrawTabItem(pDC, rcItem, i);		
	}
	
}

void CVSTab::DrawArrow(CDC *pDC, CPoint ptArrow, COLORREF crCol)
{
	CPen penTmp(PS_SOLID,1,crCol);
	CPen* pOldPen = pDC->SelectObject(&penTmp);

	CPoint ptDest;
	ptArrow += CPoint(-1,2);

	pDC->SetPixel(ptArrow, crCol);

	ptArrow -= CPoint(1,1);
	pDC->MoveTo(ptArrow);
	ptDest = ptArrow;
	ptDest += CPoint(3,0);
	pDC->LineTo(ptDest);

	ptArrow -= CPoint(1,1);
	pDC->MoveTo(ptArrow);
	ptDest = ptArrow;
	ptDest += CPoint(5,0);
	pDC->LineTo(ptDest);

	ptArrow -= CPoint(1,1);
	pDC->MoveTo(ptArrow);
	ptDest = ptArrow;
	ptDest += CPoint(7,0);
	pDC->LineTo(ptDest);
	
	pDC->SelectObject(pOldPen);
}

void CVSTab::DrawTabItem(CDC *pDC, CRect rcItem, int nItem)
{
	if (nItem < 0 || nItem >= m_nItemCount)
		return;
	
	TabItem* pItem = FindItem(nItem);
	int nLeft = nItem * m_nItemWidth;
	rcItem.DeflateRect(2,0);

	//draw background
	if (m_nCurItem != nItem)
		rcItem.top += 2;
	pDC->FillSolidRect(rcItem, COLOR_BK_NORMAL);
	if (m_nCurItem == nItem)
	{
		CRect rcTop(rcItem);
		rcTop.bottom = rcTop.top + 4;
		pDC->FillSolidRect(rcTop, COLOR_ITEM_SELECTED);
		rcTop.top = rcTop.bottom;
		rcTop.bottom = rcItem.bottom;
		pDC->FillSolidRect(rcTop, RGB(255,255,255));
		DrawLine(pDC, CPoint(rcItem.left, rcItem.top), CPoint(rcItem.left,rcItem.bottom),COLOR_ITEM_SELECTED);
	}
	else
	{
		pDC->Draw3dRect(rcItem, COLOR_ITEM_SELECTED, COLOR_ITEM_SELECTED);//COLOR_BK_NORMAL);
	}

	//draw border
	DrawLine(pDC, CPoint(rcItem.right, rcItem.top+1), CPoint(rcItem.right,rcItem.bottom-1), RGB(192,192,192));

	CPoint pt;
	CRect rcImage, rcText(rcItem);
	IMAGEINFO imgInfo = {0};

	//draw label icon
	m_pImageList->GetImageInfo(pItem->nImage,&imgInfo);
	rcImage = imgInfo.rcImage;
	pt.x = rcItem.left + 4;
	pt.y = rcItem.top + rcItem.Height() / 2 - rcImage.Height()/2;
	rcText.left = pt.x + rcImage.Width() + HMARGIN;
	
	m_pImageList->Draw(pDC, pItem->nImage, pt, ILD_TRANSPARENT);
	
	/*
	//draw close icon
	m_pImageList->GetImageInfo(pItem->nCloseBtn, &imgInfo);
	rcImage = imgInfo.rcImage;
	pt.x = rcItem.right - 4 - rcImage.Width();
	pt.y = rcItem.top + rcItem.Height() / 2 - rcImage.Height()/2;
	rcText.right = pt.x - HMARGIN;

	m_pImageList->Draw(pDC, pItem->nCloseBtn, pt, ILD_TRANSPARENT);
	*/

	//draw text
	CFont *pOldFont = pDC->SelectObject(&m_fontText);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_clrText);
	rcText.top += 4;
	pDC->DrawText(pItem->strItem, rcText, DT_LEFT|DT_END_ELLIPSIS);
	pDC->SelectObject(pOldFont);
}

int CVSTab::CheckItem(int nItem)
{
	if (nItem < 0 || nItem >= m_nItemCount)
		return -1;
	else
		return 0;
}
int CVSTab::SetCurSel(int nItem)
{
	if (CheckItem(nItem) < 0)
		return -1;

	m_nCurItem = nItem;
	Invalidate();
	return 0;
}
int CVSTab::SetItemText(int nItem, CString szText)
{
	if (CheckItem(nItem) < 0)
		return -1;

	TabItem* pItem = FindItem(nItem);
	if (pItem)
		pItem->strItem = szText;
	else
		return -1;
	return 0;
}
CString CVSTab::GetItemText(int nItem)
{
	if (CheckItem(nItem) < 0)
		return "";

	TabItem* pItem = FindItem(nItem);
	if (pItem)
		return pItem->strItem;
	else
		return "";
}
int CVSTab::SetItemImage(int nItem, int nImage)
{
	if (CheckItem(nItem) < 0)
		return -1;

	TabItem* pItem = FindItem(nItem);
	if (pItem)
		pItem->nImage = nImage;
	else
		return -1;
	return 0;
}
int CVSTab::GetItemImage(int nItem)
{
	if (CheckItem(nItem) < 0)
		return -1;

	TabItem* pItem = FindItem(nItem);
	if (pItem)
		return pItem->nImage;
	else
		return -1;
}

//itemOrData为TURE，nInfo为nItem,否则为nData
TabItem*  CVSTab::FindItem(int nInfo, bool itemOrData)
{
	if (m_TabItemList.IsEmpty())
		return NULL;
	for (POSITION pos = m_TabItemList.GetHeadPosition(); pos != NULL; )
	{
		TabItem* pItem = m_TabItemList.GetNext(pos);
		if (pItem == NULL)
			break;
		if (pItem->nItem == nInfo && itemOrData)
			return pItem;
		else if (pItem->nData == nInfo && !itemOrData)
			return pItem;
	}
	return NULL;
}

int CVSTab::InsertItem(TabItem* pItem)
{
	if (FindItem(pItem->nItem))
		return -1;
	m_TabItemList.AddTail(pItem);
	m_nItemCount++;
	CalculateItemWidth();
	Invalidate();
	return m_nItemCount;
}
int CVSTab::InsertItem(CString szText, CWnd *pWnd, int nImage, int nData)
{
	TabItem* pItem = new TabItem;
	pItem->nData = nData;
	pItem->nImage = nImage;
	pItem->nItem = m_nItemCount;
	pItem->strItem = szText;
	pItem->pWnd = pWnd;
	return InsertItem(pItem);
}

int CVSTab::DeleteItem(int nInfo, bool itemOrData)
{
	if (m_TabItemList.IsEmpty())
		return -1;
	POSITION pos, rpos;
	for (pos = m_TabItemList.GetHeadPosition(); pos != NULL; )
	{
		rpos = pos;
		TabItem* pItem = m_TabItemList.GetNext(pos);
		if (pItem)
		{
			if (pItem->nItem == nInfo && itemOrData)
			{
				return DeleteItem(rpos);
			}
			else if (pItem->nData == nInfo && !itemOrData)
			{
				return DeleteItem(rpos);
			}
		}
	}
	return -1;
}

int CVSTab::DeleteItem(POSITION pos)
{
	if (pos == NULL)
		return -1;
	POSITION rpos = pos;
	TabItem* pItem = NULL;
	//之后的标签索引重新排序
	while(pos)
	{
		pItem = m_TabItemList.GetNext(pos);
		pItem->nItem--;
	}
	pItem = m_TabItemList.GetAt(rpos);
	delete pItem;
	m_TabItemList.RemoveAt(rpos);
	m_nItemCount--;
	CalculateItemWidth();
	Invalidate();
	return m_nItemCount;
}


int CVSTab::HitTest(CPoint pt)
{
	CRect rect;
	GetClientRect(&rect);
	CRect rcItem(rect);

	rcItem.top += VMARGIN;
	rcItem.bottom -= VMARGIN;

	//标签范围内
	for (int i = 0; i < m_nItemCount; i++)
	{
		rcItem.left = i * m_nItemWidth;
		rcItem.right = rcItem.left + m_nItemWidth;
		if (rcItem.PtInRect(pt))
			return i;
	}
	//关闭按钮范围内
	rcItem.right = rect.right - HMARGIN;
	rcItem.left = rcItem.right - CLOSE_ITEM_WIDTH;
	if (rcItem.PtInRect(pt))
		return HIT_CLOSE_ITEM;

	//下拉菜单范围内
	rcItem.right = rect.right - HMARGIN - CLOSE_ITEM_WIDTH;
	rcItem.left = rcItem.right - DROP_MENU_WIDTH;
	if (rcItem.PtInRect(pt))
		return HIT_DROP_MENU;
	//新建标签页范围内
	rcItem.left = m_nItemCount * m_nItemWidth;
	rcItem.right = rcItem.left + NEW_ITEM_WIDTH;
	if (rcItem.PtInRect(pt))
		return HIT_NEW_ITEM;

	return HIT_OUT_OF_RANGE;
}

NM_DATA* CVSTab::NewNotifyMsg(int nCode, int nArea, CPoint pt, TabItem* pItem)
{
	NM_DATA* pMsg = new NM_DATA;
	pMsg->hdr.hwndFrom = GetSafeHwnd();
	pMsg->hdr.idFrom = m_nControlID;
	pMsg->hdr.code = nCode;
	pMsg->pItem = pItem;
	pMsg->hitArea = nArea;

	CRect rect;
	GetWindowRect(&rect);
	pMsg->hitPoint.x = pt.x + rect.left;
	pMsg->hitPoint.y = pt.y + rect.top;
	return pMsg;
}
//父窗口必须有对应的消息处理函数，并且需要delete掉lParam参数，否则内存泄漏
void CVSTab::OnLButtonDown(UINT nFlags, CPoint point)
{
	KillTimer(TIMER_MOUSE_HOVER);
	m_bTimerAlive = false;
	int nItem = HitTest(point);

	if (CheckItem(nItem) == 0)
	{
		m_nCurItem = nItem;
		Invalidate();
	}
	if (nItem > HIT_OUT_OF_RANGE)
	{
		NM_DATA* pNMHDR = NewNotifyMsg(VSTAB_LBUTTONDOWN, nItem, point, FindItem(nItem));
		GetParent()->PostMessage(WM_NOTIFY, m_nControlID, (LPARAM)pNMHDR);
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CVSTab::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}

void CVSTab::OnRButtonDown(UINT nFlags, CPoint point)
{
	KillTimer(TIMER_MOUSE_HOVER);
	m_bTimerAlive = false;
	int nItem = HitTest(point);

	if (nItem >= 0)
	{
		NM_DATA* pNMHDR = NewNotifyMsg(VSTAB_RBUTTONDOWN, nItem, point, FindItem(nItem));
		GetParent()->PostMessage(WM_NOTIFY, m_nControlID, (LPARAM)pNMHDR);
	}

	CWnd::OnRButtonDown(nFlags, point);
}

void CVSTab::OnMouseMove(UINT nFlags, CPoint point)
{
	int nItem = HitTest(point);

	m_btnState[BTN_NEW_ITEM] = BTNST_NORMAL;
	m_btnState[BTN_DROP_MENU] = BTNST_NORMAL;
	m_btnState[BTN_CLOSE_ITEM] = BTNST_NORMAL;

	if (!m_bTimerAlive)
		this->SetTimer(TIMER_MOUSE_HOVER, MOUSE_HOVER_ELAPSE, NULL);
	m_nCurMouseHoverItem = nItem;
	m_nOldMouseHoverItem = nItem;
	m_bTimerAlive = true;
	m_curPoint = point;

	switch (nItem)
	{
	case HIT_NEW_ITEM:
		m_btnState[BTN_NEW_ITEM] = BTNST_HOT;
		break;
	case HIT_CLOSE_ITEM:
		m_btnState[BTN_CLOSE_ITEM] = BTNST_HOT;
		break;
	case HIT_DROP_MENU:
		m_btnState[BTN_DROP_MENU] = BTNST_HOT;
		break;
	case HIT_OUT_OF_RANGE:
		break;
	default:
		break;
	}

	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}

BOOL CVSTab::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

int CVSTab::CalculateItemWidth(void)
{
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width() - NEW_ITEM_WIDTH - DROP_MENU_WIDTH - CLOSE_ITEM_WIDTH - HMARGIN;

	if (m_nItemCount * DEFAULT_ITEM_WIDHT > width)
		if (m_nItemCount > 0)
			m_nItemWidth = width / m_nItemCount;
		else
			m_nItemWidth = width;

	return m_nItemWidth;
}

CRect CVSTab::GetItemRect(int nItem)
{
	CRect rect;
	GetClientRect(&rect);
	CRect rcItem(rect);

	rcItem.top += VMARGIN;
	rcItem.bottom -= VMARGIN;
	rcItem.left = nItem * m_nItemWidth;
	rcItem.right = rcItem.left + m_nItemWidth;

	return rcItem;
}

BOOL CVSTab::DrawIcon(CDC* pDC, int nImage, CPoint point)
{
	CRect rcImage;
	IMAGEINFO imgInfo = {0};

	m_pImageList->GetImageInfo(nImage,&imgInfo);
	rcImage = imgInfo.rcImage;
	return m_pImageList->Draw(pDC, nImage, point, ILD_TRANSPARENT);
}

void CVSTab::DrawLine(CDC* pDC, CPoint ptStart, CPoint ptEnd, COLORREF clrPen)
{
	CPen pen(PS_SOLID, 1, clrPen);
	CPen* oldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(ptStart);
	pDC->LineTo(ptEnd);
	pDC->SelectObject(oldPen);
}

void CVSTab::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	Invalidate();
}

BOOL CVSTab::SetItemTextFont(CString szFont, UINT nHeight)
{
	if (szFont.IsEmpty() || nHeight <= 0)
		return FALSE;

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	
	lf.lfHeight = nHeight;
	strcpy_s(lf.lfFaceName, LF_FACESIZE, (char *)szFont.GetBuffer());
	m_fontText.DeleteObject();
	return m_fontText.CreateFontIndirect(&lf);
}


BOOL CVSTab::PreTranslateMessage(MSG* pMsg)
{

	return CWnd::PreTranslateMessage(pMsg);
}

void CVSTab::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_MOUSE_HOVER)
	{
		if (m_nOldMouseHoverItem >= HIT_OUT_OF_RANGE && m_nOldMouseHoverItem == m_nCurMouseHoverItem)
		{
			NM_DATA* pNMHDR = NewNotifyMsg(VSTAB_MOUSEMOVE, m_nOldMouseHoverItem, m_curPoint, FindItem(m_nOldMouseHoverItem));
			GetParent()->PostMessage(WM_NOTIFY, m_nControlID, (LPARAM)pNMHDR);
		}
		KillTimer(TIMER_MOUSE_HOVER);
		m_bTimerAlive = false;
	}

	CWnd::OnTimer(nIDEvent);
}
