/*
 * CTabbed.cpp		1.0  01/01/2006
 *
 * Copyright 2006 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. 
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 *  ----------------------
 * 
 *   Frames Wrapper functions
 *
 *****/


#include "stdafx.h"
#include "resource1.h"


CTabbed::CTabbed(void)
{
	m_nDif=0;
	m_cfontNormal.CreateFont(14,0,0,0,400,0,0,0,0,1,2,1,34,"MS Sans Serif");
	m_cfontBold.CreateFont(14,0,0,0,700,0,0,0,0,1,2,1,34,"MS Sans Serif");
	m_count=0;
	m_doc=1;
}

CTabbed::~CTabbed(void)
{
	m_cfontNormal.m_hFont=NULL;
	m_cfontBold.m_hFont=NULL;
}

void CTabbed::SetExtileExt(ExtTab m_ext)
{
	m_ExtTab=m_ext;
	m_toolBtn[0].ShowWindow(SW_SHOW);
	m_toolBtn[1].ShowWindow(SW_SHOW);
	m_toolBtnC.ShowWindow(SW_SHOW);
	
}

void  CTabbed::AddNewtab(CWin* pParent,UINT nID, LPCSTR LpTitle)
{
	if (LpTitle == NULL)
	{
		char	szTemp[250];
		sprintf(szTemp," Untitled%i",m_doc);
		SetWindowText(szTemp);
		Addtab(pParent,szTemp);
		m_doc++;
	}
	else
		Addtab(pParent,LpTitle);
	HMENU hMenu=theApp->LoadMenuMDI((LPCTSTR)nID);	
	::SetMenu(theApp->m_WinMain->GetSafeHwnd(),hMenu);
	theApp->m_WinMain->cSpawn.RemapMenu(hMenu);
	theApp->m_WinMain->DrawMenuBar();

}

BOOL CTabbed::OnEraseBkgnd(HDC hDC) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Numtabs == 0)
	{
		CGDI pDC(hDC);
		CBrush cbr;
		cbr.CreateSysColorBrush(COLOR_BTNSHADOW);
		CRect m_rect;
		GetClientRect(m_rect);
		m_rect.top-=22;
		pDC.FillRect(m_rect,&cbr);
		cbr.DeleteObject();
		pDC.DeleteDC();
		
	}
	return TRUE;
}



void CTabbed::Drawtabs(CGDI* dc)
{
	
	if (m_Numtabs == 0)
	{
		m_toolBtnC.ShowWindow(FALSE);
		m_toolBtn[0].ShowWindow(FALSE);
		m_toolBtn[1].ShowWindow(FALSE);

		CBrush cbr;
		cbr.CreateSysColorBrush(COLOR_BTNSHADOW);
		CRect m_rect;
		GetClientRect(m_rect);
		dc->FillRect(m_rect,&cbr);
		cbr.DeleteObject();
		return;
	}
	else
	{
		m_toolBtnC.ShowWindow(TRUE);
		m_toolBtn[0].ShowWindow(TRUE);
		m_toolBtn[1].ShowWindow(TRUE);
		CBrush cbr;
		cbr.CreateSysColorBrush(COLOR_BTNFACE);
		CRect m_rect;
		GetClientRect(m_rect);
		dc->FillRect(m_rect,&cbr);
		cbr.DeleteObject();
	}
	int m_StrPos=0;
	BOOL m_ViewAlltab=TRUE;
	CRect m_rClient;
	CBrush cbr;
	CPen Dark;

	Dark.CreatePen(PS_SOLID,1,CDrawLayer::GetRGBColorShadow());
	CRect rectText;
	HFONT m_fontOld=dc->SelectFont(m_cfontNormal);
	HFONT m_fontOldBold;
	HPEN hPen=dc->SelectObject(&Dark);
	CRect m_rcTabMain;	
	CSize mszBtn=GetSizeButton();
	int m_iSizeButton=mszBtn.cx;
	
	m_rectTab.DeflateRect(1,1);
	m_rectTab.bottom+=1;
	
	
	CRect rectT=m_rectTab;
	rectT.right-=m_iSizeButton+2;
	int mSizeTotal=m_iMinValRec;
	m_toolBtn[0].EnableWindow(FALSE);
	m_toolBtn[1].EnableWindow(FALSE);
	if (mSizeTotal > m_rectTab.Width())
	{
		
		m_toolBtn[1].EnableWindow(TRUE);
		if (m_nDif < 0) 
			m_toolBtn[0].EnableWindow(TRUE);
		if((mSizeTotal-(abs(m_nDif)-20)) < m_rectTab.Width())
			m_toolBtn[1].EnableWindow(FALSE);
	}
	else
		m_nDif=0;
	
	CRect rectScroll; 
	int m_right=m_nDif;
	for ( int iCont=0; iCont< m_Numtabs;iCont++)
	{	

		CRect mrt;
		mrt=((CTab*)m_pArray[iCont])->rect;
		int ancho=mrt.Width();
		mrt.left=m_right;
		mrt.right=mrt.left+ancho;
	
		//si es la carpeta seleccionada, se debe 
		//eliminar las lineas oscuras de encima
		if ((iCont ==m_iSelectTab) || (iCont == 0) )
		{
			
					CRect  m_rectTabAux;
					m_rectTabAux=mrt;
					m_rcTabMain=m_rectTabAux;
					CGradient M(CSize(m_rectTabAux.Width(),m_rectTabAux.Height()));	
					M.PrepareTabs(dc,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
					if (iCont ==m_iSelectTab && iCont != 0)
					{
						M.Draw(dc,m_rectTabAux.left+3,m_rectTabAux.bottom+2,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+4,m_rectTabAux.bottom+1,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-12,m_rectTabAux.bottom,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-11,m_rectTabAux.bottom-1,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-10,m_rectTabAux.bottom-2,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-9,m_rectTabAux.bottom-3,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-8,m_rectTabAux.bottom-4,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-7,m_rectTabAux.bottom-5,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-6,m_rectTabAux.bottom-6,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-5,m_rectTabAux.bottom-7,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-4,m_rectTabAux.bottom-8,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-3,m_rectTabAux.bottom-9,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						
						M.Draw(dc,m_rectTabAux.left-2,m_rectTabAux.bottom-10,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left,m_rectTabAux.top+7,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-1,m_rectTabAux.top+8,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left-2,m_rectTabAux.top+9,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						
						M.Draw(dc,m_rectTabAux.left+2,m_rectTabAux.top+6,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+4,m_rectTabAux.top+5,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+5,m_rectTabAux.top+4,0,0,m_rectTabAux.Width()-2,m_rectTabAux.Height(),SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+6,m_rectTabAux.top+3,0,0,m_rectTabAux.Width()-4,m_rectTabAux.Height(),SRCCOPY);
						
						dc->MoveTo(m_rectTabAux.left-15, m_rectTabAux.bottom+1);
						dc->LineTo(m_rectTabAux.left+2, m_rectTabAux.top+5);

						dc->MoveTo(m_rectTabAux.left+2, m_rectTabAux.top+5);
						dc->LineTo(m_rectTabAux.left+7, m_rectTabAux.top+3);

						dc->MoveTo(m_rectTabAux.left+7, m_rectTabAux.top+3);
						dc->LineTo(m_rectTabAux.right+2, m_rectTabAux.top+3);
					}
					else
					{
						CGradient M(CSize(m_rectTabAux.Width(),m_rectTabAux.Height()));	
						if (iCont !=m_iSelectTab)
							M.PrepareTabs(dc,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBSemiShadow());
						else
						{
							M.PrepareTabs(dc,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
							M.Draw(dc,m_rectTabAux.left+4,m_rectTabAux.bottom+2,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+5,m_rectTabAux.bottom+1,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+6,m_rectTabAux.bottom,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+7,m_rectTabAux.bottom-1,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+8,m_rectTabAux.bottom-2,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+9,m_rectTabAux.bottom-3,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+10,m_rectTabAux.bottom-4,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+11,m_rectTabAux.bottom-5,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+15,m_rectTabAux.bottom-6,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+13,m_rectTabAux.bottom-7,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+14,m_rectTabAux.bottom-8,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+15,m_rectTabAux.bottom-9,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+16,m_rectTabAux.bottom-10,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+17,m_rectTabAux.bottom-11,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+18,m_rectTabAux.bottom-12,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+19,m_rectTabAux.bottom-13,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+20,m_rectTabAux.bottom-14,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+21,m_rectTabAux.bottom-15,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+22,m_rectTabAux.bottom-16,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+23,m_rectTabAux.bottom-17,0,0,m_rectTabAux.Width()-20,m_rectTabAux.Height(),SRCCOPY);
							M.Draw(dc,m_rectTabAux.left+27,m_rectTabAux.bottom-18,0,0,m_rectTabAux.Width()-26,m_rectTabAux.Height(),SRCCOPY);
						}	
						dc->MoveTo(m_rectTabAux.left+3, m_rectTabAux.bottom+1);
						dc->LineTo(m_rectTabAux.left+20, m_rectTabAux.top+5);

						dc->MoveTo(m_rectTabAux.left+20, m_rectTabAux.top+5);
						dc->LineTo(m_rectTabAux.left+27, m_rectTabAux.top+3);

						dc->MoveTo(m_rectTabAux.left+27, m_rectTabAux.top+3);
						dc->LineTo(m_rectTabAux.right+2, m_rectTabAux.top+3);

		
					}
					
					
					
					dc->MoveTo(m_rectTabAux.right+1, m_rectTabAux.top+3);
					dc->LineTo(m_rectTabAux.right+5, m_rectTabAux.top+5);

					dc->MoveTo(m_rectTabAux.right+4, m_rectTabAux.top+5);
					dc->LineTo(m_rectTabAux.right+4, m_rectTabAux.bottom+3);
					
					//linea desde el punto inferior derecho del tab hasta el final del area de tabs
				
					
					dc->MoveTo(m_rectTabAux.right+4, m_rectTabAux.bottom+1);
					dc->LineTo(m_rectTab.right, m_rectTabAux.bottom+1);
					dc->MoveTo(m_rectTab.left, m_rectTabAux.bottom+1);
					dc->LineTo(m_rectTabAux.left-14, m_rectTabAux.bottom+1);
					

		}else{
				CRect  m_rectTabAux=mrt;
				m_rcTabMain=m_rectTabAux;
				//CGradient M(CSize(m_rectTabAux.Width()-4,m_rectTabAux.Height()));	
				//M.PrepareTabs(dc,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorFace());
				//M.Draw(dc,m_rectTabAux.left+6,m_rectTabAux.top+2,0,0,m_rectTabAux.Width(),m_rectTabAux.Height()-2,SRCCOPY);
			
				{
					
						dc->MoveTo(m_rectTabAux.left+4, m_rectTabAux.top+6);
						dc->LineTo(m_rectTabAux.left+8, m_rectTabAux.top+2);
					

					dc->MoveTo(m_rectTabAux.left+8, m_rectTabAux.top+3);
					dc->LineTo(m_rectTabAux.right+1, m_rectTabAux.top+3);
					dc->MoveTo(m_rectTabAux.right+1, m_rectTabAux.top+3);
					dc->LineTo(m_rectTabAux.right+4, m_rectTabAux.top+5);

					dc->MoveTo(m_rectTabAux.right+4, m_rectTabAux.top+5);
					dc->LineTo(m_rectTabAux.right+4, m_rectTabAux.bottom+3);
					
				}
		}
		//---------------------------------------------------
		
		
		
		CRect m_rectTabAux= mrt;
		m_rectTabAux.top+=4;
		m_rectTabAux.left+=4;
		int OldMode=dc->SetBkMode(TRANSPARENT);

		COLORREF clrtext=RGB(0,0,0);
		
		if (iCont !=m_iSelectTab)
		{
			clrtext=dc->SetTextColor(RGB(0,0,0));
	
		}
		if (iCont == m_iSelectTab)
			m_fontOldBold=dc->SelectFont(m_cfontBold);
		CRect rcW;
		rcW=m_rectTabAux;
		rcW.left+=5;
		dc->DrawText(((CTab*)m_pArray[iCont])->lpMsg,m_rectTabAux,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		
		if (iCont == m_iSelectTab)
			dc->SelectFont(m_fontOldBold);

		if (iCont !=m_iSelectTab)
		{
			dc->SetTextColor(clrtext);
			
		}	
		m_right=mrt.right;
		((CTab*)m_pArray[iCont])->rect=mrt;
		dc->SetBkMode(OldMode);
	}


	dc->SelectClipRgn(NULL);

	
	dc->MoveTo(m_rectTab.right-(m_iSizeButton+2), m_rcTabMain.bottom+2);
	dc->LineTo(m_rectTab.right, m_rcTabMain.bottom+2);
	

	CRect rcCli;
	GetClientRect(rcCli);
    rcCli.top=m_rectTab.top;
	rcCli.bottom=m_rectTab.bottom;
	rcCli.left=rcCli.right-(m_iSizeButton);
	int nacum=0;
	for (int i=0; i<3;i++)
	{
		CSize szBtn=m_toolBtn[i].GetSizeButton();
		m_toolBtn[i].MoveWindow(rcCli.left+nacum-1,rcCli.top+2,szBtn.cx,rcCli.Height()+1);
		nacum+=szBtn.cx;
	}
	GetClientRect(rcCli);
	dc->Draw3dRect(rcCli,CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
	m_toolBtnC.EnableWindow(TRUE);
	cbr.DeleteObject();
	Dark.DeleteObject();
	dc->SelectObject(m_fontOld);
	::DeleteObject((HFONT)m_fontOld);
	m_toolBtnC.Invalidate();
    m_toolBtnC.UpdateWindow();
	m_toolBtn[0].Invalidate();
    m_toolBtn[0].UpdateWindow();
	m_toolBtn[1].Invalidate();
    m_toolBtn[1].UpdateWindow();
	
}



void  CTabbed::OnScrollLeft(WPARAM wParam, LPARAM lParam, HWND handle)
{
	m_nDif+=10;
	CClientDC dc(this);
	Drawtabs(&dc);	
	dc.DeleteDC();
	RecalLayout();

	
}

void  CTabbed::OnScrollRight(WPARAM wParam, LPARAM lParam, HWND handle)
{
	m_nDif-=10;
	CClientDC dc(this);
	Drawtabs(&dc);	
	dc.DeleteDC();
	RecalLayout();
	
}

void  CTabbed::OnScrollClose(WPARAM wParam, LPARAM lParam, HWND handle)
{
	CWin* pWnd=GetNumWnd(GetCurtab());
	if (pWnd==NULL)
	{
		return;
	}
	pWnd->SendMessage(WM_CLOSE,0L,0L);
	DeleteTab(GetCurtab());	
	Invalidate();
	UpdateWindow();
	if (GetCount()<=0)
	{
		::SetMenu(theApp->m_WinMain->GetSafeHwnd(),theApp->GetMenuDefault());
		theApp->m_WinMain->DrawMenuBar();
	}
}


int CTabbed::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CContainer::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_img.Create(IDB_GUI_DOCKBAR,9,11,RGB(255,0,255)))
	{
		return -1;
	}


	m_ExtTab=NORMAL_TAB;
	m_toolBtn[0].Create(hWndt,SCROLLLEFT,_T("<"),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0));
	m_toolBtn[0].SetToolTip(_T("Scroll Left"));
	m_toolBtn[0].SethIcon(m_img.ExtractIcon(4));
	m_toolBtn[0].ShowDark(FALSE);
	m_toolBtn[1].Create(hWndt,SCROLLRIGHT,_T(">"),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0));
	m_toolBtn[1].SetToolTip(_T("Scroll Right"));
	m_toolBtn[1].SethIcon(m_img.ExtractIcon(2));
	m_toolBtn[1].ShowDark(FALSE);
	m_toolBtnC.Create(hWndt,SCROLLCLOSE,_T("X"),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0));
	m_toolBtnC.SetToolTip(_T("Close"));
	m_toolBtnC.SethIcon(m_img.ExtractIcon(6));
	m_toolBtnC.ShowDark(FALSE);
	m_toolBtn[0].EnableWindow(FALSE);
	m_toolBtn[1].EnableWindow(FALSE);
	SetALingTabs(CContainer::ALN_TOP); //los tabs arriba
	SetStyle(CContainer::FLAT);	   //no debe acondicionar el tamaño de los tabs		return 0;
	SetTypeTab(CContainer::TYPE_MDI);
	SetActualTitle(FALSE);
	SetCaption();
	return 0;
}

CSize CTabbed::GetSizeButton()
{
	CSize szresult=CSize(0,0);
	for (int i=0; i < 3; i++)
	{
		CSize sztemp=m_toolBtn[i].GetSizeButton();
		szresult.cx+=sztemp.cx;
		szresult.cy+=sztemp.cy;
	}
	return szresult;
}

BOOL CTabbed::OnSysColorChange() 
{
	CContainer::OnSysColorChange();
	m_toolBtn[0].Invalidate();
    m_toolBtn[0].UpdateWindow();	
	m_toolBtn[1].Invalidate();
    m_toolBtn[1].UpdateWindow();
	m_toolBtn[2].Invalidate();
    m_toolBtn[2].UpdateWindow();
	Invalidate ();
	UpdateWindow ();
	return TRUE;
}


