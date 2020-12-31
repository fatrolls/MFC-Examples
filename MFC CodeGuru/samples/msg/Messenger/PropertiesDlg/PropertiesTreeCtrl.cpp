//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================


// PropertiesTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "PropertiesTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesTreeCtrl

CPropertiesTreeCtrl::CPropertiesTreeCtrl()
{
	m_PropertiesIndex = 0;

	m_LeftBracket = "<";
	m_RightBracket = ">";
}

CPropertiesTreeCtrl::~CPropertiesTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CPropertiesTreeCtrl, CColorTreeCtrl)
	//{{AFX_MSG_MAP(CPropertiesTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesTreeCtrl message handlers
void CPropertiesTreeCtrl::AddProperties(CTreeCursor &cursor,LPCSTR text,long properties,long action,COLORREF colorText,COLORREF color)
{
	CString str;

	str.Format("%i",properties);
	AddProperties(cursor,text,str,action,colorText,color);
}

void CPropertiesTreeCtrl::AddProperties(CTreeCursor &cursor,LPCSTR text,LPCSTR properties,long action,COLORREF colorText,COLORREF color)
{
	CString str(text);

	RemoveText(cursor);
	str +=": ";
	AddText(cursor,str);
	AddText(cursor,m_LeftBracket,RGB(0,0,255));
	m_PropertiesIndex = AddText(cursor,properties,colorText,color);
	AddText(cursor,m_RightBracket,RGB(0,0,255));

	SetAction(cursor,action);
}

void CPropertiesTreeCtrl::ModifyProperties(CTreeCursor &cursor,LPCSTR properties)
{
	SetText(cursor,m_PropertiesIndex,properties);
}

void CPropertiesTreeCtrl::ModifyProperties(CTreeCursor &cursor,COLORREF colorText,COLORREF color)
{
	SetColor(cursor,m_PropertiesIndex,colorText,color);
}

BOOL CPropertiesTreeCtrl::GetProperties(CTreeCursor &cursor,long &properties)
{
	CString str;

	if(GetText(cursor,m_PropertiesIndex,str))
	{
		properties = atoi(str);
		return TRUE;
	}

	return FALSE;
}

BOOL CPropertiesTreeCtrl::GetProperties(CTreeCursor &cursor,CString &properties)
{
	return GetText(cursor,m_PropertiesIndex,properties);
}

BOOL CPropertiesTreeCtrl::GetProperties(CTreeCursor &cursor,LPSTR properties,int size)
{
	CString str;

	if(GetText(cursor,m_PropertiesIndex,str))
	{
		strncpy(properties,str,size);
		return TRUE;
	}

	return FALSE;
}

BOOL CPropertiesTreeCtrl::GetProperties(CTreeCursor &cursor,COLORREF &colorText,COLORREF &color)
{
	return GetColor(cursor,m_PropertiesIndex,colorText,color);
}

BOOL CPropertiesTreeCtrl::GetProperties(CTreeCursor &cursor,CString &properties,COLORREF &colorText,COLORREF &color)
{
	if(GetText(cursor,m_PropertiesIndex,properties))
	{
		GetColor(cursor,m_PropertiesIndex,colorText,color);
		return TRUE;
	}

	return FALSE;
}

BOOL CPropertiesTreeCtrl::GetProperties(DWORD dwData,long &properties)
{
	CTreeCursor cursor = GetRootItem().Find(dwData);

	return GetProperties(cursor,properties);
}

BOOL CPropertiesTreeCtrl::GetProperties(DWORD dwData,CString &properties)
{
	CTreeCursor cursor = GetRootItem().Find(dwData);

	return GetProperties(cursor,properties);
}

BOOL CPropertiesTreeCtrl::GetProperties(DWORD dwData,LPSTR properties,int size)
{
	CTreeCursor cursor = GetRootItem().Find(dwData);

	return GetProperties(cursor,properties,size);
}

BOOL CPropertiesTreeCtrl::GetProperties(DWORD dwData,COLORREF &colorText,COLORREF &color)
{
	CTreeCursor cursor = GetRootItem().Find(dwData);

	return GetProperties(cursor,colorText,color);
}

BOOL CPropertiesTreeCtrl::GetProperties(DWORD dwData,CString &properties,COLORREF &colorText,COLORREF &color)
{
	CTreeCursor cursor = GetRootItem().Find(dwData);

	return GetProperties(cursor,properties,colorText,color);
}
