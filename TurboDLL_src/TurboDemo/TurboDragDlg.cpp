// TurboDragDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TurboDemo.h"
#include "TurboDragDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTurboDragDlg dialog


CTurboDragDlg::CTurboDragDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTurboDragDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTurboDragDlg)
	//}}AFX_DATA_INIT
}


void CTurboDragDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTurboDragDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTurboDragDlg, CDialog)
	//{{AFX_MSG_MAP(CTurboDragDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTurboDragDlg message handlers

BOOL CTurboDragDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ImageList.Create( IDB_BITMAP_TREE, 16, 4, 0xFF00FF );

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect( 5, 5, 5, 5 );

	CRect left;
	left = rect;
	left.right = ( rect.left + rect.right ) / 2;

	CRect right;
	right = rect;
	right.left = ( rect.left + rect.right ) / 2;

	m_tree1.Create( 0x50810000, left, this, 0 );
	m_tree1.SetRedraw(FALSE);

	m_tree2.Create( 0x50810000, right, this, 1 );
	m_tree2.SetRedraw(FALSE);
	
	m_tree1.SetStyle( TLC_DOUBLECOLOR | TLC_BKGNDCOLOR| TLC_SHOWSELALWAYS | TLC_MULTIPLESELECT | TLC_SHOWSELACTIVE | TLC_HEADER | TLC_HGRID | TLC_VGRID );
	m_tree1.SetStyle( m_tree1.GetStyle() | TLC_TREELINE |  TLC_BUTTON | TLC_CHECKBOX | TLC_LOCKBOX | TLC_IMAGE | TLC_DRAG );

	m_tree2.SetStyle( TLC_DOUBLECOLOR | TLC_BKGNDCOLOR| TLC_SHOWSELALWAYS | TLC_MULTIPLESELECT | TLC_SHOWSELACTIVE | TLC_HEADER | TLC_HGRID | TLC_VGRID );
	m_tree2.SetStyle( m_tree2.GetStyle() | TLC_TREELINE |  TLC_BUTTON | TLC_CHECKBOX | TLC_LOCKBOX | TLC_IMAGE | TLC_DROP );

	m_tree1.SetStyle
		( 0
		| TLC_TREELIST								// TreeList or List
//		| TLC_BKGNDIMAGE							// image background
//		| TLC_BKGNDCOLOR							// colored background ( not client area )
//		| TLC_DOUBLECOLOR							// double color background

		| TLC_MULTIPLESELECT						// single or multiple select
		| TLC_SHOWSELACTIVE							// show active column of selected item
		| TLC_SHOWSELALWAYS							// show selected item always
		| TLC_SHOWSELFULLROWS						// show selected item in fullrow mode

		| TLC_HEADER								// show header
		| TLC_HGRID									// show horizonal grid lines
		| TLC_VGRID									// show vertical grid lines
		| TLC_TGRID									// show tree horizonal grid lines ( when HGRID & VGRID )
		| TLC_HGRID_EXT								// show extention horizonal grid lines
		| TLC_VGRID_EXT								// show extention vertical grid lines
		| TLC_HGRID_FULL							// show full horizonal grid lines
//		| TLC_READONLY								// read only

		| TLC_TREELINE								// show tree line
		| TLC_ROOTLINE								// show root line
		| TLC_BUTTON								// show expand/collapse button [+]
		| TLC_CHECKBOX								// show check box
		| TLC_LOCKBOX								// show lock box
		| TLC_IMAGE									// show image
		| TLC_HOTTRACK								// show hover text 

		| TLC_DRAG									// drag support
		| TLC_DROP									// drop support
//		| TLC_DROPTHIS								// drop self support
//		| TLC_DROPROOT								// drop on root support

		| TLC_HEADDRAGDROP							// head drag drop
		| TLC_HEADFULLDRAG							// head funn drag
//		| TLC_NOAUTOCHECK							// do NOT auto set checkbox of parent & child
//		| TLC_NOAUTOLOCK							// do NOT auto set lockbox of parent & child
		);

	m_tree2.SetStyle
		( 0
		| TLC_TREELIST								// TreeList or List
//		| TLC_BKGNDIMAGE							// image background
//		| TLC_BKGNDCOLOR							// colored background ( not client area )
//		| TLC_DOUBLECOLOR							// double color background

		| TLC_MULTIPLESELECT						// single or multiple select
		| TLC_SHOWSELACTIVE							// show active column of selected item
		| TLC_SHOWSELALWAYS							// show selected item always
		| TLC_SHOWSELFULLROWS						// show selected item in fullrow mode

		| TLC_HEADER								// show header
//		| TLC_HGRID									// show horizonal grid lines
//		| TLC_VGRID									// show vertical grid lines
//		| TLC_TGRID									// show tree horizonal grid lines ( when HGRID & VGRID )
		| TLC_HGRID_EXT								// show extention horizonal grid lines
		| TLC_VGRID_EXT								// show extention vertical grid lines
		| TLC_HGRID_FULL							// show full horizonal grid lines
//		| TLC_READONLY								// read only

		| TLC_TREELINE								// show tree line
		| TLC_ROOTLINE								// show root line
		| TLC_BUTTON								// show expand/collapse button [+]
		| TLC_CHECKBOX								// show check box
		| TLC_LOCKBOX								// show lock box
		| TLC_IMAGE									// show image
		| TLC_HOTTRACK								// show hover text 

//		| TLC_DRAG									// drag support
		| TLC_DROP									// drop support
		| TLC_DROPTHIS								// drop self support
//		| TLC_DROPROOT								// drop on root support

		| TLC_HEADDRAGDROP							// head drag drop
		| TLC_HEADFULLDRAG							// head funn drag
///		| TLC_NOAUTOCHECK							// do NOT auto set checkbox of parent & child
//		| TLC_NOAUTOLOCK							// do NOT auto set lockbox of parent & child
		);

	m_tree1.MoveWindow(&left, TRUE);
	m_tree1.SetImageList(&m_ImageList);

	m_tree2.MoveWindow(&right, TRUE);
	m_tree2.SetImageList(&m_ImageList);

	m_tree1.InsertColumn(_T("Name"), TLF_DEFAULT_LEFT   | TLF_CAPTION_IMAGE );
	m_tree1.InsertColumn(_T("High"), TLF_DEFAULT_CENTER | TLF_CAPTION_IMAGE );
	m_tree1.InsertColumn(_T("Size"), TLF_DEFAULT_RIGHT  | TLF_ALIGN_RIGHT );
	m_tree1.InsertColumn(_T("Memo"), TLF_DEFAULT_LEFT );

	m_tree1.SetColumnModify( 0, TLM_EDIT );
	m_tree1.SetColumnModify( 1, TLM_EDIT );
	m_tree1.SetColumnModify( 2, TLM_COMBO );
	m_tree1.SetColumnModify( 3, TLM_EDIT );

	m_tree2.InsertColumn(_T("Name X"), TLF_DEFAULT_LEFT   | TLF_CAPTION_IMAGE );
	m_tree2.InsertColumn(_T("High X"), TLF_DEFAULT_CENTER | TLF_CAPTION_IMAGE );
	m_tree2.InsertColumn(_T("Size X"), TLF_DEFAULT_RIGHT  | TLF_ALIGN_RIGHT );
	m_tree2.InsertColumn(_T("Memo X"), TLF_DEFAULT_LEFT );

	m_tree2.SetColumnModify( 0, TLM_EDIT );

	m_tree1.SetColumnDefaultText( 2, "600|700|800" );

	for( int i=0; i<20; i++ )
	{
		CString str;
		str.Format( "Item [%02d]", i );
		CTreeListItem* pItem;
		pItem = m_tree1.InsertItem( str );
		m_tree1.SetItemText( pItem, _T("1000"), 1 );
		m_tree1.SetItemText( pItem, _T("none"), 2 );
		m_tree1.SetItemImage( pItem, 0, 1, 2, 3 );
		m_tree1.SetItemState( pItem, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

		if( i== 2 )
			m_tree1.SetItemState( pItem, TLIS_EXPANDED );

		for( int j=0; j<6; j++ )
		{
			CTreeListItem* pItem2;
			str.Format( "* Item [%02d]", j );
			pItem2 = m_tree1.InsertItem( str, pItem );
			m_tree1.SetItemImage( pItem2, 4, 5, 6, 7 );
			m_tree1.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

			for( int k=0; k<12; k++ )
			{
				CTreeListItem* pItem3;
				str.Format("** Item [%2d]", k );
				pItem3 = m_tree1.InsertItem( str, pItem2 );
				m_tree1.SetItemImage( pItem3, 8, 9, 10, 11 );

				if( k>=0 )
					m_tree1.SetItemState( pItem3, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );
				if( k>=5 )
					m_tree1.SetItemState( pItem3, TLIS_SHOWCHECKBOX, TLIS_SHOWLOCKBOX );
				if( k>=8 )
					m_tree1.SetItemState( pItem3, TLIS_SHOWLOCKBOX, TLIS_SHOWCHECKBOX );
			} 
		}
	}

	for( i=0; i<20; i++ )
	{
		CString str;
		str.Format( "Item [%02d]", i );
		CTreeListItem* pItem;
		pItem = m_tree2.InsertItem( str );
		m_tree2.SetItemText( pItem, _T("1000"), 1 );
		m_tree2.SetItemText( pItem, _T("none"), 2 );
		m_tree2.SetItemImage( pItem, 0, 1, 2, 3 );
		m_tree2.SetItemState( pItem, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

		if( i== 2 )
			m_tree2.SetItemState( pItem, TLIS_EXPANDED );

		for( int j=0; j<6; j++ )
		{
			CTreeListItem* pItem2;
			str.Format( "* Item [%02d]", j );
			pItem2 = m_tree2.InsertItem( str, pItem );
			m_tree2.SetItemImage( pItem2, 4, 5, 6, 7 );
			m_tree2.SetItemState( pItem2, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );

			for( int k=0; k<12; k++ )
			{
				CTreeListItem* pItem3;
				str.Format("** Item [%2d]", k );
				pItem3 = m_tree2.InsertItem( str, pItem2 );
				m_tree2.SetItemImage( pItem3, 8, 9, 10, 11 );

				if( k>=0 )
					m_tree2.SetItemState( pItem3, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );
				if( k>=5 )
					m_tree2.SetItemState( pItem3, TLIS_SHOWCHECKBOX, TLIS_SHOWLOCKBOX );
				if( k>=8 )
					m_tree2.SetItemState( pItem3, TLIS_SHOWLOCKBOX, TLIS_SHOWCHECKBOX );
			} 
		}
	}

	for( int iCol=0; iCol<m_tree1.GetColumnCount(); iCol++ )
	{
		m_tree1.SetColumnWidth( iCol, -2 );
		m_tree2.SetColumnWidth( iCol, -2 );
	}

	Invalidate();
	UpdateWindow();

	m_tree1.SetRedraw(TRUE);
	m_tree2.SetRedraw(TRUE);

	Invalidate();
	UpdateWindow();

	m_tree1.Invalidate();
	m_tree2.Invalidate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTurboDragDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if( IsWindow( m_tree1.GetSafeHwnd() ) && IsWindow( m_tree2.GetSafeHwnd() ) )
	{
		CRect rect;
		GetClientRect(&rect);
		rect.DeflateRect( 5, 5, 5, 5 );
		
		CRect left;
		left = rect;
		left.right = ( rect.left + rect.right ) / 2;

		CRect right;
		right = rect;
		right.left = ( rect.left + rect.right ) / 2;

		m_tree1.MoveWindow(&left, TRUE);
		m_tree2.MoveWindow(&right, TRUE );
	}
}
