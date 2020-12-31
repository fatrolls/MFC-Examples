// TabWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Tab.h"
#include "TabWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabWnd

CTabWnd::CTabWnd()
        : m_selTab(0), m_pFont(NULL), m_pBoldFont(NULL), m_bLock(FALSE)
{
        // cache most used resources
    brushBlack.CreateSolidBrush(RGB(0,0,0));
        brushWhite.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
        brushLGray.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
        brushDGray.CreateSolidBrush(::GetSysColor(COLOR_BTNSHADOW));
        brushText.CreateSolidBrush(::GetSysColor(COLOR_BTNTEXT));
        penBlack.CreatePen(PS_SOLID, 1, (COLORREF)0);
        penL1Gray.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNFACE));
        penL2Gray.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_3DLIGHT));
        penWhite.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNHIGHLIGHT));
        penWhite2.CreatePen(PS_SOLID, 2, ::GetSysColor(COLOR_BTNHIGHLIGHT));
        penDGray.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_BTNSHADOW));
        penDGray2.CreatePen(PS_SOLID, 2, ::GetSysColor(COLOR_BTNSHADOW));
        CreateFont();
}

CTabWnd::~CTabWnd()
{
        while(!m_viewList.IsEmpty())
        {
                TABWND_MEMBER *pMember=m_viewList.RemoveHead();
                delete pMember;
        }
        if (m_pFont) delete m_pFont;
        if (m_pBoldFont) delete m_pBoldFont;
}


BEGIN_MESSAGE_MAP(CTabWnd, CWnd)
        //{{AFX_MSG_MAP(CTabWnd)
        ON_WM_ERASEBKGND()
        ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
        ON_WM_PAINT()
        ON_WM_LBUTTONUP()
        //}}AFX_MSG_MAP
    ON_MESSAGE(WM_TABRESIZE, OnTabResize)
END_MESSAGE_MAP()

BOOL CTabWnd::Create(DWORD dwStyle, CWnd* pParentWnd, UINT nID)
{
        CRect rect, parent;
        ASSERT(pParentWnd);
    if (!CWnd::Create(NULL, "SealiteTabWnd", WS_CHILD|WS_VISIBLE, rect, pParentWnd, nID, NULL))
        return FALSE;

    m_dwStyle=dwStyle;
    PostMessage(WM_TABRESIZE);
    return TRUE;
}

BOOL CTabWnd::CreateView(LPCTSTR lpszLabel, CRuntimeClass * pViewClass, CCreateContext *pContext)
{
        CRect rect, client;
        ASSERT(pViewClass && pContext);

        CWnd *pWnd=(CWnd *)pViewClass->CreateObject();
        if (!pWnd) return FALSE;
        GetClientRect(&client);
        rect.left=2;
        rect.top=TABWND_HEIGHT+2;
        rect.right=client.right-2;
        rect.bottom=client.bottom-2;
        int dwStyle=AFX_WS_DEFAULT_VIEW;
        dwStyle&=~WS_BORDER;

        if (!pWnd->Create(NULL, NULL, dwStyle, rect, this, 13576+m_viewList.GetCount(), pContext))
        {
                TRACE0("Warning: couldn't create client area for tab view\n");
                // pWnd will be cleaned up by PostNcDestroy
        return FALSE;
        }

    TABWND_MEMBER *pMember=new TABWND_MEMBER;
        pMember->pWnd=pWnd;
        strcpy(pMember->szLabel, lpszLabel);
        m_viewList.AddTail(pMember);

        if (m_viewList.GetCount()!=1)
        {
                pWnd->EnableWindow(FALSE);
                pWnd->ShowWindow(SW_HIDE);
    } else
    {
        ((CFrameWnd *)GetParent())->SetActiveView((CView *)pWnd);
    }

        return TRUE;
}


void CTabWnd::CreateFont()
{

        LOGFONT logfont;

        memset( &logfont, 0, sizeof( LOGFONT ) );
        logfont.lfHeight = 12;
        strcpy(logfont.lfFaceName,"MS Sans Serif");
        m_pFont = new CFont();
    VERIFY(m_pFont->CreateFontIndirect(&logfont));

        memset( &logfont, 0, sizeof( LOGFONT ) );
        logfont.lfHeight = 12;
        strcpy(logfont.lfFaceName,"MS Sans Serif");
        m_pBoldFont = new CFont();
    VERIFY(m_pBoldFont->CreateFontIndirect(&logfont));
}

// draws a selected tab and returns its height
int CTabWnd::DrawSelTab(CDC *pDC, int x, LPCTSTR szText)
{
        pDC->SelectObject(m_pBoldFont);
        CSize textSize=pDC->GetTextExtent(szText, strlen(szText));
        int y=TABWND_HEIGHT-TABSEL_HEIGHT-TAB_DEPL;

        // black border, no bottom line
        pDC->SelectObject(&penBlack);
        pDC->MoveTo(x,y+TABSEL_HEIGHT-1);
        pDC->LineTo(x,y);
        pDC->LineTo(x+textSize.cx+TAB_SPACE-1, y);
        pDC->LineTo(x+textSize.cx+TAB_SPACE-1, y+TABSEL_HEIGHT);

        // left and upper border in white, double line
        pDC->SelectObject(&penWhite2);
        pDC->MoveTo(x+2,y+TABSEL_HEIGHT-1);
        pDC->LineTo(x+2,y+2);
        pDC->LineTo(x+textSize.cx+TAB_SPACE-4, y+2);

        // right border, dark gray, duble line
        pDC->SelectObject(&penDGray2);
        pDC->MoveTo(x+textSize.cx+TAB_SPACE-2, y+2);
        pDC->LineTo(x+textSize.cx+TAB_SPACE-2, y+TABSEL_HEIGHT-1);

        // clean up
        pDC->SelectObject(&penL1Gray);
        pDC->MoveTo(x-1, y+TABSEL_HEIGHT);
        pDC->LineTo(x+textSize.cx+TAB_SPACE, y+TABSEL_HEIGHT);
        pDC->MoveTo(x-1, y+TABSEL_HEIGHT+1);
        pDC->LineTo(x+textSize.cx+TAB_SPACE, y+TABSEL_HEIGHT+1);

        CRect client;
        GetClientRect(&client);

        // a black line to far left and right
        pDC->SelectObject(&penBlack);
        pDC->MoveTo(0, y+TABSEL_HEIGHT-1);
        pDC->LineTo(x, y+TABSEL_HEIGHT-1);
        pDC->MoveTo(x+textSize.cx+TAB_SPACE+1, y+TABSEL_HEIGHT-1);
        pDC->LineTo(client.right, y+TABSEL_HEIGHT-1);

        // and a white double line
        pDC->SelectObject(&penWhite2);
        if (x!=0)
        {
                pDC->MoveTo(0, y+TABSEL_HEIGHT+1);
                pDC->LineTo(x, y+TABSEL_HEIGHT+1);
        }
        pDC->MoveTo(x+textSize.cx+TAB_SPACE, y+TABSEL_HEIGHT+1);
        pDC->LineTo(client.right, y+TABSEL_HEIGHT+1);

        // gray inside
        pDC->FillSolidRect(x+3, y+3,textSize.cx+TAB_SPACE-6, TABSEL_HEIGHT, GetSysColor(COLOR_BTNFACE));


        // the text
        pDC->SetBkMode(TRANSPARENT);
        pDC->TextOut(x+TAB_SPACE/2, y+(TAB_HEIGHT-textSize.cy)/2+1, szText, strlen(szText));

        return textSize.cx+TAB_SPACE;
}

// draws an unselected tab and returs its height
int CTabWnd::DrawTab(CDC *pDC, int x, LPCTSTR szText)
{
        pDC->SelectObject(m_pFont);
        CSize textSize=pDC->GetTextExtent(szText, strlen(szText));
        int y=TABWND_HEIGHT-TAB_HEIGHT-TAB_DEPL;
        // black border
        pDC->FrameRect(&CRect(CPoint(x, y), CSize(textSize.cx+TAB_SPACE, TAB_HEIGHT)), &brushBlack);

        pDC->SelectObject(&penWhite);
        pDC->MoveTo(x+1, y+1);
        pDC->LineTo(x+1, y+TAB_HEIGHT-1);
        pDC->MoveTo(x+1, y+1);
        pDC->LineTo(x+textSize.cx+TAB_SPACE-2, y+1);

        pDC->SelectObject(&penDGray);
        pDC->MoveTo(x+textSize.cx+TAB_SPACE-2, y+1);
        pDC->LineTo(x+textSize.cx+TAB_SPACE-2, y+TAB_HEIGHT-1);

        pDC->FillRect(&CRect(CPoint(x+2, y+2), CSize(textSize.cx+TAB_SPACE-4, TAB_HEIGHT-3)), &brushLGray);

        // clean up
        int dy=TABSEL_HEIGHT-TAB_HEIGHT;
        pDC->FillSolidRect(x, y-dy, textSize.cx+TAB_SPACE, dy, GetSysColor(COLOR_BTNFACE));

        // the text
        pDC->SetBkMode(TRANSPARENT);
        pDC->TextOut(x+TAB_SPACE/2, y+(TAB_HEIGHT-textSize.cy)/2, szText, strlen(szText));
        return textSize.cx+TAB_SPACE;
}


int CTabWnd::HitTest(int x, int y)
{
        int count=m_viewList.GetCount();
        int notsel_y_min=TABWND_HEIGHT-TAB_HEIGHT-TAB_DEPL;
        int sel_y_min=TABWND_HEIGHT-TABSEL_HEIGHT-TAB_DEPL;
        int y_max=TABWND_HEIGHT-TAB_DEPL;

        POSITION pos=m_viewList.GetHeadPosition();
        for (int i=0; i<count; i++, m_viewList.GetNext(pos))
        {
                TABWND_MEMBER *pMember=m_viewList.GetAt(pos);
                ASSERT(pMember);

                if (i!=m_selTab && (y<notsel_y_min || y>y_max)) continue;
                if (i==m_selTab && (y<sel_y_min || y>y_max)) continue;

                if (x>=pMember->x_min && x<=pMember->x_max)
                        return i;

        }
        return -1;
}

/////////////////////////////////////////////////////////////////////////////
// CTabWnd message handlers

BOOL CTabWnd::OnEraseBkgnd(CDC* pDC)
{
        RECT rect;
        GetClientRect(&rect);
        pDC->FillSolidRect(&CRect(0, 0, rect.right, TABWND_HEIGHT), ::GetSysColor(COLOR_BTNFACE));
        return TRUE;
}

LRESULT CTabWnd::OnSizeParent(WPARAM, LPARAM lParam)
{
    if (m_bLock) return 0;
    PostMessage(WM_TABRESIZE);
    return 0;
}


void CTabWnd::OnPaint()
{
        CPaintDC dc(this); // device context for painting
        CFont *oldFont;
        CBrush *oldBrush;
        CPen *oldPen;
        int x=0;
        CRect client;

        GetClientRect(&client);

#if 0
        WINDOWPLACEMENT wp;

    // draw a line under the toolbar if the window is maximized
        GetParent()->GetWindowPlacement(&wp);
        if (wp.showCmd==SW_SHOWMAXIMIZED)
#endif
        dc.DrawEdge(&CRect(0,0,client.right,1), EDGE_ETCHED, BF_TOP);


        // client edge
        dc.Draw3dRect(0,TABWND_HEIGHT, client.right, client.bottom-TABWND_HEIGHT,
                GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT));
        dc.Draw3dRect(1,TABWND_HEIGHT+1, client.right-2, client.bottom-TABWND_HEIGHT-2,
                0, GetSysColor(COLOR_3DLIGHT));

        oldFont=dc.SelectObject(m_pFont);
        oldBrush=dc.SelectObject(&brushText);
        oldPen=dc.SelectObject(&penBlack);
        int count=m_viewList.GetCount();
        POSITION pos=m_viewList.GetHeadPosition();
        for (int i=0; i<count; i++, m_viewList.GetNext(pos))
        {
                TABWND_MEMBER *pMember=m_viewList.GetAt(pos);
                ASSERT(pMember);
                pMember->x_min=x;
                if (i!=m_selTab)
                        x+=DrawTab(&dc, x, pMember->szLabel);
                else
                        x+=DrawSelTab(&dc, x, pMember->szLabel);
                pMember->x_max=x;
        }
        dc.SelectObject(oldPen);
        dc.SelectObject(oldBrush);
        dc.SelectObject(oldFont);
}


void CTabWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
    int nNewTab=HitTest(point.x, point.y);

    SwitchView(nNewTab);
    CWnd::OnLButtonUp(nFlags, point);
}


LRESULT CTabWnd::OnTabResize(WPARAM, LPARAM)
{
    CWnd *pParent=(CWnd *)GetParent();
    CRect rect(0,0,32000,32000);
    ASSERT(pParent);

    m_bLock=TRUE; // reentrancy check (might get called recursivly from OnSize)
    pParent->RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, CWnd::reposQuery, &rect, NULL);

    MoveWindow(rect.left,rect.top,rect.Width(),rect.Height());

    CWnd *pWnd;
    for (POSITION pos=m_viewList.GetHeadPosition(); pos; m_viewList.GetNext(pos))
    {
         pWnd=m_viewList.GetAt(pos)->pWnd;
         pWnd->MoveWindow(2, TABWND_HEIGHT+2, rect.Width()-4, rect.Height()-TABWND_HEIGHT-4);
    }

    m_bLock=FALSE;
    return 0;
}

int CTabWnd::GetTabLength()
{
    int count=m_viewList.GetCount();
    POSITION pos=m_viewList.GetHeadPosition();
    int len=0;

        for (int i=0; i<count; i++, m_viewList.GetNext(pos))
        {
                TABWND_MEMBER *pMember=m_viewList.GetAt(pos);
                ASSERT(pMember);
        len+=pMember->x_max-pMember->x_min;
    }
    return len;
}

void CTabWnd::SwitchView(int nNewTab)
{
        if (nNewTab!=-1 && nNewTab!=m_selTab)
        {
        TABWND_MEMBER *newMember=m_viewList.GetAt(m_viewList.FindIndex(nNewTab));
        TABWND_MEMBER *oldMember=NULL;

        if (m_selTab!=-1)
        {
            oldMember=m_viewList.GetAt(m_viewList.FindIndex(m_selTab));
            oldMember->pWnd->EnableWindow(FALSE);
            oldMember->pWnd->ShowWindow(SW_HIDE);
            oldMember->pWnd->SendMessage(WM_TABCHANGED, 0, (LPARAM)newMember->pWnd);
        }
        newMember->pWnd->EnableWindow(TRUE);
        newMember->pWnd->ShowWindow(SW_SHOW);
        newMember->pWnd->SetFocus();
        ((CFrameWnd *)GetParent())->SetActiveView((CView *)newMember->pWnd);
        newMember->pWnd->SendMessage(WM_TABCHANGED, 1, (LPARAM)oldMember->pWnd);
        m_selTab=nNewTab;
        InvalidateRect(&CRect(0, 0, 32000, TABWND_HEIGHT), FALSE);
    }
}
