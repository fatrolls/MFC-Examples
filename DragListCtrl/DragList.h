#ifndef _DRAG_LIST_H_
#define _DRAG_LIST_H_


/****************************************************************************
一、在程序包含2个文件 DragList.cpp 和 DragList.h

二、添加鼠标处理
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	1.在你自己的派生的ClistCtrl的鼠标消息函数里添加以下代码

	//鼠标按下：
	void CMyListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
	{
		CListCtrl::OnLButtonDown(nFlags, point);

		CDragList::BeginDrag(SelectIndex,m_hWnd);  //一定要放在OnLButtonDown(nFlags, point);后面
	}

	//鼠标弹起
	void CMyListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
	{
		CDragList::EndDrag(m_hWnd);

		CListCtrl::OnLButtonUp(nFlags, point);
	}

	//鼠标移动
	void CMyListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
	{
		if ( nFlags&MK_MBUTTON )
		{
			CDragList::Dragging(m_hWnd,point,VERTICAL_LIST);
			return;
		}
		
		CListCtrl::OnMouseMove(nFlags, point);
	}

三、处理数据交换
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	确定交换两项后，CDragList会向ListCtrl发送WM_DRAGLIST消息。
	ListCtrl需添加自定义消息函数并处理item的交换，更新ListCtrl
	你需要修改的大部分代码在这里，具体看示例代码
  
	LRESULT CMyListCtrl::DragMoveItem(WPARAM wParam, LPARAM lParam) 	
	{
		
		switch (wParam)
		{
		case GET_LIST_RECT:	//get all items rect
			{
				vector<RECT>& ItemRect=*(vector<RECT>*)lParam;
				//把ListCtrl的所有items的rect放到ItemRect里
			}
			break;

		case DRAG_SAME_WND:	//if drag item in the same window
			{
				int SrcIndex=CDragList::GetSrcIndex();
				int DesIndex=CDragList::GetTargetIndex();
				if(DesIndex==SELECT_NONE) 
					DesIndex=::SendMessage(this->m_hWnd, LVM_GETITEMCOUNT, 0, 0);

				//---------------------------步骤1.获取原来项的信息----------------------------------
				...........
				::SendMessage(this->m_hWnd, LVM_GETITEMTEXT, (WPARAM)SrcIndex, (LPARAM)&lvi);

				//---------------------------步骤2.删除原来项----------------------------------------
				this->DeleteItem(SrcIndex);

				//---------------------------步骤3.由于删除一项，所以目标位置有可能需要更新---------------
				if(DesIndex>SrcIndex)
					DesIndex--;

				//---------------------------步骤4.在目标位置des插入项------------------------------------
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
			}
			break;

		case GET_AND_DELETE_ITEM:	//when drag between two widnows,we should get the original item data and delete it 
			{
				int SrcIndex=CDragList::GetSrcIndex();

				DRAGITEMDATA& TempItem=*((DRAGITEMDATA*)lParam);
		
				//获取要移动的项
				::SendMessage(this->m_hWnd, LVM_GETITEMTEXT, (WPARAM)SrcIndex, (LPARAM)&lvi);

				//删除原来的项
				this->DeleteItem(SrcIndex);
			}
			break;

		//当dragging时，如果进入一个新项，会接收到DRAG_ITEM_CHANGED消息，你可以做相应的处理
		case DRAG_ITEM_CHANGED:
			{
					
			}
			break;
		}

		return 0;
	}

四、更新以及示例代码下载
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	更新: http://hi.baidu.com/qiujiejia/blog/item/4912a3fba3e77b44034f562d.html

	1.可到QQ邮箱(vc-code@qq.com,密码code8888)下载
	2.或访问http://cid-3ba16e78a53d2d3d.office.live.com/self.aspx/VC/DragList2.zip

										Jacky
										qiujiejia@gmail.com
										2012-05-25
****************************************************************************/


#include <vector>
using namespace std;

//send message to the parent window
#define WM_DRAGLIST				WM_USER+435
#define GET_LIST_RECT			1
#define DRAG_ITEM_CHANGED		2
#define DRAG_SAME_WND			3
#define DRAG_BETWEEN_TWO_WND	4
#define GET_AND_DELETE_ITEM		5

#define SELECT_NONE				-1

//List Style
#define VERTICAL_LIST			0
#define HORIZONTAL_LIST			1

//drag result
#define DRAG_INVALID			1
#define DRAG_IN_SAMEITEM		2
#define DRAG_SUCCESSFUL			3


class CDragList  
{
public:
	static void BeginDrag(int SelectItem,HWND hWnd) ;
	static int  EndDrag(HWND ListWnd) ;
	static void Dragging(HWND ListWnd,int Style=VERTICAL_LIST) ;
	static int  GetTargetIndex();	
	static int  GetSrcIndex()		{return m_SrcItem;}

private:
	static UINT		part;				//鼠标在ItemRect的上部还是下部
	static vector	<RECT> ItemRect;	//保存所有item的rect
	static HWND		DragWnd;			//item所在的窗口
	static HWND		SrcWnd;				//鼠标按下时的窗口
	static int		m_ActiveItem;		//拖动时鼠标所在的item
	static int		m_SrcItem;			//需要移动的item的num

	static VOID CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime);
	static void	CountLinePos(int& x1,int& y1,int& x2,int& y2,int ListStyle);
	static void GetItemRect();
	static void DrawLine(HWND hWnd,int x,int y,int a,int b);
	static void EraseLine();
};


#endif // #define _DRAG_LIST_H_
