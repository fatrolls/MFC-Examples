// BeautifulEdit.cpp : implementation file
//

#include "stdafx.h"
#include "BeautifulEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBeautifulEdit

CBeautifulEdit::CBeautifulEdit(CString strTip/* = _T("")*/, UINT nIDBitmap/* = NULL*/)
{
	if(nIDBitmap)
	{
		m_bBkImg = TRUE;
		m_bitmap.LoadBitmap(nIDBitmap);
	}
	else
		m_bBkImg = FALSE;

	m_strTip = strTip;//这个不用判断，没关系的
	m_bIsFocus = FALSE;
	m_bIsEmpty = TRUE;
	m_bIsTxtChangeByUsr = FALSE;
	m_brhWhite.CreateStockObject(WHITE_BRUSH);
	m_brhNull.CreateStockObject(NULL_BRUSH);

	SetColors();
}

CBeautifulEdit::~CBeautifulEdit()
{
}


BEGIN_MESSAGE_MAP(CBeautifulEdit, CEdit)
	//{{AFX_MSG_MAP(CBeautifulEdit)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_CHAR()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeautifulEdit message handlers

//////////////////////////////////////////////////////////////////////////
//						增加资源、设置样式
void CBeautifulEdit::AddBitmap(UINT nIDBitmap)
{
	m_bBkImg = TRUE;
	m_bitmap.LoadBitmap(nIDBitmap);

	if(!m_bIsEmpty)
		Invalidate();
}

void CBeautifulEdit::AddTipString(CString strTip)
{
	m_strTip = strTip;
}

void CBeautifulEdit::SetColors(COLORREF clrText/* = RGB(0, 0, 0)*/, COLORREF 
							   clrTip /*= RGB(180, 180, 180)*/)
{
	m_clrText = clrText;
	m_clrTip = clrTip;
}

//////////////////////////////////////////////////////////////////////////
//							颜色
HBRUSH CBeautifulEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	if(m_bIsEmpty)
		pDC->SetTextColor(m_clrTip);
	else
		pDC->SetTextColor(m_clrText);

	if(m_bBkImg)
		pDC->SetBkMode(TRANSPARENT);
	else
		return m_brhWhite;

	return m_brhNull;
}

/*注意不能用WM_CTLCOLOR！！！*/

//DEL HBRUSH CBeautifulEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
//DEL {
//DEL 	HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);
//DEL 	
//DEL 	// TODO: Change any attributes of the DC here
//DEL 	pDC->SetTextColor(RGB(255, 0, 0));
//DEL 	// TODO: Return a different brush if the default is not desired
//DEL 	return hbr;
//DEL }

//////////////////////////////////////////////////////////////////////////
//							画背景
BOOL CBeautifulEdit::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
 	if(m_bBkImg)
 	{
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = memDC.SelectObject(&m_bitmap);
		BITMAP bmp;
		m_bitmap.GetBitmap(&bmp);

		CRect rc;
		GetClientRect(&rc);
		
		pDC->StretchBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0,
			 bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();
		return TRUE;
	}

	return CEdit::OnEraseBkgnd(pDC);
}

//////////////////////////////////////////////////////////////////////////
//						得失焦点的使背景图像出现或消失

void CBeautifulEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);	
	// TODO: Add your message handler code here
	m_bIsFocus = FALSE;
	if(m_bIsEmpty)
	{
		m_bIsTxtChangeByUsr = FALSE;
		SetWindowText(m_strTip);
	}
}

void CBeautifulEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	// TODO: Add your message handler code here
	Invalidate();

	m_bIsFocus = TRUE;
	if(m_bIsEmpty)
	{
		m_bIsTxtChangeByUsr = FALSE;
		SetWindowText("");
	}
}


void CBeautifulEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	m_bIsTxtChangeByUsr = TRUE;

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CBeautifulEdit::OnChange() 
{
	// TODO: Add your control notification handler code here
	if(m_bIsTxtChangeByUsr)
	{
		Invalidate();
		
		CString strContent;
		GetWindowText(strContent);
		
		if(strContent.IsEmpty())
		{
			m_bIsEmpty = TRUE;
			TRACE("TRUE");
		}
		else
		{
			m_bIsEmpty = FALSE;
			TRACE("FALSE");
		}	
	}

}


