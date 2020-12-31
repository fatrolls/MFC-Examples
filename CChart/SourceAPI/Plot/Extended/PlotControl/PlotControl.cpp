#include "StdAfx.h"
#include "PlotControl.h"
#include "../../Basics/XYPlotImpl.h"
#include "../../Basics/XYHandler.h"

LRESULT CALLBACK PlotControlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//static CXYPlotImpl plot;
	static CXYPlotImplI plot;
	PlotData *plotdata;

	// 
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	
	switch (message) 
	{
	case WM_CREATE:
		plot.SetBkgndColor(GetSysColor(COLOR_3DFACE));
		plot.SetUseDataRegionBrush(false);
		break;
	case WM_DESTROY:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		plot.OnDraw(hWnd);

		GetClientRect(hWnd, &rt);
		DrawEdge(hdc, &rt, EDGE_SUNKEN, BF_RECT);
		
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MOUSEMOVE:
	case WM_CONTEXTMENU:
	case WM_SIZE:
	case WM_ERASEBKGND:
		plot.Interactive(hWnd, message, wParam, lParam);
		break;
	case WM_SETPLOTDATA:
		plotdata = (PlotData *)lParam;
		plot.AddCurve(plotdata->pX, plotdata->pY, plotdata->nLen);
		break;
	case WM_SETPLOTTITLE:
		plot.SetTitle((LPSTR)lParam);
		break;
	case WM_SETAXISTITLE:
		if(plot.GetAxisByLocation(int(wParam)))
		{
			plot.GetAxisByLocation(int(wParam))->SetTitle((LPSTR)lParam);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM RegisterPlotControl()
{	
	WNDCLASS wcls;
	// check to see if class already registered
	static const TCHAR szClass[] = _T("plotcontrol");
	if (GetClassInfo(GetModuleHandle(NULL), szClass, &wcls))
	{
		return 1;// name already registered - ok if it was us
	}
	// Use standard "button" control as a template.
	GetClassInfo(NULL, _T("button"), &wcls);
	// set new values
	wcls.style |= CS_DBLCLKS; // Make it to receive double clicks
	wcls.lpfnWndProc = (WNDPROC)PlotControlProc;
	wcls.hInstance = GetModuleHandle(NULL);
	wcls.lpszClassName = szClass;
	
	return RegisterClass(&wcls);
}