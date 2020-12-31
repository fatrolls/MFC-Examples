//--------------------------------------------------------------------
//           Mltithrd - 示範 threads 的產生與優先權的設定
//                      Top Studio * J.J.Hou
//
// 檔名     : mltithrd.c
// 作者     : 侯俊傑
// 編譯聯結 : 請參考 mltithrd.mak
// 創意來源 : "Multitask Windows NT" Chap6 (joel Powell/WAITE GROUP PRESS)
//
// 說明 : 本例產生 5 個 threads，各給予不同之優先權 (priority)；每個
//        threads 執行 1000 次迴路，迴路中不斷繪四方形，代表執行進度。
//        以此觀察 threads 之獨立情況以及優先權不同所帶來之影響。
//
//        你可以選擇以 Sleep() 或單純之 for loop 延遲 thread 的進行，
//        這也有助於你觀察 thread 釋放控制權。
//--------------------------------------------------------------------

#include <windows.h>
#include "mltithrd.h"

// 全域變數
HANDLE _hInst;
HANDLE _hWnd;
HANDLE _hThread[5];
UINT   _uDelayType=NODELAY;

//--------------------------------------------------------------------
// WinMain : 程式進入點
//--------------------------------------------------------------------
int APIENTRY WinMain (HANDLE hInstance, HANDLE hPrevInstance,
                      LPSTR lpCmdLine, int nCmdShow)
{
MSG  msg;
WNDCLASS wndclass;

   UNREFERENCED_PARAMETER(lpCmdLine);      // 避免編譯時的警告
   UNREFERENCED_PARAMETER(hPrevInstance);

   _hInst = hInstance;

   wndclass.style = 0;
   wndclass.lpfnWndProc = (WNDPROC)MainWndProc;
   wndclass.cbClsExtra = 0;
   wndclass.cbWndExtra = 0;
   wndclass.hInstance = hInstance;
   wndclass.hIcon = LoadIcon (hInstance, "Multi1Icon");
   wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
   wndclass.hbrBackground = GetStockObject (WHITE_BRUSH);
   wndclass.lpszMenuName = "Multi1Menu";
   wndclass.lpszClassName = "Multi1Class";

   RegisterClass(&wndclass);

   _hWnd = CreateWindow ("Multi1Class",
                         "Thread Priority Example",
                         WS_OVERLAPPED | WS_SYSMENU,
                         0, 0, 400, 250,
                         NULL,
                         NULL,
                         hInstance,
                         NULL);

   ShowWindow(_hWnd, nCmdShow);

   while (GetMessage (&msg, NULL, 0, 0)) {
      TranslateMessage (&msg);
      DispatchMessage (&msg);
   }
   return (msg.wParam);
}
//--------------------------------------------------------------------
// MainWndProc - 主視窗函式
//--------------------------------------------------------------------
LONG APIENTRY MainWndProc (HWND hWnd, UINT message,
                           UINT wParam, LONG lParam)
{
int    i;
DWORD  ThreadID[5];
static HMENU  hMenu;
static HANDLE hMasterThread;
static DWORD  ThreadArg[5] = {HIGHEST_THREAD,    // 0x00
                              ABOVE_AVE_THREAD,  // 0x3F
                              NORMAL_THREAD,     // 0x7F
                              BELOW_AVE_THREAD,  // 0xBF
                              LOWEST_THREAD      // 0xFF
                             };    // 用來調整四方形顏色

 switch (message) {
   case WM_CREATE:
      hMenu = GetMenu (hWnd);

      // 取得 primary thread handle 並設為最高 priority
      hMasterThread = GetCurrentThread();
      SetThreadPriority(hMasterThread, THREAD_PRIORITY_HIGHEST);

      for(i=0; i<5; i++)   // 產生 5 個 threads
          _hThread[i] = CreateThread(NULL,
                                    0,
                                    (LPTHREAD_START_ROUTINE)ThreadProc,
                                    &ThreadArg[i],
                                    CREATE_SUSPENDED,
                                    &ThreadID[i]);
      // 設定 thread priorities
      SetThreadPriority(_hThread[0], THREAD_PRIORITY_HIGHEST);
      SetThreadPriority(_hThread[1], THREAD_PRIORITY_ABOVE_NORMAL);
      SetThreadPriority(_hThread[2], THREAD_PRIORITY_NORMAL);
      SetThreadPriority(_hThread[3], THREAD_PRIORITY_BELOW_NORMAL);
      SetThreadPriority(_hThread[4], THREAD_PRIORITY_LOWEST);
      return (0);

   case WM_COMMAND:
      switch (LOWORD(wParam))
      {
         case IDM_RESUME:       // 讓 threads 開始執行
            EnableMenuItem(hMenu, IDM_RESUME, MF_BYCOMMAND | MF_GRAYED);
            EnableMenuItem(hMenu, IDM_SUSPEND, MF_BYCOMMAND | MF_ENABLED);
            DrawMenuBar(hWnd);
            for (i=0; i<5; i++)
                ResumeThread(_hThread[i]);   // 啟動 threads 的執行
            return (0);

         case IDM_SUSPEND:  // 暫停 threads 的執行
            for (i=0; i<5; i++)
                SuspendThread(_hThread[i]);   // 暫停 threads 的執行
            EnableMenuItem(hMenu, IDM_SUSPEND, MF_BYCOMMAND | MF_GRAYED);
            EnableMenuItem(hMenu, IDM_RESUME, MF_BYCOMMAND | MF_ENABLED);
            DrawMenuBar(hWnd);
            return (0);

         case IDM_FOR:    // 以 for loop 延遲 thread 的執行
            _uDelayType = FORLOOPDELAY;
            EnableMenuItem(hMenu, IDM_FOR, MF_BYCOMMAND | MF_GRAYED);
            EnableMenuItem(hMenu, IDM_SLEEP, MF_BYCOMMAND | MF_ENABLED);
            EnableMenuItem(hMenu, IDM_NODELAY, MF_BYCOMMAND | MF_ENABLED);
            DrawMenuBar(hWnd);
            return (0);

         case IDM_SLEEP:  // 以 Sleep() 延遲 thread 的執行
            _uDelayType = SLEEPDELAY;
            EnableMenuItem(hMenu, IDM_SLEEP, MF_BYCOMMAND | MF_GRAYED);
            EnableMenuItem(hMenu, IDM_FOR, MF_BYCOMMAND | MF_ENABLED);
            EnableMenuItem(hMenu, IDM_NODELAY, MF_BYCOMMAND | MF_ENABLED);
            DrawMenuBar(hWnd);
            return (0);

         case IDM_NODELAY:  // 不延遲 thread 的執行
            _uDelayType = NODELAY;
            EnableMenuItem(hMenu, IDM_NODELAY, MF_BYCOMMAND | MF_GRAYED);
            EnableMenuItem(hMenu, IDM_FOR, MF_BYCOMMAND | MF_ENABLED);
            EnableMenuItem(hMenu, IDM_SLEEP, MF_BYCOMMAND | MF_ENABLED);
            DrawMenuBar(hWnd);
            return (0);

         default:
            return (0);
      }

   case WM_DESTROY :
      for(i=0; i<5; i++)
          TerminateThread(_hThread[i], 0);   // 終止 threads
      PostQuitMessage (0);
      return (0);

   default:
      return DefWindowProc (hWnd, message, wParam, lParam);
   }
   return (0L);
}
//--------------------------------------------------------------------
// ThreadProc() - 本例之 5 個 threads 共用之 thread procedure
//--------------------------------------------------------------------
VOID ThreadProc(DWORD *ThreadArg)
{
RECT rect;
HDC  hDC;
HANDLE hBrush, hOldBrush;
DWORD dwThreadHits = 0;
char  cBuf[80];
int   iThreadNo, i;

   GetClientRect (_hWnd, &rect);
   hDC = GetDC (_hWnd);
   hBrush = CreateSolidBrush(RGB(*(ThreadArg), *(ThreadArg), *(ThreadArg)));  // 變化畫刷顏色
   hOldBrush = SelectObject(hDC, hBrush);

   switch (*ThreadArg) {
     case HIGHEST_THREAD   : iThreadNo = 0; break;
     case ABOVE_AVE_THREAD : iThreadNo = 1; break;
     case NORMAL_THREAD    : iThreadNo = 2; break;
     case BELOW_AVE_THREAD : iThreadNo = 3; break;
     case LOWEST_THREAD    : iThreadNo = 4; break;
   }

   // 顯示 thread 號碼及其優先權 (priority)
   wsprintf(cBuf, "T%d", iThreadNo);
   TextOut(hDC, *(ThreadArg), rect.bottom-150, cBuf, lstrlen(cBuf));
   wsprintf(cBuf, "P=%d", GetThreadPriority(_hThread[iThreadNo]));
   TextOut(hDC, *(ThreadArg), rect.bottom-130, cBuf, lstrlen(cBuf));

   do
   {
     dwThreadHits++;       // 計數器

     // 畫出四方形，代表 thread 的進行
     Rectangle(hDC, *(ThreadArg), rect.bottom-(dwThreadHits/10),
               *(ThreadArg)+0x40, rect.bottom);

     // 延遲...
     if (_uDelayType == SLEEPDELAY)
         Sleep(10);
     else if (_uDelayType == FORLOOPDELAY)
         for (i=0; i<30000; i++);
     else // _uDelayType == NODELAY)
         {   }
   } while (dwThreadHits < 1000);      // 巡迴  1000 次

   hBrush = SelectObject(hDC, hOldBrush);   // 恢復畫刷顏色
   DeleteObject (hBrush);
   ReleaseDC (_hWnd, hDC);
}
//------------------------- end of file ------------------------------
