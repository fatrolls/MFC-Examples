//---------------------------------------------------------------------
//           Generic - 示範 Win32 程式的基礎寫法
//                   Top Studio * J.J.Hou
// 檔名     : generic.c
// 作者     : 侯俊傑
// 編譯聯結 : 請參考 generic.mak
//---------------------------------------------------------------------

#include <windows.h>   // 每一個 Windows 程式都需要含入此檔
#include "resource.h"  // 內含各個 resource IDs
#include "generic.h"   // 本程式之含入檔

HINSTANCE _hInst;      // Instance handle
HWND      _hWnd;

char _szAppName[] = "Generic";    // 程式名稱
char _szTitle[]   = "Generic Sample Application"; // 視窗標題

//---------------------------------------------------------------------
// WinMain - 程式進入點
//---------------------------------------------------------------------
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,     int nCmdShow)
{
MSG msg;

  UNREFERENCED_PARAMETER(lpCmdLine);      // 避免編譯時的警告

  if (!hPrevInstance)
      if (!InitApplication(hInstance))
          return (FALSE);

  if (!InitInstance(hInstance, nCmdShow))
      return (FALSE);

  while (GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
  }

  return (msg.wParam); // 傳回 PostQuitMessage 的參數
}
//---------------------------------------------------------------------
// InitApplication - 註冊視窗類別
//---------------------------------------------------------------------
BOOL InitApplication(HINSTANCE hInstance)
{
WNDCLASS  wc;

  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;     // 視窗函式
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(hInstance, "jjhouricon");
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = GetStockObject(WHITE_BRUSH);  // 視窗背景顏色
  wc.lpszMenuName  = "GenericMenu";                // .RC 所定義的表單
  wc.lpszClassName = _szAppName;

  return (RegisterClass(&wc));
}
//---------------------------------------------------------------------
// InitInstance - 產生視窗
//---------------------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  _hInst = hInstance; // 儲存為全域變數，方便使用。

  _hWnd = CreateWindow(
                       _szAppName,
                       _szTitle,
                       WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT,
                       CW_USEDEFAULT,
                       CW_USEDEFAULT,
                       CW_USEDEFAULT,
                       NULL,
                       NULL,
                       hInstance,
                       NULL
                      );

  if (!_hWnd)
      return (FALSE);

  ShowWindow(_hWnd, nCmdShow); // 顯示視窗
  UpdateWindow(_hWnd);         // 送出 WM_PAINT
  return (TRUE);
}
//---------------------------------------------------------------------
// WndProc - 視窗函式
//---------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd,     UINT message,
                         WPARAM wParam, LPARAM lParam)
{
int wmId, wmEvent;

  switch (message) {
    case WM_COMMAND:

         wmId    = LOWORD(wParam);
         wmEvent = HIWORD(wParam);

         switch (wmId) {
           case IDM_ABOUT:
                DialogBox(_hInst,
                          "AboutBox",     // 對話盒資源名稱
                          hWnd,           // 父視窗
                          (DLGPROC)About  // 對話盒函式名稱
                         );
                break;

           case IDM_EXIT:
                // 使用者想結束程式。處理方式與 WM_CLOSE 相同。
                DestroyWindow (hWnd);
                break;

           default:
                return (DefWindowProc(hWnd, message, wParam, lParam));
         }
         break;

    case WM_DESTROY:  // 視窗已經被摧毀 (程式即將結束)。
         PostQuitMessage(0);
         break;

    default:
         return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return (0);
}
//---------------------------------------------------------------------
// About - 對話盒函式
//---------------------------------------------------------------------
LRESULT CALLBACK About(HWND hDlg,     UINT message,
                       WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);      // 避免編譯時的警告

  switch (message) {
    case WM_INITDIALOG:
         return (TRUE);      // TRUE 表示我已處理過這個訊息

    case WM_COMMAND:
         if (LOWORD(wParam) == IDOK
             || LOWORD(wParam) == IDCANCEL) {
             EndDialog(hDlg, TRUE);
             return (TRUE);  // TRUE 表示我已處理過這個訊息
         }
         break;
  }
  return (FALSE); // FALSE 表示我沒有處理這個訊息
}
//------------------------ end of file ------------------------------
