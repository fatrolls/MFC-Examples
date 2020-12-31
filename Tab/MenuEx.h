//  MenuEx.h: interface for the CMenuEx class.
//  CMenuEx
//  原作者：lbird(郑恒)
//  修改:(querw)阙荣文
//  新增接口:
//  void LoadMenu();
//	BOOL ModifyMenuEx()	
//	BOOL AppendMenuEx()
//	BOOL RemoveMenuEx()
//	void LoadToolBar()
//  原接口:
//	void SetHighLightColor(COLORREF crColor)
//	void SetBackColor(COLORREF)
//	void SetTextColor(COLORREF)
//	void SetImageLeft(UINT idBmpLeft)
//									
//						2004.7.23
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUEX_H__FE677F6B_2315_11D7_8869_BB2B2A4F4D45__INCLUDED_)
#define AFX_MENUEX_H__FE677F6B_2315_11D7_8869_BB2B2A4F4D45__INCLUDED_
#include "afxtempl.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagMENUITEM
{
	CString		strText;				//菜单文本
	UINT		uID;					//菜单ID
	int			uIndex;					//菜单图标的编号
	int 		uPositionImageLeft;		//菜单左边位图的位置
	int			nSubMenuIndex;			//若是子菜单,表示在数组中的位置
	tagMENUITEM()
	{
		strText = ""; 
		uID = 0; 
		uIndex = -1; 
		uPositionImageLeft = -1; 
		nSubMenuIndex = -1;
		pImageList = NULL;
		pLeftBitmap = NULL;
	};
	CImageList *pImageList;
	CBitmap *pLeftBitmap;
}MENUITEM,*LPMENUITEM;


///////////////////////////////////////////
class CMenuEx : public CMenu  
{
	DECLARE_DYNAMIC( CMenuEx )	
public:
	//读入菜单,调用这个函数以后,菜单就有了自画风格
	BOOL LoadMenu(UINT uMenu);		
	
	//修改,添加,删除菜单项,自动指定为自画风格
	BOOL ModifyMenuEx(UINT nPosition, UINT nFlags, UINT nIDNewItem = 0, LPCTSTR lpszNewItem = NULL );	
	BOOL AppendMenuEx(UINT nFlags, UINT nIDNewItem = 0, LPCTSTR lpszNewItem = NULL );
	BOOL RemoveMenuEx(UINT nPosition, UINT nFlags);
	
	//读入工具条,可以指定一张位图以替代工具条资源的16色位图
	void LoadToolBar(UINT uToolBar,UINT uFace);
	
	//其他各种设置
	void SetHighLightColor(COLORREF crColor);
	void SetBackColor(COLORREF);
	void SetTextColor(COLORREF);
	void SetImageLeft(UINT idBmpLeft,BOOL bIsPopupMenu = FALSE);
	
	virtual void MeasureItem(LPMEASUREITEMSTRUCT  lpMIS);	
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	
	CMenuEx();
	virtual ~CMenuEx();

protected:
	int m_nSeparator;				//分割条的高度
	
	CSize m_szImageLeft;			//菜单左边为体的高度和宽度
	CBitmap m_bmpImageLeft;			//菜单左边的位图
	int m_nWidthLeftImage;			//菜单左边位图的宽度
	BOOL m_bHasImageLeft;			//是否有侧边位图
	
	COLORREF m_colMenu;				//菜单背景色
	COLORREF m_colTextSelected;		//菜单被选中时文本的颜色
	CImageList m_ImageList;			//菜单项位图列表
	COLORREF m_colText;				//菜单项没被选中时文本的颜色
	CSize m_szImage;				//菜单项位图的大小
	
	void	CalculateLeftImagePos(CMenu *pPopupMenu); //重新计算左边位图的位置(最底部的菜单项的位图标号是 0 )
	void	ChangeMenuStyle(CMenu* pMenu,HMENU hNewMenu);
	int		GetImageFromToolBar(UINT uToolBar,CToolBar *pToolBar,COLORREF	crMask=RGB(192,192,192),UINT uBitmap = 0);
	void	DrawImageLeft(CDC *pDC,CRect &rect,LPMENUITEM lpItem);
	void	TextMenu(CDC *pDC,CRect rect,CRect rcText,BOOL bSelected,BOOL bGrayed,LPMENUITEM lpItem);
	void	DrawMenuItemImage(CDC *pDC,CRect &rect,BOOL bSelected,BOOL bChecked,BOOL bGrayed,BOOL bHasImage,LPMENUITEM lpItem);
	void	GrayString(CDC *pDC,const CString &str,const CRect rect);

	CArray<CMenuEx *,CMenuEx *> m_SubMenuArr;
	CArray<MENUITEM *,MENUITEM *>m_MenuItemArr;
};

#endif // !defined(AFX_MENUEX_H__FE677F6B_2315_11D7_8869_BB2B2A4F4D45__INCLUDED_)
