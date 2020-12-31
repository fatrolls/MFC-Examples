// ComboOXTree.cpp: implementation of the CComboOXTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComboOXTree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComboOXTree::CComboOXTree() : m_container(this),
	m_pCombo(NULL),
	m_rectValid(0,0,0,0),
	m_hLastSelectedItem(NULL)
{

}

CComboOXTree::~CComboOXTree()
{

}


BOOL CComboOXTree::PreCreateWindow(CREATESTRUCT& cs)
{
	// create container window
	//

	ASSERT(!::IsWindow(m_container.GetSafeHwnd()));
	if(::IsWindow(m_container.GetSafeHwnd()))
	{
		return FALSE;
	}

    static CString sContainerWndClass=AfxRegisterWndClass(CS_SAVEBITS);

	if((cs.dwExStyle & 
		(WS_EX_CLIENTEDGE|WS_EX_STATICEDGE|WS_EX_WINDOWEDGE|WS_EX_DLGMODALFRAME))==0)
	{
		cs.dwExStyle|=WS_EX_DLGMODALFRAME;
	}
    
	if(!m_container.CreateEx(cs.dwExStyle,sContainerWndClass,_T(""),
		(cs.style & 0xffff0000 & ~(WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL))|
		WS_POPUP|MFS_SYNCACTIVE,cs.x,cs.y,cs.cx,cs.cy,cs.hwndParent,NULL))
	{
		return FALSE;
	}
	//
	///////////////////////////////////////////////


	// change create data
	cs.style&=~(WS_VISIBLE|WS_POPUP);
	// must have buttons
	cs.style|=WS_CHILD;
	cs.dwExStyle=0;
    cs.hwndParent=m_container.GetSafeHwnd();
    cs.x=cs.y=0;
	CRect rect;
	m_container.GetClientRect(rect);
	cs.cx=rect.Width();
	cs.cy=rect.Height();

	return COXTreeCtrl::PreCreateWindow(cs);
}



LRESULT CComboOXTree::WindowProc(UINT message, 
													 WPARAM wParam, 
													 LPARAM lParam)
{
	LRESULT lResult=0;

	switch(message)
	{
	case WM_KILLFOCUS: 
		OnKillFocus(CWnd::FromHandle((HWND)wParam));
		break;

	case WM_LBUTTONDOWN: 
		OnLButtonDown((UINT)wParam,CPoint(LOWORD(lParam),HIWORD(lParam)));
		break;

	case WM_LBUTTONDBLCLK:
		OnLButtonDblClk((UINT) wParam, CPoint(LOWORD(lParam),HIWORD(lParam)));
		break;

	case WM_MOUSEMOVE: 
		OnMouseMove((UINT)wParam,CPoint(LOWORD(lParam),HIWORD(lParam)));
		break;

	case WM_KEYDOWN: 
		OnKeyDown((UINT)wParam,LOWORD(lParam),HIWORD(lParam));
		break;
	default:
		lResult=COXTreeCtrl::WindowProc(message,wParam,lParam);
		break;
	}

	return lResult;
}



void CComboOXTree::OnKillFocus(CWnd* pNewWnd)
{
	COXTreeCtrl::OnKillFocus(pNewWnd);

	if(pNewWnd!=this && m_pCombo!=NULL)
	{
		m_pCombo->PostMessage(CB_SHOWDROPDOWN,FALSE);
	}
}



void CComboOXTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	
	COXTreeCtrl::OnLButtonDown(nFlags,point);
	HTREEITEM hItem=COXTreeCtrl::GetSelectedItem();
	if (hItem)
		SelectItem(hItem);
//	}
}


void CComboOXTree::OnMouseMove(UINT nFlags, CPoint point)
{
	COXTreeCtrl::OnMouseMove(nFlags,point);
}


void CComboOXTree::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(m_pCombo!=NULL)
	{
		if(nChar==VK_ESCAPE || nChar==VK_RETURN)
		{
			if(nChar==VK_RETURN)
			{
				HTREEITEM hItem=GetSelectedItem();
				if(hItem!=NULL)
				{
					m_hLastSelectedItem=hItem;
				}
			}
			m_pCombo->ShowDropDown(FALSE);
			m_pCombo->SetFocus();
			return;
		}
	}

	COXTreeCtrl::OnKeyDown(nChar,nRepCnt,nFlags);
}



void CComboOXTree::AutoResize()
{
	ASSERT(::IsWindow(GetSafeHwnd()));
	if(!::IsWindow(GetSafeHwnd()))
	{
		return;
	}

	CRect rectCurrent;
	GetWindowRect(rectCurrent);
	CRect rectBest=GetBestRect();
	CRect rect=rectBest;
	ASSERT(m_sizeMinWidthHeight.cx<=m_sizeMaxWidthHeight.cx || 
		m_sizeMinWidthHeight.cx==-1 || m_sizeMaxWidthHeight.cx==-1);
	ASSERT(m_sizeMinWidthHeight.cy<=m_sizeMaxWidthHeight.cy || 
		m_sizeMinWidthHeight.cy==-1 || m_sizeMaxWidthHeight.cy==-1);
	if(m_sizeMaxWidthHeight.cx>=0 && rect.Width()>m_sizeMaxWidthHeight.cx)
	{
		rect.right=rect.left+m_sizeMaxWidthHeight.cx;
	}
	if(m_sizeMaxWidthHeight.cy>=0 && rect.Height()>m_sizeMaxWidthHeight.cy)
	{
		rect.bottom=rect.top+m_sizeMaxWidthHeight.cy;
	}
	if(m_sizeMinWidthHeight.cx>=0 && rect.Width()<m_sizeMinWidthHeight.cx)
	{
		rect.right=rect.left+m_sizeMinWidthHeight.cx;
	}
	if(m_sizeMinWidthHeight.cy>=0 && rect.Height()<m_sizeMinWidthHeight.cy)
	{
		rect.bottom=rect.top+m_sizeMinWidthHeight.cy;
	}

	if(rectBest.Height()==rect.Height())
	{
		SetWindowPos(NULL,0,0,
			rect.Width()+::GetSystemMetrics(SM_CXVSCROLL),rect.Height(),
			SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
	}
	else
	{
		if(rectBest.Height()>rect.Height() && 
			rect.Width()<rectBest.Width()+GetSystemMetrics(SM_CXVSCROLL))
		{
			int nDiff=rectBest.Width()+GetSystemMetrics(SM_CXVSCROLL)-rect.Width();
			// vertical scroll bar will be displayed 
			// we need to adjust the width of the window
			if(m_sizeMaxWidthHeight.cx==-1 || 
				rect.Width()+nDiff<=m_sizeMaxWidthHeight.cx)
			{
				rect.right+=nDiff;
			}
		}
	}

	if(::IsWindow(m_container.GetSafeHwnd()))
	{
		m_container.CalcWindowRect(rect);
		m_container.SetWindowPos(NULL,0,0,rect.Width(),rect.Height(),
			SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
	}
	else
	{
		SetWindowPos(NULL,0,0,rect.Width(),rect.Height(),
			SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
	}
}


void CComboOXTree::GetDroppedControlRect(LPRECT lprect) const
{
	if(::IsWindow(GetSafeHwnd()))
	{
		ASSERT(::IsWindow(m_container.GetSafeHwnd()));
		if(::IsWindow(m_container.GetSafeHwnd()))
		{
			m_container.GetWindowRect(lprect);
		}
		else
		{
			GetWindowRect(lprect);
		}
	}
}



BOOL CComboOXTree::GetDroppedState() const
{
	if(::IsWindow(GetSafeHwnd()))
	{
		return IsWindowVisible();
	}

	return FALSE;
}



CRect CComboOXTree::GetBestRect()
{
	CRect rect(0,0,0,0);
	// loop through all visible items and calculate their height and width
	//
	int nLastSubItem=GetColumnsCount()-1;

	HTREEITEM hItem=GetRootItem();
	CRect rectItem;
	if(GetSubItemRect(GetItemCount()-1,nLastSubItem,LVIR_BOUNDS,rectItem))
	{
		if(rect.right<rectItem.right)
		{
			rect.right=rectItem.right;
		}
	}
	while(hItem!=NULL)
	{
		if(GetItemRect(hItem,rectItem,FALSE))
		{
			rect.bottom+=rectItem.Height();
		}
		
		if (GetFirstVisibleItem())
			hItem=GetNextVisibleItem(hItem);
		else
			hItem=NULL;
	}
	//
	////////////////////////////////////////

	// take into account window borders if any exist
	CalcWindowRect(rect);

	return rect;
}


int CComboOXTree::GetItemHeight()
{
	if(::IsWindow(GetSafeHwnd()) && GetCount()>0)
	{
		CRect rect;
		VERIFY(GetItemRect(0,rect,FALSE));
		return rect.Height();
	}
	else
	{
		return OXCOMBOPICKER_DEFAULTITEMHEIGHT;
	}
}



BOOL CComboOXTree::IsThereSelectedItem()
{
	if(!::IsWindow(GetSafeHwnd()))
	{
		return FALSE;
	}

	return (m_hLastSelectedItem!=NULL);
}



CImageList* CComboOXTree::GetSelectedItemImage()
{
	if(!IsThereSelectedItem())
	{
		return NULL;
	}

	int nItemImage=-1;
	int nItemSelectedImage=-1;
	GetItemImage(m_hLastSelectedItem,nItemImage,nItemSelectedImage);
	if(nItemImage==-1)
	{
		return NULL;
	}

	CImageList* pImageList=GetImageList(TVSIL_NORMAL);
	if(pImageList==NULL)
	{
		return NULL;
	}
	ASSERT(nItemImage<pImageList->GetImageCount());

	CImageList* pSelectedItemImageList=new CImageList();
	if(!pSelectedItemImageList->Create(pImageList))
	{
		delete pSelectedItemImageList;
		return NULL;
	}

	for(int nIndex=pSelectedItemImageList->GetImageCount()-1; nIndex>=0; nIndex--)
	{
		if(nIndex!=nItemImage)
		{
			VERIFY(pSelectedItemImageList->Remove(nIndex));
		}
	}

	return pSelectedItemImageList;
}


CString CComboOXTree::GetSelectedItemText()
{
	if(!IsThereSelectedItem())
	{
		return _T("");
	}

	return GetItemText(m_hLastSelectedItem);
}



CFont* CComboOXTree::GetSelectedItemFont()
{
	if(!IsThereSelectedItem())
	{
		return NULL;
	}

	return GetFont();
}



COLORREF CComboOXTree::GetSelectedItemTextColor()
{
	return ::GetSysColor(COLOR_WINDOWTEXT);
}



void CComboOXTree::ResetContent()
{
	if(::IsWindow(GetSafeHwnd()))
	{
		DeleteAllItems();
	}
}



void CComboOXTree::OnAttachToComboPicker()
{
	ASSERT(m_pCombo!=NULL);
	if(m_pCombo!=NULL && ::IsWindow(m_pCombo->GetSafeHwnd()) && 
		::IsWindow(GetSafeHwnd()))
	{
		ASSERT(::IsWindow(m_container.GetSafeHwnd()));
		CRect rect;
		m_pCombo->GetWindowRect(rect);
		CRect rectCalc=rect;
		m_container.CalcWindowRect(rectCalc);
		// set the minimum width for the control
		CSize sizeMinWidthHeight=GetMinWidthHeight();
		sizeMinWidthHeight.cx=2*rect.Width()-rectCalc.Width();
		SetMinWidthHeight(sizeMinWidthHeight);
	}
}



void CComboOXTree::OnChangeMinMaxWidthHeight()
{
	if(::IsWindow(GetSafeHwnd()))
	{
		AutoResize();
	}
}



void CComboOXTree::OnChangeOwnerComboSize()
{
	ASSERT(m_pCombo!=NULL);
	if(m_pCombo!=NULL && ::IsWindow(m_pCombo->GetSafeHwnd()) && 
		::IsWindow(GetSafeHwnd()))
	{
		// set the minimum width for the control
		ASSERT(::IsWindow(m_container.GetSafeHwnd()));
		CRect rect;
		m_pCombo->GetWindowRect(rect);
		CRect rectCalc=rect;
		m_container.CalcWindowRect(rectCalc);
		SetMinWidthHeight(2*rect.Width()-rectCalc.Width(),-1);
	}
}



void CComboOXTree::ShowDropDown(BOOL bShowIt/*=TRUE*/)
{
	if(m_pCombo!=NULL)
	{
		if(bShowIt)
		{
			m_hLastSelectedItem=GetSelectedItem();
		//	ASSERT(CanSelectItem(m_hLastSelectedItem));

			// adjust size of window
			AutoResize();
			
			// make sure the selected item is visible
			if(m_hLastSelectedItem!=NULL)
			{
				EnsureVisible(m_hLastSelectedItem);
			}
		}
		else
		{
			//ASSERT(CanSelectItem(m_hLastSelectedItem));
			if (CanSelectItem(m_hLastSelectedItem))
				SelectItem(m_hLastSelectedItem);
		}
	}
}



BOOL CComboOXTree::CanSelectItem(HTREEITEM hItem)
{
	UNUSED_ALWAYS(hItem);
	return TRUE;

}



void CComboOXTree::ForwardMouseMessage(UINT message, UINT nFlags, 
														   CPoint point)
{
	ASSERT(::IsWindow(GetSafeHwnd()));
	if(!::IsWindow(GetSafeHwnd()))
	{
		return;
	}

	CPoint ptScreen=point;
	ClientToScreen(&ptScreen);
	CWnd* pTargetWnd=CWnd::WindowFromPoint(ptScreen);
	if(pTargetWnd==NULL)
	{
		return;
	}

	ASSERT(pTargetWnd!=this);
	if(pTargetWnd==this)
	{
		return;
	}

	WPARAM wParam=nFlags;

	int nHitTest=
		(int)pTargetWnd->SendMessage(WM_NCHITTEST,0,MAKELONG(ptScreen.x,ptScreen.y));	
	if(nHitTest==HTCLIENT) 
	{
		pTargetWnd->ScreenToClient(&ptScreen);	
	} 
	else 
	{	
		switch(message) 
		{
		case WM_LBUTTONDOWN: 
			{
				message=WM_NCLBUTTONDOWN;		
				break;
			}
		case WM_RBUTTONDOWN: 
			{
				message=WM_NCRBUTTONDOWN;		
				break;
			}
		case WM_MBUTTONDOWN: 
			{
				message=WM_NCMBUTTONDOWN;		
				break;
			}
		case WM_LBUTTONUP: 
			{
				message=WM_NCLBUTTONUP;		
				break;
			}
		case WM_RBUTTONUP: 
			{
				message=WM_NCRBUTTONUP;		
				break;
			}
		case WM_MBUTTONUP: 
			{
				message=WM_NCMBUTTONUP;		
				break;
			}
		case WM_LBUTTONDBLCLK: 
			{
				message=WM_NCLBUTTONDBLCLK;		
				break;
			}
		case WM_RBUTTONDBLCLK: 
			{
				message=WM_NCRBUTTONDBLCLK;		
				break;
			}
		case WM_MBUTTONDBLCLK: 
			{
				message=WM_NCMBUTTONDBLCLK;		
				break;
			}
		case WM_MOUSEMOVE: 
			{
				message=WM_NCMOUSEMOVE;		
				break;
			}
		}
		wParam=nHitTest;
	}

	LPARAM lParam=MAKELONG(ptScreen.x,ptScreen.y);

	pTargetWnd->SendMessage(message,wParam,lParam);
}

void CComboOXTree::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	UNUSED_ALWAYS(point);
	UNUSED_ALWAYS(nFlags);

	HTREEITEM hItem=GetSelectedItem();
	if(hItem!=NULL)
	{
		m_hLastSelectedItem=hItem;
	}
	m_pCombo->ShowDropDown(FALSE);
	m_pCombo->SetFocus();

}

