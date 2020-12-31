#if !defined(AFX_UIBUTTON_H__20060218_72F5_1B46_6300_0080AD509054__INCLUDED_)
#define AFX_UIBUTTON_H__20060218_72F5_1B46_6300_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CButtonUI : public CControlUI
{
public:
   CButtonUI();

   LPCTSTR GetClass() const;
   UINT GetControlFlags() const;

   bool Activate();

   void SetText(LPCTSTR pstrText);

   void SetWidth(int cxWidth);
   void SetPadding(int cx, int cy);

   void Event(TEventUI& event);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);
   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   int m_cxWidth;
   SIZE m_szPadding;
   UINT m_uTextStyle;
   UINT m_uButtonState;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API COptionUI : public CControlUI
{
public:
   COptionUI();

   LPCTSTR GetClass() const;
   UINT GetControlFlags() const;

   bool Activate();

   bool IsChecked() const;
   void SetCheck(bool bSelected);
   void SetWidth(int cxWidth);
   
   void Event(TEventUI& event);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);
   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   bool m_bSelected;
   UINT m_uStyle;
   UINT m_uButtonState;
   int m_cxWidth;
};


#endif // !defined(AFX_UIBUTTON_H__20060218_72F5_1B46_6300_0080AD509054__INCLUDED_)

