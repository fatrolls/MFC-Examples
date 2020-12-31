int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow);long CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);
long CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);

void LoopThread(void * _this);
void ConnectThread(void * _this);
