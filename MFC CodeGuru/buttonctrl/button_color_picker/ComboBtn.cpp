// colorctl.cpp : implementation file
//

#include "stdafx.h"
#include "ComboBtn.h"

void FillSolidRect(CDC * pDC, int x, int y, int cx, int cy, COLORREF clr)
{
	ASSERT(pDC != NULL);
	ASSERT(pDC->m_hDC != NULL);

	COLORREF oldColor = pDC->SetBkColor(clr);
	CRect rect(x, y, x + cx, y + cy);
	pDC->ExtTextOut(0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
	pDC->SetBkColor(oldColor);
}

void Draw3dRect(CDC * pDC, int x, int y, int cx, int cy, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	FillSolidRect(pDC, x, y, cx - 1, 1, clrTopLeft);
	FillSolidRect(pDC, x, y, 1, cy - 1, clrTopLeft);
	FillSolidRect(pDC, x + cx, y, -1, cy, clrBottomRight);
	FillSolidRect(pDC, x, y + cy, cx, -1, clrBottomRight);
}

void Draw3dRect(CDC * pDC, LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	Draw3dRect(pDC, lpRect->left, lpRect->top, lpRect->right - lpRect->left, 
		lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
}

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonCombo

CButtonCombo::CButtonCombo()
{
	m_bLeftBtnDown 	= m_bRightBtnDown	= FALSE;
	m_bLeftBtnOut 	= FALSE;
	m_lItem			= m_iRealItem = 0;
}

CButtonCombo::~CButtonCombo()
{    
	m_wndColor.DestroyWindow();
}


BEGIN_MESSAGE_MAP(CButtonCombo, CWnd)
	//{{AFX_MSG_MAP(CButtonCombo)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CButtonCombo message handlers

// rect 		= size of the button
// sizeGrid 	= size of grid containing the color (x rectangles by y rectangles)
// sizeBtn 		= size of ech rectangle in the grid containing the color
// pParent		= parent of the button
// nID			= ID of the button
// sTextItems	= (optional) text to show when selecting a color

BOOL CButtonCombo::Create(CRect rect, CSize sizeGrid, CSize sizeBtn, CWnd * pParent, 
						UINT nID, CString sTextItems)
{              
	ASSERT(pParent);
	m_pParent	= pParent;
	m_nID 		= nID;

	if(!CWnd::Create(NULL, NULL, WS_BORDER | WS_VISIBLE | WS_CHILD, rect, m_pParent, m_nID))
		return FALSE;
		
	if (!m_wndColor.Create(rect.left, rect.bottom, sizeGrid, sizeBtn, this, sTextItems))
		return FALSE;        
		
	return TRUE;
}

// rect 				= size of the button
// sizeGrid 			= size of grid containing the color (x rectangles by y rectangles)
// nBitmapIDResource 	= ID of the bitmap
// iNbImages			= number of images in the bitmap
// nID					= ID of the button
// sTextItems			= (optional) text to show when selecting a color

BOOL CButtonCombo::Create(CRect rect, CSize sizeGrid, UINT nBitmapIDResource, int iNbImages, 
						CWnd * pParent, UINT nID, CString sTextItems)
{
	ASSERT(pParent);
	m_pParent	= pParent;
	m_nID 		= nID;

	if(!CWnd::Create(NULL, NULL, WS_BORDER | WS_VISIBLE | WS_CHILD, rect, m_pParent, m_nID))
		return FALSE;
		
	if (!m_wndColor.Create(rect.left, rect.bottom, sizeGrid, nBitmapIDResource, 
							iNbImages, this, sTextItems))
		return FALSE;
	return TRUE;
}

void CButtonCombo::OnItemSelected(long lItem, int iRealItem)
{                  
	m_lItem 		= lItem;
	m_iRealItem   	= iRealItem;
	m_bLeftBtnDown 	= FALSE;
	m_bRightBtnDown = FALSE;
	m_wndColor.SetSelectedItem(m_iRealItem);
	m_wndColor.ShowWindow(m_bRightBtnDown ? SW_SHOW : SW_HIDE);
	Invalidate(FALSE);
	UpdateWindow();

	if (m_lItem >= 0)
	{                
		if (m_pParent->GetOwner()->IsKindOf(RUNTIME_CLASS(CDialog)))
			m_pParent->GetOwner()->SendMessage(WM_USER+21, (WPARAM)m_nID, (LPARAM)m_lItem);
		else	
			AfxGetMainWnd()->SendMessageToDescendants(WM_USER+21, (WPARAM)m_nID, (LPARAM)m_lItem, TRUE, TRUE);
	}
}

void CButtonCombo::UnpressRightButton() 
{
    m_bRightBtnDown = FALSE;
    Invalidate(FALSE);
    UpdateWindow();
}

void CButtonCombo::OnLButtonDown(UINT nFlags, CPoint point) 
{         
	CRect rect;
	GetClientRect(&rect);
	CRect rcLeft(rect.left, rect.top, rect.right - 15, rect.bottom);
	CRect rcRight(rect.right - 15, rect.top, rect.right, rect.bottom);
	
	if (rcLeft.PtInRect(point))
	{             
		m_bLeftBtnDown	= TRUE;
		m_bRightBtnDown = FALSE;
	}
	else if (rcRight.PtInRect(point))
		m_bRightBtnDown ^= 1;
	else              
		m_bLeftBtnDown 	= m_bRightBtnDown = FALSE;
  
  	GetWindowRect(rect);
	m_wndColor.SetWindowPos(NULL, rect.left, rect.bottom, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	m_wndColor.SetSelectedItem(m_iRealItem);
	m_wndColor.ShowWindow(m_bRightBtnDown ? SW_SHOW : SW_HIDE);

	Invalidate(FALSE);
	UpdateWindow();

	SetCapture();
 	
	CWnd::OnLButtonDown(nFlags, point);
}

void CButtonCombo::OnLButtonUp(UINT nFlags, CPoint point) 
{       
    ReleaseCapture();

	if (m_bLeftBtnDown)
		OnItemSelected(m_lItem, m_iRealItem);
	m_bLeftBtnDown = FALSE;
	Invalidate(FALSE);
	UpdateWindow();
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CButtonCombo::OnMouseMove(UINT nFlags, CPoint point) 
{
	BOOL bOut = m_bLeftBtnOut;
	CRect rect;
	GetClientRect(&rect);
	CRect rcLeft(rect.left, rect.top, rect.right - 15, rect.bottom);
	
	if (rcLeft.PtInRect(point))
		m_bLeftBtnOut	= FALSE;
	else
		m_bLeftBtnOut 	= TRUE;

	if (bOut != m_bLeftBtnOut)
	{
		Invalidate(FALSE);
		UpdateWindow();
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CButtonCombo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	CRect rcLeft(rect.left, rect.top, rect.right - 15, rect.bottom-1);
	CRect rcRight(rect.right - 15, rect.top, rect.right - 1, rect.bottom-1);

	CDC memDC;
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.CreateCompatibleDC(&dc);
	CBitmap * pOldBitmap = memDC.SelectObject(&bitmap);

	CBrush brBack(GetSysColor(COLOR_BTNFACE));
	memDC.FillRect(rect, &brBack);

	Draw3dRect(&memDC, &rect, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_BTNSHADOW)); 

	CRect rcImage(rcLeft.left+1, rcLeft.top+1, rcLeft.right-1, rcLeft.bottom-1);
	if (!m_bLeftBtnDown || m_bLeftBtnOut) // Draw Button Up
		Draw3dRect(&memDC, &rcLeft, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_BTNSHADOW)); 
	else
	{
		rcLeft.SetRect(rcLeft.left, rcLeft.top, rcLeft.right+1, rcLeft.bottom+1);
		Draw3dRect(&memDC, &rcLeft, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNFACE)); 
		rcImage.OffsetRect(1, 1);
	}

	m_wndColor.DrawBtnFace(&memDC, rcImage, m_lItem);

	if (!m_bRightBtnDown) // Draw Button Up
		Draw3dRect(&memDC, &rcRight, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_BTNSHADOW)); 
	else
	{
		rcRight.SetRect(rcRight.left, rcRight.top, rcRight.right+1, rcRight.bottom+1);
		Draw3dRect(&memDC, &rcRight, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNFACE)); 
		rcRight.OffsetRect(1, 1);
	}
	
	DrawArrow(&memDC, &rcRight);	
    
    if (!IsWindowEnabled())
		DrawDisabled(&memDC, rect);

	dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, rect.left, rect.top, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	brBack.DeleteObject();
	bitmap.DeleteObject();
}

void CButtonCombo::DrawDisabled( CDC * pDC, const CRect & rc )
{
	// create a monochrome memory DC
	CDC memDC;
	memDC.CreateCompatibleDC(0);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&memDC, rc.Width(), rc.Height());
	CBitmap * pOldBmp = memDC.SelectObject(&bmp);
	
	// build a mask
	memDC.PatBlt(0, 0, rc.Width(), rc.Height(), WHITENESS);
	pDC->SetBkColor(GetSysColor(COLOR_BTNFACE));
	memDC.BitBlt(0, 0, rc.Width(), rc.Height(), pDC, rc.left, rc.top, SRCCOPY);
	pDC->SetBkColor(GetSysColor(COLOR_BTNHIGHLIGHT));
	memDC.BitBlt(0, 0, rc.Width(), rc.Height(), pDC, rc.left, rc.top, SRCPAINT);

	// Copy the image from the toolbar into the memory DC
	// and draw it (grayed) back into the toolbar.
	CBrush 	brShadow(GetSysColor(COLOR_BTNSHADOW)), 
			brHilight(GetSysColor(COLOR_BTNHIGHLIGHT)), 
			brFace(GetSysColor(COLOR_BTNFACE));
	
//	pDC->FillRect(rc, &brFace);
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(RGB(255, 255, 255));


	CBrush * pOldBrush = pDC->SelectObject(&brHilight);
	pDC->BitBlt(rc.left+1, rc.top+1, rc.Width(), rc.Height(), &memDC, 0, 0, 0x00E20746L);
	pDC->SelectObject(&brShadow);
	pDC->BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, 0x00E20746L);
	
	// reset DCs
	pDC->SelectObject(pOldBrush);
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();

	brShadow.DeleteObject();
	brHilight.DeleteObject();
	brFace.DeleteObject();
	bmp.DeleteObject();
}

void CButtonCombo::DrawArrow(CDC * pDC, CRect * pRect)
{
	ASSERT(pRect);

	CPoint ptCenter(pRect->left + (pRect->Width() / 2), pRect->top + (pRect->Height() / 2));

	CPoint ptArrow[7];
	ptArrow[0].x = ptCenter.x-1;
	ptArrow[0].y = ptCenter.y-4;
	
	ptArrow[1].x = ptCenter.x-1;
	ptArrow[1].y = ptCenter.y-1;

	ptArrow[2].x = ptCenter.x-3;
	ptArrow[2].y = ptCenter.y-1;

	ptArrow[3].x = ptCenter.x;
	ptArrow[3].y = ptCenter.y+2;

	ptArrow[4].x = ptCenter.x+3;
	ptArrow[4].y = ptCenter.y-1;

	ptArrow[5].x = ptCenter.x+1;
	ptArrow[5].y = ptCenter.y-1;

	ptArrow[6].x = ptCenter.x+1;
	ptArrow[6].y = ptCenter.y-4;

	CBrush brBlack(RGB(0, 0, 0));
  	CBrush * pOldBrush = pDC->SelectObject(&brBlack);
	pDC->Polygon(ptArrow, 7);  
	pDC->MoveTo(ptCenter.x - 3, ptCenter.y + 4);
	pDC->LineTo(ptCenter.x + 4, ptCenter.y + 4);
  	pDC->SelectObject(pOldBrush);
	brBlack.DeleteObject();
}

void CButtonCombo::OnEnable(BOOL bEnable) 
{
	CWnd::OnEnable(bEnable);
	
	Invalidate(FALSE);
	UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CWndCombo

CWndCombo::CWndCombo()
{         
	m_rgbBkColor 	= GetSysColor(COLOR_BTNFACE);
	m_iSelectedItem	= 0;
	m_iNbImages		= -1; 
}

CWndCombo::~CWndCombo()
{       
	if (m_bmImage.m_hObject)
		m_bmImage.DeleteObject();
	if (m_font.m_hObject)
		m_font.DeleteObject();
}

BEGIN_MESSAGE_MAP(CWndCombo, CWnd)
	//{{AFX_MSG_MAP(CWndCombo)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndCombo message handlers

BOOL CWndCombo::Create(int x, int y, CSize sizeGrid, CSize sizeBtn, CWnd * pParent, CString sTextItems)
{
	ASSERT(pParent);  
	if (m_hWnd)	return FALSE;
		
	m_sizeGrid	= sizeGrid;
	m_sizeBtn 	= sizeBtn;
	m_pParent 	= pParent;
	m_iNbImages = m_sizeGrid.cx * m_sizeGrid.cy;
	
	CSize sizeText = UpdateTextItems(sTextItems);
	int iWidth	= (m_sizeGrid.cx * m_sizeBtn.cx) + (m_sizeGrid.cx - 1) + 4; 
	int iRow = (sizeText.cy > 0) ? 0 : 1;
	int iHeight = (m_sizeGrid.cy * m_sizeBtn.cy) + (m_sizeGrid.cy - iRow) + 4 + sizeText.cy; 
	CRect rect(x, y, x + iWidth, y + iHeight);

	return CWnd::CreateEx(0, NULL, NULL, WS_CHILD | WS_POPUP, rect.left, rect.top, 
							rect.Width(), rect.Height(), m_pParent->m_hWnd, 0);
}

BOOL CWndCombo::Create(int x, int y, CSize sizeGrid, UINT nBitmapIDResource, int iNbImages, 
						CWnd * pParent, CString sTextItems)
{
	ASSERT(pParent);  
	if (m_hWnd)	return FALSE;
	m_pParent 	= pParent;
	m_sizeGrid	= sizeGrid;
	m_iNbImages	= iNbImages;
	
	m_bmImage.LoadBitmap(nBitmapIDResource);	

	BITMAP bm;
	m_bmImage.GetObject( sizeof( bm ), &bm );
	m_sizeBtn 	= CSize(bm.bmWidth / m_iNbImages, bm.bmHeight);

	CSize sizeText = UpdateTextItems(sTextItems);
	int iWidth	= (m_sizeGrid.cx * (m_sizeBtn.cx + 8)) + (m_sizeGrid.cx - 1) + 4; 
	int iRow = (sizeText.cy > 0) ? 0 : 1;
	int iHeight = (m_sizeGrid.cy * (m_sizeBtn.cy + 8)) + (m_sizeGrid.cy - iRow) + 4 + sizeText.cy; 
	CRect rect(x, y, x + iWidth, y + iHeight);

	return CWnd::CreateEx(0, NULL, NULL, WS_CHILD | WS_POPUP, rect.left, rect.top, 
							rect.Width(), rect.Height(), m_pParent->m_hWnd, 0);
}

CSize CWndCombo::UpdateTextItems(CString sTextItems)
{
	if (sTextItems.IsEmpty())
		return CSize(0, 0);
	int i;
	m_lstTextItems.RemoveAll;
	while ((i = sTextItems.Find(';')) != -1)
	{
		m_lstTextItems.Add(sTextItems.Left(i));
		sTextItems = sTextItems.Mid(i+1);
	}
	m_lstTextItems.Add(sTextItems);

	CDC *pDC = GetDC();
	LOGFONT logfont;
	memset(&logfont, 0, sizeof(logfont));
	// 8 point height Sans Serif font
	logfont.lfHeight = -MulDiv(8, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	logfont.lfWeight = FW_NORMAL;
	logfont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
	static char BASED_CODE szFaceName[] = "MS Sans Serif";
	lstrcpy(logfont.lfFaceName, szFaceName);
	m_font.CreateFontIndirect(&logfont);
    CSize sizeText = pDC->GetTextExtent("Test", 4);
    ReleaseDC(pDC);	
	return sizeText;
}

void CWndCombo::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
}

void CWndCombo::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_iSelectedItem != -1)
	{		
		if (m_bmImage.m_hObject)
			((CButtonCombo*)m_pParent)->OnItemSelected(m_iSelectedItem, m_iSelectedItem);
		else
			((CButtonCombo*)m_pParent)->OnItemSelected(GetColor(m_iSelectedItem), m_iSelectedItem);
	}
	m_iSelectedItem	= -1;
	ShowWindow(SW_HIDE);

	CWnd::OnLButtonUp(nFlags, point);
}

void CWndCombo::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rcItem;
	int iItem = GetItem(point, &rcItem);
	if (iItem != -1)
		m_iSelectedItem = iItem;	
	Invalidate();
	UpdateWindow();
	                                    
	CWnd::OnMouseMove(nFlags, point);
}

int CWndCombo::GetItem(CPoint point, CRect * pRect)
{
	ASSERT(pRect);
	pRect->SetRectEmpty();

	CRect rect;
	GetClientRect(rect);

	if (!rect.PtInRect(point))
		return -1;	

	int iTop = rect.top + 2, iLeft, iItem;
	CRect rcBtn;
		
	for (int i = 0; i < m_sizeGrid.cy; i++)
    {   
		rcBtn.top 		= iTop;
		if (m_bmImage.m_hObject)
			rcBtn.bottom	= rcBtn.top + m_sizeBtn.cy + 8;
		else
			rcBtn.bottom	= rcBtn.top + m_sizeBtn.cy;
		iTop 			= rcBtn.bottom + 2;
		if (point.y > rcBtn.bottom)
			continue;
        else        
        {
			iLeft = rect.left + 2;
			for (int j = 0; j < m_sizeGrid.cx; j++)
			{        
		    	rcBtn.left	= iLeft;
				if (m_bmImage.m_hObject)
					rcBtn.right = rcBtn.left + m_sizeBtn.cx + 8;
				else
					rcBtn.right = rcBtn.left + m_sizeBtn.cx;
				iLeft = rcBtn.right + 2;
				if (point.x > rcBtn.right)
					continue;             
				else              
				{
					*pRect = rcBtn;      
					iItem = (i * m_sizeGrid.cx) + j;
					if (iItem < m_iNbImages)
						return iItem;
					else
						return -1;
				}
			}                   
		}
	} 
	return -1;            
}

void CWndCombo::DrawBtnFace(CDC * pDC, CRect rect, long lItem)
{            
	if (lItem == -1)
		return;
	if (m_bmImage.m_hObject)
	{			           
		CPoint ptCenter(rect.left + (rect.Width() / 2), rect.top + (rect.Height() / 2));
		CPoint ptOffSet(ptCenter.x - (m_sizeBtn.cx / 2), ptCenter.y - (m_sizeBtn.cy / 2));

		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap * pOldBitmap = memDC.SelectObject(&m_bmImage);

		pDC->BitBlt(ptOffSet.x, ptOffSet.y, m_sizeBtn.cx, m_sizeBtn.cy, &memDC, 
					(int) lItem * m_sizeBtn.cx, 0, SRCCOPY);
		memDC.SelectObject(pOldBitmap);
    }
	else 
	{
		CBrush brRect(lItem);
		pDC->FillRect(CRect(rect.left+2, rect.top+2, rect.right-3, rect.bottom-2), &brRect);
		brRect.DeleteObject();
	}	
}

void CWndCombo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.CreateCompatibleDC(&dc);
	CBitmap * pOldBitmap = memDC.SelectObject(&bitmap);

	CBrush brBack(m_rgbBkColor), brBlack(RGB(0, 0, 0));
	memDC.FillRect(rect, &brBack);
	Draw3dRect(&memDC, &rect, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_WINDOWFRAME)); 

	int iTop = rect.top + 2, iLeft, iItem;
	CRect rcBtn;
	
	for (int i = 0; i < m_sizeGrid.cy; i++)
    {        
		rcBtn.top 		= iTop;
		if (m_bmImage.m_hObject)
			rcBtn.bottom	= rcBtn.top + m_sizeBtn.cy + 8;
		else
			rcBtn.bottom	= rcBtn.top + m_sizeBtn.cy;
		iLeft 			= rect.left + 2;
		for (int j = 0; j < m_sizeGrid.cx; j++)
		{
	    	rcBtn.left	= iLeft;
			iItem 		= (i * m_sizeGrid.cx) + j; 

			if (m_bmImage.m_hObject)
			{			           
				rcBtn.right = rcBtn.left + m_sizeBtn.cx + 8;
				if (iItem < m_iNbImages)
				{
					CPoint ptCenter(rcBtn.left + (rcBtn.Width() / 2), rcBtn.top + (rcBtn.Height() / 2));
					CPoint ptOffSet(ptCenter.x - (m_sizeBtn.cx / 2), ptCenter.y - (m_sizeBtn.cy / 2));

					CDC tmpDC;
					tmpDC.CreateCompatibleDC(&dc);
					CBitmap * pOldBitmap = tmpDC.SelectObject(&m_bmImage);
					memDC.BitBlt(ptOffSet.x, ptOffSet.y, m_sizeBtn.cx, m_sizeBtn.cy,
							&tmpDC, iItem * m_sizeBtn.cx, 0, SRCCOPY);
					tmpDC.SelectObject(pOldBitmap);
					Draw3dRect(&memDC, &rcBtn, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT)); 
				}
            }
            else
            {
				rcBtn.right = rcBtn.left + m_sizeBtn.cx;
				Draw3dRect(&memDC, &rcBtn, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT)); 
				CBrush brRect(GetColor(iItem));
				memDC.FillRect(CRect(rcBtn.left + 1, rcBtn.top + 1, rcBtn.right-1, rcBtn.bottom-1), &brRect);
				brRect.DeleteObject();
			}
			if (iItem == m_iSelectedItem)
				memDC.FrameRect(CRect(rcBtn.left-1, rcBtn.top-1, rcBtn.right+1, rcBtn.bottom+1), &brBlack);
			iLeft = rcBtn.right + 1;
		}
		iTop = rcBtn.bottom + 1;
	}

	if (m_lstTextItems.GetSize() > 0)
	{                  
		CRect rcText(rect.left + 2, iTop, rect.right - 2, rect.bottom - 2);
		CBrush brWhite(RGB(255, 255, 255));
		memDC.FillRect(rcText, &brWhite);
		Draw3dRect(&memDC, &rcText, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT)); 
		brWhite.DeleteObject();
        if (m_iSelectedItem != -1)
        {   
        	CFont * pOldFont = memDC.SelectObject(&m_font);
			memDC.DrawText(m_lstTextItems[m_iSelectedItem], -1, rcText, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        	memDC.SelectObject(pOldFont);
		}
	}

	dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, rect.left, rect.top, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	brBack.DeleteObject();
	brBlack.DeleteObject();
	bitmap.DeleteObject();
}

void CWndCombo::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);

	POINT pt;	
	GetCursorPos(&pt);
	CRect rect;
	m_pParent->GetWindowRect(rect);
	if (!rect.PtInRect(pt))
	{
		ShowWindow(SW_HIDE);
	    CButtonCombo * pBtnColor = (CButtonCombo*)m_pParent;
	    pBtnColor->UnpressRightButton();
	}
}

COLORREF CWndCombo::GetColor(int iIndex)
{
	const int  NUMENTRIES = 255;
	PALETTEENTRY palette[NUMENTRIES];       	
	HDC hDC = ::GetDC(NULL);

	UINT uResult = GetSystemPaletteEntries(hDC, 0, NUMENTRIES, palette);        
	::ReleaseDC(NULL, hDC);
	return RGB(palette[iIndex].peRed, palette[iIndex].peGreen, palette[iIndex].peBlue);
}	

