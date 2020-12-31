#include <windows.h>
#include <iostream>
#include <sstream>
#include <math.h>

#include "aaform.hpp"

using namespace std;

HBITMAP transbmp;
BITMAP transbmpdat;

#define TESTFUNC 0
#define IMAGENAME "test.bmp"

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_PAINT:
            {
                HDC ldc = CreateCompatibleDC(0);
                SelectObject(ldc, transbmp);
                HDC ddc = GetDC(hwnd);
                BitBlt(ddc, 0, 0, transbmpdat.bmWidth, transbmpdat.bmHeight, ldc, 0, 0, SRCCOPY);
                ReleaseDC(hwnd, ddc);
                DeleteDC(ldc);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
    }
    return DefWindowProc (hwnd, message, wParam, lParam);
}

bool callbackfunc(double percentdone)
{
    cout << (int)(percentdone * 1000) / 10.0 << "% Completed" << endl;
    return false;
}

int main()
{
	return WinMain(NULL, NULL, NULL, SW_SHOW);
}

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    //Load and rotate image
    HBITMAP hsrcbmp = (HBITMAP)LoadImage(NULL, IMAGENAME, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

    int starttime = GetTickCount();

    vector<double> x;
    vector<double> y;

    //A variety of tests
    if (TESTFUNC == 0)
    {
        x.push_back(200); y.push_back(30);
        x.push_back(500); y.push_back(0.0);
        x.push_back(300); y.push_back(500);
        x.push_back(0); y.push_back(400);

        transbmp = aaform::createtransform(hsrcbmp, x, y, callbackfunc, 0xFF00FF);
    }
    else if (TESTFUNC == 1)
    {
        transbmp = aaform::stretch(hsrcbmp, .7, .6, callbackfunc, 0xFFFFFF);
    }
    else if (TESTFUNC == 2)
    {
        transbmp = aaform::rotate(hsrcbmp, 37, callbackfunc, 0xFF00FF);
    }
    else if (TESTFUNC == 3)
    {
        transbmp = aaform::skewverticle(hsrcbmp, 37, callbackfunc, 0xFF00FF);
    }
    else if (TESTFUNC == 4)
    {
        transbmp = aaform::skewhorizontal(hsrcbmp, 37, callbackfunc, 0xFF00FF);
    }

    cout << "Transform completed in " << GetTickCount() - starttime << " milliseconds" << endl;    

    DeleteObject(hsrcbmp);

    //Get info on the image so we can create the right sized window and for drawing
    GetObject(transbmp, sizeof(BITMAP), &transbmpdat);

    //Standard windows code
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = "Rotator";
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (0, "Rotator", "Rotation Example", WS_OVERLAPPEDWINDOW,  CW_USEDEFAULT,  CW_USEDEFAULT, 
           transbmpdat.bmWidth + 8, transbmpdat.bmHeight + 34, HWND_DESKTOP, NULL, hThisInstance, NULL);    

    ShowWindow (hwnd, nFunsterStil);
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return (int)messages.wParam;
}
