#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

class display
{
public:
    virtual void show(char const *string) = 0;
    virtual void heading(char const *string) = 0;
    void system_error(char const *name);
    virtual void resize() {}
    virtual ~display() {}
};


class text_display : public display {

    HANDLE str;

public:
    text_display(HANDLE stream = INVALID_HANDLE_VALUE);
    virtual void show(char const *string);
    virtual void heading(char const *string) {
        show(string);
    }
};


class window_display : public display {

    HWND output;
    HWND parent;

public:
    static RECT rectDefault;

    window_display(HWND p, RECT &rectangle = rectDefault);

    virtual void show(char const *string);
    virtual void heading(char const *string);
    virtual void resize();
};

inline display &operator<<(display &d, char const *string) {
	d.show(string);
	return d;
}

#endif
