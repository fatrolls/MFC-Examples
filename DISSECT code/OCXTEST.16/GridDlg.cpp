// GridDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OcxTest.h"
#include "GridDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridDlg dialog


CGridDlg::CGridDlg(CWnd* pParent /*=NULL*/)
        : CDialog(CGridDlg::IDD, pParent)
{
        //{{AFX_DATA_INIT(CGridDlg)
        m_cellValue = _T("");
        //}}AFX_DATA_INIT
}


void CGridDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CGridDlg)
        DDX_Control(pDX, IDC_GRID, m_OcxGrid);
        DDX_Text(pDX, IDC_VALUE, m_cellValue);
        //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGridDlg, CDialog)
        //{{AFX_MSG_MAP(CGridDlg)
        ON_BN_CLICKED(IDC_UPDATEVALUE, OnUpdatevalue)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridDlg message handlers

BEGIN_EVENTSINK_MAP(CGridDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CGridDlg)
        ON_EVENT(CGridDlg, IDC_GRID, 2 /* SelChange */, OnSelChangeGrid, VTS_NONE)
        //}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CGridDlg::OnInitDialog()
{
    CString str;
    int   i, j;
    CRect rect;

    CDialog::OnInitDialog();

    VERIFY(m_OcxGrid.GetCols() == (long)MAXCOL);
    VERIFY(m_OcxGrid.GetRows() == (long)MAXROW);

    m_OcxGrid.SetRow(0);             // #0 Row
    for (i = 0; i < MAXCOL; i++) {   // 所有的 Cols
        if (i) { // column headings
            m_OcxGrid.SetCol(i);
            if (i == (MAXCOL-1))
                m_OcxGrid.SetText(CString("Total"));
            else
                m_OcxGrid.SetText(CString(char('A' + i - 1)));
        }
    }

    m_OcxGrid.SetCol(0);             // #0 Col
    for (j = 0; j < MAXROW; j++) {   // 所有的 Rows
        if (j) { // row headings
            m_OcxGrid.SetRow(j);
            if (j == (MAXROW-1))
                m_OcxGrid.SetText(CString("Total"));
            else {
                str.Format("%d", j);
                m_OcxGrid.SetText(str);
            }
        }
    }

    // sets the spreadsheet values from m_dArray
    for (i = 1; i < (MAXCOL-1); i++) {
        m_OcxGrid.SetCol(i);
        for (j = 1; j < (MAXROW-1); j++) {
            m_OcxGrid.SetRow(j);
            str.Format("%8.2f", m_dArray[i][j]);
            m_OcxGrid.SetText(str);
        }
    }

    ComputeSums();

    // be sure there's a selected cell
    m_OcxGrid.SetCol(1);
    m_OcxGrid.SetRow(1);
    m_cellValue = m_OcxGrid.GetText();
    UpdateData(FALSE); // calls DoDataExchange to update edit control
    return TRUE;
}

void CGridDlg::OnOK()
{
    int i, j;

    for (i = 1; i < (MAXCOL-1); i++) {
        m_OcxGrid.SetCol(i);
        for (j = 1; j < (MAXROW-1); j++) {
            m_OcxGrid.SetRow(j);
            m_dArray[i][j] = atof(m_OcxGrid.GetText());
        }
    }
    CDialog::OnOK();
}

void CGridDlg::OnCancel()
{
        // TODO: Add extra cleanup here

        CDialog::OnCancel();
}

void CGridDlg::OnUpdatevalue()
{
    CString str;
    double value;
    // LONG   lRow, lCol;
    int   Row, Col;

    if (m_OcxGrid.GetCellSelected() == 0) {
      AfxMessageBox("No cell selected");
      return;
    }

    UpdateData(TRUE);
    value = atof(m_cellValue);
    str.Format("%8.2f", value);

    // saves current cell selection
    Col = m_OcxGrid.GetCol();
    Row = m_OcxGrid.GetRow();

    m_OcxGrid.SetText(str); // copies new value to
                            //  the selected cell
    ComputeSums();

    // restores current cell selection
    m_OcxGrid.SetCol(Col);
    m_OcxGrid.SetRow(Row);
}

void CGridDlg::OnSelChangeGrid()
{
    if (m_OcxGrid) {
        m_cellValue = m_OcxGrid.GetText();
        UpdateData(FALSE); // calls DoDataExchange to update edit control
        GotoDlgCtrl(GetDlgItem(IDC_VALUE)); // position edit control
    }
}

void CGridDlg::ComputeSums()
{
    int    i, j, nRows, nCols;
    double sum;
    CString str;

    // adds up each row and puts the sum in the right col
    // col count could have been changed by add row/delete row
    nCols = (int) m_OcxGrid.GetCols();
    for (j = 1; j < (MAXROW-1); j++) {
        m_OcxGrid.SetRow(j);
        sum = 0.0;
        for (i = 1; i < nCols - 1; i++) {
            m_OcxGrid.SetCol(i);
            sum += atof(m_OcxGrid.GetText());
        }
        str.Format("%8.2f", sum);
        m_OcxGrid.SetCol(nCols - 1);
        m_OcxGrid.SetText(str);
    }

    // adds up each column and puts the sum in the bottom row
    // row count could have been changed by add row/delete row
    nRows = (int) m_OcxGrid.GetRows();
    for (i = 1; i < MAXCOL; i++) {
        m_OcxGrid.SetCol(i);
        sum = 0.0;
        for (j = 1; j < nRows - 1; j++) {
            m_OcxGrid.SetRow(j);
            sum += atof(m_OcxGrid.GetText());
        }
        str.Format("%8.2f", sum);
        m_OcxGrid.SetRow(nRows - 1);
        m_OcxGrid.SetText(str);
    }
}

