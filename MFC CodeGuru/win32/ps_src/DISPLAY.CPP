#include "display.h"

extern char head_string[];

void display::system_error(char const *name)
{

// Retrieve, format, and print out a message from the
// last errror.  The `name' that's passed should be in the form of a
// present tense noun (phrase) such as "opening file".
//
	char *ptr = NULL;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		0,
		GetLastError(),
		0,
		(char *)&ptr,
		1024,
		NULL);

    (*this) << "Error " << name << ": " << ptr;
    LocalFree(ptr);
}

void window_display::heading(char const *string) {

    for ( int i=0; string[i]; i++)
        head_string[i] = string[i];

    RECT parent_rect;
    GetClientRect(parent, &parent_rect);
    InvalidateRect(parent, &parent_rect, true);
    UpdateWindow(parent);
}


void window_display::show(char const *string)
{
    SendMessage(output, LB_ADDSTRING, 0 , (long)string);
}

void window_display::resize() {
    RECT rect;
    GetClientRect(parent, &rect);

    MoveWindow(output,
        rect.left,
        rect.top + 20,
        rect.right,
        rect.bottom - 20,
        true);
}

window_display::window_display(HWND p, RECT &rect) :
    parent(p)
{
    if ( rect.left == CW_USEDEFAULT )
        GetClientRect(parent, &rect);

    output = CreateWindow("LISTBOX",
        "Processes",
        WS_VSCROLL | WS_VISIBLE | WS_CHILD | LBS_USETABSTOPS |
            LBS_NOINTEGRALHEIGHT,
        rect.left,
        rect.top + 20,
        rect.right - rect.left,
        rect.bottom - rect.top - 20,
        parent,
        NULL,
        GetModuleHandle(NULL),
        NULL);

	int width = (rect.right - rect.left) / 4;

    int tab_stop = width - 10;

    SendMessage(output, LB_SETTABSTOPS, 1, (long)&tab_stop);
}

RECT window_display::rectDefault = {
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT
};


void text_display::show(char const *string)
{
    char newline = '\n';
    DWORD written;

    WriteFile(str, string, strlen(string), &written, NULL);
    WriteFile(str, &newline, 1, &written, NULL);
}

text_display::text_display(HANDLE stream) : str(stream)
{
    if (INVALID_HANDLE_VALUE == str) {
        str = GetStdHandle(STD_OUTPUT_HANDLE);
        if ( str == INVALID_HANDLE_VALUE)
            MessageBox(NULL, "Unable to get standard output handle",
                "Error", MB_OK | MB_ICONERROR);
    }
}
