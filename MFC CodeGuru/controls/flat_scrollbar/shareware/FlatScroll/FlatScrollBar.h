#if !defined(AFX_FLATSCROLLBAR_H__D71BA161_0455_11D2_BAF6_0060083D6967__INCLUDED_)
#define AFX_FLATSCROLLBAR_H__D71BA161_0455_11D2_BAF6_0060083D6967__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FlatScrollBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlatScrollBar window

class CFlatScrollBar 
{
// Construction
public:
	CFlatScrollBar();

// Attributes
public:
	CWnd *m_pWnd;

// Operations
public:
	BOOL EnableScrollBar(int, UINT);
	BOOL ShowScrollBar(int code, BOOL);

	BOOL GetScrollRange(int code, LPINT, LPINT);
	BOOL GetScrollInfo(int code, LPSCROLLINFO);
	int  GetScrollPos(int code);
	BOOL GetScrollProp(int propIndex, LPINT);

	int  SetScrollPos(int code, int pos, BOOL fRedraw);
	int  SetScrollInfo(int code, LPSCROLLINFO, BOOL fRedraw);
	int  SetScrollRange(int code, int min, int max, BOOL fRedraw);
	BOOL SetScrollProp(UINT index, int newValue, BOOL);

	BOOL InitializeFlatSB(CWnd *);
	HRESULT UninitializeFlatSB();

// Implementation
public:
	virtual ~CFlatScrollBar();

	// Generated message map functions
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATSCROLLBAR_H__D71BA161_0455_11D2_BAF6_0060083D6967__INCLUDED_)
