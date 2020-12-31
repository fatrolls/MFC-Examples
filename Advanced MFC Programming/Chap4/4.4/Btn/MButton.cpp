#include "StdAfx.h"
#include "MButton.h"

IMPLEMENT_DYNAMIC(MCButton, CButton)
BEGIN_MESSAGE_MAP(MCButton, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void MCButton::OnPaint()
{
	UINT id=GetDlgCtrlID();
	if(GetButtonStyle() & BS_AUTOCHECKBOX)
	{
		CClientDC dc(this);
		DRAWITEMSTRUCT dis;

//		dis.CtlType=ODT_BUTTON;
		dis.CtlID=GetDlgCtrlID();
/*		dis.itemID=0;
		dis.itemAction=ODA_DRAWENTIRE;
		dis.itemState=ODS_DEFAULT;
		dis.hwndItem=GetSafeHwnd();
		dis.hDC=dc.GetSafeHdc();
		GetClientRect(&dis.rcItem);
		dis.itemData=0;
		DrawItem(&dis);*/
		dc.TextOut(0, 0, "Test");
	}
	else CButton::OnPaint();
}

IMPLEMENT_DYNAMIC(MCBitmapButton, CBitmapButton)
BEGIN_MESSAGE_MAP(MCBitmapButton, CBitmapButton)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

MCBitmapButton::MCBitmapButton():CBitmapButton()
{
	m_bCheck=FALSE;
}

void MCBitmapButton::OnPaint()
{
	UINT uStyle;

	uStyle=GetButtonStyle();
//	if((uStyle == BS_AUTOCHECKBOX) || (uStyle == BS_CHECKBOX))
	if(m_bCheck)
	{
		CClientDC dc(this);
		DRAWITEMSTRUCT dis;

		dis.CtlType=ODT_BUTTON;
		dis.CtlID=GetDlgCtrlID();
		dis.itemID=0;
		dis.itemAction=ODA_DRAWENTIRE;
		if(GetCheck() == TRUE)
		{
			dis.itemState=ODS_SELECTED;
		}
		else
		{
			dis.itemState=0;
		}
		dis.hwndItem=GetSafeHwnd();
		dis.hDC=dc.GetSafeHdc();
		GetClientRect(&dis.rcItem);
		dis.itemData=0;
		DrawItem(&dis);
		//SendMessage(WM_DRAWITEM, dis.CtlID, (LPARAM)&dis);
		//dc.TextOut(0, 0, "Test");
	}
	else CButton::OnPaint();
}

BOOL MCBitmapButton::LoadBitmaps
(
	LPCTSTR lpszBitmapResource,
	LPCTSTR lpszBitmapResourceSel,
	LPCTSTR lpszBitmapResourceFocus,
	LPCTSTR lpszBitmapResourceDisabled,
	LPCTSTR lpszBitmapResourceMask
)
{
	BOOL bAllLoaded;

	m_bitmapMask.DeleteObject();
	if
	(
		CBitmapButton::LoadBitmaps
		(
			lpszBitmapResource,
			lpszBitmapResourceSel,
			lpszBitmapResourceFocus,
			lpszBitmapResourceDisabled
		) == FALSE
	)return FALSE;
	if(lpszBitmapResourceMask != NULL)
	{
		if(!m_bitmapMask.LoadBitmap(lpszBitmapResourceMask))
		{
			TRACE0("Failed to load bitmap for normal background image.\n");
			bAllLoaded=FALSE;
		}
	}
	return bAllLoaded;
}

BOOL MCBitmapButton::LoadBitmaps
(
	UINT nIDBitmapResource,
	UINT nIDBitmapResourceSel,
	UINT nIDBitmapResourceFocus,
	UINT nIDBitmapResourceDisabled,
	UINT nIDBitmapResourceMask
)
{
	BOOL bAllLoaded;

	m_bitmapMask.DeleteObject();
	if
	(
		CBitmapButton::LoadBitmaps
		(
			nIDBitmapResource,
			nIDBitmapResourceSel,
			nIDBitmapResourceFocus,
			nIDBitmapResourceDisabled
		) == FALSE
	)return FALSE;
	if(nIDBitmapResourceMask != 0)
	{
		if(!m_bitmapMask.LoadBitmap(nIDBitmapResourceMask))
		{
			TRACE0("Failed to load bitmap for normal background image.\n");
			bAllLoaded=FALSE;
		}
	}
	return bAllLoaded;
}

BOOL MCBitmapButton::AutoLoad(UINT nID, CWnd* pParent)
{
	CString buttonName;

	if(!SubclassDlgItem(nID, pParent))return FALSE;
	GetWindowText(buttonName);
	ASSERT(!buttonName.IsEmpty());
	LoadBitmaps
	(
		buttonName + _T("U"),
		buttonName + _T("D"),
		buttonName + _T("F"),
		buttonName + _T("X"),
		buttonName + _T("M")
	);
	if(m_bitmap.m_hObject == NULL)return FALSE;
	SizeToContent();
	return TRUE;
}

void MCBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CBitmap *pBitmap;
	CBitmap *pBitmapMask;
	CBitmap *pOld;
	CBitmap *pOldMask;
	CBitmap *pOldImage;
	CBitmap bmpImage;
	BITMAP bm;
	UINT state;
	CDC *pDC;
	CDC memDC;
	CDC memDCMask;
	CDC memDCImage;
	CRect rect;

	ASSERT(lpDIS != NULL);
	ASSERT(m_bitmap.m_hObject != NULL);
	pBitmap=&m_bitmap;
	if(m_bitmapMask.m_hObject != NULL)
	{
		pBitmapMask=&m_bitmapMask;
	}
	else pBitmapMask=NULL;
	state=lpDIS->itemState;
	if
	(
		(state & ODS_SELECTED) && 
		(m_bitmapSel.m_hObject != NULL)
	)
	{
		pBitmap=&m_bitmapSel;
	}
	else if
	(
		(state & ODS_FOCUS) && 
		(m_bitmapFocus.m_hObject != NULL)
	)
	{
		pBitmap=&m_bitmapFocus;
	}
	else if
	(
		(state & ODS_DISABLED) && 
		(m_bitmapDisabled.m_hObject != NULL)
	)
	{
		pBitmap=&m_bitmapDisabled;
	}
	pDC=CDC::FromHandle(lpDIS->hDC);
	memDC.CreateCompatibleDC(pDC);
	if(pBitmapMask != NULL)
	{
		memDCMask.CreateCompatibleDC(pDC);
		memDCImage.CreateCompatibleDC(pDC);
	}
	pOld=memDC.SelectObject(pBitmap);
	if(pOld == NULL)return;
	if(pBitmapMask != NULL)
	{
		pOldMask=memDCMask.SelectObject(pBitmapMask);
		if(pOldMask == NULL)return;
		pBitmap->GetBitmap(&bm);
		bmpImage.CreateCompatibleBitmap(pDC, bm.bmWidth, bm.bmHeight);
		pOldImage=memDCImage.SelectObject(&bmpImage);
		if(pOldImage == NULL)return;
	}
	rect.CopyRect(&lpDIS->rcItem);
	if(pBitmapMask == NULL)
	{
		pDC->BitBlt
		(
			rect.left,
			rect.top,
			rect.Width(),
			rect.Height(),
			&memDC,
			0,
			0,
			SRCINVERT
		);
	}
	else
	{
		memDCImage.BitBlt
		(
			0,
			0,
			rect.Width(),
			rect.Height(),
			pDC,
			rect.left,
			rect.top,
			SRCCOPY
		);
		memDCImage.BitBlt
		(
			0,
			0,
			rect.Width(),
			rect.Height(),
			&memDC,
			0,
			0,
			SRCINVERT
		);
		memDCImage.BitBlt
		(
			0,
			0,
			rect.Width(),
			rect.Height(),
			&memDCMask,
			0,
			0,
			SRCAND
		);
		memDCImage.BitBlt
		(
			0,
			0,
			rect.Width(),
			rect.Height(),
			&memDC,
			0,
			0,
			SRCINVERT
		);
		pDC->BitBlt
		(
			rect.left,
			rect.top,
			rect.Width(),
			rect.Height(),
			&memDCImage,
			0,
			0,
			SRCCOPY
		);
	}
	memDC.SelectObject(pOld);
	if(pBitmapMask != NULL)
	{
		memDCMask.SelectObject(pOldMask);
		memDCImage.SelectObject(pOldImage);
	}
}

void MCBitmapButton::OnMouseMove(UINT nFlags, CPoint point)
{
}

//void MCBitmapButton::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	Invalidate();
//}
