// SkinnedListBox.cpp : implementation file
//

#include "stdafx.h"
#include "SkinnedListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinnedListBox

CSkinnedListBox::CSkinnedListBox()
{
	m_nChildControlID = IDC_CHILD_BUTTONS;
	m_nLeftPad = 0;
	m_nTopPad = 0;
	m_lSelectedItem = -1;
	m_bProcess = TRUE;
	m_lTextAlign = TEXT_ALIGN_CENTER_HORIZ | TEXT_ALIGN_CENTER_VERT;
}

CSkinnedListBox::~CSkinnedListBox()
{
	POSITION pos = m_cobjElementList.GetHeadPosition();

	while(pos != NULL)
	{
		CSkinnedButton *pcbtnTemp = (CSkinnedButton*) m_cobjElementList.GetNext(pos);
		delete pcbtnTemp;
		pcbtnTemp = 0;
	}

	m_cobjElementList.RemoveAll();
}


BEGIN_MESSAGE_MAP(CSkinnedListBox, CWnd)
	//{{AFX_MSG_MAP(CSkinnedListBox)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSkinnedListBox message handlers

BOOL CSkinnedListBox::CreateSkinControl(LPCTSTR lpszWindowName, 
										LPRECT lpRect, 
										CWnd *pParentWnd, 
										UINT nControlID, 
										long lFlags)
{
	m_csText = lpszWindowName;
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;
	m_pParentWnd = pParentWnd;
	m_nControlID = nControlID;
	
	m_csFontName = "Arial";
	m_nFontSize = 16;
	m_nFontStyle = FONT_NORMAL;
	m_crBackgroundColorHover = RGB(143,143,143);
	m_crBackgroundColorPressed = RGB(82,145,207);
	m_crBackgroundColorUnPressed = RGB(14,18,23);
	m_crForegroundColor = RGB(232,232,232);
	
	m_lFlags = lFlags;

	if(m_lFlags & FL_LISTBOX_TYPE_COMBOCHILD)
	{
		m_hControllerHwnd = (HWND)HIWORD(lFlags);
	}
	else
	{
		m_hControllerHwnd = NULL;
	}

	long lStyle;

	if(m_lFlags & FL_LISTBOX_TYPE_COMBOCHILD)
	{
		lStyle = WS_CHILD|WS_BORDER|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	}
	else
	{
		lStyle = WS_CHILD|WS_VISIBLE|WS_BORDER|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	}

	if(CWnd::Create(NULL, 
					m_csText, 
					lStyle, 
					*lpRect,
					pParentWnd, 
					nControlID, 
					NULL))
	{
		CWnd::BringWindowToTop();

		CRect rect;
		GetClientRect(rect);
		rect.bottom = rect.top + m_nTopPad;
		m_ContainerWnd.Create(0, m_csText, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, rect,this, IDC_LIST_CONTAINER);
		m_nContainerTop = 0;

		m_scroll.SetImageResource(155/*IDB_BITMAP_SCROLLBAR_BACK*/);
		m_scroll.SetScrollButtonImageResource(157/*IDB_BITMAP_SCROLLBAR_BUTTON*/);
		m_scroll.SetScrollUpButtonImageResource(154/*IDB_BITMAP_SCROLLBAR_UP*/);
		m_scroll.SetScrollDownButtonImageResource(156/*IDB_BITMAP_SCROLLBAR_DOWN*/);
		m_scroll.CreateSkinControl("", CRect(m_nWidth-16,0,m_nWidth,m_nHeight-2), this, IDC_LISTBOX_SCROLL);
		m_scroll.ShowWindow(SW_HIDE);

		if(PrepareFont())
		{
			SetFont(&m_cfFaceTextFont, TRUE);
		}

		return TRUE;
	}
	
	return FALSE;
}

void CSkinnedListBox::MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags)
{
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;

	MoveWindow(lpRect, bRedraw);
}

BOOL CSkinnedListBox::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
		case WM_USER:
			switch(LOWORD(pMsg->wParam))
			{
				case MSG_LBUTTONDOWN:
					
					if(HIWORD(pMsg->wParam) != IDC_LISTBOX_SCROLL)
					{
						POSITION pos;

						pos = m_cobjElementList.GetHeadPosition();
												
						m_lSelectedItem = GetCurSel();

						if((m_lFlags & FL_LISTBOX_TYPE_MULTISELECT))
						{
							m_nLastSelected = HIWORD(pMsg->wParam)%IDC_CHILD_BUTTONS;
						}
						else
						{
							int nCount=0;
							while(pos!=NULL)
							{
								if(((CSkinnedButton *)m_cobjElementList.GetAt(pos))->GetControlID() != HIWORD(pMsg->wParam))
								{
									((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
								}

								m_cobjElementList.GetNext(pos);
								nCount++;
							}
						}

						::PostMessage((this->GetParent())->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_COMMAND, m_nControlID), GetCurSel());
					}

					return TRUE;

				case MSG_SCROLL:
					switch(HIWORD(pMsg->wParam))
					{
						case IDC_LISTBOX_SCROLL:
							{							
								TRACE("\nlist scroll %d - %d", HIWORD(pMsg->wParam), IDC_LISTBOX_SCROLL);
								CRect rect;

								m_ContainerWnd.GetClientRect(rect);

								//scroll the list
								int nNewTop = (int)(m_nContainerTop - ((rect.Height() - m_nHeight) * ((float)pMsg->lParam/100)));
								m_ContainerWnd.SetWindowPos(NULL, 0, nNewTop, 0, 0, SWP_NOSIZE);
								m_ContainerWnd.UpdateWindow();
								m_scroll.BringWindowToTop();
								m_scroll.UpdateWindow();
							}
							break;

						default:
							break;
					}
					return TRUE;
			}
			break;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}

int CSkinnedListBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	return 0;
}

void CSkinnedListBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CBrush brush;
	brush.CreateSolidBrush(RGB(14,18,23));
	dc.FillRect(CRect(0, 0, m_nWidth, m_nHeight), &brush);

	//UpdateList();


	int nTop = m_nTopPad;
	POSITION pos;	
	
	pos = m_cobjElementList.GetHeadPosition();

	for(int nCount=1; nCount<=m_cobjElementList.GetCount(); nCount++)
	{
		CSkinnedButton *pcsbtnTemp = 0;

		CRect rect;		
		m_ContainerWnd.GetClientRect(rect);

		if(rect.Height() < nTop)
		{
			m_ContainerWnd.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height() + m_nFontSize, SWP_NOMOVE);
		}

		pcsbtnTemp = (CSkinnedButton *)m_cobjElementList.GetNext(pos);

		pcsbtnTemp->SetFontName(m_csFontName);
		pcsbtnTemp->SetFontSize(m_nFontSize);
		pcsbtnTemp->SetFontStyle(m_nFontStyle);

		pcsbtnTemp->SetForegroundColor(m_crForegroundColor);

		pcsbtnTemp->MoveWindowEng(CRect(m_nLeftPad, nTop, m_nWidth - (m_nLeftPad+2), nTop + m_nFontSize), TRUE);
		pcsbtnTemp->SetBackgroundColor(BACKGROUND_STATE_PRESSED, GetBackgroundColor(BACKGROUND_STATE_PRESSED));
		pcsbtnTemp->SetBackgroundColor(BACKGROUND_STATE_UNPRESSED, RGB(14,18,23)/*GetBackgroundColor(BACKGROUND_STATE_UNPRESSED)*/);
		pcsbtnTemp->SetBackgroundColor(BACKGROUND_STATE_HOVER, RGB(143,143,143));//GetBackgroundColor(BACKGROUND_STATE_HOVER));

		nTop += pcsbtnTemp->GetHeight();

		pcsbtnTemp = 0;
	}

	//check if a scroll bar is required
	if(nTop > m_nHeight && !m_scroll.IsWindowVisible())
	{
		CRect rect;		
		m_ContainerWnd.GetClientRect(rect);

		m_ContainerWnd.SetWindowPos(NULL, 0, 0, m_nWidth-16, rect.Height(), SWP_NOMOVE);

		m_scroll.MoveWindow(m_nWidth-16, 0, m_nWidth, m_nHeight, TRUE);
		m_scroll.SetRange(0,100);
		m_scroll.ShowWindow(SW_SHOWNORMAL);
		m_scroll.BringWindowToTop();
	}

	CRect rect;
	GetClientRect(rect);
	rect.right -= 30;
	CDC *dcContainer = m_ContainerWnd.GetDC();
	if(dcContainer != NULL)
	{
		dcContainer->FillSolidRect(rect, RGB(255,255,255));
	}
	
	pos =m_cobjElementList.GetHeadPosition();
	while(pos != NULL)
	{
		//((CSkinnedButton*)m_cobjElementList.GetNext(pos))->UpdateWindow(); //Invalidate(TRUE);
		//((CSkinnedButton*)m_cobjElementList.GetNext(pos))->ShowWindow(SW_SHOWNORMAL);
		((CSkinnedButton*)m_cobjElementList.GetAt(pos))->UpdateMemoryDC();
		((CSkinnedButton*)m_cobjElementList.GetAt(pos))->UpdateWindow();
		m_cobjElementList.GetNext(pos);
	}
	// Do not call CWnd::OnPaint() for painting messages
}

void CSkinnedListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_lFlags & FL_LISTBOX_TYPE_COMBOCHILD)
	{
/*		ReleaseCapture();
		if(IsWindowVisible())
		{
			ShowWindow(SW_HIDE);
		}*/
//		::PostMessage((GetParent())->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_LBUTTONDOWN, m_nControlID), 0);
	}
	else
	{
		SetFocus();
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CSkinnedListBox::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	CWnd::OnLButtonUp(nFlags, point);
}

void CSkinnedListBox::OnMouseMove(UINT nFlags, CPoint point) 
{
/*	
	TRACE("\nlistbox mouse in %d %d", point.x, point.y);
	POSITION pos = m_cobjElementList.GetHeadPosition();

	((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetBackgroundColor(BUTTON_STATE_HOVER, RGB(0,0,0));
	::SendMessage(((CSkinnedButton *)m_cobjElementList.GetAt(pos))->GetSafeHwnd(), WM_MOUSEMOVE, 0,0);
	//AfxMessageBox("jk");
*/
	CWnd::OnMouseMove(nFlags, point);
}

void CSkinnedListBox::AddString(LPTSTR lpszItem)
{
	POSITION pos;

	pos = m_cobjElementList.AddTail(new CSkinnedButton);
	//((CSkinnedButton *)m_cobjElementList.GetAt(pos))->AttachSkin("listbox", (LPTSTR)(LPCTSTR)m_csControlName, this, m_nChildControlID, FL_BUTTON_TYPE_TOGGLE);
	((CSkinnedButton *)m_cobjElementList.GetAt(pos))->CreateSkinControl(lpszItem, CRect(0,0,0,0), &m_ContainerWnd, m_nChildControlID, FL_BUTTON_TYPE_TOGGLE);
	((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetForegroundColor(RGB(232,232,232));
	((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetTextColor(RGB(232,232,232));
	((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetControlText(lpszItem);
	((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetTextAlignment(GetTextAlignment());

	m_nChildControlID++;
	Invalidate(TRUE);
}

BOOL CSkinnedListBox::DeleteString(LPTSTR lpszItem)
{
	POSITION pos;
	
	pos = m_cobjElementList.GetHeadPosition();

	while(pos)
	{
		CString csTemp;

		csTemp = ((CSkinnedButton *)m_cobjElementList.GetAt(pos))->GetControlText();
		if(csTemp == lpszItem)
		{
			if(pos != NULL)
			{
				CSkinnedButton *cbtnTemp = (CSkinnedButton*) m_cobjElementList.GetAt(pos);
				m_cobjElementList.RemoveAt(pos);
				delete cbtnTemp;

				m_nChildControlID--;
				Invalidate(TRUE);
				return TRUE;
			}
		}
		m_cobjElementList.GetNext(pos);
	}

	return FALSE;
}

BOOL CSkinnedListBox::DeleteString(int nIndex)
{
	POSITION pos;
	
	pos = m_cobjElementList.FindIndex(nIndex);

	if(pos != NULL)
	{
		CSkinnedButton *cbtnTemp = (CSkinnedButton*) m_cobjElementList.GetAt(pos);
		m_cobjElementList.RemoveAt(pos);
		delete cbtnTemp;

		m_nChildControlID--;
		Invalidate(TRUE);

		return TRUE;
	}

	return FALSE;
}

BOOL CSkinnedListBox::UpdateString(int nIndex, LPTSTR lpszItem)
{
	POSITION pos;
	
	pos = m_cobjElementList.FindIndex(nIndex);

	if(pos != NULL)
	{
		CSkinnedButton *cbtnTemp = (CSkinnedButton*) m_cobjElementList.GetAt(pos);
		cbtnTemp->SetControlText(lpszItem);
		cbtnTemp->SetTextAlignment(GetTextAlignment());

		return TRUE;
	}

	return FALSE;
}

void CSkinnedListBox::InsertString(int nIndex, LPTSTR lpszItem)
{
	POSITION pos;

	if(nIndex == -1)
	{
		AddString(lpszItem);
	}
	else
	{
		if (nIndex > m_cobjElementList.GetCount() - 1)
		{
			AddString(lpszItem);
		}
		else
		{
			pos = m_cobjElementList.GetHeadPosition();

			if (pos != NULL)
			{
				for(int nCount=1; nCount<=nIndex; nCount++)
				{
					m_cobjElementList.GetNext(pos);
				}

				m_cobjElementList.InsertBefore(pos, new CSkinnedButton);
				//((CSkinnedButton *)m_cobjElementList.GetAt(pos))->AttachSkin("button", (LPTSTR)(LPCTSTR)m_csControlName, this, m_nChildControlID, FL_BUTTON_TYPE_TOGGLE);
				((CSkinnedButton *)m_cobjElementList.GetAt(pos))->CreateSkinControl(lpszItem, CRect(0,0,0,0), &m_ContainerWnd, m_nChildControlID, FL_BUTTON_TYPE_TOGGLE);
				((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetForegroundColor(RGB(232,232,232));
				((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetTextColor(RGB(232,232,232));
				((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetControlText(lpszItem);
				((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetTextAlignment(GetTextAlignment());
				m_nChildControlID++;
			}
		}
	}
}

void CSkinnedListBox::ResetContent()
{
	POSITION pos = m_cobjElementList.GetHeadPosition();

	while(pos != NULL)
	{
		CSkinnedButton *cbtnTemp = (CSkinnedButton*) m_cobjElementList.GetAt(pos);
		delete cbtnTemp;

		m_cobjElementList.GetNext(pos);
		m_nChildControlID--;
	}

	m_cobjElementList.RemoveAll();
	Invalidate(TRUE);
}

int CSkinnedListBox::FindString(LPCTSTR lpszItem)
{
	POSITION pos;
	int nItemPosition = 0;

	pos = m_cobjElementList.GetHeadPosition();

	while(pos)
	{
		if(((CSkinnedButton *)m_cobjElementList.GetNext(pos))->GetControlText() == lpszItem)
		{
			return nItemPosition;
		}
		nItemPosition++;
	}

	return -1;
}

BOOL CSkinnedListBox::SelectString(LPTSTR lpszItem)
{
	POSITION pos;

	pos = m_cobjElementList.GetHeadPosition();
	
	while(pos)
	{
		if( ((CSkinnedButton *)m_cobjElementList.GetNext(pos))->GetControlText() == lpszItem )
		{
			((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SendMessage(WM_LBUTTONDOWN);
			((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SendMessage(WM_LBUTTONUP);
			return TRUE;
		}
	}

	return FALSE;
}

int CSkinnedListBox::GetCount()
{
	return m_cobjElementList.GetCount();
}

BOOL CSkinnedListBox::GetSel(int nIndex)
{
	POSITION pos;

	pos = m_cobjElementList.GetHeadPosition();

	for(int nCount=1; nCount<nIndex; nCount++)
	{
		m_cobjElementList.GetNext(pos);
	}
	if( ((CSkinnedButton *)m_cobjElementList.GetNext(pos))->GetCurrentState() == BUTTON_STATE_PRESSED)
	{
		return TRUE;
	}

	return FALSE;
}

int CSkinnedListBox::GetText(int nIndex, LPTSTR lpszBuffer)
{
	POSITION pos;

	if(nIndex < 0)
	{
		lstrcpy(lpszBuffer, "");
		return 0;
	}

	pos = m_cobjElementList.GetHeadPosition();

	for(int nCount=0; nCount<nIndex; nCount++)
	{
		m_cobjElementList.GetNext(pos);
	}

	lstrcpy(lpszBuffer, ((CSkinnedButton *)(m_cobjElementList.GetNext(pos)))->GetControlText());
	return strlen(lpszBuffer);
}

int CSkinnedListBox::GetTextLength(int nIndex)
{
	CString csTemp;

	return GetText(nIndex, (LPTSTR)(LPCTSTR)csTemp);
}

int CSkinnedListBox::GetCurSel()
{
	POSITION pos;
	int nCount = 0;

	pos = m_cobjElementList.GetHeadPosition();

	while(pos!= NULL)
	{
		if( ((CSkinnedButton *)m_cobjElementList.GetAt(pos))->GetCurrentState() == BUTTON_STATE_PRESSED)
		{
			return nCount;
		}

		m_cobjElementList.GetNext(pos);
		nCount++;
	}

	return -1;
}

BOOL CSkinnedListBox::ClearCurSel(int nIndex)
{
	POSITION pos;

	if(nIndex > m_cobjElementList.GetCount())
	{
		return FALSE;
	}

	pos = m_cobjElementList.GetHeadPosition();

	if(pos != NULL)
	{
		for(int nCount=1; nCount<=nIndex; nCount++)
		{
			m_cobjElementList.GetNext(pos);
		}
	}

	((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
	return TRUE;
}

BOOL CSkinnedListBox::SetCurSel(int nIndex)
{
	POSITION pos;

	if(nIndex > m_cobjElementList.GetCount())
	{
		return FALSE;
	}
/*
	pos = m_cobjElementList.GetHeadPosition();

	if(m_lSelectedItem != -1)
	{
		while(pos != NULL)
		{
			((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
			m_cobjElementList.GetNext(pos);
		}
	}
*/
	pos = m_cobjElementList.GetHeadPosition();

	if(m_lFlags & FL_LISTBOX_TYPE_MULTISELECT)
	{
		if(pos != NULL)
		{
			for(int nCount=1; nCount<=nIndex; nCount++)
			{
				m_cobjElementList.GetNext(pos);
			}
		}

		((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetToggleButtonState(BUTTON_STATE_PRESSED);
	}
	else
	{
		if(pos != NULL)
		{
			//for(int nCount=0; nCount<m_cobjElementList.GetCount(); nCount++)
			//{
			//	m_cobj
			//}

			for(int nCount=1; nCount<=nIndex; nCount++)
			{
				m_cobjElementList.GetNext(pos);
			}
		}

		((CSkinnedButton *)m_cobjElementList.GetAt(pos))->SetToggleButtonState(BUTTON_STATE_PRESSED);
	}

	return TRUE;
}

int CSkinnedListBox::GetSelCount()
{
	POSITION pos;
	int nCount;


	pos = m_cobjElementList.GetHeadPosition();
	nCount = 0;

	while(pos)
	{
		if(((CSkinnedButton *)m_cobjElementList.GetNext(pos))->GetCurrentState() == BUTTON_STATE_PRESSED)
		{
			nCount++;
		}
	}

	return nCount;
}

void CSkinnedListBox::SetLeftPadding(int nPad)
{
	m_nLeftPad = nPad;
	Invalidate(TRUE);
}

void CSkinnedListBox::SetTopPadding(int nPad)
{
	m_nTopPad = nPad;
	Invalidate(TRUE);
}

void CSkinnedListBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSkinnedListBox::OnKillFocus(CWnd *pNewWnd)
{

}

void CSkinnedListBox::BltEx()
{

}

void CSkinnedListBox::SetTextAlignment(int nAlignment)
{
	m_lTextAlign = nAlignment;

	if(m_hWnd != NULL)
	{
		Invalidate(TRUE);
	}
}

long CSkinnedListBox::GetTextAlignment()
{
	return m_lTextAlign;
}

void CSkinnedListBox::OnShowWindow( BOOL bShow, UINT nStatus )
{/*
	if(m_lFlags & FL_LISTBOX_TYPE_COMBOCHILD && bShow)
	{
		SetCapture();
	}
	else
	{
		//ReleaseCapture();
	}*/
}

void CSkinnedListBox::OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if(nState == WA_ACTIVE)
	{
		Invalidate(TRUE);
	}
}

void CSkinnedListBox::UpdateList()
{
	int nTop = m_nTopPad;
	POSITION pos;	
	
	pos = m_cobjElementList.GetHeadPosition();

	for(int nCount=1; nCount<=m_cobjElementList.GetCount(); nCount++)
	{
		CSkinnedButton *pcsbtnTemp;

		CRect rect;		
		m_ContainerWnd.GetClientRect(rect);

		if(rect.Height() < nTop)
		{
			m_ContainerWnd.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height() + m_nFontSize, SWP_NOMOVE);
		}

		pcsbtnTemp = (CSkinnedButton *)m_cobjElementList.GetNext(pos);

		pcsbtnTemp->SetFontName(m_csFontName);
		pcsbtnTemp->SetFontSize(m_nFontSize);
		pcsbtnTemp->SetFontStyle(m_nFontStyle);

		pcsbtnTemp->SetForegroundColor(RGB(232,232,232));//m_crForegroundColor);

		pcsbtnTemp->MoveWindowEng(CRect(m_nLeftPad, nTop, m_nWidth - (m_nLeftPad+2), nTop + m_nFontSize), TRUE);
		pcsbtnTemp->SetBackgroundColor(BACKGROUND_STATE_PRESSED, GetBackgroundColor(BACKGROUND_STATE_PRESSED));
		pcsbtnTemp->SetBackgroundColor(BACKGROUND_STATE_UNPRESSED, GetBackgroundColor(BACKGROUND_STATE_UNPRESSED));
		pcsbtnTemp->SetBackgroundColor(BACKGROUND_STATE_HOVER, GetBackgroundColor(BACKGROUND_STATE_HOVER));
		pcsbtnTemp->SetTextColor(RGB(232,232,232));

		nTop += pcsbtnTemp->GetHeight();
	}

	//check if a scroll bar is required
	if(nTop > m_nHeight)
	{
		CRect rect;		
		m_ContainerWnd.GetClientRect(rect);

		m_ContainerWnd.SetWindowPos(NULL, 0, 0, m_nWidth-17, rect.Height(), SWP_NOMOVE);

		m_scroll.MoveWindow(m_nWidth-16, 0, m_nWidth, m_nHeight, TRUE);
		m_scroll.SetRange(0,100);
		m_scroll.ShowWindow(SW_SHOWNORMAL);
		m_scroll.BringWindowToTop();
	}

	CRect rect;
	GetClientRect(rect);
	rect.right -= 30;
	CDC *dcContainer = m_ContainerWnd.GetDC();
	dcContainer->FillSolidRect(rect, BLACK/*RGB(255,255,255)*/);
	
	pos =m_cobjElementList.GetHeadPosition();
	while(pos != NULL)
	{
		((CSkinnedButton*)m_cobjElementList.GetNext(pos))->Invalidate(TRUE);
	}
}

void CSkinnedListBox::UnselectItem(int nIndex)
{
	POSITION pos = m_cobjElementList.GetHeadPosition();

	if(pos != NULL)
	{
		for(int nCount=0; nCount<nIndex; nCount++)
		{
			m_cobjElementList.GetNext(pos);
		}

		((CSkinnedButton*)m_cobjElementList.GetAt(pos))->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
	}
}

void CSkinnedListBox::UnselectAll()
{
	POSITION pos = m_cobjElementList.GetHeadPosition();

	if(pos != NULL)
	{
		for(int nCount=0; nCount<m_cobjElementList.GetCount(); nCount++)
		{
			((CSkinnedButton*)m_cobjElementList.GetAt(pos))->SetToggleButtonState(BUTTON_STATE_UNPRESSED);
			m_cobjElementList.GetNext(pos);
		}		
	}
}

int CSkinnedListBox::GetSelItems(int *nItems)
{
	int nCount=0;
	int nCtr=0;

	POSITION pos = m_cobjElementList.GetHeadPosition();
	
	while(pos != NULL)
	{
		if(((CSkinnedButton*)m_cobjElementList.GetAt(pos))->GetCurrentState() == BUTTON_STATE_PRESSED)
		{
			nItems[nCtr] = nCount;
			nCtr++;
		}

		m_cobjElementList.GetNext(pos);
		nCount++;
	}

	return nCtr;
}

int CSkinnedListBox::GetLastSelected()
{
	return m_nLastSelected;
}

CDC* CSkinnedListBox::GetItemDC(int nItemIndex)
{
	POSITION pos;

	pos = m_cobjElementList.GetHeadPosition();

	if(pos == NULL)
	{
		return NULL;
	}

	for(int nCount=0; nCount<nItemIndex; nCount++)
	{
		m_cobjElementList.GetNext(pos);
	}

	return ((CSkinnedButton*)(m_cobjElementList.GetAt(pos)))->GetControlDC();
}
