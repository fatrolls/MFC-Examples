#include "mainwnd.h"
#include "symbols.h"
#include "display.h"
#include <string.h>

extern display *d;
char head_string[256];

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    static int tab;

    switch (message) {
        case WM_CREATE:
            head_string[0] = '\0';
            RECT rect;

            GetClientRect(hWnd, &rect);
            tab = rect.right - rect.left - 400;
            return TRUE;

        case WM_SIZE:
            if ( d )
                d->resize();
            break;

        case WM_SETFOCUS:
            break;
   
        case WM_PAINT: {
            hdc = BeginPaint (hWnd, &ps);

            TabbedTextOut(hdc,
                0,
                0,
                head_string,
                strlen(head_string),
                1,
                &tab,
                0);

            EndPaint (hWnd, &ps);
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
             break;

        case WM_COMMAND:
             switch(wParam) {
                case IDM_EXIT:
                    PostQuitMessage(0);
                    break;
                default:
                    break;
             }
             break;

        default:
             return DefWindowProc(hWnd, message, wParam, lParam);     
    }
    return 0;
}


HWND CreateMainWnd()
{
    WNDCLASS  wc;
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
    HWND hWnd;

    wc.style         = CS_PARENTDC;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (hInstance, "PS");
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = "PS";
    wc.lpszClassName = "PS";

    RegisterClass(&wc);

    hWnd = CreateWindow("PS",
        "Processes",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        0,
        CW_USEDEFAULT,
        0,
        NULL,
        NULL,
        hInstance,
        NULL);
   
    if (!hWnd) {
        int reason = GetLastError();
        return NULL;
    }

    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);

    return hWnd;
}
