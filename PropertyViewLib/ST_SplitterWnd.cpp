//  Project     : general base class
//  Compiler    : Visual C++ 5.0 / 6.0
//  Plattform   : Windows 95/98, Windows NT 3.51/4.0/2000
//  File        : ST_SplitterWnd.cpp 
//  Programmer  : dz, SoftToys
//  Copyright   : 2001 SoftToys
//  Contact     : info@softtoys.com
//  Description : base class for handling splitter windows 
//  History     : 02.Sept. 2001 Version 1.0
//


#include "stdafx.h"
#include "ST_SplitterWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(ST_SplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(ST_SplitterWnd)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ST_SplitterWnd::ST_SplitterWnd( int nLevel /* = 0 */ )
{
	m_iFixedSizePane  = 0;		//0 or 1 is has fixed size, the other pane resizes on window resize
	m_nFixedSize      = 100;
	m_nBarSize        = 11;		//first guess, recalculated after each recalclayout

	m_nHiddenPane = -1;
//	m_nHiddenCol = -1;
//	m_nHiddenRow = -1;
	m_sRegKey    = _T("SplitterWnd");
	m_nLevel     = nLevel;

	m_nPaneSize[0]    = 100;
	m_nPaneSize[1]    = 100;
	m_nPaneMinSize[0] = 10;
	m_nPaneMinSize[1] = 10;

	m_pSubSplitterWnd[0] = NULL;
	m_pSubSplitterWnd[1] = NULL;

	m_nCurrentView[0] = 0;
	m_nCurrentView[1] = 0;
}

ST_SplitterWnd::~ST_SplitterWnd()
{
//   SaveToRegistry();

   if( m_pSubSplitterWnd[0] != NULL )
   {
	   delete m_pSubSplitterWnd[0];
	   m_pSubSplitterWnd[0] = NULL;
   }

   if( m_pSubSplitterWnd[1] != NULL )
   {
	   delete m_pSubSplitterWnd[1];
	   m_pSubSplitterWnd[1] = NULL;
   }

}

bool ST_SplitterWnd::Create( CWnd* pParentWnd , CRuntimeClass* pView1 , CRuntimeClass* pView2 , CCreateContext* pContext , bool bVertical , int nID /* = AFX_IDW_PANE_FIRST */ )
{
	int nRow;
	int nCol;

	m_bVertical = bVertical;

	if (bVertical)
	{
		nRow = 1;
		nCol = 2;
	}
	else
	{
		nRow = 2;
		nCol = 1;
	}

	VERIFY( CreateStatic( pParentWnd , nRow , nCol , WS_CHILD|WS_VISIBLE|WS_BORDER , nID ) );

	if (pView1 != NULL)
	{
		VERIFY(CreateView(0,0,pView1,CSize(10,10),pContext));
	}
	
	if (pView2 != NULL)
	{
		if (bVertical)
		{
			VERIFY(CreateView(0,1,pView2,CSize(10,10),pContext));
		}
		else
		{
			VERIFY(CreateView(1,0,pView2,CSize(10,10),pContext));
		}
	}

	return true;
}

/*
void ST_SplitterWnd::SetInitialStatus()
{
	int c;
	int r;

	CString sSubKey;

	sSubKey.Format(_T("Panes_%d"),m_nLevel);

	CString s;

	s = AfxGetApp()->GetProfileString( m_sRegKey , sSubKey , _T("-1 150 -1 150") );

	sscanf( s , _T("%d %d %d %d") , &c , &m_nPaneSize[0] , &r , &m_nPaneSize[1] );

	if( m_bVertical )
	{
		SetColumnInfo( 0 , m_nPaneSize[0] , m_nPaneMinSize[0] );
		SetColumnInfo( 1 , m_nPaneSize[1] , m_nPaneMinSize[1] );

		if( c > -1 )
		{
			ToggleSide(c); 
		}
		
		if( c == -1 )
		{
			RecalcLayout();
		}
	}
	else
	{
		SetRowInfo( 0 , m_nPaneSize[0] , m_nPaneMinSize[0] );
		SetRowInfo( 1 , m_nPaneSize[1] , m_nPaneMinSize[1] );

		if (r > -1)
		{
			ToggleSide(r);
		}

		if (r == -1)
		{
			RecalcLayout();
		}
	}
	
	if( m_pSubSplitterWnd[0] != NULL )
	{
		m_pSubSplitterWnd[0]->SetInitialStatus();
	}

	if( m_pSubSplitterWnd[1] != NULL )
	{
		m_pSubSplitterWnd[1]->SetInitialStatus();
	}
}
*/

/*
void ST_SplitterWnd::SaveToRegistry()
{
   CString s;
   CString sSubKey;
   sSubKey.Format(_T("Panes_%d"),m_nLevel);

   RememberSize();
   if (m_nPaneSize[0] == -1) m_nPaneSize[0] = 100;
   if (m_nPaneSize[1] == -1) m_nPaneSize[1] = 100;

   s.Format(_T("%d %d %d %d"),m_nHiddenCol,m_nPaneSize[0],m_nHiddenRow,m_nPaneSize[1]);
   AfxGetApp()->WriteProfileString(m_sRegKey,sSubKey,s);

   if (m_pSubSplitterWnd[0] != NULL) m_pSubSplitterWnd[0]->SaveToRegistry();
   if (m_pSubSplitterWnd[1] != NULL) m_pSubSplitterWnd[1]->SaveToRegistry();
}
*/

//check if pane is hidden
bool ST_SplitterWnd::IsShown(int nPane /* = LEFT_SIDE */)
{
	return m_nHiddenPane != nPane;
}



//hide column 0 or 1
void ST_SplitterWnd::HideColumn(int colHide)
{
	ASSERT( colHide == 0 || colHide == 1 );		//0 is top, 1 is bottom pane
	ASSERT( m_bVertical == true );				//i'm a vertical splitter
	ASSERT( m_nRows==1 && m_nCols==2 );

	int nID0 = AFX_IDW_PANE_FIRST + 0 * 16 + 0;
	int nID1 = AFX_IDW_PANE_FIRST + 0 * 16 + 1;

	CWnd* pWnd0 = GetDlgItem( nID0 );			//A
	CWnd* pWnd1 = GetDlgItem( nID1 );			//B

	if( colHide == 0 )
	{
		pWnd0->ShowWindow(SW_HIDE);				//hide A
		pWnd0->SetDlgCtrlID( nID1 );			//A gets id 1 (hidden)
		pWnd1->SetDlgCtrlID( nID0 );			//B gets id 0 (the only visible)
	}
	else
	{
		pWnd1->ShowWindow(SW_HIDE);
	}

	m_nHiddenPane = colHide;
	m_nCols=1;
	RecalcLayout();
	return;
}

//show currently hidden column (m_nHiddenCol)
void ST_SplitterWnd::ShowColumn()
{
	ASSERT( m_bVertical == true );				//i'm a vertical splitter
	ASSERT( m_nRows==1 && m_nCols==1 );

	int nID0 = AFX_IDW_PANE_FIRST + 0 * 16 + 0;
	int nID1 = AFX_IDW_PANE_FIRST + 0 * 16 + 1;

	CWnd* pWnd0 = GetDlgItem( nID0 );
	CWnd* pWnd1 = GetDlgItem( nID1 );

	if( m_nHiddenPane == 0 )
	{
		pWnd1->ShowWindow(SW_SHOW);
		pWnd1->SetDlgCtrlID( nID0 );
		pWnd0->SetDlgCtrlID( nID1 );
	}
	else
	{
		pWnd1->ShowWindow(SW_SHOW);
	}

	m_nHiddenPane = -1;
	m_nCols=2;

	RecalcColRowInfo();

	RecalcLayout();
	return;
}

//hides row 0 or 1
void ST_SplitterWnd::HideRow(int rowHide)
{
	ASSERT( rowHide == 0 || rowHide == 1 );		//0 is left, 1 is right pane
	ASSERT( m_bVertical == false );				//i'm a horizontal splitter
	ASSERT( m_nRows==2 && m_nCols==1 );

	int nID0 = AFX_IDW_PANE_FIRST + 0 * 16 + 0;
	int nID1 = AFX_IDW_PANE_FIRST + 1 * 16 + 0;

	CWnd* pWnd0 = GetDlgItem( nID0 );			//row0
	CWnd* pWnd1 = GetDlgItem( nID1 );			//row1

	if( rowHide == 0 )
	{
		pWnd0->ShowWindow(SW_HIDE);
		pWnd0->SetDlgCtrlID( nID1 );			//pane 0 is now last pane (hidden)
		pWnd1->SetDlgCtrlID( nID0 );			//pane 1 is now the first pane..
	}
	else
	{
		pWnd1->ShowWindow(SW_HIDE);
	}

	m_nHiddenPane = rowHide;
	m_nRows=1;
	RecalcLayout();
	return;
}

//show row that was previously hidden
void ST_SplitterWnd::ShowRow()
{
	ASSERT( m_bVertical == false );				//i'm a horizontal splitter
	ASSERT( m_nRows==1 && m_nCols==1 );

	int nID0 = AFX_IDW_PANE_FIRST + 0 * 16 + 0;
	int nID1 = AFX_IDW_PANE_FIRST + 1 * 16 + 0;

	CWnd* pWnd0 = GetDlgItem( nID0 );
	CWnd* pWnd1 = GetDlgItem( nID1 );

	if( m_nHiddenPane == 0 )
	{
		pWnd1->ShowWindow(SW_SHOW);
		pWnd1->SetDlgCtrlID( nID0 );
		pWnd0->SetDlgCtrlID( nID1 );
	}
	else
	{
		pWnd1->ShowWindow(SW_SHOW);
	}

	m_nHiddenPane = -1;
	m_nRows=2;

	RecalcColRowInfo();

	RecalcLayout();
	return;
}





//Call this to show/hide pane, eg from menu item command. Call
//IsSideHidden() from mainframes OnUpdateXXX(CCmdUI* pCmdUI)
//to set checked on menu item
void ST_SplitterWnd::ToggleSide(int nPane)
{
	if( m_bVertical )
	{
		if (m_nHiddenPane==-1)			//none are currently hidden
		{
			HideColumn(nPane);			//hide requested
		}
		else if(m_nHiddenPane==nPane)	//rc is currently hidden?
		{
			ShowColumn();				//show corrently hidden column (m_nHiddenCol)
		}
	}
	else
	{
		if (m_nHiddenPane==-1)
		{
			HideRow(nPane);
		}
		else if (m_nHiddenPane==nPane)
		{
			ShowRow();
		}
	}
}

/*
void ST_SplitterWnd::RememberSize()
{
	if( m_pSubSplitterWnd[0] != NULL )
	{
		m_pSubSplitterWnd[0]->RememberSize();
	}

	if( m_pSubSplitterWnd[1] != NULL )
	{
		m_pSubSplitterWnd[1]->RememberSize();
	}

	if( m_bVertical )
	{
		if( m_nHiddenPane == -1 )
		{
			GetColumnInfo(0,m_nPaneSize[0],m_nPaneMinSize[0]);
			GetColumnInfo(1,m_nPaneSize[1],m_nPaneMinSize[1]);
		}
	}
	else
	{
		if( m_nHiddenPane == -1 )
		{
			GetRowInfo(0,m_nPaneSize[0],m_nPaneMinSize[0]);
			GetRowInfo(1,m_nPaneSize[1],m_nPaneMinSize[1]);
		}
	}
}
*/

ST_SplitterWnd* ST_SplitterWnd::AddSubDivision( int nSide , CRuntimeClass* pView1 , CRuntimeClass* pView2 , CCreateContext* pContext , bool bVertical )
{
	ASSERT( (nSide == 0) || (nSide == 1) );
	ASSERT( m_pSubSplitterWnd[nSide] == NULL );

	int nRow;
	int nCol;
	
	SideToRowCol( nSide, &nRow, &nCol );

	int nID = IdFromRowCol(nRow,nCol);

	m_pSubSplitterWnd[nSide] = new ST_SplitterWnd(m_nLevel+1);
	m_pSubSplitterWnd[nSide]->Create(this,pView1,pView2,pContext,bVertical,nID);
	
	return m_pSubSplitterWnd[nSide];
}

bool ST_SplitterWnd::HideView(int nRow,int nCol)
{
	CWnd* pWnd = GetPane(nRow,nCol);
	if (!pWnd) return(false);
	pWnd->SetDlgCtrlID(0);
	pWnd->ShowWindow(SW_HIDE);
	return(true);
}


bool ST_SplitterWnd::ShowView(int nRow,int nCol,CWnd* pWnd)
{
	pWnd->SetDlgCtrlID(IdFromRowCol(nRow, nCol));
	pWnd->ShowWindow(SW_SHOW);
	return(true);
}


int ST_SplitterWnd::AddView(int nSide, CRuntimeClass * pViewClass, CCreateContext* pContext)
{
	int nRow, nCol;
	SideToRowCol(nSide,&nRow,&nCol);

	// hide the current view of the pane if there is a view attached already
	if( GetDlgItem( IdFromRowCol(nRow,nCol) ) )
	{
		HideView(nRow, nCol);
	}

	// create the new view, if fail, set the previous view current 
	if( CreateView(nRow , nCol , pViewClass , CSize(10,10) , pContext) == 0 )
	{
		return -1;
	}

	// get and store the new view
	CWnd* pWnd = GetPane(nRow, nCol);
	m_views[nSide].push_back(pWnd);
	m_nCurrentView[nSide] = m_views[nSide].size() - 1;

	ShowView(nRow, nCol,pWnd);

	RedrawWindow();

	return(m_nCurrentView[nSide]);

}


void ST_SplitterWnd::SwitchToView( int nSide , int nViewIX /* = -1 */ )
{
	// if the View is -1 then just use the next view...
	if (nViewIX == -1) {
		nViewIX = m_nCurrentView[nSide] + 1;
		if (nViewIX >= m_views[nSide].size()) nViewIX = 0; // rollover to first view
	}
	
	CWnd* pWnd = m_views[nSide][nViewIX];

	int nRow, nCol;

	if ( !IsShown(LEFT_SIDE)) {
		nRow = 0;
		nCol = 0;
	}
	else {
		SideToRowCol(nSide,&nRow,&nCol);
	}
	HideView(nRow, nCol);
	ShowView(nRow, nCol, pWnd);

	m_nCurrentView[nSide] = nViewIX;
	RecalcLayout();
	RedrawWindow();
}

void ST_SplitterWnd::SetPaneSize( int iPaneIndex , int nSize )
{
	m_iFixedSizePane = iPaneIndex;
	m_nFixedSize = nSize;
}


void ST_SplitterWnd::RecalcColRowInfo()
{
	CRect cr;
	GetClientRect(&cr);
	int cx = cr.Width();
	int cy = cr.Height();

	if( m_bVertical )
	{
		int nIdeal = m_nFixedSize;			//default for pane 0

		if( m_iFixedSizePane == 1 )			//bottom pane is fixed in size
		{
			nIdeal = cx - m_nFixedSize - m_nBarSize;
		}

		if( nIdeal < 0 )
		{
			nIdeal = 0;
		}

		SetColumnInfo( 0 , nIdeal , 10 );
	}
	else
	{
		int nIdeal = m_nFixedSize;			//default for pane 0

		if( m_iFixedSizePane == 1 )			//bottom pane is fixed in size
		{
			nIdeal = cy - m_nFixedSize - m_nBarSize;
		}

		if( nIdeal < 0 )
		{
			nIdeal = 0;
		}

		SetRowInfo( 0 , nIdeal , 10 );
	}
}

//calculate the new size of pane 0 (pane 0 will get its ideal size, pan1 one will get the rest). if pane 0 is fixed pane 1 will resize
void ST_SplitterWnd::OnSize(UINT nType, int cx, int cy)
{

	if( m_pColInfo == NULL )
	{
		return;
	}

	RecalcColRowInfo();

	CSplitterWnd::OnSize(nType,cx,cy);		//recalclayout()
}


//when splitter has been moved, pane sizes updates
void ST_SplitterWnd::StopTracking(BOOL bAccept)
{
//	if( bAccept )
//	{
//		TRACE("!\n");
//	}

	CSplitterWnd::StopTracking(bAccept);	//recalclayout()

	int nMinSize;

	if( bAccept )
	{
		//get new ideal size (after user has moved splitter)

		if( m_bVertical )
		{
			GetColumnInfo( m_iFixedSizePane , m_nFixedSize , nMinSize );
		}
		else
		{
			GetRowInfo( m_iFixedSizePane , m_nFixedSize , nMinSize );
		}
	}
}


void ST_SplitterWnd::RecalcLayout()
{
	CSplitterWnd::RecalcLayout();

	//
	// get bar size
	//

	if( m_nHiddenPane == -1 )	//none hidden, so there is a bar
	{
		CRect cr;
		GetClientRect( &cr );

		int s0;
		int m0;
		int s1;
		int m1;

		if( m_bVertical )
		{
			GetColumnInfo( 0 , s0 , m0 );
			GetColumnInfo( 1 , s1 , m1 );
			m_nBarSize = cr.Width() - s0 - s1;
		}
		else
		{
			GetRowInfo( 0 , s0 , m0 );
			GetRowInfo( 1 , s1 , m1 );
			m_nBarSize = cr.Height() - s0 - s1;
		}
	}

	ASSERT(m_nBarSize>0);
}
