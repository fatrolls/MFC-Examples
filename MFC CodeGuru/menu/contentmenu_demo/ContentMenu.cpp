// ContentMenu.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ContentMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContentMenu

CContentMenu::CContentMenu()
{
    m_bLBDown   = false;
    m_bHilight  = true;
}

CContentMenu::~CContentMenu()
{
}


BEGIN_MESSAGE_MAP(CContentMenu, CListBox)
	//{{AFX_MSG_MAP(CContentMenu)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContentMenu message handlers
#define ITEM_HEIGHT   85
void CContentMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = ITEM_HEIGHT;
}



void CContentMenu::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
    CDC*            pDC = CDC::FromHandle(lpDIS->hDC);
    CRect           rcItem(lpDIS->rcItem);
    CRect           rClient(rcItem);
    CRect           rText;
    CPoint          Pt(((rcItem.Width() - 32) /2 ), rcItem.top + 15);
    pCONTENT_ITEMS  pContents    = &m_pContents[lpDIS->itemID];
    HICON           hIcon = AfxGetApp()->LoadIcon(pContents->nImageID);


    rClient.DeflateRect(5,10);
	rcItem.CopyRect(rClient);
    rText.CopyRect(rClient);
    rText.top += 35;

    pDC->SetBkMode(TRANSPARENT);


	if (lpDIS->itemAction & ODA_DRAWENTIRE)
    {
        pDC->DrawIcon(Pt, hIcon);
        pDC->DrawText(pContents->strText, rText, DT_CENTER|DT_WORDBREAK);
    }

    if  (m_bLBDown)
    {
        Pt.x += 2;
        Pt.y += 2;
        rcItem.OffsetRect(2,2);
        rText.OffsetRect(2,2);
    }

	if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
    {
        if  (m_bHilight)
        {
            pDC->FillSolidRect(rClient,GetSysColor(COLOR_BTNFACE));

            if  (m_bLBDown)
                pDC->Draw3dRect(rClient,GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT));
            else
                pDC->Draw3dRect(rClient,GetSysColor(COLOR_BTNHIGHLIGHT),GetSysColor(COLOR_3DSHADOW));

        }

        pDC->DrawIcon(Pt, hIcon);
        pDC->DrawText(pContents->strText, rText, DT_CENTER|DT_WORDBREAK);
    }

	if (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT))
    {
        pDC->FillSolidRect(rClient,GetSysColor(COLOR_WINDOW));
        pDC->DrawIcon(Pt, hIcon);
        pDC->DrawText(pContents->strText, rText, DT_CENTER|DT_WORDBREAK);
    }

    
}


void CContentMenu::OnMouseMove(UINT nFlags, CPoint point) 
{

    m_Point  = point;

    SetTimer(1,50,NULL);

	CListBox::OnMouseMove(nFlags, point);
}

void CContentMenu::OnLButtonDown(UINT nFlags, CPoint point) 
{
    m_bLBDown	= true;
    SetCurSel(GetCurSel());
	
	CListBox::OnLButtonDown(nFlags, point);
}

void CContentMenu::OnLButtonUp(UINT nFlags, CPoint point) 
{
    m_bLBDown	= false;
    SetCurSel(GetCurSel());
	CListBox::OnLButtonUp(nFlags, point);
}


void CContentMenu::OnTimer(UINT nIDEvent)
{
    BOOL        bOutSide;
    CRect       rItem;
	CPoint      CurPt;
	CRect       rWindow;
    int         nIndex;

    GetWindowRect(rWindow);
    GetCursorPos(&CurPt);

    if  (!rWindow.PtInRect(CurPt))
    {
        if  (!m_bLBDown)
        {
            SetCurSel(-1);
            m_bHilight = false;
        }

        KillTimer(1);
        return;
    }

    m_bHilight = true;
    nIndex = ItemFromPoint(m_Point, bOutSide);

    if  (nIndex != GetCurSel() && !bOutSide)
        SetCurSel(nIndex);
}
