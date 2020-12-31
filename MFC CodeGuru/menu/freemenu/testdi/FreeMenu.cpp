#include "stdafx.h"
#include "MenuItemWnd.h"
#include "FreeMenu.h"

CFreeMenu::CFreeMenu(UINT ID,
		      CPoint beginP,
			  CWnd *ParentWnd,
			  COLORREF BackGroundColor,
			  COLORREF EdgeLUColor,
			  COLORREF EdgeRDColor,
			  COLORREF TextColor,
			  CFont *font,
			  int pflags,
			  CFreeMenu *parentMenu
)

{
	int count;
	m_parentMenu = parentMenu;
	m_Menu = new CMenu;
	m_Menu->LoadMenu(ID);
	count = m_Menu->GetMenuItemCount();
	m_selfWnd = new CMenuItemWnd;
	m_selfWnd->freeMenu = this;
	m_IsVisible = FALSE;

	m_ParentWnd = ParentWnd;
	m_BackGroundColor = BackGroundColor;
	m_EdgeLUColor = EdgeLUColor;
	m_EdgeRDColor = EdgeRDColor;
	m_TextColor = TextColor;
	m_font = font;
	MenuBeginPoint = beginP;
	flags = pflags;
	m_goby = -1;
	m_selected = -1;
	for(int i=0;i<count;i++)
	{
		CMenu *menu = m_Menu->GetSubMenu(i);
		if(menu)
		{
			CRect rect = GetItemRect(m_Menu,i);
			CPoint p;
			if(flags == 1)
			{
				p.x = rect.left;
				p.y = rect.bottom+1;
			}
			else
			{
				p.x = rect.right + 1;
				p.y = rect.top;
			}
			p.Offset(beginP);
							
			CFreeMenu *submenu = new CFreeMenu(menu,p,ParentWnd,
				BackGroundColor,EdgeLUColor,EdgeRDColor,TextColor,font,0,this);
			SubMenu.Add(submenu);
		}
		else
		 SubMenu.Add(NULL);
	}
	DrawMenu();

}
CFreeMenu::CFreeMenu(CMenu *menu,
		      CPoint beginP,
			  CWnd *ParentWnd,
			  COLORREF BackGroundColor,
			  COLORREF EdgeLUColor,
			  COLORREF EdgeRDColor,
			  COLORREF TextColor,
			  CFont *font,
			  int pflags,
			  CFreeMenu *parentMenu
)

{
	m_parentMenu = parentMenu;
	m_Menu = menu;
	m_ParentWnd = ParentWnd;
	m_BackGroundColor = BackGroundColor;
	m_EdgeLUColor = EdgeLUColor;
	m_EdgeRDColor = EdgeRDColor;
	m_TextColor = TextColor;
	m_font = font;
	m_goby = -1;
	m_selected = -1;
	MenuBeginPoint = beginP;
	flags = pflags;
	m_selfWnd = new CMenuItemWnd;
	m_selfWnd->freeMenu = this;
	m_IsVisible = FALSE;
	int count = m_Menu->GetMenuItemCount();

	for(int i=0;i<count;i++)
	{
		CMenu *menu = m_Menu->GetSubMenu(i);
		if(menu)
		{
			CRect rect = GetItemRect(m_Menu,i);
			CPoint p;
			if(flags == 1)
			{
				p.x = rect.left;
				p.y = rect.bottom+1;
			}
			else
			{
				p.x = rect.right + 1;
				p.y = rect.top;
			}
			p.Offset(beginP);							
			CFreeMenu *submenu = new CFreeMenu(menu,p,ParentWnd,
				BackGroundColor,EdgeLUColor,EdgeRDColor,TextColor,font,0,this);
			SubMenu.Add(submenu);
		}
		else
			SubMenu.Add(NULL);

	}

}
void CFreeMenu::DrawMenu()
{
	//flags---0 竖排    1横排
	//state---0 普通    1选中
	//selected 当前选中项
	//CDC *pDC = m_ParentWnd->GetDC();
	//Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, 
	//const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	CMenu *menu = m_Menu;
	CWnd *wndtemp = CWnd::GetDesktopWindow();
	CDC *ppDC = wndtemp->GetDC();

	CPoint point = MenuBeginPoint;
	int count;
	CSize textSizeMax(0,0);
	CRect boardRect;
	CString st;
	count = menu->GetMenuItemCount();
	int curWidth = 0;
	CSize size(0,0);
	CFont *oldFont;
	oldFont = ppDC->SelectObject(m_font);
	CBrush *brush,*oldBrush;
	brush = new CBrush(m_BackGroundColor);
	oldBrush = ppDC->SelectObject(brush);

	for(int i=0;i<count;i++)
	{
		
		menu->GetMenuString(i,st,MF_BYPOSITION);
		size = ppDC-> GetTextExtent(st);
		if(size.cx>textSizeMax.cx) textSizeMax.cx = size.cx;
		if(size.cy>textSizeMax.cy) textSizeMax.cy = size.cy;
	}
	size = textSizeMax;
	size.cx+=size.cx/2;
	size.cy+=size.cy/2;


	if(flags==1)
	{
		CRect rect;
		boardRect = CRect(0,0,0,0);
		boardRect.right = count*size.cx+2;
		boardRect.bottom = size.cy+2;
		rect = boardRect;
		boardRect.OffsetRect(point);
		point.Offset(1,1);
		if(!m_IsVisible)
		{
			m_selfWnd->Create(AfxRegisterWndClass(CS_CLASSDC),"",WS_CHILD,boardRect,m_ParentWnd,1888);
			m_selfWnd->BringWindowToTop();
			m_IsVisible = TRUE;
		}
		
		CDC *pDC = m_selfWnd->GetDC();
		oldFont = pDC->SelectObject(m_font);
		CBrush *brush,*oldBrush;
		brush = new CBrush(m_BackGroundColor);
		oldBrush = pDC->SelectObject(brush);
		pDC->FillRect(rect,brush);
		pDC->Draw3dRect(rect,m_EdgeLUColor,m_EdgeRDColor);
		for(int i=0;i<count;i++)
		{
			
			boardRect = CRect(0,0,0,0);
			boardRect.left = i*size.cx;
			boardRect.right = (i+1)*size.cx;
			boardRect.bottom = size.cy;
			boardRect.OffsetRect(CPoint(1,1));
			COLORREF LUColor,RDColor;
			if(m_goby == i)
			{
				
				LUColor = m_EdgeLUColor;
				RDColor = m_EdgeRDColor;
			}
			else
				if(m_selected==i)
				{
					LUColor = m_EdgeRDColor;
					RDColor = m_EdgeLUColor;	
				}
				else
				{
					LUColor = m_BackGroundColor;
					RDColor = m_BackGroundColor;
				}
			pDC->FillRect(boardRect,brush);
			pDC->Draw3dRect(boardRect,LUColor,RDColor);
			menu->GetMenuString(i,st,MF_BYPOSITION);
			pDC->SetTextColor(m_TextColor);
			pDC->SetBkColor(m_BackGroundColor);
			pDC->DrawText(st,boardRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
		delete brush;
	}
	else
	{
		CRect rect;
		boardRect = CRect(0,0,0,0);
		boardRect.right = size.cx+2;
		boardRect.bottom = count*size.cy+2;
		rect = boardRect;
		boardRect.OffsetRect(point);
		point.Offset(1,1);
		if(!m_IsVisible)
		{
			m_selfWnd->Create(AfxRegisterWndClass(CS_CLASSDC),"",WS_CHILD,boardRect,m_ParentWnd,1888);
			m_selfWnd->BringWindowToTop();
			m_IsVisible = TRUE;
		}
		CDC *pDC = m_selfWnd->GetDC();
		oldFont = pDC->SelectObject(m_font);
		CBrush *brush,*oldBrush;
		brush = new CBrush(m_BackGroundColor);
		oldBrush = pDC->SelectObject(brush);
		pDC->FillRect(rect,brush);
		pDC->Draw3dRect(rect,m_EdgeLUColor,m_EdgeRDColor);
		
		for(int i=0;i<count;i++)
		{
			
			boardRect = CRect(0,0,0,0);
			boardRect.right = size.cx;
			boardRect.bottom = (i+1)*size.cy;
			boardRect.top = i*size.cy;
			boardRect.OffsetRect(CPoint(1,1));
			COLORREF LUColor,RDColor;
			if(m_goby == i)
			{
				
				LUColor = m_EdgeLUColor;
				RDColor = m_EdgeRDColor;
			}
			else
				if(m_selected==i)
				{
					LUColor = m_EdgeRDColor;
					RDColor = m_EdgeLUColor;	
				}
				else
				{
					LUColor = m_BackGroundColor;
					RDColor = m_BackGroundColor;
				}
			pDC->FillRect(boardRect,brush);
			pDC->Draw3dRect(boardRect,LUColor,RDColor);
			menu->GetMenuString(i,st,MF_BYPOSITION);
			pDC->SetTextColor(m_TextColor);
			pDC->SetBkColor(m_BackGroundColor);
			pDC->DrawText(st,boardRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			
		}
		delete brush;

	}
	ppDC->SelectObject(oldFont);
	ppDC->SelectObject(oldBrush);
	for( i=0;i<count;i++)
	{
		if((SubMenu[i]!=NULL) &&(m_selected==i))
			SubMenu[i]->DrawMenu();
	}
	delete brush;
}
UINT CFreeMenu::MeasureMenuID(CMenu *menu,CPoint CursorPosition)
{
	int count;
	CSize textSizeMax(0,0);
	CRect boardRect;
	CString st;
	count = menu->GetMenuItemCount();
	int curWidth = 0;
	CSize size(0,0);
	CFont *oldFont;
	CDC *pDC = m_ParentWnd->GetDC();
	oldFont = pDC->SelectObject(m_font);
	for(int i=0;i<count;i++)
	{
		
		menu->GetMenuString(i,st,MF_BYPOSITION);
		size = pDC-> GetTextExtent(st);
		if(size.cx>textSizeMax.cx) textSizeMax.cx = size.cx;
		if(size.cy>textSizeMax.cy) textSizeMax.cy = size.cy;
	}
	pDC->SelectObject(oldFont);
	size = textSizeMax;
	size.cx+=size.cx/2;
	size.cy+=size.cy/2;	
	CPoint point = MenuBeginPoint;
	point.Offset(1,1);
	if(flags==1)
	{
		for(int i=0;i<count;i++)
		{
			
			boardRect = CRect(0,0,0,0);
			boardRect.left = i*size.cx;
			boardRect.right = (i+1)*size.cx;
			boardRect.bottom = size.cy;
	//		boardRect.OffsetRect(point);
			if(boardRect.PtInRect(CursorPosition)) 
				return menu->GetMenuItemID(i);
		}

	}
	else
	{
		for(int i=0;i<count;i++)
		{
			
			boardRect = CRect(0,0,0,0);
			boardRect.right = size.cx;
			boardRect.bottom = (i+1)*size.cy;
			boardRect.top = i*size.cy;
	//		boardRect.OffsetRect(point);
			if(boardRect.PtInRect(CursorPosition)) 
				return menu->GetMenuItemID(i);
		}

	}
	return -1;
}
int CFreeMenu::MeasureMenuNo(CMenu *menu,CPoint CursorPosition)
{
	int count;
	CSize textSizeMax(0,0);
	CRect boardRect;
	CString st;
	count = menu->GetMenuItemCount();
	int curWidth = 0;
	CSize size(0,0);
	CFont *oldFont;
	CDC *pDC = m_ParentWnd->GetDC();
	oldFont = pDC->SelectObject(m_font);
	CPoint point = MenuBeginPoint ;
	//point.Offset(1,1);
	for(int i=0;i<count;i++)
	{
		
		menu->GetMenuString(i,st,MF_BYPOSITION);
		size = pDC-> GetTextExtent(st);
		if(size.cx>textSizeMax.cx) textSizeMax.cx = size.cx;
		if(size.cy>textSizeMax.cy) textSizeMax.cy = size.cy;
	}
	pDC->SelectObject(oldFont);
	size = textSizeMax;
	size.cx+=size.cx/2+2;
	size.cy+=size.cy/2+2;	

	if(flags==1)
	{
		for(int i=0;i<count;i++)
		{
			boardRect = CRect(0,0,0,0);
			boardRect.left = i*size.cx;
			boardRect.right = (i+1)*size.cx;
			boardRect.bottom = size.cy;
	//		boardRect.OffsetRect(point);
			if(boardRect.PtInRect(CursorPosition)) 
				return i;
		}

	}
	else
	{
		for(int i=0;i<count;i++)
		{
			boardRect = CRect(0,0,0,0);
			boardRect.right = size.cx;
			boardRect.bottom = (i+1)*size.cy;
			boardRect.top = i*size.cy;
	//		boardRect.OffsetRect(point);
			if(boardRect.PtInRect(CursorPosition)) 
				return i;
		}

	}
	return -1;
}
CRect CFreeMenu::GetItemRect(CMenu *menu,int item)
{
	int count;
	CSize textSizeMax(0,0);
	CRect boardRect;
	CString st;
	count = menu->GetMenuItemCount();
	int curWidth = 0;
	CSize size(0,0);
	CFont *oldFont;
	CDC *pDC = m_ParentWnd->GetDC();
	oldFont = pDC->SelectObject(m_font);
	for(int i=0;i<count;i++)
	{
		
		menu->GetMenuString(i,st,MF_BYPOSITION);
		size = pDC-> GetTextExtent(st);
		if(size.cx>textSizeMax.cx) textSizeMax.cx = size.cx;
		if(size.cy>textSizeMax.cy) textSizeMax.cy = size.cy;
	}
	pDC->SelectObject(oldFont);
	size = textSizeMax;
	size.cx+=size.cx/2;
	size.cy+=size.cy/2;	
	CPoint point;
	point  = MenuBeginPoint;
	point.Offset(1,1);
	if(flags==1)
	{
		if(item<count)
		{
			
			boardRect = CRect(0,0,0,0);
			boardRect.left = item*size.cx;
			boardRect.right = (item+1)*size.cx;
			boardRect.bottom = size.cy;
			//boardRect.OffsetRect(point);
			return boardRect;
		}

	}
	else
	{
		if(item<count)
		{
			boardRect = CRect(0,0,0,0);
			boardRect.right = size.cx;
			boardRect.bottom = (item+1)*size.cy;
			boardRect.top = item*size.cy;
		//	boardRect.OffsetRect(point);
			return boardRect;
		}

	}
	return CRect(-1,-1,-1,-1);
}

LRESULT CFreeMenu::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{   
	if(!m_IsVisible) return 0;
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			CPoint p;
			p.x = LOWORD(lParam);  // horizontal position of cursor 
			p.y = HIWORD(lParam); 
			int selected = MeasureMenuNo(m_Menu,p);
			
			if(selected!=-1)
			{
				if(selected!=m_selected)
				{    
					if((m_selected!=-1) && (SubMenu[m_selected]))
						SubMenu[m_selected]->Disable();
					m_goby = -1;
					m_selected = selected;
					DrawMenu();
					if(!m_Menu->GetSubMenu(selected))
					{
						m_ParentWnd->PostMessage(m_Menu-> GetMenuItemID(selected));
						m_selfWnd->BringWindowToTop();
						ClearParent();
						m_selected = -1;
						m_goby = -1;
						
					}
					

				
				}
				else
				{
					if(SubMenu[m_selected])
						SubMenu[m_selected]->Disable();
					m_selected = -1;
					DrawMenu();
					
				}

				

			}
			else
			{
				int count = m_Menu->GetMenuItemCount();
				for(int i=0;i<count;i++)
					if(SubMenu[i])
						SubMenu[i]->WindowProc(message, wParam,lParam) ;

			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			int count = m_Menu->GetMenuItemCount();
			CPoint p;
			p.x = LOWORD(lParam);  // horizontal position of cursor 
			p.y = HIWORD(lParam); 
			int Goby =  MeasureMenuNo(m_Menu,p);
			if(Goby!=-1)
			{
				if(m_selected!=-1)
				{
					if(m_selected!=Goby)
					{
						if(SubMenu[m_selected])
							SubMenu[m_selected]->Disable();
						m_selected = Goby;
						DrawMenu();
						return 2;
					}
				}
				else
				if(Goby!=m_goby)
				{
					m_goby = Goby;
					DrawMenu();
					return 2;
				}
			}
			else
			{
				
				if((m_goby != -1)||(m_selected != -1))
				{
					LRESULT ff = 0;
					for(int i=0;i<count;i++)
					{
						if((SubMenu[i]!=NULL) &&(m_selected==i) && (ff==0))
							ff = SubMenu[i]->WindowProc(message, wParam,lParam) ;
					}

					if(ff ==1)
					{
						m_goby = -1;
						m_selected = -1;
						delete m_selfWnd;
						m_selfWnd = new CMenuItemWnd;
						m_IsVisible = FALSE;
						return 1;
					}
				}
			}
		}
		break;
	}

	return 0;
}

void CFreeMenu::Disable()
{
	if(m_IsVisible)
	{
		DrawMenu();
		m_IsVisible = FALSE;
		m_selfWnd->DestroyWindow();
	}
}

void CFreeMenu::ClearParent()
{
	if(m_parentMenu)
	{
		m_parentMenu->DrawMenu();
		m_parentMenu->ClearParent();
		Disable();
	}
	m_selected = -1;

}
CFreeMenu::~CFreeMenu()
{
	
	for(int i=0;i<SubMenu.GetSize();i++)
	{
		if(SubMenu[i]) delete SubMenu[i];
	}
	if(m_parentMenu==NULL) delete m_Menu;
	if(m_selfWnd) delete m_selfWnd;

} 