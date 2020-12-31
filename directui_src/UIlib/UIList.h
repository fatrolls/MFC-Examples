#if !defined(AFX_UILIST_H__20060218_929F_BDFF_55AA_0080AD509054__INCLUDED_)
#define AFX_UILIST_H__20060218_929F_BDFF_55AA_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////////////
//

class CListHeaderUI;
class CListFooterUI;


#define UILIST_MAX_COLUMNS 10

typedef struct tagTListInfoUI
{
   int nColumns;
   RECT rcColumn[UILIST_MAX_COLUMNS];
   UITYPE_COLOR Text;
   UITYPE_COLOR Background;
   UITYPE_COLOR SelText;
   UITYPE_COLOR SelBackground;
   UITYPE_COLOR HotText;
   UITYPE_COLOR HotBackground;
   bool bExpandable;
} TListInfoUI;


/////////////////////////////////////////////////////////////////////////////////////
//

class IListCallbackUI
{
public:
   virtual LPCTSTR GetItemText(CControlUI* pList, int iItem, int iSubItem) = 0;
   virtual int CompareItem(CControlUI* pList, CControlUI* pItem1, CControlUI* pItem2) = 0;
};

class IListOwnerUI
{
public:
   virtual int GetCurSel() const = 0;
   virtual bool SelectItem(int iIndex) = 0;
   virtual void Event(TEventUI& event) = 0;
};

class IListUI : public IListOwnerUI
{
public:
   virtual CListHeaderUI* GetHeader() const = 0;
   virtual CListFooterUI* GetFooter() const = 0; 
   virtual CContainerUI* GetList() const = 0;
   virtual const TListInfoUI* GetListInfo() const = 0;
   virtual IListCallbackUI* GetTextCallback() const = 0;
   virtual void SetTextCallback(IListCallbackUI* pCallback) = 0;
   virtual bool ExpandItem(int iIndex, bool bExpand = true) = 0;
   virtual int GetExpandedItem() const = 0;
};

class IListItemUI
{
public:
   virtual int GetIndex() const = 0;
   virtual void SetIndex(int iIndex) = 0;
   virtual void SetOwner(CControlUI* pOwner) = 0;
   virtual bool IsSelected() const = 0;
   virtual bool Select(bool bSelect = true) = 0;
   virtual bool IsExpanded() const = 0;
   virtual bool Expand(bool bExpand = true) = 0;
   virtual void DrawItem(HDC hDC, const RECT& rcItem, UINT uStyle) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CListElementUI : public CControlUI, public IListItemUI
{
public:
   CListElementUI();

   UINT GetControlFlags() const;
   LPVOID GetInterface(LPCTSTR pstrName);

   int GetIndex() const;
   void SetIndex(int iIndex);

   void SetOwner(CControlUI* pOwner);

   bool IsSelected() const;
   bool Select(bool bSelect = true);
   bool IsExpanded() const;
   bool Expand(bool bExpand = true);

   bool Activate();

   void Event(TEventUI& event);
   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   int m_iIndex;
   bool m_bSelected;
   IListOwnerUI* m_pOwner;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CListHeaderUI : public CHorizontalLayoutUI
{
public:
   CListHeaderUI();

   LPCTSTR GetClass() const;
   LPVOID GetInterface(LPCTSTR pstrName);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CListHeaderItemUI : public CControlUI
{
public:
   CListHeaderItemUI();

   LPCTSTR GetClass() const;
   UINT GetControlFlags() const;
   
   void SetText(LPCTSTR pstrText);

   void Event(TEventUI& event);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);

   void SetWidth(int cxWidth);
   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

   RECT GetThumbRect(RECT rc) const;

protected:
   int m_cxWidth;
   POINT ptLastMouse;
   UINT m_uDragState;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CListFooterUI : public CHorizontalLayoutUI
{
public:
   CListFooterUI();

   LPCTSTR GetClass() const;
   LPVOID GetInterface(LPCTSTR pstrName);

   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CListUI : public CVerticalLayoutUI, public IListUI
{
public:
   CListUI();

   LPCTSTR GetClass() const;
   UINT GetControlFlags() const;
   LPVOID GetInterface(LPCTSTR pstrName);

   int GetCurSel() const;
   bool SelectItem(int iIndex);

   CListHeaderUI* GetHeader() const;
   CListFooterUI* GetFooter() const;   
   CContainerUI* GetList() const;
   const TListInfoUI* GetListInfo() const;

   CControlUI* GetItem(int iIndex) const;
   int GetCount() const;
   bool Add(CControlUI* pControl);
   bool Remove(CControlUI* pControl);
   void RemoveAll();

   void EnsureVisible(int iIndex);
   void Scroll(int dx, int dy);

   void SetExpanding(bool bExpandable);

   int GetExpandedItem() const;
   bool ExpandItem(int iIndex, bool bExpand = true);

   void SetPos(RECT rc);
   void Event(TEventUI& event);
   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

   IListCallbackUI* GetTextCallback() const;
   void SetTextCallback(IListCallbackUI* pCallback);

protected:
   int m_iCurSel;
   int m_iExpandedItem;
   IListCallbackUI* m_pCallback;
   CVerticalLayoutUI* m_pList;
   CListHeaderUI* m_pHeader;
   CListFooterUI* m_pFooter;
   TListInfoUI m_ListInfo;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CListLabelElementUI : public CListElementUI
{
public:
   CListLabelElementUI();

   LPCTSTR GetClass() const;

   void SetWidth(int cxWidth);
   void SetTextStyle(UINT uStyle);

   void Event(TEventUI& event);
   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);

   void DrawItem(HDC hDC, const RECT& rcItem, UINT uStyle);

   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   int m_cxWidth;
   UINT m_uTextStyle;
   UINT m_uButtonState;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CListTextElementUI : public CListLabelElementUI
{
public:
   CListTextElementUI();

   LPCTSTR GetClass() const;
   UINT GetControlFlags() const;

   void SetOwner(CControlUI* pOwner);

   void Event(TEventUI& event);
   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);

   void DrawItem(HDC hDC, const RECT& rcItem, UINT uStyle);

protected:
   int m_cyItem;
   int m_nLinks;
   RECT m_rcLinks[8];
   IListUI* m_pOwner;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CListExpandElementUI : public CListTextElementUI, public IContainerUI
{
public:
   CListExpandElementUI();
   virtual ~CListExpandElementUI();

   LPCTSTR GetClass() const;

   void SetPos(RECT rc);
   void Event(TEventUI& event);
   SIZE EstimateSize(SIZE szAvailable);
   void DoPaint(HDC hDC, const RECT& rcPaint);

   void SetManager(CPaintManagerUI* pManager, CControlUI* pParent);
   CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

   CControlUI* GetItem(int iIndex) const;
   int GetCount() const;
   bool Add(CControlUI* pControl);
   bool Remove(CControlUI* pControl);
   void RemoveAll();

   bool IsExpanded() const;
   bool Expand(bool bExpand = true);

   void DrawItem(HDC hDC, const RECT& rcItem, UINT uStyle);

protected:
   bool m_bExpanded;
   int m_cyExpanded;
   CContainerUI* m_pContainer;
};


#endif // !defined(AFX_UILIST_H__20060218_929F_BDFF_55AA_0080AD509054__INCLUDED_)
