// SkinScrollWnd.cpp : implementation file
// 模块：控件滚动条换肤
//		通过对一个控件的子类化实现滚动条换肤，和CSkinScrollBar配合使用。
//	2006.7.7	黄建雄	创建
//	2007.1.23	黄建雄	调整滚动条的响应
//  2007.6.14	黄建雄  修改一个bug,将调用IsWindowVisible来判断滚动条是否可见改为判断窗口Style
//////////////////////////////////////////////////////////////////////	

#include "stdafx.h"
#include "SkinScrollWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_UPDATE 100
#define UM_DESTMOVE	(WM_USER+100)

static LRESULT CALLBACK
HookWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	CSkinScrollWnd *pSkin=(CSkinScrollWnd*)GetWindowLong(hwnd,GWL_USERDATA);
	if(msg==WM_DESTROY)
	{
		WNDPROC procOld=pSkin->m_funOldProc;
		UnskinWndScroll(CWnd::FromHandle(hwnd));
		return ::CallWindowProc(procOld,hwnd,msg,wp,lp);
	}
	
	LRESULT lr=::CallWindowProc(pSkin->m_funOldProc,hwnd,msg,wp,lp);
	if(pSkin->m_bOp) return lr;
	if(msg==WM_ERASEBKGND)
	{
			SCROLLINFO si;
			DWORD dwStyle=::GetWindowLong(hwnd,GWL_STYLE);
			if(dwStyle&WS_VSCROLL)
			{
				memset(&si,0,sizeof(si));
				si.cbSize=sizeof(si);
				si.fMask=SIF_ALL;
				::GetScrollInfo(hwnd,SB_VERT,&si);
				if(si.nMax!=pSkin->m_sbVert.m_si.nMax 
					||si.nMin!=pSkin->m_sbVert.m_si.nMin
					||si.nPos!=pSkin->m_sbVert.m_si.nPos
					||si.nPage!=pSkin->m_sbVert.m_si.nPage)
				{
					pSkin->m_sbVert.SetScrollInfo(&si,!pSkin->m_bOp);
					pSkin->m_sbVert.EnableWindow(si.nMax>=si.nPage);
				}
			}
			if(dwStyle&WS_HSCROLL)
			{
				memset(&si,0,sizeof(si));
				si.cbSize=sizeof(si);
				si.fMask=SIF_ALL;
				::GetScrollInfo(hwnd,SB_HORZ,&si);
				if(si.nMax!=pSkin->m_sbHorz.m_si.nMax 
					||si.nMin!=pSkin->m_sbHorz.m_si.nMin
					||si.nPos!=pSkin->m_sbHorz.m_si.nPos
					||si.nPage!=pSkin->m_sbHorz.m_si.nPage)
				{
					pSkin->m_sbHorz.SetScrollInfo(&si,!pSkin->m_bOp);
					pSkin->m_sbHorz.EnableWindow(si.nMax>=si.nPage);
				}
			}
	}else if(msg==WM_NCCALCSIZE && wp)
	{
			LPNCCALCSIZE_PARAMS pNcCalcSizeParam=(LPNCCALCSIZE_PARAMS)lp;
			DWORD dwStyle=::GetWindowLong(hwnd,GWL_STYLE);
			DWORD dwExStyle=::GetWindowLong(hwnd,GWL_EXSTYLE);
			BOOL  bLeftScroll=dwExStyle&WS_EX_LEFTSCROLLBAR;
			int nWid=::GetSystemMetrics(SM_CXVSCROLL);
			if(dwStyle&WS_VSCROLL) 
			{
				if(bLeftScroll)
					pNcCalcSizeParam->rgrc[0].left-=nWid-pSkin->m_nScrollWid;
				else
					pNcCalcSizeParam->rgrc[0].right+=nWid-pSkin->m_nScrollWid;
			}
			if(dwStyle&WS_HSCROLL) pNcCalcSizeParam->rgrc[0].bottom+=nWid-pSkin->m_nScrollWid;
			
			RECT rc,rcVert,rcHorz;
			::GetWindowRect(hwnd,&rc);
			::OffsetRect(&rc,-rc.left,-rc.top);
			
			nWid=pSkin->m_nScrollWid;
			if(bLeftScroll)
			{
				int nLeft=pNcCalcSizeParam->rgrc[0].left;
				int nBottom=pNcCalcSizeParam->rgrc[0].bottom;
				rcVert.right=nLeft;
				rcVert.left=nLeft-nWid;
				rcVert.top=0;
				rcVert.bottom=nBottom;
				rcHorz.left=nLeft;
				rcHorz.right=pNcCalcSizeParam->rgrc[0].right;
				rcHorz.top=nBottom;
				rcHorz.bottom=nBottom+nWid;
			}else
			{
				int nRight=pNcCalcSizeParam->rgrc[0].right;
				int nBottom=pNcCalcSizeParam->rgrc[0].bottom;
				rcVert.left=nRight;
				rcVert.right=nRight+nWid;
				rcVert.top=0;
				rcVert.bottom=nBottom;
				rcHorz.left=0;
				rcHorz.right=nRight;
				rcHorz.top=nBottom;
				rcHorz.bottom=nBottom+nWid;
			}
			if(dwStyle&WS_VSCROLL && dwStyle&WS_HSCROLL)
			{
				pSkin->m_nAngleType=bLeftScroll?1:2;
			}else
			{
				pSkin->m_nAngleType=0;
			}
			if(dwStyle&WS_VSCROLL)
			{
				pSkin->m_sbVert.MoveWindow(&rcVert);
				pSkin->m_sbVert.ShowWindow(SW_SHOW);
			}else
			{
				pSkin->m_sbVert.ShowWindow(SW_HIDE);
			}
			if(dwStyle&WS_HSCROLL)
			{
				pSkin->m_sbHorz.MoveWindow(&rcHorz);
				pSkin->m_sbHorz.ShowWindow(SW_SHOW);
			}else
			{
				pSkin->m_sbHorz.ShowWindow(SW_HIDE);
			}
			pSkin->PostMessage(UM_DESTMOVE,dwStyle&WS_VSCROLL,bLeftScroll);
	}
	return lr;
}


extern "C" CSkinScrollWnd* SkinWndScroll(CWnd *pWnd,HBITMAP hBmpScroll)
{
	CSkinScrollWnd *pFrame=new CSkinScrollWnd;
	pFrame->SkinWindow(pWnd,hBmpScroll);
	return pFrame;
}


extern "C" BOOL UnskinWndScroll(CWnd *pWnd)
{
	CSkinScrollWnd *pFrame=(CSkinScrollWnd *)GetWindowLong(pWnd->m_hWnd,GWL_USERDATA);
	if(pFrame) 
	{
		RECT rc;
		CWnd *pParent=pFrame->GetParent();
		pFrame->GetWindowRect(&rc);
		pParent->ScreenToClient(&rc);
		SetWindowLong(pWnd->m_hWnd,GWL_WNDPROC,(LONG)pFrame->m_funOldProc);
		SetWindowLong(pWnd->m_hWnd,GWL_USERDATA,0);
		pWnd->SetParent(pParent);
		pWnd->MoveWindow(&rc);
		pFrame->DestroyWindow();
		delete pFrame;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSkinScrollWnd

CSkinScrollWnd::CSkinScrollWnd()
{
	m_funOldProc=NULL;
	m_bOp=FALSE;
	m_nScrollWid=16;
	m_hBmpScroll=0;
	m_nAngleType=0;
}

CSkinScrollWnd::~CSkinScrollWnd()
{
}


BEGIN_MESSAGE_MAP(CSkinScrollWnd, CWnd)
	//{{AFX_MSG_MAP(CSkinScrollWnd)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_DESTMOVE,OnDestMove)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSkinScrollWnd message handlers


BOOL CSkinScrollWnd::SkinWindow(CWnd *pWnd,HBITMAP hBmpScroll)
{
	ASSERT(m_hWnd==NULL);
	m_hBmpScroll=hBmpScroll;
	BITMAP bm;
	GetObject(hBmpScroll,sizeof(bm),&bm);
	m_nScrollWid=bm.bmWidth/9;

	CWnd *pParent=pWnd->GetParent();
	ASSERT(pParent);
	RECT rcFrm,rcWnd;
	pWnd->GetWindowRect(&rcFrm);
	pParent->ScreenToClient(&rcFrm);
	rcWnd=rcFrm;
	OffsetRect(&rcWnd,-rcWnd.left,-rcWnd.top);
	UINT uID=pWnd->GetDlgCtrlID();
	DWORD dwStyle=pWnd->GetStyle();
	DWORD dwExStyle=pWnd->GetExStyle();
	DWORD dwFrmStyle=WS_CHILD|SS_NOTIFY;
	DWORD dwFrmStyleEx=0;
	if(dwExStyle & WS_EX_TOOLWINDOW)
	{
		dwFrmStyleEx|=WS_EX_TOOLWINDOW;
		dwFrmStyleEx |=WS_EX_TOPMOST;
	}
	if(dwStyle&WS_VISIBLE) dwFrmStyle|=WS_VISIBLE;

	if(dwStyle&WS_BORDER)
	{
		dwFrmStyle|=WS_BORDER;
		pWnd->ModifyStyle(WS_BORDER,0);
		int nBorder=::GetSystemMetrics(SM_CXBORDER);
		rcWnd.right-=nBorder*2;
		rcWnd.bottom-=nBorder*2;
	}
	if(dwExStyle&WS_EX_CLIENTEDGE)
	{
		pWnd->ModifyStyleEx(WS_EX_CLIENTEDGE,0);
		int nBorder=::GetSystemMetrics(SM_CXEDGE);
		rcWnd.right-=nBorder*2;
		rcWnd.bottom-=nBorder*2;
		dwFrmStyleEx|=WS_EX_CLIENTEDGE;
	}
	this->CreateEx(dwFrmStyleEx,AfxRegisterWndClass(NULL),"SkinScrollBarFrame",dwFrmStyle,rcFrm,pParent,uID);

	m_wndLimit.Create(NULL,"LIMIT",WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,200);
	m_sbHorz.Create(WS_CHILD,CRect(0,0,0,0),this,100);
	m_sbVert.Create(WS_CHILD|SBS_VERT,CRect(0,0,0,0),this,101);
	m_sbHorz.SetBitmap(m_hBmpScroll);
	m_sbVert.SetBitmap(m_hBmpScroll);

	pWnd->SetParent(&m_wndLimit);
	SetWindowLong(pWnd->m_hWnd,GWL_USERDATA,(LONG)this);
	m_funOldProc=(WNDPROC)SetWindowLong(pWnd->m_hWnd,GWL_WNDPROC,(LONG)HookWndProc);

	pWnd->MoveWindow(&rcWnd);
	SetTimer(TIMER_UPDATE,500,NULL);
	return TRUE;
}

void CSkinScrollWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	if(cx==0 || cy==0) return;
	if(m_wndLimit.m_hWnd)
	{
		CWnd *pWnd=m_wndLimit.GetWindow(GW_CHILD);
		pWnd->MoveWindow(0,0,cx,cy);
	}
}

void CSkinScrollWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CWnd *pWnd=m_wndLimit.GetWindow(GW_CHILD);
	m_bOp=TRUE;
	pWnd->SendMessage(WM_VSCROLL,MAKELONG(nSBCode,nPos),0);
	m_bOp=FALSE;
	if(nSBCode==SB_THUMBTRACK) return;
	SCROLLINFO si={0};
	si.cbSize=sizeof(si);
	si.fMask=SIF_ALL;
	pWnd->GetScrollInfo(SB_VERT,&si);
	pScrollBar->SetScrollInfo(&si,TRUE);
}

void CSkinScrollWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CWnd *pWnd=m_wndLimit.GetWindow(GW_CHILD);
	m_bOp=TRUE;
	pWnd->SendMessage(WM_HSCROLL,MAKELONG(nSBCode,nPos),0);
	m_bOp=FALSE;
	if(nSBCode==SB_THUMBTRACK) return;
	SCROLLINFO si={0};
	si.cbSize=sizeof(si);
	si.fMask=SIF_ALL;
	pWnd->GetScrollInfo(SB_HORZ,&si);
	pScrollBar->SetScrollInfo(&si,TRUE);
}

void CSkinScrollWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	HGDIOBJ hOldBmp=::SelectObject(memdc,m_hBmpScroll);
	RECT rc;
	GetClientRect(&rc);
	if(m_nAngleType==1)
		dc.BitBlt(rc.left,rc.bottom-m_nScrollWid,m_nScrollWid,m_nScrollWid,&memdc,m_nScrollWid*8,m_nScrollWid*1,SRCCOPY);
	else if(m_nAngleType==2)
		dc.BitBlt(rc.right-m_nScrollWid,rc.bottom-m_nScrollWid,m_nScrollWid,m_nScrollWid,&memdc,m_nScrollWid*8,m_nScrollWid*0,SRCCOPY);
	::SelectObject(memdc,hOldBmp);
}

void CSkinScrollWnd::OnTimer(UINT nIDEvent) 
{
	CWnd *pWnd=m_wndLimit.GetWindow(GW_CHILD);
	SCROLLINFO si1={0};
	si1.cbSize=sizeof(SCROLLINFO);
	si1.fMask=SIF_ALL;
	SCROLLINFO si2={0};
	if(GetWindowLong(m_sbVert.m_hWnd,GWL_STYLE)&WS_VISIBLE && !m_sbVert.m_bDrag)
	{
		pWnd->GetScrollInfo(SB_VERT,&si1);
		m_sbVert.GetScrollInfo(&si2,SIF_ALL);
		if(si1.nMax!=si2.nMax||si1.nMin!=si2.nMin||si1.nPos!=si2.nPos||si1.nPage!=si2.nPage)
			m_sbVert.SetScrollInfo(&si1);
	}
	if(GetWindowLong(m_sbHorz.m_hWnd,GWL_STYLE)&WS_VISIBLE && !m_sbHorz.m_bDrag)
	{
		pWnd->GetScrollInfo(SB_HORZ,&si1);
		m_sbHorz.GetScrollInfo(&si2,SIF_ALL);
		if(si1.nMax!=si2.nMax||si1.nMin!=si2.nMin||si1.nPos!=si2.nPos||si1.nPage!=si2.nPage)
			m_sbHorz.SetScrollInfo(&si1);
	}
}

LRESULT CSkinScrollWnd::OnDestMove(WPARAM wParam, LPARAM lParam)
{
	m_bOp=TRUE;
	BOOL bVScroll=wParam;
	BOOL bLeftScroll=lParam;
	RECT rcClient;
	GetClientRect(&rcClient);
	RECT rcLimit,rcWnd;
	rcWnd=rcClient;
	rcLimit=rcClient;
	if(GetWindowLong(m_sbHorz.m_hWnd,GWL_STYLE)&WS_VISIBLE) rcLimit.bottom-=m_nScrollWid;
	if(bLeftScroll)
	{
		if(bVScroll)
		{
			rcLimit.left+=m_nScrollWid;
			OffsetRect(&rcWnd,-m_nScrollWid,0);
		}
	}else
	{
		if(bVScroll) rcLimit.right-=m_nScrollWid;
	}
	m_wndLimit.MoveWindow(&rcLimit);
	m_wndLimit.GetWindow(GW_CHILD)->SetWindowPos(NULL,rcWnd.left,0,0,0,SWP_NOSIZE|SWP_NOZORDER);
	m_bOp=FALSE;
	return 0;
}
