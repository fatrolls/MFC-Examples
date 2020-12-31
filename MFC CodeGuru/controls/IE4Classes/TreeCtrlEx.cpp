#include "stdafx.h"
#include "TreeCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlNode

const CTreeCursor& CTreeCursor::operator =(const CTreeCursor& posSrc)
{
  if (&posSrc != this)
  {
    m_hTreeItem = posSrc.m_hTreeItem;
    m_pTree = posSrc.m_pTree;
  }
  return *this;
}

CTreeCursor CTreeCursor::_Insert(LPCTSTR strItem,int nImageIndex,HTREEITEM hAfter)
{
  TVINSERTSTRUCT ins;
  ins.hParent = m_hTreeItem;
  ins.hInsertAfter = hAfter;
  ins.item.mask = TVIF_TEXT;
  ins.item.pszText = (LPTSTR) strItem;
  if (nImageIndex != -1)
  {
    ins.item.mask |= TVIF_IMAGE | TVIF_SELECTEDIMAGE;
    ins.item.iImage = nImageIndex;
    ins.item.iSelectedImage = nImageIndex;
  }
  return CTreeCursor(m_pTree->_InsertItem(&ins), m_pTree);
}

int CTreeCursor::GetImageID()
{
  TVITEM item;
  item.mask = TVIF_HANDLE | TVIF_IMAGE;
  item.hItem = m_hTreeItem;
  m_pTree->_GetItem(&item);
  return item.iImage;
}

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx

BOOL CTreeCtrlEx::GetCheck(HTREEITEM hItem) const
{
  ASSERT(::IsWindow(m_hWnd));
  TVITEM item;
  item.mask = TVIF_HANDLE | TVIF_STATE;
  item.hItem = hItem;
  item.stateMask = TVIS_STATEIMAGEMASK;
  VERIFY(::SendMessage(m_hWnd, TVM_GETITEM, 0, (LPARAM)&item));
  // Return zero if it's not checked, or nonzero otherwise.
  return ((BOOL)(item.state >> 12) -1);
}

BOOL CTreeCtrlEx::SetCheck(HTREEITEM hItem, BOOL fCheck)
{
  ASSERT(::IsWindow(m_hWnd));
  TVITEM item;
  item.mask = TVIF_HANDLE | TVIF_STATE;
  item.hItem = hItem;
  item.stateMask = TVIS_STATEIMAGEMASK;
  
  /*
  Since state images are one-based, 1 in this macro turns the check off, and
  2 turns it on.
  */
  item.state = INDEXTOSTATEIMAGEMASK((fCheck ? 2 : 1));
  
  return (BOOL)::SendMessage(m_hWnd, TVM_SETITEM, 0, (LPARAM)&item);
}

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CTreeCtrlEx, CTreeCtrl)

/////////////////////////////////////////////////////////////////////////////

