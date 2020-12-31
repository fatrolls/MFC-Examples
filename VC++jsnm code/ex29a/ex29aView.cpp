// ex29avw.cpp : implementation of the CEx29aView class
//

#include "stdafx.h"
#include "ex29a.h"

#include "ex29adoc.h"
#include "ex29aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx29aView

IMPLEMENT_DYNCREATE(CEx29aView, CRowView)

BEGIN_MESSAGE_MAP(CEx29aView, CRowView)
    //{{AFX_MSG_MAP(CEx29aView)
    ON_WM_SETFOCUS()
    ON_WM_MOUSEACTIVATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CRowView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRowView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx29aView construction/destruction

CEx29aView::CEx29aView()
{
	m_pSet = NULL;
}

CEx29aView::~CEx29aView()
{
}
									
/////////////////////////////////////////////////////////////////////////////
void CEx29aView::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{
    // called when the user executes a new query
    // can't set m_pSet in OnInitialUpdate because it's NULL then
    ScrollToPosition(CPoint(0, 0));
    Invalidate(TRUE);
    m_nSelectedRow = -1;
	CEx29aDoc* pDoc = GetDocument();
	if((m_pSet = pDoc->m_pRecordset) != NULL) {
		UpdateScrollSizes();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRowView overrides

/////////////////////////////////////////////////////////////////////////////
void CEx29aView::OnDrawRow(CDC* pDC, int nRow, int y, BOOL bSelected)
{
    int x = 0;
    int i;
    CEx29aDoc* pDoc = GetDocument();
    if (m_pSet == NULL) return;
	
    if (nRow == 0) {    // title row
      for (i = 0; i < pDoc->m_nFields; i++) {
        pDC->TextOut(x, y, pDoc->m_arrayFieldName[i]);
        x += pDoc->m_arrayFieldSize[i] * m_nCharWidth;
      }	
    }
    else {
      try {
        m_pSet->SetAbsolutePosition(nRow - 1); // adjust for title row
		// SetAbsolutePosition doesn't throw exception until AFTER 
		//  end of set
        if (m_pSet->GetAbsolutePosition() == (nRow - 1)) {
          DrawDataRow(pDC, y);
        }
      }
      catch (CDaoException* e) {
		// might be a time delay before delete is seen in this program
        if (e->m_pErrorInfo->m_lErrorCode == 3167) {
          pDC->TextOut(0, y, "**RECORD DELETED**");
        }
        else {
          m_pSet->MoveLast(); // in case m_nRowCount is too big
	      pDoc->m_nRowCount = m_pSet->GetAbsolutePosition() + 2;
        }
        e->Delete();
      }
    }
}

void CEx29aView::DrawDataRow(CDC* pDC, int y)
{
    int x = 0;
    CString strTime;

    COleVariant var;
    CString str;
    CEx29aDoc* pDoc = GetDocument();
    for (int i = 0; i < pDoc->m_nFields; i++) {
      var = m_pSet->GetFieldValue(i);
      switch (var.vt) {
      case VT_BSTR:
        str = (LPCSTR) var.bstrVal; // narrow characters in DAO
        break;
      case VT_I2:
        str.Format("%d", (int) var.iVal);
        break;
      case VT_I4:
        str.Format("%d", var.lVal);
        break;
      case VT_R4:
        str.Format("%10.2f", (double) var.fltVal);
        break;
      case VT_R8:
        str.Format("%10.2f", var.dblVal);
        break;
	  case VT_CY:
        str = COleCurrency(var).Format();
        break;
      case VT_DATE:
        str = COleDateTime(var).Format();
        break;
      case VT_BOOL:
        str = (var.boolVal == 0) ? "FALSE" : "TRUE";
        break;
      case VT_NULL:
        str =  "----";
        break;
      default:
        str.Format("Unk type %d\n", var.vt);
        TRACE("Unknown type %d\n", var.vt);
      }
      pDC->TextOut(x, y, str);
      x += pDoc->m_arrayFieldSize[i] * m_nCharWidth;
    }	
}

/////////////////////////////////////////////////////////////////////////////
void CEx29aView::GetRowWidthHeight(CDC* pDC, int& nRowWidth,
         int& nRowHeight, int& nCharWidth)
{
    TEXTMETRIC tm;

    CEx29aDoc* pDoc = GetDocument();
	pDC->GetTextMetrics(&tm);
    nCharWidth = tm.tmAveCharWidth + 1;
    nRowWidth = 0;
	for(int i = 0; i < pDoc->m_nFields; i++) {
	    nRowWidth += pDoc->m_arrayFieldSize[i];
	}
    nRowWidth *= nCharWidth;
    nRowHeight = tm.tmHeight;
}

/////////////////////////////////////////////////////////////////////////////
int CEx29aView::GetActiveRow()
{
    return m_nSelectedRow;
}

/////////////////////////////////////////////////////////////////////////////
int CEx29aView::GetRowCount()
{
    return GetDocument()->m_nRowCount;
}

/////////////////////////////////////////////////////////////////////////////
void CEx29aView::ChangeSelectionNextRow(BOOL bNext)
{
    if (bNext && (m_nSelectedRow < min(GetRowCount() - 1,
                LastViewableRow() - 2))) {
        m_nSelectedRow++;
    }
    if (!bNext && m_nSelectedRow) {
        m_nSelectedRow--;
    }
    UpdateRow(m_nSelectedRow);
}

/////////////////////////////////////////////////////////////////////////////
void CEx29aView::ChangeSelectionToRow(int nRow)
{
    if ((nRow >= 0) && (nRow < min(GetRowCount(), LastViewableRow() - 1))) {
        m_nSelectedRow = nRow;
    }
    UpdateRow(m_nSelectedRow);
}

/////////////////////////////////////////////////////////////////////////////
// CEx29aView diagnostics

#ifdef _DEBUG
void CEx29aView::AssertValid() const
{
    CRowView::AssertValid();
}

void CEx29aView::Dump(CDumpContext& dc) const
{
    CRowView::Dump(dc);
}

/////////////////////////////////////////////////////////////////////////////
CEx29aDoc* CEx29aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx29aDoc)));
    return (CEx29aDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx29aView message handlers

/////////////////////////////////////////////////////////////////////////////
void CEx29aView::OnSetFocus(CWnd* pOldWnd)
{
    // updates dialog bar query strings
	GetDocument()->PutQuery();
	CRowView::OnSetFocus(pOldWnd);
}

/////////////////////////////////////////////////////////////////////////////
int CEx29aView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// resets the focus from the dialog bar
    SetFocus(); 
    return CRowView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CEx29aView::OnInitialUpdate() 
{
	CRowView::OnInitialUpdate();
}

void CEx29aView::OnTimer(UINT nIDEvent) 
{
	Invalidate(); // update view from database
}
