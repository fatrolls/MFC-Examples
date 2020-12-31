#if !defined(AFX_DBLISTBOX_H__36762C87_0B4C_11D2_9BA2_967BD4D5D031__INCLUDED_)
#define AFX_DBLISTBOX_H__36762C87_0B4C_11D2_9BA2_967BD4D5D031__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DBListBox.h : header file
//

#define MAX_TABSTOP 10

enum COMMAND
{
	CMD_RESET,
	CMD_NEXT
};

/////////////////////////////////////////////////////////////////////////////
// CDBListBox window

class CDBListBox : public CListBox
{
// Construction
public:
	CDBListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBListBox)
	public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetCurrentID( void );
	short TabStops[ MAX_TABSTOP ];
	UINT m_Height;
	short ExtractString(COMMAND Command, CString &String);
	void SetTabStop(short idxTab, short posTab);
	void Init( UINT iHeight, const RECT & rect, CWnd * pParentWnd, UINT nID );
	virtual ~CDBListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDBListBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLISTBOX_H__36762C87_0B4C_11D2_9BA2_967BD4D5D031__INCLUDED_)
