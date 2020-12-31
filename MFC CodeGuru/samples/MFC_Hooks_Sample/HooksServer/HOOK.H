
#define PUBLIC
#if !_DEBUG
#define PRIVATE static
#else
#define PRIVATE
#endif


//
// Structure that contains the spy message data sent from the hook
// to the spy app to display.  The hwnd is sent using wParam of
// the WM_COPYDATA message, and the message number is in the dwData
// field of the COPYDATASTRUCT.  This structure allows the wParam,
// lParam and any optional extra data to be passed across.
//

LRESULT CALLBACK ClientGetMsgProc(INT hc, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ClientCallWndProc(INT hc, WPARAM wParam, LPARAM lParam);
void APIENTRY SetHookHandles(HHOOK hgetmsgHook, HHOOK hcallwndHook);

