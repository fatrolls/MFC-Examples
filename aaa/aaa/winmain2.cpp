#include <windows.h>

class ZWindow;

ZWindow* g_pWnd = NULL;

class ZWindow
{
public:
	HWND m_hWnd;

	ZWindow(HWND hWnd = 0) : m_hWnd(hWnd) { }

	inline void Attach(HWND hWnd)
	{ m_hWnd = hWnd; }

	inline BOOL ShowWindow(int nCmdShow)
	{ return ::ShowWindow(m_hWnd, nCmdShow); }

	inline BOOL UpdateWindow()
	{  return ::UpdateWindow(m_hWnd); }

	inline HDC BeginPaint(LPPAINTSTRUCT ps)
	{  return ::BeginPaint(m_hWnd, ps); }

	inline BOOL EndPaint(LPPAINTSTRUCT ps)
	{  return ::EndPaint(m_hWnd, ps); }

	inline BOOL GetClientRect(LPRECT rect)
	{  return ::GetClientRect(m_hWnd, rect); }

	BOOL Create(LPCTSTR szClassName, LPCTSTR szTitle, HINSTANCE hInstance, 
		HWND hWndParent = 0, DWORD dwStyle = WS_OVERLAPPEDWINDOW, 
		DWORD dwExStyle = 0, HMENU hMenu = 0, int x = CW_USEDEFAULT, 
		int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, 
		int nHeight = CW_USEDEFAULT)
	{
		m_hWnd = ::CreateWindowEx(dwExStyle, szClassName, szTitle, dwStyle, 
			x, y, nWidth, nHeight, hWndParent, hMenu, 
			hInstance, NULL);
		return m_hWnd != NULL;
	}

	virtual LRESULT OnPaint(WPARAM wParam, LPARAM lParam)
	{
		HDC hDC;
		PAINTSTRUCT ps;
		RECT rect;

		hDC = BeginPaint(&ps);
		GetClientRect(&rect);
		::DrawText(hDC, "Hello world", -1, &rect, 
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(&ps);
		return 0;
	}

	virtual LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	virtual LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	static LRESULT CALLBACK StartWndProc(HWND hWnd, UINT uMsg, 
		WPARAM wParam, LPARAM lParam)
	{
		ZWindow* pThis = g_pWnd;

		if (uMsg == WM_NCDESTROY)
			::PostQuitMessage(0);

		switch (uMsg)
		{
		case WM_CREATE:
			pThis->OnCreate(wParam, lParam);
			break;

		case WM_PAINT:
			pThis->OnPaint(wParam, lParam);
			break;

		case WM_LBUTTONDOWN:
			pThis->OnLButtonDown(wParam, lParam);
			break;

		case WM_KEYDOWN:
			pThis->OnKeyDown(wParam, lParam);
			break;

		case WM_DESTROY:
			::PostQuitMessage(0);
			break;
		}

		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
};

class ZDriveWindow1 : public ZWindow
{
public:
	LRESULT OnPaint(WPARAM wParam, LPARAM lParam)
	{
		HDC hDC;
		PAINTSTRUCT ps;
		RECT rect;

		hDC = BeginPaint(&ps);
		GetClientRect(&rect);
		::SetBkMode(hDC, TRANSPARENT);
		::DrawText(hDC, "ZDriveWindow1", -1, &rect, 
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(&ps);

		return 0;
	}

	LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam)
	{
		::MessageBox(NULL, "ZDriveWindow1::OnLButtonDown", "Msg", MB_OK);
		return 0;
	}

};

class ZDriveWindow2 : public ZWindow
{
public:
	LRESULT OnPaint(WPARAM wParam, LPARAM lParam)
	{
		HDC hDC;
		PAINTSTRUCT ps;
		RECT rect;

		hDC = BeginPaint(&ps);
		GetClientRect(&rect);
		::SetBkMode(hDC, TRANSPARENT);
		::Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
		::DrawText(hDC, "ZDriveWindow2", -1, &rect,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(&ps);

		return 0;
	}

	LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam)
	{
		::MessageBox(NULL, "ZDriveWindow2::OnLButtonDown", "Msg", MB_OK);
		return 0;
	}

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine,   int nCmdShow)
{
	char szAppName[] = "Hello world";
	MSG msg;
	WNDCLASS wnd;
	ZDriveWindow1 zwnd1;
	ZDriveWindow2 zwnd2;

	wnd.cbClsExtra    = NULL;
	wnd.cbWndExtra    = NULL;
	wnd.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wnd.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hInstance     = hInstance;
	wnd.lpfnWndProc   = ZWindow::StartWndProc;
	wnd.lpszClassName = szAppName;
	wnd.lpszMenuName  = NULL;
	wnd.style         = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wnd))
	{
		MessageBox(NULL, "Can not register window class", "Error", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}

	g_pWnd = &zwnd1;
	zwnd1.Create(szAppName, "Hell world", hInstance);

	zwnd1.ShowWindow(nCmdShow);
	zwnd1.UpdateWindow();

	g_pWnd = &zwnd2;

	zwnd2.Create(szAppName, "Hello world", hInstance, zwnd1.m_hWnd, 
		WS_VISIBLE | WS_CHILD | ES_MULTILINE, NULL, NULL, 0, 0, 150, 150);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
