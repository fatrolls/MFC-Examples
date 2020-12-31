#ifndef _LBCTRL_H
#define _LBCTRL_H

// lbctrl.h

#pragma once

///////////////////////////////////////////////////////////////////
// Specify which features are compiled into this class.
#define CLISTBOXCTRL_ROWMODE
#define CLISTBOXCTRL_FIRSTCOLUMNMODE
#define CLISTBOXCTRL_ANYCOLUMNMODE
//#define CLISTBOXCTRL_SORTMODE
#define CLISTBOXCTRL_COLUMNWIDTHS
#define CLISTBOXCTRL_GRIDLINEMODE

///////////////////////////////////////////////////////////////////
// Don't need either of these in "Row Mode".
#if defined CLISTBOXCTRL_ROWMODE
#undef CLISTBOXCTRL_FIRSTCOLUMNMODE
#undef CLISTBOXCTRL_ANYCOLUMNMODE
#endif

///////////////////////////////////////////////////////////////////
// CListBoxCtrl class
class CListBoxCtrl : public CListCtrl
{
public:
   CListBoxCtrl();
   virtual ~CListBoxCtrl();

public:
   BOOL   IsItem(int nItem) const;
   BOOL   IsColumn(int nCol) const;
   int    GetSelectedItem(int nStartItem = -1) const;
   BOOL   SelectItem(int nItem);
   BOOL   SelectAll();

public:
   BOOL   GetModeFirstColumn() const
            { return m_bModeFirstColumn; }

   void   SetModeFirstColumn(BOOL b = TRUE);

   BOOL   GetModeAnyColumn() const
            { return m_bModeAnyColumn; }

   void   SetModeAnyColumn(BOOL b = TRUE);

   void   SetModeColumnWidths(const CString& s);

   void   SetModeGridLine(BOOL bHorz = TRUE, BOOL bVert = TRUE)
            { m_bModeGridLineHorz = bHorz;
            m_bModeGridLineVert = bVert; }

   BOOL   GetModeGridLineHorz() const
            { return m_bModeGridLineHorz; }

   BOOL   GetModeGridLineVert() const
            { return m_bModeGridLineVert; }

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CListBoxCtrl)
   protected:
   virtual void PreSubclassWindow();
   //}}AFX_VIRTUAL

   #if defined CLISTBOXCTRL_ROWMODE
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
   #endif

// Generated message map functions
protected:
   //{{AFX_MSG(CListBoxCtrl)
   afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnDestroy();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

#ifdef CLISTBOXCTRL_SORTMODE
   afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
   static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2,
                           LPARAM lParamSort);
#endif

protected:
   BOOL      m_bModeFirstColumn;
   BOOL      m_bModeAnyColumn;
   int       m_nColumnSort;
   BOOL      m_bSortAscending;
   CString   m_sColumnWidthsKey;
   BOOL      m_bModeGridLineHorz;
   BOOL      m_bModeGridLineVert;
};

#endif // #ifndef _LBCTRL_H
