// UCPage.h: interface for the CUCPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCPAGE_H__4083E746_19B5_11D3_B57C_0080C83F712F__INCLUDED_)
#define AFX_UCPAGE_H__4083E746_19B5_11D3_B57C_0080C83F712F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UCWnd.h"

class CUCPage : public CUCWnd  
{
public:
	virtual void OnKeyDown(HWND hWnd,int nVirtKey);
	HWND GetItemHWND(int item);
	virtual void OnInitDialog(WPARAM wParam,LPARAM lParam);
	virtual void OnDrawItem(LPDRAWITEMSTRUCT);
	CUCPage(int Templ,TCHAR *temTitle);
	virtual ~CUCPage();
	PROPSHEETPAGE psp;
	void HandleFocusState(LPDRAWITEMSTRUCT,INT);
	void HandleSelectionState(LPDRAWITEMSTRUCT,INT);
	TCHAR Title[256];
	virtual void OnPaint(HDC dc);
	BOOL IsButtonChecked(int nID);
	

protected:
	int GetItemInt(int nID);
	BOOL SetItemFloat(int nID, float fValue);
	BOOL GetItemFloat(int nID, float &fValue);
	BOOL SetItemInt(int nID, int nValue);
	BOOL GetItemInt(int nID, int &nValue);
	void Apply();
	static LRESULT CALLBACK ButtonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static WNDPROC PrevButtProc;
};

#endif // !defined(AFX_UCPAGE_H__4083E746_19B5_11D3_B57C_0080C83F712F__INCLUDED_)
