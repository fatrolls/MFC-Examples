/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#include "stdafx.h"
#include "GridTreeCtrlDemo.h"
#include "GridTreeCtrlDemoDlg.h"

#include "DlgOptions.h"
#include "GridBtnCell_src\GridBtnCell.h"
#include "GridBtnCell_src\GridBtnCellCombo.h"
#include "DlgComboChoice.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const char m_szInsDelBranch[] =  "Make sure the current cell is\n"
                                        "in the tree column and try again";

#define FIXED_ROW_COUNT         1
#define FIXED_COLUMN_COUNT      1
#define TREE_COLUMN             2
#define CTL_COLUMN_BEGIN        (TREE_COLUMN + 1)

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridTreeCtrlDemoDlg dialog

CGridTreeCtrlDemoDlg::CGridTreeCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGridTreeCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGridTreeCtrlDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_TreeImage = TREE_IMAGE_AUTO;
}

void CGridTreeCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridTreeCtrlDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

    DDX_Control(pDX, IDC_GRID, m_Grid);
}

BEGIN_MESSAGE_MAP(CGridTreeCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGridTreeCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPTIONS, OnButtonOptions)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	ON_BN_CLICKED(IDC_BUTTON_BRANCH_DELETE, OnButtonBranchDelete)
	ON_BN_CLICKED(IDC_BUTTON_BRANCH_INSERT, OnButtonBranchInsert)
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_CLICK, IDC_GRID, OnGridClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridTreeCtrlDemoDlg message handlers

BOOL CGridTreeCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    m_Grid.SetEditable(TRUE);
    m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));

    m_ImageList.Create( MAKEINTRESOURCE(IDB_FOLDERS),
                        16,     // pixel size
                        1,
                        RGB(255,255,255));
    m_Grid.SetImageList(&m_ImageList);


    // seed tree data in some manner
    unsigned char ucPatternAry[] =
//.    { 0,1,2,2,2,3,3,3,3,4,3,2}; // repeating tree level pattern
//.    { 1,2,3,4,4,2,3,3,4,4,4};
//.    { 1,2,3,2,3,3,4,4,4};
    { 1,2,3,4,4,5,5,3,3,4,2,3,2};
    unsigned char ucTreeLevelAry[ 4* chDIMOF( ucPatternAry) ];

    int i1;
    int iRow = 0;
    ASSERT( chDIMOF( ucPatternAry) > 0);
    for( i1=0; i1 < chDIMOF( ucTreeLevelAry) / chDIMOF( ucPatternAry); i1++)
    {
        int i2;
        for( i2=0; i2 < chDIMOF( ucPatternAry); i2++)
        {
            ucTreeLevelAry[ iRow] = ucPatternAry[ i2];
            iRow++;
        }
    }

    typedef struct
    {
        CGridBtnCellBase::STRUCT_DRAWCTL DrawCtl;  // most btn props here
        int iBtnNbr;                        // which btn within cell does this define?
        const char* pszBtnText;             // text associated with pushbutton or NULL
    }   STRUCT_CTL;


    STRUCT_CTL DrawCtlAry[] =
    { //iWidth,         sState, ucIsMbrRadioGrp,            ucAlign,     ucType, iBtnNbr, pszBtnText
        {  0, DFCS_BUTTONCHECK, FALSE, CGridBtnCellBase::CTL_ALIGN_LEFT,  DFC_BUTTON, 0, NULL },  // checkbox
        {  0,  DFCS_BUTTONPUSH, FALSE, CGridBtnCellBase::CTL_ALIGN_CENTER,DFC_BUTTON, 0, "Test"}, // simple btn
        {  0,  DFCS_BUTTONPUSH,  TRUE, CGridBtnCellBase::CTL_ALIGN_RIGHT, DFC_BUTTON, 0, "&A"}, // radio pushbtns...
        {  0,  DFCS_BUTTONPUSH,  TRUE, CGridBtnCellBase::CTL_ALIGN_RIGHT, DFC_BUTTON, 1, "&B"},
        {  0,  DFCS_BUTTONPUSH | DFCS_CHECKED,  TRUE, CGridBtnCellBase::CTL_ALIGN_RIGHT, DFC_BUTTON, 2, "&C"},
        {  0,  DFCS_BUTTONPUSH,  TRUE, CGridBtnCellBase::CTL_ALIGN_RIGHT, DFC_BUTTON, 3, "&D"},
        { -1,  DFCS_SCROLLUP,   FALSE, CGridBtnCellBase::CTL_ALIGN_RIGHT, DFC_SCROLL, 0, NULL}, // spin box...
        { -1,  DFCS_SCROLLDOWN, FALSE, CGridBtnCellBase::CTL_ALIGN_RIGHT, DFC_SCROLL, 1, NULL},
        { -1,  DFCS_BUTTONPUSH, FALSE, CGridBtnCellBase::CTL_ALIGN_RIGHT, DFC_BUTTON, 0, "..."},// combo w/ btn...
        { -1,  DFCS_SCROLLDOWN, FALSE, CGridBtnCellBase::CTL_ALIGN_RIGHT, DFC_SCROLL, 1, NULL},
    };  // (-1 iWidth's will be filled-in later)

    // find out how many different types of cells with controls that
    //  are defined
    int iNbrCtlCellTypes = 0;
    for( i1=0; i1 < chDIMOF( DrawCtlAry); i1++)
    {
        if( DrawCtlAry[ i1].iBtnNbr == 0)
            iNbrCtlCellTypes++;
    }
    ASSERT( iNbrCtlCellTypes > 0);

    TRY
    {
        m_Grid.SetColumnCount( CTL_COLUMN_BEGIN + iNbrCtlCellTypes);
        m_Grid.SetFixedColumnCount( FIXED_COLUMN_COUNT);

        m_TreeColumn.TreeSetup( &m_Grid, // tree acts on a column in this grid
                            TREE_COLUMN,       // which column has tree
                            chDIMOF( ucTreeLevelAry), // total number of rows if tree totally expanded
                            FIXED_ROW_COUNT,    // Set fixed row count now, too
                            ucTreeLevelAry,    // Tree Level data array --
                                                //  must have aiTotalRows of entries
                            TRUE,               // T=show tree (not grid) lines; F=no tree lines
                            TRUE);              // T=use 1st 3 images from already set image list
                                                //  to display folder graphics
        m_TreeColumn.SetTreeLineColor( RGB( 0, 0, 0xFF) );
    }
    CATCH (CMemoryException, e)
    {
        e->ReportError();
        e->Delete();
        return FALSE;
    }
    END_CATCH

    DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

    // will create some cells with btns, below
    m_BtnDataBase.SetGrid( &m_Grid);

    // fill rows/cols with text
    GV_ITEM Item;
    int row;
    int col;
    for (row = 0; row < m_Grid.GetRowCount(); row++)
    {
        for (col = 0; col < m_Grid.GetColumnCount(); col++)
        {
            Item.mask = GVIF_TEXT|GVIF_FORMAT;
            Item.row = row;
            Item.col = col;
            Item.nState = 0;

            if (row < FIXED_ROW_COUNT)
            {
                Item.nFormat = DT_LEFT|DT_WORDBREAK;
                Item.strText.Format(_T("Column %d"),col);
            }
            else if (col == 0)
            {
                Item.nFormat = dwTextStyle;
                Item.strText.Format(_T("Row %d"),row);
            }
            else if( col == TREE_COLUMN )
            {
                Item.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_STATE;

                Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
                Item.strText.Format( "Level %i",
                                    ucTreeLevelAry[ row - 1] );
                Item.nState = GVIS_READONLY;
            }
            else if (col == CTL_COLUMN_BEGIN)
            {
                Item.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_STATE;
                Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
                Item.strText = "Check Box";
            }
            else
            {
                Item.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_STATE;
                Item.nFormat = dwTextStyle;
                Item.strText.Format(_T("%d"),row*col);
            }

            // Since I'm setting up cells manually, I Must tell
            //  them about being a fixed column cell
            if( col < FIXED_COLUMN_COUNT)
                Item.nState |= GVIS_FIXED | GVIS_FIXEDCOL;

            m_Grid.SetItem(&Item);

        }
    }

    // loop to create cells with buttons and controls
    int iComboCtlWidth = GetSystemMetrics( SM_CXVSCROLL);
    CStringArray strAryCombo;
    strAryCombo.Add( "Mouse");
    strAryCombo.Add( "Cat");
    strAryCombo.Add( "Dog");

    for ( row = m_Grid.GetFixedRowCount(); row < m_Grid.GetRowCount(); row++)
    {
        for (col = CTL_COLUMN_BEGIN; col < m_Grid.GetColumnCount(); col++)
        {
            // retain old cell properties
            CGridBtnCell GridCellCopy;
            GridCellCopy.SetBtnDataBase( &m_BtnDataBase);
            CGridCellBase* pCurrCell = m_Grid.GetCell( row, col);
            if (pCurrCell)
                GridCellCopy = *pCurrCell;

            // replace standard cell with special control cell

            if( col == CTL_COLUMN_BEGIN + 4)  // btn + combo
            {
                m_Grid.SetCellType( row, col, RUNTIME_CLASS(CGridBtnCellCombo) );
                CGridBtnCellCombo* pGridBtnCellCombo = (CGridBtnCellCombo*)m_Grid.GetCell( row, col);
                pGridBtnCellCombo->SetComboStyle( CBS_DROPDOWN);
                pGridBtnCellCombo->SetComboString( strAryCombo);
            }
            else
            {
                m_Grid.SetCellType( row, col, RUNTIME_CLASS(CGridBtnCell) );
            }
            CGridBtnCell* pGridBtnCell = (CGridBtnCell*)m_Grid.GetCell( row, col);
            pGridBtnCell->SetBtnDataBase( &m_BtnDataBase);


            // determine which cell controls to draw
            int iCtlTarget = col - CTL_COLUMN_BEGIN;
            int iCtlIndex = 0;
            int iCtlSetCount = -1;

            for( i1=0; i1 < chDIMOF( DrawCtlAry); i1++)
            {
                if( DrawCtlAry[ i1].iBtnNbr == 0)
                    iCtlSetCount++;

                if( iCtlSetCount == iCtlTarget)
                {
                    iCtlIndex = i1;
                    break;
                }

            }

            // draw controls within a cell
            for( i1=iCtlIndex; i1 < chDIMOF( DrawCtlAry); i1++)
            {
                if( i1 > iCtlIndex
                    && DrawCtlAry[ i1].iBtnNbr == 0)
                    break;  // bumped into next button so stop

                int iWidth = DrawCtlAry[ i1].DrawCtl.iWidth;
                if( iWidth < 0) iWidth = iComboCtlWidth;

                pGridBtnCell->SetupBtns(
                    DrawCtlAry[ i1].iBtnNbr,        // zero-based index of image to draw
                    DrawCtlAry[ i1].DrawCtl.ucType, // type of frame control to draw e.g. DFC_BUTTON
                    DrawCtlAry[ i1].DrawCtl.sState, // like DrawFrameControl()'s nState  e.g. DFCS_BUTTONCHECK
                    (CGridBtnCellBase::CTL_ALIGN)DrawCtlAry[ i1].DrawCtl.ucAlign,
                                                    // horizontal alignment of control image
                    iWidth,                         // fixed width of control or 0 for size-to-fit
                    DrawCtlAry[ i1].DrawCtl.ucIsMbrRadioGrp,  // T=btn is member of a radio group
                    DrawCtlAry[ i1].pszBtnText );   // Text to insert centered in button; if NULL no text
            }
        }

    }

    m_TreeColumn.TreeDisplayOutline( UCHAR_MAX);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGridTreeCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGridTreeCtrlDemoDlg::OnPaint()
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
HCURSOR CGridTreeCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGridTreeCtrlDemoDlg::OnButtonOptions()
{
    CDlgOptions DlgOptions;
    DlgOptions.SetGrid( &m_Grid);

    DlgOptions.DoModal();
}

void CGridTreeCtrlDemoDlg::OnButton1()
{
    m_TreeColumn.TreeDisplayOutline( 1);
}

void CGridTreeCtrlDemoDlg::OnButton2()
{
    m_TreeColumn.TreeDisplayOutline( 2);
}

void CGridTreeCtrlDemoDlg::OnButton3()
{
    m_TreeColumn.TreeDisplayOutline( 3);
}

void CGridTreeCtrlDemoDlg::OnButton4()
{
    m_TreeColumn.TreeDisplayOutline( 4);
}

void CGridTreeCtrlDemoDlg::OnPrint()
{
    m_Grid.Print();
}

void CGridTreeCtrlDemoDlg::OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    if (pItem->iRow < 0)
        return;

    CString strMsg;
    char* pszStop;
    unsigned long lNbr;

    int nRow = pItem->iRow;
    int nCol = pItem->iColumn;

    TRACE("Clicked on row %d, col %d\n", nRow, nCol);
    *pResult = 0;

    if( nRow < m_Grid.GetFixedRowCount() )
        return;

    CGridBtnCell* pGridBtnCell;
    CGridBtnCellCombo* pGridBtnCellCombo;

    // 3/2001:  I don't ASSERT(FALSE) if the button type is unexpected
    //          this is to support addition to test app of inserted
    //          tree branches that don't have button cells
    switch( nCol)
    {
        case CTL_COLUMN_BEGIN + 1:  // Test button
            pGridBtnCell = (CGridBtnCell*)m_Grid.GetCell( nRow, nCol);
            if( pGridBtnCell)
            {
                if( !pGridBtnCell->IsKindOf( RUNTIME_CLASS(CGridBtnCell) ) )
                {
                    return;
                }
                strMsg.Format( "Test Button pressed row=%i", nRow);
                AfxMessageBox( strMsg);
            }
            break;

        case CTL_COLUMN_BEGIN + 2:  // Radio buttons
            pGridBtnCell = (CGridBtnCell*)m_Grid.GetCell( nRow, nCol);
            if( pGridBtnCell)
            {
                if( !pGridBtnCell->IsKindOf( RUNTIME_CLASS(CGridBtnCell) ) )
                {
                    return;
                }
                TRACE( "Clicked button=%i\n", pGridBtnCell->GetLastCtlClicked() );
            }
            break;

        case CTL_COLUMN_BEGIN + 3:  // Spin control
            pGridBtnCell = (CGridBtnCell*)m_Grid.GetCell( nRow, nCol);
            if( pGridBtnCell)
            {
                if( !pGridBtnCell->IsKindOf( RUNTIME_CLASS(CGridBtnCell) ) )
                {
                    return;
                }
                int iOffset;
                if( pGridBtnCell->GetLastCtlClicked() < 0)
                    return;

                if( pGridBtnCell->GetLastCtlClicked() == 0)
                    iOffset = 1;
                else
                    iOffset = -1;

                // increment / decrement the number
                strMsg = pGridBtnCell->GetText();
                lNbr = strtol( strMsg, &pszStop, 10 );
                lNbr += iOffset;
                strMsg.Format( "%i", lNbr);

                pGridBtnCell->SetText( strMsg);
                m_Grid.RedrawCell( nRow, nCol);
            }
            break;

        case CTL_COLUMN_BEGIN + 4:  // btn + combo
            pGridBtnCellCombo = (CGridBtnCellCombo*)m_Grid.GetCell( nRow, nCol);
            if( pGridBtnCellCombo)
            {
                if( !pGridBtnCellCombo->IsKindOf( RUNTIME_CLASS(CGridBtnCellCombo) ) )
                {
                    return;
                }

                if( pGridBtnCellCombo->GetLastCtlClicked() < 0)
                    return;

                if( pGridBtnCellCombo->GetLastCtlClicked() == 0)
                {
                    CDlgComboChoice DlgComboChoice;
                    if( DlgComboChoice.DoModal() == IDOK)
                    {
                        static const char* pszInsects[] =
                        {
                            "Beetle",
                            "Grub",
                            "Moth",
                        };

                        m_Grid.SetItemText( nRow, nCol,
                                            pszInsects[ DlgComboChoice.m_iRadio ]);
                        m_Grid.RedrawCell( nRow, nCol);
                    }
                }
            }
            break;

        default:
            break;
    }


}

void CGridTreeCtrlDemoDlg::ChangeImages( TREE_IMAGE aTreeImage) // TREE_IMAGE
{
    GV_ITEM Item;
    Item.col = TREE_COLUMN;
    Item.mask = GVIF_IMAGE;

    m_TreeImage = aTreeImage;

    BOOL bAuto = ( aTreeImage == TREE_IMAGE_AUTO);
    m_TreeColumn.SetTreeUsesImages( bAuto);

    int iNbrAutoImages = m_TreeColumn.GetTreeUsesNbrImages();

    for (int row = m_Grid.GetFixedRowCount(); row < m_Grid.GetRowCount(); row++)
    {
        Item.row = row;
        if( m_Grid.GetItem( &Item) )
        {
            switch( aTreeImage)
            {
                case TREE_IMAGE_NONE:
                case TREE_IMAGE_AUTO:
                    Item.iImage = -1;   // no explicit image
                    break;

                case TREE_IMAGE_CUSTOM:
                    Item.iImage = iNbrAutoImages + m_TreeColumn.GetTreeLevel( row);
                    break;

                default:
                    ASSERT( FALSE);
                    break;
            }

            m_Grid.SetItem(&Item);
        }

    }
    m_Grid.Invalidate();

}

void CGridTreeCtrlDemoDlg::SetTreeLines( BOOL abShowTreeLines)
{
    m_TreeColumn.SetTreeLines( abShowTreeLines);
}

BOOL CGridTreeCtrlDemoDlg::GetTreeLines() const
{
    return m_TreeColumn.GetTreeLines();
}

void CGridTreeCtrlDemoDlg::OnButtonBranchDelete() 
{
    CCellID cell;
    cell = m_Grid.GetFocusCell();

    if( cell.col != m_TreeColumn.GetColumnWithTree() )
    {
        AfxMessageBox( m_szInsDelBranch);
        return;
    }
    
    if( cell.row < FIXED_ROW_COUNT)
        return; // tree not in fixed row

    m_TreeColumn.DeleteTreeBranch( cell.row,  // Row that the tree branch begins on
                                   TRUE); // T=redraw; F=don't
    // returns:  nbr of rows deleted
}

void CGridTreeCtrlDemoDlg::OnButtonBranchInsert() 
{
    CCellID cell;
    cell = m_Grid.GetFocusCell();

    if( cell.col != m_TreeColumn.GetColumnWithTree() )
    {
        AfxMessageBox( m_szInsDelBranch);
        return;
    }
    
    unsigned char ucPatternAry[] =
    { 2,3,4,3};

    m_TreeColumn.InsertTreeBranch(  
                            ucPatternAry, // Tree Level data array --
                                          //  must have aiTotalRows of entries
                            chDIMOF( ucPatternAry),  // NUmber of tree elements to add
                            cell.row,  // insert tree elements beginning at this row
                                       //  If -1, append to end; If 0, Insert
                                       //  at top no matter how many fixed rows
                            TRUE);     // T=redraw; F=don't
    // returns:  row where elements inserted; -1 on error


    // fill rows/cols with text
    GV_ITEM Item;
    int row;
    int col;
    int i1;
    for (i1= 0; i1 < chDIMOF( ucPatternAry); i1++)
    {
        row = cell.row + i1;
        for (col = 0; col < m_Grid.GetColumnCount(); col++)
        {
            Item.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_STATE;
            Item.row = row;
            Item.col = col;
            Item.nState = 0;

            if( col == TREE_COLUMN )
            {
                Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
                Item.strText.Format( "Level %i",
                                    ucPatternAry[ i1] );
                Item.nState = GVIS_READONLY;
            }
            else
            {
                Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
                Item.strText.Format(_T("insert %d of %d"), 
                                        i1+1, chDIMOF(ucPatternAry) );
            }

            // Since I'm setting up cells manually, I Must tell
            //  them about being a fixed column cell
            if( col < FIXED_COLUMN_COUNT)
                Item.nState |= GVIS_FIXED | GVIS_FIXEDCOL;

            m_Grid.SetItem(&Item);

        }
    }

}

