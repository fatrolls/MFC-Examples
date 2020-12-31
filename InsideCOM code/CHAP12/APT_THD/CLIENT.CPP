//
// Client.cpp - Client implementation
//
#include <windows.h> 
#include <stdlib.h>
#include <objbase.h>
#include <assert.h>

#define __OUTPROC_SERVER_ // To get the proper definition of trace
#include "Util.h"
#undef __OUTPROC_SERVER_ 

#include "Iface.h"
#include "Apart.h"
#include "Cli-Apt.h"

static inline void trace(char* msg)
	{ Util::Trace("Client", msg, S_OK) ;} 
static inline void trace(char* msg, HRESULT hr)
	{ Util::Trace("Client", msg, hr) ;}

///////////////////////////////////////////////////////////
//
// The client application
//

#include "resource.h"

///////////////////////////////////////////////////////////
//
// Global variables for main apartment
//
// Module handle
HINSTANCE g_hModule = NULL ;

// Handle to child listbox
HWND g_hWndListBox = NULL ;

// ID of the timer
static UINT g_TimerId  = 0 ;

// Pointer to the interface on our component
static IX* g_pIX = NULL ; 

// Pointer to apartment thread class
CClientApartment* g_pApartment = NULL ;

///////////////////////////////////////////////////////////
//
// Functions prototypes
//

// Create and initialize the main window.
HWND InitWindow(int nCmdShow) ;

// Create the child listbox control.
BOOL CreateChildListbox(HWND hWndParent, int cx, int cy) ;

// The main window procedure
extern "C" LONG APIENTRY MainWndProc(HWND hWnd,
                                     UINT message,
                                     UINT wParam,
                                     LONG lParam) ;

// InitializeApartment - Create the thread and the component.
void InitializeApartment(HWND hWndMain) ;

// Timer tick message handler
void OnTick() ;

// Delete and tidy.
void CleanUp(HWND hWnd) ;

///////////////////////////////////////////////////////////
//
// WinMain function
//
extern "C" int WINAPI WinMain(HINSTANCE hInstance,
                              HINSTANCE hPrevInstance,
                              LPSTR lpCmdLine,
                              int nCmdShow)
{
	// Initialize the COM Library.
	HRESULT hr = CoInitialize(NULL) ;
	if (FAILED(hr))
	{
		return 0 ;
	}
   
	// Create the main window.
	HWND hWndMain = InitWindow(nCmdShow) ;
	if (hWndMain)
	{
		// Initialize the apartment.
		InitializeApartment(hWndMain) ;
		
		// Wait for a message.
		MSG msg ;
		while (::GetMessage(&msg, 0, 0, 0) > 0)
		{
			::DispatchMessage(&msg) ;
		}
	}

	// Uninitialize the COM Library.
	CoUninitialize() ;
	return 0 ;
}


///////////////////////////////////////////////////////////
//
// Initialize window.
//
HWND InitWindow(int nCmdShow) 
{
	// Fill in window class structure with parameters
      // that describe the main window.
	WNDCLASS  wcListview ;
	wcListview.style = 0 ;                     
	wcListview.lpfnWndProc =   (WNDPROC)MainWndProc ; 
	wcListview.cbClsExtra =    0 ;              
	wcListview.cbWndExtra =    0 ;              
	wcListview.hInstance =     g_hModule ;
	wcListview.hIcon =         ::LoadIcon(g_hModule,
	                                      MAKEINTRESOURCE(IDC_ICON)) ;
	wcListview.hCursor =       ::LoadCursor(NULL, IDC_ARROW) ;
	wcListview.hbrBackground = ::GetStockObject(WHITE_BRUSH) ; 
	wcListview.lpszMenuName =  NULL ;  
	wcListview.lpszClassName = "MyServerWinClass" ;

	BOOL bResult = ::RegisterClass(&wcListview) ;
	if (!bResult)
	{
		return NULL ;
	}

	HWND hWndMain ;

	hWndMain = ::CreateWindow("MyServerWinClass",
	                          "Component Server", 
	                          WS_OVERLAPPEDWINDOW,
	                          CW_USEDEFAULT, CW_USEDEFAULT,
	                          CW_USEDEFAULT, CW_USEDEFAULT,
	                          NULL,               
	                          NULL,               
	                          g_hModule,          
	                          NULL) ;

	// If window could not be created, return "failure".
	if (!hWndMain)
	{
		return NULL ;
	}

	// Make the window visible; update its client area;
	// and return "success".
	::ShowWindow(hWndMain, nCmdShow) ;
	::UpdateWindow(hWndMain) ; 
	
	return hWndMain ;      
}

///////////////////////////////////////////////////////////
//
// Create the listbox child control in the main window.
//
BOOL CreateChildListbox(HWND hWndParent, int cx, int cy) 
{
	// Create a listbox for output.
	g_hWndListBox =
		::CreateWindow("LISTBOX",
		               NULL, 
		               WS_CHILD | WS_VISIBLE | LBS_USETABSTOPS
			               | WS_VSCROLL | LBS_NOINTEGRALHEIGHT,
		               0, 0, cx, cy,
		               hWndParent,               
		               NULL,               
		               g_hModule,          
		               NULL) ;
	if (g_hWndListBox  == NULL)
	{
		// Listbox not created
		::MessageBox (NULL, "Listbox not created!", NULL, MB_OK ) ;
		return FALSE ;
	}
	else
	{
		return TRUE ;
	}
}

///////////////////////////////////////////////////////////
//
// InitializeApartment - Create the thread and the component.
//
void InitializeApartment(HWND hWnd)
{
	// Create a simple apartment object.
	g_pApartment = new CClientApartment ;

	// Start the thread.
	if (g_pApartment->StartThread())
	{
		trace("Successfully started thread.") ;

		// Create the component.
		HRESULT hr = g_pApartment->CreateComponent(CLSID_Component,
		                                           IID_IX,
		                                           (IUnknown**)&g_pIX) ;
		if (SUCCEEDED(hr))
		{
			trace("Successfully created component.") ;
			// Initialize the component.
			HRESULT hr = g_pIX->SetStartCount(1000) ;
			if (FAILED(hr))
			{
				trace("SetStartCount failed.", hr) ; 
			}

			// Start a timer.
			g_TimerId = SetTimer(hWnd, 369, 2*1000, NULL) ;
			assert(g_TimerId != 0) ;
			return ;
		}
	}
}

///////////////////////////////////////////////////////////
//
// OnTick - Called when the window gets a WM_TIMER message
//
void OnTick()
{
	if (g_pIX != NULL)
	{
		// Get the current count.
		long c = 0 ;
		HRESULT hr = g_pIX->GetCurrentCount(&c) ;
		assert(SUCCEEDED(hr)) ;

		// Display the count.
		strstream sout ;
		sout << "The current count is : "
		     << c 
		     << "."
		     << ends ;
		trace(sout.str()) ;
	}
}

///////////////////////////////////////////////////////////
//
// Main window procedure
//
extern "C" LONG APIENTRY MainWndProc(
	HWND hWnd,                // window handle
	UINT message,             // type of message
	UINT wParam,              // additional information
	LONG lParam)              // additional information
{
	DWORD dwStyle ;

	switch (message) 
	{
	case WM_CREATE:
		{
			// Create listbox control
			CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lParam) ;
			if (!CreateChildListbox(hWnd, pcs->cx, pcs->cy))
			{
				return -1 ;
			}			
		}
		break ;

	case WM_SIZE:
		::MoveWindow(g_hWndListBox,
		             0, 0,
		             LOWORD(lParam),
		             HIWORD(lParam),
		             TRUE) ;
		break ;

	case WM_TIMER:
		OnTick() ;
		break ;

	case WM_DESTROY:     // message: window being destroyed
		::PostQuitMessage(0) ;
		break ;

	case WM_CLOSE:
		CleanUp(hWnd) ;
		//Fall through 
	default:
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return 0 ;
}

///////////////////////////////////////////////////////////
//
//	CleanUp
//
void CleanUp(HWND hWnd)
{
	// The list box is going away.
	g_hWndListBox = NULL ;

	// Kill the timer.
	if (g_TimerId != 0)
	{
		BOOL b = KillTimer(hWnd, g_TimerId) ;
		assert(b = TRUE) ;
		g_TimerId = 0 ;
	}

	// Remove interface pointer.
	if (g_pIX != NULL)
	{
		g_pIX->Release() ;
		g_pIX = NULL ;
	}

	if (g_pApartment != NULL)
	{
		g_pApartment->StopThread() ;
		delete g_pApartment ;
		g_pApartment = NULL ;
	}

}
