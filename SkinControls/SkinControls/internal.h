
#pragma once

/////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C"{
#endif

	// Min thumb size
#define MIN_THUMB_SIZE					10

	// The scroll timer ID
#define ID_TIMER_DELAY					60000
#define ID_TIMER_SCROLL					60001

	// Startup scroll timer delay
#define TIME_SCROLL_DELAY				400
#define TIME_SCROLL_INTERVAL			50


#define HTITEM_MASK						0x0000000FL
#define HTVERT_MASK						0x000000F0L

	// Hittest item code
#define HTSCROLL_NONE					0x00000000L
#define HTSCROLL_LINEUP					0x00000001L
#define HTSCROLL_LINEDOWN				0x00000002L
#define HTSCROLL_THUMB					0x00000003L
#define HTSCROLL_PAGEUP					0x00000004L
#define HTSCROLL_PAGEDOWN				0x00000005L
#define HTSCROLL_SIZEBOX				0x00000006L

#define HTSCROLL_HORZ					0x00000000L
#define HTSCROLL_VERT					0x00000010L

#define GET_HTITEM(code) (code & HTITEM_MASK)
#define GET_HTVERT(code) (code & HTVERT_MASK)

	// status...
#define	SB_STATE_DEFAULT				0
#define	SB_STATE_HIGHLIGHT				1
#define	SB_STATE_SELECTED				2
#define	SB_STATE_DISABLED				3


	// Send scroll message
#define DoScrollMsg(hwnd, cmd, pos, fvert) \
	SendMessage((hwnd), (fvert) ? WM_VSCROLL : WM_HSCROLL, MAKEWPARAM((cmd), (pos)), 0)

#define RedrawFrame(hwnd) \
	SetWindowPos((hwnd), NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_DRAWFRAME  )


	// ScrollBar data structure
	typedef struct tagSKINSB {
		HWND             	hwnd;                    // The window handle
		UINT             	flags;                   // Scrollbar disable flags
		DWORD            	style;					 // The window style
		SCROLLINFO       	Horz;                    // Horizontal scroll information
		SCROLLINFO       	Vert;                    // Vertical scroll information
		WNDPROC          	pfnOldProc;              // The originally window procedure
		BOOL             	fLeftScrollBar;          // Has left scrollbar style
		BOOL             	fPreventStyleChange;     // Prevent window style change
		BOOL             	fMouseTracking;			 // Has mouse event tracking
		BOOL             	fTracking;               // Is tracking ?
		BOOL                fRichEdit;               // Whether richedit control
		DWORD              	dwTrackCode;             // Tracking hittest item code
		int              	nTrackPos;               // Tracking thumb position
		int              	pxMouseOffset;           // Tracking the thumb of mouse position offset
		UINT             	nScrollTimerMsg;         // 32 bit value, low-word -> message, high-word -> scroll command 
		DWORD              	dwLastCode;              // Current HitTest code
		HBITMAP             hBmp;					 // The scrollbar skin bitmap handle
	} SKINSB, *LPSKINSB;


	// Scrollbar size calculate structure
	typedef struct tagSBCALC {
		int     pxLeft;
		int     pxTop;
		int     pxRight;
		int     pxBottom;
		union {
			int pxUpArrow;
			int pxLeftArrow;
		};
		union {
			int pxDownArrow;
			int pxRightArrow;
		};
		union {
			int pxThumbTop;
			int pxThumbLeft;
		};
		union {
			int pxThumbBottom;
			int pxThumbRight;
		};
	} SBCALC, *LPSBCALC;

	// Scrollbar default size metrics
	typedef struct tagSBMETRICS {
		static const int cxVArrow;
		static const int cyVArrow;
		static const int cxHArrow;
		static const int cyHArrow;
		static const int cxThumb;
		static const int cyThumb;
	} SBMETRICS;

	// Internal functions
	void SkinSB_SetWindowBits(HWND hWnd, int iWhich, DWORD dwBits, DWORD dwValue);
	LPSKINSB SkinSB_GetSB(HWND hwnd);
	BOOL SkinSB_SetSBParms(LPSCROLLINFO psi, SCROLLINFO si, BOOL* pfScroll, int* plres, BOOL bOldPos);
	BOOL SkinSB_IsScrollInfoActive(LPCSCROLLINFO lpsi);
	void SkinSB_SBCalc(LPSKINSB psb, LPSBCALC lpcalc, BOOL fVert);
	BOOL SkinSB_GetSizeBoxRect(LPSKINSB psb, LPRECT lprc);
	BOOL SkinSB_GetScrollBarRect(LPSKINSB psb, BOOL fVert, LPRECT lprc);
	BOOL SkinSB_GetThumbRect(LPSKINSB psb, LPRECT lprc, BOOL fVert);
	BOOL SkinSB_GetGrooveRect(LPSKINSB psb, LPRECT lprc, BOOL fVert);

	//int  SkinSB_GetPosFromPoint(POINT point, BOOL fVert);

	// Draw functions
	void SkinSB_DrawScrollBar(LPSKINSB psb, HDC hdc, BOOL fVert);
	BOOL SkinSB_DrawGroove(LPSKINSB psb, HDC hdc, LPRECT lprc, BOOL fVert);
	void SkinSB_DrawThumb(LPSKINSB psb, HDC hdc, BOOL fVert, UINT uState);
	BOOL SkinSB_DrawArrow(LPSKINSB psb, HDC hdc, BOOL fVert, int nArrow, UINT uState);
	BOOL SkinSB_DrawSizeBox(LPSKINSB psb, HDC hdc);

	//void SkinSB_TrackLoop(LPSKINSB psb);
	void SkinSB_Track(LPSKINSB psb, DWORD dwTrackCode, POINT pt);
	BOOL SkinSB_TrackThumb(LPSKINSB psb, BOOL fVert, POINT pt);
	BOOL SkinSB_HotTrack(LPSKINSB psb, DWORD dwTrackCode, BOOL fMouseDown);
	DWORD SkinSB_HitTest(LPSKINSB psb, BOOL fVert, POINT pt);
	BOOL SkinSB_EnableArrows(LPSKINSB psb, int nBar, UINT wArrows);
	UINT SkinSB_GetDisableFlags(LPSKINSB psb, BOOL fVert);
	UINT SkinSB_GetState(LPSKINSB psb, BOOL fVert, UINT nHitItem);


	// Message functions
	LRESULT SkinSB_OnStyleChanged(LPSKINSB psb, int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	LRESULT SkinSB_OnNcHitTest(LPSKINSB psb, WPARAM wParam, LPARAM lParam);
	LRESULT SkinSB_OnNcPaint(LPSKINSB psb, HRGN hRgn);
	LRESULT SkinSB_OnNcCalcSize(LPSKINSB psb, BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	LRESULT SkinSB_OnNcMouseMove(LPSKINSB psb, WPARAM wParam, LPARAM lParam);
	LRESULT SkinSB_OnNcLButtonDown(LPSKINSB psb, WPARAM wParam, LPARAM lParam);
	LRESULT SkinSB_OnNcMouseLeave(LPSKINSB psb, WPARAM wParam, LPARAM lParam);
	LRESULT SkinSB_OnMouseMove(LPSKINSB psb, WPARAM wParam, LPARAM lParam);
	LRESULT SkinSB_OnLButtonUp(LPSKINSB psb, WPARAM wParam, LPARAM lParam);
	LRESULT SkinSB_OnTimer(LPSKINSB psb, WPARAM wParam, LPARAM lParam);


	// The scrollbar window procedure
	LRESULT CALLBACK SkinSB_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifdef __cplusplus
}
#endif

/*==========================================================================*\

===滚动条模型描述===

+-------------------------------+---+ <-------+
|								| A |        (1)
|								+---+ <-------+----------+
|								|   |                    |
|								|   |                    |
|								|---| <-------+          |
|								|   |         |          |
|			  (10)  			| - |        (2)         |
|								| - |         |          |
|								|   |         |         (3)
|								|---| <-------+          |
|								|   |                    |
|                               |   |                    |
|								+---+ <-------+          |
|								| V |        (4)         |
+---+-----------------------+---+---+ <-------+----------+
| <	|		[	||	 ]		| >	|///|        (5)
+---+-----------------------+---+---+ <-------+
^   ^       ^        ^      ^   ^
|	|		|        |      |   |
|	|		|        |      |   |
(8)            (7)          (6)
描述:
(1)
(2) 
(3)
(4) 
\*=========================================================================*/