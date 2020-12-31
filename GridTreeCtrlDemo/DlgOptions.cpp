/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#include "stdafx.h"
#include "GridTreeCtrlDemo.h"
#include "GridTreeCtrlDemoDlg.h"
#include "DlgOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static const char szFontDesc[] = "FontDesc";

// map variables to set to tree setup data
BOOL CDlgOptions::m_bShowTreeBoxes;
int  CDlgOptions::m_iTreeImages;
BOOL CDlgOptions::m_bShowVertLines;
BOOL CDlgOptions::m_bShowHorzLines;
BOOL CDlgOptions::m_bRowResizing;
BOOL CDlgOptions::m_bColResizing;
int  CDlgOptions::m_iPrintType;
BOOL CDlgOptions::m_bIsEditable;
BOOL CDlgOptions::m_bAllowSelection;

CDlgOptions::STRUCT_TREE_ITEM CDlgOptions::m_TreeItemAry[] =
{//lev, image, button state,   pv,               text
    { 1,  0, UINT_MAX,         NULL,             "Tree"},
    { 2, -1, DFCS_BUTTONCHECK, &m_bShowTreeBoxes,"Show [+] and [-] boxes"},
    { 2, -1, DFCS_BUTTONRADIO, &m_iTreeImages,   "Show no Images"},
    { 2, -1, DFCS_BUTTONRADIO, &m_iTreeImages,   "Show auto Images"},
    { 2, -1, DFCS_BUTTONRADIO, &m_iTreeImages,   "Show custom Images"},
    { 1,  1, UINT_MAX,         NULL,             "Font"},
    { 2, -1, DFCS_BUTTONPUSH,  NULL,             szFontDesc},        // fill-in dynamically
    { 1,  2, UINT_MAX,         NULL,             "Grid Lines"},
    { 2, -1, DFCS_BUTTONCHECK, &m_bShowVertLines,"Show vertical lines"},
    { 2, -1, DFCS_BUTTONCHECK, &m_bShowHorzLines,"Show horizontal lines"},
    { 1,  3, UINT_MAX,         NULL,             "Resizing"},
    { 2, -1, DFCS_BUTTONCHECK, &m_bRowResizing,  "Allow row resizing"},
    { 2, -1, DFCS_BUTTONCHECK, &m_bColResizing,  "Allow column resizing"},
    { 1,  4, UINT_MAX,         NULL,             "Printing"},
    { 2, -1, DFCS_BUTTONRADIO, &m_iPrintType,    "WYSIWYG"},
    { 2, -1, DFCS_BUTTONRADIO, &m_iPrintType,    "Fit columns to page"},
    { 1,  5, UINT_MAX,         NULL,             "Misc."},
    { 2, -1, DFCS_BUTTONCHECK, &m_bIsEditable,   "Editable"},
    { 2, -1, DFCS_BUTTONCHECK, &m_bAllowSelection,"Allow selection"},
};

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions dialog


CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pGridCtrl = NULL;
}


void CDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
    DDX_GridControl(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CDlgOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgOptions)
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_CLICK, IDC_GRID, OnGridClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions message handlers

BOOL CDlgOptions::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here
    ASSERT( m_pGridCtrl != NULL);    // must call SetGrid() before getting here
    GetGridProps();

    const COLORREF crBk = RGB(0xFF, 0xFF, 0xFF);

    m_Grid.SetEditable(FALSE);
    m_Grid.EnableSelection(FALSE);
    m_Grid.SetGridLines( GVL_NONE);
    m_Grid.SetTextBkColor( crBk);
    m_Grid.SetBkColor( crBk);
    m_Grid.SetHandleTabKey( FALSE);

    m_ImageList.Create( MAKEINTRESOURCE(IDB_OPTIONS),
                        16,     // pixel size
                        1,
                        crBk );

    m_Grid.SetImageList(&m_ImageList);


    // copy level information to a form that the grid can work with
    int row;
    unsigned char ucLevel[ chDIMOF( m_TreeItemAry) ];

    for (row = 0; row < chDIMOF( m_TreeItemAry); row++)
    {
        ucLevel[ row] = m_TreeItemAry[ row].ucLevel;
    }


    TRY
    {
        // Setup Tree + Btn cell structure
        m_BtnDataBase.SetGrid( &m_Grid);

        m_Grid.SetColumnCount(1);
        m_Grid.SetFixedColumnCount( 0);

        m_TreeColumn.TreeSetup(
                            &m_Grid,    // tree acts on a column in this grid
                            0,          // which column has tree
                            chDIMOF( m_TreeItemAry), // total number of rows if tree totally expanded
                            0,          // Set fixed row count now, too
                            ucLevel,    // Tree Level data array --
                                        //  must have aiTotalRows of entries
                            FALSE,      // T=show tree (not grid) lines; F=no tree lines
                            FALSE);     // T=use 1st 3 images from already set image list
                                        //  to display folder graphics
    }
    CATCH (CMemoryException, e)
    {
        e->ReportError();
        e->Delete();
        return FALSE;
    }
    END_CATCH

    // calculate row height / column width matches dialog width
    m_TreeColumn.TreeDisplayOutline( UCHAR_MAX);
    m_Grid.SetItemText( 0, 0, "For Sizing");
    int iRowHeight = m_Grid.GetRowHeight(0);

    CWnd* pWnd = GetDlgItem( IDC_GRID);
    ASSERT( pWnd != NULL);
    CRect RectGrid;

    pWnd->GetClientRect( &RectGrid);
    m_Grid.SetColumnWidth( 0, RectGrid.Width() );


    // fill rows with information
    GV_ITEM Item;
    Item.mask = GVIF_TEXT|GVIF_FORMAT;
    Item.col = 0;
    Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

    for (row = 0; row < chDIMOF( m_TreeItemAry); row++)
    {
        Item.row = row;

        // replace the standard tree cell with our special cell that
        //  also has buttons

        // copy properties
        CGridTreeBtnCell GridCellCopy;
        GridCellCopy.SetBtnDataBase( &m_BtnDataBase);
        CGridTreeCell* pCurrCell = (CGridTreeCell*)m_Grid.GetCell( row, 0);
        if (pCurrCell)
        {
            ASSERT( pCurrCell->IsKindOf( RUNTIME_CLASS( CGridTreeCell) ) );
            GridCellCopy = *pCurrCell;
        }

        m_Grid.SetCellType( row, 0, RUNTIME_CLASS(CGridTreeBtnCell) );
        CGridTreeBtnCell* pGridTreeBtnCell = (CGridTreeBtnCell*)m_Grid.GetCell( row, 0);
        if (pGridTreeBtnCell)
        {
            ASSERT( pGridTreeBtnCell->IsKindOf( RUNTIME_CLASS( CGridTreeBtnCell) ) );
            *pGridTreeBtnCell = GridCellCopy;
        }


        if( strcmp( m_TreeItemAry[ row].pszText,
                    szFontDesc) == 0)
        {
            CString strText;
            GetFontDesc(    m_pGridCtrl->GetItemFont( row, 0),   // font
                            strText);  // returns:  string that describes font

            Item.strText = strText;



            // special handling of font entry
            const char szBtnText[] = "Change...";
            CSize SizeBtnText = pGridTreeBtnCell->GetTextExtent( szBtnText);

            pGridTreeBtnCell->SetupBtns(
                                    0,          // zero-based index of image to draw
                                    DFC_BUTTON, // type of frame control to draw e.g. DFC_BUTTON
                                    m_TreeItemAry[ row].uiBtnState,    // like DrawFrameControl()'s nState  e.g. DFCS_BUTTONCHECK
                                    CGridBtnCellBase::CTL_ALIGN_LEFT,   // horizontal alignment of control image
                                    SizeBtnText.cx,     // fixed width of control or 0 for size-to-fit
                                    FALSE,      // T=btn is member of a radio group
                                    szBtnText);      // Text to insert centered in button; if NULL no text
        }
        else
        {
            // ... everything else
            Item.strText = m_TreeItemAry[ row].pszText;

            if( m_TreeItemAry[ row].iImage >= 0)
            {
                m_Grid.SetItemImage( row, 0, m_TreeItemAry[ row].iImage );
            }

            if( m_TreeItemAry[ row].uiBtnState < UINT_MAX)
            {
                m_TreeItemAry[ row].uiBtnState = SetBtnState( row);    // zero-based row to set

                pGridTreeBtnCell->SetupBtns(
                                        0,          // zero-based index of image to draw
                                        DFC_BUTTON, // type of frame control to draw e.g. DFC_BUTTON
                                        m_TreeItemAry[ row].uiBtnState,  // like DrawFrameControl()'s nState  e.g. DFCS_BUTTONCHECK
                                        CGridBtnCellBase::CTL_ALIGN_LEFT,   // horizontal alignment of control image
                                        iRowHeight, // fixed width of control or 0 for size-to-fit
                                        FALSE,      // T=btn is member of a radio group
                                        NULL);      // Text to insert centered in button; if NULL no text
            }
        }

        m_Grid.SetItem(&Item);
    }

    // Make the first cell active
    LPARAM lParam = 0x00010001; // point 1,1
    m_Grid.SendMessage( WM_LBUTTONDOWN, MK_LBUTTON, lParam);
    m_Grid.SendMessage( WM_LBUTTONUP, 0, lParam);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgOptions::ChangeFont( int iRow)    // row to set text
{
    LOGFONT OldLOGFONT;
    LOGFONT* pNewLOGFONT;
	m_pGridCtrl->GetFont()->GetLogFont(&OldLOGFONT);

    CFontDialog FontDialog( &OldLOGFONT);
    if( FontDialog.DoModal() == IDOK)
    {
        pNewLOGFONT = FontDialog.m_cf.lpLogFont;

        HFONT hFont = ::CreateFontIndirect( pNewLOGFONT);

        ASSERT( m_pGridCtrl != NULL);    // must call SetGrid() before getting here
        m_pGridCtrl->SendMessage( WM_SETFONT, (WPARAM)hFont);
        DeleteObject(hFont);
        m_pGridCtrl->AutoSize(GVS_BOTH);

        CString strText;
        GetFontDesc(    pNewLOGFONT,   // font
                        strText);  // returns:  string that describes font

        m_Grid.SetItemText( iRow, 0, strText);
        m_Grid.RedrawCell(  iRow,
                            0);

    }

}

void CDlgOptions::GetFontDesc(  const LOGFONT* apLOGFONT,   // font
                                CString& arstrFont)  // returns:  string that describes font
{
    ASSERT( apLOGFONT != NULL);

    CClientDC dc( this);
    dc.SetMapMode( MM_TEXT);

    // round points up
    int iDevicePixels = dc.GetDeviceCaps(LOGPIXELSY);

    int iPointSize =    ( (apLOGFONT->lfHeight * -72) + (iDevicePixels/2) )
                        / iDevicePixels;

    arstrFont.Format(   "%s %s %s %s %i pt",
                        apLOGFONT->lfFaceName,
                        apLOGFONT->lfWeight >= FW_BOLD ? "Bold" : "",
                        apLOGFONT->lfItalic ? "Italic" : "",
                        apLOGFONT->lfUnderline ? "Underline" : "",
                        iPointSize);
}

/*****************************************************************************
Based on values from the parent grid, display proper button checked /
unchecked state

*****************************************************************************/
unsigned int CDlgOptions::SetBtnState(  int nRow)    // zero-based row to set
// returns:  button state value
{
    unsigned int uiState = m_TreeItemAry[ nRow].uiBtnState;
    if( m_TreeItemAry[ nRow].pv != NULL)
    {
        // if there is data associated with the control, set it

        if( IsButtonCheckType( uiState ) )
        {
            BOOL* pbValue = (BOOL*)m_TreeItemAry[ nRow].pv;
            if( *pbValue)
                uiState |= DFCS_CHECKED;
        }
        else if( uiState & DFCS_BUTTONRADIO)
        {
            // find which button should be checked, is it this one?
            int i1;
            for( i1=nRow - 1; i1 >= 0; i1--)
            {
                if( m_TreeItemAry[ i1].pv != m_TreeItemAry[ nRow].pv )
                    break;
            }
            int iRadioNbr = nRow - i1 - 1;
            int* piValue = (int*)m_TreeItemAry[ nRow].pv;

            if( iRadioNbr == *piValue)
                uiState |= DFCS_CHECKED;

        }
    }
    return uiState;
}

/*****************************************************************************
Get / Set parent grid properties

*****************************************************************************/
void CDlgOptions::GetGridProps()
{
    ASSERT( m_pGridCtrl != NULL);    // must call SetGrid() before getting here

    // reset all buttons so that they are unchecked
    //  gotta do this since I've set things up as static data
    int i1;
    for( i1=0; i1< chDIMOF( m_TreeItemAry); i1++)
    {
        if( m_TreeItemAry[ i1].uiBtnState < UINT_MAX)
        {
            // it's some sort of button -- uncheck it
            m_TreeItemAry[ i1].uiBtnState &= (~DFCS_CHECKED);
        }
    }

    CGridTreeCtrlDemoDlg* pGridTreeCtrlDemoDlg = (CGridTreeCtrlDemoDlg*)AfxGetMainWnd();
    ASSERT( pGridTreeCtrlDemoDlg != NULL);

    m_iTreeImages = (TREE_IMAGE)pGridTreeCtrlDemoDlg->GetCurrentImages();
    m_bShowTreeBoxes = pGridTreeCtrlDemoDlg->GetTreeLines();

    int iLines = m_pGridCtrl->GetGridLines();
    if( iLines == GVL_BOTH
        || iLines == GVL_VERT)
        m_bShowVertLines = TRUE;
    else
        m_bShowVertLines = FALSE;

    if( iLines == GVL_BOTH
        || iLines == GVL_HORZ)
        m_bShowHorzLines = TRUE;
    else
        m_bShowHorzLines = FALSE;

    m_bRowResizing = m_pGridCtrl->GetRowResize();
    m_bColResizing = m_pGridCtrl->GetColumnResize();

    if( m_pGridCtrl->GetWysiwygPrinting() )
        m_iPrintType = 0;
    else
        m_iPrintType = 1;

    m_bIsEditable = m_pGridCtrl->IsEditable();
    m_bAllowSelection = m_pGridCtrl->IsSelectable();

}

/*****************************************************************************
Can't check directly for  DFCS_BUTTONCHECK bit because it is defined as 0

*****************************************************************************/
BOOL CDlgOptions::IsButtonCheckType( UINT ui)
// returns:  T=is DFCS_BUTTONCHECK; F=some other type of DFC_BUTTON
{
    ASSERT( DFCS_BUTTONCHECK == 0);
    return !( ui & (DFCS_BUTTON3STATE
                    | DFCS_BUTTONPUSH
                    | DFCS_BUTTONRADIO
                    | DFCS_BUTTONRADIOIMAGE
                    | DFCS_BUTTONRADIOMASK ) );
}

void CDlgOptions::OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    *pResult = 0;   // ignore

    int nRow = pItem->iRow;
    int nCol = pItem->iColumn;

    CGridTreeBtnCell* pGridTreeBtnCell = (CGridTreeBtnCell*)m_Grid.GetCell( nRow, nCol);
    if( pGridTreeBtnCell)
    {
        if( !pGridTreeBtnCell->IsKindOf( RUNTIME_CLASS(CGridTreeBtnCell) ) )
        {
            ASSERT( FALSE);
            return;
        }
    }

    if( pGridTreeBtnCell->GetDrawCtlNbr() <= 0)
        return; // no buttons

    short sCtlLastClicked = pGridTreeBtnCell->GetLastCtlClicked();
    UINT uiState = pGridTreeBtnCell->GetDrawCtlState( 0);   // only 1 button, max

    if( IsButtonCheckType( uiState) )
    {
        // toggle the button
        BOOL* pbValue = (BOOL*)m_TreeItemAry[ nRow].pv;
        *pbValue = !(*pbValue);

        if( uiState & DFCS_CHECKED)
            uiState &= (~DFCS_CHECKED);
        else
            uiState |= DFCS_CHECKED;

        m_TreeItemAry[ nRow].uiBtnState = uiState;

        if( sCtlLastClicked < 0)
        {
            // if user clicked right on it, I'm all set, otherwise do drawing
            pGridTreeBtnCell->SetDrawCtlState(  0,
                                                uiState);
            m_Grid.RedrawCell(  nRow,
                                nCol);
        }

    }
    else if( uiState & DFCS_BUTTONRADIO)
    {
        int* piValue = (int*)m_TreeItemAry[ nRow].pv;
        int iRadioOffset = chDIMOF( m_TreeItemAry);

        // uncheck any previously checked radio selection
        int i1;
        for( i1=0; i1 < chDIMOF( m_TreeItemAry); i1++)
        {
            if( m_TreeItemAry[ i1].pv == piValue )
            {
                pGridTreeBtnCell = (CGridTreeBtnCell*)m_Grid.GetCell( i1, nCol);
                if( pGridTreeBtnCell)
                {
                    if( !pGridTreeBtnCell->IsKindOf( RUNTIME_CLASS(CGridTreeBtnCell) ) )
                    {
                        ASSERT( FALSE);
                        return;
                    }
                }

                if( i1 == nRow)
                    uiState |= DFCS_CHECKED;
                else
                    uiState &= (~DFCS_CHECKED);

                m_TreeItemAry[ i1].uiBtnState = uiState;

                pGridTreeBtnCell->SetDrawCtlState(  0,
                                                    uiState);
                m_Grid.RedrawCell(  i1,
                                    nCol);

                if( iRadioOffset > i1)
                    iRadioOffset = i1;  // finds first radio offset


            }
            *piValue = nRow - iRadioOffset;  // tells which is checked
        }
    }
    else if( uiState & DFCS_BUTTONPUSH)
    {
        // change font push button
        if( sCtlLastClicked == 0)
            ChangeFont( nRow);    // row to set text
    }

}


void CDlgOptions::OnOK()
{
    CGridTreeCtrlDemoDlg* pGridTreeCtrlDemoDlg = (CGridTreeCtrlDemoDlg*)AfxGetMainWnd();
    ASSERT( pGridTreeCtrlDemoDlg != NULL);

    pGridTreeCtrlDemoDlg->ChangeImages( (TREE_IMAGE)m_iTreeImages);
    pGridTreeCtrlDemoDlg->SetTreeLines( m_bShowTreeBoxes);

    int iLines;
    if( m_bShowVertLines && m_bShowHorzLines)
        iLines = GVL_BOTH;
    else if( m_bShowVertLines)
        iLines = GVL_VERT;
    else if( m_bShowHorzLines)
        iLines = GVL_HORZ;
    else
        iLines = GVL_NONE;

    m_pGridCtrl->SetGridLines(iLines);

    m_pGridCtrl->SetRowResize(m_bRowResizing);
    m_pGridCtrl->SetColumnResize(m_bColResizing);

    m_pGridCtrl->EnableWysiwygPrinting( !m_iPrintType);

    m_pGridCtrl->SetEditable( m_bIsEditable );
    m_pGridCtrl->EnableSelection( m_bAllowSelection);

    CDialog::OnOK();
}

/*****************************************************************************
If user presses space bar, make it behave as if user clicked on choice

*****************************************************************************/
BOOL CDlgOptions::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_KEYDOWN
        && pMsg->wParam == VK_SPACE)
    {
        NM_GRIDVIEW Item;
        LRESULT Result;
        CCellID cell = m_Grid.GetFocusCell();

        if( cell.IsValid() )
        {
            Item.iColumn = cell.col;
            Item.iRow = cell.row;

            // force a push of any pushbutton

            if( m_TreeItemAry[ Item.iRow].uiBtnState != -1
                && m_TreeItemAry[ Item.iRow].uiBtnState & DFCS_BUTTONPUSH )
            {
                // only font has a push button in this example
                ChangeFont( Item.iRow);
                return TRUE;
            }


            OnGridClick( (NMHDR*)&Item, &Result);
        }
        return TRUE;
    }

	return CDialog::PreTranslateMessage(pMsg);
}
