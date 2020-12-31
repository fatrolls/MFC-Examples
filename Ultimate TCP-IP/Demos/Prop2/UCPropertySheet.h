// UCPropertySheet.h: interface for the CUCPropertySheet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCPROPERTYSHEET_H__8D4BD2E1_183E_11D3_B57A_0080C83F712F__INCLUDED_)
#define AFX_UCPROPERTYSHEET_H__8D4BD2E1_183E_11D3_B57A_0080C83F712F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdafx.h"
#include "resource.h"

//UINT CALLBACK PagePatternProc(HWND hwndDlg,UINT uMsg,LPPROPSHEETPAGE lParam);
#include "UCWnd.h"
#include "UCPage.h"
class CUCPropertyElement;

class CUCPropertySheet : public CUCWnd 
{
public:
	int AddPage(CUCPage* page);
	CUCPropertySheet(HWND hParent, HINSTANCE hInst);
	virtual ~CUCPropertySheet();
	int Create(TCHAR* Title,CUCPropertyElement*);
	PROPSHEETHEADER HeaderStructure;
	CUCWnd *patterns;
	PROPSHEETPAGE psp[256];
	CUCPage *Pages[256];
	static int CALLBACK PropSheetProc(HWND hwndDlg,UINT uMsg,LPARAM lParam);

private:
	int NumPages;
	HWND m_hWndParent;
};

#endif // !defined(AFX_UCPROPERTYSHEET_H__8D4BD2E1_183E_11D3_B57A_0080C83F712F__INCLUDED_)
