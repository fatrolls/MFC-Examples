// UCWnd.h: interface for the CUCWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UCWND_H__952D63F8_1913_11D3_B57B_0080C83F712F__INCLUDED_)
#define AFX_UCWND_H__952D63F8_1913_11D3_B57B_0080C83F712F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdafx.h"
#include "resource.h"
#include "UCVTable.h"
#include "commdlg.h"





//UINT CALLBACK PagePatternProc(HWND hwndDlg,UINT uMsg,LPPROPSHEETPAGE lParam);

//void SetLine(HDC dc,int PenStyle,RECT rec);
//void SetRect(HDC dc,int BrushStyle,RECT rec);
class CUCVTable;
//class CUCPropertyElement;


class CUCWnd  
{
public:
	virtual void OnSetCursor();
	virtual void OnTimer(int nIdent);
	virtual void OnHelp(LPARAM lParam);   // GW: Added for help invoking
	virtual void OnUpdate(int item, HWND handle);
	virtual void OnSetActivePage();
	virtual void OnApply(BOOL);
	void OnNotify(WPARAM wParam,LPARAM lParam);
	virtual void OnEditChange(int,HWND);
	virtual void OnLButtonDown(int key,int px,int py);
	virtual void OnLButtonUp(int key,int px,int py);
	virtual void OnMouseMove(int key, WORD px, WORD py);
	COLORREF OpenColorDialog(COLORREF color);
	virtual void OnDropDown(int item,HWND handle);
	virtual void OnSetFocus(int item,HWND handle);
	virtual void OnMeasureitem(LPMEASUREITEMSTRUCT);
	virtual void OnPaint(HDC);
	virtual void OnSelChange(int,HWND);
	virtual void OnClicked(int);
	virtual void OnCommand(WPARAM wParam,LPARAM lParam);
	void OnWndCommand(int notification,int item,HWND handle);
	virtual void OnDrawItem(LPDRAWITEMSTRUCT);
	virtual void OnInitDialog(WPARAM wParam,LPARAM lParam);

	HWND m_hWnd;
	CUCWnd();
	virtual ~CUCWnd();
	static HINSTANCE m_hInstance;
	static BOOL CALLBACK DialogProc(HWND hwndDlg,UINT uMsg, WPARAM wParam,LPARAM lParam);
	static CUCVTable Vtable;
//	static CUCPropertyElement* PropertyElement;
//	static void SetPropertyElement(CUCPropertyElement*);
//	static CUCPropertyElement* GetPropertyElement();
	static CUCVTable *GetVTable();
	static CHOOSECOLOR ColorTable;
	static CHOOSECOLOR *GetChooseColor();
	static HINSTANCE GetInstan();
	static void SetInstan(HINSTANCE Inst);
protected:
	BOOL m_bChanged;
	
};


#endif // !defined(AFX_UCWND_H__952D63F8_1913_11D3_B57B_0080C83F712F__INCLUDED_)
