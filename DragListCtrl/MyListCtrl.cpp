// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "MyListCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMyListCtrl::CMyListCtrl()
{
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DRAGLIST, DragMoveItem) 	
END_MESSAGE_MAP()





void CMyListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CListCtrl::OnLButtonDown(nFlags, point);

	//设置焦点
	if (::GetFocus()!=m_hWnd )
		::SetFocus(m_hWnd);

	//如果ListCtrl是单选的，就用这种方式判断选中的项
	int index=::SendMessage(m_hWnd,LVM_GETNEXTITEM,-1,MAKELPARAM(LVNI_SELECTED,0));

	trace(index);
	if (index!=-1)
	{
		//一定要放在CListCtrl::OnLButtonDown(nFlags, point);后面
		CDragList::BeginDrag(index,m_hWnd);  //一定要放在OnLButtonDown(nFlags, point);后面	
	}
}

void CMyListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDragList::EndDrag(m_hWnd);
	::InvalidateRect(m_hWnd,NULL,true);
	::SetFocus(m_hWnd);

	CListCtrl::OnLButtonUp(nFlags, point);
}

void CMyListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( nFlags&MK_LBUTTON )
	{
		CDragList::Dragging(m_hWnd);
		return;
	}
	
	CListCtrl::OnMouseMove(nFlags, point);
}




struct DRAGITEMDATA
{
	TCHAR ItemText0[_MAX_FNAME];
	TCHAR ItemText1[_MAX_FNAME];
	TCHAR ItemText2[_MAX_FNAME];
};


LRESULT CMyListCtrl::DragMoveItem(WPARAM wParam, LPARAM lParam) 	
{
	
	switch (wParam)
	{
	case GET_LIST_RECT:	//get all items rect
		{
			//get the count of listctrl
			int count=(int)::SendMessage(this->m_hWnd, LVM_GETITEMCOUNT, 0, 0);

			vector<RECT>& ItemRect=*(vector<RECT>*)lParam;
			ItemRect.resize(count);

			for (int i=0;i<count;i++)
			{
				//save item rect
				ItemRect[i].left=LVIR_SELECTBOUNDS ;
				::SendMessage(this->m_hWnd,  LVM_GETITEMRECT , i,(LPARAM)&ItemRect[i]); 
			}
		}
		break;

	case DRAG_SAME_WND:	//if drag item in the same window
		{
			int SrcIndex=CDragList::GetSrcIndex();
			int DesIndex=CDragList::GetTargetIndex();
			if(DesIndex==SELECT_NONE) 
				DesIndex=::SendMessage(this->m_hWnd, LVM_GETITEMCOUNT, 0, 0);

			//---------------------------步骤1.获取原来项的信息----------------------------------

			//获取要移动的项
			LVITEM lvi;
			lvi.cchTextMax=_MAX_FNAME;

			//get the first column text
			TCHAR ItemText0[_MAX_FNAME];
			lvi.pszText=ItemText0;
			lvi.iSubItem=0;
			::SendMessage(this->m_hWnd, LVM_GETITEMTEXT, (WPARAM)SrcIndex, (LPARAM)&lvi);

			//get the second column text
			TCHAR ItemText1[_MAX_FNAME];
			lvi.pszText=ItemText1;
			lvi.iSubItem=1;
			::SendMessage(this->m_hWnd, LVM_GETITEMTEXT, (WPARAM)SrcIndex, (LPARAM)&lvi);

			//get the third column text
			TCHAR ItemText2[_MAX_FNAME];
			lvi.pszText=ItemText2;
			lvi.iSubItem=2;
			::SendMessage(this->m_hWnd, LVM_GETITEMTEXT, (WPARAM)SrcIndex, (LPARAM)&lvi);


			//---------------------------步骤2.删除原来项----------------------------------------
			this->DeleteItem(SrcIndex);


			//---------------------------步骤3.由于删除一项，所以目标位置有可能需要更新---------------
			if(DesIndex>SrcIndex)
				DesIndex--;

			//---------------------------步骤4.在目标位置des插入项------------------------------------

			//将item移到要插入的位置
			int nRow = this->InsertItem(DesIndex, ItemText0,0);//插入1行"11"代表第0列的数据 参数(行数,标题,图标索引)
			this->SetItemText(nRow, 1, ItemText1);	//设置第一列数据
			this->SetItemText(nRow, 2, ItemText2);	//设置第一列数据


			//高亮移动后的item
			this->SetItemState(DesIndex,LVIS_SELECTED,LVIS_SELECTED);
		}
		break;


	case DRAG_BETWEEN_TWO_WND:	//if drag item between two windows
		{
			HWND SrcWnd=(HWND)lParam;

			int DesIndex=CDragList::GetTargetIndex();
			if(DesIndex==SELECT_NONE) 
				DesIndex=::SendMessage(this->m_hWnd, LVM_GETITEMCOUNT, 0, 0);

			//send message to the original window to get the data of the 
			//item that is to be moved and then delete it.
			DRAGITEMDATA TempItem;
			::SendMessage(SrcWnd,WM_DRAGLIST,GET_AND_DELETE_ITEM,(LPARAM)&TempItem); 


			//将item移到要插入的位置
			int nRow = this->InsertItem(DesIndex, TempItem.ItemText0,0);//插入1行"11"代表第0列的数据 参数(行数,标题,图标索引)
			this->SetItemText(nRow, 1, TempItem.ItemText1);	//设置第一列数据
			this->SetItemText(nRow, 2, TempItem.ItemText2);	//设置第一列数据


			//高亮移动后的item
			this->SetItemState(DesIndex,LVIS_SELECTED,LVIS_SELECTED);
		}
		break;

	case GET_AND_DELETE_ITEM:	//when drag between two widnows,we should get the original item data and delete it 
		{
			int SrcIndex=CDragList::GetSrcIndex();

			DRAGITEMDATA& TempItem=*((DRAGITEMDATA*)lParam);
	

			//获取要移动的项
			LVITEM lvi;
			lvi.cchTextMax=_MAX_FNAME;

			//get the first column text
			lvi.pszText=TempItem.ItemText0;
			lvi.iSubItem=0;
			::SendMessage(this->m_hWnd, LVM_GETITEMTEXT, (WPARAM)SrcIndex, (LPARAM)&lvi);

			//get the second column text
			lvi.pszText=TempItem.ItemText1;
			lvi.iSubItem=1;
			::SendMessage(this->m_hWnd, LVM_GETITEMTEXT, (WPARAM)SrcIndex, (LPARAM)&lvi);

			//get the third column text
			lvi.pszText=TempItem.ItemText2;
			lvi.iSubItem=2;
			::SendMessage(this->m_hWnd, LVM_GETITEMTEXT, (WPARAM)SrcIndex, (LPARAM)&lvi);

			//删除原来的项
			this->DeleteItem(SrcIndex);
		}
		break;

/*
	case DRAG_ITEM_CHANGED:
		{
				
		}
		break;
*/

	}

	return 0;
}







