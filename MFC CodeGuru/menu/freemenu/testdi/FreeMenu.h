#ifndef __INCLUDE_CFREEMENU
#define __INCLUDE_CFREEMENU
class CMenuItemWnd;
class CFreeMenu
{
public:
	void ClearParent();
	CFreeMenu * m_parentMenu;
	void Disable();
	BOOL m_IsVisible;
	CMenuItemWnd * m_selfWnd;
	int m_goby; 
	int m_selected;

	int flags;
	CPoint MenuBeginPoint;
	CFreeMenu(UINT ID,
		      CPoint beginP,
			  CWnd *ParentWnd,
			  COLORREF BackGroundColor,
			  COLORREF EdgeLUColor,
			  COLORREF EdgeRDColor,
			  COLORREF TextColor,
			  CFont*,int ,CFreeMenu *p = NULL);
	CFreeMenu(CMenu *Menu,
		      CPoint beginP,
			  CWnd *ParentWnd,
			  COLORREF BackGroundColor,
			  COLORREF EdgeLUColor,
			  COLORREF EdgeRDColor,
			  COLORREF TextColor,
			  CFont*,int,CFreeMenu *p= NULL);
	~CFreeMenu();
	CMenu *m_Menu;
	CWnd *m_ParentWnd;
	CRect m_Rect;
	COLORREF m_BackGroundColor;
	COLORREF m_EdgeLUColor;
	COLORREF m_EdgeRDColor;
	COLORREF m_TextColor;
	CFont *m_font;
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void DrawMenu();
	UINT MeasureMenuID(CMenu *menu,CPoint CursorPosition);
	int MeasureMenuNo(CMenu *menu,CPoint CursorPosition);
	CRect GetItemRect(CMenu *menu,int item);
	CArray<CFreeMenu*,CFreeMenu*>SubMenu;
};
#endif