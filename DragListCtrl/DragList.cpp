/****************************************************************************
1.是否启动dragging，最主要看m_SrcItem

2.一开始按下时，必须调用BeginDrag 以确定 m_SrcItem 的值，有可能是SELECT_NONE

3.when finish dragging,must set m_SrcItem=SELECT_NONE;

****************************************************************************/

#include "stdafx.h"
#include "DragList.h"

vector<RECT>CDragList::ItemRect;
int			CDragList::m_ActiveItem=SELECT_NONE;
int			CDragList::m_SrcItem=SELECT_NONE;
HWND		CDragList::DragWnd=NULL;
HWND		CDragList::SrcWnd=NULL;
UINT		CDragList::part=-1;


void CDragList::BeginDrag(int SelectItem,HWND hWnd) 
{
	trace(_T("BeginDrag"));
	
	m_SrcItem=SelectItem;
	m_ActiveItem=SelectItem;    //当按下鼠标后没有移动就弹起，那么m_SrcItem==m_ActiveItem可以说明在同一个item弹起
	part=-10;					//用于在Dragging中告知是第一次按下，还没有移动
	DragWnd=NULL; 
	SrcWnd=hWnd;
}


/****************************************************************************
返回值：	DRAG_INVALID		-- 无效的移动
			DRAG_IN_SAMEITEM	-- 移动的目标位置是原来item的位置
			DRAG_SUCCESSFUL		-- 成功移动
****************************************************************************/
int CDragList::EndDrag(HWND ListWnd) 
{
	trace(_T("EndDrag"));

	//━━━━━━━━━━━━━━无效的移动━━━━━━━━━━━━━━
	if ( m_SrcItem==SELECT_NONE )
		return DRAG_INVALID;

	//━━━━━━━━━━━━━━移动的目标位置是原来item的位置━━━━━
	if (SrcWnd==ListWnd && ( GetTargetIndex()==m_SrcItem || GetTargetIndex()-m_SrcItem==1 ) )
	{
		trace("移动的目标位置是原来item的位置");
		return DRAG_IN_SAMEITEM;  
	}

	if(SrcWnd==ListWnd)
		::SendMessage(ListWnd,WM_DRAGLIST,DRAG_SAME_WND,NULL); 
	else
		::SendMessage(ListWnd,WM_DRAGLIST,DRAG_BETWEEN_TWO_WND,(LPARAM)SrcWnd); 

	m_SrcItem=SELECT_NONE;

	return DRAG_SUCCESSFUL;
}




void CDragList::GetItemRect()
{
	::SendMessage(DragWnd,WM_DRAGLIST,GET_LIST_RECT,(LPARAM)&ItemRect); 
}


VOID CALLBACK CDragList::TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{	
	POINT point;
	::GetCursorPos(&point);
	RECT rect; 
	::GetWindowRect(DragWnd,&rect);

	//鼠标中键和左键都没有按下时取消时钟 （左键拖动文件到list添加）
	if (GetKeyState(VK_MBUTTON)>=0 && GetKeyState(VK_LBUTTON)>=0 )
	{
		::KillTimer(NULL,idEvent);	trace("mouse boutton up and stop timer");

		//释放空间
		vector<RECT>().swap(ItemRect); 

		m_SrcItem=SELECT_NONE;

		return;
	}

	//判断窗口是否垂直滚动条
	if((GetWindowLong(DragWnd,GWL_STYLE)&WS_VSCROLL)==WS_VSCROLL)
	{
		if (point.y-rect.top<10 ) 
		{
			if(m_ActiveItem!=ItemRect.size()-1 && m_ActiveItem!=0) { EraseLine(); }
			::SendMessage(DragWnd,WM_VSCROLL,SB_LINEUP,0);  //trace("在list顶端");
			GetItemRect(); 
		}
		else if (rect.bottom-point.y<10 )	
		{
			if(m_ActiveItem!=ItemRect.size()-1 && m_ActiveItem!=0) { EraseLine(); }
			::SendMessage(DragWnd,WM_VSCROLL,SB_LINEDOWN,0);  //trace("在list底部");
			GetItemRect(); 
		}
	}

	//水平滚动条
	if( (GetWindowLong(DragWnd,GWL_STYLE)&WS_HSCROLL)==WS_HSCROLL)
	{
		if ( point.x-rect.left<10 ) //在list左端
		{
			if(m_ActiveItem!=ItemRect.size()-1 && m_ActiveItem!=0) { EraseLine(); }
			::SendMessage(DragWnd,WM_HSCROLL,SB_LINELEFT,0);  //trace("在list左端");
			GetItemRect(); 
		}
		else if ( rect.right-point.x<10 )	//在list右边
		{
			if(m_ActiveItem!=ItemRect.size()-1 && m_ActiveItem!=0) { EraseLine(); }
			::SendMessage(DragWnd,WM_HSCROLL,SB_LINERIGHT,0);  //trace("在list右边");
			GetItemRect(); 
		}
	}	

	//mouse outside window and erase the old line
	if (!::PtInRect(&rect,point))
	{
		trace("mouse outside window");
		EraseLine();
		m_ActiveItem=SELECT_NONE;
	}

}



/****************************************************************************
ListWnd 必须是MouseMove传递进来的hWnd，不要尝试用WindowFromPoint，否则有可能会出错。同样EndDragging也是。
****************************************************************************/
void CDragList::Dragging(HWND ListWnd,int ListStyle) 
{
	if(m_SrcItem==SELECT_NONE)
		return;

	POINT point;
	::GetCursorPos(&point);
	::ScreenToClient(ListWnd,&point);
	
	if (part==-10)
	{
		part=-1; trace("接收第一个WM_MOUSEMOVE用于设置时钟");

		//the timer is on until button up
		::SetTimer(NULL,0,100,TimerProc);

		return;
	}

	if (DragWnd!=ListWnd)
	{
		trace(_T("the first time move in window"));

/*
		trace(DragWnd);
		trace(ListWnd);
*/

		if ( IsWindow(DragWnd) )
		{
			trace(ListWnd);
			EraseLine();
		}

		//important 否则后面会出现不可预料的错误。下面的代码会重新设置m_ActiveItem的值
		m_ActiveItem=SELECT_NONE; 

		//更新DragWnd
		DragWnd=ListWnd;  

		//Get all List item rect;
		GetItemRect();

		//激活自己
		::BringWindowToTop(DragWnd); trace("BringWindowToTop");
	}

	//改变鼠标形状
	//当发现这里编译出错时，检查是否添加了鼠标资源IDC_MOVEITEMCUR，并且在StdAfx.h里添加 #include "Resource.h"
	::SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_MOVEITEMCUR)));	
	
	//begin find item
	UINT i;
	UINT count=ItemRect.size();
	for(i=0; i<count && !::PtInRect(&ItemRect[i],point) ; i++)	;	//注意这行的分号
	
	//if found item(即鼠标在List里面)
	if(i<count)  
	{
		//━━━━━━━━━━━━━━━━━计算鼠标在ItemRect的上部还是下部━━━━━━━━━
		int TempPart;
		if (VERTICAL_LIST ==ListStyle)
			TempPart= (  point.y < (ItemRect[i].top + (ItemRect[i].bottom-ItemRect[i].top)/2 )  ) ? 1 : 2;
		else
			TempPart= (  point.x < (ItemRect[i].left+ (ItemRect[i].right-ItemRect[i].left)/2)   ) ? 1 : 2;
		//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

		//是否第一次移入此Item
		if (m_ActiveItem!=i || part!=TempPart)	
		{
			//计算旧的line坐标
			int Ox1,Oy1,Ox2,Oy2;
			CountLinePos(Ox1,Oy1,Ox2,Oy2,ListStyle);

			//保存当前焦点的按钮索引
			m_ActiveItem=i;
			part=TempPart;
		//	trace(m_ActiveItem,part);
			
			//计算新的line坐标
			int Nx1,Ny1,Nx2,Ny2;
			CountLinePos(Nx1,Ny1,Nx2,Ny2,ListStyle);

			//如果新坐标和久坐标不一样，则擦除先前的line
			if (Ox1 != Nx1 || Oy1 != Ny1 || Ox2 != Nx2 || Oy2 != Ny2 )
			{
	//			trace("新旧坐标不一样");
				RECT rect={Ox1-3,Oy1-3,Ox2+3,Oy2+3};
				::InvalidateRect(DragWnd,&rect,true);
				::UpdateWindow(DragWnd);
			}

			//告知窗口，鼠标移入一个新的item
			::SendMessage(ListWnd,WM_DRAGLIST,DRAG_ITEM_CHANGED,m_ActiveItem);

			//绘制新的line
			DrawLine(DragWnd,Nx1,Ny1,Nx2,Ny2);

			return;
		}		
	}
/*
	//if not found item(鼠标不在List里面)
	else
	{
		//假如第一次移出List
		if (m_ActiveItem!=SELECT_NONE)
		{
			EraseLine();

			//表示鼠标在List外
			m_ActiveItem=SELECT_NONE;	
		}
	}	
*/
}	


int CDragList::GetTargetIndex()	
{
	if(m_ActiveItem==SELECT_NONE)
		return SELECT_NONE;
	return (part==2 ? m_ActiveItem+1 : m_ActiveItem) ; 
}


//擦除先前的line
void CDragList::EraseLine()
{
	if (0<=m_ActiveItem && m_ActiveItem<(int)ItemRect.size())
	{
		RECT rect={	ItemRect[m_ActiveItem].left-3,
					ItemRect[m_ActiveItem].top-3,
					ItemRect[m_ActiveItem].right+3,
					ItemRect[m_ActiveItem].bottom+3};
		::InvalidateRect(DragWnd,&rect,true);
	}
}


/****************************************************************************

****************************************************************************/
void CDragList::CountLinePos(int& x1,int& y1,int& x2,int& y2,int ListStyle)
{
	if (0<=m_ActiveItem && m_ActiveItem<(int)ItemRect.size())
	{
		if (VERTICAL_LIST ==ListStyle)
		{
			x1=ItemRect[m_ActiveItem].left+2;
			x2=ItemRect[m_ActiveItem].right-2;
			if (part==1)
				y1=y2=ItemRect[m_ActiveItem].top;
			else if (part==2)
				y1=y2=ItemRect[m_ActiveItem].bottom;
		}
		else
		{
			y1=ItemRect[m_ActiveItem].top+2;
			y2=ItemRect[m_ActiveItem].bottom-2;
			if (part==1)
				x1=x2=ItemRect[m_ActiveItem].left;
			else if (part==2)
				x1=x2=ItemRect[m_ActiveItem].right;
		}
	}
	else
	{
		y1=y2=x1=x2=0;
	}
}


void CDragList::DrawLine(HWND hWnd,int x1,int y1,int x2,int y2)
{
	HDC hdc=::GetDC(hWnd);

	if (x1==x2)
	{
		::MoveToEx(hdc, x1-3, y1+0	,NULL);		::LineTo(hdc, x1+3, y1+0);
		::MoveToEx(hdc, x1-2, y1+1	,NULL);		::LineTo(hdc, x1+2, y1+1);
		//━━━━━━━━━━━━━━━━━
		::MoveToEx(hdc, x1-1, y1+2	,NULL);		::LineTo(hdc, x1-1, y2-1);
		::MoveToEx(hdc, x1+0, y1+2	,NULL);		::LineTo(hdc, x1+0, y2-1);
		//━━━━━━━━━━━━━━━━━
		::MoveToEx(hdc, x2-3, y2-0	,NULL);		::LineTo(hdc, x2+3, y2-0);
		::MoveToEx(hdc, x2-2, y2-1	,NULL);		::LineTo(hdc, x2+2, y2-1);
	}
	else if (y1==y2)
	{
		::MoveToEx(hdc, x1+0, y1-3	,NULL);		::LineTo(hdc, x1+0, y1+3);
		::MoveToEx(hdc, x1+1, y1-2	,NULL);		::LineTo(hdc, x1+1, y1+2);
		//━━━━━━━━━━━━━━━━━
		::MoveToEx(hdc, x1+2, y1-1	,NULL);		::LineTo(hdc, x2-1, y1-1);
		::MoveToEx(hdc, x1+2, y1+0	,NULL);		::LineTo(hdc, x2-1, y1+0);
		//━━━━━━━━━━━━━━━━━
		::MoveToEx(hdc, x2-0, y2-3	,NULL);		::LineTo(hdc, x2-0, y2+3);
		::MoveToEx(hdc, x2-1, y2-2	,NULL);		::LineTo(hdc, x2-1, y2+2);
	}

	::ReleaseDC(hWnd,hdc) ;	
}