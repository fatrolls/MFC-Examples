//
//	Class:		CPPHtmlDrawer
//
//	Compiler:	Visual C++
//	Tested on:	Visual C++ 6.0
//				Visual C++ .NET 2003
//
//	Version:	See GetVersionC() or GetVersionI()
//
//	Created:	xx/xxxx/2004
//	Updated:	21/November/2004
//
//	Author:		Eugene Pustovoyt	pustovoyt@mail.ru
//
//	Disclaimer
//	----------
//	THIS SOFTWARE AND THE ACCOMPANYING FILES ARE DISTRIBUTED "AS IS" AND WITHOUT
//	ANY WARRANTIES WHETHER EXPRESSED OR IMPLIED. NO REPONSIBILITIES FOR POSSIBLE
//	DAMAGES OR EVEN FUNCTIONALITY CAN BE TAKEN. THE USER MUST ASSUME THE ENTIRE
//	RISK OF USING THIS SOFTWARE.
//
//	Terms of use
//	------------
//	THIS SOFTWARE IS FREE FOR PERSONAL USE OR FREEWARE APPLICATIONS.
//	IF YOU WISH TO THANK MY WORK, YOU MAY DONATE ANY SUM OF MONEY TO ME 
//  FOR SUPPORT OF DEVELOPMENT OF THIS CLASS.
//	IF YOU USE THIS SOFTWARE IN COMMERCIAL OR SHAREWARE APPLICATIONS YOU
//	ARE GENTLY ASKED TO DONATE ANY SUM OF MONEY TO THE AUTHOR:
//
//--- History ------------------------------ 
// 2004/03/01  *** Releases version 1.0 ***
//------------------------------------------
//		2004/04/13	[ADD] Added a "speed" parameter to a <ilst> tag for animation
//		2004/04/20	[ADD] For non-MFC program added STL class CStdString
//		2004/05/05	[ADD] Added an EnableOutput method
//					[FIX] Fixed an error in SetImageList method (thanks to topus)
//------------------------------------------
// 2004/05/05  *** Releases version 1.1 ***
//------------------------------------------
//		2004/06/06	[FIX] Fixed an error on select a reference to the handle of the font
//							instead select a handle of the font
//		2004/06/24	[ADD] Added SetMaxWidth and GetMaxWidth methods for supporting a text wrapping
//					[ADD] Added EnableTextWrap and IsTextWrapEnabled methods to sets a text wrap
//							mode or to retrieves a mode status.
//					[ADD] Added common character entities.
//		2004/06/25	[ADD] Added SetTabSize method.
//					[ADD] Implemented a support to output a justified text.
//					[ADD] Added new <justify> tag to output a justified text.
//		2004/07/18	[ADD] Support a disabled draw in the tables
//		2004/09/07	[FIX] Fixed minor errors of drawing table's cells 
//		2004/10/13	[FIX] The last line of the paragraph alignment on fields now is not applied
//		2004/10/20	[FIX] Fixed error in GetLengthUnit method. Thanks to Reinhard Steiner
//		2004/10/26	[FIX] Corrected work of the justify for the multifont text in one line
//		 			[ADD] Support a word wrapping for the text with the images
//		2004/10/28	[ADD] Now cx and cy parameters of the <ilst> tag is an optional information
//------------------------------------------
// 2004/10/30  *** Releases version 1.2 ***
//------------------------------------------
//		2004/11/30	[FIX] Fixed an error in the drawing nested tables
//		2004/12/05	[CHN] Replaces CImageList to HIMAGELIST
//					[CHN] Replaces MFC classes (CSize, CPoint, CRect) to API structures
//		2004/12/14	[FIX] Fixed an error in determinates of the hyperlink area
//					[FIX] Fixed an error in drawing of the horizontal line (<hr> tag)
//		2005/01/15	[ADD] Not fixed columns will resize to the width of the client area
//		2005/03/01	[FIX] Fixed an error of the imagelist drawing
/////////////////////////////////////////////////////////////////////
//
// "GotoURL" function by Stuart Patterson
// As seen in the August, 1997 Windows Developer's Journal.
// Copyright 1997 by Miller Freeman, Inc. All rights reserved.
// Modified by Chris Maunder to use TCHARs instead of chars.
//
// "Default hand cursor" from Paul DiLascia's Jan 1998 MSJ article.
// Modified by Zorglab to use standard hand cursor on WinMe,2k,XP
//
/////////////////////////////////////////////////////////////////////

#ifndef _PPHTMLDRAWER_H_
#define _PPHTMLDRAWER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// disable warning C4786: symbol greater than 255 character, okay to ignore
#pragma warning(disable : 4786)

#include "PPDrawManager.h"
#include <vector>
#include <map>

#ifdef _MFC_VER
	#define CPPString	CString //MFC program
#else
	#include "StdString.h"
	#ifdef _UNICODE
	#define CPPString	CStdStringW	//non-MFC program UNICODE
	#else
	#define CPPString	CStdStringA	//non-MFC program ANSI
	#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPHtmlDrawer window

class CPPHtmlDrawer
{
// Construction
public:
	CPPHtmlDrawer();

// Attributes
public:

// Operations
public:
	//Drawing methods
	void  Draw(HDC hDC, LPCTSTR lpszHtml, LPPOINT lpPoint);
	void  PrepareOutput(HDC hDC, LPCTSTR lpszHtml, LPSIZE lpSize); //Prepares to draw the HTML string
	void  DrawPreparedOutput(HDC hDC, LPCRECT lpRect);

	void  EnableEscapeSequences(BOOL bEnable = TRUE);
	void  EnableOutput(BOOL bEnable = TRUE);
	void  SetDisabledColor(COLORREF color);
	
	//Shadow of the image
	void SetImageShadow(int nOffsetX, int nOffsetY, BYTE nDarkenPercent = 50, BOOL bGradient = TRUE, int nDepthX = 7, int nDepthY = 7);

	CPPString GetResCommandPrompt(UINT nID, UINT nNumParam = 0);

	//Functions for the styles
	void SetTextStyle(LPCTSTR lpszStyleName, LPCTSTR lpszStyleValue);
	void SetCssStyles(LPCTSTR lpszCssString = NULL); //Sets the CSS styles
	void SetCssStyles(DWORD dwIdCssString, LPCTSTR lpszPathDll = NULL); //Sets the CSS styles
	LPCTSTR GetCssStyles(); //Returns the current CSS styles

	void OnLButtonDown(LPPOINT lpClient);
	BOOL OnSetCursor(LPPOINT lpClient);
	BOOL OnTimer(); //New timer count

	void SetHyperlinkCursor(HCURSOR hCursor = NULL); //Sets the cursor to be displayed when moving the mouse over a link. Specifying NULL will cause the control to display its default 'hand' cursor.
	HCURSOR GetHyperlinkCursor() const; //Returns the current link cursor.

	void SetCallbackHyperlink(HWND hWnd, UINT nMessage, LPARAM lParam = 0); //Sets the callback message: "Mouse over the link".
	void SetCallbackRepaint(HWND hWnd, UINT nMessage, LPARAM lParam = 0); //Sets the callback message: "Please repaint me".

	//Functions for images
	void SetImageList(UINT nIdBitmap, int cx, int cy, int nCount, COLORREF crMask = RGB(255, 0, 255));
	void SetImageList(HBITMAP hBitmap, int cx, int cy, int nCount, COLORREF crMask = RGB(255, 0, 255));

	void LoadResourceDll(LPCTSTR lpszPathDll, DWORD dwFlags = 0); //Sets the path to the resource's DLL
	void SetResourceDll(HINSTANCE hInstDll = NULL); //Sets the handle of the loaded resource's DLL

	void SetMaxWidth(int nWidth = 0) {m_nMaxWidth = nWidth;}; //Sets the maximum width of the output window.
	int  GetMaxWidth() {return m_nMaxWidth;}; //Gets the maximum width of the output window.
//	void EnableTextWrap(BOOL bEnable = TRUE){
//		m_bIsTextWrapEnabled = bEnable;};
//	BOOL IsTextWrapEnabled() {return m_bIsTextWrapEnabled;};

	void SetTabSize(int nSize) {m_nTabSize = nSize;};

	CPPDrawManager * GetDrawManager();

	static short GetVersionI()		{return 0x13;}
	static LPCTSTR GetVersionC()	{return (LPCTSTR)_T("1.3 beta");}
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPHtmlDrawer)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPPHtmlDrawer();

protected:
	enum{	ALIGN_LEFT = 0,
			ALIGN_CENTER,
			ALIGN_RIGHT,
			ALIGN_JUSTIFY
		};
	
	enum{	ALIGN_TOP = 0,
			ALIGN_VCENTER,
			ALIGN_BOTTOM,
			ALIGN_BASELINE
		};

	enum{	LINK_NONE = 0,
			LINK_HREF,
			LINK_MESSAGE
		};

	enum{	TEXT_TRANSFORM_NONE = 0,
			TEXT_TRANSFORM_UPPERCASE,
			TEXT_TRANSFORM_LOWERCASE,
			TEXT_TRANSFORM_CAPITALIZE
		};

	enum{	BORDER_STYLE_NONE = 0,
			BORDER_STYLE_SOLID,
			BORDER_STYLE_DOTTED,
			BORDER_STYLE_DASHED,
			BORDER_STYLE_DOUBLE,
		};

	enum {	TAG_NONE = 0,
			TAG_BOLD,
			TAG_ITALIC,
			TAG_UNDERLINE,
			TAG_STRIKEOUT,
			TAG_FONT,
			TAG_HLINE,
			TAG_NEWLINE,
			TAG_TABULATION,
			TAG_LEFT,
			TAG_CENTER,
			TAG_RIGHT,
			TAG_JUSTIFY,
			TAG_BASELINE,
			TAG_TOP,
			TAG_VCENTER,
			TAG_BOTTOM,
			TAG_BITMAP,
			TAG_ICON,
			TAG_IMAGELIST,
			TAG_STRING,
			TAG_NEWSTYLE,
			TAG_SPAN,
			TAG_HYPERLINK
		};

#pragma pack(1)
	typedef struct _STRUCT_TAGPROP
	{
		DWORD dwTagIndex;	// The hot rect of the hyperlink
		CPPString strTagName;	// The type of the hyperlink
	} STRUCT_TAGPROP;
#pragma pack()

#pragma pack(1)
	typedef struct _STRUCT_ANIMATION
	{
		int nIndex;		//The current index of the image
		int nMaxImages; //The max images in the bitmap
		int nTimerCount;//The current time position
		int nSpeed;		//The speed of animation
	} STRUCT_ANIMATION;
#pragma pack()

#pragma pack(1)
	typedef struct _STRUCT_HYPERLINK
	{
		RECT rcArea;		// The hot rect of the hyperlink
		int nTypeLink;		// The type of the hyperlink
		int nIndexLink;		// The index of the hyperlink
		CPPString sHyperlink; // The hyperlink
	} STRUCT_HYPERLINK;
#pragma pack()
	
#pragma pack(1)
	typedef struct _STRUCT_CHANGESTYLE 
	{
		CPPString strTag;		//The name of the last opened tag
		
		//Font
		int  nSizeFont;		//The height of the logic font
		int	 nWeightFont;	//The weight of the logic font
		BOOL bItalicFont;	//Is italic logic font?
		BOOL bUnderlineFont;//Is underline logic font?
		BOOL bStrikeOutFont;//Is strikeout logic font?
		BOOL bOverlineFont; //Is overline logic font?
		CPPString sFaceFont;  //The face name of the logic font
		
		//Color		
		COLORREF crText;	//The foreground color 
		COLORREF crBkgnd;	//The background color (also begin for the gradient)
		COLORREF crBorderLight;	//The border color
		COLORREF crBorderDark;	//The border color
		COLORREF crMidBkgnd;//The middle background color
		COLORREF crEndBkgnd;//The end background color

		//Fill
		int  nBkMode;		//The background mode for the text (TRANSPARENT, OPAQUE)
		int  nFillBkgnd;	//The fill effect of the background
		CPPString strNameResBk;

		//Align
		int  nHorzAlign;	//The horizontal align
		int  nVertAlign;	//The vertical align
		
		//Border
		int  nBorderStyle;	//The border style
		int  nBorderWidth;	//The width of the border

		//Cell Sizes
		int nCellWidth;		//The width of the cell
		int nCellHeight;	//The height of the cell
		BOOL bCellWidthPercent; //The width value in the percent
		BOOL bCellHeightPercent; //The height value in the percent

		//Text
		int  nTextTransform;//Transformation of the text (NONE, UPPERCASE, LOWERCASE, CAPITALIZE)

		int nMargin;		//Margins
		
		int nPadding;		//Padding
		
		//Hyperlink
		int  nTypeLink;		//The type of the link (NONE, HREF, MESSAGE)
		CPPString sHyperlink; //The additional parameter for the link
	} STRUCT_CHANGESTYLE; 
#pragma pack()
	
#pragma pack(1)
	typedef struct _STRUCT_IMAGE
	{
		int			nIndexImageList;//image's index of the image list
		int			nIdRes;			//ID resource from app
		int			nIdDll;			//ID resource from dll
		int			nHandle;		//handle of the resource
		int			cx;				//horizontal size of image
		int			cy;				//vertical size of image
		int			nWidth;			//width of image
		int			nHeight;		//height of image
		int         nSpeed;			//speed for animation
		UINT		nStyles;		//styles of image
		UINT		nHotStyles;		//hot styles of image
		BOOL        bUseMask;		//
		BOOL		bPercentWidth;
		BOOL		bPercentHeight;
		COLORREF	crMask;			//color of mask
		CPPString	strSrcFile;		//path on the source file
		CPPString   strPathDll;		//path on the resource dll
	} STRUCT_IMAGE;
#pragma pack()
	
#pragma pack(1)
	typedef struct _STRUCT_CALLBACK
	{
		HWND		hWnd;			/* Дескриптор окна, принимающего сообщение */
		UINT		nMessage;		// Message identifier
		WPARAM		wParam;
		LPARAM		lParam;
	} STRUCT_CALLBACK;
#pragma pack()

#pragma pack(1)
	typedef struct _STRUCT_HTMLLINE
	{
		int  nWidthLine;
		int  nHeightLine;
		int  nDescentLine;
		int  nAddPercentWidth;
		int  nHorzAlign;
		int  nSpaceChars;	//a count of space chars in the line
		BOOL bWrappedLine;	//TRUE if text was wrapped in the current line
	} STRUCT_HTMLLINE;
#pragma pack()

#pragma pack(1)
	typedef struct _STRUCT_CELL
	{
		int   nColSpan;			//-1 = Cell isn't used, >0 - How much columns was spaned
		int   nRowSpan;			//-1 = Cell isn't used, >0 - How much rows was spaned
		SIZE  szText;			//Real size of the text's area
		SIZE  szCell;			//Real size of the cell
		BOOL  bFixedWidth;		//TRUE if width of this cell was fixed
//		vecHtmlLine vecLines;
//		int   nWidth;			//Width of the cell
//		int   nHeight;			//Height of the cell
//		BOOL  bWidthPercent;	//if TRUE nWidth member in a percents
//		BOOL  bHeightPercent;	//if TRUE nHeight member in a percents
	} STRUCT_CELL;
#pragma pack()

	//Cells of Table
	typedef std::vector<STRUCT_CELL> vecRow;	//Alone row
	typedef std::vector<vecRow> vecTable;		//Vector of the rows is a table
	typedef std::vector<int> vecSize;			//Width of the columns or height of the rows
	typedef std::vector<BOOL> vecFlag;			//Flags for fixed widthes of the columns

#pragma pack(1)
	typedef struct _STRUCT_TABLE
	{
		vecTable  cells;	//Info about each cell of the table
		vecSize   width;	//Dimensions of the width of the columns
		vecSize	  height;	//Dimensions of the height of the rows
		vecFlag   fixed_width; //
	} STRUCT_TABLE;
#pragma pack()

	typedef std::vector<STRUCT_TABLE> vecTables;
	vecTables m_arrTables;	//All tables
	int   m_nCurTable;	  //The current index of the table
	int   m_nCurTableRow; //The current row of the table

	STRUCT_CALLBACK	m_csCallbackRepaint; //Callback for repaint HTML drawer
	STRUCT_CALLBACK	m_csCallbackLink; //Callback for hyperlink message
	STRUCT_CHANGESTYLE m_defStyle;
	STRUCT_HTMLLINE m_hline;

	CPPDrawManager m_drawmanager;
	
	//Values of the system context
	HIMAGELIST m_hImageList;
	SIZE m_szImageList;

	HINSTANCE m_hInstDll;
	BOOL m_bFreeInstDll;

	HCURSOR m_hLinkCursor;
	HFONT m_hOldFont;
	int m_nOldBkMode;
	COLORREF m_crOldText;
	COLORREF m_crOldBk;

//	BOOL m_bIsTextWrapEnabled;		//Is text wrap enabled
	BOOL m_bIsEnable; //TRUE for fullcolor output, FALSE for disabled output
	COLORREF m_crDisabled;
//	SIZE m_szOutput; // Output size
	RECT m_rcOutput; //Output rectangle
//	POINT m_ptOutput; //Output coordinates
	HDC m_hDC; //Device context to output or to prepare
	CPPString m_csHtmlText; //String to output

//	COLORREF m_clrShadow;

	int	  m_nNumPass;	//The number or type of the pass

	int   m_nTabSize;	// The max size for the each tabulation
	int   m_nMaxWidth;	// The max width for wrapping output
	int   m_nCurLine;   // The current drawing line
	int   m_nNumCurTable; //The number of the current table
//	RECT  m_rect; //
//	int m_nLineHeight; //The height of the current line
//	int m_nLineDescent;
	int m_nHoverIndexLink; //The index of the link under the mouse
	int m_nCurIndexLink;
	int m_nCurIndexAni; //The index of the animation
	BOOL m_bLastValueIsPercent;
	BOOL m_bEnableEscapeSequences; // 

	//Shadow of the image
	BOOL m_bGradientShadow;
	SIZE m_szOffsetShadow;
	SIZE m_szDepthShadow;
	BYTE m_nDarkenShadow;
	COLORREF m_crShadow;

	TEXTMETRIC m_tm;

	LOGFONT m_lfDefault; //Default font
	HFONT m_hFont;

	//Wrapper string
	CPPString m_strPrefix; //Prefix string 
	CPPString m_strPostfix; //Postfix string
	CPPString m_strCssStyles;

	//Vectors
	typedef std::vector<STRUCT_HTMLLINE> vecHtmlLine;
	vecHtmlLine m_arrHtmlLine;

	//Vector of the stack
	typedef std::vector<STRUCT_CHANGESTYLE> arrStack;
	arrStack m_arrStack;

	//Vector of the hyperlinks
	typedef std::vector<STRUCT_HYPERLINK> arrLink;
	arrLink m_arrLinks;

	typedef std::vector<STRUCT_ANIMATION> arrAni;
	arrAni m_arrAni;

	//Map of the colors by name
	typedef std::map<CPPString, COLORREF> mapColors;
	typedef std::map<CPPString, COLORREF>::iterator iterMapColors;
	mapColors m_mapColors;

	//Map of the styles
	typedef std::map<CPPString, CPPString> mapStyles;
	typedef std::map<CPPString, CPPString>::iterator iter_mapStyles;
	mapStyles m_mapStyles;
	mapStyles m_mapSpecChars;

	//Map of the colors by name
	typedef std::map<CPPString, STRUCT_TAGPROP> mapTags;
	typedef mapTags::iterator iterMapTags;
	mapTags m_mapTags;
//	mapTags m_mapTableProp;

protected:
	void SetListOfTags(); //Fill a map of tags
	void AddTagToList(LPCTSTR lpszName, DWORD dwTagIndex, LPCTSTR lpszFullName); //Add tag to the list of tags
	DWORD GetTagFromList(CPPString sTagName, CPPString & strFullName, BOOL & bCloseTag); //Get tag from the list

	void SetListSpecChars();
	void AddSpecChar(LPCTSTR lpszAlias, TCHAR tch);
	void AddSpecChar(LPCTSTR lpszAlias, LPCTSTR lpszValue);
	void ReplaceSpecChars();

	//The resource's methods
	HICON GetIconFromResources(DWORD dwID, int nWidth = 0, int nHeight = 0) const; //Load an icon from the app resources
	HICON GetIconFromFile(LPCTSTR lpszPath, int nWidth = 0, int nHeight = 0) const; //Load an icon from the file
	HICON GetIconFromDll(DWORD dwID, int nWidth = 0, int nHeight = 0, LPCTSTR lpszPathDll = NULL) const; //Load an icon from the dll resources
	HBITMAP GetBitmapFromResources(DWORD dwID) const; //Load a bitmap from the app resources
	HBITMAP GetBitmapFromFile(LPCTSTR lpszPath) const; //Load a bitmap from the file
	HBITMAP GetBitmapFromDll(DWORD dwID, LPCTSTR lpszPathDll = NULL) const; //Load a bitmap from the dll resources
	CPPString GetStringFromResource(DWORD dwID) const; //Load a string from the app resources
	CPPString GetStringFromDll(DWORD dwID, LPCTSTR lpszPathDll = NULL) const; //Load a string from the dll resources

	//The drawing methods
	void DrawHtml(LPSIZE lpSize, LPCRECT lpRect); //Draws the HTML text on device context or gets the size of the output area.
	SIZE DrawHtmlTable(CPPString & sTable, LPCRECT lpRect); //Draws the HTML table on device context or gets the size of the output area.
//	SIZE DrawHtmlTableRow(CPPString & sRow, LPCRECT lpRect, vecCol & row); //Draws the HTML row of the table
	void DrawHtmlTableRow(CPPString & sRow, LPCRECT lpRect, STRUCT_TABLE & st, int nRow);
	void DrawHtmlTableCell(CPPString & sCell, LPCRECT lpRect, STRUCT_CELL & sc); //Draws the HTML cell of the table
	SIZE DrawHtmlString(CPPString & sHtml, LPCRECT lpRect); //Draws the HTML string on device context or gets the size of the output area.

//public:
	//The methods
	void SetDefaultCssStyles();
	void SetDefaultCursor();
	LPLOGFONT GetSystemToolTipFont() const; //Gets the system logfont

	CPPString SearchNextTag(CPPString & str, CPPString & strTag, int & nIndex); //Search next tag
	BOOL SearchTag(CPPString & str, int & nIndex, CPPString strTag); //Search begin of the specified tag

	CPPString GetTagBody(CPPString & str, int & nIndex); //Gets a name of tag and the parameters of tag
	CPPString SplitTag(CPPString & sTag); //Split a tag to the tag's name and parameters
	CPPString GetNextProperty(CPPString & str, int & nIndex, CPPString & sProp); //Gets next property


	CPPString SearchPropertyOfTag(CPPString & str, int & nIndex); //Search a name or a property of a tag
	SIZE  AnalyseCellParam(CPPString & sTag, _STRUCT_CHANGESTYLE & cs, BOOL bTable);
	void  AnalyseImageParam(CPPString & strTag, _STRUCT_IMAGE & si);
	BOOL  IsImageWithShadow(_STRUCT_IMAGE & si);

	//Functions for hyperlink
	int PtInHyperlink(LPPOINT lpPoint);
	void JumpToHyperlink(int nLink);
	void StoreHyperlinkArea(int left, int top, int right, int bottom);
	HINSTANCE GotoURL(LPCTSTR url, int showcmd = SW_SHOW);
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);

	//Functions for notify
	void CallbackOnClickHyperlink(LPCTSTR sLink);
	void CallbackOnRepaint(int nIndexLink);

	//Running tag
	int  VerticalAlignText(int y, int nHeight);
	int  VerticalAlignImage(int y, int nHeight);
	void UpdateContext();
	BOOL StoreRestoreStyle(BOOL bRestore);
	void Tag_NewLine(LPPOINT lpPoint, int nNum, LPSIZE lpSize);
	void Tag_Tabulation(LPPOINT lpPoint, int nNum);
	int  InitNewLine(int x);

	void SelectNewHtmlStyle(LPCTSTR lpszNameStyle, STRUCT_CHANGESTYLE & cs);

	SIZE  GetTableDimensions(CPPString & sTable); //Gets dimensions of the table
	void  SearchEndOfTable(CPPString & str, int & nIndex); //Searching end of the table
	void  SearchEndOfRow(CPPString & str, int & nIndex); //Searching end of the row
	void  SearchEndOfCell(CPPString & str, int & nIndex); //Searching end of the cell

	//Functions for the map of the styles
	void SetTableOfColors();
	void SetColorName(LPCTSTR lpszColorName, COLORREF color);
	COLORREF GetColorByName(LPCTSTR lpszColorName, COLORREF crDefColor = RGB(0, 0, 0));

	BOOL GetIndexNextAlphaNum(CPPString & str, int & nIndex, BOOL bArithmetic = FALSE);
	BOOL GetBeginParameter(CPPString & str, int & nIndex, TCHAR chSeparator = _T(':'));
	TCHAR GetIndexNextChars(CPPString & str, int & nIndex, CPPString strChars);
	TCHAR GetIndexNextNoChars(CPPString & str, int & nIndex, CPPString strChars);
	CPPString GetParameterString(CPPString & str, int & nIndex, TCHAR chBeginParam = _T(':'), CPPString strSeparators = _T(";"));
	CPPString GetNameOfTag(CPPString & str, int & nIndex);
	CPPString GetWordWrap(CPPString & str, int nMaxSize, int & nRealSize);

	//Functions for the map of the styles
	LPCTSTR GetTextStyle(LPCTSTR lpszStyleName);
	void RemoveTextStyle(LPCTSTR lpszStyleName);
	void AddToTextStyle(LPCTSTR lpszStyleName, LPCTSTR lpszAddStyle);
	void UnpackTextStyle(CPPString strStyle, _STRUCT_CHANGESTYLE & cs);

	//Functions for analyzing parameters
	void SetDefaultStyles(_STRUCT_CHANGESTYLE & cs);
	BOOL GetStyleFontStyle(CPPString & str, BOOL bDefault);
	int  GetStyleFontWeight(CPPString & str, int nDefault);
	int  GetStyleHorzAlign(CPPString & str, int nDefault);
	int  GetStyleVertAlign(CPPString & str, int nDefault);
	COLORREF GetStyleColor(CPPString & str, COLORREF crDefault);
	int  GetStyleTextTransform(CPPString & str, int nDefault);
	CPPString GetStyleString(CPPString str, CPPString strDefault);
	void GetStyleFontShortForm(CPPString & str);
	UINT GetStyleImageShortForm(CPPString & str);
	int GetStyleBkgndEffect(CPPString & str, int nDefault);
	
	void StyleTextDecoration(CPPString & str, _STRUCT_CHANGESTYLE & cs);
	int StyleBorderWidth(CPPString & str, int Default);
	int StyleBorder(CPPString & str, int nDefault);

	//Get
	int GetLengthUnit(CPPString & str, int nDefault, BOOL bFont = FALSE);
	BOOL IsPercentableValue(CPPString & str);
	int GetTableWidth(CPPString & str, int nClientWidth, int nMinWidth, BOOL bSet = FALSE);

	//Drawing
	void DrawBackgroundImage(HDC hDC, int nDestX, int nDestY, int nWidth, int nHeight, CPPString strNameImage);

	int GetCountOfChars(CPPString str, TCHAR tchar = _T(' ')); //Gets counts of chars
};

#endif //_PPHTMLDRAWER_H_
