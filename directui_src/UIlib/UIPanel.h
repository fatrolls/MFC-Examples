#if !defined(AFX_UIPANEL_H__20060218_451A_298B_7A16_0080AD509054__INCLUDED_)
#define AFX_UIPANEL_H__20060218_451A_298B_7A16_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UILabel.h"


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CTaskPanelUI : public CVerticalLayoutUI
{
public:
   CTaskPanelUI();
   ~CTaskPanelUI();

   enum { FADE_TIMERID = 10 };
   enum { FADE_DELAY = 500UL };

   LPCTSTR GetClass() const;

   void Event(TEventUI& event);
   void SetPos(RECT rc);
   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);
   
protected:
   HBITMAP m_hFadeBitmap;
   DWORD m_dwFadeTick;
   RECT m_rcFade;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CNavigatorPanelUI : public CVerticalLayoutUI, public IListOwnerUI
{
public:
   CNavigatorPanelUI();

   LPCTSTR GetClass() const;   
   LPVOID GetInterface(LPCTSTR pstrName);

   bool Add(CControlUI* pControl);

   int GetCurSel() const;
   bool SelectItem(int iIndex);

   void Event(TEventUI& event);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);

protected:
   int m_iCurSel;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CNavigatorButtonUI : public CListElementUI
{
public:
   CNavigatorButtonUI();

   LPCTSTR GetClass() const;
   void Event(TEventUI& event);
   
   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);
   void DrawItem(HDC hDC, const RECT& rcItem, UINT uStyle);

   RECT GetButtonRect(RECT rc) const;

protected:
   UINT m_uButtonState;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CSearchTitlePanelUI : public CHorizontalLayoutUI
{
public:
   CSearchTitlePanelUI();

   LPCTSTR GetClass() const;

   void SetImage(int iIndex);

   void SetPos(RECT rc);
   void DoPaint(HDC hDC, const RECT& rcPaint);
   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   int m_iIconIndex;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CPaddingPanelUI : public CControlUI
{
public:
   CPaddingPanelUI();
   CPaddingPanelUI(int cx, int cy);

   LPCTSTR GetClass() const;

   void SetWidth(int cx);
   void SetHeight(int cy);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);
   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   SIZE m_cxyFixed;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CImagePanelUI : public CControlUI
{
public:
   CImagePanelUI();
   virtual ~CImagePanelUI();

   LPCTSTR GetClass() const;

   bool SetImage(LPCTSTR pstrImage);
   void SetWidth(int cx);
   void SetHeight(int cy);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);
   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   HBITMAP m_hBitmap;
   SIZE m_cxyFixed;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CTextPanelUI : public CLabelPanelUI
{
public:
   CTextPanelUI();

   LPCTSTR GetClass() const;
   UINT GetControlFlags() const;

   bool Activate();

   void SetTextColor(UITYPE_COLOR TextColor);
   void SetBkColor(UITYPE_COLOR BackColor);

   void Event(TEventUI& event);
   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);

   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   int m_nLinks;
   RECT m_rcLinks[8];
   UINT m_uButtonState;
   UITYPE_COLOR m_TextColor;
   UITYPE_COLOR m_BackColor;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CWarningPanelUI : public CTextPanelUI
{
public:
   CWarningPanelUI();

   LPCTSTR GetClass() const;

   void SetWarningType(UINT uType);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);  
   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   UITYPE_COLOR m_BackColor;
};


#endif // !defined(AFX_UIPANEL_H__20060218_451A_298B_7A16_0080AD509054__INCLUDED_)

