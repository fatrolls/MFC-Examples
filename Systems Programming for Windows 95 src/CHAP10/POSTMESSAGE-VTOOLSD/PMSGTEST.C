#include <windows.h>
#include <windowsx.h>

#define EXPORT __export
DWORD apiaddr;
DWORD vxdldr;
HWND hwndList;
HINSTANCE hInst;

#define arraysize(p) (sizeof(p)/sizeof((p)[0]))

LRESULT EXPORT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
void log(char *ctl, ...);

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
    {               // WinMain
    HWND hwnd;
    MSG msg;
    static char *szAppName = "PMSGTEST";
    
    hInst = hInstance;
    if (!hPrev)
        {           // register window class
        WNDCLASS wc;
        wc.style = 0;
        wc.lpfnWndProc = MainWndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = szAppName;
        if (!RegisterClass(&wc))
            return 0;
    }              // register window class
    
    hwnd = CreateWindow(szAppName, "VxD Test Program", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);
    
    if (!hwnd)
        return 0;
    
    ShowWindow(hwnd, nShow);
    
    while (GetMessage(&msg, 0, 0, 0))
        {           // process messages
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }           // process messages
    
    return msg.wParam;
    }               // WinMain

LRESULT EXPORT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {                           // MainWndProc
    switch (msg)
        {                       // process message
    
    case WM_CREATE:
        {                       // WM_CREATE
        FARPROC aPostMessage = (FARPROC) PostMessage;
        int code;
        
        _asm
            {                   // get api entry
            xor di, di
            mov es, di
            mov ax, 1684h
            mov bx, 4242h
            int 2fh
            mov word ptr apiaddr, di
            mov word ptr apiaddr+2, es
            }                   // get api entry
        
        if (!apiaddr)
            {                   // no VxD
            MessageBox(GetFocus(), "MYVXD.VXD isn't loaded", "Error", MB_ICONHAND | MB_OK);
            return -1;
            }                   // no VxD
        
        _asm
            {                   // register ourselves with VxD
            mov ax, 1
            mov bx, hwnd
            mov cx, WM_USER+256
            mov di, word ptr aPostMessage
            mov si, word ptr aPostMessage+2
            call [apiaddr]
            mov ax, 0
            rcl ax, 1
            mov code, ax
            }                   // register ourselves with VxD

        if (code)
            {                   // couldn't register
            MessageBox(GetFocus(), "Couldn't register ourselves with VxD", "Error", MB_ICONHAND | MB_OK);
            return -1;
            }                   // couldn't register    
        
        hwndList = CreateWindow("LISTBOX", "", WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL,
            0, 0, 0, 0, hwnd, NULL, hInst, NULL);
        if (!hwndList)
            return -1;
    
        return 0;
        }                       // WM_CREATE

    case WM_SIZE:
        if (hwndList)
            {                   // resize list control
            RECT rc;
            GetClientRect(hwnd, &rc);
            MoveWindow(hwndList, 0, 0, rc.right, rc.bottom, TRUE);
            }                       // resize list control
        return 0;

    case WM_DESTROY:
        if (apiaddr)
            _asm
                {               // unregister ourselves with VxD
                mov ax, 1
                xor bx, bx
                xor cx, cx
                xor di, di
                xor si, si
                call [apiaddr]
                }               // unregister ourselves with VxD
        PostQuitMessage(0);
        return 0;
    
    case WM_USER + 256:
        {                       // VxD notification
        static char* ctlname[] =
            {
            NULL,                   // 0
            NULL,                   // 1
            NULL,                   // 2
            NULL,                   // 3
            NULL,                   // 4
            NULL,                   // 5
            NULL,                   // 6
            "Create_VM",                    // 7
            "VM_Critical_Init",             // 8
            "VM_Init",                              // 9
            "VM_Terminate",                 // A
            "VM_Not_Executeable",   // B
            "Destroy_VM",                   // C
            "VM_Suspend",                   // D
            "VM_Resume",                    // E
            };
        LPSTR name = wParam < arraysize(ctlname) ? ctlname[wParam] : NULL;
        if (name)
            log("VM %8.8lX -- %s", lParam, name);
        return 0;
        }                       // VxD notification
        }                       // process message
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
    }                           // MainWndProc
    
void log(char *ctl, ...)
    {                           // log
    char buffer[256];
    int index;
    if (!hwndList)
        return;
    wvsprintf(buffer, ctl, (const void FAR*)(&ctl+1));
    if ((index = (int) SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)(LPSTR) buffer)) == LB_ERRSPACE)
        {                       // out of space
        SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
        index = (int) SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)(LPSTR) buffer);
        }                       // out of space
    SendMessage(hwndList, LB_SETTOPINDEX, index, 0);
    }                           // log
