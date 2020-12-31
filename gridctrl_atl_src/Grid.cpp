// Grid.cpp : Implementation of CGrid
//
// ATL Grid Control
//
// Written by Mario Zucca 
//        mailto:mario@GenoaValley.org
//        http://www.GenoaValley.org
//
// Copyright (c) 2000.
//
// The code contained in this file is based on the original
// Grid control written by Chris Maunder,
//        mailto:chris@codeproject.com
//        http://www.codeproject.com
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. If the source code in this file is used in 
// any  commercial application then a statement along the lines of 
// "Portions copyright (c) Mario Zucca, 2000" must be included in 
// the startup banner, "About" box or printed documentation. An email 
// letting me know that you are using it would be nice as well. 
//
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Expect bugs!
// 
// Please use and enjoy, and let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into 
// this file. 
//

#include "stdafx.h"
#include "MemDC.h"

//#include "InPlaceEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CGrid


// Get the number of lines to scroll with each mouse wheel notch
// Why doesn't windows give us this function???
UINT GetMouseScrollLines()
{
    int nScrollLines = 3;            // reasonable default
    HKEY hKey;

    if (RegOpenKeyEx(HKEY_CURRENT_USER,  _T("Control Panel\\Desktop"),
                     0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
    {
        TCHAR szData[128];
        DWORD dwKeyDataType;
        DWORD dwDataBufSize = sizeof(szData);

        if (RegQueryValueEx(hKey, _T("WheelScrollLines"), NULL, &dwKeyDataType,
                           (LPBYTE) &szData, &dwDataBufSize) == ERROR_SUCCESS)
        {
            nScrollLines = _tcstoul(szData, NULL, 10);
        }
        RegCloseKey(hKey);
    }

    return nScrollLines;
}

STDMETHODIMP CGrid::get_Image(int Row, int Col, short *pVal)
{
	CGridCell* pCell = GetCell(Row,Col);

	if(pCell)
		*pVal = pCell->GetImage();
	else
		*pVal = -1;

	return S_OK;
}

STDMETHODIMP CGrid::put_Image(int Row, int Col, short newVal)
{
	CGridCell* pCell = GetCell(Row,Col);

	if(pCell)
		pCell->SetImage(newVal);
	FireViewChange();
	return S_OK;
}

STDMETHODIMP CGrid::get_Text(int Row, int Col, BSTR *pVal)
{
	CGridCell* pCell = GetCell(Row,Col);

	if(pCell)
	*pVal = pCell->GetText();

	return S_OK;
}

STDMETHODIMP CGrid::put_Text(int Row, int Col, BSTR newVal)
{
	CGridCell* pCell = GetCell(Row,Col);

	if(pCell)
		pCell->put_Text(newVal);
	FireViewChange();

	return S_OK;
}

STDMETHODIMP CGrid::InsertRow(int Row, BSTR caption)
{
	NewRow(caption,Row);
	FireViewChange();

	return S_OK;
}

STDMETHODIMP CGrid::get_RowCount(int *pVal)
{
	*pVal = m_nRows;

	return S_OK;
}

STDMETHODIMP CGrid::put_RowCount(int newVal)
{
    ATLASSERT(newVal >= 0);

    if (newVal == m_nRows) return TRUE;

    if (newVal < m_nFixedRows) 
        m_nFixedRows = newVal;

    if (m_idCurrentCell.row >= newVal)
        SetFocusCell(-1,-1);

    int addedRows = newVal - m_nRows;

    // If we are about to lose rows, then we need to delete the GridCell objects 
    // in each column within each row
    if (addedRows < 0) {
        for (int row = newVal; row < m_nRows; row++)
        {
            // Delete cells
            for (int col = 0; col < m_nCols; col++) 
            {
                CGridCell* pCell = GetCell(row, col);
                if (pCell)
				{
//                    pCell->Empty();
		            EmptyCell(pCell, row, col);
                    delete pCell;
                }
            }
            // Delete rows
            GRID_ROW* pRow = m_RowData[row];
            if (pRow) delete pRow;
        }
    }

    // Change the number of rows.
    m_nRows = newVal;
    m_RowData.resize(m_nRows);
    m_arRow.resize(newVal);

    // If we have just added rows, we need toruct new elements for each cell
    // and set the default row height
    if (addedRows > 0) {
        // initialize row heights and data
        int startRow = newVal - addedRows;
        for (int row = startRow; row < newVal; row++) {
            m_arRow[row].Height = m_nDefCellHeight;
            m_RowData[row] = new GRID_ROW;
            m_RowData[row]->resize(m_nCols);
            for (int col = 0; col < m_nCols; col++)
            {
                GRID_ROW* pRow = m_RowData[row];
                if (pRow)
					pRow->at(col) = CreateCell(row, col);
            }
        }
    }
    //else
    //    ResetSelectedRange();
    
    if (m_bAllowDraw && m_hWnd)
    {
        ResetScrollBars();
        FireViewChange();
    }
    return TRUE;

	return S_OK;
}

STDMETHODIMP CGrid::get_ColumnCount(int *pVal)
{
	*pVal = m_nCols;

	return S_OK;
}

STDMETHODIMP CGrid::put_ColumnCount(int newVal)
{
	if (newVal < 0)
		return S_OK;

	if (newVal == m_nCols) return S_OK;

	if (newVal < m_nFixedCols) 
		m_nFixedCols = newVal;

	if (m_idCurrentCell.col >= newVal)
		SetFocusCell(-1,-1);

	int addedCols = newVal - m_nCols;

	// If we are about to lose columns, then we need to delete the GridCell objects 
	// within each column
	if (addedCols < 0) {
		for (int row = 0; row < m_nRows; row++)
			for (int col = newVal; col < m_nCols; col++)
			{
				CGridCell* pCell = GetCell(row, col);
				if (pCell) {
//					pCell->Empty();
		            EmptyCell(pCell, row, col);
					delete pCell;
				}
			}
	}

	// Change the number of columns.
	m_nCols = newVal;
	m_arCol.resize(newVal);

	// Change the number of columns in each row.
	for (int i = 0; i < m_nRows; i++)
		if (m_RowData[i]) m_RowData[i]->resize(newVal);

	// If we have just added columns, we need toruct new elements for each cell
	// and set the default column width
	if (addedCols > 0)
	{
		// initialized column widths
		int startCol = newVal - addedCols;
		for (int col = startCol; col < m_nCols; col++)
			m_arCol[col].Width = m_nDefCellWidth;

		// initialise column data
		for (int row = 0; row < m_nRows; row++)
			for (col = startCol; col < m_nCols; col++)
			{
				GRID_ROW* pRow = m_RowData[row];
				if (pRow) 
					pRow->at(col) = CreateCell(row,col);
			}
	}
	//else    // check for selected cell ranges
	//    ResetSelectedRange();

	if (m_bAllowDraw && m_hWnd)
	{
		ResetScrollBars();
		FireViewChange();
	}

	return S_OK;
}

STDMETHODIMP CGrid::get_RowHeight(int nRow, int *pVal)
{
	*pVal = GetRowHeight(nRow);

	return S_OK;
}

STDMETHODIMP CGrid::put_RowHeight(int nRow, int newVal)
{
	ATLASSERT(nRow >= 0 && nRow < m_nRows && newVal >= 0);
	if (nRow < 0 || nRow >= m_nRows || newVal < 0) return S_OK;

	m_arRow[nRow].Height = newVal;    
	FireViewChange();
	return S_OK;
}

STDMETHODIMP CGrid::get_ColumnWidth(int Col, int *pVal)
{
	*pVal = GetColumnWidth(Col);

	return S_OK;
}

STDMETHODIMP CGrid::put_ColumnWidth(int nCol, int width)
{
//ATLASSERT(nCol >= 0 && nCol < m_nCols && width >= 0);
	if (nCol < 0 || nCol >= m_nCols || width < 0) return S_OK;

	m_arCol[nCol].Width = width;
	return TRUE;
	FireViewChange();

	return S_OK;
}

STDMETHODIMP CGrid::get_CellFont(int Row, int Col, IFontDisp **pVal)
{

	HRESULT hr = S_OK;
	CGridCell* pCell;
	pCell = GetCell(Row,Col);
	if (pCell)
		hr = pCell->get_Font(pVal);

	return hr;
}

STDMETHODIMP CGrid::put_CellFont(int Row, int Col, IFontDisp *newVal)
{
	HRESULT hr = S_OK;

	CGridCell* pCell = GetCell(Row,Col);
	if (pCell)
		hr = pCell->put_Font(newVal);

	return hr;
}

STDMETHODIMP CGrid::AutoSize()
{
	HDC hDC = GetDC();
	if (!hDC) return S_OK;

	int nNumColumns = m_nCols;

	// initialize column widths to zero
	for (int nCol = 0; nCol < nNumColumns; nCol++)
		m_arCol[nCol].Width = 0;

	// initialize row heights to zero
	for (int nRow = 0; nRow < m_nRows; nRow++)
		m_arRow[nRow].Height = 0;

	SIZE size;
	for (nCol = 0; nCol < nNumColumns; nCol++)
		for (nRow = 0; nRow < m_nRows; nRow++)
		{
			size = GetCellExtent(nRow, nCol, hDC);
			if (size.cx > (int) m_arCol[nCol].Width)  m_arCol[nCol].Width = size.cx;
			if (size.cy > (int) m_arRow[nRow].Height) m_arRow[nRow].Height = size.cy;
		}

	ReleaseDC(hDC);

	if (m_bAllowDraw && m_hWnd) {
		ResetScrollBars();
		FireViewChange();
	}

	return S_OK;
}
////////////////////////////////////////////////////////////
// Grid Operations
////////////////////////////////////////////////////////////

HRESULT CGrid::OnDraw(ATL_DRAWINFO& di)
{

		
//	PAINTSTRUCT ps; 
	HDC hdc; 


	RECT rc;
	HDC hdcMem;
	HBITMAP hbmMem, hbmOld;
	//
	// Get the size of the client rectangle
	//
	GetClientRect(&rc);
	CMemDC dc(di.hdcDraw,rc);
	DrawGrid(dc.GetDC(),rc);
	return S_OK;

	hdc = di.hdcDraw; 

	//
	// Create a compatible DC
	//

	hdcMem = CreateCompatibleDC(hdc);

	//
	// Create a bitmap big enough for our client rect
	//

	hbmMem = CreateCompatibleBitmap(hdc,
									rc.right-rc.left,
									rc.bottom-rc.top);

	//
	// Select the bitmap into the off-screen dc
	//

	hbmOld = (HBITMAP) SelectObject(hdcMem, hbmMem);

	DrawGrid(hdcMem,rc);
	//
	// Render the image into the offscreen dc
	//

	SetBkMode(hdcMem, TRANSPARENT);

	//
	// Blit the changes to the screen dc
	//

	BitBlt(hdc, 
		   rc.left, rc.top,
		   rc.right-rc.left, rc.bottom-rc.top,
		   hdcMem,
		   0, 0,
		   SRCCOPY);

	//
	// Done with off screen bitmap and dc
	//

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
//	EndPaint(&ps); 
	return S_OK;
}


// selects columns
void CGrid::SelectColumns(CCellID currentCell)
{
    if (!m_bEnableSelection)
        return;

    //if (currentCell.col == m_idCurrentCell.col) return;
    if (currentCell.col < m_nFixedCols)
        return;
    if (!IsValid(currentCell))
        return;

	int fixedRow;
	get_FixedRows(&fixedRow);

    SetSelectedRange(fixedRow, 
                     min(m_SelectionStartCell.col, currentCell.col), 
                     m_nRows-1,    
                     max(m_SelectionStartCell.col, currentCell.col)); 

}

// selects rows
void CGrid::SelectRows(CCellID currentCell)
{
	int fixedColumn;
	get_FixedCols(&fixedColumn);

    if (!m_bEnableSelection)
        return;

    //if (currentCell.row; == m_idCurrentCell.row) return;
    if (currentCell.row < m_nFixedRows)
        return;
    if (!IsValid(currentCell))
        return;

    if (m_bListMode && GetSingleRowSelection())
        SetSelectedRange(currentCell.row, fixedColumn,
                         currentCell.row, m_nCols-1);
    else 
        SetSelectedRange(min(m_SelectionStartCell.row, currentCell.row),
                         fixedColumn, 
                         max(m_SelectionStartCell.row, currentCell.row), 
                         m_nCols-1); 

}

// selects cells
void CGrid::SelectCells(CCellID currentCell)
{
    if (!m_bEnableSelection) 
        return;

    int row = currentCell.row;
    int col = currentCell.col;
    if (row < m_nFixedRows || col < m_nFixedCols)
        return;
    if (!IsValid(currentCell))
        return;

    // Prevent unnecessary redraws
    //if (currentCell == m_LeftClickDownCell)  return;
    //else if (currentCell == m_idCurrentCell) return;

    SetSelectedRange(min(m_SelectionStartCell.row, row), 
                     min(m_SelectionStartCell.col, col), 
                     max(m_SelectionStartCell.row, row),
                     max(m_SelectionStartCell.col, col)); 

}

BOOL CGrid::SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data, int low, int high)
{
	// Provvisorio sarebbe da usare i template
    if (nCol >= m_nCols) return FALSE;

    if (high == -1) high = m_nRows - 1;

    int lo = low;
    int hi = high;

    if( hi <= lo ) return FALSE;

    LPARAM midItem = GetCell( (lo+hi)/2, nCol )->GetData();

    // loop through the list until indices cross
    while( lo <= hi )
    {
        // Find the first element that is greater than or equal to the partition 
        // element starting from the left Index.
        if( bAscending )
            while (lo < high  && pfnCompare(GetCell(lo, nCol)->GetData(), midItem, data) < 0)
                ++lo;
        else
            while (lo < high && pfnCompare(GetCell(lo, nCol)->GetData(), midItem, data) > 0)
                ++lo;

        // Find an element that is smaller than or equal to  the partition 
        // element starting from the right Index.
        if( bAscending )
            while (hi > low && pfnCompare(GetCell(hi, nCol)->GetData(), midItem, data) > 0)
                --hi;
        else
            while (hi > low && pfnCompare(GetCell(hi, nCol)->GetData(), midItem, data) < 0)
                --hi;

        // If the indexes have not crossed, swap if the items are not equal
        if (lo <= hi)
        {
            // swap only if the items are not equal
            if (pfnCompare(GetCell(lo, nCol)->GetData(), GetCell(hi, nCol)->GetData(), data) != 0)
            {
                for (int col = 0; col < m_nCols; col++)
                {
                    CGridCell *pCell = GetCell(lo, col);
                    SetCell(lo, col, GetCell(hi, col));
                    SetCell(hi, col, pCell);
                }
                UINT nRowHeight = m_arRow[lo].Height;
                m_arRow[lo] = m_arRow[hi];
                m_arRow[hi].Height = nRowHeight;
            }

            ++lo;
            --hi;
        }
    }

    // If the right index has not reached the left side of array
    // must now sort the left partition.
    if( low < hi )
        SortItems(pfnCompare, nCol, bAscending, data, low, hi);

    // If the left index has not reached the right side of array
    // must now sort the right partition.
    if( lo < high )
        SortItems(pfnCompare, nCol, bAscending, data, lo, high);

    return TRUE;

}

BOOL CGrid::SetCell(int nRow, int nCol, CGridCell *pCell)
{
    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols) return FALSE;

    GRID_ROW* pRow = m_RowData[nRow];
    if (!pRow) return FALSE;

    pRow->at(nCol) = pCell;
    return TRUE;

}

BOOL CGrid::SetScrollPos32(int nBar, int nPos, BOOL bRedraw /*= TRUE */)
{
    SCROLLINFO si;
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask  = SIF_POS;
    si.nPos   = nPos;
    return SetScrollInfo(nBar, &si, bRedraw);

}

void CGrid::SetModified(BOOL bModified, int nRow, int nCol)
{
	CGridCell* pCell = GetCell(nRow,nCol);

    if (nRow > 0 && nCol > 0)
    {
        if (bModified)
        {
	        SetItemState(nRow,nCol,
				pCell->GetState() | GVIS_MODIFIED);
            m_bModified = TRUE; 
        }
        else
	        SetItemState(nRow,nCol,
				pCell->GetState() & ~GVIS_MODIFIED);
    }
    else
        m_bModified = bModified;

    if (!m_bModified)
    {
        for (int row = 0; row < m_nRows; row++)
            for (int col = 0; col < m_nCols; col++) 
			{
				pCell = GetCell(nRow,nCol);
				if(pCell)
					SetItemState(nRow,nCol,
						pCell->GetState() & ~GVIS_MODIFIED);
			}
    }

}

/////////////////////////////////////////////////////////////////////////////////////
// GridCtrl cell visibility tests and invalidation/redraw functions

// EnsureVisible supplied by Roelf Werkman
void CGrid::EnsureVisible(int nRow, int nCol)
{
    CCellRange VisibleCells = GetVisibleNonFixedCellRange(NULL);

    int right = nCol - VisibleCells.GetMaxCol();
    int left  = VisibleCells.GetMinCol() - nCol;
    int down  = nRow - VisibleCells.GetMaxRow();
    int up    = VisibleCells.GetMinRow() - nRow;

    while (right > 0)
    {
        SendMessage(WM_HSCROLL, SB_LINERIGHT, 0);
        right--;
    }
    while (left > 0)
    {
        SendMessage(WM_HSCROLL, SB_LINELEFT, 0);
        left--;
    }
    while (down > 0)
    {
        SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
        down--;
   }
   while (up > 0)
   {
       SendMessage(WM_VSCROLL, SB_LINEUP, 0);
       up--;
   }

   // Move one more if we only see a snall bit of the cell
   RECT rectCell={0,0,0,0}, rectWindow={0,0,0,0};
   GetCellRect(nRow, nCol, &rectCell);
   GetClientRect(&rectWindow);
   if (rectCell.right > rectWindow.right)
        SendMessage(WM_HSCROLL, SB_LINERIGHT, 0);
   if (rectCell.bottom > rectWindow.bottom)
        SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
}

void CGrid::EnsureVisible(CCellID &cell)
{
	EnsureVisible(cell.row, cell.col);
}

void CGrid::OnFixedRowClick(CCellID &cell)
{
	int fixedColumn;
	get_FixedCols(&fixedColumn);

    if (!IsValid(cell)) 
        return;

    if (m_bListMode)
    {
        if (!m_bSortOnClick) 
            return;

        LoadCursor(_Module.m_hInst,IDC_WAIT);
        if (cell.col == m_SortColumn)
            m_bAscending = !m_bAscending;
        else 
        {
            m_bAscending = TRUE;
            m_SortColumn = cell.col;
        }
        SortTextItems(m_SortColumn, m_bAscending);
        FireViewChange();
    } 
    else if (cell.col < fixedColumn) 
    {
        m_MouseMode = MOUSE_SELECT_ALL;
        OnSelecting(cell);
    } 
    else 
    {
        m_MouseMode = MOUSE_SELECT_COL;
        OnSelecting(cell);
    }
   SetCursor(LoadCursor(_Module.m_hInst,IDC_ARROW));
 
}

void CGrid::OnFixedColumnClick(CCellID &cell)
{
    if (!IsValid(cell))
        return;

//    if (m_bListMode && (GetItemState(cell.row, m_nFixedCols) & GVNI_SELECTED))
//    {
//        OnEditCell(cell.row, cell.col, VK_LBUTTON);
//        return;
//    }

	int fixedRow;
	get_FixedRows(&fixedRow);

    if (cell.row < fixedRow) 
    {
        m_MouseMode = MOUSE_SELECT_ALL;
        OnSelecting(cell);
    }
    else 
    {
        m_MouseMode = MOUSE_SELECT_ROW;
        OnSelecting(cell);
    }

}

BOOL CGrid::MouseOverColumnResizeArea(POINT point)
{
    if (point.y >= GetFixedRowHeight())
        return FALSE;
    
    CCellID idCurrentCell = GetCellFromPt(point.x,point.y);
    POINT start;
    if (!GetCellOrigin(idCurrentCell, &start)) 
        return FALSE;
    
    int endx = start.x + GetColumnWidth(idCurrentCell.col);
    
    if ((point.x - start.x <= m_nResizeCaptureRange && idCurrentCell.col != 0) || 
        endx - point.x <= m_nResizeCaptureRange)
    {
        return TRUE;
    }
    else
        return FALSE;

}

BOOL CGrid::MouseOverRowResizeArea(POINT point)
{
    if (point.x >= GetFixedColumnWidth())
        return FALSE;
    
    CCellID idCurrentCell = GetCellFromPt(point.x,point.y);
    POINT start;
    if (!GetCellOrigin(idCurrentCell, &start)) 
        return FALSE;
    
    int endy = start.y + GetRowHeight(idCurrentCell.row);
    
    if ((point.y - start.y <= m_nResizeCaptureRange && idCurrentCell.row != 0) || 
        endy - point.y <= m_nResizeCaptureRange)
    {
        return TRUE;
    }
    else
        return FALSE;

}

void CGrid::OnSelecting(const CCellID &currentCell)
{
    if (!m_bEnableSelection) 
        return;

    switch(m_MouseMode)
    {
        case MOUSE_SELECT_ALL:   SelectAllCells();            break;
        case MOUSE_SELECT_COL:   SelectColumns(currentCell);  break;
        case MOUSE_SELECT_ROW:   SelectRows(currentCell);     break;
        case MOUSE_SELECT_CELLS: SelectCells(currentCell);    break;
    }

}

// Sorts on a given column using the cell text
BOOL CGrid::SortTextItems(int nCol, BOOL bAscending)
{
    ResetSelectedRange();
    SetFocusCell(-1,-1);
	int fixedRow;
	get_FixedRows(&fixedRow);

    return SortTextItems(nCol, bAscending, fixedRow,-1);
}

// recursive sort implementation
BOOL CGrid::SortTextItems(int nCol, BOOL bAscending, int low, int high)
{
    if (nCol >= m_nCols) return FALSE;

    if (high == -1) high = m_nRows - 1;

    int lo = low;
    int hi = high;

    if( hi <= lo ) return FALSE;

    _bstr_t midItem = GetCell( (lo+hi)/2, nCol )->GetText();

    // loop through the list until indices cross
    while( lo <= hi )
    {
        // Find the first element that is greater than or equal to the partition 
        // element starting from the left Index.
        if( bAscending )
            while (lo < high  && GetCell(lo, nCol)->GetText() < midItem)
                ++lo;
        else
            while (lo < high && GetCell(lo, nCol)->GetText() > midItem)
                ++lo;

        // Find an element that is smaller than or equal to  the partition 
        // element starting from the right Index.
        if( bAscending )
            while (hi > low && GetCell(hi, nCol)->GetText() > midItem)
                --hi;
        else
            while (hi > low && GetCell(hi, nCol)->GetText() < midItem)
                --hi;

        // If the indexes have not crossed, swap if the items are not equal
        if (lo <= hi)
        {
            // swap only if the items are not equal
            if (GetCell(lo, nCol)->GetText() != GetCell(hi, nCol)->GetText())
            {
                for (int col = 0; col < m_nCols; col++)
                {
                    CGridCell *pCell = GetCell(lo, col);
                    SetCell(lo, col, GetCell(hi, col));
                    SetCell(hi, col, pCell);
                }
                UINT nRowHeight = m_arRow[lo].Height;
                m_arRow[lo].Height = m_arRow[hi].Height;
                m_arRow[hi].Height = nRowHeight;
            }

            ++lo;
            --hi;
        }
    }

    // If the right index has not reached the left side of array
    // must now sort the left partition.
    if( low < hi )
        SortTextItems(nCol, bAscending, low, hi);

    // If the left index has not reached the right side of array
    // must now sort the right partition.
    if( lo < high )
        SortTextItems(nCol, bAscending, lo, high);

    return TRUE;

}

void CGrid::ResetSelectedRange()
{
    SetSelectedRange(-1,-1,-1,-1,FALSE);
    SetFocusCell(-1,-1);
}

// recursive sort implementation
BOOL CGrid::SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data)
{
    ResetSelectedRange();
    SetFocusCell(-1,-1);
	int fixedRow;
	get_FixedRows(&fixedRow);

    return SortItems(pfnCompare, nCol, bAscending, data, fixedRow, -1);

}

void CGrid::SetSelectedRange(const CCellRange &Range, 
							 BOOL bForceRepaint /* = FALSE*/ )
{
    SetSelectedRange(Range.GetMinRow(), Range.GetMinCol(), 
                     Range.GetMaxRow(), Range.GetMaxCol(),
                     bForceRepaint);
}

void CGrid::SetSelectedRange(int nMinRow, int nMinCol, 
					  int nMaxRow, int nMaxCol,
					  BOOL bForceRepaint /*= FALSE */)
{
    if (!m_bEnableSelection) return;

    HDC hDC = NULL;
	BOOL flg = FALSE;
    if (bForceRepaint) hDC = ::GetDC(m_hWnd);
    DWORD key;
    CCellID cell;
	CGridCell* pCell;

    // Unselect all previously selected cells
//    for (POSITION pos = m_SelectedCellMap.GetStartPosition(); pos != NULL; )
	
	selMap::iterator it = m_SelectedCellMap.begin();
	try
	{
    while( it != m_SelectedCellMap.end())
    {
//        m_SelectedCellMap.GetNextAssoc(pos, key, (CCellID&)cell);
		key = it->first;
		cell= it->second;

        // Reset the selection flag on the cell
        if (IsValid(cell))
		{
            pCell = GetCell(cell.row, cell.col);
			SetItemState(cell.row, cell.col, 
                         pCell->GetState() & ~GVIS_SELECTED,&flg);

            // If this is to be reselected, continue on past the redraw
            if (nMinRow <= cell.row && cell.row <= nMaxRow &&
                nMinCol <= cell.col && cell.col <= nMaxCol)
                    ;
			else
            if (bForceRepaint && hDC)                    // Redraw NOW
                RedrawCell(cell.row, cell.col, hDC);
            else
                InvalidateCellRect(cell);                // Redraw at leisure
        }
		if(flg == FALSE)
			it++;
		else
			it = m_SelectedCellMap.begin();

    }
	}
	catch(...)
	{
		;
    }
    // if any previous selected cells are to be retained (eg Ctrl is being held down)
    // then copy them to the newly created list, and mark all these cells as
    // selected
    if (!GetSingleRowSelection())
//    for (pos = m_PrevSelectedCellMap.GetStartPosition(); pos != NULL; /* nothing */)
    
	it = m_PrevSelectedCellMap.begin();
	while (	it != m_PrevSelectedCellMap.end())
    {
//        m_PrevSelectedCellMap.GetNextAssoc(pos, key, (CCellID&)cell);
        key = it->first;
		cell = it->second;

        if (IsValid(cell))
		{
			int nState = GetCell(cell.row, cell.col)->GetState();

			// Set state as Selected. This will add the cell to m_SelectedCells[]
			SetItemState(cell.row, cell.col, nState | GVIS_SELECTED,&flg);
			// Redraw (immediately or at leisure)
			if (bForceRepaint && hDC)
				RedrawCell(cell.row, cell.col, hDC);
			else
				InvalidateCellRect(cell);
		}
		if (flg == TRUE)
			it = m_PrevSelectedCellMap.begin();
		else
			++it;
    }

    // Now select all cells in the cell range specified. If the cell has already
    // been marked as selected (above) then ignore it.
    if (nMinRow >= 0 && nMinCol >= 0 && nMaxRow >= 0 && nMaxCol >= 0 &&
        nMaxRow < m_nRows && nMaxCol < m_nCols &&
         nMinRow <= nMaxRow && nMinCol <= nMaxCol)
    {
        for (int row = nMinRow; row <= nMaxRow; row++)
            for (int col = nMinCol; col <= nMaxCol; col++) 
            {
                int nState = GetCell(row, col)->GetState();
                if (nState & GVIS_SELECTED)
                    continue;    // Already selected - ignore

                // Add to list of selected cells
                CCellID cell(row, col);

                // Set state as Selected. This will add the cell to m_SelectedCells[]
                SetItemState(row, col, nState | GVIS_SELECTED);

                // Redraw (immediately or at leisure)
                if (bForceRepaint && hDC)
                    RedrawCell(row, col, hDC);
                else
                    InvalidateCellRect(cell);
            }
    }
//    TRACE(_T("%d cells selected.\n"), m_SelectedCellMap.GetCount());

    if (hDC != NULL) 
        ::ReleaseDC(m_hWnd,hDC);

}

void CGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
    EnsureVisible(nRow, nCol);

    CCellID cell(nRow, nCol);
    if (!IsValid(cell) || !IsCellEditable(nRow, nCol) || !IsCellVisible(nRow, nCol)) 
        return;

    RECT rect;
    if (!GetCellRect(cell, &rect)) return;


/*    GV_ITEM Item;
    Item.mask = GVIF_TEXT | GVIF_FORMAT;
    Item.row = nRow;
    Item.col = nCol;
    if (!GetItem(&Item)) return;

    DWORD dwStyle = ES_LEFT;
    if (Item.nFormat & DT_RIGHT) dwStyle = ES_RIGHT;
    else if (Item.nFormat & DT_CENTER) dwStyle = ES_CENTER;
*/

//    SendMessageToParent(nRow, nCol, GVN_BEGINLABELEDIT);
/*	VARIANT_BOOL cancel = VARIANT_FALSE;

	Fire_BeforeEdit(nRow,nCol,&cancel);
	if (cancel == VARIANT_TRUE) // Cancel Editing
		return; */
	// Editing the cell
	GetCell(nRow,nCol)->Edit(m_hWnd,&rect,nRow,nCol);
}

///////////////////////////////////////////////////////////////////////////////
// Message Handler
///////////////////////////////////////////////////////////////////////////////
LRESULT CGrid::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINTS point;

	point = MAKEPOINTS(lParam);  // position of cursor 
	int fixedColumn;
	get_FixedCols(&fixedColumn);

	if (m_MouseMode == MOUSE_OVER_COL_DIVIDE) 
    {
        CCellID cell = GetCellFromPt(point.x,point.y);
        ATLASSERT(IsValid(cell));

        POINT start;
        if (!GetCellOrigin(0, cell.col, &start)) return 0;

        if (point.x - start.x <= m_nResizeCaptureRange)     // Clicked right of border
            cell.col--;

        AutosizeColumn(cell.col);
        FireViewChange();
    } 
    else if (m_MouseMode == MOUSE_OVER_ROW_DIVIDE)
    {
        CCellID cell = GetCellFromPt(point.x,point.y);
        ATLASSERT(IsValid(cell));

        POINT start;
        if (!GetCellOrigin(0, cell.col, &start)) return 0;

        if (point.y - start.y <= m_nResizeCaptureRange)     // Clicked below border
            cell.row--;

        AutosizeRow(cell.row);
        FireViewChange();
    }
    else if (m_MouseMode == MOUSE_NOTHING)
    {
        if (m_LeftClickDownCell.row >= m_nFixedRows && 
            IsValid(m_LeftClickDownCell) &&
            m_LeftClickDownCell.col >= m_nFixedCols)
        {
            OnEditCell(m_idCurrentCell.row, m_idCurrentCell.col, VK_LBUTTON);
        }
        else if (m_bListMode)
        {
            CCellID cell = GetCellFromPt(point.x,point.y);
            if (!IsValid(cell)) return 0;
            if (cell.row >= m_nFixedRows && cell.col < fixedColumn)
                OnEditCell(cell.row, cell.col, VK_LBUTTON);
        }
    }

	return 0;
}

LRESULT CGrid::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    static BOOL bAlreadyInsideThisProcedure = FALSE;
    if (bAlreadyInsideThisProcedure)
        return DefWindowProc(uMsg,wParam,lParam);

    if (!::IsWindow(m_hWnd))
        return DefWindowProc(uMsg,wParam,lParam);;

    // Start re-entry blocking
    bAlreadyInsideThisProcedure = TRUE;

//    if (::IsWindow(GetSafeHwnd()) && GetFocus()->GetSafeHwnd() != GetSafeHwnd()) 
        SetFocus();        // Auto-destroy any InPlaceEdit's

    ResetScrollBars();    

    // End re-entry blocking
    bAlreadyInsideThisProcedure = FALSE;
	return 0;
}

LRESULT CGrid::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = LOWORD(lParam);  // X position of cursor 
	point.y = HIWORD(lParam);  // Y position of cursor 

    HWND hOldFocusWnd = ::GetFocus();

    m_LeftClickDownPoint = point;
    m_LeftClickDownCell = GetCellFromPt(point.x,point.y);
    if (!IsValid(m_LeftClickDownCell)) return 0;
	

    m_SelectionStartCell = (wParam & MK_SHIFT)? m_idCurrentCell : m_LeftClickDownCell;

    SetFocus();        // Auto-destroy any InPlaceEdit's

    // If the user clicks on the current cell, then prepare to edit it.
    // (If the user moves the mouse, then dragging occurs)
    if (m_LeftClickDownCell == m_idCurrentCell)
    {
        m_MouseMode = MOUSE_PREPARE_EDIT;
        return 0;
    }   
    else if (m_MouseMode != MOUSE_OVER_COL_DIVIDE &&
             m_MouseMode != MOUSE_OVER_ROW_DIVIDE)        
    {
//        SetFocusCell(-1,-1);
        SetFocusCell(max(m_LeftClickDownCell.row, m_nFixedRows),
                     max(m_LeftClickDownCell.col, m_nFixedCols));
    }

#ifndef GRIDCONTROL_NO_DRAGDROP
    // If the user clicks on a selected cell, then prepare to drag it.
    // (If the user moves the mouse, then dragging occurs)
    if (m_bAllowDragAndDrop && hOldFocusWnd == m_hWnd && 
        GetCell(m_LeftClickDownCell.row, m_LeftClickDownCell.col)->GetState()
				& GVNI_SELECTED)
    {
        m_MouseMode = MOUSE_PREPARE_DRAG;
        return 0;
    }
#endif

    SetCapture();

    if (m_MouseMode == MOUSE_NOTHING)
    {
        if (m_bAllowColumnResize && MouseOverColumnResizeArea(point))
        {
            if (m_MouseMode != MOUSE_OVER_COL_DIVIDE)
            {
                SetCursor(LoadCursor(_Module.m_hInst,IDC_SIZEWE));
                m_MouseMode = MOUSE_OVER_COL_DIVIDE;
            }
        }
        else if (m_bAllowRowResize && MouseOverRowResizeArea(point))
        {
            if (m_MouseMode != MOUSE_OVER_ROW_DIVIDE)
            {
                SetCursor(LoadCursor(_Module.m_hInst,IDC_SIZENS));
                m_MouseMode = MOUSE_OVER_ROW_DIVIDE;
            }
        }
        //else if (m_MouseMode != MOUSE_NOTHING)
        //{
        //    SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
        //    m_MouseMode = MOUSE_NOTHING;
        //}
    }

    if (m_MouseMode == MOUSE_OVER_COL_DIVIDE) // sizing column
    {
        m_MouseMode = MOUSE_SIZING_COL;
        POINT start;
        if (!GetCellOrigin(0, m_LeftClickDownCell.col, &start)) return 0;

        RECT rect;
        GetClientRect(&rect);

        RECT invertedRect;
		invertedRect.left = point.x;
		invertedRect.top = rect.top;
		invertedRect.right = point.x + 2;
		invertedRect.bottom = rect.bottom;


        HDC hDC = ::GetDC(m_hWnd);
        if (hDC) {
            InvertRect(hDC,&invertedRect);
            ::ReleaseDC(m_hWnd,hDC);
        }

        if (point.x - start.x <= m_nResizeCaptureRange)        // clicked right of border
            if (!GetCellOrigin(0, --m_LeftClickDownCell.col, &start)) return 0;

        rect.left = start.x;
        ClientToScreen(&rect);
#ifndef _WIN32_WCE_NO_CURSOR
        ClipCursor(&rect);
#endif
    }
    else if (m_MouseMode == MOUSE_OVER_ROW_DIVIDE) // sizing row
    {
        m_MouseMode = MOUSE_SIZING_ROW;
        POINT start;
        if (!GetCellOrigin(m_LeftClickDownCell, &start)) return 0;

        RECT rect;
        GetClientRect(&rect);

        RECT invertedRect;
		invertedRect.left = rect.left;
		invertedRect.top = point.y;
		invertedRect.right = rect.right;
		invertedRect.bottom = point.y + 2;

        HDC hDC = ::GetDC(m_hWnd);
        if (hDC) {
            InvertRect(hDC,&invertedRect);
            ::ReleaseDC(m_hWnd,hDC);
        }

        if (point.y - start.y <= m_nResizeCaptureRange)            // clicked below border
            if (!GetCellOrigin(--m_LeftClickDownCell.row, 0, &start)) return 0;

        rect.top = start.y;
        ClientToScreen(&rect);
#ifndef _WIN32_WCE_NO_CURSOR
        ClipCursor(&rect);
#endif
    }
    else // not sizing or editing -- selecting
    {    
        // If Ctrl pressed, save the current cell selection. This will get added
        // to the new cell selection at the end of the cell selection process
//        m_PrevSelectedCellMap.RemoveAll();
		Fire_SelChanging(); // Fire evnt SelChanging

        m_PrevSelectedCellMap.clear();
        if (wParam & MK_CONTROL) {
//            for (POSITION pos = m_SelectedCellMap.GetStartPosition(); pos != NULL; )
            for (selMap::iterator it = m_SelectedCellMap.begin();
				it != m_SelectedCellMap.end();
				it++)
            {
                DWORD key;
                CCellID cell;
//                m_SelectedCellMap.GetNextAssoc(pos, key, (CCellID&)cell);
                key = it->first;
				cell= it->second;
//                m_PrevSelectedCellMap[key] = cell;
                m_PrevSelectedCellMap.insert(ValuePair(key,cell));
            }
        }
        
		int fixedRow;
		int fixedColumn;
		get_FixedRows(&fixedRow);
		get_FixedCols(&fixedColumn);

        if (m_LeftClickDownCell.row < fixedRow)
            OnFixedRowClick(m_LeftClickDownCell);
        else if (m_LeftClickDownCell.col < fixedColumn)
            OnFixedColumnClick(m_LeftClickDownCell);
        else
        {
            m_MouseMode = m_bListMode? MOUSE_SELECT_ROW : MOUSE_SELECT_CELLS;
            OnSelecting(m_LeftClickDownCell);
        }
        m_nTimerID = ::SetTimer(m_hWnd,WM_LBUTTONDOWN, m_nTimerInterval, 0);

    }   
    m_LastMousePoint = point;
	return 0;
}

LRESULT CGrid::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	UINT nChar = (UINT) wParam;    // virtual-key code 

    if (!IsValid(m_idCurrentCell)) 
        return 0;

    CCellID next = m_idCurrentCell;
    BOOL bChangeLine = FALSE;

    if (IsCTRLpressed())
    {
        switch (nChar)
        {
           case 'A': SelectAllCells();  break;
#ifndef GRIDCONTROL_NO_CLIPBOARD
//           case 'X': OnEditCut();        break;
//           case 'C': OnEditCopy();       break;
//           case 'V': OnEditPaste();      break;
#endif
        }
    }

    switch (nChar)
    {
        case VK_DELETE: 
            if (IsCellEditable(m_idCurrentCell.row, m_idCurrentCell.col))
            {
				//SendMessageToParent(m_idCurrentCell.row, m_idCurrentCell.col, GVN_BEGINLABELEDIT);
				VARIANT_BOOL cancel;
				Fire_BeforeEdit(m_idCurrentCell.row, m_idCurrentCell.col,&cancel);
				if (cancel == VARIANT_TRUE) // Stop editing
					return 0; // Stop Editing
				_bstr_t t = _T("");
                GetCell(m_idCurrentCell.row, m_idCurrentCell.col)->put_Text(t);
                SetModified(TRUE, m_idCurrentCell.row, m_idCurrentCell.col);
 				//SendMessageToParent(m_idCurrentCell.row, m_idCurrentCell.col, GVN_ENDLABELEDIT);
				Fire_AfterEdit(m_idCurrentCell.row, m_idCurrentCell.col);
                RedrawCell(m_idCurrentCell);
            }
            break;

        case VK_TAB:    
            if (IsSHIFTpressed())
            {
                if (next.col > m_nFixedCols) 
                    next.col--;
                else if (next.col == m_nFixedCols && next.row > m_nFixedRows) 
                {
                    next.row--; 
                    next.col = m_nCols - 1; 
                    bChangeLine = TRUE;
                }
            }
            else
            {
                if (next.col < (m_nCols - 1)) 
                    next.col++;
                else if (next.col == (m_nCols - 1) && 
                         next.row < (m_nRows - 1) )
                {
                    next.row++; 
                    next.col = m_nFixedCols; 
                    bChangeLine = TRUE;
                }
            } 
            break;

        case VK_DOWN:   
            if (next.row < (m_nRows - 1))
                next.row++; 
            break;            
            
        case VK_UP:     
            if (next.row > m_nFixedRows)           
                next.row--; 
            break;

        case VK_RIGHT:  
            if (next.col < (m_nCols - 1)) 
                next.col++; 
            break;
            
        case VK_LEFT:   
            if (next.col > m_nFixedCols)           
                next.col--; 
            break;

        case VK_NEXT:   
            {
            CCellID idOldTopLeft = GetTopleftNonFixedCell();
            SendMessage(WM_VSCROLL, SB_PAGEDOWN, 0);
            CCellID idNewTopLeft = GetTopleftNonFixedCell();

            int increment = idNewTopLeft.row - idOldTopLeft.row;
            if (increment) {
                next.row += increment;
                if (next.row > (m_nRows - 1)) 
                    next.row = m_nRows - 1;
            }
            else
                next.row = m_nRows - 1;
                break;
            }
    
            case VK_PRIOR:  
            {
            CCellID idOldTopLeft = GetTopleftNonFixedCell();
            SendMessage(WM_VSCROLL, SB_PAGEUP, 0);
            CCellID idNewTopLeft = GetTopleftNonFixedCell();

            int increment = idNewTopLeft.row - idOldTopLeft.row;
            if (increment) 
            {
                next.row += increment;
                if (next.row < m_nFixedRows) 
                    next.row = m_nFixedRows;
            } else
                next.row = m_nFixedRows;
                break;
            }
    
        case VK_HOME:   
            SendMessage(WM_VSCROLL, SB_TOP, 0);
            next.row = m_nFixedRows;
            break;
        
        case VK_END:    
            SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
            next.row = m_nRows - 1;
            break;
                
        default:
            DefWindowProc(uMsg,wParam,lParam);
    }
  
    if (next != m_idCurrentCell) 
    {
        // While moving with the Cursorkeys the current ROW/CELL will get selected
        // OR Selection will get expanded when SHIFT is pressed
        // Cut n paste from OnLButtonDown - Franco Bez 
        // Added check for NULL mouse mode - Chris Maunder.
        if (m_MouseMode == MOUSE_NOTHING)
        {
//            m_PrevSelectedCellMap.RemoveAll();
            m_PrevSelectedCellMap.clear();
            m_MouseMode = m_bListMode? MOUSE_SELECT_ROW : MOUSE_SELECT_CELLS;
            if (!IsSHIFTpressed() || nChar == VK_TAB)
                m_SelectionStartCell = next;
            OnSelecting(next);
            m_MouseMode = MOUSE_NOTHING;
        }

        SetFocusCell(next);

        if (!IsCellVisible(next))
        {   
            EnsureVisible(next); // Make sure cell is visible

            switch (nChar) {
                case VK_RIGHT:  
                    SendMessage(WM_HSCROLL, SB_LINERIGHT, 0); 
                    break;

                case VK_LEFT:   
                    SendMessage(WM_HSCROLL, SB_LINELEFT, 0);  
                    break;

                case VK_DOWN:   
                    SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);  
                    break;
                
                case VK_UP:     
                    SendMessage(WM_VSCROLL, SB_LINEUP, 0);    
                    break;                
                
                case VK_TAB:    
                    if (IsSHIFTpressed())
                    {
                        if (bChangeLine) 
                        {
                            SendMessage(WM_VSCROLL, SB_LINEUP, 0);
                            SetScrollPos32(SB_HORZ, m_nHScrollMax);
                            break;
                        }
                        else 
                            SendMessage(WM_HSCROLL, SB_LINELEFT, 0);
                    }
                    else
                    {
                        if (bChangeLine) 
                        {
                            SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
                            SetScrollPos32(SB_HORZ, 0);
                            break;
                        }
                        else 
                            SendMessage(WM_HSCROLL, SB_LINERIGHT, 0);
                    }
                    break;

            }
            FireViewChange();
        }
    }
	return 0;
}

LRESULT CGrid::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
/////////////////////////
// Provvisorio serve per la creazione di CInPlaceEdit

	UINT nChar = wParam;
	if (!IsCTRLpressed() && m_MouseMode == MOUSE_NOTHING)
    {
        if (!m_bHandleTabKey || (m_bHandleTabKey && nChar != VK_TAB))
            OnEditCell(m_idCurrentCell.row, m_idCurrentCell.col, nChar);
    }
	return 0;
}

LRESULT CGrid::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nFlags = wParam;
	POINT point;
	POINT p1;
	p1.x = LOWORD(lParam);
	p1.y = HIWORD(lParam);
	
	point = p1;

    RECT rect;
    GetClientRect(&rect);

#ifndef GRIDCONTROL_NO_DRAGDROP
    // If outside client area, return (unless we are drag n dropping)
    if (m_MouseMode != MOUSE_DRAGGING && !::PtInRect(&rect, p1))
        return 0;
#endif

    // If the left mouse button is up, then test to see if row/column sizing is imminent
    if (!(nFlags & MK_LBUTTON) 
        || (m_MouseMode == MOUSE_NOTHING && (nFlags & MK_LBUTTON)))
    {
        if (m_bAllowColumnResize && MouseOverColumnResizeArea(point))
        {
            if (m_MouseMode != MOUSE_OVER_COL_DIVIDE)
            {
                SetCursor(LoadCursor(NULL,IDC_SIZEWE));
                m_MouseMode = MOUSE_OVER_COL_DIVIDE;
				SetCapture(); // We have to capture the mouse Mario
            }
        }
        else if (m_bAllowRowResize && MouseOverRowResizeArea(point))
        {
            if (m_MouseMode != MOUSE_OVER_ROW_DIVIDE)
            {
                SetCursor(LoadCursor(NULL,IDC_SIZENS));
                m_MouseMode = MOUSE_OVER_ROW_DIVIDE;
				SetCapture(); // We have to capture the mouse Mario
            }
        }
        else if (m_MouseMode != MOUSE_NOTHING)
        {
            SetCursor(LoadCursor(NULL,IDC_ARROW));
            m_MouseMode = MOUSE_NOTHING;
			ReleaseCapture();
        }

#ifndef GRIDCONTROL_NO_TITLETIPS
        if (m_MouseMode == MOUSE_NOTHING && m_bTitleTips)
        {
            CCellID idCurrentCell = GetCellFromPt(point);
            RECT TextRect, CellRect;
			CGridCell* pCell = GetCell(idCurrentCell.row, idCurrentCell.col);

            if (pCell && GetTextRect(idCurrentCell.row, idCurrentCell.col, &TextRect) &&
                GetCellRect(idCurrentCell.row, idCurrentCell.col, &CellRect))

               m_TitleTip->Show(TextRect, 
                                pCell->GetText(), 
                                0,
                                &CellRect,
                                pCell->GetFont());
        }
#endif

        m_LastMousePoint = point;
        return 0;
    }

    if (!IsValid(m_LeftClickDownCell))
    {
        m_LastMousePoint = point;
        return 0;
    }

    // If the left mouse button is down, then process appropriately
    if (nFlags & MK_LBUTTON) 
    {
        switch(m_MouseMode)
        {
            case MOUSE_SELECT_ALL:        
                break;

            case MOUSE_SELECT_COL:
            case MOUSE_SELECT_ROW:    
            case MOUSE_SELECT_CELLS:    
                {
                    CCellID idCurrentCell = GetCellFromPt(point.x,point.y);
                    if (!IsValid(idCurrentCell)) 
                        return 0;

                    if (idCurrentCell != m_idCurrentCell)
                    {
                        OnSelecting(idCurrentCell);
                        //SetFocusCell(max(idCurrentCell.row, m_nFixedRows),
                        //             max(idCurrentCell.col, m_nFixedCols));
                        if (idCurrentCell.row >= m_nFixedRows &&
                            idCurrentCell.col >= m_nFixedCols)
                        {
                            SetFocusCell(idCurrentCell);
                        }
                    }
                    break;
                }

            case MOUSE_SIZING_COL:   
                {
                    HDC hDC = ::GetDC(m_hWnd);
                    if (!hDC) break;
                    
					RECT oldInvertedRect;
					oldInvertedRect.left =m_LastMousePoint.x;
					oldInvertedRect.top = rect.top;
					oldInvertedRect.right = m_LastMousePoint.x + 2;
					oldInvertedRect.bottom = rect.bottom;

                    InvertRect(hDC,&oldInvertedRect);

					RECT newInvertedRect;
					newInvertedRect.left =point.x;
					newInvertedRect.top = rect.top;
					newInvertedRect.right = point.x + 2;
					newInvertedRect.bottom = rect.bottom;

                    InvertRect(hDC,&newInvertedRect);
                    ::ReleaseDC(m_hWnd,hDC);
                }
                break;
                
            case MOUSE_SIZING_ROW:        
                {
                    HDC hDC = ::GetDC(m_hWnd);
                    if (!hDC) break;
                    
					RECT oldInvertedRect;
					oldInvertedRect.left = rect.left;
					oldInvertedRect.top = m_LastMousePoint.y;
					oldInvertedRect.right = rect.right;
					oldInvertedRect.bottom = m_LastMousePoint.y + 2;


                    InvertRect(hDC,&oldInvertedRect);


					RECT newInvertedRect;
					newInvertedRect.left =rect.left;
					newInvertedRect.top = point.y;
					newInvertedRect.right = rect.right;
					newInvertedRect.bottom = point.y + 2;
                    InvertRect(hDC,&newInvertedRect);

                    ::ReleaseDC(m_hWnd,hDC);
                }
                break;

#ifndef GRIDCONTROL_NO_DRAGDROP
            case MOUSE_PREPARE_DRAG:   
                OnBeginDrag();    
                break;
#endif
        }    
    }

    m_LastMousePoint = point;
	return 0;
}

LRESULT CGrid::OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // A m_nRowsPerWheelNotch value less than 0 indicates that the mouse
    // wheel scrolls whole pages, not just lines.
	short zDelta = (short) HIWORD( wParam); // wheel rotation 
    if (m_nRowsPerWheelNotch == -1)
    {
        int nPagesScrolled = zDelta / 120;

        if (nPagesScrolled > 0)
            for (int i = 0; i < nPagesScrolled; i++)
                PostMessage(WM_VSCROLL, SB_PAGEUP, 0);
        else
            for (int i = 0; i > nPagesScrolled; i--)
                PostMessage(WM_VSCROLL, SB_PAGEDOWN, 0);
    }
    else
    {
        int nRowsScrolled = m_nRowsPerWheelNotch * zDelta / 120;

        if (nRowsScrolled > 0)
            for (int i = 0; i < nRowsScrolled; i++)
                PostMessage(WM_VSCROLL, SB_LINEUP, 0);
        else
            for (int i = 0; i > nRowsScrolled; i--)
                PostMessage(WM_VSCROLL, SB_LINEDOWN, 0);
    }

	return 0;
}

LRESULT CGrid::OnLButtonUP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);

#ifndef _WIN32_WCE_NO_CURSOR
    ClipCursor(NULL);
#endif

    if (GetCapture() == m_hWnd)
    {
        ReleaseCapture();
        KillTimer(m_nTimerID);
        m_nTimerID = 0;
    }

    // m_MouseMode == MOUSE_PREPARE_EDIT only if user clicked down on current cell
    // and then didn't move mouse before clicking up (releasing button)
    if (m_MouseMode == MOUSE_PREPARE_EDIT)    
    {
        OnEditCell(m_idCurrentCell.row, m_idCurrentCell.col, VK_LBUTTON);
    }
#ifndef GRIDCONTROL_NO_DRAGDROP
    // m_MouseMode == MOUSE_PREPARE_DRAG only if user clicked down on a selected cell
    // and then didn't move mouse before clicking up (releasing button)
    else if (m_MouseMode == MOUSE_PREPARE_DRAG) 
    {
        ResetSelectedRange();
    }
#endif
    else if (m_MouseMode == MOUSE_SIZING_COL)
    {
        RECT rect;
        GetClientRect(&rect);

        RECT invertedRect;
		invertedRect.left = m_LastMousePoint.x;
		invertedRect.top = rect.top;
		invertedRect.right = m_LastMousePoint.x + 2;
		invertedRect.bottom = rect.bottom;

        HDC hDC = ::GetDC(m_hWnd);
        if (hDC) {
            InvertRect(hDC,&invertedRect);
            ::ReleaseDC(m_hWnd,hDC);
        }

        if ( (m_LeftClickDownPoint.x != point.x) && (m_LeftClickDownPoint.y != point.y)) 
        {   
            POINT start;
            if (!GetCellOrigin(m_LeftClickDownCell, &start)) 
				return DefWindowProc(uMsg,wParam,lParam);

            put_ColumnWidth(m_LeftClickDownCell.col, point.x - start.x);
            ResetScrollBars();
            FireViewChange();
        }
    }
    else if (m_MouseMode == MOUSE_SIZING_ROW)
    {
        RECT rect;
        GetClientRect(&rect);

        RECT invertedRect;
		invertedRect.left = rect.left;
		invertedRect.top = m_LastMousePoint.y;
		invertedRect.right = rect.right;
		invertedRect.bottom = m_LastMousePoint.y + 2;
    
        HDC hDC = GetDC();
        if (hDC)
		{
            InvertRect(hDC,&invertedRect);
            ReleaseDC(hDC);
        }
   
        if ((m_LeftClickDownPoint.x != point.x) && (m_LeftClickDownPoint.y != point.y)) 
        {
            POINT start;
            if (!GetCellOrigin(m_LeftClickDownCell, &start))
				return DefWindowProc(uMsg,wParam,lParam);

            put_RowHeight(m_LeftClickDownCell.row, point.y - start.y);
            ResetScrollBars();
            FireViewChange();
        }
    } 
	else 	// Not sizing ... => end selecting
		Fire_SelChanged();


    m_MouseMode = MOUSE_NOTHING;

//    SetCursor(LoadCursor(_Module.m_hInst,IDC_ARROW));

    if (!IsValid(m_LeftClickDownCell)) 
		return DefWindowProc(uMsg,wParam,lParam);

	return DefWindowProc(uMsg,wParam,lParam);
}

LRESULT CGrid::OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nSBCode = (int) LOWORD(wParam);  // scroll bar value 
	UINT nPos = (short int) HIWORD(wParam);   // scroll box position 

	int fixedColumn;
	get_FixedCols(&fixedColumn);

    if (GetFocus()!= m_hWnd) 
        SetFocus();  // Auto-destroy any InPlaceEdit's

#ifndef GRIDCONTROL_NO_TITLETIPS
    m_TitleTip->Hide();  // hide any titletips
#endif

    int scrollPos = GetScrollPos32(SB_HORZ);

    CCellID idTopLeft = GetTopleftNonFixedCell();

    RECT rect;
    GetClientRect(&rect);

    switch (nSBCode)
    {
        case SB_LINERIGHT:
            if (scrollPos < m_nHScrollMax)
            {
                int xScroll = GetColumnWidth(idTopLeft.col);
                SetScrollPos32(SB_HORZ, scrollPos + xScroll);
                if (GetScrollPos32(SB_HORZ) == scrollPos) break;          // didn't work

                rect.left = GetFixedColumnWidth() + xScroll;
                ScrollWindow(-xScroll, 0, &rect);
                rect.left = rect.right - xScroll;
                InvalidateRect(&rect);
            }
            break;

        case SB_LINELEFT:
            if (scrollPos > 0 && idTopLeft.col > fixedColumn)
            {
                int xScroll = GetColumnWidth(idTopLeft.col-1);
                SetScrollPos32(SB_HORZ, max(0,scrollPos - xScroll));
                rect.left = GetFixedColumnWidth();
                ScrollWindow(xScroll, 0, &rect);
                rect.right = rect.left + xScroll;
                InvalidateRect(&rect);
            }
            break;

        case SB_PAGERIGHT:
            if (scrollPos < m_nHScrollMax)
            {
                rect.left = GetFixedColumnWidth();
                int offset = rect.right - rect.left;
                int pos = min(m_nHScrollMax, scrollPos + offset);
                SetScrollPos32(SB_HORZ, pos);
                rect.left = GetFixedColumnWidth();
                InvalidateRect(&rect);
            }
            break;

        case SB_PAGELEFT:
            if (scrollPos > 0)
            {
                rect.left = GetFixedColumnWidth();
                int offset = -(rect.right - rect.left);
                int pos = max(0, scrollPos + offset);
                SetScrollPos32(SB_HORZ, pos);
                rect.left = GetFixedColumnWidth();
                InvalidateRect(&rect);
            }
            break;

        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            {
                SetScrollPos32(SB_HORZ, GetScrollPos32(SB_HORZ, TRUE));
                CCellID idNewTopLeft = GetTopleftNonFixedCell();
                if (idNewTopLeft != idTopLeft)
                {
                    rect.left = GetFixedColumnWidth();
                    InvalidateRect(&rect);
                }
            }
            break;

        case SB_LEFT:
            if (scrollPos > 0)
            {
                SetScrollPos32(SB_HORZ, 0);
                FireViewChange();
            }
            break;

        case SB_RIGHT:
            if (scrollPos < m_nHScrollMax)
            {
                SetScrollPos32(SB_HORZ, m_nHScrollMax);
                FireViewChange();
            }
            break;


        default: break;
    }
	return 0;
}

LRESULT CGrid::OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (GetFocus() != m_hWnd) 
        SetFocus();        // Auto-destroy any InPlaceEdit's

#ifndef GRIDCONTROL_NO_TITLETIPS
    m_TitleTip->Hide();  // hide any titletips
#endif

    // Get the scroll position ourselves to ensure we get a 32 bit value
    int scrollPos = GetScrollPos32(SB_VERT);

    CCellID idTopLeft = GetTopleftNonFixedCell();

    RECT rect;
    GetClientRect(&rect);

	UINT nSBCode = (int) LOWORD(wParam);  // scroll bar value 
	UINT nPos = (short int) HIWORD(wParam);   // scroll box position 

	int fixedRow;
	get_FixedRows(&fixedRow);

    switch (nSBCode)
    {
        case SB_LINEDOWN:
            if (scrollPos < m_nVScrollMax)
            {
                int yScroll = GetRowHeight(idTopLeft.row);
                SetScrollPos32(SB_VERT, scrollPos + yScroll);
                if (GetScrollPos32(SB_VERT) == scrollPos) 
                    break;          // didn't work

                rect.top = GetFixedRowHeight() + yScroll;
                ScrollWindow( 0, -yScroll, &rect);
                rect.top = rect.bottom - yScroll;
                InvalidateRect(&rect);
            }
            break;

        case SB_LINEUP:
            if (scrollPos > 0 && idTopLeft.row > fixedRow)
            {
                int yScroll = GetRowHeight(idTopLeft.row-1);
                SetScrollPos32(SB_VERT, max(0, scrollPos - yScroll));
                rect.top = GetFixedRowHeight();
                ScrollWindow(0, yScroll, &rect);
                rect.bottom = rect.top + yScroll;
                InvalidateRect(&rect);
            }
            break;

        case SB_PAGEDOWN:
            if (scrollPos < m_nVScrollMax)
            {
                rect.top = GetFixedRowHeight();
                scrollPos = min(m_nVScrollMax, scrollPos + (rect.bottom - rect.top));
                SetScrollPos32(SB_VERT, scrollPos);
                rect.top = GetFixedRowHeight();
                InvalidateRect(&rect);
            }
            break;

        case SB_PAGEUP:
            if (scrollPos > 0)
            {
                rect.top = GetFixedRowHeight();
                int offset = -(rect.bottom - rect.top);
                int pos = max(0, scrollPos + offset);
                SetScrollPos32(SB_VERT, pos);
                rect.top = GetFixedRowHeight();
                InvalidateRect(&rect);
            }
            break;

        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            {
                SetScrollPos32(SB_VERT, GetScrollPos32(SB_VERT, TRUE));
                CCellID idNewTopLeft = GetTopleftNonFixedCell();
                if (idNewTopLeft != idTopLeft)
                {
                    rect.top = GetFixedRowHeight();
                    InvalidateRect(&rect);
                }
            }
            break;

        case SB_TOP:
            if (scrollPos > 0)
            {
                SetScrollPos32(SB_VERT, 0);
                FireViewChange();
            }
            break;

        case SB_BOTTOM:
            if (scrollPos < m_nVScrollMax)
            {
                SetScrollPos32(SB_VERT, m_nVScrollMax);
                FireViewChange();
            }

        default: break;
    }
		return 0;
}

LRESULT CGrid::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nIDEvent = wParam;
    ATLASSERT(nIDEvent == WM_LBUTTONDOWN);
    if (nIDEvent != WM_LBUTTONDOWN)
        return 0;

    POINT pt, origPt;

#ifdef _WIN32_WCE
    if (m_MouseMode == MOUSE_NOTHING)
        return;
    origPt = GetMessagePos();
#else
    if (!GetCursorPos(&origPt))
        return 0;
#endif

    ScreenToClient(&origPt);

    RECT rect;
    GetClientRect(&rect);

    int nFixedRowHeight = GetFixedRowHeight();
    int nFixedColWidth = GetFixedColumnWidth();

    pt = origPt;
    if (pt.y > rect.bottom)
    {
        //SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
        SendMessage(WM_KEYDOWN, VK_DOWN, 0);

        if (pt.x < rect.left)  
            pt.x = rect.left;
        if (pt.x > rect.right) 
            pt.x = rect.right;
        pt.y = rect.bottom;
        OnSelecting(GetCellFromPt(pt.x,pt.y));
    }
    else if (pt.y < nFixedRowHeight)
    {
        //SendMessage(WM_VSCROLL, SB_LINEUP, 0);
        SendMessage(WM_KEYDOWN, VK_UP, 0);

        if (pt.x < rect.left)  
            pt.x = rect.left;
        if (pt.x > rect.right) 
            pt.x = rect.right;
        pt.y = nFixedRowHeight + 1;
        OnSelecting(GetCellFromPt(pt.x,pt.y));
    }

    pt = origPt;
    if (pt.x > rect.right)
    {
        // SendMessage(WM_HSCROLL, SB_LINERIGHT, 0);
        SendMessage(WM_KEYDOWN, VK_RIGHT, 0);

        if (pt.y < rect.top)    
            pt.y = rect.top;
        if (pt.y > rect.bottom) 
            pt.y = rect.bottom;
        pt.x = rect.right;
        OnSelecting(GetCellFromPt(pt.x,pt.y));
    } 
    else if (pt.x < nFixedColWidth)
    {
        //SendMessage(WM_HSCROLL, SB_LINELEFT, 0);
        SendMessage(WM_KEYDOWN, VK_LEFT, 0);

        if (pt.y < rect.top)    
            pt.y = rect.top;
        if (pt.y > rect.bottom)
            pt.y = rect.bottom;
        pt.x = nFixedColWidth + 1;
        OnSelecting(GetCellFromPt(pt.x,pt.y));
    }
	return 0;
}

////////////////////////////////////////////////////////////
// End Grid Operations
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Grid Drawing
////////////////////////////////////////////////////////////

BOOL CGrid::RedrawCell(const CCellID &cell, HDC hDC /*= NULL*/)
{
    return RedrawCell(cell.row, cell.col, hDC);
}

BOOL CGrid::RedrawCell(int nRow, int nCol, HDC hDC)
{
	BOOL bResult = TRUE;
    BOOL bMustReleaseDC = FALSE;

    if (!m_bAllowDraw || !IsCellVisible(nRow, nCol))
        return FALSE;

    RECT rect;
    if (!GetCellRect(nRow, nCol, &rect)) 
        return FALSE;

    if (!hDC) {
        hDC = ::GetDC(m_hWnd);
        if (hDC)
            bMustReleaseDC = TRUE;
    }

    if (hDC)
    {
        // Redraw cells directly
        if (nRow < m_nFixedRows || nCol < m_nFixedCols)
        {
            bResult = DrawFixedCell(hDC, nRow, nCol, rect, TRUE);
        }
        else
        {
            bResult = 
				GetCell(nRow,nCol)->DrawCell(hDC,
				m_pImageList,
				rect,
				m_crTextBkColour,
				m_crTextColour,
				m_nMargin,
				TRUE);
            
            // Since we have erased the background, we will need to redraw the gridlines
			HPEN pen = CreatePen(PS_SOLID, 0, m_crGridColour);;
			HPEN pOldPen =NULL;
			if(pen)
				HPEN pOldPen = (HPEN) SelectObject(hDC,(HPEN)pen);
			else
				return FALSE;

            if (m_nGridLines == GVL_BOTH || m_nGridLines == GVL_HORZ) 
            {
                MoveToEx(hDC,rect.left, rect.bottom,NULL);
                LineTo(hDC,rect.right+1, rect.bottom);
            }
            if (m_nGridLines == GVL_BOTH || m_nGridLines == GVL_VERT) 
            {
                MoveToEx(hDC,rect.right, rect.top,NULL);
                LineTo(hDC,rect.right, rect.bottom+1);    
            }
            SelectObject(hDC,pOldPen);
			DeleteObject(pen);
//			DeleteObject(pOldPen);
        }
    } else
        InvalidateRect(&rect, TRUE);     // Could not get a DC - FireViewChange it anyway
                                        // and hope that OnPaint manages to get one

    if (bMustReleaseDC) 
        ::ReleaseDC(m_hWnd,hDC);

    return bResult;
}

BOOL CGrid::DrawFixedCell(HDC hDC, int nRow, int nCol, RECT rect, BOOL bEraseBk)
{
    if (!m_bAllowDraw) 
        return FALSE;
	
/*
    GV_ITEM Item;
    Item.mask = GVIF_TEXT | GVIF_FORMAT | GVIF_IMAGE | GVIF_BKCLR | GVIF_FGCLR;
    Item.row = nRow;
    Item.col = nCol;
    if (!GetItem(&Item))
        return FALSE;
*/
	CGridCell* Item = GetCell(nRow,nCol);
	if (Item== 0)
		return FALSE;

    // Force redraw of background if custom colour
    //if (Item.crBkClr != CLR_DEFAULT)
        bEraseBk = TRUE;

    if (bEraseBk)
    {
        HBRUSH brush;
		brush = CreateSolidBrush((Item->GetCRBkClr() == CLR_DEFAULT)? m_crFixedBkColour : Item->GetCRBkClr());
        FillRect(hDC,&rect, brush);
		DeleteObject(brush);
    }
    ::SetTextColor(hDC,(Item->GetCRFgClr() == CLR_DEFAULT)? m_crFixedTextColour : Item->GetCRFgClr());
    
    int nSavedDC = SaveDC(hDC);
    
    // Create the appropriate font and select into DC
	CGridCell* pCell;
	pCell = GetCell(nRow,nCol);
	LOGFONT cLF;

	if (pCell)
      cLF = *pCell->GetFont();
	else
		cLF = m_Logfont;

    CCellID FocusCell = m_idCurrentCell;

    // if (IsCellFixed(nRow, nCol) && (FocusCell.row == nRow || FocusCell.col == nCol))
    //{
    if (FocusCell.row == nRow || FocusCell.col == nCol)
    {
        static LOGFONT lf;
        memcpy(&lf, &cLF, sizeof(LOGFONT));
        lf.lfWeight = SELECTED_CELL_FONT_WEIGHT;
        cLF = lf;
    }
   
    HFONT Font;
    Font = CreateFontIndirect(&cLF);
    SelectObject(hDC,Font);

    if (IsValid(FocusCell) &&  (FocusCell.row == nRow || FocusCell.col == nCol))
    {
        rect.right++; rect.bottom++;
        DrawEdge(hDC,&rect, BDR_SUNKENINNER /*EDGE_RAISED*/, BF_RECT);
        InflateRect(&rect,-1,-1);
    }
    else
    {
        HPEN lightpen,
             darkpen,
             pOldPen ;

		lightpen = CreatePen(PS_SOLID, 1,  ::GetSysColor(COLOR_3DHIGHLIGHT));
		darkpen = CreatePen(PS_SOLID,  1, ::GetSysColor(COLOR_3DDKSHADOW));
    
		if (lightpen && darkpen)
		{
			pOldPen = (HPEN) SelectObject(hDC,lightpen);
			MoveToEx(hDC,rect.right, rect.top,NULL);
			LineTo(hDC,rect.left, rect.top);
			LineTo(hDC,rect.left, rect.bottom);

			SelectObject(hDC,darkpen);
			MoveToEx(hDC,rect.right, rect.top,NULL);
			LineTo(hDC,rect.right, rect.bottom);
			LineTo(hDC,rect.left, rect.bottom);

			SelectObject(hDC,pOldPen);
			InflateRect(&rect,-1,-1);

			DeleteObject(lightpen);
			DeleteObject(darkpen);
			DeleteObject(pOldPen);
		}
		else
		{
			LPTSTR lpMsgBuf;
			DWORD err = GetLastError();

			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER,
				NULL,
				err,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				lpMsgBuf,
				0,
				NULL 
			);
			// Process any inserts in lpMsgBuf.
			// ...
			// Display the string.
			ATLTRACE( (LPCTSTR)lpMsgBuf);
			// Free the buffer.
			LocalFree( lpMsgBuf );
		}

    }

    SetBkMode(hDC,TRANSPARENT);
    InflateRect(&rect,-m_nMargin, 0);

    if (m_pImageList && Item->GetImage() >= 0)
    {
        IMAGEINFO Info;
        if (ImageList_GetImageInfo(m_pImageList,Item->GetImage(), &Info))
        {
            //CRgn rgn;
            //rgn.CreateRectRgnIndirect(rect);
            //pDC->SelectClipRgn(&rgn);
            //rgn.DeleteObject();
    
            int nImageWidth = Info.rcImage.right-Info.rcImage.left+1;
			
			IMAGELISTDRAWPARAMS iDP;
			iDP.cbSize = sizeof(iDP);
			iDP.cx = 0;
			iDP.cy = 0;
			iDP.dwRop = SRCCOPY ;
			iDP.fStyle = ILD_NORMAL;
			iDP.hdcDst = hDC;
			iDP.himl = m_pImageList;
			iDP.i = Item->GetImage();
			iDP.rgbBk = CLR_DEFAULT;
			iDP.rgbFg = CLR_DEFAULT;
			iDP.x = rect.left;
			iDP.y = rect.top;
			iDP.xBitmap = 0;
			iDP.yBitmap = 0;

            ImageList_DrawIndirect(&iDP);
            rect.left += nImageWidth+m_nMargin;
        }
    }

    DrawText(hDC, Item->GetText(), -1, &rect, Item->GetFormat());

    RestoreDC(hDC,nSavedDC);
    DeleteObject(Font);

    return TRUE;

}

void CGrid::DrawGrid(HDC hDC,RECT rc)
{
    RECT rect;
    int row,col;

    RECT clipRect=rc;

/*    if (GetClipBox(hDC,&clipRect) == ERROR) 
        return;
*/
    EraseBkgnd(hDC,rc);            // OnEraseBkgnd does nothing, so erase bkgnd here.
                                // This necessary since we may be using a Memory DC.

    int nFixedRowHeight = GetFixedRowHeight();
    int nFixedColWidth  = GetFixedColumnWidth();

    CCellID idTopLeft = GetTopleftNonFixedCell();
    int minVisibleRow = idTopLeft.row,
        minVisibleCol = idTopLeft.col;

    RECT VisRect;
    CCellRange VisCellRange = GetVisibleNonFixedCellRange(&VisRect);
    int maxVisibleRow = VisCellRange.GetMaxRow(),
        maxVisibleCol = VisCellRange.GetMaxCol();

    // draw top-left cells 0..m_nFixedRows-1, 0..m_nFixedCols-1
    rect.bottom = -1;
    for (row = 0; row < m_nFixedRows; row++)
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + GetRowHeight(row)-1;
        rect.right = -1;
		if(GetRowHeight(row)>0)
        for (col = 0; col < m_nFixedCols; col++)
        {
            rect.left = rect.right+1;
            rect.right = rect.left + GetColumnWidth(col)-1;  
            
            DrawFixedCell(hDC, row, col, rect,FALSE);
        }
    }
     
    // draw fixed column cells:  m_nFixedRows..n, 0..m_nFixedCols-1
    rect.bottom = nFixedRowHeight-1;
    for (row = minVisibleRow; row <= maxVisibleRow; row++)
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + GetRowHeight(row)-1;

        // rect.bottom = bottom pixel of previous row
        if (rect.top > clipRect.bottom) 
            break;                // Gone past cliprect
        if (rect.bottom < clipRect.top)
            continue;             // Reached cliprect yet?

        rect.right = -1;
 		if(GetRowHeight(row)>0)
		for (col = 0; col < m_nFixedCols; col++)
		{
			rect.left = rect.right+1;
			rect.right = rect.left + GetColumnWidth(col)-1;

			if (rect.left > clipRect.right) 
				break;            // gone past cliprect
			if (rect.right < clipRect.left) 
				continue;         // Reached cliprect yet?

			DrawFixedCell(hDC, row, col, rect,FALSE);
		}
    }
    
    // draw fixed row cells  0..m_nFixedRows, m_nFixedCols..n
    rect.bottom = -1;
    for (row = 0; row < m_nFixedRows; row++)
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + GetRowHeight(row)-1;

        // rect.bottom = bottom pixel of previous row
        if (rect.top > clipRect.bottom) 
            break;                // Gone past cliprect
        if (rect.bottom < clipRect.top) 
            continue;             // Reached cliprect yet?

        rect.right = nFixedColWidth-1;
		if(GetRowHeight(row)>0)
        for (col = minVisibleCol; col <= maxVisibleCol; col++)
        {                                       
            rect.left = rect.right+1;
            rect.right = rect.left + GetColumnWidth(col)-1;

            if (rect.left > clipRect.right)
                break;        // gone past cliprect
            if (rect.right < clipRect.left) 
                continue;     // Reached cliprect yet?

            DrawFixedCell(hDC, row, col, rect,FALSE);
        }
    }
    
    // draw rest of non-fixed cells
    rect.bottom = nFixedRowHeight-1;
    for (row = minVisibleRow; row <= maxVisibleRow; row++)
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + GetRowHeight(row)-1;

        // rect.bottom = bottom pixel of previous row
        if (rect.top > clipRect.bottom) 
            break;                // Gone past cliprect
        if (rect.bottom < clipRect.top) 
            continue;             // Reached cliprect yet?

        rect.right = nFixedColWidth-1;
		if(GetRowHeight(row)>0)
        for (col = minVisibleCol; col <= maxVisibleCol; col++)
        {
            rect.left = rect.right+1;
            rect.right = rect.left + GetColumnWidth(col)-1;

            if (rect.left > clipRect.right)
                break;        // gone past cliprect
            if (rect.right < clipRect.left) 
                continue;     // Reached cliprect yet?

			GetCell(row,col)->DrawCell(hDC,
				m_pImageList,
				rect,
				m_crTextBkColour,
				m_crTextColour,
				m_nMargin,
				FALSE);
            //DrawCell(hDC, row, col, rect,FALSE);
        }
    }


	HPEN pen = CreatePen(PS_SOLID, 0, m_crGridColour);
	if (pen != NULL)
		SelectObject(hDC,(HPEN)pen);

    // draw vertical lines (drawn at ends of cells)
    if (m_nGridLines == GVL_BOTH || m_nGridLines == GVL_VERT) 
    {
        int x = nFixedColWidth;
        for (col = minVisibleCol; col <= maxVisibleCol; col++) {
            x += GetColumnWidth(col);
            MoveToEx(hDC,x-1, nFixedRowHeight,NULL);
            LineTo(hDC,x-1, VisRect.bottom);   
        }
    }
    
    // draw horizontal lines (drawn at bottom of each cell)
    if (m_nGridLines == GVL_BOTH || m_nGridLines == GVL_HORZ) 
    {
        int y = nFixedRowHeight;
        for (row = minVisibleRow; row <= maxVisibleRow; row++) {
            y += GetRowHeight(row);
            MoveToEx(hDC,nFixedColWidth, y-1,NULL);    
            LineTo(hDC,VisRect.right,  y-1);
        }
    }

    SelectObject(hDC,
		GetStockObject(WHITE_PEN));

	//		CreatePen(PS_NULL,0,NULL));
	DeleteObject(pen);
}

////////////////// ERASE BACKGROUND //////////////////
void CGrid::EraseBkgnd(HDC hDC,RECT rc)
{

    RECT  VisRect, ClipRect, rect;

    HBRUSH FixedBack,
           TextBack,
           Back;

	FixedBack = CreateSolidBrush(m_crFixedBkColour);
	TextBack = CreateSolidBrush(m_crTextBkColour);
	Back = CreateSolidBrush(m_crBkColour);

/*    if (GetClipBox(hDC,&ClipRect) == ERROR) 
        return;
*/
	ClipRect = rc;

    GetVisibleNonFixedCellRange(&VisRect);

    // Draw Fixed columns background
    int nFixedColumnWidth = GetFixedColumnWidth();
    
	if (ClipRect.left < nFixedColumnWidth && ClipRect.top < VisRect.bottom)
	{
		RECT recF;
		recF.left =ClipRect.left;
		recF.top = ClipRect.top;
		recF.right = nFixedColumnWidth;
		recF.bottom = VisRect.bottom;

        FillRect(hDC,&recF,FixedBack);
	}
        
    // Draw Fixed rows background
    int nFixedRowHeight = GetFixedRowHeight();
    if (ClipRect.top < nFixedRowHeight && 
        ClipRect.right > nFixedColumnWidth && ClipRect.left < VisRect.right)
	{
        RECT recF;
		recF.left =nFixedColumnWidth-1;
		recF.top = ClipRect.top;
		recF.right = VisRect.right;
		recF.bottom = nFixedRowHeight;
		
		FillRect(hDC,&recF,FixedBack);
	}
    // Draw non-fixed cell background
    if (IntersectRect(&rect,&VisRect, &ClipRect)) 
    {
        RECT CellRect;
		CellRect.left=max(nFixedColumnWidth, rect.left);
		CellRect.top=max(nFixedRowHeight, rect.top);
		CellRect.right=rect.right;
		CellRect.bottom=rect.bottom;

        FillRect(hDC,&CellRect, TextBack);
    }

    // Draw right hand side of window outside grid
    if (VisRect.right < ClipRect.right) 
	{
		RECT recF;
		recF.left =VisRect.right;
		recF.top = ClipRect.top;
		recF.right = ClipRect.right;
		recF.bottom = ClipRect.bottom;

        FillRect(hDC,&recF,Back);
	}

    // Draw bottom of window below grid
    if (VisRect.bottom < ClipRect.bottom && ClipRect.left < VisRect.right) 
	{
		RECT recF;
		recF.left =ClipRect.left;
		recF.top = VisRect.bottom;
		recF.right = VisRect.right;
		recF.bottom = ClipRect.bottom;
        FillRect(hDC,&recF,Back);
	}
	DeleteObject(FixedBack);
	DeleteObject(TextBack);
	DeleteObject(Back);
}

BOOL CGrid::InvalidateCellRect(const CCellID &cell)
{
    if (!::IsWindow(m_hWnd) || !m_bAllowDraw)
        return FALSE;

    ATLASSERT(IsValid(cell));

    if (!IsCellVisible(cell.row, cell.col)) return FALSE;

    RECT rect;
    if (!GetCellRect(cell, &rect)) return FALSE;
    rect.right++; rect.bottom++;
    InvalidateRect(&rect, TRUE);

    return TRUE;

}

BOOL CGrid::InvalidateCellRect(const CCellRange &cellRange)
{
    ATLASSERT(IsValid(cellRange));
    if (!::IsWindow(m_hWnd) || !m_bAllowDraw) return FALSE;

    CCellRange visibleCellRange = GetVisibleNonFixedCellRange(NULL).Intersect(cellRange);

    RECT rect;
    if (!GetCellRangeRect(visibleCellRange, &rect)) return FALSE;

    rect.right++; rect.bottom++;
    InvalidateRect(&rect, TRUE);

    return TRUE;

}

////////////////////////////////////////////////////////////
// End Grid Drawing
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Grid Attributes
////////////////////////////////////////////////////////////

// Creates a new grid cell and performs any necessary initialisation
// Provvisorio deve farlo la cella.
CGridCell* CGrid::CreateCell(int nRow, int nCol)
{
    CGridCell* pCell = new CComObject<CGridCell>;
    if (!pCell)
        return NULL;
    
    pCell->AddRef();
	pCell->SetParent(this);

    // Make format same as cell above
    if (nRow > 0 && nCol >= 0 && nCol < m_nCols)
        pCell->SetFormat(GetCell(nRow-1, nCol)->GetFormat());
 
    // Make font default grid font
    pCell->put_Font(m_pFont);
    
    return pCell;

}

CCellID CGrid::SetFocusCell(int nRow, int nCol)
{
    return SetFocusCell(CCellID(nRow, nCol));
}

CCellID CGrid::SetFocusCell(CCellID cell)
{
    if (cell == m_idCurrentCell) 
        return m_idCurrentCell;

    CCellID idPrev = m_idCurrentCell;
    m_idCurrentCell = cell;

    if (IsValid(idPrev)) 
    {
//        SendMessageToParent(idPrev.row, idPrev.col, GVN_SELCHANGING);
		CGridCell* pCell = GetCell(idPrev.row,idPrev.col);
		if (pCell)
			pCell->SetState(pCell->GetState() & ~GVIS_FOCUSED);

		EnsureVisible(cell);

    if (IsValid(m_idCurrentCell)) //{
        SetItemState(m_idCurrentCell.row, m_idCurrentCell.col, 
                     GetItemState(m_idCurrentCell.row, m_idCurrentCell.col) | GVIS_FOCUSED);
/*        RedrawCell(idPrev,NULL); ???? Serve ???

        if (idPrev.col != m_idCurrentCell.col)
            for (int row = 0; row < m_nFixedRows; row++)
//???                RedrawCell(row, idPrev.col,NULL);
        if (idPrev.row != m_idCurrentCell.row)
            for (int col = 0; col < m_nFixedCols; col++) 
//???                RedrawCell(idPrev.row, col,NULL);
    }

    if (IsValid(m_idCurrentCell)) {
        SetItemState(m_idCurrentCell.row, m_idCurrentCell.col, 
                     GetItemState(m_idCurrentCell.row, m_idCurrentCell.col) | GVIS_FOCUSED);

//???        RedrawCell(m_idCurrentCell,NULL);

        if (idPrev.col != m_idCurrentCell.col)
            for (int row = 0; row < m_nFixedRows; row++) 
                RedrawCell(row, m_idCurrentCell.col,NULL);
        if (idPrev.row != m_idCurrentCell.row)
            for (int col = 0; col < m_nFixedCols; col++) 
                RedrawCell(m_idCurrentCell.row, col,NULL);

//        SendMessageToParent(m_idCurrentCell.row, m_idCurrentCell.col, GVN_SELCHANGED); 
    
*/
	
	}
	FireViewChange();
    return idPrev;

}

void CGrid::ResetScrollBars()
{
	if (!m_bAllowDraw || !::IsWindow(m_hWnd)) 
		return;

	RECT rect;
	GetClientRect(&rect);
	rect.left  += GetFixedColumnWidth();
	rect.top   += GetFixedRowHeight();
	if (rect.left >= rect.right || rect.top >= rect.bottom) return;

	RECT VisibleRect;
		VisibleRect.left =GetFixedColumnWidth();
		VisibleRect.top = GetFixedRowHeight();
		VisibleRect.right = rect.right;
		VisibleRect.bottom = rect.bottom;

	RECT VirtualRect;
		VirtualRect.left =GetFixedColumnWidth();
		VirtualRect.top = GetFixedRowHeight();
		VirtualRect.right = GetVirtualWidth();
		VirtualRect.bottom = GetVirtualHeight();


	CCellRange visibleCells = GetUnobstructedNonFixedCellRange();
	if (!IsValid(visibleCells)) return;

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_PAGE;
	si.nPage  = VisibleRect.right - VisibleRect.left;    SetScrollInfo(SB_HORZ, &si, FALSE); 
	si.nPage  = VisibleRect.bottom - VisibleRect.top;   SetScrollInfo(SB_VERT, &si, FALSE); 

	if ((VisibleRect.bottom - VisibleRect.top) < (VirtualRect.bottom - VirtualRect.top))
		m_nVScrollMax = (VirtualRect.bottom - VirtualRect.top)-1; //+ GetRowHeight(visibleCells.GetTopLeft().row);
	else
		m_nVScrollMax = 0;

	if ((VisibleRect.right - VisibleRect.left) < (VirtualRect.right - VirtualRect.left))
		m_nHScrollMax = VirtualRect.right - VirtualRect.left-1; //+ GetColumnWidth(visibleCells.GetTopLeft().col);
	else
		m_nHScrollMax = 0;

	ATLASSERT(m_nVScrollMax < INT_MAX && m_nHScrollMax < INT_MAX); // This should be fine :)
	SetScrollRange(SB_VERT, 0, m_nVScrollMax, TRUE);
	SetScrollRange(SB_HORZ, 0, m_nHScrollMax, TRUE);

}

SIZE CGrid::GetTextExtent(LPCTSTR str, BOOL bUseSelectedFont /*  = TRUE*/)
{
	HDC pDC = GetDC();

	SIZE size = {0,0};
	if (!pDC) return size;

	HFONT pOldFont, font;

	if (bUseSelectedFont)
	{
		LOGFONT lf;
		memcpy(&lf, &m_Logfont, sizeof(LOGFONT));
		lf.lfWeight = SELECTED_CELL_FONT_WEIGHT;
        
		font = CreateFontIndirect(&lf);

		pOldFont = (HFONT) SelectObject(pDC,font);
	}
	else
		pOldFont = (HFONT) SelectObject(pDC,m_Font);

	::GetTextExtentPoint32(pDC,
			   str, strlen(str), &size);

	SelectObject(pDC,pOldFont);
	ReleaseDC(pDC);
	size.cx += 2*m_nMargin;
	size.cy += 2*m_nMargin;

	return size;

}

////////////////////////////////////////////////////////////////////////////////////
// Row/Column count functions
int CGrid::GetScrollPos32(int nBar, BOOL bGetTrackPos /* = FALSE*/)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);

	if (bGetTrackPos)
	{
		si.fMask = SIF_TRACKPOS;
		if (GetScrollInfo(nBar, &si))
			return si.nTrackPos;
	}
	else 
	{
		si.fMask = SIF_POS;
		if (GetScrollInfo(nBar, &si))
			return si.nPos;
	}

	return 0;

}

SIZE CGrid::GetCellExtent(int nRow, int nCol, HDC hDC)
{
	CGridCell* pCell;
	pCell = GetCell(nRow,nCol);
	LOGFONT cLF;

	if (pCell)
      cLF = *pCell->GetFont();
	else
		cLF = m_Logfont;
    
    // use selected font since it's thicker   
    LOGFONT lf;
    memcpy(&lf, &cLF, sizeof(LOGFONT));
    
    if (nRow < m_nFixedRows || nCol < m_nFixedCols)
        lf.lfWeight = SELECTED_CELL_FONT_WEIGHT;
            
    HFONT font;
    font = CreateFontIndirect(&lf);
    
    HFONT pOldFont = (HFONT) SelectObject(hDC,font);

	SIZE size;
	LPCTSTR lpString;
	SIZE ret;

	lpString = (const char*) pCell->GetText();
	int len = 0;
	if(lpString)
		len = strlen(lpString);
	//VERIFY(
	BOOL bval = ::GetTextExtentPoint32(hDC,
		lpString,
		len,
		&size);
	if(bval == 0)
	{
		ret.cx = 0;
		ret.cy = 0;
		return ret;
	}

    SelectObject(hDC,pOldFont);

    size.cx += 4*m_nMargin;
	size.cy += 2*m_nMargin;

    SIZE ImageSize = {0,0};
    if (m_pImageList) {
        int nImage = pCell->GetImage();
        if (nImage >= 0) {
            IMAGEINFO Info;
            if (ImageList_GetImageInfo(m_pImageList,nImage, &Info))
                ImageSize.cx = Info.rcImage.right-Info.rcImage.left+1;
				ImageSize.cy = Info.rcImage.bottom-Info.rcImage.top+1;
        }
    }
    SIZE sz={0,0};
	if (pCell)
		sz = pCell->GetPictureSize();
		
	ret.cx = size.cx + ImageSize.cx + sz.cx;
	ret.cy = max(size.cy, ImageSize.cy);
	ret.cy = max(ret.cy,sz.cy);

	DeleteObject(font);
    return ret;
}

BOOL CGrid::GetCellRangeRect(const CCellRange &cellRange, LPRECT lpRect)
{
    POINT MinOrigin,MaxOrigin;

    if (!GetCellOrigin(cellRange.GetMinRow(), cellRange.GetMinCol(), &MinOrigin)) 
        return FALSE;
    if (!GetCellOrigin(cellRange.GetMaxRow(), cellRange.GetMaxCol(), &MaxOrigin)) 
        return FALSE;

    lpRect->left   = MinOrigin.x;
    lpRect->top    = MinOrigin.y;
    lpRect->right  = MaxOrigin.x + GetColumnWidth(cellRange.GetMaxCol()-1);
    lpRect->bottom = MaxOrigin.y + GetRowHeight(cellRange.GetMaxRow()-1);

    return TRUE;
}

CCellID CGrid::GetTopleftNonFixedCell()
{
    int nVertScroll = GetScrollPos(SB_VERT), 
		nHorzScroll = GetScrollPos(SB_HORZ);

    int nColumn = m_nFixedCols, nRight = 0;
    while (nRight < nHorzScroll && nColumn < (m_nRows-1))
        nRight += GetColumnWidth(nColumn++);

    int nRow = m_nFixedRows, nTop = 0;
    while (nTop < nVertScroll && nRow < (m_nRows-1))
        nTop += GetRowHeight(nRow++);

    //TRACE("TopLeft cell is row %d, col %d\n",nRow, nColumn);
    return CCellID(nRow, nColumn);

}

// This gets even partially visible cells
CCellRange CGrid::GetVisibleNonFixedCellRange(LPRECT pRect)
{
    RECT rect;
    GetClientRect(&rect);

    CCellID idTopLeft = GetTopleftNonFixedCell();

    // calc bottom
    int bottom = GetFixedRowHeight();
    for (int i = idTopLeft.row; i < m_nRows; i++)
    {
        bottom += GetRowHeight(i);
        if (bottom >= rect.bottom) {
            bottom = rect.bottom;
            break;
        }
    }                                
    int maxVisibleRow = min(i, m_nRows - 1);
    
    // calc right
    int right = GetFixedColumnWidth();
    for (i = idTopLeft.col; i < m_nCols; i++)
    {
        right += GetColumnWidth(i);
        if (right >= rect.right) {
            right = rect.right;
            break;
        }
    }
    int maxVisibleCol = min(i, m_nCols - 1);
    if (pRect) {
        pRect->left = pRect->top = 0;
        pRect->right = right;
        pRect->bottom = bottom;
    }

    return CCellRange(idTopLeft.row, idTopLeft.col, maxVisibleRow, maxVisibleCol);
}

BOOL CGrid::IsCellVisible(CCellID cell)
{
    return IsCellVisible(cell.row, cell.col);

}

BOOL CGrid::IsCellVisible(int nRow, int nCol)
{
    if (!::IsWindow(m_hWnd))
        return FALSE;

    int x,y;

 	int fixedRow;
	int fixedColumn;
	get_FixedRows(&fixedRow);
	get_FixedCols(&fixedColumn);

   CCellID TopLeft;
    if (nCol >= fixedColumn || nRow >= fixedRow)
    {
        TopLeft = GetTopleftNonFixedCell();
        if (nCol >= fixedColumn && nCol < TopLeft.col) return FALSE;
        if (nRow >= fixedRow && nRow < TopLeft.row) return FALSE;
    }

    RECT rect;
    GetClientRect(&rect);
    if (nCol < fixedColumn)
    {
        x = 0;
        for (int i = 0; i <= nCol; i++) 
        {
            if (x >= rect.right) return FALSE;
            x += GetColumnWidth(i);    
        }
    } 
    else 
    {
        x = GetFixedColumnWidth();
        for (int i = TopLeft.col; i <= nCol; i++) 
        {
            if (x >= rect.right) return FALSE;
            x += GetColumnWidth(i);    
        }
    }

    if (nRow < fixedRow)
    {
        y = 0;
        for (int i = 0; i <= nRow; i++) 
        {
            if (y >= rect.bottom) return FALSE;
            y += GetRowHeight(i);    
        }
    } 
    else 
    {
        if (nRow < TopLeft.row) return FALSE;
        y = GetFixedRowHeight();
        for (int i = TopLeft.row; i <= nRow; i++) 
        {
            if (y >= rect.bottom) return FALSE;
            y += GetRowHeight(i);    
        }
    }

    return TRUE;
}

BOOL CGrid::GetCellOrigin(int nRow, int nCol, LPPOINT p)
{
    int i;

    if (!IsValid(nRow, nCol)) return FALSE;

    CCellID idTopLeft;
    if (nCol >= m_nFixedCols || nRow >= m_nFixedRows)
        idTopLeft = GetTopleftNonFixedCell();

    if ((nRow >= m_nFixedRows && nRow < idTopLeft.row) ||
        (nCol>= m_nFixedCols && nCol < idTopLeft.col))
        return FALSE;

    p->x = 0;
    if (nCol < m_nFixedCols)                      // is a fixed column
        for (i = 0; i < nCol; i++)
            p->x += GetColumnWidth(i);
    else {                                        // is a scrollable data column
        for (i = 0; i < m_nFixedCols; i++)
            p->x += GetColumnWidth(i);
        for (i = idTopLeft.col; i < nCol; i++)
            p->x += GetColumnWidth(i);
    }

    p->y = 0;
    if (nRow < m_nFixedRows)                      // is a fixed row
        for (i = 0; i < nRow; i++)
            p->y += GetRowHeight(i);
    else {                                        // is a scrollable data row
        for (i = 0; i < m_nFixedRows; i++)
            p->y += GetRowHeight(i);
        for (i = idTopLeft.row; i < nRow; i++)
            p->y += GetRowHeight(i);
    }

    return TRUE;
}

BOOL CGrid::GetCellOrigin(const CCellID &cell, LPPOINT p)
{
    return GetCellOrigin(cell.row, cell.col, p);
}

BOOL CGrid::GetCellRect(const CCellID &cell, LPRECT pRect)
{
    return GetCellRect(cell.row, cell.col, pRect);

}

BOOL CGrid::GetCellRect(int nRow, int nCol, LPRECT pRect)
{
    POINT CellOrigin;
    if (!GetCellOrigin(nRow, nCol, &CellOrigin)) return FALSE;

    pRect->left   = CellOrigin.x;
    pRect->top    = CellOrigin.y;
    pRect->right  = CellOrigin.x + GetColumnWidth(nCol)-1;
    pRect->bottom = CellOrigin.y + GetRowHeight(nRow)-1;

    //TRACE("Row %d, col %d: L %d, T %d, W %d, H %d:  %d,%d - %d,%d\n",
    //      nRow,nCol, CellOrigin.x, CellOrigin.y, GetColumnWidth(nCol), GetRowHeight(nRow),
    //      pRect->left, pRect->top, pRect->right, pRect->bottom);

    return TRUE;
}

BOOL CGrid::IsCellEditable(CCellID &cell)
{
    return IsCellEditable(cell.row, cell.col); 
}

BOOL CGrid::IsCellEditable(int nRow, int nCol)
{
	VARIANT_BOOL IsEditable;
	CGridCell* pCell = GetCell(nRow,nCol);

	get_Editable(&IsEditable);
	if(pCell)
		return IsEditable && ((pCell->GetState() & GVIS_READONLY) != GVIS_READONLY);
	else
		return IsEditable;
}

// used by ResetScrollBars() - This gets only fully visible cells
CCellRange CGrid::GetUnobstructedNonFixedCellRange()
{
	RECT rect;
	GetClientRect(&rect);

	CCellID idTopLeft = GetTopleftNonFixedCell();

	// calc bottom
	int bottom = GetFixedRowHeight();
	for (int i = idTopLeft.row; i < m_nRows; i++)
	{
		bottom += GetRowHeight(i);
		if (bottom >= rect.bottom) break;
	}
	int maxVisibleRow = min(i, m_nRows - 1);
	if (maxVisibleRow > 0 && bottom > rect.bottom) maxVisibleRow--;

	// calc right
	int right = GetFixedColumnWidth();
	for (i = idTopLeft.col; i < m_nCols; i++)
	{
		right += GetColumnWidth(i);
		if (right >= rect.right) break;
	}
	int maxVisibleCol = min(i, m_nCols - 1);
	if (maxVisibleCol > 0 && right > rect.right) maxVisibleCol--;


	return CCellRange(idTopLeft.row, idTopLeft.col, maxVisibleRow, maxVisibleCol);
}

CCellID CGrid::GetCellFromPt(long x,long y,
					  BOOL bAllowFixedCellCheck /*= TRUE*/)
{
	// Modified to adapt to POINTS e POINT

    CCellID idTopLeft = GetTopleftNonFixedCell();
    CCellID cellID; // return value

    // calculate column index
    int fixedColWidth = GetFixedColumnWidth();

    if (x < 0 || (!bAllowFixedCellCheck && x < fixedColWidth)) // not in window
        cellID.col = -1;
    else if (x < fixedColWidth) // in fixed col
    {
        int xpos = 0;
        for (int col = 0; col < m_nFixedCols; col++)
        {
            xpos += GetColumnWidth(col);
            if (xpos > x) break;
        }
        cellID.col = col;
    }
    else    // in non-fixed col
    {
        int xpos = fixedColWidth;
        for (int col = idTopLeft.col; col < m_nCols; col++)
        {
            xpos += GetColumnWidth(col);
            if (xpos > x) break;
        }

        if (col >= m_nCols)
            cellID.col = -1;
        else
            cellID.col = col;
    }
    
    // calculate row index
    int fixedRowHeight = GetFixedRowHeight();
    if (y < 0 || (!bAllowFixedCellCheck && y < fixedRowHeight)) // not in window
        cellID.row = -1;
    else if (y < fixedRowHeight) // in fixed col
    {
        int ypos = 0;
        for (int row = 0; row < m_nFixedRows; row++)
        {
            ypos += GetRowHeight(row);
            if (ypos > y) break;
        }
        cellID.row = row;
    }
    else
    {
        int ypos = fixedRowHeight;
        for (int row = idTopLeft.row; row < m_nRows; row++)
        {
            ypos += GetRowHeight(row);
            if (ypos > y) break;
        }

        if (row >= m_nRows)
            cellID.row = -1;
        else
            cellID.row = row;
    }

    return cellID;
}
/*
BOOL CGrid::SetFont(LOGFONT lf)
{

    // Store font as the global default
    memcpy(&m_Logfont, &lf, sizeof(LOGFONT));

    // reset all cells' fonts
    for (int row = 0; row < m_nRows; row++)
        for (int col = 0; col < m_nCols; col++)
            GetCell(row, col)->SetFont(lf);

    // Get the font size and hence the default cell size
	if (m_hWnd == NULL)
		return TRUE;
    HDC hDC = GetDC();
    if (hDC) 
    {
		if (m_Font)
			DeleteObject(m_Font);
        m_Font=CreateFontIndirect(&m_Logfont);
        HFONT pOldFont = (HFONT) SelectObject(hDC,m_Font);
        
        TEXTMETRIC tm;
        GetTextMetrics(hDC,&tm);
        
		SIZE size;
		::GetTextExtentPoint32(hDC, _T(" "), 1, &size);

        m_nMargin = size.cx;
        SelectObject(hDC,pOldFont);
        ReleaseDC(hDC);

        m_nDefCellHeight = tm.tmHeight+tm.tmExternalLeading + 2*m_nMargin;
        m_nDefCellWidth  = tm.tmAveCharWidth*12 + 2*m_nMargin;
    }

    if (m_hWnd) 
        FireViewChange();

    return TRUE;

}
*/
int CGrid::NewRow(_bstr_t strHeading, int nRow)
{
    // If the insertion is for a specific row, check it's within range.
    if (nRow >= 0 && nRow >= m_nRows)
        return -1;

//??    ResetSelectedRange();

    // Gotta be able to at least _see_ some of the row.
    if (m_nCols < 1) 
        put_ColumnCount(1);    

    // Adding a row to the bottom
	if (nRow<0)
		nRow = m_nRows;
    m_nRows++;
	
//	m_arRow.resize(m_nRows);
	m_RowData.insert(
		m_RowData.begin()+nRow);

	m_arRow.insert(
		m_arRow.begin()+nRow);

    m_RowData[nRow]= new GRID_ROW;
    
    m_RowData[nRow]->resize(m_nCols);

    // Initialise cell data
    for (int col = 0; col < m_nCols; col++)
    {
        GRID_ROW* pRow = m_RowData[nRow];
        if (!pRow) return -1;
        pRow->at(col) = CreateCell(nRow, col);
    }

    // Set row title
    GetCell(nRow, 0)->put_Text(strHeading);

    // initialized row height
    m_arRow[nRow].Height = GetTextExtent(strHeading).cy;

    if (m_idCurrentCell.row != -1 && nRow < m_idCurrentCell.row)
        m_idCurrentCell.row++;
    
    ResetScrollBars();

    return nRow;
}

long CGrid::GetVirtualWidth()
{
	long lVirtualWidth = 0;
	int iColCount = m_nCols;
	for (int i = 0; i < iColCount; i++)
		lVirtualWidth += m_arCol[i].Width;

	return lVirtualWidth;
}

long CGrid::GetVirtualHeight()
{
	long lVirtualHeight = 0;

	for (int i = 0; i < m_nRows; i++)
		lVirtualHeight += m_arRow[i].Height;

	return lVirtualHeight;
}

int CGrid::GetFixedRowHeight()
{
	int nHeight = 0;
	for (int i = 0; i < m_nFixedRows; i++)
		nHeight += GetRowHeight(i);

	return nHeight;
}

BOOL CGrid::IsValid(int nRow, int nCol)
{
	return (nRow >= 0 && nRow < m_nRows && nCol >= 0 && nCol < m_nCols);
}

BOOL CGrid::IsValid(const CCellID &cell)
{
	return IsValid(cell.row, cell.col);
}

BOOL CGrid::IsValid(const CCellRange &range)
{
	 return (range.GetMinRow() >= 0 && range.GetMinCol() >= 0 && 
			range.GetMaxRow() >= 0 && range.GetMaxCol() >= 0 &&
			range.GetMaxRow() < m_nRows && range.GetMaxCol() < m_nCols &&
			 range.GetMinRow() <= range.GetMaxRow() && range.GetMinCol() <= range.GetMaxCol());
}

BOOL CGrid::SetItemState(int nRow, int nCol, UINT state, BOOL* itInv /*= NULL*/) // Indica se l'iteratore delle celle selezionate viene o meno invalidato
{
	// itInv vale TRUE se cancello l'elemento e quindi invalido
	// l'iteratore 

    CGridCell* pCell = GetCell(nRow, nCol);
    ATLASSERT(pCell);

	if (itInv)
		*itInv = FALSE;
    if (!pCell)
        return FALSE;

    // If the cell is being unselected, remove it from the selected list
    if ((pCell->GetState() & GVIS_SELECTED) && !(state & GVIS_SELECTED))
    {
        CCellID cell;
        DWORD key = MAKELONG(nRow, nCol);

//        if (m_SelectedCellMap.Lookup(key, (CCellID&)cell))
		selMap::iterator it = m_SelectedCellMap.find(key);

        if (it != m_SelectedCellMap.end())
		{
            m_SelectedCellMap.erase(it); //Invalida l'iteratore
			if (itInv)
				*itInv=TRUE;
		}
    }

    // If cell is being selected, add it to the list of selected cells
    else if (!(pCell->GetState() & GVIS_SELECTED) && (state & GVIS_SELECTED))
    {
        CCellID cell(nRow, nCol);
        m_SelectedCellMap.insert(ValuePair(MAKELONG(nRow, nCol), cell));
		if (itInv)
			*itInv=TRUE;
    }

    // Set the cell's state
    pCell->SetState(state);

    return TRUE;
}

int CGrid::GetRowHeight(int nRow)
{
    ATLASSERT(nRow >= 0 && nRow < m_nRows);
    if (nRow < 0 || nRow >= m_nRows)
		return -1;

    return m_arRow[nRow].Height;
}

int CGrid::GetFixedColumnWidth()
{
    int nWidth = 0;
    for (int i = 0; i < m_nFixedCols; i++)
        nWidth += GetColumnWidth(i);

    return nWidth;
}

int CGrid::GetColumnWidth(int nCol)
{
    ATLASSERT(nCol >= 0 && nCol < m_nCols);
    if (nCol < 0 || nCol >= m_nCols) return -1;

    return m_arCol[nCol].Width;

}

CGridCell* CGrid::GetCell(int nRow, int nCol)
{
    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols) return NULL;

    GRID_ROW* pRow = m_RowData[nRow];
    if (!pRow) return NULL;
//    return pRow->GetAt(nCol);
    return pRow->at(nCol);
}
/*
BOOL GetItem(GV_ITEM* pItem)
{
    if (!pItem)
        return FALSE;
    CGridCell* pCell = GetCell(pItem->row, pItem->col);
    if (!pCell) 
        return FALSE;

    if (pItem->mask & GVIF_TEXT)   pItem->szText  = pCell->GetText();
    if (pItem->mask & GVIF_PARAM)  pItem->lParam  = pCell->lParam;
    if (pItem->mask & GVIF_IMAGE)  pItem->iImage  = pCell->iImage;
    if (pItem->mask & GVIF_STATE)  pItem->state   = pCell->state;
    if (pItem->mask & GVIF_FORMAT) pItem->nFormat = pCell->nFormat;
    if (pItem->mask & GVIF_BKCLR)  pItem->crBkClr = pCell->crBkClr;
    if (pItem->mask & GVIF_FGCLR)  pItem->crFgClr = pCell->crFgClr;
    if (pItem->mask & GVIF_FONT)   memcpy(&(pItem->lfFont), &(pCell->lfFont), sizeof(LOGFONT));

    return TRUE;
}
*/

////////////////////////////////////////////////////////////
// End Grid Attributes
////////////////////////////////////////////////////////////

STDMETHODIMP CGrid::get_ColumnResizing(VARIANT_BOOL *pVal)
{
	if (m_bAllowColumnResize == TRUE)
		*pVal = VARIANT_TRUE;
	else
		*pVal = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CGrid::put_ColumnResizing(VARIANT_BOOL newVal)
{
	if (newVal == VARIANT_TRUE)
		m_bAllowColumnResize = TRUE;
	else
		m_bAllowColumnResize = FALSE;

	return S_OK;
}

STDMETHODIMP CGrid::get_RowResizing(VARIANT_BOOL *pVal)
{
	if (m_bAllowRowResize == TRUE)
		*pVal = VARIANT_TRUE;
	else
		*pVal = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CGrid::put_RowResizing(VARIANT_BOOL newVal)
{
	if (newVal == VARIANT_TRUE)
		m_bAllowRowResize = TRUE;
	else
		m_bAllowRowResize = FALSE;

	return S_OK;
}

STDMETHODIMP CGrid::get_GridLines(grGridLines *pVal)
{
	*pVal = m_nGridLines;

	return S_OK;
}

STDMETHODIMP CGrid::put_GridLines(grGridLines newVal)
{
	m_nGridLines = newVal;
	if (m_hWnd)
		FireViewChange();
	return S_OK;
}

STDMETHODIMP CGrid::get_Editable(VARIANT_BOOL *pVal)
{
	if (m_bEditable == TRUE)
		*pVal = VARIANT_TRUE;
	else
		*pVal = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CGrid::put_Editable(VARIANT_BOOL newVal)
{
	if (newVal == VARIANT_TRUE)
		m_bEditable = TRUE;
	else
		m_bEditable = FALSE;

	return S_OK;
}

STDMETHODIMP CGrid::get_FixedRows(int *pVal)
{
	*pVal = m_nFixedRows;
	return S_OK;
}

STDMETHODIMP CGrid::put_FixedRows(int newVal)
{
	if (newVal < 0)
		return S_OK;

	if (newVal > m_nRows) 
		if (!put_RowCount(newVal)) return FALSE;

	if (m_idCurrentCell.row < newVal)
		SetFocusCell(-1,-1);

	m_nFixedRows = newVal;

	if (m_bAllowDraw && m_hWnd)
		FireViewChange();

	return S_OK;
}

STDMETHODIMP CGrid::get_FixedCols(int *pVal)
{
	*pVal = m_nFixedCols;
	return S_OK;
}

STDMETHODIMP CGrid::put_FixedCols(int newVal)
{
    ATLASSERT(newVal >= 0);
    if (newVal > m_nCols)
        if (put_ColumnCount(newVal) != S_OK) return FALSE;

    if (m_idCurrentCell.col < newVal)
        SetFocusCell(-1,-1);

    m_nFixedCols = newVal;

    if (m_bAllowDraw && m_hWnd)
        FireViewChange();

	return S_OK;
}

STDMETHODIMP CGrid::AutosizeColumn(int col)
{
	if (col <0)
	{
		BOOL stopDraw = m_bAllowDraw;
		m_bAllowDraw = FALSE;
		int nNumColumns = m_nCols;
		for (int nCol = 0; nCol < nNumColumns; nCol++)
			AutosizeColumn(nCol);
		
		m_bAllowDraw = stopDraw;

	}
	else
	{
		if ( col >= m_nCols) return FALSE;

		SIZE size;
		HDC hDC = GetDC();
		if (!hDC) return FALSE;

		int nWidth = 0;

		for (int nRow = 0; nRow < m_nRows; nRow++)
		{
			size = GetCellExtent(nRow, col, hDC);
			if (size.cx > nWidth) nWidth = size.cx;
		}

		m_arCol[col].Width = nWidth;

		::ReleaseDC(m_hWnd,hDC);
		ResetScrollBars();
	}

    if (m_bAllowDraw && m_hWnd)
        FireViewChange();

	return S_OK;
}

STDMETHODIMP CGrid::AutosizeRow(int row)
{
	if(row < 0)
	{
		BOOL stopDraw = m_bAllowDraw;
		m_bAllowDraw = FALSE;

		for (int nRow = 0; nRow < m_nRows; nRow++)
			AutosizeRow(nRow);
		m_bAllowDraw = stopDraw;
	}
	else
	{
		if (row >= m_nRows) return FALSE;

		SIZE size;
		HDC hDC = ::GetDC(m_hWnd);
		if (!hDC) return FALSE;

		int nHeight = 0;
		int nNumColumns = m_nCols;
		for (int nCol = 0; nCol < nNumColumns; nCol++)
		{  
			size = GetCellExtent(row, nCol, hDC);
			if (size.cy > nHeight) nHeight = size.cy;
		}  
		m_arRow[row].Height = nHeight;

		::ReleaseDC(m_hWnd,hDC);
		ResetScrollBars();

	}
    if (m_bAllowDraw && m_hWnd)
        FireViewChange();

	return S_OK;
}

STDMETHODIMP CGrid::get_CellEnabled(int row, int col, VARIANT_BOOL *pVal)
{
	*pVal = (GetItemState(row,col) & GVIS_READONLY);

	return S_OK;
}

STDMETHODIMP CGrid::put_CellEnabled(int row, int col, VARIANT_BOOL newVal)
{
    if (newVal == FALSE)
        SetItemState(row,col, GetItemState(row,col) | GVIS_READONLY);
    else
        SetItemState(row,col, GetItemState(row,col) & ~GVIS_READONLY);
	return S_OK;
}

STDMETHODIMP CGrid::get_AllowSelection(VARIANT_BOOL *pVal)
{
	*pVal = m_bEnableSelection;
	return S_OK;
}

STDMETHODIMP CGrid::put_AllowSelection(VARIANT_BOOL newVal)
{
	ResetSelectedRange();
	m_bEnableSelection = newVal;
	ResetSelectedRange();
	return S_OK;
}

STDMETHODIMP CGrid::get_ListMode(VARIANT_BOOL *pVal)
{
	if (m_bListMode)
		*pVal = VARIANT_TRUE;
	else
		*pVal = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CGrid::put_ListMode(VARIANT_BOOL newVal)
{
	if(newVal == VARIANT_TRUE)
		m_bListMode = TRUE;
	else
		m_bListMode = FALSE;


	return S_OK;
}

UINT CGrid::GetItemState(int nRow, int nCol)
{
    CGridCell* pCell = GetCell(nRow, nCol);
    ATLASSERT(pCell);
    if (!pCell)
        return 0;

    return pCell->GetState();
}

STDMETHODIMP CGrid::get_CurrentRow(int *pVal)
{
	*pVal = m_idCurrentCell.row;

	return S_OK;
}

STDMETHODIMP CGrid::put_CurrentRow(int newVal)
{
	SetFocusCell(newVal, m_idCurrentCell.col);

	return S_OK;
}

STDMETHODIMP CGrid::get_CurrentCol(int *pVal)
{
	*pVal = m_idCurrentCell.col;
	return S_OK;
}

STDMETHODIMP CGrid::put_CurrentCol(int newVal)
{
	SetFocusCell(m_idCurrentCell.row,newVal);
	return S_OK;
}

STDMETHODIMP CGrid::DeleteRow(int row)
{

    if ( row < 0 || row >= m_nRows)
        return S_OK;

    GRID_ROW* pRow = m_RowData[row];
    if (!pRow) return S_OK;

    ResetSelectedRange();

    for (int col = 0; col < m_nCols; col++) 
    {
        CGridCell* pCell = pRow->at(col);
        if (pCell) {
            EmptyCell(pCell, row, col);
            delete pCell;
        }
    }
//    delete pRow;
    m_RowData.erase(m_RowData.begin()+row);
    m_arRow.erase(m_arRow.begin()+row);

    m_nRows--;
    if (row < m_nFixedRows) m_nFixedRows--;

    if (row == m_idCurrentCell.row)
        m_idCurrentCell.row = m_idCurrentCell.col = -1;
    else if (row < m_idCurrentCell.row)
        m_idCurrentCell.row--;

    ResetScrollBars();

	FireViewChange();

	return S_OK;
}

STDMETHODIMP CGrid::DeleteColumn(int col)
{
    if (col < 0 || col >= m_nCols)
        return S_OK;

    ResetSelectedRange();

    for (int row = 0; row < m_nRows; row++) 
    {
        GRID_ROW* pRow = m_RowData[row];
        if (!pRow) return FALSE;

        CGridCell* pCell = pRow->at(col);
        if (pCell) {
            EmptyCell(pCell, row, col);
            delete pCell;
        }
        pRow->erase(pRow->begin()+col);
    }
    m_arCol.erase(m_arCol.begin()+col);
    m_nCols--;
    if (col < m_nFixedCols) m_nFixedCols--;

    if (col == m_idCurrentCell.col)
        m_idCurrentCell.row = m_idCurrentCell.col = -1;
    else if (col < m_idCurrentCell.col)
        m_idCurrentCell.col--;

    ResetScrollBars();
	FireViewChange();

	return S_OK;
}

STDMETHODIMP CGrid::get_HeaderSort(VARIANT_BOOL *pVal)
{
	*pVal = m_bSortOnClick;
	return S_OK;
}

STDMETHODIMP CGrid::put_HeaderSort(VARIANT_BOOL newVal)
{
	m_bSortOnClick = newVal;
	return S_OK;
}

STDMETHODIMP CGrid::get_SingleRowSelection(VARIANT_BOOL *pVal)
{
	*pVal = m_bSingleRowSelection;
	return S_OK;
}

STDMETHODIMP CGrid::put_SingleRowSelection(VARIANT_BOOL newVal)
{
	m_bSingleRowSelection = newVal;
	return S_OK;
}
BOOL CGrid::GetSingleRowSelection()
{
	VARIANT_BOOL pVal;
	get_SingleRowSelection(&pVal);
	if(pVal == VARIANT_TRUE)
		return TRUE;
	else
		return FALSE;
}
// Performs any cell cleanup necessary to maintain grid integrity
void CGrid::EmptyCell(CGridCell *pCell, int nRow, int nCol)
{
    // Set the cells state to 0. If the cell is selected, this
    // will remove the cell from the selected list.
    SetItemState(nRow, nCol, 0);

    // Empty strings
//    pCell->szText;
}


STDMETHODIMP CGrid::get_BackColor(OLE_COLOR *pVal)
{
	*pVal = (OLE_COLOR) m_crBkColour;

	return S_OK;
}

STDMETHODIMP CGrid::put_BackColor(OLE_COLOR newVal)
{
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_crBkColour = cr;

	if (m_hWnd)
		FireViewChange();


	return S_OK;
}

STDMETHODIMP CGrid::get_FixedBackColor(OLE_COLOR *pVal)
{
	*pVal = (OLE_COLOR) m_crFixedBkColour;

	return S_OK;
}

STDMETHODIMP CGrid::put_FixedBackColor(OLE_COLOR newVal)
{
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_crFixedBkColour = cr;

	if (m_hWnd)
		FireViewChange();


	return S_OK;
}

STDMETHODIMP CGrid::get_TextColor(OLE_COLOR *pVal)
{
	*pVal = (OLE_COLOR) m_crTextColour;

	return S_OK;
}

STDMETHODIMP CGrid::put_TextColor(OLE_COLOR newVal)
{
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_crTextColour = cr;

	if (m_hWnd)
		FireViewChange();


	return S_OK;
}

STDMETHODIMP CGrid::get_TextBackColor(OLE_COLOR *pVal)
{
	*pVal = m_crTextBkColour;

	return S_OK;
}

STDMETHODIMP CGrid::put_TextBackColor(OLE_COLOR newVal)
{
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_crTextBkColour = cr;

	if (m_hWnd)
		FireViewChange();


	return S_OK;
}

STDMETHODIMP CGrid::get_Color(OLE_COLOR *pVal)
{
	*pVal = (OLE_COLOR) m_crGridColour;

	return S_OK;
}

STDMETHODIMP CGrid::put_Color(OLE_COLOR newVal)
{
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_crGridColour = cr;

	if (m_hWnd)
		FireViewChange();



	return S_OK;
}

STDMETHODIMP CGrid::get_FixedTextColor(OLE_COLOR *pVal)
{
	*pVal = (OLE_COLOR) m_crFixedTextColour;

	return S_OK;
}

STDMETHODIMP CGrid::put_FixedTextColor(OLE_COLOR newVal)
{
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_crFixedTextColour = cr;

	if (m_hWnd)
		FireViewChange();


	return S_OK;
}

STDMETHODIMP CGrid::get_CellFgColor(int Row, int Col, OLE_COLOR *pVal)
{
	CGridCell* pCell = GetCell(Row,Col);
	if (pCell)
		*pVal = (OLE_COLOR) pCell->GetCRFgClr();
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CGrid::put_CellFgColor(int Row, int Col, OLE_COLOR newVal)
{
	CGridCell* pCell = GetCell(Row,Col);
	if (pCell)
	{
		COLORREF cr;
		int i = OleTranslateColor(newVal,
					NULL,
					&cr);
		if ( i == S_OK)
			pCell->SetFgColour(cr);

		if (m_hWnd)
			FireViewChange();

	}

	return S_OK;
}

STDMETHODIMP CGrid::get_CellBgColor(int Row, int Col, OLE_COLOR *pVal)
{
	CGridCell* pCell = GetCell(Row,Col);
	if (pCell)
		*pVal = (OLE_COLOR) pCell->GetCRBkClr();
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CGrid::put_CellBgColor(int Row, int Col, OLE_COLOR newVal)
{
	CGridCell* pCell = GetCell(Row,Col);
	if (pCell)
	{
		COLORREF cr;
		int i = OleTranslateColor(newVal,
					NULL,
					&cr);
		if ( i == S_OK)
			pCell->SetBkColour(cr);

		if (m_hWnd)
			FireViewChange();

	}

	return S_OK;
}

void CGrid::SetFont(IFontDisp *font)
{
	CComQIPtr<IFont> pFont(font);
	if (pFont)
	{
		HFONT hf;
		LOGFONT lf;
		memset(&lf,0,sizeof(LOGFONT));
		HRESULT hr = pFont->get_hFont(&hf);
		if SUCCEEDED(hr)
		{
			pFont->AddRefHfont(hf);
			int bytes;
			DWORD err;
			if(hf)
				bytes = GetObject(hf, sizeof(LOGFONT), &lf);
			if(bytes == 0)
			{
				err = GetLastError();
			}

		// Store font as the global default
		memcpy(&m_Logfont, &lf, sizeof(LOGFONT));

  
		// reset all cells' fonts
		for (int row = 0; row < m_nRows; row++)
			for (int col = 0; col < m_nCols; col++)
				GetCell(row, col)->put_Font(font);

		// Get the font size and hence the default cell size
		if (m_hWnd == NULL)
			return;
		HDC hDC = GetDC();
		if (hDC) 
		{
			if (m_Font)
				DeleteObject(m_Font);
			m_Font=CreateFontIndirect(&m_Logfont);
			HFONT pOldFont = (HFONT) SelectObject(hDC,m_Font);
        
			TEXTMETRIC tm;
			GetTextMetrics(hDC,&tm);
        
			SIZE size;
			::GetTextExtentPoint32(hDC, _T(" "), 1, &size);

			m_nMargin = size.cx;
			SelectObject(hDC,pOldFont);
			ReleaseDC(hDC);

			m_nDefCellHeight = tm.tmHeight+tm.tmExternalLeading + 2*m_nMargin;
			m_nDefCellWidth  = tm.tmAveCharWidth*12 + 2*m_nMargin;
		}

		if (m_hWnd) 
			FireViewChange();

			pFont->ReleaseHfont(hf);
		}
	}
	return ;

}

STDMETHODIMP CGrid::SimpleConf()
{
		//// Semplice codice di inizializzazione della grid per TEST

				// Gestione del Font
		LOGFONT lf;                        // Used to create the CFont.

	   memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.

	   lf.lfHeight = 14;
	   lf.lfWidth = 0;
	   lf.lfEscapement = 0;
	   lf.lfOrientation = 0;
	   lf.lfWeight = FW_NORMAL;
	   lf.lfItalic = FALSE;
	   lf.lfUnderline = FALSE;
	   lf.lfStrikeOut = FALSE;
	   lf.lfCharSet = ANSI_CHARSET;
	   lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	   lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	   lf.lfQuality = DEFAULT_QUALITY;
	   lf.lfPitchAndFamily = FF_DONTCARE;
	   strcpy(lf.lfFaceName, "MS Sans Serif");
   
//		SetFont(lf); // Provvisorio deve diventare una property

//		static CImageList list1;
//		list1.Create(MAKEINTRESOURCE(IDB_IMAGES), 16, 1, RGB(255,255,255));
//		SetImageList(list1.m_hImageList);

		put_FixedRows(1);
		put_FixedCols(1);

		put_RowCount(10);
		put_ColumnCount(10);
		put_TextBackColor(RGB(0xFF, 0xFF, 0xE0));
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
		#ifndef _WIN32_WCE
			dwTextStyle |= DT_END_ELLIPSIS;
		#endif
	// fill rows/cols with text
	char buffer[200] = "\0";
	_bstr_t tmp;
	
	CGridCell* pCell;

	for (int row = 0; row < 10; row++)
		for (int col = 0; col < m_nCols; col++)
		{ 
			pCell = GetCell(row,col);
			if(pCell)
			{
//			Item.mask = GVIF_TEXT|GVIF_FORMAT;
				if (row < 1)
				{
					pCell->SetFormat(DT_LEFT|DT_WORDBREAK);
					sprintf(buffer,"Column %d",col);
					tmp = buffer;
					pCell->put_Text(tmp);
				}
				else if (col < 1) 
				{
					sprintf(buffer,"Row %d",row);
					pCell->SetFormat(dwTextStyle);
					tmp = buffer;
					pCell->put_Text(tmp);
				}
				else 
				{
					sprintf(buffer,"%d",row*col);
					pCell->SetFormat(dwTextStyle);
					tmp = buffer;
					pCell->put_Text(tmp);
				}

				int fixedColumn;
				get_FixedCols(&fixedColumn);
				if (col == (fixedColumn-1) )//&& row >= m_Grid.GetFixedRowCount())
					GetCell(row, col)->SetImage(
					rand()%ImageList_GetImageCount(m_pImageList));	

				//else if (rand() % 10 == 1)
				//	m_Grid.SetItemImage(row, col, 0);

				if (rand() % 10 == 1)
				{
					COLORREF clr = RGB(rand() % 128+128, rand() % 128+128, rand() % 128+128);
					pCell->SetBkColour(clr);
					pCell->SetFgColour(RGB(255,0,0));
				}
			}
		}
	AutoSize();

	int height;
	get_RowHeight(0,&height);
	put_RowHeight(0, 3*height/2);

	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////
// IOleControl method overrides

STDMETHODIMP CGrid::GetMiscStatus (DWORD dwAspect, DWORD *pdwStatus)
{
    if (NULL == pdwStatus) return E_POINTER;

    *pdwStatus = 
           OLEMISC_SETCLIENTSITEFIRST |
           OLEMISC_ACTIVATEWHENVISIBLE |
           OLEMISC_INSIDEOUT |
           OLEMISC_CANTLINKINSIDE |
           OLEMISC_RECOMPOSEONRESIZE;/* |
           OLEMISC_NOUIACTIVATE ;*/

    return S_OK;
}

STDMETHODIMP CGrid::get_Cell(int Row, int Col, IGridCell **pVal)
{
	
	CGridCell* pCell = GetCell(Row,Col);
	
	if(pCell)
		pCell->AddRef();
	*pVal = pCell;

	return S_OK;
}

STDMETHODIMP CGrid::put_Cell(int Row, int Col, IGridCell *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
BOOL CGrid::GetTextRect(int nRow, int nCol, LPRECT pRect)
{
/* TODO: i've to get image information
    GV_ITEM Item;
    Item.mask = GVIF_IMAGE;
    Item.row = nRow;
    Item.col = nCol;
    if (!GetItem(&Item))
        return FALSE;
*/
    if (!GetCellRect(nRow, nCol, pRect))
        return FALSE;

    //pRect->left += m_nMargin;
    //pRect->right -= m_nMargin;
/*
    if (m_pImageList && Item.iImage >= 0) {
        IMAGEINFO Info;
        if (m_pImageList->GetImageInfo(Item.iImage, &Info)) {
            int nImageWidth = Info.rcImage.right-Info.rcImage.left+1;
            pRect->left += nImageWidth+m_nMargin;
        }
    }
*/
    return TRUE;
}
// Get cell from point
CCellID CGrid::GetCellFromPt(POINT point, BOOL bAllowFixedCellCheck /*=TRUE*/)
{  
    CCellID idTopLeft = GetTopleftNonFixedCell();
    CCellID cellID; // return value

    // calculate column index
    int fixedColWidth = GetFixedColumnWidth();

    if (point.x < 0 || (!bAllowFixedCellCheck && point.x < fixedColWidth)) // not in window
        cellID.col = -1;
    else if (point.x < fixedColWidth) // in fixed col
    {
        int xpos = 0;
        for (int col = 0; col < m_nFixedCols; col++)
        {
            xpos += GetColumnWidth(col);
            if (xpos > point.x) break;
        }
        cellID.col = col;
    }
    else    // in non-fixed col
    {
        int xpos = fixedColWidth;
        for (int col = idTopLeft.col; col < m_nCols; col++)
        {
            xpos += GetColumnWidth(col);
            if (xpos > point.x) break;
        }

        if (col >= m_nCols)
            cellID.col = -1;
        else
            cellID.col = col;
    }
    
    // calculate row index
    int fixedRowHeight = GetFixedRowHeight();
    if (point.y < 0 || (!bAllowFixedCellCheck && point.y < fixedRowHeight)) // not in window
        cellID.row = -1;
    else if (point.y < fixedRowHeight) // in fixed col
    {
        int ypos = 0;
        for (int row = 0; row < m_nFixedRows; row++)
        {
            ypos += GetRowHeight(row);
            if (ypos > point.y) break;
        }
        cellID.row = row;
    }
    else
    {
        int ypos = fixedRowHeight;
        for (int row = idTopLeft.row; row < m_nRows; row++)
        {
            ypos += GetRowHeight(row);
            if (ypos > point.y) break;
        }

        if (row >= m_nRows)
            cellID.row = -1;
        else
            cellID.row = row;
    }

    return cellID;
}

STDMETHODIMP CGrid::get_ToolTip(VARIANT_BOOL *pVal)
{
	if(m_bTitleTips ==TRUE)
		*pVal = VARIANT_TRUE;
	else
		*pVal = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CGrid::put_ToolTip(VARIANT_BOOL newVal)
{
	if(newVal == VARIANT_TRUE)
		m_bTitleTips = TRUE;
	else
		m_bTitleTips = FALSE;
	return S_OK;
}

STDMETHODIMP CGrid::Refresh()
{

	FireViewChange();
	return S_OK;
}

STDMETHODIMP CGrid::SelectAllCells()
{
// selects all cells
	if (!m_bEnableSelection)
		return S_OK;

	SetSelectedRange(m_nFixedRows, m_nFixedCols, m_nRows-1, m_nCols-1);


	return S_OK;
}

BOOL CGrid::PreTranslateAccelerator(LPMSG pMsg, HRESULT &hRet)
{
	 BOOL bHandled;
      if(pMsg->message == WM_KEYDOWN && pMsg->hwnd == m_hWnd &&
         (pMsg->wParam == VK_LEFT || 
         pMsg->wParam == VK_RIGHT ||
         pMsg->wParam == VK_UP ||
         pMsg->wParam == VK_DOWN))
      {
         hRet = S_OK; 
		 OnKeyDown(pMsg->message,pMsg->wParam,pMsg->lParam,bHandled);
//         m_ctlEdit.SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
         return TRUE;
      }
      //TODO: Add your additional accelerator handling code here
      if(pMsg->message == WM_KEYDOWN && 
         ((pMsg->wParam == VK_ESCAPE) || (pMsg->wParam == VK_UP) ||
         (pMsg->wParam == VK_DOWN) ))
	  {
		  hRet = S_OK; // Stop an eventual in place action
		  ::PostMessage(pMsg->hwnd,WM_KILLFOCUS,0,0);
		  return TRUE;
	  }
      if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
	  {
		  // special case: use TAB
		  if(pMsg->hwnd == m_hWnd) // The grid has the focus, so delegate to OnKeyDown
		  {
			if (m_vbKeepTab == VARIANT_FALSE)
				 return FALSE;

			OnKeyDown(pMsg->message,pMsg->wParam,pMsg->lParam,bHandled);
			 return TRUE;
		  }
		  else
		  {
//		  SendMessage(pMsg->hwnd,WM_KILLFOCUS,0,0);
			// Move to next cell
			int row = m_idCurrentCell.row,col=m_idCurrentCell.col+1;
			if(col>=m_nCols)
			{
				col = m_nFixedCols;
				row +=1;
				if (row>=m_nRows)
					row = m_nFixedRows;
			}
/*			VARIANT_BOOL cancel = VARIANT_FALSE;

			Fire_BeforeEdit(row,col,&cancel);
			if (cancel == VARIANT_TRUE) // Cancel Editing
				return FALSE;*/
			// Editing the cell
			RECT rect;
			CCellID cellID(row,col);
			SetFocusCell(cellID);
			GetCellRect(cellID,&rect);
			GetCell(row,col)->Edit(m_hWnd,&rect,row,col);
			return TRUE;
		  }
	  }
      return FALSE;

}

STDMETHODIMP CGrid::get_KeepTab(VARIANT_BOOL *pVal)
{
	*pVal = m_vbKeepTab;

	return S_OK;
}

STDMETHODIMP CGrid::put_KeepTab(VARIANT_BOOL newVal)
{
	m_vbKeepTab = newVal;

	return S_OK;
}
