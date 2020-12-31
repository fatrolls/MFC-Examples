//--------------------------------------------------------------------
// ÀÉ¦W : mltithrd.h
//--------------------------------------------------------------------
#define IDM_RESUME    1
#define IDM_SUSPEND   2
#define IDM_FOR       3
#define IDM_SLEEP     4
#define IDM_NODELAY   5

#define HIGHEST_THREAD    0x00
#define ABOVE_AVE_THREAD  0x3F
#define NORMAL_THREAD     0x7F
#define BELOW_AVE_THREAD  0xBF
#define LOWEST_THREAD     0xFF
#define SLEEPDELAY        1
#define FORLOOPDELAY      2
#define NODELAY           3

// ¨ç¦¡«Å§i
LONG APIENTRY MainWndProc (HWND, UINT, UINT, LONG);
VOID ThreadProc (DWORD *ThreadArg);
