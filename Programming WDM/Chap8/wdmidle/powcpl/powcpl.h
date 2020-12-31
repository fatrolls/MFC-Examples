// powcpl.h -- Declarations for sample power-management property page provider
// Copyright (C) 1998 by Walter Oney
// All rights reserved

#ifndef POWCPL_H
#define POWCPL_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define arraysize(p) (sizeof(p)/sizeof((p)[0]))

enum HEAPTYPE {LOCALHEAP, SHELLHEAP};

#ifdef _DEBUG
	#define ASSERT_THIS_VALID() pThis->AssertValid()
#else
	#define AssertValid()
	#define ASSERT_THIS_VALID()
#endif

///////////////////////////////////////////////////////////////////////////////

class CShellxApp : public CWinApp
{
public:

	//{{AFX_VIRTUAL(CShellxApp)
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CShellxApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////

class CShellPropPage : public CPropertyPage
{								// class CShellPropPage
	DECLARE_DYNAMIC(CShellPropPage)

public:
	CShellPropPage(CCmdTarget* parent, UINT id);
	virtual ~CShellPropPage();

	CCmdTarget*	m_parent;
	UINT (CALLBACK* m_callback)(HWND, UINT, LPPROPSHEETPAGE);

	HRESULT AddPage(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
};								// class CShellPropPage

#include "page1.h"

///////////////////////////////////////////////////////////////////////////////
																			
class CShellExtension : public CCmdTarget
{								// class CShellExtension
	DECLARE_DYNCREATE(CShellExtension)
	CShellExtension();

private:
	DWORD	m_sig;

public:
	//{{AFX_VIRTUAL(CShellExtension)
	//}}AFX_VIRTUAL

protected:

	virtual ~CShellExtension();

#ifdef _DEBUG
	void AssertValid();
#endif

	CPage1			m_page1;
	IDataObject*			m_data;		// current data object
	HKEY					m_hkey;		// registry key
	LPCITEMIDLIST			m_idlist;	// ID list for affected object
	CString					m_source;	// name of drag source or context menu subject

	//{{AFX_MSG(CShellExtension)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CShellExtension)

	DECLARE_INTERFACE_MAP()

	// IShellExtInit interface
	BEGIN_INTERFACE_PART(ShellExtInit, IShellExtInit)
		STDMETHOD(Initialize)(LPCITEMIDLIST idlist, LPDATAOBJECT objects, HKEY hkey);
	END_INTERFACE_PART(ShellExtInit)

	// IShellPropSheetExt interface
	BEGIN_INTERFACE_PART(ShellPropSheetExt, IShellPropSheetExt)
		STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
		STDMETHOD(ReplacePage)(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam);
	END_INTERFACE_PART(ShellPropSheetExt)
};								// class CShellExtension

///////////////////////////////////////////////////////////////////////////////

inline CString UuidToCString(const UUID& iid)
	{
	LPTSTR s;
#ifdef _UNICODE
	UuidToString((UUID*) &iid, (LPWSTR) &s);
#else
	UuidToString((UUID*) &iid, (PBYTE*) &s);
#endif
	CString result(s);
	RpcStringFree((PBYTE*) &s);
	return result;
	}

#define IMPLEMENT_DUAL_INTERFACE_IUNKNOWN(theClass, localClass) \
ULONG theClass::X##localClass::AddRef() { \
	METHOD_PROLOGUE(theClass, localClass) \
	return pThis->ExternalAddRef(); } \
ULONG theClass::X##localClass::Release() { \
	METHOD_PROLOGUE(theClass, localClass) \
	return pThis->ExternalRelease(); } \
HRESULT theClass::X##localClass::QueryInterface(REFIID iid, PVOID* ppv) { \
	METHOD_PROLOGUE(theClass, localClass) \
	return (HRESULT) pThis->ExternalQueryInterface(&iid, ppv); }

#endif
