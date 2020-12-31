#if !defined(AFX_QUICKLIST_H__92CE873E_DD8F_11D8_B14D_002018574596__INCLUDED_)
#define AFX_QUICKLIST_H__92CE873E_DD8F_11D8_B14D_002018574596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuickList window

/*
	CQuickList is an owner draw virtual list. Useful to create 
	a complex large list without using a lot of memory.

	Version 1.01 - 22 Jan 2006
	Fixed problem when LVS_EX_HEADERDRAGDROP was used.


	Version 1.0 - 10 Sep 2004
	Solved the "hot item" problem in Windows XP. Added support 
	for themes. Added message when user right clicks on the 
	column header. 


	Version 0.9 - 28 Aug 2004
	First version, stable but with some minor problems.

	Get the latest version at http://www.codeproject.com/listctrl/quicklist.asp

	/PEK


	Credits
	Hans Dietrich, "XListCtrl - A custom-draw list control with subitem formatting"
	http://www.codeproject.com/listctrl/xlistctrl.asp

  	Michael Dunn, "Neat Stuff to do in List Controls Using Custom Draw"
	http://www.codeproject.com/listctrl/lvcustomdraw.asp

	Allan Nielsen, "SuperGrid - Yet Another listview control"
	http://www.codeproject.com/listctrl/supergrid.asp

	Lee Nowotny, "Easy Navigation Through an Editable List View"
	http://www.codeproject.com/listctrl/listeditor.asp

	Craig Henderson, "Time to Complete Progress Control"
	http://www.codeproject.com/miscctrl/progresstimetocomplete.asp

  */
/*
You could define one or several of the following, if
you don't use the specific feature:

#define	QUICKLIST_NOIMAGE			//No image support
#define	QUICKLIST_NOBUTTON			//No button support
#define	QUICKLIST_NOTEXTSTYLE		//No text style support (bold, italic, position)
#define	QUICKLIST_NOEMPTYMESSAGE	//No support for empty message
#define	QUICKLIST_NOPROGRESSBAR		//No progress bar support
#define QUICKLIST_NOKEYFIND			//No support for LVN_ODFINDITEM message (but you might implement this by yourself)
#define QUICKLIST_NONAVIGATION		//No support for column navigation
#define QUICKLIST_NOEDIT			//No support for editing items
#define	QUICKLIST_NOCOLORS			//Default colors will be used
#define	QUICKLIST_NOTOOLTIP			//No support for tool tips.
#define	QUICKLIST_NOXPTHEME			//No support themes in XP.
*/


//This message is sent then the list needs data
//WPARAM: Handle to list	LPARAM: Pointer to CListItemData
#define WM_QUICKLIST_GETLISTITEMDATA	(WM_USER + 1979)

//This is sent when navigation column is changing
//WPARAM: Handle to list	LPARAM: Pointer to CNavigationTest
#define WM_QUICKLIST_NAVIGATIONTEST		(WM_USER + 1980)

//This is when user click on the list
//WPARAM: Handle to list	LPARAM: Pointer to CListHitInfo
#define WM_QUICKLIST_CLICK				(WM_USER + 1981)

//Send when the user right click on a column
//WPARAM: Handle to list	LPARAM: Pointer to CHeaderRightClick
#define WM_QUICKLIST_HEADERRIGHTCLICK	(WM_USER + 1982)

//This is sent when edit box is losing focus, and when
//edit box doesn't closed automaticly when losing focus
//WPARAM: Handle to edit box LPARAM: 0
#define WM_QUICKLIST_EDITINGLOSTFOCUS	(WM_USER + 1983)



#define KEYFIND_CURRENTCOLUMN -1
#define KEYFIND_DISABLED	  -2

//Use these color if you want to draw with the default color or transparent
#define DEFAULTCOLOR		CLR_DEFAULT
#define TRANSPARENTCOLOR	CLR_NONE

#ifndef QUICKLIST_NOEDIT
	#include "QuickEdit.h"
	class CQuickEdit;
#endif

#ifndef QUICKLIST_NOXPTHEME
	#include "theme.h"
#endif

class CQuickList : public CListCtrl
{
// Construction
public:
	CQuickList();
	virtual ~CQuickList();

	//See definitions after this class
	class CListItemData;
	class CNavigationTest;
	class CListHitInfo;
	class CHeaderRightClick;

// Attributes
public:

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuickList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//Get the rect of specific items
	bool GetCheckboxRect(const int item, const int subitem, CRect& rect, bool checkOnly);
	bool GetCheckboxRect(CQuickList::CListItemData& id, CRect& rect, bool checkOnly);

	bool GetImageRect(const int item, const int subitem, CRect& rect, bool imageOnly);
	bool GetImageRect(CQuickList::CListItemData& id, CRect& rect, bool imageOnly);

	bool GetTextRect(const int item, const int subitem, CRect& rect);
	bool GetTextRect(CQuickList::CListItemData& id, CRect& rect);

	bool GetProgressRect(const int item, const int subitem, CRect& rect, bool interior);
	bool GetProgressRect(CQuickList::CListItemData& id, CRect& rect, bool interior);

	//Redraw images in a column
	void RedrawImages(const int topitem, const int bottomitem, const int column, BOOL erase=FALSE);

	//Redraw check boxs images in a column
	void RedrawCheckBoxs(const int topitem, const int bottomitem, const int column, BOOL erase=FALSE);

	//Redraw text/progressbar in a column
	void RedrawText(const int topitem, const int bottomitem, const int column, BOOL erase=FALSE);

	//Redraw subitems in a column
	void RedrawSubitems(const int topitem, const int bottomitem, const int column, BOOL erase=FALSE);

	//Enable/Disable column navigation with this function. It is on by default.
	void EnableColumnNavigation(const bool enable);

	//Is column navigation on?
	bool IsColumnNavigationOn() const;

	//Set which column the navigation column is
	void SetNavigationColumn(const int column);

	//Get navigation column
	int  GetNavigationColumn() const;

	//Set start edit events
	void SetEditOnEnter(const bool edit);
	void SetEditOnF2(const bool edit);
	void SetEditOnDblclk(const bool edit);
	void SetEditOnWriting(const bool edit);

	//Return true if point is on an item. "item" and "subitem" shows which item the point is on.
	//If you want to now if the point is on a check box and/or image use the last two parameters.
	bool HitTest(const POINT& point, CListHitInfo &info);
	bool HitTest(const POINT& point, int& item, int& subitem, bool* onCheck=NULL, bool* onImage=NULL);
	
	//Set which column to use to make it possible to naviaget by writing
	void SetKeyfindColumn(const int col=KEYFIND_DISABLED);

	//Start/stop editing
	CEdit* EditSubItem (int Item, int Column, LPCTSTR addToEnd=NULL);
	void StopEdit(bool cancel=false);
	
	//Return which key was pressed when last editing was finished.
	//Possible values: 0, (no key) VK_RETURN or VK_ESCAPE
	UINT GetLastEndEditKey() const;

	//Edit box is closing when losing focus. You can change this.
	//If the edit box should close when losing focus, the parent will
	//recieve WM_QUICKLIST_EDITINGLOSTFOCUS when the box is losing focus.
	void SetEndEditOnLostFocus(bool autoend = true);
	bool GetEndEditOnLostFocus() const;

	//Get edit box. May be NULL.
	CEdit* GetEditBox() const;

	//  This doesn't work (the returned image is instable/transparent): 
	// CImageList* CreateDragImageEx(const int nItem, const int nSubItem);

#ifndef QUICKLIST_NOEMPTYMESSAGE
	//Set the message that will be shown if the list is empty
	void SetEmptyMessage(UINT ID);
	void SetEmptyMessage(const CString& message);
#endif

	//Return true if an item is selected. NOTE: subitems (>0) is never selected if not full row selection is activated.
	bool IsSelected(const int item, const int subitem);

#ifndef QUICKLIST_NOXPTHEME
	void SetThemeManager(CTheme* theme=NULL);
#endif
	
	int GetItemInFocus();

	// Generated message map functions
protected:
	afx_msg void OnLvnHotTrack(NMHDR *pNMHDR, LRESULT *pResult);
	
	//{{AFX_MSG(CQuickList)
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnClickEx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnDblClickEx(NMHDR* pNMHDR, LRESULT* pResult);
	
#ifndef QUICKLIST_NOKEYFIND
	//Is called when user pressing on keys to find an item. 
	afx_msg BOOL OnOdfinditem(NMHDR* pNMHDR, LRESULT* pResult);
	int m_keyFindColumn;
#endif

#ifndef QUICKLIST_NOTOOLTIP
	afx_msg BOOL OnToolTipText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	virtual int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
#endif

#ifndef QUICKLIST_NOEDIT
	void OnEndEdit(const int item, const int subitem, const CString text, bool bCancel, UINT endkey);
	
	friend CQuickEdit;
	CQuickEdit *m_edit;

	bool m_editOnEnter;
	bool m_editOnF2;
	bool m_editOnDblclk;
	bool m_editOnWriting;
	bool m_editEndOnLostFocus;
	
	UINT m_editLastEndKey;
#endif

#ifndef QUICKLIST_NONAVIGATION
	bool m_enableNavigation;
	int m_navigationColumn;
#endif

#ifndef QUICKLIST_NOXPTHEME
	CTheme* m_theme;
#endif
	//Fill a rect with a solid color.
	inline void FillSolidRect(CDC* pDC, const RECT& rect, const COLORREF color);

	//Try to navigato to a column. Ask parent first
	void TryNavigate(const int newcol);

	//Make a column visible
	void MakeColumnVisible(int nCol);

	//Draw functions
	void DrawItem(int item, int subitem, CDC* pDC);

	void DrawImage(	CQuickList::CListItemData& id,
					CDC* pDC );

	void DrawText(		CQuickList::CListItemData& id,
						CDC* pDC);
	
	void DrawButton(	CQuickList::CListItemData& id,
						CDC* pDC);

	void DrawProgressBar(	CQuickList::CListItemData& id,
							CDC* pDC);

	//Redraw some of a subitem
	void RedrawSubitems(int topitem, int bottomitem, int column, int part, BOOL erase);

	//Get how wide the bar in the progress bar should be
	int GetBarSize(const CQuickList::CListItemData& id, const CRect& rect) const;

	//Return true if full row select is activated
	bool FullRowSelect();

	//Get the color to use to draw text or background.
	COLORREF GetTextColor(const CQuickList::CListItemData& id, const bool forceNoSelection=false, const bool forceSelection=false);
	COLORREF GetBackColor(const CQuickList::CListItemData& id, const bool forceNoSelection=false);


	//Get the rect where a specific item should be drawn 
	BOOL GetSubItemRect(int iItem, int iSubItem, int nArea, CRect& rect);
	

#ifndef QUICKLIST_NOEMPTYMESSAGE	
	//The message that is drawn if list is empty
	CString m_emptyMessage;
#endif

	//Returns information about a specific item (calling parent to get information)
	virtual CQuickList::CListItemData& GetItemData(const int item, const int subitem);
	
	//Used by GetItemData. Don't use this directly
	CListItemData* m_lastget;

	//Returns DT_CENTER, DT_LEFT or DT_RIGHT
	UINT GetTextJustify(const int header);

	//Make sure that top and bottom is inside visible area
	//Return false in everything is outside visible area
	bool MakeInside(int& top, int &bottom);	

	DECLARE_MESSAGE_MAP()
};

//This structure is used to get information about an item.
class CQuickList::CListItemData
{
public:
	CListItemData();
	
	//Some obvius functions
	int GetItem() const;
	int GetSubItem() const;
	bool IsSelected() const;
	bool IsHot() const;
	
	//The item text
	CString m_text;

#ifndef QUICKLIST_NOTOOLTIP
	//Tool tip text. Note: Don't forget to call EnableToolTips()
	//to enable tool tips. 
	CString m_tooltip;
#endif

	//Set this to true if you don't want to draw a selection mark
	//even if this item is selected.
	//Default value: false
	bool m_noSelection;
	
	//Set this to true if the item is available for editing
	//Default value: false
#ifndef QUICKLIST_NOEDIT
	bool m_allowEdit;
#endif
	
#ifndef QUICKLIST_NOTEXTSTYLE 
	//Information about which text style that should be used.
	struct CListTextStyle
	{
		//Default value: false
		bool m_bold;

		//Default value: false
		bool m_italic;

		//Default value: 
		// DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS 
		//See CDC:DrawText in MSDN
		UINT m_textPosition; 
	} m_textStyle;
#endif
	
#ifndef QUICKLIST_NOIMAGE
	//Information about the image
	struct CListImage
	{
		//The image position in the image list.
		//-1 if no image.
		//Default value: -1
		int m_imageID;

		//The image list where the image is.
		//Default value: A pointer to the image list in the list
		//control that is used small images (LVSIL_SMALL)
		CImageList* m_imageList;

		//Set true if you don't want to draw selection mark if
		//the item is selection
		//Default value: true
		bool m_noSelection;

		//Center the image. Useful if no text.
		//Default value: false;
		bool m_center;

		//Blend if the image is selected. Use ILD_BLEND25 or 
		//ILD_BLEND50, or 0 if you don't want to use this feature.
		//Default value: ILD_BLEND25
		int m_blend;

	} m_image;
#endif
	
#ifndef QUICKLIST_NOBUTTON
	//Information about the button
	struct CListButton
	{
		//The style to use to draw the control.
		//Default value: DFCS_BUTTONCHECK
		//Use DFCS_CHECKED to draw the check mark.
		//Use DFCS_BUTTONRADIO for radio button, DFCS_BUTTONPUSH
		//for push button.
		//See CDC::DrawFrameControl for details.
		int m_style; 

		//If you want to draw a button, set this to true
		//Default value: false
		bool m_draw;

		//Center the check box is the column. Useful if no text
		//Default value: false
		bool m_center;

		//Set this to true if you don't want to draw selection
		//mark under the control.
		//Default value: true
		bool m_noSelection;
		
	} m_button;
#endif
	
#ifndef QUICKLIST_NOPROGRESSBAR
	//Information about the progress bar
	struct CListProgressbar
	{
		//Note: The m_text member specifies the text in
		//the progress bar

		//The max value of progress bar. Use -1 to disable
		//progress bar.The min value is supposed to be 0.
		//Default value: -1
		int m_maxvalue;

		//The value the progress bar has. The width of the 
		//progress bar is calculated with use m_value and 
		//m_maxvalue.
		//Default value: 0
		int m_value;

		//The color the progress bar should be drawn with. 
		//Default value: DEFAULTCOLOR
		COLORREF m_fillColor;

		//The color of the text on the progress bar
		//Default value: DEFAULTCOLOR
		COLORREF m_fillTextColor;

		//How to draw the edge. Use 0 for no edge.
		//See CDC::DrawEdge for different styles.
		//Default value: EDGE_SUNKEN
		UINT m_edge;
	} m_progressBar;
#endif

#ifndef QUICKLIST_NOCOLORS
	//Information about the colors to use
	struct CListColors
	{
		//Default value for all: DEFAULTCOLOR
		COLORREF m_textColor;
		COLORREF m_backColor;
		COLORREF m_hotTextColor;
		COLORREF m_selectedTextColor;
		COLORREF m_selectedBackColor;
		COLORREF m_selectedBackColorNoFocus;

		//These colors are used to draw selected items 
		//in the "navigation column"
		#ifndef QUICKLIST_NONAVIGATION
		COLORREF m_navigatedTextColor;
		COLORREF m_navigatedBackColor;
		#endif
	} m_colors;			
#endif

	private:
		friend CQuickList;
		
		void Reset();
		int m_item;
		int m_subitem;
		bool m_isSelected;	
		bool m_isHot;
};


class CQuickList::CNavigationTest
{
public:
	int m_previousColumn;
	int m_newColumn;
	bool m_allowChange;
};

class CQuickList::CListHitInfo
{
public:
	int m_item;
	int m_subitem;
	bool m_onImage;
	bool m_onButton;
};

class CQuickList::CHeaderRightClick
{
public:
	int m_column;
	CPoint m_mousePos;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUICKLIST_H__92CE873E_DD8F_11D8_B14D_002018574596__INCLUDED_)
