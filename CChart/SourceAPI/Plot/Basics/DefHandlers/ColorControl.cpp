#include "StdAfx.h"
#include "ColorControl.h"
#include <commdlg.h>

BOOL MyChooseColor(COLORREF &cr, HWND hWnd)
{
	static CHOOSECOLOR cc;
	static COLORREF crCustColors[16];
	cc.lStructSize=sizeof(CHOOSECOLOR);
	cc.hwndOwner=hWnd;
	cc.hInstance=NULL;
	cc.rgbResult=cr;
	cc.lpCustColors =crCustColors;
	cc.Flags=CC_RGBINIT|CC_FULLOPEN|CC_ANYCOLOR;
	cc.lCustData=0;
	cc.lpfnHook=NULL;
	cc.lpTemplateName=NULL;
	BOOL ret=ChooseColor(&cc);
	if(ret)cr=cc.rgbResult;
	return ret;
}

LRESULT CALLBACK ColorControlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	COLORREF color,*pcolor;
	HBRUSH hb;
	
	switch (message) 
	{
	case WM_CREATE:
		SetWindowLong(hWnd,GWL_USERDATA,RGB(128,128,128));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rt);
		color=GetWindowLong(hWnd,GWL_USERDATA);
		hb=CreateSolidBrush(color);
		FillRect(hdc, &rt, hb);
		DeleteObject(hb);
		DrawEdge(hdc, &rt, EDGE_SUNKEN, BF_RECT);

		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDBLCLK:
		color=GetWindowLong(hWnd, GWL_USERDATA);
		if( MyChooseColor(color, hWnd) )
		{
			SetWindowLong(hWnd,GWL_USERDATA,color);
			GetClientRect(hWnd, &rt);
			InvalidateRect( hWnd, &rt, TRUE);
		}
		break;
	case WM_GETCOLOR:
		pcolor=(COLORREF *)lParam;
		*pcolor=GetWindowLong(hWnd,GWL_USERDATA);
		break;
	case WM_SETCOLOR:
		color=lParam;
		SetWindowLong(hWnd, GWL_USERDATA, color);
		GetClientRect(hWnd, &rt);
		InvalidateRect( hWnd, &rt, TRUE);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM RegisterColorControl()
{	
	WNDCLASS wcls;
	// check to see if class already registered
	static const TCHAR szClass[] = _T("colorcontrol");
	if (GetClassInfo(GetModuleHandle(NULL), szClass, &wcls))
	{
		return 1;// name already registered - ok if it was us
	}
	// Use standard "button" control as a template.
	GetClassInfo(NULL, _T("button"), &wcls);
	// set new values
	wcls.style |= CS_DBLCLKS; // Make it to receive double clicks
	wcls.lpfnWndProc = (WNDPROC)ColorControlProc;
	wcls.hInstance = GetModuleHandle(NULL);
	wcls.lpszClassName = szClass;
	
	return RegisterClass(&wcls);
}
