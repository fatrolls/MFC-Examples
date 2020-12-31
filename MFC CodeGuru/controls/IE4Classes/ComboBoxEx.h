#ifndef __CBCTL_H__
#define __CBCTL_H__

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

#ifndef __AFXDISP_H__
  #include <afxdisp.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxEx

class CComboBoxEx : public CComboBox
{
  DECLARE_DYNAMIC(CComboBoxEx)

// Constructors
public:
  CComboBoxEx();
  BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Operations
  int DeleteItem(int iIndex);
  BOOL GetItem(COMBOBOXEXITEM* pCBItem);
  int InsertItem(const COMBOBOXEXITEM* pCBItem);
  BOOL SetItem(const COMBOBOXEXITEM* pCBItem);

// Attributes
  BOOL HasEditChanged()
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, CBEM_HASEDITCHANGED, 0, 0); }
  DWORD GetExtendedStyle() const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, CBEM_GETEXTENDEDSTYLE, 0, 0); }
  DWORD SetExtendedStyle(DWORD dwExMask, DWORD dwExStyles)
  { ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, CBEM_SETEXTENDEDSTYLE, (DWORD) dwExMask, (LPARAM) dwExStyles); }
  CEdit* GetEditCtrl()
  { ASSERT(::IsWindow(m_hWnd)); return (CEdit*) CEdit::FromHandle((HWND) ::SendMessage(m_hWnd, CBEM_GETEDITCONTROL, 0, 0)); }
  CComboBox* GetComboBoxCtrl()
  { ASSERT(::IsWindow(m_hWnd)); return (CComboBox*) CComboBox::FromHandle((HWND) ::SendMessage(m_hWnd, CBEM_GETCOMBOCONTROL, 0, 0)); }
  CImageList* GetImageList() const
  { ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, CBEM_GETIMAGELIST, 0, 0)); }
  CImageList* SetImageList(CImageList* pImageList)
  { ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, CBEM_SETIMAGELIST, 0, (LPARAM)pImageList->GetSafeHandle())); }

// Implementation
public:
  virtual ~CComboBoxEx();
};

#endif //__CBCTL_H__

/////////////////////////////////////////////////////////////////////////////
