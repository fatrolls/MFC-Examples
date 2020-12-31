#if !defined(AFX_GRIDCTRL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_GRIDCTRL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// GridCtrl.h : header file
//
// MFC Grid Control header file
//
// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
// Copyright (c) 1998.
//
// The code contained in this file is based on the original
// WorldCom Grid control written by Joe Willcoxson,
//        E-mail:  chinajoe@aol.com
//        URL:  http://users.aol.com/chinajoe
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. If the source code in this file is used in 
// any  commercial application then a statement along the lines of 
// "Portions copyright (c) Chris Maunder, 1998" must be included in 
// the startup banner, "About" box or printed documentation. An email 
// letting me know that you are using it would be nice as well. That's 
// not much to ask considering the amount of work that went into this.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Expect bugs!
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
/////////////////////////////////////////////////////////////////////////////

#include "CellRange.h"
#include "GridDropTarget.h"
#include <afxtempl.h>


// Use this as the classname when inserting this control as a custom control
// in the MSVC++ dialog editor
#define GRIDCTRL_CLASSNAME _T("MFCGridCtrl")

#define IsSHIFTpressed() ( (GetKeyState(VK_SHIFT) & (1 << (sizeof(SHORT)*8-1))) != 0   )
#define IsCTRLpressed()  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 )

// Used for Get/SetItem calls.
typedef struct _GV_ITEM { 
    int      row,col;     // Row and Column of item
    UINT     mask;        // Mask for use in getting/setting cell data
    UINT     state;       // cell state (focus/hilighted etc)
    UINT     nFormat;     // Format of cell
    CString  szText;      // Text in cell
    int      iImage;      // index of the list view item’s icon
    COLORREF crBkClr;     // Background colour (or CLR_DEFAULT)
    COLORREF crFgClr;     // Forground colour (or CLR_DEFAULT)
    LPARAM   lParam;      // 32-bit value to associate with item 
} GV_ITEM; 

// Grid line selection
#define GVL_NONE                0
#define GVL_HORZ                1
#define GVL_VERT                2
#define GVL_BOTH                3

// Cell data mask
#define GVIF_TEXT               LVIF_TEXT
#define GVIF_IMAGE              LVIF_IMAGE
#define GVIF_PARAM              LVIF_PARAM
#define GVIF_STATE              LVIF_STATE
#define GVIF_BKCLR              (GVIF_STATE<<1)
#define GVIF_FGCLR              (GVIF_STATE<<2)
#define GVIF_FORMAT             (GVIF_STATE<<3)

// Cell states
#define GVIS_FOCUSED            0x0001
#define GVIS_SELECTED           0x0002
#define GVIS_DROPHILITED        0x0004
#define GVIS_READONLY           0x0008

// Cell Searching options
#define GVNI_FOCUSED            0x0001
#define GVNI_SELECTED           0x0002
#define GVNI_DROPHILITED        0x0004
#define GVNI_READONLY           0x0008

#define GVNI_ABOVE              LVNI_ABOVE
#define GVNI_BELOW              LVNI_BELOW
#define GVNI_TOLEFT             LVNI_TOLEFT
#define GVNI_TORIGHT            LVNI_TORIGHT

// Hit test values (not yet implemented)
#define GVHT_DATA               0x0000
#define GVHT_TOPLEFT            0x0001
#define GVHT_COLHDR             0x0002
#define GVHT_ROWHDR             0x0004
#define GVHT_COLSIZER           0x0008
#define GVHT_ROWSIZER           0x0010
#define GVHT_LEFT               0x0020
#define GVHT_RIGHT              0x0040
#define GVHT_ABOVE              0x0080
#define GVHT_BELOW              0x0100

typedef struct tagNM_GRIDVIEW { 
    NMHDR hdr; 
    int   iRow; 
    int   iColumn; 
} NM_GRIDVIEW;

typedef struct tagGV_DISPINFO { 
    NMHDR   hdr; 
    GV_ITEM item; 
} GV_DISPINFO;

// Messages sent to the grid's parent (More will be added in future)
#define	GVN_BEGINDRAG           LVN_BEGINDRAG
#define	GVN_BEGINLABELEDIT      LVN_BEGINLABELEDIT
//#define	GVN_BEGINRDRAG          LVN_BEGINRDRAG
//#define GVN_COLUMNCLICK         LVN_COLUMNCLICK
//#define	GVN_DELETEITEM          LVN_DELETEITEM
#define GVN_ENDLABELEDIT        LVN_ENDLABELEDIT
//#define GVN_SELCHANGING         LVN_SELCHANGING
//#define GVN_SELCHANGED          LVN_SELCHANGED



// Each cell contains one of these. Fields "row" and "column" are not stored since we
// will usually have acces to them in other ways, and they are an extra 8 bytes per
// cell that is probably unnecessary.

class CGridCell : public CObject
{
public:
    CGridCell():
        state(0), nFormat(0), szText(), iImage(-1), lParam(0),
		crBkClr(CLR_DEFAULT), crFgClr(CLR_DEFAULT) {};

    UINT     state;       // Cell state (selected/focus etc)
    UINT     nFormat;     // Cell format
    CString  szText;      // Cell text (or binary data if you wish...)
    int      iImage;      // Index of the list view item’s icon 
    COLORREF crBkClr;     // Background colour (or CLR_DEFAULT)
    COLORREF crFgClr;     // Forground colour (or CLR_DEFAULT)
    LPARAM   lParam;      // 32-bit value to associate with item
}; 


// storage typedef for each row in the grid
typedef CTypedPtrArray<CObArray, CGridCell*> GRID_ROW;

// DDX_GridControl is used where a DDX_Control call is needed. In some strange
// situations the usual DDX_Control does not result in CGridCtrl::SubclassWindow
// or CGridCtrl::PreSubclassWindow being called. Using this version calls 
// CGridCtrl::SubclassWindow directly - ensuring that cell metrics are set properly
class CGridCtrl;
void AFXAPI DDX_GridControl(CDataExchange* pDX, int nIDC, CGridCtrl& rControl);

/////////////////////////////////////////////////////////////////////////////
// CGridCtrl window

class CGridCtrl : public CWnd
{
// Construction
public:
    CGridCtrl(int nRows = 0, int nCols = 0, int nFixedRows = 0, int nFixedCols = 0);
    DECLARE_DYNCREATE(CGridCtrl)

    BOOL Create(const RECT& rect, CWnd* parent, UINT nID,
                DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE);
    BOOL SubclassWindow(HWND hWnd);

// Attributes
public:
    int  GetRowCount() const                    { return m_nRows; }
    int  GetColumnCount() const                 { return m_nCols; }
    int  GetFixedRowCount() const               { return m_nFixedRows; }
    int  GetFixedColumnCount() const            { return m_nFixedCols; }
    BOOL SetRowCount(int nRows = 10);
    BOOL SetColumnCount(int nCols = 10);
    BOOL SetFixedRowCount(int nFixedRows = 1);
    BOOL SetFixedColumnCount(int nFixedCols = 1);

    int  GetRowHeight(int nRow) const;
    BOOL SetRowHeight(int row, int height);
    int  GetColumnWidth(int nCol) const;
    BOOL SetColumnWidth(int col, int width);

    BOOL GetCellOrigin(int nRow, int nCol, LPPOINT p) const;
    BOOL GetCellOrigin(const CCellID& cell, LPPOINT p) const;
    BOOL GetCellRect(int nRow, int nCol, LPRECT pRect) const;
    BOOL GetCellRect(const CCellID& cell, LPRECT pRect) const;

    int  GetFixedRowHeight() const;
    int  GetFixedColumnWidth() const;
    long GetVirtualWidth() const;
    long GetVirtualHeight() const;

    void   SetTextColor(COLORREF clr)             { m_crTextColour = clr;             }
    COLORREF GetTextColor() const                 { return m_crTextColour;            }
    void   SetTextBkColor(COLORREF clr)           { m_crTextBkColour = clr;           }
    COLORREF GetTextBkColor() const               { return m_crTextBkColour;          }
    void   SetBkColor(COLORREF clr)               { m_crBkColour = clr;               }
    COLORREF GetBkColor() const                   { return m_crBkColour;              }
    void   SetFixedTextColor(COLORREF clr)        { m_crFixedTextColour = clr;        }
    COLORREF GetFixedTextColor() const            { return m_crFixedTextColour;       }
    void SetFixedBkColor(COLORREF clr)            { m_crFixedBkColour = clr;          }
    COLORREF GetFixedBkColor() const              { return m_crFixedBkColour;         } 

    int GetSelectedCount() const                  { return m_SelectedCellMap.GetCount(); }

    CCellID GetFocusCell() const                  { return m_idCurrentCell;           }

    void SetImageList(CImageList* pList)          { m_pImageList = pList;             }
    CImageList* GetImageList() const              { return m_pImageList;              }

    void SetGridLines(int nWhichLines = GVL_BOTH) { m_nGridLines = nWhichLines; 
                                                    if (::IsWindow(GetSafeHwnd())) Invalidate(); }
    int  GetGridLines() const                     { return m_nGridLines;              }

    void SetEditable(BOOL bEditable = TRUE)       { m_bEditable = bEditable;          }
    BOOL IsEditable() const                       { return m_bEditable;               }
    void SetModified(BOOL bModified = TRUE)       { m_bModified = bModified;          }
    BOOL GetModified() const                      { return m_bModified;               }
    void SetListMode(BOOL bEnableListMode = TRUE) { m_bListMode = bEnableListMode;    }
    BOOL GetListMode() const                      { return m_bListMode;               }
    void EnableSelection(BOOL bEnable = TRUE)     { ResetSelectedRange(); m_bEnableSelection = bEnable; ResetSelectedRange(); }
    BOOL IsSelectable() const                     { return m_bEnableSelection;        }
    void EnableDragAndDrop(BOOL bAllow = TRUE)    { m_bAllowDragAndDrop = bAllow;     }
    BOOL GetDragAndDrop() const                   { return m_bAllowDragAndDrop;       }
    void SetRowResize(BOOL bResize = TRUE)        { m_bAllowRowResize = bResize;      }
    BOOL GetRowResize() const                     { return m_bAllowRowResize;         }
    void SetColumnResize(BOOL bResize = TRUE)     { m_bAllowColumnResize = bResize;   }
    BOOL GetColumnResize() const                  { return m_bAllowColumnResize;      }
    void SetHeaderSort(BOOL bSortOnClick = TRUE)  { m_bSortOnClick = bSortOnClick;    }
    BOOL GetHeaderSort() const                    { return m_bSortOnClick;            }
    void SetHandleTabKey(BOOL bHandleTab = TRUE)  { m_bHandleTabKey = bHandleTab;     }
    BOOL GetHandleTabKey() const                  { return m_bHandleTabKey;           }
    void SetDoubleBuffering(BOOL bBuffer = TRUE)  { m_bDoubleBuffer = bBuffer;        }
    BOOL GetDoubleBuffering() const               { return m_bDoubleBuffer;           }

    BOOL SetItem(const GV_ITEM* pItem);
    BOOL GetItem(GV_ITEM* pItem);
    BOOL SetItemText(int nRow, int nCol, LPCTSTR str);
    virtual CString GetItemText(int nRow, int nCol);
    BOOL   SetItemData(int nRow, int nCol, LPARAM lParam);
    LPARAM GetItemData(int nRow, int nCol) const;
    BOOL   SetItemImage(int nRow, int nCol, int iImage);
    int    GetItemImage(int nRow, int nCol) const;
    BOOL   SetItemState(int nRow, int nCol, UINT state);
    UINT   GetItemState(int nRow, int nCol) const;
    BOOL   SetItemFormat(int nRow, int nCol, UINT nFormat);
    UINT   GetItemFormat(int nRow, int nCol) const;
	BOOL   SetItemBkColour(int nRow, int nCol, COLORREF cr = CLR_DEFAULT);
	COLORREF GetItemBkColour(int nRow, int nCol) const;
	BOOL   SetItemFgColour(int nRow, int nCol, COLORREF cr = CLR_DEFAULT);
	COLORREF GetItemFgColour(int nRow, int nCol) const;

// Operations
public:
    int  InsertColumn(LPCTSTR strHeading, UINT nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE,
                      int nColumn = -1);
    int  InsertRow(LPCTSTR strHeading, int nRow = -1);
    BOOL DeleteColumn(int nColumn);
    BOOL DeleteRow(int nRow);
    void DeleteAllItems();

    BOOL AutoSizeRow(int nRow);
    BOOL AutoSizeColumn(int nCol);
    void AutoSizeRows();
    void AutoSizeColumns();
    void AutoSize();
    void ExpandColumnsToFit();
    void ExpandRowsToFit();
    void ExpandToFit();

    CSize GetTextExtent(LPCTSTR str, BOOL bUseSelectedFont = TRUE);

    // SetRedraw stops/starts redraws on things like changing the # rows/columns
    // and autosizing, but not for user-intervention such as resizes
    void SetRedraw(BOOL bAllowDraw, BOOL bResetScrollBars = FALSE);
    BOOL RedrawCell(int nRow, int nCol, CDC* pDC = NULL);
    BOOL RedrawCell(const CCellID& cell, CDC* pDC = NULL);
    BOOL RedrawRow(int row);
    BOOL RedrawColumn(int col);

    void Print(); 

    CCellRange GetCellRange() const;
    CCellRange GetSelectedCellRange() const;
    void SetSelectedRange(const CCellRange& Range, BOOL bForceRepaint = FALSE);
    void SetSelectedRange(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol,
                          BOOL bForceRepaint = FALSE);
    BOOL IsValid(int nRow, int nCol) const;
    BOOL IsValid(const CCellID& cell) const;
    BOOL IsValid(const CCellRange& range) const;

    // Clipboard and cut n' paste operations
    virtual void CutSelectedText();
    virtual COleDataSource* CopyTextFromGrid();
    virtual BOOL PasteTextToGrid(CCellID cell, COleDataObject* pDataObject);

    void OnBeginDrag();
    DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    void OnDragLeave();
    BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);

    virtual void OnEditCut();
    virtual void OnEditCopy();
    virtual void OnEditPaste();
    virtual void OnEditSelectAll() { SetSelectedRange(GetFixedRowCount(), GetFixedColumnCount(), 
                                                      GetRowCount()-1, GetColumnCount()-1, TRUE); }

    CCellID GetNextItem(CCellID& cell, int nFlags) const;

    BOOL SortTextItems(int nCol, BOOL bAscending);
    BOOL SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data = 0);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGridCtrl)
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL
    public:
    virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnPrint(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

// Implementation
public:
    virtual ~CGridCtrl();

protected:
    BOOL RegisterWindowClass();

    BOOL IsCellVisible(int nRow, int nCol) const;
    BOOL IsCellVisible(CCellID cell) const;

    BOOL InvalidateCellRect(const CCellID& cell);
    BOOL InvalidateCellRect(const CCellRange& cellRange);
    void EraseBkgnd(CDC* pDC);

    BOOL GetCellRangeRect(const CCellRange& cellRange, LPRECT lpRect) const;

    CGridCell* GetCell(int nRow, int nCol) const;
    BOOL SetCell(int nRow, int nCol, CGridCell* pCell);

    int  SetMouseMode(int nMode) { int nOldMode = m_MouseMode; m_MouseMode = nMode; return nOldMode; }
    int  GetMouseMode() const    { return m_MouseMode; }

    CCellID GetCellFromPt(CPoint point, BOOL bAllowFixedCellCheck = TRUE) const;
    CCellID GetTopleftNonFixedCell() const;
    CCellRange GetUnobstructedNonFixedCellRange() const;
    CCellRange GetVisibleNonFixedCellRange(LPRECT pRect = NULL) const;

    CCellID SetFocusCell(CCellID cell);
    CCellID SetFocusCell(int nRow, int nCol);

    void ResetSelectedRange();
    void ResetScrollBars();
    int  GetScrollPos32(int nBar, BOOL bGetTrackPos = FALSE);
    BOOL SetScrollPos32(int nBar, int nPos, BOOL bRedraw = TRUE);

    BOOL SortTextItems(int nCol, BOOL bAscending, int low, int high);
    BOOL SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data, 
                   int low, int high);

// Overrrides
protected:
    // Printing    
    virtual void PrintColumnHeadings(CDC *pDC, CPrintInfo *pInfo);
    virtual void PrintHeader(CDC *pDC, CPrintInfo *pInfo);
    virtual void PrintFooter(CDC *pDC, CPrintInfo *pInfo);

    // Drag n' drop
    virtual CImageList* CreateDragImage(CPoint *pHotSpot);    // no longer necessary

    // Mouse Clicks
    virtual void  OnFixedColumnClick(CCellID& cell);
    virtual void  OnFixedRowClick(CCellID& cell);

    // Editing
    virtual CSize GetCellExtent(int nRow, int nCol, CDC* pDC);
    virtual void  OnEndEditCell(int nRow, int nCol, CString str);
    virtual void  OnEditCell(int nRow, int nCol, UINT nChar);

    // Drawing
    virtual void  OnDraw(CDC* pDC);
    virtual BOOL  DrawFixedCell(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBk=FALSE);
    virtual BOOL  DrawCell(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBk=FALSE);

    // Cleanup
    virtual void EmptyCell(CGridCell* pCell, int nRow, int nCol);

// Attributes
protected:
    // General attributes
    COLORREF    m_crTextColour, m_crTextBkColour, m_crBkColour,   // Grid colours
                m_crFixedTextColour, m_crFixedBkColour;
    COLORREF    m_crWindowText, m_crWindowColour, m_cr3DFace,     // System colours
                m_crShadow;    

    int         m_nGridLines;
    BOOL        m_bEditable;
    BOOL        m_bModified;
    BOOL        m_bAllowDragAndDrop;
    BOOL        m_bListMode;
    BOOL        m_bAllowDraw;
    BOOL        m_bEnableSelection;
    BOOL        m_bSortOnClick;
    BOOL        m_bHandleTabKey;
    BOOL        m_bDoubleBuffer;

    // Cell size details
    int         m_nRows, m_nFixedRows, m_nCols, m_nFixedCols;
    CUIntArray  m_arRowHeights, m_arColWidths;
    int         m_nMargin;
    int         m_nDefCellWidth, m_nDefCellHeight;
    int         m_nVScrollMax, m_nHScrollMax;

    // Fonts and images
    CFont       m_Font, m_SelectFont, m_PrinterFont;
    CImageList* m_pImageList;

    // Cell data
    CTypedPtrArray<CObArray, GRID_ROW*> m_RowData;

    // Mouse operations such as cell selection
    int         m_MouseMode;
    CPoint      m_LeftClickDownPoint, m_LastMousePoint;
    CCellID     m_LeftClickDownCell, m_SelectionStartCell;
    CCellID     m_idCurrentCell;
    int         m_nTimerID;
    int         m_nTimerInterval;
    int         m_nResizeCaptureRange;
    BOOL        m_bAllowRowResize, m_bAllowColumnResize;
    int         m_nRowsPerWheelNotch;
    CMap<DWORD,DWORD, CCellID, CCellID&> m_SelectedCellMap, m_PrevSelectedCellMap;

    // Drag and drop
	BOOL		m_bMustUninitOLE;		// Do we need to uninitialise OLE?
    CCellID     m_LastDragOverCell;
    CGridDropTarget m_DropTarget;

    // Printing information
    CSize       m_CharSize;
    int         m_nPageHeight;
    CSize       m_LogicalPageSize,      // Page size in gridctrl units.
                m_PaperSize;            // Page size in device units.

    // sorting
    int         m_bAscending;
    int         m_SortColumn;

protected:
    void SelectAllCells();
    void SelectColumns(CCellID currentCell);
    void SelectRows(CCellID currentCell);
    void SelectCells(CCellID currentCell);
    void OnSelecting(const CCellID& currentCell);

    // Generated message map functions
    //{{AFX_MSG(CGridCtrl)
    afx_msg void OnPaint();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    afx_msg UINT OnGetDlgCode();
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    afx_msg void OnSysColorChange();
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    //}}AFX_MSG
    afx_msg LRESULT OnSetFont(WPARAM hFont, LPARAM lParam);
    afx_msg LRESULT OnGetFont(WPARAM hFont, LPARAM lParam);
    afx_msg BOOL OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

    enum eMouseModes { MOUSE_NOTHING, MOUSE_SELECT_ALL, MOUSE_SELECT_COL, MOUSE_SELECT_ROW,
                       MOUSE_SELECT_CELLS, MOUSE_SCROLLING_CELLS,
                       MOUSE_OVER_ROW_DIVIDE, MOUSE_SIZING_ROW, 
                       MOUSE_OVER_COL_DIVIDE, MOUSE_SIZING_COL,
                       MOUSE_PREPARE_EDIT, MOUSE_PREPARE_DRAG, MOUSE_DRAGGING};
};

inline CGridCell* CGridCtrl::GetCell(int nRow, int nCol) const
{
    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols) return NULL;

    GRID_ROW* pRow = m_RowData[nRow];
    if (!pRow) return NULL;
    return pRow->GetAt(nCol);
}

inline BOOL CGridCtrl::SetCell(int nRow, int nCol, CGridCell* pCell)
{
    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols) return FALSE;

    GRID_ROW* pRow = m_RowData[nRow];
    if (!pRow) return FALSE;

    pRow->SetAt(nCol, pCell);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
