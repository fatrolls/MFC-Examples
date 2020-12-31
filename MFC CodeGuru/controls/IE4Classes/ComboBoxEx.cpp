#include "stdafx.h"
#include "ComboBoxEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxEx

CComboBoxEx::CComboBoxEx()
{
  // initialize common controls
  INITCOMMONCONTROLSEX icex;
  icex.dwSize = sizeof(icex);
  icex.dwICC = ICC_USEREX_CLASSES;
  VERIFY(InitCommonControlsEx(&icex));
}

BOOL CComboBoxEx::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
                         UINT nID)
{
  CWnd* pWnd = this;
  return pWnd->Create(WC_COMBOBOXEX, NULL, dwStyle, rect, pParentWnd, nID);
}

int CComboBoxEx::DeleteItem(int iIndex)
{
  ASSERT(::IsWindow(m_hWnd));
  return (int) ::SendMessage(m_hWnd, CBEM_DELETEITEM, (WPARAM) iIndex, 0);
}

BOOL CComboBoxEx::GetItem(COMBOBOXEXITEM* pCBItem)
{
  ASSERT(::IsWindow(m_hWnd));
  ASSERT(pCBItem != NULL);
  ASSERT(AfxIsValidAddress(pCBItem, sizeof(COMBOBOXEXITEM)));

  return (int) ::SendMessage(m_hWnd, CBEM_GETITEM, 0, (LPARAM) pCBItem);
}

int CComboBoxEx::InsertItem(const COMBOBOXEXITEM* pCBItem)
{
  ASSERT(::IsWindow(m_hWnd));
  ASSERT(pCBItem != NULL);
  ASSERT(AfxIsValidAddress(pCBItem, sizeof(COMBOBOXEXITEM), FALSE));

  return (int) ::SendMessage(m_hWnd, CBEM_INSERTITEM, 0, (LPARAM) pCBItem);
}

BOOL CComboBoxEx::SetItem(const COMBOBOXEXITEM* pCBItem)
{
  ASSERT(::IsWindow(m_hWnd));
  ASSERT(pCBItem != NULL);
  ASSERT(AfxIsValidAddress(pCBItem, sizeof(COMBOBOXEXITEM), FALSE));

  return (int) ::SendMessage(m_hWnd, CBEM_SETITEM, 0, (LPARAM) pCBItem);
}

CComboBoxEx::~CComboBoxEx()
{
  DestroyWindow();
}

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CComboBoxEx, CComboBox)

/////////////////////////////////////////////////////////////////////////////

