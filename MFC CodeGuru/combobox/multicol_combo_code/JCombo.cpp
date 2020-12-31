// JCombo.cpp : implementation file
//
#include <afxwin.h>
#include <afxext.h> 
#include "stdafx.h"
#include "JCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTitleTip

CTitleTip::CTitleTip()
{
        // Register the window class if it has not already been registered.
        WNDCLASS wndcls;
        HINSTANCE hInst = AfxGetInstanceHandle();
        if(!(::GetClassInfo(hInst, TITLETIP_CLASSNAME, &wndcls)))
        {
                // otherwise we need to register a new class
                wndcls.style = CS_SAVEBITS ;
                wndcls.lpfnWndProc = ::DefWindowProc;
                wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
                wndcls.hInstance = hInst;
                wndcls.hIcon = NULL;
                wndcls.hCursor = LoadCursor( hInst, IDC_ARROW );
                wndcls.hbrBackground = (HBRUSH)(COLOR_INFOBK + 1); 	//COLOR_HIGHLIGHT;//
                wndcls.lpszMenuName = NULL;
                wndcls.lpszClassName = TITLETIP_CLASSNAME;
                if (!AfxRegisterClass(&wndcls))
                        AfxThrowResourceException();
        }
		TITLETIP_SHOW = TRUE;
		bFocusRect = FALSE;
}

CTitleTip::~CTitleTip()
{
}



BOOL CTitleTip::Create(CWnd * pParentWnd)
{
        ASSERT_VALID(pParentWnd);

        DWORD dwStyle = WS_BORDER | WS_POPUP; 
        DWORD dwExStyle = WS_EX_TOOLWINDOW | WS_EX_TOPMOST;
        m_pParentWnd = pParentWnd;
        return CreateEx( dwExStyle, TITLETIP_CLASSNAME, NULL, dwStyle, 0, 0, 0, 0, 
                NULL, NULL, NULL );
}


// Show                 - Show the titletip if needed
// rectTitle            - The rectangle within which the original 
//                        title is constrained - in client coordinates
// lpszTitleText        - The text to be displayed
// xoffset              - Number of pixel that the text is offset from
//                        left border of the cell
void CTitleTip::Show(CRect rectTitle, LPCTSTR lpszTitleText, int xoffset /*=0*/)
{
        ASSERT( ::IsWindow( m_hWnd ) );
        ASSERT( !rectTitle.IsRectEmpty() );

       // Do not display the titletip is app does not have focus
        if(( GetFocus() == NULL )||(!TITLETIP_SHOW))
		{
			if( IsWindowVisible() ) 
				ShowWindow(FALSE);	
			return;
		}


        // Determine the width of the text
        m_pParentWnd->ClientToScreen( rectTitle );

        CClientDC dctmp(this);
		dc = CDC::FromHandle(dctmp.m_hDC);

		
        CString strTitle(lpszTitleText);
		strTitle += _T("  ");
        CFont *pFont = m_pParentWnd->GetFont(); // use same font as ctrl
	    dc->SelectObject( pFont );

        CRect rectDisplay = rectTitle;
        CSize size = dc->GetTextExtent( strTitle );

		rectDisplay.top   += 24;
		rectDisplay.bottom  += 25;
        rectDisplay.left += xoffset-4;
        rectDisplay.right = rectDisplay.left + size.cx +1;




        // Do not display if the text fits within available space 
        if( rectDisplay.right <= rectTitle.right-xoffset-2 ){
			if( IsWindowVisible() ) 
				ShowWindow(FALSE);	//DestroyWindow();

			return;
		}

		
		//;
		if ( DCB_RESET == dc->GetBoundsRect(&rectTitle,DCB_RESET))
			 dc->SetBoundsRect(NULL,DCB_ENABLE);

		dc->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
	    dc->SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
	 
       // Show the titletip
 	   // If titletip is already displayed, don't do anything.

        if( IsWindowVisible() ) 
		{
		 		MoveWindow(rectDisplay.left, rectDisplay.top, 
                   rectDisplay.Width(), rectDisplay.Height());
			   	
	   			dc->FillSolidRect(&rectTitle,::GetSysColor(COLOR_HIGHLIGHT));
				//if rectDisplay is not being used, let me use it for Text area
				rectDisplay = rectTitle;
				rectDisplay.left += 2;
				dc->DrawText(strTitle,-1,rectDisplay, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
				dc->DrawFocusRect(&rectTitle); 
		}
		else
		{
			SetWindowPos( &wndTop, rectDisplay.left, rectDisplay.top, 
                        rectDisplay.Width(), rectDisplay.Height(), 
                        SWP_SHOWWINDOW|SWP_NOACTIVATE );
			dc->SetBkMode( OPAQUE );
			dc->DrawFocusRect(&rectTitle);
		}

}




/////////////////////////////////////////////////////////////////////////////
// CJCombo

CJCombo::CJCombo()
{
	TotalCol = 1;
	CHECKBOX = FALSE;
}
						
CJCombo::~CJCombo()
{
}


BEGIN_MESSAGE_MAP(CJCombo, CComboBox)
	//{{AFX_MSG_MAP(CJCombo)
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// CJCombo message handlers

 
// if your sorting scheme is different than a standard collating sequence, 
// such as one where the comparisons need to be case-insensitive.)
int CJCombo::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return -1;
}


void CJCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	BOOL bFocus=(lpDrawItemStruct->itemAction & ODA_FOCUS);
	BOOL bDrawEntire=(lpDrawItemStruct->itemAction & ODA_FOCUS);
	BOOL bSelected = ((lpDrawItemStruct->itemState & ODS_SELECTED));

	//Hide the titletip first until dropdown is active
	//but titletip window has been initialised.... (-:
	m_titletip.TITLETIP_SHOW = GetDroppedState();

	if (bFocus||bSelected)
	{
		if (EDGE_STYLE == EDGE) 
			DrawDropList(lpDrawItemStruct, EDGE_HIGHLIGHT);
		else
			DrawDropList(lpDrawItemStruct,HIGH_LIGHT);
	}
	else
	{
		if (EDGE_STYLE == EDGE) 
			DrawDropList(lpDrawItemStruct, EDGE_NORMAL);
		else
			DrawDropList(lpDrawItemStruct,NORMAL);
	}
	
 	if (CHECKBOX)
		if( (lpDrawItemStruct->itemID == CurSel))	//(bSelected)||
			DrawDropList(lpDrawItemStruct,CHECKED);
}


 
// You can actually specify variable heights as long as you set the 
// CBS_OWNERDRAWVARIABLE style.
void CJCombo::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// all items are of fixed size
	// must use CBS_OWNERDRAWVARIABLE for this to work
	if (EDGE_STYLE == EDGE)
		lpMeasureItemStruct->itemHeight = ITEM_HEIGHT;

}


int CJCombo::AddString(LPCTSTR lpszString)
{  	
	return CJCombo::AddItem(lpszString,0,CComboBox::GetCount()); 
}

int CJCombo::AddItem(CString strItem,int nCol,int nRow,int nMask,int nFmt)
{
	int CB_MSG;
	if (nRow != PrevRow)
		CB_MSG = CComboBox::AddString(strItem);
   	PrevRow = nRow;

	cItem[nCol][nRow] = strItem;

	return CB_MSG; 

}




void CJCombo::DrawDropList(LPDRAWITEMSTRUCT lpDrawItemStruct,UINT STATE)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	CRect rcText;

	switch(STATE)
	{
		case EDGE_HIGHLIGHT:
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
			pDC->SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
			rcItem.SetRect(rcItem.left+1,rcItem.top,rcItem.right-2,rcItem.bottom);
			pDC->FillRect(&rcItem,&CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
			if(lpDrawItemStruct->itemID>=0)
				rcText = OnDrawThisText(pDC,lpDrawItemStruct->rcItem,lpDrawItemStruct->itemID);			
			if (CHECKBOX) 
			{
				rcItem.SetRect(rcItem.right-14,rcItem.top,rcItem.right+3,rcItem.bottom);
				pDC->DrawFrameControl(&rcItem, DFC_BUTTON, DFCS_CHECKED );
			}

			
			//rcItem = lpDrawItemStruct->rcItem;
			// You can set your own position for the Tooltip here
			rcText.SetRect(rcText.left+5,rcText.top,rcText.right+5,rcText.bottom); 
			//m_titletip.Show(rcItem, cItem[TotalCol-1][lpDrawItemStruct->itemID], 43 );
			m_titletip.Show(rcText, cItem[TotalCol-1][lpDrawItemStruct->itemID], 0);
									 

		break;

		case EDGE_NORMAL:
			pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
			pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
			pDC->FillRect(&lpDrawItemStruct->rcItem,&CBrush(::GetSysColor(COLOR_WINDOW)));
			
			if(lpDrawItemStruct->itemID>=0)
				OnDrawThisText(pDC,lpDrawItemStruct->rcItem,lpDrawItemStruct->itemID);
			if (CHECKBOX) {
				rcItem.SetRect(rcItem.right-17,rcItem.top,rcItem.right+1,rcItem.bottom);
				//if (lpDrawItemStruct->itemID == CurSel)
				//	pDC->DrawFrameControl(&rcItem, DFC_BUTTON, DFCS_CHECKED);
				//else
					pDC->DrawFrameControl(&rcItem, DFC_BUTTON, DFCS_BUTTONCHECK);
				// We don't need Focus Rect with border. it's too ugly.
				//pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);
			}
	    break;

		case HIGH_LIGHT:
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
			pDC->SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
			pDC->FillRect(&rcItem,&CBrush(::GetSysColor(COLOR_HIGHLIGHT)));

			if (CHECKBOX) 
			{
				rcItem.SetRect(rcItem.right-17,rcItem.top,rcItem.right+1,rcItem.bottom);
				pDC->DrawFrameControl(&rcItem, DFC_BUTTON, DFCS_CHECKED );
			}
			
			rcItem = lpDrawItemStruct->rcItem;	
			rcItem.SetRect(rcItem.left-3,rcItem.top,rcItem.right,rcItem.bottom);
			if(lpDrawItemStruct->itemID>=0)
				OnDrawThisText(pDC,rcItem,lpDrawItemStruct->itemID);
			rcItem.SetRect(rcItem.left-3,rcItem.top,rcItem.right+20,rcItem.bottom);
			pDC->DrawFocusRect(&rcItem);
					
			m_titletip.Show(rcItem, cItem[0][lpDrawItemStruct->itemID], 10 );
			
		break;

		case NORMAL:
			pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
			pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
			pDC->FillRect(&lpDrawItemStruct->rcItem,&CBrush(::GetSysColor(COLOR_WINDOW)));
			
			if (CHECKBOX) {
				rcItem.SetRect(rcItem.right-17,rcItem.top,rcItem.right+1,rcItem.bottom);
				pDC->DrawFrameControl(&rcItem, DFC_BUTTON, DFCS_BUTTONCHECK);				
				pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);
			}
			rcItem = lpDrawItemStruct->rcItem;	
			rcItem.SetRect(rcItem.left-3,rcItem.top,rcItem.right,rcItem.bottom);
			if(lpDrawItemStruct->itemID>=0)
				OnDrawThisText(pDC,rcItem,lpDrawItemStruct->itemID);

	   break;

		case CHECKED:
			pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
			pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
			pDC->FillRect(&lpDrawItemStruct->rcItem,&CBrush(::GetSysColor(COLOR_WINDOW)));
	
			if(lpDrawItemStruct->itemID>=0)
				OnDrawThisText(pDC,lpDrawItemStruct->rcItem,lpDrawItemStruct->itemID);
			rcItem.SetRect(rcItem.right-17,rcItem.top,rcItem.right+1,rcItem.bottom);
			pDC->DrawFrameControl(&rcItem, DFC_BUTTON, DFCS_CHECKED);
	   break;

	}


	
}




BOOL CJCombo::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}





void CJCombo::FormatList(int tCol,int nJustify, BOOL bCheckBox, UINT nEdge)
{
	//Everything gets initialised here
	TotalCol = tCol;
	JUSTIFY = nJustify;
	CHECKBOX = bCheckBox;
	EDGE_STYLE = nEdge;
	PrevRow = -1;
	CurSel = -1; 
	EnableToolTips(TRUE);



}

CRect CJCombo::OnDrawThisText(CDC* pDC,CRect rcItem,int itemID)
{

	CRect rcText = rcItem;
	CRect rcBorder = rcItem;	
	rcText.SetRect(rcText.left,rcText.top,rcText.left+3,rcText.bottom);
	rcBorder.SetRect(rcBorder.left,rcBorder.top,rcText.left+1,rcBorder.bottom);
	int wid = 0;
	for(int j=1;j<=TotalCol;j++){

		if (j!=TotalCol)
		{	
			rcText.SetRect(rcBorder.right+2,rcText.top,rcText.right+ wid,rcText.bottom);
			wid = DrawThisText(pDC,rcText,j-1,itemID);
	
			rcBorder.SetRect(rcBorder.right,rcBorder.top,rcBorder.right+wid,rcBorder.bottom);
			if ((EDGE_STYLE == EDGE)&&(itemID >= -1))
			{
				pDC->DrawEdge(&rcBorder,EDGE_ETCHED,BF_RECT);
			}
		}
		else
		if (j == TotalCol)
		{
			rcText.SetRect(rcBorder.right+4,rcText.top,rcBorder.right+ OFFSET_END,rcText.bottom);
			wid = DrawThisText(pDC,rcText,j-1,itemID);
			rcBorder.SetRect(rcBorder.right,rcBorder.top,rcItem.right-1,rcBorder.bottom);
			if ((EDGE_STYLE == EDGE)&&(itemID >= -1))
			{
				pDC->DrawEdge(&rcBorder,EDGE_ETCHED,BF_RECT); //
			

			}
		}
		
	}
	

	return rcBorder;// for One column 
}

int CJCombo::DrawThisText(CDC * pDC,CRect rcText,
									 int nColumn,int nItem)
{
	CString str;


	if (EDGE_STYLE == EDGE) 
		rcText.SetRect(rcText.left,rcText.top+1,rcText.right,rcText.bottom);
	if ((nColumn >= 0)&&(nItem >= 0))
		str = cItem[nColumn][nItem];
	if (str == _T("")) return 0;

	if (EDGE_STYLE == EDGE)
		pDC->DrawText(str,-1,rcText, JUSTIFY | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
	else
	{	///////This operation is for showing hint when the box is droping down.////
		//rcText.SetRect(rcText.left,rcText.top,rcText.right+30,rcText.bottom);
		pDC->TabbedTextOut(rcText.left,rcText.top,str,0,NULL,rcText.left);

	}

	//plus offset for additional space between columns
	if (cItem[nColumn][GetCount()-nItem].GetLength() > cItem[nColumn][0].GetLength())
	{
		ColWidth[nColumn] = pDC->GetTextExtent(cItem[nColumn][nItem]).cx +12;
		SetRedraw(TRUE); // Redraw if the columns are different
	} 
	else
	if ((nItem==0) ||(cItem[nColumn][GetCount()-nItem].GetLength() == cItem[nColumn][0].GetLength()))
		//Draw the first item then compare
		ColWidth[nColumn] = pDC->GetTextExtent(cItem[nColumn][0]).cx +12;


    
	return ColWidth[nColumn];  

}


void CJCombo::PreSubclassWindow() 
{
	ModifyStyleEx(WS_EX_TOPMOST,NULL,0);
	CComboBox::PreSubclassWindow();
	m_titletip.Create(this);

}




void CJCombo::OnMouseMove(UINT nFlags, CPoint point) 
{
	m_titletip.TITLETIP_SHOW = TRUE;
	CComboBox::OnMouseMove(nFlags, point);
}

void CJCombo::OnCloseup() 
{
	m_titletip.TITLETIP_SHOW = FALSE;

}




int CJCombo::GetLBText(int col, int nIndex, CString & rString)
{
	rString = cItem[col][nIndex];
	return rString.GetLength();

}

int CJCombo::SetCurSel(int nSelect)
{
	CurSel = nSelect;
	return CComboBox::SetCurSel(nSelect);
}

