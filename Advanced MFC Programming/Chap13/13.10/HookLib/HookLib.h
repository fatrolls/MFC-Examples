#if !defined(__HOOKLIB_H__)
#define __HOOKLIB_H__

#include "Windows.h"
#include "BaseTyps.h"

#if !defined(__DLLIMPORT__)

#define DLLENTRY EXTERN_C __declspec(dllexport)
#define STDENTRY EXTERN_C __declspec(dllexport) HRESULT STDAPICALLTYPE
#define STDENTRY_(type) EXTERN_C __declspec(dllexport) type STDAPICALLTYPE

BOOL CALLBACK LibMain(HANDLE, DWORD, LPVOID);
int	CALLBACK WEP(int);
BOOL UnsetKeyboardHook();
LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);

#else

#define DLLENTRY EXTERN_C __declspec(dllimport)
#define STDENTRY EXTERN_C __declspec(dllimport) HRESULT STDAPICALLTYPE
#define STDENTRY_(type) EXTERN_C __declspec(dllimport) type STDAPICALLTYPE

#endif

STDENTRY_(BOOL) SetKeyboardHook(HWND, HINSTANCE);

#endif