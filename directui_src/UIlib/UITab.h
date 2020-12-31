#if !defined(AFX_UITAB_H__20060218_95D6_2F8B_4F7A_0080AD509054__INCLUDED_)
#define AFX_UITAB_H__20060218_95D6_2F8B_4F7A_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIlist.h"


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CTabFolderUI : public CContainerUI, public IListOwnerUI
{
public:
   CTabFolderUI();

   LPCTSTR GetClass() const;

   void Init();

   bool Add(CControlUI* pControl);

   int GetCurSel() const;
   bool SelectItem(int iIndex);

   void Event(TEventUI& Event);

   void SetPos(RECT rc);
   void DoPaint(HDC hDC, const RECT& rcPaint);

   void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
   int m_iCurSel;
   RECT m_rcPage;
   RECT m_rcClient;
   CControlUI* m_pCurPage;
   CStdValArray m_aTabAreas;
};


class UILIB_API CTabPageUI : public CContainerUI
{
public:
   CTabPageUI();
   LPCTSTR GetClass() const;

   bool Activate();
};



#endif // !defined(AFX_UITAB_H__20060218_95D6_2F8B_4F7A_0080AD509054__INCLUDED_)

