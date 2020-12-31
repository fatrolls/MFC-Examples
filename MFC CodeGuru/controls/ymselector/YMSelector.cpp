// YMSelector.cpp : implementation file
// Control to select year and month
// Designed and developed by Shekar Narayanan
// ShekarNarayanan@Hotmail.com
// 


#include "stdafx.h"
#include "YMSelector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static char *Months[] =
{
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

/////////////////////////////////////////////////////////////////////////////
// CYMPopUp

CYMPopUp::CYMPopUp(CPoint p, CWnd* pParent, int nYear, int nMonth) 
: m_bkBrush(::GetSysColor(COLOR_INFOBK))
{
    if  (-1 == nYear)
        m_nYear     = CTime::GetCurrentTime().GetYear();
    else
        m_nYear     = nYear;

    if  (-1 == nMonth)
        m_nMonth    = CTime::GetCurrentTime().GetMonth() -1;
    else
        m_nMonth    = nMonth -1;

    ASSERT(m_nYear >= START_YEAR && m_nYear <= END_YEAR);
    ASSERT(m_nMonth >= 0   && m_nMonth <= 11 );

    Create(p, pParent);
}


CYMPopUp::~CYMPopUp()
{
    m_bkBrush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CYMPopUp, CWnd)
	//{{AFX_MSG_MAP(CYMPopUp)
	ON_WM_NCDESTROY()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CYMPopUp message handlers


BOOL CYMPopUp::Create(CPoint p, CWnd* pParent)
{
    m_pParent = pParent;
    ASSERT(m_pParent);

    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
                                              0, (HBRUSH)m_bkBrush,0);

    if (!CWnd::CreateEx(0, szClassName, _T(""), WS_VISIBLE|WS_POPUP|WS_BORDER, 
                        p.x, p.y, 250, 200, 
                        pParent->GetSafeHwnd(), 0, NULL))
        return FALSE;

    m_pParent->EnableWindow(false);

    UpdateWindow();


    return TRUE;
}

void CYMPopUp::OnNcDestroy() 
{
	CWnd::OnNcDestroy();
    delete this;
	
	
}


void CYMPopUp::OnPaint() 
{
	CPaintDC    dc(this);
    CString     Buffer;
    CRect       rClient;
    CRect       rCell;
    CRect       rStart;
    CFont       fText;
    CFont*      pfdc;
    short       nCellHeight;
    short       nCellWidth;
    short       nIndex = 0;


    GetClientRect(rClient);
    rClient.DeflateRect(2,2);

    m_rMinus.CopyRect(rClient);
    m_rMinus.right  = m_rMinus.left + 30;
    m_rMinus.bottom = m_rMinus.top + 30;

    m_rPlus.CopyRect(rClient);
    m_rPlus.left    = m_rPlus.right - 30;
    m_rPlus.bottom  = m_rPlus.top + 30;

    m_rYear.CopyRect(rClient);
    m_rYear.left    = m_rMinus.right + 5;
    m_rYear.right   = m_rPlus.left   - 5;
    m_rYear.bottom  = m_rYear.top    + 30;

    fText.DeleteObject();
    fText.CreatePointFont(120,"Times New Roman");
    pfdc = dc.SelectObject(&fText);

    dc.SetBkColor(::GetSysColor(COLOR_INFOBK));
    dc.SetTextColor(::GetSysColor(COLOR_INFOTEXT));

    Buffer.Format("%d", m_nYear);
    dc.DrawText(Buffer, m_rYear, DT_CENTER|DT_VCENTER|DT_SINGLELINE);


    dc.Rectangle(m_rMinus);
    dc.Rectangle(m_rPlus);

    dc.SetBkMode(TRANSPARENT);
    dc.DrawText("<<", m_rMinus, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    dc.DrawText(">>", m_rPlus, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    dc.SetBkMode(OPAQUE);

    dc.SelectObject(pfdc);
    fText.DeleteObject();
    fText.CreatePointFont(80,"MS Sans Serif");
    pfdc = dc.SelectObject(&fText);
    

    nCellHeight     = rClient.Height() / 5;
    nCellWidth      = rClient.Width() / 3;

    rCell.left      = rClient.left;
    rCell.top       = rClient.top + nCellHeight;
    rCell.right     = rCell.left  + nCellWidth;
    rCell.bottom    = rCell.top   + nCellHeight;

    rStart.CopyRect(rCell);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            dc.MoveTo(rCell.left,rCell.top);
            dc.LineTo(rCell.right,rCell.top);
            dc.LineTo(rCell.right,rCell.bottom);

            dc.MoveTo(rCell.left,rCell.top);
            dc.LineTo(rCell.left,rCell.bottom); //

            CRect   rCurSel(rCell);
            rCurSel.DeflateRect(1,1);

            if  ( m_nMonth == nIndex )
            {
                dc.FillSolidRect(rCurSel,::GetSysColor(COLOR_HIGHLIGHT));
                dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
            }
            else
            {
                dc.FillSolidRect(rCurSel,::GetSysColor(COLOR_INFOBK));
                dc.SetTextColor(::GetSysColor(COLOR_INFOTEXT));
            }

            dc.DrawText(Months[nIndex], rCell, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
            m_rCells[nIndex].CopyRect(rCell);

            rCell.OffsetRect(nCellWidth,0);
            nIndex++;
        }

        rStart.OffsetRect(0,nCellHeight);
        rCell.CopyRect(rStart);
    }

    dc.MoveTo(rClient.left, rClient.bottom - 4);
    dc.LineTo(rClient.right, rClient.bottom -4);

    dc.SelectObject(pfdc);
    fText.DeleteObject();

}

void CYMPopUp::OnLButtonDown(UINT nFlags, CPoint point) 
{
    CClientDC   dc(this);
	CWnd::OnLButtonDown(nFlags, point);

    for (int i = 0; i < 12; i++)
    {
        if  (m_rCells[i].PtInRect(point))
        {
            InvalidateRect(m_rCells[m_nMonth]);
            m_nMonth = i;
            InvalidateRect(m_rCells[i]);
            return;
        }
    }

    if  (m_rMinus.PtInRect(point))
        dc.InvertRect(m_rMinus);

    if  (m_rPlus.PtInRect(point))
        dc.InvertRect(m_rPlus);

}

void CYMPopUp::OnLButtonUp(UINT nFlags, CPoint point) 
{
    CClientDC   dc(this);
    CRect       rClient;
    int         nCellHeight;

    if  (m_rMinus.PtInRect(point))
    {
        m_nYear--; if   (m_nYear < START_YEAR)m_nYear = START_YEAR;
        dc.InvertRect(m_rMinus);
        InvalidateRect(m_rYear);
        return;
    }

    if  (m_rPlus.PtInRect(point))
    {
        m_nYear++; if   (m_nYear > END_YEAR)m_nYear = END_YEAR;
        dc.InvertRect(m_rPlus);
        InvalidateRect(m_rYear);
        return;
    }



    GetClientRect(rClient);
    rClient.DeflateRect(2,2);

    nCellHeight     = rClient.Height() / 5;
    rClient.top += nCellHeight;

    if  (rClient.PtInRect(point))
    {
        m_pParent->EnableWindow(true);
        m_pParent->PostMessage(YM_SELECTED, (WPARAM)m_nYear, (LPARAM)m_nMonth);
        DestroyWindow();
    }

}


void CYMPopUp::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
    if (nChar == VK_ESCAPE) 
    {
        m_pParent->EnableWindow(true);
        m_pParent->SendMessage(YM_ABORTED);
        DestroyWindow();
    }
	
}

/////////////////////////////////////////////////////////////////////////////
// CYMSelector

CYMSelector::CYMSelector()
{
    m_nMonth = CTime::GetCurrentTime().GetMonth();
    m_nYear  = CTime::GetCurrentTime().GetYear();
}

CYMSelector::~CYMSelector()
{
}


BEGIN_MESSAGE_MAP(CYMSelector, CButton)
	//{{AFX_MSG_MAP(CYMSelector)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
    ON_MESSAGE(YM_SELECTED, YMSelected)
    ON_MESSAGE(YM_ABORTED,  YMAborted)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYMSelector message handlers

void CYMSelector::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    ASSERT(lpDrawItemStruct);

    CString BtnText;
    CDC*    pDC     = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect   rect    = lpDrawItemStruct->rcItem;
    UINT    state   = lpDrawItemStruct->itemState;
    
    CRect   rArrow(rect);

    rArrow.left    = rArrow.right - 20;

    CSize Margins(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

    pDC->DrawFrameControl(&rArrow, DFC_SCROLL, DFCS_SCROLLDOWN  | 
                          ((state & ODS_SELECTED) ? DFCS_PUSHED : 0) |
                          ((state & ODS_DISABLED) ? DFCS_INACTIVE : 0));


    rect.right -= rArrow.Width();

    pDC->FillSolidRect(rect,::GetSysColor(COLOR_WINDOW));

    GetWindowText(BtnText);
    if  (state & ODS_DISABLED)
        pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
    else
        pDC->SetTextColor(::GetSysColor(COLOR_BTNTEXT));

    pDC->DrawText(BtnText, rect, DT_CENTER|DT_SINGLELINE|DT_VCENTER);

    if (state & ODS_FOCUS) 
    {
        rect.DeflateRect(1,1);
        pDC->DrawFocusRect(rect);
    }

    rect.InflateRect(1,1);
    pDC->DrawEdge(rect,EDGE_BUMP,BF_RECT);

	
}

void CYMSelector::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
    CString buffer;
    CTime   tCurrent = CTime::GetCurrentTime();
    buffer = tCurrent.Format("%B, %Y");
    SetWindowText(buffer);

    m_nYear  = tCurrent.GetYear();
    m_nMonth = tCurrent.GetMonth() - 1;
}

void CYMSelector::OnClicked() 
{
    CRect rect;
    GetWindowRect(rect);
    rect.OffsetRect(0,rect.Height());
    GetParent()->EnableWindow(false);

    new CYMPopUp(CPoint(rect.left,rect.top), this,GetYear(),GetMonth());

    return;

}


LONG CYMSelector::YMSelected(WPARAM wParam , LPARAM lParam )
{
    m_nYear   = (int) wParam;
    m_nMonth  = (int)lParam;

    CString buffer;
    buffer.Format("%s, %d", GetMonthString(), GetYear());
    SetWindowText(buffer);
    GetParent()->EnableWindow(true);
    GetParent()->SetFocus();

    return 0;
}

LONG CYMSelector::YMAborted(WPARAM wParam , LPARAM lParam )
{
    GetParent()->EnableWindow(true);
    GetParent()->SetFocus();

    return 0;
}

int CYMSelector::GetYear()
{
    return m_nYear;
}

int CYMSelector::GetMonth()
{
    return m_nMonth + 1;
}

LPCTSTR CYMSelector::GetMonthString()
{
    return Months[m_nMonth];
}

void CYMSelector::SetMonth(int m)
{
    m--;
    ASSERT(m >= 0 && m <= 11);
    m_nMonth = m;

    CString buffer;
    buffer.Format("%s, %d", GetMonthString(), GetYear());
    SetWindowText(buffer);
}


void CYMSelector::SetYear(int y)
{

    ASSERT( y >= START_YEAR && y <= END_YEAR);
    m_nYear = y;

    CString buffer;
    buffer.Format("%s, %d", GetMonthString(), GetYear());
    SetWindowText(buffer);
}
