#ifndef __HooksServer_h__
#define __HooksServer_h__

typedef struct
{
    WPARAM wParam;
    LPARAM lParam;
    BYTE ExtraData[64];
} CLIENTMSGDATA, *PCLIENTMSGDATA;

#define HOOKWINDOWNAME  "App8HooksClient"
#define HOOKWINDOWCLASS "App8HooksClientClass"

#define WM_HOOK_COPYDATA WM_USER + 666

#endif
