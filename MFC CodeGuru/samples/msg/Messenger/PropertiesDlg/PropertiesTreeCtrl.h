#ifndef PROPERTIES_TREE_CTRL_H
#define PROPERTIES_TREE_CTRL_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropertiesTreeCtrl.h : header file
//

#ifndef COLOR_TREE_CTRL_H
	#include "ColorTreeCtrl.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesTreeCtrl window

class CPropertiesTreeCtrl : public CColorTreeCtrl
{
	int m_PropertiesIndex;
// Construction
public:
	CPropertiesTreeCtrl();

// Attributes
public:
	CString m_LeftBracket;
	CString m_RightBracket;

// Operations
public:
	void AddProperties(CTreeCursor &cursor,LPCSTR text,long properties,long action = 0,COLORREF colorText = -1,COLORREF color = -1);
	void AddProperties(CTreeCursor &cursor,LPCSTR text,LPCSTR properties,long action = 0,COLORREF colorText = -1,COLORREF color = -1);
	void ModifyProperties(CTreeCursor &cursor,LPCSTR properties);
	void ModifyProperties(CTreeCursor &cursor,COLORREF colorText,COLORREF color);

	BOOL GetProperties(CTreeCursor &cursor,long &properties);
	BOOL GetProperties(CTreeCursor &cursor,CString &properties);
	BOOL GetProperties(CTreeCursor &cursor,LPSTR properties,int size);
	BOOL GetProperties(CTreeCursor &cursor,COLORREF &colorText,COLORREF &color);
	BOOL GetProperties(CTreeCursor &cursor,CString &properties,COLORREF &colorText,COLORREF &color);

	BOOL GetProperties(DWORD dwData,long &properties);
	BOOL GetProperties(DWORD dwData,CString &properties);
	BOOL GetProperties(DWORD dwData,LPSTR properties,int size);
	BOOL GetProperties(DWORD dwData,COLORREF &colorText,COLORREF &color);
	BOOL GetProperties(DWORD dwData,CString &properties,COLORREF &colorText,COLORREF &color);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropertiesTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertiesTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESTREECTRL_H__8F409833_C8FE_11D1_B7DF_0060084C3BF4__INCLUDED_)
