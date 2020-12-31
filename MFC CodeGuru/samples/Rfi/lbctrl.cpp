// lbctrl.cpp

#include "stdafx.h"
#include "lbctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////
// CListBoxCtrl

// Constructor.
CListBoxCtrl::CListBoxCtrl() :
   m_bModeFirstColumn(FALSE), m_bModeAnyColumn(FALSE),
   m_nColumnSort(-1), m_bSortAscending(TRUE),
   m_bModeGridLineHorz(FALSE), m_bModeGridLineVert(FALSE)
{
}

// Destructor.
/* virtual */ CListBoxCtrl::~CListBoxCtrl()
{
}

BEGIN_MESSAGE_MAP(CListBoxCtrl, CListCtrl)
   //{{AFX_MSG_MAP(CListBoxCtrl)
   ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
   ON_WM_DESTROY()
   //}}AFX_MSG_MAP

#ifdef CLISTBOXCTRL_SORTMODE
   ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
#endif

END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CListBoxCtrl helper functions

// Does the sent item exist?
BOOL CListBoxCtrl::IsItem(int nItem) const
{
   return GetItemCount() > nItem;
}

// Does the sent column exist?
BOOL CListBoxCtrl::IsColumn(int nCol) const
{
   LV_COLUMN lvc;
   memset(&lvc, 0, sizeof(lvc));
   lvc.mask = LVCF_WIDTH;
   return GetColumn(nCol, &lvc);
}

// Returns the first item that is selected by default.
int CListBoxCtrl::GetSelectedItem(int nStartItem /* = -1 */ ) const
{
   return GetNextItem(nStartItem, LVNI_SELECTED);
}

// Selects the sent item.
BOOL CListBoxCtrl::SelectItem(int nItem) 
{
   return SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);
}

// Selects all the items in the control.
BOOL CListBoxCtrl::SelectAll()
{
   BOOL bReturn(TRUE);

   for (int nItem = 0; IsItem(nItem); nItem++) 
      if (! SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED)) {
         bReturn = FALSE;
         break;
      }

   return bReturn;
}

///////////////////////////////////////////////////////////////////
// CListBoxCtrl mode functions

#if defined CLISTBOXCTRL_FIRSTCOLUMNMODE
void CListBoxCtrl::SetModeFirstColumn(BOOL b /* = TRUE */ )
{
   m_bModeFirstColumn = b;
}
#endif

#if defined CLISTBOXCTRL_ANYCOLUMNMODE
void CListBoxCtrl::SetModeAnyColumn(BOOL b /* = TRUE */ )
{
   m_bModeAnyColumn = b;
}
#endif

// Handle clicks.
void CListBoxCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
   UNUSED_ALWAYS(pNMHDR);

   // Get the mouse position in screen coords, convert to client.
   POINT pt;
   ::GetCursorPos(&pt);
   ScreenToClient(&pt);

   // Do we want clicks anywhere in the first column to count,
   // and if so was the mouse over the first column?
   #if defined CLISTBOXCTRL_FIRSTCOLUMNMODE
   if (GetModeFirstColumn()) {
      UINT uiFlags(0U);
      HitTest(pt, &uiFlags);

      if (IsColumn(0)) {
         int nWidth(GetColumnWidth(0));

         // If outside of text but in first column, force the
         // selection of this item (if on a valid line).
         if (! (uiFlags & LVHT_ONITEM)  &&  pt.x <= nWidth) {
            pt.x = 2;
            int nItem(HitTest(pt, &uiFlags));

            if (-1 != nItem  &&  LVHT_ONITEM & uiFlags) 
               SetItemState(nItem, LVIS_FOCUSED | LVIS_SELECTED,
                  LVIS_FOCUSED | LVIS_SELECTED);
         }
      }
   }
   #endif

   #if defined CLISTBOXCTRL_ANYCOLUMNMODE
   // A click anywhere on the item selects.
   if (GetModeAnyColumn()) {
      UINT uiFlags(0U);
      HitTest(pt, &uiFlags);
   
      if (! (uiFlags & LVHT_ONITEM)) {
         pt.x = 2;
         int nItem(HitTest(pt, &uiFlags));

         if (-1 != nItem  &&  LVHT_ONITEM & uiFlags)
            SetItemState(nItem, LVIS_FOCUSED | LVIS_SELECTED,
               LVIS_FOCUSED | LVIS_SELECTED);
      }
   }
   #endif

   *pResult = 0;
}

#if defined CLISTBOXCTRL_SORTMODE
// handle column clicks.
void CListBoxCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
{
   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;

   // If a different column is being sorted from the last time we
   // sorted, we always start off ascending.
   if (pNMListView->iSubItem != m_nColumnSort)
      m_bSortAscending = TRUE;
   else
      m_bSortAscending = ! m_bSortAscending;

   m_nColumnSort = pNMListView->iSubItem;

   // Now, the only way the CListCtrl can know how to sort is by
   // each item's LPARAM, so we give it the item number.
   for (int nItem = 0; IsItem(nItem); nItem++)
      SetItemData(nItem, nItem);

   // Call the sort routine.
   SortItems(CompareFunc, reinterpret_cast <DWORD> (this));
   *pResult = 0;
}
#endif

#if defined CLISTBOXCTRL_SORTMODE
// This is the function that the base CListCtrl code calls whenever
// it needs to compare two items.
/* static */ int CALLBACK CListBoxCtrl::CompareFunc(LPARAM lParam1,
                                             LPARAM lParam2,
                                             LPARAM lParamSort)
{
   CListBoxCtrl* pListCtrl =
      reinterpret_cast <CListBoxCtrl*> (lParamSort);

   LV_FINDINFO lvi;
   memset(&lvi, 0, sizeof(lvi));
   lvi.flags = LVFI_PARAM;

   lvi.lParam = lParam1;
   int nItem1(pListCtrl->FindItem(&lvi));

   lvi.lParam = lParam2;
   int nItem2(pListCtrl->FindItem(&lvi));

   CString s1(pListCtrl->GetItemText(nItem1,
      pListCtrl->m_nColumnSort));

   CString s2(pListCtrl->GetItemText(nItem2,
      pListCtrl->m_nColumnSort));

   int nReturn(s1.CompareNoCase(s2));

   if (! pListCtrl->m_bSortAscending)
      nReturn = -nReturn;

   return nReturn;
}
#endif

// Override that draws the entire row as selected, instead of just
//the text in the zeroth column.
#if defined CLISTBOXCTRL_ROWMODE
/* virtual */ void CListBoxCtrl::DrawItem(LPDRAWITEMSTRUCT 
                                        lpDrawItemStruct)
{
   // Get the display context for the control.
   CDC* pCDC = CDC::FromHandle(lpDrawItemStruct->hDC);

   // Use mask if there is one.
   UINT uiFlags(ILD_TRANSPARENT);

   // Check to see if this item is selected.
   if (lpDrawItemStruct->itemState & ODS_SELECTED) {
      pCDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
      pCDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
      uiFlags |= ILD_BLEND50;
   }
   else {
      pCDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
      pCDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
   }

   // Get the image list and draw.
   CImageList* plistImages = GetImageList(LVSIL_SMALL);

   // Get the item image to be displayed.
   LV_ITEM lvi;
   memset(&lvi, 0, sizeof(&lvi));
   lvi.mask = LVIF_IMAGE | LVIF_STATE;
   lvi.iItem = lpDrawItemStruct->itemID;
   GetItem(&lvi);

   // If valid, draw.
   if (plistImages) {
      CPoint ptAt(lpDrawItemStruct->rcItem.left,
         lpDrawItemStruct->rcItem.top);
	  if ( ! plistImages->Draw(pCDC, 0/*lvi.iImage*/, ptAt, uiFlags) ) {
		  int x = 0;
		  x++;
	  }
   }

   #if defined CLISTBOXCTRL_GRIDLINEMODE
   // Create the pen used to draw the gridlines.
   CPen pen(PS_SOLID, 0, ::GetSysColor(COLOR_WINDOWTEXT));
   CPen* penOld = pCDC->SelectObject(&pen);
   #endif

   // Now walk through columns and draw text.
   char szText[256];     // Increase this if you have longer text.
   LV_COLUMN lvc;
   memset(&lvc, 0, sizeof(lvc));
   lvc.mask = LVCF_WIDTH;

   for (int nColumn = 0; GetColumn(nColumn, &lvc); nColumn++) {
      CRect rTextClip;

      // First time.
      if (0 == nColumn) {
         rTextClip.left   = lpDrawItemStruct->rcItem.left +
            (plistImages ? 16 : 0);
         rTextClip.top    = lpDrawItemStruct->rcItem.top;
         rTextClip.right  = lpDrawItemStruct->rcItem.left + lvc.cx;
         rTextClip.bottom = lpDrawItemStruct->rcItem.bottom;
      }
      else {
         // Just "move" the rect to the right.
         rTextClip.left  = rTextClip.right;
         rTextClip.right = rTextClip.left + lvc.cx;
      }

      // Get the text.
      lvi.iItem = lpDrawItemStruct->itemID;
      lvi.mask = LVIF_TEXT;
      lvi.iSubItem = nColumn;
      lvi.pszText = szText;
      lvi.cchTextMax = sizeof(szText);
      GetItem(&lvi);

      // Add ellipses if necessary.
      int nTextCount(lstrlen(lvi.pszText));

      CSize sizText(pCDC->GetOutputTextExtent(lvi.pszText,
         nTextCount));

      // Make the clipping rectangle a little smaller for a gap
      // effect between columns.
      rTextClip.right -= 4;

      if (sizText.cx >= rTextClip.Width()) {

         // Make a shorter string, including "..." that fits.
         CSize sizEllipse = pCDC->GetOutputTextExtent("...", 3);

         // Now start dropping characters at the tail until width
         // is correct.
         while (sizText.cx+sizEllipse.cx > (rTextClip.Width())  &&
           nTextCount > 1) {
            lvi.pszText[--nTextCount] = 0;
            sizText = pCDC->GetOutputTextExtent(lvi.pszText,
               nTextCount);
         }

         // Ok, append "...".
         lvi.pszText[nTextCount] = '.';
         lvi.pszText[nTextCount + 1] = '.';
         lvi.pszText[nTextCount + 2] = '.';
         lvi.pszText[nTextCount + 3] = 0;
      }

      // Restore full rect.
      rTextClip.right += 4;

      // Print the text.
      pCDC->ExtTextOut(rTextClip.left + 2, rTextClip.top + 1,
         ETO_CLIPPED | ETO_OPAQUE, &rTextClip, lvi.pszText,
         lstrlen(lvi.pszText), NULL);

      #if defined CLISTBOXCTRL_GRIDLINEMODE
      // Draw the gridlines.
      if (GetModeGridLineHorz()) {
         pCDC->MoveTo(rTextClip.left + 1, rTextClip.bottom - 1);
         pCDC->LineTo(rTextClip.right - 1, rTextClip.bottom - 1);
      }

      if (GetModeGridLineVert()) {
         pCDC->MoveTo(rTextClip.right - 1, rTextClip.bottom - 1);
         pCDC->LineTo(rTextClip.right - 1, rTextClip.top);
      }
      #endif
   }

   // Reset colors if necessary.
   if (lpDrawItemStruct->itemState & ODS_SELECTED) {
      pCDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
      pCDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
   }

   // If focused draw focus rect.
   if (lpDrawItemStruct->itemState & ODS_FOCUS) {
      CRect rTextClip(lpDrawItemStruct->rcItem);
      rTextClip.left += (plistImages ? 16 : 0);
      pCDC->DrawFocusRect(&rTextClip);
   }

   // We must leave the display context as we found it.
   #if defined CLISTBOXCTRL_GRIDLINEMODE
   pCDC->SelectObject(penOld);
   #endif
}
#endif

// Fix color "bug".
/* virtual */ void CListBoxCtrl::PreSubclassWindow() 
{
   #if ! defined CLISTBOXCTRL_ROWMODE

   if ((GetTextBkColor() == CLR_NONE  ||
      GetTextBkColor() == CLR_DEFAULT)  &&
     ::GetSysColor(COLOR_WINDOW) == ::GetSysColor(COLOR_3DFACE)) {

      // If the current background is lighter than average, we use
      // white (unless it's already white - then use light gray).
      if (GetRValue(::GetSysColor(COLOR_3DFACE)) +
        GetGValue(::GetSysColor(COLOR_3DFACE)) +
        GetBValue(::GetSysColor(COLOR_3DFACE)) > (255 * 3 / 2)) {

         if (::GetSysColor(COLOR_3DFACE) == RGB(255,255,255))
            SetTextBkColor(RGB(192,192,192));
         else
            SetTextBkColor(RGB(255,255,255));
      }
      else {
         // Current background is darker than average.  Use dark
         // gray (unless it's already dark gray, then use black).
         if (::GetSysColor(COLOR_3DFACE) == RGB(83,83,83))
            SetTextBkColor(RGB(0,0,0));
         else
            SetTextBkColor(RGB(83,83,83));
      }
   }
   #endif

   // Call the base class member.
   CListCtrl::PreSubclassWindow();
}

#if defined CLISTBOXCTRL_COLUMNWIDTHS
// Call this from your view's OnInitialUpdate() method.  Pass it
// something like "Software\\MyCompany\\MyApp\\CustomerColWidths".
void CListBoxCtrl::SetModeColumnWidths(const CString& s)
{
   m_sColumnWidthsKey = s;
 
   // Be sure we really want to do this.
   if (! m_sColumnWidthsKey.IsEmpty()) {
      HKEY hKey(NULL);
      DWORD dwDisp(0L);

      // First open the key (if it's there).
      if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_CURRENT_USER,
        m_sColumnWidthsKey, NULL, KEY_READ, &hKey)) {

         // If key must there, open columns until you run out.
         LONG lnReturn(ERROR_SUCCESS);

         for (int nCol = 0; ERROR_SUCCESS == lnReturn; nCol++) {
            CString sValueName;
            sValueName.Format("Column%d", nCol);
            DWORD dwType(0L);
            DWORD dwData(0L);
            DWORD dwDataSize(sizeof(DWORD));
            BYTE* pData = reinterpret_cast<BYTE*> (&dwData);
            
            if (ERROR_SUCCESS == (lnReturn = ::RegQueryValueEx(
              hKey, sValueName, NULL, &dwType, pData,
              &dwDataSize))) 

               SetColumnWidth(nCol, dwData);
         }

         ::RegCloseKey(hKey);
         hKey = NULL;
      }
   }
}
#endif

// When the control is about to be destroyed, we write the column
// widths to the Registry key specified by the client.
void CListBoxCtrl::OnDestroy() 
{
   CListCtrl::OnDestroy();
   
   #if defined CLISTBOXCTRL_COLUMNWIDTHS

   if (! m_sColumnWidthsKey.IsEmpty()) {
      HKEY hKey(NULL);
      DWORD dwDisp(0L);

      ::RegCreateKeyEx(HKEY_CURRENT_USER, m_sColumnWidthsKey,
        NULL, "MyListCtrlClass", 0L, KEY_WRITE, NULL, &hKey,
        &dwDisp);

      for (int nCol = 0; IsColumn(nCol); nCol++) {
         CString sValueName;
         sValueName.Format("Column%d", nCol);
         int nData(GetColumnWidth(nCol));
         
         const BYTE* pData = 
            reinterpret_cast<const BYTE*> (&nData);

         ::RegSetValueEx(hKey, sValueName, NULL, REG_DWORD, pData,
            sizeof(DWORD));
      }

      ::RegCloseKey(hKey);
      hKey = NULL;
   }
   #endif
}
