// MyListBox.cpp : implementation file
//

#include "stdafx.h"
#include "MyListBox.h"
#include "Resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMyListBox

CMyListBox::CMyListBox()
{

}

CMyListBox::~CMyListBox()
{

}


BEGIN_MESSAGE_MAP(CMyListBox, CListBox)
	//{{AFX_MSG_MAP(CMyListBox)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()

	ON_MESSAGE(WM_DRAGLIST, DragMoveItem) 	

END_MESSAGE_MAP()


void CMyListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListBox::OnLButtonDown(nFlags, point);

	//一定要先ReleaseCapture，否则会出错
	::ReleaseCapture();

	int index=GetCurSel();;
	if (index!=LB_ERR )
	{
		//一定要放在OnLButtonDown(nFlags, point);后面
		CDragList::BeginDrag(index,m_hWnd);  //一定要放在OnLButtonDown(nFlags, point);后面	
	}
}

void CMyListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDragList::EndDrag(m_hWnd);
	::InvalidateRect(m_hWnd,NULL,true);
	::SetFocus(m_hWnd);

	CListBox::OnLButtonUp(nFlags, point);
}

void CMyListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( nFlags&MK_LBUTTON )
	{
		CDragList::Dragging(m_hWnd);
		return;
	}

	CListBox::OnMouseMove(nFlags, point);
}





LRESULT CMyListBox::DragMoveItem(WPARAM wParam, LPARAM lParam) 	
{
	
	switch (wParam)
	{
	case GET_LIST_RECT:	//get all items rect
		{
			//get the count of listctrl
			int count=GetCount();

			vector<RECT>& ItemRect=*(vector<RECT>*)lParam;
			ItemRect.resize(count);

			for (int i=0;i<count;i++)
			{
				//save item rect
				GetItemRect(i,&ItemRect[i]);
			}
		}
		break;

	case DRAG_SAME_WND:	//if drag item in the same window
		{
			int SrcIndex=CDragList::GetSrcIndex();
			int DesIndex=CDragList::GetTargetIndex();
			if(DesIndex==SELECT_NONE) 
				DesIndex=GetCount();

			//---------------------------步骤1.获取原来项的信息----------------------------------

			//获取要移动的项
			TCHAR text[1000];
			this->GetText(SrcIndex,text);

			//---------------------------步骤2.删除原来项----------------------------------------
			this->DeleteString(SrcIndex);

			//---------------------------步骤3.由于删除一项，所以目标位置有可能需要更新---------------
			if(DesIndex>SrcIndex)
				DesIndex--;

			//---------------------------步骤4.在目标位置des插入项------------------------------------

			//将item移到要插入的位置
			this->InsertString(DesIndex,text);
			this->SetCurSel(DesIndex);
		}
		break;


	case DRAG_BETWEEN_TWO_WND:	//if drag item between two windows
		{
			HWND SrcWnd=(HWND)lParam;

			int DesIndex=CDragList::GetTargetIndex();
			if(DesIndex==SELECT_NONE) 
				DesIndex=GetCount();

			//send message to the original window to get the data of the 
			//item that is to be moved and then delete it.
			TCHAR text[1000];;
			::SendMessage(SrcWnd,WM_DRAGLIST,GET_AND_DELETE_ITEM,(LPARAM)text); 

			//将item移到要插入的位置
			this->InsertString(DesIndex,text);
			this->SetCurSel(DesIndex);
		}
		break;

	case GET_AND_DELETE_ITEM:	//when drag between two widnows,we should get the original item data and delete it 
		{
			int SrcIndex=CDragList::GetSrcIndex();

			TCHAR* text=(TCHAR*)lParam;
	
			//获取要移动的项
			this->GetText(SrcIndex,text);

			//删除原来的项
			this->DeleteString(SrcIndex);
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