// DBListBox.cpp : implementation file
//

#include "stdafx.h"
#include "Pizza.h"
#include "DBListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBListBox

CDBListBox::CDBListBox()
{
}

CDBListBox::~CDBListBox()
{
}


BEGIN_MESSAGE_MAP(CDBListBox, CListBox)
	//{{AFX_MSG_MAP(CDBListBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBListBox message handlers

void CDBListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	lpMeasureItemStruct->itemHeight = m_Height;
}

void CDBListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
		CDC		tmpDC;
	CString tmpStr;

	tmpDC.Attach( lpDrawItemStruct->hDC );
	
	CRect tmpRect = lpDrawItemStruct->rcItem;
	tmpRect.top += 1;
	tmpRect.left += 1;
	tmpRect.right -= 1;

	if( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE )
	{
		GetText( lpDrawItemStruct->itemID, tmpStr );
		ExtractString( CMD_RESET, tmpStr );
		short tmpTab;
		while( ( tmpTab = ExtractString( CMD_NEXT, tmpStr ) ) != -1 )
			if( tmpTab < MAX_TABSTOP )
				tmpDC.TextOut( ( lpDrawItemStruct->rcItem ).left +
							   TabStops[ tmpTab ], 
						       ( lpDrawItemStruct->rcItem ).top, tmpStr );
		
		tmpDC.FrameRect( tmpRect, &CBrush( RGB( 0, 0 ,0 ) ) );
		
		if( lpDrawItemStruct->itemState & ODS_SELECTED )
			tmpDC.InvertRect( tmpRect );
	}

	if( lpDrawItemStruct->itemAction & ODA_SELECT )
		tmpDC.InvertRect( tmpRect );
	
	tmpDC.Detach();
}

BOOL CDBListBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	return CListBox::PreCreateWindow(cs);
}

void CDBListBox::Init(UINT iHeight, const RECT & rect, CWnd * pParentWnd, UINT nID)
{
	m_Height = iHeight;
	CListBox::Create( WS_CHILD | WS_VISIBLE | WS_TABSTOP |
					  WS_BORDER | WS_VSCROLL | LBS_HASSTRINGS |
					  LBS_NOTIFY | LBS_OWNERDRAWFIXED,
					  rect, pParentWnd, nID );
}

void CDBListBox::SetTabStop(short idxTab, short posTab)
{
	if( idxTab < MAX_TABSTOP )
		TabStops[ idxTab ] = posTab;
}

// String data will be changeg
short CDBListBox::ExtractString(COMMAND Command, CString & String)
{
	static CString Buffer;
	static short   Index;
	static short   CurrentTab;

	if( Command == CMD_RESET )
	{
		Buffer = String;
		Index = 0;
		CurrentTab = -1;
	}
	else if( Command == CMD_NEXT )
	{
		String = "";
		
		if( ( (const char *)Buffer )[ Index ] == 0 )
		{
			CurrentTab = -1;
			goto Fin;
		}
		
		while( ( ( (const char *)Buffer )[ Index ] != '#' ) &&
			   ( ( (const char *)Buffer )[ Index ] != 0 ) )
		{
			String += ( (const char *)Buffer )[ Index ];
			Index ++;
		}

		if( ( (const char *)Buffer )[ Index ] == '#' )
			Index++;

		CurrentTab++;
	}

Fin:
	return CurrentTab;
}

// if return == "NS" there is no current selection in the list box
CString CDBListBox::GetCurrentID()
{
	int CurSel;
	CString tmpString = "NS";

	CurSel = GetCurSel();
	if( CurSel != LB_ERR )
	{
		GetText( CurSel, tmpString );
		ExtractString( CMD_RESET, tmpString );
		ExtractString( CMD_NEXT, tmpString );
	}
	
	return tmpString;
}

