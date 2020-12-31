// FullTestAPI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include "../SourceAPI/Plot/PlotInterface.h"									////
#ifdef _DEBUG																////
#pragma comment(lib,"..\\SourceAPI\\Debug\\Plotd.lib")						////
#else																		////
#pragma comment(lib,"..\\SourceAPI\\Release\\Plot.lib")						////
#endif

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FULLTESTAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_FULLTESTAPI);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_FULLTESTAPI);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_FULLTESTAPI;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

LRESULT CALLBACK	PlotCtrlDlgProc(HWND, UINT, WPARAM, LPARAM);

double f(double x, double y)
{
	return 1.0/(x * x + y * y + 1.0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Chart *chart=0;//an pointer
	static int	charttype=0;//plot type

	CAxis *axis;
	double *pX, *pY;
	int i;
	DataPoint2D dp;
	MyVData2D vData;
	double x[2]={-1,1}, y[2]={-2,2};
	double range[4]={-1,1,-2,2};

	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_TEST_CLEAR:
			if(chart)
			{
				delete chart;
				chart=0;
				charttype=0;
			}
			hdc = GetDC(hWnd);
			SendMessage(hWnd,WM_ERASEBKGND,(WPARAM)hdc,0);
			ReleaseDC(hWnd, hdc);
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_XYPLOT:
			if(charttype==1)
			{
				break;
			}

			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			
			chart=new XYChartI;
			charttype=1;

			pX=new double[200];
			pY=new double[200];
			
			for(i=0; i<200; i++)
			{
				pX[i]=2.0/199.0*i;
				pY[i]=0.2*cos(pX[i]*8.0*myPi);
			}
			((XYChartI*)chart)->AddCurve(pX, pY, 200);
			delete []pX;
			delete []pY;

			chart->SetTitle("Test XY Plotting");
			axis=chart->AddAxis(kLocationBottom);
			axis->SetTitle("Bottom");
			axis=chart->AddAxis(kLocationLeft);
			axis->SetTitle("Left");

			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_DBLBUFFER:
			if(charttype==2)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			chart=new XYChartID;
			charttype=2;

			pX=new double[200];
			pY=new double[200];
			
			for(i=0; i<200; i++)
			{
				pX[i]=2.0/199.0*i;
				pY[i]=0.2*sin(pX[i]*8.0*myPi);
			}
			((XYChartID*)chart)->AddCurve(pX, pY, 200);
			delete []pX;
			delete []pY;

			chart->SetTitle("Test Double Buffer Plotting");
			axis=chart->AddAxis(kLocationBottom);
			axis->SetTitle("Bottom");
			axis=chart->AddAxis(kLocationLeft);
			axis->SetTitle("Left");

			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_PIEPLOT:
			if(charttype==3)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}	
			chart=new PieChartID;
			charttype=3;

			((PieChartID*)chart)->AddPie(3);
			((PieChartID*)chart)->AddPie(2);
			((PieChartID*)chart)->AddPie(1);
			((PieChartID*)chart)->AddPie(6);
			((PieChartID*)chart)->AddPie(7);

			chart->SetTitle("Test Pie Plotting");

			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_SPLITPLOT:
			if(charttype==4)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}	
			chart=new SplitChartID;
			charttype=4;
			
			((SplitChartID*)chart)->ResizePlots(kSplit3T2B1,2,2);

			
			pX=new double[200];
			pY=new double[200];
			
			for(i=0; i<200; i++)
			{
				pX[i]=2.0/199.0*i;
				pY[i]=0.2*sin(pX[i]*8.0*myPi);
			}
			((SplitChartID*)chart)->AddCurve(pX,pY,200,0);
			for(i=0; i<200; i++)
			{
				pY[i]=0.2*cos(pX[i]*8.0*myPi);
			}
			((SplitChartID*)chart)->AddCurve(pX,pY,200,1);
			for(i=0; i<200; i++)
			{
				pY[i]=pX[i]*pX[i];
			}
			((SplitChartID*)chart)->AddCurve(pX,pY,200,2);
			
			delete []pX;
			delete []pY;
			
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_LAYEREDPLOT:
			if(charttype==5)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}	
			chart=new LayeredChartID;
			charttype=5;
			
			((LayeredChartID*)chart)->AddLayer();
			((LayeredChartID*)chart)->AddLayer();

			pX=new double[200];
			pY=new double[200];
			
			for(i=0; i<200; i++)
			{
				pX[i]=2.0/199.0*i;
				pY[i]=0.2*sin(pX[i]*8.0*myPi);
			}
			((LayeredChartID*)chart)->AddCurve(pX, pY, 200, 0);
			for(i=0; i<200; i++)
			{
				pX[i]=2.0/199.0*i;
				pY[i]=20*cos(pX[i]*8.0*myPi);
			}
			((LayeredChartID*)chart)->AddCurve(pX, pY, 200, 1);
			delete []pX;
			delete []pY;

			((LayeredChartID*)chart)->SetTitle("Test Layered Plot");
			
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_BENDINGPLOT:
			if(charttype==6)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			//chart=new CDbBufBendingII<CBendingPlotImpl>(hWnd);
			chart=new BendChartID;
			charttype=6;
			
			((BendChartID*)chart)->AddBendingSect(0.0, myPi/2.0, 1.0, myPi/2.0);
			((BendChartID*)chart)->AddBendingSect(1.0, myPi/2.0, 2.0, myPi*3.0/4.0);
			((BendChartID*)chart)->InitBendingAxis( ); 

			pX=new double[200];
			pY=new double[200];
			
			for(i=0; i<200; i++)
			{
				pX[i]=2.0/199.0*i;
				pY[i]=0.2*sin(pX[i]*8.0*myPi);
			}
			((BendChartID*)chart)->AddCurve(pX, pY, 200);
			delete []pX;
			delete []pY;

			chart->SetTitle("Test Bending Plotting");
			axis=chart->AddAxis(kLocationBottom);
			axis->SetTitle("Bottom");
			axis=chart->AddAxis(kLocationLeft);
			axis->SetTitle("Left");
			
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_OBJECTPLOT:
			if(charttype==7)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			//chart=new CDbBufBendingII<CBendingPlotImpl>(hWnd);
			chart=new ObjChartID;
			charttype=7;
						
			pX=new double[200];
			pY=new double[200];
			
			for(i=0; i<200; i++)
			{
				pX[i]=2.0/199.0*i;
				pY[i]=0.2*sin(pX[i]*8.0*myPi);
			}
			((ObjChartID*)chart)->AddCurve(pX, pY, 200);
			((ObjChartID*)chart)->AddEllipse(1.25, 0.0, true, 0.2, true, 0.1, true, 1, 2, RGB(0,255,0), false, RGB(255,128,0));
			delete []pX;
			delete []pY;

			chart->SetTitle("Test Object Plotting");
			axis=chart->AddAxis(kLocationBottom);
			axis->SetTitle("Bottom");
			axis=chart->AddAxis(kLocationLeft);
			axis->SetTitle("Left");
						
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_OSCILLOPLOT:
			if(charttype==8)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			chart=new OscilloChartID;
			charttype=8;
			
			pX=new double[200];
			pY=new double[200];
			
			for(i=0; i<200; i++)
			{
				pX[i]=2.0/199.0*i;
				pY[i]=0.2*sin(pX[i]*8.0*myPi);
			}
			((OscilloChartID*)chart)->AddCurve(pX, pY, 200);
			delete []pX;
			delete []pY;

			chart->SetTitle("Test Oscillo Plotting");
			axis=chart->AddAxis(kLocationBottom);
			axis->SetTitle("Bottom");
			axis=chart->AddAxis(kLocationLeft);
			axis->SetTitle("Left");

			((OscilloChartID*)chart)->SetEnableXZoneSel(true);
			((OscilloChartID*)chart)->SetXZoneSelLower(1.0);
			((OscilloChartID*)chart)->SetXZoneSelUpper(1.5);
			
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_SPLINEPLOT:
			if(charttype==9)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			chart=new SplineChartID;
			charttype=9;
			
			vData.clear();
			for(i=1; i<8; i++)
			{
				dp.x=i;
				dp.y=i*i;
				vData.push_back(dp);
			}
			dp.x=10;dp.y=2;vData.push_back(dp);
			dp.x=12;dp.y=6;vData.push_back(dp);

			((SplineChartID*)chart)->AddDataSet(vData,kXYPlotScatter, RGB(0,255,128), kXYMarkerSquareUpright, 1);
			((SplineChartID*)chart)->AddSpline(vData);
			chart->SetTitle("Test Spline Plotting");
			axis=chart->AddAxis(kLocationBottom);
			axis->SetTitle("Bottom");
			axis=chart->AddAxis(kLocationLeft);
			axis->SetTitle("Left");
						
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_IMAGEPLOT:
			if(charttype==10)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			chart=new ImgChartID;
			charttype=10;
			
			((ImgChartID*)chart)->SetFieldFcn(f);
			
			((ImgChartID*)chart)->SetRanges(x, y);
			((ImgChartID*)chart)->CreateMemDC(hWnd);
			((ImgChartID*)chart)->CreateImage();
			
			chart->SetTitle("Test Image Plotting");
			axis=chart->AddAxis(kLocationBottom);
			axis->SetTitle("Bottom");
			axis=chart->AddAxis(kLocationLeft);
			axis->SetTitle("Left");
	
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_CONTOURLINEPLOT:
			if(charttype==11)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			chart=new ContourLineChartID;
			charttype=11;
			
			((ContourLineChartID*)chart)->SetFieldFcn(f);
			
			((ContourLineChartID*)chart)->SetPlotRange(range);
			((ContourLineChartID*)chart)->CreateContour(20);
			((ContourLineChartID*)chart)->SetDataInfoDraw(true);
			
			chart->SetTitle("Test Contour Line Plotting");
			axis=chart->AddAxis(kLocationBottom);
			axis->SetTitle("Bottom");
			axis=chart->AddAxis(kLocationLeft);
			axis->SetTitle("Left");
			
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_STEMPLOT:
			if(charttype==12)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			chart=new StemChartID;
			charttype=12;
			
			pX=new double[5];
			for(i=0; i<5; i++)
			{
				pX[i]=i+1;
			}
			((StemChartID*)chart)->AddData(pX, 5);
			for(i=0; i<5; i++)
			{
				pX[i]=5-i;
			}
			((StemChartID*)chart)->AddData(pX, 5);
			delete pX;

			chart->SetTitle("Test Stem Plotting");
			axis=chart->AddAxis(kLocationBottom);
			axis->SetTitle("Bottom");
			axis=chart->AddAxis(kLocationLeft);
			axis->SetTitle("Left");
			
			SendMessage(hWnd, WM_PAINT, 0, 0);
			break;
		case ID_TEST_REALTIMEPLOT:
			if(charttype==13)
			{
				break;
			}
			
			if(chart!=0)
			{
				delete chart;
				chart=0;
			}
			chart=new CRealtimeDemoImplI(hWnd);
			charttype=13;
			((CRealtimeDemoImplI*)chart)->SetNumOfDatas(2);
			((CRealtimeDemoImplI*)chart)->Start();

			((CRealtimeDemoImplI*)chart)->SetTitle("Realtime Demo Plotting");
			break;
		case ID_TEST_PLOTCONTROL:
			RegisterPlotControl();
			DialogBox(hInst, (LPCTSTR)IDD_PLOTCONTROLTEST_DIALOG, hWnd, (DLGPROC)PlotCtrlDlgProc);

			break;
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MOUSEMOVE:
	case WM_CONTEXTMENU:
	case WM_SIZE:
	case WM_ERASEBKGND:
		if(chart)
		{
			switch(charttype)
			{
			case 1:
				((XYChartI*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 2:
				((XYChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 3:
				((PieChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 4:
				((SplitChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 5:
				((LayeredChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 6:
				((BendChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 7:
				((ObjChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 8:
				((OscilloChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 9:
				((SplineChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 10:
				((ImgChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 11:
				((ContourLineChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 12:
				((StemChartID*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			case 13:
				((CRealtimeDemoImplI*)chart)->Interactive(hWnd, message, wParam, lParam);
				break;
			default:
				break;
			}				
		}
		else
		{
			if(message == WM_ERASEBKGND)
			{
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		if(chart)
		{
			chart->OnDraw(hWnd);
		}
		else
		{
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, "Demo Usage of CChart", strlen("Demo Usage of CChart"), &rt, DT_CENTER);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		if(chart)delete chart;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

// Mesage handler for about box.
LRESULT CALLBACK PlotCtrlDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	double pX[128], pY[128];
	PlotData pd;
	int i;
	switch (message)
	{
	case WM_INITDIALOG:
		
		for( i=0; i<128; i++)
		{
			pX[i] = i/128.0*4*myPi;
			pY[i] = 8.0*sin(pX[i]);
		}
		pd.pX = pX;
		pd.pY = pY;
		pd.nLen = 128;
		SendDlgItemMessage(hDlg, IDC_PLOTCONTROL, WM_SETPLOTDATA, 0, (LPARAM)&pd);
		SendDlgItemMessage(hDlg, IDC_PLOTCONTROL, WM_SETPLOTTITLE, 0, (LPARAM)"Test Control");
		SendDlgItemMessage(hDlg, IDC_PLOTCONTROL, WM_SETAXISTITLE, 0, (LPARAM)"Left");
		SendDlgItemMessage(hDlg, IDC_PLOTCONTROL, WM_SETAXISTITLE, 1, (LPARAM)"Bottom");
		return TRUE;
		
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
    return FALSE;
}
