//*************************************************************************
// BCMenu.h : header file
// Version : 1.1
// Date : November 18, 1997
// Author : Brent Corkum
// 
// Portions of code supplied by Ben Ashley and Girish Bharadwaj.
// Bug Fixes: Stefan Kuhr 
//

#include <afxtempl.h>

#ifndef BCMenu_H
#define BCMenu_H

// BCMenuData class. Fill this class structure to define a single menu item:

class BCMenuData
{
public:
BCMenuData () {menuIconNormal=-1;xoffset=-1;bitmap=NULL;};
~BCMenuData ();
char menuText[80];
int xoffset;
int menuIconNormal;
UINT nFlags;
CImageList *bitmap;
};


typedef enum {Normal,TextOnly} HIGHLIGHTSTYLE;


class BCMenu : public CMenu  // Derived from CMenu
{
// Construction
public:
BCMenu(); 
// Attributes
protected:
CTypedPtrArray<CPtrArray, BCMenuData*> m_MenuList;  // Stores list of menu items 
// When loading an owner-drawn menu using a Resource, BCMenu must keep track of
// the popup menu's that it creates. Warning, this list *MUST* be destroyed
// last item first :)

CTypedPtrArray<CPtrArray, BCMenu*>  m_SubMenus;  // Stores list of sub-menus 
// Operations
public: 
// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CCustomMenu)
//}}AFX_VIRTUAL 
// Implementation
public:
  void SetBitmapBackground(COLORREF color);
  int AddBitmapToImageList(CImageList *list,UINT nResourceID);
  BOOL LoadFromToolBar(UINT nID,UINT nToolBar,int& xoffset);
  void InsertTabs(void);
  static LRESULT FindKeyboardShortcut(UINT nChar,UINT nFlags,CMenu *pMenu);
  static void UpdateMenu(CMenu *pmenu);
  void DrawCheckmark(CDC *pDC,int x,int y,COLORREF color);
  BCMenu * FindMenuOption(int nId,int& nLoc);
  BOOL GetMenuText(UINT id,CString &string);
  CImageList *checkmaps;
  int m_selectcheck;
  int m_unselectcheck;
  void LoadCheckmarkBitmap(int unselect,int select);
  void DitherBlt (HDC hdcDest, int nXDest, int nYDest, int nWidth, 
                   int nHeight, HBITMAP hbm, int nXSrc, int nYSrc);
virtual ~BCMenu();  // Virtual Destructor 
// Drawing: 
virtual void DrawItem( LPDRAWITEMSTRUCT);  // Draw an item
virtual void MeasureItem( LPMEASUREITEMSTRUCT );  // Measure an item

// Customizing:

void SetIconSize (int, int);  // Set icon size
virtual BOOL AppendODMenu(LPCTSTR lpstrText, 
UINT nFlags = MF_OWNERDRAW,
UINT nID = 0,
int nIconNormal = -1); // Owner-Drawn Append 
virtual BOOL ModifyODMenu(LPCTSTR lpstrText,
UINT  nID = 0,
int  nIconNormal = -1);  // Owner-Drawn Modify 
virtual BOOL NewODMenu(LPCTSTR lpstrText,UINT nID,UINT nFlags);
virtual BOOL LoadMenu(LPCTSTR lpszResourceName);  // Load a menu
virtual BOOL LoadMenu(int nResource);  // ... 
// Destoying:

virtual BOOL DestroyMenu();

// Generated message map functions
protected:
int m_iconX,m_iconY;
CImageList m_bitmapList;
COLORREF m_bitmapBackground;
//{{AFX_MSG(CCustomMenu)
// NOTE - the ClassWizard will add and remove member functions here.
//}}AFX_MSG
}; 
///////////////////////////////////////////////////////////////////////////
// 
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line. 
#endif // CCUSTOMMENU_H 

//*************************************************************************
