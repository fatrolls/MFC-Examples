
#ifndef SKIN_MENU_H_
#define SKIN_MENU_H_
#pragma once

#include "SkinControlsDefine.h"

#include <afxtempl.h>
#include <afxpriv.h>

// Flagdefinitions 
#define MFT_TITLE       	0x0001
#define MFT_TOP_TITLE   	0x0000
#define MFT_SIDE_TITLE  	0x0002
#define MFT_GRADIENT    	0x0004
#define MFT_SUNKEN      	0x0008
#define MFT_LINE        	0x0010
#define MFT_ROUND       	0x0020
#define MFT_CENTER      	0x0040

// Additional flagdefinition for highlighting
#ifndef ODS_HOTLIGHT
#define ODS_HOTLIGHT        0x0040
#endif

#ifndef ODS_INACTIVE
#define ODS_INACTIVE        0x0080
#endif

// new define menustyles
#define ODS_SELECTED_OPEN   0x0800
#define ODS_RIGHTJUSTIFY    0x1000
#define ODS_WRAP            0x2000
#define ODS_HIDDEN          0x4000
#define ODS_DRAW_VERTICAL   0x8000

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuIcons menu icons for drawing

class SKIN_CONTROLS_EXPORT CSkinMenuIcons : public CObject
{
	DECLARE_DYNCREATE(CSkinMenuIcons)

public:
	CSkinMenuIcons();
	virtual ~CSkinMenuIcons();

public:
	BOOL GetIconSize(int* cx, int* cy);
	CSize GetIconSize();

	virtual int FindIndex(UINT nID);
	virtual void OnSysColorChange();

	virtual BOOL LoadToolBar(LPCTSTR lpszResourceName, HMODULE hInst);
	virtual BOOL LoadToolBar(WORD* pToolInfo, COLORREF crTransparent=CLR_NONE);
	virtual BOOL LoadToolBar(HBITMAP hBitmap, CSize size, UINT* pID, COLORREF crTransparent=CLR_NONE);

	virtual BOOL DoMatch(LPCTSTR lpszResourceName, HMODULE hInst);
	virtual BOOL DoMatch(WORD* pToolInfo, COLORREF crTransparent=CLR_NONE);
	virtual BOOL DoMatch(HBITMAP hBitmap, CSize size, UINT* pID);

	virtual BOOL LoadBitmap(int nWidth, int nHeight, LPCTSTR lpszResourceName, HMODULE hInst=NULL);

	//  virtual BOOL SetBlendImage();
	virtual int AddGloomIcon(HICON hIcon, int nIndex=-1);
	virtual int AddGrayIcon(HICON hIcon, int nIndex=-1);
	virtual BOOL MakeImages();

	void SetResourceName(LPCTSTR lpszResourceName);

	int AddRef();
	int Release();

public:
	LPCTSTR m_lpszResourceName;
	HMODULE m_hInst;
	HBITMAP m_hBitmap;
	int m_nColors;
	COLORREF m_crTransparent;

	CImageList m_IconsList;

	CArray<UINT,UINT&> m_IDs;
	DWORD m_dwRefCount;
};

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuBitmaps menu icons for drawing

class SKIN_CONTROLS_EXPORT CSkinMenuBitmaps : public CSkinMenuIcons
{
	DECLARE_DYNCREATE(CSkinMenuBitmaps)

public:
	CSkinMenuBitmaps();
	virtual ~CSkinMenuBitmaps();

public:
	int Add(UINT nID, COLORREF crTransparent=CLR_NONE);
	int Add(HICON hIcon, UINT nID=0);
	int Add(CBitmap* pBitmap, COLORREF crTransparent=CLR_NONE);

	virtual void OnSysColorChange();

	CArray<COLORREF,COLORREF&> m_TranspColors;
};

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuItemData menu item data for drawing

class SKIN_CONTROLS_EXPORT CSkinMenuItemData : public CObject
{
	DECLARE_DYNCREATE(CSkinMenuItemData)

public:
	CSkinMenuItemData();
	virtual ~CSkinMenuItemData();

public:
	// get the item text, 
	// hAccel=INVALID_HANDLE_VALUE = gets the default from the frame
	// hAccel=NULL disable accelerator support
	virtual CString GetString(HACCEL hAccel=NULL);
	virtual void SetString(LPCTSTR szMenuText);

public:
	CString m_szMenuText;

	UINT m_nTitleFlags;
	UINT m_nFlags;
	UINT m_nID;
	UINT m_nSyncFlag;

	CSkinMenuIcons* m_pMenuIcon;
	int m_nMenuIconOffset;

	void* m_pData;
};

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuItemDataTitle menu item data for drawing menu Title

class SKIN_CONTROLS_EXPORT CSkinMenuItemDataTitle : public CSkinMenuItemData
{
	DECLARE_DYNCREATE(CSkinMenuItemDataTitle)

public:
	CSkinMenuItemDataTitle();
	virtual ~CSkinMenuItemDataTitle();

public:
	COLORREF m_clrTitle;
	COLORREF m_clrLeft;
	COLORREF m_clrRight;

	CFont m_Font;
};

/////////////////////////////////////////////////////////////////////////////
// CSkinMenu the new menu class

class SKIN_CONTROLS_EXPORT CSkinMenu : public CMenu
{
	friend class CSkinMenuHook;
	friend class CSkinMenuIcons;

	DECLARE_DYNCREATE(CSkinMenu)

	// how seperators are handled when removing a menu (Tongzhe Cui)
	typedef enum {NONE, HEAD, TAIL, BOTH} ESeperator;

public:
	CSkinMenu(HMENU hParent=0); 
	virtual ~CSkinMenu();

	// Functions for loading and applying bitmaps to menus (see example application)
	virtual BOOL LoadMenu(HMENU hMenu);
	virtual BOOL LoadMenu(LPCTSTR lpszResourceName);
	virtual BOOL LoadMenu(int nResource);

	BOOL LoadToolBar(HBITMAP hBitmap, CSize size, UINT* pID, COLORREF crTransparent=CLR_NONE);
	BOOL LoadToolBar(WORD* pIconInfo, COLORREF crTransparent=CLR_NONE);
	BOOL LoadToolBar(LPCTSTR lpszResourceName, HMODULE hInst = NULL);
	BOOL LoadToolBar(UINT nToolBar, HMODULE hInst = NULL);
	BOOL LoadToolBars(const UINT *arID,int n, HMODULE hInst = NULL);
	BOOL LoadToolBar(UINT n16ToolBarID, UINT n256BitmapID, COLORREF transparentColor, HMODULE hInst = NULL);

	BOOL LoadFromToolBar(UINT nID,UINT nToolBar,int& xoffset);
	BOOL AddBitmapToImageList(CImageList *list,UINT nResourceID);

	static HBITMAP LoadSysColorBitmap(int nResourceId);
	// custom check mark bitmaps
	void LoadCheckmarkBitmap(int unselect, int select); 

	// functions for appending a menu option, use the AppendMenu call
	BOOL AppendMenu(UINT nFlags,UINT nIDNewItem=0,LPCTSTR lpszNewItem=NULL,int nIconNormal=-1);
	BOOL AppendMenu(UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CImageList *il,int xoffset);
	BOOL AppendMenu(UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CBitmap *bmp);

	BOOL AppendODMenu(LPCTSTR lpstrText, UINT nFlags = MF_OWNERDRAW, UINT nID = 0, int nIconNormal = -1);  
	BOOL AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID, CBitmap* pbmp);
	BOOL AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID, CImageList *il, int xoffset);
	BOOL AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID, CSkinMenuIcons* pIcons, int nIndex);

	// for appending a popup menu (see example application)
	CSkinMenu* AppendODPopupMenu(LPCTSTR lpstrText);

	// functions for inserting a menu option, use the InsertMenu call (see above define)
	BOOL InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem=0,LPCTSTR lpszNewItem=NULL,int nIconNormal=-1);
	BOOL InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CImageList *il,int xoffset);
	BOOL InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CBitmap *bmp);

	BOOL InsertODMenu(UINT nPosition,LPCTSTR lpstrText, UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1);  
	BOOL InsertODMenu(UINT nPosition,LPCTSTR lpstrText, UINT nFlags, UINT nID, CBitmap* pBmp);
	BOOL InsertODMenu(UINT nPosition,LPCTSTR lpstrText, UINT nFlags, UINT nID, CImageList *il,int xoffset);
	BOOL InsertODMenu(UINT nPosition,LPCTSTR lpstrText, UINT nFlags, UINT nID, CSkinMenuIcons* pIcons, int nIndex);

	// Same as ModifyMenu but replacement for CSkinMenu
	BOOL ModifyODMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem = 0,LPCTSTR lpszNewItem = NULL);
	BOOL ModifyODMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem, const CBitmap* pBmp);

	// functions for modifying a menu option, use the ModifyODMenu call (see above define)
	BOOL ModifyODMenu(LPCTSTR lpstrText, UINT nID=0, int nIconNormal=-1);
	BOOL ModifyODMenu(LPCTSTR lpstrText, UINT nID, CImageList *il, int xoffset);
	BOOL ModifyODMenu(LPCTSTR lpstrText, UINT nID, CSkinMenuIcons* pIcons, int nIndex);

	BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID,CBitmap *bmp);
	BOOL ModifyODMenu(LPCTSTR lpstrText,LPCTSTR OptionText,int nIconNormal);
	// use this method for adding a solid/hatched colored square beside a menu option
	// courtesy of Warren Stevens
	BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID,COLORREF fill,COLORREF border,int hatchstyle=-1);

	// for deleting and removing menu options
	BOOL  DeleteMenu(UINT uiId,UINT nFlags);
	BOOL  RemoveMenu(UINT uiId,UINT nFlags);
	int RemoveMenu(LPCTSTR pText, ESeperator sPos=CSkinMenu::NONE);

	// function for retrieving and setting a menu options text (use this function
	// because it is ownerdrawn)
	BOOL GetMenuText(UINT id,CString &string,UINT nFlags = MF_BYPOSITION);
	BOOL SetMenuText(UINT id,CString string, UINT nFlags = MF_BYPOSITION);

	// Getting a submenu from it's name or position
	CMenu* GetSubMenu (LPCTSTR lpszSubMenuName) const;
	CMenu* GetSubMenu (int nPos) const;
	int GetMenuPosition(LPCTSTR pText);

	// Destoying
	virtual BOOL DestroyMenu();

	// Drawing: 
	// Draw an item
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	// Measure an item  
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	// Draw title of the menu
	virtual void DrawTitle(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar);
	// Erase the Background of the menu
	virtual BOOL EraseBkgnd(HWND hWnd, HDC hDC);

	static COLORREF GetMenuBarColor2003();
	//static void GetMenuBarColor2003(COLORREF& color1, COLORREF& color2, BOOL bBackgroundColor = TRUE);
	static COLORREF GetMenuBarColorXP();
	static COLORREF GetMenuBarColor(HMENU hMenu=NULL);
	static COLORREF GetMenuColor(HMENU hMenu=NULL);

	static void SetMenuTitleFont(CFont* pFont);
	static void SetMenuTitleFont(LOGFONT* pLogFont);
	static LOGFONT GetMenuTitleFont();

	// Menutitle function
	BOOL SetMenuTitle(LPCTSTR pTitle, UINT nTitleFlags=MFT_TOP_TITLE, int nIconNormal = -1);
	BOOL SetMenuTitle(LPCTSTR pTitle, UINT nTitleFlags, CBitmap* pBmp);
	BOOL SetMenuTitle(LPCTSTR pTitle, UINT nTitleFlags, CImageList *pil, int xoffset);
	BOOL SetMenuTitle(LPCTSTR pTitle, UINT nTitleFlags, CSkinMenuIcons* pIcons, int nIndex);

	BOOL SetMenuTitleColor(COLORREF clrTitle=CLR_DEFAULT, COLORREF clrLeft=CLR_DEFAULT, COLORREF clrRight=CLR_DEFAULT);
	BOOL RemoveMenuTitle();

	// Function to set how disabled items are drawn 
	//(mode=FALSE means they are not drawn selected)
	static BOOL SetSelectDisableMode(BOOL mode);
	static BOOL GetSelectDisableMode();

	// Function to set how icons were drawn in normal mode 
	//(enable=TRUE means they are drawn blended)
	static BOOL SetXpBlending(BOOL bEnable=TRUE);
	static BOOL GetXpBlending();

	// added SetGloomFactor() and GetGloomFactor() so that the glooming can be done in a more or less subtle way
	static int SetGloomFactor(int nGloomFactor);
	static int GetGloomFactor();

	// Function to set how default menu border were drawn
	//(enable=TRUE means that all menu in the application has the same border)
	static BOOL SetNewMenuBorderAllMenu(BOOL bEnable=TRUE);
	static BOOL GetNewMenuBorderAllMenu();

	static void OnSysColorChange();

	// Static functions used for handling menu's in the mainframe
	static LRESULT FindKeyboardShortcut(UINT nChar,UINT nFlags,CMenu *pMenu);
	static BOOL OnMeasureItem(const MSG* pMsg);
	static void OnInitMenuPopup(HWND hWnd, CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

	// Helperfunction to find the menu to the item
	static CMenu* FindPopupMenuFromID(CMenu* pMenu, UINT nID);
	static CMenu* FindPopupMenuFromID(HMENU hMenu, UINT nID);

	static CMenu* FindPopupMenuFromIDData(CMenu* pMenu, UINT nID, ULONG_PTR pData);
	static CMenu* FindPopupMenuFromIDData(HMENU hMenu, UINT nID, ULONG_PTR pData);

	virtual void OnInitMenuPopup();
	virtual BOOL OnUnInitPopupMenu();

	// Customizing:
	// Set icon size
	void SetIconSize(int width, int height);
	CSize GetIconSize();

	// set the color in the bitmaps that is the background transparent color
	COLORREF SetBitmapBackground(COLORREF newColor);
	COLORREF GetBitmapBackground(); 

	// Return the last itemrect from a menubaritem.
	CRect GetLastActiveMenuRect();
	void SetLastMenuRect(HDC hDC, LPRECT pRect);
	void SetLastMenuRect(LPRECT pRect);

	HMENU GetParent();
	BOOL IsPopup();
	BOOL SetPopup(BOOL bIsPopup=TRUE);

	BOOL SetItemData(UINT uiId, DWORD_PTR dwItemData, BOOL fByPos = FALSE);
	BOOL SetItemDataPtr(UINT uiId, void* pItemData, BOOL fByPos = FALSE);

	DWORD_PTR GetItemData(UINT uiId, BOOL fByPos = FALSE) const;
	void* GetItemDataPtr(UINT uiId, BOOL fByPos = FALSE) const;

	BOOL SetMenuData(DWORD_PTR dwMenuData);
	BOOL SetMenuDataPtr(void* pMenuData);

	DWORD_PTR GetMenuData() const;
	void* GetMenuDataPtr() const;

	// enable or disable the global accelerator drawing
	static BOOL SetAcceleratorsDraw (BOOL bDraw);
	static BOOL GetAcceleratorsDraw ();

	// Set Alphablending of the menu only win2000 /XP/2003
	// When bAlpha is 255, the window is opaque
	static BYTE SetAlpha(BYTE bAlpha);
	static BYTE GetAlpha();

	// INVALID_HANDLE_VALUE = Draw default frame's accel. NULL = Off
	HACCEL SetAccelerator (HACCEL hAccel);
	HACCEL GetAccelerator ();

	// can set icons from a global saved icons-list
	DWORD SetMenuIcons(CSkinMenuIcons* pMenuIcons);

	// Miscellaneous Protected Member functions
protected:
	CSkinMenuIcons* GetMenuIcon(int &nIndex, UINT nID, CImageList *pil, int xoffset);
	CSkinMenuIcons* GetMenuIcon(int &nIndex, int nID);
	CSkinMenuIcons* GetMenuIcon(int &nIndex, CBitmap* pBmp);

	CSkinMenuIcons* GetToolbarIcons(UINT nToolBar, HMODULE hInst=NULL);

	BOOL Replace(UINT nID, UINT nNewID);

	static BOOL IsNewShell();
	BOOL IsMenuBar(HMENU hMenu=NULL);

	CSkinMenuItemData* FindMenuItem(UINT nID);
	CSkinMenu* FindMenuOption(int nId, int& nLoc);
	CSkinMenu* FindMenuOption(LPCTSTR lpstrText, int& nLoc);

	CSkinMenu* FindAnotherMenuOption(int nId, int& nLoc, CArray<CSkinMenu*,CSkinMenu*>&newSubs, CArray<int,int&>&newLocs);

	CSkinMenuItemData* NewODMenu(UINT pos, UINT nFlags, UINT nID, LPCTSTR string);
	CSkinMenuItemDataTitle* GetMemuItemDataTitle();

	void SynchronizeMenu();
	void InitializeMenuList(int value);
	void DeleteMenuList();

	CSkinMenuItemData* FindMenuList(UINT nID);
	CSkinMenuItemData* CheckMenuItemData(ULONG_PTR nItemData) const;

	void DrawSpecial_WinXP(CDC* pDC, LPCRECT pRect, UINT nID, DWORD dwStyle);

	void DrawSpecialCharStyle(CDC* pDC, LPCRECT pRect, TCHAR Sign, DWORD dwStyle);
	void DrawSpecialChar(CDC* pDC, LPCRECT pRect, TCHAR Sign, BOOL bBold);

	void DrawMenuTitle(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar);

	void MeasureItem_WinXP( LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenuBar); 
	void DrawItem_WinXP (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar);

	void ColorBitmap(CDC* pDC, CBitmap& bmp, CSize size, COLORREF fill, COLORREF border, int hatchstyle=-1);

	static BOOL OnInitMenuWnd(HWND hWnd);
	static BOOL OnUninitMenuWnd(HWND hWnd);
	static BOOL OnDrawBorder(HWND hWnd, HDC hDC, BOOL bOnlyBorder=FALSE);
	static void* SetScreenBitmap(HWND hWnd, HDC hDC);
	static void DrawFrame(CDC* pDC, CRect rectOuter, CRect rectInner, COLORREF crBorder);
	static void DrawShade(HWND hWnd, HDC hDC, CPoint screen);
	static BOOL OnCalcFrameRect(HWND hWnd,LPRECT pRect);

	// Member Variables
public:
	static DWORD m_dwLastActiveItem;

protected: 
	// Stores list of menu items
	CTypedPtrArray<CPtrArray, CSkinMenuItemData*> m_MenuItemList;   
	// When loading an owner-drawn menu using a Resource, CSkinMenu must keep track of
	// the popup menu's that it creates. Warning, this list *MUST* be destroyed
	// last item first :)
	// Stores list of sub-menus
	CTypedPtrArray<CPtrArray, HMENU>  m_SubMenus;

	static BOOL m_bEnableXpBlending;
	static BOOL m_bNewMenuBorderAllMenu;
	static BOOL m_bSelectDisable;
	// added gloom factor
	static int m_nGloomFactor;
	//static CSkinMenuTheme* m_pActMenuDrawing;
	static LOGFONT m_MenuTitleFont;
	static CTypedPtrList<CPtrList, CSkinMenuIcons*>* m_pSharedMenuIcons;
	static BOOL m_bDrawAccelerators;
	static BYTE m_bAlpha;

	int m_iconX;
	int m_iconY;

	HWND m_hTempOwner;
	COLORREF m_bitmapBackground;
	CImageList* m_checkmaps;
	BOOL m_checkmapsshare;
	int m_selectcheck;
	int m_unselectcheck;
	BOOL m_bDynIcons;
	HMENU m_hParentMenu;
	BOOL m_bIsPopupMenu;
	CRect m_LastActiveMenuRect;
	DWORD m_dwOpenMenu;
	void* m_pData;
	HACCEL  m_hAccelToDraw;
};

#define  SKIN_MENU_DIALOG_SUBCLASS     1
#define  SKIN_MENU_DIALOG_SYSTEM_MENU  2
#define  SKIN_MENU_DEFAULT_BORDER      4
#define  SKIN_MENU_CHANGE_MENU_STYLE   8

#endif 
