// TurboDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TurboDemo.h"
#include "TurboDemoDlg.h"
#include "TurboDragDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTurboDemoDlg dialog

CTurboDemoDlg::CTurboDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTurboDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTurboDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTurboDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTurboDemoDlg)
	DDX_Control(pDX, IDC_TREELIST, m_ctrlTreeList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTurboDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTurboDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DD, OnButtonDd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTurboDemoDlg message handlers

BOOL CTurboDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// m_tree.SetBkColor(0xF0F0F0);
	m_ImageList.Create( IDB_BITMAP_TREE, 16, 4, 0xFF00FF );

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect( 5, 45, 5, 5 );

	CRect left;
	left = rect;
	left.right = ( rect.left + rect.right ) / 2;

	CRect right;
	right = rect;
	right.left = ( rect.left + rect.right ) / 2;

//	m_ctrlTreeList.Create( 0x50810000, left, this, 0 );
//	m_ctrlTreeList.SetRedraw(FALSE);
	m_ctrlTreeList.SetStyle
		( 0
		| TLC_TREELIST								// TreeList or List
//		| TLC_BKGNDIMAGE							// image background
//		| TLC_BKGNDCOLOR							// colored background ( not client area )
		| TLC_DOUBLECOLOR							// double color background

		| TLC_MULTIPLESELECT						// single or multiple select
		| TLC_SHOWSELACTIVE							// show active column of selected item
		| TLC_SHOWSELALWAYS							// show selected item always
		| TLC_SHOWSELFULLROWS						// show selected item in fullrow mode

		| TLC_HEADER								// show header
		| TLC_HGRID									// show horizonal grid lines
		| TLC_VGRID									// show vertical grid lines
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

		| TLC_DRAG									// drag support
		| TLC_DROP									// drop support
//		| TLC_DROPTHIS								// drop self support
//		| TLC_DROPROOT								// drop on root support

		| TLC_HEADDRAGDROP							// head drag drop
		| TLC_HEADFULLDRAG							// head funn drag
//		| TLC_NOAUTOCHECK							// do NOT auto set checkbox of parent & child
//		| TLC_NOAUTOLOCK							// do NOT auto set lockbox of parent & child
		);

	m_ctrlTreeList.SetImageList(&m_ImageList);

	m_ctrlTreeList.InsertColumn(_T("Name"), TLF_DEFAULT_LEFT   | TLF_CAPTION_IMAGE );
	m_ctrlTreeList.InsertColumn(_T("Size"), TLF_DEFAULT_RIGHT  | TLF_ALIGN_RIGHT );
	m_ctrlTreeList.InsertColumn(_T("Memo"), TLF_DEFAULT_LEFT  | TLF_ALIGN_RIGHT );

	m_ctrlTreeList.SetColumnModify( 0, TLM_EDIT );
	m_ctrlTreeList.SetColumnModify( 1, TLM_EDIT );
	m_ctrlTreeList.SetColumnModify( 2, TLM_EDIT );

	m_ctrlTreeList.SetColumnWidth( 0, 200 );
	m_ctrlTreeList.SetColumnWidth( 1, 100 );
	m_ctrlTreeList.SetColumnWidth( 2, 100 );

	for( int i=0; i<20; i++ )
	{
		CString str;
		str.Format( "Item [%02d]", i );
		CTreeListItem* pItem;
		pItem = m_ctrlTreeList.InsertItem( str );
		m_ctrlTreeList.SetItemText( pItem, _T("1000"), 1 );
		m_ctrlTreeList.SetItemText( pItem, _T("none"), 2 );

		if( i<=3 )
			m_ctrlTreeList.SetItemState( pItem, TLIS_SHOWCHECKBOX, TLIS_SHOWLOCKBOX );
		else if ( i<= 5 )
			m_ctrlTreeList.SetItemState( pItem, TLIS_SHOWLOCKBOX, TLIS_SHOWCHECKBOX );
		else
			m_ctrlTreeList.SetItemState( pItem, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX, 0 );

		m_ctrlTreeList.SetItemImage( pItem, 0, 1, 2, 3 );

		for( int j=0; j<6; j++ )
		{
			CTreeListItem* pItem2;
			str.Format( "* Item [%02d]", j );
			pItem2 = m_ctrlTreeList.InsertItem( str, pItem );
			m_ctrlTreeList.SetItemImage( pItem2, 4, 5, 6, 7 );

			if( j<=3 )
				m_ctrlTreeList.SetItemState( pItem2, TLIS_SHOWLOCKBOX, TLIS_SHOWCHECKBOX );
			else
				m_ctrlTreeList.SetItemState( pItem2, TLIS_SHOWCHECKBOX, TLIS_SHOWLOCKBOX );

			CTreeListItem* pAfter = NULL;

			for( int k=0; k<12; k++ )
			{
				CTreeListItem* pItem3;
				str.Format("** Item [%2d]", k );

				if( pAfter == NULL )
					pItem3 = m_ctrlTreeList.InsertItem( str, pItem2 );
				else
					pItem3 = m_ctrlTreeList.InsertItem( str, pItem2, pAfter );

				if( k==2 )
					pAfter = pItem3;

				m_ctrlTreeList.SetItemImage( pItem3, 8, 9, 10, 11 );

				if( k>=0 )
					m_ctrlTreeList.SetItemState( pItem3, 0, TLIS_SHOWCHECKBOX | TLIS_SHOWLOCKBOX );
				if( k>=5 )
					m_ctrlTreeList.SetItemState( pItem3, TLIS_SHOWCHECKBOX, TLIS_SHOWLOCKBOX );
				if( k>=8 )
					m_ctrlTreeList.SetItemState( pItem3, TLIS_SHOWLOCKBOX, TLIS_SHOWCHECKBOX );
			} 
		
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTurboDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTurboDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTurboDemoDlg::OnButtonDd() 
{
	// TODO: Add your control notification handler code here
	CTurboDragDlg dlg;
	dlg.DoModal();
}
