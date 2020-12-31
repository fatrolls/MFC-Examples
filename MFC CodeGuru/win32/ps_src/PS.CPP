#include "95enum.h"
#include "NTenum.h"
#include "mainwnd.h"

display *d = NULL;

int main(int argc, char **argv)
{
    OSVERSIONINFO info;
    info.dwOSVersionInfoSize = sizeof(info);
    GetVersionEx(&info);
    HWND window = NULL;
    process_enumerator *processes;

    if ( argc > 1 ) {
        window = CreateMainWnd();
        d=new window_display(window);
    }
    else
        d=new text_display;

    if (info.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
        processes = new Win95_enumerator(*d);
    else if ( info.dwPlatformId == VER_PLATFORM_WIN32_NT )
        processes = new NT_process_enumerator(*d);
    else
        MessageBox(NULL,
                   "Error",
                   "Sorry: This doesn't work on Win32s",
                   MB_OK);

    processes->show();

    MSG msg;

    if ( window ) {
        while ( GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    delete d;
    return 0;
}
