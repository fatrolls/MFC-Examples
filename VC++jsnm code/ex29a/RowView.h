// rowview.h : interface of the CRowView class
//
// This class implements the behavior of a scrolling view that presents
//  multiple rows of fixed-height data.  A row view is similar to an
//  owner-draw list box in its visual behavior; but unlike list boxes,
//  a row view has all of the benefits of a view (as well as scroll view),
//  including perhaps most importantly printing and print preview.
/////////////////////////////////////////////////////////////////////////////

class CRowView : public CScrollView 
{
DECLARE_DYNAMIC(CRowView)
protected:
// Construction/destruction
    CRowView();
    virtual ~CRowView();
// Attributes
protected:
    int m_nRowWidth;            // width of row in logical units
    int m_nRowHeight;           // height of row in logical units
    int m_nCharWidth;           // avg char width in logical units
    int m_nPrevSelectedRow;     // index of the most recently selected row
    int m_nPrevRowCount;        // most recent row count, before update
    int m_nRowsPerPrintedPage;  // how many rows fit on a printed page

// Operations-Attributes
protected:
    virtual void UpdateRow(int nInvalidRow); // called by derived class 
	                                         //  OnUpdate
    virtual void CalculateRowMetrics(CDC* pDC)
            { GetRowWidthHeight(pDC, m_nRowWidth, m_nRowHeight, 
			    m_nCharWidth); }
    virtual void UpdateScrollSizes();
    virtual CRect RowToWndRect(CDC* pDC, int nRow);
    virtual int RowToYPos(int nRow);
    virtual void RectLPtoRowRange(const CRect& rectLP, int& nFirstRow,
        int& nLastRow, BOOL bIncludePartiallyShownRows);
    virtual int LastViewableRow();

// Overridables
protected:
    virtual void GetRowWidthHeight(CDC* pDC, int& nRowWidth, 
        int& nRowHeight, int& nCharWidth) = 0;
    virtual int GetActiveRow() = 0;
    virtual int GetRowCount() = 0;
    virtual void OnDrawRow(CDC* pDC, int nRow, int y, BOOL bSelected) = 0;
    virtual void ChangeSelectionNextRow(BOOL bNext) = 0;
    virtual void ChangeSelectionToRow(int nRow) = 0;

// Implementation
protected:
    // standard overrides of MFC classes
    virtual void OnInitialUpdate();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
    //{{AFX_MSG(CRowView)
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
    