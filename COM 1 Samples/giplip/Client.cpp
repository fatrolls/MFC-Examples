
#define _WIN32_DCOM 1
#include <windows.h>
#include <stdio.h>
#include "RectPoint.h"
#include "RectPoint_i.c"


#include "giplip.h"
#include "giplip.cpp"

DWORD WINAPI TP(void*pv)
{
// cast thread-param as a GIT cookie
    DWORD dwCookie = DWORD(pv);
    printf("Thread %d beginning\n", GetCurrentThreadId());
// enter a new STA
    HRESULT hr = CoInitialize(0);
    if (SUCCEEDED(hr))
    {
// import the cookie
        LIP(IPoint) pPoint(dwCookie, hr);
        if (SUCCEEDED(hr))
        {
            for (int i = 0; i < 1000; i++)
            {
                long x, y = rand();
                hr = pPoint->SetCoords(y, y);
                assert(SUCCEEDED(hr));
                hr = pPoint->GetCoords(&x, &y);
                assert(SUCCEEDED(hr) && x == y);
                if (!(i % 100))
                    printf("Thread %d completes %d\n", GetCurrentThreadId(), i);

            }
        }
        CoUninitialize();
    }
    printf("Thread %d ending\n", GetCurrentThreadId());
    return hr;
}


void main(void)
{
//    HRESULT hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

    if (SUCCEEDED(hr))
    {
        GIT _init_git;
        IPoint *pPoint = 0;
        hr = CoCreateInstance(CLSID_Point, 0, CLSCTX_ALL, IID_IPoint, (void**)&pPoint);
        if (SUCCEEDED(hr))
        {
            GIP(IPoint) gipPoint(pPoint, hr);
            assert(SUCCEEDED(hr));
            pPoint->Release();
            DWORD dw;
            HANDLE hthreads[] = 
            { 
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw),
                CreateThread(0, 0, TP, LPVOID(gipPoint.GetCookie()), 0, &dw)
            };
            WaitForMultipleObjects(sizeof(hthreads)/sizeof(*hthreads), hthreads,
                                   TRUE, INFINITE);
            
        }


        IRect *pRect = 0;
        hr = CoCreateInstance(CLSID_Rect, 0, CLSCTX_ALL,
                              IID_IRect, (void**)&pRect);
        if (SUCCEEDED(hr))
        {
            hr = pRect->SetCoords(2, 3, 4, 5);
            if (SUCCEEDED(hr))
            {
                long nVolume;
                hr = pRect->get_Volume(&nVolume);
                if (SUCCEEDED(hr))
                    printf("The Volume is %d\n", nVolume);
            }
            pRect->Release();
        }
        CoUninitialize();
        if (FAILED(hr))
        {
            char sz[1024];
            if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, hr, 0, sz, 1024, 0))
                strcpy(sz, "Unknown error");

            printf("%s (%x)\n", sz, hr);
        }
    }
}