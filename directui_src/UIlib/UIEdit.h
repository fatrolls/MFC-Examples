#if !defined(AFX_UIEDIT_H__20060218_14AE_7A41_09A2_0080AD509054__INCLUDED_)
#define AFX_UIEDIT_H__20060218_14AE_7A41_09A2_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////////////
//

class CSingleLineEditWnd;


class UILIB_API CSingleLineEditUI : public CControlUI
{
friend CSingleLineEditWnd;
public:
   CSingleLineEditUI();

   LPCTSTR GetClass() const;
   UINT GetControlFlags() const;

   void SetText(LPCTSTR pstrText);

   void SetEditStyle(UINT uStyle);
   void SetReadOnly(bool bReadOnly);
   bool IsReadOnly() const;

   void Event(TEventUI& event);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);

protected:
   CSingleLineEditWnd* m_pWindow;

   bool m_bReadOnly;
   UINT m_uEditStyle;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CMultiLineEditWnd;


class UILIB_API CMultiLineEditUI : public CControlUI
{
friend CMultiLineEditWnd;
public:
   CMultiLineEditUI();
   ~CMultiLineEditUI();

   LPCTSTR GetClass() const;
   UINT GetControlFlags() const;

   void Init();
   
   CStdString GetText() const;
   void SetText(LPCTSTR pstrText);

   void SetEnabled(bool bEnabled);
   void SetVisible(bool bVisible);
   void SetReadOnly(bool bReadOnly);
   void SetFocus(bool bReadOnly);
   bool IsReadOnly() const;

   void Event(TEventUI& event);

   SIZE EstimateSize(SIZE szAvailable);
   void SetPos(RECT rc);
   void SetPos(int left, int top, int right, int bottom);
   void DoPaint(HDC hDC, const RECT& rcPaint);

protected:
   CMultiLineEditWnd* m_pWindow;
};


#endif // !defined(AFX_UIEDIT_H__20060218_14AE_7A41_09A2_0080AD509054__INCLUDED_)

