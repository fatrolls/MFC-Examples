// TblView.cpp : implementation of the CDaoTableView class
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoSet.h"
#include "DaoDoc.h"
#include "TblView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OFFITEM 1
#define OFFCHAR 2
#define BSIZE 256

// for printing only
#define HEADER_LINE  3
#define FOOTER_LINE  3
#define LABEL_LINE   2
#define OFFSET_PAGE 15
#define TOTAL_LINE (HEADER_LINE+FOOTER_LINE+LABEL_LINE)

int DaoListFormat(short Type)
{
  switch (Type)
  {
    case dbBoolean:	break;
    case dbByte:	break;
    case dbInteger:	return LVCFMT_RIGHT;
    case dbLong:	return LVCFMT_RIGHT;
    case dbCurrency:	return LVCFMT_RIGHT;
    case dbSingle:	return LVCFMT_RIGHT;
    case dbDouble:	return LVCFMT_RIGHT;
    case dbDate:	break;
    case dbText:	break;
    case dbLongBinary:  break;
    case dbMemo:	break;
    case dbGUID:	break;
  }
  return LVCFMT_LEFT;
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView

IMPLEMENT_DYNCREATE(CDaoTableView, CListView)

BEGIN_MESSAGE_MAP(CDaoTableView, CListView)
  //{{AFX_MSG_MAP(CDaoTableView)
  ON_WM_CREATE()
  ON_WM_SIZE()
  ON_WM_PAINT()
  ON_WM_SETFOCUS()
  ON_WM_KILLFOCUS()
  ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
  ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
  ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
  ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
  ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
  //}}AFX_MSG_MAP
  // Header command
  ON_NOTIFY_REFLECT(HDN_BEGINTRACK, OnHeaderBeginTrack)
  ON_NOTIFY_REFLECT(HDN_ENDTRACK, OnHeaderEndTrack)
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView construction/destruction

CDaoTableView::CDaoTableView()
{
  m_colorText   = ::GetSysColor(COLOR_WINDOWTEXT);
  m_colorTextBk = ::GetSysColor(COLOR_WINDOW);
  m_colorBkgnd  = ::GetSysColor(COLOR_WINDOW);
  m_bFitToPage = FALSE;
  m_bPrintMarge = TRUE;
}

CDaoTableView::~CDaoTableView()
{
  if (m_Font.m_hObject != NULL) m_Font.DeleteObject();
}

BOOL CDaoTableView::PreCreateWindow(CREATESTRUCT& cs)
{
  // default is report view and full row selection
  cs.style &= ~LVS_TYPEMASK;
  cs.style |= LVS_REPORT | LVS_OWNERDRAWFIXED;
  return CListView::PreCreateWindow(cs);
}

int CDaoTableView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CListView::OnCreate(lpCreateStruct) == -1)
    return -1;

  // Create the default font for the list
  int Height = (3 * HIWORD(::GetDialogBaseUnits())) / 4;

  LOGFONT lf;
  memset(&lf, 0, sizeof(lf));
  lf.lfHeight = -Height;
  lf.lfWeight = (Height > 13) ? 700: 400;
  lf.lfPitchAndFamily = 0x31;
  strcpy(lf.lfFaceName, "Courier New");
  VERIFY(m_Font.CreateFontIndirect(&lf));
	
  return 0;
}

void CDaoTableView::OnSize(UINT nType, int cx, int cy) 
{
  m_cxClient = cx; m_cyClient = cy;
  CListView::OnSize(nType, cx, cy);
}

void CDaoTableView::OnPaint() 
{
  // in full row select mode, we need to extend the clipping region
  // so we can paint a selection all the way to the right
  CRect rectAllLabels;
  GetListCtrl().GetItemRect(0, rectAllLabels, LVIR_BOUNDS);

  if (rectAllLabels.right < m_cxClient)
  {
    // need to call BeginPaint (in CPaintDC constructor)
    // to get correct clipping rect
    CPaintDC dc(this);

    CRect rectClip;
    dc.GetClipBox(rectClip);
    if (!rectClip.IsRectEmpty())
    {
      rectClip.left = min(rectAllLabels.right - 1, rectClip.left);
      rectClip.right = m_cxClient;

      InvalidateRect(rectClip, FALSE);
    }
    // EndPaint will be called in CPaintDC destructor
    DrawRaster(&dc);
  }
  CListView::OnPaint();
}

void CDaoTableView::OnSetFocus(CWnd* pOldWnd) 
{
  CListView::OnSetFocus(pOldWnd);

  // check if we are getting focus from label edit box
  if (pOldWnd != NULL && pOldWnd->GetParent() == this)
    return;
	
  // repaint items that should change appearance
  RepaintSelectedItems();
}

void CDaoTableView::OnKillFocus(CWnd* pNewWnd) 
{
  CListView::OnKillFocus(pNewWnd);

  // check if we are losing focus to label edit box
  if (pNewWnd != NULL && pNewWnd->GetParent() == this)
    return;
	
  // repaint items that should change appearance
  RepaintSelectedItems();
}

void CDaoTableView::OnInitialUpdate()
{
  // Initialise table
  CListCtrl& ctrlList = GetListCtrl();
  ctrlList.DeleteAllItems();
  while (ctrlList.DeleteColumn(0));
  UpdateWindow();

  // get textmetric
  ctrlList.SetFont(&m_Font);
  m_tmAveCharWidth = ctrlList.GetStringWidth(" ");

  // get recordset and update
  CDaoRecordset* pSet = OnGetRecordset();
  if (pSet == NULL) return;

  ASSERT(pSet->m_pDatabase != NULL);
  ASSERT(pSet->IsOpen());

  CWaitCursor waitCursor;

  // Set columns
  CDaoFieldInfo fieldInfo;
  CDaoTableDef tableDef(pSet->m_pDatabase);
  try
  {
    CString strLabel;
    int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    tableDef.Open(pSet->GetName());
    int m_nField = tableDef.GetFieldCount();
    for (int i = 0; i < m_nField; i++)
    {
      tableDef.GetFieldInfo(i, fieldInfo, AFX_DAO_ALL_INFO);
      strLabel = fieldInfo.m_strName;
      AddColumn(strLabel, i, -1, nMask, DaoListFormat(fieldInfo.m_nType));
      // the fist column is can only be left justified !
      if (i == 0) m_nJustifyFirstCol = DaoListFormat(fieldInfo.m_nType);
    }
  }
  catch (CDaoException* e)
  {
    DaoMessageBox(e);
    e->Delete();
  }
  tableDef.Close();

  CListView::OnInitialUpdate();
}

void CDaoTableView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  // get recordset and update
  CDaoRecordset* pSet = OnGetRecordset();

  // for me ?
  if (pHint && pHint != pSet) return;

  // Clean up
  GetListCtrl().DeleteAllItems();

  if (pSet == NULL) return;
  ASSERT(pSet->m_pDatabase != NULL);
  ASSERT(pSet->IsOpen());

  CWaitCursor waitCursor;
  m_Record.RemoveAll();
  m_Record.SetSize(GetRecordCount());

  // set data
  try
  {
    UINT iItem = 0;
    pSet->MoveFirst();
    COleVariant var;
    while (!pSet->IsEOF())
    {
      var = pSet->GetBookmark();
      m_Record.SetAt(iItem, var);
      AddItem(iItem++);
      pSet->MoveNext();
    }
    pSet->MoveFirst();
    var = pSet->GetBookmark();
  }
  catch (CDaoException* e)
  {
    DaoMessageBox(e);
    e->Delete();
  }
  UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView virtual functions

CDaoRecordset* CDaoTableView::OnGetRecordset()
{
  ASSERT(FALSE);  // must be overrided
  return NULL;
}

long CDaoTableView::GetRecordCount()
{
  ASSERT(FALSE);  // must be overrided
  return 0L;
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView helper functions

UINT CDaoTableView::JustifyText(int fmt, int c)
{
  // the first column can only be left justified
  if (c == 0) fmt = m_nJustifyFirstCol;
  UINT nJustify = DT_LEFT;
  switch(fmt & LVCFMT_JUSTIFYMASK)
  {
    case LVCFMT_RIGHT:
      nJustify = DT_RIGHT;
      break;
    case LVCFMT_CENTER:
      nJustify = DT_CENTER;
      break;
  }
  return nJustify|DT_SINGLELINE|DT_NOPREFIX|DT_NOCLIP|DT_VCENTER;
}

void CDaoTableView::RepaintSelectedItems()
{
  CListCtrl& ctrlList = GetListCtrl();
  CRect rectItem, rectLabel;

  // invalidate focused item so it can repaint properly
  int nItem = ctrlList.GetNextItem(-1, LVNI_FOCUSED);
  if (nItem != -1)
  {
    ctrlList.GetItemRect(nItem, rectItem, LVIR_BOUNDS);
    ctrlList.GetItemRect(nItem, rectLabel, LVIR_LABEL);
    rectItem.left = rectLabel.left;
    InvalidateRect(rectItem, FALSE);
  }

  // if selected items should not be preserved, invalidate them
  if (!(GetStyle() & LVS_SHOWSELALWAYS))
  {
    for (nItem = ctrlList.GetNextItem(-1, LVNI_SELECTED);
      nItem != -1; nItem = ctrlList.GetNextItem(nItem, LVNI_SELECTED))
    {
      ctrlList.GetItemRect(nItem, rectItem, LVIR_BOUNDS);
      ctrlList.GetItemRect(nItem, rectLabel, LVIR_LABEL);
      rectItem.left = rectLabel.left;
      InvalidateRect(rectItem, FALSE);
    }
  }

  // update changes
  UpdateWindow();
}

void CDaoTableView::UpdateViews()
{
  // Find the focused item
  CListCtrl& ctrlList = GetListCtrl();
  int nItem = ctrlList.GetNextItem(-1, LVNI_FOCUSED);
  if (nItem != -1)
  {
    // read the record and update all views
    CDaoRecordset* pSet = OnGetRecordset();
    COleVariant var = pSet->GetBookmark();
    if (var != m_Record.GetAt(nItem))
    {
      try
      {
        pSet->SetBookmark(m_Record.GetAt(nItem));
      }
      catch (CDaoException* e)
      {
        DaoMessageBox(e);
        e->Delete();
      }
    }
    // Send message to all views with the recordset pointer
    GetDocument()->UpdateAllViews(this, 0, pSet);
  }
}

BOOL CDaoTableView::AddColumn(LPCTSTR strItem, int nItem, int nSubItem, int nMask, int nFmt)
{
  LV_COLUMN lvc;
  lvc.mask = nMask;
  lvc.fmt = nFmt;
  lvc.pszText = (LPTSTR)strItem;
  CListCtrl& ctrlList = GetListCtrl();
  lvc.cx  = ctrlList.GetStringWidth(" ");
  lvc.cx *= strlen(strItem) + OFFCHAR;
  if (nMask & LVCF_SUBITEM)
  {
    if (nSubItem != -1)
      lvc.iSubItem = nSubItem;
    else
      lvc.iSubItem = nItem;
  }
  return ctrlList.InsertColumn(nItem, &lvc);
}

BOOL CDaoTableView::AddItem(int nItem, LPARAM lParam)
{
  CListCtrl& ctrlList = GetListCtrl();
  LV_ITEM lvItem;
  lvItem.mask = LVIF_TEXT|LVIF_PARAM;
  lvItem.iItem = nItem;
  lvItem.iSubItem = 0;
  lvItem.pszText = LPSTR_TEXTCALLBACK;
  lvItem.lParam = lParam;
  if (nItem == 0)
  {
    lvItem.mask |= LVIF_STATE;
    lvItem.state = LVIS_SELECTED;
  }
  return ctrlList.InsertItem(&lvItem);
}

LPCTSTR CDaoTableView::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
{
  static const _TCHAR szThreeDots[] = _T("...");

  int nStringLen = lstrlen(lpszLong);

  if (nStringLen == 0 || pDC->GetTextExtent(lpszLong, nStringLen).cx + nOffset <= nColumnLen)
    return(lpszLong);

  static _TCHAR szShort[MAX_PATH];

  lstrcpy(szShort, lpszLong);
  int nAddLen = pDC->GetTextExtent(szThreeDots, sizeof(szThreeDots)).cx;

  for (int i = nStringLen - 1; i > 0; i--)
  {
    szShort[i] = 0;
    if (pDC->GetTextExtent(szShort, i).cx + nOffset + nAddLen <= nColumnLen)
      break;
  }

  lstrcat(szShort, szThreeDots);

  return(szShort);
}

void CDaoTableView::DrawRaster(CDC* pDC)
{
  CListCtrl& ctrlList = GetListCtrl();
  CRect rectItem; ctrlList.GetItemRect(0, &rectItem, LVIR_BOUNDS);

  LV_COLUMN lvc; int x = rectItem.left;
  lvc.mask = LVCF_FMT | LVCF_WIDTH;
  for (int c = 0; ctrlList.GetColumn(c, &lvc); c++)
  {
    x += lvc.cx;
    pDC->MoveTo(x-1, 0);
    pDC->LineTo(x-1, m_cyClient);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView printing helpers

void CDaoTableView::GetPrintTitle(CString& strTitle)
{
  ASSERT(FALSE);
  strTitle = _T("");
}

void CDaoTableView::SetPrintRectangle(CDC* pDC, CPrintInfo* pInfo)
{
  LPDEVMODE pDM = pInfo->m_pPD->GetDevMode();
  pInfo->m_rectDraw.SetRect(0, 0, pDC->GetDeviceCaps(HORZRES),
				  pDC->GetDeviceCaps(VERTRES));
  if (m_bPrintMarge)
  {
    if (pDM->dmOrientation == DMORIENT_PORTRAIT)
      pInfo->m_rectDraw.left +=
	MulDiv(pDC->GetDeviceCaps(LOGPIXELSX), OFFSET_PAGE, 25);
    else
      pInfo->m_rectDraw.top +=
	MulDiv(pDC->GetDeviceCaps(LOGPIXELSX), OFFSET_PAGE, 25);
  }
  if (pDM->dmDefaultSource == DMBIN_TRACTOR)
  {
    pInfo->m_rectDraw.top    += pDC->GetDeviceCaps(LOGPIXELSY);
    pInfo->m_rectDraw.bottom -= pDC->GetDeviceCaps(LOGPIXELSY);
  }
}

int CDaoTableView::PrintCharPerLine()
{
  int cx = 0;
  LV_COLUMN lvc;
  CListCtrl& ctrlList = GetListCtrl();
  lvc.mask = LVCF_WIDTH;
  for (int c = 0; ctrlList.GetColumn(c, &lvc); c++)
    cx += lvc.cx;
  return cx / m_tmAveCharWidth;
}

int CDaoTableView::GetListLine(int Line, CString& strLine)
{
  int nLen;
  LV_COLUMN lvc;
  lvc.mask = LVCF_FMT | LVCF_WIDTH;
  char szBuffer[BSIZE+2];
  strLine.Empty();

  CListCtrl& ctrlList = GetListCtrl();
  for (int c = 0; ctrlList.GetColumn(c, &lvc); c++)
  {
    nLen = ctrlList.GetItemText(Line, c+1, szBuffer, BSIZE);
    szBuffer[nLen] = '\t'; szBuffer[nLen+1] = '\0';
    strLine += szBuffer;
  }
  nLen = strLine.GetLength();
  char *p = strLine.GetBuffer(nLen+1);
  p = &p[nLen-1]; *p++ = '\r'; *p++ = '\n'; *p = '\0';
  strLine.ReleaseBuffer(nLen + 1);
  return nLen+1;
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView printing

BOOL CDaoTableView::OnPreparePrinting(CPrintInfo* pInfo)
{
  // default preparation
  return DoPreparePrinting(pInfo);
}

void CDaoTableView::OnBeginPrinting(CDC* pDC, CPrintInfo *pInfo)
{
  CListCtrl& ctrlList = GetListCtrl();

  // set print rectangle
  SetPrintRectangle(pDC, pInfo);

  // get number or char per line and page width
  int nChar = PrintCharPerLine();
  int Width = pInfo->m_rectDraw.Width();
  
  // Create printer font
  if (m_bFitToPage && Width / nChar < m_tmAveCharWidth)
    m_PrintFont.Create(pDC, nChar, Width);
  else
    m_PrintFont.Create(pDC);
  ctrlList.SetFont(&m_PrintFont);

  // calculate the number of rows per printed page
  ASSERT(m_PrintFont.m_tm.tmHeight != 0);
  int PageHeight = pInfo->m_rectDraw.Height();
  m_RowsPerPrintedPage = PageHeight / m_PrintFont.m_tm.tmHeight - TOTAL_LINE;

  // calculate the number of page
  int LineCount = ctrlList.GetItemCount();
  int nPage = LineCount / m_RowsPerPrintedPage;
  if (LineCount % m_RowsPerPrintedPage) nPage++;

  // check if a row must be printed on more than one page
  LV_COLUMN lvc;
  m_nColPage = 1;
  int ColChar, SumChar = 0;
  int MaxChar = Width / m_PrintFont.m_tm.tmAveCharWidth;
  lvc.mask = LVCF_WIDTH;
  for (int c = 0; ctrlList.GetColumn(c, &lvc); c++)
  {
    ColChar = lvc.cx / m_tmAveCharWidth;
    if (SumChar + ColChar > MaxChar)
    {
      m_nColPage++; SumChar = 0;
    }
    SumChar += ColChar;
  }
  
  // set number of page and current page  
  pInfo->SetMaxPage(nPage * m_nColPage);
  pInfo->m_nCurPage = 1;
}

void CDaoTableView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
  int l, c, x, y, nLen;
  CString strText;
  char szBuffer[BSIZE];
  CRect rectItem, rectLabel;
  CArray <PRNCOLINFO, PRNCOLINFO&> ColInfos;
  PRNCOLINFO ColInfo;

  // initialize
  /////////////
  // set print rectangle
  SetPrintRectangle(pDC, pInfo);
  // select object
  CListCtrl& ctrlList = GetListCtrl();
  CFont *pOldFont = pDC->SelectObject(&m_PrintFont);
  pDC->SetBkMode(TRANSPARENT);
  int tmHeight = m_PrintFont.m_tm.tmHeight;
  int tmAveCharWidth = m_PrintFont.m_tm.tmAveCharWidth;
  // get print position
  int xl   = pInfo->m_rectDraw.left;
  int xr   = pInfo->m_rectDraw.right;
  int yPos = pInfo->m_rectDraw.top;
  int yb   = pInfo->m_rectDraw.bottom; 
  
  // draw the Header
  //////////////////

  // first line blank
  yPos += tmHeight;

  // username
  VERIFY(strText.LoadString(IDS_PRN_USER_NAME));
  pDC->TextOut(xl, yPos, strText);

  // list title
  GetPrintTitle(strText);
  x = xl + (xr - xl - strText.GetLength() * tmAveCharWidth) / 2;
  pDC->TextOut(x, yPos, strText);

  // local date
  SYSTEMTIME Time;
  GetLocalTime(&Time);
  COleDateTime OleTime(Time);
  CString strFormat;
  VERIFY(strFormat.LoadString(IDS_PRN_DATE_FORMAT));
  strText = OleTime.Format(strFormat);
  x = xr - strText.GetLength() * tmAveCharWidth;
  pDC->TextOut(x, yPos, strText);

  // title
  yPos += tmHeight; y = yPos + tmHeight / 2;
  pDC->MoveTo(xl, y); pDC->LineTo(xr, y);
  yPos += tmHeight;

  // calculate the row and ColPage position with the page number
  int Page     = (pInfo->m_nCurPage - 1) / m_nColPage;
  int ColPage  = ((pInfo->m_nCurPage - 1) % m_nColPage) + 1;

  // find the right ColPage
  int FirstCol;
  LV_COLUMN lvc;
  lvc.mask = LVCF_WIDTH;
  int CurPage = 1;
  for (c = 0, x = xl; ctrlList.GetColumn(c, &lvc) && CurPage != ColPage; c++)
  {
    x += MulDiv(lvc.cx, tmAveCharWidth, m_tmAveCharWidth);
    if (x > xr) { CurPage++; if (CurPage == ColPage) break; }
  }
  // draw the list header and save column infos
  lvc.cchTextMax = BSIZE;
  lvc.pszText = szBuffer;
  lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
  rectItem.SetRect(xl, yPos, 0, yPos + tmHeight);
  for (FirstCol = c; ctrlList.GetColumn(c, &lvc); c++)
  {
    rectItem.right = rectItem.left + MulDiv(lvc.cx, tmAveCharWidth, m_tmAveCharWidth);
    if (rectItem.right > xr) break; // on next page

    rectLabel = rectItem;
    rectLabel.InflateRect(-tmAveCharWidth * OFFCHAR / 2, 0);

    LPCSTR pszText = MakeShortString(pDC, lvc.pszText, rectItem.right - rectItem.left, 2*OFFITEM);
    UINT nJustify = DT_LEFT;
    if (pszText == lvc.pszText) nJustify = JustifyText(lvc.fmt, c);

    rectLabel.InflateRect(-OFFITEM, 0);
    pDC->DrawText(pszText, -1, rectLabel, nJustify);

    ColInfo.rectItem  = rectItem;
    ColInfo.rectLabel = rectLabel;
    ColInfo.nJustify  = nJustify;
    ColInfo.rectItem.OffsetRect(0, tmHeight);
    ColInfo.rectLabel.OffsetRect(0, tmHeight);
    ColInfos.Add(ColInfo);

    rectItem.left = rectItem.right;
  }
  // separation
  yPos += tmHeight; y = yPos + tmHeight / 2;
  pDC->MoveTo(xl, y); pDC->LineTo(xr, y);
  yPos += tmHeight;
  
  // draw the list
  ////////////////
  CString strLine;
  int LineCount = ctrlList.GetItemCount();
  int Line = Page * m_RowsPerPrintedPage;

  // draw the list
  int Size = ColInfos.GetSize();
  for (l = 0; l < m_RowsPerPrintedPage; l++)
  {
    // no more line
    if (l + Line >= LineCount) break;

    c = 0;
    nLen = GetListLine(l + Line, strLine);
    char *p = strLine.GetBuffer(nLen+1);
    p = strtok(p, "\t\r\n");

    // find the right ColPage
    while (p && *p && c != FirstCol)
    {
      p = strtok(NULL, "\t\r\n");
      c++; if (c == Size) break;
    }
    c = 0;
    while (p && *p)
    {
      ColInfos[c].rectItem.OffsetRect(0, tmHeight);
      ColInfos[c].rectLabel.OffsetRect(0, tmHeight);
      LPCSTR pszText = MakeShortString(pDC, p, ColInfos[c].rectItem.Width(), 2*OFFITEM);
      pDC->DrawText(pszText, -1, ColInfos[c].rectLabel, ColInfos[c].nJustify);
      p = strtok(NULL, "\t\r\n");
      c++; if (c == Size) break;
    }
    strLine.ReleaseBuffer(nLen);
    yPos += tmHeight;
  }

  // draw footer
  //////////////
  yPos = yb - FOOTER_LINE * tmHeight;
  // separation
  y = yPos + tmHeight / 2;
  pDC->MoveTo(xl, y); pDC->LineTo(xr, y);
  yPos += tmHeight;
  // application name
  VERIFY(strText.LoadString(IDS_PRN_APPLICATION_NAME));
  pDC->TextOut(xl, yPos, strText);
  // page number
  strText.Format(IDS_PRN_PAGE_FORMAT, pInfo->m_nCurPage);
  x = xr - strText.GetLength() * tmAveCharWidth;
  pDC->TextOut(x, yPos, strText);
  
  // cleanup
  //////////
  pDC->SelectObject(pOldFont);
}

void CDaoTableView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
  GetListCtrl().SetFont(&m_Font);
  m_PrintFont.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView diagnostics

#ifdef _DEBUG
void CDaoTableView::AssertValid() const
{
	CListView::AssertValid();
}

void CDaoTableView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMSDIDaoDoc* CDaoTableView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSDIDaoDoc)));
	return (CMSDIDaoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView virtual functions for the list control

void CDaoTableView::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  CListCtrl& ctrlList = GetListCtrl();
  CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
  CRect rectItem(lpDrawItemStruct->rcItem);
  UINT uiFlags = ILD_TRANSPARENT;
  int nItem = lpDrawItemStruct->itemID;
  BOOL bFocus = (GetFocus() == this);
  COLORREF colorTextSave, colorBkSave;
  COLORREF colorImage = m_colorBkgnd;
  static _TCHAR szBuffer[MAX_PATH];
  LPCTSTR pszText;

  // get item data
  LV_ITEM lvi;
  lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
  lvi.iItem = nItem;
  lvi.iSubItem = 0;
  lvi.pszText = szBuffer;
  lvi.cchTextMax = sizeof(szBuffer);
  lvi.stateMask = 0xFFFF; 	// get all state flags
  ctrlList.GetItem(&lvi);
  BOOL bSelected = (bFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
  bSelected = bSelected || (lvi.state & LVIS_DROPHILITED);

  // set colors if item is selected
  CRect rectAllLabels;
  ctrlList.GetItemRect(nItem, rectAllLabels, LVIR_BOUNDS);
  // extend the rectangle to the whole client area
  if (rectAllLabels.right < m_cxClient) rectAllLabels.right = m_cxClient;

  if (bSelected)
  {
    colorTextSave = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
    colorBkSave = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
    pDC->FillRect(rectAllLabels, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
  }
  else
    pDC->FillRect(rectAllLabels, &CBrush(m_colorTextBk));

  // draw labels for all columns
  CRect rectLabel;
  LV_COLUMN lvc;
  lvc.mask = LVCF_FMT | LVCF_WIDTH;
  rectItem = rectAllLabels;
  for (int c = 0; ctrlList.GetColumn(c, &lvc); c++)
  {
    rectItem.right = rectItem.left + lvc.cx;

    rectLabel = rectItem;
    rectLabel.InflateRect(-m_tmAveCharWidth * OFFCHAR / 2, 0);

    int nRetLen = ctrlList.GetItemText(nItem, c+1, szBuffer, sizeof(szBuffer));
    if (nRetLen == 0) continue;

    pszText = MakeShortString(pDC, szBuffer, rectLabel.Width(), 2*OFFITEM);
    UINT nJustify = DT_LEFT;
    if (pszText == szBuffer) nJustify = JustifyText(lvc.fmt, c);

    rectLabel.InflateRect(-OFFITEM, 0);
    pDC->DrawText(pszText, -1, rectLabel, nJustify);

    // draw raster to bottom
    pDC->MoveTo(rectItem.right-1, rectLabel.top);
    pDC->LineTo(rectItem.right-1, m_cyClient);

    rectItem.left = rectItem.right;
  }

  // draw focus rectangle if item has focus
  if (lvi.state & LVIS_FOCUSED && bFocus)
    pDC->DrawFocusRect(rectAllLabels);

  // set original colors if item was selected
  if (bSelected)
  {
    pDC->SetTextColor(colorTextSave);
    pDC->SetBkColor(colorBkSave);
  }
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView list message handlers

void CDaoTableView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
  COleVariant var;
  CDaoRecordset* pSet = OnGetRecordset();
  ASSERT(pSet != NULL);

  LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
  // Test if we are in get mode
  if (pDispInfo->hdr.code == LVN_GETDISPINFO)
  {
    // iSubItem == 0 for Image !
    if (pDispInfo->item.iSubItem != 0)
    {
      // read the record when necessary
      var = pSet->GetBookmark();
      if (var != m_Record.GetAt(pDispInfo->item.iItem))
      {
	try
	{
	  pSet->SetBookmark(m_Record.GetAt(pDispInfo->item.iItem));
	  var = pSet->GetFieldValue(pDispInfo->item.iSubItem-1);
	  strcpy(pDispInfo->item.pszText, CCrack::strVARIANT(var));
	}
	catch (CDaoException* e)
	{
  	  strcpy(pDispInfo->item.pszText, "?");
	  DaoMessageBox(e);
	  e->Delete();
	}
      }
      else
      {
        var = pSet->GetFieldValue(pDispInfo->item.iSubItem-1);
        strcpy(pDispInfo->item.pszText, CCrack::strVARIANT(var));
      }
    }
  }
  *pResult = 0;
}

void CDaoTableView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
  UpdateViews();
  *pResult = 0;
}

void CDaoTableView::OnReturn(NMHDR* pNMHDR, LRESULT* pResult) 
{
  UpdateViews();
  *pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView list header message handlers

void CDaoTableView::OnHeaderBeginTrack(NMHDR* pNMHDR, LRESULT* pResult) 
{
  *pResult = 0;
}

void CDaoTableView::OnHeaderEndTrack(NMHDR* pNMHDR, LRESULT* pResult) 
{
  Invalidate();		// to redraw raster
  *pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView clipboard

#define BLKSIZE 4096
static HANDLE hData = NULL;	// handles to clip data

void CDaoTableView::OnEditCopy()
{
  CWaitCursor waitCursor;
  if (OpenClipboard())
  {
    EmptyClipboard();

    try
    {
      // allocate memory in block of BLKSIZE bytes
      DWORD nSize = BLKSIZE;
      if (hData != NULL) GlobalFree(hData);
      hData = GlobalAlloc(GMEM_MOVEABLE, nSize);
      if (hData == NULL) AfxThrowMemoryException();

      // initialize
      LPSTR lpData = (LPSTR)GlobalLock(hData);
      LPSTR lp;
      DWORD nCount = 0;
      CString strLine;
      int l, nLen;

      CListCtrl& ctrlList = GetListCtrl();
      int LineCount = ctrlList.GetItemCount();
      for (l = 0; l < LineCount; l++)
      {
	nLen = GetListLine(l, strLine);
	if (nCount + (DWORD)nLen >= nSize)  // ">=" for the last NUL
	{
	  nSize += BLKSIZE;
	  GlobalUnlock(hData);
	  hData = GlobalReAlloc(hData, nSize, GMEM_MOVEABLE);
	  if (hData == NULL)
	    AfxThrowMemoryException();
          lpData = (LPSTR)GlobalLock(hData);
        }
        lp = &lpData[nCount];
	memcpy(lp, strLine, nLen);
	nCount += nLen;
      }
      lpData[nCount++] = '\0';

      // set exact memory size
      GlobalUnlock(hData);
      hData = GlobalReAlloc(hData, nCount, GMEM_MOVEABLE);
      // give the handle to the clipboard
      SetClipboardData(CF_TEXT, hData);
    }
    catch (CMemoryException* e)
    {
      AfxMessageBox("Memory allocation error", MB_ICONEXCLAMATION);
      e->Delete();
    }
    CloseClipboard();
  }
}

void CDaoTableView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(GetListCtrl().GetItemCount() != 0);
}

/////////////////////////////////////////////////////////////////////////////
// CDaoTableView message handlers
